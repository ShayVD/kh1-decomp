/* The Vita's screen for the first port build (docs/vita-build.md): the GS memory model's display
 * buffer (host/null/gsmem.c, fed by the chain walk) copied to a 960 x 544 framebuffer after each
 * frame copy (brightfade.c's D_002A6890 send, the same hook as the host's KH1_HOST_SHOT present,
 * host/null/present.c), through the canvas map (include/platform/canvas.h): the 4:3 picture scaled
 * to the screen's height and centred, point-sampled, the pillarbox black.  This is a software
 * stand-in for the GXM renderer (vita-port-plan section 2): it shows only what the model draws (2D
 * sprites, clears, fades, uploads, copies), not the 3D (VIF1 / VU1 is not replaced yet).
 *
 * The left pillarbox carries a status strip so a black picture can be told from a hang: a square
 * that changes colour every 30 frames (the vblank count moves), a green bar per 256 disc reads
 * and a blue one per frame copy shown.  Not part of the PS2 build. */
#include <psp2/display.h>
#include <psp2/kernel/sysmem.h>
#include <string.h>
#include "common.h"
#include "gsregs.h"
#include "gsmem.h"
#include "dmawalk.h"
#include "platform/canvas.h"
#include "vita.h"

#define FB_W 960
#define FB_H 544
#define FB_SIZE ((FB_W * FB_H * 4 + 0x3FFFF) & ~0x3FFFF)

static u32 *fb[2];
static int fb_cur; /* the buffer on screen */
static u32 shown;  /* frame copies shown */
static u32 frame_copy;
static KH1Canvas canvas;
/* for each screen column / row, the display's column / line (-1: outside the picture) */
static s16 col_of[FB_W], line_of[FB_H];
static u32 line_buf[512];
static unsigned long status_frames; /* the last vblank's, for the strip after a copy */
static unsigned status_reads;
volatile u32 kh1_vita_sends, kh1_vita_last_send, kh1_vita_shown; /* the watchdog's (main.c) */

int kh1_vita_display_init(const void *frame_copy_send) {
    int i;
    for (i = 0; i < 2; i++) {
        void *base;
        SceUID id = sceKernelAllocMemBlock("kh1_fb", SCE_KERNEL_MEMBLOCK_TYPE_USER_CDRAM_RW, FB_SIZE, 0);
        if (id < 0 || sceKernelGetMemBlockBase(id, &base) < 0) return -1;
        fb[i] = base;
        memset(fb[i], 0, FB_SIZE);
    }
    kh1_canvas_fit(&canvas, (f32)FB_W, (f32)FB_H);
    for (i = 0; i < FB_W; i++) {
        f32 cx, cy;
        kh1_canvas_unmap(&canvas, (f32)i + 0.5f, 0.5f, &cx, &cy);
        col_of[i] = cx >= 0.0f && cx < 512.0f ? (s16)cx : -1;
    }
    frame_copy = (u32)(unsigned long)frame_copy_send;
    kh1_vita_flip();
    return 0;
}

/* the display's 448 lines are the canvas's 384 (NTSC's taller pixels) */
static void map_lines(u32 lines) {
    int i;
    for (i = 0; i < FB_H; i++) {
        f32 cx, cy;
        kh1_canvas_unmap(&canvas, 0.5f, (f32)i + 0.5f, &cx, &cy);
        line_of[i] = cy >= 0.0f && cy < 384.0f ? (s16)(cy * (f32)lines / 384.0f) : -1;
    }
}

static u32 abgr_of(u32 psm, u32 v) {
    if (psm == KH1_PSMCT16 || psm == KH1_PSMCT16S)
        v = (v & 0x1F) << 3 | (v >> 5 & 0x1F) << 11 | (v >> 10 & 0x1F) << 19;
    return 0xFF000000u | (v & 0xFFFFFF);
}

/* the model's buffer (FRAME's FBP, FBW, PSM) into the back buffer, then shown */
void kh1_vita_status(unsigned long frames, unsigned reads);
static void present_buffer(u32 bp, u32 bw, u32 psm, u32 lines) {
    u32 *out = fb[fb_cur ^ 1];
    int x, y, last = -2;
    u32 w = bw * 64 < 512 ? bw * 64 : 512;
    if (psm != KH1_PSMCT32 && psm != KH1_PSMCT24 && psm != KH1_PSMCT16 && psm != KH1_PSMCT16S) return;
    if (!bw) return;
    map_lines(lines);
    for (y = 0; y < FB_H; y++) {
        u32 *row = out + y * FB_W;
        int l = line_of[y];
        if (l == last && y) {
            memcpy(row, row - FB_W, FB_W * 4);
            continue;
        }
        last = l;
        if (l < 0) {
            memset(row, 0, FB_W * 4);
            continue;
        }
        for (x = 0; x < (int)w; x++) line_buf[x] = abgr_of(psm, kh1_gsmem_read_pixel(psm, bp, bw, x, l));
        for (x = 0; x < FB_W; x++) {
            int c = col_of[x];
            row[x] = c >= 0 && c < (int)w ? line_buf[c] : 0xFF000000u;
        }
    }
    shown++;
    kh1_vita_shown = shown;
    kh1_vita_flip();
    /* the copy filled the pillarbox black: the strip again (a vblank draws it too) */
    kh1_vita_status(status_frames, status_reads);
}

/* host/null/dmawalk.c's hook after each send: the frame copy's FRAME is the display buffer */
static void after_send(u32 tadr) {
    const KH1GsReg *r;
    kh1_vita_sends++;
    kh1_vita_last_send = tadr;
    if (tadr != frame_copy) return;
    r = &kh1_gs_state()->ctx[0].frame;
    present_buffer((r->lo & 0x1FF) * 32, r->lo >> 16 & 63, r->lo >> 24 & 63, 448);
}

void kh1_vita_present_on(void) { kh1_dma_after_send = after_send; }

static void fill(u32 *p, int x, int y, int w, int h, u32 c) {
    int i, j;
    for (j = y; j < y + h && j < FB_H; j++)
        for (i = x; i < x + w && i < FB_W; i++) p[j * FB_W + i] = c;
}

/* the status strip in the left pillarbox of the buffer on screen (see the header) */
void kh1_vita_status(unsigned long frames, unsigned reads) {
    status_frames = frames;
    status_reads = reads;
    static const u32 beat[4] = { 0xFF0000FFu, 0xFF00FFFFu, 0xFFFF00FFu, 0xFFFFFFFFu };
    u32 *p = fb[fb_cur];
    if (!p) return;
    fill(p, 8, 8, 16, 16, beat[(frames / 30) & 3]);
    fill(p, 8, 32, 100, 4, 0xFF000000u);
    fill(p, 8, 32, (int)(reads / 256 % 100), 4, 0xFF00FF00u);
    fill(p, 8, 40, 100, 4, 0xFF000000u);
    fill(p, 8, 40, (int)(shown % 100), 4, 0xFFFF0000u);
}

/* a whole-screen colour (the "no disc" screen) */
void kh1_vita_fill(u32 abgr) {
    u32 *p = fb[fb_cur ^ 1];
    int i;
    if (!p) return;
    for (i = 0; i < FB_W * FB_H; i++) p[i] = abgr;
    kh1_vita_flip();
}

void kh1_vita_flip(void) {
    SceDisplayFrameBuf f;
    fb_cur ^= 1;
    memset(&f, 0, sizeof f);
    f.size = sizeof f;
    f.base = fb[fb_cur];
    f.pitch = FB_W;
    f.pixelformat = SCE_DISPLAY_PIXELFORMAT_A8B8G8R8;
    f.width = FB_W;
    f.height = FB_H;
    sceDisplaySetFrameBuf(&f, SCE_DISPLAY_SETBUF_NEXTFRAME);
}

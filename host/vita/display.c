/* The Vita's screen (docs/vita-build.md): the GS memory model's display buffer (host/null/gsmem.c,
 * fed by the chain walk) shown after each frame copy (brightfade.c's D_002A6890 send, the same hook
 * as the host's KH1_HOST_SHOT present, host/null/present.c).  This shows only what the model draws
 * (2D sprites, clears, fades, uploads, copies), not the 3D (VIF1 / VU1 is not replaced yet).
 *
 * Session 135: drawn by the GPU.  The buffer's pixels are read once a frame into a 512 x 512 GXM
 * texture (kh1_gsmem_read_rect: two address tables, not the swizzle per pixel) and vita2d (vitasdk's
 * 2D library, whose shaders come compiled: there is no psp2cgc for the port's own, docs/sdk.md) draws
 * it as one quad through the canvas map (include/platform/canvas.h): the 4:3 picture scaled to the
 * screen's height and centred, bilinear, the pillarbox black.  Before, the CPU wrote all 960 x 544
 * pixels point-sampled, reading each through the swizzle.  The frame pacing stays main.c's (the
 * game's vblank on the Vita's), so vita2d does not wait for one.
 *
 * The left pillarbox carries a status strip so a black picture can be told from a hang: a square
 * that changes colour every 30 frames (the vblank count moves), a green bar per 256 disc reads
 * and a blue one per frame copy shown.  With no frame copy for 30 vblanks (a load) the last picture
 * is drawn again with the strip.
 *
 * Session 136: when the GPU renderer runs (gxm.c, kh1_vita_present_gpu), the picture is its display target,
 * drawn each vblank after the frame's GPU scenes (main.c), and the GS model draws no pixels.  Not part of the
 * PS2 build.
 *
 * Wide screen (config.txt wide=, docs/vita-build.md "Wide screen"): kh1_vita_display_mode picks how the
 * picture covers the 960 x 544 screen: 0 the 4:3 picture pillarboxed as above, 1 the GPU's wide display target
 * (main.c set the hor+ view, host/port/view.c, so the target is the view's 678 x 448) over the whole screen, 2 the
 * 4:3 picture stretched to the whole screen.  In 1 and 2 the status strip is drawn only while no picture is
 * shown (the boot, a load, a hang) or with strip=1. */
#include <psp2/display.h>
#include <psp2/gxm.h>
#include <psp2/kernel/processmgr.h>
#include <vita2d.h>
#include "common.h"
#include "gsregs.h"
#include "gsmem.h"
#include "dmawalk.h"
#include "platform/canvas.h"
#include "vita.h"

#define FB_W 960
#define FB_H 544
#define TEX_W 512
#define TEX_H 512

static vita2d_texture *tex;
static u32 shown; /* frame copies shown */
static u32 frame_copy;
static KH1Canvas canvas;
static u32 pic_w, pic_lines;               /* the texture's picture: columns, the display's lines */
static unsigned long status_frames, drawn_at; /* the last vblank's; the vblank of the last draw */
static unsigned status_reads;
static int gpu; /* session 136: the picture is gxm.c's display target */
static int mode; /* 0 4:3 pillarboxed, 1 the wide view's target, 2 4:3 stretched (kh1_vita_display_mode) */
static int strip_on = 1;
volatile u32 kh1_vita_sends, kh1_vita_last_send, kh1_vita_shown; /* the watchdog's (main.c) */
volatile u32 kh1_vita_us_present; /* session 135: microseconds in present_buffer (the watchdog's) */

int kh1_vita_display_init(const void *frame_copy_send) {
    if (vita2d_init() < 0) return -1;
    vita2d_set_vblank_wait(0);
    vita2d_set_clear_color(0xFF000000u);
    tex = vita2d_create_empty_texture_format(TEX_W, TEX_H, SCE_GXM_TEXTURE_FORMAT_A8B8G8R8);
    if (!tex) return -1;
    vita2d_texture_set_filters(tex, SCE_GXM_TEXTURE_FILTER_LINEAR, SCE_GXM_TEXTURE_FILTER_LINEAR);
    kh1_canvas_fit(&canvas, (f32)FB_W, (f32)FB_H);
    frame_copy = (u32)(unsigned long)frame_copy_send;
    vita2d_start_drawing();
    vita2d_clear_screen();
    vita2d_end_drawing();
    vita2d_swap_buffers();
    return 0;
}

static void strip(void) {
    static const u32 beat[4] = { 0xFF0000FFu, 0xFF00FFFFu, 0xFFFF00FFu, 0xFFFFFFFFu };
    vita2d_draw_rectangle(8, 8, 16, 16, beat[(status_frames / 30) & 3]);
    vita2d_draw_rectangle(8, 32, (float)(status_reads / 256 % 100), 4, 0xFF00FF00u);
    vita2d_draw_rectangle(8, 40, (float)(shown % 100), 4, 0xFFFF0000u);
}

/* the texture's picture over the canvas (its 512 columns and the display's lines are the canvas's
 * 512 x 384: NTSC's taller pixels), the strip, shown */
static void draw(void) {
    int pic = 0;
    vita2d_start_drawing();
    vita2d_clear_screen();
    if (gpu) {
        if (mode ? kh1_vita_gxm_present(0.0f, 0.0f, (f32)FB_W, (f32)FB_H)
                 : kh1_vita_gxm_present(canvas.ox, canvas.oy, 512.0f * canvas.s, 384.0f * canvas.s)) {
            shown++;
            pic = 1;
        }
        kh1_vita_shown = shown;
    } else if (pic_w && pic_lines) {
        if (mode)
            vita2d_draw_texture_part_scale(tex, 0.0f, 0.0f, 0, 0, (float)pic_w, (float)pic_lines, (float)FB_W / (float)pic_w,
                                           (float)FB_H / (float)pic_lines);
        else
            vita2d_draw_texture_part_scale(tex, canvas.ox, canvas.oy, 0, 0, (float)pic_w, (float)pic_lines, canvas.s,
                                           canvas.s * 384.0f / (float)pic_lines);
        pic = 1;
    }
    if (!mode || !pic || strip_on > 1) strip();
    kh1_vita_menu_draw(); /* the FPS counter, the mod menu (menu.c) */
    vita2d_end_drawing();
    vita2d_swap_buffers();
    drawn_at = status_frames;
}

/* the model's buffer (FRAME's FBP, FBW, PSM) into the texture as ABGR, then drawn */
static void present_buffer(u32 bp, u32 bw, u32 psm, u32 lines) {
    u32 w = bw * 64 < TEX_W ? bw * 64 : TEX_W, stride, x, y, *p;
    SceUInt64 t0;
    if (psm != KH1_PSMCT32 && psm != KH1_PSMCT24 && psm != KH1_PSMCT16 && psm != KH1_PSMCT16S) return;
    if (!bw || lines > TEX_H) return;
    t0 = sceKernelGetProcessTimeWide();
    vita2d_wait_rendering_done(); /* the GPU is done with the last frame's texture */
    p = vita2d_texture_get_datap(tex);
    stride = vita2d_texture_get_stride(tex) / 4;
    if (kh1_gsmem_read_rect(psm, bp, bw, 0, 0, w, lines, p, stride)) return;
    for (y = 0; y < lines; y++, p += stride) {
        if (psm == KH1_PSMCT16 || psm == KH1_PSMCT16S)
            for (x = 0; x < w; x++)
                p[x] = 0xFF000000u | (p[x] & 0x1F) << 3 | (p[x] >> 5 & 0x1F) << 11 | (p[x] >> 10 & 0x1F) << 19;
        else
            for (x = 0; x < w; x++) p[x] |= 0xFF000000u;
    }
    pic_w = w;
    pic_lines = lines;
    shown++;
    kh1_vita_pictures++;
    kh1_vita_shown = shown;
    draw();
    kh1_vita_us_present += (u32)(sceKernelGetProcessTimeWide() - t0);
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

/* session 136: the GPU's picture; the sends are still counted for the watchdog, and the frame copy marks
 * the display buffer whole (main.c latches the GPU's display target then: kh1_vita_frame_copied) */
static int copied;
static void count_send(u32 tadr) {
    kh1_vita_sends++;
    kh1_vita_last_send = tadr;
    if (tadr == frame_copy) copied = 1;
}

int kh1_vita_frame_copied(void) {
    int c = copied;
    copied = 0;
    return c;
}

void kh1_vita_present_gpu(void) {
    gpu = 1;
    kh1_dma_after_send = count_send;
    kh1_dma_after_send_reads = 0; /* session 141: tadr only, so the sends need not wait for the GS worker */
}

/* config.txt's wide= and strip= (main.c): mode 1 only with the GPU's picture (the GS model's buffers stay the
 * PS2's 512 wide, so the software picture takes 1 as 2); strip 1 keeps the status strip over a full-screen picture */
void kh1_vita_display_mode(int m, int strip_always) {
    mode = m;
    strip_on = strip_always ? 2 : 1;
}

/* session 136: each vblank after the GPU's frame (main.c) */
void kh1_vita_draw(void) { draw(); }

/* each vblank (main.c): the strip's counts, drawn with the last picture when no frame copy has
 * been shown for 30 vblanks */
void kh1_vita_status(unsigned long frames, unsigned reads) {
    status_frames = frames;
    status_reads = reads;
    if (tex && !gpu && frames - drawn_at >= 30) draw();
}

/* a whole-screen colour (the "no disc" screen) */
void kh1_vita_fill(u32 abgr) {
    vita2d_set_clear_color(abgr);
    vita2d_start_drawing();
    vita2d_clear_screen();
    vita2d_end_drawing();
    vita2d_swap_buffers();
    vita2d_set_clear_color(0xFF000000u);
}

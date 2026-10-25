/* KH1_HOST_SHOT (session 94, docs/vita-port-plan.md 5.1ah, renderer-spec 5.4 "Session 94"): a host
 * "present".  After each frame copy (brightfade.c's D_002A6890 send: the 3D target to the display) the
 * GS memory model's display buffer (the copy's FRAME), or with the target source the 3D target (the
 * copy's TEX0), is written as a W x H PAM through the canvas map (include/platform/canvas.h): the 4:3
 * canvas scaled to the screen's height and centred, point-sampled, black where the model has no pixel
 * (the pillarbox, and under KH1_HOST_WIDE the view's sides: the model's buffers are the PS2's 512
 * wide).  The display's 448 lines are the canvas's 384 (NTSC's taller pixels).
 *
 * The model holds what uploads, copies and the point-sampled sprites it can draw (host/null/gsmem.c)
 * wrote, and since session 95 the untextured sprites (the clears, the display clear, fade and
 * letterbox: kh1_gsmem_flat, turned on here, which leaves every trace counter as it was), and since
 * session 96 the textured sprites the exact model refuses, point-sampled (the frame copy itself: the
 * display shows what the 3D target holds), not the 3D, so on the fake disc a frame shows the clears' colours only; the
 * picture is for the real disc's run and for a renderer's bring-up to compare with.  Frames from the user's disc: never commit them.  Not part of the PS2 build. */
#include "common.h"
#include "gsregs.h"
#include "gsmem.h"
#include "dmawalk.h"
#include "platform/canvas.h"
#include "present.h"

void *fopen(const char *, const char *);
int fclose(void *);
int fprintf(void *, const char *, ...);
__SIZE_TYPE__ fwrite(const void *, __SIZE_TYPE__, __SIZE_TYPE__, void *);
int sprintf(char *, const char *, ...);
int printf(const char *, ...);
void *malloc(__SIZE_TYPE__);
unsigned long kh1_host_frame(void);

/* a buffer's pixel as RGB (R in bits 0-7): CT32 / CT24 as stored, CT16 / CT16S widened */
static u32 rgb_of(u32 psm, u32 v) {
    if (psm == KH1_PSMCT16 || psm == KH1_PSMCT16S)
        return (v & 0x1F) << 3 | (v >> 5 & 0x1F) << 11 | (v >> 10 & 0x1F) << 19;
    return v & 0xFFFFFF;
}

int kh1_present_rgb(u8 *rgb, s32 w, s32 h, u32 psm, u32 bp, u32 bw, u32 lines) {
    KH1Canvas c;
    s32 x, y;
    f32 cx, cy;
    if (psm != KH1_PSMCT32 && psm != KH1_PSMCT24 && psm != KH1_PSMCT16 && psm != KH1_PSMCT16S) return -1;
    if (!bw || !lines) return -1;
    kh1_canvas_fit(&c, (f32)w, (f32)h);
    for (y = 0; y < h; y++)
        for (x = 0; x < w; x++) {
            u8 *o = rgb + (y * w + x) * 3;
            u32 v = 0;
            /* the pixel's centre, back to the canvas */
            kh1_canvas_unmap(&c, (f32)x + 0.5f, (f32)y + 0.5f, &cx, &cy);
            if (cx >= 0.0f && cx < 512.0f && cx < (f32)(bw * 64) && cy >= 0.0f && cy < 384.0f)
                v = rgb_of(psm, kh1_gsmem_read_pixel(psm, bp, bw, (u32)cx, (u32)(cy * (f32)lines / 384.0f)));
            o[0] = v;
            o[1] = v >> 8;
            o[2] = v >> 16;
        }
    return 0;
}

static s32 shot_w, shot_h, shot_target;
static const char *shot_dir;
static u32 shot_send, shot_n;
static u8 *shot_rgb;

static void present_after(u32 tadr) {
    const KH1GsState *s = kh1_gs_state();
    const KH1GsReg *r = shot_target ? &s->ctx[0].tex0 : &s->ctx[0].frame;
    u32 bp, bw, psm;
    char path[512];
    void *f;
    if (tadr != shot_send) return;
    if (shot_target) { /* TEX0: TBP0, TBW, PSM */
        bp = r->lo & 0x3FFF;
        bw = r->lo >> 14 & 63;
        psm = r->lo >> 20 & 63;
    } else { /* FRAME: FBP (2048-word pages), FBW, PSM */
        bp = (r->lo & 0x1FF) * 32;
        bw = r->lo >> 16 & 63;
        psm = r->lo >> 24 & 63;
    }
    if (kh1_present_rgb(shot_rgb, shot_w, shot_h, psm, bp, bw, shot_target ? 384 : 448)) {
        printf("kh1-host: shot frame %lu: psm %02x bw %u not presentable\n", kh1_host_frame(), psm, bw);
        return;
    }
    sprintf(path, "%.400s/shot_%05u.pam", shot_dir, shot_n++);
    f = fopen(path, "wb");
    if (!f) {
        printf("kh1-host: shot frame %lu: %s: cannot write\n", kh1_host_frame(), path);
        return;
    }
    fprintf(f, "P7\nWIDTH %d\nHEIGHT %d\nDEPTH 3\nMAXVAL 255\nTUPLTYPE RGB\nENDHDR\n", shot_w, shot_h);
    fwrite(shot_rgb, 3, (__SIZE_TYPE__)shot_w * shot_h, f);
    fclose(f);
    printf("kh1-host: shot frame %lu: %s (%s bp %04x bw %u psm %02x; %u flat, %u textured sprites so far)\n",
           kh1_host_frame(), path, shot_target ? "target" : "display", bp, bw, psm, kh1_gsmem_stats()->flat_sprites,
           kh1_gsmem_stats()->tex_sprites);
}

int kh1_present_init(s32 w, s32 h, int target, const char *dir, const void *send) {
    if (w <= 0 || h <= 0 || w > 4096 || h > 4096) return -1;
    shot_rgb = malloc((__SIZE_TYPE__)w * h * 3);
    if (!shot_rgb) return -1;
    shot_w = w;
    shot_h = h;
    shot_target = target;
    shot_dir = dir;
    shot_send = (u32)(unsigned long)send;
    kh1_dma_after_send = present_after;
    kh1_gsmem_flat(1); /* session 95: the clears, fades and letterbox filled into the model */
    return 0;
}

/* The static full-screen packets a wide view stretches (include/platform/fullscreen.h,
 * docs/renderer-spec.md 5.4 "Session 93"), read with tools/vu/gs_packets.py -v: each is one REFE send
 * through func_00106b18.  Port data for every platform; the host's null GIF path applies it under
 * KH1_HOST_WIDE (host/null/dmawalk.c, kh1_dma_fullscreen).  Not part of the PS2 build. */
#include "common.h"
#include "platform/fullscreen.h"

extern u8 D_002A6500[], D_002A6890[], D_002A6070[], D_002A61E0[], D_002A5FD0[], D_002A4ED0[];
extern u8 D_002A4FC0[], D_002B6760[], D_002BC980[], D_002A6110[], D_002B66B0[];

const KH1FullScreen kh1_fullscreen[] = {
    /* brightfade.c: the clear, 16 black sprites of 32 px, x 1792 .. 2304 (each column a sprite) */
    { D_002A6500, KH1_FS_X, "clear" },
    /* brightfade.c: the frame copy, 16 strips of the target (u 0.5 .. 512.5) to the 512 x 448 display */
    { D_002A6890, KH1_FS_X | KH1_FS_U, "frame copy" },
    /* sceneeff.c func_00103170: the fade, one sprite 1792 .. 2304 */
    { D_002A6070, KH1_FS_X, "fade" },
    /* brightfade.c: the letterbox, two bars 1792 .. 2304 (y 0-34 and 350-384) */
    { D_002A61E0, KH1_FS_X, "letterbox" },
    /* sceneeff.c: the target copied into the Z area for the sway / lens grid, 16 strips from x 1790.5 */
    { D_002A5FD0, KH1_FS_X | KH1_FS_U, "copy into the Z area" },
    /* sceneeff.c func_00102da8: the spin's display-to-target copy, u 1 .. 513, its SCISSOR_1 the full
     * canvas (kh1_canvas_scissor's whole view) */
    { D_002A4ED0, KH1_FS_X | KH1_FS_U, "spin copy" },
    /* the spin's turned strip D_002A4F60 (sent as D_002A4FC0): u 0.5 .. 512.5 of the display; its XYZ
     * come from C, already wide (func_00102cc8's PLAT_VIEW_W), so u only */
    { D_002A4FC0, KH1_FS_U, "spin strip" },
    /* capture.c: the menu capture, the target (u 0 .. 512) to a buffer of its own at half size (x
     * 1792 .. 2048 = its pixels 0 .. 256): the buffer is the port's, the view's half wide, so x scales
     * from its left edge without the view's offset */
    { D_002B6760, KH1_FS_XS | KH1_FS_U, "menu capture" },
    /* capture.c func_0010a120 / func_0010a248 / func_0010a378 (session 98, seen in the fake-disc wide run
     * at 0 .. 512): the stored frame, loaded back into the Z area by func_00109f88 (512 x 384, the port's
     * target size), drawn over the target, u 0 .. 512 at x 1791.5 .. 2303.5, its colour fading */
    { D_002B66B0, KH1_FS_X | KH1_FS_U, "stored frame back" },
    /* dispenv.c func_0010ff60 (session 93): the display cleared to a grey level, one sprite 1792 .. 2304
     * x 1856 .. 2304 under SCISSOR_1 0 .. 511 x 0 .. 447 (the scissor rule's display case) */
    { D_002BC980, KH1_FS_X, "display clear" },
    /* sceneeff.c func_00103c48 (session 94): the lens grid's CLAMP_1 REGION_CLAMP U 0 .. 510 over the
     * copy into the Z area, which is the view's width now; its mesh stays the centre square and its ST
     * take the view's margin in C (PLAT_VIEW_SIDE) */
    { D_002A6110, KH1_FS_CLAMP, "lens grid" },
};
const s32 kh1_nfullscreen = sizeof kh1_fullscreen / sizeof kh1_fullscreen[0];

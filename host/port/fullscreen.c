/* The static full-screen packets a wide view stretches (include/platform/fullscreen.h,
 * docs/renderer-spec.md 5.4 "Session 93"), read with tools/vu/gs_packets.py -v: each is one send
 * through func_00106b18 (session 100: or frame.c's path-2 func_001e05a8), checked by tools/host/fscheck.py.  Port data for every platform; the host's null GIF path applies it under
 * KH1_HOST_WIDE (host/null/dmawalk.c, kh1_dma_fullscreen).  Not part of the PS2 build. */
#include "common.h"
#include "platform/fullscreen.h"

extern u8 D_002A6500[], D_002A6890[], D_002A6070[], D_002A61E0[], D_002A5FD0[], D_002A4ED0[];
extern u8 D_002A4FC0[], D_002B6760[], D_002BC980[], D_002A6110[], D_002B66B0[];
extern u8 D_002A4DD0[], D_002A4B60[], D_002A5A90[], D_002A5620[], D_002A5AC0[], D_002A6A40[], D_002A6AA0[], D_002B65E0[];
extern u8 D_003DAE30[], D_003DAF60[], D_003DB050[];

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
    /* capture.c func_00109e20 (session 99, tools/host/fscheck.py): the stored frame cross-faded, the target
     * (u 0 .. 512) and the frame func_00109cd0 loaded into the Z area (u 0 .. 512), two sprites 1792 .. 2304 */
    { D_002B65E0, KH1_FS_X | KH1_FS_U, "stored frame cross-fade" },
    /* sceneeff.c func_00102a48 (session 99): the menu blur with an empty capture, one black sprite 1792 ..
     * 2304 (TEX0 the capture, u 0 .. 1: one texel modulated to black) */
    { D_002A4DD0, KH1_FS_X, "menu blur, no capture" },
    /* sceneeff.c func_00102a48 (session 99): the menu blur's nine copies of the half-size capture at 0x3600,
     * u 0 .. 256; their XYZ come from C (PLAT_VIEW_GX0 / GX1, the first copy's too off the PS2), so u only:
     * the capture holds the view at half size (D_002B6760's KH1_FS_XS), and the stretch is proportional */
    { D_002A4B60, KH1_FS_U | KH1_FS_UOWN, "menu blur" },
    /* sceneeff.nostrict.c func_00103058 (session 99): the depth blur's capture, the target (u 0 .. 512) to
     * 0x3600 at half size (D_002A5380, x 1792 .. 2048), a buffer of its own like the menu capture; sent by
     * both modes (mode 1 after its alpha mask D_002A5250 / D_002A52B0); every XYZ written from C off the
     * PS2 (the capture's right edge 0x7000 + PLAT_VIEW_W16 / 2), so u only */
    { D_002A5A90, KH1_FS_U, "depth blur capture" },
    { D_002A5620, KH1_FS_U, "depth blur mask and capture" },
    /* sceneeff.nostrict.c func_00103058 (session 99): the depth blur's nine copies of 0x3600 (u 0 .. 255) in
     * the 16 columns; XYZ from C (D_002A5430), so u only */
    { D_002A5AC0, KH1_FS_U | KH1_FS_UOWN, "depth blur" },
    /* brightfade.c func_00106460 (session 99): the shaped wipe (renderer-spec 3.2's destination-alpha mask), the target's alpha set to 0x80 (FBMSK 0xFFFFFF)
     * and the black drawn where the alpha says, each one sprite 1792 .. 2304; the centre sprite between
     * them (D_002A6B70) is placed from C */
    { D_002A6A40, KH1_FS_X, "wipe mask alpha" },
    { D_002A6AA0, KH1_FS_X, "wipe mask black" },
    /* frame.c / screen.c (session 100, fscheck's func_001e05a8 sends): the stored frame D_00F20000, loaded
     * into the Z area (0x0E00 / 0x1400, like D_002B66B0), drawn back over the target, u 0 .. 512: as it is
     * (func_001e0898), cross-faded with the target (func_001e08d8 and screen.c's fades: the second sprite's
     * corners D_003DAE40[33] / [35] come from C, zoomed by D_003DACB0 / B4 and moved by D_003DACB8 / BC in
     * canvas units, which the row's stretch carries to the view like the static first sprite) and
     * tinted (func_001e15a0) */
    { D_003DAE30, KH1_FS_X | KH1_FS_U, "stored frame" },
    { D_003DAF60, KH1_FS_X | KH1_FS_U, "stored frame zoom / cross-fade" },
    { D_003DB050, KH1_FS_X | KH1_FS_U, "stored frame tint" },
    /* dispenv.c func_0010ff60 (session 93): the display cleared to a grey level, one sprite 1792 .. 2304
     * x 1856 .. 2304 under SCISSOR_1 0 .. 511 x 0 .. 447 (the scissor rule's display case) */
    { D_002BC980, KH1_FS_X, "display clear" },
    /* sceneeff.c func_00103c48 (session 94): the lens grid's CLAMP_1 REGION_CLAMP U 0 .. 510 over the
     * copy into the Z area, which is the view's width now; its mesh stays the centre square and its ST
     * take the view's margin in C (PLAT_VIEW_SIDE) */
    { D_002A6110, KH1_FS_CLAMP, "lens grid" },
};
const s32 kh1_nfullscreen = sizeof kh1_fullscreen / sizeof kh1_fullscreen[0];

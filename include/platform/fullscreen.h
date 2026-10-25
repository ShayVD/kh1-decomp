#ifndef PLATFORM_FULLSCREEN_H
#define PLATFORM_FULLSCREEN_H

/* The static full-screen packets (docs/renderer-spec.md 5.4 "Session 92" / "Session 93"): port data,
 * not game code, beside the HUD's anchor table (include/platform/hudanchor.h) and keyed the same way,
 * by the send's start (what func_00106b18 is given).  These packets hold the 4:3 canvas's constants as
 * words in the ELF's data, so under a wide view a port stretches what they draw to the whole view:
 * KH1_FS_X maps each XYZ X from canvas 0 .. 512 to the view's x0 .. x1, KH1_FS_U maps each UV u (a
 * texel of a copy of the target or the display) the same way, from the view's left edge
 * (include/platform/canvas.h).  The full-screen passes built in C already use include/platform/view.h
 * and are not listed.  Not part of the PS2 build. */
#ifndef KH1_PS2
#define KH1_FS_X 1  /* XYZ X: canvas 0 .. 512 to the view's x0 .. x1 (a buffer laid out like the target) */
#define KH1_FS_U 2  /* UV u: 0 .. 512 texels to 0 .. the view's width, from its left edge */
#define KH1_FS_XS 4 /* XYZ X scaled from 0x7000 only: a buffer of its own (the capture) starts at 0 */
#define KH1_FS_CLAMP 8 /* CLAMP REGION_CLAMP's MAXU grows by the view's added width (session 94: the lens
                        * grid's copy of the target is the view's width) */

typedef struct {
    const void *send; /* the packet's DMA tag, the send's start */
    u32 what;         /* KH1_FS_X or KH1_FS_XS, | KH1_FS_U; or KH1_FS_CLAMP */
    const char *name;
} KH1FullScreen;

extern const KH1FullScreen kh1_fullscreen[];
extern const s32 kh1_nfullscreen;
#endif

#endif

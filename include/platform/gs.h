/* Platform wrapper: the GS (libgraph). See docs/portability.md.
 *
 * What the game asks of libgraph: wait for the GIF paths to drain
 * (PlatGsSyncPath(0, 0) before and after every DMA send), upload an image to
 * GS memory (PlatGsSetDefLoadImage builds the packet, PlatGsExecLoadImage
 * sends it with the pixels), read one back (PlatGsExecStoreImage, the frame
 * capture of src/screen/capture.c and src/menu/menubg.c), and set the
 * display / drawing environment (src/screen/dispenv.c, display.c: PlatGsResetGraph, PlatGsResetPath,
 * PlatGsPutDispEnv; src/memcard/mcqueue.c waits on PlatGsSyncV).  On the
 * matching PS2 build each wrapper is a macro for the libgraph call; the casts
 * take the game's own packet structs and compile to nothing.  The Vita port
 * implements the same names on its renderer: an image load becomes a texture
 * upload into its model of GS memory (docs/renderer-spec.md).
 *
 * The game also writes a few GS privileged registers itself (session 57):
 * src/game/framectl.c and src/screen/fade.c show read circuit 1 alone
 * (PlatGsPutPmode(0xff03), PlatGsPutDispfb1(0x11b0), PlatGsPutDisplay1(...))
 * and framectl.c's func_0010f658 blanks to circuit 2 (PlatGsPutPmode(0x22));
 * src/screen/dispenv.c clears EXTWRITE after the reset; src/screen/display.c
 * reads the field from CSR (PlatGsGetCsr() & PLAT_GS_CSR_FIELD).  On the PS2
 * these are the 64-bit stores / load at 0x12000000 / 0x12001000; the Vita
 * port keeps the values for its display pass (docs/renderer-spec.md). */
#ifndef KH1_PLATFORM_GS_H
#define KH1_PLATFORM_GS_H

#include "common.h"

#ifdef KH1_PS2
#include "sce/libgraph.h"
#define PlatGsResetGraph(mode, inter, omode, ffmd) sceGsResetGraph((mode), (inter), (omode), (ffmd))
#define PlatGsResetPath() sceGsResetPath()
#define PlatGsSyncV(mode) sceGsSyncV(mode)
#define PlatGsSyncPath(mode, timeout) sceGsSyncPath((mode), (timeout))
#define PlatGsSetDefLoadImage(lp, dbp, dbw, psm, x, y, w, h) \
    sceGsSetDefLoadImage((sceGsLoadImage *)(lp), (dbp), (dbw), (psm), (x), (y), (w), (h))
#define PlatGsSetDefStoreImage(sp, sbp, sbw, psm, x, y, w, h) \
    sceGsSetDefStoreImage((sceGsStoreImage *)(sp), (sbp), (sbw), (psm), (x), (y), (w), (h))
#define PlatGsExecLoadImage(lp, src) sceGsExecLoadImage((sceGsLoadImage *)(lp), (void *)(src))
#define PlatGsExecStoreImage(sp, dst) sceGsExecStoreImage((sceGsStoreImage *)(sp), (void *)(dst))
#define PlatGsDefDispEnv(disp, psm, w, h, dx, dy) sceGsDefDispEnv((sceGsDispEnv *)(disp), (psm), (w), (h), (dx), (dy))
#define PlatGsPutDispEnv(disp) sceGsPutDispEnv((sceGsDispEnv *)(disp))
#define PlatGsPutDrawEnv(giftag) sceGsPutDrawEnv((void *)(giftag))
#define PlatGsPutPmode(v) (*(volatile u64 *)0x12000000 = (v))
#define PlatGsPutDispfb1(v) (*(volatile u64 *)0x12000070 = (v))
#define PlatGsPutDisplay1(v) (*(volatile u64 *)0x12000080 = (v))
#define PlatGsPutExtwrite(v) (*(volatile u64 *)0x120000d0 = (v))
#define PlatGsGetCsr() (*(volatile u64 *)0x12001000)
#else
void PlatGsResetGraph(short mode, short inter, short omode, short ffmd);
void PlatGsResetPath(void);
int PlatGsSyncV(int mode);
int PlatGsSyncPath(int mode, unsigned short timeout);
int PlatGsSetDefLoadImage(void *lp, short dbp, short dbw, short psm, short x, short y, short w, short h);
int PlatGsSetDefStoreImage(void *sp, short sbp, short sbw, short psm, short x, short y, short w, short h);
int PlatGsExecLoadImage(void *lp, void *src);
int PlatGsExecStoreImage(void *sp, void *dst);
void PlatGsDefDispEnv(void *disp, short psm, short w, short h, short dx, short dy);
void PlatGsPutDispEnv(void *disp);
void PlatGsPutDrawEnv(void *giftag);
void PlatGsPutPmode(u64 v);
void PlatGsPutDispfb1(u64 v);
void PlatGsPutDisplay1(u64 v);
void PlatGsPutExtwrite(u64 v);
u64 PlatGsGetCsr(void);
#endif
#define PLAT_GS_CSR_FIELD 0x2000 /* CSR.FIELD: the field being displayed (interlace) */

#endif /* KH1_PLATFORM_GS_H */

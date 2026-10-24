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
 * upload into its model of GS memory (docs/renderer-spec.md). */
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
#endif

#endif /* KH1_PLATFORM_GS_H */

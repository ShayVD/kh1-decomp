/* Platform wrapper: the GS (libgraph). See docs/portability.md.
 *
 * What the game asks of libgraph: wait for the GIF paths to drain
 * (PlatGsSyncPath(0, 0) before and after every DMA send), upload an image to
 * GS memory (PlatGsSetDefLoadImage builds the packet, PlatGsExecLoadImage
 * sends it with the pixels), read one back (PlatGsExecStoreImage, the frame
 * capture of src/screen/capture.c and src/menu/menubg.c), and set the
 * display / drawing environment (src/screen/dispenv.c, display.c).  On the
 * matching PS2 build each wrapper is a macro for the libgraph call; the casts
 * take the game's own packet structs and compile to nothing.  The Vita port
 * implements the same names on its renderer: an image load becomes a texture
 * upload into its model of GS memory (docs/renderer-spec.md). */
#ifndef KH1_PLATFORM_GS_H
#define KH1_PLATFORM_GS_H

#include "common.h"

#ifdef KH1_PS2
#include "sce/libgraph.h"
#define PlatGsSyncPath(mode, timeout) sceGsSyncPath((mode), (timeout))
#define PlatGsSetDefLoadImage(lp, dbp, dbw, psm, x, y, w, h) \
    sceGsSetDefLoadImage((sceGsLoadImage *)(lp), (dbp), (dbw), (psm), (x), (y), (w), (h))
#define PlatGsExecLoadImage(lp, src) sceGsExecLoadImage((sceGsLoadImage *)(lp), (void *)(src))
#define PlatGsExecStoreImage(sp, dst) sceGsExecStoreImage((sceGsStoreImage *)(sp), (void *)(dst))
#define PlatGsDefDispEnv(disp, psm, w, h, dx, dy) sceGsDefDispEnv((sceGsDispEnv *)(disp), (psm), (w), (h), (dx), (dy))
#define PlatGsPutDrawEnv(giftag) sceGsPutDrawEnv((void *)(giftag))
#else
int PlatGsSyncPath(int mode, unsigned short timeout);
int PlatGsSetDefLoadImage(void *lp, short dbp, short dbw, short psm, short x, short y, short w, short h);
int PlatGsExecLoadImage(void *lp, void *src);
int PlatGsExecStoreImage(void *sp, void *dst);
void PlatGsDefDispEnv(void *disp, short psm, short w, short h, short dx, short dy);
void PlatGsPutDrawEnv(void *giftag);
#endif

#endif /* KH1_PLATFORM_GS_H */

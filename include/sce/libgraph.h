/* Declarations of SCE libgraph functions as linked into the game ELF.
 * Hand-written from the public function signatures; no SDK headers are
 * copied into this repository. Addresses are in functions.tsv.  The game
 * keeps the packets in its own structs, so the packet types stay opaque
 * here (include/platform/gs.h casts to them). */
#ifndef KH1_SCE_LIBGRAPH_H
#define KH1_SCE_LIBGRAPH_H

typedef struct sceGsLoadImage sceGsLoadImage;   /* 0x60 bytes: DMA / GIF tags, BITBLTBUF ... TRXDIR */
typedef struct sceGsStoreImage sceGsStoreImage;
typedef struct sceGsDispEnv sceGsDispEnv;       /* PMODE, SMODE2, DISPFB, DISPLAY, BGCOLOR */

/* void: declared returning int, src/screen/dispenv.c func_0010ffe0 allocates
 * another register after the call (the game was built with a void one). */
void sceGsResetGraph(short mode, short inter, short omode, short ffmd);
void sceGsResetPath(void);
int sceGsSyncV(int mode);
int sceGsSyncPath(int mode, unsigned short timeout);
int sceGsSetDefLoadImage(sceGsLoadImage *lp, short dbp, short dbw, short dpsm, short x, short y, short w, short h);
int sceGsSetDefStoreImage(sceGsStoreImage *sp, short sbp, short sbw, short spsm, short x, short y, short w, short h);
int sceGsExecLoadImage(sceGsLoadImage *lp, void *src);
int sceGsExecStoreImage(sceGsStoreImage *sp, void *dst);
void sceGsDefDispEnv(sceGsDispEnv *disp, short psm, short w, short h, short dx, short dy);
void sceGsPutDispEnv(sceGsDispEnv *disp);
void sceGsPutDrawEnv(void *giftag);

#endif /* KH1_SCE_LIBGRAPH_H */

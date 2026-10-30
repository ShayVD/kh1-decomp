/* The null platform's DMA chain walk (KH1_HOST_TRACE=2, host/null/dmawalk.c). */
#ifndef KH1_HOST_DMAWALK_H
#define KH1_HOST_DMAWALK_H

#include "platform/hudanchor.h"
#include "platform/fullscreen.h"

/* where(addr, n): a name for the memory n bytes at addr lie in ("image", "spr", ...), 0 when
 * the host does not own it */
typedef const char *(*KH1DmaWhere)(u32 addr, u32 n);

/* Walks the chain a send on channel ch starts at tadr and prints one line (every tag on a
 * problem or with KH1_HOST_TRACE=3).  Returns 0, or the problem bits below. */
int kh1_dma_walk(int ch, u32 chcr, u32 tadr, KH1DmaWhere where);

/* The distinct GS state values (register address, 64-bit value) the last walk's GIF or PATH2
 * stream wrote, in the order first written (vertex registers left out; at most 512 kept).
 * Fills up to max of each array and returns the count.  KH1_HOST_TRACE=4 prints them. */
int kh1_dma_gs_values(u32 *reg, u32 *lo, u32 *hi, int max);

#define KH1_DMA_TAG_OUTSIDE   0x01
#define KH1_DMA_DATA_OUTSIDE  0x02
#define KH1_DMA_CALL_DEEP     0x04
#define KH1_DMA_NO_END        0x08
#define KH1_DMA_GIF_SHORT     0x10 /* the chain ends inside a GIF packet */
#define KH1_DMA_VIF_SHORT     0x20 /* the chain ends inside a VIF code's data */
#define KH1_DMA_VIF_BAD       0x40 /* a word that is no VIF code */
#define KH1_DMA_PATH2_SHORT   0x80 /* the DIRECT data ends inside a GIF packet (PATH2) */

/* Session 92 (KH1_HOST_WIDE, docs/renderer-spec.md 5.3.1): moves the HUD's anchored parts.  A send
 * whose start is an entry's env sets that entry's x shift (side * margin, 1/16 pixels) for its own
 * vertices and for the sends from the staging buffer [via, via + via_n) after it; any other send
 * sets none.  n = 0 turns it off (the default).  The table is the port's (host/port/hudanchor.c). */
void kh1_dma_hud_anchors(const KH1HudAnchor *tab, int n, u32 via, u32 via_n, s32 margin);

/* Session 93 (KH1_HOST_WIDE, docs/renderer-spec.md 5.4 "Session 93"): stretches the static full-screen
 * packets.  A send whose start is an entry's send stretches its own vertices (and u, with KH1_FS_U) to
 * the view x0 .. x0 + w (canvas sixteenths, kh1_gs_xstretch); any other send none.  n = 0 turns it off
 * (the default).  The table is the port's (host/port/fullscreen.c). */
void kh1_dma_fullscreen(const KH1FullScreen *tab, int n, s32 x0, s32 w);

/* a GIF packet of qwc qwords sent in normal mode (no chain), read and printed like a walk's */
void kh1_dma_gif_direct(const u32 *q, u32 qwc);

extern int kh1_host_trace;
extern const char *kh1_host_texdump;

/* Session 94: called with the send's start after each walk or direct send, once its GS writes are in
 * the register file and the memory model (KH1_HOST_SHOT, host/null/present.c); 0 = none */
extern void (*kh1_dma_after_send)(u32 tadr);
/* Session 141: 1 (the default) when kh1_dma_after_send reads the GS model, so with the GS side on its worker
 * (host/null/gsqueue.h) each send waits for it first; 0 for a hook that only reads tadr */
extern int kh1_dma_after_send_reads;
/* Session 135: 1 walks the chains (the register file, the memory model, the present) without the
 * send's "dma ch" line, the ~7 lines a frame the Vita wrote through an unbuffered log; 0 (the host's
 * default) prints them.  Levels 3-5's extra lines still print. */
extern int kh1_dma_quiet;
/* Session 143: the sends with a problem (bad chain, data outside, a word that is no VIF code ...), counted.  A quiet
 * walk (the Vita's) prints the tag list and problem lines of the first KH1_DMA_BAD_SHOWN only: the Vita's Dive sent
 * ~8 a second, each ~20 lines through the unbuffered log, from inside the walk's time */
#define KH1_DMA_BAD_SHOWN 16
extern u32 kh1_dma_bad_sends;
/* Session 137v: 1 runs each VIF1 stream's codes on VIF1 / VU1 (host/port/vu1.c, include/platform/vu1.h) and reads
 * their XGKICK output as GIF packets, so renderer A / B's meshes reach the register file, the GS model and the GPU
 * recorder; 0 (the default) only counts the program starts (kh1_gs_path1).  KH1_HOST_VU1=1, the Vita's vu1=1. */
extern int kh1_dma_vu1;
/* the native renderer (include/platform/natdraw.h): 1 hands P18's runs to the GPU's transform (host/port/vu1_draw.h) */
extern int kh1_dma_native;

#endif

/* Platform wrapper: DMA (libdma). See docs/portability.md.
 *
 * The game only takes a channel (2, the GIF, almost everywhere; 1, VIF1, in
 * src/gfx/shadow.c and src/model/mdldraw*.c) and sends a DMA chain to it:
 * the tag's address, bit 31 set for the scratchpad (0x70000000).  On the
 * matching PS2 build each wrapper is a macro for the libdma call; the casts
 * take whatever the matched code holds the channel and the chain in (an int,
 * a struct pointer), and compile to nothing.  The Vita port implements the
 * same names: PlatDmaSend on PlatDmaChan(2) walks the chain into the
 * renderer's GIF parser (docs/renderer-spec.md). */
#ifndef KH1_PLATFORM_DMA_H
#define KH1_PLATFORM_DMA_H

#include "common.h"

#define PLAT_DMA_VIF1 1
#define PLAT_DMA_GIF 2

#ifdef KH1_PS2
#include "sce/libdma.h"
/* A macro, not a typedef: gcc 2.96 treats a typedef of the struct as another
 * type and converts between them, and `D = PlatDmaGetChan(2)` then keeps &D in
 * a saved register over the call (session 56). */
#define PlatDmaChan sceDmaChan
#define PlatDmaGetChan(id) sceDmaGetChan(id)
/* For matched code that holds the channel as its CHCR bit fields
 * (src/model/mdldraw*.c): the call is typed instead of its result converted,
 * for the same reason. */
#define PlatDmaGetChanAs(T, id) (((T (*)(int))sceDmaGetChan)(id))
#define PlatDmaSend(ch, tag) sceDmaSend((sceDmaChan *)(ch), (void *)(tag))
#else
typedef struct PlatDmaChan PlatDmaChan;
PlatDmaChan *PlatDmaGetChan(int id);
#define PlatDmaGetChanAs(T, id) ((T)PlatDmaGetChan(id))
void PlatDmaSend(PlatDmaChan *ch, void *tag);
#endif

#endif /* KH1_PLATFORM_DMA_H */

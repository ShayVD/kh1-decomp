/* Platform wrapper: DMA (libdma). See docs/portability.md.
 *
 * The game only takes a channel (2, the GIF, almost everywhere; 1, VIF1, in
 * src/gfx/shadow.c and src/model/mdldraw*.c) and sends a DMA chain to it:
 * the tag's address, bit 31 set for the scratchpad (0x70000000).  On the
 * matching PS2 build each wrapper is a macro for the libdma call; the casts
 * take whatever the matched code holds the channel and the chain in (an int,
 * a struct pointer), and compile to nothing.  The Vita port implements the
 * same names: PlatDmaSend on PlatDmaChan(2) walks the chain into the
 * renderer's GIF parser (docs/renderer-spec.md).
 *
 * A few places drive the DMA controller and the VIFs by their registers
 * (session 58): src/gfx/sceneeff.c, dmapool.c and mdlpkt.c start a VIF1
 * chain by hand (PlatDmaPutVif1Qwc(0), PlatDmaPutVif1Tadr(tag & 0x0fffffff),
 * PlatDmaPutStat(2) to clear channel 1's interrupt status, a cache flush,
 * then PlatDmaPutVif1Chcr(0x145 or 0x105): STR, chain mode, DIR from memory,
 * 0x40 TTE), and src/model/mdlgs.nostrict.c clears channels 1 and 2's status
 * (PlatDmaPutStat(6)), masks the VIF0 / VIF1 error interrupts
 * (PlatVifPutErr(0 / 1, 6)) and waits for VIF1 to idle with an empty FIFO
 * (PlatVif1GetStat() & PLAT_VIF1_STAT_BUSY).  On the PS2 these are the 32-bit
 * stores / load at 0x1000xxxx; the Vita port treats a Chcr write with STR as
 * PlatDmaSend of the chain at the last Tadr on channel 1, and the status
 * reads as idle. */
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
#define PlatDmaPutStat(v) (*(volatile u32 *)0x1000e010 = (v))
#define PlatDmaPutVif1Chcr(v) (*(volatile u32 *)0x10009000 = (v))
#define PlatDmaPutVif1Qwc(v) (*(volatile u32 *)0x10009020 = (v))
#define PlatDmaPutVif1Tadr(v) (*(volatile u32 *)0x10009030 = (v))
#define PlatVifPutErr(n, v) (*(volatile u32 *)(0x10003820 + (n) * 0x400) = (v))
#define PlatVif1GetStat() (*(volatile u32 *)0x10003c00)
#else
typedef struct PlatDmaChan PlatDmaChan;
PlatDmaChan *PlatDmaGetChan(int id);
#define PlatDmaGetChanAs(T, id) ((T)PlatDmaGetChan(id))
void PlatDmaSend(PlatDmaChan *ch, void *tag);
void PlatDmaPutStat(u32 v);
void PlatDmaPutVif1Chcr(u32 v);
void PlatDmaPutVif1Qwc(u32 v);
void PlatDmaPutVif1Tadr(u32 v);
void PlatVifPutErr(int n, u32 v);
u32 PlatVif1GetStat(void);
#endif

/* The scratchpad (session 59): 16 KiB of fast EE memory at 0x70000000 that
 * src/util/heap.c runs a frame stack over (D_004F6EB8, from PLAT_SPR_BASE to
 * PLAT_SPR_END) and that func_00237018 (src/gfx/gspkt.nostrict_nofill.c)
 * builds packets in: a DMA tag address with bit 31 set (PLAT_DMA_SPR) reads
 * from the scratchpad, and an address below PLAT_SPR_BASE is main memory.  The
 * Vita port makes the scratchpad a plain 16 KiB buffer and PLAT_DMA_SPR 0 (a
 * Vita address can have bit 31 set; the chain walker takes plain pointers). */
#ifdef KH1_PS2
#define PLAT_SPR_BASE 0x70000000
#define PLAT_DMA_SPR 0x80000000
#else
extern u8 PlatSpr[0x4000];
#define PLAT_SPR_BASE ((u32)PlatSpr)
#define PLAT_DMA_SPR 0
#endif
#define PLAT_SPR_END (PLAT_SPR_BASE + 0x4000)

/* VIF1_STAT: FQC (the FIFO's quadword count, bits 24-28) and VPS (bits 0-1,
 * 0 = idle). */
#define PLAT_VIF1_STAT_BUSY 0x1f000003

#endif /* KH1_PLATFORM_DMA_H */

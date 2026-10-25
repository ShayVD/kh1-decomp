/* The null platform's DMA chain walk (KH1_HOST_TRACE=2, host/null/dmawalk.c). */
#ifndef KH1_HOST_DMAWALK_H
#define KH1_HOST_DMAWALK_H

/* where(addr, n): a name for the memory n bytes at addr lie in ("image", "spr", ...), 0 when
 * the host does not own it */
typedef const char *(*KH1DmaWhere)(u32 addr, u32 n);

/* Walks the chain a send on channel ch starts at tadr and prints one line (every tag on a
 * problem or with KH1_HOST_TRACE=3).  Returns 0, or the problem bits below. */
int kh1_dma_walk(int ch, u32 chcr, u32 tadr, KH1DmaWhere where);

#define KH1_DMA_TAG_OUTSIDE   0x01
#define KH1_DMA_DATA_OUTSIDE  0x02
#define KH1_DMA_CALL_DEEP     0x04
#define KH1_DMA_NO_END        0x08
#define KH1_DMA_GIF_SHORT     0x10 /* the chain ends inside a GIF packet */
#define KH1_DMA_VIF_SHORT     0x20 /* the chain ends inside a VIF code's data */
#define KH1_DMA_VIF_BAD       0x40 /* a word that is no VIF code */
#define KH1_DMA_PATH2_SHORT   0x80 /* the DIRECT data ends inside a GIF packet (PATH2) */

extern int kh1_host_trace;

#endif

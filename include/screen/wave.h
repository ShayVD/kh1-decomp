/* The wave transition's GS packet D_00631620 (src/screen/wave*.c;
 * docs/modules.md "Session 35"): a DMA tag, a GIF tag with its register
 * settings, 100 strips of four qwords (two vertices: XYZ and UV / colour)
 * and an end tag.  0x1960 bytes. */
#ifndef KH1_SCREEN_WAVE_H
#define KH1_SCREEN_WAVE_H

#include "common.h"

typedef int WaveU128 __attribute__((mode(TI)));
typedef struct { s32 a, b, c, d; } WaveQ;
typedef union { WaveU128 q; u32 w; } WaveTag;
typedef struct { WaveTag dma; u64 gif[8]; WaveQ v[400]; WaveTag end; } WavePkt;

s32 func_001e9418(void);

#endif /* KH1_SCREEN_WAVE_H */

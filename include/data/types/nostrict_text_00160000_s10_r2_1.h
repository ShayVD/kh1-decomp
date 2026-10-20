/* Types moved from src/hand/nostrict/text_00160000_s10_r2_1.c (phase 4, tools/shift/type_move.py). */
#ifndef KH1_DATA_TYPES_NOSTRICT_TEXT_00160000_S10_R2_1_H
#define KH1_DATA_TYPES_NOSTRICT_TEXT_00160000_S10_R2_1_H

#include "common.h"

typedef struct { f32 x, y, z, w; } V4EA;
typedef struct { u8 pad0[0x38]; u64 w38; u8 pad40[0x24]; f32 f64; u8 pad68[0x28]; void *p90; } WkEA;
typedef struct { u32 flags; u8 pad4[0xC]; V4EA pos; u8 pad20[0x1C]; f32 f3C; u8 pad40[0x104]; WkEA *p144; } ChrEA;
typedef struct { u8 pad0[0x10]; V4EA pos; u8 pad20[0x350]; u64 f370; } EntEA;
typedef struct { EntEA *tgt; s32 part; } LockEA;
typedef struct { u8 pad0[8]; s32 *p8; s32 (*fC)(ChrEA *, WkEA *); s32 *p10; s32 (*f14)(ChrEA *, WkEA *); } TalkEA;

#endif /* KH1_DATA_TYPES_NOSTRICT_TEXT_00160000_S10_R2_1_H */

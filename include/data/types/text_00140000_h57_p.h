/* More types moved from src/hand/text_00140000_h57.c (phase 4, session 24, tools/shift/type_pieces.py). */
#ifndef KH1_DATA_TYPES_TEXT_00140000_H57_P_H
#define KH1_DATA_TYPES_TEXT_00140000_H57_P_H

#include "common.h"
#include "data/types/text_00140000_h57.h"

typedef struct { u8 id; u8 b1; u8 b2; u8 b3; u8 b4; } BoxHd57_f1b8;
typedef union { u64 flags; BoxHd57_f1b8 c; } BoxU57_f1b8;
typedef struct { BoxU57_f1b8 u; u8 pad8[8]; f32 lo[4]; f32 hi[4]; } Box57_f1b8;
typedef struct { u8 pad0[3]; u8 x3; u8 n; u8 x5; u8 pad6[0xa]; Box57_f1b8 box[1]; } BoxSet57_f1b8;

#endif /* KH1_DATA_TYPES_TEXT_00140000_H57_P_H */

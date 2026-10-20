/* Types moved from src/hand/nostrict/text_00140000_h33.c (phase 4, tools/shift/type_move.py). */
#ifndef KH1_DATA_TYPES_NOSTRICT_TEXT_00140000_H33_H
#define KH1_DATA_TYPES_NOSTRICT_TEXT_00140000_H33_H

#include "common.h"

typedef struct Snd { u8 pad[8]; struct Snd *next; u8 padc[0xA]; u8 st; u8 pad17; f32 f18; } Snd;
typedef struct { s32 n0; s32 n4; s32 n8; u8 padc[4]; u8 data[1]; } LdHdr;
typedef struct { s32 id; LdHdr *h; } LdEnt;
typedef struct { u64 used:1; u64 b1:1; u64 b2:1; u64 rest:61; } EntF;
typedef struct { union { u64 d; EntF f; struct { u32 lo; s32 id; } w; } u; s16 n; u8 pad[0x16]; } Ent32;

#endif /* KH1_DATA_TYPES_NOSTRICT_TEXT_00140000_H33_H */

/* Types moved from src/hand/text_00140000_h8.c (phase 4, tools/shift/type_move.py). */
#ifndef KH1_DATA_TYPES_TEXT_00140000_H8_H
#define KH1_DATA_TYPES_TEXT_00140000_H8_H

#include "common.h"

/* A 0x20-byte light / projection record (D_0035C710[256], session 31: h8,
 * b03 B3PjE, h40 PppLight, h56 Spr).  v[3] is h40's dist. */
typedef union {
    u64 w;
    u8 id;
    struct { u64 lo:8; u64 f8:1; u64 f9:1; u64 f10:1; u64 rest:53; } b;
} Fl_35c710;
typedef struct { f32 v[4]; f32 x10; f32 x14; Fl_35c710 u; } W8Ent35;

#endif /* KH1_DATA_TYPES_TEXT_00140000_H8_H */

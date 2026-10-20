/* Types moved from src/hand/nostrict/text_00150000_h35.c (phase 4, tools/shift/type_move.py). */
#ifndef KH1_DATA_TYPES_NOSTRICT_TEXT_00150000_H35_H
#define KH1_DATA_TYPES_NOSTRICT_TEXT_00150000_H35_H

#include "common.h"

typedef union { s32 w; struct { s8 id; u8 n; } b; } E550400W;
typedef struct { E550400W h; char name[0x40]; s32 w44; } E550400;
typedef struct { u8 pad[0x74]; s32 w74; } S6C_1576a8;
typedef struct { u8 pad[0x6C]; S6C_1576a8 *p6C; } Act1576a8;
typedef struct { s8 b0, b1, b2, b3; Act1576a8 *w4; s32 w8; s32 wC; s32 w10; } E551670;

#endif /* KH1_DATA_TYPES_NOSTRICT_TEXT_00150000_H35_H */

/* Types moved from src/hand/text_00100000_h28.c (phase 4, tools/shift/type_move.py). */
#ifndef KH1_DATA_TYPES_TEXT_00100000_H28_H
#define KH1_DATA_TYPES_TEXT_00100000_H28_H

#include "common.h"

typedef struct { u8 x[0x60]; } E60;
typedef struct { u8 x[0x90]; } E90;
typedef struct { u8 x[32]; } E32;
typedef struct { E60 e[2]; u8 pad[0x10]; } ED0;

#endif /* KH1_DATA_TYPES_TEXT_00100000_H28_H */

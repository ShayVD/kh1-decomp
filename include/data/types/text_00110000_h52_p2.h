/* More types moved from src/hand/text_00110000_h52.c (phase 4, session 24, tools/shift/type_pieces.py). */
#ifndef KH1_DATA_TYPES_TEXT_00110000_H52_P2_H
#define KH1_DATA_TYPES_TEXT_00110000_H52_P2_H

#include "common.h"
#include "data/types/text_00110000_h52.h"
#include "data/types/text_00110000_h52_p.h"

typedef struct { u8 pad[0x10]; s32 x10; u8 pad14[0xc]; s32 x20; } Mdl52;
typedef struct { Mdl52 *m; u8 pad[12]; } MdlEnt52;

#endif /* KH1_DATA_TYPES_TEXT_00110000_H52_P2_H */

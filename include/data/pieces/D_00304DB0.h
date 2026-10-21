/* The data piece D_00304DB0 (src/data/data_0030.s): one declaration its users
 * share (phase 4, session 26: a union of the users' views; each user names its member). */
#ifndef KH1_DATA_PIECES_D_00304DB0_H
#define KH1_DATA_PIECES_D_00304DB0_H

#include "common.h"

typedef struct { f32 x0; s32 x4, x8, xc, x10; } B3PjInf_304DB0;
typedef struct { f32 h; f32 f4; s32 f8; s32 fc; s32 f10; } HtTab_304DB0;
typedef union { B3PjInf_304DB0 b3PjInf[0x8c / sizeof(B3PjInf_304DB0)]; HtTab_304DB0 htTab[0x8c / sizeof(HtTab_304DB0)]; } U00304DB0;

extern U00304DB0 D_00304DB0;

#endif /* KH1_DATA_PIECES_D_00304DB0_H */

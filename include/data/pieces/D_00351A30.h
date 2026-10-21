/* The data piece D_00351A30 (src/data/data_0035.s): one declaration its users
 * share (phase 4, session 26: a union of the users' views; each user names its member). */
#ifndef KH1_DATA_PIECES_D_00351A30_H
#define KH1_DATA_PIECES_D_00351A30_H

#include "common.h"

typedef struct { u8 a, b; } P2_351A30;
typedef union { P2_351A30 p2[0x10 / sizeof(P2_351A30)]; u8 b[0x10]; } U00351A30;

extern U00351A30 D_00351A30;

#endif /* KH1_DATA_PIECES_D_00351A30_H */

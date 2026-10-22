/* The data piece D_002E319C (src/data/data_002E.s): the current menu item (phase 4:
 * session 26 cast at each use, session 27 folded the users' views, session 28 declared
 * the pointer with the folded type; D_002E31A0 points to the same item). */
#ifndef KH1_DATA_PIECES_D_002E319C_H
#define KH1_DATA_PIECES_D_002E319C_H

#include "common.h"

typedef struct {
    u16 f0;
    u8 pad_2[0x4];
    u8 f6;
    s8 f7;
    s8 f8;
    s8 f9;
    s8 fa;
    s8 fb;
    u16 f0c;
    u16 f0e;
} O8_2e319c;

extern O8_2e319c *D_002E319C;

#endif /* KH1_DATA_PIECES_D_002E319C_H */

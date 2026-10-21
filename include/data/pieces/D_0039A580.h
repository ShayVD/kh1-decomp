/* The data piece D_0039A580 (src/data/data_0039.s): one struct its
 * users share (phase 4: session 26 cast at each use, session 27 folded the users'
 * views into these types; users not folded still cast). */
#ifndef KH1_DATA_PIECES_D_0039A580_H
#define KH1_DATA_PIECES_D_0039A580_H

#include "common.h"

typedef struct {
    s32 id;
    u8 pad_4[0x6c];
    s8 *code;
    u8 pad_74[0x2c];
    s32 xa0;
    u8 pad_a4[0xdc];
    s32 sp;
    s32 stk[37];
    u8 pad_218[0x100];
    s32 x318;
    u8 pad_31c[0x34];
} VM_39a580;

extern VM_39a580 D_0039A580;

#endif /* KH1_DATA_PIECES_D_0039A580_H */

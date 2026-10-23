/* The struct types of the data piece D_00304BE8 (data/pieces/D_00304BE8.h declares it with
 * the root type left incomplete; the users that read its fields include this). */
#ifndef KH1_DATA_PIECES_D_00304BE8_S_H
#define KH1_DATA_PIECES_D_00304BE8_S_H

#include "common.h"
#include "data/pieces/D_00304BE8.h"

typedef struct {
    u8 pad_0[0x6];
    u8 x6;
    u8 pad_7[0x1];
} Q9c_304be8;

typedef struct {
    u8 lv;
    u8 x1;
    u8 hpmax;
    u8 x3;
    u8 mpmax;
    u8 x5;
    u8 x6;
    u8 x7;
    u8 pad_8[0x10];
    u8 x18;
    u8 x19[8];
    u8 x21;
    u8 x22[0x10];
    u8 x32;
    u8 pad_33[0x1];
    u8 x34;
    u32 :8;
    u32 b16:1;
    u32 :15;
    s16 x38;
    u8 pad_3a[0x2];
    s32 exp;
    u8 name[0x30];
} Sub_304be8;

typedef struct {
    Sub_304be8 sub;
    u8 bits;
    u8 pad_71[0x3];
} W606Mem_304be8;

struct Save_304be8 {
    u8 pad_0[0x4];
    W606Mem_304be8 m[10];
    u8 x48c;
    u8 x48d;
    u8 x48e[4];
    u8 b492[7];
    u8 items[0x100];
    u8 list599[0x30];
    u8 pad_5c9[0x3];
    u32 bits5cc[(0x7D0 - 0x5CC) / 4];
    s8 x7d0[7];
    u8 pad_7d7[0x1];
    u16 cnt[51];
    u16 x83e;
    u8 pad_840[0x4];
    s8 x844[3];
    u8 pad_847[0x1];
    u16 cnt_848[1];
    u8 pad_84a[0x2a];
    u32 f874;
    u64 x878;
    u8 f880;
    u8 pad_881[0x7];
};

#endif /* KH1_DATA_PIECES_D_00304BE8_S_H */

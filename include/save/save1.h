/* Save block 1 (func_00232cc0(1); docs/modules.md "Session 35"): the script's
 * flags and records, 0xdd8 bytes.  One type for the views of b11 (SaveInit,
 * func_001eacd0), h21 (Sv), h45 / s7_w19 (Rec98), h46 (SvA) and the auto
 * files.  Where the views disagreed on a region's layout it is a union and
 * each function keeps the member that gives its code: func_001eacd0 clears
 * the region at 0 as three areas and sets the bit-fields of 0xad0 / 0xdc4,
 * the others read 0xad0 as a word and 0xdc4-0xdd0 as words. */
#ifndef KH1_SAVE_SAVE1_H
#define KH1_SAVE_SAVE1_H

#include "common.h"

typedef struct {
    union {
        struct { u8 a[2048]; u8 b[256]; u8 c[384]; } z;    /* the areas func_001eacd0 clears */
    } u;                                    /* 0x000 */
    u8 l0[10], l1[10], l2[10], l3[50];      /* 0xa80: the four record lists (src/list/list.c) */
    union {
        u32 open;                           /* 0xad0: bits 0-3, which lists are open */
        struct { u32 f0:1, f1:1, f2:1, f3:1; char name[10]; } b;   /* 0xad1: a name */
    } ad0;
    u8 padadc[7];
    u8 fl[0x20];                            /* 0xae3: flags 0-255 (bit 7 first) */
    u8 fl2[0x11];                           /* 0xb03: flags 0-135 */
    s32 tbl[32][5];                         /* 0xb14: score tables, five entries each */
    u32 w[11];                              /* 0xd94: flag words (bit 31 first) */
    u8 fl3[4];                              /* 0xdc0 */
    union {
        struct { u32 g0:1, g1:1, g2:1, g3:1, g4:1; u8 padg[3]; u8 h[8]; u8 dd0; } i;
        struct { u32 dc4; u8 fl5[4]; s32 dcc; s32 dd0; } f;
    } x;                                    /* 0xdc4 */
    u32 dd4;                                /* 0xdd4 */
} Save1;

#endif /* KH1_SAVE_SAVE1_H */

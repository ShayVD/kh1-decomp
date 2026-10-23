/* The text windows (src/text/textwin.c, docs/modules.md "Session 37"):
 * 24 slots of 0xf0 bytes at D_0063F758 (the extern is in the .c files:
 * tools/shift/cover_check.py reads only those).
 *
 * func_001f31a8 opens a window from a descriptor (TextWinDesc) in a free
 * slot (state 0) and puts it at the head of the open list D_00640DD8
 * (newer / older at +0x14 / +0x18) and of the focus list D_00640DDC
 * (+0x1c / +0x20).  Windows can also be chained side by side (prev / next
 * at +0xc / +0x10).  States: 0 free, 1-3 open, 4-5 closing; func_001f3680
 * sets the close request (bit 0 of the word at +0x44). */
#ifndef KH1_TEXT_TEXTWIN_H
#define KH1_TEXT_TEXTWIN_H

#include "common.h"

struct TextWin;

/* What func_001f31a8 opens a window from (D_003E9630 is a scratch one). */
typedef struct {
    s32 x0;                       /* the window's +0x4 */
    s32 x4;                       /* the window's +0x8 */
    s32 x8;                       /* flags: 4 / 8 refuse a second window */
    s16 xc, xe;                   /* x, y */
    u16 x10, x12, x14, x16, x18, x1a, x1c, x1e, x20;
    u16 x22, x24, x26, x28;       /* func_001f3520 only */
} TextWinDesc;

typedef struct TextWin {
    void (*x0)(struct TextWin *);
    s32 x4;                 /* a callback, but s32: a pointer type changes func_001f31a8 */
    s32 x8;
    struct TextWin *prev;   /* +0x0c: chain */
    struct TextWin *next;   /* +0x10 */
    struct TextWin *x14;    /* open list: newer */
    struct TextWin *x18;    /* open list: older */
    struct TextWin *x1c;    /* focus list */
    struct TextWin *x20;
    s32 x24, x28, x2c, x30, x34, x38, x3c;
    union {
        struct { u64 lo:32; u64 hi:32; } a;
        struct { u64 :32; u64 b0:1; u64 :31; } b;
        struct { u32 x40; u32 x44; } v;
        struct { u32 x40; u32 b44:1; u32 r44:31; } w;
    } u40;
    union {
        struct { u64 c0:1; u64 crest:63; } a;
        u64 q;                      /* func_001f5e10 sets bit 0 */
        struct { s32 lo, hi; } w;   /* bit 0 of lo: scale around the anchor */
    } u48;
    s32 x50, x54;           /* func_001f31a8 clears both with one sd */
    s32 x58, x5c;
    TextWinDesc *desc;      /* +0x60 */
    void *x64;              /* default D_00490AE0 */
    void *x68;              /* an entry of D_003E8E30 or 0 */
    s32 x6c;
    s32 x70;
    f32 x74, x78;
    s32 x7c;                /* group */
    s32 x80, x84, x88;
    s32 state;              /* +0x8c */
    s32 x90;
    f32 x94, x98, x9c, xa0, xa4, xa8;
    s32 xac, xb0, xb4;
    s16 xb8, xba, xbc, xbe, xc0, xc2, xc4, xc6, xc8, xca, xcc, xce;
    s16 xd0, xd2, xd4, xd6, xd8, xda;
    u8 xdc[16];
} TextWin;

#endif /* KH1_TEXT_TEXTWIN_H */

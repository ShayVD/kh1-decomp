/* Page 5 of the menu (docs/modules.md "Session 41" and "Session 42"):
 * src/menu/journal.c is the frame, journal_s0.c ... journal_s5.c its six
 * sections, numbered by their place in the opener table D_003F5A00 (the
 * order in memory is 2, 0, 3, 5, 1, 4).  Each section has an opener (keeps
 * the section's window), a set up (journal.c's func_0021dad8) and a reset
 * (func_0021db30). */
#ifndef KH1_MENU_JOURNAL_H
#define KH1_MENU_JOURNAL_H

#include "common.h"

/* The TextWin fields (include/text/textwin.h) the sections read, with
 * +0xd2 as a plain s16. */
typedef struct JsWin {
    u8 pad0[0xc];
    struct JsWin *xc;
    struct JsWin *x10;
    u8 pad14[0x24 - 0x14];
    s32 x24;
    u8 pad28[0x40 - 0x28];
    s32 x40;
    u8 pad44[0x90 - 0x44];
    s32 x90;
    u8 pad94[0xa0 - 0x94];
    f32 xa0;
    u8 pada4[0xb0 - 0xa4];
    s32 xb0, xb4;
    u8 padb8[0xc4 - 0xb8];
    s16 xc4;
    u8 padc6[0xca - 0xc6];
    s16 xca, xcc, xce;
    u8 padd0[2];
    s16 xd2;
    u8 padd4[0xd8 - 0xd4];
    s16 xd8, xda;
} JsWin;

#endif /* KH1_MENU_JOURNAL_H */

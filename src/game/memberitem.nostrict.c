/* The party members' items and equipment against the save data D_00304BE8:
 * using a recovery item (func_00149170, func_00149440), the equipped weapon
 * (func_00149740), and the three member weapon models D_0054C1B0
 * (func_00149c80 loads one by name, func_00149f10 swaps one, the callback
 * D_0054C210). Flag mode: nostrict (the other modes are in the sibling
 * files). Read from the code, not proved by a boot (docs/modules.md "Session
 * 53"). */
#include "common.h"
#include "data/pieces/D_0035C710.h"
#include "data/bss_0053.h"
#include "data/pieces/D_002C58A0.h"
#include "data/pieces/D_00304DB0.h"
#include "data/pieces/D_00308CDC.h"
#include "data/pieces/D_003044A0.h"
#include "data/pieces/D_00304BE8_s.h"
#include "data/types/nostrict_text_00140000_s9_w8.h"
#include "data/pieces/D_00350CE8.h"

/* func_00149440 (from hand/nostrict/text_00140000_h56.c). */
typedef struct { u8 pad[0x40]; s32 w40; s32 w44; s32 w48; u8 pad4c[0xf0 - 0x4c]; } StBuf;
typedef struct { u8 b0, b1, b2, b3; s16 h4; s16 h6; } Itm;
Itm *func_00147840(s32);
void func_00141b10(s32, StBuf *);
s32 func_00149440(s32 kind, s32 id) {
    StBuf st;
    Sub_304be8 *e;
    s32 a, b, r;
    u8 m = func_00147840(kind)->b2;

    if (m != 0 && m != 12) return 0;
    e = &D_00304BE8->m[id].sub;
    func_00141b10(id, &st);
    a = e->x1 < st.w40;
    b = e->x3 < st.w48;
    r = 0;
    switch (kind) {
    case 1:
    case 2:
    case 6:
    case 142:
        r = a | 2;
        break;
    case 3:
    case 7:
        r = b | 4;
        break;
    case 4:
    case 8:
    case 143:
    case 144:
        r = (a | b) | 8;
        break;
    case 152:
        r = 16;
        if (e->x6 < 100) r = 17;
        break;
    case 153:
        r = 32;
        if (e->x7 < 100) r = 33;
        break;
    case 154:
        r = 64;
        if (e->x5 < 100) r = 65;
        break;
    }
    return r;
}

/* func_00149c80 (from hand/nostrict/text_00140000_s9_w8.c). */
typedef Q9c_304be8 Q9c;
typedef struct { u8 pad[6]; s16 x6; } R9c;
extern Ent9c D_0054C1B0[];
extern s32 D_00350D14;
extern char D_0048E410[];
u8 *func_001477c8(void *);
s32 sprintf(char *, const char *, ...);
void func_00120748(char *, s32, void *, s32);
void func_00149bd0();
#define func_00147840 ((R9c *(*)(s32)) func_00147840)
/* func_00149c80 (hand/nostrict): func_001477c8 result read into a local `u8 *s` in its own statement before sprintf; this lengthens id's live range so param i (s1) outranks id (s2) in global-alloc. */
s32 func_00149c80(s32 i, s32 a) {
    char buf[32];
    Q9c *m = (Q9c *)((u32)D_00304BE8 + (u32)(i * 0x74 + 0x30));
    Ent9c *e;
    s32 id, j;
    u8 *s;
    if (m->x6 == 0) return 0;
    id = func_00147840(m->x6)->x6;
    for (e = D_0054C1B0, j = 0; j < 3; j++, e++) {
        if (e->used && e->x4 == i && e->x8 == id) {
            e->state = 1;
            return 0;
        }
    }
    e = D_0054C1B0;
    if (i != 0) {
        e++;
        for (j = 0; j < 2; j++, e++) {
            if (!e->used || !e->state) break;
        }
    }
    e->used = 1;
    e->state = 1;
    e->b3 = 0;
    e->x1c = a;
    e->x4 = i;
    e->x8 = id;
    if (id == 0) return 0;
    s = func_001477c8(D_00350CE8[i]);
    sprintf(buf, D_0048E410, s + id * 0x58 - 0x58, D_00350D14);
    func_00120748(buf, e->x10, func_00149bd0, 0);
    return 1;
}
#undef func_00147840


/* Pointer tables only this file uses (phase 4, tools/shift/define_ptr_tables.py;
   moved from hand/nostrict/text_00140000_s9_w8.c in session 53). */
extern u8 D_0048E418[];
s32 D_00350D14 ALIGNED(4) = (s32)D_0048E418;

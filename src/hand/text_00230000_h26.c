/* 0x00230000-0x0024FFFF game code by hand (batch 26). */
#include "common.h"

extern u8 D_00426970[];
extern u8 D_0042B790[];
extern u8 D_004305B0[];
void func_00249a48(void *, s32);

void func_0023d698(s32 a) {
    if (a == 0) {
        func_00249a48(D_00426970, 1);
    } else if (a == 1) {
        func_00249a48(D_0042B790, 1);
    } else {
        func_00249a48(D_004305B0, 1);
    }
}

typedef struct { u8 pad[0xA24]; s32 unkA24; u8 padA28[8]; s32 unkA30; } Obj3;
extern f32 D_002BBDFC;

s32 func_00240b28(Obj3 *e) {
    s32 r;
    if (e->unkA30 > 0) {
        e->unkA30 = e->unkA30 - D_002BBDFC;
        r = 1;
    } else {
        r = 2;
        if (e->unkA24 == 0) r = 0;
    }
    return r;
}

/* Five 0xD00-byte slots, each with an in-use flag. */
typedef struct {
    u32 state;  /* +0x0 */
    s32 unk4;   /* +0x4 */
    u8 pad8[0x94 - 8];
    s32 unk94;
    s32 unk98;
    s32 unk9C;
    u8 padA0[0x770 - 0xA0];
    s32 unk770;
    u8 pad774[0x9D0 - 0x774];
    s32 unk9D0;
    u8 pad9D4[0xA18 - 0x9D4];
    s32 unkA18;
    f32 unkA1C;
    s32 unkA20;
    s32 unkA24;
    u8 padA28[0xD00 - 0xA28];
} Slot;
typedef struct {
    s32 on[8];  /* +0x0 */
    Slot e[5];  /* +0x20 */
} SlotTbl;
extern SlotTbl D_00651E50;
s32 func_00122ff8(s32);
s32 func_0023d490(Slot *);
void func_002414a8(s32, s32);
void func_0023d1a0(void);

void func_00241560(void) {
    s32 i;
    Slot *p = D_00651E50.e;
    for (i = 0; i < 5; i++, p++) {
        if (D_00651E50.on[i] && p->state < 3) {
            if (!func_00122ff8(p->unk4)) {
                D_00651E50.on[i] = 0;
                if (p->state == 0) func_0023d1a0();
            }
        }
    }
}

Slot *func_00241b60(s32 i, s32 b) {
    Slot *p;
    D_00651E50.on[i] = 1;
    D_00651E50.e[i].unk4 = b;
    p = &D_00651E50.e[i];
    p->unkA18 = 1;
    p->state = i;
    p->unk98 = p->unk94 = func_0023d490(p);
    p->unkA24 = 0;
    p->unk770 = 0;
    p->unk9D0 = 0;
    p->unk9C = 0;
    func_002414a8(i, 1);
    return p;
}

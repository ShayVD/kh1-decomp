/* Labelled numbers over the field (docs/modules.md "Session 46"),
 * 0x00246cf0-0x002474e8, default flags part.  D_0045FAC0 (in .data) holds ten
 * of them (LblNum, 0x930 bytes: state, age, position, value, a label, a frame
 * and ten digit sprites).  func_00247228 sets one up with a value at a
 * position; func_00247190 is the draw hook (func_00247258, the set up,
 * registers it and builds the sprites from D_0045E1F0) with its drawing
 * environment D_00668E20 (TEST_1 0x8000000048); func_002470d0 steps one
 * (out when its label's animation ends) and draws it (func_00246ed8).
 * func_00247408 shows a value over an actor (its point 0x8004), func_00247468
 * over a position; both take a free slot or the oldest (func_00247388).
 * func_00247350 is the HUD's step (all off), func_002474a8 is 1 while one is
 * shown.  func_00246cf0 splits a value into digits (as counter.c's
 * func_00244b10).
 * What the label says is not known (no boot). */
#include "common.h"
#include "data/types/text_00240000_h50.h"

typedef struct {
    s32 state;          /* +0x0 */
    s32 cnt;            /* +0x4 */
    u8 pad8[8];
    u8 pos[0x10];       /* +0x10 */
    s32 value;          /* +0x20 */
    u8 pad24[0xC];
    u8 label[0xC0];     /* +0x30 */
    u8 frame[0xC0];     /* +0xF0 */
    u8 digit[10][0xC0]; /* +0x1B0 */
} LblNum;
typedef struct { u8 pad[0x60]; Q4 q[4]; Q4 r[4]; } Panel;
typedef struct { u8 pad[0x60]; u64 unk60; u8 pad68[8]; u64 unk70; u8 pad78[0xE0 - 0x78]; u64 unkE0; u8 tail[0x160 - 0xE8]; } Q70;

extern LblNum D_0045FAC0[10];
Q70 D_00668E20 ALIGNED(32);
Panel D_00668F90 ALIGNED(16);
extern Q4 *D_00668F80;
extern u8 D_0045E1F0[];
extern u8 D_0045FA80[];
extern u8 D_0045FA88[];
extern u8 D_0045FA90[];
void func_0011ef10(s32, void *);
s32 func_0011ef38(void *);
void func_00237018(void *, s32, s32);
void func_002370c8(void *);
Q4 *func_002388b8(void *, s32, Q4 *);
void func_00246ed8(s32, LblNum *);
s32 func_0024a1c0(void *);
void func_0024aa48(void *, void *, void *);
void func_0024aac8(void *);
void func_0024af40(void *, void *, void *);
void func_0024ae00(void *);
void func_0024af00(void *);
void sceVu0CopyVector(void *, void *);
void func_001315c0(s32, s32, void *, f32);

s32 func_00246cf0(s32 v, s32 *d) {
    s32 *p;
    s32 n = 5;
    s32 i = 0;
    d[0] = v / 10000;
    d[1] = v % 10000 / 1000;
    d[2] = v % 1000 / 100;
    d[3] = v % 100 / 10;
    d[4] = v % 10;
    if (d[0] == 0) {
        p = d;
        do {
            i++;
            p++;
            n--;
        } while (i < 4 && *p == 0);
    }
    return n;
}

void func_00246dc0(void *a0, void *a1, s32 dx, s32 dy, f32 s) {
    s32 i;
    Panel *d = &D_00668F90;
    func_0024aa48(a0, d, a1);
    for (i = 0; i < 4; i++) { s32 *r = &d->r[i].b; r[-1] += dx << 4; r[0] += dy << 4; }
    for (i = 0; i < 4; i++) {
        D_00668F90.q[i].d = D_00668F90.q[i].d * s;
    }
    D_00668F80 = func_002388b8(&D_00668F90, 1, D_00668F80);
}

void func_00246ea8(s32 on, void *spr) {
    if (on != 0) {
        func_0024ae00(spr);
    }
    func_0024af00(spr);
}

void func_002470d0(LblNum *p) {
    s32 r = 0;
    switch (p->state) {
    case 0:
        return;
    case 1:
        p->state = 2;
        r = 1;
        break;
    case 2:
        if (func_0024a1c0(p->label) & 4) p->state++;
        break;
    case 3:
        p->state = 0;
        break;
    }
    p->cnt++;
    func_00246ed8(r, p);
}

s32 func_00247190(void) {
    LblNum *p;
    func_002370c8(&D_00668E20);
    D_00668E20.unkE0 = 5;
    D_00668E20.unk60 = 0x30003;
    D_00668E20.unk70 = 0x8000000048ULL;
    func_00237018(&D_00668E20, 0x16, 1);
    p = D_0045FAC0;
    do {
        func_002470d0(p);
        p++;
    } while ((s32)p < (s32)&D_0045FAC0[10]);
    return 0;
}

void func_00247228(LblNum *p, s32 value, void *pos) {
    p->value = value;
    p->state = 1;
    p->cnt = 0;
    sceVu0CopyVector(p->pos, pos);
}

void func_00247258(void) {
    s32 i;
    LblNum *p;
    func_0024aac8(D_0045E1F0);
    p = D_0045FAC0;
    for (i = 0; i < 10; i++) {
        func_0024af40(D_0045FA80, p->label, D_0045E1F0);
        func_0024af40(D_0045FA88, p->frame, D_0045E1F0);
        func_0024af40(D_0045FA90, p->digit, D_0045E1F0);
        p++;
    }
    if (func_0011ef38(func_00247190) == 0)
        func_0011ef10(0x28489, func_00247190);
}

void func_00247350(void) {
    s32 i;
    for (i = 0; i < 10; i++) D_0045FAC0[i].state = 0;
}

LblNum *func_00247388(void) {
    s32 max = -1;
    LblNum *best = 0;
    s32 i;
    LblNum *p;
    for (i = 0; i < 10; i++) {
        p = &D_0045FAC0[i];
        if (p->state == 0) return p;
    }
    for (i = 0; i < 10; i++) {
        p = &D_0045FAC0[i];
        if (max < p->cnt) {
            max = p->cnt;
            best = p;
        }
    }
    return best;
}

void func_00247408(s32 actor, s32 value) {
    s32 pos[4];
    LblNum *p = func_00247388();
    func_001315c0(actor, 0x8004, pos, 0.0f);
    func_00247228(p, value, pos);
}

void func_00247468(void *pos, s32 value) {
    func_00247228(func_00247388(), value, pos);
}

s32 func_002474a8(void) {
    s32 i;
    for (i = 0; i < 10; i++)
        if (D_0045FAC0[i].state) return 1;
    return 0;
}

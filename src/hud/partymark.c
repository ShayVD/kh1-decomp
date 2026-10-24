/* The marks over the party (docs/modules.md "Session 46"),
 * 0x00245f58-0x002464f8.  D_00668040 holds one mark for each of the two
 * party members (PMark: state, alpha, kind, the member; func_00245f58 picks
 * the slot from func_0013daa8 of the member's +0x130 +0x4C).  The battle
 * code (h60) shows one with func_00245f90 and lets it fade with
 * func_00245ff0; func_00246320 is the draw hook (func_00246438, the set up,
 * registers it and takes the sprite D_00668060 from D_0045D280): it steps
 * each mark (shown, fading by 0.2 a frame) and draws it (func_002461f8,
 * drawing environment D_00667DF0; sent only when func_00242bf0 of the
 * member's kind allows it) 54 pixels above the member's point 0x8004
 * (func_00246120; kind 0 has the sprite, the others draw nothing).
 * func_00246020 is the HUD's step (both off); func_002464f8 tells h60 which
 * of the two is shown or coming (states 1-3). */
#include "common.h"
#include "data/types/text_00240000_h50.h"
#include "data/pieces/D_002E26C0.h"
#include "data/pieces/D_00431D20.h"

typedef struct { u8 pad[0x4C]; u16 unk4C; } Info;
typedef struct { u8 pad[0x130]; Info *unk130; } Act;
typedef struct { u32 state; f32 t; s32 kind; Act *actor; } PMark;
typedef struct { u8 pad[0x60]; Q4 q[4]; Q4 r[4]; } Panel;
typedef struct { u8 pad[0x60]; u64 x60; u64 x68; u64 x70; u8 pad2[0x68]; u64 xe0; u8 tail[0x160 - 0xE8]; } S7df0;
typedef struct { u8 pad[0x180]; B192 b; } L240;

Panel D_00667F60 ALIGNED(32);
Q4 *D_00667F50 ALIGNED(16);
Q4 *D_00667F54 ALIGNED(4);
S7df0 D_00667DF0 ALIGNED(16);
extern PMark D_00668040[2]; /* src/data/bss_0066.c: u8 D_00668040[0x20] */
extern B192 D_00668060;
extern Q4 D_00351E10[];
extern u8 D_0045D280[];
extern u8 D_0045D6D0[];
s32 func_0013daa8(s32);
void *memset(void *, s32, u32);
void func_0011ef10(s32, void *);
s32 func_0011ef38(void *);
s32 func_0013c318(u16);
void func_00237018(void *, s32, s32);
void func_002370c8(void *);
Q4 *func_002388b8(void *, s32, Q4 *);
s32 func_00242bf0(s32);
void func_0024aa48(void *, void *, void *);
void func_0024aac8(void *);
void func_0024af40(void *, void *, void *);
void func_0024ae00(void *);
void func_0024af00(void *);
void func_001315c0(Act *, s32, s32 *, f32);
s32 func_00249580(s32 *);
f32 func_00237a48(s32 *, void *, s32 *, s32);
void func_00249558(s32 *, s32 *);
s32 func_001375d8(Act *);

PMark *func_00245f58(Act *a) {
    s32 i = func_0013daa8(a->unk130->unk4C) != 1;
    return &D_00668040[i];
}

void func_00245f90(s32 kind, Act *a) {
    PMark *m = func_00245f58(a);
    if (m->state == 0) {
        m->kind = kind;
        m->actor = a;
        m->state = 1;
        m->t = 1.0f;
    }
}

void func_00245ff0(Act *a) {
    PMark *m = func_00245f58(a);
    if (m->state != 0) {
        m->state = 4;
    }
}

void func_00246020(void) {
    D_00668040[1].state = 0;
    D_00668040[0].state = 0;
}

void func_00246038(void *a0, void *a1, s32 dx, s32 dy, f32 s) {
    s32 i;
    Panel *d = &D_00667F60;
    func_0024aa48(a0, d, a1);
    for (i = 0; i < 4; i++) { s32 *r = &d->r[i].b; r[-1] += dx << 4; r[0] += dy << 4; }
    for (i = 0; i < 4; i++) {
        D_00667F60.q[i].d = D_00667F60.q[i].d * s;
    }
    D_00667F50 = func_002388b8(&D_00667F60, 1, D_00667F50);
}

void func_00246120(PMark *m, s32 on, f32 f) {
    s32 v[8];
    void *spr = NULL;
    if (m->kind == 0) {
        spr = &D_00668060;
    }
    if (on != 0) {
        func_0024ae00(spr);
    }
    func_0024af00(spr);
    func_001315c0(m->actor, 0x8004, v, 0.0f);
    if (func_00249580(v) == 0) {
        func_00237a48(&v[4], D_002E26C0, v, 1);
        func_00249558(&v[4], &v[4]);
        v[5] -= 54;
        func_00246038(spr, D_00431D20, v[4], v[5], f);
    }
}

void func_002461f8(PMark *a0, s32 a1, f32 f) {
    s32 t, k;
    func_002370c8(&D_00667DF0);
    D_00667DF0.xe0 = 5;
    D_00667DF0.x60 = 0x30003;
    func_00237018(&D_00667DF0, 22, 1);
    D_00667F54 = D_00351E10;
    D_00667F50 = D_00351E10 + 1;
    func_00246120(a0, a1, f);
    t = func_0013c318(a0->actor->unk130->unk4C);
    if (t == 1) k = 1;
    else if (t == 2) k = 2;
    if (func_00242bf0(k)) {
        func_00237018(D_00667F54, D_00667F50 - D_00667F54, 1);
    }
}

s32 func_00246320(void) {
    s32 i;
    for (i = 0; i < 2; i++) {
        PMark *e = &D_00668040[i];
        s32 r = 0;
        switch (e->state) {
        case 0:
            continue;
        case 1:
            r = 1;
            e->state++;
            break;
        case 2: case 4:
            e->state++;
            break;
        case 3:
            break;
        case 5:
            e->t -= 0.199999988079071044921875f;
            if (e->t < 0.0f) {
                e->t = 0.0f;
                e->state++;
            }
            break;
        case 6:
            e->state = 0;
            continue;
        }
        if (func_001375d8(e->actor)) {
            func_00246020();
            return 0;
        }
        func_002461f8(e, r, e->t);
    }
    return 0;
}

void func_00246438(void) {
    L240 l;
    memset(D_00668040, 0, 32);
    func_0024aac8(D_0045D280);
    func_0024af40(D_0045D6D0, &l, D_0045D280);
    D_00668060 = l.b;
    if (func_0011ef38(func_00246320) == 0)
        func_0011ef10(0x28489, func_00246320);
}

void func_002464f8(s32 *out) {
    s32 i;
    for (i = 0; i < 2; i++) {
        switch ((s32)D_00668040[i].state) {
        case 0: out[i] = 0; break;
        case 4: out[i] = 0; break;
        case 5: out[i] = 0; break;
        case 6: out[i] = 0; break;
        default: out[i] = 1; break;
        }
    }
}

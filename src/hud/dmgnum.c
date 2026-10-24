/* Numbers over the field (docs/modules.md "Session 46"), 0x00245798-0x00245f58,
 * default flags part.  D_00662A30 holds ten numbers (DmgNum, 0x860 bytes: in
 * use, age, value, position, a frame sprite and ten digit sprites).
 * func_00245840 shows a value over an actor (its point 0x8004), func_002458a0
 * over a position; both take a free slot or the oldest (func_002457c8).
 * func_00245da0 is the draw hook (func_00245e40, the set up, registers it and
 * builds the sprites from D_0045BC10) with its drawing environment
 * D_006627E0; func_00245cd0 steps one number (out when its frame's animation
 * ends) and draws it (func_00245b08).  func_002458e0 is the HUD's step (all
 * off), func_00245f18 is 1 while one is shown.  Most likely the damage and
 * heal numbers; not proved by a boot. */
#include "common.h"

typedef struct {
    u32 used;          /* +0x0 */
    s32 age;           /* +0x4 */
    s32 value;         /* +0x8 */
    u8 padC[4];
    u8 pos[0x10];      /* +0x10 */
    u8 frame[0xC0];    /* +0x20 */
    u8 digit[10][0xC0]; /* +0xE0 */
} DmgNum;
typedef struct { u8 pad[0x60]; u64 unk60; u8 pad68[8]; u64 unk70; u8 pad78[0xE0 - 0x78]; u64 unkE0; u8 tail[0x160 - 0xE8]; } Q70;

Q70 D_006627E0 ALIGNED(32);
extern DmgNum D_00662A30[10]; /* src/data/bss_0066.c: E860 D_00662A30[10] */
extern u8 D_0045BC10[];
extern u8 D_0045D240[];
extern u8 D_0045D248[];
void sceVu0CopyVector(void *, void *);
void func_001315c0(s32, s32, void *, f32);
void func_0024ae00(void *);
void func_0024af00(void *);
void func_0011ef10(s32, void *);
s32 func_0011ef38(void *);
void func_00237018(void *, s32, s32);
void func_002370c8(void *);
void func_00245b08(s32, DmgNum *);
s32 func_0024a1c0(void *);
void func_0024aac8(void *);
void func_0024af40(void *, void *, void *);

void func_00245798(DmgNum *d, s32 value, void *pos) {
    d->value = value;
    d->used = 1;
    d->age = 0;
    sceVu0CopyVector(d->pos, pos);
}

DmgNum *func_002457c8(void) {
    DmgNum *best = 0;
    s32 max = -1;
    s32 i;
    DmgNum *p = D_00662A30;
    for (i = 0; i < 10; i++, p++)
        if (p->used == 0) return p;
    for (i = 0; i < 10; i++) {
        p = &D_00662A30[i];
        if (max < p->age) {
            max = p->age;
            best = p;
        }
    }
    return best;
}

void func_00245840(s32 actor, s32 value) {
    s32 pos[4];
    DmgNum *d = func_002457c8();
    func_001315c0(actor, 0x8004, pos, 0.0f);
    func_00245798(d, value, pos);
}

void func_002458a0(void *pos, s32 value) {
    func_00245798(func_002457c8(), value, pos);
}

void func_002458e0(void) {
    s32 i;
    for (i = 0; i < 10; i++) D_00662A30[i].used = 0;
}

void func_00245918(void) {
}

s32 func_00245a08(s32 v, s32 *d) {
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

void func_00245ad8(s32 on, void *spr) {
    if (on != 0) {
        func_0024ae00(spr);
    }
    func_0024af00(spr);
}

void func_00245cd0(DmgNum *p) {
    s32 r = 0;
    switch (p->used) {
    case 0:
        return;
    case 1:
        r = 1;
        p->used++;
        break;
    case 2: case 3: case 4:
        p->used++;
        break;
    case 5:
        if (func_0024a1c0(p->frame) & 4) p->used++;
        break;
    case 6:
        p->used = 0;
        return;
    }
    p->age++;
    func_00245b08(r, p);
}

s32 func_00245da0(void) {
    s32 i;
    DmgNum *p;
    func_002370c8(&D_006627E0);
    D_006627E0.unkE0 = 5;
    D_006627E0.unk60 = 0x30003;
    D_006627E0.unk70 = 0x8000000048ULL;
    func_00237018(&D_006627E0, 0x16, 1);
    func_00245918();
    p = D_00662A30;
    for (i = 0; i < 10; i++, p++) {
        if (p->used != 0) func_00245cd0(p);
    }
    return 0;
}

void func_00245e40(void) {
    s32 i;
    DmgNum *p;
    func_0024aac8(D_0045BC10);
    p = D_00662A30;
    for (i = 0; i < 10; i++) {
        func_0024af40(D_0045D240, p->frame, D_0045BC10);
        func_0024af40(D_0045D248, p->digit, D_0045BC10);
        p++;
    }
    if (func_0011ef38(func_00245da0) == 0)
        func_0011ef10(0x28489, func_00245da0);
}

s32 func_00245f18(void) {
    s32 i;
    for (i = 0; i < 10; i++) {
        if (D_00662A30[i].used != 0) return 1;
    }
    return 0;
}

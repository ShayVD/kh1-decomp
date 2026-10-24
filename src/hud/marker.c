/* Markers over actors and the lock-on (docs/modules.md "Session 46"),
 * 0x0023c1b0-0x0023cfe8, default flags part.
 * D_00651310 holds ten markers (0xE0 bytes each: in use, a sprite copied from
 * D_00651300 and the actor they follow); func_0023c228 takes a free one,
 * func_0023c5a8 frees one.  func_0023c8c8 is a draw hook (registered by
 * func_0023c968): the drawing environment D_00650F40 and the mark of the
 * current target (func_0023c7a0) in one GIF send.  func_0023c1b0 hands the
 * target's numbers to func_00246a70 when it has some (func_00141348).
 * func_0023cf30 sets up a three-sprite sign (state D_0044A820: 0 off, 1 shown,
 * 2 held, 3 fading, 4 out; func_0023cee8 shows it, func_0023cf08 releases it,
 * func_0023cfc8 is 1 while it is on, func_0023cfd8 is the HUD's step for it)
 * and registers its hook func_0023ceb0.  "Lock-on" is a guess from
 * D_002E31B0 (an actor) and the four mark kinds; not proved by a boot. */
#include "common.h"
#include "data/pieces/D_00449990.h"
#include "data/pieces/D_0044A820.h"

typedef kh1_s128 u128;
typedef struct { s32 used; s32 x; u8 pad[0xD8]; } Slot;
typedef struct { u8 pad[0x60]; u64 x60; u8 pad2[0x78]; u64 xe0; u8 tail[0x160 - 0xE8]; } GsEnv;

GsEnv D_00650F40 ALIGNED(64);
extern Slot D_00651310[10];
extern u128 D_00351E10[];
extern u128 *D_00651200; /* src/data/bss_0065.c: s32 D_00651200 */
extern u128 *D_00651204; /* src/data/bss_0065.c: u8 *D_00651204 */
extern s32 D_0044A800[4];
extern s32 D_0044A810[4];
extern void *D_00651BD8[]; /* src/data/bss_0065.c: void *D_00651BD8[0x4] */
extern void *D_00651BE8[]; /* src/data/bss_0065.c: void *D_00651BE8[0x6] */
s32 func_00122ff8(s32);
s32 func_00141348(s32 *, s32 *);
void func_00246a70(s32, s32, s32, s32);
void func_00237018(void *, s32, s32);
void func_002370c8(void *);
void func_0023c7a0(void);
void func_0023cc80(s32 *);
void *memset(void *, s32, u32);
void func_0024afc0(void *, void *, void *);
s32 func_0011ef38(s32 (*)(void));
void func_0011ef10(s32, s32 (*)(void));

void func_0023c1b0(s32 *a, s32 x, s32 y) {
    s32 r[4];
    if (func_00122ff8(*a) != 0) {
        func_00141348(a, r);
        if (r[0] != 0 && r[0] != 2) {
            func_00246a70(x, y, r[1], r[2]);
        }
    }
}

Slot *func_0023c228(void) {
    s32 i;
    for (i = 0; i < 10; i++) {
        if (D_00651310[i].used == 0) {
            D_00651310[i].used = 1;
            D_00651310[i].x = 0;
            return &D_00651310[i];
        }
    }
    return 0;
}

void func_0023c5a8(s32 i) {
    D_00651310[i].used = 0;
}

s32 func_0023c8c8(void) {
    func_002370c8(&D_00650F40);
    D_00650F40.xe0 = 5;
    D_00650F40.x60 = 0x30003;
    func_00237018(&D_00650F40, 22, 1);
    D_00651204 = D_00351E10;
    D_00651200 = D_00351E10 + 1;
    func_0023c7a0();
    func_00237018(D_00651204, D_00651200 - D_00651204, 1);
    return 0;
}

s32 func_0023ceb0(void) {
    if (D_0044A820 == 0) {
        return 0;
    }
    func_0023cc80(&D_0044A820);
    return 0;
}

void func_0023cee8(void) {
    if (D_0044A820 == 0) {
        D_0044A820 = 1;
    }
}

void func_0023cf08(void) {
    if (D_0044A820 == 2) {
        D_0044A820 = 3;
    }
}

void func_0023cf30(void) {
    memset(&D_0044A820, 0, 8);
    func_0024afc0(D_0044A800, D_00651BD8, &D_00449990);
    func_0024afc0(D_0044A810, D_00651BE8, &D_00449990);
    if (func_0011ef38(func_0023ceb0) == 0) {
        func_0011ef10(0x28489, func_0023ceb0);
    }
}

s32 func_0023cfc8(void) {
    return D_0044A820 != 0;
}

void func_0023cfd8(void) {
    D_0044A820 = 0;
}

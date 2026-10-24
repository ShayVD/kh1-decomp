/* The counter (docs/modules.md "Session 46"), 0x00244960-0x00245238, nostrict
 * part.  A five-digit number (at most 99999) drawn at (25, 238) with its
 * actor's sprite (D_0065FD80: ten digit sprites for each of the five places,
 * D_00662300: the frame and two icons, the second for a value under 2).
 * func_00244a10 starts it for an actor with a value, or adds to the one shown;
 * func_00245090 is the draw hook (func_00245148, the set up, registers it and
 * builds the sprites from D_00459D40), with its drawing environment
 * D_0065FB30 (TEST_1 0x8000000048); func_00244f28 steps it (shown, held 60
 * frames, the value re-read from func_001ef7a0, out when the frame's
 * animation ends) and ends it when the actor is gone (func_001375d8).
 * Most likely the munny count; not proved by a boot. */
#include "common.h"
#include "data/types/nostrict_text_00240000_s7_w36.h" /* QW */
#include "data/pieces/D_004267F0.h"
#include "data/pieces/D_00426820.h"

typedef struct { s32 x, y, z, w; } I4;
typedef struct { u8 pad[0x60]; I4 c[4]; I4 p[4]; } Pkt;
typedef struct { u8 b[0xC0]; } Spr0C0;
typedef struct { u8 pad[0x60]; u64 unk60; u8 pad68[8]; u64 unk70; u8 pad78[0xE0 - 0x78]; u64 unkE0; u8 tail[0x160 - 0xE8]; } Q70;
typedef struct { u32 unk0; s32 unk4; s32 unk8; u8 padC[8]; void *unk14; } St;

Pkt D_0065FCA0 ALIGNED(32);
QW *D_0065FC90 ALIGNED(16);
Q70 D_0065FB30 ALIGNED(16);
QW *D_0065FC94 ALIGNED(4);
extern QW D_00351E10[]; /* the staging arena as quadwords */
extern St D_00662540; /* src/data/bss_0066.c: Hud D_00662540 */
extern Spr0C0 D_0065FD80[5][10]; /* src/data/bss_0065.c: Obj D_0065FD80[5][10] */
extern Spr0C0 D_00662300[]; /* src/data/bss_0066.c: u8 D_00662300[0x240] */
extern u8 D_00459D40[];
extern u8 D_0045B770[];
extern u8 D_0045B780[];
void func_00237018(void *, s32, s32);
void func_002370c8(void *);
void func_0024aa48(s32, Pkt *, s32);
s32 func_002388b8(Pkt *, s32, s32);
void func_0024ae90(Spr0C0 *);
s32 func_00244b10(s32, s32 *);
void func_00244960(void);
void *memset(void *, s32, u32);
void func_0024aac8(void *);
void func_0024af40(void *, void *, void *);
s32 func_0011ef38(void *);
void func_0011ef10(s32, void *);
s32 func_0024a1c0(void *);
s32 func_001ef7a0(void);
s32 func_00122ff8(void *);
s32 func_001375d8(void *);
void func_00244b00(void);
void func_00244d00(s32, s32);

void func_00244968(s32 a0, s32 a1, s32 x, s32 y) {
    s32 i;
    s32 *p;
    s32 dx, dy;
    func_0024aa48(a0, &D_0065FCA0, a1);
    dx = x * 16;
    dy = y * 16;
    p = &D_0065FCA0.p[0].y;
    for (i = 0; i < 4; i++) {
        p[-1] += dx;
        *p += dy;
        p += 4;
    }
    D_0065FC90 = (QW *)func_002388b8(&D_0065FCA0, 1, (s32)D_0065FC90);
}

void func_00244a10(void *a0, s32 a1) {
    s32 i, j;
    St *h = &D_00662540;
    if (h->unk0 == 0) {
        h->unk4 = a1;
        h->unk0 = 1;
        h->unk14 = a0;
        for (i = 0; i < 5; i++) {
            for (j = 0; j < 10; j++) func_0024ae90(&D_0065FD80[i][j]);
        }
        for (i = 0; i < 3; i++) func_0024ae90(&D_00662300[i]);
    } else {
        h->unk4 += a1;
    }
    h->unk8 = 0;
}

void func_00244be0(s32 a0, s32 y, s32 z) {
    s32 buf[5];
    s32 n, k, cy;
    n = func_00244b10(a0, buf);
    cy = y;
    for (k = 0; k < n; k++) {
        func_00244968((s32)&D_0065FD80[k][buf[5 - n + k]], (s32)D_00426820, cy, z);
        cy += 13;
    }
    cy += 2;
    func_00244968((s32)&D_00662300[0], (s32)D_004267F0, cy, z);
    func_00244968((s32)(a0 < 2 ? &D_00662300[1] : &D_00662300[2]), (s32)D_004267F0, cy, z);
}

void func_00244f28(void) {
    St *s = &D_00662540;
    s32 b = 0;
    s32 a = 0;
    switch (s->unk0) {
    case 0:
        return;
    case 1:
        s->unk0++;
        a = 1;
        break;
    case 3:
        if (++s->unk8 < 61) break;
    case 2:
        s->unk0++;
        break;
    case 4:
        s->unk0++;
        b = 1;
        s->unk4 = func_001ef7a0();
        break;
    case 5:
        if (func_0024a1c0(D_00662300) & 4) s->unk0++;
        break;
    case 6:
        s->unk0 = 0;
        break;
    }
    if (s->unk14 == NULL) return;
    if (func_00122ff8(s->unk14) == 0) return;
    if (func_001375d8(s->unk14)) {
        func_00244b00();
        return;
    }
    func_00244d00(a, b);
    if (s->unk4 > 99999) s->unk4 = 99999;
    func_00244be0(s->unk4, 25, 238);
}

s32 func_00245090(void) {
    func_002370c8(&D_0065FB30);
    D_0065FB30.unkE0 = 5;
    D_0065FB30.unk60 = 0x30003;
    D_0065FB30.unk70 = 0x8000000048ULL;
    func_00237018(&D_0065FB30, 0x16, 1);
    func_00244960();
    D_0065FC94 = D_00351E10;
    D_0065FC90 = D_00351E10 + 1;
    func_00244f28();
    func_00237018(D_0065FC94, D_0065FC90 - D_0065FC94, 1);
    return 0;
}

void func_00245148(void) {
    s32 i;
    memset(&D_00662540, 0, 0x18);
    func_0024aac8(D_00459D40);
    func_0024af40(D_0045B770, D_00662300, D_00459D40);
    for (i = 0; i < 5; i++) func_0024af40(D_0045B780, D_0065FD80[i], D_00459D40);
    if (func_0011ef38(func_00245090) == 0) func_0011ef10(0x28489, func_00245090);
}

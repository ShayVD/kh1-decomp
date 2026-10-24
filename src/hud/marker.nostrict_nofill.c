/* Markers over actors and the lock-on (docs/modules.md "Session 46"),
 * nostrict_nofill part.  func_0023c270 draws one marker over its actor (the
 * actor's position func_0012ec60 projected with func_00237a48, centred on
 * the sprite, skipped off screen); func_0023c5c8 draws the target's mark of
 * kind 1-4 the same way.  func_0023cb30 draws the sign's six sprites
 * (D_00651BE8 / D_00651BD8) at x 16, y 24, 65 or 80 (func_002485f0 bits)
 * with its own drawing environment D_006510A0; func_0023cc80 steps the sign
 * (shown, held, released, then fading out by D_002BBDFC / 6 a
 * frame). */
#include "common.h"
#include "data/bss_0064_mixed.h"
#include "data/pieces/D_00426820.h"
#include "data/pieces/D_004267F0.h"
#include "data/pieces/D_002E26C0.h"
#include "data/pieces/D_00426850.h"
#include "data/pieces/D_002BBDFC.h"

typedef struct { f32 x, y, z, w; } __attribute__((aligned(16))) V4;
typedef struct { s32 x, y, z, w; } __attribute__((aligned(16))) I4;
typedef struct { s32 x, y, z, w; } I4b;
typedef struct { u8 pad[0x60]; s32 c[4][4]; I4b p[4]; } Spr6;
typedef struct { u8 pad0[4]; f32 t; u8 pad8[8]; u8 sub[0xC8]; s32 d8[2]; } Ob;
typedef struct { s32 unk0; f32 unk4; } Ob4;
typedef struct { u8 pad[0x60]; u64 unk60; u8 pad68[0xE0-0x68]; u64 unkE0; u8 tail[0x160 - 0xE8]; } Q;

Q D_006510A0 ALIGNED(32);
extern u8 D_00351E10[];
extern Spr6 D_00651210; /* src/data/bss_0065.c: Pkt D_00651210 */
extern s32 D_00651200;
extern u8 *D_00651204;
extern f32 D_002BBDFC;
extern void *D_006512F0; /* src/data/bss_0065.c: u8 *D_006512F0 */
extern void *D_006512F4; /* src/data/bss_0065.c: u8 *D_006512F4 */
extern void *D_006512F8; /* src/data/bss_0065.c: u8 *D_006512F8 */
extern void *D_006512FC; /* src/data/bss_0065.c: u8 *D_006512FC */
extern void *D_00651BE8[];
extern void *D_00651BD8[];
void func_0024aa48(void *, Spr6 *, void *);
s32 func_002388b8(Spr6 *, s32, s32);
void func_002370c8(void *);
void func_00237018(void *, s32, s32);
void func_0024ac08(void *, s32 *);
s32 func_00122ff8(s32);
void func_0024ae00(void *);
void func_0024af00(void *);
void func_0012ec60(s32, s32, V4 *);
s32 func_00249580(V4 *);
f32 func_00237a48(I4 *, void *, V4 *, s32);
void func_00249558(I4 *, I4 *);
s32 func_002485f0(void);
void func_0023ca48(void *, void *, s32, s32, f32);

s32 func_0023c270(Ob *o) {
    I4 sc;
    s32 r[4];
    V4 v;
    s32 dx, dy, i;
    s32 *q;
    s32 *d = o->d8;
    if (func_00122ff8(d[0]) == 0) return 1;
    if (o->t == 0.0f) func_0024ae00(o->sub);
    o->t += D_002BBDFC;
    func_0012ec60(d[0], d[1], &v);
    if (func_00249580(&v)) return 0;
    func_00237a48(&sc, D_002E26C0, &v, 1);
    func_0024aa48(o->sub, &D_00651210, D_00426850);
    func_00249558(&sc, &sc);
    dx = sc.x;
    dy = sc.y;
    func_0024ac08(o->sub, r);
    dx -= r[2] / 2;
    dy -= r[3] / 2;
    for (i = 0; i < 4; i++) {
        q = &D_00651210.p[i].y;
        q[-1] += dx * 16;
        q[0] += dy * 16;
    }
    D_00651200 = func_002388b8(&D_00651210, 1, D_00651200);
    func_0024af00(o->sub);
    return 0;
}

void func_0023c5c8(s32 *d, s32 kind, s32 show) {
    I4 sc;
    s32 r[4];
    V4 v;
    s32 dx, dy, i;
    s32 *q;
    void *s = 0;
    if (func_00122ff8(d[0]) == 0) return;
    func_0012ec60(d[0], d[1], &v);
    if (func_00249580(&v)) return;
    func_00237a48(&sc, D_002E26C0, &v, 1);
    switch (kind) {
    case 1: s = D_006512F0; break;
    case 2: s = D_006512F8; break;
    case 3: s = D_006512F4; break;
    case 4: s = D_006512FC; break;
    }
    func_00249558(&sc, &sc);
    dx = sc.x;
    dy = sc.y;
    func_0024ac08(s, r);
    dx -= r[2] / 2;
    dy -= r[3] / 2;
    if (show) func_0024ae00(s);
    func_0024aa48(s, &D_00651210, D_00426850);
    for (i = 0; i < 4; i++) {
        q = &D_00651210.p[i].y;
        q[-1] += dx * 16;
        q[0] += dy * 16;
    }
    D_00651200 = func_002388b8(&D_00651210, 1, D_00651200);
    func_0024af00(s);
}

void func_0023cb30(Ob4 *o) {
    s32 c = 24;
    s32 i;
    if (func_002485f0() & 1) c = 65;
    if (func_002485f0() & 2) c = 80;
    func_002370c8(&D_006510A0);
    D_006510A0.unkE0 = 5;
    D_006510A0.unk60 = 0x30003;
    func_00237018(&D_006510A0, 0x16, 1);
    D_00651204 = D_00351E10;
    *(u8 **)&D_00651200 = D_00351E10 + 0x10;
    for (i = 0; i < 3; i++) func_0023ca48(D_00651BE8[i], D_00426820, 16, c, o->unk4);
    for (i = 0; i < 3; i++) func_0023ca48(D_00651BD8[i], D_004267F0, 16, c, o->unk4);
    func_00237018(D_00651204, (*(u8 **)&D_00651200 - D_00651204) >> 4, 1);
}

void func_0023cc80(Ob4 *o) {
    s32 i;
    switch (o->unk0) {
    case 1:
        o->unk4 = 1.0f;
        for (i = 0; i < 3; i++) func_0024ae00(D_00651BD8[i]);
        for (i = 0; i < 3; i++) func_0024ae00(D_00651BE8[i]);
        o->unk0++;
        break;
    case 2:
        for (i = 0; i < 3; i++) func_0024af00(D_00651BD8[i]);
        for (i = 0; i < 3; i++) func_0024af00(D_00651BE8[i]);
        break;
    case 3:
        for (i = 0; i < 3; i++) func_0024af00(D_00651BD8[i]);
        for (i = 0; i < 3; i++) func_0024af00(D_00651BE8[i]);
        o->unk4 = 1.0f;
        o->unk0++;
        break;
    case 4:
        for (i = 0; i < 3; i++) func_0024af00(D_00651BD8[i]);
        for (i = 0; i < 3; i++) func_0024af00(D_00651BE8[i]);
        o->unk4 -= D_002BBDFC * 0.16666666f;
        if (o->unk4 <= 0.0f) {
            o->unk4 = 0.0f;
            o->unk0 = 0;
        }
        break;
    }
    func_0023cb30(o);
}

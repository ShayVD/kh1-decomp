/* The party popups (docs/modules.md "Session 46"), 0x00243c10-0x00244960,
 * nostrict part.  D_00656510 (Tbl) holds up to five popups for each of three
 * party members (column g from func_0013c318 of the member's +0x130 +0x4C).
 * func_00244670 adds one for this frame (a, b: one or two values; the title
 * is message 295-304 by the member's +0x4C, the colours D_00459CA0 ... by
 * it); func_00244298 is the draw hook (func_00244500, the set up, registers it
 * and builds every popup's sprites from D_00458560): the popups are laid out
 * in columns of 16 lines from (16, 16), 200 apart, each sent on its own
 * with the drawing environment D_006562C0.  func_00244188 steps one (shown,
 * held 90 frames, fading by 1/8 a frame) and draws it (func_00243ef8).
 * func_00243c10 sends one sprite moved by (x, y) with the colour v and
 * alpha scale s.  What the popups say is not known (no boot). */
#include "common.h"
#include "data/types/nostrict_text_00240000_s7_w36.h" /* QW */
#include "data/types/nostrict_text_00240000_h75.h"
#include "data/pieces/D_004267F0.h"
#include "data/pieces/D_004267C0.h"

typedef struct { s32 x, y, z, w; } I4;
typedef struct { u8 pad[0x60]; I4 c[4]; I4 p[4]; } Pkt;
typedef struct { u8 pad[0x60]; u64 unk60; u8 pad68[0xE0 - 0x68]; u64 unkE0; u8 tail[0x160 - 0xE8]; } Pk;
typedef struct { u8 pad[0x4C]; u16 unk4C; } C130;
typedef struct { u8 pad[0x130]; C130 *unk130; } Chr2;

extern Tbl D_00656510;
Pk D_006562C0 ALIGNED(64);
extern QW *D_00656420; /* src/data/bss_0065.c: s32 D_00656420 */
QW *D_00656424 ALIGNED(4);
Pkt D_00656430 ALIGNED(16);
extern QW D_00351E10[]; /* the staging arena as quadwords */
extern u8 D_00458560[];
extern u8 D_00459C50[];
extern u8 D_00459C68[];
extern u8 D_00459C78[];
extern u8 D_00459C98[];
extern u8 D_00459CA0[];
extern u8 D_00459CB0[];
extern u8 D_00459CC0[];
extern u8 D_00459CD0[];
extern u8 D_00459CE0[];
extern u8 D_00459CF0[];
extern u8 D_00459D00[];
extern u8 D_00459D10[];
void func_00237018(void *, s32, s32);
void func_002370c8(void *);
void func_0024aa48(s32, Pkt *, s32);
s32 func_002388b8(Pkt *, s32, s32);
void *memset(void *, s32, u32);
void func_0024aac8(void *);
void func_0024af40(void *, void *, void *);
s32 func_0011ef38(void *);
void func_0011ef10(s32, void *);
void func_00243ef8(s32, void *, void *, void *, void *, void *, void *, s32, s32, s32, s32, s32, s32, void *, void *, f32);
s32 func_0013c318(u16);
s32 func_00147808(s32);

void func_00243c10(s32 a0, s32 a1, s32 x, s32 y, s32 *v, f32 s) {
    s32 i;
    s32 *p;
    s32 dx, dy;
    func_0024aa48(a0, &D_00656430, a1);
    dx = x * 16;
    dy = y * 16;
    p = &D_00656430.p[0].y;
    for (i = 0; i < 4; i++) {
        p[-1] += dx;
        *p += dy;
        p += 4;
    }
    for (i = 0; i < 4; i++) {
        D_00656430.c[i].x = v[0];
        D_00656430.c[i].y = v[1];
        D_00656430.c[i].z = v[2];
        D_00656430.c[i].w = D_00656430.c[i].w * s;
    }
    D_00656420 = (QW *)func_002388b8(&D_00656430, 1, (s32)D_00656420);
}

void func_00244188(Ent *o) {
    s32 f = 0;
    switch (o->unk0) {
    case 0:
        return;
    case 1:
        f = 1;
        o->unk0++;
        break;
    case 2:
    case 4:
        o->unk0++;
        break;
    case 3:
        if (++o->unkC >= 91) o->unk0++;
        break;
    case 5:
        o->unk9F0 -= 0.125f;
        if (o->unk9F0 < 0.0f) {
            o->unk9F0 = 0.0f;
            o->unk0++;
        }
        break;
    case 6:
        o->unk0 = 0;
        break;
    }
    func_00243ef8(f, o->unk30, o->unk330, o->unk4B0, o->unk930, D_004267C0, D_004267F0, o->unk10, o->unk14,
                  o->unk18, o->unk24, o->unk1C, o->unk20, o->unk9F4, o->unk9F8, o->unk9F0);
}

s32 func_00244298(void) {
    s32 i, j, n;
    s32 x;
    s32 left;
    s32 px;
    s32 py;
    Ent *e;
    px = 16;
    py = 16;
    x = 200;
    left = 16;
    D_00656510.frame++;
    func_002370c8(&D_006562C0);
    D_006562C0.unkE0 = 5;
    D_006562C0.unk60 = 0x30003;
    func_00237018(&D_006562C0, 22, 1);
    for (i = 0; i < 3; i++) {
        for (j = 0; j < D_00656510.cnt[i]; j++) {
            e = &D_00656510.e[i][j];
            D_00656424 = D_00351E10;
            D_00656420 = D_00351E10 + 1;
            if (e->unk0 == 0) continue;
            n = e->unk18;
            if (left < n + 1) {
                px = x + 16;
                x += 200;
                py = 16;
                left = 16;
            }
            left = left - n - 1;
            e->unk14 = py;
            e->unk10 = px;
            py = py + n * 22 + 22;
            func_00244188(e);
            func_00237018(D_00656424, D_00656420 - D_00656424, 1);
        }
    }
    return 0;
}

void func_00244500(void) {
    s32 i, j;
    Ent *e;
    memset(&D_00656510, 0, sizeof(Tbl));
    func_0024aac8(D_00458560);
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 5; j++) {
            e = &D_00656510.e[i][j];
            func_0024af40(D_00459C50, e->unk30, D_00458560);
            func_0024af40(D_00459C68, e->unk330, D_00458560);
            func_0024af40(D_00459C78, e->unk4B0, D_00458560);
            func_0024af40(D_00459C98, e->unk930, D_00458560);
        }
    }
    if (func_0011ef38(func_00244298) == 0) func_0011ef10(0x29811, func_00244298);
}

void func_00244670(Chr2 *o, s32 a, s32 b) {
    s32 g = -1;
    s32 k, f, n;
    Ent *e;
    k = func_0013c318(o->unk130->unk4C);
    switch (k) {
    case 0: g = 0; break;
    case 1: g = 1; break;
    case 2: g = 2; break;
    }
    f = a != 0;
    if (b) f++;
    if (D_00656510.stamp[g] != D_00656510.frame) D_00656510.cnt[g] = 0;
    if (D_00656510.cnt[g] == 5) return;
    D_00656510.stamp[g] = D_00656510.frame;
    e = &D_00656510.e[g][D_00656510.cnt[g]];
    D_00656510.cnt[g]++;
    e->unk8 = k;
    e->unk18 = f;
    e->unk1C = a;
    e->unk20 = b;
    e->unk9F0 = 1.0f;
    e->unk0 = 1;
    e->unkC = 0;
    switch (o->unk130->unk4C) {
    case 0: e->unk9F4 = D_00459CA0; e->unk9F8 = D_00459CE0; break;
    case 1: e->unk9F4 = D_00459CB0; e->unk9F8 = D_00459CF0; break;
    case 2: e->unk9F4 = D_00459CC0; e->unk9F8 = D_00459D00; break;
    default: e->unk9F4 = D_00459CD0; e->unk9F8 = D_00459D10; break;
    }
    switch (o->unk130->unk4C) {
    case 0: n = 295; break;
    case 1: n = 296; break;
    case 2: n = 297; break;
    case 3: n = 298; break;
    case 4: n = 299; break;
    case 5: n = 300; break;
    case 6: n = 301; break;
    case 7: n = 302; break;
    case 8: n = 303; break;
    case 9: n = 304; break;
    default: return;
    }
    e->unk24 = func_00147808(n);
}

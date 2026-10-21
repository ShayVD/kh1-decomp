/* 0x00230000-0x0024FFFF game code by hand (batch 49), delay-slot filling off. */
#include "common.h"
#include "data/bss_0064.h"

void func_00239860(s32, s32, s32, s32, f32, s32, s32, s32);
void func_00239b90(s32, s32, s32, s32, f32, s32, s32, s32);
void func_0024ae00(s32);
void func_0024af00(s32);

void func_00239a80(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6, f32 f) {
    if (a0 != 0) {
        func_0024ae00(a1);
        if (a2 != 0) func_0024ae00(a2);
    }
    func_0024af00(a1);
    if (a2 != 0) func_0024af00(a2);
    func_00239860(a1, a3, a4, a5, f, 0, a6, 0);
    if (a2 != 0) func_00239860(a1, a3, a4, a5, f, 0, a6, 0);
}

void func_00239d20(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6, f32 f) {
    if (a0 != 0) {
        func_0024ae00(a1);
        if (a2 != 0) func_0024ae00(a2);
    }
    func_0024af00(a1);
    if (a2 != 0) func_0024af00(a2);
    func_00239b90(a1, a3, a4, a5, f, 0, a6, 0);
    if (a2 != 0) func_00239b90(a1, a3, a4, a5, f, 0, a6, 0);
}

typedef struct { u8 pad[0x60]; u64 unk60; u8 pad68[0xE0-0x68]; u64 unkE0; u8 tail[0x160 - 0xE8]; } Q;
Q D_00648790 ALIGNED(16);
extern u8 D_00351E10[];
extern u8 *D_006488F0; /* src/data/bss_0064.c: s32 D_006488F0 */
extern u8 *D_006488F4;
void func_002370c8(void *);
void func_00237018(void *, s32, s32);
void func_0023a490(s32, s32, s32, s32, f32);

void func_0023a608(s32 a0, s32 a1, s32 a2, s32 a3, f32 f) {
    func_002370c8(&D_00648790);
    D_00648790.unkE0 = 5;
    D_00648790.unk60 = 0x30003;
    func_00237018(&D_00648790, 0x16, 1);
    D_006488F4 = D_00351E10;
    D_006488F0 = D_00351E10 + 0x10;
    func_0023a490(a0, a1, a2, a3, f);
    if (f != 0.0f) {
        func_00237018(D_006488F4, (D_006488F0 - D_006488F4) >> 4, 1);
    }
}
typedef struct { s32 unk0; u32 unk4; u8 pad8[8]; s32 unk10; u8 pad14[0x10]; u8 unk24[1]; } Spr;
extern Spr *D_002E3170[];

void func_0023a720(void) {
    Spr **pp;
    Spr *p;
    s32 i;
    for (pp = D_002E3170; *pp != 0; pp++) {
        p = *pp;
        if (pp[1] == 0) {
            for (i = 0; i < p->unk10; i++) {
                if (p->unk4 & (1 << i)) p->unk24[i] = 0x73;
                else p->unk24[i] = 0xE6;
            }
        } else {
            for (i = 0; i < p->unk10; i++) p->unk24[i] = 0x73;
        }
    }
}
extern f32 D_002BBDFC;

void func_0023a7e8(void) {
    Spr **pp;
    Spr *p;
    s32 i, v;
    for (pp = D_002E3170; *pp != 0; pp++) {
        p = *pp;
        if (pp[1] == 0) {
            for (i = 0; i < p->unk10; i++) {
                if (p->unk4 & (1 << i)) {
                    v = p->unk24[i]; v = v - D_002BBDFC * 32.0f;
                    if (v < 0x73) v = 0x73;
                    p->unk24[i] = v;
                } else {
                    v = p->unk24[i]; v = v + D_002BBDFC * 32.0f;
                    if (v > 0xE6) v = 0xE6;
                    p->unk24[i] = v;
                }
            }
        }
    }
}
typedef struct { u8 pad[0x7C]; f32 unk7C; f32 unk80; } Cam;
extern Cam D_00449908;

void func_0023b4b8(s32 a) {
    switch (a) {
    case 0:
        D_00449908.unk7C = 1.0f;
        D_00449908.unk80 = -0.0999999940395355224609375f;
        break;
    case 1:
        D_00449908.unk80 = 0.0999999940395355224609375f;
        D_00449908.unk7C = 0.0f;
        break;
    case 2:
        D_00449908.unk7C = 1.0f;
        D_00449908.unk80 = 0.0f;
        break;
    case 3:
        D_00449908.unk80 = 0.0f;
        D_00449908.unk7C = 0.0f;
        break;
    }
}
typedef struct { s32 unk0; u8 pad[0xDC]; } Ent0E0;
Q D_00650DE0 ALIGNED(32);
extern u8 *D_00651200; /* src/data/bss_0065.c: s32 D_00651200 */
extern u8 *D_00651204;
extern Ent0E0 D_00651310[]; /* src/data/bss_0065.c: Slot D_00651310[10] */
void func_0023c270(Ent0E0 *);

s32 func_0023c400(void) {
    s32 i;
    func_002370c8(&D_00650DE0);
    D_00650DE0.unkE0 = 5;
    D_00650DE0.unk60 = 0x30003;
    func_00237018(&D_00650DE0, 0x16, 1);
    D_00651204 = D_00351E10;
    D_00651200 = D_00351E10 + 0x10;
    for (i = 0; i < 10; i++) {
        if (D_00651310[i].unk0 != 0) func_0023c270(&D_00651310[i]);
    }
    func_00237018(D_00651204, (D_00651200 - D_00651204) >> 4, 1);
    return 0;
}
extern s32 D_00651BD0;
typedef struct { s32 unk0; s32 unk4; s32 unk8; } Hdr;
extern Hdr D_00449990;
extern u8 *D_006512F0;
extern u8 *D_006512F4;
extern u8 *D_006512F8;
extern u8 *D_006512FC;
extern u8 *D_00651300;
void *memset(void *, s32, u32);
void func_0024aac8(void *);
s32 func_0011ef38(void *);
void func_0011ef10(s32, void *);
void func_0023c8c8(void);
void func_0023cf30(void);

void func_0023c968(void) {
    u8 *b;
    memset(D_00651310, 0, 0x8C0);
    D_00651BD0 = 0;
    func_0024aac8(&D_00449990);
    b = (u8 *)&D_00449990 + D_00449990.unk8;
    D_006512F8 = b + 0xC0;
    D_006512F4 = b;
    D_006512F0 = b + 0x180;
    D_006512FC = b + 0x240;
    D_00651300 = b + 0x300;
    if (func_0011ef38(func_0023c8c8) == 0) func_0011ef10(0x28489, func_0023c8c8);
    if (func_0011ef38(func_0023c400) == 0) func_0011ef10(0x28489, func_0023c400);
    func_0023cf30();
}

#include "data/types/nofill_text_00230000_h49.h"
extern Pkt D_00651210;
void func_0024aa48(s32, Pkt *, s32);
s32 func_002388b8(Pkt *, s32, s32);
void func_0023ca48(s32 a0, s32 a1, s32 x, s32 y, f32 s) {
    s32 i;
    s32 *p;
    s32 dx, dy;
    func_0024aa48(a0, &D_00651210, a1);
    dx = x * 16;
    dy = y * 16;
    p = &D_00651210.p[0].y;
    for (i = 0; i < 4; i++) {
        p[-1] += dx;
        *p += dy;
        p += 4;
    }
    for (i = 0; i < 4; i++) {
        D_00651210.c[i].w = D_00651210.c[i].w * s;
    }
    D_00651200 = (u8 *)func_002388b8(&D_00651210, 1, (s32)D_00651200);
}
extern u8 D_00454558[], D_00454570[], D_00454580[], D_00454598[], D_004545B0[], D_004545C8[], D_004545E0[], D_004545F8[];
void func_0024afc0(void *, void *, s32);

void func_0023cfe8(u8 *o, s32 k, s32 a) {
    switch (k) {
    case 0:
        break;
    case 1:
        func_0024afc0(D_00454558, o, a);
        func_0024afc0(D_004545F8, o + 0x14, a);
        break;
    case 2:
        func_0024afc0(D_004545B0, o + 0x18, a);
        func_0024afc0(D_004545E0, o + 0x28, a);
        func_0024afc0(D_004545C8, o + 0x3C, a);
        break;
    case 3:
        func_0024afc0(D_00454558, o, a);
        func_0024afc0(D_004545F8, o + 0x14, a);
        func_0024afc0(D_00454570, o + 0x18, a);
        func_0024afc0(D_00454580, o + 0x28, a);
        func_0024afc0(D_00454598, o + 0x3C, a);
        break;
    }
}
Pkt D_00651D70 ALIGNED(16);

s32 func_0023d700(s32 a0, s32 a1, s32 x, s32 y, s32 q, f32 s) {
    s32 i;
    s32 *p;
    s32 dx, dy;
    func_0024aa48(a0, &D_00651D70, a1);
    dx = x * 16;
    dy = y * 16;
    p = &D_00651D70.p[0].y;
    for (i = 0; i < 4; i++) {
        p[-1] += dx;
        *p += dy;
        p += 4;
    }
    for (i = 0; i < 4; i++) {
        D_00651D70.c[i].w = D_00651D70.c[i].w * s;
    }
    return func_002388b8(&D_00651D70, 1, q);
}

/* needs make: uses rodata */

extern s32 D_002E31B0;
extern u32 D_002E31B8;
extern s32 D_002E31BC;
extern s32 D_00651BD0;
void func_0023c1b0(s32 *, s32, s32);
void func_0023c5c8(s32 *, s32, s32);
void func_0023cee8(void);
void func_0023cf08(void);

void func_0023c7a0(void) {
    s32 f = 0;
    s32 m = 0;
    s32 *p;
    s32 c;
    switch (D_002E31B8) {
    case 0:
        m = 0;
        break;
    case 3:
        if (D_002E31B0 == 0) { m = 0; break; }
        f = 1;
        func_0023cee8();
        switch (D_002E31BC) {
        case 0: m = 1; break;
        case 1: m = 2; break;
        case 2: m = 3; break;
        }
        break;
    case 1:
    case 2:
    case 4:
        m = 4;
        break;
    }
    p = &D_00651BD0;
    c = *p != m;
    if (m != 0) {
        func_0023c5c8(&D_002E31B0, m, c);
        func_0023c1b0(&D_002E31B0, 0, 0);
    }
    if (f == 0) func_0023cf08();
    *p = m;
}
#include "data/data_002E.h"
#include "data/data_0045.h"
#include "data/pieces/D_002BBDFC.h"

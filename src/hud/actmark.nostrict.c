/* The mark over an actor (docs/modules.md "Session 46"), nostrict part.
 * func_002455c0 is the draw hook (func_002456e8, the set up, registers it and
 * takes the three kinds' sprites D_006627C8 / D_006627D0 / D_006627D8 from
 * D_0045B7B0): it steps the mark (shown, fading by 0.2 a frame) and draws it
 * (func_00245508, drawing environment D_00662560) 54 pixels above the
 * actor's point 0x8004 (func_001315c0) when it is on screen
 * (func_002453e8, func_00245300). */
#include "common.h"
#include "data/types/nostrict_text_00240000_s7_w36.h" /* QW */
#include "data/pieces/D_00431D20.h"
#include "data/pieces/D_002E26C0.h"

typedef struct { s32 x, y, z, w; } I4;
typedef struct { u8 pad[0x60]; I4 c[4]; I4 p[4]; } Pkt;
typedef struct { u8 pad[0x60]; u64 unk60; u8 pad68[0xE0-0x68]; u64 unkE0; u8 tail[0x160 - 0xE8]; } Q;
typedef struct { s32 unk0; s32 unk4; u32 unk8; f32 unkC; s32 unk10; s32 unk14; } Msg3;
typedef struct { s32 x, y; } XY;

Pkt D_006626D0 ALIGNED(16);
QW *D_006626C0 ALIGNED(16);
s32 D_006627C8 ALIGNED(8);
s32 D_006627D0 ALIGNED(16);
s32 D_006627D8 ALIGNED(8);
Q D_00662560 ALIGNED(32);
QW *D_006626C4 ALIGNED(4);
extern Msg3 D_006627B0;
extern QW D_00351E10[]; /* the staging arena as quadwords */
extern u8 D_0045B7B0[], D_0045BC00[];
void func_00237018(void *, s32, s32);
void func_0024aa48(s32, Pkt *, s32);
s32 func_002388b8(Pkt *, s32, s32);
void func_002370c8(void *);
void *memset(void *, s32, u32);
void func_0024aac8(void *);
s32 func_0011ef38(void *);
void func_0011ef10(s32, void *);
void func_0024ae00(void *);
void func_0024af00(void *);
void func_001315c0(s32, s32, void *, f32);
s32 func_00249580(void *);
void func_00237a48(XY *, void *, void *, s32);
void func_00249558(XY *, XY *);
void func_0024afc0(void *, void *, void *);
s32 func_001375d8(s32);
s32 func_00122ff8(s32);
void func_002452c8(void);
void func_002452f0(void);

void func_00245300(s32 a0, s32 a1, s32 x, s32 y, f32 s) {
    s32 i;
    s32 *p;
    s32 dx, dy;
    func_0024aa48(a0, &D_006626D0, a1);
    dx = x * 16;
    dy = y * 16;
    p = &D_006626D0.p[0].y;
    for (i = 0; i < 4; i++) {
        p[-1] += dx;
        *p += dy;
        p += 4;
    }
    for (i = 0; i < 4; i++) {
        D_006626D0.c[i].w = D_006626D0.c[i].w * s;
    }
    D_006626C0 = (QW *)func_002388b8(&D_006626D0, 1, (s32)D_006626C0);
}

void func_002453e8(s32 a0, f32 f) {
    Msg3 *m = &D_006627B0;
    s32 v = 0;
    u8 buf[16];
    XY r;
    switch (m->unk0) {
    case 0:
        v = D_006627C8;
        break;
    case 1:
        v = D_006627D0;
        break;
    case 2:
        v = D_006627D8;
        break;
    }
    if (a0 != 0) func_0024ae00((void *)v);
    func_0024af00((void *)v);
    func_001315c0(m->unk4, 0x8004, buf, 0.0f);
    if (func_00249580(buf) == 0) {
        func_00237a48(&r, D_002E26C0, buf, 1);
        func_00249558(&r, &r);
        r.y -= 54;
        func_00245300(v, (s32)D_00431D20, r.x, r.y, f);
    }
}

void func_00245508(s32 a0, f32 f) {
    func_002370c8(&D_00662560);
    D_00662560.unkE0 = 5;
    D_00662560.unk60 = 0x30003;
    func_00237018(&D_00662560, 0x16, 1);
    D_006626C4 = D_00351E10;
    D_006626C0 = D_00351E10 + 1;
    func_002453e8(a0, f);
    func_00237018(D_006626C4, D_006626C0 - D_006626C4, 1);
}

s32 func_002455c0(void) {
    Msg3 *m = &D_006627B0;
    s32 f = 0;
    switch (m->unk8) {
    case 0:
        return 0;
    case 1:
        f = 1;
        m->unk8++;
        break;
    case 2:
    case 4:
        m->unk8++;
        break;
    case 3:
        break;
    case 5:
        m->unkC -= 0.2f;
        if (m->unkC < 0.0f) {
            m->unkC = 0.0f;
            m->unk8++;
        }
        break;
    case 6:
        m->unk8 = 0;
        return 0;
    }
    if (m->unk4 == 0) return 0;
    if (func_00122ff8(m->unk4) == 0) return 0;
    if (m->unk14 == 0 && func_001375d8(m->unk4) != 0) {
        func_002452f0();
        return 0;
    }
    m->unk14 = 0;
    func_00245508(f, m->unkC);
    if (m->unk10 == 0) func_002452c8();
    m->unk10 = 0;
    return 0;
}

void func_002456e8(void) {
    s32 buf[4];
    memset(&D_006627B0, 0, 0x18);
    D_006627B0.unk8 = 0;
    func_0024aac8(D_0045B7B0);
    func_0024afc0(D_0045BC00, buf, D_0045B7B0);
    D_006627C8 = buf[2];
    D_006627D0 = buf[1];
    D_006627D8 = buf[0];
    if (func_0011ef38(func_002455c0) == 0) func_0011ef10(0x28489, func_002455c0);
}

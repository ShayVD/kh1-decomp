/* Hand-matched functions (worker b03). */
#include "common.h"

typedef struct { u8 pad[0xcc]; f32 xcc; } B3Mv;
typedef struct B3Ob {
    u32 x0;
    s32 x4;
    u8 pad08[0x20 - 0x8];
    f32 x20[4];
    u8 pad30[0x3c - 0x30];
    f32 x3c;
    u8 pad40[0x6c - 0x40];
    B3Mv *x6c;
    s32 x70;
    u8 pad74[0x88 - 0x74];
    u32 x88;
    u8 pad8c[0x144 - 0x8c];
    s32 x144;
    u8 pad148[0x150 - 0x148];
    f32 x150;
    u8 pad154[0x164 - 0x154];
    s32 x164;
    u8 pad168[0x280 - 0x168];
    f32 x280;
    u8 pad284[0x370 - 0x284];
    u64 x370;
    s32 x378;
    u8 pad37c[0x3d0 - 0x37c];
    s32 x3d0;
    u8 pad3d4[0x3e4 - 0x3d4];
    f32 x3e4;
    u16 x3e8;
} B3Ob;

extern f32 D_002BBDFC;
extern f32 D_002C58B0[4];
extern u32 D_002C5958;
f32 func_001216d8(f32, f32, f32);
s32 func_00123368(B3Ob *);
s32 func_0012ba98(s32);
void func_00130340(B3Ob *o, s32 a, f32 f);
void func_00130398(B3Ob *o, s32 a, f32 f);
void *func_00130578(B3Ob *, s32, f32);
void func_00135658(B3Ob *);
s32 func_00137618(B3Ob *);
void func_00137688(B3Ob *, f32);
void func_00138900(B3Ob *);
void func_00138948(B3Ob *);
s32 func_00138988(B3Ob *);
void func_001395d8(B3Ob *);
void func_00139da8(B3Ob *);
void func_00139ff8(B3Ob *);
void func_002675a8(f32 *, f32 *);

void func_0013a0f0(B3Ob *o) {
    s32 v;
    o->x370 &= ~0x2000000000000000ULL;
    if (o->x0 & 0x400) {
        switch (o->x70) {
        case 0:
            switch (o->x378) {
            case 2:
            case 3:
                func_00139ff8(o);
                o->x370 |= 0x2000000000000000ULL;
                break;
            }
            break;
        case 2:
        case 3:
            func_00130340(o, 6, 8.0f);
            break;
        case 4:
            if (o->x378 == 5) {
                func_00130398(o, (o->x3d0 + 7) | 0x1000000, 0.0f);
                func_00130578(o, 0x40000000, 8.0f);
                func_002675a8(o->x20, D_002C58B0);
            }
            break;
        }
    }
    if (func_00138988(o) == 4) {
        o->x3e4 -= D_002BBDFC;
        if (o->x280 <= 2.0f || o->x3e4 <= 0.0f) {
            func_00138900(o);
            func_00130398(o, o->x164 + 1, 8.0f);
            func_00130578(o, 0x40000000, 8.0f);
        }
    } else if (o->x164 == 0x43) {
        o->x3e4 -= D_002BBDFC;
        if (o->x3e4 <= 0.0f) {
            func_00138900(o);
            func_00130398(o, 0x44, 0.0f);
            func_00130578(o, 0x40000000, 8.0f);
        }
    }
    func_001395d8(o);
    if (func_00123368(o)) {
        func_00139da8(o);
    } else {
        func_00135658(o);
    }
    if (o->x88 & 1) return;
    if (!((D_002C5958 >> 21) & 1) && func_00137618(o)) {
        if (o->x88 & 2) {
            func_00138948(o);
            func_00130340(o, 0x1000042, 8.0f);
            func_00130578(o, 0x43, 0.0f);
        } else if (((s32)(o->x370 >> 48) & 1) && o->x144) {
            func_00138900(o);
            if (func_0012ba98(o->x144) < 0) o->x144 = 0;
        }
    }
    if (!((s32)(o->x370 >> 44) & 1)) {
        func_00137688(o, func_001216d8(o->x3c, o->x150, o->x6c->xcc));
    }
    if (o->x3e8 && !(o->x0 & 4)) o->x3e8 = 0;
}

extern f32 D_002BBDFC;
extern f32 D_002C58D0[4];
extern u32 D_002C5958;
extern f32 D_002E2780[4];
extern f32 D_002E2790[4];
extern f32 D_00304B20[4];
extern f32 D_00304B30[4];
f32 D_0052AD04 ALIGNED(4);
f32 D_0052AD08 ALIGNED(8);
f32 D_0052AD0C ALIGNED(4);
f32 D_0052AD10[4] ALIGNED(16);
f32 D_0052AD20[4] ALIGNED(16);
f32 D_0052AD30[4] ALIGNED(16);
f32 D_0052AD40[4] ALIGNED(16);
f32 D_0052AD50 ALIGNED(16);
extern u8 *D_0052AE38;
f32 atan2f(f32, f32);
f32 cosf(f32);
f32 func_00120bf8(f32 *);
f32 func_00120c18(f32 *);
f32 func_00120c88(f32);
void func_00121fc4(f32 *, f32 *);
void func_001625c8(void *, f32 *);
f32 func_00176850(void);
void func_002672f8(f32 *, void *, f32 *);
void func_002673b8(f32 *, f32 *);
void func_002674f0(f32 *, f32 *, f32 *, f32);
void func_00267518(f32 *, f32 *, f32 *);
void func_00267530(f32 *, f32 *, f32 *);
void func_00267560(f32 *, f32 *, f32);
void func_00267810(f32 *, f32 *, f32);

s32 func_0013abf8(u16 *o) {
    f32 a[4];
    f32 b[4];
    f32 rm[16];
    f32 m[16];
    f32 t, r;

    if (!((D_002C5958 >> 20) & 1)) return 4;
    if (*o & 0x10) {
        func_001625c8(D_0052AE38 + 0xd0, m);
        D_002E2780[3] = D_002E2790[3] = 1.0f;
        func_002672f8(D_0052AD20, m, D_002E2780);
        func_002672f8(D_0052AD30, m, D_002E2790);
        func_00267530(D_0052AD10, D_00304B30, D_0052AD20);
        D_0052AD08 = func_00120bf8(D_0052AD10);
        func_00267530(D_0052AD10, D_0052AD30, D_0052AD20);
        func_002673b8(D_0052AD10, D_0052AD10);
        func_00267560(D_0052AD10, D_0052AD10, D_0052AD08);
        func_00267518(D_0052AD30, D_0052AD10, D_0052AD20);
        func_00267530(D_0052AD40, D_0052AD20, D_0052AD30);
        D_0052AD40[1] = 0.0f;
        func_00121fc4(D_0052AD40, D_0052AD40);
        D_0052AD08 = D_0052AD40[3];
        D_0052AD40[3] = 1.0f;
        func_00267530(D_0052AD10, D_00304B20, D_00304B30);
        D_0052AD0C = func_00120c18(D_0052AD10) - D_0052AD08;
        r = atan2f(D_0052AD20[0] - D_0052AD30[0], D_0052AD20[2] - D_0052AD30[2]);
        D_0052AD04 = func_00120c88(atan2f(D_00304B20[0] - D_00304B30[0], D_00304B20[2] - D_00304B30[2]) - r);
        if (func_00176850() < 0.5f) {
            if (D_0052AD04 < 0.0f) {
                D_0052AD04 = D_0052AD04 + 6.2831855f;
            } else {
                D_0052AD04 = D_0052AD04 - 6.2831855f;
            }
        }
        if (func_00176850() < 0.5f) {
            D_0052AD04 = D_0052AD04 + 0.5235987901687622f;
        } else {
            D_0052AD04 = D_0052AD04 - 0.5235987901687622f;
        }
        D_0052AD50 = 40.0f;
    }
    D_0052AD50 -= D_002BBDFC;
    t = D_0052AD50 / 40.0f;
    if (t < 0.0f) t = 0.0f;
    t = (cosf(t * 3.1415928f) + 1.0f) * 0.5f;
    func_002674f0(b, D_00304B30, D_0052AD30, t);
    func_00267810(rm, D_002C58D0, func_00120c88(D_0052AD04 * t));
    func_002672f8(D_0052AD10, rm, D_0052AD40);
    func_00267560(D_0052AD10, D_0052AD10, D_0052AD08 + D_0052AD0C * t);
    func_00267518(a, b, D_0052AD10);
    a[3] = 1.0f;
    b[3] = 1.0f;
    a[1] = D_00304B20[1] * t + D_0052AD20[1] * (1.0f - t);
    func_002672f8(D_002E2780, D_0052AE38 + 0xd0, a);
    func_002672f8(D_002E2790, D_0052AE38 + 0xd0, b);
    return 0;
}

typedef struct {
    u8 x0, x1, x2, x3, x4, x5, x6, x7;
    u8 x8[16];
    u8 x18;
    u8 x19[8];
    u8 x21;
    u8 x22[16];
    u8 x32, x33, x34, x35;
    u16 x36, x38, x3a;
    s32 x3c;
    u8 x40[48];
    u8 x70[4];
} B3SvEnt;
typedef struct {
    B3SvEnt e[10];
    u8 x488[2];
    u8 x48a;
    u8 x48b[3];
    u8 x48e[7];
    u8 x495[256];
    u8 x595[48];
    u8 x5c5[0x7cc - 0x5c5];
    u8 x7cc[7];
    u8 x7d3[0x840 - 0x7d3];
    u8 x840[3];
} B3SvSub;
typedef struct {
    s32 x0;
    B3SvSub b;
} B3Sv;
typedef struct {
    u8 x0, x1, x2, x3, x4;
    u8 x5[16];
    u8 x15, x16;
} B3SvSrc;
extern B3Sv *D_00304BE8;
extern s32 D_00304BC0[10];
extern u16 D_00351530[512];
B3Sv *func_00232cc0(s32);
B3SvSrc *func_001477c8(s32);
void func_0013c9e0(s32, s32);
void func_0013c638(s32, s32);

void func_0013cb98(void) {
    B3Sv *s;
    B3SvSrc *d;
    B3SvEnt *e;
    B3SvSub *b;
    s32 i, j;

    B3Sv **pp = &D_00304BE8;
    s = func_00232cc0(0);
    *pp = s;
    s->x0 = 5;
    for (i = 0; i < 256; i++) s->b.x495[i] = 0;
    for (i = 0; i < 10; i++) {
        s->b.e[i].x32 = D_00304BC0[i];
        func_0013c9e0(D_00304BC0[i], 12);
    }
    s->b.x48a = 0;
    for (i = 1; i < 4; i++) (&s->b.x48a)[i] = -1;
    for (i = 0; i < 48; i++) s->b.x595[i] = 0;
    b = &s->b;
    e = b->e;
    d = func_001477c8(14808);
    for (i = 0; i < 10; i++) {
        e->x34 = 1;
        e->x0 = 1;
        e->x1 = e->x2 = d->x0;
        e->x3 = e->x4 = d->x1;
        e->x38 = 0;
        e->x5 = d->x2;
        e->x6 = d->x3;
        e->x7 = d->x4;
        e->x18 = d->x15;
        e->x21 = d->x16;
        e->x3c = 0;
        for (j = 0; j < 16; j++) e->x8[j] = d->x5[j];
        for (j = 0; j < 8; j++) e->x19[j] = 0;
        for (j = 0; j < 16; j++) e->x22[j] = 0;
        for (j = 0; j < 48; j++) e->x40[j] = 0;
        e++;
        d++;
    }
    for (i = 0; i < 512; i++) func_0013c638(i, D_00351530[i] & 1);
    for (i = 0; i < 7; i++) s->b.x7cc[i] = -1;
    for (i = 0; i < 7; i++) D_00304BE8->b.x48e[i] = 1;
    for (i = 0; i < 3; i++) b->x840[i] = -1;
}

#include "common.h"
#include "data/types/nostrict_text_00110000_h53.h"
typedef struct {
    u8 pad0[0x1c];
    f32 p[4];
    f32 q[3];
    f32 r[3];
    u8 pad44[0x10];
    s8 x54;
    u8 pad55[3];
    u8 x58;
    u8 pad59;
    u8 x5a;
} Info3b;
typedef struct {
    u8 pad0[4];
    s32 x4;
    u8 x6pad[0];
} Dummy3b;
typedef struct Obj3b {
    u8 pad0[4];
    s32 x4;
    u8 pad8[0x38];
    f32 x40[3];
    u8 pad4c[0xe4];
    Info3b *info;
} Obj3b;
extern void *D_002E26A0[3];
void func_00113138(V53 *);
void func_00113270(V53 *);
void func_001133a0(V53 *);
void func_00123ab8(s32, f32 *);
void func_0014eab0(Obj3b *, V53 *);
void func_0014eb60(Obj3b *, V53 *);
void func_00267530(V53 *, V53 *, V53 *);
void func_002675a8(void *, void *);
void func_0014e668(V53 *, s32, V53 *, f32, f32);
float atan2f(float, float);

void func_00123b40(Obj3b *o, V53 *out) {
    Info3b *in = o->info;
    f32 t[3];
    V53 d;
    s32 k;
    switch (in->x54) {
    case 0:
        func_00113138(out);
        return;
    case 1:
        if (D_002E26A0[1] == o) {
            func_00113270(out);
        } else {
            func_001133a0(out);
        }
        return;
    }
    k = ((u8 *)o)[6];
    if (k < 6) {
        if (k >= 4) {
            out->x = in->p[0];
            out->y = in->p[1];
            out->z = in->p[2];
            out->w = 0.0f;
            o->x40[0] = in->q[0];
            o->x40[1] = in->q[1];
            o->x40[2] = in->q[2];
            t[0] = in->r[0];
            t[1] = in->r[1];
            t[2] = in->r[2];
            func_00123ab8(o->x4, t);
            return;
        }
    }
    out->x = in->p[0];
    out->y = in->p[1];
    out->z = in->p[2];
    out->w = in->p[3];
    switch (in->x5a) {
    case 2:
        if (D_002E26A0[0] == 0) return;
        func_0014eab0(o, out);
        func_00267530(&d, (V53 *)((u8 *)D_002E26A0[0] + 16), out);
        out->w = atan2f(d.x, d.z);
        break;
    case 3:
        if (D_002E26A0[0] == 0) return;
        func_0014eb60(o, out);
        func_00267530(&d, (V53 *)((u8 *)D_002E26A0[0] + 16), out);
        out->w = atan2f(d.x, d.z);
        break;
    case 4:
        func_002675a8(&d, out);
        func_0014e668(&d, o->info->x58, out, 0.0f, 500.0f);
        break;
    }
}

typedef struct { u8 pad[0x4c]; u16 x4c; } Info3d;
typedef struct { u8 pad[0xbd]; u8 xbd; } Sub3d;
typedef struct { u8 pad[0x154]; s32 x154; u8 pad158[0x28]; } W3d;
typedef struct { u8 pad[0x83e]; u16 x83e; } G3d;
typedef struct { u8 pad[0x10]; s32 x10; } R3d;
typedef struct {
    u64 lo : 37;
    u64 k : 2;
    u64 hi : 25;
} F3d;
typedef struct Obj3d {
    u8 pad0[6];
    u8 x6;
    u8 pad7[0x65];
    Sub3d *x6c;
    u8 pad70[0xc0];
    Info3d *info;
    u8 pad134[0x14];
    W3d *x148;
    s32 x14c;
    u8 pad150[0x7c];
    s32 x1cc;
    u8 pad1d0[0x1a0];
    F3d f;
} Obj3d;
W3d D_004F71D0[0x3] ALIGNED(16);
extern G3d *D_00304BE8;
extern s32 D_002BC128, D_002BC130, D_002BC134;
s32 func_001499a0(void);
u32 func_0013c318(u32);
void func_00141e68(Obj3d *);
void func_00153d88(Obj3d *);
void func_001358b8(void *, s32);
void func_00241c60(Obj3d *, u32);
R3d *func_00157818(Obj3d *, s32);

void func_00123d48(Obj3d *o) {
    u32 n, k;
    W3d *w;
    o->x14c = func_001499a0();
    n = func_0013c318(o->info->x4c);
    k = n;
    if (n >= 3) return;
    if (o->x6 != 3) return;
    if ((s32)n > 0) {
        k = (D_002E26A0[1] == 0) ? 1 : 2;
    }
    w = &D_004F71D0[k];
    D_002E26A0[k] = o;
    o->x148 = w;
    w->x154 = 0;
    o->x1cc = 1;
    o->f.k = 1;
    o->x6c->xbd = k;
    func_00141e68(o);
    func_00153d88(o);
    D_00304BE8->x83e |= 1 << o->info->x4c;
    func_001358b8(o, 12);
    func_00241c60(o, n);
    if (D_002BC128 == 16 && ((D_002BC130 == 37 && D_002BC134 == 13 && o->info->x4c == 2) ||
                             (D_002BC128 == 16 && D_002BC130 == 38 && D_002BC134 == 13 && o->info->x4c == 1))) {
        func_00157818(o, 0)->x10 = 0x3000;
    }
}

#define FLD(T, p, off) (*(T *)((u8 *)(p) + (off)))
extern V53 D_002C58B0;
void func_00145240(void *);
void func_00176310(void *);
s32 func_0014f5c8(void *);
void func_0014f658(void *, s32);
void *func_00134928(void *);
void func_001350d0(void *);
void func_00137448(void *);
void func_001238d0(void *, V53 *);
typedef struct { u64 lo : 4; u64 b4 : 1; u64 hi : 59; } F160;

void func_00124060(u8 *o, V53 *pos) {
    void *v;
    if (FLD(u8 *, o, 0x148)) {
        FLD(s32, FLD(u8 *, o, 0x148), 0x90) = 0xffff;
        if (0.0f < FLD(f32, FLD(u8 *, o, 0x148), 0xe0)) {
            FLD(f32, FLD(u8 *, FLD(u8 *, o, 0x134), 0x10), 0xc) = FLD(f32, FLD(u8 *, o, 0x148), 0xe0);
            FLD(f32, FLD(u8 *, o, 0x148), 0xe0) = 0.0f;
        }
        func_00145240(o);
        func_002675a8(FLD(u8 *, o, 0x148) + 0x160, &D_002C58B0);
        func_001358b8(o, 12);
    }
    if (FLD(u8 *, o, 0x14c)) {
        if (FLD(void *, FLD(u8 *, o, 0x14c), 0x1c)) {
            func_00176310(FLD(void *, FLD(u8 *, o, 0x14c), 0x1c));
            FLD(void *, FLD(u8 *, o, 0x14c), 0x1c) = 0;
        }
        FLD(s32, FLD(u8 *, o, 0x14c), 0x24) = -1;
    }
    if (!func_0014f5c8(o)) func_0014f658(o, 0);
    FLD(s32, o, 0x388) = 0;
    FLD(f32, o, 0x480) = 1.0f;
    FLD(u32, o, 0) = (FLD(u32, o, 0) & 0x01004083) | 0x8000;
    FLD(s32, o, 0x88) = 0;
    for (; (v = func_00134928(o)) != 0;) func_001350d0(v);
    FLD(F160, o, 0x160).b4 = 0;
    FLD(f32, o, 0x284) = 1.0f;
    FLD(f32, o, 0x458) = -1.0f;
    FLD(s32, o, 0x470) = 0;
    FLD(s32, o, 0x450) = 0;
    FLD(s32, o, 0x454) = 0;
    FLD(s32, o, 0x474) = 0;
    FLD(s32, o, 0x98) = 0;
    func_00137448(o);
    FLD(f32, o, 0x4ac) = 60.0f;
    func_001238d0(o, pos);
    func_002675a8(o + 0x3c0, &D_002C58B0);
    func_002675a8(o + 0x120, &D_002C58B0);
}

extern V53 D_002C6490;
void *func_001230a0(void *);
void func_001247e8(void *);
s32 func_001232f0(void *);
void func_00142480(V53 *, V53 *, s32, V53 *);
void func_00131500(void *);
void func_00130340(void *, s32, f32);
void func_0012b9b0(void *);

void func_00124a28(void) {
    u8 *o;
    V53 v;
    for (o = 0; (o = func_001230a0(o)) != 0;) {
        switch (o[6]) {
        case 3:
            if (((s32)(FLD(u64, o, 0x370) >> 48) & 1) && !((s32)(FLD(u64, o, 0x440) >> 32) & 1)) {
                func_001247e8(o);
                break;
            }
            func_002675a8(&v, o + 0x10);
            if (!func_0014f5c8(o) && func_001232f0(o)) {
                v.y -= FLD(f32, FLD(u8 *, FLD(u8 *, o, 0x134), 0x10), 8);
                func_00142480(&v, &D_002C6490, 0, &v);
            }
            v.w = FLD(f32, o, 0x3c);
            func_00124060(o, &v);
            func_00131500(o);
            func_00130340(o, 0, 0.0f);
            break;
        case 7:
            func_001247e8(o);
            break;
        }
        if (((s32)(FLD(u64, o, 0x370) >> 48) & 1) && FLD(void *, o, 0x144)) {
            func_0012b9b0(FLD(void *, o, 0x144));
            FLD(void *, o, 0x144) = 0;
        }
    }
}
#include "data/data_002B.h"
#include "data/pieces/D_002BC128.h"
#include "data/pieces/D_002C6490.h"

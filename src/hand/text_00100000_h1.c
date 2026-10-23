/* Hand-matched functions from 0x00100000-0x00108fff (worker 1). */
#include "common.h"
#include "data/pieces/D_002A624C.h"
#include "data/bss_0049.h"

/* ---- types ---- */
typedef struct { s32 a, b, c, d; } Q4;
/* DMA tag pair built by func_00101970. */
typedef struct { Q4 h; s32 n, x, c, d; } DmaHdr;
typedef Vtx Vec3;
/* Flag word D_002BC0A8. */
#include "data/pieces/D_002BC0A8.h"
typedef Flags_2BC0A8 Flags;
/* Packed attribute word at +16 of the 20-byte entries of D_002A6238. */
#include "data/pieces/D_002A6238.h"
typedef EntBits_2a6238 EntBits;
typedef Ent20_2a6238 Ent20;
#include "data/pieces/D_002A6274.h"
typedef struct { s32 w0, w4, w8, w12; } Ent16;
typedef struct { u8 m[64]; u8 v64[16]; u8 v80[16]; s32 w96; } Xf;
#include "data/types/text_00100000_h1.h"
/* Objects returned by func_0011f090 (task/effect slots). */
typedef struct { u8 pad[16]; u8 b16; u8 b17; } Obj;
typedef struct { u8 pad[16]; f32 f16; f32 f20; f32 f24; } Fade;
typedef struct { u8 pad[16]; s32 w16; f32 f20; f32 f24; } Fade2;
typedef struct { u8 pad[16]; u32 w16; } DmaReq;
#include "data/pieces/D_0048C630.h"
typedef Blk32_48c630 Blk32;
typedef struct { u8 pad[16]; s32 w16, w20, w24, w28; u8 pad2[80]; s32 w112, w116, w120, w124; } Blk128;

/* ---- data ---- */
extern char D_0029B170[];
#include "data/pieces/D_0029B280.h"
extern u8 D_002A4160[];
extern u8 D_002A4180[];
extern s32 D_002A3F20;
extern s32 D_002A3F28;
#include "data/pieces/D_002A3F50.h"
extern u64 D_002A6058;
extern u8 D_002A6070[];
extern u64 D_002A6178;
extern s32 D_002A61F0;
extern s32 D_002A6204;
#include "data/pieces/D_002A6208.h"
extern s32 D_002A6230;
#include "data/pieces/D_002A6238.h"
extern s32 D_002A6258;
extern s32 D_002A6294;
extern u16 D_002A62F8[];
extern GsRegs D_002A6330;
extern u8 D_002A6500[];
extern s32 D_002A6B84;
#include "data/pieces/D_002A6C10.h"
extern s32 D_002A6C50;
extern f32 D_002BBDFC;
extern s32 D_002BBE14;
extern s32 D_002BC060[4];
#include "data/pieces/D_002BC070.h"
extern s32 D_002BC090, D_002BC094, D_002BC0A0, D_002BC0A4;
extern s32 D_002BC0BC;
extern s32 D_002BC128, D_002BC130, D_002BC134;
#include "data/pieces/D_002BC720.h"
#include "data/pieces/D_002BCAF0.h"
extern s32 D_002BCC98;
extern s32 D_002BCDE8;
extern s32 D_002C1368[];
extern s32 D_002C138C;
#include "data/pieces/D_002E2780.h"
#include "data/pieces/D_002E2790.h"
extern s32 D_00472150[];
extern s32 D_0048BFD0[2];
#include "data/pieces/D_0048C690.h"
#include "data/pieces/D_0048C6F0.h"
extern u8 D_00494320[];
extern s32 D_00494410[];
u8 D_00494420[0x1c0] ALIGNED(32);
extern u8 D_004945E0[];
extern s32 D_00494894;
extern f32 D_00494898;
extern f32 D_004948A0[4];
extern f32 D_00494A74;
extern Ent16 *D_00494BA8;
extern Vec3 D_00494C00[]; /* src/data/bss_0049.c: V3 D_00494C00[0x20] */

/* ---- functions ---- */
void func_00101bb8(void);
void func_00103838(void);
void func_00103920(void);
void func_00103c48(void);
s32 func_00104298(f32 *);
s32 func_00104388(void *);
void func_001044c0(Xf *);
void func_00104528(void);
void func_00104678(void);
s32 func_00106708(void *);
s32 func_00106810(void *);
void func_00106900(void);
void func_00106910(void);
s32 func_00106920(void *);
void func_00106b18(void *);
void func_00106bd8(char *, s32);
s32 func_00106db0(DmaReq *);
s32 func_00106e18(s32);
void func_001081a0(s32);
void func_00108f18(s32, s32, void *);
void func_00109288(void);
void func_00109770(void);
EntBits *func_0011ab38(s32, s32);
u8 func_0011ab60(s32, s32);
void func_0011d3c8(s32, s32, s32);
void func_0011ef10(s32, void *);
void func_0011efa8(void *, void *, s32, s32);
void *func_0011f090(void *, s32, void *);
s32 func_00142730(s32, s32 *);
DmaReq *func_0015ed80(s32, void *);
void func_001761f0(void);
void func_00176230(void);
void func_00262c78(void);
void func_00266f38(s32, u32);
void func_002673b8(f32 *, f32 *);
void func_00267530(f32 *, f32 *, f32 *);
void func_00267578(void *, void *, void *);
void func_002678b8(void *, void *, void *);
s32 sceGsSyncPath(s32, s32);
void iFlushCache(s32);
void sceVu0MulMatrix(void *, void *, void *);

void func_00100580(s32 idx, s32 *dst) {
    s32 i;
    for (i = 0; i < 2; i++) { 
        dst[0] = D_0048C6F0[idx].v[0];
        dst[1] = D_0048C6F0[idx].v[1];
        dst[2] = D_0048C6F0[idx].v[2];
        dst[3] = D_0048C6F0[idx].v[3];
        dst[4] = D_00472150[0];
        dst[5] = D_00472150[1];
        dst[6] = D_00472150[2];
        dst[7] = D_00472150[3];
        dst += 8;
    }
}

void func_001008e8(void) {
    func_00106bd8(D_0029B170, 10010);
    func_001044c0((Xf *)D_00494320);
    func_00108f18(0, 10010, D_00494320);
    if (D_002BC0A8.flags.b5 == 1) {
        func_001044c0((Xf *)(D_00494320 + 128));
        func_00108f18(1, 10010, D_00494320 + 128);
    }
}

void func_00100ae0(void) {
    D_002BC0A8.flags.b0 = 0;
    D_002BC0A8.flags.b1 = 0;
    func_001761f0();
    func_00176230();
}

void func_00101628(void) {
    D_00494410[0] = -1;
    D_00494410[1] = -1;
    D_002C1368[0] = 0;
    D_002C1368[1] = 0;
    D_002C138C = 0;
    D_002BCDE8 = 0;
}

void func_00101728(s32 arg) {
    s32 i;
    for (i = 0; i < 2; i++) {
        s32 v = D_00494410[i];
        if (v != ((s32 *)&D_002A3F50)[i] || v == 0) {
            func_0011d3c8(v, i, arg);
        }
    }
}

void func_00101970(s32 sel, DmaHdr *q, s32 x) {
    Q4 *q1 = (Q4 *)&q->n;
    q1->d = 0;
    q1->c = 0;
    q->h.d = 0;
    q->h.c = 0;
    if (sel == 0) {
        q->h.a = 0x30000002;
        q->h.b = (s32)D_002A4160;
        q1->a = 4;
    } else {
        q->h.a = 0x30000002;
        q->h.b = (s32)D_002A4180;
        q1->a = 8;
    }
    q->x = x;
}

void func_00101e70(void) {
    s32 i;
    func_0011efa8(D_004945E0, D_00494420, 28, 16);
    for (i = 0; i < D_002A3F20; i++) {
        Obj *o = func_0011f090(D_004945E0, 120000, func_00101bb8);
        if (o) {
            o->b16 = 0;
            o->b17 = i;
        }
    }
}

void func_00102cc8(s32 *x0, s32 *x1, s32 *y0, s32 *y1) {
    s32 ox = D_002BC0A0, cx = D_002BC090, oy = D_002BC0A4, cy = D_002BC094;
    s32 x = (cx + ox) * 16, y = (cy + oy) * 16;
    *x0 = x - 4096; *x1 = x + 4096; *y0 = y - 3072; *y1 = y + 3072;
}

void func_001038b0(s32 n) {
    func_0011ef10(0x280a2, func_00103838);
    D_00494894 = n * 2;
    if (n == 0) n = 1;
    D_00494898 = 255.0f / (f32)(n * 2);
}

void func_00103988(s32 n) {
    func_0011ef10(0x280a2, func_00103920);
    D_00494894 = n * 2;
    if (n == 0) n = 1;
    D_00494898 = 255.0f / (f32)(n * 2);
}

s32 func_001039f8(void) {
    if (D_002A6204 != 0) {
        if (D_002A61F0 == 0) D_002A6058 = ((u64)D_002A6204 << 24) | 0x100000000;
        else D_002A6058 = ((u64)D_002A6204 << 24) | 0x100FFFFFF;
        func_00106b18(D_002A6070);
    }
    return 0;
}

void func_00104220(void) {
    D_004948A0[0] = D_004948A0[1] = D_004948A0[3] = 0.0f;
    D_004948A0[2] = D_00494A74;
    func_0011ef10(0x280a4, func_00103c48);
}

s32 func_00104298(f32 *p) {
    p[4] -= D_002BBDFC;
    if (p[4] <= 0.0f) {
        D_002A6178 = 0x100000000;
        return 4;
    }
    D_002A6178 = ((u64)(s32)(p[5] * p[4]) << 24) | 0x100000000;
    return 0;
}

void func_00104300(s32 n) {
    Fade *o;
    D_002A6208 = 1;
    o = func_0011f090(D_002BC720, 0, func_00104298);
    if (o) {
        o->f16 = (f32)(n * 2);
        if (n == 0) n = 1;
        o->f20 = 128.0f / (f32)(n * 2);
    }
}

void func_001043f8(s32 n) {
    Fade2 *o = func_0011f090(D_002BC720, 0, func_00104388);
    if (o) {
        D_002A6208 = 1;
        o->w16 = 0;
        o->f24 = (f32)(n * 2);
        if (n == 0) n = 1;
        o->f20 = 128.0f / (f32)(n * 2);
    }
}

void func_001044c0(Xf *p) {
    func_002678b8(p, D_002BCAF0, p->v64);
    func_00267578(p, p, p->v80);
    if (p->w96 != -1) sceVu0MulMatrix(p, (void *)p->w96, p);
}

void func_001047c8(void) {
    if (D_002A3F28 != 0) {
        if (D_002BC128 == 15 && D_002BC130 == 12 && (D_002BC134 == 24 || D_002BC134 == 2)) {
            func_00104528();
            return;
        }
        func_00104678();
    } else {
        func_00104528();
    }
}

s32 func_00104a90(s32 i, s32 *out) {
    Ent20 *e = &D_002A6238[i]; s32 d;
    out[0] = e->v[0]; out[1] = e->v[1]; out[2] = e->v[2]; out[3] = d = e->v[3];
    if (d == -2 || d == -1) return 3; return 4;
}

void func_00104eb0(s32 i, f32 *out) {
    Vec3 *v = &D_002A624C[D_002A6238[i].v[0]];
    out[0] = v->x;
    out[1] = v->y;
    out[2] = v->z;
    out[3] = 1.0f;
}

s32 func_00105020(void) {
    s32 i;
    for (i = 0; i < D_002A6294; i++) {
        if ((D_002A6274[i].f.w & 0xf6) == 80) return 1;
    }
    return 0;
}

s32 func_00105078(void) {
    s32 i;
    for (i = 0; i < D_002A6294; i++) {
        if ((D_002A6274[i].f.w & 0xf6) == 144) return 1;
    }
    return 0;
}

void func_00105218(void) {
    s32 i;
    for (i = 0; i < D_002A6230; i++) func_0011d3c8(D_002A62F8[i], i, 960);
}

s32 func_00105960(s32 a, s32 b) {
    s32 sub;
    s32 idx = func_00142730(a, &sub);
    if (sub == -1) { s32 off = idx * 20; return ((Ent20 *)((u8 *)D_002A6238 + off))->id == b; }
    return func_0011ab60(sub, idx) == b;
}

s32 func_00105b10(s32 sub, s32 idx) {
    if (sub == -1) { s32 off = idx * 20; return ((Ent20 *)((u8 *)D_002A6238 + off))->f.e.f22; }
    return func_0011ab38(sub, idx)->f22;
}

s32 func_00105b68(s32 sub, s32 idx) {
    if (sub == -1) { s32 off = idx * 20; return ((Ent20 *)((u8 *)D_002A6238 + off))->f.e.f4; }
    return func_0011ab38(sub, idx)->f4;

}

s32 func_00105bc0(s32 sub, s32 idx) {
    if (sub == -1) { s32 off = idx * 20; return ((Ent20 *)((u8 *)D_002A6238 + off))->f.e.f18; }
    return func_0011ab38(sub, idx)->f18;

}

s32 func_00105c18(s32 sub, s32 idx) {
    if (sub == -1) { s32 off = idx * 20; return ((Ent20 *)((u8 *)D_002A6238 + off))->f.e.f28; }
    return func_0011ab38(sub, idx)->f28;

}

s32 func_00105ce0(s32 id) {
    s32 i; for (i = 0; i < D_002A6258; i++) { Ent20 *e = &D_002A6238[i]; if (e->id == id) return e->f.e.f11; } return 0;
}

void func_00105f28(void) {
    if (D_002BBE14) {
        D_002A6330.d32 = 0x131000070;
        D_002A6330.d16 = 0x131000070;
    } else {
        D_002A6330.d32 = 0x31000070;
        D_002A6330.d16 = 0x31000070;
    }
    D_002A6330.d152 = (u64)D_002BC060[0] | ((u64)D_002BC060[1] << 8) | ((u64)D_002BC060[2] << 16) | ((u64)D_002BC060[3] << 24) | 0x100000000;
    func_00106b18(D_002A6500);
}

s32 func_001063f8(void) {
    if ((*(s32 *)&D_002BC070) == 128 && D_002BC0BC == 0 && D_002A6204 == 0) return 0;
    return 1;
}

void func_00106780(s32 n) {
    Fade2 *o;
    func_00106900();
    func_00106910();
    o = func_0011f090(D_002BC720, 0, func_00106708);
    if (o) {
        o->w16 = 0;
        o->f24 = (f32)(n * 2);
        if (n == 0) n = 1;
        o->f20 = 128.0f / (f32)(n * 2);
    }
}

void func_00106880(s32 n) {
    Fade *o = func_0011f090(D_002BC720, 0, func_00106810);
    if (o) {
        o->f16 = (f32)(n * 2);
        if (n == 0) n = 1;
        o->f20 = 128.0f / (f32)(n * 2);
    }
}

void func_00106978(s32 n) {
    Fade2 *o;
    func_00106900();
    func_00106910();
    o = func_0011f090(D_002BC720, 0, func_00106920);
    if (o) {
        o->w16 = 0;
        o->f24 = (f32)(n * 2);
        if (n == 0) n = 1;
        o->f20 = 128.0f / (f32)(n * 2);
    }
}

void func_00106b58(u32 x) {
    u32 v = x | 0x80000000;
    sceGsSyncPath(0, 0);
    func_00266f38(D_002A6B84, v);
}

s32 func_00106db0(DmaReq *r) {
    *(volatile u32 *)0x10009020 = 0;
    *(volatile u32 *)0x10009030 = r->w16 & 0x0fffffff;
    *(volatile u32 *)0x1000e010 = 2;
    iFlushCache(0);
    *(volatile u32 *)0x10009000 = 0x105;
    return 2;
}

void func_00106e98(s32 a) {
    if (D_002A6C50) func_0015ed80(a, func_00106e18);
}

s32 func_00107520(s32 i) {
    Ent16 *e = &D_00494BA8[i]; return (D_002BCC98 & e->w8) != 0;
}

void func_00107e60(void) {
    f32 m[4][4] __attribute__((aligned(16)));
    f32 v[4] __attribute__((aligned(16)));
    f32 *p = v;
    func_00267530(p, &D_002E2790.x, &D_002E2780.x);
    func_002673b8(p, p);
    func_002678b8(D_002A6C10, &D_0029B280, p);
}

void func_00108180(s32 n) {
    *(volatile s32 *)&D_002BCC98 = (1 << n) | *(volatile s32 *)&D_002BCC98;
}

void func_001081a0(s32 n) {
    *(volatile s32 *)&D_002BCC98 = ~(1 << n) & *(volatile s32 *)&D_002BCC98;
}

void func_001085e8(s32 a, s32 b) {
    func_0015ed80(a, func_00106db0)->w16 = b;
}

void func_00108650(s32 i, s32 n) {
    f32 d = (f32)(n * 2);
    D_00494C00[i].x = d;
    D_00494C00[i].y = 1.0f;
    D_00494C00[i].z = -(1.0f / d);
    func_001081a0(i);
}

void func_001086b8(s32 i, s32 n) {
    f32 d = (f32)(n * 2);
    D_00494C00[i].x = d;
    D_00494C00[i].y = 0.0f;
    D_00494C00[i].z = 1.0f / d;
}

void func_00108900(Blk128 *o, s32 unused, s32 *a, s32 *b) {
    a[0] = b[0] = D_0048BFD0[0];
    a[1] = b[1] = D_0048BFD0[1];
    o->w16 = D_0048C630.x10;
    o->w20 = (s32)a;
    o->w24 = D_0048C630.x18;
    o->w28 = D_0048C630.x1c;
    o->w112 = D_0048C690.x10;
    o->w116 = (s32)b;
    o->w120 = D_0048C690.x18;
    o->w124 = D_0048C690.x1c;
}
#include "data/bss_0049_mixed.h"
#include "data/data_002A.h"
#include "data/data_002B.h"
#include "data/data_002C.h"
#include "data/data_0029.h"
#include "data/pieces/D_0048BFD0.h"
#include "data/pieces/D_002BBDFC.h"
#include "data/pieces/D_002BC128.h"
#include "data/pieces/D_002C1368.h"
#include "data/pieces/D_002A6330.h"

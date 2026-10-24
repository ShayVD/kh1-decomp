/* Object draw jobs: func_001371f0 queues a draw job on the task list
 * D_0052A100 (func_00136bc0 runs it) with a per-kind draw callback
 * (func_001368e8, func_001369e8, func_00136ab8), func_00136428 draws a model
 * with a colour and alpha, func_001372a0 resets the lists, func_00135ed0 uploads a texture through
 * GIF path 3 and func_00136d38 builds an object's matrix with a ground ray. Flag mode: nostrict (the other modes are in the sibling
 * files). Read from the code, not proved by a boot (docs/modules.md "Session
 * 53"). */
#include "common.h"
#include "platform/vu.h"
#include "platform/gs.h"
#include "platform/dma.h"
#include "data/bss_0052.h"
#include "data/types/nostrict_text_00120000_b02.h"
#include "data/pieces/D_002BC0F0.h"
#include "data/pieces/D_002E26C0.h"
#include "data/bss_004F.h"
#include "data/pieces/D_002C58A0.h"
#include "data/pieces/D_002C5C80.h"
#include "data/pieces/D_00350CE0.h"
#include "data/pieces/D_002E26A0.h"
#include "data/types/nostrict_text_00120000_h54.h"
#include "data/pieces/D_00304BE8_s.h"
#include "data/pieces/D_00304B78.h"
#include "data/pieces/D_002E31A8.h"
#include "data/pieces/D_002C58D0.h"
#include "data/pieces/D_002BC0A8.h"

/* func_00135ed0 (from hand/nostrict/text_00130000_c02.c, session 54). */
#define C02_TEX0(tbp, tbw, psm, tw, th, tcc, tfx, cbp, cpsm, csm, csa, cld) \
    ((u64)(tbp) | ((u64)(tbw) << 14) | ((u64)(psm) << 20) | ((u64)(tw) << 26) | \
     ((u64)(th) << 30) | ((u64)(tcc) << 34) | ((u64)(tfx) << 35) | ((u64)(cbp) << 37) | \
     ((u64)(cpsm) << 51) | ((u64)(csm) << 55) | ((u64)(csa) << 56) | (cld))

typedef union {
    struct { u64 a, b; } d;
    s32 w[4];
} C02Q;

typedef struct {
    u16 x0;
    u8 x2;
    u8 x3;
    s32 x4;
    s32 x8;
    s32 xc;
} C02Tex;

typedef struct {
    u16 x0;
    u8 x2;
    u8 x3;
    u16 x4;
    u16 x6;
    u16 x8;
    u8 pad0a[2];
    s32 xc;
    s32 x10;
} C02Img;

typedef struct {
    u8 pad00[0x154];
    void *x154;
} C02Res;

typedef struct {
    C02Res *res;
    s32 x4;
} C02Src;

#include "data/pieces/D_00351BC8.h"

C02Q *func_0011fb38(s32 reg, u64 val, C02Q *p);
void func_0011fb48(C02Q *t, s32 eop, C02Q *end);
void func_0011fb78(C02Q *t, s32 id, C02Q *end);
C02Q *func_0011fbb0(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6, u32 a7, s32 a8, C02Q *buf);
s32 func_001623e8(void *r);
void func_001623f8(void *r, s32 i, C02Tex *t);
void func_00162428(s32 a, s32 b);

s32 func_00135ed0(C02Img *img, C02Src *src)
{
    C02Q buf[128];
    C02Tex tex;
    C02Q *p;
    C02Q *dt;
    C02Q *gt;
    u64 regs;
    s32 c;
    s32 adc;
    u64 cld;
    s32 n;

    if (src->x4 >= 128)
        return 0;
    regs = 0x53531;
    c = 128;
    adc = 0x8000;
    cld = 1UL << 61;
    n = func_001623e8(src->res->x154);
    func_001623f8(src->res->x154, img->xc + n / 2, &tex);
    dt = &buf[0];
    gt = &buf[1];
    p = &buf[2];
    p = func_0011fb38(0x4c, ((u64)img->x4 >> 6) << 16 | 0x1d0, p);
    p = func_0011fb38(0x4e, 1UL << 32, p);
    p = func_0011fb38(0x18, 0, p);
    p = func_0011fb38(0x40, (u64)(img->x4 - 1) << 16 | (u64)(img->x6 - 1) << 48, p);
    p = func_0011fb38(0x42, 0x8000000011UL, p);
    p = func_0011fb38(0x47, 0x30000, p);
    func_0011fb48(gt, 0, p);
    p->d.a = 0x508b400000008001UL;
    p->d.b = regs;
    p++;
    p->w[0] = c;
    p->w[1] = c;
    p->w[2] = c;
    p->w[3] = src->x4;
    p++;
    p->w[0] = 0;
    p->w[1] = 0;
    p++;
    p->w[0] = 0;
    p->w[1] = 0;
    p->w[2] = 0;
    p->w[3] = adc;
    p++;
    p->w[0] = img->x4 << 4;
    p->w[1] = img->x6 << 4;
    p++;
    p->w[0] = img->x4 << 4;
    p->w[1] = img->x6 << 4;
    p->w[2] = 0;
    p->w[3] = 0;
    p++;
    func_0011fb78(dt, 1, p);
    p = func_0011fbb0(img->x0, img->x2, img->x3, 0, 0, 1 << tex.x2, 1 << tex.x3, tex.x0, tex.x8, p);
    p = func_0011fbb0(img->x8, 1, 0, 0, 0, 16, 16, 64, tex.xc, p);
    dt = p++;
    gt = p++;
    p = func_0011fb38(63, 0, p);
    func_0011fb48(gt, 1, p);
    func_0011fb78(dt, 7, p);
    D_00351BC8(0);
    PlatDmaSend(PlatDmaGetChan(2), buf);
    PlatGsSyncPath(0, 0);
    func_00162428(img->x10, 1);
    PlatGsSyncPath(0, 0);

    dt = &buf[0];
    gt = &buf[1];
    p = func_0011fb38(63, 0, &buf[2]);
    p = func_0011fb38(6, C02_TEX0(img->x0, img->x2, img->x3, tex.x2, tex.x3, 1, 0, img->x8, 0, 0, 0, cld), p);
    func_0011fb48(gt, 0, p);
    p->d.a = 0x50ab400000000001UL;
    p->d.b = regs;
    p++;
    p->w[0] = c;
    p->w[1] = c;
    p->w[2] = c;
    p->w[3] = c;
    p++;
    p->w[0] = 0;
    p->w[1] = 0;
    p++;
    p->w[0] = 0;
    p->w[1] = 0;
    p->w[2] = 0;
    p->w[3] = adc;
    p++;
    p->w[0] = img->x4 << 4;
    p->w[1] = img->x6 << 4;
    p++;
    p->w[0] = img->x4 << 4;
    p->w[1] = img->x6 << 4;
    p->w[2] = 0;
    p->w[3] = 0;
    p++;
    gt = p;
    p = func_0011fb38(0x4c, 0x800d0, gt + 1);
    p = func_0011fb38(0x4e, 0x31000070, p);
    p = func_0011fb38(0x18, 0x0000740000007000UL, p);
    p = func_0011fb38(0x40, 0x017f000001ff0000UL, p);
    p = func_0011fb38(0x42, 0x44, p);
    p = func_0011fb38(0x47, 0x5000d, p);
    p = func_0011fb38(0x3f, 0, p);
    p = func_0011fb38(6, C02_TEX0(0x3a00, img->x4 >> 6, 0, tex.x2, tex.x3, 1, 0, 0, 0, 0, 0, cld), p);
    func_0011fb48(gt, 1, p);
    func_0011fb78(dt, 7, p);
    D_00351BC8(0);
    PlatDmaSend(PlatDmaGetChan(2), buf);
    PlatGsSyncPath(0, 0);
    return 0;
}

/* func_00136428 (from hand/nostrict/text_00120000_b02.c). */
typedef struct { u8 p0[4]; u32 f4; u8 p8[0x4c - 8]; u16 h4c; } K14;
typedef struct { s32 f0; s32 f4; u8 p8[4]; u8 c[4]; } Q14;
typedef struct { s32 f0; s32 f4; } R14;
typedef struct {
    u32 f0;
    u8 p4[0x48 - 4];
    f32 f48;
    u8 p4c[4];
    V4 f50;
    u8 p60[0xd0 - 0x60];
    f32 fd0[4][4];
    u8 p110[0x130 - 0x110];
    K14 *f130;
    u8 p134[0x14c - 0x134];
    Q14 *f14c;
    u8 p150[0x15c - 0x150];
    s32 f15c;
    u64 f160;
    u8 p168[0x370 - 0x168];
    u64 f370;
    u8 p378[0x410 - 0x378];
    f32 f410;
    f32 f414;
    u8 p418[8];
    s32 f420;
} O14;
typedef struct {
    u32 f40;
    s32 f44;
    s32 f48;
    u8 c[4];
    u8 b[4];
    s32 f54;
    u8 d[4];
    u8 e[4];
    void *fn;
    void *p;
    u32 fl;
    s32 f6c;
    void *fn1;
    void *fn2;
    u64 g[2];
} S14;
extern void func_00122770(void);
extern void func_001229c0(void);
extern void func_00135ed0_fn(void) __asm__("func_00135ed0");
extern void func_00175600(void);
extern R14 *func_001357b8(void);
extern void func_00135a68(u8 *, f32, f32);
extern s32 func_00121000(f32 (*)[4], u8 *);
extern void func_001621e0(s32, f32 (*)[4], S14 *, O14 *);
void func_00136428(O14 *o, u32 fl, s32 a2, f32 *col, f32 alpha) {
    f32 m[4][4];
    S14 s;
    u8 buf[128];
    s32 i;
    Q14 *q;
    R14 *r;

    s.f44 = o->f420;
    s.f48 = -1;
    s.fn1 = func_00122770;
    s.fn2 = func_001229c0;
    s.b[0] = D_002BC0F0.i[4];
    s.b[1] = D_002BC0F0.i[5];
    s.b[2] = D_002BC0F0.i[6];
    s.b[3] = (s32)alpha;
    s.f40 = 0;
    switch (o->f130->h4c) {
    case 35:
    case 516:
        r = func_001357b8();
        r->f0 = (s32)o;
        r->f4 = o->f48 * 128.0f;
        s.p = r;
        s.fn = func_00135ed0_fn;
        break;
    case 507:
        if ((s32)(o->f160 >> 10) & 1) {
            fl |= 4;
            s.fn = func_00175600;
        } else {
            s.fn = 0;
        }
        break;
    default:
        s.p = o;
        s.fn = 0;
        break;
    }
    s.fl = fl;
    s.f6c = a2;
    for (i = 0; i < 4; i++) s.c[i] = (s32)col[i];
    q = o->f14c;
    if (q && q->f0 && (o->f0 & 0x4000)) {
        s.f54 = q->f4;
        for (i = 0; i < 4; i++) {
            s.d[i] = s.c[i];
            s.e[i] = q->c[i];
        }
    } else {
        s.f54 = 0;
    }
    PlatVu0CopyMatrix(m, o->fd0);
    PlatVu0CopyVector(m[3], &o->f50);
    m[3][3] = 1.0f;
    PlatVu0MulMatrix(m, D_002E26C0, m);
    if (!((o->f370 >> 49) & 1)) {
        func_00135a68(buf, o->f410, o->f414);
        if (func_00121000(m, buf)) s.f40 |= 0x100;
    }
    if (o->f130->f4 & 4) s.f40 |= 0x200;
    {
        u64 t = 0x000800d0;
        s.g[0] = 0x31000070;
        s.g[1] = t;
    }
    func_001621e0(o->f15c, D_002E26C0, &s, o);
}

/* func_00136768 (from hand/nostrict/text_00120000_h54.c). */
typedef union { u64 x; struct { u32 lo:24; u32 b3:8; u32 b4:8; u32 k:2; u32 hi:22; } b; } F370;
typedef struct { u8 pad[0x50]; V4 pos; u8 p60[0x2c4-0x60]; f32 f2c4; u8 p2c8[4]; s32 f2cc; u8 p2d0[0x320-0x2d0]; V4 v320; u8 p330[0x370-0x330]; F370 f370; } E2;
typedef struct { u8 p[0x4c]; u16 f4c; } I21;
typedef struct Actor_36768 { u32 f0; u8 p4[2]; u8 f6; u8 p7[0x118 - 7]; f32 f118; u8 p11c[0x130 - 0x11c]; I21 *f130; u8 p134[0x144 - 0x134]; s32 f144; u8 p148[0x370 - 0x148]; u64 f370; u8 p378[0x38c - 0x378]; s32 f38c; u8 p390[4]; s32 f394; u8 p398[0x430 - 0x398]; V4 f430; } E21;
typedef struct { void *p; s32 n; } Arg21;
extern f32 func_00135ca0(f32);
extern void func_00122588(E21 *);
extern void func_00135df0(E21 *, V4 *);
extern s32 func_00135bb0(E21 *);
extern void func_0012bce0(s32, s32, s32, Arg21 *, s32);
extern void func_00128218(E2 *, f32);
#define func_00136428 ((s32 (*)(E21 *, s32, s32, V4 *, f32)) func_00136428)
void func_00136768(E21 *e) {
    Arg21 a;
    V4 v;
    s32 w;
    f32 s = func_00135ca0(e->f118);
    func_00122588(e);
    func_00135df0(e, &v);
    PlatVu0MulVector(&v, &v, &e->f430);
    if (v.w <= 0.0f) return;
    if (func_00135bb0(e) && (e->f0 & 1)) {
        s32 f = e->f38c;
        if (e->f130->f4c == 8) {
            if (e->f6 == 3) {
                if (e->f0 & 0x4000) f |= 2;
            }
        }
        w = func_00136428(e, f, e->f394, &v, s);
        if (((s32)(e->f370 >> 48) & 1) && e->f144) {
            a.p = &w;
            a.n = 4;
            func_0012bce0(e->f144, 4, 1, &a, 0);
        }
        e->f370 |= 0x800000000LL;
    }
    if (e->f0 & 2) {
        if (e == D_002E26A0[0] && D_00304BE8->f880) return;
        func_00128218((E2 *)e, v.w * s * (1.0f / 32640.0f));
    }
}
#undef func_00136428

/* func_001369e8 (from hand/nostrict/text_00130000_s6_na.c). */
typedef union { u64 x; struct { u32 lo; u32 x32:3; u32 b35:1; u32 hi:28; } b; } F370d;
typedef struct { u32 f0; u8 p4[0xd0-4]; u8 fd0[0x154-0xd0]; s32 f154; u8 p158[0x370-0x158]; F370d f370; } Ob8;
extern s32 func_00114a38(void *, s32, s32, f32 *);
#define func_00135df0 ((void (*)(Ob8 *, f32 *)) func_00135df0)
#define func_00128218 ((void (*)(Ob8 *, f32)) func_00128218)
void func_001369e8(Ob8 *o) {
    f32 v[4];
    s32 i;
    if (!(o->f0 & 1)) return;
    if (!(D_002BC0A8.u & 1)) return;
    func_00135df0(o, v);
    for (i = 0; i < 4; i++) v[i] *= 0.0078125f;
    { u64 m = 0x800000000ULL;
    func_00114a38(o->fd0, o->f154, v[3] < 1.0f ? 0xc35a : 0x9c40, v);
    o->f370.x |= m; }
    if (o->f0 & 2) func_00128218(o, 1.0f);
}
#undef func_00135df0
#undef func_00128218

/* func_00136d38 (from hand/nostrict/text_00130000_c02.c, session 54). */
typedef f32 C02Vec[4];

typedef struct {
    u8 pad00[0x4C];
    u16 x4c;
    u8 pad4e[0x54 - 0x4E];
    s8 x54;
} C02Desc;

typedef struct {
    f32 x0;
    f32 x4;
    f32 x8;
    f32 xc;
    f32 x10;
} C02Rec;

typedef struct {
    u8 pad00[4];
    u8 x4;
    u8 pad05[0x10 - 5];
    C02Rec *recs;
} C02Info;

typedef struct {
    u8 pad00[6];
    u8 x6;
    u8 pad07[0x10 - 7];
    C02Vec pos;      /* 0x10 */
    u8 pad20[0x10];
    C02Vec rot;      /* 0x30 */
    C02Vec scale;    /* 0x40 */
    u8 pad50[0xD0 - 0x50];
    C02Vec mtx[4];   /* 0xD0 */
    u8 pad110[0x130 - 0x110];
    C02Desc *desc;   /* 0x130 */
    C02Info *info;   /* 0x134 */
    u8 pad138[0x1CC - 0x138];
    u32 x1cc;
    u8 pad1d0[0x1F0 - 0x1D0];
    C02Vec v1f0;
    u8 pad200[0x370 - 0x200];
    union {
        u64 w;
        struct {
            u64 lo : 44;
            u64 b44 : 1;
            u64 b45 : 1;
            u64 mid : 11;
            u64 b57 : 1;
            u64 hi : 6;
        } b;
    } fl;
    u8 pad378[0x3A0 - 0x378];
    void *x3a0;
    u8 pad3a4[0x450 - 0x3A4];
    C02Vec v450;
    u8 pad460[0x480 - 0x460];
    f32 x480;
} C02Obj;

typedef struct {
    C02Vec pos;
    C02Vec dir;
    C02Vec out;
    s16 hit;
    u8 pad[0xE];
} C02Ray;

#include "data/pieces/D_002C58A0.h"
#include "data/pieces/D_002C58D0.h"
extern u8 D_003044C0[];
extern u8 D_003044B0[];

f32 func_00120c88(f32 x);
void func_00118668(C02Ray *r);
s32 func_001232f0(C02Obj *o);
void func_00121958(void *dst, void *src, void *v);
void func_00136cc0(C02Obj *o);

static inline f32 c02_fabsf(f32 x) { return __builtin_fabsf(x); }

void func_00136d38(C02Obj *o)
{
    C02Vec scale;
    C02Vec pts[2];
    C02Vec dir;
    C02Ray ray;
    C02Vec save[4];
    f32 *m;
    f32 *up;
    s32 i, j;
    u16 k;

    m = o->mtx[0];
    PlatVu0CopyMatrix(save, m);
    if ((s32)(o->fl.w >> 44) & 1) {
        f32 *r = o->rot;
        i = 2;
        do {
            *r = func_00120c88(*r);
            r++;
        } while (--i >= 0);
        PlatVu0RotMatrixX(m, D_002C58D0, o->rot[0]);
        PlatVu0RotMatrixY(m, m, o->rot[1]);
        PlatVu0RotMatrixZ(m, m, o->rot[2]);
        if (o->desc->x54 == 10) {
            PlatVu0ApplyMatrix(o->mtx[3], m, D_003044C0);
            PlatVu0SubVector(o->mtx[3], o->pos, o->mtx[3]);
            PlatVu0AddVector(o->mtx[3], o->mtx[3], D_003044C0);
            o->mtx[0][3] = 0;
            o->mtx[1][3] = 0;
            o->mtx[2][3] = 0;
            o->mtx[3][3] = 1.0f;
            return;
        }
    } else {
        if (func_001232f0(o) && o->info->x4 >= 3) {
            C02Rec *rec = o->info->recs + 1;
            for (i = 0; i < 2; i++) {
                PlatVu0ScaleVector(dir, o->rot, rec->x4 * 100.0f);
                PlatVu0AddVector(pts[i], o->pos, dir);
                PlatVu0CopyVector(ray.pos, pts[i]);
/*P*/
                ray.pos[1] -= rec->x8 + rec->xc;
                ray.pos[3] = 1.0f;
                ray.dir[0] = ray.dir[2] = 0.0f;
                ray.dir[1] = rec->xc * 2.0f;
                ray.dir[3] = 1.0f;
                rec++;
/*Q*/
                func_00118668(&ray);
                if (ray.hit >= 0)
                    PlatVu0CopyVector(pts[i], ray.out);
            }
            PlatVu0SubVector(dir, pts[1], pts[0]);
            PlatVu0Normalize(dir, dir);
            up = dir;
        } else {
            up = o->rot;
        }
        PlatVu0OuterProduct(m, up, D_003044B0);
        PlatVu0Normalize(m, m);
        PlatVu0SubVector(o->mtx[2], &D_002C58A0, up);
        PlatVu0OuterProduct(o->mtx[1], o->mtx[2], m);
        PlatVu0Normalize(o->mtx[1], o->mtx[1]);
    }
    o->fl.w &= ~(1UL << 45);
    PlatVu0CopyVector(scale, o->scale);
    scale[1] *= o->x480;
    k = o->desc->x4c;
    if (k != 0x204 && k != 0x23) {
        for (i = 0; i < 3; i++) {
            if (c02_fabsf(scale[i] - 1.0f) > 0.0001f) {
                o->fl.w |= 1UL << 45;
                break;
            }
        }
    }
    if ((s32)(o->fl.w >> 45) & 1)
        func_00121958(m, m, scale);
    PlatVu0CopyVector(o->mtx[3], o->pos);
    o->mtx[0][3] = 0;
    o->mtx[3][3] = 1.0f;
    o->mtx[1][3] = 0;
    o->mtx[2][3] = 0;
    if (o->x3a0)
        func_00136cc0(o);
    if (o->x1cc & 8) {
        f32 t = o->v450[3];
        o->v450[3] = 0;
        PlatVu0ApplyMatrix(o->v1f0, m, o->v450);
        o->v1f0[3] = t;
    }
    if (o->x6 == 5) {
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                if (save[i][j] != o->mtx[i][j]) {
                    o->fl.w &= ~(1UL << 57);
                    return;
                }
            }
        }
    }
}

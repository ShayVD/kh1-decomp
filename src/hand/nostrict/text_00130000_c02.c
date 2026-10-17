/* Hand-matched functions (worker c02). Built without strict aliasing. */
#include "common.h"

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

extern void (*D_00351BC8)(s32);

C02Q *func_0011fb38(s32 reg, u64 val, C02Q *p);
void func_0011fb48(C02Q *t, s32 eop, C02Q *end);
void func_0011fb78(C02Q *t, s32 id, C02Q *end);
C02Q *func_0011fbb0(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6, u32 a7, s32 a8, C02Q *buf);
s32 func_001623e8(void *r);
void func_001623f8(void *r, s32 i, C02Tex *t);
void func_00162428(s32 a, s32 b);
s32 func_00266c08(s32 ch);
void func_00266f38(s32 ch, C02Q *buf);
s32 sceGsSyncPath(s32 mode, u16 timeout);

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
    func_00266f38(func_00266c08(2), buf);
    sceGsSyncPath(0, 0);
    func_00162428(img->x10, 1);
    sceGsSyncPath(0, 0);

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
    func_00266f38(func_00266c08(2), buf);
    sceGsSyncPath(0, 0);
    return 0;
}


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

extern u8 D_002C58A0[];
extern u8 D_002C58D0[];
extern u8 D_003044C0[];
extern u8 D_003044B0[];

void sceVu0CopyMatrix(void *dst, void *src);
f32 func_00120c88(f32 x);
void func_00267768(void *dst, void *src, f32 a);
void func_00267810(void *dst, void *src, f32 a);
void func_002676c0(void *dst, void *src, f32 a);
void func_002672f8(void *dst, void *m, void *v);
void func_00267530(void *dst, void *a, void *b);
void func_00267518(void *dst, void *a, void *b);
void func_00267560(void *dst, void *a, f32 s);
void func_002675a8(void *dst, void *src);
void func_00267370(void *dst, void *a, void *b);
void func_002673b8(void *dst, void *src);
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
    sceVu0CopyMatrix(save, m);
    if ((s32)(o->fl.w >> 44) & 1) {
        f32 *r = o->rot;
        i = 2;
        do {
            *r = func_00120c88(*r);
            r++;
        } while (--i >= 0);
        func_00267768(m, D_002C58D0, o->rot[0]);
        func_00267810(m, m, o->rot[1]);
        func_002676c0(m, m, o->rot[2]);
        if (o->desc->x54 == 10) {
            func_002672f8(o->mtx[3], m, D_003044C0);
            func_00267530(o->mtx[3], o->pos, o->mtx[3]);
            func_00267518(o->mtx[3], o->mtx[3], D_003044C0);
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
                func_00267560(dir, o->rot, rec->x4 * 100.0f);
                func_00267518(pts[i], o->pos, dir);
                func_002675a8(ray.pos, pts[i]);
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
                    func_002675a8(pts[i], ray.out);
            }
            func_00267530(dir, pts[1], pts[0]);
            func_002673b8(dir, dir);
            up = dir;
        } else {
            up = o->rot;
        }
        func_00267370(m, up, D_003044B0);
        func_002673b8(m, m);
        func_00267530(o->mtx[2], D_002C58A0, up);
        func_00267370(o->mtx[1], o->mtx[2], m);
        func_002673b8(o->mtx[1], o->mtx[1]);
    }
    o->fl.w &= ~(1UL << 45);
    func_002675a8(scale, o->scale);
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
    func_002675a8(o->mtx[3], o->pos);
    o->mtx[0][3] = 0;
    o->mtx[3][3] = 1.0f;
    o->mtx[1][3] = 0;
    o->mtx[2][3] = 0;
    if (o->x3a0)
        func_00136cc0(o);
    if (o->x1cc & 8) {
        f32 t = o->v450[3];
        o->v450[3] = 0;
        func_002672f8(o->v1f0, m, o->v450);
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

/* needs make: uses rodata */

typedef f32 C02V4[4] __attribute__((aligned(16)));

typedef struct {
    C02V4 v00;      /* 0x2A0 */
    C02V4 v10;      /* 0x2B0 */
    u8 pad20[0x28 - 0x20];
    u32 x28;        /* 0x2C8 */
    u8 pad2c[0x30 - 0x2C];
    u32 x30;        /* 0x2D0 */
    u8 pad34[0x3E - 0x34];
    u16 x3e;        /* 0x2DE */
    C02V4 v40;      /* 0x2E0 */
    u8 pad50[0x6E - 0x50];
    u16 x6e;        /* 0x30E */
    u8 pad70[0x80 - 0x70];
} C02Mv;

typedef struct {
    u8 pad00[4];
    u32 x4;
} C02Desc2;

typedef struct {
    u8 pad00[0x90];
    s32 x90;
} C02Tgt;

typedef struct C02Ob2 {
    u32 x0;
    u8 pad04[0x70 - 0x4];
    s32 x70;
    u8 pad74[0x90 - 0x74];
    u64 x90;
    u8 pad98[0x130 - 0x98];
    C02Desc2 *desc;
    u8 pad134[0x148 - 0x134];
    C02Tgt *x148;
    u8 pad14c[0x2A0 - 0x14C];
    C02Mv mv;
    u8 pad320[0x370 - 0x320];
    union {
        u64 w;
        struct {
            u64 lo : 53;
            u64 b53 : 1;
            u64 b54 : 2;
            u64 b56 : 1;
            u64 b57 : 1;
            u64 hi : 6;
        } b;
    } fl;
    u8 pad378[0x398 - 0x378];
    s32 x398;
} C02Ob2;

typedef struct {
    s32 a;
    s32 b;
    C02Ob2 *p;
    s32 c;
} C02Slot;

extern C02Slot D_003044D8[];
extern u8 D_002C58A0[];

void func_002675a8(void *dst, void *src);
void func_00267530(void *dst, void *a, void *b);
u64 func_001166e8(C02Mv *m);
s32 func_00143080(C02Ob2 *o, f32 *v);
void func_00142fe0(C02Ob2 *o, C02Ob2 *p);
void func_0014d070(C02Ob2 *o, f32 *v);
f32 func_00121748(void *a, f32 *v);
f32 func_00120bf8(void *a);

void func_00143180(C02Ob2 *o, f32 *v)
{
    C02V4 d;
    C02Mv save;
    C02Mv tmp;
    u32 fl0;
    s32 i, n;
    u16 k;

    if ((o->desc->x4 & 0x2000) && ((s32)(o->fl.w >> 53) & 1) && o->x398 == 0
        && v[0] == 0.0f && v[1] == 0.0f && v[2] == 0.0f)
        return;
    fl0 = o->mv.x30;
    for (;;) {
        func_002675a8(o->mv.v10, v);
        o->mv.v10[3] = 1.0f;
        save = o->mv;
        func_002675a8(save.v40, o->mv.v00);
        if (o->x0 & 0x100) {
            if (!func_00143080(o, v)) {
                o->mv = save;
                func_002675a8(o->mv.v40, o->mv.v00);
            }
        } else {
            n = 0;
            o->x90 = func_001166e8(&o->mv);
            for (i = 0; i < 32; i++) {
                if ((o->x90 >> i) & 1) {
                    if (i > 0) {
                        func_00142fe0(o, D_003044D8[i - 1].p);
                        if ((s32)(D_003044D8[i - 1].p->fl.w >> 57) & 1)
                            n++;
                    } else {
                        n++;
                    }
                }
            }
            if (n >= 2) {
                tmp = o->mv;
                func_002675a8(tmp.v00, tmp.v40);
                func_002675a8(tmp.v10, D_002C58A0);
                if (func_001166e8(&tmp)) {
                    o->mv = save;
                    o->mv.x28 |= 0x80000000;
                }
            }
        }
        switch (o->x70) {
        case 2:
        case 3:
            func_0014d070(o, v);
            break;
        case 10:
            func_00267530(o->mv.v10, o->mv.v40, o->mv.v00);
            if (v[0] != 0.0f || v[2] != 0.0f) {
                if (o->mv.x3e == 0xFFFF || func_00121748(o->mv.v10, v) < 1.0f) {
                    v[2] = 0.0f;
                    v[0] = 0.0f;
                    continue;
                }
            } else if (o->mv.x3e == 0xFFFF) {
                func_002675a8(v, D_002C58A0);
                func_002675a8(o->mv.v40, o->mv.v00);
                o->mv.x3e = 0;
            }
            break;
        case 15:
            func_00267530(d, o->mv.v40, o->mv.v00);
            if (func_00120bf8(d) > 15.0f)
                o->x148->x90 = 0xFFFF;
            func_002675a8(o->mv.v40, o->mv.v00);
            break;
        case 18:
            if (o->mv.x6e == 0xFFFF) {
                if (o->mv.x30 & 0x20) {
                    o->mv.x6e = 0;
                } else if (!(fl0 & 0x20)) {
                    if (v[0] == 0.0f && v[2] == 0.0f) {
                        func_002675a8(o->mv.v40, o->mv.v00);
                        o->mv.x6e = 0;
                    } else {
                        v[0] = v[2] = 0.0f;
                        continue;
                    }
                }
            }
            break;
        }
        break;
    }
    func_00267530(v, o->mv.v40, o->mv.v00);
    o->fl.b.b53 = 1;
    o->fl.b.b56 = 1;
}

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

typedef f32 C02V4[4] __attribute__((aligned(16)));

typedef f32 C02M4[4][4] __attribute__((aligned(16)));

typedef struct {
    s32 cnt;
    s32 mesh;
    s32 *list;
} C02GEnt;

typedef struct {
    f32 min[3];
    f32 max[3];
    s32 x18;
    s32 n;
    C02GEnt e[8];
} C02GBox;

typedef struct {
    u16 poly;
    u16 i0;
    u16 i1;
} C02Edge;

typedef struct {
    u8 pad00[0x90];
    s32 x90;
    void *x94;
} C02Hit;

typedef struct {
    u8 pad00[0x10];
    C02V4 pos;
    u8 pad20[0x2C - 0x20];
    f32 x2c;
    u8 pad30[0x148 - 0x30];
    u8 *x148;
    u8 pad14c[0x2C0 - 0x14C];
    f32 x2c0;
    u8 pad2c4[0x324 - 0x2C4];
    f32 x324;
} C02Ob3;

typedef struct {
    u8 *p;
    u8 pad[12];
} C02MSlot;

extern C02MSlot D_003044E0[];
extern u8 D_002C58A0[];

f32 func_0015ca50(C02Ob3 *o);
f32 func_0015ca70(C02Ob3 *o);
void func_001178d0(C02GBox *b);
void func_002675a8(void *dst, void *src);
void func_00267530(void *dst, void *a, void *b);
void func_00105a30(s32 mesh, s32 id, f32 *out);
s32 func_00105ad0(s32 mesh, s32 id, C02V4 *out);
s32 func_00117948(C02Edge *e, s32 n, s32 *list, s32 mesh);
f32 func_00121550(f32 *out, f32 *p0, f32 *d0, f32 *p1, f32 *d1);
f32 func_00120c18(f32 *v);
void func_002674f0(f32 *out, f32 *a, f32 *b, f32 t);
void func_002673b8(void *dst, void *src);
void func_0015cac0(C02Ob3 *o, f32 *p, f32 *n, f32 *out);
s32 func_0015bcb8(C02Ob3 *o, f32 *p);
void func_00267440(void *dst, void *src);
void func_002672f8(void *dst, void *m, void *v);
void sceVu0CopyMatrix(void *dst, void *src);
void func_002673f8(void *dst, void *src);
s32 func_0015cb48(C02Ob3 *o);
s32 func_0014f658(C02Ob3 *o, s32 st);
void func_00130340(C02Ob3 *o, s32 f, f32 x);
void func_00130578(C02Ob3 *o, s32 f, f32 x);

s32 func_0015cc48(C02Ob3 *o, f32 *pos)
{
    C02GBox box;
    C02V4 d;
    C02V4 pc;
    C02V4 verts[4];
    C02Edge q;
    C02M4 m;
    C02V4 tri;
    C02V4 hit;
    C02V4 edge;
    C02V4 bn;
    C02V4 bp;
    C02V4 be;
    struct {
        s32 mesh;
        s32 id;
        f32 dist;
    } bst;
    s32 *list;
    s32 j;
    s32 i;
    s32 cnt;
    f32 r, a, b, top, t, dist;
    s32 k, nv, mesh;
    s32 *lp;
    u8 *mo;
    f32 *n;

    r = o->x2c0 + 30.0f;
    a = func_0015ca50(o);
    b = func_0015ca70(o);
    box.min[0] = o->pos[0] - r;
    box.min[1] = (o->pos[1] - a) + -30.0f;
    box.min[2] = o->pos[2] - r;
    box.max[0] = o->pos[0] + r;
    box.max[1] = (o->pos[1] - a) + 60.0f;
    box.max[2] = o->pos[2] + r;
    top = (o->x324 - a) - b;
    if (top < box.max[1]) {
        box.max[1] = top;
        if (top < box.min[1])
            return 0;
    }
    func_001178d0(&box);
    if (box.n == 0)
        return 0;
    func_002675a8(pc, pos);
    bst.dist = r;
    for (i = 0; i < box.n; i++) {
        cnt = box.e[i].cnt;
        list = box.e[i].list;
        mesh = box.e[i].mesh;
        for (j = 0; j < cnt; j++) {
            lp = &list[j];
            func_00105a30(mesh, *lp, tri);
            if (tri[1] > -0.5f)
                continue;
            q.poly = *lp;
            nv = func_00105ad0(mesh, *lp, verts);
            for (k = 0; k < nv; k++) {
                f32 *v0, *v1;
                s32 k2;
                q.i0 = k;
                k2 = (k + 1) % nv;
                q.i1 = k2;
                v0 = verts[k];
                v1 = verts[k2];
                func_00267530(edge, v1, v0);
                func_00267530(d, o->pos, v1);
                if (edge[0] * d[2] - edge[2] * d[0] < 0.0f)
                    continue;
                if (!func_00117948(&q, cnt, list, mesh))
                    continue;
                d[0] = edge[2];
                d[1] = 0;
                d[2] = -edge[0];
                t = func_00121550(hit, v0, edge, o->pos, d);
                if (hit[1] < box.min[1])
                    continue;
                if (box.max[1] < hit[1])
                    continue;
                if (t < 0.0f)
                    continue;
                if (1.0f < t)
                    continue;
                func_00267530(d, hit, o->pos);
                dist = func_00120c18(d);
                if (bst.dist <= dist)
                    continue;
                func_002675a8(bn, tri);
                func_002674f0(bp, v1, v0, t);
                func_002675a8(be, edge);
                bst.mesh = mesh;
                bst.id = *lp;
                bst.dist = dist;
            }
        }
    }
    if (r <= bst.dist)
        return 0;
    func_002673b8(edge, be);
    edge[3] = 0;
    func_0015cac0(o, bp, edge, hit);
    if (func_0015bcb8(o, hit))
        return 0;
    mo = 0;
    if (bst.mesh != -1)
        mo = D_003044E0[bst.mesh].p;
    ((C02Hit *)o->x148)->x90 = bst.id;
    ((C02Hit *)o->x148)->x94 = mo;
    bn[3] = 0;
    if (mo == 0) {
        f32 *n0 = bn;
        func_002675a8(o->x148 + 0x70, bp);
        func_002675a8(o->x148 + 0x60, n0);
        func_002675a8(o->x148 + 0x80, edge);
    } else {
        func_00267440(m, mo + 0xD0);
        n = bn;
        func_002672f8(o->x148 + 0x70, m, bp);
        sceVu0CopyMatrix(m, mo + 0xD0);
        func_002675a8(m[3], D_002C58A0);
        func_002673f8(m, m);
        func_002672f8(o->x148 + 0x60, m, n);
        func_002672f8(o->x148 + 0x80, m, edge);
    }
    func_0015cb48(o);
    func_0014f658(o, 15);
    func_00130340(o, 0x100000E, 0.0f);
    func_00130578(o, 0x4000000D, 0.0f);
    pos[3] = 0.0f;
    o->x2c = 0.0f;
    return 1;
}

/* needs make: uses rodata */


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

typedef struct {
    u32 x0;
    u8 pad4[0x3c - 4];
    s32 x3c;
    s32 x40;
} C02Ab;

typedef struct {
    u8 pad0[0x4c];
    u16 x4c;
} C02Kd;

typedef struct {
    u8 pad0[0x170];
    u64 x170;
} C02Ex;

typedef struct C02Ac C02Ac;

typedef struct {
    union { u64 x0; struct { u32 lo; C02Ac *x4; } w; } u;
    u64 x8;
} C02It;

typedef struct {
    u8 pad0[8];
    f32 *x8;
} C02Fx;

struct C02Ac {
    u32 x0;
    u8 pad4[0x6c - 4];
    C02Ab *x6c;
    u8 pad70[0x88 - 0x70];
    u32 x88;
    u8 pad8c[0x98 - 0x8c];
    void *x98;
    u8 pad9c[0x130 - 0x9c];
    C02Kd *x130;
    u8 pad134[0x148 - 0x134];
    C02Ex *x148;
    u8 pad14c[0x17c - 0x14c];
    u16 x17c;
};

extern u32 D_002C5958;
extern u32 D_00304B78;
extern u32 D_002E31A8;
extern u8 D_002E3190[];
s32 D_00F20000(s32, void *);
s32 func_001349d0(C02Ac *, C02It *);
C02It *func_00134928(C02Ac *);
void func_001350d0(C02It *);
s32 func_001347f0(C02Ac *, C02It *);
s32 func_00154e38(C02Ac *, s32, C02It *, s32);
s32 func_00141468(C02Ac *, s32);
void func_0013aaa0(void);
void func_001ea498(s32);
void func_00153f88(C02Ac *);
void func_00147790(s32);
void func_001586a8(s32);
void func_00141608(C02Ac *, s32);
s32 func_00132f20(s32);
C02Fx *func_00148768(s32, s32, C02Ac *, s32, f32);
f32 func_00132f00(C02Ac *);
s32 func_0013c318(s32);
void func_00241948(s32, s32);
void func_00137330(void *, C02Ac *, s32);
void func_00157a30(C02Ac *, s32, s32);
void *memset(void *, s32, u32);

void func_001550a0(C02Ac *o, s32 arg1)
{
    C02It *it;
    s32 hp;
    s32 max;
    s32 lock;
    s32 best;
    s32 hit;
    s32 k;
    s32 n;
    s32 h;
    C02Fx *fx;
    f32 f;
    f32 r;
    f32 *v;

    it = NULL;
    lock = 0;
    best = -1;
    hit = 0;
    hp = o->x6c->x3c;
    max = hp;
    for (;;) {
        if (it != NULL) {
            func_001350d0(it);
        }
        it = func_00134928(o);
        if (it == NULL) {
            break;
        }
        if ((s32)(it->u.x0 >> 5) & 1) continue;
        if (o->x0 & 0x200) continue;
        if ((o->x6c->x0 >> 2) & 1) continue;
        hp = func_001349d0(o, it);
        if (o->x88 & 0x20) continue;
        if (hp <= 0) {
            if (o->x130->x4c == 0) {
                if (((D_002C5958 >> 13) & 1) && (D_00304B78 & 0xf) == 11) {
                    D_00F20000(4, o);
                    hp = func_00141468(o, o->x6c->x40);
                    func_0013aaa0();
                } else if (!((o->x6c->x0 >> 2) & 1)) {
                    o->x6c->x0 |= 4;
                    lock = 1;
                }
            } else if ((D_002C5958 >> 17) & 1) {
                func_00141468(o, 1);
            } else {
                o->x88 |= 0x10;
            }
        }
        if ((u32)(((s32)(it->x8 >> 38) & 0xf) - 11) < 2 && o->x130->x4c != 0 && it->u.w.x4 != NULL
            && it->u.w.x4 != o && it->u.w.x4->x130->x4c < 10) {
            func_00157a30(o, 23, 0);
        }
        if (lock) {
            k = 4;
        } else {
            k = func_001347f0(o, it);
        }
        if ((o->x0 & 0x1000080) || ((D_002E31A8 >> 1) & 1)) {
            if (k != 6) {
                if (k != 7) continue;
            }
        }
        if (best < k) {
            if (k != 0) {
                if (func_00154e38(o, k, it, arg1)) {
                    hit = 1;
                }
            }
            best = k;
        }
    }
    if (lock) {
        func_001ea498(o->x17c);
        memset(D_002E3190, 0, 12);
        func_00157a30(o, 2, 0);
        return;
    }
    func_00153f88(o);
    if (best < 0) return;
    if (o->x130->x4c == 0) {
        switch (best) {
        case 3:
            func_00147790(1);
            func_001586a8(13);
            break;
        case 4:
        case 5:
            func_00147790(0);
            func_001586a8(13);
            break;
        case 6:
            func_00147790(6);
            break;
        case 7:
            func_00147790(5);
            break;
        }
        memset(D_002E3190, 0, 12);
    }
    if (hp < max) {
        n = (s32)(o->x148->x170 >> 33) & 7;
        if (n > 0) {
            func_00141608(o, (f32)(max - hp) * (f32)n);
        }
        hit = 1;
    }
    if ((o->x88 & 8) && hit) {
        fx = func_00148768(func_00132f20(6), 5, o, 0x8002, 0.0f);
        f = func_00132f00(o);
        v = fx->x8;
        v[2] = f;
        v[1] = f;
        v[0] = f;
    }
    h = func_0013c318(o->x130->x4c);
    if (h >= 0) {
        r = (f32)hp / (f32)max;
        if (r < 1.0f) {
            func_00241948(h, r < 0.5f ? 2 : r < 0.7999999523162842f ? 1 : 0);
        }
    }
    if (hp <= 0) {
        func_00157a30(o, 2, 0);
    } else if (o->x130->x4c != 0 && (n = (f32)o->x6c->x40 * 0.5f) < max && n >= hp) {
        func_00157a30(o, 20, 0);
    } else {
        switch (best) {
        case 3:
            func_00157a30(o, 0, 0);
            break;
        case 4:
        case 5:
            func_00157a30(o, 1, 0);
            break;
        }
    }
    if (o->x98 != NULL) {
        func_00137330(o->x98, o, -3);
    }
}

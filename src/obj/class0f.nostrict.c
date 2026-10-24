/* Object class 0x0F, without strict aliasing (docs/modules.md "Session 52"):
 * the handlers func_0015d560 registers in the class table D_00350D88
 * (func_0014f830(0x0F, ...): one 32-byte record of a parameter and seven
 * handlers per class) and their helpers. The rest is in class0f.c. Read from
 * the code, not proved by a boot. */
#include "common.h"
#include "platform/math.h"
#include "data/pieces/D_002C58A0.h"
#include "data/types/nostrict_text_00150000_h36.h"
#include "data/pieces/D_002BC0F0.h"
#include "data/pieces/D_00351BC8.h"
#include "data/pieces/D_002C58D0.h"
#include "data/pieces/D_003044E0.h"

/* func_0015cb48 (from hand/nostrict/text_00150000_h36.c). */
void func_002675a8(void *, void *);
typedef struct { u8 b0; u8 type; u16 bone; f32 off; f32 dy; f32 r; f32 h; } CylSrc;
typedef struct { u8 pad[4]; u8 n4, n5, n6, n7; u8 pad8[0xC]; CylSrc *cyl; CylSrc *cyl2; } CylHdr;
typedef struct { u8 pad[0xD0]; f32 m[4][4]; } Mtx0D0;
typedef struct { u8 pad[0x60]; f32 v60[4]; f32 v70[4]; f32 v80[4]; s32 x90; Mtx0D0 *mtx; u8 pad98[0x78]; f32 x110[4]; s32 x120; } Sub148;
typedef struct {
    u32 w0; u8 pad4[0xC]; f32 pos[4]; f32 x20[4]; f32 vel[4]; f32 sx, sy; u8 pad48[0x24]; struct { u8 pad[4]; f32 f4, f8; } *p6C; s32 x70; u8 pad74[0xC0];
    CylHdr *hdr; u8 pad138[0x10]; Sub148 *p148; u8 pad14c[4]; f32 rot; u8 pad154[0xC]; union { u64 d; u32 w; } x160; u8 pad168[0x1A6];
    u16 h30E; u8 pad310[0x60]; u64 flags; u8 pad378[0x2C]; u32 mask; u32 mask2;
    u8 pad3ac[0x14]; f32 x3C0[4];
} CylObj;
void func_002672f8(f32 *, void *, f32 *);
void func_0015cac0(void *, f32 *, f32 *, f32 *);
void func_00137688(void *, f32);
f32 atan2f(f32, f32);
s32 func_0015cb48(CylObj *o) {
    f32 v0[4], v1[4], v2[4];
    if (o->p148->mtx == 0) {
        func_002675a8(v0, o->p148->v70);
        func_002675a8(v1, o->p148->v80);
        func_002675a8(v2, o->p148->v60);
    } else {
        func_002672f8(v0, o->p148->mtx->m, o->p148->v70);
        func_002672f8(v1, o->p148->mtx->m, o->p148->v80);
        func_002672f8(v2, o->p148->mtx->m, o->p148->v60);
    }
    func_0015cac0(o, v0, v1, o->pos);
    o->rot = atan2f(v1[2], -v1[0]);
    func_00137688(o, o->rot);
    return v2[1] < -0.5f;
}

/* func_0015cc48 (from hand/nostrict/text_00130000_c02.c). */
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
f32 func_0015ca50(C02Ob3 *o);
f32 func_0015ca70(C02Ob3 *o);
void func_001178d0(C02GBox *b);
void func_00267530(void *dst, void *a, void *b);
void func_00105a30(s32 mesh, s32 id, f32 *out);
s32 func_00105ad0(s32 mesh, s32 id, C02V4 *out);
s32 func_00117948(C02Edge *e, s32 n, s32 *list, s32 mesh);
f32 func_00121550(f32 *out, f32 *p0, f32 *d0, f32 *p1, f32 *d1);
f32 func_00120c18(f32 *v);
void func_002674f0(f32 *out, f32 *a, f32 *b, f32 t);
void func_002673b8(void *dst, void *src);
s32 func_0015bcb8(C02Ob3 *o, f32 *p);
void func_00267440(void *dst, void *src);
void sceVu0CopyMatrix(void *dst, void *src);
void func_002673f8(void *dst, void *src);
s32 func_0014f658(C02Ob3 *o, s32 st);
void func_00130340(C02Ob3 *o, s32 f, f32 x);
void func_00130578(C02Ob3 *o, s32 f, f32 x);
#define func_0015cac0 ((void (*)(C02Ob3 *o, f32 *p, f32 *n, f32 *out)) func_0015cac0)
#define func_002672f8 ((void (*)(void *dst, void *m, void *v)) func_002672f8)
#define func_0015cb48 ((s32 (*)(C02Ob3 *o)) func_0015cb48)
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
        mo = D_003044E0[bst.mesh].x0;
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
        func_002675a8(m[3], &D_002C58A0);
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
#undef func_0015cac0
#undef func_002672f8
#undef func_0015cb48

/* func_0015d2c8 (from hand/nostrict/text_00150000_h36.c). */
typedef struct { s32 type; f32 r; f32 h; s32 idx; f32 pos[4] __attribute__((aligned(16))); } Cyl;
void *func_001230a0(void *);
void func_00267518(f32 *, f32 *, f32 *);
void func_00267560(f32 *, f32 *, f32);
s32 func_00137450(void *);
s32 func_00105b10(s32, s32);
void func_0015bad0(CylObj *, void *, Cyl *); /* src/obj/cylhit.nostrict.c */
s32 func_0015bb88(Cyl *, CylObj *, Cyl *);
#define func_0015ca50 ((f32 (*)(void *)) func_0015ca50)
s32 func_0015d2c8(CylObj *o) {
    Cyl c;
    CylObj *p;
    if (func_00105b10(func_00137450(o->p148->mtx), o->p148->x90) != 1) return 0;
    p = 0;
    func_0015bad0(o, o->hdr->cyl, &c);
    func_00267560(c.pos, o->vel, 85.0f);
    c.pos[1] = -func_0015ca50(o);
    func_00267518(c.pos, c.pos, o->pos);
    while ((p = func_001230a0(p)) != 0) {
        if (p == o) continue;
        if (func_0015bb88(&c, p, 0)) return 0;
    }
    return 1;
}
#undef func_0015ca50

/* func_0015d3b8 (from hand/nostrict/text_00150000_h36.c). */
typedef struct { u8 pad[0xC]; void *cb; } Task;
void func_00130398(void *, s32, f32);
void func_0015db80(void *);
void func_0015d1d0(void *, f32 *);
void func_0015d248();
#define func_0014f658 ((void (*)(void *, s32)) func_0014f658)
#define func_00130578 ((Task *(*)(void *, s32, f32)) func_00130578)
void func_0015d3b8(CylObj *o, f32 *s) {
    f32 t;
    if (o->p148->x90 != 0xFFFF && func_0015cb48(o)) {
        func_002675a8(o->x20, o->vel);
        o->x20[3] = 0;
        t = o->x20[3];
        if (!(t < s[3])) return;
        if (!(s[1] < t)) return;
        if (func_0015d2c8(o)) {
            func_0015db80(o);
            return;
        }
        func_00130398(o, 0x100000F, t);
        func_00130578(o, 0x40000006, t)->cb = func_0015d248;
        func_0014f658(o, 16);
        return;
    }
    func_0015d1d0(o, s);
}
#undef func_0014f658
#undef func_00130578


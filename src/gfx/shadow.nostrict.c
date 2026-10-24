/* Projected shadows (docs/renderer-spec.md): the light-space matrix
 * (func_00127b98), the shadow models drawn into a texture (func_00127568,
 * func_00127960, func_00127c20; their records D_004F82C0), the GS packets
 * for the shadow texture (func_001284a0, func_00128738 on D_002E27E0) sent
 * through DMA (func_001274c8, func_00127500), func_00128218 an object's
 * shadow on the ground ray, func_00128b20 the reset. Flag mode: nostrict
 * (the other modes are in the sibling files). Read from the code, not proved
 * by a boot (docs/modules.md "Session 54"). */
#include "common.h"
#include "platform/vu.h"
#include "data/pieces/D_002C5968.h"
#include "data/bss_004E.h"
#include "data/bss_004F.h"
#include "data/types/nostrict_text_00110000_s6_04_p.h"
#include "data/pieces/D_002C5960.h"
#include "data/pieces/D_002C58B0.h"
#include "data/types/nostrict_text_00110000_s6_04.h"
#include "data/pieces/D_002C5C48.h"
#include "data/pieces/D_002C5C80.h"
#include "data/pieces/D_002C5910.h"
#include "data/bss_0052.h"
#include "data/pieces/D_002BC0F0.h"
#include "data/pieces/D_00308CDC.h"
#include "data/pieces/D_002E27C8.h"
#include "data/pieces/D_002E26A0.h"
#include "data/types/fvec.h"
#include "data/pieces/D_002BD250.h"
#include "data/pieces/D_002BBFA0.h"
#include "data/pieces/D_002C58D0.h"
#include "data/pieces/D_002C58A0.h"

/* func_00127568 (from hand/nostrict/text_00110000_s6_04.c). */
void func_00114f50(s32, void *);
s32 *func_0015ed80(s32, void (*)(void));
void func_00127500(void);
u32 *func_00121e28(s32, s32 *);
s32 func_00115018(void *, s32, f32 (*)[4]);
void func_00115058(void *, s32, f32 (*)[4]);
void func_00115098(void *, s32, f32 *);
f32 func_00120ef0(f32 *, void *, f32 *);
void func_00127568(s32 *list, s32 n, void *a2, void *a3, void *a4, f32 scale) {
    f32 v[4][4];
    f32 c[4][4];
    f32 out[4];
    f32 nrm[4];
    u32 *base;
    u32 *tag1;
    u32 *tag2;
    u32 *q;
    s32 count;
    s32 total;
    s32 k;
    s32 i;
    s32 j;
    s32 m;
    s32 idx;

    count = 0;
    func_00114f50(D_004F82C4 + D_004F82C0++, a4);
    tag1 = 0;
    tag2 = 0;
    base = func_00121e28(n * 224 + 16, func_0015ed80(D_004F82C4 + D_004F82C0++, func_00127500) + 4);
    q = base + 4;
    for (i = 0; i < n; i++) {
        k = func_00115018(a4, list[i], v);
        func_00115058(a4, list[i], c);
        func_00115098(a4, list[i], nrm);
        if (PlatVu0InnerProduct(nrm, a3) >= 0.0f) continue;
        total = count + k;
        if (total > 50) {
            *tag1 = ((count * 3 + 1) << 16) | 0x6C008000;
            *tag2 = count | 0x8000;
            *q++ = 0x17000000;
            *q++ = 0;
            *q++ = 0;
            *q++ = 0;
            count = 0;
            total = k;
        }
        if (count == 0) {
            *q++ = 0x13000000;
            *q++ = 0;
            *q++ = 0;
            tag1 = q++;
            tag2 = q++;
            *q++ = 0x312E4000;
            *q++ = 1042;
            *q++ = 0;
        }
        for (j = 0; j < k; j++) {
            if (k == 3) idx = j; else idx = j ^ (j >> 1);
            for (m = 0; m < 3; m++) *(f32 *)q++ = v[idx][m];
            *(f32 *)q++ = 1.0f;
            for (m = 0; m < 4; m++) *(f32 *)q++ = 128.0f;
            func_00120ef0(out, a2, c[idx]);
            *(f32 *)q++ = out[0] / scale + 0.5f;
            *(f32 *)q++ = out[1] / scale + 0.5f;
            *(f32 *)q++ = 1.0f;
            if (j < 2) {
                *q = 0;
            } else if (j == 2) {
                *q = 0xBF800020;
            } else {
                *q = 0x3F800020;
            }
            q++;
        }
        count = total;
    }
    if (count > 0) {
        *tag1 = ((count * 3 + 1) << 16) | 0x6C008000;
        *tag2 = count | 0x8000;
        *q++ = 0x17000000;
        *q++ = 0x13000000;
        *q++ = 0;
        *q++ = 0;
    }
    *(u64 *)base = (((u8 *)q - (u8 *)base + 15) / 16 - 1) | 0x70000000;
}

/* func_00127960 (from hand/nostrict/text_00120000_h54.c). */
typedef struct {
    s32 f0; s32 f4; s32 f8;
    s8 c[4]; s8 d[4];
    s32 f14;
    s8 e[4]; s8 f[4];
    s32 f20; s32 f24; s32 f28; s32 f2c; s32 f30; s32 f34;
    u64 f38; u64 f40;
} Pkt;
typedef struct { u32 f0; u8 pad[0x114]; f32 f118; u8 p2[0x14c-0x11c]; s32 *f14c; u8 p3[0x15c-0x150]; s32 f15c; u8 p4[0x390-0x160]; s32 f390; } E1;
extern f32 func_00135ca0(f32);
extern void func_001621e0(s32, s32, Pkt *, E1 *);
void func_00127960(E1 *e, s32 a1, s32 a2) {
    Pkt p;
    s32 i;
    s32 *q;
    u64 k;
    if (e->f0 & 0x100) {
        p.c[0] = 0x80;
        p.c[1] = 0x80;
        p.c[2] = 0x80;
        p.c[3] = 0x80;
        p.f0 = 0x101;
        p.d[0] = D_002BC0F0.cam.f10;
        p.d[1] = D_002BC0F0.cam.f14;
        p.d[2] = D_002BC0F0.cam.f18;
        p.d[3] = func_00135ca0(e->f118);
    } else {
        p.f0 = 0x101;
        p.c[3] = a2;
        p.c[0] = 0; p.c[1] = 0; p.c[2] = 0;
        p.d[0] = 0x80; p.d[1] = 0x80;
        p.d[2] = 0x80;
        p.d[3] = 0xff;
    }
    p.f4 = 0;
    q = &D_004F82C0;
    p.f8 = D_004F82C4 + *q;
    *q += 10;
    p.f20 = 0;
    p.f28 = e->f390;
    if (e->f390 & 0x40000000) p.f28 = -1;
    p.f2c = 0;
    if (e->f14c && e->f14c[0] && (e->f0 & 0x4000)) {
        p.f14 = e->f14c[1];
        for (i = 0; i < 4; i++) {
            p.e[i] = p.c[i];
            p.f[i] = p.d[i];
        }
    } else {
        p.f14 = 0;
    }
    k = 0x1000401d0LL;
    p.f38 = 0x3a0001c0;
    p.f40 = k;
    p.f30 = 0;
    p.f34 = 0;
    func_001621e0(e->f15c, a1, &p, e);
}

/* func_00127c20 (from hand/nostrict/text_00110000_c01.c). */
typedef FMtx4 C01Mat;
typedef struct {
    u8 pad000[0x40];
    f32 x40[3];
    u8 pad04c[0x50 - 0x4c];
    f32 x50;
    f32 x54;
    f32 x58;
    u8 pad05c[0xc0 - 0x5c];
    f32 xc0;
    f32 xc4;
    f32 xc8;
    u8 pad0cc[0xd0 - 0xcc];
    C01Mat xd0;
    u8 pad110[0x2c4 - 0x110];
    f32 x2c4;
    u8 pad2c8[0x2cc - 0x2c8];
    s32 x2cc;
    u8 pad2d0[0x320 - 0x2d0];
    f32 x320;
    f32 x324;
    f32 x328;
    u8 pad32c[0x370 - 0x32c];
    u64 x370;
    u8 pad378[0x410 - 0x378];
    f32 x410;
    f32 x414;
} C01Obj4;
typedef struct { f32 v[6]; u16 n; u8 pad[6]; } C01Box;
typedef struct { u8 pad[0x10]; void *x10; } C01Task;
typedef struct { u8 b[0x150]; } C01E150;
typedef struct { u8 b[0x220]; } C01E220;
extern s32 D_002E27E0[];
extern u8 D_002E2800[];
extern C01E150 D_004F7820[];
extern C01E220 D_004F7C10[];
void func_001274c8(void);
void func_00121620(C01Mat, f32 *, f32, f32, f32, f32);
s32 func_0024edf0(void *, f32 (*)[4]);
void func_00114f18(C01Box *, s32);
void func_00127b98(C01Obj4 *, C01Mat, f32);
#define C01MAX(a, b) ((a) < (b) ? (b) : (a))
#define func_0015ed80 ((C01Task *(*)(s32, void (*)(void))) func_0015ed80)
#define func_00127568 ((void (*)(void *, s32, C01Mat, f32 *, s32, f32)) func_00127568)
void func_00127c20(C01Obj4 *o, f32 *pos, f32 scale) {
    void *tex = &D_002BD250;
    C01Box box;
    C01Mat m;
    C01Mat m2;
    C01Mat m3;
    f32 e[4];
    f32 dir[4];
    f32 pts[8][4];
    C01Mat m4;
    f32 dist;
    f32 t;
    f32 sz;
    f32 h;
    f32 r;
    f32 *sp;
    f32 *row;
    s32 i;
    C01Task *task;

    dist = o->x324 - o->x54;
    if (dist >= 300.0f) return;
    if (dist < 0.0f) dist = 0.0f;
    D_004F82C4 = 60000;
    func_00121620(m, pos, o->xc0, o->xc4, o->xc8, o->xc0 * o->x320 + o->xc4 * o->x324 + o->xc8 * o->x328);
    PlatVu0MulMatrix(m, m, o->xd0);
    sp = o->x40;
    row = m[0];
    for (i = 0; i < 3; i++) {
        PlatVu0ScaleVectorXYZ(row, row, *sp++);
        row += 4;
    }
    h = o->x2c4 * o->x40[1];
    r = o->x410;
/*P*/
    box.v[1] = o->x54 - h;
    box.v[4] = o->x324 + h;
    box.v[0] = o->x50 - r;
    box.v[3] = o->x50 + r;
    box.v[2] = o->x58 - r;
    box.v[5] = o->x58 + r;
/*Q*/
    for (i = 0; i < 8; i++) {
        pts[i][0] = (i & 1) ? box.v[0] : box.v[3];

        pts[i][1] = (i & 2) ? box.v[1] : box.v[4];

        pts[i][2] = (i & 4) ? box.v[2] : box.v[5];

        pts[i][3] = 1.0f;
    }
    if (func_0024edf0(D_002BBFA0, pts)) return;
    func_00114f18(&box, o->x2cc);
    if (!box.n) return;
    PlatVu0CopyVector(dir, pos);
    PlatVu0Normalize(dir, dir);
    sz = C01MAX(C01MAX(o->x40[2], (o->x40[0] > o->x40[1] ? o->x40[0] : o->x40[1])), 1.0f);
    sz *= C01MAX(o->x414, o->x410 * 2.0f);
    t = dist / 300.0f;
    sz /= D_002E27E0[(s32)(o->x370 >> 40) & 3];
    sz *= t * 8.0f + 1.0f;
    PlatVu0ScaleVector(dir, dir, sz * 32768.0f);
    PlatVu0SubVector(e, &o->x50, dir);
    e[1] -= o->x414 * 0.5f;
    PlatVu0CameraMatrix(m4, e, dir, D_002E2800);
    func_00121620(m, pos, pos[0], pos[1], pos[2], pos[0] * o->x50 + pos[1] * (o->x54 - o->x414 * 0.5f) + pos[2] * o->x58);
    PlatVu0CopyMatrix(m3, D_002C58D0);
    m3[3][0] = -o->x50;
    m3[3][1] = o->x414 * 0.5f - o->x54;
    m3[3][2] = -o->x58;
    PlatVu0MulMatrix(m, m3, m);
    PlatVu0CopyMatrix(m2, m4);
    m2[0][3] = m2[1][3] = m2[2][3] = m2[3][0] = m2[3][1] = m2[3][2] = 0.0f;
    m2[3][3] = 1.0f;
    PlatVu0MulMatrix(m, m2, m);
    task = func_0015ed80(D_004F82C4 + D_004F82C0++, func_001274c8);
    task->x10 = &D_004F7820[(s32)(o->x370 >> 40) & 3];
    func_00127b98(o, m4, (s32)((1.0f - t) * 64.0f * scale));
    task = func_0015ed80(D_004F82C4 + D_004F82C0++, func_001274c8);
    task->x10 = &D_004F7C10[(s32)(o->x370 >> 40) & 3];
    func_00127568(tex, box.n, m, pos, o->x2cc, sz * 256.0f);
}
#undef func_0015ed80
#undef func_00127568
#undef C01MAX

/* func_00128218 (from hand/nostrict/text_00120000_h54.c). */
typedef FVec4 V4_28218;
typedef struct { V4_28218 a; V4_28218 b; V4_28218 c; s16 f30; s16 pad32; s32 f34; } Ray2;
typedef Lt64_2c5c80 Lt2;
typedef union { u64 x; struct { u32 lo:24; u32 b3:8; u32 b4:8; u32 k:2; u32 hi:22; } b; } F370;
typedef struct { u8 pad[0x50]; V4_28218 pos; u8 p60[0x2c4-0x60]; f32 f2c4; u8 p2c8[4]; s32 f2cc; u8 p2d0[0x320-0x2d0]; V4_28218 v320; u8 p330[0x370-0x330]; F370 f370; } E2;
extern s32 func_001232f0(E2 *);
extern void func_00121fc4(V4_28218 *, V4_28218 *);
extern void func_00118668(Ray2 *);
#define func_00127c20 ((void (*)(E2 *, V4_28218 *, f32)) func_00127c20)
void func_00128218(E2 *e, f32 k) {
    V4_28218 v;
    Ray2 r;
    Lt2 *l;
    s32 i;
    if (e->f370.b.k == 3) return;
    if (!func_001232f0(e)) {
        PlatVu0CopyVector(&r.a, &e->pos);
        r.b.w = r.a.w = 1.0f;
        r.b.x = 0;
        r.b.z = 0;
        r.a.y -= e->f2c4;
        r.b.y = e->f2c4 + 300.0f;
        func_00118668(&r);
        if (r.f30 < 0) return;
        PlatVu0CopyVector(&e->v320, &r.c);
        e->f2cc = r.f34;
    }
    k *= e->f370.b.b3 * 0.0078125f;
    l = &D_002C5C80;
    for (i = 0; i < 31; i++, l++) {
        if (!(l->flags & 4)) continue;
        switch (l->kind) {
        case 2:
            PlatVu0CopyVector(&v, &l->dir);
            v.w = 1.0f;
            func_00127c20(e, &v, k);
            break;
        case 3:
        case 5:
            PlatVu0CopyVector(&v, &e->pos);
            v.y -= e->f2c4;
            PlatVu0SubVector(&v, &v, &l->pos);
            func_00121fc4(&v, &v);
            if (v.w < l->radius && v.y > 0.5f) {
                v.w = 1.0f;
                func_00127c20(e, &v, k);
            }
            break;
        }
    }
}
#undef func_00127c20


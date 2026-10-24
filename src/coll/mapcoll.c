/* Collision against the room's map triangles (a guess at the name),
 * 0x00114f18-0x0011a068: D_002A6238 holds the triangles (four vertex
 * indices into D_002A624C and a plane distance), D_002A6244 the tree nodes
 * with their boxes; func_00115940 culls a triangle against the query box
 * D_002C1260 with VU0, func_00116368 walks the nodes and calls the per-kind
 * filters of D_002BD178 / D_002BD1A8 (func_00115e90 ...) that append to the
 * hit list D_002BD250, func_00115408 gives a triangle's height under a point
 * and func_001166e8 is the large move-and-slide query.  The map collision
 * models' set up (func_00114f50 with D_003044D8) is here too.  Read from the
 * code, not proved by a boot (docs/modules.md "Session 55"). */
#include "m2c.h"
#include "data/pieces/D_002BCB60.h"
#include "data/pieces/D_002C1260.h"
#include "data/pieces/D_002BBDF4.h"
#include "vm/script_vm.h"
#include "common.h"
#include "platform/vu.h"
#include "data/bss_004D.h"
#include "data/bss_004E.h"
#include "data/types/text_00110000_h29_p.h"
#include "data/pieces/D_002A6208.h"
#include "data/types/text_00110000_h29_p3.h"
#include "data/pieces/D_002BBD90.h"
#include "data/pieces/D_002BBD48.h"
#include "data/pieces/D_002BBDF0.h"
#include "data/types/text_00110000_h29.h"
#include "data/pieces/D_002BCCA0.h"
#include "data/pieces/D_002BCDA0.h"
#include "data/pieces/D_002BCDAC.h"
#include "data/pieces/D_002A3F3C.h"
#include "data/pieces/D_002BCCE0.h"
#include "data/pieces/D_003044D8.h"
#include "data/pieces/D_002BD250.h"
#include "data/types/text_00110000_h3.h"
#include "data/types/text_00110000_h3_p.h"
#include "data/pieces/D_002C5958.h"
#include "data/pieces/D_002C5968.h"
#include "data/pieces/D_002B6778.h"
#include "data/pieces/D_002BBDE0.h"
#include "data/pieces/D_002BD118.h"
#include "data/pieces/D_002BBFA0.h"
#include "data/pieces/D_0029B280.h"
#include "data/types/text_00110000_h29_p2.h"
#include "data/pieces/D_002BBDF8.h"
#include "data/types/text_00110000_h52.h"
#include "data/pieces/D_002BBF20.h"
#include "data/pieces/D_002BBEE0.h"
#include "data/pieces/D_002BBEA0.h"
#include "data/pieces/D_002BBE60.h"
#include "data/pieces/D_002BBE20.h"
#include "data/pieces/D_002BBF60.h"
#include "data/pieces/D_0037A378.h"
#include "data/pieces/D_002BC070.h"
#include "data/types/text_00110000_h52_p.h"
#include "data/pieces/D_0048C630.h"
#include "data/pieces/D_0048C690.h"
#include "data/pieces/D_0048C6F0.h"
#include "data/pieces/D_002A6238.h"
#include "data/pieces/D_002A624C.h"
#include "data/pieces/D_002BCB40.h"
#include "data/pieces/D_002BCB50.h"
#include "data/pieces/D_002A623C.h"
#include "data/pieces/D_002A6244.h"
#include "data/pieces/D_002BBFE0.h"
#include "data/pieces/D_002BC020.h"
#include "data/pieces/D_002E2700.h"
#include "data/pieces/D_002E26A0.h"
#include "data/pieces/D_002A3F48.h"
#include "data/types/text_00110000_b01.h"
#include "data/types/text_00110000_b01_p2.h"
#include "data/types/text_00110000_b01_p.h"
#include "data/pieces/D_002BCD60.h"
#include "data/pieces/D_002BC0A8.h"
#include "data/types/text_00110000_s7_w12.h"

/* func_00114f18 (from auto/text_00110000_6.c). */
s32 func_0011b0c0(s32, s32);
void func_001178b8(s32);
void func_00114f18(s32 arg0, s32 arg1) {
    if (arg1 == -1) {
        func_001178b8(arg0);
        return;
    }
    func_0011b0c0(arg1, arg0);
}

/* func_00114f50 (from hand/text_00110000_h29.c). */
typedef struct { u8 b[0x50]; } W29E50;
extern W29E50 D_004D9380[2];
extern W29E50 D_004D9420[0x40][2];
typedef struct { u8 pad[0x10]; void *x10; } W29Task;
extern s32 D_00351BD0;
void func_00108d90(void);
W29Task *func_0015ed80(void *, void (*)(void));
void func_00114db0(s32, s32);
void func_00114f50(void *a, s32 i) {
    if (i == -1) {
        func_0015ed80(a, func_00108d90)->x10 = &D_004D9380[D_00351BD0];
        return;
    }
    func_00114db0(i, D_003044D8[i].x0);
    func_0015ed80(a, func_00108d90)->x10 = &D_004D9420[i][D_00351BD0];
}

/* func_00115018 (from auto/text_00110000_6.c). */
s32 func_00104c38(s32, s32);
s32 func_0011a868(s32, s32, s32);
s32 func_00115018(s32 arg0, s32 arg1, s32 arg2) {
    if (arg0 == -1) {
        return func_00104c38(arg1, arg2);
    }
    return func_0011a868(arg0, arg1, arg2);
}

/* func_00115058 (from auto/text_00110000_6.c). */
s32 func_0011aa18(s32, s32, s32);
void func_00115058(s32 arg0, s32 arg1, s32 arg2) {
    if (arg0 == -1) {
        func_00104c38(arg1, arg2);
        return;
    }
    func_0011aa18(arg0, arg1, arg2);
}

/* func_00115098 (from auto/text_00110000_6.c). */
void func_00104f10(s32, s32);
void func_0011a978(s32, s32, s32);
void func_00115098(s32 arg0, s32 arg1, s32 arg2) {
    if (arg0 == -1) {
        func_00104f10(arg1, arg2);
        return;
    }
    func_0011a978(arg0, arg1, arg2);
}

/* func_001150d8 (from hand/text_00110000_h3.c). */
typedef struct {
    f32 v[4];
    s32 x10;
    f32 x14;
    s32 x18;
    u8 pad1c[8];
    f32 x24;
    u8 pad28[8];
    s16 x30;
    u8 pad32[14];
} Query40;
void func_00118378();
#define func_00118378 ((void (*)(void *, s32, s32, s32)) func_00118378)
void func_001150d8(u8 *a) {
    Query40 q;
    PlatVu0CopyVector(&q, a + 64);
    q.v[1] = *(f32 *)(a + 68) - 500.0f;
    q.x10 = 0;
    q.x14 = 1000000.0f;
    q.x18 = 0;
    func_00118378(&q, 6, 1, -1);
    if (q.x30 != -1) {
        *(f32 *)(a + 52) = q.x24;
    }
}
#undef func_00118378

/* func_00115158 (from hand/text_00110000_s6_02.c). */
typedef f32 V4_52[4] __attribute__((aligned(16)));
static inline void v52_sub(f32 *d, f32 *a, f32 *b) {
    __asm__ volatile(
        "lqc2 $vf4, 0(%1)\n"
        "lqc2 $vf5, 0(%2)\n"
        "vsub.xyzw $vf6xyzw, $vf4xyzw, $vf5xyzw\n"
        "sqc2 $vf6, 0(%0)\n"
        "nop\n"
        : : "r"(d), "r"(a), "r"(b) : "memory");
}
static inline f32 v52_dot(f32 *a, f32 *b) {
    f32 r;
    __asm__ volatile(
        "lqc2 $vf4, 0(%1)\n"
        "lqc2 $vf5, 0(%2)\n"
        "vmul.xyz $vf5xyz, $vf4xyz, $vf5xyz\n"
        "vaddy.x $vf5x, $vf5x, $vf5y\n"
        "vaddz.x $vf5x, $vf5x, $vf5z\n"
        "qmfc2 $2, $vf5\n"
        "mtc1 $2, %0\n"
        : "=f"(r) : "r"(a), "r"(b) : "$2");
    return r;
}
s32 func_00115158(f32 *a, f32 *b, f32 *n) {
    V4_52 v;
    v52_sub(v, b, a);
    if (v52_dot(v, n) >= 0.0f) return 0;
    return 1;
}

/* func_001151a8 (from hand/text_00110000_s6_02.c). */
#define func_00104f10 ((void (*)(s32, V4_52)) func_00104f10)
s32 func_001151a8(s32 id, f32 *n) {
    V4_52 v;
    func_00104f10(id, v);
    if (v52_dot(v, n) >= 0.0f) return 0;
    return 1;
}
#undef func_00104f10

/* func_00115200 (from hand/text_00110000_h29.c). */
static inline f32 w29_dot(void *a, void *b) {
    f32 r;
    __asm__ volatile(
        "lqc2 $vf4, 0(%1)\n"
        "lqc2 $vf5, 0(%2)\n"
        "vmul.xyz $vf5xyz, $vf4xyz, $vf5xyz\n"
        "vaddy.x $vf5x, $vf5x, $vf5y\n"
        "vaddz.x $vf5x, $vf5x, $vf5z\n"
        "qmfc2 $2, $vf5\n"
        "mtc1 $2, %0\n"
        : "=f"(r) : "r"(a), "r"(b) : "$2");
    return r;
}
static inline void w29_scale(void *d, void *s, f32 t) {
    __asm__ volatile(
        "lqc2 $vf4, 0(%1)\n"
        "lw $8, 0(%2)\n"
        "qmtc2 $8, $vf5\n"
        "vmulx.xyz $vf4xyz, $vf4xyz, $vf5x\n"
        "sqc2 $vf4, 0(%0)\n"
        : : "r"(d), "r"(s), "r"(&t) : "$8", "memory");
}
static inline void w29_add(void *d, void *a, void *b) {
    __asm__ volatile(
        "lqc2 $vf4, 0(%1)\n"
        "lqc2 $vf5, 0(%2)\n"
        "vadd.xyzw $vf6xyzw, $vf4xyzw, $vf5xyzw\n"
        "sqc2 $vf6, 0(%0)\n"
        "nop\n"
        : : "r"(d), "r"(a), "r"(b) : "memory");
}
s32 func_00115200(void *p0, void *dir, void *p1, void *n, void *out) {
    f32 den, t;
    den = w29_dot(n, dir);
    if (den >= 0.0f) return 0;
    t = (w29_dot(n, p1) - w29_dot(n, p0)) / den;
    if (t > 1.0f) return 0;
    w29_scale(out, dir, t);
    w29_add(out, out, p0);
    return 1;
}

/* func_001152c8 (from hand/text_00110000_h29.c). */
void func_00104eb0(void *, W29V4 *);
#define func_00104f10 ((void (*)(void *, W29V4 *)) func_00104f10)
s32 func_001152c8(void *obj, void *p0, void *dir, void *out) {
    W29V4 nrm, pt;
    f32 den, t;
    func_00104f10(obj, &nrm);
    den = w29_dot(&nrm, dir);
    if (den >= 0.0f) return 0;
    func_00104eb0(obj, &pt);
    t = (w29_dot(&nrm, &pt) - w29_dot(&nrm, p0)) / den;
    if (t < 0.0f) return 0;
    if (t > 1.0f) return 0;
    w29_scale(out, dir, t);
    w29_add(out, out, p0);
    return 1;
}
#undef func_00104f10

/* func_00115408 (from hand/text_00110000_h52.c). */
s32 func_00104ae0(s32, V4_52 *);
f32 fabsf(f32);
static inline void v52_cross(f32 *d, f32 *a, f32 *b) {
    __asm__ volatile(
        "lqc2 $vf4, 0(%1)\n"
        "lqc2 $vf5, 0(%2)\n"
        "vopmula.xyz ACC, $vf4xyz, $vf5xyz\n"
        "vopmsub.xyz $vf6xyz, $vf5xyz, $vf4xyz\n"
        "vsub.w $vf6w, $vf6w, $vf6w\n"
        "sqc2 $vf6, 0(%0)\n"
        "nop\n"
        : : "r"(d), "r"(a), "r"(b) : "memory");
}
static inline void v52_normalize(f32 *d, f32 *s) {
    __asm__ volatile(
        "lqc2 $vf4, 0(%1)\n"
        "vmul.xyz $vf5xyz, $vf4xyz, $vf4xyz\n"
        "vaddy.x $vf5x, $vf5x, $vf5y\n"
        "vaddz.x $vf5x, $vf5x, $vf5z\n"
        "vsqrt Q, $vf5x\n"
        "vwaitq\n"
        "vaddq.x $vf5x, $vf0x, Q\n"
        "vdiv Q, $vf0w, $vf5x\n"
        "vsub.xyzw $vf6xyzw, $vf0xyzw, $vf0xyzw\n"
        "vwaitq\n"
        "vmulq.xyz $vf6xyz, $vf4xyz, Q\n"
        "sqc2 $vf6, 0(%0)\n"
        "nop\n"
        : : "r"(d), "r"(s) : "memory");
}
#define func_00104eb0 ((void (*)(s32, V4_52)) func_00104eb0)
#define func_00104f10 ((void (*)(s32, V4_52)) func_00104f10)
void func_00115408(s32 id, f32 *pos, f32 *out, s32 mode) {
    V4_52 pt, e, f, n;
    V4_52 v[4];
    f32 d;
    func_00104eb0(id, pt);
    func_00104f10(id, n);
    if (mode != 1 && fabsf(n[1]) > 0.0999999940395355224609375f) {
        *out = (-D_002A6238[id].d - (n[0] * pos[0] + n[2] * pos[2])) / n[1];
        return;
    }
    func_00104ae0(id, v);
    v52_sub(e, v[0], v[1]);
    v52_sub(f, v[2], v[1]);
    v52_cross(n, e, f);
    v52_normalize(n, n);
    d = v52_dot(n, pt);
    if (n[1] != 0.0f) {
        *out = (d - (n[0] * pos[0] + n[2] * pos[2])) / n[1];
    } else {
        *out = 1000000.0f;
    }
}
#undef func_00104eb0
#undef func_00104f10

/* func_00115600 (from hand/text_00110000_h29.c). */
static inline void w29_sub(void *d, void *a, void *b) {
    __asm__ volatile(
        "lqc2 $vf4, 0(%1)\n"
        "lqc2 $vf5, 0(%2)\n"
        "vsub.xyzw $vf6xyzw, $vf4xyzw, $vf5xyzw\n"
        "sqc2 $vf6, 0(%0)\n"
        "nop\n"
        : : "r"(d), "r"(a), "r"(b) : "memory");
}
static inline void w29_outer(void *d, void *a, void *b) {
    __asm__ volatile(
        "lqc2 $vf4, 0(%1)\n"
        "lqc2 $vf5, 0(%2)\n"
        "vopmula.xyz ACC, $vf4, $vf5\n"
        "vopmsub.xyz $vf6, $vf5, $vf4\n"
        "vsub.w $vf6w, $vf6w, $vf6w\n"
        "sqc2 $vf6, 0(%0)\n"
        "nop\n"
        : : "r"(d), "r"(a), "r"(b) : "memory");
}
extern s32 D_002BD150[];
extern s32 D_002BD160[];
#define func_00104ae0 ((s32 (*)(void *, W29V4 *)) func_00104ae0)
s32 func_00115600(void *obj, void *p) {
    W29V4 e, d, c, v[4];
    s32 n, i, *idx;
    n = func_00104ae0(obj, v);
    if (n == 3) idx = D_002BD150;
    else idx = D_002BD160;
    for (i = 0; i < n; i++) {
        w29_sub(&e, &v[idx[i]], &v[i]);
        w29_sub(&d, p, &v[i]);
        w29_outer(&c, &e, &d);
        if (c.v[1] < 0.0f) return 0;
    }
    return 1;
}
#undef func_00104ae0

/* func_001156f0 (from hand/text_00110000_h3.c). */
#define func_00104f10 ((void (*)(void *, void *)) func_00104f10)
void func_001156f0(void *a0, f32 *a1) {
    f32 *v = a1 + 4;
    func_00104f10(a0, v);
    a1[8] = -v[0];
    a1[9] = -a1[5];
    a1[10] = -a1[6];
    a1[11] = 1.0f;
}
#undef func_00104f10

/* func_00115758 (from hand/text_00110000_s9_w4.c). */
typedef struct { u8 pad[0x50]; f32 cx; f32 top; f32 cz; u8 pad5c[4]; f32 r; f32 h; u8 pad68[0xc]; s16 id; } Bnd;
static inline f32 vlen(f32 *v) {
    f32 r;
    __asm__ volatile(
        "lqc2 $vf5, 0(%1)\n"
        "lqc2 $vf4, 0(%1)\n"
        "vmul.xyz $vf5xyz, $vf4xyz, $vf5xyz\n"
        "vaddy.x $vf5x, $vf5x, $vf5y\n"
        "vaddz.x $vf5x, $vf5x, $vf5z\n"
        "vsqrt Q, $vf5x\n"
        "vwaitq\n"
        "vaddq.x $vf5x, $vf0x, Q\n"
        "qmfc2 $2, $vf5\n"
        "mtc1 $2, %0\n"
        : "=f"(r) : "r"(v) : "$2");
    return r;
}
/* func_00115758 (hand): from session6 w6_02 draft. Fixes: (maxz + minz) operand order (add.s f1,f7,f1); init copies ordered so cse.c does not swap them (maxx = maxy; minx = miny; maxz = maxy; minz = minx, non-adjacent same-source copies) and miny const first (sched2 picks the first-LUID dependent of the call); b->top = maxy last so maxy stays the cse canonical reg for -1e6 (REGNO_LAST_UID rule). */
void func_00115758(s32 id, Bnd *b) {
    V4_52 d;
    V4_52 v[4];
    f32 minx, maxx, miny, maxy, minz, maxz;
    s32 i;
    func_00104ae0(id, v);
    miny = 1000000.0f;
    maxy = -1000000.0f;
    maxx = maxy;
    minx = miny;
    maxz = maxy;
    minz = minx;
    for (i = 0; i < 4; i++) {
        if (maxy < v[i][1]) maxy = v[i][1];
        if (v[i][1] < miny) miny = v[i][1];
        if (v[i][0] < minx) minx = v[i][0];
        if (maxx < v[i][0]) maxx = v[i][0];
        if (v[i][2] < minz) minz = v[i][2];
        if (maxz < v[i][2]) maxz = v[i][2];
    }
    b->id = id;
    b->h = miny - maxy;
    b->cx = (maxx + minx) * 0.5f;
    b->cz = (maxz + minz) * 0.5f;
    b->top = maxy;
    d[0] = v[0][0] - b->cx;
    d[1] = 0.0f;
    d[2] = v[0][2] - b->cz;
    b->r = vlen(d);
}

/* func_001158a8 (from hand/text_00110000_h3.c). */
void func_001158a8(f32 *a, f32 *b) {
    __asm__ volatile("lwc1 $f0, 0(%1)\nswc1 $f0, 0(%0)\nswc1 $f0, 4(%0)\nswc1 $f0, 8(%0)\nswc1 $f0, 12(%0)\nnop\nnop"
                     : : "r"(a), "r"(b) : "$f0");
}

/* func_001158c8 (from auto/text_00110000_6.c). */
#define func_001158a8 ((M2C_UNK (*)(M2C_UNK *, s32)) func_001158a8)
void func_001158c8(s32 arg0) {
    func_001158a8(&D_002C1260, arg0);
    func_001158a8(((s8 *)&D_002C1260) + 0x30, arg0 + 0xC);
    func_001158a8(((s8 *)&D_002C1260) + 0x10, arg0 + 4);
    func_001158a8(((s8 *)&D_002C1260) + 0x40, arg0 + 0x10);
    func_001158a8(((s8 *)&D_002C1260) + 0x20, arg0 + 8);
    func_001158a8(((s8 *)&D_002C1260) + 0x50, arg0 + 0x14);
}
#undef func_001158a8

/* func_00115940 (from hand/text_00110000_s7_w25.c). */
typedef f32 V4_25[4] __attribute__((aligned(16)));
typedef Ent20_2a6238 Tri25;
typedef Vec3_2a624c Vtx25;
extern s32 D_002C12C4;
#define VSUB_MAC(r, a, b) \
    __asm__ volatile( \
        "lqc2 $vf4, 0(%1)\n" \
        "lqc2 $vf5, 0(%2)\n" \
        "vsub.xyzw $vf6xyzw, $vf4xyzw, $vf5xyzw\n" \
        "vnop\n" \
        "vnop\n" \
        "vnop\n" \
        "vnop\n" \
        "vnop\n" \
        "cfc2 %0, $vi17\n" \
        : "=&r"(r) : "r"(a), "r"(b) : "memory")
/* kh1-decomp session 7, worker w25: func_00115940 (hand; also matches hand/nostrict).
   VU0 bounding-box cull: C with the vsub/cfc2 MAC-flag test as an inline-asm macro. */
void func_00115940(s32 id) {
    V4_25 v;
    Tri25 *t = &D_002A6238[id];
    u16 *q = &t->v[0];
    Vtx25 *p0, *p1, *p2, *p3;
    register s32 r asm("$2");
    register s32 r2 asm("$3");
    p0 = &((Vec3_2a624c *)D_002A624C)[*q++];
    p1 = &((Vec3_2a624c *)D_002A624C)[*q++];
    p2 = &((Vec3_2a624c *)D_002A624C)[*q++];
    switch (t->v[3]) {
    case -1: case -2:
        v[0] = p0->x[0]; v[1] = p1->x[0]; v[2] = p2->x[0];
        VSUB_MAC(r, D_002C1260.mx[0], v); if ((r & 0xe0) == 0xe0) return;
        VSUB_MAC(r2, v, D_002C1260.mn[0]); if ((r2 & 0xe0) == 0xe0) return;
        v[0] = p0->x[1]; v[1] = p1->x[1]; v[2] = p2->x[1];
        VSUB_MAC(r, D_002C1260.mx[1], v); if ((r & 0xe0) == 0xe0) return;
        VSUB_MAC(r2, v, D_002C1260.mn[1]); if ((r2 & 0xe0) == 0xe0) return;
        v[0] = p0->x[2]; v[1] = p1->x[2]; v[2] = p2->x[2];
        VSUB_MAC(r, D_002C1260.mx[2], v); if ((r & 0xe0) == 0xe0) return;
        VSUB_MAC(r2, v, D_002C1260.mn[2]); if ((r2 & 0xe0) == 0xe0) return;
        break;
    default:
        p3 = &((Vec3_2a624c *)D_002A624C)[*q];
        v[0] = p0->x[0]; v[1] = p1->x[0]; v[2] = p2->x[0]; v[3] = p3->x[0];
        VSUB_MAC(r, D_002C1260.mx[0], v); if ((r & 0xf0) == 0xf0) return;
        VSUB_MAC(r2, v, D_002C1260.mn[0]); if ((r2 & 0xf0) == 0xf0) return;
        v[0] = p0->x[1]; v[1] = p1->x[1]; v[2] = p2->x[1]; v[3] = p3->x[1];
        VSUB_MAC(r, D_002C1260.mx[1], v); if ((r & 0xf0) == 0xf0) return;
        VSUB_MAC(r2, v, D_002C1260.mn[1]); if ((r2 & 0xf0) == 0xf0) return;
        v[0] = p0->x[2]; v[1] = p1->x[2]; v[2] = p2->x[2]; v[3] = p3->x[2];
        VSUB_MAC(r, D_002C1260.mx[2], v); if ((r & 0xf0) == 0xf0) return;
        VSUB_MAC(r2, v, D_002C1260.mn[2]); if ((r2 & 0xf0) == 0xf0) return;
        break;
    }
    D_002BD250[D_002C12C4++] = id;
}
#undef VSUB_MAC

/* func_00115d18 (from auto/text_00110000_9.c). */
extern M2C_UNK *D_004E0420;
extern s8 D_004761D0;
void func_00115d18(void) {
    s32 *var_v0;
    s32 var_a0;

    var_a0 = 0x3FF;
    D_004E0420 = &D_004761D0;
    var_v0 = &D_004761D0 + 8;
    do {
        var_a0 -= 1;
        *var_v0 = 0;
        var_v0 += 4;
    } while (var_a0 >= 0);
}

/* func_00115d58 (from hand/text_00110000_h29.c). */
typedef struct { s32 f; u8 pad[12]; } W29Mark;
typedef struct { u8 hdr[8]; W29Mark e[1]; } W29MarkTbl;
s32 D_002BD170 ALIGNED(16) = 0;
s32 func_00104940(void *, s32 *, s32);
extern W29MarkTbl *D_004E0420_00115d58 __asm__("D_004E0420");
#define D_004E0420 D_004E0420_00115d58
s32 func_00115d58(void *a) {
    s32 buf[1024];
    s32 n, i, j, k, cnt;
    u16 *l;
    n = func_00104940(a, buf, 1024);
    if (n == -1) return D_002BD170;
    cnt = 0;
    for (i = 0; i < n; i++) {
        l = D_002A623C[buf[i]];
        if (l == (u16 *)-1) continue;
        k = l[0];
        for (j = 0; j < k; j++) {
            u16 id = l[j + 1];
            if (D_004E0420->e[id].f == 0) {
                D_004E0420->e[id].f = 1;
                D_004E0428[cnt++] = id;
            }
        }
    }
    for (k = 0; k < cnt; k++) D_004E0420->e[D_004E0428[k]].f = 0;
    D_002BD170 = cnt;
    return cnt;
}
#undef D_004E0420

/* func_00115e90 (from hand/text_00110000_h3.c). */
void func_00115e90(void *a0, s32 *a1) {
    if (!(*a1 & 0x106)) ((void **)&D_002BD250)[D_002C12C4++] = a0;
}

/* func_00115ed0 (from hand/text_00110000_h3.c). */
void func_00115ed0(void *a0, s32 *a1) {
    if ((*a1 & 0x406) == 0x400) ((void **)&D_002BD250)[D_002C12C4++] = a0;
}

/* func_00115f10 (from hand/text_00110000_h3.c). */
void func_00115f10(void *a0, s32 *a1) {
    if ((*a1 & 0xf6) == 0x20) ((void **)&D_002BD250)[D_002C12C4++] = a0;
}

/* func_00115f50 (from hand/text_00110000_h3.c). */
void func_00115f50(void *a0, s32 *a1) {
    if (!(*a1 & 0xe)) ((void **)&D_002BD250)[D_002C12C4++] = a0;
}

/* func_00115f90 (from hand/text_00110000_h3.c). */
typedef struct {
    u32 lo : 4;
    u32 kind : 4;
} KindBits;
void func_00115f90(void *a0, KindBits *a1) {
    if (a1->kind != 7 && a1->kind != 5) ((void **)&D_002BD250)[D_002C12C4++] = a0;
}

/* func_00115fd8 (from hand/text_00110000_h3.c). */
void func_00115fd8(void *a0, s32 *a1) {
    if (!(*a1 & 0x10006)) ((void **)&D_002BD250)[D_002C12C4++] = a0;
}

/* func_00116020 (from hand/text_00110000_h3.c). */
void func_00116020(void *a0, s32 *a1) {
    if ((*a1 & 0xf6) == 0x50) ((void **)&D_002BD250)[D_002C12C4++] = a0;
}

/* func_00116060 (from hand/text_00110000_h3.c). */
void func_00116060(void *a0, KindBits *a1) {
    if (a1->kind != 7 && a1->kind != 9 && a1->kind != 5) ((void **)&D_002BD250)[D_002C12C4++] = a0;
}

/* func_001160b0 (from hand/text_00110000_h3.c). */
void func_001160b0(void *a0, KindBits *a1) {
    if (a1->kind == 9) ((void **)&D_002BD250)[D_002C12C4++] = a0;
}

/* func_001160f0 (from hand/text_00110000_h3.c). */
void func_001160f0(void *a0, u32 *a1) {
    if (!((*a1 >> 17) & 1)) ((void **)&D_002BD250)[D_002C12C4++] = a0;
}

/* func_00116130 (from auto/text_00110000_6.c). */
#define func_00115940 ((M2C_UNK (*)()) func_00115940)
void func_00116130(s32 arg0, s32 *arg1) {
    if (!(*arg1 & 0x106)) {
        func_00115940();
    }
}
#undef func_00115940

/* func_00116160 (from auto/text_00110000_6.c). */
#define func_00115940 ((M2C_UNK (*)()) func_00115940)
void func_00116160(s32 arg0, s32 *arg1) {
    if ((*arg1 & 0x406) == 0x400) {
        func_00115940();
    }
}
#undef func_00115940

/* func_00116198 (from auto/text_00110000_6.c). */
#define func_00115940 ((M2C_UNK (*)()) func_00115940)
void func_00116198(s32 arg0, s32 *arg1) {
    if ((*arg1 & 0xF6) == 0x20) {
        func_00115940();
    }
}
#undef func_00115940

/* func_001161d0 (from auto/text_00110000_6.c). */
#define func_00115940 ((M2C_UNK (*)()) func_00115940)
void func_001161d0(s32 arg0, s32 *arg1) {
    if (!(*arg1 & 0xE)) {
        func_00115940();
    }
}
#undef func_00115940

/* func_00116200 (from auto/text_00110000_16.c). */
void func_00116200(s32 arg0, s32 arg1) {
    u64 temp_a1;

    temp_a1 = (u64) *(u8 *)arg1 >> 4;
    if ((temp_a1 != 7) && (temp_a1 != 5)) {
        func_00115940(arg0);
    }
}

/* func_00116240 (from auto/text_00110000_6.c). */
#define func_00115940 ((M2C_UNK (*)()) func_00115940)
void func_00116240(s32 arg0, s32 *arg1) {
    if (!(*arg1 & 0x10006)) {
        func_00115940();
    }
}
#undef func_00115940

/* func_00116278 (from auto/text_00110000_6.c). */
#define func_00115940 ((M2C_UNK (*)()) func_00115940)
void func_00116278(s32 arg0, s32 *arg1) {
    if ((*arg1 & 0xF6) == 0x50) {
        func_00115940();
    }
}
#undef func_00115940

/* func_001162b0 (from auto/text_00110000_16.c). */
void func_001162b0(s32 arg0, s32 arg1) {
    u64 temp_a1;

    temp_a1 = (u64) *(u8 *)arg1 >> 4;
    if ((temp_a1 != 7) && (temp_a1 != 9) && (temp_a1 != 5)) {
        func_00115940(arg0);
    }
}

/* func_001162f8 (from auto/text_00110000_14.c). */
#define func_00115940 ((M2C_UNK (*)()) func_00115940)
void func_001162f8(s32 arg0, u8 *arg1) {
    u64 wide;
    wide = *arg1;

    if ((wide >> 4) == 9) {
        func_00115940();
    }
}
#undef func_00115940

/* func_00116330 (from auto/text_00110000_6.c). */
#define func_00115940 ((M2C_UNK (*)()) func_00115940)
void func_00116330(s32 arg0, u32 *arg1) {
    if (!(((u32) *arg1 >> 0x11) & 1)) {
        func_00115940();
    }
}
#undef func_00115940

/* func_00116368 (from hand/text_00110000_s9_w8.c).  Both id loops written
 * out with function-level `s32 id; s32 *fl;` shared by the two loops (global
 * pseudos: fl is not tied to the address chain, gets a1 by copy preference;
 * id ends in a1). */
typedef Node01 Node368;
typedef struct { u8 pad[0x18]; u16 cnt; } Out368;
/* Per-kind triangle callbacks: D_002BD178 for nodes inside the box,
 * D_002BD1A8 for nodes that only overlap it (only func_00116368 uses them). */
void (*D_002BD178[11])(s32, s32 *) = {
    func_00115e90, func_00115ed0, func_00115f10, func_00115f50, func_00115f90, func_00115fd8,
    func_00116020, func_00115f50, func_00116060, func_001160b0, func_001160f0,
};
void (*D_002BD1A8[11])(s32, s32 *) = {
    func_00116130, func_00116160, func_00116198, func_001161d0, func_00116200, func_00116240,
    func_00116278, func_001161d0, func_001162b0, func_001162f8, func_00116330,
};
static inline s32 overlap(f32 *mn, f32 *mx, Box_2c1260 *b) {
    if (mn[0] <= b->mx[0][0] && b->mn[0][0] <= mx[0]
        && b->mx[1][0] >= mn[1] && b->mn[1][0] <= mx[1]
        && b->mx[2][0] >= mn[2] && b->mn[2][0] <= mx[2]) return 1;
    return 0;
}
static inline s32 inside(f32 *mn, f32 *mx, Box_2c1260 *b) {
    if (b->mn[0][0] < mn[0] && b->mx[0][0] > mx[0]
        && b->mn[1][0] < mn[1] && b->mx[1][0] > mx[1]
        && b->mn[2][0] < mn[2] && b->mx[2][0] > mx[2]) return 1;
    return 0;
}
#define func_00115d58 ((s32 (*)(void)) func_00115d58)
#define func_001158c8 ((void (*)(Out368 *)) func_001158c8)
void func_00116368(Out368 *o, s32 k) {
    s32 n, i, j;
    u16 *q;
    s32 *p;
    Node368 *nd;
    void (*f1)(s32, s32 *);
    void (*f2)(s32, s32 *);
    s32 id; s32 *fl;
    D_002C12C4 = 0;
    n = func_00115d58();
    p = D_004E0428;
    func_001158c8(o);
    f2 = D_002BD1A8[k];
    f1 = D_002BD178[k];
    for (j = 0; j < n; j++) {
        nd = D_002A6244[*p++];
        if (overlap(nd->mn, nd->mx, &D_002C1260)) {
            if (inside(nd->mn, nd->mx, &D_002C1260)) {
                q = nd->ids;
                for (i = 0; i < nd->n; i++) {
                    id = *q++;
                    fl = &D_002A6238[id].f.w;
                    if (!(*fl & 1)) f1(id, fl);
                }
            } else {
                q = nd->ids;
                for (i = 0; i < nd->n; i++) {
                    id = *q++;
                    fl = &D_002A6238[id].f.w;
                    if (!(*fl & 1)) f2(id, fl);
                }
            }
        }
    }
    o->cnt = *(u16 *)&D_002C12C4;
}
#undef func_00115d58
#undef func_001158c8

/* func_00116628 (from hand/text_00110000_s6_02.c). */
typedef struct { u8 pad[0x2c]; s32 x2c; s32 x30; u8 pad34[4]; s16 x38; s16 x3a; u8 pad3c[2]; s16 x3e; u8 pad40[0x20]; s32 x60; u8 pad64[8]; s16 x6c; s16 x6e; s16 x70; u8 pad72[2]; s16 x74; s16 x76; } Ent628;
void func_00116628(Ent628 *e) {
    e->x30 = 0;
    e->x38 = 0;
    e->x2c = -1;
    e->x60 = 0;
    e->x76 = -1;
    e->x74 = -1;
    e->x70 = -1;
    e->x6e = -1;
    e->x6c = -1;
    e->x3e = -1;
    e->x3a = -1;
}

/* func_00116660 (from auto/text_00110000_6.c). */
#define func_00116628 ((void (*)(s32)) func_00116628)
void func_00116660(s32 arg0) {
    func_00116628(arg0);
    M2C_FIELD(arg0, s16 *, 0x3C) = -1;
}
#undef func_00116628

/* func_00116690 (from auto/text_00110000_3.c). */
s32 func_00116690(u32 *arg0) {
    return ((u32) *arg0 >> 0x11) & 1;
}

/* func_001166a0 (from auto/text_00110000_3.c). */
s32 func_001166a0(u32 *arg0) {
    return ((u32) *arg0 >> 0x1A) & 1;
}

/* func_001166b0 (from auto/text_00110000_3.c). */
s32 func_001166b0(void *arg0) {
    return M2C_FIELD(arg0, u8 *, 3) & 1;
}

/* func_001166c0 (from auto/text_00110000_3.c). */
s32 func_001166c0(void) {
    return 0;
}

/* func_001166c8 (from auto/text_00110000_3.c). */
s32 func_001166c8(u32 *arg0) {
    return ((u32) *arg0 >> 0x1B) & 1;
}

/* func_001166d8 (from auto/text_00110000_3.c). */
s32 func_001166d8(u32 *arg0) {
    return ((u32) *arg0 >> 9) & 1;
}

/* func_001166e8 (from hand/text_00110000_s10_r2_10.c). */
typedef struct {
    f32 pos[4];   /* +0x00 */
    f32 d[4];     /* +0x10 */
    f32 r;        /* +0x20 */
    f32 h;        /* +0x24 */
    s32 fl;       /* +0x28 */
    s32 x2C;      /* +0x2C */
    s32 st;       /* +0x30 */
    u8 pad34[4];
    s16 x38;      /* +0x38 */
    s16 x3A;      /* +0x3A */
    s16 x3C;      /* +0x3C */
    s16 x3E;      /* +0x3E */
    f32 out[4];   /* +0x40 */
    u8 pad50[0x18];
    f32 x68;      /* +0x68 */
    s16 x6C;      /* +0x6C */
    s16 x6E;      /* +0x6E */
    s16 x70;      /* +0x70 */
    u8 pad72[4];
    s16 x76;      /* +0x76 */
} ColO;
typedef ColBits_2a6238 ColF;
typedef Ent20_2a6238 ColE;
typedef struct {
    f32 min[3];
    f32 max[3];
    u16 n;
    u8 pad1A[6];
} ColBox;
typedef struct {
    u64 w;
} ColTri;
extern f32 D_002C1250;
extern s32 D_002C1304;
extern s32 D_002C12C0;
extern s32 D_002BC128;
extern s32 D_002BC130;
s32 func_00119a20(s32, f32 *, f32 *, f32 *, f32 *);
s32 func_00119ad8(s32, s32, f32 *, f32 *, f32 *, f32 *);
void func_0011a9c8(s32, s32, f32 *);
ColTri *func_0011ab38(s32, s32);
u64 func_0011b6a0(ColO *, f32 *, s32);
s32 func_0011bdf8(ColO *, f32 *, s32 *, f32 *);
static inline f32 colDist(f32 *a, f32 *b) {
    f32 r;
    __asm__ volatile(
        "lqc2 $vf6, 0(%1)\n"
        "lqc2 $vf4, 0(%2)\n"
        "vsub.xyzw $vf5xyzw, $vf6xyzw, $vf4xyzw\n"
        "vmove.xyzw $vf4xyzw, $vf5xyzw\n"
        "vmul.xyz $vf5xyz, $vf4xyz, $vf5xyz\n"
        "vaddy.x $vf5x, $vf5x, $vf5y\n"
        "vaddz.x $vf5x, $vf5x, $vf5z\n"
        "vsqrt Q, $vf5x\n"
        "vwaitq\n"
        "vaddq.x $vf5x, $vf0x, Q\n"
        "qmfc2 $2, $vf5\n"
        "mtc1 $2, %0\n"
        : "=f"(r) : "r"(a), "r"(b) : "$2");
    return r;
}
#define func_00104eb0 ((void (*)(s32, f32 *)) func_00104eb0)
#define func_00104f10 ((s32 (*)(s32, f32 *)) func_00104f10)
#define func_00115600 ((s32 (*)(s32, f32 *)) func_00115600)
#define func_00115758 ((void (*)(s32, ColO *)) func_00115758)
#define func_00116368 ((void (*)(ColBox *, s32)) func_00116368)
#define func_00116628 ((void (*)(ColO *)) func_00116628)
#define func_0011a978 ((void (*)(s32, s32, f32 *)) func_0011a978)
/* func_001166e8 (r2_10 s10): MATCH by wqb03_rr.py 0048D090, mode hand (strict). session8 w20 16w draft with `s32 func_00104f10(s32, f32 *);` instead of void (lever 2: callee return type). */
u64 func_001166e8(ColO *o)
{
    s32 ids[512];
    f32 pos[4] __attribute__((aligned(16)));
    f32 p1[4] __attribute__((aligned(16)));
    f32 p2[4] __attribute__((aligned(16)));
    f32 hit[4] __attribute__((aligned(16)));
    f32 cur[4] __attribute__((aligned(16)));
    f32 tmp[4] __attribute__((aligned(16)));
    f32 tmp2[4] __attribute__((aligned(16)));
    f32 nrm[4] __attribute__((aligned(16)));
    f32 unk[16] __attribute__((aligned(16)));
    ColBox box __attribute__((aligned(16)));
    s32 list[512];
    s32 tri;
    f32 h2;
    f32 h1;
    s32 best1;
    s32 best2;
    u64 r0;
    u64 hf;
    u64 acc0;
    u64 acc1;
    s32 lastid;
    s32 cnt;
    s32 it;
    s32 maxit;
    s32 (*fn)(ColF *);
    f32 *vel;
    s32 i, n, id, k, tf;
    ColF *fp;
    ColE *ep;
    f32 e, y, d, best;
    s32 b;

    best = 1000000.0f;
    acc0 = 0;
    acc1 = 0;
    o->fl |= 0x80000000;
    best2 = -1;
    best1 = -1;
    lastid = -1;
    func_00116628(o);
    fn = func_001166a0;
    maxit = 3;
    it = 0;
    cnt = 0;
    h1 = h2 = best;
    D_002C1250 = o->r - 0.008f;
    switch (o->fl & 0x7C) {
    case 4: fn = func_00116690; break;
    case 16: break;
    case 8: fn = func_001166b0; break;
    case 32: fn = func_001166c0; break;
    case 64: fn = func_001166c8; break;
    default: fn = func_001166d8; break;
    }
    if (D_002C1304 == 1) {
        o->out[1] = o->pos[1];
        o->out[3] = 1.0f;
        o->out[0] = o->pos[0] + o->d[0];
        o->out[2] = o->pos[2] + o->d[2];
        return 0;
    }
    vel = o->d;
    PlatVu0AddVector(pos, o->pos, vel);
again:
    r0 = 0;
    hf = 0;
    if (!(o->fl & 2)) r0 = func_0011b6a0(o, pos, 0);
again2:
    i = 0;
    PlatVu0CopyVector(cur, pos);
    n = 0;
    PlatVu0CopyVector(p1, pos);
    PlatVu0CopyVector(p2, pos);
    p2[1] -= o->h;
    e = D_002C1250 + o->r * 0.5f;
    box.min[0] = pos[0] - e;
    box.max[0] = pos[0] + e;
    box.min[2] = pos[2] - e;
    box.max[2] = pos[2] + e;
    box.min[1] = (pos[1] - o->h) - e;
    box.max[1] = (pos[1] - o->h) + e;
    func_00116368(&box, 4);
    hit[3] = 1.0f;
    pos[1] -= o->h;
    for (; i < box.n; i++) {
        u8 kd;
        id = D_002BD250[i];
        func_00104f10(id, tmp);
        fp = &D_002A6238[id].f.c;
        if (D_002A6238[id].act && func_00119a20(id, tmp, p2, hit, &D_002C1250)) {
            s32 b;
            s32 x = D_002A6238[id].act;
            b = fp->b15;
            o->x3A = id;
            o->x38 = x;
            if (b == 1) o->st |= 4;
        }
        kd = fp->kind;
        if (kd == 0) continue;
        if (fp->sub) continue;
        switch (kd) {
        case 10:
            if (func_00119a20(id, tmp, p2, hit, &D_002C1250)) o->st |= 0x10;
            else list[n++] = id;
            break;
        case 3:
            if (func_00119a20(id, tmp, p2, hit, &D_002C1250)) {
                lastid = id;
                cnt++;
            } else list[n++] = id;
            break;
        case 4:
            if (func_00119a20(id, tmp, p2, hit, &D_002C1250)) o->x6C = id;
            else list[n++] = id;
            break;
        case 2:
            if (func_00119a20(id, tmp, p2, hit, &D_002C1250)) o->x3E = id;
            else list[n++] = id;
            break;
        case 8:
            if (func_00119a20(id, tmp, pos, hit, &D_002C1250)) {
                o->st |= 8;
                hf = 1;
                PlatVu0ScaleVectorXYZ(tmp, tmp, o->r);
                PlatVu0AddVector(pos, hit, tmp);
                if (fp->b23) o->x76 = id;
            } else list[n++] = id;
            break;
        case 13:
            if (func_00119a20(id, tmp, pos, hit, &D_002C1250)) o->x70 = id;
            else list[n++] = id;
            break;
        case 6:
            if (func_00119a20(id, tmp, pos, hit, &D_002C1250)) o->x6E = id;
            else list[n++] = id;
            break;
        case 12:
            if (func_00119a20(id, tmp, pos, hit, &D_002C1250)) o->st |= 0x20;
            else list[n++] = id;
            break;
        case 9:
            break;
        default:
            if (fn(fp) == 0) {
                if (func_00119a20(id, tmp, pos, hit, &D_002C1250)) {
                    hf = 1;
                    PlatVu0ScaleVectorXYZ(tmp, tmp, o->r);
                    PlatVu0AddVector(pos, hit, tmp);
                    if (fp->b23) o->x76 = id;
                } else list[n++] = id;
            }
            break;
        }
    }
    for (i = 0; i < n; i++) {
        s32 kd;
        id = list[i];
        func_00104f10(id, tmp);
        fp = &D_002A6238[id].f.c;
        if (D_002A6238[id].act && func_00119ad8(-1, id, tmp, p2, hit, &D_002C1250)) {
            s32 b;
            s32 x = D_002A6238[id].act;
            b = fp->b15;
            o->x3A = id;
            o->x38 = x;
            if (b == 1) o->st |= 4;
        }
        kd = fp->kind;
        if (kd == 0) continue;
        switch (kd) {
        case 10:
            if (func_00119ad8(-1, id, tmp, p2, hit, &D_002C1250)) o->st |= 0x10;
            break;
        case 3:
            if (func_00119ad8(-1, id, tmp, p2, hit, &D_002C1250)) {
                lastid = id;
                cnt++;
            }
            break;
        case 4:
            if (func_00119ad8(-1, id, tmp, p2, hit, &D_002C1250)) o->x6C = id;
            break;
        case 2:
            if (func_00119ad8(-1, id, tmp, p2, hit, &D_002C1250)) o->x3E = id;
            break;
        case 8:
            if (func_00119ad8(-1, id, tmp, pos, hit, &D_002C1250)) {
                o->st |= 8;
                hf = 1;
                PlatVu0SubVector(pos, pos, hit);
                PlatVu0Normalize(pos, pos);
                PlatVu0ScaleVectorXYZ(pos, pos, o->r);
                PlatVu0AddVector(pos, hit, pos);
                if (fp->b23) o->x76 = id;
            }
            break;
        case 13:
            if (func_00119ad8(-1, id, tmp, pos, hit, &D_002C1250)) o->x70 = id;
            break;
        case 6:
            if (func_00119ad8(-1, id, tmp, pos, hit, &D_002C1250)) o->x6E = id;
            break;
        case 12:
            if (func_00119ad8(-1, id, tmp, pos, hit, &D_002C1250)) o->st |= 0x20;
            break;
        case 9:
            break;
        default:
            if (fn(fp) == 0) {
                if (func_00119ad8(-1, id, tmp, pos, hit, &D_002C1250)) {
                    PlatVu0SubVector(nrm, pos, hit);
                    hf = 1;
                    PlatVu0Normalize(nrm, nrm);
                    PlatVu0ScaleVectorXYZ(nrm, nrm, o->r);
                    PlatVu0AddVector(pos, hit, nrm);
                    if (fp->b23) o->x76 = id;
                }
            }
            break;
        }
    }
    pos[1] += o->h;
    acc1 |= hf;
    acc0 |= r0;
    if (hf | r0) {
        if (it < maxit) {
            best = colDist(pos, o->pos);
            if (!(o->r < best)) {
                it++;
                goto again;
            }
        } else if (it == 100) {
            goto done;
        }
        if (D_002BC128 == 10 && D_002BC130 == 7) {
            PlatVu0SubVector(nrm, pos, p1);
            PlatVu0Normalize(nrm, nrm);
            PlatVu0ScaleVectorXYZ(nrm, nrm, o->r);
            PlatVu0AddVector(pos, p1, nrm);
            if (maxit != 4) {
                maxit = 4;
                it = 0;
                goto again;
            }
        } else {
            PlatVu0AddVector(pos, o->pos, vel);
            r0 = 0;
            hf = 0;
            it = 100;
            goto again2;
        }
    }
done:
    PlatVu0CopyVector(cur, pos);
    if (cnt) func_00115758(lastid, o);
    if (!(o->fl & 2)) best2 = func_0011bdf8(o, pos, &tri, &h2);
    box.min[0] = pos[0];
    box.min[2] = pos[2];
    box.min[1] = pos[1] - o->h;
    box.max[1] = pos[1] + 1000000.0f;
    box.max[0] = pos[0];
    box.max[2] = pos[2];
    n = 0;
    i = 0;
    func_00116368(&box, 8);
    for (; i < box.n; i++) {
        id = D_002BD250[i];
        fp = &D_002A6238[id].f.c;
        if (fp->sub) continue;
        if (fn(fp)) continue;
        if (func_00115600(id, cur)) {
            ids[n] = id;
            n++;
        }
    }
    best = h1;
    pos[1] -= o->h;
    for (i = 0; i < n; i++) {
        func_00115408(ids[i], cur, &hit[1], 0);
        d = fabsf(pos[1] - hit[1]);
        if (d < best) {
            if (hit[1] < cur[1] - o->h) {
                if (d < o->h) {
                    best = d;
                    h1 = hit[1];
                    best1 = ids[i];
                }
            } else {
                best = d;
                h1 = hit[1];
                best1 = ids[i];
            }
        }
    }
    if (best2 == -1) {
        if (best1 == -1) {
            o->x3C = -1;
            PlatVu0CopyVector(o->out, cur);
            return acc1 | acc0;
        }
        if (D_002C12C0) func_00115408(best1, cur, &h1, 1);
        y = h1;
        tf = 0;
    } else if (h1 < h2) {
        if (D_002C12C0) func_00115408(best1, cur, &h1, 1);
        y = h1;
        tf = 0;
    } else {
        y = h2;
        tf = 1;
        o->x2C = tri;
    }
    if (o->fl & 1) {
        if (!tf) {
            func_00104eb0(best1, tmp2);
            func_00104f10(best1, tmp);
        } else {
            func_0011a9c8(tri, best2, tmp2);
            func_0011a978(tri, best2, tmp);
        }
        if (func_00115158(cur, tmp2, tmp)) {
            o->st |= 1;
        } else {
            if (!tf) {
                if ((((ColTri *)&D_002A6238[best1].f)->w & 0xFF) >> 4 == 11) o->st |= 1;
                else o->st &= ~1;
            } else if ((func_0011ab38(tri, best2)->w & 0xFF) >> 4 == 11) o->st |= 1;
            else o->st &= ~1;
            cur[1] = y;
        }
    } else {
        if (p1[1] + o->h * 0.5f < y) o->st |= 1;
        else cur[1] = y;
        if (!tf) {
            if ((((ColTri *)&D_002A6238[best1].f)->w & 0xFF) >> 4 == 11) o->st |= 1;
        } else if ((func_0011ab38(tri, best2)->w & 0xFF) >> 4 == 11) o->st |= 1;
    }
    o->x68 = y;
    if (!tf) {
        k = o->st;
        o->x3C = best1;
        if (!(k & 1)) {
            if (D_002A6238[best1].act) {
                ep = &D_002A6238[best1];
                o->x38 = ep->act;
                o->x3A = best1;
                o->st = k | 2;
                b = ep->f.c.b15;
                if (b == 1) o->st = k | 6;
            }
        }
    } else {
        o->x3C = best2;
    }
    PlatVu0CopyVector(o->out, cur);
    return acc1 | acc0;
}
#undef func_00104eb0
#undef func_00104f10
#undef func_00115600
#undef func_00115758
#undef func_00116368
#undef func_00116628
#undef func_0011a978

/* func_00117710 (from hand/text_00110000_h52.c). */
typedef PlaneBits_2a6238 Bf52;
extern s32 D_002A62E8;
typedef struct { u8 pad[0x28]; s32 x28; s32 x2c; u8 pad30[4]; f32 x34; u8 pad38[4]; u16 x3c; u8 pad3e[2]; V4_52 x40; u8 pad50[0x18]; f32 x68; } Src52;
typedef struct { V4_52 p; s32 x10[4]; s32 x20; f32 x24; s32 x28; f32 x2c; V4_52 x30; s32 x40; } Dst52;
void func_0011aac8(s32, void *, s32);
#define func_001150d8 ((void (*)(void)) func_001150d8)
#define func_001156f0 ((void (*)(s32, void *)) func_001156f0)
#define func_0011ab38 ((Bf52 *(*)()) func_0011ab38)
void func_00117710(Src52 *a, Dst52 *b) {
    s32 id;
    Bf52 *bp;
    s32 k;
    a->x34 = 123456.0f;
    if (a->x28 >= 0) return;
    if (D_002A62E8) func_001150d8();
    PlatVu0CopyVector(b->x30, ((V4_52 *)D_002A3F48));
    id = a->x3c;
    a->x28 &= 0x7fffffff;
    b->x40 = 0;
    if (id == 0xffff) {
        PlatVu0CopyVector(b, a->x40);
        b->x20 = 0;
        b->x24 = 1.0f;
        b->x28 = 0;
        b->x2c = 1.0f;

        return;
    }
    b->p[0] = a->x40[0];
    b->p[1] = a->x68;
    b->p[2] = a->x40[2];
    b->p[3] = 1.0f;
    if (a->x2c == -1) {
        func_001156f0(id, b);
        b->x40 = (&D_002A6238[id].f.p)->x40;
        k = (&D_002A6238[id].f.p)->k;
    } else {
        func_0011aac8(id, b, a->x2c);
        bp = func_0011ab38(a->x2c, id);
        b->x40 = bp->x40;
        k = bp->k;
    }
    PlatVu0CopyVector(b->x30, ((V4_52 *)D_002A3F48)[k]);
}
#undef func_001150d8
#undef func_001156f0
#undef func_0011ab38

/* func_001178b8 (from auto/text_00110000_7.c). */
#define func_00116368 ((void (*)(s32, s32)) func_00116368)
void func_001178b8(s32 arg0) {
    func_00116368(arg0, 0);
}
#undef func_00116368

/* func_001178d0 (from hand/text_00110000_h3.c). */
typedef struct {
    u8 pad0[0x18];
    u16 x18;
    u8 pad1a[2];
    s32 x1c;
    s32 x20;
    s32 x24;
    void *x28;
} Obj178;
void func_0011b108(void *, s32);
#define func_00116368 ((void (*)(void *, s32)) func_00116368)
void func_001178d0(Obj178 *a) {
    s32 r = 0;
    a->x1c = 0;
    func_00116368(a, 1);
    if (a->x18 != 0) {
        a->x28 = &D_002BD250;
        a->x24 = -1;
        a->x1c++;
        r = 1;
        a->x20 = a->x18;
    }
    func_0011b108(a, r);
}
#undef func_00116368

/* func_00117948 (from hand/text_00110000_h52.c). */
typedef struct { u16 poly; u16 i0; u16 i1; } Edge52;
s32 func_00104a90(s32, s32 *);
void func_0011a818(s32 *, s32 *, Edge52 *);
s32 func_0011a7c0(s32, s32, s32 *);
#define func_0011ab38 ((Bf52 *(*)()) func_0011ab38)
s32 func_00117948(Edge52 *e, s32 n, s32 *list, s32 grp) {
    s32 v[4];
    s32 a, b;
    s32 i, j, cnt, id;
    s32 *idx;
    u32 *f, *g;
    if (grp == -1) {
        s32 ta = D_002A6238[e->poly].v[e->i0];
        s32 tb = D_002A6238[e->poly].v[e->i1];
        a = ta;
        b = tb;
        for (i = 0; i < n; i++) {
            id = list[i];
            f = &D_002A6238[id].f.w;
            if (e->poly == id) continue;
            cnt = func_00104a90(id, v);
            if (cnt == 3) idx = D_002BD150;
            else idx = D_002BD160;
            for (j = 0; j < cnt; j++) {
                if (b == v[j] && a == v[idx[j]]) return (*f & 0x406) != 0x400;
            }
        }
        return 1;
    }
    func_0011a818(&a, &b, e);
    for (i = 0; i < n; i++) {
        id = list[i];
        g = (u32 *)func_0011ab38(grp, id, grp);
        if (e->poly == id) continue;
        cnt = func_0011a7c0(grp, id, v);
        idx = cnt == 3 ? D_002BD150 : D_002BD160;
        for (j = 0; j < cnt; j++) {
            if (b == v[j] && a == v[idx[j]]) return (*g & 0x406) != 0x400;
        }
    }
    return 1;
}
#undef func_0011ab38

/* func_00117bb0 (from hand/text_00110000_h3.c). */
s32 func_001198c8();
#define func_001152c8 ((s32 (*)(void *, s32, s32, s32)) func_001152c8)
#define func_001198c8 ((s32 (*)(s32, void *, void *)) func_001198c8)
s32 func_00117bb0(void *a0, s32 a1, s32 a2, void *a3) {
    if (func_001152c8(a0, a1, a2, (s32)a3) && func_001198c8(-1, a0, a3)) return 1;
    return 0;
}
#undef func_001152c8
#undef func_001198c8

/* func_00117c08 (from hand/text_00110000_h52.c). */
typedef struct { V4_52 pts[512]; V4_52 tmp; s32 ids[512]; } Hits52;
void *func_00122048(s32, s32);
void func_001220b8(void *);
static inline void v52_copy(void *d, void *s) {
    __asm__ volatile(
        "lq $6, 0(%1)\n"
        "sq $6, 0(%0)\n"
        "nop\n"
        : : "r"(d), "r"(s) : "$6", "memory");
}
static inline f32 v52_dist2(f32 *a, f32 *b) {
    f32 r;
    __asm__ volatile(
        "lqc2 $vf6, 0(%1)\n"
        "lqc2 $vf4, 0(%2)\n"
        "vsub.xyzw $vf5xyzw, $vf6xyzw, $vf4xyzw\n"
        "vmove.xyzw $vf4xyzw, $vf5xyzw\n"
        "vmul.xyz $vf5xyz, $vf4xyz, $vf5xyz\n"
        "vaddy.x $vf5x, $vf5x, $vf5y\n"
        "vaddz.x $vf5x, $vf5x, $vf5z\n"
        "qmfc2 $2, $vf5\n"
        "mtc1 $2, %0\n"
        : "=f"(r) : "r"(a), "r"(b) : "$2");
    return r;
}
#define func_001152c8 ((s32 (*)(s32, void *, void *, void *)) func_001152c8)
s32 func_00117c08(s32 n, f32 *p, void *dir, f32 *out) {
    Hits52 *w;
    s32 i, cnt, id;
    s32 *q;
    f32 d, bd;
    cnt = 0;
    w = func_00122048(sizeof(Hits52), 4);
    for (i = 0; i < n; i++) {
        id = D_002BD250[i];
        if (func_001152c8(id, p, dir, w->tmp) && func_001198c8(-1, id, w->tmp)) {
            v52_copy(w->pts[cnt], w->tmp);
            w->ids[cnt] = id;
            cnt++;
        }
    }
    i = 0;
    if (cnt != 0) {
        bd = 1e12f;
        id = 0;
        for (; i < cnt; i++) {
            d = v52_dist2(p, w->pts[i]);
            if (d < bd) {
                bd = d;
                id = i;
            }
        }
        v52_copy(out, w->pts[id]);
        i = w->ids[id];
        func_001220b8(w);
        return i;
    }
    func_001220b8(w);
    return -1;
}
#undef func_001152c8

/* func_00117db0 (from hand/text_00110000_b01.c). */
typedef struct { u8 pad[0x18]; s16 cnt; } Qry01;
static inline s32 ov01(f32 *mn, f32 *mx) {
    if (mn[0] <= D_002C1260.mx[0][0] && D_002C1260.mn[0][0] <= mx[0] && D_002C1260.mx[1][0] >= mn[1] &&
        D_002C1260.mn[1][0] <= mx[1] && D_002C1260.mx[2][0] >= mn[2] && D_002C1260.mn[2][0] <= mx[2]) return 1;
    return 0;
}
static inline s32 in01(f32 *mn, f32 *mx) {
    if (D_002C1260.mn[0][0] < mn[0] && D_002C1260.mx[0][0] > mx[0] && D_002C1260.mn[1][0] < mn[1] &&
        D_002C1260.mx[1][0] > mx[1] && D_002C1260.mn[2][0] < mn[2] && D_002C1260.mx[2][0] > mx[2]) return 1;
    return 0;
}
#define func_00115d58 ((s32 (*)(Qry01 *)) func_00115d58)
#define func_001158c8 ((void (*)(Qry01 *)) func_001158c8)
void func_00117db0(Qry01 *q) {
    s32 n, i, j;
    Node01 *e;
    u16 *p;
    s32 id;
    s32 *ip;
    D_002C12C4 = 0;
    n = func_00115d58(q);
    ip = D_004E0428;
    func_001158c8(q);
    for (i = 0; i < n; i++) {
        e = D_002A6244[*ip++];
        if (ov01(e->mn, e->mx)) {
            if (in01(e->mn, e->mx)) {
                p = e->ids;
                for (j = 0; j < e->n; j++) {
                    u32 *f;
                    id = *p++;
                    f = &D_002A6238[id].f.w;
                    if (!(*f & 1)) {
                        D_002BD250[D_002C12C4] = id;
                        D_002C12C4++;
                    }
                }
            } else {
                p = e->ids;
                for (j = 0; j < e->n; j++) {
                    u32 *f;
                    id = *p++;
                    f = &D_002A6238[id].f.w;
                    if (!(*f & 1)) func_00115940(id);
                }
            }
        }
    }
    q->cnt = D_002C12C4;
}
#undef func_00115d58
#undef func_001158c8

/* func_00118060 (from hand/text_00110000_h52.c). */
typedef struct { V4_52 pos; V4_52 dir; V4_52 out; s16 x30; s32 x34; } Ray52;
typedef struct { u8 pad[0x18]; u16 x18; u8 pad1a[6]; V4_52 x20; V4_52 x30; } RayW52;
extern s32 D_002A62EC;
void func_001195d8();
s32 func_0011c338(RayW52 *, Ray52 *, f32 *, f32 *, s32, s32 *);
static inline f32 v52_dist(f32 *a, f32 *b) {
    f32 r;
    __asm__ volatile(
        "lqc2 $vf6, 0(%1)\n"
        "lqc2 $vf4, 0(%2)\n"
        "vsub.xyzw $vf5xyzw, $vf6xyzw, $vf4xyzw\n"
        "vmove.xyzw $vf4xyzw, $vf5xyzw\n"
        "vmul.xyz $vf5xyz, $vf4xyz, $vf5xyz\n"
        "vaddy.x $vf5x, $vf5x, $vf5y\n"
        "vaddz.x $vf5x, $vf5x, $vf5z\n"
        "vsqrt Q, $vf5x\n"
        "vwaitq\n"
        "vaddq.x $vf5x, $vf0x, Q\n"
        "qmfc2 $2, $vf5\n"
        "mtc1 $2, %0\n"
        : "=f"(r) : "r"(a), "r"(b) : "$2");
    return r;
}
#define func_001195d8 ((void (*)(Ray52 *, RayW52 *)) func_001195d8)
#define func_00116368 ((void (*)(void *, s32)) func_00116368)
#define func_00117db0 ((void (*)()) func_00117db0)
void func_00118060(Ray52 *o, s32 a1, s32 a2, s32 a3) {
    s32 hit;
    s32 r1, r2;
    RayW52 *w;
    if (D_002C1304 == 1) {
        o->x30 = o->x34 = -1;
        return;
    }
    o->x34 = -1;
    r1 = -1;
    w = func_00122048(64, 4);
    func_001195d8(o, w);
    if (a2 == 0) r1 = func_0011c338(w, o, o->dir, w->x20, a3, &hit);
    if (D_002A62EC == 0) func_00116368(w, a1);
    else func_00117db0(w, a1);
    r2 = func_00117c08(w->x18, o->pos, o->dir, w->x30);
    if (r1 != -1) {
        if (r2 == -1) {
            PlatVu0CopyVector(o->out, w->x20);
            o->x30 = r1;
            o->x34 = hit;
        } else if (v52_dist(o->pos, w->x20) < v52_dist(o->pos, w->x30)) {
            PlatVu0CopyVector(o->out, w->x20);
            o->x30 = r1;
            o->x34 = hit;
        } else {
            PlatVu0CopyVector(o->out, w->x30);
            o->x30 = r2;
        }
    } else {
            PlatVu0CopyVector(o->out, w->x30);
            o->x30 = r2;
    }
    func_001220b8(w);
}
#undef func_001195d8
#undef func_00116368
#undef func_00117db0

/* func_00118230 (from hand/text_00110000_h52.c). */
#define func_00115600 ((s32 (*)(s32, f32 *)) func_00115600)
s32 func_00118230(s32 n, f32 *p, f32 *lim, f32 *out) {
    f32 h;
    s32 *buf;
    s32 i, cnt, best, id;
    f32 d, bd;
    cnt = 0;
    best = -1;
    buf = func_00122048(0x800, 4);
    for (i = 0; i < n; i++) {
        id = D_002BD250[i];
        if (func_00115600(id, p)) {
            buf[cnt] = id;
            cnt++;
        }
    }
    bd = lim[1];
    for (i = 0; i < cnt; i++) {
        func_00115408(buf[i], p, &h, 0);
        d = fabsf(p[1] - h);
        if (d < bd) {
            out[1] = h;
            bd = d;
            best = buf[i];
        }
    }
    out[0] = p[0];
    out[2] = p[2];
    func_001220b8(buf);
    return best;
}
#undef func_00115600

/* func_00118378 (from hand/text_00110000_h52.c). */
#define func_001195d8 ((void (*)(Ray52 *, RayW52 *)) func_001195d8)
#define func_00116368 ((void (*)(void *, s32)) func_00116368)
#define func_00117db0 ((void (*)()) func_00117db0)
void func_00118378(Ray52 *o, s32 a1, s32 a2, s32 a3) {
    s32 hit;
    s32 r1, r2;
    RayW52 *w;
    if (D_002C1304 == 1) {
        o->x30 = o->x34 = -1;
        return;
    }
    o->x34 = -1;
    r1 = -1;
    w = func_00122048(64, 4);
    func_001195d8(o, w);
    if (a2 == 0) r1 = func_0011c338(w, o, o->dir, w->x20, a3, &hit);
    if (D_002A62EC == 0) func_00116368(w, a1);
    else func_00117db0(w, a1);
    r2 = func_00118230(w->x18, o->pos, o->dir, w->x30);
    if (r1 != -1) {
        if (r2 == -1) {
            PlatVu0CopyVector(o->out, w->x20);
            o->x30 = r1;
            o->x34 = hit;
        } else if (v52_dist(o->pos, w->x20) < v52_dist(o->pos, w->x30)) {
            PlatVu0CopyVector(o->out, w->x20);
            o->x30 = r1;
            o->x34 = hit;
        } else {
            PlatVu0CopyVector(o->out, w->x30);
            o->x30 = r2;
        }
    } else {
            PlatVu0CopyVector(o->out, w->x30);
            o->x30 = r2;
    }
    func_001220b8(w);
}
#undef func_001195d8
#undef func_00116368
#undef func_00117db0

/* func_00118548 (from auto/text_00110000_6.c). */
extern s32 D_002A62F0;
#define func_00118060 ((void (*)(s32, s32, s32, s32)) func_00118060)
void func_00118548(s32 arg0) {
    if (D_002A62F0 != 0) {
        func_00118060(arg0, 9, 1, -1);
        return;
    }
    M2C_FIELD(arg0, s32 *, 0x34) = -1;
    M2C_FIELD(arg0, s16 *, 0x30) = -1;
}
#undef func_00118060

/* func_00118590 (from auto/text_00110000_6.c). */
#define func_00115408 ((void (*)(s32, s32, s32, s32)) func_00115408)
#define func_00118378 ((void (*)(s32, s32, s32, s32)) func_00118378)
void func_00118590(s32 arg0, s32 arg1) {
    s16 temp_a0;

    func_00118378(arg0, 5, arg1, -1);
    if (D_002C12C0 != 0) {
        temp_a0 = M2C_FIELD(arg0, s16 *, 0x30);
        if ((temp_a0 != -1) && (M2C_FIELD(arg0, s32 *, 0x34) == -1)) {
            func_00115408((s32) temp_a0, arg0 + 0x20, arg0 + 0x24, 1);
        }
    }
}
#undef func_00115408
#undef func_00118378

/* func_00118608 (from auto/text_00110000_6.c). */
#define func_00118060 ((void (*)(s32, s32, s32, s32)) func_00118060)
void func_00118608(s32 arg0) {
    func_00118060(arg0, 3, 0, -1);
}
#undef func_00118060

/* func_00118628 (from auto/text_00110000_6.c). */
#define func_00118060 ((void (*)(s32, s32, s32, s32)) func_00118060)
void func_00118628(s32 arg0, s32 arg1) {
    func_00118060(arg0, 3, 0, arg1);
}
#undef func_00118060

/* func_00118648 (from auto/text_00110000_6.c). */
#define func_00118060 ((void (*)(s32, s32, s32, s32)) func_00118060)
void func_00118648(s32 arg0) {
    func_00118060(arg0, 0xA, 1, -1);
}
#undef func_00118060

/* func_00118668 (from auto/text_00110000_11.c). */
#define func_00118378 ((void (*)(s32, s32, s32, s32)) func_00118378)
void func_00118668(s32 arg0) {
    func_00118378(arg0, 3, 0, -1);
}
#undef func_00118378

/* func_00118688 (from auto/text_00110000_11.c). */
#define func_00118378 ((void (*)(s32, s32, s32, s32)) func_00118378)
void func_00118688(s32 arg0, s32 arg1) {
    func_00118378(arg0, 3, 0, arg1);
}
#undef func_00118378

/* func_001186a8 (from hand/text_00110000_h52.c). */
typedef struct { f32 mn[3]; f32 mx[3]; u16 cnt; } Box52;
typedef struct { V4_52 pos; V4_52 dir; f32 x20; f32 x24; } Probe52;
#define func_00104f10 ((void (*)(s32, V4_52)) func_00104f10)
#define func_00116368 ((void (*)(void *, s32)) func_00116368)
#define func_00119a20 ((s32 (*)(s32, void *, void *, void *, f32 *)) func_00119a20)
#define func_00119ad8 ((s32 (*)(s32, s32, void *, void *, void *, f32 *)) func_00119ad8)
s32 func_001186a8(Probe52 *o) {
    V4_52 pt, x, n;
    Box52 box;
    s32 ids[512];
    s32 i, cnt, id;
    cnt = 0;
    D_002C1250 = o->x20 - 0.0079999999f;
    PlatVu0AddVector(pt, o->pos, o->dir);
    pt[1] -= o->x24;
    box.mn[0] = pt[0] - D_002C1250;
    box.mn[2] = pt[2] - D_002C1250;
    box.mn[1] = pt[1] - D_002C1250;
    box.mx[0] = pt[0] + D_002C1250;
    box.mx[1] = pt[1] + D_002C1250;
    box.mx[2] = pt[2] + D_002C1250;
    func_00116368(&box, 2);
    for (i = 0; i < box.cnt; i++) {
        id = D_002BD250[i];
        func_00104f10(id, n);
        if (func_00119a20(id, n, pt, x, &D_002C1250)) return id;
        ids[cnt] = id;
        cnt++;
    }
    for (i = 0; i < cnt; i++) {
        id = ids[i];
        func_00104f10(id, n);
        if (func_00119ad8(-1, id, n, pt, x, &D_002C1250)) return id;
    }
    return 0xffff;
}
#undef func_00104f10
#undef func_00116368
#undef func_00119a20
#undef func_00119ad8

/* func_00118868 (from hand/text_00110000_s6_03.c). */
typedef struct { f32 mn[3]; f32 mx[3]; s16 cnt; u8 pad[6]; } Qry;
typedef struct { V4 x0; V4 x10; f32 x20; u8 pad24[12]; V4 x30; } Mov;
typedef struct { u8 pad[0x20]; f32 r; f32 h; s32 flags; u8 pad2[0x54]; } ColObj;
void func_001047c8(void);
void func_00104528(void);
#define func_00104f10 ((void (*)(s32, f32 *)) func_00104f10)
#define func_00116368 ((void (*)(Qry *, s32)) func_00116368)
#define func_00117db0 ((void (*)(Qry *)) func_00117db0)
s32 func_00118868(Mov *o) {
    V4 a, b, c;
    Qry q;
    s32 miss[512];
    ColObj obj;
    s32 hit, retry;
    s64 res;
    s32 i, n, id;
    o->x0[3] = 1.0f;
    o->x10[3] = 1.0f;
    retry = 0;
    D_002C1250 = o->x20 - 0.007999999681f;
    PlatVu0AddVector(a, o->x0, o->x10);
    obj.r = o->x20;
    obj.h = 0.0f;
    func_001047c8();
loop:
    hit = 0;
    res = ((s32 (*)(ColObj *, f32 *, s32))func_0011b6a0)(&obj, a, 1);
    q.mn[0] = a[0] - o->x20;
    q.mn[2] = a[2] - o->x20;
    q.mn[1] = a[1] - o->x20;
    q.mx[2] = a[2] + o->x20;
    q.mx[0] = a[0] + o->x20;
    q.mx[1] = a[1] + o->x20;
    if (D_002A62EC == 0) func_00116368(&q, 7);
    else func_00117db0(&q);
    b[3] = 1.0f;
    n = 0;
    for (i = 0; i < (u16)q.cnt; i++) {
        id = D_002BD250[i];
        func_00104f10(id, c);
        if (func_00119a20(id, c, a, b, &D_002C1250)) {
            hit = 1;
            PlatVu0ScaleVectorXYZ(c, c, o->x20);
            PlatVu0AddVector(a, b, c);
        } else {
            miss[n++] = id;
        }
    }
    for (i = 0; i < n; i++) {
        id = miss[i];
        func_00104f10(id, c);
        if (func_00119ad8(-1, id, c, a, b, &D_002C1250)) {
            PlatVu0SubVector(a, a, b);
            hit = 1;
            PlatVu0Normalize(a, a);
            PlatVu0ScaleVectorXYZ(a, a, o->x20);
            PlatVu0AddVector(a, b, a);
        }
    }
    PlatVu0CopyVector(o->x30, a);
    if ((hit || res) && retry < 3) {
        retry++;
        goto loop;
    }
    func_00104528();
    return retry != 0;
}
#undef func_00104f10
#undef func_00116368
#undef func_00117db0

/* func_00118b58 (from hand/text_00110000_h52.c). */
typedef struct { V4_52 a; V4_52 b; f32 r; s32 x24; u8 pad[0x58]; } Sph52;
#define func_00104f10 ((void (*)(s32, V4_52)) func_00104f10)
#define func_00116368 ((void (*)(void *, s32)) func_00116368)
#define func_00117db0 ((void (*)()) func_00117db0)
#define func_00119a20 ((s32 (*)(s32, void *, void *, void *, f32 *)) func_00119a20)
#define func_00119ad8 ((s32 (*)(s32, s32, void *, void *, void *, f32 *)) func_00119ad8)
#define func_0011b6a0 ((s32 (*)(Sph52 *, f32 *, s32)) func_0011b6a0)
s32 func_00118b58(Probe52 *o) {
    V4_52 pt, x, n;
    Box52 box;
    s32 ids[512];
    Sph52 s;
    s32 i, cnt, id;
    o->dir[3] = o->pos[3] = 1.0f;
    D_002C1250 = o->x20 - 0.0079999999f;
    PlatVu0AddVector(pt, o->pos, o->dir);
    s.r = o->x20;
    s.x24 = 0;
    if (func_0011b6a0(&s, pt, 1)) return 1;
    func_001047c8();
    box.mn[0] = pt[0] - o->x20;
    box.mn[2] = pt[2] - o->x20;
    box.mn[1] = pt[1] - o->x24;
    box.mx[0] = pt[0] + o->x20;
    box.mx[1] = pt[1] + o->x24;
    box.mx[2] = pt[2] + o->x20;
    if (D_002A62EC == 0) func_00116368(&box, 7);
    else func_00117db0(&box);
    x[3] = 1.0f;
    cnt = 0;
    for (i = 0; i < box.cnt; i++) {
        id = D_002BD250[i];
        func_00104f10(id, n);
        if (func_00119a20(id, n, pt, x, &D_002C1250)) {
            func_00104528();
            return 1;
        }
        ids[cnt] = id;
        cnt++;
    }
    for (i = 0; i < cnt; i++) {
        id = ids[i];
        func_00104f10(id, n);
        if (func_00119ad8(-1, id, n, pt, x, &D_002C1250)) {
            func_00104528();
            return 1;
        }
    }
    func_00104528();
    return 0;
}
#undef func_00104f10
#undef func_00116368
#undef func_00117db0
#undef func_00119a20
#undef func_00119ad8
#undef func_0011b6a0

/* func_00118d78 (from auto/text_00110000.c). */
#define func_00104528 ((M2C_UNK (*)()) func_00104528)
#define func_001047c8 ((M2C_UNK (*)()) func_001047c8)
#define func_00118060 ((M2C_UNK (*)(s32, M2C_UNK, M2C_UNK, M2C_UNK)) func_00118060)
void func_00118d78(s32 arg0) {
    func_001047c8();
    func_00118060(arg0, 3, 0, -1);
    func_00104528();
}
#undef func_00104528
#undef func_001047c8
#undef func_00118060

/* func_00118db0 (from hand/text_00110000_h29.c). */
static inline void w29_copy(void *d, void *s) {
    __asm__ volatile(
        "lq $6, 0(%1)\n"
        "sq $6, 0(%0)\n"
        "nop\n"
        : : "r"(d), "r"(s) : "$6", "memory");
}
extern W29V4 D_002BD1E0;
s32 func_00118db0(void *p, W29V4 *v) {
    W29V4 c, prev, e[4];
    s32 i;
    s32 *idx = D_002BD160;
    for (i = 0; i < 4; i++) w29_sub(&e[i], &v[i], p);
    w29_copy(&prev, &D_002BD1E0);
    for (i = 0; i < 4; i++) {
        w29_outer(&c, &e[i], &e[idx[i]]);
        if (w29_dot(&prev, &c) < 0.0f) return 0;
        w29_copy(&prev, &c);
    }
    return 1;
}

/* func_00118ea0 (from hand/text_00110000_b01.c). */
typedef struct { u8 pad[0x10]; V4_01 x10; } Obj01;
extern V4_01 D_002BD1F0[];
static inline f32 dot01(f32 *a, f32 *b) {
    f32 r;
    __asm__ volatile(
        "lqc2 $vf4, 0(%1)\n"
        "lqc2 $vf5, 0(%2)\n"
        "vmul.xyz $vf5xyz, $vf4xyz, $vf5xyz\n"
        "vaddy.x $vf5x, $vf5x, $vf5y\n"
        "vaddz.x $vf5x, $vf5x, $vf5z\n"
        "qmfc2 $2, $vf5\n"
        "mtc1 $2, %0\n"
        : "=f"(r) : "r"(a), "r"(b) : "$2");
    return r;
}
#define func_00115200 ((s32 (*)(Obj01 *, f32 *, V4_01 *, f32 *, f32 *)) func_00115200)
#define func_00118db0 ((s32 (*)(f32 *, V4_01 *)) func_00118db0)
s32 func_00118ea0(Obj01 *id, f32 *n, f32 *mn, f32 *mx, s32 k) {
    V4_01 t[4];
    V4_01 out;
    s32 i;
    if (k < 6) return 1;
    t[0][3] = t[1][3] = t[2][3] = t[3][3] = 1.0f;
    for (i = 0; i < 6; i++) {
        if (dot01(D_002BD1F0[i], n) >= 0.0f) continue;
        switch (i) {
        case 0:
            t[0][0] = mn[0]; t[0][1] = mn[1]; t[0][2] = mx[2];
            t[1][0] = mx[0]; t[1][1] = mn[1]; t[1][2] = mx[2];
            t[2][0] = mx[0]; t[2][1] = mn[1]; t[2][2] = mn[2];
            t[3][0] = mn[0]; t[3][1] = mn[1]; t[3][2] = mn[2];
            break;
        case 1:
            t[0][0] = mx[0]; t[0][1] = mx[1]; t[0][2] = mx[2];
            t[1][0] = mn[0]; t[1][1] = mx[1]; t[1][2] = mx[2];
            t[2][0] = mn[0]; t[2][1] = mx[1]; t[2][2] = mn[2];
            t[3][0] = mx[0]; t[3][1] = mx[1]; t[3][2] = mn[2];
            break;
        case 2:
            t[0][0] = mn[0]; t[0][1] = mx[1]; t[0][2] = mn[2];
            t[1][0] = mn[0]; t[1][1] = mn[1]; t[1][2] = mn[2];
            t[2][0] = mx[0]; t[2][1] = mn[1]; t[2][2] = mn[2];
            t[3][0] = mx[0]; t[3][1] = mx[1]; t[3][2] = mn[2];
            break;
        case 3:
            t[0][0] = mx[0]; t[0][1] = mx[1]; t[0][2] = mx[2];
            t[1][0] = mx[0]; t[1][1] = mn[1]; t[1][2] = mx[2];
            t[2][0] = mn[0]; t[2][1] = mn[1]; t[2][2] = mx[2];
            t[3][0] = mn[0]; t[3][1] = mx[1]; t[3][2] = mx[2];
            break;
        case 4:
            t[0][0] = mn[0]; t[0][1] = mx[1]; t[0][2] = mx[2];
            t[1][0] = mn[0]; t[1][1] = mn[1]; t[1][2] = mx[2];
            t[2][0] = mn[0]; t[2][1] = mn[1]; t[2][2] = mn[2];
            t[3][0] = mn[0]; t[3][1] = mx[1]; t[3][2] = mn[2];
            break;
        case 5:
            t[0][0] = mx[0]; t[0][1] = mx[1]; t[0][2] = mn[2];
            t[1][0] = mx[0]; t[1][1] = mn[1]; t[1][2] = mn[2];
            t[2][0] = mx[0]; t[2][1] = mn[1]; t[2][2] = mx[2];
            t[3][0] = mx[0]; t[3][1] = mx[1]; t[3][2] = mx[2];
            break;
        }
        if (func_00115200(id, n, t, D_002BD1F0[i], out) && func_00118db0(out, t)) return 1;
    }
    return 0;
}
#undef func_00115200
#undef func_00118db0

/* func_00119128 (from hand/text_00110000_h3.c). */
#define func_00104f10 ((void (*)(void *, void *)) func_00104f10)
#define func_00104eb0 ((void (*)(void *, void *)) func_00104eb0)
#define func_001198c8 ((s32 (*)(s32, void *, void *)) func_001198c8)
s32 func_00119128(void *a0, void *a1, void *a2) {
    f32 c[4];
    f32 b[4];
    f32 a[4];
    func_00104eb0(a0, a);
    func_00104f10(a0, b);
    if (func_00115200(a1, a2, a, b, c) && func_001198c8(-1, a0, c)) return 1;
    return 0;
}
#undef func_00104f10
#undef func_00104eb0
#undef func_001198c8

/* func_001191c8 (from hand/text_00110000_b01.c). */
typedef struct { u32 b0:1; u32 p1:3; u32 k:4; u32 p8:9; u32 b17:1; u32 p18:11; u32 b29:1; u32 p30:2; } Bits01;
#define func_00115d58 ((s32 (*)(Qry01 *)) func_00115d58)
#define func_001158c8 ((void (*)(Qry01 *)) func_001158c8)
#define func_00119128 ((s32 (*)(s32, Obj01 *, f32 *)) func_00119128)
s32 func_001191c8(Qry01 *q, Obj01 *o, s32 mode) {
    s32 i;
    s32 *ip;
    s32 n, j;
    Node01 *e;
    u16 *p;
    s32 id;
    u32 w;
    u32 *f;
    s32 c;
    D_002C12C4 = 0;
    n = func_00115d58(q);
    ip = D_004E0428;
    func_001158c8(q);
    for (i = 0; i < n; i++) {
        e = D_002A6244[*ip++];
        if (!ov01(e->mn, e->mx)) continue;
        if (in01(e->mn, e->mx)) {
            if (!func_00118ea0(o, o->x10, e->mn, e->mx, e->n)) continue;
            p = e->ids;
            for (j = 0; j < e->n; j++) {
                s32 k;
                id = *p++;
                f = &D_002A6238[id].f.w;
                w = *f;
                if (w & 1) continue;
                if (mode != 8) {
                    if (mode != 11) continue;
                    if (((Bits01 *)f)->b29 == 1) continue;
                }
                k = (w >> 4) & 0xf;
                if (k == 7) continue;
                if (k == 9) continue;
                if ((w >> 17) & 1) continue;
                if (k == 5) continue;
                if (func_00119128(id, o, o->x10)) return 1;
            }
        } else {
            if (!func_00118ea0(o, o->x10, e->mn, e->mx, e->n)) continue;
            p = e->ids;
            for (j = 0; j < e->n; j++) {
                s32 k;
                id = *p++;
                f = &D_002A6238[id].f.w;
                w = *f;
                if (w & 1) continue;
                if (mode != 8) {
                    if (mode != 11) continue;
                    if (((Bits01 *)f)->b29 == 1) continue;
                }
                k = (w >> 4) & 0xf;
                if (k == 7) continue;
                if (k == 9) continue;
                if ((w >> 17) & 1) continue;
                if (k == 5) continue;
                if (func_001151a8(id, o->x10)) {
                    c = D_002C12C4;
                    func_00115940(id);
                    if (D_002C12C4 != c && func_00119128(id, o, o->x10)) return 1;
                }
            }
        }
    }
    return -1;
}
#undef func_00115d58
#undef func_001158c8
#undef func_00119128

/* func_001195d8 (from hand/text_00110000_h29.c). */
typedef struct { f32 mn[3]; f32 mx[3]; } W29Box;
void func_001195d8(W29V4 *a, W29Box *b) {
    W29V4 t;
    PlatVu0AddVector(&t, a, a + 1);
    {
        f32 p, q; q = t.v[0]; p = a->v[0];
        if (q > p) { b->mn[0] = p; b->mx[0] = q; }
        else { b->mx[0] = p; b->mn[0] = q; }
    }
    {
        f32 p, q; q = t.v[1]; p = a->v[1];
        if (q > p) { b->mn[1] = p; b->mx[1] = q; }
        else { b->mx[1] = p; b->mn[1] = q; }
    }
    {
        f32 p = a->v[2], q = t.v[2];
        if (p < q) { b->mn[2] = p; b->mx[2] = q; }
        else { b->mx[2] = p; b->mn[2] = q; }
    }
}

/* func_00119688 (from auto/text_00110000_17.c). */
#define func_001047c8 ((M2C_UNK (*)()) func_001047c8)
#define func_001195d8 ((M2C_UNK (*)(s32, void *)) func_001195d8)
#define func_001191c8 ((s32 (*)(void *, s32, M2C_UNK)) func_001191c8)
#define func_0011c338 ((s32 (*)(void *, s32, s32, M2C_UNK *, M2C_UNK, M2C_UNK *)) func_0011c338)
#define func_00104528 ((void (*)()) func_00104528)
s32 func_00119688(s32 arg0) {
  M2C_UNK *new_var;
  s32 sp[16];
  s32 temp_s0;
  s32 temp_s1;
  s32 var_v0;
  func_001047c8();
  func_001195d8(arg0, sp);
  new_var = &(*((M2C_UNK *) (((s8 *) sp) + 0x30)));
  temp_s1 = func_0011c338(sp, arg0, arg0 + 0x10, &(*((M2C_UNK *) (((s8 *) sp) + 0x20))), -1, new_var);
  temp_s0 = func_001191c8(sp, arg0, 8);
  func_00104528();
  var_v0 = -1;
  if (!((temp_s1 != (-1)) || (temp_s0 != temp_s1)))
  {
    return var_v0;
  }
  ;
  return 1;
}
#undef func_001047c8
#undef func_001195d8
#undef func_001191c8
#undef func_0011c338
#undef func_00104528

/* func_00119710 (from auto/text_00110000_16.c). */
#define func_001195d8 ((f32 (*)(s32, s32)) func_001195d8)
#define func_001191c8 ((s32 (*)(s32, s32, s32)) func_001191c8)
#define func_0011c338 ((s32 (*)(s32, s32, s32, s32, s32, s32)) func_0011c338)
s32 func_00119710(s32 arg0) {
    s32 sp[16];    s32 temp_s1;
    s32 var_v0;

    func_001195d8(arg0, (s32) sp);
    temp_s1 = func_0011c338((s32) sp, arg0, arg0 + 0x10, (s32) &M2C_FIELD(sp, M2C_UNK *, 0x20), -1, (s32) &M2C_FIELD(sp, M2C_UNK *, 0x30));
    var_v0 = func_001191c8((s32) sp, arg0, 8);
    if (!((temp_s1 != -1) || (var_v0 != temp_s1))) {
        return var_v0;
    }
    var_v0 = 1;
    return var_v0;
}
#undef func_001195d8
#undef func_001191c8
#undef func_0011c338

/* func_00119788 (from hand/text_00110000_h3.c). */
#define func_001191c8 ((s32 (*)(void *, void *, s32)) func_001191c8)
#define func_001195d8 ((void (*)(void *, void *)) func_001195d8)
s32 func_00119788(void *a0) {
    u8 buf[32];
    s32 r;
    func_001047c8();
    func_001195d8(a0, buf);
    r = func_001191c8(buf, a0, 11);
    func_00104528();
    return r != -1 ? 1 : -1;
}
#undef func_001191c8
#undef func_001195d8

/* func_001197e0 (from hand/text_00110000_s6_03.c). */
s32 func_001197e0(f32 *a, f32 *b, f32 *c) {
    s32 t;
    t = c[0] < a[0];
    if (b[0] < c[0]) { t ^= 1; if (!t) goto z1; } else if (!t) goto zero;
    t = c[1] < a[1];
    if (b[1] < c[1]) { t ^= 1; if (!t) goto z1; } else if (!t) goto zero;
    t = c[2] < a[2];
    if (b[2] < c[2]) { t ^= 1; if (!t) goto z1; } else if (!t) goto zero;
    return 1;
z1:
    return 0;
zero:
    return 0;
}

/* func_001198c8 (from hand/text_00110000_cc.c). */
typedef kh1_s128 u128;
extern u128 D_002C12F0;
static inline void vsubv(f32 *d, f32 *a, f32 *b) {
    __asm__ volatile(
        "lqc2 $vf4, 0(%1)\n"
        "lqc2 $vf5, 0(%2)\n"
        "vsub.xyzw $vf6xyzw, $vf4xyzw, $vf5xyzw\n"
        "sqc2 $vf6, 0(%0)\n"
        "nop\n"
        : : "r"(d), "r"(a), "r"(b) : "memory");
}
static inline void vcross(f32 *d, f32 *a, f32 *b) {
    __asm__ volatile(
        "lqc2 $vf4, 0(%1)\n"
        "lqc2 $vf5, 0(%2)\n"
        "vopmula.xyz ACC, $vf4xyz, $vf5xyz\n"
        "vopmsub.xyz $vf6xyz, $vf5xyz, $vf4xyz\n"
        "vsub.w $vf6w, $vf6w, $vf6w\n"
        "sqc2 $vf6, 0(%0)\n"
        "nop\n"
        : : "r"(d), "r"(a), "r"(b) : "memory");
}
static inline f32 vdot(f32 *a, f32 *b) {
    f32 r;
    __asm__ volatile(
        "lqc2 $vf4, 0(%1)\n"
        "lqc2 $vf5, 0(%2)\n"
        "vmul.xyz $vf5xyz, $vf4xyz, $vf5xyz\n"
        "vaddy.x $vf5x, $vf5x, $vf5y\n"
        "vaddz.x $vf5x, $vf5x, $vf5z\n"
        "qmfc2 $2, $vf5\n"
        "mtc1 $2, %0\n"
        : "=f"(r) : "r"(a), "r"(b) : "$2");
    return r;
}
static inline void vcopy(void *d, void *s) {
    __asm__ volatile(
        "lq $6, 0(%1)\n"
        "sq $6, 0(%0)\n"
        "nop\n"
        : : "r"(d), "r"(s) : "$6", "memory");
}
#define func_00104ae0 ((s32 (*)(s32, V4 *)) func_00104ae0)
#define func_0011aa18 ((s32 (*)(s32, s32, V4 *)) func_0011aa18)
/* func_00119a20 and func_00119ef8 only match with their callee func_001198c8
 * defined above them. */
s32 func_001198c8(s32 a0, s32 a1, f32 *p) {
    V4 c, n;
    V4 pts[4];
    s32 i, cnt;
    s32 *idx;
    if (a0 == -1) cnt = func_00104ae0(a1, pts);
    else cnt = func_0011aa18(a0, a1, pts);
    if (cnt == 3) idx = D_002BD150;
    else idx = D_002BD160;
    for (i = 0; i < cnt; i++) vsubv(pts[i], pts[i], p);
    vcopy(n, &D_002C12F0);
    for (i = 0; i < cnt; i++) {
        vcross(c, pts[i], pts[idx[i]]);
        if (vdot(n, c) < 0.0f) return 0;
        vcopy(n, c);
    }
    return 1;
}
#undef func_00104ae0
#undef func_0011aa18

/* func_00119a20 (from hand/text_00110000_cc.c). */
static inline void vscale(f32 *d, f32 *s, f32 t) {
    __asm__ volatile(
        "lqc2 $vf4, 0(%1)\n"
        "lw $8, 0(%2)\n"
        "qmtc2 $8, $vf5\n"
        "vmulx.xyzw $vf6xyzw, $vf4xyzw, $vf5x\n"
        "sqc2 $vf6, 0(%0)\n"
        : : "r"(d), "r"(s), "r"(&t) : "$8", "memory");
}
/* func_00119a20 and func_00119ef8 only match with their callee func_001198c8
 * defined above them. */
s32 func_00119a20(s32 i, f32 *n, f32 *p, f32 *out, f32 *maxd) {
    V4 t;
    f32 d;
    d = vdot(p, n) + D_002A6238[i].d;
    if (*maxd < d) return 0;
    if (d < 0.0f) return 0;
    vscale(t, n, d);
    vsubv(out, p, t);
    return func_001198c8(-1, i, out) != 0;
}

/* func_00119ad8 (from hand/text_00110000_s7_w12.c). */
static inline void vaddv(f32 *d, f32 *a, f32 *b) {
    __asm__ volatile(
        "lqc2 $vf4, 0(%1)\n"
        "lqc2 $vf5, 0(%2)\n"
        "vadd.xyzw $vf6xyzw, $vf4xyzw, $vf5xyzw\n"
        "sqc2 $vf6, 0(%0)\n"
        "nop\n"
        : : "r"(d), "r"(a), "r"(b) : "memory");
}
static inline f32 vdist2(void *a, void *b) {
    f32 r;
    __asm__ volatile(
        "lqc2 $vf6, 0(%1)\n"
        "lqc2 $vf4, 0(%2)\n"
        "vsub.xyzw $vf5xyzw, $vf6xyzw, $vf4xyzw\n"
        "vmove.xyzw $vf4xyzw, $vf5xyzw\n"
        "vmul.xyz $vf5xyz, $vf4xyz, $vf5xyz\n"
        "vaddy.x $vf5x, $vf5x, $vf5y\n"
        "vaddz.x $vf5x, $vf5x, $vf5z\n"
        "qmfc2 $2, $vf5\n"
        "mtc1 $2, %0\n"
        : "=f"(r) : "r"(a), "r"(b) : "$2");
    return r;
}
extern V4 D_002C12E0;
#define func_00104ae0 ((s32 (*)(s32, V4 *)) func_00104ae0)
#define func_0011aa18 ((s32 (*)(s32, s32, V4 *)) func_0011aa18)
s32 func_00119ad8(s32 a0, s32 a1, f32 *n, f32 *p, f32 *out, f32 *maxd) {
    V4 d, e0, e1, w;
    V4 pts[4];
    V4 hits[4];
    f32 t;
    s32 nhit;
    s32 cnt, i, best, bk;
    s32 *idx;
    f32 r2, dd, min, m1;
    f32 *src;
    r2 = *maxd * *maxd;
    nhit = 0;
    if (a0 == -1) cnt = func_00104ae0(a1, pts);
    else cnt = func_0011aa18(a0, a1, pts);
    if (cnt == 3) idx = D_002BD150;
    else idx = D_002BD160;
    for (i = 0; i < cnt; i++) {
        vcopy(e0, pts[i]);
        vcopy(e1, pts[idx[i]]);
        vsubv(d, e1, pts[i]);
        vsubv(w, e0, p);
        t = -(vdot(w, d) / vdot(d, d));
        vscale(d, d, t);
        vaddv(out, d, e0);
        if (vdist2(p, out) <= r2) {
            vaddv(e1, e1, D_002C12E0);
            vaddv(e0, e0, D_002C12E0);
            if (!func_001197e0(e1, e0, out)) {
                vcopy(hits[nhit++], out);
            }
        }
    }
    if (nhit) {
        best = 0;
        m1 = 1.0e12f;
        for (i = 0; i < nhit; i++) {
            vsubv(out, p, hits[i]);
            dd = vdot(out, out);
            if (dd < m1) { m1 = dd; best = i; }
        }
        vcopy(out, hits[best]);
        return 1;
    } else {
        bk = cnt;
        min = r2;
        for (i = 0; i < cnt; i++) {
            dd = vdist2(p, pts[i]);
            if (dd <= min) { min = dd; bk = i; }
        }
        if (cnt != bk) {
            vcopy(out, pts[bk]);
            return 1;
        }
    }
    return 0;
}
#undef func_00104ae0
#undef func_0011aa18

/* func_00119e80 (from hand/text_00110000_s6_03.c). */
#define func_0011a9c8 ((void (*)(s32, s32, V4 *)) func_0011a9c8)
f32 func_00119e80(s32 a0, s32 a1, f32 *n, f32 *p) {
    V4 v;
    f32 d;
    func_0011a9c8(a0, a1, &v);
    d = -vdot(n, v);
    return vdot(p, n) + d;
}
#undef func_0011a9c8

/* func_00119ef8 (from hand/text_00110000_cc.c). */
/* func_00119a20 and func_00119ef8 only match with their callee func_001198c8
 * defined above them. */
s32 func_00119ef8(s32 a0, s32 a1, f32 *n, f32 *p, f32 *out, f32 *maxd) {
    V4 t;
    f32 d;
    d = func_00119e80(a0, a1, n, p);
    if (*maxd < d) return 0;
    if (d < 0.0f) return 0;
    vscale(t, n, d);
    vsubv(out, p, t);
    return func_001198c8(a0, a1, out) != 0;
}

/* func_00119fc0 (from hand/text_00110000_h29.c). */
static inline void w29_scale4(void *d, void *s, f32 t) {
    __asm__ volatile(
        "lqc2 $vf4, 0(%1)\n"
        "lw $8, 0(%2)\n"
        "qmtc2 $8, $vf5\n"
        "vmulx.xyzw $vf6xyzw, $vf4xyzw, $vf5x\n"
        "sqc2 $vf6, 0(%0)\n"
        : : "r"(d), "r"(s), "r"(&t) : "$8", "memory");
}
#define func_001198c8 ((s32 (*)(s32, s32, void *)) func_001198c8)
s32 func_00119fc0(s32 i, void *n, void *p, void *out, f32 *maxd) {
    W29V4 t;
    f32 d;
    d = w29_dot(p, n) + D_002A6238[i].d;
    if (*maxd < d) return 0;
    w29_scale4(&t, n, d);
    w29_sub(out, p, &t);
    return func_001198c8(-1, i, out) != 0;
}
#undef func_001198c8


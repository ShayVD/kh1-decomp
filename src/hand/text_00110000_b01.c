#include "common.h"
typedef f32 V4_01[4] __attribute__((aligned(16)));
typedef struct { u8 pad[0x10]; V4_01 x10; } Obj01;
typedef struct { u32 b0:1; u32 p1:3; u32 k:4; u32 p8:9; u32 b17:1; u32 p18:11; u32 b29:1; u32 p30:2; } Bits01;
typedef struct { f32 minx, p0[3], miny, p1[3], minz, p2[3], maxx, p3[3], maxy, p4[3], maxz, p5[3]; } Box01;
extern Box01 D_002C1260;
extern s32 D_002C12C4;
extern s32 D_002BD250[];
extern s32 D_004E0428[];
typedef struct { f32 mn[3]; f32 mx[3]; u16 n; u16 ids[1]; } Node01;
extern Node01 **D_002A6244;
typedef struct { u32 a, b, c, d; u32 f; } Tri01;
extern Tri01 *D_002A6238;
typedef struct { u8 pad[0x18]; s16 cnt; } Qry01;
s32 func_00115d58(Qry01 *);
void func_001158c8(Qry01 *);
void func_00115940(s32);

static inline s32 ov01(f32 *mn, f32 *mx) {
    if (mn[0] <= D_002C1260.maxx && D_002C1260.minx <= mx[0] && D_002C1260.maxy >= mn[1] &&
        D_002C1260.miny <= mx[1] && D_002C1260.maxz >= mn[2] && D_002C1260.minz <= mx[2]) return 1;
    return 0;
}
static inline s32 in01(f32 *mn, f32 *mx) {
    if (D_002C1260.minx < mn[0] && D_002C1260.maxx > mx[0] && D_002C1260.miny < mn[1] &&
        D_002C1260.maxy > mx[1] && D_002C1260.minz < mn[2] && D_002C1260.maxz > mx[2]) return 1;
    return 0;
}

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
                    f = &D_002A6238[id].f;
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
                    f = &D_002A6238[id].f;
                    if (!(*f & 1)) func_00115940(id);
                }
            }
        }
    }
    q->cnt = D_002C12C4;
}

/* needs make: uses rodata */
extern V4_01 D_002BD1F0[];
s32 func_00115200(Obj01 *, f32 *, V4_01 *, f32 *, f32 *);
s32 func_00118db0(f32 *, V4_01 *);

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

s32 func_00119128(s32, Obj01 *, f32 *);
s32 func_001151a8(s32, f32 *);

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
                f = &D_002A6238[id].f;
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
                f = &D_002A6238[id].f;
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

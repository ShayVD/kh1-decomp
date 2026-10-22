#include "common.h"
/* 0011b220: one RFlg *f for both loops; scale helper with separate dst/src operands (sceVu0ScaleVector form) */
typedef f32 V4[4] __attribute__((aligned(16)));
typedef struct { u8 pad[16]; s32 x10; } Rec20w;
typedef struct { Rec20w *x0; u8 pad[60]; } Ent2458;
extern Ent2458 D_004E2458[];
/* 16-byte collision entries at D_003044D8, D_003044D0 of them. */
#include "data/pieces/D_003044D8.h"
typedef ColFlags_3044d8 ColFlags;
typedef ColEnt_3044d8 ColEnt;
extern s32 D_003044D0;
void func_001158c8(void *);
void func_001158c8(void *);
s32 func_0011ab88(s32, s32, void *);
extern f32 D_002C1250;
s32 func_00119ad8(s32, s32, f32 *, f32 *, f32 *, f32 *);
typedef struct { u32 lo : 4; u32 type : 4; u32 rest : 24; } RFlg;
typedef struct { u8 pad[16]; RFlg f; } Rec20b;
typedef s32 (*RFn)(RFlg *);
#include "data/pieces/D_002C1300.h"
extern s32 D_002BC128;
extern s32 D_002BC130;
void func_0011a978(s32, s32, f32 *);
s32 func_00119ef8(s32, s32, f32 *, f32 *, f32 *, f32 *);
static inline void vscale2(f32 *d, f32 *v, f32 s) {
    __asm__ volatile(
        "lqc2 $vf4, 0(%1)\n"
        "lw $8, 0(%2)\n"
        "qmtc2 $8, $vf5\n"
        "vmulx.xyz $vf4xyz, $vf4xyz, $vf5x\n"
        "sqc2 $vf4, 0(%0)\n"
        : : "r"(d), "r"(v), "r"(&s) : "$8", "memory");
}
static inline void vadd3(f32 *d, f32 *a, f32 *b) {
    __asm__ volatile(
        "lqc2 $vf4, 0(%1)\n"
        "lqc2 $vf5, 0(%2)\n"
        "vadd.xyzw $vf6xyzw, $vf4xyzw, $vf5xyzw\n"
        "sqc2 $vf6, 0(%0)\n"
        "nop\n"
        : : "r"(d), "r"(a), "r"(b) : "memory");
}
static inline void vsub3(f32 *d, f32 *a, f32 *b) {
    __asm__ volatile(
        "lqc2 $vf4, 0(%1)\n"
        "lqc2 $vf5, 0(%2)\n"
        "vsub.xyzw $vf6xyzw, $vf4xyzw, $vf5xyzw\n"
        "sqc2 $vf6, 0(%0)\n"
        "nop\n"
        : : "r"(d), "r"(a), "r"(b) : "memory");
}
static inline void vnorm(f32 *d, f32 *a) {
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
        : : "r"(d), "r"(a) : "memory");
}
u64 func_0011b220(s32 a0, f32 *out, void *a2, s32 a3, f32 scale) {
    V4 p;
    V4 n;
    s32 list1[256];
    s32 list2[256];
    s32 n2;
    s32 cnt;
    s32 i, id;
    s64 hit;
    Rec20b *rec;
    u16 *ids;
    u8 *h;
    u16 *hd;
    RFlg *f;

    h = (u8 *)D_003044D8[a0].x4;
    h += *(s32 *)(h + 16);
    rec = (Rec20b *)D_004E2458[a0].x0;
    hd = (u16 *)(h + *(s32 *)(h + 32));
    p[3] = 1.0f;
    hit = 0;
    cnt = 0;
    n2 = 0;
    func_001158c8(a2);
    for (i = 0; i < *hd; i++) {
        id = hd[i + 1];
        f = &rec[id].f;
        if (f->type == 0) continue;
        if (!func_0011ab88(a0, id, a2)) continue;
        func_0011a978(a0, id, n);
        if (f->type == 3) {
            if (a3 == 0 && n[1] < -0.167f) continue;
            if (func_00119ef8(a0, id, n, out, p, &D_002C1250)) {
                hit = 1;
                vscale2(n, n, scale);
                vadd3(out, p, n);
                list2[n2++] = id;
            } else {
                list1[cnt++] = id;
            }
        } else {
            if (D_002BC128 == 10 && D_002BC130 == 7 && (*(RFn *)&D_002C1300)(f)) continue;
            if (func_00119ef8(a0, id, n, out, p, &D_002C1250)) {
                hit = 1;
                vscale2(n, n, scale);
                vadd3(out, p, n);
                list2[n2++] = id;
            } else {
                list1[cnt++] = id;
            }
        }
    }
    for (i = 0; i < cnt; i++) {
        id = list1[i];
        f = &rec[id].f;
        if (f->type == 0) continue;
        func_0011a978(a0, id, n);
        if (f->type == 3) {
            if (n[1] < -0.167f) continue;
            if (func_00119ad8(a0, id, n, out, p, &D_002C1250)) {
                hit = 1;
                vsub3(out, out, p);
                vnorm(out, out);
                vscale2(out, out, scale);
                vadd3(out, p, out);
            }
        } else {
            if (D_002BC128 == 10 && D_002BC130 == 7 && (*(RFn *)&D_002C1300)(f)) continue;
            if (func_00119ad8(a0, id, n, out, p, &D_002C1250)) {
                hit = 1;
                vsub3(out, out, p);
                vnorm(out, out);
                vscale2(out, out, scale);
                vadd3(out, p, out);
            }
        }
    }
    return hit << (a0 + 1);
}


#include "data/data_002B.h"
#include "data/data_002C.h"
#include "data/pieces/D_002BC128.h"

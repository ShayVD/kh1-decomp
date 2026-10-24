#include "common.h"
#include "data/bss_004F.h"

#include "data/types/text_00110000_h53_p.h"

static inline f32 w53_dot(void *a, void *b) {
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

static inline void w53_scale(void *d, void *s, f32 t) {
    __asm__ volatile(
        "lqc2 $vf4, 0(%1)\n"
        "lw $8, 0(%2)\n"
        "qmtc2 $8, $vf5\n"
        "vmulx.xyz $vf4xyz, $vf4xyz, $vf5x\n"
        "sqc2 $vf4, 0(%0)\n"
        : : "r"(d), "r"(s), "r"(&t) : "$8", "memory");
}

static inline void w53_add(void *d, void *a, void *b) {
    __asm__ volatile(
        "lqc2 $vf4, 0(%1)\n"
        "lqc2 $vf5, 0(%2)\n"
        "vadd.xyzw $vf6xyzw, $vf4xyzw, $vf5xyzw\n"
        "sqc2 $vf6, 0(%0)\n"
        "nop\n"
        : : "r"(d), "r"(a), "r"(b) : "memory");
}

void func_0011a978(s32, s32, V53 *);
void func_0011a9c8(s32, s32, V53 *);

s32 func_0011bfc8(s32 a0, s32 a1, void *p0, void *dir, void *out) {
    V53 n, p;
    f32 den, t;
    func_0011a978(a0, a1, &n);
    den = w53_dot(&n, dir);
    if (den >= 0.0f) return 0;
    func_0011a9c8(a0, a1, &p);
    t = (w53_dot(&n, &p) - w53_dot(&n, p0)) / den;
    if (t < 0.0f) return 0;
    if (t > 1.0f) return 0;
    w53_scale(out, dir, t);
    w53_add(out, out, p0);
    return 1;
}

extern f32 D_002C5980[4];
extern f32 D_002C5C20;
f32 func_00120bf8(void *);
void func_002673b8(void *, void *);
void func_00267560(void *, void *, f32);

s32 func_0011f370(V53 *st, u8 *pad) {
    s32 bits = 0;
    s32 s, j;
    f32 v, len;
    V53 *d = st;
    for (s = 0; s < 2; s++) {
        for (j = 0; j < 2; j++) {
            v = (f32)pad[s * 2 + 2 + j] - 127.5f;
            D_002C5980[j] = v;
            if (v > 0.0f) {
                D_002C5980[j] = v - D_002C5C20;
                if (D_002C5980[j] < 0.0f) {
                    D_002C5980[j] = 0.0f;
                } else {
                    bits |= ((j * 5) ^ 1) << (s * 8 + 21 - j);
                }
            } else {
                D_002C5980[j] = v + D_002C5C20;
                if (D_002C5980[j] > 0.0f) {
                    D_002C5980[j] = 0.0f;
                } else {
                    bits |= ((j * 5) ^ 4) << (s * 8 + 21 - j);
                }
            }
            D_002C5980[j] = D_002C5980[j] / (127.5f - D_002C5C20);
        }
        len = func_00120bf8(D_002C5980);
        if (len > 1.0f) len = 1.0f;
        func_002673b8(&d[5], D_002C5980);
        d[5].w = 1.0f;
        func_00267560(&d[3], &d[5], len);
        d++;
    }
    return bits;
}

typedef struct { u64 a, b; } Q53;
Q53 *func_0011fb38(s32, u64, Q53 *);
void func_0011fb48(Q53 *, s32, Q53 *);
void func_0011fb78(Q53 *, s32, Q53 *);

Q53 *func_0011fbb0(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6, u32 a7, s32 a8, Q53 *buf) {
    Q53 *p, *r, *t;
    t = buf + 1;
    p = func_0011fb38(0x50, (u64)a0 << 32 | (u64)a1 << 48 | (u64)a2 << 56, buf + 2);
    p = func_0011fb38(0x51, (u64)a3 << 32 | (u64)a4 << 48, p);
    p = func_0011fb38(0x52, (u64)a5 | (u64)a6 << 32, p);
    p = func_0011fb38(0x53, 0, p);
    func_0011fb48(t, 0, p);
    t = p;
    p++;
    t->a = (u64)a7 | 0x8000ULL << 44;
    func_0011fb78(buf, 1, p);
    r = p;
    p++;
    r->a = (u64)(a7 | 0x30000000) | (u64)a8 << 32;
    r = p++;
    t = p++;
    p = func_0011fb38(63, 0, p);
    func_0011fb48(t, 1, p);
    func_0011fb78(r, 7, p);
    return r;
}

#include "data/types/text_00110000_h53_p2.h"
float cosf(float);
char D_004F7150[0x4][32] ALIGNED(16);
extern char *D_002C6460[];
extern u8 D_00491A18[];

static inline s32 w53_toupper(s32 c) {
    return ((D_00491A18 + 1)[c] & 2) ? c - 32 : c;
}
void func_002675a8(V53 *, V53 *);
float cosf(float);

#include "data/types/text_00110000_h53.h"
extern f32 D_004F7650, D_004F77E0;

#define FLD(T, p, off) (*(T *)((u8 *)(p) + (off)))

/* needs make: uses rodata */
void func_002675a8(V53 *, V53 *);

#define FLD(T, p, off) (*(T *)((u8 *)(p) + (off)))
extern f32 D_004F77E0;

/* Pointer tables only this file uses (phase 4, tools/shift/define_ptr_tables.py). */
/* D_0046A6A8 stays extern: the dktitle.x overlay also writes it (two %lo fields), so it is shared. */
extern u8 D_0048D2C8[];
extern u8 D_0048D2D0[];
extern u8 D_0048D2D8[];
extern u8 D_0048D2E0[];
extern u8 D_0048D2E8[];
extern u8 D_0048D2F0[];
extern u8 D_0048D2F8[];
extern u8 D_0048D300[];
extern u8 D_0048D308[];
extern u8 D_0048D310[];
extern u8 D_0048D318[];
char *D_002C6460[0xb] ALIGNED(16) = {
    (void *)D_0048D318, (void *)D_0048D310, (void *)D_0048D308, (void *)D_0048D300,
    (void *)D_0048D2F8, (void *)D_0048D2F0, (void *)D_0048D2E8, (void *)D_0048D2E0,
    (void *)D_0048D2D8, (void *)D_0048D2D0, (void *)D_0048D2C8,
};
#include "data/data_002B.h"
#include "data/data_002C.h"
#include "data/data_002E.h"
#include "data/data_0049.h"
#include "data/data_0048.h"

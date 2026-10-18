/* func_001c53c8 (hand/nostrict_nofill, no context). s10 r2_9 from r2_6__001c53c8_42w.c: (1) `u = (t - c0) / dt;` instead of reassigning x (c0 outlives x, so cse keeps c0 in the sub: FP regs exact); (2) `k = 0;` before the block-local `Elem *m = e->next;` (move a3,zero first); (3) the b==2 arm writes out the q20/q30 memcpys + call + return instead of `goto tail` (jump2 merges them; +2 refs each lifts &q20/&q30 over the loop base copy: s5/s6/s7). */
#include "common.h"

typedef struct { u32 b0:1, b1:1, b2:1, b3:1, b4:1, rest:27; } Bits;

typedef struct {
    s32 x0;
    s32 x4;
    u8 pad8[0xc];
    f32 f14, f18, f1c, f20;
    u8 pad24[0x4c];
    s8 *code;
    s32 n;
    s32 x78;
    u32 lbl[64];
    u32 pc;
    s32 sp;
    s32 stk[32];
    s32 var[26];
    s32 stk2[33];
    s32 x2f0;
    f32 x2f4;
    s32 ret[8];
    s32 rsp;
    s32 x31c, x320, x324;
    u32 b0:1, b1:1, b2:1, b3:1, b4:1, b5:1, b6:1, b7:1, b8:1, b9:1, b10:1, b11:1, b12:1, b13:1, b14:1, b15:1, brest:16;
    u8 pad32c[0x24];
} __attribute__((aligned(8))) VMa;

typedef struct {
    u8 pad0[4];
    s32 x4;
    u8 pad8[0x3c];
    s32 x44;
    u8 pad48[0x24];
    s32 x6c;
} Q48;

typedef struct {
    u8 pad0[0x1034];
    s32 a1034[512];
    s32 a1834[512];
    s32 a2034[512];
    s32 a2834[512];
    s32 x3034;
    u8 pad3038[8];
    u8 *x3040;
    u8 *x3044;
    u32 x3048;
    s32 *x304c;
    u32 x3050;
    s32 *x3054;
    s32 x3058;
    s32 x305c;
    s32 *x3060;
    s32 x3064;
    s32 *x3068;
    s32 x306c;
    union { u64 x; s32 w[2]; struct { u32 lo; u32 p0:6, b38:1, b39:1, p40:3, b43:1, p44:9, b53:1, p54:10; } __attribute__((aligned(8))) f; } f3070;
    union { u64 x; struct { u32 b0:1, b1:1, b2:1, b3:1, b4:1, b5:1, b6:1, b7:1, b8:1, b9:1, b10:1, brest:21; u32 hi; } __attribute__((aligned(8))) b; } f3078;
    u8 pad3080[0x3148 - 0x3080];
    u32 x3148;
    u8 pad314c[0x3158 - 0x314c];
    s32 x3158[5];
    void *x316c;
    u8 pad3170[0x3178 - 0x3170];
    s32 x3178;
} BigA;

extern BigA D_00389C90;
extern u32 D_0037A378;
extern s32 D_002C5958;
extern VMa D_0038D170[];
extern VMa D_0039A580[];
extern s32 D_0039A570;
extern s32 D_003A7980;
extern u8 D_003DE570[];
s32 func_001c1ce8(s8 *, s32);
void func_001c19f8(VMa *, s32);
void func_001c4198(void *, s32);

typedef f32 Vec[4] __attribute__((aligned(16)));
typedef struct Elem {
    s32 a;
    s32 b;
    s32 c;
    s32 pad;
    Vec m[11];
    f32 f[6];
    struct Elem *next;
    struct Elem *prev;
} Elem;
typedef struct {
    f32 x0;
    u8 pad4[0xc];
    Vec q10, q20, q30, q40;
    Vec q50;
    f32 x60;
    u8 pad64[0xf0 - 0x64];
    Elem arr[256];
    s32 n;
    f32 xE0F4;
    Elem *first;
    Elem *last;
} Scn;
extern Scn D_0037A380;
typedef struct {
    u8 pad0[0xd0];
    Vec v[5];
    f32 f120, f124;
} __attribute__((aligned(16))) CamS;
extern CamS D_003C5510;
extern s32 D_003C5500;
void func_001c53c8(f32);
void func_001c6a20(void);
void func_001c5b88(void);
void func_0011ef10(s32, void *);
VMa *func_001e98d0(s32, s32);

extern s8 *D_003C39AC;
extern s32 D_006277E0, D_006277E4, D_006297F0, D_006297F4;
extern u32 D_00389C80;
extern u8 *D_00388480[];
extern s32 (*D_0037A198[])(VMa *, s32);
s32 func_001ee200(void);
void srand(u32);
void func_001c29d8(void);
void func_001c6720(void);
void func_001cab48(void);
void func_001c2d20(s8 *, void *, void *);
s32 func_001c1cf8(s8 *, s32);
void func_001c2778(void);

typedef struct {
    u8 type;
    u64 val:24;
    s32 x;
    s32 a8;
    s32 ac;
    f32 v[4];
} Msg;
typedef struct {
    u8 pad0[4];
    s32 x4;
    s32 x8;
    u8 padc[0x34];
    s32 x40[3];
    u8 pad4c[0x14];
    s32 x60[3];
} S5BB0;
typedef struct {
    u8 pad0[0x10];
    VMa *vm;
    s32 n;
    s32 x18;
} Task;
extern S5BB0 D_002C5BB0;
extern u32 D_003C39A8;
extern u8 *D_003C21A8[];
extern f32 D_002BBDFC;
Msg *func_001c4730(void);
void func_001c4788(Msg *);
s32 func_001c4640(Msg *);
void func_001cebe8(void);
void func_001cff28(void);
void func_001cfff8(void);
void func_001ca800(void);
void func_001dcea8(VMa *);
void func_001dcfd0(VMa *);
void func_001e9fe8(Vec *dst, Vec *src);
void func_001e9f18(Vec *dst, Vec *a, Vec *b, f32 t);
f32 func_001e9e58(Vec *a, Vec *b);
void func_001e9d00(Vec *d, Vec *a, Vec *b, f32 t);
void func_001c5168(void);

static inline f32 herm(f32 u, f32 u2, f32 u3, f32 dt, f32 p0, f32 p1, f32 m0, f32 m1) {
    f32 h1 = 2.0f * u3 - 3.0f * u2 + 1.0f;
    f32 h2 = -2.0f * u3 + 3.0f * u2;
    f32 h3 = u3 - 2.0f * u2 + u;
    f32 h4 = u3 - u2;
    return h1 * p0 + h2 * p1 + (h3 * m0 + h4 * m1) * dt;
}

void func_001c53c8(f32 t) {
    Vec q0;
    Vec q1;
    Vec r;
    Elem *e, *n;
    s32 i, k;
    f32 c0, c1, dt, u, u2, u3;
    f32 x;
    if (t < (f32)D_0037A380.first->c) return;
    if ((f32)D_0037A380.last->c < t) return;
    e = D_0037A380.first;
    for (i = 0; i < D_0037A380.n; i++) {
        x = (f32)e->c;
        if (t == x) {
            __builtin_memcpy(&D_0037A380.q10, &e->m[5], 16);
            __builtin_memcpy(&D_0037A380.q20, &e->m[6], 16);
            __builtin_memcpy(&D_0037A380.q30, &e->m[7], 16);
            __builtin_memcpy(&D_0037A380.q40, &e->m[10], 16);
            D_0037A380.x60 = e->f[2];
            D_0037A380.xE0F4 = e->f[5];
            func_001c5168();
            return;
        }
        n = e->next;
        c1 = (f32)n->c;
        if (t < c1) {
            if (((s8 *)&e->b)[1] == 2) {
                c0 = x;
                dt = c1 - c0;
                u = (t - c0) / dt;
                u2 = u * u;
                u3 = u * u2;
                for (k = 0; k < 3; k++) {
                    D_0037A380.q10[k] = herm(u, u2, u3, dt, e->m[5][k], n->m[5][k], e->m[4][k], n->m[3][k]);
                    D_0037A380.q40[k] = herm(u, u2, u3, dt, e->m[10][k], n->m[10][k], e->m[9][k], n->m[8][k]);
                }
                D_0037A380.x60 = herm(u, u2, u3, dt, e->f[2], n->f[2], e->f[1], n->f[0]);
                D_0037A380.xE0F4 = herm(u, u2, u3, dt, e->f[5], n->f[5], e->f[4], n->f[3]);
                __builtin_memcpy(&D_0037A380.q20, &e->m[6], 16); __builtin_memcpy(&D_0037A380.q30, &e->m[7], 16); func_001c5168(); return;
            }
            switch (((s8 *)&e->b)[3]) {
            case 0:
            case 1:
                c0 = x;
                dt = c1 - c0;
                u = (t - c0) / dt;
                u2 = u * u;
                u3 = u * u2;
                func_001e9fe8(&r, &e->m[10]);
                func_001e9f18(&q0, &e->m[5], &r, e->f[2]);
                func_001e9fe8(&r, &e->next->m[10]);
                func_001e9f18(&q1, &e->next->m[5], &r, e->next->f[2]);
                k = 0; { Elem *m = e->next;
                for (; k < 3; k++) {
                    D_0037A380.q10[k] = herm(u, u2, u3, dt, e->m[5][k], m->m[5][k], e->m[4][k], m->m[3][k]);
                    q0[k] = herm(u, u2, u3, dt, q0[k], q1[k], e->m[1][k], m->m[0][k]);
                }
                D_0037A380.q40[2] = herm(u, u2, u3, dt, e->m[10][2], m->m[10][2], e->m[9][2], m->m[8][2]); }
                D_0037A380.x60 = func_001e9e58(&q0, &D_0037A380.q10);
                func_001e9d00(&D_0037A380.q40, &D_0037A380.q10, &q0, D_0037A380.q40[2]);
                D_0037A380.xE0F4 = herm(u, u2, u3, dt, e->f[5], e->next->f[5], e->f[4], e->next->f[3]);
                __builtin_memcpy(&D_0037A380.q20, &e->m[6], 16);
                __builtin_memcpy(&D_0037A380.q30, &e->m[7], 16);
                func_001c5168();
                return;
            case 2:
                c0 = x;
                dt = c1 - c0;
                u = (t - c0) / dt;
                u2 = u * u;
                u3 = u * u2;
                func_001e9fe8(&r, &e->m[10]);
                func_001e9f18(&q0, &e->m[5], &r, e->f[2]);
                func_001e9fe8(&r, &e->next->m[10]);
                func_001e9f18(&q1, &e->next->m[5], &r, e->next->f[2]);
                k = 0; { Elem *m = e->next;
                for (; k < 3; k++) {
                    q0[k] = herm(u, u2, u3, dt, q0[k], q1[k], e->m[1][k], m->m[0][k]);
                    D_0037A380.q40[k] = herm(u, u2, u3, dt, e->m[10][k], m->m[10][k], e->m[9][k], m->m[8][k]);
                }
                D_0037A380.x60 = herm(u, u2, u3, dt, e->f[2], m->f[2], e->f[1], m->f[0]);
                D_0037A380.xE0F4 = herm(u, u2, u3, dt, e->f[5], m->f[5], e->f[4], m->f[3]); }
                __builtin_memcpy(&D_0037A380.q20, &e->m[6], 16);
                __builtin_memcpy(&D_0037A380.q30, &e->m[7], 16);
                func_001e9fe8(&r, &D_0037A380.q40);
                func_001e9f18(&D_0037A380.q10, &q0, &r, -D_0037A380.x60);
                func_001c5168();
                return;
            }
        }
        e = e->next;
    }
}

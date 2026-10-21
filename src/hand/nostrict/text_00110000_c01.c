#include "common.h"
#include "data/bss_004F.h"

typedef struct {
    u32 b0 : 1; u32 b1 : 1; u32 b2 : 1; u32 b3 : 1; u32 b4 : 1; u32 b5 : 1;
    u32 b6 : 1; u32 b7 : 1; u32 b8 : 1; u32 b9 : 1;
    u32 b10 : 3;
    u32 pad13 : 6;
    u32 b19 : 3;
    u32 b22 : 1;
    u32 b23 : 1; u32 b24 : 1; u32 b25 : 1; u32 b26 : 1; u32 b27 : 1; u32 b28 : 1; u32 b29 : 1;
} C01Flg27C8;
typedef struct {
    u8 pad[0x170];
    u64 lo : 32;
    u64 b32 : 1;
    u64 b33 : 3;
    u64 b36 : 1;
    u64 b37 : 1;
    u64 b38 : 1;
} C01Sub148;
typedef struct { u8 pad[0x18]; u8 n; u8 id[1]; } C01Cnt;
typedef struct { u8 pad[0x10]; f32 x10; u8 pad14[0xc8 - 0x14]; C01Cnt *xc8; } C01Sub6C;
typedef struct { u8 pad[0x4c]; u16 x4c; } C01Sub130;
typedef struct {
    u8 pad[0x6c];
    C01Sub6C *x6c;
    u8 pad70[0x130 - 0x70];
    C01Sub130 *x130;
    u8 pad134[0x148 - 0x134];
    C01Sub148 *x148;
} C01Ply;
typedef struct { u16 a; u16 b; } C01Pr;
typedef struct { u8 pad[0x54]; C01Pr e[1]; } C01Tbl;

#include "data/pieces/D_002E27C8.h"
extern f32 D_00304D54;
extern f32 D_00306844;
extern f32 D_00306848;
extern C01Ply *D_002E26A0[3];
extern s32 D_002C5C54;
extern s32 D_002C5C4C;
extern u32 D_002C5958;
#include "data/pieces/D_00308CDC.h"
s32 func_0013c968(s32, s32);

void func_001252f8(void) {
    C01Ply *p;
    s32 i;
    s32 j;
    s32 id;
    s32 c;

    *(u32 *)((C01Flg27C8 *)&D_002E27C8) = 0;
    D_00306844 = D_00306848 = 1.0f;
    D_00304D54 = 1.0f;
    for (i = 0; i < 3; i++) {
        p = D_002E26A0[i];
        if (!p) continue;
        id = p->x130->x4c;
        p->x148->b32 = (u32)func_0013c968(23, id);

        p->x148->b33 = func_0013c968(24, id);
        p->x148->b36 = (u32)func_0013c968(25, id);
        p->x148->b37 = (u32)func_0013c968(26, id);

        (*(C01Flg27C8 *)&D_002E27C8).b10 += func_0013c968(16, id);
        D_00306844 += func_0013c968(27, id) * 0.5f;
        D_00306848 += func_0013c968(28, id) * 0.5f;
        p->x6c->x10 = D_002C5C54 ? (*(C01Tbl **)&D_00308CDC)->e[id].b : (*(C01Tbl **)&D_00308CDC)->e[id].a;
        p->x148->b38 = func_0013c968(62, id);
        for (j = 0; j < p->x6c->xc8->n; j++) {
            c = p->x6c->xc8->id[j];
            switch (c) { case 56: case 57: case 58: D_00304D54 += 0.2f; break; case 59: case 60: D_00304D54 += 0.3f; break; }

        }
    }
    if (D_002C5C54) return;
    if (D_002C5958 >> 22 & 1) return;
    (*(C01Flg27C8 *)&D_002E27C8).b19 = func_0013c968(60, 0);
    if (func_0013c968(2, 11)) (*(C01Flg27C8 *)&D_002E27C8).b6 = 1;
    if (D_002C5C4C) return;
    if (func_0013c968(17, 0)) (*(C01Flg27C8 *)&D_002E27C8).b0 = 1;
    if (func_0013c968(18, 0)) (*(C01Flg27C8 *)&D_002E27C8).b1 = 1;
    if (func_0013c968(19, 0)) (*(C01Flg27C8 *)&D_002E27C8).b2 = 1;
    if (func_0013c968(20, 0)) (*(C01Flg27C8 *)&D_002E27C8).b3 = 1;
    if (func_0013c968(21, 0)) (*(C01Flg27C8 *)&D_002E27C8).b4 = 1;
    if (func_0013c968(22, 0)) (*(C01Flg27C8 *)&D_002E27C8).b5 = 1;
    if (func_0013c968(1, 11)) {
        (*(C01Flg27C8 *)&D_002E27C8).b9 = 1;
        for (i = 0; i < 3; i++) {
            p = D_002E26A0[i];
            if (p) p->x6c->x10 = (*(C01Tbl **)&D_00308CDC)->e[p->x130->x4c].b;
        }
    }
    if (func_0013c968(3, 11)) (*(C01Flg27C8 *)&D_002E27C8).b7 = 1;
    if (func_0013c968(4, 11)) (*(C01Flg27C8 *)&D_002E27C8).b8 = 1;
    (*(C01Flg27C8 *)&D_002E27C8).b23 = func_0013c968(53, 0);
    (*(C01Flg27C8 *)&D_002E27C8).b24 = func_0013c968(54, 0);
    (*(C01Flg27C8 *)&D_002E27C8).b25 = func_0013c968(55, 0);
    (*(C01Flg27C8 *)&D_002E27C8).b26 = func_0013c968(56, 0);
    (*(C01Flg27C8 *)&D_002E27C8).b27 = func_0013c968(57, 0);
    (*(C01Flg27C8 *)&D_002E27C8).b28 = func_0013c968(58, 0);
    (*(C01Flg27C8 *)&D_002E27C8).b29 = func_0013c968(59, 0);
}

typedef f32 C01Mat[4][4];
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

#include "data/pieces/D_002BD250.h"
#include "data/pieces/D_002BBFA0.h"
#include "data/pieces/D_002C58D0.h"
extern s32 D_002E27E0[];
extern u8 D_002E2800[];
extern C01E150 D_004F7820[]; /* src/data/bss_004F.c: A6 D_004F7820[3] */
extern C01E220 D_004F7C10[]; /* src/data/bss_004F.c: B6 D_004F7C10[3] */
extern s32 D_004F82C0;
extern s32 D_004F82C4;
void func_001274c8(void);

void func_00121620(C01Mat, f32 *, f32, f32, f32, f32);
void sceVu0MulMatrix(C01Mat, C01Mat, C01Mat);
void sceVu0CopyMatrix(C01Mat, C01Mat);
void func_00267e90(f32 *, f32 *, f32);
s32 func_0024edf0(void *, f32 (*)[4]);
void func_00114f18(C01Box *, s32);
void func_002675a8(f32 *, f32 *);
void func_002673b8(f32 *, f32 *);
void func_00267560(f32 *, f32 *, f32);
void func_00267530(f32 *, f32 *, f32 *);
void func_00267930(C01Mat, f32 *, f32 *, void *);
C01Task *func_0015ed80(s32, void (*)(void));
void func_00127b98(C01Obj4 *, C01Mat, f32);
void func_00127568(void *, s32, C01Mat, f32 *, s32, f32);

#define C01MAX(a, b) ((a) < (b) ? (b) : (a))

void func_00127c20(C01Obj4 *o, f32 *pos, f32 scale) {
    void *tex = ((u8 *)&D_002BD250);
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
    sceVu0MulMatrix(m, m, o->xd0);
    sp = o->x40;
    row = m[0];
    for (i = 0; i < 3; i++) {
        func_00267e90(row, row, *sp++);
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
    func_002675a8(dir, pos);
    func_002673b8(dir, dir);
    sz = C01MAX(C01MAX(o->x40[2], (o->x40[0] > o->x40[1] ? o->x40[0] : o->x40[1])), 1.0f);
    sz *= C01MAX(o->x414, o->x410 * 2.0f);
    t = dist / 300.0f;
    sz /= D_002E27E0[(s32)(o->x370 >> 40) & 3];
    sz *= t * 8.0f + 1.0f;
    func_00267560(dir, dir, sz * 32768.0f);
    func_00267530(e, &o->x50, dir);
    e[1] -= o->x414 * 0.5f;
    func_00267930(m4, e, dir, D_002E2800);
    func_00121620(m, pos, pos[0], pos[1], pos[2], pos[0] * o->x50 + pos[1] * (o->x54 - o->x414 * 0.5f) + pos[2] * o->x58);
    sceVu0CopyMatrix(m3, (*(C01Mat *)&D_002C58D0));
    m3[3][0] = -o->x50;
    m3[3][1] = o->x414 * 0.5f - o->x54;
    m3[3][2] = -o->x58;
    sceVu0MulMatrix(m, m3, m);
    sceVu0CopyMatrix(m2, m4);
    m2[0][3] = m2[1][3] = m2[2][3] = m2[3][0] = m2[3][1] = m2[3][2] = 0.0f;
    m2[3][3] = 1.0f;
    sceVu0MulMatrix(m, m2, m);
    task = func_0015ed80(D_004F82C4 + D_004F82C0++, func_001274c8);
    task->x10 = &D_004F7820[(s32)(o->x370 >> 40) & 3];
    func_00127b98(o, m4, (s32)((1.0f - t) * 64.0f * scale));
    task = func_0015ed80(D_004F82C4 + D_004F82C0++, func_001274c8);
    task->x10 = &D_004F7C10[(s32)(o->x370 >> 40) & 3];
    func_00127568(tex, box.n, m, pos, o->x2cc, sz * 256.0f);
}

/* needs make: uses rodata (jump table jtbl_0048DA10) */
typedef struct {
    u32 id : 8;
    u32 v : 24;
    s32 x4;
    u8 pad8[0x10 - 0x8];
    f32 x10[4];
} __attribute__((aligned(8))) C01Cmd;
#include "data/types/nostrict_text_00110000_c01.h"
typedef struct {
    u32 lo : 4;
    u32 b4 : 1;
} __attribute__((aligned(8))) C01Bits160;
typedef struct {
    u32 x0;
    u8 pad004[0x3c - 0x4];
    f32 x3c;
    f32 x40[4];
    u8 pad050[0xa0 - 0x50];
    f32 xa0[4];
    u8 pad0b0[0x160 - 0xb0];
    C01Bits160 x160;
    u8 pad168[0x350 - 0x168];
    f32 x350[4];
    u8 pad360[0x370 - 0x360];
    u64 x370;
    u8 pad378[0x3c0 - 0x378];
    f32 x3c0[3];
    f32 x3cc;
    s32 x3d0;
    u8 pad3d4[0x440 - 0x3d4];
    u64 x440;
} C01Act3;
typedef struct {
    u8 pad[0x30];
    s8 x30[4];
    s8 x34[4];
    u8 pad38[0x40 - 0x38];
    f32 x40[4];
} C01Ev;
typedef struct { u8 pad[4]; f32 x4; } C01Snd;

extern C01CmdInfo D_0030433C[];

C01Cmd *func_001c45e8(void);
void func_001c4788(C01Cmd *);
C01Act3 *func_00123488(s32);
void func_001336d8(void);
void func_00133708(void);
void func_002675a8(f32 *, f32 *);
void func_00123a88(s32, f32 *);
void func_001339c0(C01Act3 *);
f32 atan2f(f32, f32);
f32 func_00120c88(f32);
void func_00133a38(C01Cmd *, f32, f32);
C01Ev *func_00133868(C01Act3 *, C01Cmd *);
C01Snd *func_00130340(C01Act3 *, s32, f32);
void func_00135800(C01Act3 *, f32, f32);
void func_00171f58(C01Act3 *);
void func_00153d88(C01Act3 *);
void func_0014cce0(C01Act3 *, f32);
void func_00133978(C01Act3 *, s32);
void func_00133a00(C01Act3 *);
void func_00135df0(C01Act3 *, f32 *);
void func_001358b8(C01Act3 *, s32);
void func_00124060(C01Act3 *, f32 *);
void func_00142388(f32 *, f32 *);
void func_001223b8(void);
void func_0014f658(C01Act3 *, s32);

void func_00133a88(void) {
    C01Cmd *c;
    C01Act3 *a;
    C01Ev *e;
    C01Snd *s;
    f32 v[4];
    f32 f;
    s32 i;

    while ((c = func_001c45e8()) != 0) {
        a = func_00123488(c->x4);
        if (D_0030433C[c->id].x0 && !a) {
            func_001c4788(c);
            continue;
        }
        switch (c->id) {
        case 0:
            func_001336d8();
            break;
        case 1:
            func_00133708();
            break;
        case 3:
            func_002675a8(v, c->x10);
            v[3] = a->x3c;
            func_00123a88(c->x4, v);
            break;
        case 4:
            func_001339c0(a);
            func_00133a38(c, func_00120c88(atan2f(c->x10[0], c->x10[2]) - a->x3c), (u32)c->v);
            func_00133868(a, c);
            c = 0;
            break;
        case 5:
            a->x0 &= ~4;
            func_00130340(a, c->v, 0.0f);
            break;
        case 6:
            a->x0 |= 1;
            func_00135800(a, 1.0f, 0.0f);
            break;
        case 7:
            a->x0 &= ~1;
            break;
        case 8:
            a->x0 |= 2;
            break;
        case 9:
            a->x0 &= ~2;
            break;
        case 10:
            a->x0 &= ~0x20;
            break;
        case 11:
            a->x0 |= 0x20;
            break;
        case 13:
            a->x440 &= ~(1ULL << 32);
            break;
        case 14:
            a->x440 |= 1ULL << 32;
            a->x0 &= ~4;
            if ((C01Act3 *)D_002E26A0[1] == a || (C01Act3 *)D_002E26A0[2] == a) {
                func_00171f58(a);
                func_00153d88(a);
            }
            break;
        case 15:
            a->x440 &= ~(1ULL << 33);
            break;
        case 16:
            a->x440 |= 1ULL << 33;
            break;
        case 12:
            func_0014cce0(a, fabsf(c->x10[1]));
            func_002675a8(a->x3c0, c->x10);
            a->x3c0[1] = a->x3cc = 0.0f;
            if (!((a->x440 >> 33) & 1)) {
                a->x3d0 = 0;
                func_00130340(a, 0x10004, 0.0f);
            }
            a->x0 &= ~0x400;
            break;
        case 2:
            func_00133978(a, 2);
            c->x10[3] = c->x10[3] / 180.0f * 3.1415928f;
            func_00133868(a, c);
            c = 0;
            break;
        case 17:
            a->x0 &= ~4;
            func_00130340(a, c->v, c->x10[0]);
            break;
        case 18:
            func_00133a00(a);
            break;
        case 19:
            a->x0 &= ~4;
            s = func_00130340(a, c->v, c->x10[0]);
            s->x4 = c->x10[1];
            break;
        case 20:
            a->x160.b4 ^= 1;
            break;
        case 21:
            func_001339c0(a);
            f = func_00120c88(atan2f(c->x10[0], c->x10[2]) - a->x3c);
            if (f > 0.0f) f -= 6.2831855f;
            func_00133a38(c, f, (u32)c->v);
            func_00133868(a, c);
            c = 0;
            break;
        case 22:
            func_001339c0(a);
            f = func_00120c88(atan2f(c->x10[0], c->x10[2]) - a->x3c);
            if (f < 0.0f) f += 6.2831855f;
            func_00133a38(c, f, (u32)c->v);
            func_00133868(a, c);
            c = 0;
            break;
        case 23:
            func_00133978(a, 23);
            func_00133978(a, 44);
            e = func_00133868(a, c);
            func_00135df0(a, v);
            for (i = 0; i < 4; i++) {
                e->x30[i] = v[i];
                e->x34[i] = c->x10[i] * 128.0f;
            }
            a->x370 |= 1ULL << 52;
            c = 0;
            break;
        case 24:
            a->x370 &= ~(1ULL << 52);
            break;
        case 27:
            a->x0 &= ~0x10;
            break;
        case 28:
            a->x0 |= 0x10;
            break;
        case 29:
            func_001358b8(a, (u32)c->v);
            if (c->x10[0] > 0.0f) {
                func_00133868(a, c);
                c = 0;
            }
            break;
        case 30:
            func_00133978(a, 30);
            e = func_00133868(a, c);
            c = 0;
            func_002675a8(e->x40, a->x40);
            break;
        case 31:
            func_00133868(a, c);
            c = 0;
            break;
        case 32:
            func_002675a8(v, c->x10);
            v[3] = a->x3c;
            func_00124060(a, v);
            break;
        case 33:
            a->x0 &= ~0x200;
            break;
        case 34:
            a->x0 |= 0x200;
            break;
        case 35:
            a->x0 &= ~0x1000000;
            break;
        case 36:
            a->x0 |= 0x1000000;
            break;
        case 37:
            a->x0 &= ~0x200000;
            break;
        case 38:
            a->x0 |= 0x200000;
            break;
        case 39:
            func_00142388(c->x10, a->x350);
            break;
        case 40:
            func_001223b8();
            break;
        case 41:
            func_0014f658(a, (u32)c->v);
            break;
        case 42:
            a->x0 &= ~0x40;
            break;
        case 43:
            a->x0 |= 0x40;
            break;
        case 44:
            func_00133978(a, 23);
            func_00133978(a, 44);
            e = func_00133868(a, c);
            for (i = 0; i < 4; i++) {
                e->x30[i] = a->xa0[i] * 128.0f;
                e->x34[i] = c->x10[i] * 128.0f;
            }
            c = 0;
            break;
        }
        if (c) func_001c4788(c);
    }
}
#include "data/data_002C.h"
#include "data/data_002E.h"
#include "data/data_0030.h"
#include "data/pieces/D_002C5958.h"
#include "data/pieces/D_0030433C.h"

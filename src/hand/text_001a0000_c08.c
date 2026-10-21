#include "common.h"
#include "data/bss_0062.h"

#include "data/types/text_001a0000_c08.h"
extern s32 D_00625748;
extern IdCnt D_00625750[];
void func_001b9e40(s32, s32);

void func_001bdb58(void) {
    u32 a[16];
    s32 b[16];
    s32 i, j;

    for (i = 0; i < 16; i++) {
        a[i] = 0;
        b[i] = 0;
    }
    for (i = 0; i < D_00625748; i++) {
        a[D_00625750[i].id] = D_00625750[i].n;
        switch (D_00625750[i].n) {
        case 0x400: b[10] = 1; break;
        case 0x1000: b[12] = 1; break;
        case 0x2000: b[13] = 1; break;
        case 0x4000: b[14] = 1; break;
        case 0x8000: b[15] = 1; break;
        }
    }
    a[4] = a[3];
    a[7] = a[6];
    a[5] = a[3];
    a[8] = a[6];
    j = 0;
    if (a[j] == 0) {
        if (!b[14]) { a[j] = 0x4000; b[14] = 1; }
        else if (!b[13]) { a[j] = 0x2000; b[13] = 1; }
        else if (!b[15]) { a[j] = 0x8000; b[15] = 1; }
        else if (!b[12]) { a[j] = 0x1000; b[12] = 1; }
        else if (!b[10]) { a[j] = 0x400; b[10] = 1; }
    }
    j = 1;
    if (a[j] == 0) {
        if (!b[15]) { a[j] = 0x8000; b[15] = 1; }
        else if (!b[13]) { a[j] = 0x2000; b[13] = 1; }
        else if (!b[14]) { a[j] = 0x4000; b[14] = 1; }
        else if (!b[12]) { a[j] = 0x1000; b[12] = 1; }
        else if (!b[10]) { a[j] = 0x400; b[10] = 1; }
    }
    j = 2;
    if (a[j] == 0) {
        if (!b[12]) { a[j] = 0x1000; b[12] = 1; }
        else if (!b[15]) { a[j] = 0x8000; b[15] = 1; }
        else if (!b[13]) { a[j] = 0x2000; b[13] = 1; }
        else if (!b[14]) { a[j] = 0x4000; b[14] = 1; }
        else if (!b[10]) { a[j] = 0x400; b[10] = 1; }
    }
    j = 3;
    if (a[j] == 0) {
        if (!b[13]) { a[j] = 0x2000; b[13] = 1; }
        else if (!b[15]) { a[j] = 0x8000; b[15] = 1; }
        else if (!b[14]) { a[j] = 0x4000; b[14] = 1; }
        else if (!b[12]) { a[j] = 0x1000; b[12] = 1; }
        else if (!b[10]) { a[j] = 0x400; b[10] = 1; }
    }
    a[j+1] = a[j]; a[j+2] = a[j];
    j = 6;
    if (a[j] == 0) {
        if (!b[13]) { a[j] = 0x2000; b[13] = 1; }
        else if (!b[15]) { a[j] = 0x8000; b[15] = 1; }
        else if (!b[14]) { a[j] = 0x4000; b[14] = 1; }
        else if (!b[12]) { a[j] = 0x1000; b[12] = 1; }
        else if (!b[10]) { a[j] = 0x400; b[10] = 1; }
    }
    a[j+1] = a[j]; a[j+2] = a[j];
    func_001b9e40(0, a[0]);
    func_001b9e40(1, a[1]);
    func_001b9e40(2, a[2]);
    func_001b9e40(3, a[3]);
    func_001b9e40(4, a[4]);
    func_001b9e40(5, a[5]);
    func_001b9e40(6, a[6]);
    func_001b9e40(7, a[7]);
    func_001b9e40(8, a[8]);
}


#include "data/types/text_001a0000_c08_p.h"
extern C4 D_0037A130[16];
typedef struct { u16 h0; u16 r0 : 4; u16 r1 : 4; u16 r2 : 4; u16 r3 : 4; } Ori_1bbf88;

void func_001bbf88(Ori_1bbf88 *o, s32 axis, s32 dir) {
    C4 a, b, c, t;
    s32 i;

    a = D_0037A130[o->r0];
    b = D_0037A130[o->r1];
    c = D_0037A130[o->r2];
    switch (axis) {
    case 0:
        switch (dir) {
        case -1:
            t.x = a.x; t.y = -a.z; t.z = a.y; a = t;
            t.x = b.x; t.y = -b.z; t.z = b.y; b = t;
            t.x = c.x; t.y = -c.z; t.z = c.y; c = t;
            break;
        case 1:
            t.x = a.x; t.y = a.z; t.z = -a.y; a = t;
            t.x = b.x; t.y = b.z; t.z = -b.y; b = t;
            t.x = c.x; t.y = c.z; t.z = -c.y; c = t;
            break;
        }
        break;
    case 1:
        switch (dir) {
        case 1:
            t.x = -a.z; t.y = a.y; t.z = a.x; a = t;
            t.x = -b.z; t.y = b.y; t.z = b.x; b = t;
            t.x = -c.z; t.y = c.y; t.z = c.x; c = t;
            break;
        case -1:
            t.x = a.z; t.y = a.y; t.z = -a.x; a = t;
            t.x = b.z; t.y = b.y; t.z = -b.x; b = t;
            t.x = c.z; t.y = c.y; t.z = -c.x; c = t;
            break;
        }
        break;
    case 2:
        switch (dir) {
        case -1:
            t.x = -a.y; t.y = a.x; t.z = a.z; a = t;
            t.x = -b.y; t.y = b.x; t.z = b.z; b = t;
            t.x = -c.y; t.y = c.x; t.z = c.z; c = t;
            break;
        case 1:
            t.x = a.y; t.y = -a.x; t.z = a.z; a = t;
            t.x = b.y; t.y = -b.x; t.z = b.z; b = t;
            t.x = c.y; t.y = -c.x; t.z = c.z; c = t;
            break;
        }
        break;
    }
    for (i = 0; i < 6; i++) {
        if (D_0037A130[i].x == a.x && D_0037A130[i].y == a.y && D_0037A130[i].z == a.z) {
            o->r0 = i;
            break;
        }
    }
    for (i = 0; i < 6; i++) {
        if (D_0037A130[i].x == b.x && D_0037A130[i].y == b.y && D_0037A130[i].z == b.z) {
            o->r1 = i;
            break;
        }
    }
    for (i = 0; i < 6; i++) {
        if (D_0037A130[i].x == c.x && D_0037A130[i].y == c.y && D_0037A130[i].z == c.z) {
            o->r2 = i;
            break;
        }
    }
}


typedef struct {
    u8 type;
    u64 val:24;
    s32 x;
    s32 a8;
    s32 ac;
    f32 v[4];
} Msg;
typedef union {
    u64 x;
    s32 i[2];
    struct { u32 b0:1; u32 b1:1; u32 b2:1; u32 b3:1; u32 b4:4; u32 b8:1; u32 b9:4; u32 b13:1; u32 r14:18; u32 hi; } b;
} VMFl;
typedef struct {
    s32 x0;
    u8 pad4[0x10];
    f32 f14, f18, f1c, f20;
    u8 pad24[0x4c];
    s32 w70;
    u8 pad74[0x108];
    s32 pc;
    u8 pad180[0x174];
    f32 f2f4;
    u8 pad2f8[0x30];
    VMFl fl;
    u8 pad330[0x20];
} VM;
typedef union {
    u64 x;
    struct { u32 lo; u32 h0:6; u32 b38:1; u32 b39:1; u32 b40:1; u32 h9:2; u32 b43:1; u32 h12:9; u32 b53:1; u32 h22:10; } b;
} F3070;
typedef union {
    u64 x;
    struct { u32 b0:1; u32 b1:1; u32 r2:8; u32 b10:1; u32 b11:1; u32 b12:1; u32 b13:1; u32 r14:18; u32 hi; } b;
} F3078;
typedef struct { s32 a, b, c, d, e, f; } S24;
typedef struct {
    u8 pad0[0x1034];
    s32 A[512];
    s32 B[512];
    s32 C[512];
    s32 D[512];
    s32 x3034;
    s32 x3038;
    s32 x303c;
    s32 x3040;
    u8 pad3044[0x2c];
    F3070 f3070;
    F3078 f3078;
    u8 pad3080[0xc8];
    u32 x3148;
    u8 pad314c[0x20];
    s32 x316c;
    u8 pad3170[0x214];
    S24 e[8];
} Big;
typedef struct { u64 w[14]; } B112;
typedef struct { s32 w0; s32 w4; s32 w8; u8 padc[0x34]; s32 a[8]; s32 b[3]; } S5BB0;
typedef struct { u32 b0:1; u32 b1:1; u32 b2:1; u32 rest:29; } Bits;

extern u8 D_00389C90[];
#define D_00389C90 (*(Big *)&D_00389C90)
extern B112 D_002C5AD0;
extern u8 D_002C5BB0[];
#define D_002C5BB0 (*(S5BB0 *)&D_002C5BB0)
extern VM D_0038D170[], D_0039A580[];
extern s32 D_0039A570, D_003A7980;
extern f32 D_002BBDFC;
extern s32 D_0037A190;
extern Bits D_0037A378;
extern u8 D_002C5958[];
#define D_002C5958 (*(s32 *)&D_002C5958)
extern volatile s32 D_002BBDE0;
extern s32 (*D_0037A198[])(VM *, s32);
s32 func_001c1ce8(s32, s32);
s32 func_001c1cf8(s32, s32);
s32 func_001c1e30(void);
void func_001c2ec8(s32, s32);
Msg *func_001c4730(void);
s32 func_001c4640(Msg *m);
void func_001cebe8(void);
void func_001cff28(void);
void func_001cfff8(void);
void func_001d8f38(void);
void func_001ca800(void);
s32 func_00146878(void);
void func_001dcea8(VM *);
void func_001dcfd0(VM *);

s32 func_001c1f80(void) {
    Msg m;
    B112 tmp = D_002C5AD0;
    Msg list[256];
    s32 n = 0;
    VM *vm;
    s32 *cnt;
    s32 i, j, r, k, op, arg;
    Msg *p;
    VM *v;

    if (D_00389C90.f3070.b.b40) return 4;
    if (D_00389C90.x3038 > 0) {
        if (D_00389C90.x3034 == 0) { vm = D_0038D170; cnt = &D_0039A570; }
        else { vm = D_0039A580; cnt = &D_003A7980; }
        for (i = 0; i < *cnt; i++, vm++) {
            if ((vm->fl.x & 0x14) == 4) {
                vm->f2f4 -= D_002BBDFC;
                if (!(0.0f < vm->f2f4)) vm->fl.x &= ~4;
            }
        }
        return 0;
    }
    D_0037A190 = 0;
    D_00389C90.x316c = 0;
    if (D_0037A378.b2) return 0;
    if (D_00389C90.f3078.b.b12 == 1) return 0;
    if (D_00389C90.f3078.b.b13 == 1) return 0;
    k = func_001c1e30();
    if (k > 0 && D_00389C90.x3034 == 0) {
        func_001c2ec8(D_00389C90.x3040, k);
        return 0;
    }
    D_002C5BB0.w4 &= D_00389C90.x3148;
    D_002C5BB0.w8 &= D_00389C90.x3148;
    if (~(D_00389C90.x3148 >> 23) & 1) {
        for (i = 0; i < 3; i++) {
            D_002C5BB0.a[i] = 0;
            D_002C5BB0.b[i] = 0;
        }
    }
    if (D_00389C90.f3078.b.b11) D_002C5958 &= ~0x1000;
    for (i = 0; i < 8; i++) {
        D_00389C90.e[i].a = 0;
        D_00389C90.e[i].b = -1;
        D_00389C90.e[i].c = -1;
        D_00389C90.e[i].e = 1;
        D_00389C90.e[i].d = 0;
        D_00389C90.e[i].f = -1;
    }
    if (D_00389C90.x3034 == 0) { vm = D_0038D170; cnt = &D_0039A570; }
    else { vm = D_0039A580; cnt = &D_003A7980; }
    p = func_001c4730();
    while (p) {
        list[n++] = *p;
        p = func_001c4730();
    }
    if (D_00389C90.f3070.b.b43 == 1) func_001cebe8();
    if (D_00389C90.f3070.b.b38 == 1) func_001cff28();
    if (D_00389C90.f3070.b.b39 == 1) func_001cfff8();
    if (D_00389C90.f3078.b.b1 == 1) func_001d8f38();
    if (D_00389C90.f3078.b.b10) func_001ca800();
    if (D_00389C90.f3070.b.b53) return 0;
    for (i = 0; i < *cnt; i++, vm++) {
        if (vm->fl.b.b3) {
            if (i != 0) continue;
            if (D_00389C90.x3034 != 0) {
                v = D_0038D170;
                D_00389C90.x3034 = 0;
                for (j = 1, v++; j < D_0039A570; j++, v++) {
                    if ((u32)v->fl.i[0] % 2 == 1) {
                        m.type = 2;
                        m.val = (u32)v->f20;
                        m.x = v->x0;
                        m.v[0] = v->f14;
                        m.v[1] = v->f18;
                        m.v[2] = v->f1c;
                        m.v[3] = 10.0f;
                        func_001c4640(&m);
                    }
                }
                for (i = 0; i < 512; i++) {
                    D_00389C90.A[i] = D_00389C90.C[i];
                    D_00389C90.B[i] = D_00389C90.D[i];
                }
                return 0;
            }
            if (D_002BBDE0 == 3) {
                D_002C5958 &= ~8;
                D_002C5958 &= ~4;
            }
            return 4;
        }
        if (vm->fl.b.b8) continue;
        if (vm->fl.b.b13) {
            if (!func_00146878()) continue;
            vm->fl.x &= ~0x2000;
        }
        func_001dcea8(vm);
        func_001dcfd0(vm);
        if ((vm->fl.x & 0x14) == 4) {
            vm->f2f4 -= D_002BBDFC;
            if (0.0f < vm->f2f4) continue;
            vm->fl.x &= ~4;
        }
        for (j = 0; j < n; j++) {
            p = &list[j];
            switch (p->type) {
            case 2:
                if (p->x == vm->x0) {
                    vm->fl.x &= ~1;
                    if (D_0037A378.b0) {
                        m.type = 3;
                        m.val = 0;
                        m.x = vm->x0;
                        m.v[0] = vm->f14;
                        m.v[1] = vm->f18;
                        m.v[2] = vm->f1c;
                        m.v[3] = 1.0f;
                        func_001c4640(&m);
                    }
                }
                break;
            case 4:
                if (p->x == vm->x0) vm->fl.x &= ~2;
                break;
            case 21:
                if (p->x == vm->x0) vm->fl.x &= ~2;
                break;
            case 22:
                if (p->x == vm->x0) vm->fl.x &= ~2;
                break;
            }
        }
        for (;;) {
            op = func_001c1ce8(vm->w70, vm->pc);
            arg = func_001c1cf8(vm->w70, vm->pc);
            r = D_0037A198[op](vm, arg);
            if (r & 2) vm->pc++;
            if (r & 4) break;
            if (r & 8) {
                if (D_00389C90.f3070.b.b40) return 4;
                i = *cnt;
                break;
            }
        }
    }
    return 0;
}
#undef D_00389C90
#undef D_002C5BB0
#undef D_002C5958
#include "data/data_0037.h"
#include "data/data_0039.h"
#include "data/data_003A.h"
#include "data/pieces/D_002BBDFC.h"

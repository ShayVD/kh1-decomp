#include "common.h"
#include "vm/script_vm.h"
#include "vm/vm_find.h"
#include "data/bss_0062.h"
#include "data/bss_0063.h"

/* Script VM handlers: obj at +4, top index at +0x180, value stack at +0x184.
 * The stack is indexed off &vm->u.s (vm+4) with a local copy of sp. */
typedef struct {
    void *obj;
    u8 pad4[0x17c];
    s32 stk[105];
} Sub;
typedef struct {
    s32 x0;
    union {
        Sub s;
        struct { void *obj; u8 pad[0x178]; s32 sp; } h;
    } u;
} VM;

/* Menu window (0xb0 bytes); D_0062F6E0/D_0062F790/D_0062F840 and
 * D_00630300/D_006303B0/D_00630460 are runs of these. */
#include "data/types/text_001e0000_h45.h"

typedef struct { s32 a; s32 b; void (*fn)(); s32 d; } Cb20;
#include "data/types/text_001e0000_h45_p.h"
typedef struct Actor { s32 x0; u8 pad4[0x5c]; f32 f60; f32 f64; } Obj26;
typedef struct { u8 pad0[0x3070]; u64 f3070; u64 f3078; u8 pad3080[0x450]; s32 f34d0; } Big20;
typedef struct { f32 x, y, z; } Vec3;
typedef struct { s32 x0; s32 id; } Ent88;
typedef struct { u8 pad[0xb10]; u32 tbl[4][5]; } Rec98s;
typedef struct { s32 x0; Rec98s s; } Rec98;
typedef struct { u8 pad[0x664]; s32 a, b, c, d; } Big498;

/* Message passed to func_001c4640. */

extern Big20 D_00389C90;
extern Cb20 D_006305C0;
extern E212 D_003DB078[];
extern E212 D_003DB718[];
#include "data/pieces/D_002E26A0.h"
extern Win D_00630300;
extern Win D_006303B0; /* src/data/bss_0063.c: u8 D_006303B0[0xb0] */
extern Win D_00630460;
extern Win D_00631570;
extern char D_003DD290[][6];
extern char D_004908C8[];
extern Big498 D_003DC498;
extern s32 D_002BCDE4;
extern s32 D_002C1364;
#include "data/pieces/D_0037A378.h"
#include "data/pieces/D_003DABD4.h"
extern s32 D_003DD258;
extern s32 D_003DD25C;
extern s32 D_003DD28C;
extern s32 D_003F7A68;
extern s32 D_003F7EC8;
extern s32 D_006305CC;
extern s32 D_006314CC;
extern s32 D_006314D0;
extern s32 D_006314D4;
extern s8 D_006314C8;
#include "data/pieces/D_003DBA68.h"
#include "data/pieces/D_003DC390.h"
#include "data/pieces/D_003DCD70.h"
extern u8 D_003DCF30[];
extern u8 D_003DD320[];
extern u8 D_00630380[];
extern u8 D_006304E0[];
extern u8 D_00630510[];
extern u8 D_006305D0[][10];
extern u8 D_006307C8[]; /* src/data/bss_0063.c: char D_006307C8[0x800] */
extern u8 D_00F20000[];
f32 D_006314E0[0x8][4] ALIGNED(32);

int sprintf(char *, const char *, ...);
void func_0010bdd0(void *, void (*)());
void func_0010e3f0(void *);
void func_0010ef70(void *, void *, void *);
void func_0010f558(void *, void *, s32);
void func_0011c7a8(s32, s32, s32, s32, s32, s32);
void func_0011c7c0(s32, s32, s32);
void func_0011c7d8(s32);
void func_0011d2a0(s32, s32, f32 *, s32);
s32 func_0011e340(void *);
void func_0011e9d8();
void func_0011ea40(s32, void *);
void func_0011eae0(s32, void *);
s32 func_0011ef10(s32, void (*)());
void func_00120748(void *, s32, void (*)(), s32);
Ent88 *func_001230a0(Ent88 *);
s32 func_00123618(s32);
void func_001caf58(void);
s32 func_001e4a68(void);
void func_001e5198();
void func_001e5788(s32);
s32 func_001e6450(void);
void func_001e6500();
void func_001e65d0();
void func_001e6b70();
void func_001e72a0();
void func_001e81c8();
void func_001e84f0();
void func_001e8628();
void func_001e8ed8();
void func_001e92e0();
void func_001e9670(void);
Rec98 *func_00232cc0(s32);

/* func_001e31b8, func_001e3600, func_001e3770, func_001e38b0, func_001e3b40, func_001e3c70, func_001e3dd0, func_001e3f20, func_001e4790, func_001e4868 are in src/shop/shop.c. */










void func_001e4990(void) {
    D_003F7EC8 = 1;
    func_0010e3f0(D_00630380);
    func_0010ef70(D_00630380 - 0x80, D_006307C8, func_001e5198);
    if (D_003DD25C == 3) {
        Cb20 *p = &D_006305C0;
        p->a = D_003DD25C;
        if (D_006305CC == 4 || D_006305CC == 0) p->b = 13;
        else p->b = 14;
    } else {
        D_006305C0.a = 4;
        D_006305C0.b = 13;
    }
    D_006305C0.fn = (void (*)())func_001e5788;
    func_0010f558(&D_006305C0, &D_00630300, D_006314C8);
}

void func_001e4b08(void) {
    s32 i;
    for (i = 0; i < 50; i++) {
        if (i < 9) {
            D_006305D0[i][0] = 15;
            D_006305D0[i][1] = 2;
            D_006305D0[i][2] = 1;
            D_006305D0[i][3] = i + 34;
            D_006305D0[i][4] = 1;
            D_006305D0[i][5] = 15;
            D_006305D0[i][6] = 3;
            D_006305D0[i][7] = 0;
        } else {
            D_006305D0[i][0] = 15;
            D_006305D0[i][1] = 2;
            D_006305D0[i][2] = (i + 1) / 10 + 33;
            D_006305D0[i][3] = (i + 1) % 10 + 33;
            D_006305D0[i][4] = 1;
            D_006305D0[i][5] = 15;
            D_006305D0[i][6] = 3;
            D_006305D0[i][7] = 0;
        }
    }
}

void func_001e4c20(void) {
    D_00630300.f30 = -110.0f;
    D_00630300.f34 = -5.0f;
    D_00630300.f40 = 10.0f;
    D_00630300.f44 = 14.0f;
    D_00630300.h4 = 6;
    D_00630300.hc = 1;
    D_00630300.he = 1;
    D_00630300.h6 = 0;
    D_00630300.h8 = 0;
    D_00630300.b90 = 0;
    D_00630300.f1c = 45.0f;
    D_00630300.x0 = -1;
    D_00630300.f94 = 1.0f;
    D_006303B0.f30 = 120.0f;
    D_006303B0.f34 = 100.0f;
    D_006303B0.f40 = 9.0f;
    D_006303B0.f44 = 5.0f;
    D_006303B0.h4 = 6;
    D_006303B0.hc = 1;
    D_006303B0.he = 1;
    D_006303B0.h6 = 0;
    D_006303B0.h8 = 0;
    D_006303B0.b90 = 0;
    D_006303B0.f1c = 45.0f;
    D_006303B0.x0 = -1;
    D_006303B0.f94 = 1.0f;
    D_003DC498.a = 28512;
    D_003DC498.b = 30176;
    D_003DC498.c = 0x8180;
    D_003DC498.d = 0x8c60;
}

void func_001e5810(void) {
    func_0010ef70(&D_00630300, D_006307C8, func_001e5198);
    func_0011ef10(0xc350, (void (*)())func_001e4a68);
    if (D_003DD25C == 3) {
        Cb20 *p = &D_006305C0;
        D_006305CC = 0;
        p->a = D_003DD25C;
        p->b = 13;
        p->fn = (void (*)())func_001e5788;
    } else {
        D_006305C0.b = 13;
        D_006305C0.fn = (void (*)())func_001e5788;
        D_006305C0.a = 4;
    }
    func_0010f558(&D_006305C0, &D_00630300, D_006305C0.a);
}

void func_001e6ba8(void) {
    func_0011ef10(0xc350, func_001e6500);
    D_003DD28C = 1;
    func_0010ef70(&D_00630300, D_006307C8, func_001e65d0);
    if (D_003DD25C == 3) {
        Cb20 *p = &D_006305C0;
        D_006305CC = 0;
        p->a = 2;
        p->b = 11;
        p->fn = func_001e6b70;
    } else {
        D_006305C0.b = 10;
        D_006305C0.fn = func_001e6b70;
        D_006305C0.a = 2;
    }
    func_0010f558(&D_006305C0, &D_00630300, D_006305C0.a);
}

void func_001e6d20(void) {
    s32 k = D_003DD258;
    switch (k) {
    case 1:
        func_0010e3f0(D_006304E0);
        func_0010ef70(D_006304E0 - 0x80, D_003DCF30, 0);
        func_0010bdd0(D_00630510, (void (*)())func_001e6450);
        break;
    case 2:
        func_0010e3f0(D_006304E0);
        func_0010ef70(D_006304E0 - 0x80, D_003DCD70, 0);
        { u8 *q = D_00630510; void (*fp)() = func_001e72a0; func_0010bdd0(q, fp); }
        break;
    }
}

void func_001e7800(void) {
    D_00630460.f30 = 0.0f;
    D_00630460.f34 = 0.0f;
    D_00630460.f40 = 7.0f;
    D_00630460.f44 = 1.9f;
    D_00630460.h4 = 0;
    D_00630460.hc = 2;
    D_00630460.he = 2;
    D_00630460.h6 = 0;
    D_00630460.h8 = 13;
    D_00630460.b90 = 0;
    D_00630460.f1c = 135.0f;
    D_00630460.x0 = -1;
    D_00630460.f94 = 1.0f;
    D_00630300.f30 = 120.0f;
    D_00630300.f34 = -30.0f;
    D_00630300.f40 = 7.0f;
    D_00630300.f44 = 11.0f;
    D_00630300.h4 = 6;
    D_00630300.hc = 1;
    D_00630300.he = 3;
    D_00630300.h6 = 0;
    D_00630300.h8 = 0;
    D_00630300.b90 = 0;
    D_00630300.f1c = 45.0f;
    D_00630300.x0 = -1;
    D_00630300.f94 = 1.0f;
}

s32 func_001e7f08(VM *vm) {
    Sub *s = &vm->u.s;
    s32 *p = &D_006314D4;
    s32 i = vm->u.h.sp;
    s32 a = s->stk[i - 2], b = s->stk[i - 1], c = s->stk[i];
    s32 t, n;
    *p = a - 1;
    t = (f32)(b * 0x3000) / 100.0f;
    n = c * 8;
    func_0011c7d8(D_002C1364);
    func_0011c7a8(*p, 0, t, n, 0, 0);
    vm->u.h.sp -= 3;
    return 2;
}

s32 func_001e8238(VM *vm) {
    s32 buf[64];
    Sub *s = &vm->u.s;
    s32 i;
    func_0011eae0(s->stk[vm->u.h.sp], buf);
    func_00120748(buf, ((s32)D_003DABD4), func_001e81c8, 0);
    D_00389C90.f3070 |= 0x100000000000000LL;
    i = vm->u.h.sp;
    D_006314D0 = s->stk[i - 1] - 1;
    vm->u.h.sp = i - 2;
    return 2;
}

s32 func_001e8560(VM *vm) {
    s32 buf[64];
    Sub *s = &vm->u.s;
    s32 i;
    func_0011ea40(s->stk[vm->u.h.sp], buf);
    func_00120748(buf, ((s32)D_003DABD4), func_001e84f0, 0);
    D_00389C90.f3070 |= 0x8000LL << 36;
    i = vm->u.h.sp;
    D_006314CC = s->stk[i - 1] - 1;
    vm->u.h.sp = i - 2;
    return 2;
}

s32 func_001e8800(VM *vm) {
    Sub *s = &vm->u.s;
    s32 i = vm->u.h.sp;
    s32 a = s->stk[i - 1], c = s->stk[i];
    s32 t, n;
    t = (f32)(a * 0x3000) / 100.0f;
    n = c * 8;
    if (!func_0011e340(0)) {
        func_0011e9d8(t, n, func_001e8628, D_00F20000);
        D_00389C90.f3070 |= 0x200000000000000LL;
        vm->u.h.sp -= 2;
        return 2;
    }
    return 4;
}

s32 func_001e88e0(VM *vm) {
    Sub *s = &vm->u.s;
    s32 i = vm->u.h.sp;
    s32 a = s->stk[i - 1], c = s->stk[i];
    s32 t, n;
    t = (f32)(a * 0x3000) / 100.0f;
    n = c * 8;
    if (!func_0011e340(0)) {
        func_0011e9d8(t, n, func_001e8628, D_003DABD4);
        D_00389C90.f3070 |= 0x200000000000000LL;
        vm->u.h.sp -= 2;
        return 2;
    }
    return 4;
}

s32 func_001e8a50(VM *vm) {
    Sub *s = &vm->u.s;
    s32 t;
    if (s->stk[vm->u.h.sp - 1] == 1) t = 1; else t = (f32)(s->stk[vm->u.h.sp - 1] * 0x3000) / 100.0f;
    if (16383 < t) t = 16383; else if (t < 0) t = 0;
    func_0011c7c0(s->stk[vm->u.h.sp - 2] - 1, t, s->stk[vm->u.h.sp] * 8);
    vm->u.h.sp -= 3;
    return 2;
}

s32 func_001e8bd8(VM *vm) {
    Sub *s = &vm->u.s;
    s32 flag;
    s32 i = vm->u.h.sp;
    f32 z;
    s32 a;
    flag = D_0037A378 & 1;
    D_006314E0[s->stk[i - 3]][0] = s->stk[i - 2];
    a = s->stk[i - 4];
    D_006314E0[s->stk[i - 3]][1] = s->stk[i - 1];
    z = s->stk[i];
    D_006314E0[s->stk[i - 3]][2] = z;
    if (!flag) {
        func_0011d2a0(a, s->stk[i - 3], D_006314E0[s->stk[i - 3]], 0);
        i = vm->u.h.sp;
    }
    vm->u.h.sp = i - 5;
    return 2;
}

s32 func_001e8f68(VM *vm) {
    char buf[512];
    if (!(D_0037A378 & 1)) {
        Sub *s = &vm->u.s;
        sprintf(buf, D_004908C8, D_003DD290[s->stk[vm->u.h.sp - 1]], s->stk[vm->u.h.sp]);
        D_00389C90.f3070 |= 0x80000000000000LL;
        func_00120748(buf, ((s32)D_003DABD4), func_001e8ed8, 0);
    }
    vm->u.h.sp -= 2;
    return 2;
}

s32 func_001e9310(VM *vm) {
    D_00631570.f30 = 0.0f;
    D_00631570.f34 = 110.0f;
    D_00631570.f40 = 10.0f;
    D_00631570.f44 = 3.0f;
    D_00631570.h4 = 0;
    D_00631570.hc = 2;
    D_00631570.he = 2;
    D_00631570.h6 = 0;
    D_00631570.h8 = 0;
    D_00631570.b90 = 0;
    D_00631570.f1c = 45.0f;
    D_00631570.x0 = -1;
    D_00631570.f94 = 1.0f;
    func_001e9670();
    func_0010bdd0(&D_00631570, func_001e92e0);
    vm->u.h.sp -= 1;
    return 2;
}

void func_001e9fe8(Vec3 *out, Vec3 *in) {
    out->x = in->x;
    out->y = in->y;
    out->z = in->z;
    while (1) {
        if (out->x > 3.1415928f) out->x -= 6.2831855f;
        else if (out->x < -3.1415928f) out->x += 6.2831855f;
        else break;
    }
    while (1) {
        if (out->y > 3.1415928f) out->y -= 6.2831855f;
        else if (out->y < -3.1415928f) out->y += 6.2831855f;
        else break;
    }
    while (1) {
        if (out->z > 3.1415928f) out->z -= 6.2831855f;
        else if (out->z < -3.1415928f) out->z += 6.2831855f;
        else break;
    }
}

void func_001ea498(s32 a) {
    Obj26 *p = D_002E26A0[0];
    p->f60 = 1.0f;
    p->f64 = 0.0f;
    p->x0 |= 1;
    func_001caf58();
    D_00389C90.f34d0 = a;
    if (!((D_00389C90.f3070 >> 54) & 1)) {
        D_00389C90.f3070 |= 0x10000000000LL;
        func_001c4198((s8 *)D_003DD320, 0);
        {
            s32 *q = &D_0037A378;
            D_00389C90.f3070 &= ~0x800000000000000LL;
            *q |= 2;
        }
    } else {
        func_001c2ec8((s8 *)D_002BCDE4, 99);
    }
}

s32 func_001ea6b8(VmRec *vm) {
    VmMsg m;
    VmRec *e = func_001e98d0(vm->fl.b.b5, vm->stk[vm->sp]);
    if (e) {
        m.type = 13;
        m.val = 0;
        m.v[3] = 1.0f;
        m.v[0] = 0;
        m.v[1] = 0;
        m.v[2] = 0;
        m.x = e->x0;
        func_001c4640(&m);
    }
    vm->sp -= 1;
    return 2;
}

s32 func_001ea760(VmRec *vm) {
    VmMsg m;
    VmRec *e = func_001e98d0(vm->fl.b.b5, vm->stk[vm->sp]);
    if (e) {
        m.type = 14;
        m.val = 0;
        m.v[3] = 1.0f;
        m.v[0] = 0;
        m.v[1] = 0;
        m.v[2] = 0;
        m.x = e->x0;
        func_001c4640(&m);
    }
    vm->sp -= 1;
    return 2;
}

s32 func_001ea908(VmRec *vm) {
    VmMsg m;
    VmRec *e = func_001e98d0(vm->fl.b.b5, vm->stk[vm->sp]);
    if (e) {
        m.type = 35;
        m.val = 0;
        m.x = e->x0;
        func_001c4640(&m);
        m.type = 42;
        m.val = 0;
        m.x = e->x0;
        func_001c4640(&m);
    }
    vm->sp -= 1;
    return 2;
}

s32 func_001ea9c8(VmRec *vm) {
    VmMsg m;
    VmRec *e = func_001e98d0(vm->fl.b.b5, vm->stk[vm->sp]);
    if (e) {
        m.type = 36;
        m.val = 0;
        m.x = e->x0;
        func_001c4640(&m);
        m.type = 43;
        m.val = 0;
        m.x = e->x0;
        func_001c4640(&m);
    }
    vm->sp -= 1;
    return 2;
}

s32 func_001eaa88(void) {
    VmMsg m;
    Ent88 *p = func_001230a0(0);
    while (p) {
        if (func_00123618(p->id) >= 0 && func_00123618(p->id) < 10 && ((u8 *)p)[6] == 3) {
            m.type = 35;
            m.val = 0;
            m.x = p->id;
            func_001c4640(&m);
            m.type = 42;
            m.val = 0;
            m.x = p->id;
            func_001c4640(&m);
        }
        p = func_001230a0(p);
    }
    return 2;
}

s32 func_001eab78(void) {
    VmMsg m;
    Ent88 *p = func_001230a0(0);
    while (p) {
        if (func_00123618(p->id) >= 0 && func_00123618(p->id) < 10 && ((u8 *)p)[6] == 3) {
            m.type = 36;
            m.val = 0;
            m.x = p->id;
            func_001c4640(&m);
            m.type = 43;
            m.val = 0;
            m.x = p->id;
            func_001c4640(&m);
        }
        p = func_001230a0(p);
    }
    return 2;
}

s32 func_001eb698(VM *vm) {
    Sub *s = &vm->u.s;
    s32 i = vm->u.h.sp;
    s32 a = s->stk[i - 2];
    s32 b = s->stk[i - 1];
    u32 c = s->stk[i];
    Rec98 *r = func_00232cc0(1);
    Rec98s *q = &r->s;
    s32 j, k;
    for (j = 0; j < 5; j++) {
        if (q->tbl[a][j] == -1 || (b == 0 && q->tbl[a][j] < c) || (b == 1 && q->tbl[a][j] > c)) {
            for (k = 4; j < k; k--) q->tbl[a][k] = q->tbl[a][k - 1];
            q->tbl[a][j] = c;
            break;
        }
    }
    vm->u.h.sp -= 3;
    return 2;
}
#include "data/bss_0063_typed.h"
#include "data/data_002B.h"
#include "data/data_002C.h"
#include "data/data_003D.h"
#include "data/data_003F.h"
#include "data/data_0049.h"
#include "data/pieces/D_003DD258.h"
#include "data/pieces/D_003DD28C.h"
#include "data/pieces/D_003F7A68.h"
#include "data/pieces/D_003DB078.h"
#include "data/pieces/D_003DB718.h"

#include "common.h"
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
typedef struct {
    u8 pad0[0x14];
    void *owner;
    u8 pad18[0x10];
    s32 arg;
    s32 kind;
} Task;
extern u8 D_0062A630[];
Task *func_0011f090(void *, s32, void *);
void func_001dd5c0();
typedef struct { f32 *v; } Obj760;
Obj760 *func_001760d0(s32);
Obj760 *func_001760f0(s32);
extern s32 D_0029B418;
extern s32 D_0029B41C;
Obj760 *func_001760b0(s32);
typedef struct { f32 x, y, z; } Vec3;
typedef struct { Vec3 *pos; u8 pad4[0x10]; s32 flags; } Ent698;
typedef struct { u8 pad0[4]; s32 id; } Mdl698;
typedef struct {
    u8 pad0[0x10];
    Ent698 *ent;
    Mdl698 *mdl;
    s32 k;
    f32 t;
} Ctx698;
void func_001315c0(s32, s32, Vec3 *, f32);
f32 *D_0062A430 ALIGNED(16);
extern f32 *D_0062A428;
typedef struct { u8 pad0[0x10]; f32 x, y, z; } Obj9c0;
extern u64 D_0038CD00;
typedef struct { s32 x0; s32 n; s32 tbl[1]; } Tbl;
extern Tbl *D_003DACA0;
void func_001ed6b0(void *);
s32 func_0011e340(void *);
typedef struct { s32 a, b, c, d; } Q4;
extern Q4 D_003DACC0;
extern u64 D_003DB028;
extern s32 D_003DACCC;
extern s32 D_003DACD0;
s32 func_0011ef10(s32, void (*)());
void func_001e15a0();
void func_001e2678();
extern f32 D_003DAD3C;
extern f32 D_003DAD40;
extern s32 D_003DAD44;
typedef struct { u8 pad0[0x3070]; u64 f3070; u64 f3078; } Big20;
extern Big20 D_00389C90;
extern s32 D_002BBBA0;
typedef struct { s32 x0; s32 a; s32 b; } Pair20;
extern Pair20 D_002E26A0;
void func_0022eee0(s32);
extern s32 D_003DC490;
extern u8 D_003DC1E8[];
typedef struct { u8 pad0[0x44]; f32 f44; u8 pad48[0x38]; u8 sub[0x80]; } Mgr20;
extern Mgr20 D_0062F790;
typedef struct { s32 a; s32 b; void (*fn)(); s32 d; } Cb20;
extern Cb20 D_0062F8F0;
void func_001e2f98();
void func_001e2f88();
void func_0010ef70(void *, void *, void *);
void func_0010f558(void *, void *, s32);
extern u8 D_0062F840[];
void func_001e39f0();
void func_0010bd90(void *, void (*)());
extern s32 D_003DC484;
void func_00231b98(void *);
void func_0010e3f0(void *);
extern u8 D_003DC3C0[];
extern u8 D_003DC390[];
extern u8 D_003DC268[];
extern s32 D_003DC48C;
void func_001e3a00(void);
void func_001e3a98();
extern u8 D_003DC228[];
void func_001e3f20();
void func_001e3ef0();
void func_001e4578();
void func_0010bdd0(void *, void (*)());
extern s32 D_002C5BB8;
extern s32 D_003DD264;
extern u8 D_006303B0[];
extern u8 D_00630300[];
void func_001e4990();
void func_00232aa8(void);
extern s32 D_003DD25C;
extern s32 D_003DD258;
extern u8 D_006314C8;
void func_001e4d50();
extern s32 D_003DD28C;
extern u8 D_00630510[];
void func_001e6388();
extern u8 D_003DCEB0[];
extern Cb20 D_006305C0;
void func_001e6410();
void func_001e6438();
s32 func_001e63a8(void);
void func_001e64e0();
extern s32 D_003DD260;
void func_001e6de0();
void func_001e6e08();
s32 func_001e6c90();
typedef struct { s32 x0; s16 h4; } Obj460;
extern Obj460 D_00630460;
extern u8 D_003DCFF0[];
void func_001e78d8();
void func_001e7928();
extern volatile s32 D_002C5958;
void func_001e7800(void);
void func_001e7930(void);
extern u8 D_003DD030[];
void func_001e7a10();
void func_001e7a60();
void func_001e7a68(void);
extern u8 D_003DD070[];
void func_001e7d58();
void func_001e7d80();
void func_001e7d90(void);
void func_001e4b08(void);
extern s32 D_006314D0;
extern s32 D_006314D8;
extern s32 D_003DABD4;
void func_001e7fe0();
void func_0011ec08(s32, s32, s32, void (*)());
extern s32 D_006314CC;
extern s32 D_006314DC;
void func_001e8308();
void func_0011eb88(s32, s32, s32, void (*)());
extern volatile s32 D_002C58C0;
s32 func_0011c808(s32);
extern s32 D_0037A378;
void func_0011d080(s32, s32);
void func_0011d0d8(s32, s32);
void func_0011d108(s32, s32, s32);
s32 func_0011e368(s32, s32);
void func_0011d350(s32, s32);

s32 func_001ddfb8(VM *vm) {
    Task *t = func_0011f090(D_0062A630, 0, func_001dd5c0);
    Sub *s = &vm->u.s;
    s32 i;
    t->kind = 0;
    i = vm->u.h.sp;
    t->owner = s->obj ? vm : 0;
    t->arg = s->stk[i];
    vm->u.h.sp -= 1;
    return 2;
}

s32 func_001de030(VM *vm) {
    Task *t = func_0011f090(D_0062A630, 0, func_001dd5c0);
    Sub *s = &vm->u.s;
    s32 i;
    t->kind = 10;
    i = vm->u.h.sp;
    t->owner = s->obj ? vm : 0;
    t->arg = s->stk[i];
    vm->u.h.sp -= 1;
    return 2;
}

s32 func_001de0b0(VM *vm) {
    Task *t = func_0011f090(D_0062A630, 0, func_001dd5c0);
    Sub *s = &vm->u.s;
    s32 i;
    t->kind = 16;
    i = vm->u.h.sp;
    t->owner = s->obj ? vm : 0;
    t->arg = s->stk[i];
    vm->u.h.sp -= 1;
    return 2;
}

s32 func_001de290(VM *vm) {
    Sub *s = &vm->u.s;
    Obj760 *o = func_001760d0(s->stk[vm->u.h.sp - 3]);
    s32 i;
    if (o) {
        f32 *v = o->v;
        i = vm->u.h.sp;
        v[0] = s->stk[i - 2];
        v[1] = s->stk[i - 1];
        v[2] = s->stk[i];
    } else {
        i = vm->u.h.sp;
    }
    vm->u.h.sp = i - 4;
    return 2;
}

s32 func_001df170(VM *vm) {
    Task *t = func_0011f090(D_0062A630, 0, func_001dd5c0);
    t->kind = 2;
    t->arg = vm->u.s.stk[vm->u.h.sp];
    vm->u.h.sp -= 1;
    return 2;
}

s32 func_001df1d8(VM *vm) {
    if (D_0029B418 && D_0029B41C) { Task *t = func_0011f090(D_0062A630, 0, func_001dd5c0); Sub *s; s32 i; t->kind = 3; s = &vm->u.s; i = vm->u.h.sp; t->owner = s->obj ? vm : 0; t->arg = s->stk[i]; }
    vm->u.h.sp -= 1;
    return 2;
}

s32 func_001df310(VM *vm) {
    Sub *s = &vm->u.s;
    Obj760 *o = func_001760f0(s->stk[vm->u.h.sp - 3]);
    s32 i;
    if (o) {
        f32 *v = o->v;
        i = vm->u.h.sp;
        v[0] = s->stk[i - 2];
        v[1] = s->stk[i - 1];
        v[2] = s->stk[i];
    } else {
        i = vm->u.h.sp;
    }
    vm->u.h.sp = i - 4;
    return 2;
}

s32 func_001df698(Ctx698 *c) {
    Vec3 v;
    Vec3 *p;
    if (c->ent->flags & 2) return 4;
    func_001315c0(c->mdl->id, c->k, &v, c->t);
    p = c->ent->pos;
    p->x = v.x;
    p->y = v.y;
    p->z = v.z;
    return 0;
}

s32 func_001df940(VM *vm) {
    Sub *s = &vm->u.s; s32 i = vm->u.h.sp; f32 *p = D_0062A430; f32 x = s->stk[i - 2], y = s->stk[i - 1], z = s->stk[i]; vm->u.h.sp = i - 4; p[0] = x / 100.0f; p[1] = y / 100.0f; p[2] = z / 100.0f;
    return 2;
}

s32 func_001dfb20(VM *vm) {
    Sub *s = &vm->u.s;
    Obj760 *o = func_001760b0(s->stk[vm->u.h.sp - 3]);
    s32 i;
    if (o) {
        f32 *v = o->v;
        i = vm->u.h.sp;
        v[0] = s->stk[i - 2];
        v[1] = s->stk[i - 1];
        v[2] = s->stk[i];
    } else {
        i = vm->u.h.sp;
    }
    vm->u.h.sp = i - 4;
    return 2;
}

s32 func_001e0318(VM *vm) {
    if ((s32)(D_0038CD00 >> 52) & 1) return 4;
    return 2;
}

s32 func_001e16b0(VM *vm) {
    Sub *s = &vm->u.s;
    u64 r;
    D_003DACC0.a = s->stk[vm->u.h.sp - 2];
    D_003DACC0.b = s->stk[vm->u.h.sp - 1];
    D_003DACC0.c = s->stk[vm->u.h.sp];
    r = (s64)D_003DACC0.a | 0x100000000LL; r |= (s64)D_003DACC0.c << 16 | (s64)D_003DACC0.b << 8; r |= (s64)D_003DACC0.d << 24;
    vm->u.h.sp -= 3; D_003DB028 = r;
    return 2;
}

s32 func_001e1748(VM *vm) {
    s32 n = vm->u.s.stk[vm->u.h.sp];
    if (n > 0) {
        D_003DACD0 = 128 / n; D_003DACCC = 0;
    } else {
        D_003DACD0 = 0;
        D_003DACCC = 128;
    }
    func_0011ef10(0x280a0, func_001e15a0);
    vm->u.h.sp -= 1;
    return 2;
}

s32 func_001e17e0(VM *vm) {
    s32 n = vm->u.s.stk[vm->u.h.sp];
    if (n > 0) {
        D_003DACD0 = -128 / n;
    } else {
        D_003DACD0 = -128;
    }
    vm->u.h.sp -= 1;
    return 2;
}

s32 func_001e25c8(VM *vm) {
    if ((s32)(D_0038CD00 >> 50) & 1) return 4;
    return 2;
}

s32 func_001e26b8(VM *vm) {
    Sub *s = &vm->u.s;
    s32 i = vm->u.h.sp;
    f32 x = s->stk[i - 1], y = s->stk[i];
    D_003DAD44 = y;
    D_003DAD40 = (x - D_003DAD3C) / y;
    func_0011ef10(50000, func_001e2678);
    vm->u.h.sp -= 2;
    return 2;
}

void func_001e2778(void) {
    D_002BBBA0 = 0;
    D_00389C90.f3070 &= ~0x400000000000LL;
}

void func_001e2a40(s32 a) {
    if (a == 3) {
        if (!D_002E26A0.a) a = 2;
        if (!D_002E26A0.b) a = a - 1;
    }
    func_0022eee0(a);
}

void func_001e30f8(void) {
    D_003DC490 = 1;
    func_0010ef70(&D_0062F790, D_003DC1E8, func_001e2f98);
    D_0062F8F0.a = 1;
    D_0062F8F0.b = 2;
    D_0062F8F0.fn = func_001e2f88;
    func_0010f558(&D_0062F8F0, &D_0062F790, 1);
}

void func_001e3aa8(void) {
    D_003DC48C = 1;
    func_0010ef70(D_0062F840, D_003DC268, func_001e3a00);
    D_0062F8F0.a = 1;
    D_0062F8F0.b = 2;
    D_0062F8F0.fn = func_001e3a98;
    func_0010f558(&D_0062F8F0, D_0062F840, 1);
}

s32 func_001e3ed0(VM *vm) {
    if ((s32)(D_0038CD00 >> 46) & 1) return 4;
    return 2;
}

void func_001e3fc8(void) {
    D_003DC490 = 1;
    func_0010ef70(&D_0062F790, D_003DC228, func_001e3f20);
    D_0062F8F0.a = 1;
    D_0062F8F0.b = 2;
    D_0062F8F0.fn = func_001e3ef0;
    func_0010f558(&D_0062F8F0, &D_0062F790, 1);
}

void func_001e42b0(void) {
    D_0062F790.f44 = 2.0f;
    if (D_002E26A0.a) D_0062F790.f44 = 3.0f;
    if (D_002E26A0.b) D_0062F790.f44 = 4.0f;
    func_0010bdd0(&D_0062F790, func_001e4578);
}

s32 func_001e4a68(void) {
    if (D_002C5BB8 & 2) {
        if (D_003DD264 == 1) {
            func_0010bd90(D_006303B0, func_001e4990);
            D_003DD264 = 0;
        } else {
            func_0010bd90(D_00630300, 0);
            func_00232aa8();
            D_00389C90.f3078 &= ~0x10;
            return 4;
        }
    }
    return 0;
}

void func_001e5788(s32 a) {
    D_006314C8 = a;
    if (D_003DD25C == 3) {
        D_003DD258 = a - 3;
        if (a - 3 < 10) {
            func_0010bdd0(D_006303B0, func_001e4d50);
            D_003DD264 = 1;
        }
    } else {
        D_003DD258 = a - 4;
        func_0010bdd0(D_006303B0, func_001e4d50);
        D_003DD264 = 1;
    }
}

s32 func_001e63a8(void) {
    if (!D_003DD28C) return 4;
    if (D_002C5BB8 & 2) {
        D_003DD28C = 0;
        D_003DD258 = 2;
        func_0010bd90(D_00630510, func_001e6388);
        return 4;
    }
    return 0;
}

s32 func_001e6450(void) {
    s32 r;
    func_0010ef70(D_00630510, D_003DCEB0, func_001e6410);
    D_006305C0.fn = func_001e6438;
    D_006305C0.b = 2;
    D_006305C0.a = 1;
    func_0010f558(&D_006305C0, D_00630510, 1);
    r = func_0011ef10(50000, (void (*)())func_001e63a8);
    D_003DD28C = 1;
    return r;
}

void func_001e6580(s32 a) {
    D_003DD28C = 0;
    D_003DD260 = a + D_006305C0.d * 10;
    func_0010bd90(D_00630300, func_001e64e0);
}

s32 func_001e6e20(void) {
    s32 r;
    func_0010ef70(D_00630510, D_003DCEB0, func_001e6de0);
    D_006305C0.fn = func_001e6e08;
    D_006305C0.b = 2;
    D_006305C0.a = 1;
    func_0010f558(&D_006305C0, D_00630510, 1);
    r = func_0011ef10(50000, (void (*)())func_001e6c90);
    D_003DD28C = 1;
    return r;
}

void func_001e7930(void) {
    func_0010ef70(&D_00630460, D_003DCFF0, func_001e78d8);
    D_006305C0.a = 1;
    D_006305C0.b = 2;
    D_006305C0.fn = func_001e7928;
    func_0010f558(&D_006305C0, &D_00630460, 1);
}

s32 func_001e79a0(void) {
    D_002C5958 |= 0xc;
    func_001e7800();
    D_00630460.h4 = 1;
    func_0010bdd0(&D_00630460, func_001e7930);
    D_00389C90.f3070 |= 0x20000000000000LL;
    return 6;
}

void func_001e7a68(void) {
    func_0010ef70(&D_00630460, D_003DD030, func_001e7a10);
    D_006305C0.a = 1;
    D_006305C0.b = 2;
    D_006305C0.fn = func_001e7a60;
    func_0010f558(&D_006305C0, &D_00630460, 1);
}

s32 func_001e7ad8(void) {
    D_002C5958 |= 0xc;
    func_001e7800();
    D_00630460.h4 = 1;
    func_0010bdd0(&D_00630460, func_001e7a68);
    D_00389C90.f3070 |= 0x20000000000000LL;
    return 6;
}

void func_001e7d90(void) {
    func_0010ef70(&D_00630460, D_003DD070, func_001e7d58);
    D_006305C0.a = 1;
    D_006305C0.b = 3;
    D_006305C0.fn = func_001e7d80;
    func_0010f558(&D_006305C0, &D_00630460, 1);
}

s32 func_001e7e00(void) {
    D_002C5958 |= 0xc;
    func_001e7800();
    func_001e4b08();
    D_00630460.h4 = 1;
    func_0010bdd0(&D_00630460, func_001e7d90);
    D_00389C90.f3070 |= 0x20000000000000LL;
    return 6;
}

s32 func_001e8178(void) {
    if (func_0011e340(0)) return 0;
    func_0011ec08(D_006314D0, D_003DABD4, D_006314D8, func_001e7fe0);
    return 4;
}

s32 func_001e82e0(VM *vm) {
    if ((s32)(D_0038CD00 >> 56) & 1) return 4;
    return 2;
}

s32 func_001e84a0(void) {
    if (func_0011e340(0)) return 0;
    func_0011eb88(D_006314CC, D_003DABD4, D_006314DC, func_001e8308);
    return 4;
}

s32 func_001e8608(VM *vm) {
    if ((s32)(D_0038CD00 >> 51) & 1) return 4;
    return 2;
}

s32 func_001e89c0(VM *vm) {
    if ((s32)(D_0038CD00 >> 57) & 1) return 4;
    return 2;
}

s32 func_001e8b50(VM *vm) {
    D_002C58C0 |= 0x8000;
    if (!func_0011c808(vm->u.s.stk[vm->u.h.sp] - 1)) return 4;
    vm->u.h.sp -= 1;
    return 2;
}

s32 func_001e8c88(VM *vm) {
    Sub *s = &vm->u.s;
    s32 i = vm->u.h.sp;
    s32 a = s->stk[i - 1], b = s->stk[i];
    if (!(D_0037A378 & 1)) {
        func_0011d080(a, b);
        i = vm->u.h.sp;
    }
    vm->u.h.sp = i - 2;
    return 2;
}

s32 func_001e8cf0(VM *vm) {
    Sub *s = &vm->u.s;
    s32 i = vm->u.h.sp;
    func_0011d0d8(s->stk[i - 1], s->stk[i]);
    vm->u.h.sp -= 2;
    return 2;
}

s32 func_001e8d40(VM *vm) {
    Sub *s = &vm->u.s;
    s32 i = vm->u.h.sp;
    func_0011d108(s->stk[i - 2], s->stk[i - 1], s->stk[i] * 8);
    vm->u.h.sp -= 3;
    return 2;
}

s32 func_001e8de8(VM *vm) {
    Sub *s = &vm->u.s;
    s32 i = vm->u.h.sp;
    func_0011d350(s->stk[i - 1], s->stk[i]);
    vm->u.h.sp -= 2;
    return 2;
}

#include "common.h"

typedef struct {
    u8 type;
    u64 val:24;
    s32 x;
    s32 a8;
    s32 ac;
    f32 v[4];
} Msg;
s32 func_001c4640(Msg *m);
typedef struct Ent {
    s32 x0;
    void *f4;
    u8 pad8[0x328 - 8];
    union { u64 x; s32 i[2]; } flags;
} Ent;
typedef struct {
    s32 x0;
    void *obj;
    u8 pad8[0x178];
    s32 sp;
    s32 stk[92];
    f32 f2f4;
    u8 pad2f8[0x30];
    union { u64 x; s32 i[2]; } flags;
    f32 f330;
} VM;
Ent *func_001e98d0(s32, s32);
typedef struct { u8 pad0[0x1f]; u8 n; u8 items[0x74 - 0x20]; } Chr;
typedef struct { u8 pad0[6]; Chr ch[10]; u8 a48e[11]; u8 a499[1]; } Save;
extern Save *D_00304BE8;

typedef struct { u8 type; u32 val:24; s32 x; s32 a8; s32 ac; f32 v[4]; } __attribute__((aligned(8))) Msg2;
typedef struct { u8 pad0[0x10]; f32 pos[3]; u8 pad1c[0x14]; f32 f30; f32 f34; f32 f38; } Obj5;
typedef struct {
    s32 x0;
    Obj5 *obj;
    u8 pad8[0xc];
    f32 f14[3];
    f32 f20;
    u8 pad24[0x3c];
    s32 f60;
    s32 f64;
    u8 pad68[0x118];
    s32 sp;
    s32 stk[92];
    f32 f2f4;
    u8 pad2f8[0x30];
    union { u64 x; s32 i[2]; } flags;
} VM5;
double sqrt(double);
double atan2(double, double);
s32 func_001d5b58(VM5 *vm) {
    Msg2 m;
    f32 v[3];
    f32 len, a, f, g;
    double d;
    vm->flags.x |= 1;
    v[0] = (f32)vm->stk[vm->sp - 2] - vm->obj->pos[0];
    v[1] = (f32)vm->stk[vm->sp - 1] - vm->obj->pos[1];
    v[2] = (f32)vm->stk[vm->sp] - vm->obj->pos[2];
    len = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);

    v[2] /= len;
    v[0] /= len;
    v[1] /= len;

    a = atan2(v[2], v[0]);
    d = a - (f32)atan2(vm->obj->f38, vm->obj->f30);
    if (d < 0.0) d = -d;
    f = d;
    if (3.1415928f < f) f = 3.1415928f - (f - 3.1415928f);
    d = f * 180.0f / 3.1415928f;
    if (d < 0.0) d = -d;
    g = d;

    m.type = 2;
    m.val = vm->stk[vm->sp - 3];
    m.v[0] = vm->stk[vm->sp - 2];
    m.x = vm->x0;
    m.v[1] = vm->stk[vm->sp - 1];
    m.v[2] = vm->stk[vm->sp];
    m.v[3] = g * 2.0f / (len / vm->stk[vm->sp - 3]);

    func_001c4640((Msg *)&m);
    vm->sp -= 4;
    vm->f14[0] = m.v[0];
    vm->f14[1] = m.v[1];
    vm->f14[2] = m.v[2];
    vm->f20 = m.val;
    vm->f60 = 0;
    vm->f64 = 0;
    return 2;
}
typedef struct {
    s32 x0;
    s32 f4;
    f32 a[3];
    f32 b[3];
    u8 pad20[4];
    f32 f24;
    f32 f28;
    u8 pad2c[0x328 - 0x2c];
    union { u64 x; s32 i[2]; } flags;
} VM93;
extern f32 D_002BBDFC;
void func_001d9348(VM93 *vm) {
    Msg m;
    f32 t;
    vm->f28 += D_002BBDFC;
    if (vm->f24 < vm->f28) {
        m.type = 3;
        m.val = 0;
        m.x = vm->x0;
        m.v[0] = vm->b[0];
        m.v[1] = vm->b[1];
        m.v[2] = vm->b[2];
        m.v[3] = 1.0f;
        func_001c4640(&m);
        vm->flags.x &= ~0x800ULL;
    } else {
        t = vm->f28 / vm->f24;
        m.type = 3;
        m.val = 0;
        m.x = vm->x0;
        m.v[0] = vm->a[0] + (vm->b[0] - vm->a[0]) * t;
        m.v[1] = vm->a[1] + (vm->b[1] - vm->a[1]) * t;
        m.v[2] = vm->a[2] + (vm->b[2] - vm->a[2]) * t;
        m.v[3] = 1.0f;
        func_001c4640(&m);
    }
}
/* rodata */
typedef struct { u8 pad0[0x3070]; u64 f3070; } Big02;
extern Big02 D_00389C90;
extern s32 D_0037A378;
extern char D_003DAC40[][6];
typedef struct { s32 x0; s32 n; s32 tbl[1]; } Tbl;
extern Tbl *D_003DACA0;
s32 func_0011e340(void *);
s32 func_001559f0(s32, s32);
void func_001e01f0(void);

s32 sprintf(char *, const char *, ...);
s32 func_001e0220(VM *vm) {
    char buf[512];
    s32 *pp;
    if (!(D_0037A378 & 1)) {
        if (func_0011e340(0) == 0) {
            sprintf(buf, "voice/event/%s_%03d.vset", D_003DAC40[vm->stk[vm->sp - 1]], vm->stk[vm->sp]);
            pp = (s32 *)&D_003DACA0;
            *pp = func_001559f0(60, 4); func_00120748(buf, *pp, func_001e01f0, 0);
            D_00389C90.f3070 |= 0x8000ULL << 37;
        } else {
            return 4;
        }
    }
    vm->sp -= 2;
    return 2;
}
extern s32 D_0037A378;
double ceil(double);
void func_0011e220(void *, s32, s32, s32);
s32 func_001e0338(VM *vm) {
    Tbl *t = D_003DACA0;
    s32 k = vm->stk[vm->sp - 2];
    s32 s; void *p;
    f32 a, b;
    s = *(t->tbl + k); p = (u8 *)t + *(t->tbl + k + t->n); a = vm->stk[vm->sp - 1] / 100.0f; b = vm->stk[vm->sp] / 100.0f;
    if (!(D_0037A378 & 1)) {
        func_0011e220(p, s, ceil(a * 16383.0f), ceil(b * 16383.0f));
    }
    vm->flags.x |= 4; vm->f2f4 = 4.0f; vm->sp -= 3;
    return 6;
}
void func_001ed6b0(void *);
s32 func_001e0498(VM *vm) {
    s32 k = vm->stk[vm->sp];
    if (k == -1) {
        func_001ed6b0((void *)-1);
        vm->sp--;
        return 2;
    }
    {
        Tbl *t = D_003DACA0;
        func_001ed6b0((u8 *)t + *(t->tbl + k + t->n));
    }
    vm->sp--;
    return 2;
}
s32 func_001e0528(VM *vm) {
    s32 k = vm->stk[vm->sp];
    if (k == -1) { if (func_0011e340(0)) return 4; }
    else { Tbl *t = D_003DACA0; if (func_0011e340((u8 *)t + *(t->tbl + k + t->n))) return 4; }
    vm->sp--;
    return 2;
}

#include "common.h"
typedef struct {
    u8 pad0[0x10];
    f32 pos[3];
    u8 pad1c[0x20];
    f32 f3c;
    u8 pad40[0x330];
    u64 f370;
} Ent;
typedef struct {
    s32 x0;
    Ent *ent;
    u8 pad8[0x60];
    f32 f68;
    s32 f6c;
    s32 code;
    u8 pad74[8];
    s32 lbl[64];
    s32 pc;
    s32 sp;
    s32 stk[92];
    f32 f2f4;
    u8 pad2f8[0x30];
    u64 flags;
} VM;
typedef struct {
    u8 type;
    u64 val:24;
    s32 x;
    s32 a8;
    s32 ac;
    f32 v[4];
} Msg;
s32 func_001c4640(void *m);
double sin(double);
double cos(double);
typedef struct {
    s32 x0;
    void *ent;
    f32 cur[3];
    f32 tgt[3];
    f32 spd;
    u8 pad24[0x304];
    u64 flags;
} VM2;
typedef struct {
    u8 type;
    u64 val:24;
    s32 x;
    s32 a8;
    s32 ac;
    f32 v[4];
    f32 d[3];
} Msg2;
double sqrt(double);
void func_001d1080(VM2 *vm) {
    Msg2 m;
    f32 dx, dy, dz, dist, spd;
    dx = vm->tgt[0] - vm->cur[0];
    dy = vm->tgt[1] - vm->cur[1];
    dz = vm->tgt[2] - vm->cur[2];
    dist = sqrt(dx * dx + dy * dy + dz * dz);
    spd = vm->spd;
    if (dist < spd) {
        m.type = 3;
        m.val = 0;
        m.x = vm->x0;
        m.v[0] = vm->tgt[0];
        m.v[1] = vm->tgt[1];
        m.v[2] = vm->tgt[2];
        m.v[3] = 1.0f;
        func_001c4640(&m);
        vm->flags &= ~0x40ULL;
    } else {
    m.type = 3;
    m.val = 0;
    m.x = vm->x0;
    m.v[3] = 1.0f;
    m.d[0] = (vm->tgt[0] - vm->cur[0]) / dist * spd;
    m.d[1] = (vm->tgt[1] - vm->cur[1]) / dist * spd;
    m.d[2] = (vm->tgt[2] - vm->cur[2]) / dist * spd;
    vm->cur[0] += m.d[0];
    vm->cur[1] += m.d[1];
    vm->cur[2] += m.d[2];
    m.v[0] = vm->cur[0];
    m.v[1] = vm->cur[1];
    m.v[2] = vm->cur[2];
    func_001c4640(&m);
    }
}

VM *func_001e98d0(s32, s32);
void func_001e9d00(f32 *out, f32 *to, f32 *from, f32 x);
static inline f32 inl_deg(f32 r) {
    f32 d = r * 180.0f / 3.1415928f;
    return d < 0.0f ? d + 360.0f : d;
}
s32 func_001d2090(VM *vm) {
    f32 from[4];
    f32 to[4];
    f32 out[4];
    VM *p;
    Ent *e;
    f32 a, b;
    s32 *r;
    p = func_001e98d0((s32)(vm->flags >> 5) & 1, vm->stk[vm->sp - 3]);
    if (!p) {
        vm->sp -= 3;
        vm->stk[vm->sp] = 0;
        return 2;
    }
    e = p->ent;
    from[0] = e->pos[0];
    from[1] = e->pos[1];
    from[2] = e->pos[2];
    to[0] = vm->stk[vm->sp - 2];
    to[1] = vm->stk[vm->sp - 1];
    to[2] = vm->stk[vm->sp];
    to[3] = from[3] = 1.0f;
    func_001e9d00(out, to, from, 0.0f);
    vm->sp -= 3;
    a = inl_deg(p->ent->f3c);
    vm->stk[vm->sp] = inl_deg(out[1]) - a;
    if (vm->stk[vm->sp] < 0) vm->stk[vm->sp] += 360;
    return 2;
}

s32 func_001d2270(VM *vm) {
    f32 from[4];
    f32 to[4];
    f32 out[4];
    VM *p, *q;
    Ent *e, *e2;
    f32 a;
    p = func_001e98d0((s32)(vm->flags >> 5) & 1, vm->stk[vm->sp - 1]);
    q = func_001e98d0((s32)(vm->flags >> 5) & 1, vm->stk[vm->sp]);
    if (!p || !q) {
        vm->sp -= 1;
        vm->stk[vm->sp] = 0;
        return 2;
    }
    e = p->ent;
    from[0] = e->pos[0];
    e2 = q->ent;
    from[1] = e->pos[1];
    from[2] = e->pos[2];
    from[3] = 1.0f;
    to[0] = e2->pos[0];
    to[1] = e2->pos[1];
    to[2] = e2->pos[2];
    to[3] = 1.0f;
    func_001e9d00(out, to, from, 0.0f);
    vm->sp -= 1;
    a = inl_deg(p->ent->f3c);
    vm->stk[vm->sp] = inl_deg(out[1]) - a;
    if (vm->stk[vm->sp] < 0) vm->stk[vm->sp] += 360;
    return 2;
}

extern s32 D_0037A378;
void func_001d3e30(VM2 *vm) {
    Msg2 m;
    f32 dx, dy, dz, dist, spd;
    dx = vm->tgt[0] - vm->cur[0];
    dy = vm->tgt[1] - vm->cur[1];
    dz = vm->tgt[2] - vm->cur[2];
    dist = sqrt(dx * dx + dy * dy + dz * dz);
    spd = vm->spd;
    if (dist < spd || (D_0037A378 & 1)) {
        m.type = 3;
        m.val = 0;
        m.x = vm->x0;
        m.v[0] = vm->tgt[0];
        m.v[1] = vm->tgt[1];
        m.v[2] = vm->tgt[2];
        m.v[3] = 1.0f;
        func_001c4640(&m);
        vm->flags &= ~0x200ULL;
    } else {
    m.type = 3;
    m.val = 0;
    m.x = vm->x0;
    m.v[3] = 1.0f;
    m.d[0] = (vm->tgt[0] - vm->cur[0]) / dist * spd;
    m.d[1] = (vm->tgt[1] - vm->cur[1]) / dist * spd;
    m.d[2] = (vm->tgt[2] - vm->cur[2]) / dist * spd;
    vm->cur[0] += m.d[0];
    vm->cur[1] += m.d[1];
    vm->cur[2] += m.d[2];
    m.v[0] = vm->cur[0];
    m.v[1] = vm->cur[1];
    m.v[2] = vm->cur[2];
    func_001c4640(&m);
    }
}

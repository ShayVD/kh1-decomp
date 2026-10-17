#include "common.h"

/* Script VM context (same layout as h15/h16): pc at +0x17c, sp at +0x180,
   value stack at +0x184, flags at +0x328. */
typedef struct {
    s32 x0;
    s32 x4;
    u8 pad8[0x68];
    s32 code;
    u8 pad74[8];
    s32 lbl[64];
    s32 pc;
    s32 sp;
    s32 stk[92];
    u8 pad2f4[0x34];
    u64 flags;
} VM;

typedef struct { u8 pad[0x7c]; s32 a[1]; u8 pad80[0x2f8-0x80]; s32 b[8]; } P;
P *func_001e98d0(s32, s32);
s32 func_001c1980(P *, s32, s32);

s32 func_001c19f8(VM *vm, s32 k) {
    s32 a = vm->stk[vm->sp--];
    s32 b = vm->stk[vm->sp--];
    P *p;
    if (b < 0) b = 0;
    else if (b >= 8) b = 7;
    p = func_001e98d0((s32)(vm->flags >> 5) & 1, a);
    func_001c1980(p, b, p->a[k]);
    return 2;
}

s32 func_001c1aa8(VM *vm) {
    s32 a = vm->stk[vm->sp--];
    s32 b = vm->stk[vm->sp--];
    P *p;
    if (b < 0) b = 0;
    else if (b >= 8) b = 7;
    p = func_001e98d0((s32)(vm->flags >> 5) & 1, a);
    if (p->b[b] != -1) {
        vm->pc -= 2;
        return 4;
    }
    return 2;
}

s32 func_001c1ce8(s32, s32);
s32 func_001c1cf8(s32, s32);
extern s32 (*D_0037A198[])(VM *, s32);

void func_001c1d20(VM *vm, s32 k) {
    s32 saved = vm->pc;
    s32 op, arg, r;
    vm->pc = vm->lbl[k];
    for (;;) {
        op = func_001c1ce8(vm->code, vm->pc);
        arg = func_001c1cf8(vm->code, vm->pc);
        if (op == 5) break;
        r = D_0037A198[op](vm, arg);
        if (r & 2) vm->pc++;
        if (r & 4) goto out;
        if (r & 8) goto out;
    }
out:
    vm->pc = saved;
}
typedef struct { s32 id; u8 pad[12]; f32 c[4]; f32 s[4]; } Box;
typedef struct {
    u8 pad0[0x3034];
    s32 x3034;
    s32 x3038;
    s32 x303c;
    u8 pad3040[0x30];
    u64 f3070;
    u64 f3078;
    u8 pad3080[0x3170 - 0x3080];
    s32 x3170;
    s32 x3174;
    s32 nbox;
    u8 pad317c[4];
    Box box[15];
    s32 x3450;
} Big;
extern Big D_00389C90;
typedef struct { u8 pad[16]; f32 pos[4]; } Obj;
extern Obj *D_002E26A0;
void func_002675a8(void *, void *);
s32 func_001c1e30(void) {
    f32 mn[4], mx[4], p[4];
    s32 i;
    if (D_002E26A0 == 0) return 0;
    func_002675a8(p, D_002E26A0->pos);
    for (i = 0; i < D_00389C90.nbox; i++) {
        mn[0] = D_00389C90.box[i].c[0] - D_00389C90.box[i].s[0] * 0.5f;
        mn[1] = D_00389C90.box[i].c[1] - D_00389C90.box[i].s[1] * 0.5f;
        mn[2] = D_00389C90.box[i].c[2] - D_00389C90.box[i].s[2] * 0.5f;
        mx[0] = D_00389C90.box[i].c[0] + D_00389C90.box[i].s[0] * 0.5f;
        mx[1] = D_00389C90.box[i].c[1] + D_00389C90.box[i].s[1] * 0.5f;
        mx[2] = D_00389C90.box[i].c[2] + D_00389C90.box[i].s[2] * 0.5f;
        if (mn[0] <= p[0] && p[0] <= mx[0] && mn[1] <= p[1] && p[1] <= mx[1] && mn[2] <= p[2] && p[2] <= mx[2])
            return D_00389C90.box[i].id;
    }
    return 0;
}

/* 32-byte message queue at D_006257E0 (tail D_006277E4, head D_006277E0). */
typedef struct {
    u8 type;
    u64 val:24;
    s32 x;
    s32 a8;
    s32 ac;
    f32 v[4];
} Msg;
extern Msg D_006257E0[256];
extern s32 D_006277E0;
extern s32 D_006277E4;
typedef struct { s32 f; s32 pad; } MsgTbl;
extern MsgTbl D_0037A21C[];
s32 func_00123488(s32);

s32 func_001c4640(Msg *m) {
    Msg t;
    if ((D_006277E4 + 1) % 256 == D_006277E0) return -1;
    if (func_00123488(m->x) == 0 && D_0037A21C[m->type].f != 0) return 0;
    D_006257E0[D_006277E4] = *m;
    D_006277E4 = (D_006277E4 + 1) % 256;
    return 0;
}

extern VM D_0038D170, D_0039A580;
extern volatile s32 D_002BBE04;
s32 func_001d59a0(VM *);

s32 func_001c4de0(s32 a, s32 b) {
    VM *vm;
    Msg m;
    D_00389C90.x3170 = a;
    D_00389C90.x3174 = b;
    if (D_00389C90.x3034 == 0) vm = &D_0038D170;
    else vm = &D_0039A580;
    D_00389C90.x3450 = 0;
    func_001c1d20(vm, 10);
    if (b == 1) {
        func_001d59a0(vm);
        m.type = 40;
        m.val = 0;
        m.v[0] = 0.0f;
        m.v[1] = 0.0f;
        m.v[2] = 0.0f;
        m.v[3] = 1.0f;
        func_001c4640(&m);
        if (D_002BBE04 == b) D_002BBE04 = 4;
    }
    return D_00389C90.x3450;
}

typedef struct { f32 x, y, z, w; } __attribute__((aligned(16))) V4;
typedef struct { u8 pad[8]; s32 n; } Lim;
typedef struct {
    f32 t;
    u8 pad4[0xc];
    V4 a;
    V4 b;
    V4 c;
    V4 d;
    V4 e;
    f32 f60;
    u8 pad64[0xE0F4 - 0x64];
    f32 fE0F4;
    u8 padE0F8[4];
    Lim *lim;
} Cam;
extern Cam D_0037A380;
typedef struct {
    union {
        u64 flags;
        struct { s32 lo; f32 dur0; f32 dur1; } s;
    } u;
    u8 pad10[8];
    f32 t0;
    f32 t1;
    u8 pad20[0x20];
    V4 p40;
    V4 p50;
    V4 p60;
    V4 p70;
    V4 p80;
    u8 pad90[0x30];
    V4 v0;
    V4 a, b, c, d, e;
    f32 f50;
    f32 f54;
} CamOut;
extern CamOut D_003C5510;
extern u8 D_003C55E0[];
/* D_003C55E0 is +0xd0 into this block. */
#define OUT (*(CamOut *)(D_003C55E0 - 0xd0))
void func_001c53c8(f32);
void func_001c6a20(void);
static inline void inl_cpy(V4 *d, V4 *s) {
    *d = *s;
}
s32 func_001c5db8(void) {
    D_0037A380.t += 1.0f;
    if ((f32)D_0037A380.lim->n < D_0037A380.t) {
        D_0037A380.t = (f32)D_0037A380.lim->n;
        return 4;
    }
    func_001c53c8(D_0037A380.t);
    inl_cpy(&OUT.a, &D_0037A380.a);
    inl_cpy(&OUT.b, &D_0037A380.d);
    inl_cpy(&OUT.c, &D_0037A380.e);
    inl_cpy(&OUT.e, &D_0037A380.c);
    inl_cpy(&OUT.d, &D_0037A380.b);
    OUT.f50 = D_0037A380.f60;
    OUT.f54 = D_0037A380.fE0F4;
    func_001c6a20();
    return 0;
}

void func_001c6890(void);
f32 func_001e9e58(V4 *, V4 *);
void func_001e9d00(V4 *, V4 *, V4 *, f32);
s32 func_001c8168(VM *vm) {
    V4 t, r;
    func_001c6890();
    t.x = vm->stk[vm->sp - 2];
    t.y = vm->stk[vm->sp - 1];
    t.z = vm->stk[vm->sp];
    OUT.f50 = func_001e9e58(&t, &OUT.a);
    func_001e9d00(&r, &OUT.a, &t, OUT.b.z);
    func_002675a8(&OUT.b, &r);
    func_001c6a20();
    if ((s32)(OUT.u.flags >> 8) & 1) func_002675a8(&OUT.v0, &OUT.a);
    vm->sp -= 3;
    return 2;
}

s32 func_001c8260(VM *vm) {
    func_001c6890();
    D_003C5510.a.x = vm->stk[vm->sp - 2];
    D_003C5510.a.y = vm->stk[vm->sp - 1];
    D_003C5510.a.z = vm->stk[vm->sp];
    func_001c6a20();
    if ((s32)(D_003C5510.u.flags >> 8) & 1) func_002675a8(&D_003C5510.v0, &D_003C5510.a);
    vm->sp -= 3;
    return 2;
}

s32 func_001c8308(VM *vm) {
    func_001c6890();
    D_003C5510.b.x = vm->stk[vm->sp - 2] / 180.0f * 3.1415928f;
    D_003C5510.b.y = vm->stk[vm->sp - 1] / 180.0f * 3.1415928f;
    D_003C5510.b.z = vm->stk[vm->sp] / 180.0f * 3.1415928f;
    func_001c6a20();
    vm->sp -= 3;
    return 2;
}

extern f32 D_002BBDFC;

void func_001e9fe8(V4 *, V4 *);
void func_001e9f18(V4 *, V4 *, V4 *, f32);
void func_001c8758(void) {
    CamOut *c = &D_003C5510;
    V4 *f = &c->p40;
    V4 *t = &c->p70;
    V4 *o = &c->a;
    V4 m, q;
    c->t0 += D_002BBDFC;
    if (c->u.s.dur0 < c->t0) {
        c->t0 = c->u.s.dur0;
        c->u.flags &= ~1;
    }
    func_001e9fe8(&q, &c->b);
    func_001e9f18(&m, o, &q, c->f50);
    o->x = f->x + (t->x - f->x) / c->u.s.dur0 * c->t0;
    c->a.y = f->y + (t->y - f->y) / c->u.s.dur0 * c->t0;
    c->a.z = f->z + (t->z - f->z) / c->u.s.dur0 * c->t0;
    func_001c6a20();
}

s32 func_001c8878(VM *vm) {
    f32 d;
    func_001c6890();
    D_003C5510.u.flags |= 1;
    D_003C5510.p40.x = D_003C5510.a.x;
    D_003C5510.p40.y = D_003C5510.a.y;
    D_003C5510.p40.z = D_003C5510.a.z;
    d = vm->stk[vm->sp - 3] * 2.0f;
    D_003C5510.p70.x = vm->stk[vm->sp - 2];
    D_003C5510.p70.y = vm->stk[vm->sp - 1];
    D_003C5510.p70.z = vm->stk[vm->sp];
    D_003C5510.t0 = 0.0f;
    vm->sp -= 4;
    D_003C5510.u.s.dur0 = d;
    return 2;
}

static inline void inl_lerp2(V4 *f, V4 *t, f32 d, f32 s) {
    D_003C5510.b.x = f->x + (t->x - f->x) / d * s;
    D_003C5510.b.y = f->y + (t->y - f->y) / d * s;
    D_003C5510.b.z = f->z + (t->z - f->z) / d * s;
}
void func_001c8930(void) {
    CamOut *c = &D_003C5510;
    c->t1 += D_002BBDFC;
    if (c->u.s.dur1 < c->t1) {
        c->t1 = c->u.s.dur1;
        c->u.flags &= ~2;
    }
    inl_lerp2(&c->p50, &c->p80, c->u.s.dur1, c->t1);
    do { func_001c6a20(); } while (0);
}

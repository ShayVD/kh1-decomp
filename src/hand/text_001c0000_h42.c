#include "common.h"
#include "data/bss_0062.h"

typedef struct Ent2 {
    u8 pad0[0x10];
    f32 pos[3];
    u8 pad1c[0x370 - 0x1c];
    u8 col[4];
} Ent2;

/* Script VM context (same layout as h15/h16): pc at +0x17c, sp at +0x180,
   value stack at +0x184, flags at +0x328. */
typedef struct {
    s32 x0;
    struct Ent2 *ent;
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

typedef struct { s32 x0; s32 id; } PQ;
typedef struct { s32 x0; PQ *q; u8 pad8[0x74]; s32 a[1]; u8 pad80[0x2f8-0x80]; s32 b[8]; } P;
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
typedef struct Fx {
    u8 pad0[0x30];
    f32 v30[4];
} Fx;
typedef struct { s32 id; u8 pad[12]; f32 c[4]; f32 s[4]; } Box;
typedef struct {
    u8 b0[4];
    u8 b4[8];
    u8 bc[4];
    u16 h10[8][256];
    s32 w1010[8];
    s8 c1030[4];
    u8 pad1034[0x3034 - 0x1034];
    s32 x3034;
    s32 x3038;
    s32 x303c;
    u8 pad3040[0x30];
    union { u64 x; s32 i[2]; } f3070;
    u64 f3078;
    u8 pad3080[0x18];
    s32 idx;
    s32 cnt;
    f32 d[3];
    struct Fx *ptrs[4];
    u8 pad30bc[0x3170 - 0x30bc];
    s32 x3170;
    s32 x3174;
    s32 nbox;
    u8 pad317c[4];
    Box box[15];
    s32 x3450;
} Big;
extern Big D_00389C90;
typedef struct { u8 pad[16]; f32 pos[4]; } Actor;
extern Actor *D_002E26A0;
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
#include "data/types/text_001c0000_h42.h"
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

#include "data/pieces/D_0039A580.h"
#include "data/pieces/D_0038D170.h"
extern volatile s32 D_002BBE04;
s32 func_001d59a0(VM *);

s32 func_001c4de0(s32 a, s32 b) {
    VM *vm;
    Msg m;
    D_00389C90.x3170 = a;
    D_00389C90.x3174 = b;
    if (D_00389C90.x3034 == 0) vm = ((VM *)&D_0038D170);
    else vm = ((VM *)&D_0039A580);
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

#include "data/pieces/D_0037A380.h"
typedef V4_37A380 V4;
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
    (*(Cam_37A380 *)&D_0037A380).t += 1.0f;
    if ((f32)(*(Cam_37A380 *)&D_0037A380).last->n < (*(Cam_37A380 *)&D_0037A380).t) {
        (*(Cam_37A380 *)&D_0037A380).t = (f32)(*(Cam_37A380 *)&D_0037A380).last->n;
        return 4;
    }
    func_001c53c8((*(Cam_37A380 *)&D_0037A380).t);
    inl_cpy(&OUT.a, &(*(Cam_37A380 *)&D_0037A380).a);
    inl_cpy(&OUT.b, &(*(Cam_37A380 *)&D_0037A380).d);
    inl_cpy(&OUT.c, &(*(Cam_37A380 *)&D_0037A380).e);
    inl_cpy(&OUT.e, &(*(Cam_37A380 *)&D_0037A380).c);
    inl_cpy(&OUT.d, &(*(Cam_37A380 *)&D_0037A380).b);
    OUT.f50 = (*(Cam_37A380 *)&D_0037A380).f60;
    OUT.f54 = (*(Cam_37A380 *)&D_0037A380).fE0F4;
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

/* 0xB0-byte entries at D_006298F0 (D_0062A130 is entry 12). */
typedef struct {
    s32 x0;
    u16 h4;
    u16 h6;
    u16 h8;
    u8 pada[2];
    u16 hc;
    u16 he;
    u8 pad10[0xc];
    f32 f1c;
    u8 pad20[0x10];
    f32 v30[2];
    u8 pad38[8];
    f32 v40[2];
    u8 pad48[0x38];
    u8 f80[0x10];
    u8 b90;
    u8 pad91[3];
    f32 f94;
    u8 pad98[0x18];
} __attribute__((aligned(8))) Obj;
extern Obj D_006298F0[];
extern Obj D_0062A130; /* src/data/bss_0062.c: u8 D_0062A130[0xb0] */
extern Obj D_00629E70[]; /* src/data/bss_0062.c: Ent176 D_00629E70[4] */
void func_001cab48(void) {
    s32 i;
    for (i = 0; i < 8; i++) {
        D_00389C90.b0[i] = 0;
        D_00389C90.b4[i] = 0;
        D_00389C90.bc[i] = 0;
        D_00389C90.w1010[i] = 0;
        D_006298F0[i].v30[0] = -1.0f;
        D_006298F0[i].v30[1] = 30.0f;
        D_006298F0[i].v40[0] = 10.0f;
        D_006298F0[i].v40[1] = 3.0f;
        D_006298F0[i].h4 = 2;
        D_006298F0[i].hc = 2;
        D_006298F0[i].he = 2;
        D_006298F0[i].h6 = 0;
        D_006298F0[i].h8 = 0;
        D_006298F0[i].f1c = 45.0f;
        D_006298F0[i].x0 = -1;
        D_006298F0[i].b90 = 0;
        D_006298F0[i].f94 = 1.0f;
    }
    D_0062A130.v30[0] = 0.0f;
    D_0062A130.v30[1] = 0.0f;
    D_0062A130.v40[0] = 12.0f;
    D_0062A130.v40[1] = 3.0f;
    D_0062A130.h4 = 1;
    D_0062A130.hc = 1;
    D_0062A130.he = 1;
    D_0062A130.h6 = 0;
    D_0062A130.h8 = 0;
    D_0062A130.f1c = 45.0f;
    D_0062A130.x0 = -1;
    D_0062A130.b90 = 0;
    D_0062A130.f94 = 1.0f;
}

void func_001cae20(Obj *);
void func_0010bd90(Obj *, void (*)(Obj *));
s32 func_001cae78(VM *vm) {
    s32 v = vm->stk[vm->sp];
    s32 i;
    for (i = 0; i < 4; i++) {
        if (v == D_00389C90.c1030[i]) break;
    }
    if (i < 4 && D_00389C90.b0[i] != 0) {
        func_0010bd90(&D_00629E70[i], func_001cae20);
        D_00389C90.b0[i] = 3;
    }
    vm->sp--;
    return 2;
}

void func_0010e3f0(void *);
void func_0010ef70(Obj *, s32, void *);
extern s32 D_003C5890;
#include "data/pieces/D_00388480.h"
void func_001cafe8(s32 id, Obj *t) {
    s32 i;
    D_003C5890 = id;
    for (i = 0; i < 4; i++) {
        Obj *o = &D_00629E70[i];
        if (o == t) {
            s32 k = D_00389C90.c1030[i];
            if (D_00389C90.w1010[k] == id) {
                func_0010bd90(o, func_001cae20);
            } else {
                D_00389C90.b0[i] = 2;
                D_00389C90.b4[k] = 2;
                func_0010e3f0(D_00629E70[i].f80);
                func_0010ef70(o, ((s32 *)&D_00388480)[D_00389C90.h10[k][id]], func_001cafe8);
            }
        }
    }
}

void func_001cbab0(s32 id, Obj *t) {
    s32 i;
    D_003C5890 = 0;
    for (i = 0; i < 4; i++) {
        Obj *o = &D_00629E70[i];
        if (o == t) {
            s32 k = D_00389C90.c1030[i];
            if (D_00389C90.w1010[k] == 0) {
                func_0010bd90(o, func_001cae20);
            } else {
                D_00389C90.b0[i] = 2;
                D_00389C90.b4[k] = 2;
                func_0010ef70(o, ((s32 *)&D_00388480)[D_00389C90.h10[k][id]], func_001cafe8);
            }
        }
    }
}
void func_001cbd80(s32 id, Obj *t) {
    s32 i;
    D_003C5890 = id;
    for (i = 0; i < 4; i++) {
        Obj *o = &D_00629E70[i];
        if (o == t) {
            s32 k = D_00389C90.c1030[i];
            if (D_00389C90.w1010[k] == id) {
                D_00389C90.b0[i] = 4;
                D_00389C90.b4[k] = 4;
            } else {
                D_00389C90.b0[i] = 2;
                D_00389C90.b4[k] = 2;
                func_0010ef70(o, ((s32 *)&D_00388480)[D_00389C90.h10[k][id]], func_001cbd80);
            }
        }
    }
}
void func_001cbea0(s32 id, Obj *t) {
    s32 i;
    D_003C5890 = 0;
    for (i = 0; i < 4; i++) {
        Obj *o = &D_00629E70[i];
        if (o == t) {
            s32 k = D_00389C90.c1030[i];
            if (D_00389C90.w1010[k] == 0) {
                D_00389C90.b0[i] = 4;
                D_00389C90.b4[k] = 4;
            } else {
                D_00389C90.b0[i] = 2;
                D_00389C90.b4[k] = 2;
                func_0010ef70(o, ((s32 *)&D_00388480)[D_00389C90.h10[k][id]], func_001cbd80);
            }
        }
    }
}

s32 func_001cc548(VM *vm) {
    s32 c = vm->stk[vm->sp - 2];
    s32 x = vm->stk[vm->sp - 1];
    s32 y = vm->stk[vm->sp];
    s32 i;
    for (i = 0; i < 4; i++) {
        if (D_00389C90.b0[i] == 2 && c == D_00389C90.c1030[i]) break;
    }
    if (i < 4) {
        Obj *o = &D_00629E70[i];
        o->v30[0] = x;
        D_00629E70[i].v30[1] = y;
    }
    vm->sp -= 3;
    return 2;
}

s32 func_0010f098(s32);

s32 func_001ccbf8(VM *vm) {
    s32 n = vm->stk[vm->sp - 3];
    s32 t = vm->stk[vm->sp - 2];
    s32 x = vm->stk[vm->sp - 1];
    s32 y = vm->stk[vm->sp];
    f32 r = func_0010f098(((s32 *)&D_00388480)[t]);
    D_006298F0[n].v40[0] = r;
    D_006298F0[n].v30[0] = x + r * 12.0f;
    D_006298F0[n].v30[1] = y + D_006298F0[n].v40[1] * 12.0f;
    vm->sp -= 4;
    return 2;
}

s32 func_001cd940(VM *vm) {
    Msg m;
    m.type = 3;
    m.val = 0;
    m.x = vm->x0;
    m.v[0] = vm->stk[vm->sp - 2];
    m.v[1] = vm->stk[vm->sp - 1];
    m.v[2] = vm->stk[vm->sp];
    m.v[3] = 1.0f;
    func_001c4640(&m);
    vm->sp -= 3;
    return 2;
}

s32 func_001cec68(VM *vm) {
    Fx *e;
    s32 n;
    f32 x, y, z, fn;
    D_00389C90.idx = vm->stk[vm->sp - 4];
    e = D_00389C90.ptrs[D_00389C90.idx];
    n = vm->stk[vm->sp];
    D_00389C90.cnt = n;
    fn = n;
    x = vm->stk[vm->sp - 3] / 255.0f;
    y = vm->stk[vm->sp - 2] / 255.0f;
    z = vm->stk[vm->sp - 1] / 255.0f;
    D_00389C90.d[0] = (x - e->v30[0]) / fn;
    D_00389C90.d[1] = (y - e->v30[1]) / fn;
    D_00389C90.d[2] = (z - e->v30[2]) / fn;
    if (n == 0) {
        e->v30[0] = x;
        e->v30[1] = y;
        e->v30[2] = z;
        e->v30[3] = 1.0f;
    } else {
        D_00389C90.f3070.x |= 0x80000000000ULL;
    }
    vm->sp -= 5;
    return 2;
}

s32 func_001cf018(VM *vm) {
    Msg m;
    m.type = 19;
    m.val = (u32)vm->stk[vm->sp - 2];
    m.x = vm->x0;
    m.v[0] = vm->stk[vm->sp - 1];
    m.v[1] = vm->stk[vm->sp] * 2.0f;
    func_001c4640(&m);
    vm->sp -= 3;
    return 2;
}

s32 func_001cf110(VM *vm) {
    Msg m;
    m.type = 23;
    m.val = (u32)vm->stk[vm->sp];
    m.x = vm->x0;
    m.v[0] = vm->stk[vm->sp - 4] / 255.0f;
    m.v[1] = vm->stk[vm->sp - 3] / 255.0f;
    m.v[2] = vm->stk[vm->sp - 2] / 255.0f;
    m.v[3] = vm->stk[vm->sp - 1] * 0.0078125f;
    func_001c4640(&m);
    vm->sp -= 5;
    return 2;
}
s32 func_001cf210(VM *vm) {
    Msg m;
    if (vm->ent != 0) {
        m.type = 23;
        m.val = (u32)(vm->stk[vm->sp] * 2);
        m.x = vm->x0;
        m.v[0] = vm->ent->col[0] * 0.0078125f;
        m.v[1] = vm->ent->col[1] * 0.0078125f;
        m.v[2] = vm->ent->col[2] * 0.0078125f;
        m.v[3] = 1.0f;
        func_001c4640(&m);
    }
    vm->sp--;
    return 2;
}

s32 func_001cfd30(VM *vm) {
    Msg m;
    m.type = 17;
    m.val = (u32)(vm->stk[vm->sp - 1] | 0x10000);
    m.x = vm->x0;
    m.v[0] = vm->stk[vm->sp];
    func_001c4640(&m);
    vm->sp -= 2;
    return 2;
}
#include "data/data_003C.h"
#include "data/pieces/D_002BBDFC.h"
#include "data/pieces/D_002BBE04.h"
#include "data/pieces/D_0037A21C.h"

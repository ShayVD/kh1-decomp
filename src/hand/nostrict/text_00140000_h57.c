#include "common.h"

typedef struct {
    union { u64 flags; s32 w; } u;
    u8 pad8[4];
    f32 f0c;
    f32 v10[4];
    s32 i20;
    f32 f24;
    f32 f28;
    u8 pad2c[0x34-0x2c];
    s32 i34;
    u8 pad38[0x3c-0x38];
    f32 f3c;
    f32 v40[4];
    u8 pad50[0x54-0x50];
    s32 i54;
    u8 pad58[0x70-0x58];
    f32 v70[4];
    f32 v80[4];
    s32 i90;
    u8 pad94[0x9c-0x94];
    s32 i9c;
    u8 pada0[0xc0-0xa0];
} Src57_c130;
typedef struct { s32 kind; s32 a4; s32 a8; s32 src; s32 a10; f32 f14; f32 f18; s32 pad1c; f32 v[4]; } Ent57_c130;
typedef struct { u8 x[20]; } Col57_c130;
typedef struct { u8 pad0[6]; u8 n; u8 pad7[0x18-7]; Col57_c130 *cols; } ColSet57_c130;
typedef struct {
    u8 pad0[0x134];
    ColSet57_c130 *cs;
    u8 pad138[0x370-0x138];
    u64 f370;
    u8 pad378[0x3a8-0x378];
    u32 mask;
    u8 pad3ac[0x3e0-0x3ac];
    s32 f3e0;
} Chr57_c130;
typedef struct { u8 pad0[0x100]; u64 f100; } Sub57_c850;
typedef struct {
    u8 pad0[0x30];
    f32 v30[3];
    f32 f3c;
    u8 pad40[0x148-0x40];
    Sub57_c850 *o148;
    u8 pad14c[0x150-0x14c];
    f32 f150;
    u8 pad154[0x170-0x154];
    f32 f170;
    u8 pad174[0x3c0-0x174];
    f32 v3c0[4];
    u8 pad3d0[4];
    f32 f3d4;
} Obj57_c850;
typedef struct { u8 pad0[0x130]; f32 v130[4]; } Sub57_0678;
typedef struct {
    s32 flags;
    u8 pad4[0x30-4];
    f32 v30[4];
    u8 pad40[0x148-0x40];
    Sub57_0678 *o148;
    u8 pad14c[0x150-0x14c];
    f32 f150;
    u8 pad154[0x3c0-0x154];
    f32 v3c0[4];
} Obj57_0678;
typedef struct { u8 pad0[0x34]; f32 f34; } Arg57_0678;
typedef struct { u8 pad0[0x4c]; u16 h4c; } Info57_0ec8;
typedef struct { u8 pad0[0x130]; Info57_0ec8 *info; } Pl57_0ec8;
typedef struct { s32 i0; u8 pad4[4]; s32 i8; f32 fc; f32 v10[4]; u8 pad20[0x2c-0x20]; f32 f2c; u8 pad30[4]; s32 i34; } Ev57_0ec8;
typedef struct {
    s32 flags;
    u8 pad4[0x10-4];
    f32 v10[4];
    f32 v20[4];
    u8 pad30[0x144-0x30];
    Ev57_0ec8 *ev;
} Obj57_0ec8;
typedef struct Slot57_15d0 Slot57_15d0;
typedef struct {
    s32 flags;
    u8 pad4[0x10-4];
    f32 v10[4];
    f32 f20;
    f32 f24;
    f32 f28;
    u8 pad2c[0x40-0x2c];
    f32 f40;
    f32 f44;
    f32 f48;
    u8 pad4c[0x144-0x4c];
    Slot57_15d0 *slot;
} Obj57_15d0;
struct Slot57_15d0 {
    s32 x0;
    Obj57_15d0 *obj;
    void *owner;
    u8 padc[0x20-0xc];
    f32 f20;
    f32 f24;
    s32 age;
    s32 x2c;
    f32 f30;
    s32 x34;
    u8 pad38[0x40-0x38];
};
typedef struct { s32 id; f32 f4; } Kind57_15d0;
typedef struct { u8 pad0[3]; u8 b3; } Q57_15d0;

extern u32 D_002C5958;
extern Src57_c130 D_0054C440[64];
extern s32 D_0054F440;
extern f32 D_002BBDFC;
extern f32 D_002C5970;
extern f32 D_0054F444;
extern s32 D_0054F738;
extern Pl57_0ec8 *D_002E26A0;
extern f32 D_002C58B0[];
extern Slot57_15d0 D_0054F750[8];
extern s32 D_0054F740;
extern Kind57_15d0 D_003514E8[];

Ent57_c130 *func_00121e28(s32, s32);
void func_00121ee0(Ent57_c130 *);
Chr57_c130 *func_001230a0(Chr57_c130 *);
s32 func_00123368(Chr57_c130 *);
s32 func_0014bdc0(Ent57_c130 *);
void func_0014b550(Ent57_c130 *, Ent57_c130 *, s32);
void func_0015bad0(Chr57_c130 *, Col57_c130 *, void *);
void func_002675a8(f32 *, f32 *);
f32 func_00120c18(f32 *);
f32 func_00120bf8(f32 *);
void func_00267560(f32 *, f32 *, f32);
f32 sinf(f32);
f32 cosf(f32);
f32 func_00120c88(f32);
f32 func_00267390(f32 *, f32 *);
void func_00137688(Obj57_0678 *, f32);
void func_00137308(Obj57_0678 *, Arg57_0678 *);
s32 func_0014f658(void *, s32);
void func_001315c0(Pl57_0ec8 *, s32, f32 *, f32);
s32 func_001453a8(Pl57_0ec8 *, f32 *, s32);
s32 func_0013c9e0(s32, s32);
void func_00243630(s32, s32);
void func_00267530(f32 *, f32 *, f32 *);
void func_001473a8(s32, s32, f32 *);
void func_00137418(Obj57_15d0 *, f32);
Q57_15d0 *func_00147840(void *);
Obj57_15d0 *func_00124218(s32);
f32 func_00176850(void);

s32 func_0014c130(void) {
    Ent57_c130 *tbl;
    s32 cnt;
    Ent57_c130 *e;
    Chr57_c130 *p;
    Chr57_c130 *q;
    Src57_c130 *s;
    Col57_c130 *c;
    s32 i;

    if ((D_002C5958 >> 14) & 1) return 0;
    tbl = func_00121e28(0x3000, 0);
    cnt = func_0014bdc0(tbl);
    e = &tbl[cnt];
    e->a10 = 1;
    e->src = 0;
    for (q = 0; (p = func_001230a0(q)) != 0; q = p) {
        if (!func_00123368(p)) continue;
        e->kind = (s32)(p->f370 >> 37) & 3;
        e->a4 = (s32)p;
        c = p->cs->cols;
        for (i = 0; i < p->cs->n; i++, c++) {
            if (!(p->mask & (1 << i))) {
                func_0015bad0(p, c, &e->a10);
                e->a8 = c->x[0];
                func_0014b550(e, tbl, cnt);
            }
        }
    }
    func_00121ee0(tbl);
    s = D_0054C440;
    for (i = 0; i < 64; i++, s++) {
        if ((s32)(s->u.flags >> 15) & 1) {
            func_002675a8(s->v70, s->v10);
            func_002675a8(s->v80, s->v40);
            s->u.flags |= 0x10000;
        } else {
            s->u.flags &= ~0x10000;
        }
        s->i9c &= D_0054F440;
    }
    p = 0;
    while ((p = func_001230a0(p)) != 0) {
        p->f3e0 &= D_0054F440;
    }
    return (s32)p;
}

void func_0014c850(Obj57_c850 *o, f32 *v) {
    f32 d;
    f32 lim;
    f32 k;
    f32 t;

    if ((s32)(o->o148->f100 >> 32) & 1) {
        lim = 16.0f;
        k = 2.0f;
        if (o->f3d4 < 70.0f) {
            t = o->f3d4 / 70.0f;
            k = (t * t * 0.800000026822f + 0.199999991804f) * 2.0f;
        }
    } else {
        lim = 8.0f;
        k = 1.19999995828f;
    }
    d = func_00120c18(o->v3c0);
    if (d < lim) {
        d += D_002BBDFC * 0.399999983609f;
        if (lim < d) d = lim;
    }
    func_002675a8(v, o->v30);
    func_00267560(v, v, d * D_002BBDFC);
    if (k * D_002BBDFC < o->v3c0[1]) {
        v[1] = k;
    } else {
        if (o->v3c0[1] < 0.0f) {
            o->v3c0[1] *= 0.799999967217f;
        }
        v[1] = o->v3c0[1] + D_002BBDFC * 0.484693862498f;
    }
    func_00267560(o->v3c0, v, D_002C5970);
    o->v3c0[1] = v[1];
    D_0054F444 = func_00120bf8(v);
}

void func_00150678(Obj57_0678 *o, Arg57_0678 *p) {
    f32 v[4];
    f32 a;
    f32 d;

    a = p->f34;
    v[1] = 0.0f;
    v[0] = sinf(a);
    v[1] = 0.0f;
    v[2] = cosf(a);
    v[3] = 1.0f;
    if (func_00120c18(o->v3c0) < 1.0f) d = func_00267390(v, o->v30);
    else d = func_00267390(v, o->v3c0);
    if (d > 0.0f) {
        o->flags |= 0x800000;
        a = p->f34;
    } else {
        o->flags &= ~0x800000;
        a = func_00120c88(p->f34 + 3.1415928f);
    }
    o->f150 = a;
    func_00137688(o, a);
    func_00267560(o->o148->v130, o->v3c0, D_002BBDFC * 0.5f);
    func_00137308(o, p);
    func_0014f658(o, 26);
    D_0054F738 = 0;
}

s32 func_00150ec8(Obj57_0ec8 *o) {
    f32 v[4];
    Pl57_0ec8 *pl;
    Ev57_0ec8 *e;
    s32 r;

    pl = D_002E26A0;
    func_001315c0(pl, 0x8003, v, 0.0f);
    e = o->ev;
    if (!(o->flags & 0x20)) {
        if (func_001453a8(pl, o->v10, e->i34)) {
            r = func_0013c9e0(e->i8, pl->info->h4c);
            if (r == 255) {
                if (e->f2c <= 0.0f) func_00243630(2, e->i8);
                e->f2c = 60.0f;
                goto end;
            }
            e->i0 = 2;
            func_00267530(e->v10, o->v10, v);
            func_00243630(r == 12, e->i8);
            func_001473a8(27, 0, o->v10);
            e->fc = 30.0f;
            o->flags |= 0x30;
            func_002675a8(o->v20, D_002C58B0);
            return 1;
        }
    }
end:
    return 0;
}

s32 func_001515d0(void *owner, f32 *pos, s32 type) {
    Slot57_15d0 *best;
    Slot57_15d0 *e;
    s32 i;
    Q57_15d0 *q;
    Obj57_15d0 *o;

    best = 0;
    e = D_0054F750;
    for (i = 0; i < 8; i++, e++) {
        if (e->obj == 0) break;
        if (best == 0 || best->age > e->age) best = e;
    }
    if (i >= 8) {
        func_00137418(best->obj, 12.0f);
        best->obj->slot = 0;
        e = best;
    }
    q = func_00147840(owner);
    o = func_00124218(D_003514E8[q->b3].id);
    o->f40 = o->f44 = o->f48 = e->f20 = D_003514E8[q->b3].f4;
    e->owner = owner;
    e->obj = o;
    e->x0 = 0;
    e->f24 = 1.0f;
    e->age = D_0054F740++;
    e->x2c = 0;
    e->x34 = type;
    o->slot = e;
    o->flags |= 0x20;
    func_002675a8(o->v10, pos);
    o->f20 = func_00176850() * 10.0f - 5.0f;
    o->f28 = func_00176850() * 10.0f - 5.0f;
    switch (type) {
    case 0:
        o->f24 = func_00176850() * 10.0f + -30.0f;
        break;
    case 1:
        o->f24 = func_00176850() * 10.0f + -20.0f;
        e->f30 = 1.0f;
        break;
    }
    return func_0014f658(o, 20);
}

#include "common.h"
#include "data/bss_0053.h"
/* Hand-matched functions near 0x13C000-0x149000 (worker 33).
 * Built without strict aliasing (several of these need the reloads). */

typedef struct { f32 x, y, z, w; } V4f;
typedef struct { s32 x, y, z; } V3i;

/* ---- save data (D_00304BE8), shared with h7 ---- */
typedef struct {
    u8 lv;
    u8 x1;
    u8 x2;
    u8 x3;
    u8 pad04[0x21 - 0x4];
    u8 nslot;
    u8 slot[0x38 - 0x22];
    s16 x38;
    u8 pad3a[2];
    s32 exp;
    u8 name[0x30];
    u8 bits;
    u8 pad71[3];
} W7Member;

typedef struct {
    u8 pad000[4];
    W7Member m[10];
    u8 x48c;
    u8 x48d;
    u8 party[4];
    u8 pad492[0x499 - 0x492];
    u8 inv[0x599 - 0x499];
    u8 list599[0x30];
    u8 pad5c9[0x5CC - 0x5C9];
    u32 bits5cc[(0x7D0 - 0x5CC) / 4];
    s8 x7d0[7];
    u8 pad7d7[0x844 - 0x7D7];
    s8 x844[3];
    u8 pad847[0x878 - 0x847];
    u64 x878;
} W7Save;

extern W7Save *D_00304BE8;

/* ---- actor object ---- */
typedef struct Eff154 { u8 pad[0x10]; u8 *p10; u32 w14; } Eff154;
typedef struct S130 { u8 pad[0x5C]; u8 b5c; } S130;
typedef struct {
    u8 pad[0x30];
    u64 d30;
    u8 pad38[8];
    V4f p;
    f32 f50;
    f32 f54;
    u8 pad58[4];
    s32 w5c;
    u8 pad60[0x40];
    V4f va0;
    f32 fb0;
    f32 fb4;
    f32 fb8;
    f32 fbc;
    u8 padc0[0x154 - 0xC0];
    Eff154 *p154;
    f32 f158;
} Sub148;
typedef struct {
    u32 flags;
    s32 w4;
    u8 pad8[0x8];
    V4f pos;
    u8 pad20[0x88 - 0x20];
    u32 w88;
    u8 pad8c[0x130 - 0x8C];
    S130 *p130;
    u8 pad134[0x148 - 0x134];
    Sub148 *p148;
    u8 pad14c[0x1CC - 0x14C];
    u32 w1cc;
    u8 pad1d0[0x2A0 - 0x1D0];
    V4f v2a0;
    V4f v2b0;
    f32 f2c0;
    u8 pad2c4[0x2D0 - 0x2C4];
    u32 w2d0;
    u8 pad2d4[0x2F0 - 0x2D4];
    V4f v2f0;
    f32 f300;
    f32 f304;
    u8 pad308[0x314 - 0x308];
    u16 h314;
    u8 pad316[0x39E - 0x316];
    u8 b39e;
    u8 pad39f[0x3C4 - 0x39F];
    f32 f3c4;
} ObjF3;

/* ---- level/stat block (o->p6c) ---- */
typedef struct {
    u32 flags;
    u8 pad4[0x38];
    s32 w3c;
    s32 w40;
    s32 w44;
    s32 w48;
    s32 w4c;
    s32 w50;
    u8 pad54[0x68 - 0x54];
    s32 w68;
    u8 pad6c[4];
    s32 w70;
    u8 pad74[4];
    f32 f78[16];
    s32 wb8;
    u8 bbc;
    u8 padbd;
    u16 hbe;
    u16 hc0;
    u16 hc2;
    f32 fc4;
    void *pc8;
    u8 padcc[6];
    u16 hd2;
    u8 padd4[4];
    s32 wd8;
    f32 fdc;
} Lv;
typedef struct { u8 pad[0x6C]; Lv *p6c; } Pl;

typedef struct {
    s32 w0;
    s32 w4;
    s32 w8;
    u16 hc;
    u8 pade[2];
    u16 h10;
    u8 pad12[2];
    s32 w14;
    f32 f18;
    s32 w1c;
    u16 h20;
    u8 pad22[2];
    f32 f24;
    s32 a28[16];
    s32 w68;
} LvInit;

/* ---- misc ---- */
typedef struct { V4f p; V4f d; V4f hit; s16 h30; s32 w34; u8 pad38[8]; } Ray;
typedef struct { u8 pad[0x350]; s32 a[4]; } Mdl;
typedef struct { Mdl *m; u8 pad[0xC]; } MdlEnt;
typedef struct { u8 x0, x1, x2; } Item;
typedef struct { u32 type:8; u32 id:16; u32 hi:8; s32 w4; } Cmd;
typedef struct { u8 id; u8 pad[3]; s32 w4; s32 w8; } Cmd8;
typedef struct { f32 x, y, z; s32 w; } V4;
typedef struct { u8 pad[0x88]; f32 f88; u8 pad8c[0xE8 - 0x8C]; f32 fe8; u8 padec[4]; f32 ff0; } Cfg;
typedef struct { u8 pad[0x54]; s8 b54; } Sub130;
typedef struct { u8 pad[0x130]; Sub130 *p130; } Obj130;
typedef struct { u8 pad[0x3C]; s32 w3c; s32 w40; } S6C;
typedef union {
    u64 x;
    struct { u64 lo:48; u64 b48:1; u64 hi:15; } d;
    struct { u32 lo0; u32 lo:5; u32 kind:2; u32 hi:25; } b;
} B370;
typedef struct {
    u8 pad0[6];
    u8 b6;
    u8 pad7[0x6C - 7];
    S6C *p6c;
    u8 pad70[0x144 - 0x70];
    s32 w144;
    u8 pad148[0x370 - 0x148];
    B370 f370;
} P141;
typedef struct { P141 *p; s32 x4; } A141;
typedef struct { void *p; s32 n; } Pair;
typedef struct { s32 ok; s32 a; s32 b; } R141;
typedef struct {
    u32 flags;
    u8 pad4[0xC];
    V4f pos;
    V4f v20;
    V4f v30;
    u8 pad40[0x150 - 0x40];
    f32 f150;
} O2cf0;
#include "data/types/nostrict_text_00140000_h33.h"
typedef struct { u8 pad[0x80]; s32 w80; } Blk;
typedef struct { f32 p; s32 id; } Drop;
typedef struct { s32 n[7]; Drop d[3]; } DropTbl;
typedef struct { u8 pad[0x10]; s16 h10; s16 st; LdHdr *hdr; void (*cb)(s32); s32 arg; } LdTask;
typedef struct { s16 h0; s16 h2; } Prc;
typedef struct { f32 m[4][4]; u8 buf[0x3C]; s32 w7c; s32 w80; s32 w84; } MdlBlk;
typedef struct { V4f *pos; V3i *rot; } RotObj;
typedef struct {
    union { u64 d; struct { u32 lo; u8 b4; u8 b5; s16 h6; } s; } u;
    s32 w8;
    f32 fc;
    V4f v10;
    V4f v20;
} Eff;
typedef struct { u8 pad[0x18]; void **p18; } Blk7c;
typedef struct { u8 pad[0x68]; s32 w68; u8 pad6c[0x1C]; u32 w88; } Act;

/* ---- data ---- */
extern Cfg *D_00308CDC;
extern u32 D_002C5958;
extern u32 D_002C5960;
extern u32 D_002C5AD4;
extern f32 D_002BBDFC;
extern V4f D_002C58A0;
extern Pl *D_002E26A0;
extern f32 D_00304D54;
extern u32 D_00304B78;
extern MdlEnt D_003044E0[];
extern s32 D_002BC128;
extern s32 D_002BC130;
extern u32 D_002E27C8;
extern Snd *D_0052EB58;
extern Snd D_0052EB50;
extern s32 D_00531B64;
extern Blk *D_00531B60; /* src/data/bss_0053.c: B3Col *D_00531B60 */
extern f32 D_00306840;
extern f32 D_00306844;
extern f32 D_00306848;
extern LdEnt D_00531B70[128];
extern u8 D_00531F70[];
u8 D_00531F80[0xc00] ALIGNED(64);
extern s32 D_00532B80;
extern Ent32 D_00532B90[128];
extern s32 D_00533B90;
extern u16 D_00307226[];
extern u16 D_003085D8[];
u8 D_0054C160[0x50] ALIGNED(32);

/* ---- functions ---- */
Item *func_00147840(s32);
s32 func_00133000(ObjF3 *, s32);
void func_00130340(ObjF3 *, s32, f32);
void func_00130578(ObjF3 *, s32, f32);
void func_001333e0(ObjF3 *, s32, s32 *);
void func_0014cce0(ObjF3 *, f32);
void func_00267560(V4f *, V4f *, f32);
void func_00137330(s32, ObjF3 *, s32);
u16 *func_001478c8(s32);
s32 func_0012f040(s32, s32);
void func_0013ecf8(s32, s32 *, V4 *);
void func_002675a8(V4f *, V4f *);
void func_0013e1f8(Obj130 *, V4f *);
s32 func_001375d8(Obj130 *);
s32 func_0013f108(Obj130 *);
void func_001271b0(Obj130 *, V4f *);
void func_00159978(Obj130 *, V4f *);
void func_001707d0(Obj130 *, V4f *);
void func_002673b8(V4f *, V4f *);
void func_0013e558(Obj130 *, V4f *);
void func_00267530(V4f *, V4f *, V4f *);
void func_00121fc4(V4f *, V4f *);
s32 func_001375f0(ObjF3 *);
s32 func_0013f478(ObjF3 *, s32);
void func_0014f658(ObjF3 *, s32);
s32 func_0013f330(ObjF3 *, s32);
void func_00130398(ObjF3 *, s32, f32);
void func_00267518(V4f *, V4f *, V4f *);
void func_0014cc88(ObjF3 *, f32);
s32 func_0013c968(s32, s32);
void func_0012bce0(s32, s32, s32, Pair *, s32);
void func_002458a0(V4f *, s32);
void func_0013c548(s32);
void D_00F20000(s32, s32);
u8 *func_00147730(s32);
void func_00118668(Ray *);
void func_00105c98(s32, s32 *);
s32 func_00105bc0(s32, s32);
f32 func_00121840(V4f *, V4f *);
void func_00121860(V4f *, V4f *, V4f *, f32);
f32 atan2f(f32, f32);
void func_00137688(O2cf0 *, f32);
s32 func_001443a8(ObjF3 *);
void func_00153e80(ObjF3 *);
void func_00144958(ObjF3 *, V4f *);
void func_00150de0(s32);
void func_00176310(Eff154 *);
f32 func_00121b08(f32);
void func_0011d3c8(s32, s32, s32);
Blk *func_00122048(s32, s32);
s32 func_0011f130(Snd *, s32);
void func_001220b8(Blk *);
void func_00146188(s32, s32, s32);
f32 func_00176850(void);
void func_001515d0(s32, s32, s32);
s32 func_0011e248(s32);
void func_001ed658(s32, u8 *, s32);
s32 func_001ed220(s32, u8 *, s32);
s32 func_001ecfd8(void);
LdTask *func_0011f090(u8 *, s32, s32 (*)(LdTask *));
void func_00147338(s32, s32);
void func_00146928(s32);
void func_0011efa8(u8 *, u8 *, s32, s32);
s32 func_0011ef38(void (*)(void));
Prc *func_0011ef10(s32, void (*)(void));
void func_001474a0(void);
s32 func_001473a8(s32, s32, V4f *);
void *func_00176488(s32, u8 *, s32, s32);
s32 func_001765f8(void *);
s32 func_00162368(s32, s32);
s32 func_001320a8(s32);
u8 *func_001623e0(s32);
void sceVu0CopyMatrix(void *, void *);
void func_00147a68(void);
void func_00121a10(s32, V4f *);
void func_00121a78(V4f *, V4f *);
Eff *func_00148438(void *, s32);
void func_001315c0(s32, s32, V4f *, f32);
Blk7c *func_00147c98(s32, s32, s32);
Eff *func_00148570(Blk7c *, s32, s32);
void func_001318e8(Act *, s32, V4f *);

s32 func_0013c9e0(s32 item, u32 who) {
    if (item & 0x400) return 255;
    if (who < 10) {
        W7Member *m = &D_00304BE8->m[who];
        if (func_00147840(item)->x2 == 0) {
            s32 k;
            for (k = 0; k < m->nslot; k++) {
                if (m->slot[k] == 0) {
                    m->slot[k] = item;
                    return who;
                }
            }
        }
    }
    if (D_00304BE8->inv[item] < 99) {
        D_00304BE8->inv[item]++;
        return 12;
    }
    return 255;
}

s32 func_0013cae8(u32 who, s32 item) {
    if (who < 10) {
        W7Member *m = &D_00304BE8->m[who];
        s32 k;
        for (k = 0; k < m->nslot; k++) {
            if (m->slot[k] == item) {
                m->slot[k] = 0;
                return who;
            }
        }
    }
    if (D_00304BE8->inv[item] != 0) {
        D_00304BE8->inv[item]--;
        return 12;
    }
    return 255;
}

void func_0013e978(ObjF3 *o, Cmd *c) {
    u8 t = *(u8 *)c;
    if (t != 0) {
        if (t == 2) {
            if (func_00133000(o, c->id) == 0) return;
            if (c->id == 0) {
                f32 z = 0.0f;
                func_00130340(o, 0x1000083, z);
                func_00130578(o, 0x8A, z);
            } else {
                func_00130340(o, (c->id + 0x83) | 0x1000000, 0.0f);
            }
            func_00130578(o, 0x40000006, 8.0f);
            func_001333e0(o, c->id, &c->w4);
            func_0014cce0(o, D_00308CDC->fe8);
            func_00267560((V4f *)((u8 *)o + 0x3C0), (V4f *)((u8 *)o + 0x3C0), D_00308CDC->ff0);
            return;
        }
        func_00137330(c->w4, o, t);
    }
}

void func_0013ed88(s32 o, Cmd8 *c, V4 *v) {
    if (*func_001478c8(c->id) & 2) {
        if (func_0012f040(c->w4, c->w8)) {
            func_0013ecf8(o, &c->w4, v);
            return;
        }
        if (v->x == 0.0f && v->z == 0.0f) {
            func_002675a8((V4f *)v, (V4f *)(o + 0x30));
        }
        v->w = 0;
    }
}

void func_0013f198(Obj130 *o) {
    V4f a, b;
    func_0013e1f8(o, &a);
    if (!func_001375d8(o) && !func_0013f108(o)) {
        if (o->p130->b54 == 0) {
            func_001271b0(o, &a);
        } else if ((D_002C5958 >> 17) & 1) {
            func_00159978(o, &a);
        } else if (!((D_002C5960 >> 3) & 1)) {
            func_001707d0(o, &a);
        } else if (D_002C5AD4 & 0x8000) {
            func_001271b0(o, &a);
        }
    }
    func_002675a8(&b, &a);
    b.y = 0;
    func_002673b8(&b, &b);
    b.y = a.y;
    b.w = a.w;
    func_0013e558(o, &b);
}

void func_0013f358(ObjF3 *o) {
    V4f t;
    func_002675a8(&o->p148->p, &o->v2f0);
    o->p148->f50 = o->f300;
    o->p148->f54 = o->p148->p.y + o->f304;
    o->p148->w5c = o->h314;
    func_00267530(&t, &o->v2f0, &o->pos);
    t.y = 0;
    func_00121fc4(&t, &t);
    func_00267560(&t, &t, o->p148->f50 + o->f2c0);
    o->pos.x = o->p148->p.x - t.x;
    o->pos.z = o->p148->p.z - t.z;
    o->flags |= 0x200000;
    o->w1cc &= ~1;
}

s32 func_0013f510(ObjF3 *o, s32 a) {
    if (func_001375f0(o) && func_0013f478(o, a)) {
        f32 lim;
        o->p148->f50 += D_002BBDFC;
        lim = 12.0f;
        if (!(o->f300 > 25.0f)) lim = 6.0f;
        if (lim < o->p148->f50) {
            f32 z;
            z = 0.0f;
            func_0014f658(o, 13);
            func_00130398(o, func_0013f330(o, 28) | 0x1000000, z);
            func_00130578(o, func_0013f330(o, 27) | 0x40000000, z);
            return 1;
        }
        return 0;
    }
    o->p148->f50 = 0.0f;
    return 0;
}

void func_0013f770(ObjF3 *o, V4f *v) {
    V4f t;
    f32 s;
    u32 fl = 0;
    if (v->y < 0.0f) {
        s = 20.0f;
        func_00130398(o, 5, 0.0f);
        func_00130578(o, 6, 0.0f);
    } else if (v->w > 0.0f) {
        s = 15.0f;
        func_00130398(o, 5, 0.0f);
        func_00130578(o, 6, 0.0f);
    } else {
        s = 5.0f;
        fl = 0x10000;
        func_00130398(o, 6, 12.0f);
    }
    v->y = 0.0f;
    func_00267560(&t, (V4f *)((u8 *)o + 0x30), -1.0f);
    func_00267518(v, v, &t);
    func_002673b8(v, v);
    v->w = 2.0f;
    func_0014cc88(o, s);
    o->flags |= fl;
}

void func_00140db8(ObjF3 *o, V4f *v) {
    f32 s;
    u32 fl = 0;
    if (v->y < 0.0f) {
        s = 20.0f;
        func_00130398(o, 5, 0.0f);
        func_00130578(o, 6, 0.0f);
    } else if (v->w > 0.0f) {
        s = 15.0f;
        func_00130398(o, 5, 0.0f);
        func_00130578(o, 6, 0.0f);
    } else {
        s = 5.0f;
        fl = 0x10000;
        func_00130398(o, 6, 12.0f);
    }
    v->y = 0.0f;
    func_00267518(v, v, (V4f *)o->p148);
    func_002673b8(v, v);
    v->w = 2.0f;
    func_0014cc88(o, s);
    o->flags |= fl;
}

s32 func_00141348(A141 *a, R141 *r) {
    Pair pr[2];
    if (func_0013c968(10, 0) > 0 && a->p->b6 == 3 && a->p->f370.b.kind != 1) {
        r->ok = 1;
        r->a = a->p->p6c->w3c;
        r->b = a->p->p6c->w40;
        if ((s32)(a->p->f370.x >> 48) & 1) {
            if (a->p->w144) {
                pr[0].p = &a->x4;
                pr[0].n = 4;
                pr[1].p = &r;
                pr[1].n = 4;
                func_0012bce0(a->p->w144, 3, 2, pr, 0);
            }
        }
    } else {
        r->ok = 0;
    }
    return r->ok;
}

void func_001417a0(V4f *p, s32 n) {
    V4f t;
    if (D_002E26A0 == 0 || D_002E26A0->p6c->w3c > 0) {
        func_002675a8(&t, p);
        t.w = 1.0f;
        n = n * D_00304D54 + 0.5f;
        func_002458a0(&t, n);
        func_0013c548(n);
        if ((D_00304B78 & 0xF) == 9) {
            D_00F20000(5, n);
        }
    }
}

void func_00141f10(Pl *o, LvInit *in) {
    Lv *s = o->p6c;
    s32 i;
    s32 v = in->w0;
    s->w48 = 0;
    s->w40 = v;
    s->w3c = v;
    s->w44 = 0;
    s->hbe = 0;
    s->w4c = func_00147730(in->w4)[0];
    s->w50 = func_00147730(in->w8)[1];
    s->hc0 = in->hc;
    s->hc2 = in->h10;
    s->wb8 = 0;
    s->bbc = 0;
    s->fc4 = in->f18;
    s->w68 = in->w1c;
    s->hd2 = in->h20;
    s->wd8 = in->w14;
    s->fdc = in->f24;
    for (i = 0; i < 16; i++) {
        s->f78[i] = in->a28[i] / 100.0f;
    }
    s->w70 = in->w68;
}

s32 func_00142388(V4f *p, s32 *out) {
    Ray r;
    s32 i;
    func_002675a8(&r.p, p);
    r.p.w = 1.0f;
    r.d.x = 0;
    r.d.y = 100000.0f;
    r.d.z = 0;
    r.d.w = 1.0f;
    func_00118668(&r);
    if (r.h30 >= 0) {
        if (r.w34 == -1) {
            func_00105c98(r.h30, out);
        } else {
            Mdl *m = D_003044E0[r.w34].m;
            for (i = 0; i < 4; i++) {
                out[i] = m->a[i];
            }
        }
        return func_00105bc0(r.w34, r.h30);
    }
    return 0;
}

f32 func_00142cf0(O2cf0 *o, V4f *tg, f32 spd, f32 r) {
    V4f t;
    f32 d;
    func_00267530(&t, tg, &o->pos);
    if (!(o->flags & 0x10)) t.y = 0;
    func_00121fc4(&t, &t);
    if (r == 0.0f) {
        f32 k;
        r = func_00121840(&o->v30, &t);
        k = t.w / spd * 0.3f;
        if (k > 1.0f) r /= k;
    }
    d = t.w;
    if (d < spd) spd = d;
    func_00121860(&o->v30, &t, &t, r);
    o->f150 = atan2f(t.x, t.z);
    func_00137688(o, o->f150);
    t.w = spd;
    func_002675a8(&o->v20, &t);
    return d;
}

s32 func_00144510(ObjF3 *o, V4f *v) {
    s32 k;
    f32 f;
    if (D_002BC128 == 13 && D_002BC130 == 8) return 0;
    if (!func_001443a8(o)) return 0;
    func_0014f658(o, 17);
    func_00267560(&o->p148->va0, v, v->w * 0.5f);
    o->p148->va0.y = o->f3c4;
    f = 16.0f;
    o->f3c4 = o->f3c4 / D_002BBDFC;
    k = 45;
    if (v->w > 0.0f) o->f3c4 = o->f3c4 * 0.19999999f;
    if (o->w88 & 0x20) {
        func_00153e80(o);
    } else {
        func_00130398(o, k, f);
        o->flags &= ~4;
        v->w = 0.0f;
        func_00144958(o, v);
    }
    return 1;
}

void func_00145080(s32 on, s32 n) {
    f32 f = n;
    Snd *p;
    D_00531B64 = on;
    D_00306840 = f;
    p = D_0052EB58;
    if (on) {
        for (; p; p = p->next) {
            if (p->st < 2) {
                p->st = 4;
                p->f18 = f;
            }
        }
    } else {
        for (; p; p = p->next) {
            if (p->st == 4) {
                p->st = 5;
                p->f18 = f;
            }
        }
    }
    func_00150de0(on);
}

void func_001452a0(ObjF3 *o) {
    Eff154 *e = o->p148->p154;
    s32 k;
    if (e == 0) return;
    k = e->w14 & 3;
    if (k != 1) {
        o->p148->p154 = 0;
        return;
    }
    if (!(o->flags & 1)) {
        func_00176310(e);
        o->p148->p154 = 0;
        func_0011d3c8(168, o->w4 + 1, 60);
        return;
    }
    o->p148->f158 = func_00121b08(o->p148->f158);
    if (!(o->p148->f158 <= 0.0f) && !(D_002C5958 & 0x104000)) return;
    *o->p148->p154->p10 = k;
    func_0011d3c8(168, o->w4 + 1, 120);
}

s32 func_001460b8(void) {
    Snd *p;
    Blk *b = func_00122048(160, 16);
    *(Blk *volatile *)&D_00531B60 = b;
    b->w80 = 1;
    if (func_0011f130(&D_0052EB50, 0) >= 205) {
        for (p = D_0052EB50.next; p; p = p->next) {
            if (p->st == 1) {
                p->st = 3;
                p->f18 = 12.0f;
                break;
            }
        }
    }
    func_001220b8(D_00531B60);
    return 0;
}

void func_00146380(DropTbl *t, s32 a, s32 b) {
    s32 i, j, n;
    if (D_00531B64) return;
    for (i = 0; i < 7; i++) {
        n = t->n[i] * D_00306844;
        for (j = 0; j < n; j++) {
            func_00146188(i, a, b);
        }
    }
    for (i = 0; i < 3; i++) {
        f32 p = t->d[i].p * D_00306848;
        if (func_00176850() < p) {
            func_001515d0(t->d[i].id, a, b);
        }
    }
}

s32 func_00146998(LdTask *t) {
    u8 *p;
    switch (t->st) {
    case 0:
        if (func_0011e248(0) == 0) {
            p = t->hdr->data;
            if (t->hdr->n0) {
                func_001ed658(t->h10, p, t->hdr->n0);
                p += t->hdr->n4;
            }
            func_001ed220(t->h10, p, t->hdr->n8);
            t->st++;
        }
        return 8;
    case 1:
        if (func_001ecfd8() == 0) {
            if (t->cb) t->cb(t->arg);
            return 4;
        }
        return 8;
    }
    return 8;
}

s32 func_00146a68(LdHdr *h, s32 id, void (*cb)(s32), s32 arg) {
    s32 i;
    LdTask *t;
    for (i = 0; i < 128; i++) {
        if (D_00531B70[i].id == id && D_00531B70[i].h == h) {
            cb(arg);
            return 1;
        }
    }
    for (i = 0; i < 128; i++) {
        if (D_00531B70[i].h == 0) {
            D_00531B70[i].id = id;
            D_00531B70[i].h = h;
            break;
        }
    }
    t = func_0011f090(D_00531F70, 0, func_00146998);
    t->arg = arg;
    t->h10 = id;
    t->hdr = h;
    t->cb = cb;
    t->st = 0;
    {
        s32 *pc = &D_00532B80;
        (*pc)++;
    }
    return 1;
}

Ent32 *func_00146bd0(s32 n, s32 id) {
    s32 i;
    Ent32 *e;
    if (n <= 0) return 0;
    if (id > 0) {
        func_00147338(n, id);
    } else {
        s32 *pc = &D_00533B90;
        id = (*pc)++;
    }
    e = D_00532B90;
    for (i = 0; i < 128; i++, e++) {
        if (!(e->u.w.lo & 1)) {
            e->n = n;
            e->u.f.used = 1;
            e->u.f.b1 = 1;
            e->u.f.b2 = 0;
            e->u.w.id = id;
            return e;
        }
    }
    return 0;
}

s32 func_00147138(ObjF3 *o, s32 v) {
    u32 k = o->p130->b5c;
    if (v == 4) {
        v = D_003085D8[k];
        if (v == 0) return 0;
    } else {
        u16 t = D_00307226[o->b39e + (D_002BC128 * 8 + k) * 15];
        if (t == 0) return 0;
        v += t;
    }
    return func_001473a8(v, o->w4 + 1, &o->pos);
}

void func_00147628(void) {
    s32 i;
    for (i = 0; i < 128; i++) D_00532B90[i].u.f.used = 0;
    for (i = 127; i >= 0; i--) D_00531B70[i].h = 0;
    func_00146928(-3);
    func_00146928(-4);
    func_00146928(-5);
    func_00146928(-6);
    func_00146928(-7);
    D_00533B90 = 1;
    func_0011efa8(D_00531F70, D_00531F80, 32, 96);
    D_00532B80 = 0;
    if (!func_0011ef38(func_001474a0)) {
        func_0011ef10(0x23668, func_001474a0)->h2 = -1;
    }
}

void *func_00147b08(s32 a, s32 b, s32 c) {
    s32 r;
    if (!func_00176488(a, D_0054C160, 0, 20000)) return 0;
    r = func_001765f8(D_0054C160);
    if (r >= 0) {
        MdlBlk *m = (MdlBlk *)(D_0054C160 - 0x40);
        r = func_00162368(c, r & 0xFFF);
        m->w80 = r;
        m->w7c = c;
        m->w84 = func_001320a8(b);
        sceVu0CopyMatrix(m, func_001623e0(c) + (r << 6));
        func_0011ef10(0x21728, func_00147a68)->h2 = -1;
    }
    return D_0054C160;
}

void func_00147d50(RotObj *o, s32 m) {
    V4f r;
    func_00121a10(m, &r);
    o->rot->x = (u16)(s32)(r.x / 6.2831855f * 65536.0f);
    o->rot->y = (u16)(s32)(r.y / 6.2831855f * 65536.0f);
    o->rot->z = (u16)(s32)(r.z / 6.2831855f * 65536.0f);
}

void func_00147e08(RotObj *o, V4f *m) {
    V4f r;
    func_00121a78(m, &r);
    o->rot->x = (u16)(s32)(r.x / 6.2831855f * 65536.0f);
    o->rot->y = (u16)(s32)(r.y / 6.2831855f * 65536.0f);
    o->rot->z = (u16)(s32)(r.z / 6.2831855f * 65536.0f);
    func_002675a8(o->pos, m + 3);
}

Eff *func_001484c8(V4f **o, s32 a, s32 b, f32 f) {
    Eff *e = func_00148438(o, a);
    if (!e) return 0;
    e->w8 = b;
    e->u.s.b4 = 1;
    e->fc = f;
    func_002675a8(&e->v10, &D_002C58A0);
    func_001315c0(a, b, &e->v20, f);
    func_002675a8(*o, &e->v20);
    return e;
}

Blk7c *func_00148968(s32 a, s32 b, s32 fl) {
    Blk7c *k = func_00147c98(b, fl, 20000);
    s32 r;
    Eff *e;
    if (k) {
        *k->p18 = (void *)a;
        r = func_001765f8(k);
        if (r >= 0) {
            e = func_00148570(k, a, r);
            if (e) {
                if (fl & 0x800) e->u.s.h6 = -1;
                if (fl & 0x1000) e->u.d |= 1;
            }
        } else if (fl & 0x800) {
            e = func_00148438(k, a);
            e->u.s.h6 = -1;
            e->u.s.b4 = 0;
        }
    }
    return k;
}

Blk7c *func_00148a60(Act *o, s32 fl) {
    Blk7c *k = func_00147c98(o->w68, fl, 20000);
    s32 r;
    Eff *e;
    V4f m[4];
    if (k) {
        *k->p18 = o;
        r = func_001765f8(k);
        if (r >= 0) {
            if (o->w88 & 1) {
                func_001318e8(o, r & 0xFFFEFFFF, m);
                func_00147e08((RotObj *)k, m);
                return k;
            }
            e = func_00148570(k, (s32)o, r);
            if (e) {
                if (fl & 0x800) e->u.s.h6 = -1;
                if (fl & 0x1000) e->u.d |= 1;
            }
        } else if (fl & 0x800) {
            e = func_00148438(k, (s32)o);
            e->u.s.h6 = -1;
            e->u.s.b4 = 0;
        }
    }
    return k;
}

/* func_00141468 and func_00141540 only match with func_00141448 defined
 * above them. */
typedef struct { u8 b0; u8 b1; u8 b2; u8 b3; } S1C8;
typedef struct { u32 flags; u8 pad4[0x38]; s32 w3c; s32 w40; u8 pad44[0xC8 - 0x44]; S1C8 *pc8; } St6C;
typedef struct { u8 pad[0x44]; s32 w44; s32 w48; u8 pad4c[0xC8 - 0x4C]; S1C8 *pc8; } St6Cb;
extern St6C D_00304C70;
typedef struct { u8 pad[0x4C]; u16 h4c; } S130b;
typedef struct { u8 pad[0x6C]; St6C *p6c; u8 pad70[0x18]; u32 w88; u8 pad8c[0x130 - 0x8C]; S130b *p130; } O1468;

s32 func_00141448(s32 a, s32 b, s32 max) {
    s32 v = a + b;
    if (max < v) {
        v = max;
    } else if (v < 0) {
        v = 0;
    }
    return v;
}

s32 func_00141468(O1468 *o, s32 x) {
    St6C *s = o->p6c;
    s32 v;
    if (s == 0 || s == &D_00304C70) return 0;
    v = func_00141448(s->w3c, x, s->w40);
    if ((o->w88 & 0x20) && !func_0013c968(9, o->p130->h4c)) {
        v = s->w3c + (s32)((v - s->w3c) * D_00308CDC->f88);
    }
    s->w3c = v;
    s->flags &= ~4;
    if (s->pc8) s->pc8->b1 = v;
    return v;
}

s32 func_00141540(O1468 *o, s32 x) {
    St6Cb *s = (St6Cb *)o->p6c;
    s32 v;
    if (s == 0 || s == (St6Cb *)&D_00304C70) return 0;
    v = func_00141448(s->w44, x, s->w48);
    if ((o->w88 & 0x20) && !func_0013c968(9, o->p130->h4c)) {
        v = s->w44 + (s32)((v - s->w44) * D_00308CDC->f88);
    }
    s->w44 = v;
    if (s->pc8) s->pc8->b3 = v;
    return v;
}
#include "data/bss_0053_mixed.h"
#include "data/data_002B.h"
#include "data/data_0030.h"
#include "data/pieces/D_002C5958.h"
#include "data/pieces/D_002BBDFC.h"
#include "data/pieces/D_002BC128.h"

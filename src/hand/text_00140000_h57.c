#include "common.h"
#include "data/bss_0054.h"

typedef struct { u8 pad0[0x100]; u64 f100; } Sub57_c6c0;
typedef struct {
    u8 pad0[0x3c];
    f32 f3c;
    u8 pad40[0x148-0x40];
    Sub57_c6c0 *o148;
    u8 pad14c[0x150-0x14c];
    f32 f150;
    u8 pad154[0x170-0x154];
    f32 f170;
    u8 pad174[0x3c0-0x174];
    f32 v3c0[4];
} Obj57_c6c0;
typedef struct { u8 pad0[8]; f32 f8; u8 pad0c[0x14-0xc]; f32 f14; f32 f18; } Prm57_cee8;
typedef struct {
    s32 flags;
    u8 pad4[0x14-4];
    f32 f14;
    u8 pad18[0x20-0x18];
    f32 v20[3];
    f32 f2c;
    u8 pad30[0x6c-0x30];
    Prm57_cee8 *prm;
    u8 pad70[0x124-0x70];
    f32 f124;
    u8 pad128[0x3b0-0x128];
    f32 f3b0;
    f32 f3b4;
    f32 f3b8;
    u8 pad3bc[4];
    f32 v3c0[4];
} Obj57_cee8;
typedef struct { u8 pad0[0x100]; u64 f100; } Sub57_dd48;
typedef struct {
    u8 pad0[0x148];
    Sub57_dd48 *o148;
    u8 pad14c[0x3b0-0x14c];
    f32 f3b0;
} Obj57_dd48;
typedef struct { u8 pad0[0xcc]; f32 fcc; } Prm57_df60;
typedef struct {
    u8 pad0[0x20];
    f32 v20[4];
    f32 v30[4];
    u8 pad40[0x6c-0x40];
    Prm57_df60 *prm;
    u8 pad70[0x164-0x70];
    s32 i164;
    u8 pad168[0x170-0x168];
    f32 f170;
    u8 pad174[0x178-0x174];
    s32 i178;
    u8 pad17c[0x3c0-0x17c];
    f32 v3c0[4];
    u8 pad3d0[0x440-0x3d0];
    u64 f440;
} Obj57_df60;
typedef struct { u8 pad0[8]; f32 f8; } Tab57_e160;
typedef struct {
    u8 pad0[4];
    s32 i4;
    u8 pad8[0x14-8];
    f32 f14;
    u8 pad18[0x20-0x18];
    f32 v20[1];
    f32 f24;
    u8 pad28[0x2c-0x28];
    f32 f2c;
    u8 pad30[0x3c0-0x30];
    f32 v3c0[3];
    f32 f3cc;
} Obj57_e160;
typedef struct { s32 x0; u8 pad4[0x48-4]; s16 x48; u8 pad4a[0x58-0x4a]; u8 x58; } Ent57_f028;
typedef struct { u8 id; u8 b1; u8 b2; u8 b3; u8 b4; } BoxHd57_f1b8;
typedef union { u64 flags; BoxHd57_f1b8 c; } BoxU57_f1b8;
typedef struct { BoxU57_f1b8 u; u8 pad8[8]; f32 lo[4]; f32 hi[4]; } Box57_f1b8;
typedef struct { u8 pad0[3]; u8 x3; u8 n; u8 x5; u8 pad6[0xa]; Box57_f1b8 box[1]; } BoxSet57_f1b8;
#include "data/types/text_00140000_h57.h"
typedef struct { u8 pad0[8]; f32 f8; } Prm57_f410;
typedef struct {
    s32 flags;
    u8 pad4[0x2c-4];
    f32 f2c;
    u8 pad30[0x6c-0x30];
    Prm57_f410 *prm;
    s32 i70;
    u8 pad74[0x164-0x74];
    s32 i164;
    u8 pad168[0x178-0x168];
    s32 i178;
    u8 pad17c[0x378-0x17c];
    s32 i378;
    u8 pad37c[0x39e - 0x37c];
    u8 b39e;
    u8 pad39f[0x3d0-0x39f];
    s32 i3d0;
    u8 pad3d4[0x440-0x3d4];
    u64 f440;
} Obj57_f410;
typedef struct { u8 pad0[0x2c]; f32 f2c; f32 f30; f32 f34; f32 f38; } Prm57_fab0;
typedef struct {
    u8 pad0[0x6c];
    Prm57_fab0 *prm;
    u8 pad70[0xd0-0x70];
    f32 md0[16];
} Obj57_fab0;
typedef struct { u8 pad0[0x2c]; f32 f2c; f32 f30; f32 f34; f32 f38; } Prm57_fc68;
typedef struct {
    u8 pad0[0x6c];
    Prm57_fc68 *prm;
    u8 pad70[0xd0-0x70];
    f32 md0[16];
    u8 pad110[0x460-0x110];
    f32 v460[4];
} Obj57_fc68;
typedef struct { u8 x[20]; } Col57_07d0;
typedef struct { u8 pad0[4]; u8 n[4]; u8 pad8[8]; Col57_07d0 *cols[4]; } ColSet57_07d0;
typedef struct { u8 pad0[0x54]; s8 kind; } Info57_07d0;
typedef struct { u8 pad0[0xc]; f32 fc; } Sub57_07d0;
typedef struct { u8 pad0[0x140]; s32 i140; } Sub148_07d0;
typedef struct {
    u8 pad0[0x130];
    Info57_07d0 *info;
    ColSet57_07d0 *cs;
    u8 pad138[0x144-0x138];
    Sub57_07d0 *o144;
    Sub148_07d0 *o148;
    u8 pad14c[0x164-0x14c];
    u32 i164;
} Chr57_07d0;
typedef struct { u8 pad0[0x54]; s8 kind; } Info57_0930;
typedef struct { u8 pad0[0xc]; f32 fc; } Sub57_0930;
typedef struct { u8 pad0[4]; f32 f4; } Ret57_0930;
typedef struct { u8 pad0[8]; f32 f8; } Prm57_0930;
typedef struct Chr57_0930 {
    u8 pad0[0x10];
    f32 v10[4];
    u8 pad20[0x6c-0x20];
    Prm57_0930 *prm;
    u8 pad70[0x98-0x70];
    struct Chr57_0930 *o98;
    u8 pad9c[0x130-0x9c];
    Info57_0930 *info;
    u8 pad134[0x144-0x134];
    Sub57_0930 *o144;
    u8 pad148[0x3b0-0x148];
    f32 f3b0;
    f32 f3b4;
    f32 f3b8;
    u8 pad3bc[4];
    f32 v3c0[1];
    f32 f3c4;
    u8 pad3c8[4];
    f32 f3cc;
} Chr57_0930;

extern f32 D_002BBDFC;
extern f32 D_002C58A0[];
extern u32 D_002E3190;
extern s32 D_002E31B0[2];
extern s32 D_002E31B8;
extern u32 D_002C5958;
extern void *D_002E26A0;
extern s32 D_0054F448;
extern BoxSet57_f1b8 *D_00350D78;
extern s32 D_00350D7C;
extern s32 D_00350D80;
extern s32 D_0054F44C;
extern Grp57_f1b8 D_0054F438[];
extern Grp57_f1b8 D_0054F450[];
extern s32 D_002BC128;
extern s32 D_002BC130;
extern f32 D_002C58D0[];

f32 atan2f(f32, f32);
f32 func_00120c88(f32);
void func_00121fc4(f32 *, f32 *);
void func_00130398(void *, s32, f32);
void func_00137688(Obj57_c6c0 *, f32);
void func_00144650(Obj57_c6c0 *, f32 *);
void func_002675a8(f32 *, f32 *);
f32 func_00120c18(f32 *);
void func_0014cdc8(Obj57_cee8 *, f32 *);
void func_00267518(f32 *, f32 *, f32 *);
void func_00267560(f32 *, f32 *, f32);
void func_00267e90(f32 *, f32 *, f32);
f32 func_0012ec60(s32, s32, f32 *);
void func_001315c0(void *, s32, f32 *, f32);
void func_00267530(f32 *, f32 *, f32 *);
f32 func_00121748(f32 *, f32 *);
f32 func_00121b08(f32);
s32 func_001375f0(Obj57_df60 *);
void func_001376e8(void *, f32 *);
f32 func_00267390(f32 *, f32 *);
void func_00267370(f32 *, f32 *, f32 *);
Tab57_e160 *func_0014dab8(void);
s32 func_0012c8e8(Obj57_e160 *);
void func_00147410(s32, s32, Obj57_e160 *);
void func_00147278(s32, s32, s32);
f32 func_00176850(void);
f32 sinf(f32);
f32 cosf(f32);
s32 func_0014e5b8(f32 *);
void func_001426a8(f32 *, f32);
s32 func_0012f0f8(f32 *, f32 *, s32);
s32 func_0014ee88(void *);
Ent57_f028 *func_00132040(Ent57_f028 *);
s32 func_00123488(s32);
s32 func_00142240(s32);
s32 func_00124218(s32);
s32 func_0014f028(void);
s32 func_0011ef38(void *);
void func_0011ef10(s32, void *);
s32 func_0013c968(s32, s32);
s32 func_00142058(s32);
void func_0014f3d0(Obj57_f410 *);
void func_00130340(Obj57_f410 *, s32, f32);
void func_00130578(Obj57_f410 *, s32, f32);
void func_00146c98(Obj57_f410 *, s32);
void func_0012bd98(Obj57_f410 *, s32, s32, f32 *);
void func_0012ec88();
void func_002673f8(f32 *, f32 *);
void func_002672f8(f32 *, f32 *, f32 *);
void func_00267768(f32 *, f32 *, f32);
void func_00267810(f32 *, f32 *, f32);
f32 asinf(f32);
void func_002674f0(f32 *, f32 *, f32 *, f32);
void func_0015bad0(Chr57_07d0 *, Col57_07d0 *, f32 *);
s32 func_0015b998(f32 *, f32 *);
Chr57_07d0 *func_001230a0(Chr57_07d0 *);
s32 func_00123330(Chr57_07d0 *);
void func_00150678(Chr57_07d0 *, Chr57_07d0 *);
Ret57_0930 *func_0014cb90(Chr57_0930 *);
s32 func_0014f658(Chr57_0930 *, s32);

void func_0014c6c0(Obj57_c6c0 *o, f32 *v) {
    f32 t[4];
    f32 a;
    f32 lim;
    s32 id;

    if (v[3] > 0.0f) {
        a = func_00120c88(atan2f(v[0], v[2]) - o->f3c);
    } else {
        a = 0.0f;
    }
    if (o->f170 == 0.0f) {
        if (a > 0.523598730564117431640625f) {
            id = 115;
        } else if (a < -0.523598730564117431640625f) {
            id = 116;
        } else {
            func_002675a8(t, o->v3c0);
            t[1] = 0.0f;
            func_00121fc4(t, t);
            if (t[3] > 8.0f) id = 114;
            else id = 113;
        }
        func_00130398(o, id, 16.0f);
    }
    if ((s32)(o->o148->f100 >> 32) & 1) {
        lim = D_002BBDFC * 0.0174532905221f;
    } else {
        lim = D_002BBDFC * 0.0349065810442f;
    }
    if (lim < a) a = lim;
    else if (a < -lim) a = -lim;
    a = func_00120c88(a + o->f3c);
    func_00137688(o, a);
    o->f150 = a;
    func_00144650(o, v);
}

void func_0014cee8(Obj57_cee8 *o, f32 *v) {
    f32 d;

    if (o->flags & 0x1000) {
        o->f3b0 = o->f3b8 = 0.0f;
        o->f3b4 = o->f14;
        func_002675a8(v, D_002C58A0);
    } else {
        if (o->f2c > 0.0f) {
            d = func_00120c18(o->v3c0);
            func_00267560(v, o->v20, o->f2c * o->prm->f14);
            func_00267518(v, v, o->v3c0);
            v[1] = 0.0f;
            func_00121fc4(v, v);
            if (!(o->prm->f8 < d)) d = o->prm->f8;
            if (d < v[3]) v[3] = d;
            func_00267e90(v, v, v[3]);
        } else {
            func_00267560(v, o->v3c0, o->prm->f18);
        }
        func_002675a8(o->v3c0, v);
        func_00267e90(v, v, D_002BBDFC);
        o->f3b0 += D_002BBDFC;
        func_0014cdc8(o, v);
    }
    o->f3b4 += o->f124;
}

void func_0014dd48(Obj57_dd48 *o, s32 unused, f32 *v) {
    f32 b[4];
    f32 a[4];
    f32 h;
    f32 d;
    f32 t;

    if (v[3] > 0.0f) {
        if (v[3] < 0.799999967217f) v[3] = 8.0f;
        else v[3] = 16.0f;
    }
    if ((D_002E3190 >> 27) & 1) {
        v[1] = -8.0f;
    } else if ((D_002E3190 >> 28) & 1) {
        v[1] = 8.0f;
        goto skip;
    } else {
        v[1] = 0.0f;
    }
    if (o->o148) o->o148->f100 |= (u64)0x8000 << 19;
skip:
    if (D_002E31B8 >= 3 && v[3] > 0.0f && v[1] == 0.0f) {
        h = func_0012ec60(D_002E31B0[0], D_002E31B0[1], a);
        func_001315c0(o, 0x8003, b, 0.0f);
        func_00267530(a, a, b);
        if (func_00121748(a, v) > 0.5f) {
            d = (func_00120c18(a) - h - 200.0f) * 0.799999967217f;
            if (d > 0.0f) {
                t = a[1] / d * v[3];
                v[1] = t;
                if (t > 8.0f) v[1] = 8.0f;
                else if (t < -8.0f) v[1] = -8.0f;
            }
        }
    }
    o->f3b0 = func_00121b08(o->f3b0);
}

void func_0014df60(Obj57_df60 *o, f32 *v) {
    f32 t[4];
    f32 c[4];
    f32 spd;
    s32 id;

    if (v[0] != 0.0f || v[2] != 0.0f) {
        if (func_001375f0(o)) {
            o->prm->fcc = 0.0698131620884f;
        }
        func_001376e8(o, v);
    }
    spd = 16.0f;
    id = 117;
    if (v[3] > 0.0f) {
        if (v[3] > 8.0f) id = 119;
        else id = 118;
        func_002675a8(t, o->v3c0);
        t[1] = 0.0f;
        func_00121fc4(t, t);
        if (t[3] >= 8.0f && func_00267390(o->v30, t) < 0.866f) {
            id = 120;
            func_00267370(c, o->v30, t);
            if (!(c[1] < 0.0f)) id = 121;
            if ((u32)(o->i164 - 120) < 2) spd = 24.0f;
        }
    } else if (v[1] > 0.0f) {
        id = 123;
    } else if (v[1] < 0.0f) {
        id = 122;
    }
    if (func_001375f0(o) && !((o->f440 >> 33) & 1)) {
        if (id == 117) {
            if (o->i178) goto end;
        } else if (o->f170 > 0.0f) goto end;
        func_00130398(o, id, spd);
    }
end:
    func_002675a8(o->v20, v);
}

void func_0014e160(Obj57_e160 *o, f32 *v) {
    f32 d;
    f32 y;
    f32 tgt;
    Tab57_e160 *p;

    d = func_00120c18(o->v3c0);
    if (o->f2c > 0.0f) {
        func_00267560(v, o->v20, D_002BBDFC * 0.599999979138f);
        v[1] = 0.0f;
        func_00267518(o->v3c0, o->v3c0, v);
    }
    func_002675a8(v, o->v3c0);
    v[1] = 0.0f;
    func_00121fc4(v, v);
    if (v[3] > o->f2c) {
        if (o->f2c < d) v[3] = d * 0.929999962449f;
        else v[3] = o->f2c;
    }
    func_00267560(v, v, v[3]);
    o->v3c0[0] = v[0];
    o->v3c0[2] = v[2];
    if (o->v3c0[1] < o->f24) {
        o->v3c0[1] += D_002BBDFC * 0.35f;
        if (o->f24 < o->v3c0[1]) o->v3c0[1] = o->f24;
    } else if (o->f24 < o->v3c0[1]) {
        o->v3c0[1] -= D_002BBDFC * 0.35f;
        if (o->v3c0[1] < o->f24) o->v3c0[1] = o->f24;
    }
    func_00267560(v, o->v3c0, D_002BBDFC);
    o->f3cc = o->f24;
    o->f24 = 0.0f;
    p = func_0014dab8();
    if (p && v[1] > 0.0f && p->f8 < o->f14 + v[1]) {
        v[1] = p->f8 - o->f14;
    }
    if (func_0012c8e8(o)) func_00147410(17108, o->i4 + 1, o);
    else func_00147278(17108, o->i4 + 1, 60);
}

s32 func_0014e668(f32 *pos, s32 n, f32 *out, f32 min, f32 max) {
    f32 base[4];
    f32 t[4];
    f32 r;
    f32 ang;
    f32 a;
    s32 i;

    func_002675a8(base, pos);
    r = func_00176850() * (max - min) + min;
    ang = func_00176850() * 6.2831855f;
    for (; r >= min; r -= 100.0f) {
        for (i = 0; i < 18; i++) {
            a = func_00120c88(ang + (f32)(i ^ 5) * 0.349065847695f);
            t[0] = sinf(a) * r;
            t[1] = 0.0f;
            t[2] = cosf(a) * r;
            t[3] = 1.0f;
            func_00267518(out, base, t);
            if (n == 0 || ((func_0014e5b8(out) >> (n - 1)) & 1)) {
                func_001426a8(out, 1000.0f);
                out[1] += -100.0f;
                if (func_0012f0f8(base, out, 2)) {
                    out[1] -= -100.0f;
                    return 1;
                }
            }
        }
    }
    func_002675a8(out, pos);
    out[1] += -100.0f;
    func_001426a8(out, 1000.0f);
    return 0;
}

s32 func_0014e878(f32 *pos, s32 id, f32 *out, f32 min, f32 max) {
    f32 t[4];
    f32 r;
    f32 ang;
    f32 a;
    s32 i;
    s32 j;
    Box57_f1b8 *b;

    r = func_00176850() * (max - min) + min;
    ang = func_00176850() * 6.2831855f;
    for (; r >= min; r -= 100.0f) {
        for (i = 0; i < 18; i++) {
            a = func_00120c88(ang + (f32)(i ^ 5) * 0.349065847695f);
            t[0] = sinf(a) * r;
            t[1] = 0.0f;
            t[2] = cosf(a) * r;
            t[3] = 1.0f;
            func_00267518(out, pos, t);
            if (id == 0) return 1;
            b = D_00350D78->box;
            for (j = 0; j < D_00350D78->n; j++, b++) {
                if (b->u.c.id == id && out[0] >= b->lo[0] && out[0] <= b->hi[0]
                    && out[2] >= b->lo[2] && out[2] <= b->hi[2]) {
                    out[1] = func_00176850() * (b->hi[1] - b->lo[1]) + b->lo[1] + -100.0f;
                    if (func_0012f0f8(pos, out, 1)) {
                        out[1] -= -100.0f;
                        return 1;
                    }
                }
            }
        }
    }
    func_002675a8(out, pos);
    return 0;
}

s32 func_0014f028(void) {
    u32 m;
    s32 id;
    s32 i;
    Ent57_f028 *p;
    Grp57_f1b8 *e;

    if (!D_00350D78) return 4;
    if ((D_002C5958 >> 14) & 1) return 0;
    m = func_0014ee88(D_002E26A0);
    if (m) {
        p = 0;
        while ((p = func_00132040(p)) != 0) {
            if (p->x58 == 0) continue;
            e = &D_0054F450[p->x58 - 1];
            if ((m & (1 << (p->x58 - 1))) == 0) continue;
            if (e->fc > 0.0f) continue;
            if (func_00123488(p->x0)) continue;
            if (func_00142240(p->x0) == 1) continue;
            if (e->x14 < p->x48) continue;
            if (!func_00124218(p->x0)) continue;
            e->fc = e->f4;
            if (e->fc > 0.0f) break;
        }
    }
    D_0054F448 = m;
    e = D_0054F450;
    for (i = 0; i < 31; i++, e++) {
        if (e->fc > 0.0f) e->fc -= D_002BBDFC;
    }
    return 0;
}

s32 func_0014f1b8(BoxSet57_f1b8 *set) {
    s32 i;
    s32 r;
    Box57_f1b8 *b;
    Grp57_f1b8 *g;

    D_00350D7C = 0;
    D_0054F448 = 0;
    D_0054F44C = -1;
    D_00350D80 = 0;
    for (i = 0; i < 31; i++) {
        D_0054F450[i].fc = 0.0f;
    }
    r = 2;
    D_00350D78 = set;
    if (set) {
        b = set->box;
        D_00350D7C = set->x3;
        for (i = 0; i < D_00350D78->n; i++, b++) {
            g = &D_0054F438[b->u.c.id];
            g->b0 = (u8)(b->u.flags >> 8);
            g->b1 = (u8)(b->u.flags >> 9);
            g->f4 = b->u.c.b2;
            g->f8 = b->u.c.b3;
            g->x10 = b->u.c.b4;
            g->x14 = 0;
        }
        r = D_00350D78->x5;
        if (!func_0011ef38(func_0014f028)) func_0011ef10(0x1387f, func_0014f028);
    }
    if (D_002BC128 != 16 || (D_002BC130 != 30 && D_002BC130 != 33)) {
        if (func_0013c968(61, 0)) r = 0;
    }
    return func_00142058(r);
}

void func_0014f410(Obj57_f410 *o) {
    f32 v[4];
    s32 id;

    func_0014f3d0(o);
    if ((s32)(o->f440 >> 33) & 1) return;
    if (o->flags & 0x400) {
        switch (o->i70) {
        case 0:
            if (o->i378 == 2) {
                func_00130340(o, (o->i3d0 + 7) | 0x01000000, 0.0f);
                func_00130578(o, 0x40000000, 8.0f);
            }
            break;
        case 2:
            func_00130340(o, 6, 8.0f);
            break;
        }
    }
    if (o->i70) return;
    if (o->f2c == 0.0f) {
        if (o->i178) return;
        if ((u32)(o->i164 - 1) < 2) func_00146c98(o, 8);
        func_00130398(o, 0, 10.0f);
        return;
    }
    if (o->f2c < o->prm->f8) id = 1;
    else id = 2;
    if (o->i164 == 0) {
        func_001315c0(o, 41, v, 1.0f);
        func_0012bd98(o, o->b39e, 0x80000002, v);
        func_001315c0(o, 40, v, 1.0f);
        func_0012bd98(o, o->b39e, 0x80000002, v);
    }
    func_00130398(o, id, 8.0f);
}

f32 func_0014fab0(Obj57_fab0 *o, s32 id, f32 *dir, f32 lim) {
    f32 a[4];
    f32 b[4];
    f32 ang[4];
    f32 m[16];
    f32 len;

    func_001315c0(o, 0, a, 0.5f);
    func_0012ec88(id, b);
    func_00267530(dir, b, a);
    func_00121fc4(dir, dir);
    len = dir[3];
    func_002673f8(m, o->md0);
    dir[3] = 0.0f;
    func_002672f8(dir, m, dir);
    if (lim < dir[2]) return 0.0f;
    ang[1] = atan2f(-dir[0], -dir[2]);
    ang[2] = asinf(dir[1]);
    if (ang[2] < 0.0f) {
        if (ang[2] < -o->prm->f2c) ang[2] = -o->prm->f2c;
    } else {
        if (o->prm->f30 < ang[2]) ang[2] = o->prm->f30;
    }
    if (ang[1] < 0.0f) {
        if (ang[1] < -o->prm->f34) ang[1] = -o->prm->f34;
    } else {
        if (o->prm->f38 < ang[1]) ang[1] = o->prm->f38;
    }
    func_00267768(m, D_002C58D0, ang[2]);
    func_00267810(m, m, ang[1]);
    dir[0] = 0.0f;
    dir[1] = 0.0f;
    dir[2] = -1.0f;
    dir[3] = 0.0f;
    func_002672f8(dir, m, dir);
    return len;
}

f32 func_0014fc68(Obj57_fc68 *o, s32 id, f32 *dir, f32 lim) {
    f32 a[4];
    f32 b[4];
    f32 ang[4];
    f32 m[16];
    f32 len;

    func_001315c0(o, 0, a, 0.5f);
    func_0012ec88(id, b);
    func_002674f0(b, o->v460, b, 0.9f);
    func_002675a8(o->v460, b);
    func_00267530(dir, b, a);
    func_00121fc4(dir, dir);
    len = dir[3];
    func_002673f8(m, o->md0);
    dir[3] = 0.0f;
    func_002672f8(dir, m, dir);
    if (lim < dir[2]) return 0.0f;
    ang[1] = atan2f(-dir[0], -dir[2]);
    ang[2] = asinf(dir[1]);
    if (ang[2] < 0.0f) {
        if (ang[2] < -o->prm->f2c) ang[2] = -o->prm->f2c;
    } else {
        if (o->prm->f30 < ang[2]) ang[2] = o->prm->f30;
    }
    if (ang[1] < 0.0f) {
        if (ang[1] < -o->prm->f34) ang[1] = -o->prm->f34;
    } else {
        if (o->prm->f38 < ang[1]) ang[1] = o->prm->f38;
    }
    func_00267768(m, D_002C58D0, ang[2]);
    func_00267810(m, m, ang[1]);
    dir[0] = 0.0f;
    dir[1] = 0.0f;
    dir[2] = -1.0f;
    dir[3] = 0.0f;
    func_002672f8(dir, m, dir);
    return len;
}

s32 func_001507d0(Chr57_07d0 *o) {
    f32 a[8];
    f32 b[8];
    Chr57_07d0 *p;
    Col57_07d0 *c;
    s32 n;
    s32 i;

    p = 0;
    func_0015bad0(o, o->cs->cols[0], a);
    while ((p = func_001230a0(p)) != 0) {
        if (p->info->kind != 11) continue;
        if (!func_00123330(p)) continue;
        if (p->i164 >= 2) continue;
        if (p->o144 && p->o144->fc > 0.0f) continue;
        n = p->cs->n[3];
        c = p->cs->cols[3];
        for (i = 0; i < n; i++, c++) {
            if ((c->x[0] & 0xf) != 3) continue;
            func_0015bad0(p, c, b);
            if (func_0015b998(a, b)) {
                o->o148->i140 = i;
                func_00150678(o, p);
                return 1;
            }
        }
    }
    return (s32)p;
}

void func_00150930(Chr57_0930 *o, Chr57_0930 *t, f32 *v) {
    f32 a[4];
    f32 h;
    f32 d;
    f32 k;
    f32 vy;

    if (o->o98 && o->o98->info->kind == 11) o->o98->o144->fc = 180.0f;
    func_0014cb90(o)->f4 = 4.0f;
    func_0012ec88(t, a);
    if (t->info->kind == 11) {
        a[0] = t->v10[0];
        a[2] = t->v10[2];
        a[1] += 120.0f;
    }
    func_00267530(v, a, o->v10);
    h = v[1];
    v[1] = 0.0f;
    func_00121fc4(v, v);
    d = v[3];
    k = (d / o->prm->f8 > 30.0f) ? d / o->prm->f8 : 30.0f;
    vy = (h - k * 0.484693862498f * k * 0.5f) / k;
    func_00267560(o->v3c0, v, d / k);
    o->f3b4 = 0.484693862498f;
    o->f3cc = 0.99f;
    o->f3b0 = 0.0f;
    o->f3c4 = vy;
    o->f3b8 = -vy / 0.484693862498f;
    func_0014f658(o, 3);
    func_001376e8(o, v);
}
#include "data/bss_0054_typed.h"
#include "data/data_002B.h"
#include "data/data_0035.h"

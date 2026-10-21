#include "common.h"
#include "platform/math.h"
#include "data/bss_0057.h"

typedef struct { u8 pad[0x10]; f32 f10; u8 pad14[0x28]; s32 w3C; s32 w40; s32 w44; } ChrHp;
typedef struct { u8 pad[0x38]; u64 w38; } Wk144;
typedef struct { u32 flags; u8 pad4[0xC]; f32 pos[4]; u8 pad20[0x4C]; ChrHp *p6C; s32 w70; u8 pad74[0xD0]; Wk144 *p144; } Chr;
#include "data/types/nostrict_text_00160000_h60_p.h"
typedef struct { s32 *a; s32 b; } P86F;
typedef struct {
    u8 pad[0x20]; f32 v20[4]; u8 pad30[8]; u64 w38; u8 pad40[0x18]; s32 w58; u8 pad5c[0x34];
    Chr *tgt; u8 pad94[0xC]; f32 fA0; u8 padA4[0x40]; f32 fE4;
} L60;
typedef struct { u8 pad[8]; f32 f8; u8 pad0c[4]; f32 f10; } Prm6C;
typedef struct {
    u8 pad[0x10]; f32 pos[4]; u8 pad20[0x10]; f32 v30[4]; u8 pad40[0x2C]; Prm6C *p6C; s32 w70; u8 pad74[0x1C];
    u64 w90; u8 pad98[0x28]; f32 vC0[4];
} Ent68;
typedef struct { u8 pad[4]; f32 f4; } Sub4;
typedef struct {
    u8 pad[4]; Sub4 *p4; u8 pad8[0x18]; f32 v20[4]; f32 f30; u8 pad34[4]; u64 w38; u8 pad40[0x18]; u32 w58;
    u8 pad5c[0x90]; f32 fEC; u8 padF0[0x30]; u8 x120[0x10];
} Wk68;
typedef struct { f32 p[4]; f32 d[4]; u8 pad[0x10]; s16 h; u8 pad32[2]; s32 x; u8 pad38[8]; } Ray68;
typedef struct { f32 x, y, z, w; } Hit68;
typedef struct { u8 pad[0x10]; f32 pos[4]; f32 v20[4]; f32 v30[4]; u8 pad40[0x30]; s32 w70; } Ent69;
typedef struct { u8 pad[4]; f32 f4; } Sub69;
typedef struct {
    s32 w0; Sub69 *p4; u8 pad8[0x30]; u64 w38; u8 pad40[0x28]; f32 f68; u8 pad6c[0x24]; s32 w90; s32 w94; u8 pad98[0x18];
    f32 vB0[4]; u8 padC0[0x60]; f32 v120[4];
} Wk69;
typedef struct {
    u8 pad0[0x38]; u64 w38; u8 pad40[0xB0]; f32 vF0[4]; u8 pad100[0x20]; f32 v120[4]; f32 f130;
} Wk6B;
typedef struct { u8 pad[0x70]; s32 w70; } Ent6C4;
typedef struct { u8 pad[0x10]; f32 pos[4]; u8 pad20[0x350]; u64 f370; } Ent370;
typedef struct { s32 a, b; } P8;
typedef struct {
    u8 pad0[0x38]; u64 w38; u8 pad40[0x40]; union { u64 w; struct { u64 lo:32; u64 m:8; u64 z:16; u64 hi:8; } b; } w80; u8 pad88[0]; P8 p88; Ent370 *p90; u8 pad94[4]; u8 pad98[8]; f32 fA0;
    u8 padA4[0x2C]; f32 vD0[3]; f32 fDC; u8 padE0[0x40]; f32 v120[4]; 
} Wk6C4;
typedef struct { u8 pad[8]; void *w8; u8 padC[0x64]; s32 w70; } Ent6D;
typedef struct { u8 pad[0xC]; f32 fC; f32 f10; f32 f14; f32 f18; } Rng6D;
typedef struct { u8 pad[4]; u32 w4; } Arg6D;
typedef struct {
    u8 pad0[8]; Rng6D *p08; Rng6D *p0C; u8 pad10[0x20]; f32 f30; u8 pad34[4]; u64 w38; u8 pad40[0x14]; s32 w54; u8 pad58[0xC];
    f32 f64; f32 f68; f32 f6C; u8 pad70[4]; Arg6D *p74; u8 pad78[0x18]; void *p90; u8 pad94[8]; f32 f9C; u8 padA0[0x2C];
    f32 fCC; u8 padD0[0xC]; f32 fDC; u8 padE0[0x40]; f32 v120[4];
} Wk6D;
typedef struct { f32 ang, y, scale, a, b; } Tbl6E;
typedef struct { u8 pad[0x30]; f32 v30[3]; f32 f3C; u8 pad40[0x30]; s32 w70; u8 pad74[0xF0]; s32 w164; } Ent6E;
typedef struct {
    u8 pad0[0x10]; s32 w10; Tbl6E *p14; u8 pad18[0x20]; u64 w38; u8 pad40[8]; s32 w48; s32 w4C; u8 pad50[0x18];
    f32 f68; u8 pad6C[0x24]; void *p90; u8 pad94[0x2C]; f32 vC0[4]; u8 padD0[0x50]; f32 v120[4];
} Wk6E;
typedef struct { f32 p[4]; f32 d[4]; f32 hit[4]; s16 h; u8 pad32[0xE]; } Ray6E;
#include "data/types/nostrict_text_00160000_h60.h"
typedef struct { s32 w0; u8 pad4[4]; u8 *p8; u8 *pC; u8 pad10[0x54]; f32 f64; } Wk6F8;
typedef struct { u8 pad[0x10]; f32 pos[4]; u8 pad20[0x50]; s32 w70; } Ent6FA;
typedef struct { u8 pad[8]; f32 f8; } Sub6FA;
typedef struct {
    s32 w0; Sub6FA *p4; u8 pad8[0x28]; f32 f30; u8 pad34[4]; u64 w38; u8 pad40[0x18]; s32 w58; u8 pad5c[0x34];
    void *p90; s32 w94; u8 pad98[0xC]; f32 fA4; u8 padA8[0x44]; f32 fEC; u8 padF0[0xC]; f32 fFC;
} Wk6FA;
typedef struct { s32 a, b; } P870;
typedef struct { u8 pad[0xC]; void *pC; } Ent70;
typedef struct {
    s32 w0; void *p4; void *p8; void *pC; s32 w10; s32 w14; s32 w18; Ent70 *p1C; u8 pad20[0x240];
} Wk70;
typedef struct { u8 pad[0x30]; u64 w30; } Sub148;
typedef struct { u8 pad[0x2C]; s32 w2C; } Sub14C;
typedef struct { u8 pad[0x4C]; u16 h4C; } Sub130;
typedef struct { u8 pad[0x130]; Sub130 *p130; u8 pad134[0x10]; Wk70 *p144; Sub148 *p148; Sub14C *p14C; } Obj70;
typedef struct { s32 o0, o4, o8, oC, n; s32 ofs[1]; } Tbl70;
typedef struct { Ent370 *tgt; s32 part; } Lock71;
typedef struct { s32 w0; u8 pad4[0x10]; f32 f14, f18, f1C, f20, f24; } Sub170C;
typedef struct { u8 pad[0xC]; Sub170C *pC; } Sub170;
typedef struct {
    u8 pad[0x38]; u64 w38; u8 pad40[8]; void *w48; s32 w4C; u8 pad50[0x40]; s32 w90; u8 pad94[0xD0];
    f32 f164; u8 pad168[8]; Sub170 *p170; s32 w174; s32 w178;
} Wk172;
typedef struct { u8 pad[0x14]; f32 f14; } Obj172;
typedef struct { u8 pad[0xC]; void *cb; } Task0C;
typedef struct { u8 pad[0x30]; s32 w30; } Res30;
typedef struct { u8 pad[4]; s32 w4; } Res04;
typedef struct {
    u8 pad[0x80];
    union { u64 w; struct { u64 lo:32; u64 m:8; u64 z:16; u64 hi:8; } b; } w80;
    Chr *p88; s32 w8C; u8 pad90[8]; Chr *p98;
} Wk172_22e8;
typedef struct { s32 w0; u8 pad4[0x10]; f32 f14, f18, f1C; } Sub170C_2690;
typedef struct { u8 pad[0xC]; Sub170C_2690 *pC; } Sub170_2690;
typedef struct { u64 w0; u8 pad8[0x48]; f32 f50; } Sub40;
typedef struct { u8 pad[0x40]; Sub40 *p40; u8 pad44[0x10]; s32 w54; u8 pad58[0x10]; f32 f68; } Wk172_2690;
typedef struct { u8 pad[0x70]; s32 w70; } Obj172_2690;
typedef struct {
    u8 pad0[0x38]; u64 w38; u8 pad40[8]; s32 w48; u8 pad4c[0x0C]; s32 w58; u8 pad5c[8]; f32 f64; u8 pad68[0x28];
    void *p90; s32 w94;
} Wk705;

extern f32 D_002BBDFC;
extern s32 D_002BC128;
extern s32 D_002BC130;
extern u32 D_002C5958;
extern u8 D_002C5C60[];
extern Obj70 *D_002E26A0[];
extern u32 D_002E27C8;
extern s32 D_002E31B0;
extern Prm35AE80 D_0035AE80;
extern void (*D_0035BC80[])(Obj70 *, Wk70 *);
extern f32 D_0035BD10[4];
extern Chr *D_0035BD40[];
extern u8 D_0035BE40[];
extern f32 D_0048EA68;
extern s32 D_00574FB4;
extern s32 D_00574FB8;
extern void *D_00574FC0[20];
extern s32 D_00575010;
s32 D_00575014 ALIGNED(4);
extern f32 D_00575020[][4];
extern f32 D_00575050[][4]; /* stays extern: indexed by i like D_00575020[i]; the extent (one row) is unsure */
extern P870 D_00575080; /* src/data/bss_0057.c: LockEA D_00575080 */
extern s32 D_00575088;
extern s32 D_0057508C;
extern f32 D_00575090[40][4];
extern P86F D_00575310[]; /* src/data/bss_0057.c: TalkEA D_00575310 */
extern Node6F D_00575528[30];
extern Node6F *D_00575780; /* src/data/bss_0057.c: void *D_00575780 */
extern Node6F *D_00575784; /* src/data/bss_0057.c: void *D_00575784 */
f32 cosf(f32);
s32 func_00105ad0(s32, s32, Hit68 *);
void func_00118608(Ray68 *);
void func_00118668(Ray6E *);
s32 func_00119688(f32 *);
s32 func_0011ef38(s32 (*)());
Wk70 *func_00121e28(s32, Wk70 **);
void func_001224c8(s32 *, void *, void (*)(), f32);
void func_00122768();
s32 func_00122ff8(void *);
Ent370 *func_00123158(void *, Ent370 *);
s32 func_00123368(Ent370 *);
s32 func_0012eaf8(void *);
f32 func_0012ec60(void *, s32, f32 *);
s32 func_0012ee70(void *, s32);
s32 func_0012f040(void *, s32);
void func_00130340(Obj172 *, s32, f32);
Task0C *func_00130578(Obj172 *, s32, f32);
s32 func_00133000(Ent6C4 *, s32);
void func_00137688(Ent6E *, f32);
f32 func_001376e8(void *, f32 *);
s32 func_001383d8(s32, s32 (*)());
Res04 *func_0013dbe0(Obj172 *, s32);
void func_0013df40(Obj172_2690 *, s32);
void func_0013dfb8(Ent68 *, void *);
s32 func_00141200(void *, s32);
void func_001412f8(Obj172 *, s32);
void func_00141540(Chr *, s32);
Res30 *func_001477c8(s32);
void func_00148a40(void *, s32);
void func_0014a0f0(Sub40 *);
void func_0014c448(Ent69 *);
void func_0014d428(Ent6E *, f32 *, f32, f32);
void func_0014f658(void *, s32);
void func_00157a30(void *, s32, void *);
void func_001586a8(s32);
u32 func_001627e8(s32);
f32 func_00162978(f32 *, f32 *);
f32 func_001629e8(void);
f32 func_00162a58(f32 *);
f32 func_00162c20(f32 *);
void func_001687d8(void *, void *, s32);
void func_00168d20(Ent69 *, Wk6B *);
s32 func_00169688(Ent69 *, Wk6B *);
s32 func_0016b670(Obj172 *, Wk172 *, Sub170 *, s32);
void func_0016e0d0(s32);
s32 func_0016ea58();
void func_0016f7b8(void);
void func_00170e30(s32);
void func_00170f50(Obj172 *, Wk172 *, void *, s32, s32);
s32 func_00170f90();
void func_00170fa8(void *, void *, void *, void *, f32);
Chr *func_00171078(Chr *, Wk172_22e8 *);
s32 func_00171098(Chr *, s32);
s32 func_001710d8(Chr *, s32);
void func_00171790(Ent6E *, Wk6E *);
s32 func_00171a88(void *, void *, s32);
f32 func_00171aa8(f32, f32);
s32 func_00171ae8(Obj172_2690 *, Wk172_2690 *);
void *func_00171b80(Obj172_2690 *, Wk172_2690 *, s32);
void func_00171e50(Chr *, Wk172_22e8 *, Chr *);
void func_001731f8();
s32 func_001734f8();
void func_00173610();
void func_00173718();
void func_00242b00(Chr *);
void func_00242b38(Chr *);
void func_00245f90(s32, Chr *);
void func_00245ff0(Chr *);
void func_002464f8(s32 *);
void func_00267370(f32 *, f32 *, f32 *);
f32 func_00267390(f32 *, f32 *);
void func_002673b8(f32 *, f32 *);
void func_00267518(f32 *, f32 *, f32 *);
void func_00267530(f32 *, f32 *, f32 *);
void func_00267560(f32 *, f32 *, f32);
void func_002675a8(f32 *, f32 *);
void func_00267e90(f32 *, f32 *, f32);
void *memset(void *, s32, u32);
f32 sinf(f32);

void func_001689d0(Chr *self, L60 *l) {
    f32 a[4];
    f32 b[4];
    f32 c[8];
    if (((s32)((s64)(l->w38 << 22) >> 32) & 1) || l->tgt == 0) {
        if (l->fE4 < 0.0f) {
            func_00267518(a, D_0035BD40[0]->pos, l->v20);
            func_00267530(b, self->pos, D_0035BD40[0]->pos);
        } else {
            func_00267518(a, self->pos, l->v20);
            func_00267530(b, D_0035BD40[0]->pos, self->pos);
        }
    } else {
        if (l->fA0 < 0.0f) {
            func_00267518(a, l->tgt->pos, l->v20);
            func_00267530(b, self->pos, l->tgt->pos);
        } else {
            func_00267518(a, self->pos, l->v20);
            func_00267530(b, l->tgt->pos, self->pos);
        }
    }
    if (func_00119688(a) < 0 && func_00162a58(b) < 500.0f) l->w58 = 0;
}

s32 func_00168b30(Ent68 *e, Wk68 *w, s32 flag, f32 *unused) {
    Ray68 r;
    f32 a[4];
    f32 b[4];
    f32 pad[8];
    Hit68 h[4];
    s32 n;
    f32 m, d;
    s32 i;
    if (e->w90 == 0) return 0;
    func_00267518(r.p, e->pos, w->v20);
    func_00267370(b, e->vC0, e->v30);
    func_00267370(a, b, e->vC0);
    func_002673b8(a, a);
    func_00267560(r.d, a, w->f30 + e->p6C->f8 * D_002BBDFC);
    func_00118608(&r);
    if (r.h < 0) goto fail;
    n = func_00105ad0(r.x, r.h, h);
    m = 0.0f;
    for (i = 0; i < n; i++) {
        d = e->pos[1] - h[i].y;
        if (d > 0.0f) d = 0.0f;
        d = -d;
        if (!(m < d)) d = m;
        m = d;
    }
    if (m < e->p6C->f10) {
        if (e->w70 == 8 || e->w70 == 21 || e->w70 == 2 || e->w70 == 24) goto fail;
        if (e->w70 == 17) goto z;
    } else goto z;
    if (flag == 0 && D_0057508C == 0 && w->fEC < w->p4->f4) w->w38 |= 0x80;
    if (w->w58 < 80) {
        if (e->w70 != 2) func_0013dfb8(e, w->x120);
        return 1;
    }
z:    return 0;
fail:
    return 0;
}

void func_00169008(Ent69 *e, Wk69 *w) {
    f32 v[4];
    f32 u[4];
    s32 lock;
    f32 y, len, k;
    if ((D_002C5958 & 1) && w->w90 != 0 && w->w94 >= 0 && !((s32)w->w38 & 1)) {
        func_002675a8(v, w->vB0);
        lock = 1;
        w->w38 &= ~0x400;
    } else {
        lock = 0;
        func_002675a8(v, D_00575020[w->w0]);
        w->w38 |= 0x400;
    }
    if (func_00168b30((Ent68 *)e, (Wk68 *)w, lock, v) != 0) return;
    func_00267530(w->v120, v, e->pos);
    y = w->v120[1];
    w->v120[1] = 0.0f;
    k = -10.0f;
    len = func_00162c20(w->v120);
    if (!(y < -100.0f)) {
        k = 10.0f;
        if (!(100.0f < y)) k = 0.0f;
    }
    func_001687d8(e, w, lock);
    w->v120[1] = k;
    if (k == 0.0f && D_0035AE80.f1D4 < len && ((D_002E27C8 >> 6) & 1)) {
        func_002675a8(u, e->v30);
        u[1] = 0.0f;
        func_002673b8(u, u);
        if (func_00267390(w->v120, u) > 0.97999996f) {
            func_0014f658(e, 25);
            w->f68 = D_0035AE80.f1D8;
        }
    }
}

void func_00169210(Ent69 *e, Wk69 *w) {
    f32 v[4];
    s32 lock;
    f32 y, len, k;
    if ((D_002C5958 & 1) && w->w90 != 0 && w->w94 >= 0 && !((s32)w->w38 & 1)) {
        func_002675a8(v, w->vB0);
        lock = 1;
        w->w38 &= ~0x400;
    } else {
        lock = 0;
        func_002675a8(v, D_00575020[w->w0]);
        w->w38 |= 0x400;
    }
    if (func_00168b30((Ent68 *)e, (Wk68 *)w, lock, v) != 0) return;
    func_00267530(w->v120, v, e->pos);
    y = w->v120[1];
    w->v120[1] = 0.0f;
    k = -10.0f;
    len = func_00162c20(w->v120);
    if (!(y < -100.0f)) {
        k = 10.0f;
        if (!(100.0f < y)) k = 0.0f;
    }
    func_001687d8(e, w, lock);
    w->v120[1] = k;
    if (e->w70 == 21) {
        if (len < w->p4->f4 || func_00267390(e->v20, w->v120) <= 0.0f) func_0014c448(e);
    }
}

void func_001693c8(Ent69 *e, Wk6B *w) {
    f32 v[4];
    switch (e->w70) {
    case 24:
        func_00169008(e, w);
        break;
    case 8:
    case 21:
    case 4:
        func_00169210(e, w);
        break;
    default:
        if (func_00169688(e, w)) return;
        func_00168d20(e, w);
        break;
    }
    if (w->v120[1] == 0.0f && w->v120[3] == 0.0f) {
        if ((s32)((s64)(w->w38 << 22) >> 32) & 1) {
            w->w38 |= 0x80;
            func_00267560(v, w->vF0, 0.39999998f);
            func_00267518(v, v, e->v30);
            v[1] = 0.0f;
            func_002673b8(w->v120, v);
        }
    } else {
        w->w38 &= ~0x80;
    }
}

static inline s32 inl_ok(Ent6C4 *e, s32 K) {
    s32 r;
    switch (e->w70) {
    case 0:
    case 8:
    case 24:
        if (func_00133000(e, K) == 0) break;
        return 1;
    }
    return 0;
}

s32 func_0016c480(Ent6C4 *e, Wk6C4 *w, s32 unused, s32 mode) {
    s32 ok;
    f32 f;
    switch (mode) {
    case 0:
        return 0;
    case 1:
        if (!((s32)((s64)(w->w38 << 30) >> 32) & 1)) return 0;
        if (!inl_ok(e, 0)) return 0;
        if (w->p90 == 0) return 0;
        if (func_00141200(w->p90, 2)) return 0;
        f = w->fDC;
        if (f < D_0035AE80.fD0) return 0;
        if (D_0035AE80.fD4 < f) return 0;
        if (!(D_0035AE80.fD8 <= f)) return 1;
        if (!(f <= D_0035AE80.fDC)) return 1;
        f = w->fA0;
        if (f < D_0035AE80.fE0) return 0;
        if (D_0035AE80.fE4 < f) return 0;
        break;
    case 2:
        func_001376e8(e, w->vD0);
        func_002675a8(w->v120, w->vD0);
        w->v120[3] = 0;
        w->w80.b.m = mode;
        w->w80.b.z = 0;
        w->p88 = *(P8 *)&w->p90;
        break;
    }
    return 1;
}


/* inline copy of func_001715b0 */
static inline s32 inl_001715b0(void *grp, Ent370 *self, f32 r) {
    f32 v[4];
    s32 n = 0;
    Ent370 *p = 0;
    f32 r2 = r * r;
    while ((p = func_00123158(grp, p)) != 0) {
        if (p == self) continue;
        if (((s32)(p->f370 >> 37) & 3) != 2) continue;
        if (!func_00123368(p)) continue;
        func_00267530(v, p->pos, self->pos);
        if (func_00267390(v, v) < r2) n++;
    }
    return n;
}

s32 func_0016cb98(Ent6C4 *e, Wk6C4 *w, s32 unused, s32 mode) {
    f32 f;
    switch (mode) {
    case 0:
        return 0;
    case 1:
        if (!((s32)((s64)(w->w38 << 30) >> 32) & 1)) return 0;
        if (!inl_ok(e, 2)) return 0;
        if (w->p90 == 0) return 0;
        if (func_00141200(w->p90, 4)) return 0;
        f = w->fDC;
        if (f < D_0035AE80.f154) return 0;
        if (D_0035AE80.f158 < f) return 0;
        f = w->fA0;
        if (!(D_0035AE80.f160 <= f)) break;
        if (!(f <= D_0035AE80.f164)) break;
        if (inl_001715b0(e, w->p90, D_0035AE80.f15C) < D_0035AE80.wB4) return 0;
        break;
    case 2:
        func_001376e8(e, w->vD0);
        func_002675a8(w->v120, w->vD0);
        w->v120[3] = 0;
        w->w80.b.m = mode;
        w->w80.b.z = 2;
        w->p88 = *(P8 *)&w->p90;
        break;
    }
    return 1;
}

s32 func_0016dd30();

s32 func_0016db80(Ent6D *e, Wk6D *w, Arg6D *x, s32 mode) {
    Rng6D *p;
    f32 f, a, b;
    if (w->f64 > 0.0f) p = w->p0C;
    else p = w->p08;
    switch (mode) {
    case 1:
        if (!(x->w4 & 0x800) && w->w54 == 0) return 0;
    case 0:
        if (w->p90 == 0) return 0;
        if ((s32)w->w38 & 1) return 0;
        if (w->w54 == 0) {
            if (!func_0016dd30(e, w, x)) return 1;
            if (w->p74 == x) return 0;
            break;
        }
        f = w->f68;
        if (f <= 0.0f) return 0;
        if (w->f6C - f >= p->fC * 0.5f && func_0016dd30(e, w, x)) return 0;
        break;
    case 2:
        if (w->w54 == 0) {
            a = p->fC;
            b = p->f10;
            f = func_001629e8();
            w->w38 |= 2;
            w->f6C = w->f68 = a + f * (b - a);
        }
        func_001693c8((Ent69 *)e, (Wk6B *)w);
        w->v120[3] = 0;
        break;
    }
    return 1;
}

s32 func_0016dd30(Ent6D *e, Wk6D *w, Arg6D *x, s32 mode) {
    Rng6D *p;
    void *t;
    f32 a, b, f;
    if (w->f64 > 0.0f) p = w->p0C;
    else p = w->p08;
    switch (mode) {
    case 1:
        if (!(x->w4 & 0x800) && w->w54 == 0) return 0;
    case 0:
        t = w->p90;
        if (t == 0) return 0;
        if (w->w54 != 0 && w->f68 <= 0.0f) return 0;
        if (e->w70 == 0) {
            if (w->fDC < w->f9C + w->f30 + D_0035AE80.f1DC) return 0;
        } else if (e->w70 == 8 || e->w70 == 24) {
            if (w->fCC < w->f9C + w->f30 + D_0035AE80.f1DC) return 0;
        }
        if (e->w8 == t) return 0;
        break;
    case 2:
        if (w->w54 == 0) {
            a = p->f14;
            b = p->f18;
            f = func_001629e8();
            w->w38 |= 2;
            w->f68 = a + f * (b - a);
        }
        func_001693c8((Ent69 *)e, (Wk6B *)w);
        if (w->v120[3] == 0.0f) return 1;
        if (w->f64 > 0.0f || ((s32)w->w38 & 1)) w->v120[3] = 20.0f;
        else w->v120[3] = 10.0f;
        break;
    }
    return 1;
}

static inline s32 inl_in(s32 k, Wk6E *w) {
    if (k < 13) { if (k >= 3) return 1; }
    return k == w->w4C;
}

void func_0016df30(Ent6E *e, Wk6E *w) {
    f32 v[4];
    Tbl6E *t;
    f32 ang;
    if (e->w70 == 0) w->w38 |= 0x10000;
    if (!inl_in(e->w164, w)) {
        w->w48 = 0;
        w->w38 &= ~0x8000;
        return;
    }
    func_00171790(e, w);
    if (w->p90 != 0) {
        func_00137688(e, func_001376e8(e, w->vC0));
        func_00267e90(w->v120, e->v30, 1.0f);
    }
    if (w->f68 <= 0.0f && ((s32)((s64)(w->w38 << 17) >> 32) & 1)) {
        t = &w->p14[func_001627e8(w->w10 << 12) >> 12];
        ang = e->f3C + t->ang;
        v[0] = sinf(ang);
        v[1] = 0.0f;
        v[2] = cosf(ang);
        v[3] = 0.0f;
        func_00267560(v, v, t->scale);
        v[1] = t->y;
        func_0014d428(e, v, t->a, t->b);
        w->w38 &= ~0x8000;
    }
}

void func_0016e1f0(s32 i) {
    f32 a[4];
    Ray6E r;
    Wk144 *w;
    f32 best, d;
    s32 j, k;
    w = D_0035BD40[i]->p144;
    w->w38 &= ~0x4000;
    if (D_0035BD40[i]->w70 == 8 || D_0035BD40[i]->w70 == 24 || D_0035BD40[i]->w70 == 25) return;
    if (D_00575020[i][1] < D_0035BD40[i]->pos[1] - D_0035BD40[i]->p6C->f10) return;
    if (D_0035BD40[i]->pos[1] + D_0035BD40[i]->p6C->f10 < D_00575020[i][1]) return;
    func_00267560(a, D_0035BD10, D_0035BD40[i]->p6C->f10);
    func_00267530(r.p, D_00575020[i], a);
    func_00267560(r.d, a, 2.0f);
    func_00118668(&r);
    if (r.h < 0) {
    w->w38 |= 0x4000;
    k = 0;
    func_00267530(a, D_00575090[0], D_00575020[i]);
    best = func_00267390(a, a);
    for (j = 1; j < 40; j++) {
        func_00267530(a, D_00575090[j], D_00575020[i]);
        d = func_00267390(a, a);
        if (d < best) {
            best = d;
            k = j;
        }
    }
    func_00267518(a, D_00575090[k], D_00575050[i]);
    func_00267560(D_00575020[i], a, 0.5f);
    } else {
        func_002675a8(D_00575020[i], r.hit);
    }
}

s32 func_0016f1f0(void) {
    s32 st[2];
    Wk144 *w1 = 0;
    Wk144 *w2 = 0;
    if (D_0035BD40[1] != 0) w1 = D_0035BD40[1]->p144;
    if (D_0035BD40[2] != 0) w2 = D_0035BD40[2]->p144;
    func_002464f8(st);
    if (w1 != 0) {
        if (st[0] && !(D_0035BD40[1]->flags & 0x8000)) {
            func_00245ff0(D_0035BD40[1]);
            w1->w38 &= ~0x20;
            st[0] = 0;
        }
        if ((s32)((s64)(w1->w38 << 28) >> 32) & 1) func_00242b00(D_0035BD40[1]);
        else func_00242b38(D_0035BD40[1]);
        if ((s32)((s64)(w1->w38 << 27) >> 32) & 1) {
            if (st[0] == 0) func_00245f90(0, D_0035BD40[1]);
        } else if (st[0] != 0) {
            func_00245ff0(D_0035BD40[1]);
        }
    }
    if (w2 != 0) {
        if (st[1] && !(D_0035BD40[2]->flags & 0x8000)) {
            func_00245ff0(D_0035BD40[2]);
            w2->w38 &= ~0x20;
            st[1] = 0;
        }
        if ((s32)((s64)(w2->w38 << 28) >> 32) & 1) func_00242b00(D_0035BD40[2]);
        else func_00242b38(D_0035BD40[2]);
        if ((s32)((s64)(w2->w38 << 27) >> 32) & 1) {
            if (st[1] == 0) func_00245f90(0, D_0035BD40[2]);
        } else if (st[1] != 0) {
            func_00245ff0(D_0035BD40[2]);
        }
    }
    func_0016e0d0(2);
    return 0;
}

static inline s32 inl_same(Wk6F3 *w) {
    if (w->w38.s.p3C != 0 && w->p40 != 0) {
        if ((u64 *)*w->w38.s.p3C == w->p40) return 1;
    }
    return 0;
}

void func_0016f3d0(void *o, Wk6F3 *w) {
    s32 i;
    s32 *p;
    w->w94 = -1;
    w->w90 = 0;
    w->w48 = 0;
    for (i = 0; i < 30; i++) {
        if (D_00575528[i].id == w->w0 && D_00575528[i].cb != 0) {
            D_00575528[i].cb(o, w, 2, D_00575528[i].arg);
            D_00575528[i].cb = 0;
        }
    }
    p = D_00575310[w->w0].a;
    if (p != 0 && *p == 1) {
        func_001224c8(p, D_002C5C60, func_00122768, 30.0f);
        D_00575310[w->w0].a = 0;
    }
    w->w38.w &= ~0x10;
    w->w38.w &= ~0x20;
    if (inl_same(w)) {
        *w->p40 &= ~0x100;
        *w->p40 &= ~0xC;
    }
    w->w38.s.p3C = 0;
    w->p40 = 0;
    memset(&w->w38, 0, 0x128);
}

void func_0016f640(void) {
    s32 i;
    Node6F **pp;
    D_00575088 = 0;
    if (!func_0011ef38(func_0016ea58)) D_00575010 = func_001383d8(2500, func_0016ea58);
    if (!func_0011ef38(func_0016f1f0)) D_00575014 = func_001383d8(3499, func_0016f1f0);
    { s32 j; for (j = 2; j >= 0; j--) D_00575310[j].a = 0; }
    D_00574FB8 = 0;
    { s32 j; for (j = 19; j >= 0; j--) D_00574FC0[j] = 0; }
    pp = &D_00575784;
    for (i = 0; i < 30; i++) {
        D_00575528[i].cb = 0;
        *pp = &D_00575528[i];
        pp = &D_00575528[i].next;
    }
    *pp = 0;
    D_00575780 = 0;
    D_00574FB4 = 2;
    if (D_002BC128 == 10 && D_002BC130 == 7) func_00170e30(0);
}

static inline s32 inl_alive2(Chr *a, u8 *kp) {
    s32 k = *kp;
    if (a->flags & 0x200) return 0;
    if (a->p6C->w40 * k < a->p6C->w3C * 255) return 0;
    return 1;
}

Chr *func_0016f8b8(Chr *e, Wk6F8 *w) {
    Chr *o;
    if (D_0035BD40[0] != 0 && inl_alive2(D_0035BD40[0], w->p8)) return D_0035BD40[0];
    if (inl_alive2(e, w->p8)) return e;
    o = D_0035BD40[w->w0 ^ 3];
    if (o != 0 && inl_alive2(o, w->p8)) return o;
    if (w->f64 > 0.0f && D_0035BD40[0] != 0 && inl_alive2(D_0035BD40[0], w->pC)) return D_0035BD40[0];
    return 0;
}

/* inline copy of func_00171118 */
static inline s32 inl_00171118(void *t, s32 i) {
    s32 r = 0;
    if (!(D_002C5958 & 1)) return r;
    if (t == 0) return r;
    if (!func_00122ff8(t)) return 0;
    if (i >= 0) return func_0012f040(t, i);
    for (i = -1; (i = func_0012ee70(t, i)) >= 0;) {
        if (func_0012f040(t, i)) return 1;
    }
    return 0;
}

void func_0016fa10(Ent6FA *e, Wk6FA *w, Sub6FA *pr) {
    f32 v[4];
    f32 h[4];
    void *t;
    if ((s32)w->w38 & 1) {
        if (w->fEC <= D_0035AE80.fC8) {
            w->w38 &= ~1;
        } else {
            if (e->w70 == 0 && w->fFC < fabsf(w->fA4)) {
                if (w->fFC <= w->p4->f8) w->w38 &= ~1;
                func_00267530(v, D_00575020[w->w0], e->pos);
                v[1] = 0.0f;
                if (func_00162a58(v) <= w->f30) w->w38 &= ~1;
            }
            if (!((s32)w->w38 & 1)) w->w58++;
        }
    }
    t = w->p90;
    if (t == 0) return;
    if (!((s32)w->w38 & 1) && inl_00171118(t, -1)) {
        if (!func_0012eaf8(w->p90)) return;
        func_0012ec60(w->p90, w->w94, h);
        if (pr->f8 <= func_00162978(h, e->pos) && pr->f8 <= func_00162978(h, D_0035BD40[0]->pos)) w->p90 = 0;
        if (!(D_0035AE80.fC4 <= w->fEC)) return;
    }
    w->w38 |= 1;
    w->w94 = -1;
    w->p90 = 0;
    w->w38 &= ~0x800;
}

void func_00170400(Obj70 *o) {
    u32 k;
    Wk70 *w;
    s32 i, n;
    Tbl70 *t;
    u8 *base;
    o->p148->w30 &= ~0x100000000ULL;
    o->p14C->w2C = 0;
    k = o->p130->h4C;
    w = func_00121e28(608, &o->p144);
    memset(w, 0, 608);
    w->w0 = -1;
    for (i = 0; i < 3; i++) {
        if (D_002E26A0[i] == o) {
            w->w0 = i;
            break;
        }
    }
    if (D_0035BC80[k] != 0) D_0035BC80[k](o, w);
    base = (u8 *)&D_0035AE80;
    if (w->p1C == 0) w->w18 = 0;
    t = (Tbl70 *)(((s32 *)base)[k] + (s32)base);
    if (!t->o0) w->p4 = base + 40;
    else w->p4 = (void *)(t->o0 + (s32)base);
    if (!t->o4) w->p8 = base + 64;
    else w->p8 = (void *)((s32)base + t->o4);
    if (!t->o8) w->pC = base + 92;
    else w->pC = (void *)((s32)base + t->o8);
    if (t->oC == 0) {
        w->w10 = 0;
        w->w14 = 0;
    } else {
        *(P870 *)&w->w10 = *(P870 *)(base + t->oC);
        w->w14 = (s32)base + w->w14;
    }
    {
        s32 *q = t->ofs;
        n = t->n;
        for (i = 0; i < n; i++) w->p1C[i].pC = (void *)((s32)base + q[i]);
    }
    func_0016f7b8();
}

void func_001711d0(Ent370 *self, Lock71 *out, f32 r) {
    f32 a[4];
    f32 b[4];
    Ent370 *p;
    s32 i;
    f32 best, d;
    out->part = -1;
    out->tgt = 0;
    if (r <= 0.0f) best = D_0048EA68;
    else best = r * r;
    p = 0;
    while ((p = func_00123158(self, p)) != 0) {
        if (((s32)(p->f370 >> 37) & 3) != 2) continue;
        if (!func_00123368(p)) continue;
        if (func_00141200(p, 0)) continue;
        for (i = -1; (i = func_0012ee70(p, i)) >= 0;) {
            if (!func_0012f040(p, i)) continue;
            func_0012ec60(p, i, a);
            func_00267530(b, a, self->pos);
            d = func_00267390(b, b);
            if (d < best) {
                out->tgt = p;
                best = d;
                out->part = i;
            }
        }
    }
}

s32 func_00172118(Obj172 *o, Wk172 *w, Sub170 *k, s32 mode) {
    Sub170C *c = k->pC;
    switch (mode) {
    case 0:
        return 0;
    case 1:
        if (!func_00171a88(o, w, 31)) return 0;
        if (!((s32)((s64)(w->w38 << 30) >> 32) & 1)) return 0;
        if (w->w90 == 0) return 0;
        return func_0016b670(o, w, k, 1);
    case 2:
        w->w38 |= 0x800;
        func_00130340(o, 0x10000CE, 8.0f);
        w->w4C = 206;
        w->p170 = k;
        w->w178 = 0x40000075;
        w->w174 = 0;
        w->f164 = o->f14 - c->f24;
        func_00130578(o, 0x40000075, 8.0f)->cb = func_001731f8;
        func_00148a40(o, 0);
        func_00170fa8(o, w, func_00170f90, D_0035BE40, 30.0f);
        func_001412f8(o, func_001477c8(func_0013dbe0(o, c->w0)->w4)->w30);
        w->w48 = func_00173610;
        func_00170f50(o, w, func_001734f8, 3, 0);
        return 1;
    }
    return 1;
}

s32 func_001722e8(Chr *o, Wk172_22e8 *w, s32 unused, s32 mode) {
    Chr *t = 0;
    Chr *q;
    if (w->p98 != 0 && w->p98 != o && func_001710d8(w->p98, 84)) {
        t = w->p98;
    } else if (D_0035BD40[0] != 0 && func_001710d8(D_0035BD40[0], 84)) {
        t = D_0035BD40[0];
    } else {
        q = func_00171078(o, w);
        if (q != 0) t = func_001710d8(q, 84) ? q : 0;
    }
    switch (mode) {
    case 0:
        return 0;
    case 1:
        if (t == 0) return 0;
        if (o->p6C->w44 < 2) return 0;
        if (!func_00171a88(o, w, 32)) return 0;
        break;
    case 2:
        func_00148a40(o, 0);
        func_00170fa8(o, w, func_00173718, D_0035BE40, 30.0f);
        w->w80.b.m = 3;
        w->p88 = t;
        w->w8C = 0;
        w->w80.b.z = 0x403;
        func_00171e50(o, w, t);
        func_00141540(o, -2);
        break;
    }
    return 1;
}

s32 func_001724b8(Chr *o, Wk172_22e8 *w, s32 unused, s32 mode) {
    Chr *list[3];
    Chr *t;
    s32 i;
    list[0] = o;
    list[1] = D_0035BD40[0];
    list[2] = func_00171078(o, w);
    if (w->p98 != 0 && func_00171098(w->p98, 84)) t = w->p98;
    else t = 0;
    for (i = 0; i < 3; i++) {
        if (list[i] != 0 && func_00171098(list[i], 84) && t == 0) t = list[i];
    }
    switch (mode) {
    case 0:
        return 0;
    case 1:
        if (t == 0) return 0;
        if (o->p6C->w44 < 3) return 0;
        if (!func_00171a88(o, w, 63)) return 0;
        break;
    case 2:
        func_00148a40(o, 0);
        func_00170fa8(o, w, func_00173718, D_0035BE40, 30.0f);
        w->w80.b.m = 3;
        w->w8C = -1;
        w->p88 = 0;
        w->w80.b.z = 0x406;
        func_00171e50(o, w, t);
        func_00141540(o, -3);
        break;
    }
    return 1;
}

s32 func_00172690(Obj172_2690 *o, Wk172_2690 *w, Sub170_2690 *k, s32 mode) {
    Sub170C_2690 *c = k->pC;
    switch (mode) {
    case 1:
        if (o->w70 == 24) return 0;
    case 0:
        if (c == 0) return 0;
        if (o->w70 == 8) return 0;
        return func_0016db80((Ent6D *)o, (Wk6D *)w, (Arg6D *)k, mode);
    case 2:
        func_0016db80((Ent6D *)o, (Wk6D *)w, (Arg6D *)k, mode);
        if (w->w54 == 0) {
            func_0013df40(o, 0);
            w->f68 = func_00171aa8(c->f14, c->f18);
        }
        if (!func_00171ae8(o, w)) {
            func_00171b80(o, w, c->w0);
            if (func_00171ae8(o, w)) {
                w->p40->w0 = (w->p40->w0 & ~0xC) | 4;
                w->p40->f50 = c->f1C;
            }
        } else {
            w->p40->w0 = (w->p40->w0 & ~0xC) | 4;
            func_0014a0f0(w->p40);
        }
        break;
    }
    return 1;
}

/* needs make: uses rodata */
void func_001705c0(void *e, Wk705 *w) {
    f32 f;
    if ((s32)((s64)(w->w38 << 29) >> 32) & 1) {
        f32 t;
        func_001586a8(20);
        t = D_0035AE80.fBC;
        w->w38 &= ~8;
        w->f64 = t;
        *(P870 *)&w->p90 = D_00575080;
        if (!((s32)((s64)(w->w38 << 27) >> 32) & 1)) {
            w->w38 |= 0x20;
            if (D_002E31B0 != 0) func_00157a30(e, 21, 0);
            else func_00157a30(e, 22, D_0035BD40[0]);
        }
        if (w->p90 == 0) {
            w->w38 |= 1;
            w->w94 = -1;
            w->w38 &= ~0x800;
            w->w38 &= ~0x10;
            w->p90 = 0;
        } else {
            w->w38 |= 0x800;
            w->w38 |= 0x10;
        }
        w->w58 += 20;
    } else {
        f = w->f64;
        if (f > 0.0f) {
            f = w->f64 = f - D_002BBDFC;
        }
        if (f < 0.0f) {
            w->f64 = 0.0f;
            f = 0.0f;
        }
        if ((double)w->f64 < (double)D_0035AE80.fBC - 90.0) w->w38 &= ~0x20;
        if (f <= 0.0f) w->w38 &= ~0x10;
        if (f <= 0.0f && w->w48 == 0) w->w38 &= ~0x800;
    }
}

/* Pointer tables only this file uses (phase 4, tools/shift/define_ptr_tables.py). */
void func_00172010();
void func_00172d90();
void func_00173740();
void func_00173ad8();
void func_00173ea8();
void func_00174398();
void func_00174950();
void func_00174d98();
void (*D_0035BC80[0xa])(Obj70 *, Wk70 *) ALIGNED(16) = {
    0, (void *)func_00172010, (void *)func_00172d90, (void *)func_00173740,
    0, (void *)func_00173ad8, (void *)func_00173ea8, (void *)func_00174398,
    (void *)func_00174950, (void *)func_00174d98,
};
#include "data/data_002B.h"
#include "data/data_0035.h"
#include "data/data_0048.h"
#include "data/pieces/D_002C5958.h"
#include "data/pieces/D_0035AE80.h"

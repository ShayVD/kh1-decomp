/* The party members' control, default flags (docs/modules.md "Session 52"):
 * the per-frame party hooks func_00168500 / func_00168518, func_00168530
 * (a member's position kept near D_00575020[i]) and func_00169f28 (a
 * member's follow and placement step against the leader).  The rest of
 * 0x00168500-0x00170170 is in partyctl.nostrict.c.  Read from the code,
 * not proved by a boot. */
#include "m2c.h"
#include "data/pieces/D_0035BD40.h"
#include "common.h"
#include "data/bss_0057.h"
#include "data/pieces/D_002BBFA0.h"
#include "data/pieces/D_002C58B0.h"

/* func_00168500 (from auto/text_00160000.c). */
M2C_UNK func_0016f640();
void func_00168500(void) {
    func_0016f640();
}

/* func_00168518 (from auto/text_00160000_5.c). */
M2C_UNK func_00170e98();
void func_00168518(void) {
    func_00170e98();
}

/* func_00168530 (from auto/text_00160000_6.c). */
M2C_UNK func_00123a88(s32, void *);
M2C_UNK func_00137688(void *, f32);
M2C_UNK func_00267530(s32, s32, s32);
M2C_UNK func_002675a8(s32, s32);
extern volatile unsigned char D_00575020;
f32 func_001376e8(void *, s32);
f32 func_00162c20(s32);
void func_00168530(void *arg0) {
  s32 *var_v0;
  s32 *var_v1;
  s32 temp_s0;
  s32 temp_s2;
  s32 var_a0;
  void *temp_s3;
  temp_s3 = *((void **) (((s8 *) arg0) + 0x144));
  temp_s0 = temp_s3 + 0xE0;
  temp_s2 = temp_s3 + 0xF0;
  func_00267530(temp_s0, D_0035BD40.i + 0x10, arg0 + 0x10);
  func_002675a8(temp_s2, temp_s3 + 0xE0);
  *((s32 *) (((s8 *) temp_s3) + 0xF4)) = 0;
  *((f32 *) (((s8 *) temp_s3) + 0xEC)) = func_00162c20(temp_s3 + 0xE0);
  *((f32 *) (((s8 *) temp_s3) + 0xFC)) = func_00162c20(temp_s2);
  func_00123a88(*((s32 *) (((s8 *) arg0) + 4)), (&D_00575020) + ((*((s32 *) (((s8 *) temp_s3) + 0))) * 0x10));
  func_00137688(arg0, func_001376e8(arg0, temp_s2));
  var_a0 = 4;
  var_v1 = temp_s3 + 0x154;
  var_v0 = temp_s3 + 0x140;
  do
  {
    var_a0 -= 1;
    *var_v0 = 0;
    *var_v1 = 0;
    var_v1 -= 1;
    var_v0 -= 1;
  }
  while (var_a0 > 0);
  *((s32 *) (((s8 *) temp_s3) + 0x58)) = 0;
}

/* func_00169f28 (from hand/text_00160000_s11_w4.c). */
typedef f32 Mtx[4][4];
typedef struct { u8 pad[0x18]; f32 x18; } S130;
typedef struct {
    u32 x0;
    u8 pad4[0xC];
    f32 pos[4];
    u8 pad20[0x50];
    s32 x70;
    u8 pad74[0x5C];
    Mtx mD0;
    u8 pad110[0x20];
    s32 x130;
    u8 pad134[0x30];
    s32 x164;
    u8 pad168[0x158];
    f32 x2C0;
    f32 x2C4;
    u8 pad2C8[0xA8];
    u64 x370;
} E9F;
typedef struct {
    u8 pad0[0x34];
    f32 f34;
    u32 b0:6;
    u32 b6:1;
    u32 b7:25;
    u32 hi;
    u8 pad40[0xC];
    s32 w4C;
    u8 pad50[8];
    u32 w58;
    u8 pad5C[4];
    u32 w60;
    u8 pad64[0xC];
    f32 f70;
    u8 pad74[0x70];
    f32 fE4;
    u8 padE8[8];
    f32 vF0[4];
    u8 pad100[0x20];
    u8 x120[0x10];
} __attribute__((aligned(8))) W9F;
typedef struct { f32 a[4]; f32 b[4]; f32 c0; f32 c1; s32 c2; s32 c3; u8 pad[0x50]; } Q9F;
extern f32 D_002BBDFC;
extern f32 D_0048E8D4;
extern f32 D_00575090[][4];
extern s32 D_002E27A8;
s32 func_00137618(E9F *);
s32 func_00153d78(E9F *);
void func_0013dfb8(E9F *, void *);
s32 func_00135838(E9F *);
f32 func_00267390(f32 *, f32 *);
void func_00135b88(E9F *, f32 (*)[4]);
void sceVu0CopyMatrix(Mtx, Mtx);
void func_00162c5c(Mtx, Mtx, Mtx);
s32 func_0024edf0(Mtx, f32 (*)[4]);
void func_00116660(Q9F *);
u64 func_001166e8(Q9F *);
f32 func_001629b0(f32 *, f32 *);
void func_00124060(E9F *, f32 *);
void func_00135800(E9F *, f32, f32);
void func_001373f8(E9F *, f32);
static inline s32 inl_a(s32 v, W9F *b) {
    s32 w = v;
    if (w < 3 && v >= 0) return 1;
    return v == b->w4C;
}
static inline s32 inl_b(s32 v, W9F *b) {
    s32 w = v;
    if (v < 124 && w >= 117) return 1;
    return v == b->w4C;
}
static inline s32 inl_c(s32 v, W9F *b) {
    s32 w = v;
    if (v >= 0 && (v < 3 || (v < 131 && w >= 124))) return 1;
    return v == b->w4C;
}
static inline s32 inl_d(s32 v, W9F *b) {
    s32 w = v;
    if (v < 49 && w >= 45) return 1;
    return v == b->w4C;
}
static inline void inl_rst(E9F *e, W9F *w) {
    if (e->x70 != 2) func_0013dfb8(e, w->x120);
}
static inline void inl_go(E9F *e, f32 *p) {
    func_00124060(e, p);
    func_00135800(e, 0.0f, 0.0f);
    func_00135800(e, 1.0f, 30.0f);
    ((S130 *)e->x130)->x18 = 1.0f;
    func_001373f8(e, 30.0f);
}
static inline s32 inl_find(E9F *e, W9F *w) {
    s32 i, bi;
    f32 best, d;
    f32 *p;
    best = D_0048E8D4;
    bi = -1;
    for (i = w->w60 + 1; i < 40; i += 10) {
        f32 v[4];
        f32 m10[8][4];
        Mtx m90;
        Q9F q;
        s32 vis;
        p = D_00575090[i];
        func_00267530(v, p, D_0035BD40.chr9F[0]->pos);
        { f32 a = v[1] * w->fE4; if (p) { if (0.0999999940395355224609375f < a) continue; } else { if (0.0999999940395355224609375f < a) continue; } }
        v[1] = 0.0f;
        { f32 a = func_00267390(v, w->vF0); if (p) { if (0.0999999940395355224609375f < a) continue; } else { if (0.0999999940395355224609375f < a) continue; } }
        func_00135b88(e, m10);
        sceVu0CopyMatrix(m90, e->mD0);
        func_002675a8(m90[3], p);
        m90[3][3] = 1.0f;
        func_00162c5c(m90, D_002BBFA0, m90);
        if (!func_0024edf0(m90, m10)) continue;
        func_00116660(&q);
        func_002675a8(q.a, p);
        func_002675a8(q.b, (*(f32 (*)[0x4])&D_002C58B0));
        q.c0 = e->x2C0;
        q.c1 = e->x2C4;
        q.c2 = 0;
        vis = func_001166e8(&q) == 0;
        if (vis) {
            d = func_001629b0(e->pos, p);
            if (d < best) {
                best = d;
                bi = i;
            }
        }
    }
    return bi;
}
#define func_00267530 ((void (*)(f32 *, f32 *, f32 *)) func_00267530)
#define func_002675a8 ((void (*)(f32 *, f32 *)) func_002675a8)
/* ---- func_00169f28 ---- */
s32 func_00169f28(E9F *e, W9F *w) {
    s32 ok, t;
    s32 i, bi;
    f32 best, d;
    f32 *p;
    if (w->b6) {
        if (e->x0 & 0x80) goto r0;
        w->b6 = 0;
        ((S130 *)e->x130)->x18 = w->f34;
        goto r0;
    }
    ok = 0;
    if (D_00574FB4 != 1) {
        if (D_00574FB4 == 0) goto r0;
    } else if ((s32)(e->x370 >> 50) & 1) return 0;
    if (!func_00137618(e)) return 0;
    { s32 r = func_00153d78(e); s32 t2; if (r || (e->x0 & 0x200)) t2 = 1; else t2 = 0; if (t2) goto r0; }
    if (0.0f < w->f70) w->f70 -= D_002BBDFC;
    if (0.0f < w->f70) goto r0;
    if (w->w58 >= 240) ok = 1;
    else if (w->w58 >= 160 || (w->w58 >= 80 && D_0057508C != 0)) {
        s32 save = w->w4C;
        w->w4C = -1;
        switch (e->x70) {
        case 10: case 13: case 15: case 18: case 26: inl_rst(e, w); break;
        case 0: ok = inl_a(e->x164, w); break;
        case 8: ok = inl_b(e->x164, w); break;
        case 24: ok = inl_c(e->x164, w); break;
        case 17: ok = inl_d(e->x164, w); break;
        }
        w->w4C = save;
    }
    if (!ok) goto r0;
    if (func_00135838(e)) goto r0;
    bi = inl_find(e, w);
    if (bi >= 0) {
        inl_go(e, D_00575090[bi]);
        w->b6 = 1;
        w->w58 = 0;
        w->w60 = 0;
        if (D_002E27A8 == 2) w->f70 = 600.0f;
        else w->f70 = 240.0f;
        return 1;
    }
    w->w60++;
    if (w->w60 >= 10) w->w60 = 0;
    goto r0;
r0:
    return 0;
}
#undef func_00267530
#undef func_002675a8


/* Hand-matched functions near 0x148BC0-0x14EE00 (worker 34). */
#include "common.h"
#include "platform/math.h"
#include "data/bss_0054.h"

/* ---- shared data ---- */
extern f32 D_002BBDFC;

/* party member records (D_00304BE8->m[i], 0x74 bytes each) */
/* actors: x6c stats, x370 flag word */
typedef struct { u8 pad[0x3c]; s32 cur; s32 max; s32 mcur; s32 mmax; } W34St;
typedef union { u64 x; struct { u32 lo; u32 l19:19; u32 b51:1; u32 hi:12; } b; } W34F370;
typedef struct { u8 pad[0x6c]; W34St *st; u8 pad70[0x370 - 0x70]; W34F370 x370; } W34Act;
W34Act *func_00123488(u32);

/* list walker entries (func_00132040) */
typedef struct { s32 x0; u8 pad4[0x44]; s16 x48; u8 pad4a[0xe]; u8 x58; u8 x59; } W34Ent;
W34Ent *func_00132040(W34Ent *);
s32 func_00142240(s32);

/* summon/effect slots: D_0054C1B0[3] (0x20 bytes), D_0054C218[9] (0x3c bytes) */
#include "data/types/text_00140000_h34.h"
typedef struct { u8 pad[0x4c]; u16 x4c; } W34O130;

/* player x148 block */
typedef struct { u8 pad[0x100]; f32 x100; u64 f:32; } W34Tm;

/* ---- callees ---- */
s32 func_0011ef38(void (*f)(void));
void func_0011ef10(s32 a, void (*f)(void));
void func_00267530(f32 *, f32 *, f32 *);
void func_002675a8(f32 *, f32 *);
f32 func_00120bf8(f32 *);
void func_0014c448();
s32 func_00130340(void *, s32, f32);
void func_00130578(void *, s32, f32);
void func_0014f658(void *, s32);
f32 func_0014cc88(void *, f32);
void func_00130398(void *, s32, f32);
f32 atan2f(f32, f32);

/* 0x148BC0 */

/* 0x148F08 */
u8 D_0054B818[0x908] ALIGNED(8);

/* 0x148FB0: restore HP */

/* 0x149090: restore MP */

/* 0x149170: use a recovery item (needs func_00148fb0 defined above) */

/* 0x149860 */

/* 0x1499A0 */

/* 0x149A88 */

/* 0x149BD0 */

/* 0x149FA0 */

/* 0x14A0F0 */

/* 0x14A238 */

/* 0x14AF60 */

/* 0x14C5C8 */
typedef struct { u8 pad[4]; s32 x4; } W34Pad;
typedef struct { u8 pad[0x30]; f32 pos[4]; u8 pad40[0x148 - 0x40]; W34Tm *x148; } W34Pl;
void func_0014c5c8(W34Pl *o, W34Pad *b, f32 *v) {
    s32 m;
    if (v[0] == 0.0f && v[1] == 0.0f && v[2] == 0.0f) {
        func_002675a8(v, o->pos);
        v[3] = 0.0f;
    }
    if (o->x148->x100 > 0.0f) {
        o->x148->x100 -= D_002BBDFC;
    } else {
        if (o->x148->f & 1) m = b->x4 & 0x10;
        else m = b->x4 & 4;
        if (!m) func_0014c448(o, b->x4);
    }
}

/* 0x14CA38 */
typedef struct { s32 x0; u8 pad4[0xc]; f32 x10[4]; u8 pad20[0x50]; s32 x70; u8 pad74[0x148 - 0x74]; W34Tm *x148; u8 pad14c[0x490 - 0x14c]; f32 x490[4]; } W34Pl2;
extern u32 D_002C5958;
extern f32 D_0054F444;
s32 func_0014db20(W34Pl2 *);
s32 func_0014ca38(W34Pl2 *o, s32 a) {
    f32 v[4] __attribute__((aligned(16)));
    if ((D_002C5958 >> 5 & 1) && func_0014db20(o)) {
        o->x0 &= ~4;
        return 8;
    }
    if (!a) goto call;
    if (o->x148->x100 <= 0.0f) {
        func_00267530(v, o->x10, o->x490);
        if (v[1] < 0.0f) {
        call:
            func_0014c448(o);
        } else if (func_00120bf8(v) / D_0054F444 < 0.7f) func_0014c448(o);
    }
    return o->x70;
}

/* 0x14CB90 */
#include "data/pieces/D_002E27C8.h"
typedef struct { u32 x0; u8 pad4[0x144]; W34Tm *x148; u8 pad14c[0x3b0 - 0x14c]; f32 x3b0; u8 pad3b4[0x3d0 - 0x3b4]; s32 x3d0; } W34Pl3;
s32 func_0014cb90(W34Pl3 *o) {
    s32 r;
    if (o->x0 & 0x2000) o->x3d0 = 171;
    else if ((*(u32 *)&D_002E27C8) >> 9 & 1) o->x3d0 = 5;
    else o->x3d0 = 0;
    r = func_00130340(o, (o->x3d0 + 4) | 0x10000, 0.0f);
    func_0014f658(o, 1);
    o->x3b0 = 0.0f;
    o->x148->x100 = 0.0f;
    return r;
}

/* 0x14D070 */
typedef struct {
    u8 pad[0x70];
    s32 x70;
    u8 pad74[0x2a0 - 0x74];
    f32 x2a0[4];
    u8 pad2b0[0x20];
    s32 x2d0;
    u8 pad2d4[0xc];
    f32 x2e0[4];
    u8 pad2f0[0x3b4 - 0x2f0];
    f32 x3b4;
    u8 pad3b8[0x3c4 - 0x3b8];
    f32 x3c4;
    u8 pad3c8[8];
    s32 x3d0;
} W34Pl4;
void func_0014d070(W34Pl4 *o, f32 *b) {
    f32 v[4] __attribute__((aligned(16)));
    func_00267530(v, o->x2e0, o->x2a0);
    if (b[1] < v[1]) {
        switch (o->x70) {
        case 2:
            o->x3b4 += v[1] - b[1];
            if (b[1] < 0.0f && (o->x2d0 & 8)) {
                func_0014cc88(o, 0.0f);
                o->x3b4 = o->x2e0[1];
                func_00130340(o, o->x3d0 + 5, 6.0f);
                func_00130578(o, o->x3d0 + 6, 0.0f);
            }
            break;
        case 3:
            if (b[1] < 0.0f && (o->x2d0 & 8)) o->x3c4 = 0.0f;
            break;
        }
    }
}

/* 0x14D210 */
typedef struct { u32 x0; u8 pad4[0x1c]; f32 x20[4]; u8 pad30[0x150 - 0x30]; f32 x150; u8 pad154[0x10]; s32 x164; } W34Pl5;
extern s32 D_002C5C54;
s32 func_0014d180(W34Pl5 *);
s32 func_00140370(W34Pl5 *, f32 *);
s32 func_0013f618(W34Pl5 *, f32 *);
s32 func_0015cc48(W34Pl5 *, f32 *);
s32 func_001507d0(W34Pl5 *, f32 *);
s32 func_00144510(W34Pl5 *, f32 *);
void func_0014d210(W34Pl5 *o, f32 *v) {
    if (!(o->x0 & 0x2000) && func_0014d180(o)) {
        if (func_00140370(o, v)) return;
        if (func_0013f618(o, v)) return;
        if (!D_002C5C54 && func_0015cc48(o, v)) return;
        if (func_001507d0(o, v)) return;
    }
    if (func_00144510(o, v)) return;
    if (v[3] > 0.0f && !(o->x0 & 0x400)) {
        o->x150 = atan2f(v[0], v[2]);
        if (o->x164 == 220) func_00130398(o, 6, 8.0f);
    }
    func_002675a8(o->x20, v);
}

/* 0x14E400 */
typedef struct { u8 pad[0x100]; union { u64 x; struct { u32 lo; u32 l2:2; u32 b34:1; u32 hi:29; } b; } x100; } W34T148b;
typedef struct {
    u8 pad[0x130];
    W34O130 *x130;
    u8 pad134[0x14];
    W34T148b *x148;
    u8 pad14c[0x370 - 0x14c];
    union { u64 x; struct { u32 lo; u32 l28:28; u32 b60:1; u32 hi:3; } b; } x370;
    u8 pad378[0x3cc - 0x378];
    f32 x3cc;
} W34Pl6;
void func_0014e3a0(W34Pl6 *);
s32 func_0014e400(W34Pl6 *o, s32 a) {
    W34T148b *t = o->x148;
    if ((t && t->x100.b.b34) || o->x3cc <= 0.0f || a) {
        if (t) t->x100.x &= ~(1LL << 34);
        return 8;
    }
    if (o->x130->x4c == 8) return 8;
    if (o->x370.b.b60) return 8;
    func_0014e3a0(o);
    return 2;
}

/* 0x14E510 */
s32 func_0014e510(s32 key) {
    W34Ent *p = 0;
    s32 n = 0;
    while ((p = func_00132040(p))) {
        if (p->x58 == key) {
            W34Act *a = func_00123488(p->x0);
            if (!a) {
                if (func_00142240(p->x0) != 1) n++;
            } else if (!a->x370.b.b51) n++;
        }
    }
    return n;
}

/* 0x14E5B8 */
#include "data/pieces/D_00350D78.h"
s32 func_0014e5b8(f32 *p) {
    Box57_f1b8 *b;
    s32 m, n, i;
    if (!D_00350D78) return 0;
    n = D_00350D78->n;
    b = D_00350D78->box;
    m = 0;
    for (i = 0; i < n; i++, b++) {
        if ((b->u.flags & 0x200) || (p[0] >= b->lo[0] && p[0] <= b->hi[0] && p[2] >= b->lo[2] && p[2] <= b->hi[2]))
            m |= 1 << (b->u.c.id - 1);
    }
    return m;
}

/* 0x14EC60 */
typedef struct { s32 x0; s32 x4; f32 x8; f32 xc; s32 x10; s32 x14; } W34Grp;
extern W34Grp D_0054F450[]; /* src/data/bss_0054.c: Grp57_f1b8 D_0054F450[0x1f] */
void func_0014ec60(s32 g) {
    W34Grp *e = &D_0054F450[g - 1];
    s32 n = 0;
    W34Ent *p = 0;
    while ((p = func_00132040(p))) {
        if (p->x58 == g && e->x14 >= p->x48 && func_00142240(p->x0) != 1) n += p->x59;
    }
    if (e->x10 >= n) e->x14++;
}

/* 0x14ED30 (calls func_0014ec60 above) */
extern W34Grp D_0054F438[];
extern s32 D_0054F448;
typedef struct { u8 pad[0x58]; u8 x58; } W34O130b;
typedef struct { u8 pad[4]; s32 x4; u8 pad8[0x128]; W34O130b *x130; u8 pad134[0x370 - 0x134]; W34F370 x370; } W34Act4;
void func_001421d0(s32, s32);
void func_0014ed30(W34Act4 *o) {
    s32 i;
    if (o->x370.b.b51) {
        if (o->x130->x58) {
            if (!(D_0054F438[o->x130->x58].x0 & 1)) func_001421d0(o->x4, 1);
            func_0014ec60(o->x130->x58);
        } else {
            func_001421d0(o->x4, 1);
        }
    }
    for (i = 0; i < 31; i++) {
        if (D_0054F448 >> i & 1) D_0054F450[i].xc = D_0054F450[i].x8;
    }
}
#include "data/data_002C.h"
#include "data/pieces/D_002C5958.h"
#include "data/pieces/D_002BBDFC.h"

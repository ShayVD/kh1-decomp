/* Object data slots, default flags (docs/modules.md "Session 52"): the 64
 * slot headers D_00550400 for the 0x40000-byte areas at D_00FE0000 that
 * object files load into (func_00155760, func_001560f8 starts a load task,
 * the pool D_0054F970 / D_0054F980 is defined here).  The rest is in
 * objslot.nofill.c and objslot.nostrict.c.  Read from the code, not proved by a boot. */
#include "m2c.h"
#include "actor.h"
#include "data/pieces/D_00304BE8.h"
#include "data/bss_0055.h"
#include "data/pieces/D_002C58B0.h"
#include "data/pieces/D_002E31B0.h"
#include "data/pieces/D_00350CE0.h"
#include "common.h"
#include "platform/math.h"
#include "data/bss_0054.h"
#include "data/pieces/D_00350D78.h"
#include "data/types/text_00140000_h9_p.h"
#include "data/pieces/D_00350D88.h"
#include "data/types/text_00140000_h9.h"
#include "data/pieces/D_002E26A0.h"
#include "data/pieces/D_00308CDC.h"
#include "data/pieces/D_002C58A0.h"

/* func_00155730 (from auto/text_00150000.c). */
M2C_UNK func_00146b90(void *, M2C_UNK, M2C_UNK, M2C_UNK);
void func_00155730(void *arg0) {
    func_00146b90(arg0 + M2C_FIELD(arg0, s32 *, 0x1C), -6, 0, 0);
}

/* func_00155760 (from auto/text_00150000_3.c). */
extern s8 D_00550400;
extern s8 D_00FE0000;
#define func_00155730 ((s32 (*)(s32)) func_00155730)
void func_00155760(s32 arg0) {
    s32 *temp_v1;
    s8 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s8 *, 0x55);
    temp_v1 = &D_00550400 + (temp_v0 * 0x48);
    *temp_v1 |= 0x10000;
    func_00155730((s32) (&D_00FE0000 + (temp_v0 << 0x12)));
}
#undef func_00155730

/* func_001557b0 (from auto/text_00150000.c). */
s32 func_001320a8();
#define func_00155760 ((M2C_UNK (*)(s32)) func_00155760)
void func_001557b0(void) {
    func_00155760(func_001320a8());
}
#undef func_00155760

/* func_00155878 (from hand/text_00140000_s6_07.c). */
typedef struct { s8 id; u8 n; u8 x2; u8 x3; u8 pad[0x44 - 4]; s32 x44; } E5878;
typedef struct { u8 pad[0x1c]; s32 off; s32 end; u8 rest[0x40000 - 0x24]; } R5878;
extern s32 D_002C5958;
void func_00146928(s32);
extern E5878 D_00550400_00155878[] __asm__("D_00550400");
#define D_00550400 D_00550400_00155878
extern R5878 D_00FE0000_00155878[] __asm__("D_00FE0000");
#define D_00FE0000 D_00FE0000_00155878
#define func_00146b90 ((void (*)(void *, s32, s32, s32)) func_00146b90)
void func_00155878(void) {
    s32 i, j;
    E5878 *p;
    R5878 *r;

    D_002C5958 &= ~0x40000;
    func_00146928(-6);
    for (i = 0; i < 64; i++) {
        p = &D_00550400[i];
        if (p->id != i) continue;
        if (!(*(u32 *)p & 0x10000)) continue;
        for (j = 0; j < p->n; j++) {
            if (p->id != p[j].id) { p = 0; break; }
        }
        if (!p) continue;
        r = &D_00FE0000[i];
        if (r->end - r->off > 0) func_00146b90((u8 *)r + r->off, -6, 0, 0);
    }
}
#undef D_00550400
#undef D_00FE0000
#undef func_00146b90

/* func_001559a8 (from hand/text_00140000_h9.c). */
typedef struct {
    union {
        s32 w;
        struct { s8 b0; u8 b1; u8 b2; u8 b3; } b;
        struct { u32 lo:16; u32 f16:1; u32 f17:1; u32 f18:1; u32 hi:13; } f;
    } h;
    u8 pad4[0x24 - 4];
    char name[0x20];
    s32 x44;
} W9Blk;
extern W9Blk D_00550400_001559a8[] __asm__("D_00550400");
#define D_00550400 D_00550400_001559a8
extern u8 D_00FE0000_001559a8[] __asm__("D_00FE0000");
#define D_00FE0000 D_00FE0000_001559a8
s32 func_001559a8(u8 *p) {
    s32 i = (p - D_00FE0000) / 0x40000;
    return D_00550400[i].x44;
}
#undef D_00550400
#undef D_00FE0000

/* func_00155a50 (from hand/text_00140000_h9.c). */
extern W9Blk D_005512A0[0xc];
extern u8 D_01CE0000[];
u8 *func_00155a50(void) {
    s32 i;
    for (i = 0; i < 12; i++) {
        D_005512A0[i].h.b.b0 = -1;
        D_005512A0[i].h.w |= 0x20000;
    }
    return D_01CE0000;
}

/* func_00155a90 (from hand/text_00140000_h9.c). */
s32 func_00155a90(void) {
    s32 i;
    for (i = 0; i < 12; i++) {
        if (!(D_005512A0[i].h.w & 0x20000)) return 1;
    }
    return 0;
}

/* func_00155ad8 (from hand/text_00140000_h9.c). */
extern W9Blk D_00550400_00155ad8[] __asm__("D_00550400");
#define D_00550400 D_00550400_00155ad8
s32 func_00155ad8(s32 i, s32 n) {
    W9Blk *p = &D_00550400[i];
    s32 j;
    for (j = 0; j < n; j++) {
        if (p[j].h.b.b0 != i || p[j].h.b.b1 != n) {
            for (j = 0; j < n; j++) {
                p[j].h.b.b0 = i;
                p[j].h.b.b1 = n;
            }
            return 0;
        }
    }
    return 1;
}
#undef D_00550400

/* func_00155b70 (from hand/text_00140000_h9.c). */
typedef struct {
    s32 x0;
    s32 x4;
    s32 x8;
    s32 xc;
    s32 x10;
    s32 x14;
    s32 x18;
} W9Hdr;
void func_00162058(void *p);
void func_001763f0(void *p);
void func_0015c9f8(void *p);
void func_00155b70(W9Hdr *h) {
    func_00162058((u8 *)h + h->x4);
    if (h->xc - h->x8 > 0) func_001763f0((u8 *)h + h->x8);
    if (h->x18 - h->x14 > 0) func_0015c9f8((u8 *)h + h->x14);
}

/* func_00155be0 (from hand/text_00140000_h9.c). */
void func_00155be0(s32 *h) {
    s32 i;
    func_00162058((u8 *)h + h[1]);
    if (h[4] - h[3] > 0) {
        h = (s32 *)((u8 *)h + h[3]);
        for (i = 0; i < 10; i++) {
            if (h[i + 2] - h[i + 1] > 0) func_00155be0((s32 *)((u8 *)h + h[i + 1]));
        }
    }
}

/* func_00155c68 (from hand/text_00140000_h9.c). */
extern W9Blk D_00550400_00155c68[] __asm__("D_00550400");
#define D_00550400 D_00550400_00155c68
extern u8 D_00FE0000_00155c68[] __asm__("D_00FE0000");
#define D_00FE0000 D_00FE0000_00155c68
void func_00155c68(u32 size, s32 a1, u8 *h) {
    W9Blk *q;
    s32 i;
    func_00155b70((W9Hdr *)h);
    i = (h - D_00FE0000) / 0x40000;
    q = &D_00550400[i];
    q->x44 = (s32)(h + ((size + 127) >> 7 << 7));
    q->h.b.b3++;
}
#undef D_00550400
#undef D_00FE0000

/* func_00155cf8 (from hand/text_00140000_s6_07.c). */
extern E5878 D_00550400_00155cf8[] __asm__("D_00550400");
#define D_00550400 D_00550400_00155cf8
void func_00155cf8(s32 a0, s32 a1, s32 key) {
    s32 i;
    E5878 *p;

    p = D_00550400;
    for (i = 0; i < 64; i++, p++) {
        if (p->id == i && p->x44 == key) break;
    }
    p->x3++;
    func_00155be0(key);
}
#undef D_00550400

/* func_00155e48 (from hand/text_00140000_h9.c). */
s32 strcmp(const char *, const char *);
extern W9Blk D_00550400_00155e48[] __asm__("D_00550400");
#define D_00550400 D_00550400_00155e48
s32 func_00155e48(s32 i, s32 n, const char *name) {
    W9Blk *p = &D_00550400[i];
    s32 j;
    if (p->h.b.b0 != i || strcmp(p->name, name)) return 0;
    for (j = 0; j < n; j++) {
        if (p[j].h.b.b0 != i) return 0;
    }
    return 1;
}
#undef D_00550400

/* func_00155ee8 (from auto/text_00150000_2.c). */
void func_00155ee8(void *arg0) {
    M2C_FIELD(arg0, u8 *, 3) = (u8) (M2C_FIELD(arg0, u8 *, 3) + 1);
}

/* func_001560f8 (from hand/text_00140000_h9.c). */
typedef struct {
    u8 pad0[8];
    u8 *x8;
    u8 padc[0x55 - 0xC];
    s8 x55;
} W9Obj55;
typedef struct {
    u8 pad0[0x14];
    W9Obj55 *x14;
    s32 x18;
} W9Task;
extern u8 D_0054F970[];
void func_00155ef8(void);
W9Task *func_0011f090(void *q, s32 a, void (*fn)(void));
extern W9Blk D_00550400_001560f8[] __asm__("D_00550400");
#define D_00550400 D_00550400_001560f8
extern u8 D_00FE0000_001560f8[] __asm__("D_00FE0000");
#define D_00FE0000 D_00FE0000_001560f8
#define func_001320a8 ((W9Obj55 *(*)(s32 a)) func_001320a8)
s32 func_001560f8(s32 a0, s32 a1) {
    W9Obj55 *o = func_001320a8(a0);
    s32 k = o->x55;
    W9Task *t;
    if (k < 0) return 0;
    D_00550400[k].h.b.b3 = 0;
    o->x8 = D_00FE0000 + (k << 18);
    t = func_0011f090(D_0054F970, 0, func_00155ef8);
    t->x14 = o;
    t->x18 = a1;
    return 1;
}
#undef D_00550400
#undef D_00FE0000
#undef func_001320a8

/* func_00156188 (from auto/text_00150000_16.c). */
M2C_UNK func_0011f130(M2C_UNK *, M2C_UNK);
#define D_0054F970 (*(M2C_UNK (*)) &D_0054F970)
s32 func_00156188(void) {
    func_0011f130(&D_0054F970, 0);
    return 0;
}
#undef D_0054F970

/* func_001561b0 (from hand/text_00140000_h9.c). */
extern W9Blk D_00550400_001561b0[] __asm__("D_00550400");
#define D_00550400 D_00550400_001561b0
void func_001561b0(void) {
    s32 i;
    for (i = 0; i < 64; i++) {
        D_00550400[i].h.f.f16 = 0;
        D_00550400[i].h.f.f18 = 0;
    }
}
#undef D_00550400

/* func_001561f8 (from auto/text_00150000_3.c). */
M2C_UNK func_0011efa8(M2C_UNK *, M2C_UNK *, M2C_UNK, M2C_UNK);
M2C_UNK D_0054F980[0x2a0] ALIGNED(64);
s32 func_0011ef38(M2C_UNK *);
void *func_0011ef10(M2C_UNK, M2C_UNK *);
#define D_0054F970 (*(M2C_UNK (*)) &D_0054F970)
void func_001561f8(void) {
    func_0011efa8(&D_0054F970, &D_0054F980, 0x1C, 0x60);
    if (func_0011ef38(&func_00156188) == 0) {
        M2C_FIELD(func_0011ef10(0x15F90, &func_00156188), s16 *, 2) = -1;
    }
}
#undef D_0054F970


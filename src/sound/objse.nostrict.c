/* Object sounds and voices, without strict aliasing (docs/modules.md
 * "Session 52"): func_001571a8 loads a party member's voice bank (a ".vsb"
 * named from the member) into D_00551608, func_00157818 queues a sound for
 * an object, the task func_00157c60 and its setup func_00157dc8.  Read from the code, not proved by a boot. */
#include "common.h"
#include "platform/vu.h"
#include "data/pieces/D_00308CDC.h"
#include "data/pieces/D_00304BE8_s.h"
#include "platform/math.h"
#include "data/types/nostrict_text_00150000_h58_p.h"
#include "data/pieces/D_002E31B0.h"
#include "data/pieces/D_002C58A0.h"
#include "data/pieces/D_002E26A0.h"
#include "data/pieces/D_002C58B0.h"
#include "data/pieces/D_00351A30.h"
#include "data/pieces/D_002E31A8.h"
#include "data/pieces/D_002E3168.h"
#include "data/pieces/D_002E2790.h"
#include "data/pieces/D_002E2780.h"
#include "data/types/nostrict_text_00150000_h58.h"
#include "data/bss_0055.h"
#include "data/types/nostrict_text_00150000_h35.h"
#include "data/pieces/D_002BC0F0.h"
#include "data/pieces/D_003519E0.h"
#include "data/pieces/D_0037A378.h"
#include "data/pieces/D_00304BE8.h"

/* func_001571a8 (from hand/nostrict/text_00150000_h58.c). */
void *func_00121e28(s32, void *);
char *strcpy(char *, const char *);
char *strcat(char *, const char *);
s32 func_00120748(char *, void *, void *, s32);
extern E1608 D_00551608[];
extern s32 D_002BC128;
extern char D_00351990[];
typedef struct { s32 x0; s32 x4; void *x8; u8 padc[4]; void (*x10)(void); } Tk;
void func_00112298(s32, s32, s32, char *);
char *func_0013dbb0(s32);
s32 strcmp(const char *, const char *);
void *func_001559f0(s32, s32);
void *func_001208e0(void *);
void func_001570d0();
/* ---- func_001571a8 ---- */
s32 func_001571a8(s32 i, void (*cb)(void)) {
    s32 k, n, j, j0;
    E1608 *e;
    Tk *t;
    void *x;
    if (!D_002BC128) {
        D_005516C0[i] = -1;
        goto done;
    }
    if (i < 3) {
        func_00112298(D_002BC128, 0, 0, D_00351990 + 6);
        D_00351990[8] = '_';
        strcpy(D_00351990 + 9, func_0013dbb0(i));
    } else {
        strcpy(D_00351990 + 6, func_0013dbb0(i));
    }
    strcat(D_00351990, ".vsb");
    k = -1;
    if (i == 0) { j0 = 0; n = 1; } else { j0 = 1; n = 3; }
    for (e = &D_00551608[j0], j = j0; j < n; j++, e++) {
        if (e->b0 == i && !strcmp(e->name, D_00351990)) {
            e->b1 |= 1;
        done:
            if (cb) cb();
            return 0;
        }
        if (k < 0 && !(e->b1 & 1)) k = j;
    }
    e = &D_00551608[k];
    e->b0 = i;
    e->b1 |= 1;
    strcpy(e->name, D_00351990);
    D_005516C0[i] = k;
    x = func_001559f0(54, 2);
    func_00120748(D_00351990, x, 0, 0);
    t = func_00121e28(20, (u8 *)func_001208e0(func_001570d0) + 72);
    t->x10 = cb;
    t->x4 = k;
    t->x8 = x;
    t->x0 = 0;
    return 1;
}

/* func_00157400 (from hand/nostrict/text_00150000_h35.c). */
typedef struct { u8 pad[0x48]; void *p48; } Task157400;
void func_001573d8(s32);
#define func_001571a8 ((s32 (*)(s32, s32)) func_001571a8)
#define func_001208e0 ((Task157400 *(*)(void *)) func_001208e0)
/* ---- func_00157400 ---- */
void func_00157400(void (*cb)(s32)) {
    s32 i, n = 0;
    u8 *q;
    for (i = 0; i < 3; i++) {
        q = (u8 *)(i + (s32)D_00304BE8) + 0x48E;
        if (*q != 0xFF) {
            if (func_001571a8(*q, 0)) n++;
        }
    }
    if (n > 0) {
        func_001208e0(func_001573d8)->p48 = cb;
    } else {
        cb(-1);
    }
}
#undef func_001571a8
#undef func_001208e0

/* func_001576a8 (from hand/nostrict/text_00150000_h35.c). */
void func_001315c0(s32, s32, void *, f32);
s32 func_00122ff8(Act1576a8 *);
void func_0011dcf0(void *, s32 *, s32 *);
void func_001ed7d8(s32, s32, s32, s32);
void func_001ed6f0(s32, s32, s32);
/* ---- func_001576a8 ---- */
void func_001576a8(E551670 *e) {
    f32 v[4];
    s32 x, y;
    f32 b, d;
    if (func_00122ff8(e->w4)) {
        func_001315c0((s32)e->w4, e->w4->p6C->w74, v, 0.0f);
        func_0011dcf0(v, &x, &y);
        b = (f32)e->w10;
        d = 16383.0f - b;
        x = b + d * ((f32)x / 16383.0f);
        y = b + d * ((f32)y / 16383.0f);
        if (e->b1 == 0) {
            func_001ed7d8(e->b2, e->b3, x, y);
        } else {
            func_001ed6f0(e->wC, x, y);
        }
    }
}

/* func_00157818 (from hand/nostrict/text_00150000_h35.c). */
extern u32 D_002C5958;
typedef struct { u8 pad[0x4C]; u16 h4C; } S130_157818;
typedef struct { u8 pad[0x6C]; s32 w6C; u8 pad70[0x4D]; s8 idx; } S6C_157818;
typedef struct { u8 pad[0x6C]; S6C_157818 *p6C; u8 pad70[0xC0]; S130_157818 *p130; u8 pad134[0x374]; s32 *tbl; } Obj157818;
extern E551670 D_00551670[];
void func_00157648(void);
/* ---- func_00157818 ---- */
E551670 *func_00157818(Obj157818 *a, s32 k) {
    E551670 *e;
    u32 h;
    s8 v;
    func_00157648();
    if ((D_002C5958 >> 20) & 1) return 0;
    e = &D_00551670[a->p6C->idx];
    h = a->p130->h4C;
    if (h < 10) {
        v = D_005516C0[h];
        if (v < 0) return 0;
        e->b2 = v;
        e->b1 = 0;
    } else {
        if (a->tbl == 0 || k >= *a->tbl) return 0;
        e->b1 = 1;
        e->wC = (s32)a->tbl + a->tbl[k + 1];
    }
    e->b3 = k;
    e->w4 = (Act1576a8 *)a;
    e->b0 = 2;
    e->w10 = a->p6C->w6C;
    return e;
}

/* func_00157a00 (from hand/nostrict/text_00150000_h58.c). */
void func_001358b8(void *, s32);
void func_00157910(void *, s32, s32);
void func_00157a00(void *a, s32 v, s32 b) {
    func_00157910(a, v, b);
    func_001358b8(a, 35);
}

/* func_00157a30 (from hand/nostrict/text_00150000_h58.c). */
typedef S31b0_2e31b0 P8;
typedef struct {
    u32 w0; s32 w4; s32 w8; s32 wC; s32 x10; f32 f14; s32 x18; f32 f1c; s32 x20; u8 pad24[0xc]; V4 v30; f32 f40; f32 f44; s32 x48; s32 x4c;
} S144;
typedef struct {
    u8 pad0[0x10]; V4 pos; u8 pad20[0x10]; V4 v30; u8 pad40[0x30]; s32 x70; u8 pad74[0xf0]; s32 x164;
} S98;
typedef struct { u8 pad0[5]; u8 b5; u8 pad6[0xe]; struct { u8 pad0[1]; u8 b1; } *x14; } S134;
#define ACT_BODY(T144) \
    u32 w0; u8 pad4[4]; s32 x8; u8 padc[4]; V4 pos; V4 x20; V4 x30; V4 x40; u8 pad50[0x18]; s32 x68; struct { u8 pad[0x3c]; s32 x3c; } *x6c; s32 x70; P8 x74; u8 pad7c[0xc]; s32 x88; s32 x8c; u64 x90; S98 *x98; u8 pad9c[0x24]; V4 xc0; f32 xd0[4][4]; u8 pad110[0x10]; V4 x120; \
    struct { u8 pad[0x44]; f32 x44; s16 x48; u8 pad4a[2]; u16 x4c; } *x130; S134 *x134; u8 pad138[0xc]; T144 *x144; \
    struct { u8 pad[0x160]; V4 v160; } *x148; u8 pad14c[0x1d4]; V4 x320; u8 pad330[0x40]; u64 x370; u8 pad378[0x26]; u8 x39e; u8 pad39f[0x11]; f32 x3b0; u8 pad3b4[0xc]; V4 x3c0; u8 pad3d0[0x14]; f32 x3e4; u8 pad3e8[8]; V4 x3f0; s32 x400; u8 pad404[0x9c]; void *x4a0;
typedef struct Actor_57a30 { ACT_BODY(S144) } Act;
f32 func_00176850(void);
typedef struct { s8 id; s8 w; } Ent12;
typedef struct { u8 b0; Ent12 e[5]; } Rec12;
extern s32 D_003519B0[];
extern s32 D_002BC130;
extern s32 D_002BC134;
Rec12 *func_001477c8(s32);
#define func_00122ff8 ((s32 (*)(void *)) func_00122ff8)
void func_00157a30(Act *a, s32 k, Act *b) {
    s32 cand[5];
    s32 n = 0;
    Rec12 *t = func_001477c8(D_003519B0[a->x130->x4c]) + k;
    s32 r = func_00176850() * 100.0f;
    s32 i;
    s32 v;
    if (D_002BC128 == 3 && D_002BC130 == 2 && D_002BC134 == D_002BC130) b = 0;
    for (i = 0; i < 5; i++) {
        switch (t->e[i].id) {
        case -2:
            v = -1;
            break;
        case -1:
            continue;
        case -3:
            if (!func_00122ff8(b)) continue;
            if (b->x130->x4c >= 10) continue;
            if (b->x130->x4c == a->x130->x4c) continue;
            if (r < t->e[i].w) {
                func_00157a00(a, b->x130->x4c, t->b0);
                return;
            }
            continue;
        default:
            v = t->e[i].id;
            break;
        }
        if (t->e[i].w > 0) {
            r -= t->e[i].w;
            if (r < 0) {
                if (v >= 0) func_00157a00(a, v, t->b0);
                return;
            }
        } else {
            cand[n] = v;
            n++;
        }
    }
    if (n > 0) {
        v = cand[(s32)(func_00176850() * n)];
        if (v >= 0) func_00157a00(a, v, t->b0);
    }
}
#undef func_00122ff8
#undef ACT_BODY

/* func_00157c60 (from hand/nostrict/text_00150000_h58.c). */
extern f32 D_002BBDFC;
typedef struct { s8 b0, b1, b2, b3; void *w4; f32 w8; s32 wC; s32 w10; } E551670_57c60;
void func_0011ddd0(void);
s32 func_001ecfd8(void);
void func_001577a0(E551670_57c60 *);
s32 func_001ecd08(s32, s32, s32);
extern E551670_57c60 D_00551670_00157c60[] __asm__("D_00551670");
#define D_00551670 D_00551670_00157c60
#define func_00157818 ((void (*)(void *, s32)) func_00157818)
#define func_001576a8 ((void (*)(E551670_57c60 *)) func_001576a8)
/* ---- func_00157c60 ---- */
s32 func_00157c60(void) {
    s32 i;
    s32 busy = 0;
    E551670_57c60 *e;
    func_0011ddd0();
    for (i = 0, e = D_00551670; i < 4; i++, e++) {
        switch (e->b0) {
        case 0:
            break;
        case 1:
            e->w8 -= D_002BBDFC;
            if (e->w8 < 0.0f) func_00157818(e->w4, e->b3);
            break;
        case 2:
            if (e->b1 == 1 && busy) break;
            if (func_001ecfd8()) break;
            func_001577a0(e);
            e->b0 = 3;
            if (e->b1 == 1) busy = 1;
            break;
        case 3:
            e->b0 = 4;
            break;
        case 4:
            func_001576a8(e);
            switch (e->b1) {
            case 0:
                if (!func_001ecd08(e->b2, e->b3, 0)) e->b0 = 0;
                break;
            case 1:
                if (!func_001ecd08(-1, -1, e->wC)) e->b0 = 0;
                break;
            }
            break;
        }
    }
    return 0;
}
#undef D_00551670
#undef func_00157818
#undef func_001576a8

/* func_00157dc8 (from hand/nostrict/text_00150000_h35.c). */
typedef struct { s8 b0; u8 f0:1; u8 f1:7; u8 pad[32]; } E551608;
s32 func_0011ef38(void *);
void func_0011ef10(s32, void *);
extern E551608 D_00551608_00157dc8[] __asm__("D_00551608");
#define D_00551608 D_00551608_00157dc8
/* ---- func_00157dc8 ---- */
void func_00157dc8(void) {
    s32 i;
    for (i = 0; i < 3; i++) {
        D_00551608[i].b0 = -1;
        D_00551608[i].f0 = 0;
    }
    for (i = 0; i < 10; i++) {
        D_005516C0[i] = -1;
    }
    for (i = 0; i < 4; i++) {
        D_00551670[i].b0 = 0;
    }
    if (func_0011ef38(func_00157c60) == 0) {
        func_0011ef10(0x23669, func_00157c60);
    }
}
#undef D_00551608

/* func_00157ea8 (from hand/nostrict/text_00150000_h35.c). */
s32 func_00130340(void *, s32, f32);
typedef struct { f32 x, y, z, w; } Vec154768;
void func_00137688(void *, f32);
typedef struct { u8 pad[0x3C]; s32 w3C; s32 w40; s32 w44; s32 w48; u8 pad4c[0x72]; u16 hBE; } S6C_156c68;
typedef struct Actor_57ea8 {
    s32 w0;
    u8 pad4[0xc];
    Vec154768 v10;
    u8 pad20[0x1c];
    f32 f3C;
    u8 pad40[0x2c];
    S6C_156c68 *p6C;
    u8 pad70[0xc0];
    void *p130;
    u8 pad134[0x30];
    s32 w164;
    u8 pad168[0x4];
    f32 f16C;
    u8 pad170[0x1e0];
    s32 w350[4];
    u8 pad360[0x10];
    u64 d370;
} Pl1557d0;
typedef Pl1557d0 Obj157ea8;
typedef struct { u8 pad[4]; f32 f4; } Ret157ea8;
/* ---- func_00157ea8 ---- */
void func_00157ea8(Obj157ea8 *a) {
    Obj157ea8 *p;
    s32 i;
    a->w0 |= 0x02000270;
    a->d370 &= ~(3ULL << 37);
    p = D_002E26A0[0];
    if (func_00122ff8((Act1576a8 *)p)) {
        PlatVu0CopyVector(&a->v10, &p->v10);
        func_00137688(a, p->f3C);
        for (i = 0; i < 4; i++) {
            a->w350[i] = p->w350[i];
        }
        ((Ret157ea8 *)func_00130340(a, p->w164, 0.0f))->f4 = p->f16C;
    }
}


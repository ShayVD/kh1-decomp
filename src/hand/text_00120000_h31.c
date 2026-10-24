#include "common.h"
#include "data/bss_0051.h"
#include "data/bss_0052.h"

/* shared declarations */
#include "data/pieces/D_002E31B0.h"
#include "data/pieces/D_002E26A0.h"
extern u32 D_002C5958;
#include "data/pieces/D_002E31B8.h"

typedef struct { u8 pad[0x10]; volatile s32 n; } Q14;

extern s32 func_00122ff8(void *);
extern f32 func_0012ec60(struct Actor *, s32, f32 *);
extern void func_00267530(void *, void *, void *);
extern void func_0011ef10(s32, void *);
extern f32 func_00121748(f32 *, f32 *);

#include "data/types/text_00120000_h31_p.h"
extern A2 D_002C6814[];
extern void *D_002C64A0;
#include "data/pieces/D_002E26AC.h"
extern void func_001372a0(void);
extern void func_00138738(void);
extern s32 func_0011ef38(void *);
extern void func_00123790();

void func_00124b90(void) {
    s32 i;
    for (i = 0; i < 96; i++) D_002C6814[i].f0 = 0;
    D_002E26AC = &D_002C64A0;
    for (i = 0; i < 3; i++) D_002E26A0[i] = 0;
    func_001372a0();
    func_00138738();
    if (func_0011ef38(func_00123790) == 0)
        func_0011ef10(0x27cb9, func_00123790);
}

typedef struct { u8 pad[0x70]; s32 f70; u8 pad74[0x3c0 - 0x74]; f32 f3c0[4]; } E2;
#include "data/pieces/D_00308CDC.h"
extern void func_00130340(E2 *, s32, f32);
extern void func_00130578(E2 *, s32, f32);
extern void func_00267560(f32 *, f32 *, f32);
extern void func_001333e0(E2 *, s32, s32);

void func_00125be8(E2 *e, s32 a1) {
    switch (e->f70) {
    case 2:
        func_00130340(e, 0x100008a, 8.0f);
        func_00130578(e, 0x40000006, 0.0f);
        func_00267560(e->f3c0, e->f3c0, (*(Cfg_308cdc **)&D_00308CDC)->ff0);
        break;
    case 8:
        func_00130340(e, 0x100008a, 8.0f);
        func_00130578(e, 0x40000075, 8.0f);
        func_00267560(e->f3c0, e->f3c0, (*(Cfg_308cdc **)&D_00308CDC)->ff0);
        break;
    default:
        func_00130340(e, 0x100003d, 8.0f);
        func_00130578(e, 0x40000000, 0.0f);
        break;
    }
    func_001333e0(e, 0, a1);
}

extern float fabsf(float);
typedef struct { u8 pad[0x10]; f32 f10[16]; u8 pad50[0x3c4 - 0x50]; f32 f3c4; } E3;

void func_00125cf0(E3 *e, f32 k, f32 lim) {
    f32 v[4];
    f32 t, r;
    if (func_00122ff8((void *)D_002E31B0.f0) == 0) return;
    func_0012ec60(D_002E31B0.f0, D_002E31B0.f4, v);
    v[1] += 100.0f;
    func_00267530(v, v, e->f10);
    if (fabsf(v[1]) > 50.0f) {
        t = e->f3c4 + v[1] * k;
        if (t < -lim) r = -lim;
        else if (lim < t) r = lim;
        else r = t;
        e->f3c4 = r;
    }
}

#include "data/types/text_00120000_h31.h"
extern A6 D_004F7820[3];
extern B6 D_004F7C10[3];
extern D6 D_004F8270[];
extern u8 D_004F82D0[];
#include "data/pieces/D_00351BC8.h"
extern void func_001284a0(A6 *, s32);
extern void func_00128738(B6 *, s32);
extern void *func_0011fb38(s32, s32, void *);
extern void func_0011fb48(void *, s32, void *);
extern void func_0011fb78(void *, s32, void *);
extern void func_00267b08(void *, f32, f32, f32, f32, f32, f32, f32, f32, f32);
extern void func_00128440();

void func_00128b20(void) {
    s32 i;
    u8 *q, *d, *b;
    for (i = 0; i < 3; i++) {
        func_001284a0(&D_004F7820[i], i);
        func_00128738(&D_004F7C10[i], i);
    }
    q = (u8 *)D_004F8270;
    d = q;
    q += 16;
    b = q;
    q = func_0011fb38(0x47, 0x50000, b + 16);
    q = func_0011fb38(0x48, 0x50000, q);
    q = func_0011fb38(0x14, 0x60, q);
    func_0011fb48(b, 1, q);
    func_0011fb78(d, 7, q);
    D_00351BC8(0);
    func_00267b08(D_004F82D0, 32768.0f, 1.0f, 1.0f, 2048.0f, 2048.0f, 1.0f, 65535.0f, 1.0f, 65535.0f);
    func_0011ef10(0x1fbcf, func_00128440);
}
extern void func_0012cb40(Q14 *, s32, s32);

static inline s32 add(Q14 *q, s32 x) {
    s32 i = q->n++;
    func_0012cb40(q, i, x);
    return i;
}

typedef struct Actor {
    u32 f0;
    u8 pad4[0x2c];
    f32 f30[4];
    u8 pad40[0x30];
    s32 f70;
    u8 pad74[0xf0];
    s32 f164;
    u8 pad168[0x172];
    u16 f2da;
    u8 pad2dc[0x94];
    u64 f370;
} O16;
typedef O16 E18;

static inline f32 fmx(f32 a, f32 b) { return (b < a) ? a : b; }

typedef struct Ob50 Ob50;
typedef struct { u32 f0; u8 pad4[8]; void (*fc)(Ob50 *); } Sb50;
struct Ob50 { u32 f0; u8 pad4[0x15c]; u64 f160; u8 pad168[0x178 - 0x168]; s32 f178; Sb50 f17c; };

/* needs make: uses rodata */

typedef E18 E1;
#include "data/pieces/D_002E31A8.h"
extern f32 D_004F7800[];
extern s32 func_00137618(E1 *, s32);
extern void func_00105a30(s32, s32, f32 *);

s32 func_00125a28(s32 a0) {
    E1 *e;
    f32 buf[4];
    if (D_002E31B8 == 3) goto ret0;
    if (D_002C5958 & 0x12000) return 0;
    if ((D_002E31A8 >> 1) & 1) goto ret0;
    e = D_002E26A0[0];
    if (a0 & 1) {
        if (!func_00137618(e, 3)) return 0;
        func_00105a30(-1, e->f2da, buf);
        if (func_00121748(e->f30, buf) > -0.7f) return 0;
        if (func_00121748(D_004F7800, buf) > -0.7f) return 0;
    }
    if (a0 & 2) {
        switch (e->f164) {
        case 3: case 7: case 8:
        ret0:
            return 0;
        case 1: case 2: case 4: case 5: case 6: case 9: case 10: case 11:
            break;
        default:
            return 0;
        }
    }
    if (a0 & 4) {
        if (e->f70) return 0;
    }
    return 1;
}
#include "data/bss_004F_mixed.h"
#include "data/bss_004F_typed.h"
#include "data/data_002B.h"
#include "data/data_002E.h"
#include "data/pieces/D_002C5958.h"

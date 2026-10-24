/* Hand-matched functions, 0x001743b0..0x001803f0 (worker 38).
 * The ones that need -fno-strict-aliasing are in nostrict/text_00170000_h38.c. */
#include "common.h"

typedef int u128 __attribute__((mode(TI)));
typedef struct { f32 x, y, z; } V3;
#include "data/types/text_00170000_h38.h"
typedef union { V4 v; u128 q; } V4A;

/* --- actor state handlers (Wk = owner, Ob = actor) --- */
typedef struct Prm {
    s32 x0;         /* 0x00 */
    u8 pad4[0x10];
    f32 x14;        /* 0x14 */
    f32 x18;        /* 0x18 */
    f32 x1c;        /* 0x1C */
    f32 x20;        /* 0x20 */
} Prm;
typedef struct { u8 pad[0xc]; Prm *xc; } P160;
typedef struct { u8 pad[0x50]; f32 x50; } P40;

typedef struct Ob {
    u8 pad0[0x38];
    u64 flags;      /* 0x38 */
    P40 *x40;       /* 0x40 */
    u8 pad44[4];
    s32 x48;        /* 0x48 */
    s32 x4c;        /* 0x4C */
    u8 pad50[0x68 - 0x50];
    f32 x68;        /* 0x68 */
    u8 pad6c[0x160 - 0x6c];
    P160 *x160;     /* 0x160 */
    s32 x164;       /* 0x164: sub-state */
} Ob;

typedef struct Wk {
    u8 pad0[0x144];
    Ob *x144;       /* 0x144 */
} Wk;

/* the object D_00575894 points to */

/* camera path (D_00362438 points to one) */
#include "data/types/text_00170000_h38_p.h"

/* camera state at D_00575940 */
extern f32 D_003623F8;
extern f32 D_003624B8;
extern u8 D_0035C2B0[];
extern u8 D_0035C410[];

s32 func_00171a88(Wk *, Ob *, s32);
f32 func_00171aa8(f32, f32);
s32 func_00171ae8(Wk *, Ob *);
s16 *func_00171b80(Wk *, Ob *, s32);
void func_00170f90(void);
void func_00170fa8(Wk *, Ob *, void *, void *, f32);
void func_00148a40(Wk *, s32);
s32 func_0016b670(Wk *, Ob *, s32, s32);
s32 func_0016c480(Wk *, Ob *, s32, s32);
s32 func_0016c650(Wk *, Ob *, s32, s32);
s32 func_0016cb98(Wk *, Ob *, s32, s32);
s32 func_0016d040(Wk *, Ob *, s32, s32);
s32 func_0016d2d0(Wk *, Ob *, s32, s32);
s32 func_0016d768(Wk *, Ob *, s32, s32);
f32 func_00162950(V3 *, void *);
void func_00182870(void);
void func_00267370(V4A *, V4A *, V4A *);
void func_002673b8(V4A *, V4A *);
void sceVu0MulMatrix(V4A *, V4A *, V4A *);

s32 func_001743b0(Wk *w, Ob *o, s32 a2, s32 a3) {
    switch (a3) {
    case 0:
        return 0;
    case 1:
        if (!func_00171a88(w, o, 39)) return 0;
        if (!((s32)(o->flags >> 2) & 1)) return 0;
        return func_0016b670(w, o, a2, 1);
    case 2:
        func_00148a40(w, 0);
        func_0016b670(w, o, a2, 2);
        func_00170fa8(w, o, func_00170f90, D_0035C2B0, 30.0f);
        return 1;
    }
    return 1;
}

s32 func_001744b8(Wk *w, Ob *o, s32 a2, s32 a3) {
    switch (a3) {
    case 0:
        return 0;
    case 1:
        if (!func_00171a88(w, o, 40)) return 0;
        return func_0016c480(w, o, a2, 1);
    case 2:
        func_0016c480(w, o, a2, a3);
        return 1;
    }
    return 1;
}

s32 func_00174570(Wk *w, Ob *o, s32 a2, s32 a3) {
    switch (a3) {
    case 0:
        return 0;
    case 1:
        if (!func_00171a88(w, o, 41)) return 0;
        return func_0016c650(w, o, a2, 1);
    case 2:
        func_0016c650(w, o, a2, a3);
        return 1;
    }
    return 1;
}

s32 func_00174628(Wk *w, Ob *o, s32 a2, s32 a3) {
    switch (a3) {
    case 0:
        return 0;
    case 1:
        if (!func_00171a88(w, o, 42)) return 0;
        return func_0016cb98(w, o, a2, 1);
    case 2:
        func_0016cb98(w, o, a2, a3);
        return 1;
    }
    return 1;
}

s32 func_001746e0(Wk *w, Ob *o, s32 a2, s32 a3) {
    switch (a3) {
    case 0:
        return 0;
    case 1:
        if (!func_00171a88(w, o, 43)) return 0;
        return func_0016d040(w, o, a2, 1);
    case 2:
        func_0016d040(w, o, a2, a3);
        return 1;
    }
    return 1;
}

s32 func_00174968(Wk *w, Ob *o, s32 a2, s32 a3) {
    switch (a3) {
    case 0:
        return 0;
    case 1:
        if (!func_00171a88(w, o, 45)) return 0;
        return func_0016d2d0(w, o, a2, 1);
    case 2:
        func_0016d2d0(w, o, a2, a3);
        return 1;
    }
    return 1;
}

s32 func_00174a20(Wk *w, Ob *o, s32 a2, s32 a3) {
    switch (a3) {
    case 0:
        return 0;
    case 1:
        if (!func_00171a88(w, o, 46)) return 0;
        return func_0016d768(w, o, a2, 1);
    case 2:
        func_0016d768(w, o, a2, a3);
        return 1;
    }
    return 1;
}

void func_00174ad8(Wk *w) {
    Ob *o = w->x144;
    Prm *q;
    if ((s32)(o->flags >> 17) & 1) {
        o->flags &= ~0x20000ULL;
        return;
    }
    q = o->x160->xc;
    o->x68 = func_00171aa8(q->x14, q->x18);
    o->x4c = *func_00171b80(w, o, q->x0);
    if (func_00171ae8(w, o)) o->x40->x50 = q->x1c;
    o->x164 = 1;
}

s32 func_00174db0(Wk *w, Ob *o, s32 a2, s32 a3) {
    switch (a3) {
    case 0:
        return 0;
    case 1:
        if (!func_00171a88(w, o, 47)) return 0;
        if (!((s32)(o->flags >> 2) & 1)) return 0;
        return func_0016b670(w, o, a2, 1);
    case 2:
        func_00148a40(w, 0);
        func_0016b670(w, o, a2, 2);
        func_00170fa8(w, o, func_00170f90, D_0035C410, 30.0f);
        return 1;
    }
    return 1;
}

s32 func_00174eb8(Wk *w, Ob *o, s32 a2, s32 a3) {
    switch (a3) {
    case 0:
        return 0;
    case 1:
        if (!func_00171a88(w, o, 48)) return 0;
        if (!((s32)(o->flags >> 2) & 1)) return 0;
        return func_0016b670(w, o, a2, 1);
    case 2:
        func_00148a40(w, 0);
        func_0016b670(w, o, a2, 2);
        func_00170fa8(w, o, func_00170f90, D_0035C410, 30.0f);
        return 1;
    }
    return 1;
}

/* intersection of segment a-b with a plane; out gets w = 1 */
s32 func_00175820(V3 *a, V3 *b, void *pl, V4 *out) {
    f32 da = func_00162950(a, pl);
    f32 db = func_00162950(b, pl);
    f32 t;
    if (fabsf(da - db) < 1.17549449095213395e-38f) return 0;
    t = -da / (db - da);
    out->x = (b->x - a->x) * t + a->x;
    out->y = (b->y - a->y) * t + a->y;
    out->z = (b->z - a->z) * t + a->z;
    out->w = 1.0f;
    return 1;
}

/* cubic Bezier through the 4 control points m[0..3] */

/* --- shift packed 14-bit x / 14-bit y coordinates of every entry --- */
#include "data/data_002E.h"
#include "data/data_0036.h"
#include "data/data_0035.h"

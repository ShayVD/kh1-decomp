/* Hand-matched functions, 0x001742b0..0x001803f0 (worker 38).
 * This file was built without strict aliasing. */
#include "common.h"

typedef struct { f32 x, y, z; } V3;

/* per-state parameter block (Ob->x160->xc) */
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
    u8 pad6c[0x90 - 0x6c];
    s32 x90;        /* 0x90 */
    u8 pad94[0xc0 - 0x94];
    V3 xc0;         /* 0xC0 */
    u8 padcc[0x120 - 0xcc];
    f32 x120, x124, x128, x12c; /* 0x120 */
    u8 pad130[0x160 - 0x130];
    P160 *x160;     /* 0x160 */
    s32 x164;       /* 0x164: sub-state */
} Ob;

typedef struct Wk {
    u8 pad0[0x144];
    Ob *x144;       /* 0x144 */
    u8 pad148[0x160 - 0x148];
    s32 x160;       /* 0x160 */
    s32 x164;       /* 0x164 */
} Wk;

extern u8 D_0035C2B0[];
extern u8 D_0035C410[];

s32 func_00171118(s32, s32);
void func_00171790(Wk *, Ob *);
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
void func_00130340(Wk *, s32, f32);
void func_00267e90(f32, f32 *, V3 *);
f32 func_00162c20(f32 *);

void func_001742b0(Wk *w, Ob *o) {
    f32 v[3];
    Prm *q = o->x160->xc;
    if (!func_00171118(o->x90, -1)) {
        o->x48 = 0;
        return;
    }
    o->flags |= 0x100000;
    func_00171790(w, o);
    if (o->x164 == 0) return;
    if (o->x164 != 1) return;
    if (o->x68 < 0.0f) o->x48 = 0;
    o->flags |= 0x1000;
    func_00267e90(q->x20, v, &o->xc0);
    o->x124 = v[1];
    v[1] = 0.0f;
    o->x12c = func_00162c20(v);
    o->x120 = v[0];
    o->x128 = v[2];
}

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

s32 func_00174b90(Wk *w, Ob *o, s32 a2) {
    s32 r = 0;
    switch (a2) {
    case 1:
        switch (o->x164) {
        case 0:
            if (!(w->x160 & 1)) {
                if (w->x164 != 202) r = 1;
            }
            break;
        case 1:
            if (!(w->x160 & 1)) {
                if (w->x164 != o->x4c) r = 1;
            }
            break;
        }
        break;
    case 2:
        r = o->x48 == 0;
        break;
    }
    if (r == 1) {
        o->x48 = 0;
        o->flags &= ~0x800;
        o->flags &= ~0x200;
        o->flags |= 0x20000;
        if (w->x164 == 202 || w->x164 == o->x4c) func_00130340(w, 0x40000075, 8.0f);
    }
    return r;
}

void func_00174ca8(Wk *w, Ob *o) {
    f32 v[3];
    Prm *q = o->x160->xc;
    if (!func_00171118(o->x90, -1)) {
        o->x48 = 0;
        return;
    }
    o->flags |= 0x100000;
    func_00171790(w, o);
    if (o->x164 == 0) return;
    if (o->x164 != 1) return;
    if (o->x68 < 0.0f) o->x48 = 0;
    o->flags |= 0x1000;
    o->flags |= 0x200;
    func_00267e90(q->x20, v, &o->xc0);
    o->x124 = v[1];
    v[1] = 0.0f;
    o->x12c = func_00162c20(v);
    o->x120 = v[0];
    o->x128 = v[2];
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


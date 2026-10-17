/* Hand-matched functions (worker c04), built without strict aliasing. */
#include "common.h"

typedef struct { s16 h0; s16 pad2; s32 w4; f32 f8; } Res8;
typedef struct { u8 pad[4]; s32 w4; } Res04;
typedef struct { u8 pad[0x30]; s32 w30; } Res30;
typedef struct { u8 pad[0xC]; void *cb; } Task0C;
typedef struct { u8 pad[0xB4]; void *cb; void **slot; } Sub2C;
typedef struct { u8 pad[0x2C]; Sub2C *p2C; } Sub14C;
typedef struct { u8 pad[0x10]; f32 f10; } Sub6C;
typedef struct {
    u8 pad[8]; void *w8; u8 padC[0x60]; Sub6C *p6C; s32 w70; u8 pad74[0xD8]; Sub14C *p14C;
} ObjB6;
typedef union { u64 x; struct { u64 lo:40; u64 id:16; u64 hi:8; } b; struct { u32 lo; u8 b4; } c; } Bf80;
typedef struct {
    u8 pad[0x3C]; void **slot; Sub2C *p40; u8 pad44[8]; s32 w4C; u8 pad50[0x30];
    Bf80 w80; u8 pad88[8]; void *p90; s32 w94; s32 w98; f32 f9C; f32 fA0; u8 padA4[0x2C];
    f32 vD0[3]; f32 fDC; u8 padE0[0x40]; f32 v120[3]; s32 w12C;
} WkB6;
typedef union { u16 h; s32 w; } RngId;
typedef struct { RngId id; f32 f4, f8, fC, f10; } RngB6;
typedef struct { u8 pad[4]; s32 flags; u8 pad8[4]; RngB6 *rng; } KB6;

extern u32 D_002C5958;
extern s32 D_00574FB8;
extern void *D_00574FC0[20];
extern s32 func_00122ff8(void *);
extern s32 func_0012f040(void *, s32);
extern s32 func_0012ee70(void *, s32);
extern void func_00130340(ObjB6 *, s32, f32);
extern Task0C *func_00130578(ObjB6 *, s32, f32);
extern void func_001376e8(ObjB6 *, f32 *);
extern Res8 *func_0013dbe0(ObjB6 *, s32);
extern Res8 *func_0013dc10(ObjB6 *, s32);
extern s32 func_00141288(ObjB6 *, s32);
extern void func_001412f8(ObjB6 *, s32);
extern Res30 *func_001477c8(s32);
extern void func_0014cce0(ObjB6 *, f32);
extern s32 func_00169510(ObjB6 *, WkB6 *, s32);
extern void func_00171f38(void);
extern void func_002675a8(f32 *, f32 *);

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

static inline Res8 *inl_00171b80(ObjB6 *o, WkB6 *l, u16 k) {
    s32 i = D_00574FB8;
    s32 n = 0;
    Res8 *r;
    Sub2C *p;
    while (D_00574FC0[i] != 0) {
        i++;
        n++;
        if (i >= 20) i = 0;
        if (n >= 20) goto out;
    }
out:
    D_00574FB8 = i + 1;
    if (i + 1 >= 20) D_00574FB8 = 0;
    r = func_0013dc10(o, k);
    p = o->p14C->p2C;
    if (p != 0) {
        void **s = &D_00574FC0[i];
        p->slot = s;
        p->cb = func_00171f38;
        l->slot = s;
        *s = p;
        l->p40 = p;
    } else {
        l->p40 = 0;
    }
    return r;
}

s32 func_0016b670(ObjB6 *o, WkB6 *w, KB6 *k, s32 mode) {
    RngB6 *rng = k->rng;
    Res8 *r;
    f32 f;
    s32 fl;
    switch (mode) {
    case 0:
        return 0;
    case 1:
        if (rng == 0) return 0;
        if (!func_00169510(o, w, k->flags)) return 0;
        if (!inl_00171118(w->p90, w->w94)) return 0;
        if (o->w8 != w->p90) {
            if (w->fDC < rng->f4 - w->f9C) goto r4;
            if (rng->f8 + w->f9C < w->fDC) goto r4;
            if (w->fA0 < rng->fC - w->f9C) goto r4;
            if (rng->f10 + w->f9C < w->fA0) { r4: return 0; }
        }
        r = func_0013dbe0(o, rng->id.w);
        if (r->f8 != 0.0f) k->flags |= 8;
        if (!func_00141288(o, func_001477c8(r->w4)->w30)) return 0;
        break;
    case 2:
        w->w80.c.b4 = 1;
        w->w80.b.id = rng->id.h;
        func_001376e8(o, w->vD0);
        func_002675a8(w->v120, w->vD0);
        w->w12C = 0;
        r = inl_00171b80(o, w, w->w80.b.id);
        w->w4C = r->h0;
        func_001412f8(o, func_001477c8(r->w4)->w30);
        if (o->w70 != 8 && o->w70 != 24 && w->fA0 < 0.0f && ((fl = k->flags) & 8)) {
            f = r->f8 - w->fA0;
            if (o->p6C->f10 < f) f = o->p6C->f10;
            if (r->h0 >= 0) {
                if (fl & 2) func_00130578(o, 0x40000000, 8.0f);
                else if (fl & 4) func_00130578(o, 0x40000075, 8.0f);
                else func_00130578(o, 0x40000006, 8.0f);
            }
            func_0014cce0(o, f);
        } else if (r->h0 >= 0) {
            if (k->flags & 0x10) {
                f = 0.0f;
                func_0014cce0(o, f);
                func_00130340(o, r->h0 | 0x1800000, f);
            }
            if (r->h0 >= 0) {
                s32 fl2 = k->flags;
                if (fl2 & 2) func_00130578(o, 0x40000000, 8.0f);
                else if (fl2 & 4) func_00130578(o, 0x40000075, 8.0f);
                else if (fl2 & 0x10) func_00130578(o, 0x40000006, 8.0f);
                else func_00130578(o, 0x40000000, 8.0f);
            }
        }
        w->w12C = 0;
        return 1;
    }
    return 1;
}

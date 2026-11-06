/* xs_simba.x func_00f20ad8: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad0[0xD0]; OvlMtx m; u8 pad110[0x3C]; u8 *p14c; u8 pad150[0x220]; u64 f370; } Act;
typedef struct { f32 lv; f32 f4; s32 f8; u8 padc[8]; s32 f14; s32 f18; s32 f1c; } Lvl;
typedef struct { f32 d; Act *act; s32 id; } Tgt;
typedef struct { Act *act; s32 id; } Cur;
typedef struct { s32 f0; f32 f4; f32 f8; s32 fc; } Qry;
typedef struct { u8 pad[0xC]; s32 id; OvlVec pos; } Hit;
typedef struct { u64 flags; u8 pad8[8]; OvlVec pos; } Eff;
s32 func_0011ef10(s32, s32 (*)(void));
f32 func_00120bf8(f32 *);
s32 func_00122ff8(Act *);
Act *func_001230a0(Act *);
void func_0012c880(Act *, s32);
#ifdef KH1_PS2
void func_0012ec60(Act *, s32, f32 *);
#else /* the definition returns f32: an x86 caller that drops it unbalances the x87 stack */
f32 func_0012ec60(Act *, s32, f32 *);
#endif
s32 func_00130340(Act *, s32, f32);
void *func_00130578(Act *, s32, f32);
void func_001373f8(Act *, f32);
s32 func_001477e0(s32);
void *func_00147ed8(void *, s32, s32, f32 *);
void func_00148968(Act *, void *, s32);
Eff *func_0014a4a8(Act *, s32, s32);
void func_00157818(Act *, s32);
void func_00157a30(Act *, s32, s32);
s32 func_0015bd78(Qry *, Act *, Hit *);
void func_00f20188(void);
s32 func_00f209a0(void);
s32 func_00f20ab8(f32 *, f32 *);
void qsort(void *, s32, s32, s32 (*)(f32 *, f32 *));
extern Cur D_002E31B0;
extern Act *D_00F21C34;
extern Act *D_00F21C38;
extern Lvl *D_00F21C3C;
extern void *D_00F21C44;
extern f32 D_00FA6A00[];
extern Tgt D_00FA6A98[];
extern s32 D_00FA6F18;
extern s32 D_00FA6F1C;
extern s32 D_00FA6F20;
extern f32 D_00FA6F24;
extern Eff *D_00FA6F28;
void func_00f20ad8(void) {
    OvlVec v;
    OvlVec d;
    Qry q;
    OvlVec w;
    Hit hit;
    Tgt *t;
    Act *act;
    s32 n;

    func_00130340(D_00F21C38, 0x010000CB, 0.0f);
    func_00130578(D_00F21C38, 0x40000000, 0.0f);
    func_00148968(D_00F21C38, D_00F21C44, D_00F21C3C->f14);
    func_00157818(D_00F21C38, 0);
    func_00130340(D_00F21C34, 0x010000CB, 0.0f);
    func_00130578(D_00F21C34, 0x40100000, 0.0f);
    func_0012c880(D_00F21C34, 6);
    *(void **)(D_00F21C34->p14c + 0x20) = D_00F21C44;
    func_001373f8(D_00F21C34, 10.0f);
    func_00157a30(D_00F21C34, 5, 0);
    if (func_00122ff8(D_002E31B0.act))
        func_0012ec60(D_002E31B0.act, D_002E31B0.id, v);
    else
        PlatVu0ApplyMatrix(v, D_00F21C34->m, D_00FA6A00);
    func_00147ed8(D_00F21C44, D_00F21C3C->f18, 20000, v);
    t = D_00FA6A98;
    act = NULL;
    q.f0 = 1;
    q.f4 = q.f8 = D_00F21C3C->f4;
    PlatVu0CopyVector(w, v);
    while ((act = func_001230a0(act)) != NULL) {
        if (((act->f370 >> 37) & 3) != 2)
            continue;
        if (!func_0015bd78(&q, act, &hit))
            continue;
        t->act = act;
        if (D_002E31B0.act == act)
            t->id = D_002E31B0.id + 100;
        else
            t->id = hit.id;
        PlatVu0SubVector(d, hit.pos, v);
        t->d = func_00120bf8(d);
        t++;
        PlatVu0InnerProduct(d, d);
    }
    n = t - D_00FA6A98;
    D_00FA6F18 = n;
    if (n > 0) {
        qsort(D_00FA6A98, n, 12, func_00f20ab8);
        D_00FA6F1C = 0;
        D_00FA6F20 = D_00F21C3C->f1c;
        D_00FA6F24 = 8.0f;
        func_0011ef10(0xCB20, func_00f209a0);
        D_00FA6F28 = func_0014a4a8(D_00F21C34, 0, func_001477e0(D_00F21C3C->f8));
        D_00FA6F28->flags |= 0x40;
        D_00FA6F28->flags |= 0x100;
        PlatVu0CopyVector(D_00FA6F28->pos, v);
    } else {
        func_00f20188();
    }
}

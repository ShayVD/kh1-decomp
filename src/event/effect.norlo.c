/* func_001dd5c0 of src/event/effect.c: needs norlo (-fno-rerun-loop-opt;
 * s7_w10: without it the second loop pass reverses the case-9 counter j
 * into a countdown). */
#include "common.h"
#include "data/types/vm_rec.h"
#include "event/effect.h"
#include "vm/vm_obj.h"
#include "data/bss_0062.h"
#include "data/data_0029.h"
#include "data/pieces/D_0037A378.h"
#include "data/pieces/D_00350CE0.h"

s32 func_00176040(void *, void *, s32, s32);
s32 func_00176078(s32, s32, s32, s32);
s32 func_00176008(s32, s32, s32, s32);
s32 func_00176488(s32, EvFx *, s32, s32);
void func_001761d0(void);
void func_001761b0(void);
void func_00176310(EvFx *);
s32 func_001765f8(EvFx *);

/* Run the request t->f2c for effect t->f28: start it (0, 3, 6, 11 with the
 * buffers of the three kinds; 10 / 16 also follow the entity), stop it
 * (2, 5, 12; 1 / 4 stop all), start one of the eight model effects on the
 * entity (7, 8, 13; 9 / 14 stop them), or fade its colour (15). */
s32 func_001dd5c0(EvTask *t) {
    EvFx *e;
    EvTask *n;
    s32 i;
    switch (t->f2c) {
    case 0:
        if (D_0037A378 & 1) return 4;
        func_00176040(D_0062A220, D_0062A224, t->f28, 100000);
        break;
    case 1:
        func_001761d0();
        return 4;
    case 2:
        e = func_001760d0(t->f28);
        if (e) func_00176310(e);
        return 4;
    case 3:
        func_00176078(D_0029B418, D_0029B41C, t->f28, 100000);
        break;
    case 4:
        func_001761b0();
        return 4;
    case 5:
        e = func_001760f0(t->f28);
        if (e) func_00176310(e);
        return 4;
    case 6:
        func_00176488(D_00350CE0, D_0062A428, t->f28, 100000);
        break;
    case 7:
        func_00176488((s32)t->f10, &D_0062A428[t->f18], t->f28, 100000);
        D_0062A428[t->f18].f0[0] = t->f14->obj->pos[0];
        D_0062A428[t->f18].f0[1] = t->f14->obj->pos[1];
        D_0062A428[t->f18].f0[2] = t->f14->obj->pos[2];
        if (func_001765f8(&D_0062A428[t->f18]) < 0) break;
        n = func_0011f090(D_0062A630, 1, func_001dd208);
        n->f10 = &D_0062A428[t->f18];
        n->f14 = t->f14;
        n->f18 = func_001765f8(n->f10);
        n->f1c = 0;
        n = func_0011f090(D_0062A630, 1, func_001dd320);
        n->f10 = &D_0062A428[t->f18];
        n->f14 = t->f14;
        n->f18 = func_001765f8(n->f10);
        n->f1c = 0;
        break;
    case 8:
        func_00176488((s32)t->f10, &D_0062A428[t->f18], t->f28, 100000);
        *D_0062A428[t->f18].f10 = 1;
        D_0062A428[t->f18].f0[0] = t->f14->obj->pos[0];
        D_0062A428[t->f18].f0[1] = t->f14->obj->pos[1];
        D_0062A428[t->f18].f0[2] = t->f14->obj->pos[2];
        if (func_001765f8(&D_0062A428[t->f18]) < 0) break;
        n = func_0011f090(D_0062A630, 1, func_001dd208);
        n->f10 = &D_0062A428[t->f18];
        n->f14 = t->f14;
        n->f18 = func_001765f8(n->f10);
        n->f1c = 0;
        n = func_0011f090(D_0062A630, 1, func_001dd320);
        n->f10 = &D_0062A428[t->f18];
        n->f14 = t->f14;
        n->f18 = func_001765f8(n->f10);
        n->f1c = 0;
        break;
    case 9:
        { s32 j; for (j = 0; j < 8; j++) { if (D_0062A608[j] == t->f28) func_00176310(&D_0062A428[j]); } }
        
        return 4;
    case 10:
        if (D_0037A378 & 1) return 4;
        func_00176040(D_0062A220, D_0062A224, t->f28, 100000);
        e = func_001760d0(t->f28);
        if (func_001765f8(e) < 0) return 4;
        if (!t->f14) break;
        n = func_0011f090(D_0062A630, 1, func_001dd550);
        n->f10 = e;
        n->f14 = t->f14;
        n->f18 = func_001765f8(e);
        n->f1c = 0;
        break;
    case 16:
        if (D_0037A378 & 1) return 4;
        func_00176078(D_0029B418, D_0029B41C, t->f28, 100000);
        e = func_001760f0(t->f28);
        if (func_001765f8(e) < 0) return 4;
        if (!t->f14) break;
        n = func_0011f090(D_0062A630, 1, func_001dd550);
        n->f10 = e;
        n->f14 = t->f14;
        n->f18 = func_001765f8(e);
        n->f1c = 0;
        break;
    case 11:
        func_00176008(D_0029B410, D_0029B414, t->f28, 100000);
        break;
    case 12:
        e = func_001760b0(t->f28);
        if (e) func_00176310(e);
        return 4;
    case 13:
        func_00176488(t->f14->obj->f14c->f14, D_0062A428, t->f28, 100000);
        D_0062A428->f0[0] = t->f14->obj->pos[0];
        D_0062A428->f0[1] = t->f14->obj->pos[1];
        D_0062A428->f0[2] = t->f14->obj->pos[2];
        if (func_001765f8(D_0062A428) < 0) break;
        n = func_0011f090(D_0062A630, 1, func_001dd208);
        n->f10 = D_0062A428;
        n->f14 = t->f14;
        n->f18 = func_001765f8(D_0062A428);
        n->f1c = 0;
        n = func_0011f090(D_0062A630, 1, func_001dd320);
        n->f10 = D_0062A428;
        n->f14 = t->f14;
        n->f18 = func_001765f8(D_0062A428);
        n->f1c = 0;
        break;
    case 14:
        func_00176310(D_0062A428);
        return 4;
    case 15:
        n = func_0011f090(D_0062A630, 2, func_001dd488);
        n->f28 = t->f28; n->f30 = t->f30; n->f10 = t->f10; n->f40[0] = t->f40[0]; n->f40[1] = t->f40[1]; n->f40[2] = t->f40[2];
        break;
    }
    return 4;
}

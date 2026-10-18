#include "common.h"
/* func_001dd5c0: MATCH in hand with -fno-rerun-loop-opt (rodata jump table at 0x4907b0, verified with wqb03_rr). Without the flag the second loop pass reverses the case-9 counter j into a countdown. */
typedef struct { u8 pad0[0x14]; s32 f14; } Sub14c;
typedef struct { u8 pad0[0x10]; f32 pos[3]; u8 pad1c[0x14c - 0x1c]; Sub14c *f14c; } Ob5;
typedef struct { s32 x0; Ob5 *f4; } HS5;
typedef struct { f32 *f0; s32 *f4; f32 *f8; f32 *fc; u8 *f10; s32 f14; u8 pad18[60 - 0x18]; } E60;
typedef struct { u8 pad0[0x10]; void *f10; HS5 *f14; s32 f18; f32 f1c; u8 pad20[8]; s32 f28; s32 f2c; f32 f30; u8 pad34[0xc]; f32 f40[3]; } Hd5;
extern u8 D_0062A630[];
extern E60 D_0062A428[];
extern s32 D_0062A608[];
extern s32 D_0037A378;
extern s32 D_0062A220, D_0062A224, D_0029B418, D_0029B41C, D_0029B410, D_0029B414, D_00350CE0;
s32 func_001dd5c0(Hd5 *);
s32 func_001dd208(Hd5 *);
s32 func_001dd320(Hd5 *);
s32 func_001dd488(Hd5 *);
s32 func_001dd550(Hd5 *);
Hd5 *func_0011f090(void *, s32, s32 (*)(Hd5 *));
s32 func_00176040(s32, s32, s32, s32);
s32 func_00176078(s32, s32, s32, s32);
s32 func_00176008(s32, s32, s32, s32);
s32 func_00176488(s32, E60 *, s32, s32);
void func_001761d0(void);
void func_001761b0(void);
E60 *func_001760d0(s32);
E60 *func_001760f0(s32);
E60 *func_001760b0(s32);
void func_00176310(E60 *);
s32 func_001765f8(E60 *);
/* rodata */
s32 func_001dd5c0(Hd5 *t) {
    E60 *e;
    Hd5 *n;
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
        D_0062A428[t->f18].f0[0] = t->f14->f4->pos[0];
        D_0062A428[t->f18].f0[1] = t->f14->f4->pos[1];
        D_0062A428[t->f18].f0[2] = t->f14->f4->pos[2];
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
        D_0062A428[t->f18].f0[0] = t->f14->f4->pos[0];
        D_0062A428[t->f18].f0[1] = t->f14->f4->pos[1];
        D_0062A428[t->f18].f0[2] = t->f14->f4->pos[2];
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
        func_00176488(t->f14->f4->f14c->f14, D_0062A428, t->f28, 100000);
        D_0062A428->f0[0] = t->f14->f4->pos[0];
        D_0062A428->f0[1] = t->f14->f4->pos[1];
        D_0062A428->f0[2] = t->f14->f4->pos[2];
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
/* Hidden function at 0x1ddbf8 (inside layout symbol func_001dd5c0), untested:
extern s32 D_0062A220;
void func_001763f0(s32);
void func_001ddbf8(void) {
    func_001763f0(D_0062A220);
    D_00389C90.f3070 &= ~(1ULL << 44);
}
*/

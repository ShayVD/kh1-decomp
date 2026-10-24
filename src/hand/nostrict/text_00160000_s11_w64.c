/* func_00169688 (hand/nostrict), rodata jtbl_0048E870 (verify with wqb03_rr.py 0048E870), s11w64. Natural, no flagged code.
   From session9 w3's 4w draft; new: case 10 as two paths that each load p = o->x148 and jump to one
   shared block: `if (!(D & 1)) { p = o->x148; if (hi & 1) goto c10b; goto r1; } p = o->x148; c10b: B; r1: return 1;`
   The hi path's `goto c10b` is not a jump to the next insn (the D path's p load sits between), so it
   survives jump2 and reorg fills it from c10b (`b L+4; ld v1,48(a2)`); the bnez to the D path gets the hi
   path's p load in its slot and is redirected past the duplicate load. r1 sits after B's fall-through, so
   jump.c does not hoist `li v0,1` above the hi test (the test keeps v0). */
#include "common.h"
typedef struct { f32 x, y, z, w; } Vec;
typedef struct { f32 a, b, c; } Lim;
typedef struct {
    u8 pad0[0x30];
    union { u64 x; struct { u64 lo:32; u64 hi:32; } b; } x30;
    u8 pad38[0xc0 - 0x38];
    Vec xc0;
} O148;
typedef struct {
    u8 pad0[8];
    s32 x8;
    u8 padc[4];
    Vec x10;
    u8 pad20[0x70 - 0x20];
    s32 x70;
    u8 pad74[0x90 - 0x74];
    s64 x90;
    u8 pad98[0x148 - 0x98];
    O148 *x148;
    u8 pad14c[0x3cc - 0x14c];
    f32 x3cc;
} Obj;
typedef struct {
    s32 x0;
    Lim *x4;
    u8 pad8[0x38 - 8];
    union { s64 x; s32 i; } x38;
    u8 pad40[0x58 - 0x40];
    s32 x58;
    u32 x5c;
    u8 pad60[0x68 - 0x60];
    f32 x68;
    u8 pad6c[0x90 - 0x6c];
    s32 x90;
    s32 x94;
    u8 pad98[0xb0 - 0x98];
    Vec xb0;
    u8 padc0[0x120 - 0xc0];
    Vec x120;
} Wk;
void func_0013dfb8(Obj *, Vec *);

static inline void Tail(Obj *o, Wk *w) {
    if (o->x70 != 2) {
        func_0013dfb8(o, &w->x120);
    }
}

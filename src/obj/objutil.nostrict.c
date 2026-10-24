/* Small object helpers every class uses: func_001375f0 (the object can act),
 * func_00137618, func_00137688 (turn to an angle), func_001376e8,
 * func_001373f8, the collision entry of an object (func_00137450,
 * D_003044D8), and the id lists D_0052ABF0 / D_0052ACF0 (func_001374a8).
 * Flag mode: nostrict (the other modes are in the sibling files). Read from
 * the code, not proved by a boot (docs/modules.md "Session 53"). */
#include "common.h"
#include "data/pieces/D_002BC0A8.h"

/* func_00137330 (from hand/nostrict/text_00130000_s6_na.c). */
typedef struct { void *p; s32 n; } Arg7;
typedef union { u64 x; struct { u32 lo; u32 b32:1; u32 x33:15; u32 b48:1; u32 hi:15; } b; } F370c;
typedef struct Ob7 Ob7;
struct Ob7 { u8 pad[0x144]; void *f144; u8 p148[0x370-0x148]; F370c f370; u8 p378[0x4a0-0x378]; s32 (*f4a0)(Ob7 *, s32, s32); };
extern s32 func_0012bce0(void *, s32, s32, Arg7 *, s32 *);
extern s32 func_001c4ed0(Ob7 *, s32, s32);
s32 func_00137330(Ob7 *o, s32 a, s32 b) {
    Arg7 args[2];
    s32 r;
    if (o == 0 || !o->f370.b.b32) return 0;
    r = 0;
    if (o->f370.b.b48 && o->f144) {
        args[0].n = 4;
        args[0].p = &a;
        args[1].p = &b;
        args[1].n = 4;

        func_0012bce0(o->f144, 1, 2, args, &r);
        return r;
    }
    if (o->f4a0) r = o->f4a0(o, a, b);
    else r = func_001c4ed0(o, a, b);
    return r;
}


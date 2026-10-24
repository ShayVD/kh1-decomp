#include "common.h"

typedef union { u64 x; struct { u32 lo; u32 x32:3; u32 b35:1; u32 hi:28; } b; } F370d;
typedef struct { u32 f0; u8 p4[0xd0-4]; u8 fd0[0x154-0xd0]; s32 f154; u8 p158[0x370-0x158]; F370d f370; } Ob8;
#include "data/pieces/D_002BC0A8.h"
extern void func_00135df0(Ob8 *, f32 *);
extern s32 func_00114a38(void *, s32, s32, f32 *);
extern void func_00128218(Ob8 *, f32);
void func_001369e8(Ob8 *o) {
    f32 v[4];
    s32 i;
    if (!(o->f0 & 1)) return;
    if (!(D_002BC0A8.u & 1)) return;
    func_00135df0(o, v);
    for (i = 0; i < 4; i++) v[i] *= 0.0078125f;
    { u64 m = 0x800000000ULL;
    func_00114a38(o->fd0, o->f154, v[3] < 1.0f ? 0xc35a : 0x9c40, v);
    o->f370.x |= m; }
    if (o->f0 & 2) func_00128218(o, 1.0f);
}

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

#include "data/data_002E.h"
#include "data/data_0036.h"

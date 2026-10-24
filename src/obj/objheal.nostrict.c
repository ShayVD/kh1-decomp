/* Party heal objects, without strict aliasing (docs/modules.md "Session
 * 52"): func_00156c68 heals the party members whose HP is below the
 * maximum, func_00156d88.  Read from the code, not proved by a boot. */
#include "common.h"
#include "data/bss_0055.h"
#include "data/pieces/D_00308CDC.h"
#include "data/pieces/D_002C58B0.h"
#include "data/pieces/D_002C58A0.h"
#include "data/pieces/D_002E26A0.h"
#include "data/types/nostrict_text_00150000_h35.h"

/* func_00156c68 (from hand/nostrict/text_00150000_h35.c). */
typedef struct { f32 x, y, z, w; } Vec154768;
typedef struct { u8 pad[0x3C]; s32 w3C; s32 w40; s32 w44; s32 w48; u8 pad4c[0x72]; u16 hBE; } S6C_156c68;
typedef struct Actor_56c68 {
    s32 w0;
    u8 pad4[0xc];
    Vec154768 v10;
    u8 pad20[0x1c];
    f32 f3C;
    u8 pad40[0x2c];
    S6C_156c68 *p6C;
    u8 pad70[0xc0];
    void *p130;
    u8 pad134[0x30];
    s32 w164;
    u8 pad168[0x4];
    f32 f16C;
    u8 pad170[0x1e0];
    s32 w350[4];
    u8 pad360[0x10];
    u64 d370;
} Pl1557d0;
typedef struct { u32 b0:1; u32 b1:1; u32 b23:2; u32 b4:1; u32 hi:27; } F144_156c68;
typedef struct { u8 pad[0x144]; F144_156c68 *p144; } Obj156c68;
typedef Pl1557d0 Pl156c68;
void func_00141468(Pl156c68 *, s32);
s32 func_00141540(Pl156c68 *, s32);
void func_00141608(Pl156c68 *, s32);
/* ---- func_00156c68 ---- */
void func_00156c68(Obj156c68 *a) {
    s32 i;
    Pl156c68 *p;
    if (!a->p144->b4) {
        a->p144->b0 = 1;
        a->p144->b4 = 1;
    }
    for (i = 0; i < 3; i++) {
        p = D_002E26A0[i];
        if (p) {
            if (p->p6C->w3C < p->p6C->w40) {
                func_00141468(p, 2);
                a->p144->b0 = 1;
            }
            if (p->p6C->w44 < p->p6C->w48 && !a->p144->b23) {
                a->p144->b0 = 1;
                func_00141540(p, 1);
                func_00141608(p, -p->p6C->hBE);
            }
        }
    }
}

/* func_00156d88 (from hand/nostrict/text_00150000_h35.c). */
typedef struct { u8 pad[4]; s32 w4; s32 w8; } S144_156d88;
typedef struct { u8 pad[0x4A]; s16 h4A; } S130_156d88;
typedef struct { u8 pad[0x130]; S130_156d88 *p130; u8 pad134[0x10]; S144_156d88 *p144; } Obj156d88;
typedef struct { u8 pad[0x70]; s32 w70; } Arg156d88;
void func_0012cc38(s32, s32);
void func_0012ccb0(s32, s32);
void func_00176310(s32);
s32 func_001ebfc8(void);
void func_00124920(void);
void func_0011c768(s32);
/* ---- func_00156d88 ---- */
s32 func_00156d88(Obj156d88 *a, Arg156d88 *b, s32 c) {
    s32 n;
    switch (c) {
    case -1:
        func_0012cc38(3, 54);
        if (b->w70 != 0 && b->w70 != 24) {
            func_0012ccb0(3, b->w70);
        } else {
            func_00156c68((Obj156c68 *)a);
        }
        break;
    case -2:
        func_00176310(a->p144->w4);
        if (a->p144->w8) func_00176310(a->p144->w8);
        break;
    case 54:
        n = a->p130->h4A ? (func_001ebfc8() ? 3 : 2) : 1;
        func_00124920();
        func_0011c768(n);
        break;
    }
    return 0;
}


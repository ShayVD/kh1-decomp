/* Hand-matched functions near 0x167000-0x175000 (worker 37), built without strict aliasing. */
#include "common.h"
#include "data/bss_0057.h"

/* ---- shared types ---- */
typedef union { s32 w; struct { u16 lo, hi; } h; } Key677;
typedef struct { f32 t; s32 a, b, c; } Key16;
typedef struct { Key677 k; s32 n; Key16 *keys; } Ent677;
typedef struct { u8 pad[0x3C]; Ent677 *tbl; } Obj677;

typedef struct { u8 pad[0x10]; u32 w10; u32 n1; u32 *list1; u32 n; s8 **list; u8 *map; } Dat684;
typedef struct { u8 b0; u8 b1; u8 pad[2]; s32 w4; u8 pad8[8]; u32 *w10; } Ent67F;
typedef struct { u8 pad[0x10]; Dat684 *w10; Dat684 *w14; Ent67F e[4]; } Obj67F;
typedef struct { u8 pad[8]; s32 w8; } Arg67F;

extern Dat684 *func_001684e0(s32);

/* inline copy of func_001677e0 */
static inline Ent677 *inl_001677e0(Obj677 *o, u32 key) {
    Ent677 *e = o->tbl;
    u32 hi = key >> 16;
    key &= 0xFFFF;
    for (; e->k.w != -1; e++) {
        if (e->k.h.hi == hi && (key == 0xFFFF || e->k.h.lo == key)) return e;
    }
    return 0;
}

static inline Dat684 *inl_get684(Obj67F *o, Arg67F *a) {
    if (a != 0) {
        if (o->w14 == 0) o->w14 = func_001684e0(a->w8);
        return o->w14;
    }
    return o->w10;
}

/* inline copy of func_00168318 */
static inline s32 inl_00168318(u32 *p) {
    switch (*p) {
    case 0x4A424F4D:
    case 0x41584554:
    case 0x454E4F42:
    case 0x4E544D4D:
    case 0x4C535255:
    case 0x564E454D:
        return 1;
    }
    return 0;
}

#include "data/pieces/D_0035BD40.h"
typedef struct Actor { u32 flags; u8 pad[0x140]; s32 w144; } ObjBD40;

#include "data/pieces/D_002E26A0.h"
extern f32 D_0048E9EC;

typedef struct { s32 w0; u8 pad4[0x10]; f32 f14, f18, f1C, f20, f24; } Sub170C;
typedef struct { u8 pad[0xC]; Sub170C *pC; } Sub170;
typedef struct { u8 pad[0x50]; f32 f50; } Sub40;
typedef struct { u8 pad[0x38]; u64 w38; Sub40 *p40; u8 pad44[4]; void *w48; s32 w4C; u8 pad50[0x18]; f32 f68; u8 pad6C[0x24]; ObjBD40 *w90; u8 pad94[0x2C]; f32 vC0[4]; u8 padD0[0x50]; f32 f120, f124, f128, f12C; u8 pad130[0x34]; f32 f164; u8 pad168[8]; Sub170 *p170; s32 w174; s32 w178; } Wk144;
typedef struct { u8 pad[0x14]; f32 f14; u8 pad18[0x58]; s32 w70; u8 pad74[0xD0]; Wk144 *p144; u8 pad148[0x18]; s32 w160; s32 w164; } Obj144;
typedef struct { u8 pad[0xC]; void *cb; } Task0C;
typedef struct { u8 pad[0x30]; s32 w30; } Res30;
typedef struct { u8 pad[4]; s32 w4; } Res04;
extern Task0C *func_00130578(Obj144 *, s32, f32);
extern Res04 *func_0013dbe0(Obj144 *, s32);
extern Res30 *func_001477c8(s32);
extern void func_001412f8(Obj144 *, s32);

/* ---- functions ---- */

/* needs make: uses rodata */
#include "data/data_002E.h"
#include "data/data_0035.h"
#include "data/data_0048.h"

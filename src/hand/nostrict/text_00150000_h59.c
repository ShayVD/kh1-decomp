#include "common.h"
#include "platform/math.h"
/* Hand-matched functions near 0x15b000-0x169000 (worker 59). */
typedef struct { void *a; void *b; } Pair59;
void func_00267530(f32 *, f32 *, f32 *);
void func_00267560(f32 *, f32 *, f32);
void func_00267518(f32 *, f32 *, f32 *);
void func_00267530(f32 *, f32 *, f32 *);
f32 func_00267390(f32 *, f32 *);
void func_00267530(f32 *, f32 *, f32 *);
void func_002675a8(f32 *, f32 *);
void func_00267560(f32 *, f32 *, f32);
void func_00267518(f32 *, f32 *, f32 *);
void func_00130398(void *, s32, f32);
void func_002675a8(f32 *, f32 *);
void func_00130398(void *, s32, f32);
void func_002675a8(f32 *, f32 *);
void func_00267560(f32 *, f32 *, f32);

static inline f32 inl_min(f32 a, f32 b) { if (!(a < b)) a = b; return a; }
static inline f32 inl_max(f32 a, f32 b) { if (!(b < a)) a = b; return a; }

typedef unsigned int u128 __attribute__((mode(TI)));

/* 4/7-qword copy through $8-$11 (the caller moves its 5th arg out of $8). */

#include "data/types/nostrict_text_00150000_h59.h"

f32 func_00267390(f32 *, f32 *);
void func_00162cd0(f32 *, f32 *, M64_59 *);

typedef struct { u8 pad[0x1c]; u32 n; s8 **ids; u8 *map; } Tbl59;
typedef struct { u8 id; s8 x1; u8 pad2[2]; s32 busy; f32 x8; f32 xC; u32 *p; } Slot59;
typedef struct { u8 pad[0x10]; Tbl59 *t10; Tbl59 *t14; Slot59 s[1]; } Own59;
typedef struct { u8 pad[8]; s32 x8; } Res59;
Tbl59 *func_001684e0(s32);

static inline Tbl59 *inl_tbl59(Own59 *o, Res59 *r) {
    if (r) {
        if (!o->t14) o->t14 = func_001684e0(r->x8);
        return o->t14;
    }
    return o->t10;
}

typedef struct { u32 tag; u32 size; } Chk59;

static inline s32 inl_known59(u32 t) {
    switch (t) {
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

static inline Chk59 *inl_next59(Chk59 *c) {
    if (inl_known59(c->tag)) {
        c = (Chk59 *)((u8 *)c + c->size + 8);
        if (inl_known59(c->tag)) return c;
    }
    return 0;
}

/* needs make: uses rodata */
void func_00162cd0(f32 *, f32 *, M64_59 *);
#include "data/bss_0057_mixed.h"
#include "data/bss_0056_typed.h"
#include "data/data_0035.h"

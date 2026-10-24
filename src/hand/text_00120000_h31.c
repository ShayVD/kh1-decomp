#include "common.h"
#include "data/bss_0051.h"
#include "data/bss_0052.h"

/* shared declarations */
#include "data/pieces/D_002E26A0.h"

typedef struct { u8 pad[0x10]; volatile s32 n; } Q14;
extern void func_0011ef10(s32, void *);

#include "data/types/text_00120000_h31_p.h"
extern A2 D_002C6814[];
extern void *D_002C64A0;
#include "data/pieces/D_002E26AC.h"
extern void func_001372a0(void);
extern void func_00138738(void);
extern s32 func_0011ef38(void *);
extern void func_00123790();

void func_00124b90(void) {
    s32 i;
    for (i = 0; i < 96; i++) D_002C6814[i].f0 = 0;
    D_002E26AC = &D_002C64A0;
    for (i = 0; i < 3; i++) D_002E26A0[i] = 0;
    func_001372a0();
    func_00138738();
    if (func_0011ef38(func_00123790) == 0)
        func_0011ef10(0x27cb9, func_00123790);
}

#include "data/types/text_00120000_h31.h"
extern void func_0012cb40(Q14 *, s32, s32);

static inline s32 add(Q14 *q, s32 x) {
    s32 i = q->n++;
    func_0012cb40(q, i, x);
    return i;
}

static inline f32 fmx(f32 a, f32 b) { return (b < a) ? a : b; }

typedef struct Ob50 Ob50;
typedef struct { u32 f0; u8 pad4[8]; void (*fc)(Ob50 *); } Sb50;
struct Ob50 { u32 f0; u8 pad4[0x15c]; u64 f160; u8 pad168[0x178 - 0x168]; s32 f178; Sb50 f17c; };

/* needs make: uses rodata */
#include "data/bss_004F_mixed.h"
#include "data/bss_004F_typed.h"
#include "data/data_002B.h"
#include "data/data_002E.h"

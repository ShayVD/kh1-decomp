#include "common.h"
#include "data/bss_0066.h"

/* 16-byte list entries; the D_00667F50/D_00667F54-style globals are
 * [end, begin) pointers into such lists. */
#include "data/types/text_00240000_h50.h"

/* Panel state blocks (D_00667F60, D_00668290, D_00668F90, D_006691E0). */
typedef struct { u8 pad[0x60]; Q4 q[4]; Q4 r[4]; } Panel;

typedef int u128 __attribute__((mode(TI)));

/* Render-packet headers set up before func_00237018 (D_00667DF0, D_006697C0). */
typedef struct { u8 pad[0x60]; u64 x60; u64 x68; u64 x70; u8 pad2[0x68]; u64 xe0; u8 tail[0x160 - 0xE8]; } S7df0;

#include "data/types/text_00240000_h50_p.h"

/* GS texture header: TEX0-style bitfield word at +0x18. */
#include "data/pieces/D_00304BE8_s.h"
extern s32 D_002C5C4C;
extern s32 D_002C5C50;
extern s32 D_0046A6B0[];
extern s32 D_0066AAA0;
extern void (*D_0066AA80)(void);
s32 func_001560f8(s32, void *);
void func_0024f1d0(void);

s32 func_0024f210(s32 a, void (*cb)(void)) {
    u8 c;
    s32 id;
    D_0066AAA0 = a;
    D_0066AA80 = cb;
    c = D_00304BE8->x48e[3];
    id = D_0046A6B0[c];
    if (D_002C5C4C) {
        if (c == 1) id = 0xc000a;
        else if (c == 2) id = 0xc000b;
    } else if (D_002C5C50) {
        if (c == 1) id = 0xc0008;
        else if (c == 2) id = 0xc0009;
    }
    func_001560f8(id, func_0024f1d0);
    return id;
}

/* ---- the functions below need make: they use rodata (jump tables,
 * string literals) ---- */
#include "data/bss_0066_typed.h"
#include "data/data_002C.h"
#include "data/data_0046.h"
#include "data/data_0045.h"

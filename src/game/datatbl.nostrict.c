/* Lookups into the game's data tables (D_00547BA0 ... D_00547BB0,
 * D_00533BA0, D_00308874, D_00308C70): func_00147860 an item's stat bonuses,
 * func_00147840 an item's record, func_001478e0 sets the tables up. Flag
 * mode: nostrict (the other modes are in the sibling files). Read from the
 * code, not proved by a boot (docs/modules.md "Session 53"). */
#include "common.h"
#include "data/pieces/D_0035C710.h"
#include "data/bss_0053.h"
#include "data/pieces/D_002C58A0.h"
#include "data/pieces/D_00304DB0.h"
#include "data/pieces/D_00308CDC.h"
#include "data/pieces/D_003044A0.h"

/* func_001478e0 (from hand/nostrict/text_00140000_h56.c). */
typedef struct { u8 pad[0xc]; void *pc; u8 pad10[4]; } Rel20;
typedef struct { u32 w0; void *p4; void *p8; } Rel12;
extern u8 D_0048E398[];
extern u8 D_00533BA0[];
extern Rel20 *volatile D_00547BA0;
extern void *volatile D_00547BA4;
extern Rel12 *volatile D_00547BA8;
extern void *volatile D_00547BAC;
extern void *volatile D_00547BB0;
void func_001205f0(void *, void *);
u32 func_001477c8(u32);
void func_001478e0(void) {
    void **p;
    s32 i;

    func_001205f0(D_0048E398, D_00533BA0);
    D_00308CDC = (void *)func_001477c8(0x58);
    D_003044A0 = (void *)func_001477c8(0);
    D_00547BA0 = (void *)func_001477c8(0x1a58);
    D_00547BA4 = (void *)func_001477c8(0x2e58);
    D_00547BA8 = (void *)func_001477c8(0x33d8);
    D_00547BAC = (void *)func_001477c8(0xa58);
    D_00547BB0 = (void *)func_001477c8(0xc6a8);
    p = (void *)func_001477c8(0x258);
    for (i = 0; i < 512; i++) {
        *p = (void *)func_001477c8((u32)*p);
        p++;
    }
    for (i = 0; i < 255; i++) {
        D_00547BA0[i].pc = (void *)func_001477c8((u32)D_00547BA0[i].pc);
    }
    for (i = 0; i < 63; i++) {
        D_00547BA8[i].p4 = (void *)func_001477c8((u32)D_00547BA8[i].p4);
        D_00547BA8[i].p8 = (void *)func_001477c8((u32)D_00547BA8[i].p8);
    }
}


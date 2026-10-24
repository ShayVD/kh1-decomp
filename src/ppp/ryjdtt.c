/* The pppRyjDrawMatrixWorldDtt and pppRyjDrawMatrixWorldDttFr classes
 * (docs/modules.md "Session 49"), 0x001a1f88-0x001a2178: each keeps a local
 * matrix in its work area (Con: copied from D_00615E70, or a position and a
 * scale from D_003701D0 / D_003701F0) and each frame makes the current
 * matrix owner's m2 the world matrix (local x m, x D_00615EB0, saved, then x
 * D_00616040); the Fr variant builds the local matrix from a position and
 * scales m's rows first.  Read from the code, not proved by a boot. */
#include "m2c.h"
#include "ppp.h"
#include "data/types/shared.h"

M2C_UNK func_002675a8(s32, M2C_UNK *);
M2C_UNK func_002675b8(s32, M2C_UNK *);
extern M2C_UNK D_00615E70;

void pppRyjDrawMatrixWorldDttCon(s32 arg0, PppEntry *arg1) {
    func_002675b8(arg0 + arg1->offsets[1] + 0xE0, &D_00615E70);
}

void sceVu0MulMatrix(PppMtx, PppMtx, PppMtx);
void sceVu0CopyMatrix(PppMtx, PppMtx);
typedef struct {
    u8 pad[0x10];
    PppMtx m;    /* +0x10 */
    PppMtx m2;   /* +0x50 */
} PppMtxOwner;
extern PppMtxOwner *D_00615E68; /* src/data/bss_0061.c: s32 D_00615E68 */
extern PppMtx D_00615EB0; /* src/data/bss_0061.c: u8 D_00615EB0[0x40] */
extern u8 D_00616040[];
typedef struct {
    PppMtx out;   /* +0x00 */
    PppMtx local; /* +0x40 */
} PppDttWork;

void pppRyjDrawMatrixWorldDttFrame(void *obj, void *k, PppEntry *e) {
    PppDttWork *w = (PppDttWork *) ((u8 *) obj + e->offsets[1] + 0xA0);

    sceVu0MulMatrix(D_00615E68->m2, w->local, D_00615E68->m);
    sceVu0MulMatrix(D_00615E68->m2, D_00615EB0, D_00615E68->m2);
    sceVu0CopyMatrix(w->out, D_00615E68->m2);
    sceVu0MulMatrix(D_00615E68->m2, (f32 (*)[4]) D_00616040, D_00615E68->m2);
}

#include "data/pieces/D_003701D0.h"
#include "data/pieces/D_003701F0.h"

void pppRyjDrawMatrixWorldDttFrCon(s32 arg0, PppEntry *arg1) {
    s32 temp_s0;

    temp_s0 = arg0 + arg1->offsets[1];
    func_002675a8(temp_s0 + 0xE0, ((M2C_UNK *)&D_003701D0));
    func_002675a8(temp_s0 + 0xF0, (M2C_UNK *)&D_003701F0);
}

M2C_UNK func_002672f8(s32, void *, s32);
M2C_UNK func_00267560(s32, s32, f32);
M2C_UNK func_00267620(void *);
/* m2c's view: the owner as an address. */
#define E68 ((s32)D_00615E68)

void pppRyjDrawMatrixWorldDttFrFrame(s32 arg0, s32 arg1, void *arg2) {
    s32 sp[16];    void *temp_a0;
    void *temp_s1;

    temp_s1 = (void *)arg0 + M2C_FIELD(M2C_FIELD(arg2, void **, 0xC), s32 *, 4) + 0xA0;
    func_00267620(sp);
    M2C_FIELD(sp, f32 *, 0x30) = M2C_FIELD(temp_s1, f32 *, 0x40);
    M2C_FIELD(sp, f32 *, 0x34) = M2C_FIELD(temp_s1, f32 *, 0x44);
    M2C_FIELD(sp, f32 *, 0x38) = M2C_FIELD(temp_s1, f32 *, 0x48);
    sceVu0MulMatrix((void *)sp, D_00615EB0, (void *)sp);
    func_00267560(E68 + 0x50, E68 + 0x10, M2C_FIELD(temp_s1, f32 *, 0x50));
    func_00267560(E68 + 0x60, E68 + 0x20, M2C_FIELD(temp_s1, f32 *, 0x54));
    func_00267560(E68 + 0x70, E68 + 0x30, M2C_FIELD(temp_s1, f32 *, 0x58));
    func_002672f8(E68 + 0x80, sp, E68 + 0x40);
    func_002675b8((s32)temp_s1, (M2C_UNK *)(E68 + 0x50));
    temp_a0 = (void *)(E68 + 0x50);
    sceVu0MulMatrix(temp_a0, (void *)D_00616040, temp_a0);
}

#undef E68

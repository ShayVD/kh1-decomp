/* The pppRyjMegaBirth class's default-flag functions (docs/modules.md
 * "Session 50"): func_0019bb40 is a random number in -a/2 .. 3a/2 from
 * vu0.c's func_0019baf8; func_0019bb98 is the gate the frame and the draw
 * check (the particle block, and the extras the key asks for, allocated);
 * func_0019cfc0 is the draw's base matrix (unless the key's mode says the
 * particles are in world space).  The Con clears the work area and
 * D_0061E2D0 (defined here: nothing else uses it); the Des frees the three
 * particle blocks with func_00183b20.  ryjmb.nostrict.c has the rest of the
 * class.  Read from the code, not proved by a boot. */
#include "m2c.h"
#include "platform/vu.h"
#include "ppp.h"

typedef unsigned int u128 __attribute__((mode(TI)));
typedef f32 PppMtx[4][4] __attribute__((aligned(16)));

typedef struct {
    u8 pad[0x10];
    PppMtx m;    /* +0x10 */
    PppMtx m2;   /* +0x50 */
} PppMtxOwner;

extern PppMtxOwner *D_00615E68; /* src/data/bss_0061.c: s32 D_00615E68 */
extern PppMtx D_00615EB0; /* src/data/bss_0061.c: u8 D_00615EB0[0x40] */
f32 func_0019baf8(void);

s8 func_0019bb40(u8 a) {
    f32 f = func_0019baf8();

    return (f32) (a * 2) * f - (f32) (a >> 1);
}

typedef struct {
    u8 pad[0x50];
    s32 unk50;
    s32 unk54;
    s32 unk58;
} PppBb98A;

typedef struct {
    u8 pad[0xC9];
    u8 unkC9;
    u8 padCA[2];
    u8 unkCC;
} PppBb98B;

s32 func_0019bb98(PppBb98A *p, PppBb98B *q) {
    if (p->unk50 == 0)
        return 0;
    if ((u8) (q->unkCC - 1) < 2 && p->unk54 == 0)
        return 0;
    if (q->unkC9 != 0 && p->unk58 == 0)
        return 0;
    return 1;
}

void func_0019cfc0(PppMtx out, PppBb98B *q, PppMtx m) {
    if (q->unkCC != 0)
        return;
    PlatVu0MulMatrix(out, m, D_00615E68->m);
    PlatVu0MulMatrix(out, D_00615EB0, out);
}

PppMtx D_0061E2D0 ALIGNED(16);
typedef struct {
    PppMtx m;   /* +0x00 */
    u128 q;     /* +0x40 */
    s32 i[4];   /* +0x50 */
    s16 h[2];   /* +0x60 */
} PppMegaBirth;

void pppRyjMegaBirthCon(void *obj, PppEntry *e) {
    PppMegaBirth *w = (PppMegaBirth *) ((u8 *) obj + e->offsets[2] + 0xA0);

    PlatVu0UnitMatrix(w->m);
    w->q = 0;
    w->i[0] = 0;
    w->i[1] = 0;
    w->i[2] = 0;
    w->i[3] = 0;
    w->h[0] = 0;
    w->h[1] = 0;
    PlatVu0UnitMatrix(D_0061E2D0);
}

M2C_UNK func_00183b20(s32, s32);
extern s32 D_00615E64;

void pppRyjMegaBirthDes(s32 arg0, PppEntry *arg1) {
    s32 temp_a1;
    s32 temp_a1_2;
    s32 temp_v0;
    void *temp_s0;

    temp_s0 = arg0 + arg1->offsets[2] + 0xA0;
    temp_v0 = M2C_FIELD(temp_s0, s32 *, 0x50);
    if (temp_v0 != 0) {
        func_00183b20(D_00615E64, temp_v0);
        M2C_FIELD(temp_s0, s32 *, 0x50) = 0;
    }
    temp_a1 = M2C_FIELD(temp_s0, s32 *, 0x54);
    if (temp_a1 != 0) {
        func_00183b20(D_00615E64, temp_a1);
        M2C_FIELD(temp_s0, s32 *, 0x54) = 0;
    }
    temp_a1_2 = M2C_FIELD(temp_s0, s32 *, 0x58);
    if (temp_a1_2 != 0) {
        func_00183b20(D_00615E64, temp_a1_2);
        M2C_FIELD(temp_s0, s32 *, 0x58) = 0;
    }
}

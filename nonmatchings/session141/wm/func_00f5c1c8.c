/* 13 words left (score 26): register allocation in the first loop only (original: pointer a0, consts t1/t0/a3/a2; ours v1/t0/a3/a2/a0). The CONTEXT_ONLY func_00f5ae10 stub fixes the second loop bltz/bltzl (session 131b near miss). Tried pointer/index/countdown forms, if-chain vs switch, local World *, 10 min permuter (no gain). */
#include "ovl.h"

typedef struct {
    u8 pad0[4];
    u16 kind;
    u8 pad6[6];
} Ent;

typedef struct {
    u8 pad0[0xA4];
    u16 count;
    u8 padA6[0x110 - 0xA6];
    Ent ent[1];
} World;

extern World *D_00F9B540;
extern s32 D_00F9B568;
CONTEXT_ONLY void func_00f5ae10(void *a, s32 b) {}
void func_00f5ae98(s32, s32);
s32 func_00f68770(s32, s32, void *, s32, s32);

void func_00f5c1c8(void) {
    OvlMtx m;
    OvlMtx w;
    OvlMtx r;
    s32 mode = -1;
    s32 i;

    for (i = 0; i < D_00F9B540->count; i++) {
        switch (D_00F9B540->ent[i].kind - 1) {
        case 54:
            if (mode < 0) {
                mode = 0;
            }
            break;
        case 55:
            if (mode <= 0) {
                mode = 1;
            }
            break;
        }
    }
    if (mode < 0) {
        return;
    }
    PlatVu0UnitMatrix(r);
    PlatVu0RotMatrixY(r, r, 3.141592503f);
    for (i = 0; i < D_00F9B540->count; i++) {
        switch (D_00F9B540->ent[i].kind - 1) {
        case 0:
        case 1:
        case 2:
        case 3:
            func_00f5ae10(w, i);
            PlatVu0UnitMatrix(m);
            PlatVu0CopyVector(m[3], w[3]);
            if (mode != 0) {
                func_00f5ae98(func_00f68770(27, 1, m, 0, D_00F9B568), 8);
            }
            PlatVu0MulMatrix(m, m, r);
            func_00f5ae98(func_00f68770(27, 1, m, 0, D_00F9B568), 8);
            return;
        }
    }
}

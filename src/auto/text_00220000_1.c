/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
#include "data/bss_0064.h"

M2C_UNK func_0011d768(M2C_UNK);
M2C_UNK func_001f36b8(s32);
M2C_UNK func_001f3d58(s32, M2C_UNK);
M2C_UNK func_001f3e48(s32, void *);
M2C_UNK func_001f4058(s32, M2C_UNK);
M2C_UNK func_0020bda8(M2C_UNK);
M2C_UNK func_00222ba8();
M2C_UNK func_00223980(s32, M2C_UNK, M2C_UNK);
M2C_UNK func_00224698(s32);
M2C_UNK func_00233ef8(M2C_UNK);
extern M2C_UNK D_003F6950;
extern s32 D_003F34C8;
extern s32 D_003F5C1C;
extern s32 D_003F6E28;
extern s32 D_003F6E30;
extern s32 D_006436B8;
extern s32 D_006436BC;
extern s32 D_006436C0;
extern s32 D_006436C4;
extern s32 D_006436D0;
extern s32 D_006436D4;
extern s32 D_00643708;
extern s32 D_0064373C;
extern s32 D_00643758;
extern s32 D_00643794;
extern s32 D_00643798;
s32 func_001f31a8(M2C_UNK *, M2C_UNK);

void func_002234b8(void) {
    func_00222ba8();
    D_003F5C1C = D_006436B8 != 0;
}

void func_002234e8(void) {
    D_006436BC = 0;
    D_006436C0 = 0;
    D_006436C4 = 0;
}

void func_00223e68(void) {
    D_00643798 += 1;
    D_00643794 += 1;
    D_003F34C8 -= 1;
}

void func_002259c8(void *arg0) {
    s32 temp_v0;

    func_001f36b8(M2C_FIELD(arg0, s32 *, 0x10));
    func_0011d768(3);
    D_0064373C = 0;
    D_00643758 = 0;
    func_00223980(D_006436D4, 0, 0);
    func_00233ef8(0);
    temp_v0 = func_001f31a8(&D_003F6950, 6);
    if (temp_v0 != 0) {
        func_001f3e48(temp_v0, arg0);
        func_001f4058(temp_v0, 1);
        func_001f3d58(temp_v0, 6);
        func_00224698(temp_v0);
        func_0020bda8(0x10);
    }
}

void func_00229820(void) {
    D_00643798 = 0;
    D_003F6E30 = 0;
    D_003F6E28 = 0;
    D_006436D0 = 0;
    D_00643708 = 0;
}

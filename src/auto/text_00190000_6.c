/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
#include "ppp.h"
M2C_UNK func_001a62a8(s32);
M2C_UNK func_001a6538(s32);
M2C_UNK func_001a67a0(s32);
M2C_UNK func_002672f8(M2C_UNK *, s32, s32);
M2C_UNK func_00267328(s32, M2C_UNK *, s32);
M2C_UNK func_002673b8(M2C_UNK *, s32);
M2C_UNK func_002675a8(s32, M2C_UNK *);
M2C_UNK func_002675b8(s32, M2C_UNK *);
#include "data/pieces/D_003701D0.h"
#include "data/pieces/D_003701F0.h"
extern M2C_UNK D_00615E70;
extern M2C_UNK D_00616040; /* src/data/bss_0061.c: u8 D_00616040[0x40] */
extern s32 D_00615E68;
void func_001a60d0(s32);
void func_001a60e8(s32, s32);

void func_00192f78(s32 arg0) {
    s32 sp[8];
    M2C_FIELD(sp, s32 *, 0x4) = M2C_FIELD(arg0, s32 *, 0x24);
    M2C_FIELD(sp, f32 *, 0xC) = M2C_FIELD(arg0, f32 *, 0x20);
    M2C_FIELD(sp, M2C_UNK * *, 0x8) = &D_00616040;
    M2C_FIELD(sp, s32 *, 0x10) = arg0 + 0x10;
    M2C_FIELD(sp, s32 *, 0x0) = arg0;
    func_001a60e8((s32) sp, 0);
}

void pppKeLnsArndTCon(s32 arg0, PppEntry *arg1) {
    func_001a62a8(arg0 + arg1->offsets[0] + 0xA0);
}

void pppKeLnsArndTDes(void) {

}

void pppKeLnsClmTCon(s32 arg0, s32 arg1) {
    s32 temp_s0;

    temp_s0 = arg0 + *M2C_FIELD(arg1, s32 **, 0xC) + 0xA0;
    func_001a60d0(temp_s0);
    M2C_FIELD(temp_s0, s8 *, 8) = 4;
}

void pppKeLnsCrnTCon(s32 arg0, PppEntry *arg1) {
    func_001a6538(arg0 + arg1->offsets[0] + 0xA0);
}

void pppKeLnsCrnTDes(void) {

}

void pppKeLnsFlsTCon(s32 arg0, PppEntry *arg1) {
    func_001a67a0(arg0 + arg1->offsets[0] + 0xA0);
}

void pppKeLnsFlsTDes(void) {

}

void pppKeParMatRFrame(void *arg0) {
    s32 sp[20];    s32 temp_a0;
    s32 temp_s0;
    s32 temp_s1;

    temp_s0 = M2C_FIELD(arg0, s32 *, 4);
    temp_s1 = temp_s0 + 0x10;
    func_002673b8(sp, temp_s1);
    func_002673b8(&M2C_FIELD(sp, M2C_UNK *, 0x10), temp_s0 + 0x20);
    func_002673b8(&M2C_FIELD(sp, M2C_UNK *, 0x20), temp_s0 + 0x30);
    func_002672f8(&M2C_FIELD(sp, M2C_UNK *, 0x40), temp_s1, D_00615E68 + 0x40);
    temp_a0 = D_00615E68 + 0x10;
    func_00267328(temp_a0, sp, temp_a0);
    func_002675a8(D_00615E68 + 0x40, &M2C_FIELD(sp, M2C_UNK *, 0x40));
}

void pppRyjDrawMatrixWorldCon(s32 arg0, PppEntry *arg1) {
    func_002675b8(arg0 + arg1->offsets[1] + 0xA0, &D_00615E70);
}

void pppRyjDrawMatrixWorldFrontCon(s32 arg0, PppEntry *arg1) {
    s32 temp_s0;

    temp_s0 = arg0 + arg1->offsets[1];
    func_002675a8(temp_s0 + 0xA0, ((M2C_UNK *)&D_003701D0));
    func_002675a8(temp_s0 + 0xB0, (M2C_UNK *)&D_003701F0);
}

void pppRyjDrawMatrixWorldNoRotCon(s32 arg0, PppEntry *arg1) {
    s32 temp_s0;

    temp_s0 = arg0 + arg1->offsets[1];
    func_002675a8(temp_s0 + 0xA0, ((M2C_UNK *)&D_003701D0));
    func_002675a8(temp_s0 + 0xB0, (M2C_UNK *)&D_003701F0);
}

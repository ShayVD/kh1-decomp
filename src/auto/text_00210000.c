/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
#include "data/bss_0064.h"

M2C_UNK func_001efcb0(s32, s32);
M2C_UNK func_002192f8();
M2C_UNK func_00219348();
M2C_UNK func_00219380();
M2C_UNK func_002193b8();
M2C_UNK func_002193f0();
M2C_UNK func_00219500();
M2C_UNK func_0021ae28();
M2C_UNK func_0021cfc8();
M2C_UNK func_0021d188();
M2C_UNK func_0021dc40();
M2C_UNK func_0021fb28();
M2C_UNK func_00220590();
M2C_UNK func_002210c0();
M2C_UNK func_00222b50();
M2C_UNK func_002234b8();
M2C_UNK func_00223948();
M2C_UNK func_00266f38(s32, M2C_UNK *);
extern M2C_UNK D_00642EB0;
extern M2C_UNK D_00642F60;
extern s32 *D_003F34B8;
extern s32 D_002B6478;
#include "data/pieces/D_003E3D68.h"
extern s32 D_003F34E8;
extern s32 D_00641250;
extern s32 D_00641BC4;
extern s32 D_00641BC8;
extern s32 D_00641BCC;
extern s32 D_00641BD0;
extern s32 D_00641BD4;
extern s32 D_00641BD8;
extern s32 D_00641BDC;
extern s32 D_00641C04;
extern s32 D_00641C08;
extern s32 D_00642C58; /* src/data/bss_0064.c: u32 D_00642C58 */
extern s32 D_00642C5C;
extern s32 D_00642C60;
extern s32 D_00642C64;
extern s32 D_00642C68;
extern s32 D_00642C6C;
extern s32 D_00642C70;
extern s32 D_00642CCC;
extern s32 D_00642CD0;
extern s32 D_00642CD4;
extern s32 D_00642CD8;
extern s32 D_00642CDC;
extern s32 D_00642CE0;
extern s32 D_00642D18;
extern s32 D_00642D24;
extern s32 D_00643100;
s32 func_001ebea8();
s32 func_001ef5c0(s32);
s32 func_001ef5f8(s32);
s32 func_00266c08(M2C_UNK);

void func_00211358(void) {
    s32 temp_a1;

    temp_a1 = D_003E3D68 + func_001ebea8();
    if (temp_a1 < D_00641250) {
        D_00641250 = temp_a1;
    }
}

void func_00213d30(void) {
    D_00641BC4 = 0;
    D_00641BC8 = 0;
    D_00641BCC = 0;
    D_00641BD0 = 0;
    D_00641BD4 = 0;
    D_00641BD8 = 0;
    D_00641BDC = 0;
    D_00641C04 = 0;
    D_00641C08 = 0;
}

s32 func_00213d80(s32 arg0) {
    return (func_001ef5f8(arg0 & ~0x80) << 0x10) | (arg0 & 0x80);
}

s32 func_00213db8(s32 arg0) {
    s32 temp_s0;
    s32 temp_s1;

    temp_s0 = arg0 & ~0x80;
    temp_s1 = func_001ef5c0(temp_s0);
    return (temp_s1 << 0x18) | (func_001ef5f8(temp_s0) << 8) | (arg0 & 0x80);
}

s32 func_00213e18(s32 arg0) {
    return ((arg0 & 0x80) << 0x10) | func_001ef5f8(arg0 & ~0x80);
}

void func_00216140(void) {
    D_00642C58 = 0;
    D_00642C5C = 0;
    D_00642C60 = 0;
    D_00642C64 = 0;
    D_00642C68 = 0;
    D_00642C6C = 0;
    D_00642C70 = 0;
}

void func_00217fe8(void) {
    D_00642CCC = 0;
    D_00642CD0 = 0;
    D_00642CD4 = 0;
    D_00642CD8 = 0;
    D_00642CDC = 0;
    D_00642CE0 = 0;
}

void func_00219118(void) {
    D_00642D18 = 0;
}

s32 func_00219288(void) {
    return *D_003F34B8;
}

void func_00219308(void) {
    func_002192f8();
}

void func_00219358(void) {
    func_00219348();
}

void func_00219390(void) {
    func_00219380();
}

void func_002193c8(void) {
    func_002193b8();
}

void func_00219400(void) {
    func_002193f0();
}

s32 func_00219428(void) {
    return D_002B6478 == 2;
}

void func_0021adb0(void) {
    func_00219500();
}

void func_0021adc8(void) {
    D_00642D24 = 0;
}

s32 func_0021b7f0(void) {
    return D_00643100;
}

void func_0021b800(s32 arg0) {
    func_001efcb0(D_003F34E8, arg0);
}

void func_0021b820(void) {
    func_00266f38(func_00266c08(2), &D_00642EB0);
    func_00266f38(func_00266c08(2), &D_00642F60);
}

void func_0021dad8(void) {
    func_0021d188();
    func_0021fb28();
    func_00220590();
    func_002210c0();
    func_00223948();
    func_00222b50();
    func_002234b8();
    func_0021cfc8();
    func_0021ae28();
}

s32 func_0021dc38(s32 arg0) {
    return arg0;
}

void func_0021fb10(void) {
    func_0021dc40();
}

s32 func_0021fd88(s32 arg0) {
    return arg0;
}
#include "data/data_002B.h"
#include "data/data_003F.h"

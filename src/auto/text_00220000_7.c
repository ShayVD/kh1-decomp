/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

extern M2C_UNK D_003F6950;
extern M2C_UNK D_003F69E0;
extern M2C_UNK D_003F6A10;
extern M2C_UNK D_003F6A40;
extern M2C_UNK D_003F6A70;
extern M2C_UNK D_003F6AA0;
extern M2C_UNK D_003F6E70;
extern M2C_UNK D_003F6EA0;
extern M2C_UNK D_003F6ED0;
extern M2C_UNK D_003F6F00;
extern s32 D_006436D4;
extern s32 D_00643734;
extern s32 D_00643738;
extern s32 D_0064373C;
extern s32 D_00643758;
extern s32 D_006437DC;
extern s32 D_006437E0;
extern s32 D_006437E4;
extern s32 D_006469A4;
extern void *D_00425BC8;
extern void *D_00643740;
extern void *D_00646990;
s32 func_0011d768(s32);
s32 func_001f31a8(s32, s32);
s32 func_001f3520(s32, s32);
s32 func_001f42b8(s32);
s32 func_001fe570(s32);
s32 func_00207bb0(s32, s32);
void func_001f36b8(s32);
void func_001f3758(s32);
void func_001f3d58(s32, s32);
void func_001f3e48(s32, s32);
void func_001f4058(s32, s32);
void func_0020bd18(s32, s32);
void func_0020bda8(s32);
void func_00223980(s32, s32, s32);
void func_00224698(s32);
void func_00224c48(s32);
void func_00224d68(s32);
void func_00224e88(s32);
void func_00225030(s32);
void func_00225150(s32);
void func_002299b0(s32);
void func_00229bd8(s32);
void func_00229cf8(s32);
void func_00229e18(s32);
void func_00233ef8(s32);

s32 func_002239b0(s32 arg0) {
    if (func_001f42b8(arg0) != 0) {
        if (M2C_FIELD(D_00425BC8, s32 *, 8) & 0x4000) {
            func_001f36b8(arg0);
            func_0011d768(3);
        } else {
            func_0020bd18(arg0, 8);
            if (func_001fe570(arg0) != 0) {
                func_001f36b8(arg0);
            }
        }
    }
    return func_00207bb0(arg0, 0x190);
}

void func_002246f8(s32 arg0) {
    s32 temp_v0;

    func_001f3758(M2C_FIELD(D_00643740, s32 *, 0x10));
    func_0011d768(3);
    D_0064373C = 0;
    D_00643758 = 0;
    D_00643738 = 0;
    func_00223980(D_006436D4, 0, 0);
    func_00233ef8(0);
    temp_v0 = func_001f31a8((s32) &D_003F6950, 6);
    if (temp_v0 != 0) {
        func_001f3e48(temp_v0, arg0);
        func_001f4058(temp_v0, 1);
        func_001f3d58(temp_v0, 6);
        func_00224698(temp_v0);
    }
}

void func_00225a90(s32 arg0) {
    s32 temp_v0;

    func_001f36b8(M2C_FIELD(arg0, s32 *, 0x10));
    func_0011d768(4);
    D_00643734 = 0;
    D_0064373C = 0;
    D_00643758 = 0;
    func_00223980(D_006436D4, 0, 0);
    func_00233ef8(0);
    temp_v0 = func_001f31a8((s32) &D_003F69E0, 6);
    if (temp_v0 != 0) {
        func_001f3e48(temp_v0, arg0);
        func_001f4058(temp_v0, 1);
        func_001f3d58(temp_v0, 6);
        func_00224c48(temp_v0);
        func_0020bda8(0x10);
    }
}

void func_00225b60(s32 arg0) {
    s32 temp_v0;

    func_001f36b8(M2C_FIELD(arg0, s32 *, 0x10));
    func_0011d768(4);
    D_00643734 = 0;
    D_0064373C = 0;
    D_00643758 = 0;
    func_00223980(D_006436D4, 0, 0);
    func_00233ef8(0);
    temp_v0 = func_001f31a8((s32) &D_003F6A10, 6);
    if (temp_v0 != 0) {
        func_001f3e48(temp_v0, arg0);
        func_001f4058(temp_v0, 1);
        func_001f3d58(temp_v0, 6);
        func_00224d68(temp_v0);
        func_0020bda8(0x10);
    }
}

void func_00225c30(s32 arg0) {
    s32 temp_v0;

    func_001f36b8(M2C_FIELD(arg0, s32 *, 0x10));
    func_0011d768(6);
    D_00643734 = 0;
    D_0064373C = 0;
    D_00643758 = 0;
    func_00233ef8(0);
    func_00223980(D_006436D4, 0, 0);
    temp_v0 = func_001f3520((s32) &D_003F6A70, 6);
    if (temp_v0 != 0) {
        func_001f3e48(temp_v0, arg0);
        func_001f4058(temp_v0, 1);
        func_001f3d58(temp_v0, 6);
        func_00225030(temp_v0);
        M2C_FIELD(temp_v0, s16 *, 0xDA) = 0x10;
        func_0020bda8(0x10);
    }
}

void func_00225d08(s32 arg0) {
    s32 temp_v0;

    func_001f36b8(M2C_FIELD(arg0, s32 *, 0x10));
    func_0011d768(4);
    D_00643734 = 0;
    D_0064373C = 0;
    D_00643758 = 0;
    func_00223980(D_006436D4, 0, 0);
    func_00233ef8(0);
    temp_v0 = func_001f31a8((s32) &D_003F6AA0, 6);
    if (temp_v0 != 0) {
        func_001f3e48(temp_v0, arg0);
        func_001f4058(temp_v0, 1);
        func_001f3d58(temp_v0, 6);
        func_00225150(temp_v0);
        func_0020bda8(0x10);
    }
}

void func_00225dd8(s32 arg0) {
    s32 temp_v0;

    func_001f36b8(M2C_FIELD(arg0, s32 *, 0x10));
    func_0011d768(4);
    D_00643734 = 0;
    D_0064373C = 0;
    D_00643758 = 0;
    func_00223980(D_006436D4, 0, 0);
    func_00233ef8(0);
    temp_v0 = func_001f31a8((s32) &D_003F6A40, 6);
    if (temp_v0 != 0) {
        func_001f3e48(temp_v0, arg0);
        func_001f4058(temp_v0, 1);
        func_001f3d58(temp_v0, 6);
        func_00224e88(temp_v0);
        func_0020bda8(0x10);
    }
}

void func_00229a10(s32 arg0) {
    s32 temp_v0;

    func_001f3758(M2C_FIELD(D_00646990, s32 *, 0x10));
    func_0011d768(3);
    D_006437E4 = 0;
    D_006469A4 = 0;
    D_006437E0 = 0;
    func_00233ef8(0);
    temp_v0 = func_001f31a8((s32) &D_003F6E70, 6);
    if (temp_v0 != 0) {
        func_001f3e48(temp_v0, arg0);
        func_001f4058(temp_v0, 2);
        func_001f3d58(temp_v0, 6);
        func_002299b0(temp_v0);
    }
}

void func_0022a3a0(s32 arg0) {
    s32 temp_v0;

    func_001f36b8(M2C_FIELD(arg0, s32 *, 0x10));
    func_0011d768(3);
    D_006437E4 = 0;
    D_006469A4 = 0;
    func_00233ef8(0);
    temp_v0 = func_001f31a8((s32) &D_003F6E70, 6);
    if (temp_v0 != 0) {
        func_001f3e48(temp_v0, arg0);
        func_001f4058(temp_v0, 2);
        func_001f3d58(temp_v0, 6);
        func_002299b0(temp_v0);
        func_0020bda8(0x10);
    }
}

void func_0022a458(s32 arg0) {
    s32 temp_v0;

    func_001f36b8(M2C_FIELD(arg0, s32 *, 0x10));
    func_0011d768(4);
    D_006437DC = 0;
    D_006437E4 = 0;
    D_006469A4 = 0;
    func_00233ef8(0);
    temp_v0 = func_001f31a8((s32) &D_003F6EA0, 6);
    if (temp_v0 != 0) {
        func_001f3e48(temp_v0, arg0);
        func_001f4058(temp_v0, 2);
        func_001f3d58(temp_v0, 6);
        func_00229bd8(temp_v0);
        func_0020bda8(0x10);
    }
}

void func_0022a518(s32 arg0) {
    s32 temp_v0;

    func_001f36b8(M2C_FIELD(arg0, s32 *, 0x10));
    func_0011d768(4);
    D_006437DC = 0;
    D_006437E4 = 0;
    D_006469A4 = 0;
    func_00233ef8(0);
    temp_v0 = func_001f31a8((s32) &D_003F6ED0, 6);
    if (temp_v0 != 0) {
        func_001f3e48(temp_v0, arg0);
        func_001f4058(temp_v0, 2);
        func_001f3d58(temp_v0, 6);
        func_00229cf8(temp_v0);
        func_0020bda8(0x10);
    }
}

void func_0022a5d8(s32 arg0) {
    s32 temp_v0;

    func_001f36b8(M2C_FIELD(arg0, s32 *, 0x10));
    func_0011d768(4);
    D_006437DC = 0;
    D_006437E4 = 0;
    D_006469A4 = 0;
    func_00233ef8(0);
    temp_v0 = func_001f31a8((s32) &D_003F6F00, 6);
    if (temp_v0 != 0) {
        func_001f3e48(temp_v0, arg0);
        func_001f4058(temp_v0, 2);
        func_001f3d58(temp_v0, 6);
        func_00229e18(temp_v0);
        func_0020bda8(0x10);
    }
}

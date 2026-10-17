/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

extern s32 D_0046A55C;
extern s32 D_0046A618;
extern s32 D_0046A674;
extern s32 D_0046A67C;
extern s32 D_0046A680;
extern s32 D_00652898;
extern s32 D_00655264;
extern s32 D_00669A38;
extern s32 D_00669A3C;
extern s32 D_00669A7C;

void func_00242bc0(void) {
    D_00655264 = 1;
}

void func_00242bd0(void) {
    D_00652898 = 0;
}

void func_00242be0(void) {
    D_00652898 = 1;
}

s32 func_0024a488(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0x88);
}

s32 func_0024a6b0(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0x9C);
}

void func_0024abd8(s32 arg0, void *arg1) {
    s32 var_a0;
    void *var_a1;

    var_a0 = arg0;
    var_a1 = arg1;
    if (var_a0 > 0) {
        do {
            var_a0 -= 1;
            M2C_FIELD(var_a1, s32 *, 0x10) = 0;
            M2C_FIELD(var_a1, s32 *, 0x14) = 0;
            var_a1 += 0x20;
        } while (var_a0 != 0);
    }
}

void func_0024b1e8(void) {

}

s32 func_0024b9c0(void) {
    return D_00669A38;
}

s32 func_0024b9d0(void) {
    return D_00669A3C;
}

void func_0024b9e0(s32 arg0) {
    D_00669A38 = arg0;
}

void func_0024b9f0(s32 arg0) {
    D_00669A3C = arg0;
}

s32 func_0024cf90(void) {
    return D_00669A7C;
}

s32 func_0024d408(void) {
    return D_0046A55C;
}

s32 func_0024d608(void) {
    return D_0046A618;
}

s32 func_0024db68(void) {
    return D_0046A674;
}

void func_0024e088(s32 arg0) {
    D_0046A67C = arg0;
}

s32 func_0024e098(void) {
    return D_0046A680;
}

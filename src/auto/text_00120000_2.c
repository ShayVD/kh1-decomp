/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
M2C_UNK func_001249d8();
M2C_UNK func_0012c180(s32, void *);
M2C_UNK func_0012fc20();
M2C_UNK func_00133520();
M2C_UNK func_00137330(void *, s32, s32);
M2C_UNK func_0013bd08();
M2C_UNK func_00146508();
M2C_UNK func_00149660(s32, void *);
M2C_UNK func_0014c378();
M2C_UNK func_00151808();
M2C_UNK func_001574f0();
M2C_UNK func_00157a30(void *, M2C_UNK, M2C_UNK);
M2C_UNK func_00168518();
M2C_UNK func_001762c8();
M2C_UNK func_00176c60(M2C_UNK);
M2C_UNK func_0017db68();
M2C_UNK func_0017ebd0();
M2C_UNK func_00239488();
extern s32 D_00351A48;
f32 func_00120c18();
f32 func_0026b9a8(f32, f32);
s32 func_0012f040(void *, M2C_UNK);
s32 func_00153d78(void *);

void func_001210f0(void *arg0, void *arg1, f32 fparg0) {
    M2C_FIELD(arg0, f32 *, 0) = (f32) (M2C_FIELD(arg1, f32 *, 0) * fparg0);
    M2C_FIELD(arg0, f32 *, 4) = (f32) M2C_FIELD(arg1, f32 *, 4);
    M2C_FIELD(arg0, f32 *, 8) = (f32) (M2C_FIELD(arg1, f32 *, 8) * fparg0);
    M2C_FIELD(arg0, f32 *, 0xC) = (f32) M2C_FIELD(arg1, f32 *, 0xC);
}

void func_00121a10(void *arg0, void *arg1) {
    f32 temp_f0;

    M2C_FIELD(arg1, f32 *, 0) = func_0026b9a8(-M2C_FIELD(arg0, f32 *, 4), func_00120c18());
    temp_f0 = func_0026b9a8(M2C_FIELD(arg0, f32 *, 0), M2C_FIELD(arg0, f32 *, 8));
    M2C_FIELD(arg1, s32 *, 8) = 0;
    M2C_FIELD(arg1, f32 *, 4) = temp_f0;
    M2C_FIELD(arg1, f32 *, 0xC) = 1.0f;
}

void func_00122330(void) {
    func_00239488();
    func_00176c60(0);
    func_0013bd08();
    func_0014c378();
    func_001249d8();
    func_0012fc20();
    func_0017ebd0();
    func_0017db68();
    func_00133520();
    func_00146508();
    func_00151808();
    func_001762c8();
    func_00168518();
    D_00351A48 = 6;
    func_001574f0();
}

void func_00122f48(void *arg0, f32 fparg0) {
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x130), f32 *, 0x44) = fparg0;
}

void func_0012c238(s32 arg0, s32 arg1, void *arg2) {
    s32 temp_s1;

    temp_s1 = arg1 & ~0x400;
    if (!(((u32) *M2C_FIELD(arg2, u32 **, 0x6C) >> 2) & 1)) {
        func_00149660(temp_s1, arg2);
        func_00137330(arg2, arg0, temp_s1 | 0x10000);
        if (M2C_FIELD(arg2, s32 *, 0) & 0x8000) {
            if (arg0 != arg2) {
                if (M2C_FIELD(M2C_FIELD(arg2, void **, 0x130), s8 *, 0x54) == 1) {
                    if ((func_0012f040(arg2, -1) != 0) && (func_00153d78(arg2) == 0)) {
                        func_00157a30(arg2, 0x17, 0);
                    }
                }
            }
            func_0012c180(temp_s1, arg2);
        }
    }
}
#include "data/bss_0052_mixed.h"
#include "data/pieces/D_00351A48.h"

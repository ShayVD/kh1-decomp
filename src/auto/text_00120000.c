/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
#include "data/bss_004F.h"

M2C_UNK D_00F20000(M2C_UNK, s32);
M2C_UNK func_0011efa8(M2C_UNK *, M2C_UNK *, M2C_UNK, M2C_UNK);
M2C_UNK func_001247e8(s32);
M2C_UNK func_00124c68();
M2C_UNK func_00127340();
M2C_UNK func_00132e38();
M2C_UNK func_0013cec8(s32);
M2C_UNK func_0013cfe8(s32, M2C_UNK, s32);
M2C_UNK func_0013f2c0();
M2C_UNK func_001478e0();
M2C_UNK func_00148e60();
M2C_UNK func_0014a380(s32, s32);
M2C_UNK func_0014f868();
M2C_UNK func_00151b90();
M2C_UNK func_00176310(s32);
M2C_UNK func_001ef7b0(s32);
M2C_UNK func_00266f38(s32, s32);
M2C_UNK func_0026a9d0(s32);
M2C_UNK func_0026b978(f32);
M2C_UNK func_0026b9a8(f32, f32);
M2C_UNK func_00270b40();
extern M2C_UNK D_002E2F28;
extern M2C_UNK D_002E2F34;
extern M2C_UNK D_004F6EC0; /* src/data/bss_004F.c: TPool D_004F6EC0 */
M2C_UNK D_004F6ED0[0xa0] ALIGNED(16);
extern M2C_UNK func_00120908;
extern f32 D_002BBDFC;
extern f32 D_002BBE00;
extern f32 D_002E27A0;
extern f32 D_004F77E4;
extern s32 D_0029B418;
extern s32 D_002BBE04;
extern s32 D_002E31A8;
extern s32 D_00304B78;
extern s32 D_00350D7C;
extern s32 D_004F6EB8; /* src/data/bss_004F.c: u32 *D_004F6EB8 */
extern s32 D_00514F10;
extern s32 D_00514F14;
extern u32 D_002BBDE4;
extern u32 D_002C5958;
f32 func_00121748();
f32 func_00176850();
s32 func_00120930();
s32 func_001226f0(s32, s32, s32);
s32 func_001230a0(s32);
s32 func_001233e8(s32);
s32 func_00123488();
s32 func_00124218(s32);
s32 func_0012ef30(s32, s32, s32, f32);
s32 func_00131b08(s32);
s32 func_001349d0(s32, s32);
s32 func_001354b8(s32, s32);
s32 func_00137330(s32, s32, s32);
s32 func_001389c0(s32);
s32 func_001389e8(s32);
s32 func_0013a670(s32, s32, f32, f32);
s32 func_00142480(s32, s32, s32, s32);
s32 func_00142b30(s32, s32);
s32 func_00142c80(s32, s32);
s32 func_001477c8(s32);
s32 func_00147c98(s32, s32, s32);
s32 func_00148968(s32, s32, s32);
s32 func_00148a40(s32, s32);
s32 func_00148b70(s32, s32, s32, f32);
s32 func_0014ee88(s32);
s32 func_0014efe0(s32, s32);
s32 func_0014f5c8(s32);
s32 func_0014f600(s32);
s32 func_00157528(s32);
s32 func_0015bd78(s32, s32, M2C_UNK);
s32 func_001ef7a0();
s32 func_0025ed28(s32, M2C_UNK, M2C_UNK);
s32 func_00266c08(M2C_UNK);
s32 func_0026a530(M2C_UNK);
void *func_0011ef10(M2C_UNK, M2C_UNK *);
void *func_00120190(s32);
void *func_00121de0();
void *func_00130578(s32, s32, f32);
void *func_0014a4a8(void *, s32, s32);

void func_00120038(s32 *arg0) {
    *arg0 = 0;
}

void func_00120888(s32 arg0) {
    void *temp_v0;

    if (func_0026a530(1) == 2) {
        temp_v0 = func_00120190(arg0);
        if (temp_v0 != NULL) {
            func_0026a9d0(M2C_FIELD(temp_v0, s32 *, 8));
        }
    }
}

void func_001209d8(void) {
    s32 temp_a0;
    s32 temp_s0;

    temp_s0 = func_00120930();
    temp_a0 = temp_s0;
    do {

    } while (func_0025ed28(temp_a0, 0, 0) < 0);
}

void func_00120a70(void) {
    M2C_FIELD(func_0011ef10(0x2D2A8, &func_00120908), s16 *, 2) = -1;
}

void func_00121840(void) {
    func_0026b978(func_00121748());
}

f32 func_00121b08(f32 fparg0) {
    f32 var_f12;

    var_f12 = fparg0;
    if (var_f12 > 0.0f) {
        var_f12 -= D_002BBDFC;
        if (var_f12 < 0.0f) {
            var_f12 = 0.0f;
        }
    }
    return var_f12;
}

void func_00121eb0(void) {
    s32 *temp_v1;
    void *temp_v0;

    temp_v0 = func_00121de0();
    temp_v1 = M2C_FIELD(temp_v0, s32 **, 0xC);
    if (temp_v1 != NULL) {
        *temp_v1 = 0;
    }
    M2C_FIELD(temp_v0, s32 **, 0xC) = NULL;
}

void func_001220b8(void) {
    D_004F6EB8 -= 8;
}

void func_001220d0(void) {
    func_00270b40();
}

void func_001220e8(void) {
    func_00148e60();
    func_001478e0();
    func_0013f2c0();
    func_00127340();
    func_0014f868();
    func_00151b90();
    func_00132e38();
}

void func_00122768(s32 *arg0) {
    *arg0 = 0;
}

void func_00122bd8(void) {
    func_0011efa8(&D_004F6EC0, &D_004F6ED0, 0x50, 8);
}

void func_00123460(void *arg0) {
    s32 temp_v0;
    s32 temp_v1;

    temp_v0 = M2C_FIELD(arg0, s32 *, 0x388);
    temp_v1 = temp_v0 - 1;
    if (temp_v0 > 0) {
        M2C_FIELD(arg0, s32 *, 0x388) = temp_v1;
        M2C_FIELD(arg0, s32 *, 0) = (s32) M2C_FIELD(((temp_v1 * 4) + arg0), s32 *, 0x37C);
    }
}

void func_001248e8(void) {
    s32 temp_v0;

    temp_v0 = func_00123488();
    if (temp_v0 != 0) {
        func_001247e8(temp_v0);
    }
}

void func_00124ce0(void) {
    D_004F77E4 = D_002E27A0;
    func_00124c68();
}

void func_00124d28(void *arg0, void *arg1) {
    func_0026b9a8(M2C_FIELD(arg0, f32 *, 0) - M2C_FIELD(arg1, f32 *, 0), M2C_FIELD(arg0, f32 *, 8) - M2C_FIELD(arg1, f32 *, 8));
}

s32 func_001274c8(void *arg0) {
    func_00266f38(func_00266c08(2), M2C_FIELD(arg0, s32 *, 0x10));
    return 2;
}

void func_00128db0(void *arg0) {
    M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0) * 2) + D_00514F10), u16 *, 0x724) = (u16) M2C_FIELD(arg0, u16 *, 4);
}

void func_00128dd0(void) {

}

void func_00128dd8(void) {

}

void func_00128e90(f32 *arg0) {
    *arg0 = func_00176850();
}

void func_00128eb8(f32 *arg0) {
    *arg0 = D_002BBDFC;
}

void func_00128ec8(s32 *arg0) {
    *arg0 = func_001477c8(*arg0);
}

void func_00128ef8(void) {

}

void func_00128f00(void) {

}

void func_00128f08(void) {

}

void func_00128f60(f32 *arg0) {
    D_002BBE00 = *arg0;
}

void func_00128f70(s32 *arg0) {
    s32 var_a1;

    var_a1 = 0;
    if ((u32) D_002BBDE4 >= 2U) {
        var_a1 = D_002BBDE4 != 7;
    }
    *arg0 = var_a1;
}

void func_00128f98(s32 *arg0) {
    *arg0 = ((u32) D_002C5958 >> 0xD) & 1;
}

void func_00128fb0(s32 *arg0) {
    *arg0 = D_00304B78 & 7;
}

void func_00129330(void) {

}

void func_00129428(void *arg0) {
    M2C_FIELD(func_00130578(M2C_FIELD(arg0, s32 *, 0), M2C_FIELD(arg0, s32 *, 4), M2C_FIELD(arg0, f32 *, 8)), f32 *, 4) = (f32) M2C_FIELD(arg0, f32 *, 0xC);
}

void func_001294c0(s32 *arg0) {
    *arg0 = func_001230a0(*arg0);
}

void func_00129570(s32 *arg0) {
    *arg0 = func_00124218(*arg0);
}

void func_00129608(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0) = func_001349d0(M2C_FIELD(arg0, s32 *, 0), M2C_FIELD(arg0, s32 *, 4));
}

void func_00129638(void *arg0) {
    func_0014a380(M2C_FIELD(arg0, s32 *, 0), M2C_FIELD(arg0, s32 *, 4));
    M2C_FIELD(arg0, s32 *, 0) = 0;
}

void func_001296d8(void) {

}

void func_00129748(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0) = func_00148a40(M2C_FIELD(arg0, s32 *, 0), M2C_FIELD(arg0, s32 *, 4));
}

void func_00129778(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0) = func_0012ef30(M2C_FIELD(arg0, s32 *, 0), M2C_FIELD(arg0, s32 *, 4), M2C_FIELD(arg0, s32 *, 8), M2C_FIELD(arg0, f32 *, 0xC));
}

void func_001297f0(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0) = func_0014efe0(M2C_FIELD(arg0, s32 *, 0), M2C_FIELD(arg0, s32 *, 4));
}

void func_00129820(s32 *arg0) {
    *arg0 = func_0014ee88(*arg0);
}

void func_001298a8(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0) = func_00142b30(M2C_FIELD(arg0, s32 *, 0), M2C_FIELD(arg0, s32 *, 4));
}

void func_001298d8(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0) = func_00142c80(M2C_FIELD(arg0, s32 *, 0), M2C_FIELD(arg0, s32 *, 4));
}

void func_001299e8(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0) = func_00148b70(M2C_FIELD(arg0, s32 *, 0), M2C_FIELD(arg0, s32 *, 4), M2C_FIELD(arg0, s32 *, 8), M2C_FIELD(arg0, f32 *, 0xC));
}

void func_00129af8(void *arg0) {
    void *temp_a1;

    temp_a1 = M2C_FIELD(arg0, void **, 0);
    M2C_FIELD(temp_a1, s32 *, 0x1CC) = (s32) (M2C_FIELD(temp_a1, s32 *, 0x1CC) & ~M2C_FIELD(arg0, s32 *, 4));
}

void func_00129bb8(void *arg0) {
    void *temp_a2;

    temp_a2 = M2C_FIELD(arg0, void **, 0);
    M2C_FIELD(temp_a2, s32 *, 0x3A4) = (s32) (M2C_FIELD(temp_a2, s32 *, 0x3A4) | M2C_FIELD(arg0, s32 *, 4));
    M2C_FIELD(temp_a2, s32 *, 0x3A8) = (s32) (M2C_FIELD(temp_a2, s32 *, 0x3A8) | M2C_FIELD(arg0, s32 *, 8));
    M2C_FIELD(temp_a2, s32 *, 0x3AC) = (s32) (M2C_FIELD(temp_a2, s32 *, 0x3AC) | M2C_FIELD(arg0, s32 *, 0xC));
}

void func_00129bf0(void *arg0) {
    void *temp_a2;

    temp_a2 = M2C_FIELD(arg0, void **, 0);
    M2C_FIELD(temp_a2, s32 *, 0x3A4) = (s32) (M2C_FIELD(temp_a2, s32 *, 0x3A4) & ~M2C_FIELD(arg0, s32 *, 4));
    M2C_FIELD(temp_a2, s32 *, 0x3A8) = (s32) (M2C_FIELD(temp_a2, s32 *, 0x3A8) & ~M2C_FIELD(arg0, s32 *, 8));
    M2C_FIELD(temp_a2, s32 *, 0x3AC) = (s32) (M2C_FIELD(temp_a2, s32 *, 0x3AC) & ~M2C_FIELD(arg0, s32 *, 0xC));
}

void func_00129d88(void **arg0) {
    *arg0 = (void *) M2C_FIELD(M2C_FIELD(*arg0, void **, 0x130), u8 *, 0x5A);
}

void func_00129ea8(s32 *arg0) {
    *arg0 = func_001233e8(*arg0);
}

void func_0012a0c8(s32 *arg0) {
    *arg0 = func_00131b08(*arg0);
}

void func_0012a0f8(void **arg0) {
    *arg0 = (void *) M2C_FIELD(M2C_FIELD(*arg0, void **, 0x130), u16 *, 0x4E);
}

void func_0012a110(void *arg0) {
    M2C_FIELD(M2C_FIELD(M2C_FIELD(arg0, void **, 0), void **, 0x6C), u8 *, 0xBD) = (u8) M2C_FIELD(arg0, u8 *, 4);
}

void func_0012a128(s32 *arg0) {
    *arg0 = func_00157528(*arg0);
}

void func_0012a1e8(void **arg0) {
    *arg0 = (void *) M2C_FIELD(*arg0, u8 *, 0x39E);
}

void func_0012a228(void **arg0) {
    *arg0 = (void *) M2C_FIELD(M2C_FIELD(*arg0, void **, 0x130), u8 *, 0x58);
}

void func_0012a358(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0) = func_00148968(M2C_FIELD(arg0, s32 *, 0), M2C_FIELD(arg0, s32 *, 4), M2C_FIELD(arg0, s32 *, 8));
}

void func_0012a400(s32 *arg0) {
    if (((u32) D_002C5958 >> 0xD) & 1) {
        D_00F20000(6, *arg0);
    }
}

void func_0012a448(s32 *arg0) {
    s32 var_s1;

    var_s1 = 0;
    if (func_0014f5c8(*arg0) == 0) {
        var_s1 = func_0014f600(*arg0) == 0;
    }
    *arg0 = var_s1;
}

void func_0012a4f8(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0) = func_00147c98(M2C_FIELD(arg0, s32 *, 0), M2C_FIELD(arg0, s32 *, 4), M2C_FIELD(arg0, s32 *, 8));
}

void func_0012a750(s32 *arg0) {
    s32 temp_v0;

    temp_v0 = *arg0;
    if (temp_v0 != 0) {
        func_00176310(temp_v0);
    }
    *arg0 = 0;
}

void func_0012a830(void *arg0) {
    void *temp_v0;

    temp_v0 = func_0014a4a8(M2C_FIELD(arg0, void **, 0), M2C_FIELD(arg0, s32 *, 4), M2C_FIELD(arg0, s32 *, 8));
    M2C_FIELD(arg0, void **, 0) = temp_v0;
    M2C_FIELD(temp_v0, s32 *, 0xA0) = (s32) D_00514F10;
}

void func_0012a870(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0) = func_001354b8(M2C_FIELD(arg0, s32 *, 0), M2C_FIELD(arg0, s32 *, 4));
}

void func_0012a9b8(void **arg0) {
    *arg0 = M2C_FIELD(M2C_FIELD(*arg0, void **, 0x2C), void **, 0x6C);
}

void func_0012ab80(s32 *arg0) {
    *arg0 = func_001389c0(*arg0);
}

void func_0012abb0(s32 *arg0) {
    *arg0 = func_001389e8(*arg0);
}

void func_0012ac60(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0) = func_00137330(M2C_FIELD(arg0, s32 *, 0), M2C_FIELD(arg0, s32 *, 4), M2C_FIELD(arg0, s32 *, 8));
}

void func_0012acd8(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0) = func_0013a670(M2C_FIELD(arg0, s32 *, 0), M2C_FIELD(arg0, s32 *, 4), M2C_FIELD(arg0, f32 *, 8), M2C_FIELD(arg0, f32 *, 0xC));
}

void func_0012ad78(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0) = func_001226f0(M2C_FIELD(arg0, s32 *, 0), M2C_FIELD(arg0, s32 *, 4) | 8, M2C_FIELD(arg0, s32 *, 8));
}

void func_0012b0c0(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0) = (s32) (func_00142480(M2C_FIELD(arg0, s32 *, 0), M2C_FIELD(arg0, s32 *, 4), M2C_FIELD(arg0, s32 *, 8), M2C_FIELD(arg0, s32 *, 0xC)) + 1);
}

void func_0012b100(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0) = func_0015bd78(M2C_FIELD(arg0, s32 *, 0), M2C_FIELD(arg0, s32 *, 4), 0);
}

void func_0012b1a8(s32 *arg0) {
    if (*arg0 != 0) {
        D_002E31A8 |= 4;
        return;
    }
    D_002E31A8 &= ~4;
}

void func_0012b1e8(M2C_UNK **arg0) {
    *arg0 = &D_002E2F28;
}

void func_0012b1f8(M2C_UNK **arg0) {
    *arg0 = &D_002E2F34;
}

void func_0012b2b0(s32 *arg0) {
    *arg0 = D_0029B418;
}

void func_0012b408(s32 *arg0) {
    func_001ef7b0(*arg0);
    *arg0 = func_001ef7a0();
}

void func_0012b440(void) {

}

void func_0012b448(void) {

}

void func_0012b530(void) {
    D_002BBE04 = 0;
}

void func_0012b680(s32 *arg0) {
    *arg0 = D_00350D7C;
}

void func_0012ba30(s32 arg0) {
    func_0013cec8(arg0 + 8);
}

s32 func_0012eaf8(void *arg0) {
    return M2C_FIELD(M2C_FIELD(arg0, void **, 0x130), s32 *, 4) & 0x1000;
}

s32 func_0012ffd0(void *arg0) {
    s32 var_v0;
    void *temp_v1;
    void *temp_v1_2;

    temp_v1 = M2C_FIELD(arg0, void **, 0x398);
    var_v0 = 0;
    if (temp_v1 != NULL) {
        temp_v1_2 = M2C_FIELD(temp_v1, void **, 0x3A0);
        if (temp_v1_2 != NULL) {
            var_v0 = M2C_FIELD(temp_v1_2, u8 *, 6) == 3;
        }
    }
    return var_v0;
}
#include "data/bss_0051_mixed.h"

/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
#include "data/bss_0064.h"

M2C_UNK func_00109268();
M2C_UNK func_0011d768(M2C_UNK);
M2C_UNK func_001efb78(M2C_UNK);
M2C_UNK func_001f36b8(void *);
M2C_UNK func_001f3758(s32);
M2C_UNK func_001f9010(M2C_UNK);
M2C_UNK func_001f9438(s32, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK);
M2C_UNK func_001f94f0(s32, M2C_UNK, M2C_UNK, M2C_UNK, s32, M2C_UNK, M2C_UNK);
M2C_UNK func_001fade0(void *, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, s32);
M2C_UNK func_00205938(void *, M2C_UNK);
M2C_UNK func_00206f78(s32);
M2C_UNK func_00207210(M2C_UNK);
M2C_UNK func_002072e0(M2C_UNK);
M2C_UNK func_00207bb0(s32, M2C_UNK);
M2C_UNK func_0020ab88(s32);
M2C_UNK func_0020bd18(s32, M2C_UNK);
M2C_UNK func_0021af38(s32);
M2C_UNK func_0021b800(s32);
M2C_UNK func_0021b820();
M2C_UNK func_0021c780(s32, M2C_UNK, M2C_UNK);
M2C_UNK func_0021cb00(s32, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK);
M2C_UNK func_0021ccd0(s32, M2C_UNK);
extern M2C_UNK D_003F61E0;
extern M2C_UNK D_003F70E8;
extern f32 D_002BBDFC;
extern f32 D_006469B8[]; /* src/data/bss_0064.c: s32 D_006469B8[0x6] */
extern s32 D_003F34C8;
extern s32 D_003F34D4;
extern s32 D_003F34FC;
extern s32 D_00643660;
s32 D_006436C8 ALIGNED(8);
extern s32 D_00643734;
extern s32 D_00643740;
extern s32 D_00646990;
extern void *D_00425BC8;
extern void *D_00643428; /* src/data/bss_0064.c: s32 D_00643428 */
s32 func_001efc10(M2C_UNK);
s32 func_001f42b8();
s32 func_001f4390();
s32 func_001f4400();
s32 func_001fe570(s32);
void func_00205e30(s32, s32);
void func_00206130(s32, s32, s32, s32, s32, s32);
void func_00207830(s32, s32, s32, s32, s32, s32, s32);
void func_0020ca30(s32, s32, s32, s32);

void func_002202b8(s32 arg0) {
    func_0021b820();
    func_0021ccd0(arg0, 2);
    func_0021af38(arg0);
}

void func_002202f0(s32 arg0) {
    func_0021b820();
    func_0021c780(arg0, 0x10, 0x48);
    func_0021cb00(arg0, 0x118, 0x6C, 9, 0x1E);
}

void func_002207f0(s32 arg0) {
    func_0021b800(arg0 + 8);
}

void func_00220808(s32 arg0) {
    func_0021b800(*(M2C_UNK *)((s8 *)(s8 *)&D_003F61E0 + ((arg0 / 3) * 4)) + 8);
}

void func_00220848(s32 arg0) {
    if ((func_001f42b8() != 0) && (M2C_FIELD(D_00425BC8, s32 *, 8) & 0x4000)) {
        func_001f3758(M2C_FIELD(D_00643428, s32 *, 0x10));
        func_0011d768(3);
    }
    func_0021b820();
    func_0021ccd0(arg0, 3);
    func_0021af38(arg0);
}

void func_00221098(void) {
    func_002072e0(3);
}

void func_00221390(s32 arg0) {
    func_0021b800(arg0 + 0x30);
}

void func_00221648(void) {
    func_00207210(0);
}

void func_00221980(void) {
    func_00207210(1);
}

void func_00221be0(void) {
    func_00207210(2);
}

void func_00221d68(void) {
    func_00207210(3);
}

void func_00221ef0(void) {
    func_00207210(4);
}

void func_00222078(void) {
    func_00207210(5);
}

void func_00222230(void) {
    func_00207210(6);
}

void func_002223e8(void) {
    func_00207210(7);
}

void func_00222658(void) {
    func_00207210(8);
}

void func_002228f0(s32 arg0) {
    if ((func_001f42b8() != 0) && (M2C_FIELD(D_00425BC8, s32 *, 8) & 0x4000)) {
        func_001f3758(D_00643660);
        func_0011d768(3);
    }
    func_0021b820();
    func_0021ccd0(arg0, 4);
    func_0021af38(arg0);
}

void func_00222958(s32 arg0) {
    func_0021b820();
    func_0021c780(arg0, 0x10, 0x48);
    func_0021cb00(arg0, 0x118, 0x6C, 9, 0x1E);
}

void func_00222e78(void *arg0) {
    func_00206f78(M2C_FIELD(arg0, s32 *, 0x24));
}

void func_002231e0(s32 arg0) {
    func_0021b820();
    func_0021ccd0(arg0, 0xC);
    func_0021af38(arg0);
}

void func_00223218(s32 arg0) {
    func_0021b820();
    func_0021c780(arg0, 0x10, 0x48);
    func_0021cb00(arg0, 0x118, 0x6C, 9, 0x1E);
}

void func_00223668(s32 arg0) {
    if ((func_001f42b8() != 0) && (M2C_FIELD(D_00425BC8, s32 *, 8) & 0x4000)) {
        func_001f3758(D_006436C8);
        func_0011d768(3);
    }
    func_0021b820();
    func_0021ccd0(arg0, 0xD);
    func_0021af38(arg0);
}

void func_00223920(void) {
    func_002072e0(4);
}

void func_00223938(s32 arg0) {
    D_006436C8 = arg0;
}

void func_00223d98(s32 arg0) {
    func_001f9010(0x17);
    func_001f9438(arg0, 0, 0xAE, 0xC, 0x191, 0x11, 0x8078C850);
}

void func_00223de0(void) {
    D_003F34FC += 1;
    D_003F34C8 -= 1;
}

void func_002245c8(s32 arg0) {
    func_001f9010(0x17);
    func_001f9438(arg0, 0, 0xAE, 0xC, 0x188, 0x11, 0x8078C850);
}

void func_00224610(s32 arg0) {
    if (func_001f42b8() != 0) {
        if (M2C_FIELD(D_00425BC8, s32 *, 8) & 0x4000) {
            func_001f3758(D_00643740);
            func_0011d768(3);
        } else {
            func_0020bd18(arg0, 8);
            if (func_001fe570(arg0) != 0) {
                func_001f3758(D_00643740);
            }
        }
    }
    func_00207bb0(arg0, 0x18F);
}

void func_002252e8(s32 arg0) {
    func_001f9010(0x17);
    func_001f9438(arg0, 0, 0xAE, 0xC, 0x187, 0x11, 0x8078C850);
}

void func_00225988(void) {
    D_003F34D4 += 1;
    D_00643734 += 1;
    D_003F34C8 -= 1;
}

void func_00228078(s32 arg0) {
    func_001f9010(0x17);
    func_001f9438(arg0, 0, 0xAE, 0xC, 0x173, 0x11, 0x8078C850);
}

void func_002298e0(s32 arg0) {
    func_001f9010(0x17);
    func_001f9438(arg0, 0, 0xAE, 0xC, 0x1A6, 0x11, 0x80399BFF);
}

void func_00229928(s32 arg0) {
    if (func_001f42b8() != 0) {
        if (M2C_FIELD(D_00425BC8, s32 *, 8) & 0x4000) {
            func_001f3758(D_00646990);
            func_0011d768(3);
        } else {
            func_0020bd18(arg0, 8);
            if (func_001fe570(arg0) != 0) {
                func_001f3758(D_00646990);
            }
        }
    }
    func_00207bb0(arg0, 0x1A9);
}

void func_00229e78(s32 arg0) {
    func_001f9010(0x17);
    func_001f9438(arg0, 0, 0xAE, 0xC, 0x1A5, 0x11, 0x80399BFF);
}

void func_0022b3c8(s32 arg0) {
    func_001f9010(0x17);
    func_001f9438(arg0, 0, 0xAE, 0xC, 0x199, 0x11, 0x80399BFF);
}

void func_0022b630(void) {
    func_00109268();
}

void func_0022b9a8(s32 arg0) {
    func_00207830(arg0, 4, 2, 0, 0, 0x7A, 0x192);
}

void func_0022b9d8(s32 arg0) {
    func_00205e30(arg0, (s32) &D_003F70E8);
    func_00206130(arg0, 0, 0x3E, 0x200, 2, 0x80399BFF);
    func_0020ca30(arg0, 0, 0x80221F8F, 0x806360E1);
}

void func_0022bac0(void *arg0) {
    u32 temp_a0;

    temp_a0 = M2C_FIELD(arg0, u32 *, 0x90);
    func_0020ab88((s32) (temp_a0 + (temp_a0 >> 0x1F)) >> 1);
    func_00205938(arg0, 0x64000000);
}

void func_0022bb00(void) {
    if ((func_001f4390() != 0) && (M2C_FIELD(D_00425BC8, s32 *, 8) & 8)) {
        func_0011d768(4);
    }
}

void func_0022d140(void *arg0) {
    f32 temp_f0;

    if ((func_001f4400() != 0) && (D_006469B8[1] != 0.0f)) {
        temp_f0 = D_006469B8[1] - D_002BBDFC;
        D_006469B8[1] = temp_f0;
        if (temp_f0 <= 0.0f) {
            func_001f36b8(arg0);
        }
    }
    func_001fade0(arg0, 0, 0, 0x1D, 0x12, M2C_FIELD(arg0, s32 *, 0x24));
}

void func_0022d1b8(void *arg0) {
    f32 temp_f0;

    if ((func_001f4400() != 0) && (D_006469B8[2] != 0.0f)) {
        temp_f0 = D_006469B8[2] - D_002BBDFC;
        D_006469B8[2] = temp_f0;
        if (temp_f0 <= 0.0f) {
            func_001f36b8(arg0);
        }
    }
    func_001fade0(arg0, 0, 0, 0xE, 0x12, M2C_FIELD(arg0, s32 *, 0x24));
}

void func_0022d230(void *arg0) {
    f32 temp_f0;

    if ((func_001f4400() != 0) && (D_006469B8[3] != 0.0f)) {
        temp_f0 = D_006469B8[3] - D_002BBDFC;
        D_006469B8[3] = temp_f0;
        if (temp_f0 <= 0.0f) {
            func_001f36b8(arg0);
        }
    }
    func_001fade0(arg0, 0, 0, 0x22, 0x12, M2C_FIELD(arg0, s32 *, 0x24));
}

void func_0022d2a8(void *arg0) {
    f32 temp_f0;

    if ((func_001f4400() != 0) && (D_006469B8[4] != 0.0f)) {
        temp_f0 = D_006469B8[4] - D_002BBDFC;
        D_006469B8[4] = temp_f0;
        if (temp_f0 <= 0.0f) {
            func_001f36b8(arg0);
        }
    }
    func_001fade0(arg0, 0, 0, 0x20, 0x12, M2C_FIELD(arg0, s32 *, 0x24));
}

void func_0022d320(void *arg0) {
    f32 temp_f0;

    if ((func_001f4400() != 0) && (D_006469B8[5] != 0.0f)) {
        temp_f0 = D_006469B8[5] - D_002BBDFC;
        D_006469B8[5] = temp_f0;
        if (temp_f0 <= 0.0f) {
            func_001f36b8(arg0);
        }
    }
    func_001fade0(arg0, 0, 0, 0x12, 0x12, M2C_FIELD(arg0, s32 *, 0x24));
}

void func_0022e2c0(s32 arg0) {
    func_001f94f0(arg0, 2, 0x100, 0x90, func_001efc10(0x1D8), 0x12, 0x801E4696);
}

void func_0022eaa0(void) {
    func_001efb78(0);
}

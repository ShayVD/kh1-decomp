/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
#include "data/bss_0049.h"

M2C_UNK FlushCache(M2C_UNK);
M2C_UNK func_00100360();
M2C_UNK func_00101680();
M2C_UNK func_00106b18(M2C_UNK *);
M2C_UNK func_001091f8(void *, void *);
M2C_UNK func_0010c438(M2C_UNK, s32);
M2C_UNK func_0010e4f0(void *);
M2C_UNK func_0010e610(s32, s32, M2C_UNK);
M2C_UNK func_0011c898(M2C_UNK);
M2C_UNK func_0011ef10(M2C_UNK, M2C_UNK *);
M2C_UNK func_0011f130(M2C_UNK *, M2C_UNK);
M2C_UNK func_00121ee0(s32);
M2C_UNK func_00122130();
M2C_UNK func_0015f018();
M2C_UNK func_001c06f8();
M2C_UNK func_00236f18();
M2C_UNK func_0024b990();
M2C_UNK func_002660c0(void *, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK);
M2C_UNK func_002672f8(M2C_UNK *, void *, s32);
M2C_UNK func_00267328(s32, s32, void *);
M2C_UNK func_00267620(void *);
M2C_UNK func_002676c0(void *, void *, f32);
M2C_UNK func_00267768(void *, void *, f32);
M2C_UNK func_00267810(void *, void *, f32);
M2C_UNK func_00267930(s32, M2C_UNK *, M2C_UNK *, M2C_UNK *);
M2C_UNK iReferSemaStatus(s32, void *);
M2C_UNK iSignalSema(s32);
M2C_UNK sceGsExecLoadImage(M2C_UNK *, s32);
M2C_UNK sceGsExecStoreImage(void *, M2C_UNK *);
M2C_UNK sceGsSetDefLoadImage(M2C_UNK *, s16, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK);
M2C_UNK sceGsSyncPath(M2C_UNK, M2C_UNK);
#include "data/pieces/D_002B7590.h"
#include "data/pieces/D_002BBAA0.h"
extern M2C_UNK D_002BBC20;
extern M2C_UNK D_002BBCF0;
extern M2C_UNK D_002BBD30;
#include "data/pieces/D_002BBD48.h"
#include "data/pieces/D_002BBD90.h"
extern M2C_UNK D_002BC210;
#include "data/pieces/D_002BC720.h"
extern M2C_UNK D_004945E0; /* src/data/bss_0049.c: u8 D_004945E0[0x10] */
extern M2C_UNK D_00F20000;
extern M2C_UNK func_00101048;
extern M2C_UNK func_0010a120;
extern M2C_UNK func_0010a248;
extern f32 D_002BBDFC;
#include "data/pieces/D_002A6238.h"
extern s32 D_002A6B84;
extern s32 D_002B6770;
extern s32 D_00472150[];
#include "data/pieces/D_0048C630.h"
#include "data/pieces/D_0048C690.h"
extern s32 D_00495180;
extern s32 D_00495254;
extern u32 D_004D8EC0[]; /* src/data/bss_004D.c: s32 D_004D8EC0[0xc] */
#include "data/pieces/D_002E2700.h"
#include "data/pieces/D_002E2740.h"
#include "data/pieces/D_002BBDE0.h"
#include "data/pieces/D_002BC070.h"
extern volatile s32 D_00494410[]; /* src/data/bss_0049.c: s32 D_00494410[2] */
extern volatile s32 D_00495160;
extern volatile s32 D_00495164;
extern volatile s32 D_00495258;
#include "data/pieces/D_002BC140.h"
#include "data/pieces/D_002BC144.h"
f32 func_00266f38(s32, s32);
f32 iFlushCache(M2C_UNK);
s32 func_0010a0d8(void);
s32 func_0010ef90(s32, s32);
s32 func_0011ab60(s32, s32);
s32 func_00121e28(M2C_UNK, s32 *);
s32 func_00142730(s32, s32);
void func_00108900(s32, s32, s32, s32);
void func_00108970(s32, s32, s32);

void func_001012b8(void) {
    func_0011ef10(0x2E630, &func_00101048);
}

void func_001017b8(void) {
    func_0011c898(0);
    D_00494410[1] = -1;
    D_00494410[0] = -1;
    func_00101680();
}

void func_00101f10(void) {
    func_0011f130(&D_004945E0, 0);
}

void func_00103b68(s32 arg0, s32 arg1, s32 arg2, s32 arg3, void *arg4) {
    s32 sp[28];
    func_00267620(sp);
    func_00267768(sp, sp, M2C_FIELD(arg4, f32 *, 0));
    func_00267810(sp, sp, M2C_FIELD(arg4, f32 *, 4));
    func_002676c0(sp, sp, M2C_FIELD(arg4, f32 *, 8));
    func_002672f8(&M2C_FIELD(sp, M2C_UNK *, 0x40), sp, arg2);
    func_002672f8(&M2C_FIELD(sp, M2C_UNK *, 0x50), sp, arg3);
    func_002672f8(&M2C_FIELD(sp, M2C_UNK *, 0x60), sp, arg1);
    func_00267930(arg0, &M2C_FIELD(sp, M2C_UNK *, 0x60), &M2C_FIELD(sp, M2C_UNK *, 0x40), &M2C_FIELD(sp, M2C_UNK *, 0x50));
}

s32 func_001059d0(s32 arg0) {
    s32 sp[4];
    s32 temp_a3;
    s32 temp_v0;

    temp_v0 = func_00142730(arg0, (s32) sp);
    temp_a3 = temp_v0 * 0x14;
    if (M2C_FIELD(sp, M2C_UNK *, 0x0) == -1) {
        return (s32) M2C_FIELD((((s32)D_002A6238) + temp_a3), u8 *, 0xB);
    }
    return func_0011ab60(M2C_FIELD(sp, M2C_UNK *, 0x0), temp_v0);
}

void func_00106438(s32 arg0) {
    void *temp_a0;
    void *temp_a0_2;

    temp_a0 = arg0 + 0x10;
    temp_a0_2 = temp_a0 + M2C_FIELD(temp_a0, u16 *, 0xC);
    func_001091f8(temp_a0_2, temp_a0_2 + M2C_FIELD(temp_a0, s32 *, 8));
}

s32 func_00106708(void *arg0) {
    f32 temp_f2;
    s32 temp_f1;

    temp_f2 = M2C_FIELD(arg0, f32 *, 0x10) + D_002BBDFC;
    M2C_FIELD(arg0, f32 *, 0x10) = temp_f2;
    if (M2C_FIELD(arg0, f32 *, 0x18) <= temp_f2) {
        D_002BC070[0] = 0x80;
        D_002BC070[3] = 0x80;
        D_002BC070[2] = 0x80;
        D_002BC070[1] = 0x80;
        return 4;
    }
    temp_f1 = (s32) (M2C_FIELD(arg0, f32 *, 0x14) * temp_f2);
    D_002BC070[0] = temp_f1;
    D_002BC070[3] = temp_f1;
    D_002BC070[2] = temp_f1;
    D_002BC070[1] = temp_f1;
    return 0;
}

s32 func_00106810(void *arg0) {
    f32 temp_f2;
    s32 temp_f1;

    temp_f2 = M2C_FIELD(arg0, f32 *, 0x10) - D_002BBDFC;
    M2C_FIELD(arg0, f32 *, 0x10) = temp_f2;
    if (temp_f2 <= 0.0f) {
        D_002BC070[0] = 0;
        D_002BC070[3] = 0;
        D_002BC070[2] = 0;
        D_002BC070[1] = 0;
        return 4;
    }
    temp_f1 = (s32) (M2C_FIELD(arg0, f32 *, 0x14) * temp_f2);
    D_002BC070[0] = temp_f1;
    D_002BC070[3] = temp_f1;
    D_002BC070[2] = temp_f1;
    D_002BC070[1] = temp_f1;
    return 0;
}

s32 func_00106b98(void *arg0) {
    iFlushCache(0);
    func_00266f38(D_002A6B84, M2C_FIELD(arg0, s32 *, 0x10));
    return 2;
}

void func_00108a60(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 temp_a1;
    s32 var_s3;
    void *var_s0;

    M2C_FIELD(arg2, s32 *, 0x20) = (s32) D_0048C630[8];
    var_s0 = arg2 + 0x5C;
    M2C_FIELD(arg2, s32 *, 0x24) = (s32) D_0048C630[9];
    M2C_FIELD(arg2, s32 *, 0x28) = (s32) D_0048C630[10];
    M2C_FIELD(arg2, s32 *, 0x2C) = (s32) D_0048C630[11];
    M2C_FIELD(arg2, s32 *, 0x80) = (s32) D_0048C690[8];
    M2C_FIELD(arg2, s32 *, 0x84) = (s32) D_0048C690[9];
    M2C_FIELD(arg2, s32 *, 0x88) = (s32) D_0048C690[10];
    M2C_FIELD(arg2, s32 *, 0x8C) = (s32) D_0048C690[11];
    func_00108900(arg2, arg0, arg3, arg4);
    var_s3 = 0;
    do {
        temp_a1 = var_s3;
        var_s3 += 1;
        func_00108970(arg2, temp_a1, arg1);
        M2C_FIELD(var_s0, s32 *, -0xC) = (s32) D_00472150[0];
        M2C_FIELD(var_s0, s32 *, -8) = (s32) D_00472150[1];
        M2C_FIELD(var_s0, s32 *, -4) = (s32) D_00472150[2];
        M2C_FIELD(var_s0, s32 *, 0) = (s32) D_00472150[3];
        var_s0 += 0x60;
    } while (var_s3 < 2);
}

void func_00109180(s32 arg0, s16 arg1) {
    sceGsSetDefLoadImage(&D_002BC210, arg1, 0, 0, 0, 0, 8, 2);
    FlushCache(0);
    sceGsSyncPath(0, 0);
    sceGsExecLoadImage(&D_002BC210, arg0);
}

s32 func_00109360(void) {
    func_0011f130((M2C_UNK *)&D_002BC720, 0);
    return 0;
}

void func_00109558(s32 arg0) {
    D_00495164 = arg0;
    D_00495160 = 2;
    func_0010a0d8();
}

void func_001095b0(void) {
    func_00122130();
    func_0015f018();
    func_00100360();
    func_001c06f8();
    func_00236f18();
    func_0024b990();
    (*(volatile s8 **)&D_002BC140) = ((volatile M2C_UNK *)&D_002E2700);
    (*(volatile s8 **)&D_002BC144) = ((volatile M2C_UNK *)&D_002E2740);
    D_002BBDE0 = 3;
    D_00495160 = 0;
}

s32 func_00109d98(void) {
    s32 sp[28];
    func_002660c0(sp, 0x1A00, 8, 1, 0, 0, 0x200, 0x180);
    FlushCache(0);
    sceGsSyncPath(0, 0);
    sceGsExecStoreImage(sp, &D_00F20000);
    return 4;
}

void func_0010a320(void) {
    D_00495180 = 0;
    if (D_002B6770 != 0) {
        func_0011ef10(0x2E630, &func_0010a248);
        return;
    }
    func_0011ef10(0x2E630, &func_0010a120);
}

void func_0010b208(s32 arg0, s32 arg1, void *arg2) {
    s32 sp[16];
    func_00267620(sp);
    M2C_FIELD(sp, f32 *, 0x0) = M2C_FIELD(arg2, f32 *, 0);
    M2C_FIELD(sp, f32 *, 0x14) = M2C_FIELD(arg2, f32 *, 4);
    M2C_FIELD(sp, f32 *, 0x28) = M2C_FIELD(arg2, f32 *, 8);
    func_00267328(arg0, arg1, sp);
}

s32 func_0010c010(void) {
    func_0011f130((M2C_UNK *)&D_002B7590, 0);
    D_00495254 = 0;
    return 0;
}

void func_0010c378(void) {
    s32 sp[8];
    iReferSemaStatus(D_00495258, sp);
    if (M2C_FIELD(sp, M2C_UNK *, 0xC) != 0) {
        iSignalSema(D_00495258);
    }
}

void func_0010e750(void) {
    s32 sp[8];
    M2C_FIELD(sp, s32 *, 0x0) = func_00121e28(0x40, sp);
    M2C_FIELD(sp, s32 *, 0x4) = func_00121e28(0x40, &M2C_FIELD(sp, s32 *, 0x4));
    M2C_FIELD(sp, s32 *, 0x8) = func_00121e28(0x40, &M2C_FIELD(sp, s32 *, 0x8));
    M2C_FIELD(sp, s32 *, 0xC) = func_00121e28(0x40, &M2C_FIELD(sp, s32 *, 0xC));
    M2C_FIELD(sp, s32 *, 0x10) = func_00121e28(0x40, &M2C_FIELD(sp, s32 *, 0x10));
    M2C_FIELD(sp, s32 *, 0x14) = func_00121e28(0x40, &M2C_FIELD(sp, s32 *, 0x14));
    M2C_FIELD(sp, s32 *, 0x18) = func_00121e28(0x40, &M2C_FIELD(sp, s32 *, 0x18));
    M2C_FIELD(sp, s32 *, 0x1C) = func_00121e28(0x40, &M2C_FIELD(sp, s32 *, 0x1C));
    func_0010e610(M2C_FIELD(sp, s32 *, 0x0), M2C_FIELD(sp, s32 *, 0x4), 0);
    func_0010e610(M2C_FIELD(sp, s32 *, 0x8), M2C_FIELD(sp, s32 *, 0xC), 1);
    func_0010e610(M2C_FIELD(sp, s32 *, 0x10), M2C_FIELD(sp, s32 *, 0x14), 2);
    func_0010e610(M2C_FIELD(sp, s32 *, 0x18), M2C_FIELD(sp, s32 *, 0x1C), 3);
    func_0010c438(0x3FEC, M2C_FIELD(sp, s32 *, 0x0));
    func_0010c438(0x3FED, M2C_FIELD(sp, s32 *, 0x4));
    func_0010c438(0x3FEE, M2C_FIELD(sp, s32 *, 0x8));
    func_0010c438(0x3FEF, M2C_FIELD(sp, s32 *, 0xC));
    func_0010c438(0x3FF0, M2C_FIELD(sp, s32 *, 0x10));
    func_0010c438(0x3FF1, M2C_FIELD(sp, s32 *, 0x14));
    func_0010c438(0x3FF2, M2C_FIELD(sp, s32 *, 0x18));
    func_0010c438(0x3FF3, M2C_FIELD(sp, s32 *, 0x1C));
    sceGsSyncPath(0, 0);
    func_00121ee0(M2C_FIELD(sp, s32 *, 0x0));
    func_00121ee0(M2C_FIELD(sp, s32 *, 0x4));
    func_00121ee0(M2C_FIELD(sp, s32 *, 0x8));
    func_00121ee0(M2C_FIELD(sp, s32 *, 0xC));
    func_00121ee0(M2C_FIELD(sp, s32 *, 0x10));
    func_00121ee0(M2C_FIELD(sp, s32 *, 0x14));
    func_00121ee0(M2C_FIELD(sp, s32 *, 0x18));
    func_00121ee0(M2C_FIELD(sp, s32 *, 0x1C));
}

void func_0010ea00(void *arg0) {
    func_00106b18((M2C_UNK *)&D_002BBAA0);
    M2C_FIELD(arg0, s8 *, 0x11) = 1;
    func_0010e4f0(arg0);
}

void func_0010ea38(void *arg0) {
    func_00106b18((M2C_UNK *)&D_002BBAA0);
    M2C_FIELD(arg0, s32 *, 0x24) = 0;
    M2C_FIELD(arg0, s8 *, 0x11) = 0;
    func_0010e4f0(arg0);
}

s32 func_0010f098(s32 arg0) {
    s32 sp[4];
    return (func_0010ef90(arg0, (s32) sp) / 24) + 1;
}

void func_0010f580(void) {
    func_00106b18(&D_002BBC20);
    sceGsSyncPath(0, 0);
}

void func_0010f5a8(void) {
    func_00106b18(&D_002BBCF0);
    sceGsSyncPath(0, 0);
}

void func_0010f5d0(void) {
    func_00106b18(&D_002BBD30);
    sceGsSyncPath(0, 0);
}

void func_0010fbe0(s32 arg0) {
    s32 *temp_a0;
    s32 *temp_v1_2;
    s32 temp_v0;
    s32 temp_v1;
    s32 var_a3;
    void *var_a2;

    var_a2 = arg0 + 0x10;
    var_a3 = 0;
    do {
        temp_v1 = var_a3 * 4;
        temp_a0 = temp_v1 + (s8 *)&(*(M2C_UNK *)&D_002BBD48);
        temp_v1_2 = temp_v1 + (s8 *)(M2C_UNK *)&D_002BBD90;
        var_a3 += 1;
        *temp_a0 = arg0 + M2C_FIELD(var_a2, s32 *, 0);
        temp_v0 = M2C_FIELD(var_a2, s32 *, 4);
        var_a2 += 8;
        *temp_v1_2 = temp_v0;
    } while (var_a3 < 0x11);
}

void func_0010ffb8(s32 *arg0, s32 *arg1) {
    *arg0 = D_004D8EC0[6] & 0xFFF;
    *arg1 = ((u32) D_004D8EC0[6] >> 0xC) & 0x7FF;
}
#include "data/data_002A.h"
#include "data/data_002B.h"
#include "data/pieces/D_002BC1B0.h"
#include "data/pieces/D_002BBDFC.h"

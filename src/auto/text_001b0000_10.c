/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
#include "data/bss_0062.h"

M2C_UNK D_00F20000();
M2C_UNK FlushCache(M2C_UNK);
M2C_UNK asin();
M2C_UNK func_0010fe80();
M2C_UNK func_0010fe90();
M2C_UNK func_00112fa0();
M2C_UNK func_001bb880(M2C_UNK);
M2C_UNK func_001bbbd0(void *, s32);
M2C_UNK func_001bbce0();
M2C_UNK func_001bd470();
M2C_UNK func_001be670(M2C_UNK);
M2C_UNK func_001be820(M2C_UNK *, M2C_UNK);
M2C_UNK func_001c0da0(s32, M2C_UNK, void *);
M2C_UNK func_001c0e80(s32, M2C_UNK, void *);
M2C_UNK func_002672f8(M2C_UNK *, void *, s32);
M2C_UNK func_00267328(s32, s32, void *);
M2C_UNK func_00267620(void *);
M2C_UNK func_002676c0(void *, void *, f32);
M2C_UNK func_00267768(void *, void *, f32);
M2C_UNK func_00267810(void *, void *, f32);
M2C_UNK func_00267930(s32, M2C_UNK *, M2C_UNK *, M2C_UNK *);
M2C_UNK memset(s32, M2C_UNK, M2C_UNK);
extern M2C_UNK D_00621220; /* src/data/bss_0062.c: Lt2 D_00621220 */
extern M2C_UNK D_00625648; /* src/data/bss_0062.c: s32 D_00625648[0x40] */
extern s32 D_003772D0;
extern s32 D_003772DC;
extern s32 D_00621210;
extern s32 D_00621300;
extern s32 D_00625640;
extern volatile M2C_UNK D_00623ED4;
extern volatile s32 D_00621308[]; /* src/data/bss_0062.c: s32 D_00621308[4] */
s32 func_001207f8(s32);
s32 func_001ba9d8(s32);
void func_001baaa8(s32);

void func_001b9bf8(void) {
    asin();
}

s32 func_001b9c10(void) {
    if (func_001207f8(D_00621210) != 0) {
        return 0;
    }
    FlushCache(0);
    FlushCache(2);
    D_00F20000();
    return 4;
}

void func_001ba708(s32 arg0) {
    D_003772D0 = arg0;
    if (arg0 != 0) {
        func_001be820(&D_00621220, 0x70);
        D_00621300 = 0;
        D_00621308[3] = 0;
        D_00621308[0] = 0;
        D_00621308[1] = 0;
        D_00621308[2] = 0;
        func_0010fe90();
        return;
    }
    func_0010fe80();
}

void func_001ba768(s32 arg0) {
    D_00621300 = arg0;
}

void func_001ba798(void) {
    D_003772D0 = 0;
    func_001be670(0);
}

void func_001ba7b8(void) {
    func_00112fa0();
}

s32 func_001ba7d0(void) {
    return D_003772DC;
}

void func_001ba930(s32 arg0, s8 arg1) {
    s32 sp[4];
    M2C_FIELD(sp, s8 *, 0x0) = arg1;
    func_001c0e80(arg0 + 0x2F0, 1, sp);
}

s8 func_001ba958(s32 arg0) {
    s32 sp[4];
    func_001c0da0(arg0 + 0x2F0, 1, sp);
    return M2C_FIELD(sp, M2C_UNK *, 0x0);
}

void func_001bbf38(s32 arg0, s32 arg1) {
    s32 sp[16];
    func_001bbce0();
    func_001bbbd0(sp, arg1);
    func_00267328(arg0, arg0, sp);
}

void func_001be320(s32 arg0) {
    if (arg0 >= D_00625640) {
        func_001baaa8(arg0 - D_00625640);
        return;
    }
    func_001baaa8(*(M2C_UNK *)((s8 *)(s8 *)&D_00625648 + (arg0 * 4)) | 0x80);
}

void func_001be370(s32 arg0) {
    if (arg0 >= D_00625640) {
        func_001baaa8(arg0 - D_00625640);
        return;
    }
    func_001baaa8(*(M2C_UNK *)((s8 *)(s8 *)&D_00625648 + (arg0 * 4)) | 0x80);
}

void func_001be3c0(s32 arg0) {
    s32 var_a1;
    u8 *var_a0;
    u8 *var_v1;
    u8 temp_v0;

    var_a0 = func_001ba9d8(arg0 - D_00625640) + 0x50;
    var_v1 = (s8 *)&D_00623ED4 + (arg0 * 0x60);
    var_a1 = 0x1F;
    do {
        temp_v0 = *var_v1;
        var_v1 += 1;
        var_a1 -= 1;
        *var_a0 = temp_v0;
        var_a0 += 1;
    } while (var_a1 >= 0);
}

void func_001be430(s32 arg0) {
    memset(func_001ba9d8(arg0 - D_00625640), 0, 0xF70);
    func_001bb880(0);
    func_001bd470();
}

void func_001be8a8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, void *arg4) {
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

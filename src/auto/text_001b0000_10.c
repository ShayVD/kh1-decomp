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
M2C_UNK func_001be670(M2C_UNK);
M2C_UNK func_001be820(M2C_UNK *, M2C_UNK);
#include "vm/script_vm.h"
extern M2C_UNK D_00621220; /* src/data/bss_0062.c: Lt2 D_00621220 */
extern s32 D_003772D0;
extern s32 D_003772DC;
extern s32 D_00621210;
extern s32 D_00621300;
extern volatile s32 D_00621308[]; /* src/data/bss_0062.c: s32 D_00621308[4] */
s32 func_001207f8(s32);

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
#include "data/data_0037.h"

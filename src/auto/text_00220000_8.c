/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
#include "data/bss_0064.h"

extern M2C_UNK D_003F6920;
extern M2C_UNK D_003F6E40;
extern s32 D_006436D4;
extern s32 D_00643734;
extern s32 D_00643740;
extern s32 D_006437C4;
extern s32 D_00646990;
extern void *D_00425BC8;
s32 func_0011d768(s32);
s32 func_001f31a8(s32, s32);
s32 func_001f42b8(s32);
s32 func_001fe570(s32);
s32 func_00207bb0(s32, s32);
s32 func_002246f8(s32);
s32 func_00229a10(s32);
s32 func_00233f40(s32, s32);
void func_001f3758(s32);
void func_001f3dc0(s32);
void func_001f3e48(s32, s32);
void func_0020bd18(s32, s32);
void func_0020be10(s32);
void func_00233f18(void);
void func_00233fb0(s32, s32);
void func_00233ff8(s32, s32);

s32 func_00224b38(s32 arg0) {
    s32 temp_v0;

    if (func_001f42b8(arg0) != 0) {
        if (func_00233f40(D_006436D4, 0) != 0) {
            func_00233fb0(D_006436D4, 0);
            func_0011d768(2);
            func_001f3758(arg0);
            func_0020be10(0x10);
            D_00643734 = 0;
            func_00233f18();
            temp_v0 = func_001f31a8((s32) &D_003F6920, 6);
            if (temp_v0 != 0) {
                func_001f3e48(temp_v0, arg0);
                func_001f3dc0(D_00643740);
            }
        } else if (M2C_FIELD(D_00425BC8, s32 *, 8) & 0x4000) {
            func_001f3758(D_00643740);
            func_0011d768(3);
        } else {
            func_0020bd18(arg0, 8);
            if (func_001fe570(arg0) != 0) {
                func_001f3758(D_00643740);
            }
        }
    }
    return func_00207bb0(arg0, 0x18B);
}

s32 func_00224ca8(s32 arg0) {
    if (func_001f42b8(arg0) != 0) {
        if (func_00233f40(D_006436D4, 0) != 0) {
            func_00233ff8(D_006436D4, 0);
            func_002246f8(arg0);
        } else if (M2C_FIELD(D_00425BC8, s32 *, 8) & 0x4000) {
            func_001f3758(D_00643740);
            func_0011d768(3);
        } else {
            func_0020bd18(arg0, 8);
            if (func_001fe570(arg0) != 0) {
                func_001f3758(D_00643740);
            }
        }
    }
    return func_00207bb0(arg0, 0x176);
}

s32 func_00224dc8(s32 arg0) {
    if (func_001f42b8(arg0) != 0) {
        if (func_00233f40(D_006436D4, 0) != 0) {
            func_00233ff8(D_006436D4, 0);
            func_002246f8(arg0);
        } else if (M2C_FIELD(D_00425BC8, s32 *, 8) & 0x4000) {
            func_001f3758(D_00643740);
            func_0011d768(3);
        } else {
            func_0020bd18(arg0, 8);
            if (func_001fe570(arg0) != 0) {
                func_001f3758(D_00643740);
            }
        }
    }
    return func_00207bb0(arg0, 0x17E);
}

s32 func_00225090(s32 arg0) {
    if (func_001f42b8(arg0) != 0) {
        if (func_00233f40(D_006436D4, 0) != 0) {
            func_00233ff8(D_006436D4, 0);
            func_002246f8(arg0);
        } else if (M2C_FIELD(D_00425BC8, s32 *, 8) & 0x4000) {
            func_001f3758(D_00643740);
            func_0011d768(3);
        } else {
            func_0020bd18(arg0, 8);
            if (func_001fe570(arg0) != 0) {
                func_001f3758(D_00643740);
            }
        }
    }
    return func_00207bb0(arg0, 0x18D);
}

s32 func_00229ad0(s32 arg0) {
    s32 temp_v0;

    if (func_001f42b8(arg0) != 0) {
        if (func_00233f40(D_006437C4, 0) != 0) {
            func_00233fb0(D_006437C4, 0);
            func_001f3758(arg0);
            func_0011d768(2);
            func_0020be10(0x10);
            func_00233f18();
            temp_v0 = func_001f31a8((s32) &D_003F6E40, 6);
            if (temp_v0 != 0) {
                func_001f3e48(temp_v0, arg0);
                func_001f3dc0(D_00646990);
            }
        } else if (M2C_FIELD(D_00425BC8, s32 *, 8) & 0x4000) {
            func_001f3758(D_00646990);
            func_0011d768(3);
        } else {
            func_0020bd18(arg0, 8);
            if (func_001fe570(arg0) != 0) {
                func_001f3758(D_00646990);
            }
        }
    }
    return func_00207bb0(arg0, 0x1A7);
}

s32 func_00229c38(s32 arg0) {
    if (func_001f42b8(arg0) != 0) {
        if (func_00233f40(D_006437C4, 0) != 0) {
            func_00233ff8(D_006437C4, 0);
            func_00229a10(arg0);
        } else if (M2C_FIELD(D_00425BC8, s32 *, 8) & 0x4000) {
            func_001f3758(D_00646990);
            func_0011d768(3);
        } else {
            func_0020bd18(arg0, 8);
            if (func_001fe570(arg0) != 0) {
                func_001f3758(D_00646990);
            }
        }
    }
    return func_00207bb0(arg0, 0x19C);
}

s32 func_00229d58(s32 arg0) {
    if (func_001f42b8(arg0) != 0) {
        if (func_00233f40(D_006437C4, 0) != 0) {
            func_00233ff8(D_006437C4, 0);
            func_00229a10(arg0);
        } else if (M2C_FIELD(D_00425BC8, s32 *, 8) & 0x4000) {
            func_001f3758(D_00646990);
            func_0011d768(3);
        } else {
            func_0020bd18(arg0, 8);
            if (func_001fe570(arg0) != 0) {
                func_001f3758(D_00646990);
            }
        }
    }
    return func_00207bb0(arg0, 0x1A8);
}
#include "data/bss_0064_mixed.h"

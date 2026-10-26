/* xl_limit.x: functions matched by hand (session 131b). */
#include "ovl.h"

extern s32 D_00F23200, D_00F23204, D_00F23208, D_002E26A0;
void func_0012cab8(s32);
void func_00131500(s32);
void func_00f21870(void); void func_00f217d0(void); void func_00f21428(void); void func_00f213d8(void);
void func_00f21d90(void); void func_00f21d70(void); void func_00f21cb8(void); void func_00f20ff0(void);
void func_00f20e10(void); void func_00f22d40(void);

s32 func_00f20000(u32 arg0, s32 arg1) {
    D_00F23204 = arg1;
    switch (arg0) {
    case 5: return D_00F23200;
    case 6: func_0012cab8(0); func_00131500(D_002E26A0); return 0;
    case 0: D_00F23208 = arg1; func_00f21870(); return 0;
    case 7: func_00f217d0(); return 0;
    case 1: D_00F23208 = arg1; func_00f21428(); return 0;
    case 8: func_00f213d8(); return 0;
    case 2: D_00F23208 = arg1; func_00f21d90(); return 0;
    case 9: func_00f21d70(); return 0;
    case 10: func_00f21cb8(); return 0;
    case 3: D_00F23208 = arg1; func_00f20ff0(); return 0;
    case 11: func_00f20e10(); return 0;
    case 4: D_00F23208 = arg1; func_00f22d40(); return 0;
    }
    return 0;
}

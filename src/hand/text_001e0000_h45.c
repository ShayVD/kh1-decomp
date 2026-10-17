#include "common.h"
extern s32 D_002C5BB8;
extern u8 D_003DBA68[];
extern s32 D_003DC478;
extern s32 D_003DC47C;
extern s32 D_003DC48C;
extern s32 D_003DC490;
extern s32 D_003F7A68;
extern u8 D_0062F6E0[];
extern u8 D_0062F760[];
extern u8 D_0062F790[];
void func_001e2810();
void func_001e2920();
void func_001e3178();
void func_001e31b0();
void func_001e3f00();
void func_0010bd90(void *, void (*)());
void func_0010e3f0(void *);
void func_0010ef70(void *, void *, void *);
void func_0010f520(void);
void func_0011d768(s32);
s32 func_0011ef10(s32, void (*)());
void func_00231980(void);

s32 func_001e31b8(void) {
    if (D_002C5BB8 & 2) {
        s32 *p = &D_003DC490;
        if (*p == 0) return 0;
        func_0011d768(3);
        if (D_003F7A68 != 0) {
            D_003DC478 = 0;
            func_0010bd90(D_0062F6E0, func_001e31b0);
            func_00231980();
            func_0011ef10(0xC350, func_001e3178);
            return 4;
        }
        if (D_003DC48C != 0) {
            *p = 0;
            func_0010bd90(D_0062F790, func_001e3f00);
            func_0010f520();
            func_0010e3f0(D_0062F760);
            func_0010ef70(D_0062F760 - 0x80, D_003DBA68, func_001e2810);
            D_003DC478 = 1;
            D_003DC47C = 0x3C;
            func_0011ef10(0xC350, func_001e2920);
        }
    }
    return 0;
}

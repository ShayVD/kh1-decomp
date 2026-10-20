/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
#include "data/bss_0063.h"

M2C_UNK func_0010bd90(M2C_UNK *, M2C_UNK);
M2C_UNK func_00232aa8();
extern M2C_UNK D_00630300;
extern M2C_UNK D_00630460;
extern s32 D_006314D4;
extern s64 D_00389C90[];
void func_0011c7d8(s32, f32, f32, f32, f32, f32, f32, f32, f32);
void func_001e86a0(void);
void func_001e8728(void);

void func_001e01f0(void) {
    D_00389C90[1550] = (s64) (D_00389C90[1550] & (((((s64) 0xFFEFFFFF << 0x10) | 0xFFFF) << 0x10) | 0xFFFF));
}

void func_001e2498(void) {
    D_00389C90[1550] = (s64) (D_00389C90[1550] & (((((s64) 0xFFFBFFFF << 0x10) | 0xFFFF) << 0x10) | 0xFFFF));
}

void func_001e78d8(void) {
    func_0010bd90(&D_00630460, 0);
    D_00389C90[1550] = (s64) (D_00389C90[1550] & (((((s64) 0xFFDFFFFF << 0x10) | 0xFFFF) << 0x10) | 0xFFFF));
}

void func_001e7a10(void) {
    func_0010bd90(&D_00630460, 0);
    D_00389C90[1550] = (s64) (D_00389C90[1550] & (((((s64) 0xFFDFFFFF << 0x10) | 0xFFFF) << 0x10) | 0xFFFF));
}

void func_001e7b50(void) {
    func_00232aa8();
    func_0010bd90(&D_00630300, 0);
    D_00389C90[1550] = (s64) (D_00389C90[1550] & (((((s64) 0xFFDFFFFF << 0x10) | 0xFFFF) << 0x10) | 0xFFFF));
}

void func_001e7fe0(void) {
    D_00389C90[1550] = (s64) (D_00389C90[1550] & (((((s64) 0xFEFFFFFF << 0x10) | 0xFFFF) << 0x10) | 0xFFFF));
}

void func_001e8308(void) {
    D_00389C90[1550] = (s64) (D_00389C90[1550] & (((((s64) 0xFFF7FFFF << 0x10) | 0xFFFF) << 0x10) | 0xFFFF));
}

void func_001e8628(void) {
    D_00389C90[1550] = (s64) (D_00389C90[1550] & (((((s64) 0xFDFFFFFF << 0x10) | 0xFFFF) << 0x10) | 0xFFFF));
}

s32 func_001e8770(f32 fparg0, f32 fparg1, f32 fparg2, f32 fparg3, f32 fparg4, f32 fparg5, f32 fparg6, f32 fparg7) {
    func_0011c7d8(D_006314D4, fparg0, fparg1, fparg2, fparg3, fparg4, fparg5, fparg6, fparg7);
    D_00389C90[1550] = (s64) (D_00389C90[1550] | ((s64) 0x8000 << 0x2A));
    func_001e86a0();
    return 2;
}

s32 func_001e87b8(f32 fparg0, f32 fparg1, f32 fparg2, f32 fparg3, f32 fparg4, f32 fparg5, f32 fparg6, f32 fparg7) {
    func_0011c7d8(D_006314D4, fparg0, fparg1, fparg2, fparg3, fparg4, fparg5, fparg6, fparg7);
    D_00389C90[1550] = (s64) (D_00389C90[1550] | ((s64) 0x8000 << 0x2A));
    func_001e8728();
    return 2;
}

void func_001e8e38(void) {
    D_00389C90[1550] = (s64) (D_00389C90[1550] & (((((s64) 0xFF7FFFFF << 0x10) | 0xFFFF) << 0x10) | 0xFFFF));
}

s32 func_001ea438(void) {
    D_00389C90[1550] = (s64) (D_00389C90[1550] & (((((s64) 0xFFBFFFFF << 0x10) | 0xFFFF) << 0x10) | 0xFFFF));
    return 2;
}

s32 func_001ea470(void) {
    D_00389C90[1550] = (s64) (D_00389C90[1550] | ((s64) 0x8000 << 0x27));
    return 2;
}

/* wm.x func_00f218e8: matched by hand. */
#include "ovl.h"

extern s32 D_00F87270, D_002C1370, D_00FBA800, D_00F850A8, D_00F87308, D_002B6770, D_00F850CC, D_00F850F8;
extern f32 D_00FBA900[4][4], D_00FBA880[4][4], D_00F85200[4][4], D_00F85180[4][4], D_00F9A580[4][4];
s32 func_00122048(s32, s32);
void func_001220b8(s32);
void func_001bb858(f32 (*)[4], f32 (*)[4]);
void sceVu0CopyMatrix(f32 (*)[4], f32 (*)[4]);
void sceVu0UnitMatrix(f32 (*)[4]);
void sceVu0RotMatrix(f32 (*)[4], f32 (*)[4], f32 *);
void func_00110a48(f32);
void func_00f43ce0(void);
void func_00f23860(void);
void func_00f66ef0(void);
void func_00f681b0(void);
void func_001c0010(void);
void func_00112fe0(void);
void func_00f4a020(void);
void func_001ba708(s32);
void func_001bb4b0(void);
s32 func_001c00e8(s32, void (*)(void), kh1_u128);
void func_001bfc90(s32);
void func_00f206f0(void);
void func_001be9f0(f32 *);
void func_001bfac8(void);
void func_00f23628(void);
void func_00f43ae0(void);

s32 func_00f218e8(void) {
    f32 rot[4];
    s32 *p;

    p = &D_00F87270;
    *p = func_00122048(4096, 16);
    D_002C1370 = 0;
    func_001bb858(D_00FBA900, D_00FBA880);
    sceVu0CopyMatrix(D_00FBA900, D_00F85200);
    sceVu0CopyMatrix(D_00FBA880, D_00F85180);
    func_00110a48(277.0f);
    if (D_00FBA800 != 0) {
        switch (D_00F850A8) {
        case 0:
            func_00f43ce0();
            break;
        case 1:
            func_00f23860();
            break;
        }
        D_00F850A8 = -1;
    }
    switch (D_00FBA800) {
    case 3:
        D_00FBA800 = 0;
        func_00f66ef0();
        func_00f681b0();
        func_001c0010();
        D_002B6770 = D_00F87308;
        func_00112fe0();
        func_001ba708(0);
        func_001220b8(D_00F87270);
        return 4;
    case 4:
        D_00FBA800 = 0;
        func_00f66ef0();
        func_00f681b0();
        func_001c0010();
        func_00f4a020();
        func_001ba708(0);
        func_001220b8(D_00F87270);
        return 4;
    case 1:
        D_00FBA800 = 0;
        func_00f681b0();
        func_001bb4b0();
        func_001c0010();
        func_001c00e8(2, func_00f23628, 0);
        func_001bfc90(3);
        break;
    case 2:
        D_00FBA800 = 0;
        func_00f681b0();
        func_001bb4b0();
        func_001c0010();
        func_001c00e8(2, func_00f43ae0, 0);
        func_001bfc90(3);
        break;
    }
    if (D_00F850CC != 0) {
        func_00f206f0();
    }
    rot[3] = 1.0f;
    rot[0] = 0.0f;
    rot[1] = 0.0f;
    rot[2] = 0.0f;
    rot[1] = (D_00F850F8 % 480) * 6.283185006f / 480.0f;
    func_001be9f0(rot);
    sceVu0UnitMatrix(D_00F9A580);
    sceVu0RotMatrix(D_00F9A580, D_00F9A580, rot);
    D_00F850F8++;
    func_001bfac8();
    func_001220b8(D_00F87270);
    return 0;
}

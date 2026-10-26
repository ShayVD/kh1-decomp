/* xs_bambi.x func_00f203d8: matched by hand (session 131b). */
#include "ovl.h"

extern u8 *D_00F20900;
extern u8 D_00F20A10[];
f32 *func_0014dab8(void);
void func_0013aaa0(void);
void func_00f20638(void *, f32 *, f32);
void func_00130398(void *, s32, f32);
void func_00130578(void *, s32, f32);
void func_00130340(void *, s32, f32);
s32 func_00137618(void *);
s32 func_0012ba98(s32);
f32 func_001216d8(f32, f32, f32);
void func_00137688(void *, f32);
void func_00f203d8(u8 *o) {
    OvlVec v;
    f32 *p;

    p = func_0014dab8();
    if (p != NULL && p[1] < M2C_FIELD(o, f32 *, 0x14)) {
        func_0013aaa0();
    }
    PlatVu0CopyVector(v, D_00F20900 + 0x10);
    func_00f20638(D_00F20A10, v, 30.0f);
    if (M2C_FIELD(o, s32 *, 0) & 0x400) {
        switch (M2C_FIELD(o, s32 *, 0x70)) {
        case 0:
            switch (M2C_FIELD(o, s32 *, 0x378)) {
            case 2:
            case 3:
                func_00130398(o, (M2C_FIELD(o, s32 *, 0x3D0) + 7) | 0x01000000, 0.0f);
                func_00130578(o, 0x40000000, 0.0f);
                PlatVu0CopyVector(o + 0x20, o + 0x30);
                M2C_FIELD(o, f32 *, 0x2C) = 0.0f;
                break;
            }
            break;
        case 2:
        case 3:
            func_00130340(o, 6, 0.0f);
            break;
        }
    }
    if (func_00137618(o) != 0 && func_0012ba98(M2C_FIELD(o, s32 *, 0x144)) < 0) {
        M2C_FIELD(o, s32 *, 0x144) = 0;
    }
    if (!((M2C_FIELD(o, u64 *, 0x370) >> 0x2C) & 1)) {
        func_00137688(o, func_001216d8(M2C_FIELD(o, f32 *, 0x3C), M2C_FIELD(o, f32 *, 0x150),
                                       M2C_FIELD(M2C_FIELD(o, u8 **, 0x6C), f32 *, 0xCC)));
    }
}

/* wm.x func_00f55bf8: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[0x48]; u8 m48[0x82 - 0x48]; s16 h82; } WmObj;
extern WmObj *D_00F9B540;
extern s32 D_00F9B548;
extern s32 D_00FA5CE0;
extern f32 D_00FA5CE4;
extern f32 D_00FA5CE8;
extern f32 D_00FA5D00[4];
void func_001bbbd0(void *, void *);
void func_001bfac8(void);
s32 func_00f4ad68(s32);
s32 func_00f4ae48(s32);
void func_00f4eaa0(s32, s32 *, s32, s32, s32, s32, void *, f32, f32);
#ifdef KH1_PS2 /* portability rule 11: the EE passes the floats in their own registers */
s32 func_00f4ec30(s32, s32 *, s32, s32, s32, f32, f32, s32, f32);
#else
s32 func_00f4ec30(s32, s32 *, s32, s32, s32, s32, f32, f32, f32);
static __inline__ s32 ee_00f4ec30(s32 x0, s32 * x1, s32 x2, s32 x3, s32 x4, f32 x5, f32 x6, s32 x7, f32 x8) { return func_00f4ec30(x0, x1, x2, x3, x4, x7, x5, x6, x8); }
#undef func_00f4ec30
#define func_00f4ec30 ee_00f4ec30
#endif
void func_00f559d0(void);
void func_00f55ad8(void);

void func_00f55bf8(void) {
    f32 m[4][4];
    s32 a;
    s32 b;
    s32 r;
    s32 c;

    while (1) {
        if (D_00FA5CE0 != 0) {
            func_00f55ad8();
        }
        a = func_00f4ae48(D_00F9B540->h82);
        b = func_00f4ad68(D_00F9B540->h82);
        c = D_00F9B540->h82;
        r = func_00f4ec30(0x2BC0, &D_00F9B548, 0x29, 0x4C, a, 0.0f, 0.0f, 0x3A, D_00FA5CE4);
        func_00f4ec30(r, &D_00F9B548, 0x29, 0x15B, b, 0.0f, 0.0f, 0x3A, D_00FA5CE4);
        func_00f559d0();
        func_001bbbd0(m, D_00F9B540->m48);
        PlatVu0RotMatrix(m, m, D_00FA5D00);
        func_00f4eaa0(0x29E0, &D_00F9B548, 0x440, 0xC00, c, 0, m, D_00FA5CE8, D_00FA5CE4);
        func_001bfac8();
    }
}

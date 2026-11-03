/* gb.x func_00f2eb00: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[0x48]; f32 rot[4]; u8 pad58[0x2A]; s16 cur; } World;
void func_001bbbd0(OvlMtx, void *);
void func_001bfac8(void);
s32 func_00f23c70(s32);
s32 func_00f23d50(s32);
void func_00f279a8(s32, void *, s32, s32, s32, s32, OvlMtx, f32, f32);
#ifdef KH1_PS2 /* portability rule 11: the EE passes the floats in their own registers */
s32 func_00f27b38(s32, void *, s32, s32, s32, f32, f32, s32, f32);
#else
s32 func_00f27b38(s32, void *, s32, s32, s32, s32, f32, f32, f32);
static __inline__ s32 ee_00f27b38(s32 x0, void * x1, s32 x2, s32 x3, s32 x4, f32 x5, f32 x6, s32 x7, f32 x8) { return func_00f27b38(x0, x1, x2, x3, x4, x7, x5, x6, x8); }
#undef func_00f27b38
#define func_00f27b38 ee_00f27b38
#endif
void func_00f2e8d8(void);
void func_00f2e9e0(void);
extern World *D_00F56DC0;
extern u8 D_00F56DC8[];
extern s32 D_00F61560;
extern f32 D_00F61564;
extern f32 D_00F61568;
extern OvlVec D_00F61580;

void func_00f2eb00(void) {
    OvlMtx m;
    s32 prev, next, cur, r;
    while (1) {
        if (D_00F61560 != 0) {
            func_00f2e9e0();
        }
        prev = func_00f23d50(D_00F56DC0->cur);
        next = func_00f23c70(D_00F56DC0->cur);
        cur = D_00F56DC0->cur;
        r = func_00f27b38(0x2BC0, D_00F56DC8, 41, 76, prev, 0.0f, 0.0f, 58, D_00F61564);
        func_00f27b38(r, D_00F56DC8, 41, 347, next, 0.0f, 0.0f, 58, D_00F61564);
        func_00f2e8d8();
        func_001bbbd0(m, D_00F56DC0->rot);
        PlatVu0RotMatrix(m, m, D_00F61580);
        func_00f279a8(0x29E0, D_00F56DC8, 0x440, 0xC00, cur, 0, m, D_00F61568, D_00F61564);
        func_001bfac8();
    }
}

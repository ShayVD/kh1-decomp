/* The view: the view and projection matrices D_002E26C0 / D_002E2700
 * (func_00125000 builds them, func_001251a0 the screen ones), the view state
 * D_002E27A0-D_002E27A8 (func_00124c68 / func_00124ce0 / func_00124d08), the
 * field of view (func_00124d28, called by the cameras of src/camera/),
 * func_00125240 the per-frame update. Flag mode: default (the other modes
 * are in the sibling files). Read from the code, not proved by a boot
 * (docs/modules.md "Session 54"). */
#include "m2c.h"
#include "actor.h"
#include "data/bss_004F.h"
#include "data/pieces/D_002C5C80.h"
#include "data/pieces/D_002C6440.h"
#include "data/pieces/D_002E26A0.h"
#include "data/pieces/D_002C58D0.h"
#include "data/pieces/D_002E27A4.h"
#include "data/pieces/D_002C5C48.h"
#include "common.h"
#include "platform/vu.h"
#include "data/pieces/D_002C5968.h"
#include "data/types/text_00110000_h53_p.h"
#include "data/types/text_00110000_h53_p2.h"
#include "data/pieces/D_002C5910.h"
#include "data/pieces/D_002C58A0.h"
#include "data/types/text_00110000_h53.h"
#include "data/pieces/D_002E2790.h"
#include "data/pieces/D_002E2780.h"
#include "data/pieces/D_002E2700.h"
#include "data/pieces/D_002E2740.h"
#include "data/pieces/D_002BBE20.h"
#include "data/pieces/D_002E26C0.h"
#include "data/pieces/D_002E27C8.h"
#include "data/pieces/D_002E27D4.h"

/* func_00124c68 (from auto/text_00120000_3.c). */
extern f32 D_002E27A0;
f32 func_0026b8b8(f32);
void func_00124c68(f32 fparg0) {
    D_002E27A0 = fparg0;
    D_004F7650 = 256.0f / func_0026b8b8(((fparg0 * 0.5f) / 180.0f) * 3.141592979f);
}

/* func_00124ce0 (from auto/text_00120000.c). */
#define func_00124c68 ((M2C_UNK (*)(f32)) func_00124c68)
void func_00124ce0(f32 fparg0) {
    D_004F77E4 = D_002E27A0;
    func_00124c68(fparg0);
}
#undef func_00124c68

/* func_00124d08 (from auto/text_00120000_1.c). */
#define func_00124c68 ((M2C_UNK (*)(f32)) func_00124c68)
void func_00124d08(void) {
    func_00124c68(D_004F77E4);
}
#undef func_00124c68

/* func_00124d28 (from auto/text_00120000.c). */
M2C_UNK func_0026b9a8(f32, f32);
void func_00124d28(void *arg0, void *arg1) {
    func_0026b9a8(M2C_FIELD(arg0, f32 *, 0) - M2C_FIELD(arg1, f32 *, 0), M2C_FIELD(arg0, f32 *, 8) - M2C_FIELD(arg1, f32 *, 8));
}

/* func_00124d58 (from auto/text_00120000_8.c). */
f32 func_00120c88(f32);
void func_00124d58(void *arg0, void *arg1, f32 fparg0, f32 fparg1) {
    s32 sp[16];
    PlatVu0RotMatrixY(sp, ((M2C_UNK *)&D_002C58D0), -func_00120c88(D_002E27A4));
    PlatVu0ApplyMatrix(arg1, sp, arg0);
    M2C_FIELD(arg1, f32 *, 0) = (f32) -M2C_FIELD(arg1, f32 *, 0);
    M2C_FIELD(arg1, f32 *, 0xC) = fparg1;
    PlatVu0RotMatrixY(sp, ((M2C_UNK *)&D_002C58D0), fparg0);
    PlatVu0ApplyMatrix(arg1, sp, arg1);
}

/* func_00124e08 (from hand/text_00110000_h53.c). */
#define FLD(T, p, off) (*(T *)((u8 *)(p) + (off)))
extern s32 D_002E27A8;
extern f32 D_004F77E0;
#define func_00124d58 ((void (*)(V53 *, V53 *, f32, f32)) func_00124d58)
void func_00124e08(u8 *o, u8 *p, V53 *out) {
    f32 m[4][4];
    V53 v;
    switch (D_002E27A8) {
    case 2:
        PlatVu0RotMatrixY(m, D_002C58D0, FLD(f32, p, 0x40) * 0.0523598762229085f);
        PlatVu0ApplyMatrix(out, m, (V53 *)(o + 0x30));
        out->y = out->w = 0.0f;
        return;
    case 11:
        if (FLD(f32, p, 0x44) <= 0.0f) {
            PlatVu0RotMatrixY(m, D_002C58D0, FLD(f32, p, 0x40) * 0.0523598762229085f);
            PlatVu0ApplyMatrix(out, m, (V53 *)(o + 0x20));
            out->y = 0.0f;
            PlatVu0Normalize(out, out);
            out->w = -FLD(f32, p, 0x44);
            return;
        }
        if ((FLD(u32, p, 8) & 0x400000) && FLD(f32, p, 0x40) == 0.0f) {
            PlatVu0SubVector(out, &D_002C58A0, (V53 *)(o + 0x20));
        } else {
            PlatVu0CopyVector(out, o + 0x20);
        }
        out->y = 0.0f;
        PlatVu0Normalize(out, out);
        out->w = 0.0f;
        return;
    }
    PlatVu0CopyVector(&v, p + 0x60);
    switch (FLD(s32, o, 0x70)) {
    case 10:
    case 13:
    case 15:
        break;
    case 18:
        v.y = 0.0f;
        break;
    case 29:
        PlatVu0CopyVector(out, &v);
        out->w = FLD(f32, p, 0x4c);
        return;
    default:
        v.z = v.y;
        v.y = 0.0f;
        break;
    }
    func_00124d58(&v, out, D_004F77E0, FLD(f32, p, 0x4c));
}
#undef func_00124d58
#undef FLD

/* func_00125000 (from hand/text_00110000_h53.c). */
extern V53 D_002E26B0;
extern s32 D_002C5950;
extern M53 D_004F76E0[];
extern M53 D_004F7660[];
extern M53 D_004F7760[];
extern f32 (*D_002E27AC)[4];
void func_00110a48(f32);
void func_00120cf8(V53 *, f32 (*)[4], f32);
void func_00110ba8(void);
#define func_00124d28 ((f32 (*)(V53 *, V53 *)) func_00124d28)
s32 func_00125000(void) {
    V53 d, r;
    M53 m;
    func_00110a48(D_004F7650);
    PlatVu0SubVector(&d, &D_002E2790, &D_002E2780);
    PlatVu0Normalize(&d, &d);
    func_00120cf8(&d, m, func_00120c88(D_002E27A4));
    PlatVu0ApplyMatrix(&r, m, &D_002E26B0);
    PlatVu0CameraMatrix(D_004F76E0[D_002C5950], &D_002E2780, &d, &r);
    PlatVu0CopyMatrix(D_002E2700, D_004F76E0[D_002C5950]);
    PlatVu0CopyMatrix(D_004F7760[D_002C5950], D_002BBE20);
    PlatVu0CopyMatrix(D_002E2740, D_004F7760[D_002C5950]);
    PlatVu0MulMatrix(D_004F7660[D_002C5950], D_002E2740, D_002E2700);
    PlatVu0CopyMatrix(D_002E26C0, D_004F7660[D_002C5950]);
    D_002E27AC = D_004F7660[D_002C5950];
    func_00110ba8();
    D_004F77E0 = func_00124d28(&D_002E2780, &D_002E2790);
    return 0;
}
#undef func_00124d28

/* func_001251a0 (from auto/text_00120000_7.c). */
M2C_UNK func_00110c30();
#define D_004F7660 (*(M2C_UNK (*)) &D_004F7660)
#define D_004F76E0 (*(M2C_UNK (*)) &D_004F76E0)
#define D_004F7760 (*(M2C_UNK (*)) &D_004F7760)
s32 func_001251a0(void) {
    PlatVu0CopyMatrix(((M2C_UNK *)&D_002E2700), (s8 *)&D_004F76E0 + ((D_002C5950 ^ 1) << 6));
    PlatVu0CopyMatrix((M2C_UNK *)&D_002E26C0, (s8 *)&D_004F7660 + ((D_002C5950 ^ 1) << 6));
    PlatVu0CopyMatrix(((M2C_UNK *)&D_002E2740), (s8 *)&D_004F7760 + ((D_002C5950 ^ 1) << 6));
    func_00110c30();
    return 0;
}
#undef D_004F7660
#undef D_004F76E0
#undef D_004F7760

/* func_00125240 (from hand/text_00120000_s22_s22m1.c). */
typedef FVec4 V4f;
void func_0011ef10(s32, void (*)(void));
void func_0017f510(void);
#define func_00125000 ((void (*)(void)) func_00125000)
/* func_00125240: MATCHED (session 22, s22m1), hand. From s20m1's 3w draft (natural body, FP constants pinned: 10000.0f in $f0, -10000.0f in $f2, 1.0f in $f3). New: `f32 *q = &D_002E27A4;` at the top with the store written `*q = x;`. The 27A4 HIGH now gets the low LUID from the declaration (combine folds the LO_SUM into the swc1), independent of where the store sits, so sched1 issues it before the D_004F77E0 HIGH and local-alloc still gives it a0; then pclimb_s15 over the body order (1 -> 0). FLAGGED: three local register variables (without them 8w). */
void func_00125240(void) {
    V4f *p = &D_002E2780;
    f32 y, x;
    register f32 k KH1_REG("$f0");
    register f32 m KH1_REG("$f2");
    register f32 one KH1_REG("$f3");
    f32 *q = &D_002E27A4;
    m = -10000.0f;
    p->y = m;
    one = 1.0f;
    p->x = 0.0f;
    p->w = one;
    k = 10000.0f;
    p->z = k;
    x = p->x;
    D_002E2790.x = x;
    D_004F77E0 = x;
    D_002E2790.y = x;
    D_002E2790.z = x;
    y = 53.0f;
    *q = x;
    D_002E2790.w = one;
    func_00124c68(y);
    func_00125000();
    func_0011ef10(0x1adb0, func_00125000);
    func_0011ef10(0x20f58, func_001251a0);
    func_0017f510();
}
#undef func_00125000


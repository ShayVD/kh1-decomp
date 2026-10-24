/* The object scripts' commands: the 225 functions of the command table at
 * 0x002E2810 (8-byte {fn, argc, flags} records, reached through the
 * descriptor D_002E2F20; docs/renderer-spec.md), each taking its arguments
 * from the stack VM (src/vm/stackvm.nostrict.c) and calling the object code:
 * motion (func_00130340 ...), bones, movement, damage, effects, the party,
 * the room's area boxes; func_00128c60-func_00128db0 before the table are
 * the helpers on the current node D_00514F10. Flag mode: default (the other
 * modes are in the sibling files). Read from the code, not proved by a boot
 * (docs/modules.md "Session 54"). */
#include "m2c.h"
#include "data/pieces/D_002E26A0.h"
#include "actor.h"
#include "data/bss_004F.h"
#include "data/pieces/D_002C5C80.h"
#include "data/pieces/D_002C6440.h"
#include "data/pieces/D_002C58D0.h"
#include "data/pieces/D_002E2700.h"
#include "data/pieces/D_002E27A4.h"
#include "data/pieces/D_002C5C48.h"
#include "data/pieces/D_002E2F28.h"
#include "data/pieces/D_002E31A8.h"
#include "data/pieces/D_00304B78.h"
#include "data/pieces/D_002BBDE4.h"
#include "common.h"
#include "platform/vu.h"
#include "data/bss_0051.h"
#include "data/bss_0052.h"
#include "data/types/text_00120000_h5.h"
#include "data/pieces/D_002E31B0.h"
#include "data/pieces/D_002C58B0.h"
#include "data/pieces/D_002E31B8.h"
#include "data/types/text_00120000_h31_p.h"
#include "data/pieces/D_002E26AC.h"
#include "data/pieces/D_00308CDC.h"
#include "data/types/text_00120000_h31.h"
#include "data/pieces/D_00351BC8.h"
#include "data/pieces/D_002C5C60.h"
#include "data/pieces/D_002BC098.h"

/* func_00128c60 (from auto/text_00120000_15.c). */
extern void *D_00514F10;
s32 func_0012b930(s32, s32);
void func_0012ba30(s32, s32, s32);
s32 func_00128c60(s32 arg0, s32 arg1) {
    s32 temp_a0;
    s32 temp_v0;

    temp_v0 = func_0012b930((s32) D_00514F10, M2C_FIELD(D_00514F10, s32 *, 4) + (arg1 * 2));
    temp_a0 = temp_v0;
    if (*(M2C_UNK *)arg0 != 0) {
        func_0012ba30(temp_a0, arg0, 4);
    }
    return temp_v0;
}

/* func_00128cc8 (from auto/text_00120000_3.c). */
void func_00128cc8(s32 arg0) {
    M2C_FIELD(arg0, s32 *, 0) = func_00128c60(arg0, M2C_FIELD(arg0, s32 *, 4));
}

/* func_00128cf8 (from auto/text_00120000_8.c). */
M2C_UNK func_0012b9b0(s32);
void func_00128cf8(s32 *arg0) {
    func_0012b9b0(*arg0);
}

/* func_00128d10 (from auto/text_00120000_8.c). */
#define func_00128c60 ((s32 (*)(void *, s32)) func_00128c60)
void func_00128d10(void *arg0) {
    s32 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s32 *, 0);
    if (temp_v0 != 0) {
        func_0012b9b0(temp_v0);
    }
    M2C_FIELD(arg0, s32 *, 0) = func_00128c60(arg0 + 4, M2C_FIELD(arg0, s32 *, 8));
}
#undef func_00128c60

/* func_00128d58 (from auto/text_00120000_8.c). */
extern s32 D_00514F14;
void func_00128d58(void) {
    func_0012b9b0(D_00514F14);
}

/* func_00128d78 (from auto/text_00120000_8.c). */
extern s32 D_00514F10_00128d78 __asm__("D_00514F10");
#define D_00514F10 D_00514F10_00128d78
void func_00128d78(u16 *arg0) {
    s32 var_a1;
    s32 var_a2;
    u16 *var_a0;
    u16 temp_v1;
    void *temp_v0;

    var_a0 = arg0;
    var_a2 = 0x720;
    var_a1 = 3;
    do {
        var_a1 -= 1;
        temp_v1 = *var_a0;
        var_a0 += 2;
        temp_v0 = D_00514F10 + var_a2;
        var_a2 += 2;
        M2C_FIELD(temp_v0, u16 *, 4) = temp_v1;
    } while (var_a1 >= 0);
}
#undef D_00514F10

/* func_00128db0 (from auto/text_00120000.c). */
extern s32 D_00514F10_00128db0 __asm__("D_00514F10");
#define D_00514F10 D_00514F10_00128db0
void func_00128db0(void *arg0) {
    M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0) * 2) + D_00514F10), u16 *, 0x724) = (u16) M2C_FIELD(arg0, u16 *, 4);
}
#undef D_00514F10

/* func_00128dd0 (from auto/text_00120000.c). */
void func_00128dd0(void) {

}

/* func_00128dd8 (from auto/text_00120000.c). */
void func_00128dd8(void) {

}

/* func_00128de0 (from auto/text_00120000_3.c). */
f32 func_00120c88(f32);
f32 func_0026b7d0(f32);
void func_00128de0(f32 *arg0) {
    *arg0 = func_0026b7d0(func_00120c88((*arg0 / 180.0f) * 3.141592979f));
}

/* func_00128e38 (from auto/text_00120000_3.c). */
f32 func_0026b6f8(f32);
void func_00128e38(f32 *arg0) {
    *arg0 = func_0026b6f8(func_00120c88((*arg0 / 180.0f) * 3.141592979f));
}

/* func_00128e90 (from auto/text_00120000.c). */
f32 func_00176850();
void func_00128e90(f32 *arg0) {
    *arg0 = func_00176850();
}

/* func_00128eb8 (from auto/text_00120000.c). */
extern f32 D_002BBDFC;
void func_00128eb8(f32 *arg0) {
    *arg0 = D_002BBDFC;
}

/* func_00128ec8 (from auto/text_00120000.c). */
s32 func_001477c8(s32);
void func_00128ec8(s32 *arg0) {
    *arg0 = func_001477c8(*arg0);
}

/* func_00128ef8 (from auto/text_00120000.c). */
void func_00128ef8(void) {

}

/* func_00128f00 (from auto/text_00120000.c). */
void func_00128f00(void) {

}

/* func_00128f08 (from auto/text_00120000.c). */
void func_00128f08(void) {

}

/* func_00128f10 (from auto/text_00120000_3.c). */
void func_00128f10(f32 *arg0) {
    *arg0 = func_00120c88((*arg0 / 180.0f) * 3.141592979f);
}

/* func_00128f60 (from auto/text_00120000.c). */
extern f32 D_002BBE00;
void func_00128f60(f32 *arg0) {
    D_002BBE00 = *arg0;
}

/* func_00128f70 (from auto/text_00120000.c). */
void func_00128f70(s32 *arg0) {
    s32 var_a1;

    var_a1 = 0;
    if ((u32) D_002BBDE4 >= 2U) {
        var_a1 = D_002BBDE4 != 7;
    }
    *arg0 = var_a1;
}

/* func_00128f98 (from auto/text_00120000.c). */
extern u32 D_002C5958;
void func_00128f98(s32 *arg0) {
    *arg0 = ((u32) D_002C5958 >> 0xD) & 1;
}

/* func_00128fb0 (from auto/text_00120000.c). */
void func_00128fb0(s32 *arg0) {
    *arg0 = (*(u32 *)&D_00304B78) & 7;
}

/* func_00128fc8 (from hand/text_00120000_h5.c). */
typedef union Arg {
    s32 i;
    u32 u;
    f32 f;
    void *p;
} Arg;
extern f32 func_00120bf8(s32);
void func_00128fc8(Arg *p) {
    p->f = func_00120bf8(p->i);
}

/* func_00128ff8 (from auto/text_00120000_8.c). */
void func_00128ff8(void *arg0) {
    s32 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s32 *, 0);
    PlatVu0AddVector(temp_v0, temp_v0, M2C_FIELD(arg0, s32 *, 4));
}

/* func_00129020 (from auto/text_00120000_8.c). */
void func_00129020(void *arg0) {
    s32 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s32 *, 0);
    PlatVu0SubVector(temp_v0, temp_v0, M2C_FIELD(arg0, s32 *, 4));
}

/* func_00129048 (from auto/text_00120000_8.c). */
M2C_UNK func_00121fc4(s32, s32);
void func_00129048(s32 *arg0) {
    s32 temp_a0;

    temp_a0 = *arg0;
    func_00121fc4(temp_a0, temp_a0);
}

/* func_00129068 (from auto/text_00120000_9.c). */
void func_00129068(void *arg0) {
    s32 sp[16];
    s32 temp_a0;

    PlatVu0RotMatrixY(sp, ((M2C_UNK *)&D_002C58D0), func_00120c88((M2C_FIELD(arg0, f32 *, 4) / 180.0f) * 3.141592979f));
    temp_a0 = M2C_FIELD(arg0, s32 *, 0);
    PlatVu0ApplyMatrix(temp_a0, sp, temp_a0);
}

/* func_001290d8 (from auto/text_00120000_9.c). */
void func_001290d8(void *arg0) {
    s32 sp[16];
    s32 temp_a0;

    PlatVu0RotMatrixZ(sp, ((M2C_UNK *)&D_002C58D0), func_00120c88((M2C_FIELD(arg0, f32 *, 4) / 180.0f) * 3.141592979f));
    temp_a0 = M2C_FIELD(arg0, s32 *, 0);
    PlatVu0ApplyMatrix(temp_a0, sp, temp_a0);
}

/* func_00129148 (from auto/text_00120000_9.c). */
void func_00129148(void *arg0) {
    s32 sp[4];
    s32 temp_a0;

    PlatVu0ScaleVectorXYZ(sp, M2C_FIELD(arg0, s32 *, 4), M2C_FIELD(arg0, f32 *, 8) * D_002BBDFC);
    temp_a0 = M2C_FIELD(arg0, s32 *, 0);
    PlatVu0AddVector(temp_a0, temp_a0, sp);
}

/* func_00129198 (from auto/text_00120000_8.c). */
M2C_UNK func_00121860(s32, s32, s32, f32);
void func_00129198(void *arg0) {
    s32 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s32 *, 0);
    func_00121860(temp_v0, M2C_FIELD(arg0, s32 *, 4), temp_v0, (M2C_FIELD(arg0, f32 *, 8) / 180.0f) * 3.141592979f);
}

/* func_001291e8 (from auto/text_00120000_8.c). */
void func_001291e8(void *arg0) {
    s32 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s32 *, 0);
    PlatVu0ScaleVectorXYZ(temp_v0, temp_v0, M2C_FIELD(arg0, f32 *, 4));
}

/* func_00129210 (from hand/text_00120000_h5.c). */
extern f32 func_00121748(s32, s32);
void func_00129210(Arg *p) {
    p[0].f = func_00121748(p[0].i, p[1].i);
}

/* func_00129240 (from hand/text_00120000_h5.c). */
extern void func_0014e668(s32, s32, f32, f32, s32);
void func_00129240(Arg *p) {
    func_0014e668(p[0].i, 0, p[1].f, p[2].f, p[3].i);
}

/* func_00129270 (from hand/text_00120000_h31.c). */
typedef struct { f32 *m; f32 *rot; } R8;
void func_00129270(R8 *r) {
    f32 v[4];
    f32 m[16];
    s32 i;
    for (i = 0; i < 3; i++) {
        v[i] = func_00120c88(r->rot[i] / 180.0f * 3.1415928f);
    }
    v[3] = 0.0f;
    PlatVu0RotMatrix(m, D_002C58D0[0], v);
    PlatVu0ApplyMatrix(r->m, m, r->m);
}

/* func_00129330 (from auto/text_00120000.c). */
void func_00129330(void) {

}

/* func_00129338 (from auto/text_00120000_8.c). */
M2C_UNK func_00121a10(s32, s32);
void func_00129338(void *arg0) {
    func_00121a10(M2C_FIELD(arg0, s32 *, 0), M2C_FIELD(arg0, s32 *, 4));
}

/* func_00129358 (from auto/text_00120000_8.c). */
s32 func_00123488(s32);
void func_00129358(s32 *arg0) {
    *arg0 = func_00123488(*arg0);
}

/* func_00129388 (from auto/text_00120000_8.c). */
M2C_UNK func_00137688(void *, f32);
f32 atan2f(f32, f32);
void func_00129388(void *arg0) {
    f32 temp_f0;
    void *temp_s0;
    void *temp_v0;

    temp_v0 = M2C_FIELD(arg0, void **, 4);
    temp_s0 = M2C_FIELD(arg0, void **, 0);
    temp_f0 = atan2f(M2C_FIELD(temp_v0, f32 *, 0), M2C_FIELD(temp_v0, f32 *, 8));
    M2C_FIELD(temp_s0, f32 *, 0x150) = temp_f0;
    func_00137688(temp_s0, temp_f0);
}

/* func_001293c8 (from auto/text_00120000_8.c). */
M2C_UNK func_00130398(s32, s32, f32);
void func_001293c8(void *arg0) {
    func_00130398(M2C_FIELD(arg0, s32 *, 0), M2C_FIELD(arg0, s32 *, 4), M2C_FIELD(arg0, f32 *, 8));
}

/* func_001293f0 (from auto/text_00120000_8.c). */
void *func_00130340(s32, s32, f32);
void func_001293f0(void *arg0) {
    M2C_FIELD(func_00130340(M2C_FIELD(arg0, s32 *, 0), M2C_FIELD(arg0, s32 *, 4), M2C_FIELD(arg0, f32 *, 8)), f32 *, 4) = (f32) M2C_FIELD(arg0, f32 *, 0xC);
}

/* func_00129428 (from auto/text_00120000.c). */
void *func_00130578(s32, s32, f32);
void func_00129428(void *arg0) {
    M2C_FIELD(func_00130578(M2C_FIELD(arg0, s32 *, 0), M2C_FIELD(arg0, s32 *, 4), M2C_FIELD(arg0, f32 *, 8)), f32 *, 4) = (f32) M2C_FIELD(arg0, f32 *, 0xC);
}

/* func_00129460 (from hand/text_00120000_h5.c). */
extern void func_001315c0(void *, s32, f32, void *);
void func_00129460(Arg *p) {
    func_001315c0(p[0].p, p[1].i, p[2].f, p[3].p);
}

/* func_00129488 (from hand/text_00120000_h5.c). */
extern f32 func_00142cf0(s32, s32, f32, f32);
void func_00129488(Arg *p) {
    p[0].f = func_00142cf0(p[0].i, p[1].i, p[2].f, p[3].f);
}

/* func_001294c0 (from auto/text_00120000.c). */
s32 func_001230a0(s32);
void func_001294c0(s32 *arg0) {
    *arg0 = func_001230a0(*arg0);
}

/* func_001294f0 (from auto/text_00120000_8.c). */
M2C_UNK func_0012ec88(s32, s32);
void func_001294f0(void *arg0) {
    func_0012ec88(M2C_FIELD(arg0, s32 *, 0), M2C_FIELD(arg0, s32 *, 4));
}

/* func_00129510 (from hand/text_00120000_h5.c). */
typedef struct S178 { u8 pad[0x178]; s32 f178; } S178;
void func_00129510(Arg *p) {
    if (((S178 *)p[0].p)->f178 == 0) p[0].i = 0;
    else p[0].i = 1;
}

/* func_00129530 (from auto/text_00120000_11.c). */
void func_00129530(void *arg0) {
    s32 sp[4];
    void *temp_s0;

    temp_s0 = M2C_FIELD(arg0, void **, 0);
    PlatVu0CopyVector(sp, M2C_FIELD(arg0, s32 *, 4));
    M2C_FIELD(temp_s0, f32 *, 0x150) = atan2f(M2C_FIELD(sp, f32 *, 0x0), M2C_FIELD(sp, f32 *, 0x8));
}

/* func_00129570 (from auto/text_00120000.c). */
s32 func_00124218(s32);
void func_00129570(s32 *arg0) {
    *arg0 = func_00124218(*arg0);
}

/* func_001295a0 (from hand/text_00120000_h5.c). */
extern f32 func_00142e30(s32, s32, s32);
void func_001295a0(Arg *p) {
    p[0].f = func_00142e30(p[0].i, p[1].i, p[2].i);
}

/* func_001295d8 (from hand/text_00120000_h5.c). */
extern f32 func_00131a68(s32, s32);
void func_001295d8(Arg *p) {
    p[0].f = func_00131a68(p[0].i, p[1].i);
}

/* func_00129608 (from auto/text_00120000.c). */
s32 func_001349d0(s32, s32);
void func_00129608(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0) = func_001349d0(M2C_FIELD(arg0, s32 *, 0), M2C_FIELD(arg0, s32 *, 4));
}

/* func_00129638 (from auto/text_00120000.c). */
M2C_UNK func_0014a380(s32, s32);
void func_00129638(void *arg0) {
    func_0014a380(M2C_FIELD(arg0, s32 *, 0), M2C_FIELD(arg0, s32 *, 4));
    M2C_FIELD(arg0, s32 *, 0) = 0;
}

/* func_00129668 (from hand/text_00120000_h5.c). */
extern void func_00138a20(s32, f32, s32);
void func_00129668(Arg *p) {
    func_00138a20(p[0].i, p[1].f, p[2].i);
}

/* func_00129690 (from auto/text_00120000_8.c). */
s32 func_00122ff8(void *);
void func_00129690(void **arg0) {
    if (func_00122ff8(*arg0) != 0) {
        *arg0 = M2C_FIELD(*arg0, void **, 0x164);
        return;
    }
    *arg0 = (void *)0xFFF;
}

/* func_001296d8 (from auto/text_00120000.c). */
void func_001296d8(void) {

}

/* func_001296e0 (from auto/text_00120000_8.c). */
M2C_UNK func_00131c28(s32, f32);
void func_001296e0(void *arg0) {
    func_00131c28(M2C_FIELD(arg0, s32 *, 0), M2C_FIELD(arg0, f32 *, 4));
}

/* func_00129700 (from auto/text_00120000_8.c). */
s32 func_00123158(s32, s32);
void func_00129700(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0) = func_00123158(M2C_FIELD(arg0, s32 *, 0), M2C_FIELD(arg0, s32 *, 4));
}

/* func_00129730 (from hand/text_00120000_h5.c). */
typedef struct S24 { u8 pad[0x24]; f32 f24; } S24;
typedef struct S18 { u8 pad[0x18]; S24 *f18; } S18;
typedef struct S14cA { u8 pad[0x14c]; S18 *f14c; } S14cA;
void func_00129730(Arg *p) {
    p[0].f = ((S14cA *)p[0].p)->f14c->f18->f24;
}

/* func_00129748 (from auto/text_00120000.c). */
s32 func_00148a40(s32, s32);
void func_00129748(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0) = func_00148a40(M2C_FIELD(arg0, s32 *, 0), M2C_FIELD(arg0, s32 *, 4));
}

/* func_00129778 (from auto/text_00120000.c). */
s32 func_0012ef30(s32, s32, s32, f32);
void func_00129778(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0) = func_0012ef30(M2C_FIELD(arg0, s32 *, 0), M2C_FIELD(arg0, s32 *, 4), M2C_FIELD(arg0, s32 *, 8), M2C_FIELD(arg0, f32 *, 0xC));
}

/* func_001297b0 (from auto/text_00120000_8.c). */
M2C_UNK func_0014d428(s32, s32, f32, f32);
void func_001297b0(void *arg0) {
    func_0014d428(M2C_FIELD(arg0, s32 *, 0), M2C_FIELD(arg0, s32 *, 4), M2C_FIELD(arg0, f32 *, 8), M2C_FIELD(arg0, f32 *, 0xC));
}

/* func_001297d8 (from auto/text_00120000_8.c). */
void func_001297d8(void *arg0) {
    M2C_FIELD(M2C_FIELD(arg0, void **, 0), s32 *, 0x3D0) = (s32) (M2C_FIELD(arg0, s32 *, 4) - 3);
}

/* func_001297f0 (from auto/text_00120000.c). */
s32 func_0014efe0(s32, s32);
void func_001297f0(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0) = func_0014efe0(M2C_FIELD(arg0, s32 *, 0), M2C_FIELD(arg0, s32 *, 4));
}

/* func_00129820 (from auto/text_00120000.c). */
s32 func_0014ee88(s32);
void func_00129820(s32 *arg0) {
    *arg0 = func_0014ee88(*arg0);
}

/* func_00129850 (from auto/text_00120000_8.c). */
M2C_UNK func_00123a88(s32, s32);
void func_00129850(void *arg0) {
    func_00123a88(M2C_FIELD(M2C_FIELD(arg0, void **, 0), s32 *, 4), M2C_FIELD(arg0, s32 *, 4));
}

/* func_00129870 (from auto/text_00120000_8.c). */
void func_00129870(void) {

}

/* func_00129878 (from auto/text_00120000_8.c). */
M2C_UNK func_0014f658(s32, s32);
void func_00129878(void *arg0) {
    func_0014f658(M2C_FIELD(arg0, s32 *, 0), M2C_FIELD(arg0, s32 *, 4));
}

/* func_00129898 (from hand/text_00120000_h5.c). */
typedef struct S3d4 { u8 pad[0x3d4]; f32 f3d4; } S3d4;
void func_00129898(Arg *p) {
    p[0].f = ((S3d4 *)p[0].p)->f3d4;
}

/* func_001298a8 (from auto/text_00120000.c). */
s32 func_00142b30(s32, s32);
void func_001298a8(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0) = func_00142b30(M2C_FIELD(arg0, s32 *, 0), M2C_FIELD(arg0, s32 *, 4));
}

/* func_001298d8 (from auto/text_00120000.c). */
s32 func_00142c80(s32, s32);
void func_001298d8(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0) = func_00142c80(M2C_FIELD(arg0, s32 *, 0), M2C_FIELD(arg0, s32 *, 4));
}

/* func_00129908 (from hand/text_00120000_h5.c). */
typedef struct B370 { u8 pad[0x370]; u64 lo:37; u64 b37:2; u64 hi:25; } B370;
void func_00129908(Arg *p) {
    B370 *e = p[0].p;
    e->b37 = p[1].u;
}

/* func_00129940 (from auto/text_00120000_8.c). */
M2C_UNK func_00135978(s32, s32, s32);
void func_00129940(void *arg0) {
    func_00135978(M2C_FIELD(arg0, s32 *, 0), M2C_FIELD(arg0, s32 *, 4), M2C_FIELD(arg0, s32 *, 8));
}

/* func_00129968 (from auto/text_00120000_8.c). */
M2C_UNK func_001359c0(s32, s32, s32);
void func_00129968(void *arg0) {
    func_001359c0(M2C_FIELD(arg0, s32 *, 0), M2C_FIELD(arg0, s32 *, 4), M2C_FIELD(arg0, s32 *, 8));
}

/* func_00129990 (from auto/text_00120000_8.c). */
s32 func_0014f5c8(s32);
s32 func_0014f600(s32);
void func_00129990(s32 *arg0) {
    s32 var_s1;

    var_s1 = 0;
    if ((func_0014f5c8(*arg0) != 0) || (func_0014f600(*arg0) != 0)) {
        var_s1 = 1;
    }
    *arg0 = var_s1;
}

/* func_001299e8 (from auto/text_00120000.c). */
s32 func_00148b70(s32, s32, s32, f32);
void func_001299e8(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0) = func_00148b70(M2C_FIELD(arg0, s32 *, 0), M2C_FIELD(arg0, s32 *, 4), M2C_FIELD(arg0, s32 *, 8), M2C_FIELD(arg0, f32 *, 0xC));
}

/* func_00129a20 (from auto/text_00120000_8.c). */
M2C_UNK func_00148d18(s32, s32, f32);
void func_00129a20(void *arg0) {
    func_00148d18(M2C_FIELD(arg0, s32 *, 0), M2C_FIELD(arg0, s32 *, 4), M2C_FIELD(arg0, f32 *, 8));
}

/* func_00129a48 (from auto/text_00120000_8.c). */
M2C_UNK func_00148d50(s32, s32, s32, f32, f32);
void func_00129a48(void *arg0) {
    func_00148d50(M2C_FIELD(arg0, s32 *, 0), M2C_FIELD(arg0, s32 *, 4), M2C_FIELD(arg0, s32 *, 8), M2C_FIELD(arg0, f32 *, 0xC), M2C_FIELD(arg0, f32 *, 0x10));
}

/* func_00129a78 (from auto/text_00120000_8.c). */
s32 func_00148b98(s32, s32, s32);
void func_00129a78(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0) = func_00148b98(M2C_FIELD(arg0, s32 *, 0), M2C_FIELD(arg0, s32 *, 4), M2C_FIELD(arg0, s32 *, 8) | 0x1000);
}

/* func_00129ab0 (from auto/text_00120000_8.c). */
M2C_UNK func_00148db0(s32, s32, s32, f32);
void func_00129ab0(void *arg0) {
    func_00148db0(M2C_FIELD(arg0, s32 *, 0), M2C_FIELD(arg0, s32 *, 4), M2C_FIELD(arg0, s32 *, 8) | 0x1000, M2C_FIELD(arg0, f32 *, 0xC));
}

/* func_00129ae0 (from auto/text_00120000_8.c). */
void func_00129ae0(void *arg0) {
    void *temp_a1;

    temp_a1 = M2C_FIELD(arg0, void **, 0);
    M2C_FIELD(temp_a1, s32 *, 0x1CC) = (s32) (M2C_FIELD(temp_a1, s32 *, 0x1CC) | M2C_FIELD(arg0, s32 *, 4));
}

/* func_00129af8 (from auto/text_00120000.c). */
void func_00129af8(void *arg0) {
    void *temp_a1;

    temp_a1 = M2C_FIELD(arg0, void **, 0);
    M2C_FIELD(temp_a1, s32 *, 0x1CC) = (s32) (M2C_FIELD(temp_a1, s32 *, 0x1CC) & ~M2C_FIELD(arg0, s32 *, 4));
}

/* func_00129b18 (from auto/text_00120000_8.c). */
void func_00131498(s32, s32);
void func_00129b18(s32 arg0) {
    s32 temp_a2;
    void *temp_v0;

    temp_v0 = M2C_FIELD(arg0, void **, 4);
    temp_a2 = M2C_FIELD(M2C_FIELD(arg0, void **, 0), s32 *, 0x1DC);
    func_00131498((s32) temp_v0, temp_a2 + M2C_FIELD(((M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x130), u16 *, 0x4C) * 4) + temp_a2), s32 *, 4));
}

/* func_00129b58 (from auto/text_00120000_8.c). */
void func_00129b58(void **arg0) {
    *arg0 = (void *) M2C_FIELD(M2C_FIELD(*arg0, void **, 0x130), u16 *, 0x4C);
}

/* func_00129b70 (from auto/text_00120000_9.c). */
M2C_UNK func_001318e8(s32, s32, void *);
void func_00129b70(void *arg0) {
    s32 sp[16];
    func_001318e8(M2C_FIELD(arg0, s32 *, 0), M2C_FIELD(arg0, s32 *, 8) | 0x1000, sp);
    PlatVu0ApplyMatrix(M2C_FIELD(arg0, s32 *, 0xC), sp, M2C_FIELD(arg0, s32 *, 4));
}

/* func_00129bb8 (from auto/text_00120000.c). */
void func_00129bb8(void *arg0) {
    void *temp_a2;

    temp_a2 = M2C_FIELD(arg0, void **, 0);
    M2C_FIELD(temp_a2, s32 *, 0x3A4) = (s32) (M2C_FIELD(temp_a2, s32 *, 0x3A4) | M2C_FIELD(arg0, s32 *, 4));
    M2C_FIELD(temp_a2, s32 *, 0x3A8) = (s32) (M2C_FIELD(temp_a2, s32 *, 0x3A8) | M2C_FIELD(arg0, s32 *, 8));
    M2C_FIELD(temp_a2, s32 *, 0x3AC) = (s32) (M2C_FIELD(temp_a2, s32 *, 0x3AC) | M2C_FIELD(arg0, s32 *, 0xC));
}

/* func_00129bf0 (from auto/text_00120000.c). */
void func_00129bf0(void *arg0) {
    void *temp_a2;

    temp_a2 = M2C_FIELD(arg0, void **, 0);
    M2C_FIELD(temp_a2, s32 *, 0x3A4) = (s32) (M2C_FIELD(temp_a2, s32 *, 0x3A4) & ~M2C_FIELD(arg0, s32 *, 4));
    M2C_FIELD(temp_a2, s32 *, 0x3A8) = (s32) (M2C_FIELD(temp_a2, s32 *, 0x3A8) & ~M2C_FIELD(arg0, s32 *, 8));
    M2C_FIELD(temp_a2, s32 *, 0x3AC) = (s32) (M2C_FIELD(temp_a2, s32 *, 0x3AC) & ~M2C_FIELD(arg0, s32 *, 0xC));
}

/* func_00129c38 (from auto/text_00120000_8.c). */
void func_00129c38(void *arg0) {
    s32 temp_a1;

    temp_a1 = M2C_FIELD(arg0, s32 *, 0);
    PlatVu0SubVector(M2C_FIELD(arg0, s32 *, 4), temp_a1 + 0x10, temp_a1 + 0x490);
}

/* func_00129c60 (from auto/text_00120000_8.c). */
M2C_UNK func_0012ec60(s32, s32, s32);
void func_00129c60(void *arg0) {
    func_0012ec60(M2C_FIELD(arg0, s32 *, 0), M2C_FIELD(arg0, s32 *, 4), M2C_FIELD(arg0, s32 *, 8));
}

/* func_00129c88 (from auto/text_00120000_9.c). */
#define func_00122ff8 ((s32 (*)(s32)) func_00122ff8)
void func_00129c88(s32 *arg0) {
    *arg0 = func_00122ff8(*arg0);
}
#undef func_00122ff8

/* func_00129cb8 (from auto/text_00120000_8.c). */
M2C_UNK func_0014f948(s32, s32);
void func_00129cb8(void *arg0) {
    func_0014f948(M2C_FIELD(arg0, s32 *, 0), M2C_FIELD(arg0, s32 *, 4));
}

/* func_00129cd8 (from auto/text_00120000_8.c). */
void func_00129cd8(void *arg0) {
    M2C_FIELD(M2C_FIELD(M2C_FIELD(arg0, void **, 0), void **, 0x130), f32 *, 0x18) = (f32) M2C_FIELD(arg0, f32 *, 4);
}

/* func_00129cf0 (from auto/text_00120000_3.c). */
void func_00129cf0(void *arg0) {
    M2C_FIELD(M2C_FIELD(M2C_FIELD(arg0, void **, 0), void **, 0x6C), f32 *, 0xCC) = (f32) ((M2C_FIELD(arg0, f32 *, 4) / 180.0f) * 3.141592979f);
}

/* func_00129d28 (from auto/text_00120000_8.c). */
M2C_UNK func_001358b8(s32, s32);
void func_00129d28(void *arg0) {
    func_001358b8(M2C_FIELD(arg0, s32 *, 0), M2C_FIELD(arg0, s32 *, 4));
}

/* func_00129d48 (from auto/text_00120000_8.c). */
M2C_UNK func_001358f8(s32, s32);
void func_00129d48(void *arg0) {
    func_001358f8(M2C_FIELD(arg0, s32 *, 0), M2C_FIELD(arg0, s32 *, 4));
}

/* func_00129d68 (from auto/text_00120000_11.c). */
void func_00129d68(void **arg0) {
    void *temp_a1;

    temp_a1 = *arg0;
    M2C_FIELD(temp_a1, s64 *, 0x370) = (s64) (M2C_FIELD(temp_a1, s64 *, 0x370) | ((s64) 0x8000 << 0x24));
}

/* func_00129d88 (from auto/text_00120000.c). */
void func_00129d88(void **arg0) {
    *arg0 = (void *) M2C_FIELD(M2C_FIELD(*arg0, void **, 0x130), u8 *, 0x5A);
}

/* func_00129da0 (from auto/text_00120000_8.c). */
M2C_UNK func_00131a30(s32, s32, s32);
void func_00129da0(void *arg0) {
    func_00131a30(M2C_FIELD(arg0, s32 *, 0), M2C_FIELD(arg0, s32 *, 4), M2C_FIELD(arg0, s32 *, 8));
}

/* func_00129dc8 (from hand/text_00120000_h5.c). */
typedef struct FV { f32 f0, f4, f8, f0c; } FV;
typedef struct S3c0 { u8 pad[0x3c0]; u8 f3c0[16]; } S3c0;
#define func_0014f658 ((void (*)(void *, s32)) func_0014f658)
void func_00129dc8(Arg *p) {
    func_0014f658(p[0].p, 4);
    PlatVu0ScaleVectorXYZ(((S3c0 *)p[0].p)->f3c0, p[1].p, ((FV *)p[1].p)->f0c);
}
#undef func_0014f658

/* func_00129e08 (from auto/text_00120000_8.c). */
M2C_UNK func_00135a10(s32, s32);
void func_00129e08(void *arg0) {
    func_00135a10(M2C_FIELD(arg0, s32 *, 0), M2C_FIELD(arg0, s32 *, 4));
}

/* func_00129e28 (from auto/text_00120000_8.c). */
M2C_UNK func_00135a38(s32, s32);
void func_00129e28(void *arg0) {
    func_00135a38(M2C_FIELD(arg0, s32 *, 0), M2C_FIELD(arg0, s32 *, 4));
}

/* func_00129e48 (from hand/text_00120000_h5.c). */
extern s32 func_0012f1d0(void *, s32);
void func_00129e48(Arg *p) {
    u8 buf[16];
    if (D_002E26A0[0] == 0) {
        p[0].i = 1;
        return;
    }
    func_001315c0(D_002E26A0[0], 0, 1.0f, buf);
    p[0].i = func_0012f1d0(buf, p[0].i) == 0;
}

/* func_00129ea8 (from auto/text_00120000.c). */
s32 func_001233e8(s32);
void func_00129ea8(s32 *arg0) {
    *arg0 = func_001233e8(*arg0);
}

/* func_00129ed8 (from hand/text_00120000_h5.c). */
typedef struct E1 {
    u8 pad0[0x30];
    FV f30;
    u8 pad40[0xd0 - 0x40];
    f32 fd0[4][4];
    u8 pad110[0x1cc - 0x110];
    s32 f1cc;
    u8 pad1d0[0x450 - 0x1d0];
    FV f450;
} E1;
void func_00129ed8(Arg *p) {
    E1 *e = p[0].p;
    if (e->f1cc & 8) {
        PlatVu0CopyVector(p[1].p, &e->f450);
        ((FV *)p[1].p)->f0c = 0;
        PlatVu0ApplyMatrix(p[1].p, e->fd0, p[1].p);
        return;
    }
    PlatVu0CopyVector(p[1].p, &e->f30);
}

/* func_00129f50 (from auto/text_00120000_8.c). */
M2C_UNK func_00137440(s32, s32);
void func_00129f50(void *arg0) {
    func_00137440(M2C_FIELD(arg0, s32 *, 0), M2C_FIELD(arg0, s32 *, 4));
}

/* func_00129f70 (from auto/text_00120000_8.c). */
void func_00129f70(void **arg0) {
    void *temp_v0;
    void *var_v1;

    temp_v0 = M2C_FIELD(*arg0, void **, 0x398);
    var_v1 = (void *)-1;
    if (temp_v0 != NULL) {
        var_v1 = M2C_FIELD(temp_v0, void **, 4);
    }
    *arg0 = var_v1;
}

/* func_00129f90 (from auto/text_00120000_8.c). */
M2C_UNK func_001366d8(s32, s32, s32);
void func_00129f90(void *arg0) {
    func_001366d8(M2C_FIELD(arg0, s32 *, 0), M2C_FIELD(arg0, s32 *, 4), M2C_FIELD(arg0, s32 *, 8));
}

/* func_00129fb8 (from auto/text_00120000_8.c). */
s32 func_00137618(s32);
void func_00129fb8(s32 *arg0) {
    *arg0 = func_00137618(*arg0);
}

/* func_00129fe8 (from auto/text_00120000_8.c). */
M2C_UNK func_00137448(s32);
void func_00129fe8(s32 *arg0) {
    func_00137448(*arg0);
}

/* func_0012a000 (from auto/text_00120000_8.c). */
s32 func_001477e0(s32);
void func_0012a000(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0) = func_001477e0(M2C_FIELD(arg0, s32 *, 4));
}

/* func_0012a030 (from hand/text_00120000.c). */
void func_0012a030(s32 *slot) {
    *slot = (s32) (M2C_FIELD(*slot, u64 *, 0x370) >> 35) & 1;
}

/* func_0012a048 (from auto/text_00120000_8.c). */
M2C_UNK func_00157818(s32, s32);
void func_0012a048(void *arg0) {
    func_00157818(M2C_FIELD(arg0, s32 *, 0), M2C_FIELD(arg0, s32 *, 4));
}

/* func_0012a068 (from hand/text_00120000_h5.c). */
#define func_0014f658 ((void (*)(void *, s32)) func_0014f658)
void func_0012a068(Arg *p) {
    func_0014f658(p[0].p, 7);
    PlatVu0ScaleVectorXYZ(((S3c0 *)p[0].p)->f3c0, p[1].p, ((FV *)p[1].p)->f0c);
}
#undef func_0014f658

/* func_0012a0a8 (from hand/text_00120000_h5.c). */
typedef struct Ent {
    union {
        u64 flags; /* 0x000 */
        u8 b[8];
    };
    u8 pad008[0x134 - 8];
    u8 *info; /* 0x134 */
    u8 pad138[0x370 - 0x138];
    u64 f370; /* bits 37-38: 2-bit state */
    u8 pad378[0x3a0 - 0x378];
    s32 f3a0;
    u8 pad3a4[4];
    s32 f3a8;
} Ent;
void func_0012a0a8(Arg *p) {
    Ent *e = p[0].p;
    p[0].i = e ? (s32)(e->f370 >> 37) & 3 : 0;
}

/* func_0012a0c8 (from auto/text_00120000.c). */
s32 func_00131b08(s32);
void func_0012a0c8(s32 *arg0) {
    *arg0 = func_00131b08(*arg0);
}

/* func_0012a0f8 (from auto/text_00120000.c). */
void func_0012a0f8(void **arg0) {
    *arg0 = (void *) M2C_FIELD(M2C_FIELD(*arg0, void **, 0x130), u16 *, 0x4E);
}

/* func_0012a110 (from auto/text_00120000.c). */
void func_0012a110(void *arg0) {
    M2C_FIELD(M2C_FIELD(M2C_FIELD(arg0, void **, 0), void **, 0x6C), u8 *, 0xBD) = (u8) M2C_FIELD(arg0, u8 *, 4);
}

/* func_0012a128 (from auto/text_00120000.c). */
s32 func_00157528(s32);
void func_0012a128(s32 *arg0) {
    *arg0 = func_00157528(*arg0);
}

/* func_0012a158 (from auto/text_00120000_8.c). */
M2C_UNK func_00157648(s32);
void func_0012a158(s32 *arg0) {
    func_00157648(*arg0);
}

/* func_0012a170 (from auto/text_00120000_8.c). */
M2C_UNK func_00157978(s32, s32, f32);
void func_0012a170(void *arg0) {
    func_00157978(M2C_FIELD(arg0, s32 *, 0), M2C_FIELD(arg0, s32 *, 4), M2C_FIELD(arg0, f32 *, 8));
}

/* func_0012a198 (from auto/text_00120000_11.c). */
extern s32 D_00350D80;
void func_0012a198(void **arg0) {
    void *temp_a3;

    temp_a3 = *arg0;
    if (!(((u64) M2C_FIELD(temp_a3, u64 *, 0x370) >> 0x36) & 1)) {
        D_00350D80 -= M2C_FIELD(M2C_FIELD(temp_a3, void **, 0x130), u8 *, 0x59);
        M2C_FIELD(temp_a3, u64 *, 0x370) = (u64) (M2C_FIELD(temp_a3, u64 *, 0x370) | ((s64) 0x8000 << 0x27));
    }
}

/* func_0012a1e8 (from auto/text_00120000.c). */
void func_0012a1e8(void **arg0) {
    *arg0 = (void *) M2C_FIELD(*arg0, u8 *, 0x39E);
}

/* func_0012a1f8 (from hand/text_00120000_h5.c). */
extern f32 func_00132f00(s32);
void func_0012a1f8(Arg *p) {
    p[0].f = func_00132f00(p[0].i);
}

/* func_0012a228 (from auto/text_00120000.c). */
void func_0012a228(void **arg0) {
    *arg0 = (void *) M2C_FIELD(M2C_FIELD(*arg0, void **, 0x130), u8 *, 0x58);
}

/* func_0012a240 (from auto/text_00120000_16.c). */
s32 func_001425d0(s32);
void func_0012a240(void *arg0) {
  s32 temp_s0;
  s32 new_var;
  s32 temp_s0_2;
  temp_s0 = *((s32 *) (((s8 *) arg0) + 0));
  new_var = func_001425d0(temp_s0);
  temp_s0_2 = temp_s0 + 0x120;
  if (new_var == 0)
  {
    PlatVu0AddVector(temp_s0_2, temp_s0_2, *((s32 *) (((s8 *) arg0) + 4)));
  }
}

/* func_0012a2a0 (from hand/text_00120000_h5.c). */
typedef struct S284 { u8 pad[0x284]; f32 f284; } S284;
void func_0012a2a0(Arg *p) {
    p[0].f = ((S284 *)p[0].p)->f284;
}

/* func_0012a2b0 (from hand/text_00120000_h5.c). */
typedef struct S4c { u8 pad[0x4c]; u16 f4c; } S4c;
extern s32 func_0013c318(s32);
extern void func_002414a8(s32, s32);
extern void func_00153d88(void *);
typedef struct E2 {
    s32 w0;
    u8 pad004[0x130 - 4];
    S4c *f130;
    u8 pad134[0x370 - 0x134];
    union { u64 v; u8 b[8]; } f370;
    u8 pad378[0x3b0 - 0x378];
    s32 f3b0;
    u8 pad3b4[0x3c0 - 0x3b4];
    u8 f3c0[16];
} E2;
#define func_0014f658 ((void (*)(void *, s32)) func_0014f658)
#define func_001358b8 ((void (*)(void *, s32)) func_001358b8)
void func_0012a2b0(Arg *p) {
    E2 *e = p[0].p;
    e->w0 |= 0x240;
    func_001358b8(e, 10);
    func_0014f658(e, 8);
    PlatVu0CopyVector(e->f3c0, &D_002C58B0);
    e->f3b0 = 0;
    e->f370.v |= 1ULL << 60;
    func_002414a8(func_0013c318(e->f130->f4c), 3);
    func_00153d88(e);
}
#undef func_0014f658
#undef func_001358b8

/* func_0012a338 (from auto/text_00120000_11.c). */
void func_0012a338(void **arg0) {
    void *temp_a1;

    temp_a1 = *arg0;
    M2C_FIELD(temp_a1, s64 *, 0x370) = (s64) (M2C_FIELD(temp_a1, s64 *, 0x370) | ((s64) 0x8000 << 0x25));
}

/* func_0012a358 (from auto/text_00120000.c). */
s32 func_00148968(s32, s32, s32);
void func_0012a358(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0) = func_00148968(M2C_FIELD(arg0, s32 *, 0), M2C_FIELD(arg0, s32 *, 4), M2C_FIELD(arg0, s32 *, 8));
}

/* func_0012a390 (from auto/text_00120000_15.c). */
s32 func_00142388(s32, s32);
void func_00142470(s32, s32);
#define func_001315c0 ((void (*)(s32, s32, s32, f32)) func_001315c0)
void func_0012a390(s32 arg0) {
    s32 sp[8];    s32 temp_s0;

    temp_s0 = *(M2C_UNK *)arg0;
    func_001315c0(temp_s0, 0x8003, (s32) sp, 0.0f);
    func_00142388((s32) sp, (s32) &M2C_FIELD(sp, M2C_UNK *, 0x10));
    func_00142470(temp_s0, (s32) &M2C_FIELD(sp, M2C_UNK *, 0x10));
    M2C_FIELD(temp_s0, s64 *, 0x370) = (s64) (M2C_FIELD(temp_s0, s64 *, 0x370) | ((s64) 0x8000 << 0x25));
}
#undef func_001315c0

/* func_0012a400 (from auto/text_00120000.c). */
M2C_UNK D_00F20000(M2C_UNK, s32);
void func_0012a400(s32 *arg0) {
    if (((u32) D_002C5958 >> 0xD) & 1) {
        D_00F20000(6, *arg0);
    }
}

/* func_0012a448 (from auto/text_00120000.c). */
void func_0012a448(s32 *arg0) {
    s32 var_s1;

    var_s1 = 0;
    if (func_0014f5c8(*arg0) == 0) {
        var_s1 = func_0014f600(*arg0) == 0;
    }
    *arg0 = var_s1;
}

/* func_0012a498 (from auto/text_00120000_8.c). */
M2C_UNK func_00135848(s32);
M2C_UNK func_00135870(s32);
void func_0012a498(void *arg0) {
    if (M2C_FIELD(arg0, s32 *, 4) != 0) {
        func_00135848(M2C_FIELD(arg0, s32 *, 0));
        return;
    }
    func_00135870(M2C_FIELD(arg0, s32 *, 0));
}

/* func_0012a4c8 (from auto/text_00120000_8.c). */
s32 func_00148a60(s32, s32);
void func_0012a4c8(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0) = func_00148a60(M2C_FIELD(arg0, s32 *, 0), M2C_FIELD(arg0, s32 *, 4));
}

/* func_0012a4f8 (from auto/text_00120000.c). */
s32 func_00147c98(s32, s32, s32);
void func_0012a4f8(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0) = func_00147c98(M2C_FIELD(arg0, s32 *, 0), M2C_FIELD(arg0, s32 *, 4), M2C_FIELD(arg0, s32 *, 8));
}

/* func_0012a530 (from auto/text_00120000_9.c). */
void func_0012a530(void *arg0) {
    PlatVu0CopyVector(*M2C_FIELD(arg0, s32 **, 0), M2C_FIELD(arg0, s32 *, 4));
}

/* func_0012a550 (from auto/text_00120000_8.c). */
M2C_UNK func_00176340(s32);
void func_0012a550(s32 *arg0) {
    func_00176340(*arg0);
}

/* func_0012a568 (from auto/text_00120000_8.c). */
s32 func_00148768(s32, s32, s32, s32, f32);
void func_0012a568(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0) = func_00148768(M2C_FIELD(arg0, s32 *, 0), M2C_FIELD(arg0, s32 *, 4), M2C_FIELD(arg0, s32 *, 8), M2C_FIELD(arg0, s32 *, 0xC), M2C_FIELD(arg0, f32 *, 0x10));
}

/* func_0012a5a8 (from auto/text_00120000_8.c). */
M2C_UNK func_00147f88(s32, f32);
void func_0012a5a8(void *arg0) {
    func_00147f88(M2C_FIELD(arg0, s32 *, 0), M2C_FIELD(arg0, f32 *, 4));
}

/* func_0012a5c8 (from auto/text_00120000_8.c). */
M2C_UNK func_00120ef0(s32, void *, s32);
void func_0012a5c8(void *arg0) {
    s32 sp[16];
    PlatVu0InversMatrix(sp, ((M2C_UNK *)&D_002E2700));
    func_00120ef0(M2C_FIELD(arg0, s32 *, 0), sp, M2C_FIELD(arg0, s32 *, 4));
}

/* func_0012a608 (from auto/text_00120000_9.c). */
void func_0012a608(void *arg0) {
    PlatVu0CopyVector(M2C_FIELD(M2C_FIELD(arg0, void **, 0), s32 *, 8), M2C_FIELD(arg0, s32 *, 4));
}

/* func_0012a628 (from hand/text_00120000_h5.c). */
typedef struct S4p { u8 pad[4]; Arg *f4; } S4p;
void func_0012a628(Arg *p) {
    f32 *v = p[1].p;
    S4p *o = p[0].p;
    o->f4[0].i = (s32)(v[0] / 6.2831855f * 65536.0f) & 0xffff;
    o->f4[1].i = (s32)(v[1] / 6.2831855f * 65536.0f) & 0xffff;
    o->f4[2].i = (s32)(v[2] / 6.2831855f * 65536.0f) & 0xffff;
}

/* func_0012a6c0 (from auto/text_00120000_9.c). */
void func_0012a6c0(f32 *arg0) {
    *arg0 = atan2f(D_002E2700[0][2], D_002E2700[2][2]);
}

/* func_0012a6f8 (from auto/text_00120000_8.c). */
M2C_UNK func_00147d50(s32, s32);
void func_0012a6f8(void *arg0) {
    func_00147d50(M2C_FIELD(arg0, s32 *, 0), M2C_FIELD(arg0, s32 *, 4));
}

/* func_0012a718 (from auto/text_00120000_8.c). */
s32 func_00147ed8(s32, s32, s32, s32);
void func_0012a718(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0) = func_00147ed8(M2C_FIELD(arg0, s32 *, 0), M2C_FIELD(arg0, s32 *, 4), M2C_FIELD(arg0, s32 *, 8), M2C_FIELD(arg0, s32 *, 0xC));
}

/* func_0012a750 (from auto/text_00120000.c). */
M2C_UNK func_00176310(s32);
void func_0012a750(s32 *arg0) {
    s32 temp_v0;

    temp_v0 = *arg0;
    if (temp_v0 != 0) {
        func_00176310(temp_v0);
    }
    *arg0 = 0;
}

/* func_0012a788 (from auto/text_00120000_8.c). */
M2C_UNK func_0012bd00(s32, s32);
void func_0012a788(void *arg0) {
    func_0012bd00(M2C_FIELD(arg0, s32 *, 0), M2C_FIELD(arg0, s32 *, 4));
}

/* func_0012a7a8 (from auto/text_00120000_8.c). */
M2C_UNK func_001486b0(s32, s32, s32);
void func_0012a7a8(void *arg0) {
    func_001486b0(M2C_FIELD(arg0, s32 *, 0), M2C_FIELD(arg0, s32 *, 4), M2C_FIELD(arg0, s32 *, 8));
}

/* func_0012a7d0 (from auto/text_00120000_8.c). */
M2C_UNK func_00148068(s32, f32);
void func_0012a7d0(void *arg0) {
    func_00148068(M2C_FIELD(arg0, s32 *, 0), M2C_FIELD(arg0, f32 *, 4));
}

/* func_0012a7f0 (from auto/text_00120000_8.c). */
void func_0012a7f0(s32 *arg0) {
    func_00176310(*arg0);
}

/* func_0012a808 (from auto/text_00120000_8.c). */
s32 func_0014a408();
void func_0012a808(s32 *arg0) {
    *arg0 = func_0014a408();
}

/* func_0012a830 (from auto/text_00120000.c). */
void *func_0014a4a8(void *, s32, s32);
extern s32 D_00514F10_0012a830 __asm__("D_00514F10");
#define D_00514F10 D_00514F10_0012a830
void func_0012a830(void *arg0) {
    void *temp_v0;

    temp_v0 = func_0014a4a8(M2C_FIELD(arg0, void **, 0), M2C_FIELD(arg0, s32 *, 4), M2C_FIELD(arg0, s32 *, 8));
    M2C_FIELD(arg0, void **, 0) = temp_v0;
    M2C_FIELD(temp_v0, s32 *, 0xA0) = (s32) D_00514F10;
}
#undef D_00514F10

/* func_0012a870 (from auto/text_00120000.c). */
s32 func_001354b8(s32, s32);
void func_0012a870(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0) = func_001354b8(M2C_FIELD(arg0, s32 *, 0), M2C_FIELD(arg0, s32 *, 4));
}

/* func_0012a8a0 (from auto/text_00120000_8.c). */
M2C_UNK func_0014a898(s32, s32);
void func_0012a8a0(void *arg0) {
    func_0014a898(M2C_FIELD(arg0, s32 *, 0), M2C_FIELD(arg0, s32 *, 4));
}

/* func_0012a8c0 (from auto/text_00120000_13.c). */
void func_0012a8c0(void *arg0) {
    u64 wide;
    u64 *temp_a1;

    temp_a1 = M2C_FIELD(arg0, u64 **, 0);
    wide = M2C_FIELD(arg0, u32 *, 4);
    *temp_a1 = (*temp_a1 & ~0x3000) | ((wide & 3) << 0xC);
}

/* func_0012a8e8 (from auto/text_00120000_8.c). */
M2C_UNK func_00135640(s32, s32);
void func_0012a8e8(void *arg0) {
    func_00135640(M2C_FIELD(arg0, s32 *, 0), M2C_FIELD(arg0, s32 *, 4));
}

/* func_0012a908 (from auto/text_00120000_8.c). */
M2C_UNK func_00134870(s32, s32, s32);
void func_0012a908(void *arg0) {
    s32 temp_v0;

    temp_v0 = func_001354b8(M2C_FIELD(arg0, s32 *, 0), M2C_FIELD(arg0, s32 *, 4));
    if (temp_v0 != 0) {
        func_00134870(M2C_FIELD(arg0, s32 *, 4), temp_v0, M2C_FIELD(arg0, s32 *, 8));
    }
    M2C_FIELD(arg0, s32 *, 0) = temp_v0;
}

/* func_0012a958 (from auto/text_00120000_8.c). */
M2C_UNK func_0014ab78(s32);
void func_0012a958(s32 *arg0) {
    func_0014ab78(*arg0);
}

/* func_0012a970 (from hand/text_00120000_h5.c). */
typedef struct B0 {
    union {
        u64 v;
        struct { u64 lo:2; u64 b2:2; u64 hi:60; } bf;
    };
} B0;
void func_0012a970(Arg *p) {
    B0 *e = p[0].p;
    if (e && ((s32)(e->v >> 11) & 1)) e->bf.b2 = p[1].u;
}

/* func_0012a9b8 (from auto/text_00120000.c). */
void func_0012a9b8(void **arg0) {
    *arg0 = M2C_FIELD(M2C_FIELD(*arg0, void **, 0x2C), void **, 0x6C);
}

/* func_0012a9d0 (from auto/text_00120000_15.c). */
M2C_UNK func_00138a78(s32, void *);
M2C_UNK func_00139240(s32, void *, s32, f32, f32, f32);
void func_0012a9d0(void *arg0) {
    void *temp_v1;

    temp_v1 = M2C_FIELD(arg0, void **, 4);
    if ((s32) ((u64) M2C_FIELD(temp_v1, u64 *, 8) >> 0x2B) & 1) {
        func_00138a78(M2C_FIELD(arg0, s32 *, 0), temp_v1);
    }
    func_00139240(M2C_FIELD(arg0, s32 *, 0), M2C_FIELD(arg0, void **, 4), M2C_FIELD(arg0, s32 *, 8), M2C_FIELD(arg0, f32 *, 0xC), M2C_FIELD(arg0, f32 *, 0x10), M2C_FIELD(arg0, f32 *, 0x14));
    M2C_FIELD(arg0, s32 *, 0) = 0;
}

/* func_0012aa38 (from auto/text_00120000_15.c). */
M2C_UNK func_00138e58(s32, void *);
void func_0012aa38(void *arg0) {
    void *temp_v1;

    temp_v1 = M2C_FIELD(arg0, void **, 4);
    if ((s32) ((u64) M2C_FIELD(temp_v1, u64 *, 8) >> 0x2B) & 1) {
        func_00138a78(M2C_FIELD(arg0, s32 *, 0), temp_v1);
    }
    func_00138e58(M2C_FIELD(arg0, s32 *, 0), M2C_FIELD(arg0, void **, 4));
}

/* func_0012aa88 (from auto/text_00120000_15.c). */
M2C_UNK func_00138c30(s32, void *);
void func_0012aa88(void *arg0) {
    void *temp_v1;

    temp_v1 = M2C_FIELD(arg0, void **, 4);
    if ((s32) ((u64) M2C_FIELD(temp_v1, u64 *, 8) >> 0x2B) & 1) {
        func_00138a78(M2C_FIELD(arg0, s32 *, 0), temp_v1);
    }
    func_00138c30(M2C_FIELD(arg0, s32 *, 0), M2C_FIELD(arg0, void **, 4));
}

/* func_0012aad8 (from auto/text_00120000_8.c). */
M2C_UNK func_00141f10(s32, s32);
void func_0012aad8(void *arg0) {
    func_00141f10(M2C_FIELD(arg0, s32 *, 0), M2C_FIELD(arg0, s32 *, 4));
}

/* func_0012aaf8 (from hand/text_00120000_h5.c). */
extern s32 func_0013a440(s32, s32, f32, s32);
void func_0012aaf8(Arg *p) {
    p[0].i = func_0013a440(p[0].i, p[1].i, p[2].f, p[3].i);
}

/* func_0012ab30 (from auto/text_00120000_8.c). */
M2C_UNK func_00123030(s32, s32, M2C_UNK);
void func_0012ab30(void *arg0) {
    func_00123030(M2C_FIELD(arg0, s32 *, 0), M2C_FIELD(arg0, s32 *, 4), 0);
}

/* func_0012ab50 (from auto/text_00120000_8.c). */
M2C_UNK func_00139408(s32, s32);
void func_0012ab50(void *arg0) {
    func_00139408(M2C_FIELD(arg0, s32 *, 0), M2C_FIELD(arg0, s32 *, 4));
    M2C_FIELD(arg0, s32 *, 0) = 0;
}

/* func_0012ab80 (from auto/text_00120000.c). */
s32 func_001389c0(s32);
void func_0012ab80(s32 *arg0) {
    *arg0 = func_001389c0(*arg0);
}

/* func_0012abb0 (from auto/text_00120000.c). */
s32 func_001389e8(s32);
void func_0012abb0(s32 *arg0) {
    *arg0 = func_001389e8(*arg0);
}

/* func_0012abe0 (from auto/text_00120000_15.c). */
M2C_UNK func_00139170(s32, void *);
void func_0012abe0(void *arg0) {
    void *temp_v1;

    temp_v1 = M2C_FIELD(arg0, void **, 4);
    if ((s32) ((u64) M2C_FIELD(temp_v1, u64 *, 8) >> 0x2B) & 1) {
        func_00138a78(M2C_FIELD(arg0, s32 *, 0), temp_v1);
    }
    func_00139170(M2C_FIELD(arg0, s32 *, 0), M2C_FIELD(arg0, void **, 4));
}

/* func_0012ac30 (from auto/text_00120000_8.c). */
s32 func_001231b8(s32, s32);
void func_0012ac30(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0) = func_001231b8(M2C_FIELD(arg0, s32 *, 0), M2C_FIELD(arg0, s32 *, 4));
}

/* func_0012ac60 (from auto/text_00120000.c). */
s32 func_00137330(s32, s32, s32);
void func_0012ac60(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0) = func_00137330(M2C_FIELD(arg0, s32 *, 0), M2C_FIELD(arg0, s32 *, 4), M2C_FIELD(arg0, s32 *, 8));
}

/* func_0012ac98 (from auto/text_00120000_3.c). */
s32 func_001334b8(s32, s32, s32, s32, s32);
void func_0012ac98(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0) = func_001334b8(M2C_FIELD(arg0, s32 *, 0), M2C_FIELD(arg0, s32 *, 4), M2C_FIELD(arg0, s32 *, 8), M2C_FIELD(arg0, s32 *, 0xC), M2C_FIELD(arg0, s32 *, 0x10));
}

/* func_0012acd8 (from auto/text_00120000.c). */
s32 func_0013a670(s32, s32, f32, f32);
void func_0012acd8(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0) = func_0013a670(M2C_FIELD(arg0, s32 *, 0), M2C_FIELD(arg0, s32 *, 4), M2C_FIELD(arg0, f32 *, 8), M2C_FIELD(arg0, f32 *, 0xC));
}

/* func_0012ad10 (from auto/text_00120000_8.c). */
M2C_UNK func_00138870(s32);
void func_0012ad10(s32 *arg0) {
    func_00138870(*arg0);
}

/* func_0012ad28 (from auto/text_00120000_8.c). */
M2C_UNK func_00138808(s32, f32);
void func_0012ad28(void *arg0) {
    func_00138808(M2C_FIELD(arg0, s32 *, 0), M2C_FIELD(arg0, f32 *, 4));
}

/* func_0012ad48 (from auto/text_00120000_8.c). */
void func_0012ad48(void *arg0) {
    void *temp_a1;

    temp_a1 = M2C_FIELD(arg0, void **, 0);
    M2C_FIELD(temp_a1, s32 *, 0x88) = (s32) (M2C_FIELD(temp_a1, s32 *, 0x88) & ~M2C_FIELD(arg0, s32 *, 4));
    if (M2C_FIELD(arg0, s32 *, 4) & 2) {
        M2C_FIELD(temp_a1, s32 *, 0x3E4) = 0;
    }
}

/* func_0012ad78 (from auto/text_00120000.c). */
s32 func_001226f0(s32, s32, s32);
void func_0012ad78(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0) = func_001226f0(M2C_FIELD(arg0, s32 *, 0), M2C_FIELD(arg0, s32 *, 4) | 8, M2C_FIELD(arg0, s32 *, 8));
}

/* func_0012adb0 (from auto/text_00120000_8.c). */
M2C_UNK func_00122768(s32);
void func_0012adb0(s32 *arg0) {
    func_00122768(*arg0);
}

/* func_0012adc8 (from auto/text_00120000_8.c). */
M2C_UNK func_001224c8(s32, s32, M2C_UNK, f32);
void func_0012adc8(void *arg0) {
    func_001224c8(M2C_FIELD(arg0, s32 *, 0), M2C_FIELD(arg0, s32 *, 4), 0, M2C_FIELD(arg0, f32 *, 8));
}

/* func_0012adf0 (from auto/text_00120000_10.c). */
#define func_001224c8 ((M2C_UNK (*)(s32, M2C_UNK *, M2C_UNK *, f32)) func_001224c8)
void func_0012adf0(void *arg0) {
    func_001224c8(M2C_FIELD(arg0, s32 *, 0), ((M2C_UNK *)&D_002C5C60), &func_00122768, M2C_FIELD(arg0, f32 *, 4));
}
#undef func_001224c8

/* func_0012ae20 (from auto/text_00120000_8.c). */
M2C_UNK func_00142058(s32);
void func_0012ae20(s32 *arg0) {
    func_00142058(*arg0);
}

/* func_0012ae38 (from auto/text_00120000_8.c). */
M2C_UNK func_001421d0(s32, s32);
void func_0012ae38(void *arg0) {
    func_001421d0(M2C_FIELD(arg0, s32 *, 0), M2C_FIELD(arg0, s32 *, 4));
}

/* func_0012ae58 (from auto/text_00120000_8.c). */
s32 func_00142240(s32);
void func_0012ae58(s32 *arg0) {
    *arg0 = func_00142240(*arg0);
}

/* func_0012ae88 (from auto/text_00120000_8.c). */
M2C_UNK func_001473a8(s32, s32, s32);
void func_0012ae88(void *arg0) {
    func_001473a8(M2C_FIELD(arg0, s32 *, 0), M2C_FIELD(arg0, s32 *, 4), M2C_FIELD(arg0, s32 *, 8));
}

/* func_0012aeb0 (from auto/text_00120000_8.c). */
M2C_UNK func_00147338(s32, s32);
void func_0012aeb0(void *arg0) {
    func_00147338(M2C_FIELD(arg0, s32 *, 0), M2C_FIELD(arg0, s32 *, 4));
}

/* func_0012aed0 (from auto/text_00120000_8.c). */
M2C_UNK func_0011d768(M2C_UNK);
M2C_UNK func_001ec7c0(M2C_UNK);
M2C_UNK func_00242be0();
void func_0012aed0(void) {
    func_0011d768(0x41);
    func_001ec7c0(0xE);
    func_00242be0();
}

/* func_0012aef8 (from auto/text_00120000_8.c). */
M2C_UNK func_001ed560(M2C_UNK, M2C_UNK, s32);
void func_0012aef8(f32 *arg0) {
    s32 temp_f1;

    temp_f1 = (s32) (*arg0 * 4.0f);
    func_001ed560(0, 0, temp_f1);
    func_001ed560(1, 0, temp_f1);
}

/* func_0012af48 (from auto/text_00120000_8.c). */
s32 func_00142480(s32, s32, M2C_UNK, s32);
void func_0012af48(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0) = (s32) (func_00142480(M2C_FIELD(arg0, s32 *, 0), M2C_FIELD(arg0, s32 *, 4), 0, M2C_FIELD(arg0, s32 *, 8)) + 1);
}

/* func_0012af88 (from auto/text_00120000_12.c). */
M2C_UNK func_00116660(void *);
M2C_UNK func_001166e8(void *);
#define func_00121fc4 ((M2C_UNK (*)(M2C_UNK *, s32)) func_00121fc4)
void func_0012af88(void *arg0) {
  s32 sp[36];
  f32 temp_f0;
  f32 temp_f0_2;
  func_00116660(sp);
  temp_f0 = *((f32 *) (((s8 *) arg0) + 8));
  *((f32 *) (((s8 *) sp) + 0x24)) = temp_f0;
  *((f32 *) (((s8 *) sp) + 0x20)) = temp_f0;
  PlatVu0CopyVector(sp, *((M2C_UNK **) (((s8 *) arg0) + 0)));
  *((f32 *) (((s8 *) sp) + 0xC)) = 1.0f;
  func_00121fc4(&(*((M2C_UNK *) (((s8 *) sp) + 0x80))), *((s32 *) (((s8 *) arg0) + 4)));
  do
  {
    temp_f0_2 = *((f32 *) (((s8 *) arg0) + 8));
    if (temp_f0_2 < (*((f32 *) (((s8 *) sp) + 0x8C))))
    {
      PlatVu0ScaleVector(&(*((M2C_UNK *) (((s8 *) sp) + 0x10))), &(*((M2C_UNK *) (((s8 *) sp) + 0x80))), temp_f0_2);
      *((f32 *) (((s8 *) sp) + 0x8C)) -= *((f32 *) (((s8 *) arg0) + 8));
    }
    else
    {
      PlatVu0ScaleVector(&(*((M2C_UNK *) (((s8 *) sp) + 0x10))), &(*((M2C_UNK *) (((s8 *) sp) + 0x80))), *((f32 *) (((s8 *) sp) + 0x8C)));
      *((f32 *) (((s8 *) sp) + 0x8C)) = 0.0f;
    }
    *((f32 *) (((s8 *) sp) + 0x1C)) = 1.0f;
    *((s32 *) (((s8 *) sp) + 0x28)) = 1;
    func_001166e8(sp);
    PlatVu0CopyVector(sp, &(*((M2C_UNK *) (((s8 *) sp) + 0x40))));
  }
  while ((*((f32 *) (((s8 *) sp) + 0x8C))) > 0.0f);
  PlatVu0CopyVector(*((void **) (((s8 *) arg0) + 0xC)), &(*((M2C_UNK *) (((s8 *) sp) + 0x40))));
  *((M2C_UNK **) (((s8 *) arg0) + 0)) = (M2C_UNK *) ((*((M2C_UNK *) (((s8 *) sp) + 0x30))) & 1);
}
#undef func_00121fc4

/* func_0012b0c0 (from auto/text_00120000.c). */
#define func_00142480 ((s32 (*)(s32, s32, s32, s32)) func_00142480)
void func_0012b0c0(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0) = (s32) (func_00142480(M2C_FIELD(arg0, s32 *, 0), M2C_FIELD(arg0, s32 *, 4), M2C_FIELD(arg0, s32 *, 8), M2C_FIELD(arg0, s32 *, 0xC)) + 1);
}
#undef func_00142480

/* func_0012b100 (from auto/text_00120000.c). */
s32 func_0015bd78(s32, s32, M2C_UNK);
void func_0012b100(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0) = func_0015bd78(M2C_FIELD(arg0, s32 *, 0), M2C_FIELD(arg0, s32 *, 4), 0);
}

/* func_0012b138 (from auto/text_00120000_8.c). */
M2C_UNK func_0012cc38(s32, s32);
void func_0012b138(void *arg0) {
    func_0012cc38(M2C_FIELD(arg0, s32 *, 0), M2C_FIELD(arg0, s32 *, 4));
}

/* func_0012b158 (from auto/text_00120000_8.c). */
M2C_UNK func_0012cb78(s32, s32);
void func_0012b158(void *arg0) {
    func_0012cb78(M2C_FIELD(arg0, s32 *, 0), M2C_FIELD(arg0, s32 *, 4));
}

/* func_0012b178 (from auto/text_00120000_8.c). */
s32 func_0012ccf8(s32);
void func_0012b178(s32 *arg0) {
    *arg0 = func_0012ccf8(*arg0);
}

/* func_0012b1a8 (from auto/text_00120000.c). */
void func_0012b1a8(s32 *arg0) {
    if (*arg0 != 0) {
        D_002E31A8 |= 4;
        return;
    }
    D_002E31A8 &= ~4;
}

/* func_0012b1e8 (from auto/text_00120000.c). */
void func_0012b1e8(M2C_UNK **arg0) {
    *arg0 = ((M2C_UNK *)&D_002E2F28);
}

/* func_0012b1f8 (from auto/text_00120000.c). */
extern M2C_UNK D_002E2F34;
void func_0012b1f8(M2C_UNK **arg0) {
    *arg0 = &D_002E2F34;
}

/* func_0012b208 (from auto/text_00120000_8.c). */
M2C_UNK func_00146380(s32, s32, s32);
extern s32 D_002C5C4C;
void func_0012b208(void *arg0) {
    func_00146380(M2C_FIELD(arg0, s32 *, 0), M2C_FIELD(arg0, s32 *, 4), D_002C5C4C != 0);
}

/* func_0012b230 (from auto/text_00120000_8.c). */
s32 func_001464a0(s32);
void func_0012b230(s32 *arg0) {
    *arg0 = func_001464a0(*arg0);
}

/* func_0012b260 (from auto/text_00120000_9.c). */
#define func_00146380 ((M2C_UNK (*)(s32, s32, M2C_UNK)) func_00146380)
void func_0012b260(void *arg0) {
    func_00146380(M2C_FIELD(arg0, s32 *, 0), M2C_FIELD(arg0, s32 *, 4), 1);
}
#undef func_00146380

/* func_0012b280 (from auto/text_00120000_8.c). */
s32 func_001c4de0(s32, s32);
void func_0012b280(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0) = func_001c4de0(M2C_FIELD(arg0, s32 *, 0), M2C_FIELD(arg0, s32 *, 4));
}

/* func_0012b2b0 (from auto/text_00120000.c). */
extern s32 D_0029B418;
void func_0012b2b0(s32 *arg0) {
    *arg0 = D_0029B418;
}

/* func_0012b2c0 (from hand/text_00120000_h5.c). */
extern void func_00176c60(s32);
void func_0012b2c0(void) {
    s32 i;
    D_002E31A8 |= 2;
    for (i = 0; i < 3; i++) {
        if (D_002E26A0[i]) *(s32 *)D_002E26A0[i] |= 0x1000080;
    }
    func_00176c60(0);
}

/* func_0012b330 (from auto/text_00120000_8.c). */
s32 func_001ebe80();
void func_0012b330(s32 *arg0) {
    *arg0 = func_001ebe80();
}

/* func_0012b358 (from auto/text_00120000_15.c). */
void func_00157a30(s32, s32, s32);
void func_001ea498(s32);
void func_0012b358(s32 arg0) {
    s32 *temp_a3;

    temp_a3 = M2C_FIELD(*(s32 *)D_002E26A0, s32 **, 0x6C);
    *temp_a3 |= 4;
    func_00157a30(*(s32 *)D_002E26A0, 2, 0);
    func_001ea498(*(M2C_UNK *)arg0);
}

/* func_0012b3a8 (from auto/text_00120000_8.c). */
M2C_UNK func_0014ec10(s32);
void func_0012b3a8(s32 *arg0) {
    func_0014ec10(*arg0);
}

/* func_0012b3c0 (from auto/text_00120000_8.c). */
M2C_UNK func_0014ec38(s32);
void func_0012b3c0(s32 *arg0) {
    func_0014ec38(*arg0);
}

/* func_0012b3d8 (from auto/text_00120000_8.c). */
s32 func_0014e510(s32);
void func_0012b3d8(s32 *arg0) {
    *arg0 = func_0014e510(*arg0);
}

/* func_0012b408 (from auto/text_00120000.c). */
M2C_UNK func_001ef7b0(s32);
s32 func_001ef7a0();
void func_0012b408(s32 *arg0) {
    func_001ef7b0(*arg0);
    *arg0 = func_001ef7a0();
}

/* func_0012b440 (from auto/text_00120000.c). */
void func_0012b440(void) {

}

/* func_0012b448 (from auto/text_00120000.c). */
void func_0012b448(void) {

}

/* func_0012b450 (from hand/text_00120000_h31.c). */
typedef struct { f32 c[4]; s32 f10, f14, f18, f1c; f32 f20; s32 f24; } L9;
extern s32 D_002BC080[4];
extern s32 D_002BC090;
extern s32 D_002BC094;
extern s32 D_002BC09C;
extern s32 D_002BC0A0;
extern s32 D_002BC0A4;
extern s32 D_002BBE04;
void func_0012b450(L9 **pp) {
    L9 *p = *pp;
    s32 i;
    for (i = 0; i < 4; i++) D_002BC080[i] = p->c[i] * 128.0f;
    D_002BC090 = p->f10;
    D_002BC094 = p->f14;
    D_002BC098 = func_00120c88(p->f20 / 180.0f * 3.1415928f);
    D_002BC09C = p->f24;
    D_002BC0A0 = p->f18;
    D_002BC0A4 = p->f1c;
    D_002BBE04 = 1;
}

/* func_0012b530 (from auto/text_00120000.c). */
void func_0012b530(void) {
    D_002BBE04 = 0;
}

/* func_0012b540 (from auto/text_00120000_8.c). */
M2C_UNK func_00106a58(s32);
void func_0012b540(s32 *arg0) {
    func_00106a58(*arg0);
}

/* func_0012b558 (from auto/text_00120000_8.c). */
M2C_UNK func_00106978(s32);
void func_0012b558(s32 *arg0) {
    func_00106978(*arg0);
}

/* func_0012b570 (from auto/text_00120000_8.c). */
M2C_UNK func_00141858(s32, s32);
void func_0012b570(void *arg0) {
    func_00141858(M2C_FIELD(arg0, s32 *, 0), M2C_FIELD(arg0, s32 *, 4));
}

/* func_0012b590 (from auto/text_00120000_8.c). */
M2C_UNK func_001417a0(s32, s32);
void func_0012b590(void *arg0) {
    func_001417a0(M2C_FIELD(arg0, s32 *, 0), M2C_FIELD(arg0, s32 *, 4));
}

/* func_0012b5b0 (from auto/text_00120000_8.c). */
M2C_UNK func_0013c548(s32);
M2C_UNK func_00247408(s32, s32);
void func_0012b5b0(void *arg0) {
    s32 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s32 *, 0);
    if (temp_v0 != 0) {
        func_00247408(temp_v0, M2C_FIELD(arg0, s32 *, 4));
    }
    func_0013c548(M2C_FIELD(arg0, s32 *, 4));
}

/* func_0012b5e8 (from auto/text_00120000_10.c). */
M2C_UNK func_00247468(void *, s32);
void func_0012b5e8(void *arg0) {
    s32 sp[4];
    PlatVu0CopyVector(sp, M2C_FIELD(arg0, s32 *, 0));
    M2C_FIELD(sp, f32 *, 0xC) = 1.0f;
    func_00247468(sp, M2C_FIELD(arg0, s32 *, 4));
    func_0013c548(M2C_FIELD(arg0, s32 *, 4));
}

/* func_0012b638 (from auto/text_00120000_8.c). */
M2C_UNK func_00176ba8(s32, M2C_UNK);
void func_0012b638(s32 *arg0) {
    func_00176ba8(*arg0, 0);
}

/* func_0012b658 (from auto/text_00120000_8.c). */
#define func_00176c60 ((M2C_UNK (*)(M2C_UNK)) func_00176c60)
void func_0012b658(void) {
    func_00176c60(0);
}
#undef func_00176c60

/* func_0012b670 (from auto/text_00120000_8.c). */
void func_0012b670(s32 *arg0) {
    *arg0 = D_00350D80;
}

/* func_0012b680 (from auto/text_00120000.c). */
extern s32 D_00350D7C;
void func_0012b680(s32 *arg0) {
    *arg0 = D_00350D7C;
}

/* func_0012b690 (from hand/text_00120000_h5.c). */
typedef struct S54 { u8 pad[0x54]; s8 f54; } S54;
typedef struct E3 { u8 pad[0x130]; S54 *f130; } E3;
#define func_001230a0 ((Ent *(*)(Ent *)) func_001230a0)
void func_0012b690(s32 *out) {
    Ent *p = 0;
    s32 n = 0;
    while ((p = func_001230a0(p)) != 0) {
        if (((E3 *)p)->f130->f54 == 10) n++;
    }
    *out = n;
}
#undef func_001230a0

/* func_0012b6f0 (from auto/text_00120000_8.c). */
M2C_UNK func_001586a8(s32);
void func_0012b6f0(s32 *arg0) {
    func_001586a8(*arg0);
}

/* func_0012b708 (from auto/text_00120000_8.c). */
s32 func_001559f0(s32, M2C_UNK);
void func_0012b708(s32 *arg0) {
    *arg0 = func_001559f0(*arg0, 0);
}


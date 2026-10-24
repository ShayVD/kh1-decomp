/* Object class 0x0C, default flags (docs/modules.md "Session 52"): the
 * handlers func_0015e128 registers in the class table D_00350D88
 * (func_0014f830(0x0C, ...): one 32-byte record of a parameter and seven
 * handlers per class) and their helpers. The rest is in class0c.nostrict.c.
 * Read from the code, not proved by a boot. */
#include "m2c.h"
#include "data/pieces/D_002E26A0.h"
#include "actor.h"
#include "data/bss_0055.h"
#include "data/pieces/D_002C58B0.h"
#include "data/pieces/D_002E31B0.h"
#include "data/pieces/D_00350CE0.h"
#include "common.h"
#include "platform/vu.h"
#include "data/pieces/D_00304BE8_s.h"
#include "data/pieces/D_00351A30.h"
#include "data/pieces/D_00308CDC.h"
#include "data/pieces/D_002C58A0.h"

/* func_0015dcc8 (from auto/text_00150000_17.c). */
M2C_UNK func_00105a30(M2C_UNK, s32, M2C_UNK *);
extern M2C_UNK D_00351BB0;
void func_0015dcc8(void *arg0, M2C_UNK *arg1) {
    s32 sp[8];
    func_00105a30(-1, M2C_FIELD(M2C_FIELD(arg0, void **, 0x148), s32 *, 0x120), sp);
    PlatVu0OuterProduct(&M2C_FIELD(sp, M2C_UNK *, 0x10), sp, &D_00351BB0);
    PlatVu0Normalize(&M2C_FIELD(sp, M2C_UNK *, 0x10), &M2C_FIELD(sp, M2C_UNK *, 0x10));
    PlatVu0OuterProduct(arg1, &D_00351BB0, &M2C_FIELD(sp, M2C_UNK *, 0x10));
    PlatVu0Normalize(arg1, arg1);
}

/* func_0015de88 (from auto/text_00150000_3.c). */
f32 func_0026b9a8(f32, f32);
s32 func_00130398(s32, s32, f32);
s32 func_001375f0(s32);
#define func_0015dcc8 ((void (*)(s32, s32)) func_0015dcc8)
void func_0015de88(s32 arg0) {
    func_0015dcc8(arg0, arg0 + 0x20);
    if (func_001375f0(arg0) != 0) {
        func_00130398(arg0, 0x40000035, 8.0f);
        M2C_FIELD(arg0, f32 *, 0x150) = func_0026b9a8(M2C_FIELD(arg0, f32 *, 0x20), M2C_FIELD(arg0, f32 *, 0x28));
    }
}
#undef func_0015dcc8

/* func_0015def8 (from auto/text_00150000_19.c). */
M2C_UNK func_00121fc4(M2C_UNK *, M2C_UNK *);
extern f32 D_002BBDFC;
void func_0015def8(void *arg0, s32 arg1) {
  s32 sp[8];
  M2C_UNK *temp_s1;
  f32 var_f12;
  temp_s1 = arg0 + 0xC0;
  PlatVu0OuterProduct(sp, temp_s1, arg0 + 0x20);
  PlatVu0Normalize(sp, sp);
  PlatVu0OuterProduct(&(*((M2C_UNK *) (((s8 *) sp) + 0x10))), sp, temp_s1);
  PlatVu0Normalize(&(*((M2C_UNK *) (((s8 *) sp) + 0x10))), &(*((M2C_UNK *) (((s8 *) sp) + 0x10))));
  PlatVu0ScaleVectorXYZ(&(*((M2C_UNK *) (((s8 *) sp) + 0x10))), &(*((M2C_UNK *) (((s8 *) sp) + 0x10))), D_002BBDFC * 0.5f);
  PlatVu0AddVector(&(*((M2C_UNK *) (((s8 *) sp) + 0x10))), &(*((M2C_UNK *) (((s8 *) sp) + 0x10))), (*((s32 *) (((s8 *) arg0) + 0x148))) + 0x110);
  func_00121fc4(&(*((M2C_UNK *) (((s8 *) sp) + 0x10))), &(*((M2C_UNK *) (((s8 *) sp) + 0x10))));
  var_f12 = *((f32 *) (((s8 *) sp) + 0x1C));
  if (var_f12 > 16.0f)
  {
    var_f12 = 16.0f;
    *((f32 *) (((s8 *) sp) + 0x1C)) = 16.0f;
  }
  PlatVu0ScaleVector((*((s32 *) (((s8 *) arg0) + 0x148))) + 0x110, &(*((M2C_UNK *) (((s8 *) sp) + 0x10))), var_f12);
  PlatVu0ScaleVector(arg1, (*((s32 *) (((s8 *) arg0) + 0x148))) + 0x110, D_002BBDFC);
}

/* func_0015e0a8 (from hand/text_00150000_h10.c). */
typedef struct { u8 pad[0x10]; f32 f10; } Sub6C;
typedef struct { u8 pad[0x6C]; Sub6C *p6C; u8 pad70[0xD8]; u8 *p148; } ObjDA;
typedef struct { u8 pad[4]; union { f32 f; void *p; } f4; } RetDA;
f32 func_0014cce0(void *, f32);
RetDA *func_0014cb90(void *);
#define func_00121fc4 ((void (*)(f32 *, f32 *)) func_00121fc4)
RetDA *func_0015e0a8(ObjDA *a, f32 *v) {
    RetDA *r = func_0014cb90(a);
    r->f4.f = 4.0f;
    func_0014cce0(a, a->p6C->f10);
    PlatVu0CopyVector(v, a->p148 + 0x110);
    v[1] = 0.0f;
    func_00121fc4(v, v);
    return r;
}
#undef func_00121fc4

/* func_0015e128 (from auto/text_00150000_11.c). */
M2C_UNK func_0014f830(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK *, M2C_UNK *, M2C_UNK *, M2C_UNK, M2C_UNK *);
void func_0015dff8();
void func_0015e128(void) {
    func_0014f830(0xC, 0, 0, 0, &func_0015de88, &func_0015def8, &func_0015dff8, 0, &func_0015e0a8);
}


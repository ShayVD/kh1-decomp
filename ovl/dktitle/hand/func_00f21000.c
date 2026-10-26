/* dktitle.x func_00f21000: matched by hand. */
#include "ovl.h"

typedef struct { f32 v; s32 st; s32 t; } Fade;
extern Fade D_00F2C798;
void func_00f203a8(u64, s32, s32, s32, s32, s32, s32);
void func_00f20e70(Fade *);
void func_00f21000(void) {
    func_00f203a8(0x200E400665422E00ULL, 68, (s32)D_00F2C798.v, 0, 0, 512, 384);
    func_00f20e70(&D_00F2C798);
}

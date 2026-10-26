/* dktitle.x func_00f20f98: matched by hand. */
#include "ovl.h"

typedef struct { f32 v; s32 st; s32 t; } Fade;
extern Fade D_00F2C788;
void func_00f203a8(u64, s32, s32, s32, s32, s32, s32);
void func_00f20db0(Fade *);
void func_00f20f98(void) {
    func_00f203a8(0x200E40066541AE00ULL, 68, (s32)D_00F2C788.v, 64, 128, 384, 128);
    func_00f20db0(&D_00F2C788);
}

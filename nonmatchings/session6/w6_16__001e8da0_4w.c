/* 4w off (all modes): orig movz uses xori v1,v0,0 (late if-conversion); ours converts early in jump pass. strict hand */
#include "common.h"
typedef struct {
    u8 pad0[0x180];
    s32 sp;
    s32 stk[105];
    s64 f328;
} VM2;
s32 func_0011e368(s32, s32);

s32 func_001e8da0(VM2 *vm) {
    return func_0011e368(vm->stk[vm->sp - 1], vm->stk[vm->sp]) == 0 ? 2 : 4;
}

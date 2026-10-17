#include "common.h"

typedef struct {
    u8 pad0[0xb8];
    u16 xb8;
    u16 xba;
} WinD;

s32 func_001ff488(WinD *, s32, s32, s32, s32, s32);

s32 func_001ffaf0(WinD *o, s32 a) {
    return func_001ff488(o, 0, 0, (s16)o->xb8 >> 4, (s16)o->xba >> 4, a);
}

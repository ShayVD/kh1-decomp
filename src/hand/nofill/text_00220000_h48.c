#include "common.h"

extern s32 D_00648038[];

s32 func_002366d8(s32 i, s32 n) {
    s32 v = ((s64)D_00648038[i] * 0x41C64E6D + 12345) & 0x7FFFFFFF;
    D_00648038[i] = v;
    return ((v / 65536) * n + ((s64)(v & 0xFFFF) * n) / 65536) / 32768;
}

s32 func_002367f8(s32 *p, s32 n) {
    s32 v = ((s64)*p * 0x41C64E6D + 12345) & 0x7FFFFFFF;
    *p = v;
    return ((v / 65536) * n + ((s64)(v & 0xFFFF) * n) / 65536) / 32768;
}

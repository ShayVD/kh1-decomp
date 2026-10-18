#include "common.h"
s32 func_001aadf0(s32 *h, s32 kind, s32 i) {
    s32 o;
    s32 sz = i << 5;
    switch (kind) {
    case 2: o = h[2]; break;
    case 3: o = h[3]; sz = i << 4; break;
    default: goto dflt;
    }
    return o + (s32)h + sz;
dflt:
    sz = i << 2; o = *(s32 *)((s32)h + (kind << 2)); o += (s32)h; return *(s32 *)(sz + o);
}

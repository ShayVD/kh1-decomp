/* xs_genie.x func_00f21820: matched by hand. */
#include "ovl.h"

typedef struct { s32 a; s32 b; } P8;
typedef struct { s32 a; P8 b; s32 d; s32 e; s32 f; } P24;
typedef struct { s32 max; P24 *buf; s32 n; s32 rd; } Q;
s32 func_00f215f8(Q *, P24 *);
void func_0023c5a8(s32);
extern Q D_00FC1DD0;

s32 func_00f21820(P8 *out) {
    P24 it;
    if (func_00f215f8(&D_00FC1DD0, &it) == 0) {
        return 0;
    }
    *out = it.b;
    func_0023c5a8(it.f);
    return 1;
}

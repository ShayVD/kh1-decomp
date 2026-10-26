/* xs_genie.x func_00f216e0: matched by hand. */
#include "ovl.h"

typedef struct { s32 a; s32 b; } P8;
typedef struct { s32 a; P8 b; s32 d; s32 e; s32 f; } P24;
typedef struct { s32 max; P24 *buf; s32 n; s32 rd; } Q;
s32 func_00f21580(Q *, P24 *);
s32 func_00f21680(P8 *);
s32 func_0023c4d8(P8 *, s32, s32, s32);
void func_0011d140(s32, s32);
s32 rand(void);
extern Q D_00FC1DD0;

void func_00f216e0(P8 *p) {
    P24 it;
    it.a = 0;
    it.b = *p;
    it.e = 0;
    it.d = 0;
    if (func_00f21680(p) > 0) {
        it.d = (((rand() & 0x7FFF) / 32767.0f - 0.5f) * 2) * 256.0f;
        it.e = (((rand() & 0x7FFF) / 32767.0f - 0.5f) * 2) * 256.0f;
    }
    it.f = func_0023c4d8(&it.b, 5, it.d, it.e);
    if (func_00f21580(&D_00FC1DD0, &it) != 0) {
        func_0011d140(rand() % 5 + 10080, 1);
    }
}

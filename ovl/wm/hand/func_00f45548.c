/* wm.x func_00f45548: matched by hand. */
#include "ovl.h"

void func_001bfac8(void);
void func_00f45548(s32 n, s32 x, s32 y, s32 z, f32 *obj) {
    OvlVec cur, dst, src;
    f32 *pos = obj + 12;
    s32 i = 0;
    PlatVu0CopyVector(src, pos);
    dst[0] = x * 100.0f;
    dst[3] = 1.0f;
    cur[3] = 1.0f;
    dst[1] = y * 100.0f;
    dst[2] = z * 100.0f;
    if (n > 0) {
        f32 fn = n;
        do {
            f32 t = i;
            i++;
            cur[0] = (dst[0] - src[0]) * t / fn + src[0];
            cur[1] = (dst[1] - src[1]) * t / fn + src[1];
            cur[2] = (dst[2] - src[2]) * t / fn + src[2];
            PlatVu0CopyVector(pos, cur);
            func_001bfac8();
        } while (i < n);
    }
    PlatVu0CopyVector(pos, dst);
}

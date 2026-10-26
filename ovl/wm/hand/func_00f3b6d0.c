/* wm.x func_00f3b6d0: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[0x80]; OvlVec pos; u8 pad2[0x10]; s32 on; } A;
typedef struct { u8 pad[0x18]; s32 n; s32 x; s32 y; s32 z; } B;
void func_001bfac8(void);
void func_00f3b6d0(A *arg0, B *arg1) {
    OvlVec cur, dst, src;
    f32 *pos = arg0->pos;
    s32 n = arg1->n;
    s32 i;
    PlatVu0CopyVector(src, pos);
    dst[0] = arg1->x * 100.0f;
    dst[3] = 1.0f;
    dst[1] = arg1->y * 100.0f;
    dst[2] = arg1->z * 100.0f;
    if (n > 0) {
        for (i = 0; i < n && arg0->on != 0; ) {
            f32 t = i;
            i++;
            cur[3] = 1.0f;
            cur[0] = (dst[0] - src[0]) * t / (f32)n + src[0];
            cur[1] = (dst[1] - src[1]) * t / (f32)n + src[1];
            cur[2] = (dst[2] - src[2]) * t / (f32)n + src[2];
            PlatVu0CopyVector(pos, cur);
            func_001bfac8();
        }
    }
    PlatVu0CopyVector(pos, dst);
}

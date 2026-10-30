/* wm.x func_00f37c08: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[0x60]; f32 m60[4][4]; u8 pad2[0xE0 - 0xA0]; s32 fE0; } O37c08;
typedef struct { u8 pad[0x14]; s32 type; s32 time; s32 rx, ry, rz; } A37c08;
void func_001be9f0(f32 *);
void func_001bfac8(void);
void func_00f37770(s32, O37c08 *, A37c08 *, s32);
extern f32 D_002BBDEC;

void func_00f37c08(O37c08 *arg0, A37c08 *arg1, s32 arg2) {
    f32 m[4][4];
    f32 rot[4];
    f32 dst[4];
    s32 n;
    s32 i;

    if (arg1->type == 3) {
        func_00f37770(1, arg0, arg1, arg2);
        return;
    }
    n = (f32)arg1->time / D_002BBDEC;
    rot[0] = (f32)arg1->rx * 0.017453291f;
    rot[1] = (f32)arg1->ry * 0.017453291f;
    rot[2] = (f32)arg1->rz * 0.017453291f;
    rot[3] = 1.0f;
    switch (arg1->type) {
    case 2:
        sceVu0CopyMatrix(m, arg0->m60);
        break;
    case 4:
        sceVu0UnitMatrix(m);
        break;
    }
    dst[0] = (f32)arg1->rx * 0.017453291f;
    dst[1] = (f32)arg1->ry * 0.017453291f;
    dst[2] = (f32)arg1->rz * 0.017453291f;
    dst[3] = 1.0f;
    if (arg2 != 0 && n > 0) {
        if (arg0->fE0 == 0) {
            return;
        }
        for (i = 0; i < n && arg0->fE0 != 0; i++) {
            rot[0] = (dst[0] - 0.0f) * (f32)i / (f32)n + 0.0f;
            rot[1] = (dst[1] - 0.0f) * (f32)i / (f32)n + 0.0f;
            rot[2] = (dst[2] - 0.0f) * (f32)i / (f32)n + 0.0f;
            rot[3] = 1.0f;
            func_001be9f0(rot);
            sceVu0RotMatrix(arg0->m60, m, rot);
            func_001bfac8();
        }
    }
    sceVu0RotMatrix(arg0->m60, m, dst);
}

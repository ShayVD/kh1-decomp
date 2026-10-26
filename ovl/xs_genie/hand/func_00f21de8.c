/* xs_genie.x func_00f21de8: matched by hand. */
#include "ovl.h"

typedef struct { f32 p[4]; f32 d[4]; u8 pad[0x10]; s16 h; u8 pad32[2]; s32 x; u8 pad38[8]; } Ray68;
typedef struct { u8 pad[4]; f32 y; } Eff4;
void func_00118608(Ray68 *);
Eff4 **func_00147ed8(s32, s32, s32, f32 *);
void *memset(void *, s32, u32);
extern s32 D_00F22E98;

void func_00f21de8(u8 *arg0) {
    Ray68 r;
    OvlVec d;
    f32 *pos;

    memset(d, 0, 0x10);
    pos = (f32 *)(arg0 + 0x10);
    d[1] = 10.0f;
    PlatVu0CopyVector(r.p, pos);
    r.p[1] -= 5.0f;
    PlatVu0CopyVector(r.d, d);
    func_00118608(&r);
    if (r.h >= 0) {
        Eff4 *e = *func_00147ed8(D_00F22E98, 0x13, 0x4E20, pos);
        e->y -= 5.0f;
        return;
    }
    func_00147ed8(D_00F22E98, 0x14, 0x4E20, pos);
}

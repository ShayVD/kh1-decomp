/* wm.x func_00f4c728: matched by hand. */
#include "ovl.h"

typedef struct { u16 x : 4; u16 y : 4; u16 z : 4; u16 r : 4; } GbPos;
typedef struct { GbPos pos; u16 pad2; u16 id; u16 pad6[3]; } GbObj;
typedef struct {
    u8 pad0[0x58];
    u64 lo : 32;
    u16 x : 4;
    u16 y : 4;
    u16 z : 4;
    u16 r : 4;
    u16 pad5e;
    u8 pad60[0x88 - 0x60];
    f32 f88;
    u8 pad8c[0xA4 - 0x8C];
    u16 count;
    u16 w;
    u16 d;
    u16 h;
    u8 padac[0x110 - 0xAC];
    GbObj tbl[(0x10EC - 0x110) / 12];
    u8 pad10ec_[0x10EC - 0x110 - ((0x10EC - 0x110) / 12) * 12];
    u8 keys[1];
} GbWorld;
extern GbWorld *D_00F9B540;
s32 func_001bb740(void);
u8 func_001ba3f0(s32);
void func_00f4af28(s32);
s32 func_001bb678(void);

void func_00f4c728(void) {
    s32 i;
    s32 n;
    s32 off;
    for (i = 0; i < func_001bb740(); i++)
        D_00F9B540->keys[i] = func_001ba3f0(i);
    for (i = 0; i < D_00F9B540->count; i++)
        func_00f4af28(D_00F9B540->tbl[i].id - 1);
    n = func_001bb678();
    if (D_00F9B540->w < n) {
        off = (n - D_00F9B540->w) / 2;
        for (i = 0; i < D_00F9B540->count; i++) {
            GbObj *o = &D_00F9B540->tbl[i];
            if (o->id != 0) {
                o->pos.x += off;
                o->pos.y += off;
                o->pos.z += off;
            }
        }
        D_00F9B540->w = n;
        D_00F9B540->f88 = -2944.0f - (f32)((D_00F9B540->w - 6) * 420);
        D_00F9B540->h = n;
        D_00F9B540->d = n;
        if (D_00F9B540->x >= n)
            D_00F9B540->x = n - 1;
        if (D_00F9B540->y >= n)
            D_00F9B540->y = n - 1;
        if (D_00F9B540->z >= n)
            D_00F9B540->z = n - 1;
    }
}

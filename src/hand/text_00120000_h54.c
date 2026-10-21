#include "common.h"
typedef struct { f32 x, y, z, w; } V4;
typedef struct { u8 pad[0xd0]; f32 fd0[4][4]; u8 p110[0x15c - 0x110]; s32 f15c; } E14;
#include "data/pieces/D_002C58A0.h"
#include "data/pieces/D_002C58D0.h"
extern s32 func_00122ff8(E14 *);
extern void sceVu0CopyMatrix(f32 (*)[4], f32 (*)[4]);
extern void func_00267530(f32 *, V4 *, f32 *);
extern void func_001315c0(E14 *, s32, f32 *, f32);
typedef f32 Mtx[4][4];
extern Mtx *func_001623e0(s32);
extern s32 func_00131558(E14 *, s32);
extern s32 func_00162368(s32, s32);
void func_001318e8(E14 *e, s32 id, f32 (*m)[4]) {
    if (!func_00122ff8(e)) {
        sceVu0CopyMatrix(m, (*(f32 (*)[4][4])&D_002C58D0));
        return;
    }
    if (id & 0x8000) {
        func_00267530(m[0], ((V4 *)&D_002C58A0), e->fd0[2]);
        func_00267530(m[1], ((V4 *)&D_002C58A0), e->fd0[1]);
        func_00267530(m[2], ((V4 *)&D_002C58A0), e->fd0[0]);
        func_001315c0(e, id, m[3], 0.0f);
    } else if (id & 0x2000) {
        id &= 0xfff;
        sceVu0CopyMatrix(m, *(func_001623e0(e->f15c) + id));
    } else {
        id = func_00131558(e, id);
        if (id <= 0) {
            sceVu0CopyMatrix(m, e->fd0);
        } else {
            id = func_00162368(e->f15c, id);
            sceVu0CopyMatrix(m, *(func_001623e0(e->f15c) + id));
        }
    }
}

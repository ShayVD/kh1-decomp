/* wm.x func_00f39448: matched by hand. */
#include "ovl.h"

void func_001bfac8(void);
void func_001be9f0(f32 *);
void sceVu0UnitMatrix(f32 (*)[4]);
void sceVu0TransMatrix(f32 (*)[4], f32 (*)[4], f32 *);
void sceVu0RotMatrix(f32 (*)[4], f32 (*)[4], f32 *);
void sceVu0CopyMatrix(f32 (*)[4], f32 (*)[4]);
void sceVu0CopyVector(f32 *, f32 *);
extern f32 D_002BBDEC;

typedef struct { u8 pad[0xA0]; f32 m[4][4]; s32 e0; u8 pad3[0x18]; s32 fc; } A39448;
typedef struct { u8 pad[0x14]; s32 type; s32 time; s32 ang; s32 dist; } B39448;

void func_00f39448(s32 mode, A39448 *obj, B39448 *ev, s32 arg3) {
    f32 tmp[4];
    f32 t[4];
    f32 rot[4];
    f32 cur[4];
    f32 m[4][4];
    s32 n;
    s32 i;
    f32 s;

    n = (f32)ev->time / D_002BBDEC;
    rot[0] = 0.0f;
    rot[1] = 0.0f;
    rot[2] = 0.0f;
    rot[3] = 1.0f;
    rot[ev->type - 5] = ev->ang * 0.017453292f;
    t[0] = 0.0f;
    t[1] = 0.0f;
    t[2] = 0.0f;
    t[3] = 1.0f;
    t[(ev->type - 3) % 3] = ev->dist * 100.0f;
    sceVu0UnitMatrix(obj->m);
    if (arg3 != 0 && n > 0) {
        for (i = 0; i < n; i++) {
            if (obj->fc == 0) break;
            if (obj->e0 == 0) return;
            tmp[0] = (rot[0] - 0.0f) * i / n + 0.0f;
            tmp[1] = (rot[1] - 0.0f) * i / n + 0.0f;
            tmp[2] = (rot[2] - 0.0f) * i / n + 0.0f;
            tmp[3] = 1.0f;
            sceVu0CopyVector(cur, tmp);
            func_001be9f0(cur);
            sceVu0UnitMatrix(m);
            sceVu0TransMatrix(m, m, t);
            sceVu0RotMatrix(m, m, cur);
            if (mode == 0) {
                sceVu0CopyMatrix(obj->m, m);
            } else {
                sceVu0CopyVector(obj->m[3], m[3]);
            }
            func_001bfac8();
        }
    }
    func_001be9f0(rot);
    sceVu0UnitMatrix(m);
    sceVu0TransMatrix(m, m, t);
    sceVu0RotMatrix(m, m, rot);
    if (mode == 0) {
        sceVu0CopyMatrix(obj->m, m);
    } else {
        sceVu0CopyVector(obj->m[3], m[3]);
    }
}

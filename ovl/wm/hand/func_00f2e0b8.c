/* wm.x func_00f2e0b8: matched by hand. */
#include "ovl.h"

typedef struct { u8 b0; u8 pad[13]; u16 h14; u16 pad2; s16 h18; u8 pad3[12]; f32 m[4][4]; u8 pad4[32]; s32 idx; } A2e0b8;
typedef struct { s32 a; s32 b; u8 pad[24]; } B2e0b8;
typedef struct { s32 f0; s32 f4; } O2e0b8;
typedef struct { u8 pad[6]; u16 h6; } R2e0b8;
typedef struct { u8 pad[1344]; s32 f1344; } G2e0b8;
extern B2e0b8 D_00FBB5D0[];
extern G2e0b8 *D_00F864C0;
extern f32 D_002BBDEC;
A2e0b8 *func_00f2cae8(void);
O2e0b8 *func_00f3b4e0(s32);
R2e0b8 *func_00f3f260(s32, s32);
s32 func_00f680c0(s32);
void func_00f68ab0(s32);
void func_00f2d608(s32);
void func_00f2cf78(s32);
void func_001bfac8(void);
void sceVu0CopyMatrix(f32 (*)[4], f32 (*)[4]);

void func_00f2e0b8(s32 arg) {
    f32 m[4][4];
    A2e0b8 *s;
    O2e0b8 *obj;
    R2e0b8 *r;
    s32 idx;
    s32 id;
    s32 done;
    s32 cnt;
    f32 v;
    f32 vmax;
    f32 acc;
    s32 g;

    s = func_00f2cae8();
    v = D_002BBDEC * 2000.0f;
    acc = D_002BBDEC * 40.0f;
    idx = s->idx;
    vmax = v;
    if (idx >= 0) {
        id = D_00FBB5D0[idx].b;
    } else {
        id = -1;
    }
    if (id >= 0) {
        obj = func_00f3b4e0(id);
        if (obj != NULL) {
            r = func_00f3f260(obj->f4, D_00F864C0->f1344);
            if (r != NULL) {
                r->h6 |= 2;
            } else {
                id = -1;
            }
        } else {
            id = -1;
        }
    }
    done = 0;
    cnt = 0;
    while (func_00f680c0(s->h14)) {
        if (id >= 0) {
            func_00f3b4e0(id);
        }
        if (s->b0 == 0) {
            return;
        }
        if (s->h18 & 1) {
            s->h18 = 0;
        }
        sceVu0CopyMatrix(m, s->m);
        m[0][0] = -m[0][0];
        m[0][1] = -m[0][1];
        m[0][2] = -m[0][2];
        m[2][0] = -m[2][0];
        m[2][1] = -m[2][1];
        m[2][2] = -m[2][2];
        if (v < vmax) {
            v += acc;
            if (vmax < v) {
                v = vmax;
            }
        }
        m[3][0] += m[2][0] * v;
        m[3][1] += m[2][1] * v;
        m[3][2] += m[2][2] * v;
        m[0][0] = -m[0][0];
        m[0][1] = -m[0][1];
        m[0][2] = -m[0][2];
        m[2][0] = -m[2][0];
        m[2][1] = -m[2][1];
        m[2][2] = -m[2][2];
        sceVu0CopyMatrix(s->m, m);
        if (done == 0) {
            if (cnt >= 29) {
                func_00f68ab0(s->h14);
                done = 1;
            }
            if (done == 0) {
                func_00f2d608(arg);
            }
        }
        func_001bfac8();
        cnt++;
    }
    obj = func_00f3b4e0(id);
    if (obj != NULL) {
        g = D_00F864C0->f1344;
        D_00FBB5D0[idx].a &= 0xFD;
        r = func_00f3f260(obj->f4, g);
        if (r != NULL) {
            r->h6 ^= 2;
        }
    }
    func_00f2cf78(arg);
}

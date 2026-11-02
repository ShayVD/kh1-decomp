/* wm.x func_00f2e510: matched by hand. */
#include "ovl.h"

typedef struct { u8 b0; u8 pad[13]; u16 h14; u16 pad2; s16 h18; u8 pad3[12]; f32 m[4][4]; u8 pad4[32]; s32 idx; } A2e510;
typedef struct { s32 a; s32 b; u8 pad[24]; } B2e510;
typedef struct { s32 f0; s32 f4; u8 pad[72]; f32 v80[4]; } O2e510;
typedef struct { u8 pad[6]; u16 h6; } R2e510;
typedef struct { u8 pad[1344]; s32 f1344; } G2e510;
extern B2e510 D_00FBB5D0[];
extern G2e510 *D_00F864C0;
extern f32 D_002BBDEC;
A2e510 *func_00f2cae8(s32);
O2e510 *func_00f3b4e0(s32);
R2e510 *func_00f3f260(s32, s32);
s32 func_00f680c0(s32);
void func_00f68ab0(s32);
void func_00f2d608(s32);
void func_00f2cf78(s32);
void func_001bfac8(void);
O2e510 *func_00f2d630(f32 (*)[4], s32);
f32 func_00f2d738(f32 (*)[4], f32 *, f32, f32, f32);
void sceVu0CopyMatrix(f32 (*)[4], f32 (*)[4]);

void func_00f2e510(s32 arg) {
    f32 m[4][4];
    A2e510 *s;
    O2e510 *obj;
    R2e510 *r;
    s32 idx;
    s32 id;
    s32 done;
    s32 cnt;
    s32 g;
    B2e510 *p;
    f32 v;
    f32 vmax;
    f32 acc;
    f32 rs;

    s = func_00f2cae8(arg);
    v = D_002BBDEC * 3000.0f;
    acc = D_002BBDEC * 40.0f;
    idx = s->idx;
    vmax = v;
    if (idx >= 0) {
        id = D_00FBB5D0[idx].b;
    } else {
        id = -1;
    }
    obj = NULL;
    if (id >= 0) {
        obj = func_00f3b4e0(id);
        if (obj != NULL) {
            g = D_00F864C0->f1344;
            r = func_00f3f260(obj->f4, g);
            if (r != NULL) {
                r->h6 |= 2;
                goto ok;
            }
        }
        id = -1;
        obj = NULL;
    }
ok:
    rs = 0.17453292f;
    done = 0;
    cnt = 0;
    while (func_00f680c0(s->h14)) {
        obj = NULL;
        if (id >= 0) {
            obj = func_00f3b4e0(id);
        }
        if (s->b0 == 0) {
            return;
        }
        if (s->h18 & 1) {
            if (idx >= 0) {
                p = &D_00FBB5D0[idx];
                p->a &= 0xFD;
                id = p->b;
                obj = func_00f2d630(s->m, id);
            }
            rs += rs;
            s->h18 = 0;
        }
        sceVu0CopyMatrix(m, s->m);
        m[0][0] = -m[0][0];
        m[0][1] = -m[0][1];
        m[0][2] = -m[0][2];
        m[2][0] = -m[2][0];
        m[2][1] = -m[2][1];
        m[2][2] = -m[2][2];
        if (obj == NULL) {
            if (v < vmax) {
                v += acc;
                if (vmax < v) {
                    v = vmax;
                }
            }
            m[3][0] += m[2][0] * vmax;
            m[3][1] += m[2][1] * vmax;
            m[3][2] += m[2][2] * vmax;
        } else {
            v = func_00f2d738(m, obj->v80, rs, vmax, 1.0f);
            m[3][0] += m[2][0] * v;
            m[3][1] += m[2][1] * v;
            m[3][2] += m[2][2] * v;
        }
        m[0][0] = -m[0][0];
        m[0][1] = -m[0][1];
        m[0][2] = -m[0][2];
        m[2][0] = -m[2][0];
        m[2][1] = -m[2][1];
        m[2][2] = -m[2][2];
        sceVu0CopyMatrix(s->m, m);
        if (done == 0) {
            if (cnt >= 37) {
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

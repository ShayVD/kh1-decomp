/* xs_simba.x func_00f21148: matched by hand. */
#include "ovl.h"

typedef struct { s32 flags; u8 pad4[0xC]; OvlVec pos; OvlVec v20; OvlVec v30; u8 pad40[0x30]; s32 f70; u8 pad74[0xF0]; s32 f164; u8 pad168[0x258]; OvlVec v3c0; } Act;
typedef struct { u8 pad[0xC]; void *fc; } Mot;
typedef struct { s32 pad; f32 f4; } Gnd;
Gnd *func_0014dab8(Act *);
void func_0013aaa0(void);
s32 func_00f219c8(void *, f32 *, s32, f32 *, f32);
void func_00121fc4(f32 *, f32 *);
void func_00f21020(void);
void func_00f210c0(Act *);
s32 func_00142b30(Act *, f32 *);
s32 func_00130340(Act *, s32, f32);
void func_00130398(Act *, s32, f32);
Mot *func_00130578(Act *, s32, f32);
void func_001376e8(Act *, f32 *);
void func_00f21080(void);
extern f32 D_002BBDFC;
extern f32 D_002C58B0[];
extern Act *D_00F21C34;
extern u8 D_00FA6F38[];
extern f32 D_00FA7750;
void func_00f21148(Act *a) {
    OvlVec v;
    OvlVec d;
    OvlVec w;
    Gnd *g;
    s32 n;
    s32 r;

    g = func_0014dab8(a);
    if (g != NULL && g->f4 < a->pos[1])
        func_0013aaa0();
    PlatVu0CopyVector(v, a->pos);
    n = func_00f219c8(D_00FA6F38, v, 3, d, 50.0f);
    PlatVu0SubVector(d, d, a->pos);
    d[1] = 0.0f;
    func_00121fc4(d, d);
    if (n >= 10) {
        func_00f21020();
        n = 0;
    } else {
        if (700.0f < d[3] && n > 0) {
            if (D_00F21C34->f70 == 8)
                func_0013aaa0();
            else
                func_00f210c0(a);
            return;
        }
        if (200.0f < d[3] || n >= 5)
            n = 2;
        else if (n >= 3)
            n = 1;
        else
            n = 0;
    }
    switch (a->f70) {
    case 0:
        r = 0;
        if (n != 0) {
            PlatVu0ScaleVector(w, d, 200.0f);
            w[1] = -300.0f;
            w[3] = 1000.0f;
            r = func_00142b30(a, w);
        }
        switch (r) {
        case 3:
            func_00f21020();
            n = 0;
            break;
        case 1:
        case 2:
            n = 4095;
            func_00130340(a, 0x01000003, 0.0f);
            func_00130578(a, 0x40010004, 0.0f)->fc = func_00f21080;
            PlatVu0CopyVector(a->v3c0, D_002C58B0);
            break;
        case 0:
            if (0.0f < D_00FA7750) {
                n = a->f164;
                D_00FA7750 = D_00FA7750 - D_002BBDFC;
            } else {
                switch (n) {
                case 0:
                    break;
                case 1:
                case 2:
                    if (a->f164 != n)
                        D_00FA7750 = 20.0f;
                    break;
                }
            }
            break;
        }
        if (n != 4095) {
            func_00130398(a, n, 12.0f);
            if (n != 0)
                func_001376e8(a, d);
        }
        break;
    case 2:
        func_001376e8(a, d);
        break;
    }
    switch (n) {
    case 1:
        d[3] = 2.0f;
        break;
    case 2:
        d[3] = 8.0f;
        break;
    default:
        d[3] = 0.0f;
        break;
    }
    if (0.0f < d[3])
        PlatVu0CopyVector(a->v20, d);
}

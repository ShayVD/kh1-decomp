/* wm.x func_00f44898: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[0x40]; void (*begin)(s32); s32 (*more)(s32); } C;
extern C D_00FB6408;
extern s32 *D_01080800[];
extern s32 D_01080810[];
extern u8 D_01080820[];
extern s32 D_01080828[];
extern s32 D_01080830[];
extern s32 D_01080838[];
extern s32 D_01080840[];
extern s32 D_01080848[];
extern s32 D_01080850[];
extern s32 D_01080858[];
extern s32 D_01080860[][8];
extern s32 D_010808A0[][8];
extern s32 D_010808E0[];
extern f32 D_002BBDFC;
void sceVu0UnitMatrix(OvlMtx);
void sceVu0CopyMatrix(OvlMtx, OvlMtx);
void sceVu0RotMatrixX(OvlMtx, OvlMtx, f32);
void sceVu0RotMatrixY(OvlMtx, OvlMtx, f32);
void func_00f21260(s32, OvlMtx, OvlMtx, s32, s32 *, s32, s32, f32);
s32 func_00167698(s32);
void func_00167d70(s32, f32);
void func_00f44ee0(s32, s32, s32);
void func_001bfac8(void);

void func_00f44898(s32 side, void (*done)(s32))
{
    OvlMtx m;
    OvlMtx m2;
    s32 obj;
    s32 arg;
    s32 prev;
    s32 *st;
    s32 *fr;
    s32 n;
    s32 j;
    s32 *q;
    f32 ry, tx, ty, tz;
    f32 t;
    f32 len;

    D_01080830[side] = 1;
    D_010808E0[side] = 0;
    if (side == 0) {
        ry = -0.36999998f;
        obj = 0x15F90;
        arg = 0x170;
    } else {
        ry = 0.36999998f;
        obj = 0x16090;
        arg = 0x178;
    }
    tx = 0.0f;
    prev = -1;
    ty = 120.0f;
    D_00FB6408.begin(side);
    tz = 150.0f;
    while (1) {
        if (prev != D_01080838[side]) {
            prev = D_01080838[side];
            switch (D_01080820[prev]) {
            case 0:
            default:
                ry = -0.29999999f;
                tx = -1.0f;
                ty = 120.0f;
                tz = 150.0f;
                break;
            case 1:
            case 6:
                ry = -0.29999999f;
                tx = -4.0f;
                ty = 64.0f;
                tz = 160.0f;
                break;
            case 2:
                ry = -0.47f;
                tx = -7.0f;
                ty = 124.0f;
                tz = 196.0f;
                break;
            case 3:
            case 4:
                ry = -0.39999998f;
                tx = -1.0f;
                ty = 20.0f;
                tz = 60.0f;
                break;
            case 5:
                ry = -0.29999999f;
                tx = 0.0f;
                ty = 13.0f;
                tz = 34.0f;
                break;
            }
            if (side != 0) {
                tx = -tx;
                ry = -ry;
            }
            t = 0.0f;
        }
        sceVu0UnitMatrix(m);
        sceVu0RotMatrixY(m, m, ry);
        sceVu0CopyMatrix(m2, m);
        m2[3][0] = 0;
        m2[3][1] = 0;
        m2[3][2] = 0;
        m2[0][3] = 0;
        m2[1][3] = 0;
        m2[2][3] = 0;
        m2[3][3] = 1.0f;
        m[3][0] = tx;
        m[3][1] = ty;
        m[3][2] = tz;
        sceVu0RotMatrixX(m2, m2, 3.1415926f);
        q = D_01080810;
        st = &D_01080838[side];
        fr = &D_01080840[side];
        func_00f21260(obj, m, m2, q[*st], D_01080800[*st], *fr, arg, t);
        if (D_01080848[side] >= 0) {
            len = (f32)func_00167698(D_01080800[*st][*fr]);
            t += D_002BBDFC;
            if (D_010808E0[side] != 0) {
                n = D_01080858[side];
                D_010808E0[side] = 0;
                if (n > 0 || *fr != 0) {
                    D_01080848[side] = 0;
                    t = len + 1.0f;
                    if (n == 0) {
                        func_00f44ee0(side, 0, 0);
                    }
                }
            }
            if (len < t) {
                if (D_01080848[side] < 2 && D_01080858[side] != 0) {
                    j = D_01080850[side];
                    t = 0.0f;
                    D_01080840[side] = D_01080860[side][j];
                    D_01080848[side] = D_010808A0[side][j];
                    D_01080858[side]--;
                    D_01080850[side] = (j + 1) & 7;
                } else {
                    t -= len;
                    if (D_01080848[side] > 0) {
                        if (--D_01080848[side] == 0) {
                            D_01080848[side] = 0;
                            t = 0.0f;
                            D_01080840[side] = 0;
                        }
                    }
                }
            }
        }
        func_00167d70(D_01080810[D_01080838[side]], D_002BBDFC);
        if (D_00FB6408.more(side) == 0) break;
        func_001bfac8();
    }
    if (done != 0) {
        done(side);
    }
    D_01080828[side] = 0;
    D_01080830[side] = 0;
}

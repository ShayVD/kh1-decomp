/* gb.x func_00f27388: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[8]; u8 b8; } I4e480;
typedef struct { u8 pad[0x10]; f32 m10[4][4]; f32 m50[4][4]; f32 m90[4][4]; } O4e480;
typedef struct { s32 x0; O4e480 *o; s32 x8; } A4e480;
typedef struct { u8 pad[0x1010]; f32 m[2][4][4]; } W4e480;
I4e480 *func_001bb658(s32);
void func_00f23880(s32);
s32 func_00f25918(s32);
s32 func_00f25978(s32);
CONTEXT_ONLY f32 func_00f27310(s32 a) { return 0; }
void func_00f36c00(f32 (*)[4], s32);
void func_00f36d58(s32 *, s32);
void func_00f36e40(s32, s32, s32 *);
void func_00f36e98(s32, s32, s32 *);
O4e480 *func_00f36ee0(s32 *, O4e480 *, s32, s32, s32, s32);
void func_00f375e8(s32 *);
extern W4e480 *D_00F56DC0;
extern s32 D_00F61364;

s32 func_00f27388(s32 arg0, A4e480 *arg1, s32 id, f32 *scl, f32 (*mtx)[4], s32 flags, f32 f0, f32 sc) {
    f32 v0[4];
    f32 v1[4];
    f32 a[4][4];
    f32 b[4][4];
    f32 c[4][4];
    f32 d[4][4];
    f32 r[4][4];
    f32 x[4][4];
    f32 y[4][4];
    f32 s[4][4];
    I4e480 *info;
    f32 (*vm)[4][4];
    s32 i;

    info = func_001bb658(id);
    sceVu0UnitMatrix(r);
    sceVu0RotMatrixX(r, r, 3.1415925026f);
    sceVu0MulMatrix(mtx, mtx, r);
    func_00f23880(info->b8);
    v0[0] = 0;
    v0[1] = 0;
    v0[2] = 0;
    sceVu0TransMatrix(c, mtx, v0);
    sceVu0UnitMatrix(d);
    if (scl != NULL) {
        for (i = 0; i < 3; i++) {
            d[i][i] = scl[i];
        }
    }
    sceVu0MulMatrix(c, c, d);
    vm = D_00F56DC0->m;
    sceVu0UnitMatrix(s);
    if (D_00F61364 == 0) {
        sc *= func_00f27310(id);
    }
    s[0][0] = sc;
    s[1][1] = sc;
    s[2][2] = sc;
    s[3][3] = sc;
    v1[0] = 0;
    v1[1] = 0;
    v1[2] = 3072.0f;
    v1[3] = 1.0f;
    sceVu0UnitMatrix(a);
    sceVu0TransMatrix(a, a, v1);
    if (D_00F61364 == 0) {
        func_00f36e40(arg0, arg0, &arg1->x8);
    } else {
        func_00f36e98(arg0, arg0, &arg1->x8);
    }
    arg0++;
    func_00f36d58(&arg1->x8, flags & 2);
    sceVu0MulMatrix(b, a, c);
    sceVu0MulMatrix(arg1->o->m90, vm[0], b);
    func_00f36c00(arg1->o->m10, id);
    sceVu0MulMatrix(arg1->o->m10, arg1->o->m10, s);
    arg1->o->m10[3][3] = f0;
    sceVu0MulMatrix(arg1->o->m50, vm[1], mtx);
    arg1->o = func_00f36ee0(&arg1->x8, arg1->o, info->b8 + 1, 0, func_00f25918(id), func_00f25978(id));
    func_00f375e8(&arg1->x8);
    return arg0;
}

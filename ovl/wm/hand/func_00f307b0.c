/* wm.x func_00f307b0: matched by hand. */
#include "ovl.h"

extern s32 D_00F85088;
extern f32 D_00FBDA80[4];
extern f32 D_00FBDA90[4];
extern f32 D_00F8C144;
extern s32 D_00FBEBB8;
extern s32 D_00F8C120;
extern f32 D_00F8C240[4][4];
extern s32 D_00FBDAF0;
extern s32 D_00FBB5A0;
extern s32 D_00FBB5A4;
extern s32 D_00F8C280;
extern s32 D_00F850F4;
void func_00242b68(s32);
s32 func_001baad0(void);
s32 func_001ba9d8(s32);
void func_00f33e48(s32, s32);
void sceVu0UnitMatrix(f32 (*)[4]);
void sceVu0RotMatrixX(f32 (*)[4], f32 (*)[4], f32);
void sceVu0RotMatrixY(f32 (*)[4], f32 (*)[4], f32);
void sceVu0RotMatrixZ(f32 (*)[4], f32 (*)[4], f32);
void sceVu0TransMatrix(f32 (*)[4], f32 (*)[4], f32 *);
void func_00f30638(s32);
void func_00f357b0(void);
void func_00f35080(void);
void func_00f2d480(void);
void func_00f300a8(void);
void func_00f30210(void);
void func_00241c60(s32, s32);

void func_00f307b0(void) {
    s32 *p = &D_00F85088;
    s32 *q;
    D_00FBDA80[0] = 0.0f;
    D_00FBDA80[1] = 0.0f;
    D_00FBDA80[2] = 0.0f;
    D_00FBDA80[3] = 1.0f;
    D_00FBDA90[0] = 0.0f;
    D_00FBDA90[1] = 0.0f;
    D_00FBDA90[2] = 0.0f;
    D_00FBDA90[3] = 1.0f;
    D_00F8C144 = 1.0f;
    D_00FBEBB8 = 0;
    if (*p != 0) {
        *p = 0;
        return;
    }
    func_00242b68(4);
    q = &D_00F8C120;
    *q = func_001baad0();
    func_00f33e48(func_001ba9d8(*q), 1);
    D_00FBB5A0 = *q;
    D_00FBB5A4 = D_00FBDAF0;
    sceVu0UnitMatrix(D_00F8C240);
    sceVu0RotMatrixZ(D_00F8C240, D_00F8C240, D_00FBDA90[2]);
    sceVu0RotMatrixX(D_00F8C240, D_00F8C240, D_00FBDA90[0]);
    sceVu0RotMatrixY(D_00F8C240, D_00F8C240, D_00FBDA90[1]);
    sceVu0TransMatrix(D_00F8C240, D_00F8C240, D_00FBDA80);
    func_00f30638(0);
    func_00f357b0();
    func_00f35080();
    func_00f2d480();
    if (D_00F8C280 != 0) {
        func_00f300a8();
    }
    func_00f30210();
    func_00241c60(0, 4);
    D_00F850F4 = 1;
}

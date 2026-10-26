/* xs_dumbo.x func_00f22b28: matched by hand. */
#include "ovl.h"

typedef struct { f32 v0[4]; f32 v1[4]; f32 v2[4]; f32 v3[4]; } E;
void func_00249420();
void func_00f21a48(s32);
void func_00f21ae8(void);
void func_00f22910(void);
extern f32 D_00F2BAE0;
extern s32 D_00F2BB10[];
extern E D_00F2BB20[];

void func_00f22b28(s32 arg0) {
    f32 a[4];
    f32 b[4];
    f32 n[4];
    s32 i;
    E *p;

    func_00249420(D_00F2BB20);
    for (i = 1; i < 10; i++) {
        p = &D_00F2BB20[i];
        PlatVu0ScaleVectorXYZ(a, (p - 1)->v2, D_00F2BAE0);
        PlatVu0ScaleVectorXYZ(b, p->v2, 1.0f - D_00F2BAE0);
        PlatVu0AddVector(n, a, b);
        PlatVu0Normalize(n, n);
        func_00249420(p, n);
    }
    func_00f21a48(arg0);
    func_00f21ae8();
    func_00f22910();
    D_00F2BB10[174]++;
}

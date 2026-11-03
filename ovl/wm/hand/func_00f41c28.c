/* wm.x func_00f41c28: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[4]; u16 h4; } E41;
typedef struct { u8 pad[0x58]; f32 x58; } C41;
extern s32 D_010807E4;
extern s32 D_00F850BC;
extern s32 D_00F850C0;
extern s32 D_00F87350;
extern s32 D_00F9B2C4;
extern s32 D_00F9B2C8;
extern s32 D_00F87310;
extern s32 D_00F85000[];
extern s32 D_00F850E0;
extern f32 D_00F85200[4][4];
extern f32 D_00F9B1DC;
extern s32 D_00F9B1E0;
extern s32 D_00F9B2E0;
extern s32 D_002C5958;
extern s32 D_00F850D8;
void func_00114820(void);
void func_00f309d0(s32);
void func_00f3a4c8(void);
void func_00f3e3a0(void);
void func_00f3f2c0(void);
f32 *func_00f2c848(void);
f32 *func_00f2c878(void);
#ifdef KH1_PS2 /* portability rule 11: the EE passes the floats in their own registers */
void func_00f2c8a8(void);
#else
f32 func_00f2c8a8();
static __inline__ void ee_00f2c8a8() { func_00f2c8a8(); }
#undef func_00f2c8a8
#define func_00f2c8a8 ee_00f2c8a8
#endif
void func_00f32318(f32 *, f32 *, f32);
void func_00f404c8(s32, s32);
void func_001bfac8(void);
E41 *func_00f2ba68(s32, s32 *);
s32 func_001bafb0(s32, s32 *);
s32 func_001ba228(s32);
void func_001c01b0(s32, void (*)(void), ...);
void func_00f41990(void);
void func_00f41458(void);
void func_00f344e0(s32);
C41 *func_00f3b4e0(s32);
void sceVu0CopyMatrix(f32 (*)[4], f32 (*)[4]);
void sceVu0UnitMatrix(f32 (*)[4]);
void sceVu0TransMatrix(f32 (*)[4], f32 (*)[4], f32 *);
void sceVu0RotMatrix(f32 (*)[4], f32 (*)[4], f32 *);
void func_001bf888(f32 *, f32 (*)[4]);
void func_001bf710(f32 *, f32 *, f32 *, f32);
void func_001bf3e8(f32 (*)[4], f32 *);
void func_00f2c7e8(f32);
void func_00f33998(void);
s32 func_00f23550(s32);
void func_00f46cb8(s32, s32);
void func_00f3f358(void);
void func_00f201c0(void);
void func_00242b68(s32);
void func_00f20228(s32);

void func_00f41c28(void) {
    f32 v[4];
    f32 a[4];
    f32 pad20[4];
    f32 t[4];
    f32 m[4][4];
    f32 r[4][4];
    u8 padC0[0x60];
    f32 tb[4];
    f32 ta[4];
    f32 rot[4];
    f32 q[4];
    f32 q0[4];
    f32 q1[4];
    f32 *p;
    f32 *b;
    s32 i;
    f32 f;
    E41 *e;
    s32 k, y, x;
    f32 g, u, w, z;
    C41 *c;

    func_00114820();
    func_00f309d0(1);
    func_00f3a4c8();
    func_00f3e3a0();
    func_00f3f2c0();
    p = func_00f2c848();
    b = func_00f2c878();
    for (i = 0; i < 4; i++) {
        v[i] = p[i];
        a[i] = b[i];
    }
    func_00f2c8a8();
    D_010807E4 = 1;
    z = 0.0f;
    for (i = 0; i < 20; i++) {
        g = i;
        t[0] = (z - a[0]) * g / 20.0f + a[0];
        t[1] = (z - a[1]) * g / 20.0f + a[1];
        t[2] = (z - a[2]) * g / 20.0f + a[2];
        func_00f32318(v, t, g * -0.4f / 20.0f + 0.4f);
        func_00f404c8(D_00F850E0, 0);
        func_001bfac8();
    }
    t[0] = z;
    t[3] = 1.0f;
    t[1] = t[0];
    t[2] = t[0];
    func_00f32318(p, t, t[0]);
    if (D_00F850BC == 0 && D_00F850C0 == 0 && D_00F87350 == 0) {
        x = 496;
        y = 168;
        e = func_00f2ba68(D_00F9B2C4, &D_00F87310);
        k = 0;
        if (func_001bafb0(D_00F9B2C4, &D_00F87310)) {
            func_001c01b0(-1, func_00f41990, x - D_00F85000[18], 168, 3, 0, 0, 18);
            y = 200;
            k = 4;
        }
        if (e) {
            func_001c01b0(-1, func_00f41990, x - D_00F85000[8], y, 1, k, func_001ba228(e->h4), 12);
        }
    }
    D_010807E4 = 1;
    func_00f344e0(1);
    sceVu0CopyMatrix(m, D_00F85200);
    c = func_00f3b4e0(D_00F9B2C8);
    ta[0] = z;
    ta[2] = z;
    ta[1] = z;
    ta[3] = 1.0f;
    ta[2] = -c->x58;
    ta[0] = 2000.0f;
    tb[2] = 6000.0f;
    rot[0] = z;
    rot[1] = z;
    rot[2] = z;
    rot[3] = 1.0f;
    tb[0] = z;
    tb[1] = z;
    tb[3] = 1.0f;
    sceVu0UnitMatrix(r);
    sceVu0TransMatrix(r, r, ta);
    sceVu0RotMatrix(r, r, rot);
    sceVu0TransMatrix(r, r, tb);
    func_001bf888(q0, m);
    func_001bf888(q1, r);
    for (i = 0; i < 60; i++) {
        f = i;
        u = f / 60.0f;
        w = -f / 60.0f + 1.0f;
        func_00f2c7e8(w);
        D_00F9B1DC = w;
        sceVu0UnitMatrix(D_00F85200);
        func_001bf710(q, q0, q1, u);
        func_001bf3e8(D_00F85200, q);
        D_00F85200[3][0] = (r[3][0] - m[3][0]) * f / 60.0f + m[3][0];
        D_00F85200[3][1] = (r[3][1] - m[3][1]) * f / 60.0f + m[3][1];
        D_00F85200[3][2] = (r[3][2] - m[3][2]) * f / 60.0f + m[3][2];
        func_001bfac8();
    }
    func_00f33998();
    sceVu0CopyMatrix(D_00F85200, r);
    func_001bfac8();
    func_001bfac8();
    D_00F9B1E0 = 0;
    if (D_00F850BC != 0) D_00F850BC = 0;
    k = func_00f23550(D_00F9B2C4);
    D_002C5958 |= 8;
    D_00F9B2E0 = k;
    func_001c01b0(-1, func_00f41458);
    func_00f46cb8(65, 1);
    if (k < 0) {
        if (k >= -2) {
            D_00F850D8 = D_00F9B2C4;
            func_00f3f358();
            func_00f201c0();
        }
    }
    func_00f3f358();
    func_00242b68(4);
    func_00f20228(k);
    for (;;) {
        func_00f404c8(D_00F850E0, 1);
        func_001bfac8();
    }
}

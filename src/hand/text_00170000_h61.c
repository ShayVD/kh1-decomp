#include "common.h"

typedef struct { f32 x, y, z, w; } V4;
typedef struct { void (*fn)(void); s32 x4; } Fn8;
typedef struct { u8 pad[0xd0]; V4 xd0; } ActD0;
typedef struct Cam {
    u8 pad0[0x10];
    V4 x10;         /* 0x10 */
    u8 pad20[0x3c - 0x20];
    f32 x3c;        /* 0x3C */
    u8 pad40[0xd0 - 0x40];
    V4 xd0;         /* 0xD0 */
    u8 pade0[0x490 - 0xe0];
    V4 x490;        /* 0x490 */
} Cam;
typedef struct { f32 x0, x4, x8, xc, x10; s32 x14; } Shk;
typedef struct Z {
    V4 x0;
    s32 x10;
    u8 pad14[0x10];
    f32 x24[4];
    f32 x34, x38, x3c, x40;
} Z;
typedef struct { s32 x0; f32 x4; } S26F0;
typedef struct { u32 b0:1; u32 b1:1; u32 r:30; } BF;

extern s32 D_002E27A8;
extern V4 D_005758D0, D_005758E0, D_005758A0, D_005758B0;
extern V4 D_002E2780, D_002E2790;
extern f32 D_005758C4;
extern f32 D_005758C0;
extern s32 D_00575890;
extern Fn8 D_0036245C[];
extern Fn8 D_00362458[];
extern V4 D_00362670;
extern ActD0 *D_002E26A0;
extern u8 D_002C58D0[];
extern Shk D_00575900;
extern f32 D_002BBDFC;
extern f32 D_00362684;
extern V4 D_00362680;
extern V4 D_00362660;
extern f32 D_0036266C;
extern f32 D_0036268C;
extern Cam *D_00575894;
extern V4 D_00362560, D_00362570;
extern V4 D_003625A0, D_003625B0;
extern V4 D_003625F0;
extern Z D_005759B0;
extern V4 D_002C58A0;
extern S26F0 D_003626F0;
extern s32 D_003623F0;
extern f32 D_003623F4, D_003623F8;
extern BF D_002C5958;

void func_002675a8(V4 *, V4 *);
void func_002672f8(V4 *, void *, V4 *);
void func_00267530(V4 *, V4 *, V4 *);
void func_00267518(V4 *, V4 *, V4 *);
void func_00267810(V4 *, void *, f32);
void func_00267768(V4 *, void *, f32);
void func_00267560(V4 *, V4 *, f32);
void func_00267e90(f32, V4 *, V4 *);
void func_002674f0(V4 *, V4 *, V4 *, f32);
s32 func_00177440(V4 *, V4 *);
f32 sinf(f32);
f32 cosf(f32);
f32 fabsf(f32);
f32 func_00120c88(f32);
f32 func_00120bf8(V4 *);
void func_00121fc4(V4 *, V4 *);
f32 func_00124d28(V4 *, V4 *);
s32 func_00177608(V4 *, V4 *, V4 *);
s32 func_00177218(Cam *);
s32 func_00177288(Cam *);
f32 func_00177680(V4 *, V4 *);
f32 func_001779e8(V4 *, V4 *, f32);
void func_0017d628(void);
void func_0017de80(void);
void func_00176f08(s32, f32);

void func_00176f08(s32 st, f32 t) {
    if (D_002E27A8 == 0) {
        func_002675a8(&D_005758D0, &D_002E2780);
        func_002675a8(&D_005758E0, &D_002E2790);
        D_005758C4 = 0.0f;
        D_00575890 |= 1;
    } else {
        if (D_005758C4 > 0.0f) {
            func_002675a8(&D_005758A0, &D_002E2780);
            func_002675a8(&D_005758B0, &D_002E2790);
        } else {
            func_002675a8(&D_005758A0, &D_005758D0);
            func_002675a8(&D_005758B0, &D_005758E0);
        }
        D_005758C0 = D_005758C4 = t;
        D_00575890 &= ~1;
    }
    if (D_0036245C[D_002E27A8].fn) D_0036245C[D_002E27A8].fn();
    D_002E27A8 = st;
    D_00575890 |= 2;
}

s32 func_00177740(V4 *a0) {
    V4 m[4];
    V4 c, l, r, u, d, dir;
    func_002675a8(&c, &D_00362670);
    c.x = c.z = 0.0f;
    func_002672f8(&c, &D_002E26A0->xd0, &c);
    func_00267530(&dir, &c, a0);
    func_00267810(m, D_002C58D0, 0.26179939f);
    func_002672f8(&l, m, &dir);
    func_00267518(&l, &l, &D_005758D0);
    func_00267810(m, D_002C58D0, -0.26179939f);
    func_002672f8(&r, m, &dir);
    func_00267518(&r, &r, &D_005758D0);
    func_002675a8(&u, &c);
    u.y += 50.0f;
    func_002675a8(&d, &c);
    d.y -= 50.0f;
    if (func_00177440(&D_005758D0, &c) && func_00177440(&D_005758D0, &l)
        && func_00177440(&D_005758D0, &r) && func_00177440(&D_005758D0, &u)
        && func_00177440(&D_005758D0, &d)) return 0;
    return 1;
}

void func_00178890(void) {
    f32 t;
    f32 u;
    s32 m;
    if (D_00575900.xc <= 0.0f) return;
    D_00575900.xc -= D_002BBDFC;
    m = D_00575900.x14;
    if (m >= 0 && D_00575900.x14 < 2) {
        u = 1.0f - D_00575900.xc / D_00575900.x10;
        u = sinf(u * 3.1415928f * 0.5f);
        if (D_00575900.x14 == 1) D_00362684 = func_00120c88(D_00575900.x0 + D_00575900.x4 * u);
        else if (D_00575900.x14 == 0) D_00362684 = func_00120c88(D_00575900.x0 - D_00575900.x4 * u);
    } else {
        if (fabsf(D_00575900.x4) > 0.087266453f) {
            t = D_00575900.xc / D_00575900.x10;
            t = cosf(t * 3.1415928f);
            if (0.0f < t) D_00362680.y = func_00120c88(D_00575900.x0 + D_00575900.x4);
            t = fabsf(t);
            t = t * 0.7f + 0.3f;
            D_00362680.w = D_00575900.x8 * t;
            D_00362680.x = func_00120c88(D_00362660.x + (1.0f - t) * 1.0471975f);
        }
    }
    if (D_00575900.xc <= 0.0f) {
        D_00575900.xc = 0.0f;
        D_0036268C = D_0036266C;
    }
}

void func_0017a510(void) {
    V4 v, w;
    if (D_00575890 & 2) D_00575890 &= ~2;
    if (0.0f < D_005758C4) {
        func_002672f8(&D_005758D0, &D_00575894->xd0, &D_00362560);
    } else {
        func_002672f8(&v, &D_00575894->xd0, &D_00362560);
        func_00267530(&v, &v, &D_005758D0);
        func_00121fc4(&v, &v);
        v.w -= 100.0f;
        if (0.0f < v.w) {
            func_00267e90(v.w * 0.3f, &v, &v);
            func_00267518(&D_005758D0, &D_005758D0, &v);
        }
    }
    func_002672f8(&D_005758E0, &D_00575894->xd0, &D_00362570);
    if (func_00177608(&w, &D_005758E0, &D_005758D0)) func_002675a8(&D_005758D0, &w);
    D_00362684 = func_00124d28(&D_005758D0, &D_005758E0);
    if (!func_00177218(D_00575894)) func_00176f08(1, 30.0f);
}

void func_0017a7b0(void) {
    V4 v, w;
    if (D_00575890 & 2) D_00575890 &= ~2;
    if (0.0f < D_005758C4) {
        func_002672f8(&D_005758D0, &D_00575894->xd0, &D_003625A0);
    } else {
        func_002672f8(&v, &D_00575894->xd0, &D_003625A0);
        func_00267530(&v, &v, &D_005758D0);
        if (100.0f < v.y) v.y = (v.y - 100.0f) * 0.3f;
        else if (v.y < -100.0f) v.y = (v.y + 100.0f) * 0.3f;
        else v.y = 0.0f;
        func_00267518(&D_005758D0, &D_005758D0, &v);
    }
    func_002672f8(&D_005758E0, &D_00575894->xd0, &D_003625B0);
    if (func_00177608(&w, &D_005758E0, &D_005758D0)) func_002675a8(&D_005758D0, &w);
    D_00362684 = func_00124d28(&D_005758D0, &D_005758E0);
    if (!func_00177288(D_00575894)) func_00176f08(1, 30.0f);
}

void func_0017dd00(void) {
    V4 v;
    f32 l;
    if (D_00575890 & 2) {
        D_00575890 &= ~2;
        func_00177680(&D_005758E0, &D_00575894->x10);
        D_005758E0.y -= 150.0f;
    }
    if (D_00575890 & 1) D_00575890 &= ~1;
    if (D_00575890 & 4) D_00575890 &= ~4;
    func_00177680(&v, &D_00575894->x10);
    v.y -= 150.0f;
    func_00267530(&v, &v, &D_005758E0);
    if (func_00120bf8(&v) < 0.0f) l = 0.0f;
    else if (200.0f < func_00120bf8(&v)) l = 200.0f;
    else l = func_00120bf8(&v);
    func_00267560(&v, &v, l / 200.0f);
    func_00267518(&D_005758E0, &D_005758E0, &v);
    func_00267518(&D_005758D0, &D_005758E0, &D_003625F0);
}

void func_0017df08(void) {
    Z *z = &D_005759B0;
    V4 v;
    V4 m[4];
    f32 a;
    if (z->x10 == 4) return;
    if (D_00575890 & 2) {
        f32 r = func_00124d28(&D_002E2780, &D_002E2790);
        z->x3c = r;
        z->x38 = D_005758C0;
        z->x34 = D_005758C0;
        D_00362680.y = r;
        z->x40 = z->x24[z->x10];
        D_00575890 &= ~2;
    }
    if (D_00575890 & 1) D_00575890 &= ~1;
    if (D_00575890 & 4) D_00575890 &= ~4;
    func_00267530(&v, &z->x0, &D_005758E0);
    func_00121fc4(&v, &v);
    func_00267560(&v, &v, v.w * 0.3f);
    func_00267518(&D_005758E0, &D_005758E0, &v);
    if (0.0f < z->x34) {
        z->x34 -= D_002BBDFC;
        a = z->x3c + sinf((f32)(1.0 - z->x34 / z->x38) * 3.1415928f * 0.5f) * z->x40;
    } else {
        a = z->x3c + z->x40;
    }
    func_00267768(m, D_002C58D0, func_00120c88(D_00362680.x));
    func_00267810(m, m, func_00120c88(a));
    func_002675a8(&v, &D_002C58A0);
    v.z = D_00362680.w;
    func_002672f8(&v, m, &v);
    func_00267518(&D_005758D0, &D_005758E0, &v);
    D_00362680.y = func_00124d28(&D_005758D0, &D_005758E0);
}

void func_0017e910(void) {
    f32 a;
    if (!D_003626F0.x0) return;
    D_00362680.y = D_00575894->x3c + D_003626F0.x4;
    if (func_001779e8(&D_002E2780, &D_002E2790, D_00362680.y) < 200.0f) {
        a = 0.0f;
        while (a < 3.1415928f) {
            a += 0.31415928f;
            if (func_001779e8(&D_002E2780, &D_002E2790, D_00362680.y + a) >= D_00362680.w - 10.0f) break;
            if (func_001779e8(&D_002E2780, &D_002E2790, D_00362680.y - a) >= D_00362680.w - 10.0f) break;
        }
    }
    func_00176f08(1, 0.0f);
}

s32 func_0017ecf8(void) {
    V4 v;
    f32 t, u;
    if (D_003623F0) { D_003623F0 = 2; return 0; }
    if (D_00575894) {
        func_00267530(&v, &D_00575894->x10, &D_00575894->x490);
        D_003623F4 = func_00120bf8(&v) / D_002BBDFC;
        v.y = 0.0f;
        D_003623F8 = func_00120bf8(&v) / D_002BBDFC;
    }
    if (!D_002C5958.b1) {
    if (D_00362458[D_002E27A8].fn == 0) return 0;
    func_0017d628();
    func_0017de80();
    D_00362458[D_002E27A8].fn();
    if (0.0f < D_005758C4) {
        t = D_005758C4 - D_002BBDFC;
        D_005758C4 = t;
        if (0.0f < t) {
            u = t / D_005758C0;
            u = 1.0f - cosf(u * 3.1415928f * 0.5f);
            func_002674f0(&D_002E2780, &D_005758A0, &D_005758D0, u);
            func_002674f0(&D_002E2790, &D_005758B0, &D_005758E0, u);
        } else {
            D_005758C4 = 0.0f;
            func_002675a8(&D_002E2780, &D_005758D0);
            func_002675a8(&D_002E2790, &D_005758E0);
        }
    } else {
        func_002675a8(&D_002E2780, &D_005758D0);
        func_002675a8(&D_002E2790, &D_005758E0);
    }
    }
    return 0;
}

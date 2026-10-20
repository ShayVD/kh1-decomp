#include "common.h"
#include "data/bss_0057.h"

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
extern V4 D_005758D0, D_005758E0;
V4 D_005758A0 ALIGNED(16);
V4 D_005758B0 ALIGNED(16);
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

/* Camera-state functions that follow func_00176f08 / func_00177358 in the
 * original file (both must be defined above them). */
typedef struct { s32 x0; u8 pad4[0x3c - 4]; f32 x3c; u8 pad40[0x64 - 0x40]; f32 x64; u8 pad68[0x70 - 0x68]; s32 x70; u8 pad74[0xd0 - 0x74]; V4 xd0; } ActB;
typedef struct { u32 x0, x4; u64 x8; u8 pad10[0x44 - 0x10]; f32 x44; } PadB;
typedef struct { V4 v; f32 x10, x14, x18; } CamPt;
extern PadB D_002C5BB0;
extern CamPt *D_00362434;
extern void *D_00362438;
f32 D_00575820 ALIGNED(16);
f32 D_00575824 ALIGNED(4);
s32 D_00575828 ALIGNED(8);
extern V4 D_003624E0;
extern V4 D_003624F0;
extern f32 D_00362500;
extern u32 D_002C5960;
extern s32 D_00575920; /* src/data/bss_0057.c: S920 D_00575920 */
extern s32 D_00362420;
void func_00124c68(f32);
void func_0012fc58(void);
s32 func_001375d8(ActB *);
void func_001315c0(void *, s32, void *, f32);
void func_0011d768(s32);

#define D_00575894 (*(ActB **)&D_00575894)

s32 func_00177358(ActB *o) {
    if ((D_002C5960 >> 4) & 1) return 0;
    switch (o->x70) {
    case 0: case 8: case 24: return 1;
    }
    return 0;
}

void func_00179700(void) {
    if (D_00575890 & 2) {
        D_00575820 = 0.0f;
        D_00575824 = D_005758C0;
        func_00124c68(53.0f);
        D_003624E0.y = D_00362500;
        D_00575828 = 0;
        func_0012fc58();
        D_00575890 &= ~2;
    }
    if (D_00575824 > 0.0f) {
        D_00575824 -= D_002BBDFC;
        if (D_00575824 <= D_005758C0 * 0.6f && !D_00575828) {
            if (D_00575824 > 0.0f) D_00575894->x64 = -1.0f / D_00575824;
            else D_00575894->x64 = -1.0f;
            D_00575828 = 1;
        }
        if (D_00575824 <= 0.0f) {
            D_00575894->x0 &= ~1;
            D_00575824 = 0.0f;
        }
    }
    func_002672f8(&D_005758D0, &D_00575894->xd0, &D_003624E0);
    D_003624F0.y = D_00362500 + sinf(D_00575820) * 100.0f;
    D_003624F0.z = D_003624E0.z - cosf(D_00575820) * 100.0f;
    func_002672f8(&D_005758E0, &D_00575894->xd0, &D_003624F0);
    func_002675a8(&D_00362680, &D_00362660);
    D_00362680.y = func_00124d28(&D_005758D0, &D_005758E0);
    D_00575820 += D_002C5BB0.x44 * 0.0523598725f * D_002BBDFC;
    if (D_00575820 > 1.047197491f) D_00575820 = 1.047197491f;
    else if (D_00575820 < -1.396263272f) D_00575820 = -1.396263272f;
    if ((D_002C5BB0.x8 & 0x8200) || !func_00177358(D_00575894) || func_001375d8(D_00575894)) {
        if (!D_00362434 && !D_00362438) func_00176f08(1, 30.0f);
        else func_00176f08(9, 0.0f);
    }
}

#define D_002C5958 (*(u32 *)&D_002C5958)

void func_0017ae48(void) {
    V4 d;
    f32 len;

    if (D_00575890 & 2) {
        D_00575890 &= ~2;
        func_001315c0(D_00575894, 0x8003, &D_005758E0, 0.0f);
    }
    if (D_00575890 & 1) D_00575890 &= ~1;
    if (D_00575890 & 4) D_00575890 &= ~4;
    func_002675a8(&D_005758D0, D_00362434);
    func_001315c0(D_00575894, 0x8003, &d, 0.0f);
    func_00267530(&d, &d, &D_005758E0);
    len = func_00120bf8(&d) < 0.0f ? 0.0f : (func_00120bf8(&d) > 200.0f ? 200.0f : func_00120bf8(&d));
    len = len / 200.0f;
    func_00267560(&d, &d, len * 0.3f);
    func_00267518(&D_005758E0, &D_005758E0, &d);
    func_00267530(&d, &D_005758E0, &D_005758D0);
    if ((len = func_00120bf8(&d)) < 0.0f) func_00124c68(D_00362434->x14);
    else if (D_00362434->x18 < len) func_00124c68(D_00362434->x10);
    else func_00124c68(D_00362434->x14 - (D_00362434->x14 - D_00362434->x10) * (len / D_00362434->x18));
    if ((&D_002C5BB0)->x8 & 0x3000) {
        if (!D_00575920) func_0011d768(4);
    }
    if ((u32)(&D_002C5BB0)->x8 & 0x8000) {
        if (func_00177358(D_00575894) && !func_001375d8(D_00575894) && !((D_002C5958 >> 13) & 1) && !D_00362420)
            func_00176f08(2, D_002BBDFC);
    }
}
#undef D_002C5958
#undef D_00575894

typedef struct { f32 x, y, z, len; } Seg;
typedef struct Path {
    s32 n; f32 x4; f32 x8; f32 xc; u8 pad10[4]; f32 x14; s32 flags; u8 pad1c[4]; Seg seg[1];
} Path;
typedef struct Cam940 {
    V4 x0; V4 x10; V4 x20; V4 x30;
    s32 x40; s32 x44; f32 x48; f32 x4c; f32 x50; f32 x54; f32 x58; f32 x5c; f32 x60;
    u8 x64; u8 x65; u8 x66;
} Cam940;
extern Cam940 D_00575940;
void func_0017b308(void *, Seg *, s32, s32, s32);
void func_0017b250(void *, void *, f32);
f32 func_00120c18(V4 *);
void func_002673b8(V4 *, V4 *);
void func_0017b170(void);
void func_0017c8e8(void);
void func_0017c9a8(void);
void func_0017cf08(void);
void func_0017ba80(s32);
s32 func_0017b7e8(void);
void func_0017b740(V4 *, V4 *);
typedef struct { V4 a, b; s32 on; } S26C0;
extern S26C0 D_003626C0;

void func_0017b200(void) {
    func_002675a8(&D_003626C0.a, &D_005758D0);
    func_002675a8(&D_003626C0.b, &D_005758E0);
    D_003626C0.on = 1;
}

#define D_00575894 (*(ActB **)&D_00575894)
#define D_00362438 (*(Path **)&D_00362438)
#define D_002C5958 (*(u32 *)&D_002C5958)

void func_0017d238(void) {
    V4 v;
    f32 m[4][4];
    Path *path = D_00362438;
    f32 step, len;

    func_002672f8(&D_00575940.x30, &D_00575894->xd0, &D_00362670);
    func_00267530(&v, &D_00575940.x30, &D_005758D0);
    D_00575940.x58 = func_00120c18(&v);
    if (D_00575890 & 2) {
        D_00575890 &= ~2;
        func_0017b170();
    }
    if (D_00575890 & 1) {
        D_00575890 &= ~1;
        if (!(D_00575890 & 4)) func_0017c8e8();
    }
    if (D_00575890 & 4) {
        D_00575890 &= ~4;
        D_00575940.x65 = 1;
    }
    if (!D_00575920 || (path->flags & 0x10)) func_0017c9a8();
    else func_0017cf08();
    if (D_00575940.x65 != 0) {
        if (D_00575940.x65 == 1) {
            func_0017ba80(2);
            D_00575940.x40 = D_00575940.x44;
            D_00575940.x48 = D_00575940.x4c;
            func_0017b308(m, path->seg, path->n, D_00575940.x40, path->flags & 1);
            func_0017b250(&D_00575940, m, D_00575940.x48);
            func_002675a8(&D_00575940.x20, &D_005758D0);
            D_00575940.x65++;
            D_00575940.x66 = 0;
        }
        if (func_0017b7e8() || (path->flags & 0x20)) {
            step = D_002BBDFC * 8.0f;
            func_00267530(&v, &D_00575940.x0, &D_00575940.x20);
            len = func_00120bf8(&v);
            func_002673b8(&v, &v);
            func_00267560(&v, &v, step);
            func_00267518(&D_00575940.x20, &D_00575940.x20, &v);
            if (len < 50.0f) D_00575940.x65 = 0;
        }
        if (path->flags & 2) func_0017b740(&D_005758D0, &D_00575940.x20);
        else func_002675a8(&D_005758D0, &D_00575940.x20);
    } else {
        if (path->flags & 2) func_0017b740(&D_005758D0, &D_00575940.x0);
        else func_002675a8(&D_005758D0, &D_00575940.x0);
    }
    if ((u32)(&D_002C5BB0)->x8 & 0x8000) {
        if (func_00177358(D_00575894) && !func_001375d8(D_00575894) && !((D_002C5958 >> 13) & 1) && !D_00362420) {
            func_00176f08(2, D_002BBDFC);
            func_0017b200();
        }
    }
}
#undef D_002C5958
#undef D_00362438
#undef D_00575894

extern f32 D_003624B8;
f32 func_00177680(V4 *a, V4 *b) {
    V4 p, q;
    func_002675a8(&q, b);
    q.y -= 10.0f;
    func_002675a8(&p, b);
    p.y += D_003624B8;
    if (func_00177608(a, &q, &p)) {
        func_00267530(&p, a, b);
        return func_00120bf8(&p);
    }
    func_002675a8(a, &p);
    return 0.0f;
}


typedef struct {
    u8 pad0[0x10]; V4 x10; u8 pad20[0x10]; V4 x30; u8 pad40[0x30]; s32 x70; u8 pad74[0x34C]; V4 x3c0;
} CamC4;
typedef struct { s32 x0; f32 x4; u8 pad8[8]; V4 x10; } S5920;

#define D_00575894 (*(CamC4 * *)&D_00575894)
extern V4 D_005758D0;
extern V4 D_005758E0;
extern V4 D_002C58A0;
#define D_002C58D0 (*(V4 *)&D_002C58D0)
extern f32 D_002BBDFC;
extern V4 D_00362680;
#define D_00575890 (*(u32 *)&D_00575890)
extern V4 D_00362530;
extern V4 D_00362540;
extern f32 D_00362550;
extern u8 D_002E31B0[];
#define D_00575920 (*(S5920 *)&D_00575920)
extern u32 D_002C5BB8;
#define D_002C5958 (*(u32 *)&D_002C5958)

f32 func_00120c88(f32);
f32 func_00120c18(V4 *);
void func_00121fc4(V4 *, V4 *);
f32 func_00124d28(V4 *, V4 *);
f32 func_0012eca8(void *, V4 *);
void func_00176f08(s32, f32);
s32 func_001772f8(CamC4 *);
s32 func_00177608(V4 *, V4 *, V4 *);
f32 func_00177680(V4 *, V4 *);
void func_00179d30(void);
f32 cosf(f32);
void func_002674f0(V4 *, V4 *, V4 *, f32);
void func_00267518(V4 *, V4 *, V4 *);
void func_00267530(V4 *, V4 *, V4 *);
void func_00267560(V4 *, V4 *, f32);
void func_002675a8(V4 *, V4 *);

/* callees that must be DEFINED above (real bodies: func_00176f08 in src/hand/text_00170000_h61.c, func_00177680 in src/hand/text_00170000_h38.c); stubs here for testing */
void func_00179ee8(void) {
    V4 m[4];
    V4 a;
    V4 b;
    V4 c;
    V4 d;
    V4 e;
    V4 f;
    f32 A, B, l, h, u, k;
    s32 hit;
    if (D_00575890 & 2) D_00575890 &= ~2;
    func_00267810(m, &D_002C58D0, D_00362680.y);
    func_002675a8(&m[3], &D_00575894->x10);
    func_002675a8(&e, &D_00362530);
    A = e.y + D_00362550;
    e.y = A;
    func_002672f8(&a, m, &e);
    A = func_0012eca8(D_002E31B0, &c);
    func_00267530(&e, &c, &a);
    B = e.y;
    e.y = 0.0f;
    func_00121fc4(&e, &e);
    func_00267560(&e, &e, A + 100.0f);
    A = -B * 0.5f;
    e.y = A;
    func_00267518(&b, &c, &e);
    func_00267530(&e, &b, &a);
    l = func_00120c18(&e);
    A = e.y;
    h = fabsf(A);
    if (l < h + h) {
        if (h < l) {
            A *= (h + h - l) / h;
            e.y = A;
        }
        a.y += A * 0.5f;
    }
    func_002675a8(&f, &D_005758D0);
    func_00267530(&e, &a, &D_005758D0);
    A = 0.0f;
    B = e.y;
    e.y = A;
    func_00121fc4(&e, &e);
    e.w -= 75.0f;
    if (A < e.w) {
        e.w *= 0.8999999911f;
        func_00267560(&e, &e, e.w);
        func_00267518(&D_005758D0, &D_005758D0, &e);
    }
    B *= 0.8999999911f;
    D_005758D0.y += B;
    func_001315c0(D_00575894, 0x8003, &d, A);
    hit = func_00177608(&D_005758D0, &d, &D_005758D0) != 0;
    func_002672f8(&e, m, &D_00362540);
    B = func_00120c88(D_00362680.y - func_00124d28(&D_005758D0, &e));
    u = func_00120c88(func_00124d28(&D_005758D0, &b) - D_00362680.y);
    if (B + 0.08726645447f < u) k = u - (B + 0.08726645447f);
    else if (u < B + -0.08726645447f) k = u + (0.08726645447f - B);
    else k = A;
    k *= 0.5f;
    if (0.1745329089f < k) k = 0.1745329089f;
    else if (k < -0.1745329089f) k = -0.1745329089f;
    D_00362680.y = func_00120c88(D_00362680.y + k);
    func_00267530(&e, &b, &D_005758D0);
    l = func_00120c18(&e);
    e.w = 1.0f;
    e.x = 0.0f;
    e.z = -l;
    func_00267810(m, &D_002C58D0, D_00362680.y);
    func_002675a8(&m[3], &D_002C58A0);
    func_002672f8(&e, m, &e);
    func_00267518(&D_005758E0, &D_005758D0, &e);
    D_00362680.y = func_00124d28(&D_005758D0, &D_005758E0);
    func_00179d30();
    if (D_00575920.x4 > 0.0f) {
        D_00575920.x4 -= D_002BBDFC;
        if (D_00575920.x4 < 0.0f) D_00575920.x4 = 0.0f;
        else {
            A = D_00575920.x4 / 60.0f;
            func_002674f0(&D_005758E0, &D_005758E0, &D_00575920.x10, cosf(A * 3.141592801f * 0.5f));
        }
    }
    if (!func_001772f8(D_00575894) && !hit) {
        func_00177680(&e, &D_005758D0);
        B = D_00575894->x10.y - e.y;
        if (30.0f < B) {
            if (150.0f < B) B = 150.0f;
            D_00362550 = -(fabsf(B - 30.0f) / 120.0f * 170.0f);
        } else {
            B = c.y - D_005758D0.y;
            if (B < -200.0f) {
                if (B < -400.0f) B = -400.0f;
                D_00362550 = fabsf(B - -200.0f) / 200.0f * 20.0f;
            } else {
                D_00362550 = 0.0f;
            }
        }
    }
    if (D_002C5BB8 & 0x8000) {
        if (func_00177358(D_00575894) && !func_001375d8(D_00575894) && !((D_002C5958 >> 13) & 1)) func_00176f08(2, 30.0f);
    }
}
#undef D_00575894
#undef D_002C58D0
#undef D_00575890
#undef D_00575920
#undef D_002C5958
#include "data/data_002E.h"
#include "data/data_0036.h"

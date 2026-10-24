/* The field camera's core and its modes, default flags (docs/modules.md
 * "Session 51"): func_00176f08 changes the mode D_002E27A8 (it keeps the old
 * position / target D_005758A0 / B0 to blend from, calls the old mode's leave
 * function of D_0036245C and sets D_00575890's "changed" bit); tests on the
 * player D_00575894 (its state x70, its speeds D_003623F4 / F8, which mode a
 * state wants: func_00177218 ... func_001773b0); rays and wall tests through
 * the collision (func_00177440 ... func_001779e8); and the mode functions of
 * the table D_00362458 ({frame, leave}, 12 modes): 1 func_00178ef8, 2
 * func_00179700 (leave func_00179690), 3 func_00179ee8, 4 func_0017a510, 5
 * func_0017a6c0, 6 func_0017a7b0, 8 func_0017a958, 11 func_00179a80, with
 * their helpers.  Modes 7, 9 and 10 are in campath.c and camctl.c.
 * fieldcam.nostrict.c has five more.  Each section names the file its code
 * came from.  Read from the code, not proved by a boot. */
#include "common.h"
#include "data/bss_0057.h"
#include "data/types/text_00170000_h61.h"
#include "data/pieces/D_003626F0.h"
#include "data/pieces/D_002E2790.h"
#include "data/pieces/D_002E2780.h"
#include "data/pieces/D_002E26A0.h"
#include "data/pieces/D_002C58D0.h"
#include "data/pieces/D_002C58A0.h"
#include "m2c.h"
#include "data/pieces/D_003626C0.h"
#include "data/pieces/D_00362424.h"
#include "data/pieces/D_00362428.h"
#include "data/pieces/D_0036242C.h"
#include "data/pieces/D_00362430.h"
#include "data/pieces/D_00362434.h"
#include "data/pieces/D_00362438.h"
#include "data/pieces/D_0036243C.h"
#include "data/pieces/D_00362710.h"
#include "data/types/text_00170000_h38.h"
#include "data/types/text_00170000_h38_p.h"
#include "data/pieces/D_0036244C.h"
#include "data/pieces/D_00362450.h"
#include "data/pieces/D_00362454.h"
#include "data/types/text_00170000_h11_p4.h"
#include "data/types/text_00170000_h11.h"
#include "data/pieces/D_002C5960.h"
#include "data/types/text_00170000_h11_p3.h"
#include "data/pieces/D_003626F8.h"
#include "data/pieces/D_0035BD40.h"
#include "data/types/text_00160000_c04.h"
#include "data/types/text_00170000_b06.h"
#include "data/pieces/D_002E31B0.h"

/* func_00176f08 (from hand/text_00170000_h61.c). */
extern s32 D_002E27A8;
extern f32 D_005758D0[4];
extern f32 D_005758E0[4];
V4 D_005758A0 ALIGNED(16);
V4 D_005758B0 ALIGNED(16);
extern f32 D_005758C4;
extern s32 D_00575890;
extern Fn8 D_0036245C[];
void func_002675a8(V4 *, V4 *);
#define D_005758D0 (*(V4 (*)) &D_005758D0)
#define D_005758E0 (*(V4 (*)) &D_005758E0)
/* Camera-state functions that follow func_00176f08 / func_00177358 in the
 * original file (both must be defined above them). */
/* callees that must be DEFINED above (real bodies: func_00176f08 in src/hand/text_00170000_h61.c, func_00177680 in src/hand/text_00170000_h38.c); stubs here for testing */
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
#undef D_005758D0
#undef D_005758E0

/* func_00177070 (from auto/text_00170000.c). */
extern void *D_00575894;
s32 func_00219308();
s32 func_00177070(void) {
    s32 var_v0;

    var_v0 = 0;
    if (func_00219308() == 0) {
        var_v0 = M2C_FIELD(D_00575894, s32 *, 0x70) != 0x1B;
    }
    return var_v0;
}

/* func_00177168 (from hand/text_00170000_h38.c). */
typedef struct Actor {
    u8 pad0[0x3c];
    f32 x3c;        /* 0x3C */
    u8 pad40[0x30];
    s32 x70;        /* 0x70: state */
    u8 pad74[0xd0 - 0x74];
    V4 xd0;         /* 0xD0 */
} Actor;
extern f32 D_003623F4;
#define D_00575894 ((Actor *) D_00575894)
s32 func_00177168(void) {
    switch (D_00575894->x70) {
    case 0: return D_003623F4 > 1.0f;
    case 8: return D_003623F4 > 7.0f;
    case 24: return D_003623F4 > 7.0f;
    default: return D_003623F4 > 0.1f;
    }
}
#undef D_00575894

/* func_00177218 (from hand/text_00170000_h11.c). */
typedef struct Actor_77218 {
    u8 pad0[0x3c];
    f32 x3c;    /* 0x3C */
    u8 pad40[0x30];
    s32 x70;    /* 0x70: state */
} Actor_77218;
s32 func_00177218(Actor_77218 *o) {
    if (((*(u32 *)&D_002C5960) >> 4) & 1) return 0;
    if (o->x70 < 11) { if (o->x70 >= 9) return 1; }
    return 0;
}

/* func_00177258 (from hand/text_00170000_h11.c). */
typedef struct Actor_77258 {
    u8 pad0[0x3c];
    f32 x3c;    /* 0x3C */
    u8 pad40[0x30];
    s32 x70;    /* 0x70: state */
} Actor_77258;
s32 func_00177258(Actor_77258 *o) {
    if (((*(u32 *)&D_002C5960) >> 4) & 1) return 0;
    return o->x70 == 15;
}

/* func_00177288 (from hand/text_00170000_h11.c). */
typedef struct Actor_77288 {
    u8 pad0[0x3c];
    f32 x3c;    /* 0x3C */
    u8 pad40[0x30];
    s32 x70;    /* 0x70: state */
} Actor_77288;
s32 func_00177288(Actor_77288 *o) {
    if (((*(u32 *)&D_002C5960) >> 4) & 1) return 0;
    if (o->x70 < 15) { if (o->x70 >= 13) return 1; }
    return 0;
}

/* func_001772c8 (from hand/text_00170000_h11.c). */
typedef struct Actor_772c8 {
    u8 pad0[0x3c];
    f32 x3c;    /* 0x3C */
    u8 pad40[0x30];
    s32 x70;    /* 0x70: state */
} Actor_772c8;
s32 func_001772c8(Actor_772c8 *o) {
    if (((*(u32 *)&D_002C5960) >> 4) & 1) return 0;
    return o->x70 == 18;
}

/* func_001772f8 (from hand/text_00170000_h11.c). */
typedef struct Actor_772f8 {
    u8 pad0[0x3c];
    f32 x3c;    /* 0x3C */
    u8 pad40[0x30];
    s32 x70;    /* 0x70: state */
} Actor_772f8;
s32 func_001772f8(Actor_772f8 *o) {
    if (((*(u32 *)&D_002C5960) >> 4) & 1) return 0;
    switch (o->x70) {
    case 4: case 5: case 8: case 21: case 24: case 26:
        return 1;
    }
    return 0;
}

/* func_00177358 (from hand/text_00170000_h61.c). */
typedef struct { s32 x0; u8 pad4[0x3c - 4]; f32 x3c; u8 pad40[0x64 - 0x40]; f32 x64; u8 pad68[0x70 - 0x68]; s32 x70; u8 pad74[0xd0 - 0x74]; V4 xd0; } ActB;
/* Camera-state functions that follow func_00176f08 / func_00177358 in the
 * original file (both must be defined above them). */
s32 func_00177358(ActB *o) {
    if (((*(u32 *)&D_002C5960) >> 4) & 1) return 0;
    switch (o->x70) {
    case 0: case 8: case 24: return 1;
    }
    return 0;
}

/* func_001773b0 (from hand/text_00170000_h11.c). */
typedef struct Actor_773b0 {
    u8 pad0[0x3c];
    f32 x3c;    /* 0x3C */
    u8 pad40[0x30];
    s32 x70;    /* 0x70: state */
} Actor_773b0;
#define D_00575894 (*(Actor_773b0 *(*)) &D_00575894)
s32 func_001773b0(void) {
    Actor_773b0 **p = &D_00575894;
    s32 k;
    if (func_00177218(*p)) { func_00176f08(4, 60.0f); return 0; }
    if (func_00177258(*p)) k = 5;
    else if (func_00177288(*p)) k = 6;
    else if (func_001772c8(*p)) k = 8;
    else goto ret1;
    func_00176f08(k, 60.0f);
    return 0;
ret1:
    return 1;
}
#undef D_00575894

/* func_00177440 (from hand/text_00170000_h11.c). */
void func_00267530(void *, void *, void *);
s32 func_00119688(void *);
s32 func_00177440(void *a, void *b) {
    f32 v[4];
    f32 m[12];
    func_00267530(m, b, a);
    func_002675a8(v, a);
    return func_00119688(v) != -1;
}

/* func_00177608 (from hand/text_00170000_h11.c). */
void func_00118d78(void *);
typedef struct { f32 a[4]; f32 b[4]; s16 c; u8 pad[14]; } M30;
s32 func_00177608(void *out, void *a, void *b) {
    f32 v[4];
    M30 m;
    func_00267530(&m, b, a);
    func_002675a8(v, a);
    func_00118d78(v);
    if (m.c != -1) {
        func_002675a8(out, m.b);
        return 1;
    }
    return 0;
}

/* func_00177680 (from hand/text_00170000_h61.c). */
f32 func_00120bf8(V4 *);
extern f32 D_003624B8;
/* callees that must be DEFINED above (real bodies: func_00176f08 in src/hand/text_00170000_h61.c, func_00177680 in src/hand/text_00170000_h38.c); stubs here for testing */
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

/* func_00177740 (from hand/text_00170000_h61.c). */
extern V4 D_00362670;
void func_002672f8(V4 *, void *, V4 *);
void func_00267518(V4 *, V4 *, V4 *);
void func_00267810(V4 *, void *, f32);
#define D_005758D0 (*(V4 (*)) &D_005758D0)
s32 func_00177740(V4 *a0) {
    V4 m[4];
    V4 c, l, r, u, d, dir;
    func_002675a8(&c, &D_00362670);
    c.x = c.z = 0.0f;
    func_002672f8(&c, &D_002E26A0[0]->xd0, &c);
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
#undef D_005758D0

/* func_00177900 (from auto/text_00170000_10.c). */
extern M2C_UNK D_00362660;
f32 func_00120c88(f32);
void func_0017f178();
void func_00267768(void *, M2C_UNK *, f32);
#define D_00362670 (*(M2C_UNK (*)) &D_00362670)
void func_00177900(s32 arg0, M2C_UNK *arg1, f32 fparg0) {
    s32 sp[20];    f32 temp_f20;

    func_0017f178();
    func_002672f8(arg1, (*(s32 *)&D_002E26A0) + 0xD0, &D_00362670);
    temp_f20 = func_00120c88(fparg0);
    func_00267768(sp, ((M2C_UNK *)&D_002C58D0), func_00120c88(M2C_FIELD(&D_00362660, f32 *, 0)));
    func_00267810(sp, sp, temp_f20);
    func_002675a8(&M2C_FIELD(sp, M2C_UNK *, 0x40), ((M2C_UNK *)&D_002C58A0));
    M2C_FIELD(sp, f32 *, 0x48) = M2C_FIELD(&D_00362660, f32 *, 0xC);
    func_002672f8(&M2C_FIELD(sp, M2C_UNK *, 0x40), sp, &M2C_FIELD(sp, M2C_UNK *, 0x40));
    func_00267518(arg0, arg1, &M2C_FIELD(sp, M2C_UNK *, 0x40));
}
#undef D_00362670

/* func_001779e8 (from auto/text_00170000_12.c). */
s32 func_00177488(M2C_UNK *, void *, void *);
#define func_00120bf8 ((M2C_UNK (*)(M2C_UNK *)) func_00120bf8)
#define func_00177900 ((M2C_UNK (*)()) func_00177900)
#define D_00362670 (*(M2C_UNK (*)) &D_00362670)
void func_001779e8(void *arg0, s32 arg1) {
    s32 sp[8];
    func_00177900();
    func_002675a8(sp, &D_00362670);
    M2C_FIELD(sp, f32 *, 0x0) = M2C_FIELD(sp, f32 *, 0x8) = 0.0f;
    func_002672f8(sp, (*(s32 *)&D_002E26A0) + 0xD0, sp);
    if (func_00177488(&M2C_FIELD(sp, M2C_UNK *, 0x10), sp, arg0) != 0) {
        func_002675a8(arg0, &M2C_FIELD(sp, M2C_UNK *, 0x10));
    }
    func_00267530(&M2C_FIELD(sp, M2C_UNK *, 0x10), arg1, arg0);
    func_00120bf8(&M2C_FIELD(sp, M2C_UNK *, 0x10));
}
#undef func_00120bf8
#undef func_00177900
#undef D_00362670

/* func_00177a98 (from auto/text_00170000.c). */
M2C_UNK func_00250054(M2C_UNK *, M2C_UNK, M2C_UNK);
extern M2C_UNK D_005758F0;
void func_00177a98(void) {
    func_00250054(&D_005758F0, 0, 0x10);
}

/* func_00177ef8 (from hand/text_00160000_c04.c). */
typedef struct { V4 a; V4 b; V4 c; s16 h30; u8 pad32[0xE]; } RayC4;
typedef struct {
    u8 pad0[0x10]; V4 x10; u8 pad20[0x10]; V4 x30; u8 pad40[0x30]; s32 x70; u8 pad74[0x5C]; V4 xD0; u8 padE0[0x2E0]; V4 x3c0;
} CamC4;
V4 D_00575810 ALIGNED(16);
extern f32 D_002BBDFC;
extern f32 D_003624BC;
extern f32 D_003624C0;
extern f32 D_003624C4;
extern V4 D_00362680;
void func_00267560(V4 *, V4 *, f32);
void func_002673b8(V4 *, V4 *);
#define D_00575894 (*(CamC4 *(*)) &D_00575894)
#define D_005758D0 (*(V4 (*)) &D_005758D0)
#define D_005758E0 (*(V4 (*)) &D_005758E0)
#define D_00362660 (*(V4 (*)) &D_00362660)
s32 func_00177ef8(void) {
    RayC4 r;
    V4 t;
    s32 hit = 0;
    s32 busy;
    s32 n;
    f32 d;
    if (func_00177168()) {
        if (D_00575894->x70 == 2) {
            func_002675a8(&r.a, &D_005758E0);
            func_002675a8(&r.b, &D_002C58A0);
            r.b.y = 1000.0f;
            if (func_00119688(&r) == -1) hit = 1;
            else if (D_00575894->x3c0.y > 5.0f) {
                func_002673b8(&t, &D_00575894->x3c0);
                func_00267560(&t, &t, 250.0f);
                func_002675a8(&r.b, &t);
                func_002675a8(&r.a, &D_00575894->x10);
                hit = func_00119688(&r) == -1;
            }
        }
        D_003624C4 = 0.0f;
    } else if (func_00177070()) {
        if (D_003624C4 > 60.0f) {
            func_002675a8(&r.a, &D_00575894->x10);
            func_00267560(&r.b, &D_00575894->x30, 100.0f);
            n = func_00119688(&r);
            if (n == -1) {
                func_002675a8(&r.a, &D_00575894->x30);
                func_00267560(&r.a, &r.a, 30.0f);
                func_00267518(&r.a, &r.a, &D_00575894->x10);
                r.a.y -= 100.0f;
                func_002675a8(&r.b, &D_002C58A0);
                r.b.y = 500.0f;
                if (func_00119688(&r) == n) hit = 1;
            }
        } else {
            D_003624C4 += D_002BBDFC;
        }
    }
    func_002675a8(&D_00575810, &D_00575894->x10);
    busy = func_001772f8(D_00575894) != 0;
    if (hit && !busy) {
        D_00362680.x += D_003624BC / 30.0f * 0.0523598725f;
        D_00362680.x = func_00120c88(D_00362680.x);
        if (D_00362680.x > 1.483529598f) D_00362680.x = 1.483529598f;
        D_003624BC += D_002BBDFC;
        if (D_003624BC > 30.0f) D_003624BC = 30.0f;
    } else {
        D_003624BC = 0.0f;
    }
    func_002675a8(&r.a, &D_005758D0);
    func_002675a8(&r.b, &D_002C58A0);
    r.b.y = 55.0f;
    func_00118d78(&r);
    if (r.h30 != -1 && !busy) {
        func_00267530(&t, &r.c, &D_005758D0);
        d = func_00120bf8(&t);
        if (d < 49.49999714f) {
            d = d / 55.0f;
            D_00362680.x += (1.0f - d) * (D_003624C0 / 30.0f) * 0.0523598725f;
            D_00362680.x = func_00120c88(D_00362680.x);
            if (D_00362680.x > 1.483529598f) D_00362680.x = 1.483529598f;
            D_003624C0 += D_002BBDFC;
            if (D_003624C0 > 30.0f) D_003624C0 = 30.0f;
        }
    } else {
        if (func_00177168()) D_003624C0 -= D_002BBDFC * 0.2999999896f;
        if (D_003624C0 < 0.0f) D_003624C0 = 0.0f;
        if (D_003624C0 <= 0.0f) D_00362680.x += func_00120c88(D_00362660.x - D_00362680.x) * 0.0299999998f;
    }
    func_00267530(&r.b, &D_005758E0, &D_005758D0);
    r.b.y -= 100.0f;
    func_002675a8(&r.a, &D_005758D0);
    return func_00119688(&r) == -1;
}
#undef D_00575894
#undef D_005758D0
#undef D_005758E0
#undef D_00362660

/* func_00178468 (from hand/text_00170000_h11.c). */
s32 func_00177ac0(void);
s32 func_00178468(void) {
    s32 a = func_00177ac0();
    s32 b = func_00177ef8();
    return b || a;
}

/* func_001784b0 (from auto/text_00170000_11.c). */
extern f32 D_00575900[];
void func_001784b0(void) {
  float new_var;
  new_var = 0.0f;
  D_00575900[3] = new_var;
 do { } while (0);
  D_00575900[4] = new_var;
}

/* func_00178890 (from hand/text_00170000_h61.c). */
typedef struct { f32 x0, x4, x8, xc, x10; s32 x14; } Shk;
extern f32 D_00362684;
extern f32 D_0036266C;
extern f32 D_0036268C;
f32 sinf(f32);
f32 cosf(f32);
f32 fabsf(f32);
#define D_00575900 (*(Shk (*)) &D_00575900)
#define D_00362660 (*(V4 (*)) &D_00362660)
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
#undef D_00575900
#undef D_00362660

/* func_00178a98 (from hand/text_00170000_b06.c). */
typedef struct { V4 a; V4 b; V4 c; V4 d; } Ray;
typedef struct {
    s32 x0; u8 pad4[0x10 - 4]; V4 x10; u8 pad20[0x10]; f32 x30[3]; f32 x3c; u8 pad40[0x64 - 0x40]; f32 x64;
    u8 pad68[0x70 - 0x68]; s32 x70; u8 pad74[0xd0 - 0x74]; f32 xd0[4][4];
} ActB_78a98;
s32 func_00118b58(void *);
f32 D_005758F8 ALIGNED(8);
extern f32 D_003624C8;
extern f32 D_003624CC;
extern f32 D_003624D0;
extern f32 D_003624D4;
s32 func_001770b8(void);
#define D_00575894 ((ActB_78a98 *) D_00575894)
#define D_005758D0 (*(V4 (*)) &D_005758D0)
#define D_005758E0 (*(V4 (*)) &D_005758E0)
/* ---- func_00178a98 ---- */
void func_00178a98(void) {
    Ray s;
    f32 d, t, ad;

    if (fabsf(D_003624C8 - D_00575894->x3c) < 0.52359875f && func_001770b8()) {
        D_003624D4 += D_002BBDFC;
        if (D_003624D4 > 60.0f) {
            D_003624D4 = 60.0f;
            D_003624D0 += D_002BBDFC;
            if (D_003624D0 > 90.0f) D_003624D0 = 90.0f;
        }
    } else {
        D_003624D4 = 0.0f;
        D_003624D0 = 0.0f;
    }
    if (D_005758F8 <= 0.0f && D_003624D4 > 0.0f) {
        func_002675a8(&s.b, &D_002C58A0);
        func_002675a8(&s.a, &D_005758E0);
        s.c.y = 0.0f;
        s.c.x = 250.0f;
        if (func_00118b58(&s) || (func_002675a8(&s.a, &D_005758D0), func_00118b58(&s))) {
            D_003624CC += D_002BBDFC;
            if (D_003624CC > 60.0f) D_003624CC = 60.0f;
            if (D_003624D0 != 0.0f) D_003624D0 = 90.0f;
        } else {
            D_003624CC -= D_002BBDFC * 0.2999999896f;
            if (D_003624CC < 0.0f) D_003624CC = 0.0f;
        }
        d = func_00120c88(D_00575894->x3c + 3.1415928f - D_00362680.y);
        t = D_003624CC / 60.0f * 0.02000000002f + D_003624D0 / 90.0f * 0.02000000002f;
        ad = fabsf(d);
        if (ad < 2.094394982f) D_00362680.y += d * t;
        else D_00362680.y += d * t * (1.0f - (ad - 2.094394982f) / 1.047197491f);
    }
    D_003624C8 = D_00575894->x3c;
}
#undef D_00575894
#undef D_005758D0
#undef D_005758E0

/* func_00178d90 (from auto/text_00170000_8.c). */
M2C_UNK func_001784c8();
f32 func_00120c18(void *);
#define D_005758D0 (*(M2C_UNK (*)) &D_005758D0)
#define D_005758E0 (*(M2C_UNK (*)) &D_005758E0)
#define D_00362680 (*(f32 (*)) &D_00362680)
void func_00178d90(void) {
    s32 sp[4];
    func_00267530(sp, &D_005758D0, &D_005758E0);
    if ((func_00120c18(sp) < 40.0f) && (D_00362680 < 1.0471975f) && (func_001770b8() != 0)) {
        func_001784c8();
    }
}
#undef D_005758D0
#undef D_005758E0
#undef D_00362680

/* func_00178e10 (from hand/text_00170000_h38.c). */
typedef struct { u32 x0; u32 x4; } Pad;
f32 D_0057590C ALIGNED(4);
extern Pad D_002C5BB0;
s32 func_001375d8(Actor *);
#define D_00575894 ((Actor *) D_00575894)
void func_00178e10(void) {
    if (func_001375d8(D_00575894)) return;
    if (0.0f < D_005758C4) return;
    if (0.0f < D_0057590C) return;
    if (D_002C5BB0.x4 & 0x1000)
        D_00362680.y = func_00120c88(D_00362680.y + D_002BBDFC * 0.034906583f);
    if (D_002C5BB0.x4 & 0x2000)
        D_00362680.y = func_00120c88(D_00362680.y - D_002BBDFC * 0.034906583f);
}
#undef D_00575894

/* func_00178ef8 (from hand/text_00160000_c04.c). */
typedef struct { V4 a; V4 b; f32 r; u8 pad24[0xC]; V4 out; } SweepC4;
typedef FMtx4 M4;
typedef struct { u8 pad[8]; s32 w8; } PadC4;
extern u32 D_002C5958;
f32 func_00124d28(V4 *, V4 *);
void func_00124c68(f32);
void func_00121fc4(V4 *, V4 *);
void func_00267e90(V4 *, V4 *, f32);
s32 func_00118868(SweepC4 *);
void func_0011d768(s32);
#define D_00575894 (*(CamC4 *(*)) &D_00575894)
#define D_005758D0 (*(V4 (*)) &D_005758D0)
#define D_005758E0 (*(V4 (*)) &D_005758E0)
#define D_00362660 (*(V4 (*)) &D_00362660)
#define D_00575890 ((u32 ) D_00575890)
#define D_002C5BB0 (*(PadC4 (*)) &D_002C5BB0)
#define func_001779e8 ((void (*)(V4 *, V4 *, f32)) func_001779e8)
void func_00178ef8(void) {
    V4 p;
    V4 a;
    V4 b;
    M4 m;
    SweepC4 s;
    f32 t;
    f32 d;
    f32 e;
    s32 r;
    f32 lim;

    if (D_00575890 & 2) {
        D_00575890 &= ~2;
        D_00362680.x = D_00362660.x;
        D_00362680.y = func_00124d28(&D_002E2780, &D_002E2790);
        D_00362680.w = D_00362660.w;
        func_00124c68(53.0f);
        func_001779e8(&D_005758D0, &D_005758E0, D_00362680.y);
        D_00362434 = 0;
        D_00362438 = 0;
    }
    if (D_00575890 & 1) {
        D_00575890 &= ~1;
        func_001784b0();
        func_00177a98();
    }
    if (D_00575890 & 4) {
        D_00575890 &= ~4;
    }
    if (D_005758C4 > 0.0f) {
        func_002672f8(&D_005758E0, &D_00575894->xD0, &D_00362670);
    } else {
        func_002672f8(&a, &D_00575894->xD0, &D_00362670);
        func_002675a8(&b, &D_00362670);
        b.z = 0.0f;
        b.x = 0.0f;
        func_002672f8(&b, &D_00575894->xD0, &b);
        if (func_00177440(&b, &a)) func_002675a8(&a, &b);
        func_00267530(&a, &a, &D_005758E0);
        t = a.y;
        a.y = 0.0f;
        func_00121fc4(&a, &a);
        func_00267e90(&a, &a, a.w * 0.1999999918f);
        if (t > 0.0f) a.y = t * 0.5f;
        else a.y = t * 0.0999999959f;
        func_00267518(&D_005758E0, &D_005758E0, &a);
    }
    func_00178e10();
    func_00178890();
    if (func_00177070()) {
        func_00178a98();
        if (!(((*(u32 *)&D_002C5960) >> 4) & 1)) func_00178468();
        t = func_00120c88(D_00362680.y);
        func_00267768(&m, &D_002C58D0, func_00120c88(D_00362680.x));
        func_00267810(&m, &m, t);
        func_002675a8(&b, &D_002C58A0);
        b.z = D_00362680.w;
        func_002672f8(&b, &m, &b);
        func_00267518(&p, &D_005758E0, &b);
        func_00267530(&b, &p, &D_005758E0);
        if (D_00362660.w + 300.0f < func_00120bf8(&b)) func_001779e8(&p, &D_005758E0, D_00362680.y);
        if (((*(u32 *)&D_002C5960) >> 4) & 1) {
            func_002675a8(&D_005758D0, &p);
        } else {
            lim = 20.0f;
            do {
                func_002675a8(&s.a, &D_005758D0);
                func_00267530(&b, &p, &D_005758D0);
                d = func_00120bf8(&b);
                if (d >= 1000.0f) {
                    func_002675a8(&D_005758D0, &p);
                    break;
                }
                if (d >= lim) func_00267560(&b, &b, lim / d);
                func_002675a8(&s.b, &b);
                s.r = 40.0f;
                r = func_00118868(&s);
                func_002675a8(&D_005758D0, &s.out);
            } while (r == 0 && d >= lim);
        }
        if (!func_00177740(&D_005758D0)) func_001779e8(&D_005758D0, &D_005758E0, D_00362680.y);
    } else {
        if (!(((*(u32 *)&D_002C5960) >> 4) & 1)) func_00177ef8();
        t = func_00120c88(D_00362680.y);
        func_00267768(&m, &D_002C58D0, func_00120c88(D_00362680.x));
        func_00267810(&m, &m, t);
        func_002675a8(&b, &D_002C58A0);
        b.z = D_00362680.w;
        func_002672f8(&b, &m, &b);
        func_00267518(&p, &D_005758E0, &b);
        func_002675a8(&D_005758D0, &p);
        func_00267530(&b, &p, &D_005758E0);
        func_00121fc4(&b, &b);
        func_00267560(&b, &b, 60.0f);
        func_00267518(&p, &p, &b);
        if (func_00177608(&p, &D_005758E0, &p)) {
            func_00267530(&b, &D_005758E0, &p);
            func_00121fc4(&b, &b);
            if (b.w > 60.0f) {
                func_00267560(&b, &b, 60.0f);
                func_00267518(&D_005758D0, &p, &b);
            } else {
                func_002675a8(&D_005758D0, &p);
            }
        }
        func_00267530(&b, &D_005758E0, &D_005758D0);
        d = func_00120bf8(&b);
        if (d < 20.0f) {
            d = 20.0f - d;
            func_002673b8(&b, &b);
            func_00267560(&b, &b, d);
            func_00267518(&D_005758E0, &D_005758E0, &b);
        }
    }
    if (func_00177070()) func_00178d90();
    func_00267530(&b, &D_005758D0, &D_005758E0);
    if ((D_002C5BB0.w8 & 0x200) && !func_001375d8(D_00575894)) func_001784c8();
    if ((D_002C5BB0.w8 & 0x8000) && func_00177358(D_00575894) && !func_001375d8(D_00575894)) {
        if (!((D_002C5958 >> 13) & 1)) {
            func_00176f08(2, 30.0f);
            func_001784b0();
        } else {
            func_0011d768(4);
        }
    }
    if (func_00177070()) {
        func_00267530(&b, &D_005758D0, &D_005758E0);
        e = func_00120bf8(&b);
        D_00362680.w = e + (D_00362660.w - e) * 0.0999999959f;
    } else {
        D_00362680.w = D_00362660.w;
    }
    D_00362680.y = func_00124d28(&D_005758D0, &D_005758E0);
    func_001773b0();
}
#undef D_00575894
#undef D_005758D0
#undef D_005758E0
#undef D_00362660
#undef D_00575890
#undef D_002C5BB0
#undef func_001779e8

/* func_00179690 (from auto/text_00170000_10.c). */
void func_00179690(void) {
    M2C_FIELD(D_00575894, s32 *, 0) = (s32) (M2C_FIELD(D_00575894, s32 *, 0) | 1);
    if (D_005758C0 > 0.0f) {
        M2C_FIELD(D_00575894, f32 *, 0x64) = (f32) (1.0f / (D_005758C0 * 0.6f));
        return;
    }
    M2C_FIELD(D_00575894, f32 *, 0x64) = 1.0f;
}

/* func_00179700 (from hand/text_00170000_h61.c). */
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
typedef struct { u32 x0, x4; u64 x8; u8 pad10[0x44 - 0x10]; f32 x44; } PadB;
f32 D_00575820 ALIGNED(16);
f32 D_00575824 ALIGNED(4);
s32 D_00575828 ALIGNED(8);
extern V4 D_003624E0;
extern V4 D_003624F0;
extern f32 D_00362500;
void func_0012fc58(void);
#define D_00575894 (*(ActB **)&D_00575894)
#define D_005758D0 (*(V4 (*)) &D_005758D0)
#define D_005758E0 (*(V4 (*)) &D_005758E0)
#define D_00362660 (*(V4 (*)) &D_00362660)
#define D_002C5BB0 (*(PadB (*)) &D_002C5BB0)
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
#undef D_005758D0
#undef D_005758E0
#undef D_00362660
#undef D_002C5BB0
#undef D_00575894

/* func_00179a80 (from hand/text_00170000_b06.c). */
typedef struct {
    s32 x0; u8 pad4[0x10 - 4]; V4 x10; u8 pad20[0x10]; f32 x30[3]; f32 x3c; u8 pad40[0x64 - 0x40]; f32 x64;
    u8 pad68[0x70 - 0x68]; s32 x70; u8 pad74[0xd0 - 0x74]; f32 xd0[4][4];
} ActB_79a80;
f32 D_0057582C ALIGNED(4);
f32 D_00575830 ALIGNED(16);
extern V4 D_00362510;
void func_001315c0(void *, s32, void *, f32);
void sceVu0MulMatrix(void *, void *, void *);
#define D_00575894 ((ActB_79a80 *) D_00575894)
#define D_005758D0 (*(V4 (*)) &D_005758D0)
#define D_005758E0 (*(V4 (*)) &D_005758E0)
#define D_002C5BB0 (*(PadB (*)) &D_002C5BB0)
/* ---- func_00179a80 ---- */
void func_00179a80(void) {
    f32 m[4][4];
    u32 b;
    PadB *p;

    if (D_00575890 & 2) {
        D_00575890 &= ~2;
        D_0057582C = 0.0f;
        D_00575830 = D_005758C0;
    }
    if (D_00575830 > 0.0f) {
        D_00575830 -= D_002BBDFC;
        if (D_00575830 <= 0.0f) {
            D_00575894->x0 &= ~1;
            D_00575830 = 0.0f;
        }
    }
    func_001315c0(D_00575894, 0, &D_005758D0, 0.5f);
    func_00267768(m, D_002C58D0, D_0057582C);
    sceVu0MulMatrix(m, D_00575894->xd0, m);
    func_002675a8(m[3], &D_005758D0);
    m[3][3] = 1.0f;
    func_002672f8(&D_005758E0, m, &D_00362510);
    D_00362684 = func_00124d28(&D_005758D0, &D_005758E0);
    p = &D_002C5BB0;
    b = p->x4;
    if (b & 0x10) {
        D_0057582C -= D_002BBDFC * 0.01745329099f;
        if (D_0057582C < -1.396263272f) D_0057582C = -1.396263272f;
    } else if (b & 0x40) {
        D_0057582C += D_002BBDFC * 0.01745329099f;
        if (D_0057582C > 1.047197491f) D_0057582C = 1.047197491f;
    } else {
        if (D_0057582C > D_002BBDFC * 0.01745329099f) D_0057582C -= D_002BBDFC * 0.01745329099f;
        else if (D_0057582C < D_002BBDFC * -0.01745329099f) D_0057582C += D_002BBDFC * 0.01745329099f;
        else D_0057582C = 0.0f;
    }
    if ((u32)(&D_002C5BB0)->x8 & 0x200) {
        D_00575894->x0 |= 1;
        func_00176f08(1, 30.0f);
    }
}
#undef D_00575894
#undef D_005758D0
#undef D_005758E0
#undef D_002C5BB0

/* func_00179d08 (from auto/text_00170000.c). */
extern M2C_UNK D_00575920;
void func_00179d08(void) {
    func_00250054(&D_00575920, 0, 0x20);
}

/* func_00179ee8 (from hand/text_00170000_h61.c). */
typedef struct {
    u8 pad0[0x10]; V4 x10; u8 pad20[0x10]; V4 x30; u8 pad40[0x30]; s32 x70; u8 pad74[0x34C]; V4 x3c0;
} CamC4_79ee8;
typedef struct { s32 x0; f32 x4; u8 pad8[8]; V4 x10; } S5920;
#define D_00575894 (*(CamC4_79ee8 * *)&D_00575894)
#define D_00575890 (*(u32 *)&D_00575890)
extern V4 D_00362530;
extern V4 D_00362540;
extern f32 D_00362550;
#define D_00575920 (*(S5920 *)&D_00575920)
extern u32 D_002C5BB8;
#define D_002C5958 (*(u32 *)&D_002C5958)
f32 func_0012eca8(void *, V4 *);
void func_00179d30(void);
void func_002674f0(V4 *, V4 *, V4 *, f32);
#define D_005758D0 (*(V4 (*)) &D_005758D0)
#define D_005758E0 (*(V4 (*)) &D_005758E0)
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
    func_00267810(m, D_002C58D0, D_00362680.y);
    func_002675a8(&m[3], &D_00575894->x10);
    func_002675a8(&e, &D_00362530);
    A = e.y + D_00362550;
    e.y = A;
    func_002672f8(&a, m, &e);
    A = func_0012eca8((*(u8 (*)[0x8])&D_002E31B0), &c);
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
    func_00267810(m, D_002C58D0, D_00362680.y);
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
#undef D_005758D0
#undef D_005758E0
#undef D_00575894
#undef D_00575890
#undef D_00575920

/* func_0017a510 (from hand/text_00170000_h61.c). */
extern V4 D_00362570;
extern V4 D_00362560;
#define D_005758D0 (*(V4 (*)) &D_005758D0)
#define D_005758E0 (*(V4 (*)) &D_005758E0)
#define D_00575894 (*(Cam *(*)) &D_00575894)
#define func_00267e90 ((void (*)(f32, V4 *, V4 *)) func_00267e90)
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
#undef D_005758D0
#undef D_005758E0
#undef D_00575894
#undef func_00267e90

/* func_0017a6c0 (from hand/text_00170000_h38.c). */
extern V4 D_00362580;
extern V4 D_00362590;
#define D_00575894 (*(Actor *(*)) &D_00575894)
#define D_005758D0 (*(V4 (*)) &D_005758D0)
#define D_005758E0 (*(V4 (*)) &D_005758E0)
void func_0017a6c0(void) {
    V4 t;
    s32 *f = &D_00575890;
    Actor **pa;
    if (*f & 2) *f &= ~2;
    pa = &D_00575894;
    func_002672f8(&D_005758E0, &(*pa)->xd0, &D_00362590);
    func_002672f8(&D_005758D0, &(*pa)->xd0, &D_00362580);
    if (func_00177608(&t, &D_005758E0, &D_005758D0)) func_002675a8(&D_005758D0, &t);
    D_00362684 = func_00124d28(&D_005758D0, &D_005758E0);
    if (!func_00177258(*pa)) func_00176f08(1, 30.0f);
}
#undef D_00575894
#undef D_005758D0
#undef D_005758E0

/* func_0017a7b0 (from hand/text_00170000_h61.c). */
extern V4 D_003625B0;
extern V4 D_003625A0;
#define D_005758D0 (*(V4 (*)) &D_005758D0)
#define D_005758E0 (*(V4 (*)) &D_005758E0)
#define D_00575894 (*(Cam *(*)) &D_00575894)
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
#undef D_005758D0
#undef D_005758E0
#undef D_00575894

/* func_0017a958 (from hand/text_00170000_b06.c). */
typedef struct {
    s32 x0; u8 pad4[0x10 - 4]; V4 x10; u8 pad20[0x10]; f32 x30[3]; f32 x3c; u8 pad40[0x64 - 0x40]; f32 x64;
    u8 pad68[0x70 - 0x68]; s32 x70; u8 pad74[0xd0 - 0x74]; f32 xd0[4][4];
} ActB_7a958;
V4 D_00575840 ALIGNED(16);
f32 D_00575850 ALIGNED(16);
f32 D_00575854 ALIGNED(4);
f32 D_00575858 ALIGNED(8);
extern V4 D_003625C0;
extern V4 D_003625D0;
extern f32 D_003625E0;
#define D_00575894 ((ActB_7a958 *) D_00575894)
#define D_005758D0 (*(V4 (*)) &D_005758D0)
#define D_005758E0 (*(V4 (*)) &D_005758E0)
#define D_002C5BB0 (*(PadB (*)) &D_002C5BB0)
/* ---- func_0017a958 ---- */
void func_0017a958(void) {
    V4 a;
    V4 b;
    f32 m[4][4];
    Ray r;
    f32 s;
    f32 p;
    u32 k;

    if (D_00575890 & 2) {
        func_002675a8(&D_00575840, &D_003625C0);
        D_00575890 &= ~2;
    }
    if (D_005758C4 <= 0.0f) {
        k = D_002C5BB0.x4;
        s = 0.0f;
        if (k & 0x1000) s = 1.0f;
        if (k & 0x2000) s = -1.0f;
        if (s != 0.0f) {
            p = D_00575840.x + func_00120c88(s * 0.04363322724f * D_002BBDFC);
            func_00267768(m, D_002C58D0, func_00120c88(p));
            func_00267810(m, m, func_00120c88(D_00575850));
            func_002675a8(&b, &D_002C58A0);
            b.z = D_00575840.w;
            func_002672f8(&b, m, &b);
            func_002672f8(&D_005758E0, D_00575894->xd0, &D_003625D0);
            func_00267518(&a, &D_005758E0, &b);
            func_00267530(&r.b, &a, &D_005758E0);
            func_002675a8(&r.a, &D_005758E0);
            if (func_00119688(&r) == -1) {
                D_00575840.x = p;
                if (p > 0.8726645261f) D_00575840.x = 0.8726645261f;
                else if (p < -0.8726645261f) D_00575840.x = -0.8726645261f;
            }
        }
    } else {
        D_00575850 = D_00575894->x3c;
    }
    if ((u32)(&D_002C5BB0)->x8 & 0x200) {
        D_003625E0 = 15.0f;
        D_00575854 = D_00575840.x;
        D_00575858 = 0.3490658179f - D_00575840.x;
    }
    if (D_003625E0 > 0.0f) {
        D_003625E0 -= D_002BBDFC;
        if (D_003625E0 < 0.0f) D_003625E0 = 0.0f;
        s = sinf((1.0f - D_003625E0 / 15.0f) * 3.1415928f * 0.5f);
        D_00575840.x = D_00575854 + D_00575858 * s;
    }
    D_00575840.y = func_00120c88(D_00575850);
    func_00267768(m, D_002C58D0, func_00120c88(D_00575840.x));
    func_00267810(m, m, D_00575840.y);
    func_002675a8(&b, &D_002C58A0);
    b.z = D_00575840.w;
    func_002672f8(&b, m, &b);
    func_002672f8(&D_005758E0, D_00575894->xd0, &D_003625D0);
    func_00267518(&a, &D_005758E0, &b);
    func_00267530(&b, &a, &D_005758D0);
    func_00121fc4(&b, &b);
    b.w -= 100.0f;
    if (b.w > 0.0f) {
        func_00267e90(&b, &b, b.w);
        D_005758D0.x += b.x;
        D_005758D0.z += b.z;
    }
    D_005758D0.y = a.y;
    if (func_00177608(&b, &D_005758E0, &D_005758D0)) func_002675a8(&D_005758D0, &b);
    D_00362684 = func_00124d28(&D_005758D0, &D_005758E0);
    if (!func_001772c8(D_00575894)) func_00176f08(1, 30.0f);
}
#undef D_00575894
#undef D_005758D0
#undef D_005758E0
#undef D_002C5BB0

/* func_0017adf8 (from hand/text_00170000_h11.c). */
extern s32 D_00362444;
Rec *func_0017adf8(Rec *p, s32 n) {
    s32 i;
    for (i = 0; i < D_00362444 && i != n; i++) {
        p = (Rec *)((u8 *)p + p->n * 16 + 32);
    }
    return p;
}

/* func_0017ae48 (from hand/text_00170000_h61.c). */
extern s32 D_00362420;
#define D_00575894 (*(ActB **)&D_00575894)
#define D_005758D0 (*(V4 (*)) &D_005758D0)
#define D_005758E0 (*(V4 (*)) &D_005758E0)
#define D_002C5BB0 (*(PadB (*)) &D_002C5BB0)
#define D_00575920 ((s32 ) D_00575920)
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
#undef D_005758D0
#undef D_005758E0
#undef D_002C5BB0
#undef D_00575920
#undef D_00575894

/* func_0017b0e0 (from auto/text_00170000.c). */
extern M2C_UNK D_00575940;
void func_0017b0e0(void) {
    func_00250054(&D_00575940, 0, 0x70);
    M2C_FIELD(&D_00575940, f32 *, 0x50) = 1.0f;
}

/* func_0017b120 (from auto/text_00170000.c). */
extern M2C_UNK D_00362690;
void func_0017b120(void) {
    func_00250054(&D_00362690, 0, 0x30);
}

/* func_0017b148 (from auto/text_00170000.c). */
void func_0017b148(void) {
    func_00250054(((M2C_UNK *)&D_003626C0), 0, 0x30);
}

/* func_0017b170 (from hand/text_00170000_h11.c). */
typedef struct { u8 pad[0x28]; f32 x28; } S5970;
extern S5970 D_00575970;
s32 func_0017b170(void) {
    f32 v[4];
    Blk26C0 *s = &D_003626C0;
    f32 r;
    if (!s->flag) return 0;
    func_002675a8(D_005758D0, &s->a);
    func_002675a8(D_005758E0, &s->b);
    func_00267530(v, &D_00575970, D_005758D0);
    r = func_00120c18(v);
    s->flag = 0;
    D_00575970.x28 = r;
    return 1;
}

/* func_0017b200 (from hand/text_00170000_h61.c). */
#define D_005758D0 (*(V4 (*)) &D_005758D0)
#define D_005758E0 (*(V4 (*)) &D_005758E0)
void func_0017b200(void) {
    func_002675a8(&D_003626C0.a, &D_005758D0);
    func_002675a8(&D_003626C0.b, &D_005758E0);
    D_003626C0.flag = 1;
}
#undef D_005758D0
#undef D_005758E0


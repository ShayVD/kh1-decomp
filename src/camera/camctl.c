/* The field camera's control, default flags (docs/modules.md "Session 51"):
 * the camera data of a map (func_0017d9c8 relocates its zone boxes, paths
 * and point records into D_00362424 ...), modes 10 (func_0017dd00) and 7
 * (func_0017df08) with their helpers, the calls the game makes (func_0017e428
 * ... func_0017f110), the resets (func_0017eaa0, func_0017eb20), the start
 * (func_0017eb88) and the per-frame task func_0017ecf8 (runs the mode's frame
 * and blends the position D_002E2780 / target D_002E2790 from the previous
 * mode over D_005758C0 frames), the view angle (func_0017f150 / 0017f178:
 * D_00362660 to D_00362680), restoring a saved camera (func_0017f290), a
 * distance fade (func_0017f440), stopping the screen shake (func_0017f678) and
 * the shake's step (func_0017f688: sine offsets of the screen position).
 * camctl.nostrict.c has the rest.  Each section names the file its code came
 * from.  Read from the code, not proved by a boot. */
#include "common.h"
#include "platform/vu.h"
#include "data/types/text_00170000_h11_p4.h"
#include "data/types/text_00170000_h11.h"
#include "data/pieces/D_002E26A0.h"
#include "data/pieces/D_002C5960.h"
#include "data/types/text_00170000_h11_p3.h"
#include "data/pieces/D_003626C0.h"
#include "data/pieces/D_00362438.h"
#include "data/pieces/D_00362434.h"
#include "data/pieces/D_003626F0.h"
#include "data/pieces/D_003626F8.h"
#include "data/types/text_00170000_h11_p2.h"
#include "data/pieces/D_00362430.h"
#include "data/types/text_00170000_h11_p.h"
#include "data/pieces/D_00362424.h"
#include "data/pieces/D_00362428.h"
#include "data/pieces/D_0036242C.h"
#include "m2c.h"
#include "data/pieces/D_0036243C.h"
#include "data/pieces/D_00362710.h"
#include "data/pieces/D_0036244C.h"
#include "data/pieces/D_00362450.h"
#include "data/pieces/D_00362454.h"
#include "data/types/text_00170000_h38.h"
#include "data/types/text_00170000_h38_p.h"
#include "data/pieces/D_002C58D0.h"
#include "data/pieces/D_002E2780.h"
#include "data/pieces/D_002E2790.h"
#include "data/bss_0057.h"
#include "data/types/text_00170000_h61.h"
#include "data/pieces/D_002C58A0.h"
#include "data/types/text_00170000_b06.h"

/* func_0017d9c8 (from hand/text_00170000_h11.c). */
extern s32 D_00362444;
extern f32 D_00362660[4];
void func_0017f178(void);
typedef E30_362430 E30;
extern s32 D_00362440;
extern s32 D_00362448;
extern f32 D_00362674;
/* defined above it in its old file (h11): without it one word differs */
CONTEXT_ONLY Rec *func_0017adf8(Rec *p, s32 n) { return p; }
void func_0017d9c8(Hdr *h) {
    s32 i;
    if (((*(u32 *)&D_002C5960) >> 4) & 1) return;
    D_00362434 = 0;
    D_00362438 = 0;
    D_00362424 = h;
    D_00362440 = h->x1;
    D_00362444 = h->x2;
    D_00362448 = h->x3;
    D_00362428 = (Rec32 *)(h->x4 + (s32)h);
    D_0036242C = (Rec *)(h->x8 + (s32)h);
    D_00362430 = (E30 *)(h->xc + (s32)h);
    for (i = 0; i < D_00362448; i++) {
        E30 *e = &D_00362430[i];
        if ((s32)e->x20 < 0) e->x20 = 0;
        else if (e->x24 & 2) e->x20 = func_0017adf8(D_0036242C, (s32)e->x20);
        else e->x20 = &D_00362428[(s32)e->x20];
    }
    D_00362660[0] = D_00362424->x10;
    D_00362660[3] = D_00362424->x14;
    D_00362674 = D_00362424->x18;
    func_0017f178();
}

/* func_0017db68 (from auto/text_00170000.c). */
void func_0017db68(void) {
    D_00362424 = 0;
    D_00362428 = 0;
    D_0036242C = 0;
    D_00362430 = 0;
    D_00362434 = 0;
    D_00362438 = 0;
    D_0036243C = 0;
    D_00362440 = 0;
    D_00362448 = 0;
}

/* func_0017dbb8 (from auto/text_00170000_4.c). */
extern s32 D_002E27A8;
void func_00176f08(s32, f32);
s32 func_0017dbb8(void) {
    if (D_002E27A8 == 9) {
        (*(s32 *)&D_0036244C) = ((s32)D_00362434);
        (*(s32 *)&D_00362450) = ((s32)D_00362438);
        (*(s32 *)&D_00362454) = ((s32)D_0036243C);
        func_00176f08(0, 0.0f);
        return 1;
    }
    D_0036244C = 0;
    D_00362450 = 0;
    D_00362454 = 0;
    return 0;
}

/* func_0017dc40 (from hand/text_00170000_h38.c). */
s32 func_0017dc40(void) {
    void **a = &D_0036244C;
    void *v = *a;
    if (v != 0 || D_00362450 != 0) {
        D_00362434 = v;
        D_00362438 = D_00362450;
        (*(void **)&D_0036243C) = D_00362454;
        func_00176f08(9, 0.0f);
        *a = 0;
        D_00362450 = 0;
        D_00362454 = 0;
        return 1;
    }
    *a = 0;
    D_00362450 = 0;
    D_00362454 = 0;
    return 0;
}

/* func_0017dd00 (from hand/text_00170000_h61.c). */
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
extern f32 D_005758E0[];
extern f32 D_005758D0[];
extern s32 D_00575890;
extern Cam *D_00575894;
extern V4 D_003625F0;
f32 func_00120bf8(V4 *);
f32 func_00177680(V4 *, V4 *);
#define D_005758E0 (*(V4 (*)) &D_005758E0)
#define D_005758D0 (*(V4 (*)) &D_005758D0)
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
    PlatVu0SubVector(&v, &v, &D_005758E0);
    if (func_00120bf8(&v) < 0.0f) l = 0.0f;
    else if (200.0f < func_00120bf8(&v)) l = 200.0f;
    else l = func_00120bf8(&v);
    PlatVu0ScaleVector(&v, &v, l / 200.0f);
    PlatVu0AddVector(&D_005758E0, &D_005758E0, &v);
    PlatVu0AddVector(&D_005758D0, &D_005758E0, &D_003625F0);
}
#undef D_005758E0
#undef D_005758D0

/* func_0017de80 (from auto/text_00170000_4.c). */
extern s32 D_002BC128;
extern s32 D_002BC130;
void func_0017de80(void) {
    if (D_002E27A8 != 0xA) {
        if ((D_002BC128 == 6) && (D_002BC130 == 0xA)) {
            func_00176f08(0xA, 0.0f);
        }
    }
}

/* func_0017dee0 (from auto/text_00170000_8.c). */
M2C_UNK memset(M2C_UNK *, M2C_UNK, M2C_UNK);
extern M2C_UNK D_005759B0;
void func_0017dee0(void) {
    memset(&D_005759B0, 0, 0x50);
}

/* func_0017df08 (from hand/text_00170000_h61.c). */
typedef struct Z {
    V4 x0;
    s32 x10;
    u8 pad14[0x10];
    f32 x24[4];
    f32 x34, x38, x3c, x40;
} Z;
extern f32 D_002BBDFC;
extern V4 D_00362680;
f32 sinf(f32);
f32 func_00120c88(f32);
void func_00121fc4(V4 *, V4 *);
f32 func_00124d28(V4 *, V4 *);
#define D_005758E0 (*(V4 (*)) &D_005758E0)
#define D_005758D0 (*(V4 (*)) &D_005758D0)
#define D_005759B0 (*(Z (*)) &D_005759B0)
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
    PlatVu0SubVector(&v, &z->x0, &D_005758E0);
    func_00121fc4(&v, &v);
    PlatVu0ScaleVector(&v, &v, v.w * 0.3f);
    PlatVu0AddVector(&D_005758E0, &D_005758E0, &v);
    if (0.0f < z->x34) {
        z->x34 -= D_002BBDFC;
        a = z->x3c + sinf((f32)(1.0 - z->x34 / z->x38) * 3.1415928f * 0.5f) * z->x40;
    } else {
        a = z->x3c + z->x40;
    }
    PlatVu0RotMatrixX(m, D_002C58D0, func_00120c88(D_00362680.x));
    PlatVu0RotMatrixY(m, m, func_00120c88(a));
    PlatVu0CopyVector(&v, &D_002C58A0);
    v.z = D_00362680.w;
    PlatVu0ApplyMatrix(&v, m, &v);
    PlatVu0AddVector(&D_005758D0, &D_005758E0, &v);
    D_00362680.y = func_00124d28(&D_005758D0, &D_005758E0);
}
#undef D_005758E0
#undef D_005758D0
#undef D_005759B0

/* func_0017e170 (from hand/text_00170000_b06.c). */
typedef struct { V4 a; V4 b; V4 c; V4 d; } Ray;
s32 func_00119688(void *);
typedef struct { V4 x0; s32 x10; f32 x14[4]; f32 x24[4]; u8 pad34[0x44 - 0x34]; s32 x44; } CamB;
#define D_005759B0 (*(CamB (*)) &D_005759B0)
/* ---- func_0017e170 ---- */
s32 func_0017e170(s32 a0)
{
    Ray ray;
    V4 v40;
    V4 v50;
    V4 v60;
    f32 m[4][4];
    f32 y;
    f32 d;
    f32 a;
    s32 i;
    s32 first;
    s32 n;

    first = 1;
    n = 4;
    d = D_005759B0.x24[a0];
    y = D_00362680.y;
    if (D_005759B0.x44 == 0) {
        for (i = 0; i < 5; i++) {
            a = y + d * ((f32)i / (f32)n);
            PlatVu0CopyVector(&v40, &v50);
            PlatVu0RotMatrixX(m, D_002C58D0, func_00120c88(D_00362680.x));
            PlatVu0RotMatrixY(m, m, func_00120c88(a));
            PlatVu0CopyVector(&v60, &D_002C58A0);
            v60.z = D_00362680.w;
            PlatVu0ApplyMatrix(&v60, m, &v60);
            PlatVu0AddVector(&v50, &D_005759B0, &v60);
            v50.w = 1.0f;
            if (first) {
                PlatVu0CopyVector(&v40, &v50);
                first = 0;
            } else {
                PlatVu0CopyVector(&ray.a, &v40);
                PlatVu0SubVector(&ray.b, &v50, &v40);
                if (func_00119688(&ray) != -1) {
                    return 1;
                }
            }
        }
    } else {
        a = y + d;
        PlatVu0RotMatrixX(m, D_002C58D0, func_00120c88(D_00362680.x));
        PlatVu0RotMatrixY(m, m, func_00120c88(a));
        PlatVu0CopyVector(&v60, &D_002C58A0);
        v60.z = D_00362680.w;
        PlatVu0ApplyMatrix(&v60, m, &v60);
        PlatVu0AddVector(&v50, &D_005759B0, &v60);
        v50.w = 1.0f;
    }
    PlatVu0CopyVector(&ray.a, &D_005759B0);
    PlatVu0SubVector(&ray.b, &v50, &D_005759B0);
    return func_00119688(&ray) != -1;
}
#undef D_005759B0

/* func_0017e428 (from hand/text_00170000_b06.c). */
extern f32 D_005758C4;
f32 fabsf(f32);
extern s32 D_00362420;
extern V4 D_00362600;
extern f32 D_00362610[];
void func_0012fc58(void);
void func_00177900(void *, void *, f32);
#define D_005759B0 (*(CamB (*)) &D_005759B0)
/* ---- func_0017e428 ---- */
s32 func_0017e428(V4 *a, V4 *b)
{
    s32 tab[2];
    f32 cur;
    f32 ang;
    f32 t;
    f32 d;
    f32 spd;
    s32 i;
    s32 best;
    s32 prev;
    s32 next;
    s32 n;

    func_0012fc58();
    D_00362420 = 1;
    D_005759B0.x10 = 4;
    PlatVu0AddVector(&D_005759B0, a, b);
    PlatVu0ScaleVector(&D_005759B0, &D_005759B0, 0.5f);
    PlatVu0AddVector(&D_005759B0, &D_005759B0, &D_00362600);
    D_00362680.y = func_00124d28(&D_002E2780, &D_002E2790);
    cur = D_00362680.y;
    ang = func_00124d28(a, b);
    D_005759B0.x44 = func_0017dbb8();
    if (D_005759B0.x44 != 0) {
        D_00362680.y = ang;
        cur = D_00362680.y;
        func_00177900(&D_002E2780, &D_002E2790, cur);
        PlatVu0CopyVector(&D_002E2790, &D_005759B0);
        spd = 0.0f;
    } else {
        spd = 16.0f;
    }
    for (i = 0; i < 4; i++) {
        t = func_00120c88(D_00362610[i] + ang);
        D_005759B0.x14[i] = t;
        d = t - cur;
        D_005759B0.x24[i] = d;
        if (3.141592801f < fabsf(d)) {
            if (d < 0.0f) {
                D_005759B0.x24[i] = d + 6.2831855f;
            } else {
                D_005759B0.x24[i] = d - 6.2831855f;
            }
        }
    }
    best = 0;
    for (i = 1; i < 4; i++) {
        if (fabsf(D_005759B0.x24[i]) < fabsf(D_005759B0.x24[best])) {
            best = i;
        }
    }
    if (func_0017e170(best) == 0) {
        D_005759B0.x10 = best;
    } else {
        prev = best - 1;
        next = best + 1;
        if (prev < 0) {
            prev = 3;
        }
        n = 0;
        if (next < 4) {
            n = next;
        }
        if (fabsf(D_005759B0.x24[prev]) < fabsf(D_005759B0.x24[n])) {
            tab[0] = prev;
            tab[1] = n;
        } else {
            tab[0] = n;
            tab[1] = prev;
        }
        for (i = 0; i < 2; i++) {
            if (func_0017e170(tab[i]) == 0) {
                D_005759B0.x10 = tab[i];
                break;
            }
        }
        if (D_005759B0.x10 == 4) {
            n = (n + 1 < 4) ? n + 1 : 0;
            if (func_0017e170(n) == 0) {
                D_005759B0.x10 = n;
            }
        }
    }
    func_00176f08(7, spd);
    D_005758C4 = 0;
    return D_005759B0.x10;
}
#undef D_005759B0

/* func_0017e7d8 (from auto/text_00170000_5.c). */
extern s32 D_003623F0;
#define D_00575894 ((void *) D_00575894)
void func_0017e7d8(void) {
    if (D_00575894 != NULL) {
        M2C_FIELD(D_00575894, s32 *, 0) = (s32) (M2C_FIELD(D_00575894, s32 *, 0) | 1);
        M2C_FIELD(D_00575894, f32 *, 0x64) = 1.0f;
        func_0017dbb8();
    }
    D_00575894 = NULL;
    D_002E27A8 = 0;
    D_003623F0 = 1;
}
#undef D_00575894

/* func_0017e840 (from hand/text_00170000_h11.c). */
typedef struct Actor {
    u8 pad0[0x3c];
    f32 x3c;    /* 0x3C */
    u8 pad40[0x30];
    s32 x70;    /* 0x70: state */
} Actor;
#define D_00575894 (*(Actor **)&D_00575894)
void func_0017e840(void) {
    if (D_003623F0) {
        if ((D_00575894 = D_002E26A0[0]) != 0) {
            if (!func_0017dc40()) func_00176f08(1, 30.0f);
        }
        D_003623F0 = 0;
    }
}
#undef D_00575894

/* func_0017e8a0 (from auto/text_00170000.c). */
M2C_UNK func_00250054(M2C_UNK *, M2C_UNK, M2C_UNK);
void func_0017e8a0(void) {
    func_00250054(((M2C_UNK *)&D_003626F0), 0, 8);
}

/* func_0017e8c8 (from hand/text_00170000_h11.c). */
extern f32 D_00362684;
#define D_00575894 (*(Actor **)&D_00575894)
void func_0017e8c8(void) {
    Arg *p = ((Arg *)&D_003626F0);
    p[0].i = 1;
    p[1].f = D_00362684 - D_00575894->x3c;
    func_00176f08(0, 0.0f);
}
#undef D_00575894

/* func_0017e910 (from hand/text_00170000_h61.c). */
f32 func_001779e8(V4 *, V4 *, f32);
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

/* func_0017eaa0 (from auto/text_00170000_4.c). */
f32 func_0017b0e0(void);
void func_00177a98(void);
void func_001784b0(void);
void func_00179d08(void);
void func_0017b120(void);
void func_0017b148(void);
void func_0017eaa0(void) {
    D_002E27A8 = 0;
    D_00575890 = 0;
    D_003623F0 = 0;
    func_00177a98();
    func_001784b0();
    func_0017b0e0();
    func_0017b120();
    func_0017b148();
    func_00179d08();
    func_0017dee0();
    D_00362420 = 0;
    D_0036244C = 0;
    D_00362450 = 0;
    D_00362454 = 0;
}

/* func_0017eb20 (from auto/text_00170000_5.c). */
void func_0017eb20(void) {
    func_0017eaa0();
    D_00362428 = 0;
    D_0036242C = 0;
    D_00362430 = 0;
    D_00362434 = 0;
    D_00362438 = 0;
    D_0036243C = 0;
    D_00362440 = 0;
    D_00362444 = 0;
    D_00362448 = 0;
    func_0017e8a0();
}

/* func_0017eb88 (from auto/text_00170000_6.c). */
s32 func_0017d628(void);
s32 func_0017ecf8(void);
#define D_00575894 (*(s32 *)&D_00575894)
void func_0017eb88(void) {
    D_00575894 = (*(s32 *)&D_002E26A0);
    func_0017eaa0();
    if (func_0017d628() == 0) {
        func_00176f08(1, 0.0f);
    }
    func_0017ecf8();
}
#undef D_00575894

/* func_0017ebd0 (from auto/text_00170000_1.c). */
#define D_00575894 (*(s32 *)&D_00575894)
void func_0017ebd0(void) {
    D_00575894 = 0;
    D_002E27A8 = 0;
    D_0036244C = 0;
    D_00362450 = 0;
    D_00362454 = 0;
}
#undef D_00575894

/* func_0017ec00 (from hand/text_00170000_h38.c). */
typedef struct Actor_7ec00 {
    u8 pad0[0x3c];
    f32 x3c;        /* 0x3C */
    u8 pad40[0x30];
    s32 x70;        /* 0x70: state */
    u8 pad74[0xd0 - 0x74];
    V4 xd0;         /* 0xD0 */
} Actor_7ec00;
extern V4 D_00362620;
extern V4 D_00362630;
#define D_00575894 (*(Actor_7ec00 *(*)) &D_00575894)
#define D_005758D0 (*(V4 (*)) &D_005758D0)
#define D_005758E0 (*(V4 (*)) &D_005758E0)
void func_0017ec00(void) {
    V4 m[4];
    V4 v;
    Actor_7ec00 **pa = &D_00575894;
    if (!*pa) return;
    PlatVu0ApplyMatrix(&D_005758E0, &(*pa)->xd0, &D_00362630);
    D_00362684 = func_00120c88((*pa)->x3c + 3.1415928f);
    PlatVu0RotMatrixY(m, D_002C58D0, D_00362684);
    PlatVu0ApplyMatrix(&v, m, &D_00362620);
    PlatVu0AddVector(&D_005758D0, &D_005758E0, &v);
    PlatVu0CopyVector(&D_002E2780, &D_005758D0);
    PlatVu0CopyVector(&D_002E2790, &D_005758E0);
    func_00176f08(1, 30.0f);
    D_005758C4 = 0.0f;
}
#undef D_00575894
#undef D_005758D0
#undef D_005758E0

/* func_0017ecf8 (from hand/text_00170000_h61.c). */
typedef struct { u32 b0:1; u32 b1:1; u32 r:30; } BF;
extern V4 D_005758A0;
extern V4 D_005758B0;
extern Fn8 D_00362458[];
extern f32 D_003623F4;
extern f32 D_003623F8;
extern BF D_002C5958;
f32 cosf(f32);
#define D_005758E0 (*(V4 (*)) &D_005758E0)
#define D_005758D0 (*(V4 (*)) &D_005758D0)
s32 func_0017ecf8(void) {
    V4 v;
    f32 t, u;
    if (D_003623F0) { D_003623F0 = 2; return 0; }
    if (D_00575894) {
        PlatVu0SubVector(&v, &D_00575894->x10, &D_00575894->x490);
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
            PlatVu0InterVector(&D_002E2780, &D_005758A0, &D_005758D0, u);
            PlatVu0InterVector(&D_002E2790, &D_005758B0, &D_005758E0, u);
        } else {
            D_005758C4 = 0.0f;
            PlatVu0CopyVector(&D_002E2780, &D_005758D0);
            PlatVu0CopyVector(&D_002E2790, &D_005758E0);
        }
    } else {
        PlatVu0CopyVector(&D_002E2780, &D_005758D0);
        PlatVu0CopyVector(&D_002E2790, &D_005758E0);
    }
    }
    return 0;
}
#undef D_005758E0
#undef D_005758D0

/* func_0017ef40 (from hand/text_00170000_h38.c). */
typedef struct { s32 x0; f32 x4; u8 pad8[8]; V4 x10; } S920;
extern S920 D_00575920;
void func_0017d570(s32);
#define D_005758E0 (*(V4 (*)) &D_005758E0)
void func_0017ef40(s32 a) {
    S920 *s = &D_00575920;
    s32 m = D_002E27A8;
    s->x0 = a;
    if (m != 9) {
        if (m != 3) {
            PlatVu0CopyVector(&s->x10, &D_005758E0);
            func_00176f08(3, 60.0f);
            return;
        }
        PlatVu0CopyVector(&s->x10, &D_005758E0);
        s->x4 = 60.0f;
        return;
    }
    PlatVu0CopyVector(&s->x10, &D_005758E0);
    func_0017d570(a);
}
#undef D_005758E0

/* func_0017eff8 (from hand/text_00170000_h11.c). */
void func_0017d5a0(void);
/* defined above it in its old file (h11): without it one word differs */
CONTEXT_ONLY s32 func_001773b0(void) { return 1; }
#define D_00575894 (*(Actor **)&D_00575894)
#define D_00575920 (*(s32 (*)) &D_00575920)
void func_0017eff8(void) {
    D_00575920 = 0;
    if (D_002E27A8 != 9 && D_002E27A8 != 2) {
        if (D_00575894 && func_001773b0()) func_00176f08(1, 45.0f);
    } else {
        func_0017d5a0();
    }
}
#undef D_00575894
#undef D_00575920

/* func_0017f078 (from hand/text_00170000_h11.c). */
extern V3 D_00362640[];
extern f32 D_00362670[4];
void func_0017f078(s32 i) {
    if (i >= 2) return;
    if (i < 0) return;
    D_003626F8[0] = D_00362660[0];
    D_003626F8[1] = D_00362660[3];
    D_003626F8[2] = D_00362670[1];
    D_00362660[0] = D_00362640[i].x;
    D_00362660[3] = D_00362640[i].y;
    D_00362670[1] = D_00362640[i].z;
    func_0017f178();
}

/* func_0017f110 (from auto/text_00170000_7.c). */
#define D_00362660 (*(M2C_UNK (*)) &D_00362660)
void func_0017f110(void) {
    M2C_FIELD(&D_00362660, f32 *, 0) = (f32) M2C_FIELD((M2C_UNK *)&D_003626F8, f32 *, 0);
    M2C_FIELD(&D_00362660, f32 *, 0xC) = (f32) M2C_FIELD((M2C_UNK *)&D_003626F8, f32 *, 4);
    D_00362674 = M2C_FIELD((M2C_UNK *)&D_003626F8, f32 *, 8);
    func_0017f178();
}
#undef D_00362660

/* func_0017f150 (from auto/text_00170000.c). */
extern M2C_UNK D_00362410;
#define D_00362660 (*(M2C_UNK (*)) &D_00362660)
void func_0017f150(void) {
    PlatVu0CopyVector(&D_00362660, &D_00362410);
    func_0017f178();
}
#undef D_00362660

/* func_0017f178 (from auto/text_00170000_4.c). */
#define D_00362660 (*(M2C_UNK (*)) &D_00362660)
#define D_00362680 (*(M2C_UNK (*)) &D_00362680)
void func_0017f178(void) {
    M2C_FIELD(&D_00362680, f32 *, 0) = (f32) M2C_FIELD(&D_00362660, f32 *, 0);
    M2C_FIELD(&D_00362680, f32 *, 0xC) = (f32) M2C_FIELD(&D_00362660, f32 *, 0xC);
}
#undef D_00362660
#undef D_00362680

/* func_0017f1a0 (from auto/text_00170000.c). */
extern M2C_UNK D_00362400;
#define D_00362670 (*(M2C_UNK (*)) &D_00362670)
void func_0017f1a0(void) {
    PlatVu0CopyVector(&D_00362670, &D_00362400);
}
#undef D_00362670

/* func_0017f290 (from hand/text_00180000_h62.c). */
typedef struct {
    u8 pad[0x1C];
    s32 id; /* +0x1C */
} Rec20;
typedef struct {
    f32 a[3];   /* +0x0 */
    f32 b[3];   /* +0xC */
    f32 c;      /* +0x18 */
    u8 mode;    /* +0x1C */
    u8 id;      /* +0x1D */
    u8 kind;    /* +0x1E */
} CamArg;
extern f32 D_002E27A0;
#define func_0017adf8 ((Rec20 *(*)(s32, s32)) func_0017adf8)
void func_0017f290(CamArg *a) {
    s32 i, j;
    Rec20 *r;
    Rec20 *q;

    D_00575890 |= 4;
    for (j = 0; j < 3; j++) {
        ((f32 *)&D_002E2780)[j] = D_005758D0[j] = a->a[j];
        ((f32 *)&D_002E2790)[j] = D_005758E0[j] = a->b[j];
    }
    D_002E27A0 = a->c;
    func_00176f08(a->mode, 0.0f);
    if (a->mode == 9) {
    switch (a->kind) {
    case 0:
        for (i = 0; i < D_00362440; i++) {
            r = (Rec20 *) ((i * 32) + (s32) D_00362428);
            if (r->id == a->id) {
                (*(Rec20 **)&D_00362434) = r;
                D_00362438 = 0;
                break;
            }
        }
        break;
    case 1:
        i = 0;
    loop:
        if (i < D_00362444) {
            q = func_0017adf8(((s32)D_0036242C), i++);
            if (q->id != a->id)
                goto loop;
            D_00362438 = (Path_362438 *)((s32)q);
            D_00362434 = 0;
        }
        break;
    }
    }
}
#undef func_0017adf8

/* func_0017f440 (from auto/text_00170000_4.c). */
f32 func_00120c18(s32);
s32 func_001375d8();
#define D_002C5958 (*(s32 (*)) &D_002C5958)
f32 func_0017f440(s32 arg0) {
    f32 temp_f0;
    f32 var_f0;
    f32 var_f1;
    f32 var_f20;

    var_f20 = 1.0f;
    if ((arg0 == (*(s32 *)&D_002E26A0)) && (func_001375d8() == 0)) {
        var_f0 = 1.0f;
        if (!(D_002C5958 & 0x104000)) {
            temp_f0 = func_00120c18(arg0 + 0x110);
            var_f0 = 1.0f;
            if (temp_f0 < 150.0f) {
                var_f1 = temp_f0 - 100.0f;
                if (var_f1 < 0.0f) {
                    var_f1 = 0.0f;
                }
                var_f20 = var_f1 / 50.0f;
                if (var_f20 < 0.19999999f) {
                    var_f20 = 0.19999999f;
                }
                goto block_8;
            }
        }
    } else {
block_8:
        var_f0 = var_f20;
    }
    return var_f0;
}
#undef D_002C5958

/* func_0017f678 (from auto/text_00170000.c). */
void func_0017f678(void) {
    D_00362710 = 0;
}

/* func_0017f688 (from hand/text_00180000_h62.c). */
extern s32 D_00362704;
extern s32 D_00362708;
extern s32 D_0036270C;
extern f32 D_00362714;
extern f32 D_00362718;
extern f32 D_0036271C;
extern f32 D_00362720;
extern f32 D_00362724;
extern f32 D_00362728;
extern f32 D_0036272C;
void func_00110020(s32, s32);
f32 func_00176850(void);
void func_0017f688(void) {
    f32 x, y;

    if (D_00362710 < 0.0f) {
        D_00362704 = 0;
        func_00110020(D_00362708, D_0036270C);
        D_00362728 = func_00176850() * 3.1415928f;
        D_0036272C = func_00176850() * 3.1415928f;
    } else {
        D_00362710 -= D_002BBDFC;
        D_00362728 = D_00362728 + 6.2831854820251465 / D_00362714 * D_002BBDFC;
        D_00362728 = func_00120c88(D_00362728);
        D_0036272C = D_0036272C + 6.2831854820251465 / D_00362714 * D_002BBDFC;
        D_0036272C = func_00120c88(D_0036272C);
        x = D_00362718 * sinf(D_00362728);
        y = D_0036271C * sinf(D_0036272C);
        func_00110020(D_00362708 + (s32) x, D_0036270C + (s32) y);
        D_00362718 -= D_00362720;
        D_0036271C -= D_00362724;
        if (D_00362718 < 0.0f)
            D_00362718 = 0.0f;
        if (D_0036271C < 0.0f)
            D_0036271C = 0.0f;
    }
}


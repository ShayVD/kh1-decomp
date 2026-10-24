/* The field camera's path mode (mode 9), default flags (docs/modules.md
 * "Session 51"): a cubic Bezier at t (func_0017b250), the camera following
 * the path D_00362438 that the player's zone picked (D_00575940: position,
 * target, segment and t), stepping and blending along it, turns on pad input,
 * and the mode's frame func_0017d5d0.  campath.nostrict.c has the control
 * points of a segment (func_0017b308), the step along a segment
 * (func_0017b4f8) and the searches for the nearest point.  Each section names
 * the file its code came from.  Read from the code, not proved by a boot. */
#include "common.h"
#include "platform/vu.h"
#include "data/types/text_00170000_h38.h"
#include "data/types/text_00170000_h38_p.h"
#include "data/pieces/D_002C58D0.h"
#include "data/pieces/D_002E2780.h"
#include "data/pieces/D_002E2790.h"
#include "data/pieces/D_00362434.h"
#include "data/pieces/D_00362438.h"
#include "data/pieces/D_0036243C.h"
#include "data/pieces/D_0036244C.h"
#include "data/pieces/D_00362450.h"
#include "data/pieces/D_00362454.h"
#include "data/types/text_00170000_h11_p4.h"
#include "data/types/text_00170000_h11.h"
#include "data/pieces/D_002E26A0.h"
#include "data/pieces/D_002C5960.h"
#include "data/types/text_00170000_h11_p3.h"
#include "data/pieces/D_003626C0.h"
#include "m2c.h"
#include "data/bss_0057.h"
#include "data/types/text_00170000_h61.h"
#include "data/pieces/D_003626F0.h"
#include "data/pieces/D_002C58A0.h"

/* func_0017b250 (from hand/text_00170000_h38.c). */
void func_0017b250(f32 *out, f32 (*m)[4], f32 t) {
    f32 b[4];
    f32 s = 1.0f - t;
    s32 i;
    b[0] = s * s * s;
    b[1] = t * 3.0f * (s * s);
    b[2] = t * t * 3.0f * s;
    b[3] = t * t * t;
    for (i = 0; i < 3; i++) {
        out[i] = m[0][i] * b[0] + m[1][i] * b[1] + m[2][i] * b[2] + m[3][i] * b[3];
    }
    out[3] = 1.0f;
}

/* func_0017b668 (from hand/text_00170000_s8_w16.c). */
f32 func_0017b668(s32 start, s32 end, f32 t, f32 te) {
    Path *p = D_00362438;
    s32 n = p->n;
    s32 i = start;
    f32 sum = 0.0f;
    s32 k;
    for (k = 0; k <= n; k++) {
        if (i == end && t < te) {
            sum += (p->seg + end)->len * (te - t);
            break;
        }
        sum += (p->seg + i)->len * (1.0f - t);
        t = 0.0f;
        i++;
        if (i >= n) i = 0;
        if ((p->x18 & 1) && i == n - 1) break;
    }
    return sum;
}

/* func_0017b740 (from hand/text_00170000_h38.c). */
extern V4 D_00575970;
void func_00121fc4(V4 *, V4 *);
void func_0017b740(V4 *out, V4 *in) {
    V4 d;
    Path *p = D_00362438;
    PlatVu0SubVector(&d, &D_00575970, in);
    d.y = 0.0f;
    func_00121fc4(&d, &d);
    if (p->x8 < d.w) {
        PlatVu0ScaleVector(&d, &d, d.w - p->x8);
        PlatVu0AddVector(out, in, &d);
    } else {
        PlatVu0CopyVector(out, in);
    }
}

/* func_0017b7e8 (from hand/text_00170000_h11.c). */
extern s32 D_00575920;
extern u64 D_002C5BB0;
u8 D_005759A4 ALIGNED(4);
s32 func_001770b8(void);
s32 func_0017b7e8(void) {
    if (!(D_002C5BB0 & 0x300000000000ULL)) {
        if (D_00575920 && !(D_00362438->x18 & 0x10)) goto one;
        if (func_001770b8()) return 1;
        if (!D_005759A4) return 0;
    }
one:
    return 1;
}

/* func_0017bfe8 (from hand/text_00170000_h38.c). */
typedef struct Cam {
    V4 x0;          /* 0x00 */
    V4 x10;         /* 0x10 */
    V4 x20;
    V4 x30;         /* 0x30 */
    s32 x40;        /* 0x40 */
    s32 x44;
    f32 x48;        /* 0x48 */
    f32 x4c;
    f32 x50;        /* 0x50 */
    f32 x54;        /* 0x54 */
    u8 pad58[4];
    f32 x5c;        /* 0x5C */
    u8 pad60[4];
    u8 x64;         /* 0x64 */
    u8 x65;         /* 0x65 */
    u8 x66;         /* 0x66 (D_005759A6) */
} Cam;
extern Cam D_00575940;
extern f32 D_002BBDFC;
f32 func_00120bf8(V4 *);
void func_0017b4f8(s32 *, f32 *, f32);
void func_0017bfe8(void) {
    V4 t;
    Cam *c2;
    f32 dt = D_002BBDFC;
    Cam *c = &D_00575940;
    f32 max = D_00362438->x14 * dt;
    f32 s, d;
    f32 k = 100.0f;
    if (c->x64) {
        dt += dt;
        max += max;
    }
    c->x54 += dt;
    c->x54 = (c->x54 < 0.0f) ? 0.0f : ((max < c->x54) ? max : c->x54);
    s = D_00575940.x54;
    PlatVu0SubVector(&t, &D_00575940.x0, &D_00575940.x10);
    d = func_00120bf8(&t);
    if (d < 5.0f) d = 0.0f;
    d = (d < 0.0f) ? 0.0f : ((k < d) ? 100.0f : d);
    s *= d / k;
    if (!func_0017b7e8()) s = 0.0f;
    c2 = &D_00575940;
    func_0017b4f8(&c2->x40, &c2->x48, s * c2->x50);
}

/* func_0017c110 (from auto/text_00170000_9.c). */
M2C_UNK func_00120c18(M2C_UNK *);
M2C_UNK func_0017b308(void *, void *, s32, s32, s32);
#define D_00575970 (*(M2C_UNK (*)) &D_00575970)
void func_0017c110(s32 arg0, f32 fparg0) {
    s32 sp[20];
    func_0017b308(sp, ((void *)D_00362438) + 0x20, M2C_FIELD(D_00362438, s32 *, 0), arg0, M2C_FIELD(D_00362438, s32 *, 0x18) & 1);
    func_0017b250(&M2C_FIELD(sp, M2C_UNK *, 0x40), sp, fparg0);
    PlatVu0SubVector(&M2C_FIELD(sp, M2C_UNK *, 0x40), &D_00575970, &M2C_FIELD(sp, M2C_UNK *, 0x40));
    func_00120c18(&M2C_FIELD(sp, M2C_UNK *, 0x40));
}
#undef D_00575970

/* func_0017c4c8 (from hand/text_00170000_h11.c). */
extern s32 D_002C5BB8;
typedef struct { u8 pad[0x66]; u8 x66; } S5940;
void func_0017ba80(s32);
s32 func_0017c190(void);
#define D_00575940 (*(S5940 (*)) &D_00575940)
void func_0017c4c8(void) {
    if (D_002C5BB8 & 0x200) {
        if (D_00575940.x66 != 3) {
            D_00575940.x66 = 2;
            func_0017ba80(4);
        }
    }
    if ((u8)(D_00575940.x66 - 2) < 2) {
        if (!func_0017c190()) D_00575940.x66 = 0;
    }
}
#undef D_00575940

/* func_0017c7f0 (from hand/text_00170000_h38.c). */
typedef struct Actor {
    u8 pad0[0x3c];
    f32 x3c;        /* 0x3C */
    u8 pad40[0x30];
    s32 x70;        /* 0x70: state */
    u8 pad74[0xd0 - 0x74];
    V4 xd0;         /* 0xD0 */
} Actor;
typedef struct { s32 x0; f32 x4; u8 pad8[8]; V4 x10; } S920;
extern Actor *D_00575894;
u8 D_005759A6 ALIGNED(2);
void func_0011d768(s32);
s32 func_001375d8(Actor *);
void func_0017c550(void);
#define D_00575920 (*(S920 (*)) &D_00575920)
#define D_002C5BB8 (*(u64 (*)) &D_002C5BB8)
void func_0017c7f0(void) {
    Path *p = D_00362438;
    Cam *c;
    if (p->x18 & 4) {
        if (D_002C5BB8 & 0x3000) {
            D_005759A6 = 0;
            func_0011d768(4);
        }
        return;
    }
    c = &D_00575940;
    if (0.0f < c->x5c) {
        c->x5c -= D_002BBDFC;
        return;
    }
    if (func_001375d8(D_00575894)) return;
    if (c->x65) return;
    if (D_00575920.x0 && !(p->x18 & 0x10)) return;
    func_0017c4c8();
    func_0017c550();
}
#undef D_00575920
#undef D_002C5BB8

/* func_0017d1e0 (from auto/text_00170000_2.c). */
extern s32 D_003626B0;
void func_0017d1e0(void) {
    if (!(M2C_FIELD(D_00362438, s32 *, 0x18) & 0x10)) {
        D_003626B0 = 1;
    }
}

/* func_0017d208 (from auto/text_00170000_1.c). */
M2C_UNK func_0017b120(void *);
void func_0017d208(void) {
    if (!(M2C_FIELD(D_00362438, s32 *, 0x18) & 0x10)) {
        func_0017b120(D_00362438);
    }
}

/* func_0017d238 (from hand/text_00170000_h61.c). */
typedef struct { u32 b0:1; u32 b1:1; u32 r:30; } BF;
extern f32 D_005758D0[4];
extern s32 D_00575890;
extern V4 D_00362670;
extern BF D_002C5958;
/* defined above it in its old file (h61): without them five words differ */
CONTEXT_ONLY void func_00176f08(s32 st, f32 t) { }
CONTEXT_ONLY s32 func_00177358(void *o) { return 0; }
CONTEXT_ONLY void func_0017b200(void) { }
typedef struct { s32 x0; u8 pad4[0x3c - 4]; f32 x3c; u8 pad40[0x64 - 0x40]; f32 x64; u8 pad68[0x70 - 0x68]; s32 x70; u8 pad74[0xd0 - 0x74]; V4 xd0; } ActB;
typedef struct { u32 x0, x4; u64 x8; u8 pad10[0x44 - 0x10]; f32 x44; } PadB;
extern s32 D_00362420;
typedef struct Cam940 {
    V4 x0; V4 x10; V4 x20; V4 x30;
    s32 x40; s32 x44; f32 x48; f32 x4c; f32 x50; f32 x54; f32 x58; f32 x5c; f32 x60;
    u8 x64; u8 x65; u8 x66;
} Cam940;
void func_0017b170(void);
void func_0017c8e8(void);
void func_0017c9a8(void);
void func_0017cf08(void);
#define D_00575894 (*(ActB **)&D_00575894)
#define D_002C5958 (*(u32 *)&D_002C5958)
#define D_005758D0 (*(V4 (*)) &D_005758D0)
#define D_002C5BB0 (*(PadB (*)) &D_002C5BB0)
#define D_00575940 (*(Cam940 (*)) &D_00575940)
#define func_00120c18 ((f32 (*)(V4 *)) func_00120c18)
void func_0017d238(void) {
    V4 v;
    f32 m[4][4];
    Path *path = D_00362438;
    f32 step, len;

    PlatVu0ApplyMatrix(&D_00575940.x30, &D_00575894->xd0, &D_00362670);
    PlatVu0SubVector(&v, &D_00575940.x30, &D_005758D0);
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
    if (!D_00575920 || (path->x18 & 0x10)) func_0017c9a8();
    else func_0017cf08();
    if (D_00575940.x65 != 0) {
        if (D_00575940.x65 == 1) {
            func_0017ba80(2);
            D_00575940.x40 = D_00575940.x44;
            D_00575940.x48 = D_00575940.x4c;
            func_0017b308(m, path->seg, path->n, D_00575940.x40, path->x18 & 1);
            func_0017b250(&D_00575940, m, D_00575940.x48);
            PlatVu0CopyVector(&D_00575940.x20, &D_005758D0);
            D_00575940.x65++;
            D_00575940.x66 = 0;
        }
        if (func_0017b7e8() || (path->x18 & 0x20)) {
            step = D_002BBDFC * 8.0f;
            PlatVu0SubVector(&v, &D_00575940.x0, &D_00575940.x20);
            len = func_00120bf8(&v);
            PlatVu0Normalize(&v, &v);
            PlatVu0ScaleVector(&v, &v, step);
            PlatVu0AddVector(&D_00575940.x20, &D_00575940.x20, &v);
            if (len < 50.0f) D_00575940.x65 = 0;
        }
        if (path->x18 & 2) func_0017b740(&D_005758D0, &D_00575940.x20);
        else PlatVu0CopyVector(&D_005758D0, &D_00575940.x20);
    } else {
        if (path->x18 & 2) func_0017b740(&D_005758D0, &D_00575940.x0);
        else PlatVu0CopyVector(&D_005758D0, &D_00575940.x0);
    }
    if ((u32)(&D_002C5BB0)->x8 & 0x8000) {
        if (func_00177358(D_00575894) && !func_001375d8(D_00575894) && !((D_002C5958 >> 13) & 1) && !D_00362420) {
            func_00176f08(2, D_002BBDFC);
            func_0017b200();
        }
    }
}
#undef D_005758D0
#undef D_002C5BB0
#undef D_00575940
#undef func_00120c18
#undef D_00575894
#undef D_002C5958

/* func_0017d570 (from auto/text_00170000_3.c). */
void func_0017d570(void) {
    if (D_00362438 != 0) {
        func_0017d1e0();
    }
}

/* func_0017d5a0 (from auto/text_00170000_3.c). */
void func_0017d5a0(void) {
    if (D_00362438 != 0) {
        func_0017d208();
    }
}

/* func_0017d5d0 (from hand/text_00170000_h11.c). */
extern f32 D_005758E0[4];
extern f32 D_00362684;
void func_0017ae48(void);
f32 func_00124d28(void *, void *);
void func_0017d5d0(void) {
    if (D_00362434) func_0017ae48();
    else func_0017d238();
    D_00362684 = func_00124d28(D_005758D0, D_005758E0);
}


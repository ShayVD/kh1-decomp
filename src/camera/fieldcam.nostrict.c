/* The field camera's core, without strict aliasing (docs/modules.md
 * "Session 51"): func_001770b8 (is the player moving), func_00177488 (a
 * wall ray), func_00177ac0 (the camera distance against walls, eased),
 * func_001784c8 (search 30-degree steps around the player for a free view) and
 * func_00179d30.  fieldcam.c has the rest.  Read from the code, not proved
 * by a boot. */
#include "common.h"
#include "platform/vu.h"
#include "data/types/nostrict_text_00170000_b06.h"
#include "data/pieces/D_00362438.h"
#include "data/pieces/D_002C58A0.h"
#include "data/pieces/D_002C58D0.h"
#include "data/pieces/D_0035BD40.h"
#include "data/pieces/D_002E27C8.h"
#include "data/pieces/D_0035C440.h"
#include "data/pieces/D_0035C460.h"
#include "data/pieces/D_002C58B0.h"

/* func_001770b8 (from hand/nostrict/text_00170000_b06.c). */
typedef struct {
    s32 x0; u8 pad4[0x10 - 4]; V4 x10; u8 pad20[0x10]; f32 x30[3]; f32 x3c; u8 pad40[0x64 - 0x40]; f32 x64;
    u8 pad68[0x70 - 0x68]; s32 x70; u8 pad74[0xd0 - 0x74]; f32 xd0[4][4];
} ActB;
extern ActB *D_00575894;
extern f32 D_003623F8;
s32 func_001770b8(void) {
    switch (D_00575894->x70) {
    case 0: return D_003623F8 > 1.0f;
    case 8: return D_003623F8 > 7.0f;
    case 24: return D_003623F8 > 7.0f;
    default: return D_003623F8 > 0.1f;
    }
}

/* func_00177488 (from hand/nostrict/text_00170000_s9_r2_2.c). */
#define ASSERT(x) do { } while (0)
typedef struct { f32 x, y, z, w; } V4_74;
typedef struct { V4_74 p; V4_74 d; V4_74 hit; s16 id; u8 pad[14]; } Ray74;
typedef struct { V4_74 p; V4_74 d; f32 r; u8 pad[12]; V4_74 out; } Sph74;
void func_00118d78(Ray74 *);
void func_00118608(Ray74 *);
s32 func_00118868(Sph74 *);
f32 func_00120bf8(V4_74 *);
/* func_00177488 (hand/nostrict, no context). func_00118608 takes one argument.
 * The compiled-out assert after the join's func_002675a8 call ends the basic
 * block there (an empty do-while), so gcse's hoisted &s / &r.hit setups land in
 * the next block; the call then has no in-block dependents and sched1 issues
 * lim = 20.0f before it (LUID tie), as in the original. */
s32 func_00177488(V4_74 *out, V4_74 *a, V4_74 *b) {
    V4_74 v;
    Ray74 r;
    Sph74 s;
    s32 hit, n;
    f32 d, lim;
    PlatVu0SubVector(&r.d, b, a);
    PlatVu0CopyVector(&r.p, a);
    func_00118d78(&r);
    hit = r.id != -1;
    if (!hit) {
        func_00118608(&r);
        if (r.id != -1) hit = 1;
        if (!hit) goto done;
    }
    lim = 20.0f;
    PlatVu0CopyVector(out, a);
    ASSERT(hit);
    goto test;
body:
    if (d >= lim) PlatVu0ScaleVector(&v, &v, lim / d);
    PlatVu0CopyVector(&s.d, &v);
    s.r = 40.0f;
    n = func_00118868(&s);
    PlatVu0CopyVector(out, &s.out);
    if (n) goto done;
    if (!(d >= lim)) goto done;
test:
    PlatVu0CopyVector(&s.p, out);
    PlatVu0SubVector(&v, &r.hit, out);
    d = func_00120bf8(&v);
    if (!(d >= 1000.0f)) goto body;
done:
    return hit;
}
#undef ASSERT

/* func_00177ac0 (from hand/nostrict/text_00130000_s6_na_2.c). */
typedef struct { f32 org[4]; f32 dir[4]; f32 hit[4]; s16 id; s16 pad32; s32 x34; u8 pad38[8]; } Ray7A;
typedef struct { f32 a[4]; f32 b[4]; u8 pad[32]; } Seg7A;
typedef struct { f32 x0, x4, x8; } S58F0;
extern f32 D_005758D0[4];
extern f32 D_005758E0[4];
extern S58F0 D_005758F0;
extern f32 D_00362684;
extern f32 D_002BBDFC;
typedef struct { f32 x0, x4; } S2680;
extern S2680 D_00362680;
extern u64 D_002C5BB0;
f32 sinf(f32);
void func_00105a70(s32, s32, f32 *);
s32 func_00119688(Seg7A *);
f32 func_00120c88(f32);
f32 func_00124d28(f32 *, f32 *);
s32 func_00177ac0(void) {
    Ray7A r;
    f32 v40[4];
    f32 v50[4];
    f32 v60[4];
    f32 v70[4];
    f32 v80[4];
    f32 unk[3][4];
    Seg7A s;
    s32 ok, a, b;
    f32 ang, d;

    if (D_005758F0.x8 > 0.0f) {
        f32 t = sinf((1.0f - D_005758F0.x8 / 40.0f) * 3.1415928f * 0.5f);
        D_00362684 = D_005758F0.x0 + D_005758F0.x4 * t;
        D_005758F0.x8 -= D_002BBDFC;
        return 1;
    }
    D_005758F0.x8 = 0.0f;
    PlatVu0SubVector(v40, D_005758E0, D_005758D0);
    PlatVu0SubVector(v50, D_005758D0, D_005758E0);
    PlatVu0Normalize(v70, v50);
    v70[1] = 0.0f;
    PlatVu0RotMatrixY(v80, D_002C58D0[0], 1.5707962f);
    PlatVu0ApplyMatrix(v70, v80, v70);
    PlatVu0ScaleVector(v70, v70, 50.0f);
    PlatVu0CopyVector(r.dir, v50);
    PlatVu0AddVector(r.org, D_005758E0, v70);
    func_00118d78(&r);
    if (r.id != -1) ok = 1; else {
        PlatVu0ScaleVector(v70, v70, -1.0f);
        PlatVu0AddVector(r.org, D_005758E0, v70);
        func_00118d78(&r);
        ok = r.id != -1;
    }

    if (ok) {
        PlatVu0Normalize(v70, v40);
        PlatVu0ScaleVector(v70, v70, 300.0f);
        PlatVu0CopyVector(s.a, D_005758D0);
        PlatVu0RotMatrixY(v80, D_002C58D0[0], 0.52359875f);
        PlatVu0ApplyMatrix(s.b, v80, v70);
        a = func_00119688(&s) != -1;
        PlatVu0RotMatrixY(v80, D_002C58D0[0], -0.52359875f);
        PlatVu0ApplyMatrix(s.b, v80, v70);
        b = func_00119688(&s) != -1;
        if (a && b) return 0;
        if ((b || a) && func_001770b8()) {
            func_00105a70(r.x34, r.id, v60);
            PlatVu0SubVector(v70, r.hit, D_005758D0);
            v70[1] = v60[1] = 0.0f;
            PlatVu0Normalize(v70, v70);
            PlatVu0Normalize(v60, v60);
            ang = func_00124d28(v60, (*(f32 (*)[0x4])&D_002C58A0));
            PlatVu0OuterProduct(v70, v70, v60);
            d = func_00120c88(v70[1] >= 0.0f ? ang + 1.5707962f : ang - 1.5707962f);
            d = d - func_00120c88(D_00362680.x4);
            if (fabsf(d) > 3.1415928f) {
                if (d < 0.0f) d += 6.2831855f; else d -= 6.2831855f;
            }
            D_005758F0.x0 = func_00120c88(D_00362680.x4);
            D_005758F0.x4 = d;
            D_005758F0.x8 = 40.0f;

        }
    }
    if (D_002C5BB0 & ((u64)0xC000 << 30)) D_005758F0.x8 = 0.0f;
    return 1;
}

/* func_001784c8 (from hand/nostrict/text_00160000_s6_09.c). */
typedef struct { f32 org[4]; f32 dir[4]; u8 pad[32]; } Ray84;
typedef struct { f32 x0, x4, x8, xc, x10; s32 x14; } S5900;
typedef struct { f32 x0, x4, x8, xc; } S2680b;
typedef struct { u8 pad[0x3C]; f32 x3c; } S5894;
extern S5900 D_00575900;
extern f32 D_0036266C;
#define D_00575894 ((S5894 *) D_00575894)
#define D_00362680 (*(S2680b (*)) &D_00362680)
void func_001784c8(void) {
    Ray84 r;
    f32 prev[4];
    f32 pos[4];
    f32 up[4];
    f32 t[4];
    f32 m[4][4];
    f32 m2[4][4];
    s32 found;
    f32 step = 0.52359875f;
    f32 range, ang;
    s32 dir;

    if (D_00575900.xc > 0.0f) return;
    range = func_00120c88(D_00575894->x3c + 3.1415928f - D_00362680.x4);
    if (range > 0.0f) dir = 1; else dir = 0;
    PlatVu0RotMatrixX(m, D_002C58D0[0], func_00120c88(D_00362680.x0));
    PlatVu0CopyVector(up, (*(f32 (*)[0x4])&D_002C58A0));
    up[2] = D_00362680.xc;
    PlatVu0RotMatrixY(m2, m, func_00120c88(D_00362680.x4 + range));
    PlatVu0ApplyMatrix(r.dir, m2, up);
    PlatVu0CopyVector(r.org, D_005758E0);
    if (func_00119688(&r) != -1) dir = 2;
    if (dir != 2) {
        found = 0;
        if (dir == 0) step = -step;
        PlatVu0CopyVector(pos, D_005758D0);
        range = fabsf(range);
        for (ang = step; fabsf(ang) <= range; ang += step) {
            PlatVu0CopyVector(prev, pos);
            PlatVu0RotMatrixY(m2, m, func_00120c88(D_00362680.x4 + ang));
            PlatVu0ApplyMatrix(t, m2, up);
            PlatVu0AddVector(pos, D_005758E0, t);
            PlatVu0CopyVector(r.org, prev);
            PlatVu0SubVector(r.dir, pos, prev);
            if (func_00119688(&r) != -1) { found = 1; break; }
        }
        if (found) {
            step = -step;
            range = 6.2831855f - range;
            PlatVu0CopyVector(pos, D_005758D0);
            dir = !dir;
            found = 0;
            for (ang = step; fabsf(ang) <= range; ang += step) {
                PlatVu0CopyVector(prev, pos);
                PlatVu0RotMatrixY(m2, m, func_00120c88(D_00362680.x4 + ang));
                PlatVu0ApplyMatrix(t, m2, up);
                PlatVu0AddVector(pos, D_005758E0, t);
                PlatVu0CopyVector(r.org, prev);
                PlatVu0SubVector(r.dir, pos, prev);
                if (func_00119688(&r) != -1) { found = 1; break; }
            }
            if (found) dir = 2;
        }
    }
    D_00575900.x14 = dir;
    D_00575900.x0 = D_00362680.x4;
    D_00575900.x4 = range;
    D_00575900.x8 = D_0036266C;
    D_00575900.xc = 20.0f;
    D_00575900.x10 = 20.0f;
}
#undef D_00575894
#undef D_00362680

/* func_00179d30 (from hand/nostrict/text_00130000_s6_na.c). */
typedef struct { f32 x, y, z, w; } V4_9d;
typedef struct { u8 pad[0x10]; V4_9d pos; } Act9d;
extern f32 D_002E27A0;
extern f32 D_00362520;
void func_001315c0(Act9d *, s32, V4_9d *, f32);
f32 func_00121840(V4_9d *, V4_9d *);
#define D_00575894 (*(Act9d *(*)) &D_00575894)
#define D_005758D0 (*(V4_9d (*)) &D_005758D0)
#define D_005758E0 (*(V4_9d (*)) &D_005758E0)
void func_00179d30(void) {
    V4_9d a, b, c;
    f32 z, lim, ang, af;
    z = 0.0f;
    func_001315c0(D_00575894, 0x8003, &a, z);
    lim = D_002E27A0;
    lim *= 3.14159251f;
    lim /= 180.0f;
    PlatVu0SubVector(&b, &D_005758E0, &D_005758D0);
    PlatVu0SubVector(&c, &D_00575894->pos, &D_005758D0);
    ang = func_00121840(&b, &c);
    af = fabsf(ang);
    lim *= 0.5f;
    if (lim < af) {
        D_00362520 += D_002BBDFC;
        if (40.0f < D_00362520) D_00362520 = 40.0f;
    } else if (af < lim * 0.7999999523162842f) {
        D_00362520 -= D_002BBDFC + D_002BBDFC;
        if (D_00362520 < z) D_00362520 = z;
    }
    if (0.0f < D_00362520) {
        f32 r = D_00362520 / 40.0f;
        PlatVu0InterVector(&D_005758E0, &a, &D_005758E0, r * 0.7999999523162842f);
    }
}
#undef D_00575894
#undef D_005758D0
#undef D_005758E0


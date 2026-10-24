/* Platform wrapper: VU0 vector and matrix maths (libvu0). See docs/portability.md.
 *
 * The game does its 3D maths through libvu0 about 3,800 times: copy, add,
 * subtract, scale and normalize 4-vectors (f32 [4], quadword aligned; most
 * of the game's own vector structs, V4 / V4f / PppVec4 ..., are this layout),
 * dot and cross products, and 4x4 matrices (f32 [4][4], row-major, the
 * translation in row 3: multiply, rotate, transpose, rigid inverse, apply to
 * a vector, camera / view-screen / light matrices).  On the matching PS2
 * build each wrapper is a macro for the libvu0 call (src/sdk/libvu0/vu0.s,
 * VU0 macro mode); the casts take the game's own vector / matrix types and
 * compile to nothing, and a float argument stays a float (the cast is to f32,
 * as libvu0's prototype converts it).  The macros are the same on every
 * target: the Vita port links a C (NEON) libvu0 with the sceVu0 signatures of
 * include/sce/libvu0.h in place of vu0.s, so no game file changes; libvu0's
 * results are plain IEEE single precision except where the VU differs
 * (no denormals, no NaN / infinity: clamped to +-max), which the port should
 * keep in mind for the vrsqrt of PlatVu0Normalize and the vdiv of
 * PlatVu0DivVector.
 *
 * A function pointer to a libvu0 routine (src/ppp/keth.nostrict.c's rotation
 * table) names sceVu0Rot* directly, which the port's libvu0 defines too. */
#ifndef KH1_PLATFORM_VU_H
#define KH1_PLATFORM_VU_H

#include "common.h"

#include "sce/libvu0.h"

#define PlatVu0ApplyMatrix(v0, m0, v1) sceVu0ApplyMatrix((f32 *)(v0), (f32 (*)[4])(m0), (f32 *)(v1))
#define PlatVu0MulMatrix(m0, m1, m2) sceVu0MulMatrix((f32 (*)[4])(m0), (f32 (*)[4])(m1), (f32 (*)[4])(m2))
#define PlatVu0OuterProduct(v0, v1, v2) sceVu0OuterProduct((f32 *)(v0), (f32 *)(v1), (f32 *)(v2))
#define PlatVu0InnerProduct(v0, v1) sceVu0InnerProduct((f32 *)(v0), (f32 *)(v1))
#define PlatVu0Normalize(v0, v1) sceVu0Normalize((f32 *)(v0), (f32 *)(v1))
#define PlatVu0TransposeMatrix(m0, m1) sceVu0TransposeMatrix((f32 (*)[4])(m0), (f32 (*)[4])(m1))
#define PlatVu0InversMatrix(m0, m1) sceVu0InversMatrix((f32 (*)[4])(m0), (f32 (*)[4])(m1))
#define PlatVu0DivVector(v0, v1, q) sceVu0DivVector((f32 *)(v0), (f32 *)(v1), (f32)(q))
#define PlatVu0DivVectorXYZ(v0, v1, q) sceVu0DivVectorXYZ((f32 *)(v0), (f32 *)(v1), (f32)(q))
#define PlatVu0InterVector(v0, v1, v2, t) sceVu0InterVector((f32 *)(v0), (f32 *)(v1), (f32 *)(v2), (f32)(t))
#define PlatVu0AddVector(v0, v1, v2) sceVu0AddVector((f32 *)(v0), (f32 *)(v1), (f32 *)(v2))
#define PlatVu0SubVector(v0, v1, v2) sceVu0SubVector((f32 *)(v0), (f32 *)(v1), (f32 *)(v2))
#define PlatVu0MulVector(v0, v1, v2) sceVu0MulVector((f32 *)(v0), (f32 *)(v1), (f32 *)(v2))
#define PlatVu0ScaleVector(v0, v1, t) sceVu0ScaleVector((f32 *)(v0), (f32 *)(v1), (f32)(t))
#define PlatVu0TransMatrix(m0, m1, tv) sceVu0TransMatrix((f32 (*)[4])(m0), (f32 (*)[4])(m1), (f32 *)(tv))
#define PlatVu0CopyVector(v0, v1) sceVu0CopyVector((f32 *)(v0), (f32 *)(v1))
#define PlatVu0CopyMatrix(m0, m1) sceVu0CopyMatrix((f32 (*)[4])(m0), (f32 (*)[4])(m1))
#define PlatVu0FTOI4Vector(v0, v1) sceVu0FTOI4Vector((s32 *)(v0), (f32 *)(v1))
#define PlatVu0FTOI0Vector(v0, v1) sceVu0FTOI0Vector((s32 *)(v0), (f32 *)(v1))
#define PlatVu0ITOF4Vector(v0, v1) sceVu0ITOF4Vector((f32 *)(v0), (s32 *)(v1))
#define PlatVu0ITOF0Vector(v0, v1) sceVu0ITOF0Vector((f32 *)(v0), (s32 *)(v1))
#define PlatVu0UnitMatrix(m0) sceVu0UnitMatrix((f32 (*)[4])(m0))
#define PlatVu0RotMatrixZ(m0, m1, rz) sceVu0RotMatrixZ((f32 (*)[4])(m0), (f32 (*)[4])(m1), (f32)(rz))
#define PlatVu0RotMatrixX(m0, m1, rx) sceVu0RotMatrixX((f32 (*)[4])(m0), (f32 (*)[4])(m1), (f32)(rx))
#define PlatVu0RotMatrixY(m0, m1, ry) sceVu0RotMatrixY((f32 (*)[4])(m0), (f32 (*)[4])(m1), (f32)(ry))
#define PlatVu0RotMatrix(m0, m1, rot) sceVu0RotMatrix((f32 (*)[4])(m0), (f32 (*)[4])(m1), (f32 *)(rot))
#define PlatVu0ClampVector(v0, v1, min, max) \
    sceVu0ClampVector((f32 *)(v0), (f32 *)(v1), (f32)(min), (f32)(max))
#define PlatVu0CameraMatrix(m, p, zd, yd) \
    sceVu0CameraMatrix((f32 (*)[4])(m), (f32 *)(p), (f32 *)(zd), (f32 *)(yd))
#define PlatVu0NormalLightMatrix(m, l0, l1, l2) \
    sceVu0NormalLightMatrix((f32 (*)[4])(m), (f32 *)(l0), (f32 *)(l1), (f32 *)(l2))
#define PlatVu0LightColorMatrix(m, c0, c1, c2, a) \
    sceVu0LightColorMatrix((f32 (*)[4])(m), (f32 *)(c0), (f32 *)(c1), (f32 *)(c2), (f32 *)(a))
#define PlatVu0ViewScreenMatrix(m, scrz, ax, ay, cx, cy, zmin, zmax, nearz, farz) \
    sceVu0ViewScreenMatrix((f32 (*)[4])(m), (f32)(scrz), (f32)(ax), (f32)(ay), (f32)(cx), (f32)(cy), (f32)(zmin), (f32)(zmax), (f32)(nearz), (f32)(farz))
#define PlatVu0DropShadowMatrix(m, lp, a, b, c, mode) \
    sceVu0DropShadowMatrix((f32 (*)[4])(m), (f32 *)(lp), (f32)(a), (f32)(b), (f32)(c), (s32)(mode))
#define PlatVu0RotTransPersN(v0, m0, v1, n, mode) \
    sceVu0RotTransPersN((s32 *)(v0), (f32 (*)[4])(m0), (f32 *)(v1), (s32)(n), (s32)(mode))
#define PlatVu0RotTransPers(v0, m0, v1, mode) \
    sceVu0RotTransPers((s32 *)(v0), (f32 (*)[4])(m0), (f32 *)(v1), (s32)(mode))
#define PlatVu0CopyVectorXYZ(v0, v1) sceVu0CopyVectorXYZ((f32 *)(v0), (f32 *)(v1))
#define PlatVu0InterVectorXYZ(v0, v1, v2, t) \
    sceVu0InterVectorXYZ((f32 *)(v0), (f32 *)(v1), (f32 *)(v2), (f32)(t))
#define PlatVu0ScaleVectorXYZ(v0, v1, s) sceVu0ScaleVectorXYZ((f32 *)(v0), (f32 *)(v1), (f32)(s))
#define PlatVu0ClipScreen(v0) sceVu0ClipScreen((f32 *)(v0))
#define PlatVu0ClipScreen3(v0, v1, v2) sceVu0ClipScreen3((f32 *)(v0), (f32 *)(v1), (f32 *)(v2))
#define PlatVu0ClipAll(minv, maxv, ms, vm, n) \
    sceVu0ClipAll((f32 *)(minv), (f32 *)(maxv), (f32 (*)[4])(ms), (f32 *)(vm), (s32)(n))
#define PlatVpu0Reset() sceVpu0Reset()

/* Off the EE: C equivalents of the VU0 macro-mode sequences the game writes
 * as inline asm (docs/vita-port-plan.md section 5.1).  The PS2 build keeps
 * each file's __asm__ (the match depends on it); the file's #else side calls
 * these.  VU0 maths is IEEE single precision without denormals, NaN or
 * infinity; these use the host's floats (the same caveat as libvu0 above). */
#ifndef KH1_PS2
#include "platform/math.h"

typedef union { f32 f; u32 u; s32 i; } PlatVu0Word;

static __inline__ f32 PlatVu0Float(u32 bits) {
    PlatVu0Word w;
    w.u = bits;
    return w.f;
}
static __inline__ u32 PlatVu0Bits(f32 f) {
    PlatVu0Word w;
    w.f = f;
    return w.u;
}

/* The VU0 random register R (host/port/vu0.c): a 23-bit LFSR kept as the
 * mantissa of a float in [1, 2).  vrinit / vrxor take a field's bits, vrget
 * reads R, vrnext steps it first (PCSX2's model of the shift register). */
extern u32 PlatVu0R;
static __inline__ void PlatVu0RInit(u32 bits) { PlatVu0R = 0x3F800000 | (bits & 0x7FFFFF); }
static __inline__ void PlatVu0RXor(u32 bits) { PlatVu0R = 0x3F800000 | ((PlatVu0R ^ bits) & 0x7FFFFF); }
static __inline__ f32 PlatVu0RGet(void) { return PlatVu0Float(PlatVu0R); }
static __inline__ f32 PlatVu0RNext(void) {
    u32 r = PlatVu0R;
    r = (r << 1) ^ (((r >> 4) ^ (r >> 22)) & 1);
    PlatVu0R = 0x3F800000 | (r & 0x7FFFFF);
    return PlatVu0Float(PlatVu0R);
}
/* The ppp files' random number in [0, 1): five rounds of `vrxor R, -1;
 * vrnext`, then minus 1.0 (vitof0 of -1). */
static __inline__ f32 PlatVu0Rand(void) {
    f32 r;
    int i;
    for (i = 0; i < 5; i++) {
        PlatVu0RXor(0xFFFFFFFF);
        r = PlatVu0RNext();
    }
    return r - 1.0f;
}

/* vsqrt Q: the root of the magnitude. */
static __inline__ f32 PlatVu0Sqrt(f32 x) { return PlatSqrtf(x < 0.0f ? -x : x); }

/* |v| over xyz (vmul.xyz, vaddx.y, vaddy.z, vsqrt) */
static __inline__ f32 PlatVu0Length3(const f32 *v) {
    return PlatVu0Sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
}

/* vftoi0 / vftoi4: truncate (after scaling by 16 for ftoi4), saturating. */
static __inline__ s32 PlatVu0Ftoi0(f32 x) {
    if (x >= 2147483648.0f)
        return 0x7FFFFFFF;
    if (x <= -2147483648.0f)
        return (s32)0x80000000;
    return (s32)x;
}
static __inline__ s32 PlatVu0Ftoi4(f32 x) { return PlatVu0Ftoi0(x * 16.0f); }

/* d = v.x m[0] + v.y m[1] + v.z m[2] + v.w m[3] (vmulax / vmadday / vmaddaz
 * / vmaddw: what sceVu0ApplyMatrix does); d may be v. */
static __inline__ void PlatVu0Apply(f32 *d, f32 (*m)[4], const f32 *v) {
    f32 x = v[0], y = v[1], z = v[2], w = v[3];
    int i;
    for (i = 0; i < 4; i++)
        d[i] = m[0][i] * x + m[1][i] * y + m[2][i] * z + m[3][i] * w;
}

/* `cfc2 $vi29`: VPU-STAT (0x100: VU1 running). */
u32 PlatVu0GetVpuStat(void);

/* `vmulx.xyz` of a row by a scalar: the matrix-scale helper several ppp
 * files inline (w kept). */
static __inline__ void PlatVu0ScaleXYZ(f32 *v, f32 s) {
    v[0] *= s;
    v[1] *= s;
    v[2] *= s;
}
#endif /* !KH1_PS2 */

#endif /* KH1_PLATFORM_VU_H */

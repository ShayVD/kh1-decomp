#include "common.h"
#include "ppp.h"

#define PPP_WORK(T, obj, e, k) ((T *) ((u8 *) (obj) + (e)->offsets[k] + 0xA0))

typedef int u128 __attribute__((mode(TI)));
typedef f32 PppMtx[4][4] __attribute__((aligned(16)));
typedef f32 PppVec4[4] __attribute__((aligned(16)));

typedef struct {
    s32 unk00, unk04, unk08;
    s32 frame;
} PppObject;

typedef struct {
    u8 pad[0x10];
    PppMtx m;
    PppMtx m2;
} PppMtxOwner;
extern PppMtxOwner *D_00615E68;

typedef struct {
    s16 off;
    s16 dur;
    s8 flags;
    u8 pad5[3];
} PppShapeFrame;
typedef struct {
    u8 pad0[6];
    s16 n;
    u8 pad8[8];
    PppShapeFrame f[1];
} PppShape;
typedef struct {
    PppShape *shape;
    s32 unk4;
} PppShapeEnt;
typedef struct {
    u8 pad00[0x14];
    PppShapeEnt *shapes;
} DSysS;
extern DSysS *D_00615E64;
extern s32 D_00616224;

typedef struct {
    u16 unk0;
    u16 flags;
    u8 r, g, b, a;
    u16 h8[4];
    void *p10;
    s32 w14;
    u8 b18;
    void *p1C;
    u8 pad20[0x10];
} TailParam;

extern f32 D_003701F0[2];
extern PppMtx D_00615EB0, D_00615FC0, D_00616040;

void sceVu0CopyMatrix(PppMtx, PppMtx);
void sceVu0UnitMatrix(PppMtx);
void func_00267530(f32 *, f32 *, f32 *);
void func_002674b0(f32 *, f32 *, f32);
void func_002675a8(f32 *, f32 *);
f32 func_001a9350(f32 *);
s32 func_001b8198(void *, TailParam *, s32);

static inline void vuFtoi0Bytes(u8 *d, f32 *s) {
    __asm__ volatile(
        "lqc2 $vf31, 0(%1)\n"
        "vftoi0.xyzw $vf31xyzw, $vf31xyzw\n"
        "qmfc2 $2, $vf31\n"
        "sb $2, 0(%0)\n"
        "mtsab $0, 4\n"
        "qfsrv $2, $2, $2\n"
        "sb $2, 1(%0)\n"
        "qfsrv $2, $2, $2\n"
        "sb $2, 2(%0)\n"
        "qfsrv $2, $2, $2\n"
        "sb $2, 3(%0)\n"
        : : "r"(d), "r"(s) : "$2", "memory");
}

static inline void vuScaleXYZ(f32 *d, f32 *s, f32 f) {
    __asm__ volatile(
        "lqc2 $vf31, 0(%1)\n"
        "lqc2 $vf29, 0(%0)\n"
        "mfc1 $2, %2\n"
        "qmtc2 $2, $vf30\n"
        "vmulx.xyz $vf29xyz, $vf31xyz, $vf30x\n"
        "sqc2 $vf29, 0(%0)\n"
        : : "r"(d), "r"(s), "f"(f) : "$2", "memory");
}

static inline void vuApply(f32 *d, PppMtx m, f32 *v) {
    __asm__ volatile(
        "lqc2 $vf27, 0(%1)\n"
        "lqc2 $vf28, 16(%1)\n"
        "lqc2 $vf29, 32(%1)\n"
        "lqc2 $vf30, 48(%1)\n"
        "lqc2 $vf31, 0(%2)\n"
        "vmulax.xyzw ACCxyzw, $vf27xyzw, $vf31x\n"
        "vmadday.xyzw ACCxyzw, $vf28xyzw, $vf31y\n"
        "vmaddaz.xyzw ACCxyzw, $vf29xyzw, $vf31z\n"
        "vmaddw.xyzw $vf27xyzw, $vf30xyzw, $vf31w\n"
        "sqc2 $vf27, 0(%0)\n"
        : : "r"(d), "r"(m), "r"(v) : "memory");
}

static inline void vuApply2(f32 *d, PppMtx m, f32 *v) {
    __asm__ volatile(
        "lqc2 $vf27, 0(%1)\n"
        "lqc2 $vf28, 16(%1)\n"
        "lqc2 $vf29, 32(%1)\n"
        "lqc2 $vf30, 48(%1)\n"
        "lqc2 $vf31, 0(%2)\n"
        "vmulax.xyzw ACCxyzw, $vf27xyzw, $vf31x\n"
        "vmadday.xyzw ACCxyzw, $vf28xyzw, $vf31y\n"
        "vmaddaz.xyzw ACCxyzw, $vf29xyzw, $vf31z\n"
        "vmaddw.xyzw $vf27xyzw, $vf30xyzw, $vf31w\n"
        "sqc2 $vf27, 0(%0)\n\t"
        : : "r"(d), "r"(m), "r"(v) : "memory");
}

static inline void vuMulMatrix(PppMtx d, PppMtx a, PppMtx b) {
    __asm__ volatile(
        "lqc2 $vf27, 0(%1)\n"
        "lqc2 $vf28, 16(%1)\n"
        "lqc2 $vf29, 32(%1)\n"
        "lqc2 $vf30, 48(%1)\n"
        "lqc2 $vf31, 0(%2)\n"
        "vmulax.xyzw ACCxyzw, $vf27xyzw, $vf31x\n"
        "vmadday.xyzw ACCxyzw, $vf28xyzw, $vf31y\n"
        "vmaddaz.xyzw ACCxyzw, $vf29xyzw, $vf31z\n"
        "vmaddw.xyzw $vf26xyzw, $vf30xyzw, $vf31w\n"
        "sqc2 $vf26, 0(%0)\n"
        "lqc2 $vf31, 16(%2)\n"
        "vmulax.xyzw ACCxyzw, $vf27xyzw, $vf31x\n"
        "vmadday.xyzw ACCxyzw, $vf28xyzw, $vf31y\n"
        "vmaddaz.xyzw ACCxyzw, $vf29xyzw, $vf31z\n"
        "vmaddw.xyzw $vf26xyzw, $vf30xyzw, $vf31w\n"
        "sqc2 $vf26, 16(%0)\n"
        "lqc2 $vf31, 32(%2)\n"
        "vmulax.xyzw ACCxyzw, $vf27xyzw, $vf31x\n"
        "vmadday.xyzw ACCxyzw, $vf28xyzw, $vf31y\n"
        "vmaddaz.xyzw ACCxyzw, $vf29xyzw, $vf31z\n"
        "vmaddw.xyzw $vf26xyzw, $vf30xyzw, $vf31w\n"
        "sqc2 $vf26, 32(%0)\n"
        "lqc2 $vf31, 48(%2)\n"
        "vmulax.xyzw ACCxyzw, $vf27xyzw, $vf31x\n"
        "vmadday.xyzw ACCxyzw, $vf28xyzw, $vf31y\n"
        "vmaddaz.xyzw ACCxyzw, $vf29xyzw, $vf31z\n"
        "vmaddw.xyzw $vf26xyzw, $vf30xyzw, $vf31w\n"
        "sqc2 $vf26, 48(%0)\n"
        : : "r"(d), "r"(a), "r"(b) : "memory");
}

static inline void vuSub(f32 *d, f32 *a, f32 *b) {
    __asm__ volatile(
        "lqc2 $vf31, 0(%1)\n"
        "lqc2 $vf30, 0(%2)\n"
        "vsub.xyzw $vf31xyzw, $vf31xyzw, $vf30xyzw\n"
        "sqc2 $vf31, 0(%0)\n"
        : : "r"(d), "r"(a), "r"(b) : "memory");
}

static inline void vuAdd(f32 *d, f32 *a, f32 *b) {
    __asm__ volatile(
        "lqc2 $vf31, 0(%1)\n"
        "lqc2 $vf30, 0(%2)\n"
        "vadd.xyzw $vf31xyzw, $vf31xyzw, $vf30xyzw\n"
        "sqc2 $vf31, 0(%0)\n"
        : : "r"(d), "r"(a), "r"(b) : "memory");
}

static inline void vuScale(f32 *d, f32 *s, f32 f) {
    __asm__ volatile(
        "lqc2 $vf31, 0(%1)\n"
        "mfc1 $2, %2\n"
        "qmtc2 $2, $vf30\n"
        "vmulx.xyzw $vf31xyzw, $vf31xyzw, $vf30x\n"
        "sqc2 $vf31, 0(%0)\n"
        : : "r"(d), "r"(s), "f"(f) : "$2", "memory");
}

static inline void vuCopy(f32 *d, f32 *s) {
    __asm__ volatile(
        "lqc2 $vf31, 0(%1)\n"
        "sqc2 $vf31, 0(%0)\n"
        : : "r"(d), "r"(s) : "memory");
}

static inline f32 vuLen(f32 *v) {
    f32 r;
    __asm__ volatile(
        "lqc2 $vf31, 0(%1)\n"
        "vmul.xyz $vf31xyz, $vf31xyz, $vf31xyz\n"
        "vaddy.x $vf31x, $vf31x, $vf31y\n"
        "vaddz.x $vf31x, $vf31x, $vf31z\n"
        "vsqrt Q, $vf31x\n"
        "vwaitq\n"
        "vaddq.x $vf31x, $vf0x, Q\n"
        "qmfc2 $2, $vf31\n"
        "mtc1 $2, %0\n"
        : "=f"(r) : "r"(v) : "$2", "memory");
    return r;
}

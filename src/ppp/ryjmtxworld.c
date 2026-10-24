/* The ppp matrix classes, default flags (docs/modules.md "Session 50"): the
 * pppRyjDrawMatrixWorld family sets the current owner's draw matrix
 * (D_00615E68's second matrix) from the effect's position, rotation and
 * scale: plain, Front (facing the camera, func_00267620), NoRot (position
 * only) and Wood (a billboard about the camera's up axis, built once in the
 * Con into D_00616010 / D_006160C0).  The pppRyjMatrixWorld classes' Cons
 * (one per rotation order: XYZ, XZY, YXZ, YZX, ZXY, ZYX, pppmtx.c) set the
 * work area's rotation matrix; their frames are in ryjmtxworld.nostrict.c.
 * Each section names the file its code came from.  Read from the code, not
 * proved by a boot. */

/* pppRyjDrawMatrixWorldCon (from auto/text_00190000_6.c). */
#include "m2c.h"
#include "platform/vu.h"
#include "ppp.h"
#include "data/pieces/D_003701D0.h"
#include "data/pieces/D_003701F0.h"
extern M2C_UNK D_00615E70;
void pppRyjDrawMatrixWorldCon(s32 arg0, PppEntry *arg1) {
    PlatVu0CopyMatrix(arg0 + arg1->offsets[1] + 0xA0, &D_00615E70);
}

/* pppRyjDrawMatrixWorldFrame (from auto/text_00190000_7.c). */
extern M2C_UNK D_00615EB0;
extern M2C_UNK D_00616040;
extern s32 D_00615E68;
void pppRyjDrawMatrixWorldFrame(s32 arg0, s32 arg1, void *arg2) {
    M2C_UNK *temp_a0;
    M2C_UNK *temp_a0_2;

    PlatVu0MulMatrix(D_00615E68 + 0x50, &D_00615EB0, arg0 + M2C_FIELD(M2C_FIELD(arg2, void **, 0xC), s32 *, 4) + 0xA0);
    temp_a0 = D_00615E68 + 0x50;
    PlatVu0MulMatrix(temp_a0, &D_00616040, temp_a0);
    temp_a0_2 = D_00615E68 + 0x50;
    PlatVu0MulMatrix(temp_a0_2, temp_a0_2, D_00615E68 + 0x10);
}

/* pppRyjDrawMatrixWorldFrontCon (from auto/text_00190000_6.c). */
void pppRyjDrawMatrixWorldFrontCon(s32 arg0, PppEntry *arg1) {
    s32 temp_s0;

    temp_s0 = arg0 + arg1->offsets[1];
    PlatVu0CopyVector(temp_s0 + 0xA0, ((M2C_UNK *)&D_003701D0));
    PlatVu0CopyVector(temp_s0 + 0xB0, (M2C_UNK *)&D_003701F0);
}

/* pppRyjDrawMatrixWorldFrontFrame (from auto/text_00190000_8.c). */
void pppRyjDrawMatrixWorldFrontFrame(s32 arg0, s32 arg1, void *arg2) {
    s32 sp[16];    void *temp_a0;
    void *temp_s1;

    temp_s1 = arg0 + M2C_FIELD(M2C_FIELD(arg2, void **, 0xC), s32 *, 4) + 0xA0;
    PlatVu0UnitMatrix(sp);
    M2C_FIELD(sp, f32 *, 0x30) = M2C_FIELD(temp_s1, f32 *, 0);
    M2C_FIELD(sp, f32 *, 0x34) = M2C_FIELD(temp_s1, f32 *, 4);
    M2C_FIELD(sp, f32 *, 0x38) = M2C_FIELD(temp_s1, f32 *, 8);
    PlatVu0MulMatrix(sp, &D_00615EB0, sp);
    PlatVu0ScaleVector(D_00615E68 + 0x50, D_00615E68 + 0x10, M2C_FIELD(temp_s1, f32 *, 0x10));
    PlatVu0ScaleVector(D_00615E68 + 0x60, D_00615E68 + 0x20, M2C_FIELD(temp_s1, f32 *, 0x14));
    PlatVu0ScaleVector(D_00615E68 + 0x70, D_00615E68 + 0x30, M2C_FIELD(temp_s1, f32 *, 0x18));
    PlatVu0ApplyMatrix(D_00615E68 + 0x80, sp, D_00615E68 + 0x40);
    temp_a0 = D_00615E68 + 0x50;
    PlatVu0MulMatrix(temp_a0, &D_00616040, temp_a0);
}

/* pppRyjDrawMatrixWorldNoRotCon (from auto/text_00190000_6.c). */
void pppRyjDrawMatrixWorldNoRotCon(s32 arg0, PppEntry *arg1) {
    s32 temp_s0;

    temp_s0 = arg0 + arg1->offsets[1];
    PlatVu0CopyVector(temp_s0 + 0xA0, ((M2C_UNK *)&D_003701D0));
    PlatVu0CopyVector(temp_s0 + 0xB0, (M2C_UNK *)&D_003701F0);
}

/* pppRyjDrawMatrixWorldWoodCon (from hand/text_00180000_h40.c). */
#include "common.h"
#include "data/types/shared.h"
#include "data/types/text_00180000_h40.h"
#define PPP_WORK(T, obj, e, k) ((T *) ((u8 *) (obj) + (e)->offsets[k] + 0xA0))
extern PppQv D_00615FC0[4];
typedef struct {
    s32 unk00, unk04, unk08;
    s32 frame; /* +0x0C */
    u8 pad10[0x8D];
    u8 unk9D;  /* +0x9D */
} PppObject;
typedef f32 PppVec4[4] __attribute__((aligned(16)));
extern PppQv D_00616000_rows[4] __asm__("D_00616000");
#define D_00616010 (D_00616000_rows + 1)
extern PppMtx D_006160C0;
#define D_00616040 ((PppQv *) &D_00616040)
void pppRyjDrawMatrixWorldWoodCon(PppObject *obj, PppEntry *e) {
    PppQv u, v, c;
    f32 *w = PPP_WORK(f32, obj, e, 1);

    PlatVu0CopyVector(w, (*(f32 (*)[4])&D_003701D0));
    PlatVu0CopyVector(w + 4, D_003701F0);
    v.f[0] = D_00615FC0[1].f[0];
    v.f[1] = D_00615FC0[1].f[1];
    v.f[2] = D_00615FC0[1].f[2];
    v.f[3] = 0.0f;
    PlatVu0Normalize(v.f, v.f);
    D_00616010[0].q = v.q;
    u.f[0] = v.f[1];
    u.f[1] = -v.f[0];
    u.f[2] = 0.0f;
    u.f[3] = 0.0f;
    PlatVu0Normalize(u.f, u.f);
    D_00616010[-1].q = u.q;
    PlatVu0OuterProduct(c.f, u.f, v.f);
    PlatVu0Normalize(c.f, c.f);
    D_00616010[1].q = c.q;
    D_00616010[2].q = D_00615FC0[3].q;
    PlatVu0MulMatrix(D_006160C0, (f32 (*)[4]) D_00616040, (f32 (*)[4]) &D_00616010[-1]);
}
#undef D_00616040

/* pppRyjDrawMatrixWorldWoodFrame (from hand/text_00180000_h40.c). */
typedef struct {
    u8 pad[0x10];
    PppMtx m;    /* +0x10 */
    PppMtx m2;   /* +0x50 */
} PppMtxOwner;
#define D_00616040 ((PppQv *) &D_00616040)
#define D_00615E68 ((PppMtxOwner *) D_00615E68)
#define D_00615EB0 (*(PppMtx (*)) &D_00615EB0)
void pppRyjDrawMatrixWorldWoodFrame(PppObject *obj, void *key, PppEntry *e) {
    PppMtx m;
    f32 *w = PPP_WORK(f32, obj, e, 1);

    PlatVu0UnitMatrix(m);
    m[3][0] = w[0];
    m[3][1] = w[1];
    m[3][2] = w[2];
    PlatVu0MulMatrix(m, D_00615EB0, m);
    PlatVu0MulMatrix(m, (f32 (*)[4]) D_00616040, m);
    PlatVu0ScaleVector(D_00615E68->m2[0], D_00615E68->m[0], w[4]);
    PlatVu0ScaleVector(D_00615E68->m2[1], D_00615E68->m[1], w[5]);
    PlatVu0ScaleVector(D_00615E68->m2[2], D_00615E68->m[2], w[6]);
    *(u128 *) D_00615E68->m2[3] = *(u128 *) D_00615E68->m[3];
    PlatVu0MulMatrix(D_00615E68->m2, D_006160C0, D_00615E68->m2);
    PlatVu0ApplyMatrix(D_00615E68->m2[3], (f32 *) m, D_00615E68->m[3]);
}
#undef D_00616040
#undef D_00615E68
#undef D_00615EB0

/* pppRyjMatrixWorldCon (from auto/text_00190000_2.c). */
#include "data/pieces/D_003701E0.h"
void func_00183be0(s32, s32);
void pppRyjMatrixWorldCon(s32 arg0, s32 arg1) {
    s32 temp_s0;

    temp_s0 = arg0 + M2C_FIELD(M2C_FIELD(arg1, void **, 0xC), s32 *, 0xC) + 0xA0;
    func_00183be0(temp_s0, (s32) (M2C_UNK *)&D_003701E0);
    M2C_FIELD(temp_s0, f32 *, 0x30) = (f32) M2C_FIELD(&D_003701D0, f32 *, 0);
    M2C_FIELD(temp_s0, f32 *, 0x34) = (f32) M2C_FIELD(&D_003701D0, f32 *, 4);
    M2C_FIELD(temp_s0, f32 *, 0x38) = (f32) M2C_FIELD(&D_003701D0, f32 *, 8);
}

/* pppRyjMatrixWorldXZYCon (from auto/text_00190000_2.c). */
void func_001a5250(s32, s32);
void pppRyjMatrixWorldXZYCon(s32 arg0, s32 arg1) {
    s32 temp_s0;

    temp_s0 = arg0 + M2C_FIELD(M2C_FIELD(arg1, void **, 0xC), s32 *, 0xC) + 0xA0;
    func_001a5250(temp_s0, (s32) (M2C_UNK *)&D_003701E0);
    M2C_FIELD(temp_s0, f32 *, 0x30) = (f32) M2C_FIELD(&D_003701D0, f32 *, 0);
    M2C_FIELD(temp_s0, f32 *, 0x34) = (f32) M2C_FIELD(&D_003701D0, f32 *, 4);
    M2C_FIELD(temp_s0, f32 *, 0x38) = (f32) M2C_FIELD(&D_003701D0, f32 *, 8);
}

/* pppRyjMatrixWorldYXZCon (from auto/text_00190000_2.c). */
void func_001a5370(s32, s32);
void pppRyjMatrixWorldYXZCon(s32 arg0, s32 arg1) {
    s32 temp_s0;

    temp_s0 = arg0 + M2C_FIELD(M2C_FIELD(arg1, void **, 0xC), s32 *, 0xC) + 0xA0;
    func_001a5370(temp_s0, (s32) (M2C_UNK *)&D_003701E0);
    M2C_FIELD(temp_s0, f32 *, 0x30) = (f32) M2C_FIELD(&D_003701D0, f32 *, 0);
    M2C_FIELD(temp_s0, f32 *, 0x34) = (f32) M2C_FIELD(&D_003701D0, f32 *, 4);
    M2C_FIELD(temp_s0, f32 *, 0x38) = (f32) M2C_FIELD(&D_003701D0, f32 *, 8);
}

/* pppRyjMatrixWorldYZXCon (from auto/text_00190000_2.c). */
void func_001a52e0(s32, s32);
void pppRyjMatrixWorldYZXCon(s32 arg0, s32 arg1) {
    s32 temp_s0;

    temp_s0 = arg0 + M2C_FIELD(M2C_FIELD(arg1, void **, 0xC), s32 *, 0xC) + 0xA0;
    func_001a52e0(temp_s0, (s32) (M2C_UNK *)&D_003701E0);
    M2C_FIELD(temp_s0, f32 *, 0x30) = (f32) M2C_FIELD(&D_003701D0, f32 *, 0);
    M2C_FIELD(temp_s0, f32 *, 0x34) = (f32) M2C_FIELD(&D_003701D0, f32 *, 4);
    M2C_FIELD(temp_s0, f32 *, 0x38) = (f32) M2C_FIELD(&D_003701D0, f32 *, 8);
}

/* pppRyjMatrixWorldZXYCon (from auto/text_00190000_2.c). */
void func_001a5400(s32, s32);
void pppRyjMatrixWorldZXYCon(s32 arg0, s32 arg1) {
    s32 temp_s0;

    temp_s0 = arg0 + M2C_FIELD(M2C_FIELD(arg1, void **, 0xC), s32 *, 0xC) + 0xA0;
    func_001a5400(temp_s0, (s32) (M2C_UNK *)&D_003701E0);
    M2C_FIELD(temp_s0, f32 *, 0x30) = (f32) M2C_FIELD(&D_003701D0, f32 *, 0);
    M2C_FIELD(temp_s0, f32 *, 0x34) = (f32) M2C_FIELD(&D_003701D0, f32 *, 4);
    M2C_FIELD(temp_s0, f32 *, 0x38) = (f32) M2C_FIELD(&D_003701D0, f32 *, 8);
}

/* pppRyjMatrixWorldZYXCon (from auto/text_00190000_2.c). */
void func_001a5490(s32, s32);
void pppRyjMatrixWorldZYXCon(s32 arg0, s32 arg1) {
    s32 temp_s0;

    temp_s0 = arg0 + M2C_FIELD(M2C_FIELD(arg1, void **, 0xC), s32 *, 0xC) + 0xA0;
    func_001a5490(temp_s0, (s32) (M2C_UNK *)&D_003701E0);
    M2C_FIELD(temp_s0, f32 *, 0x30) = (f32) M2C_FIELD(&D_003701D0, f32 *, 0);
    M2C_FIELD(temp_s0, f32 *, 0x34) = (f32) M2C_FIELD(&D_003701D0, f32 *, 4);
    M2C_FIELD(temp_s0, f32 *, 0x38) = (f32) M2C_FIELD(&D_003701D0, f32 *, 8);
}

#include "data/pieces/D_0035C710.h"
#include "data/pieces/D_002E2780.h"
#include "data/pieces/D_003727B0.h"

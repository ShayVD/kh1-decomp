/* The ppp matrix classes, default flags (docs/modules.md "Session 50"):
 * pppMatrixLoc, pppParMatrix, the pppChrScl* matrices (the owner character's
 * matrix scaled on some axes), pppDrawMatrix / DrawMatrixFront /
 * DrawMatrixNoRot (the draw matrix from the owner's, facing the camera, or
 * position only), pppDrawMatrixWood's slot 14 and pppSMatrix.  The rotation
 * order frames are in pppmatrix.nostrict.c.  Read from the code, not proved
 * by a boot. */
#include "m2c.h"
#include "ppp.h"
#include "data/pieces/D_00364130.h"
#include "data/pieces/D_002BBFA0.h"
#include "common.h"
#include "data/types/text_00180000_h12.h"
#include "data/pieces/D_003701F0.h"

/* pppMatrixLocFrame (from auto/text_00180000_3.c). */
extern void *D_00615E68;
void func_00267620(s32);
void pppMatrixLocFrame(s32 arg0, s32 arg1, s32 arg2) {
    void *temp_s0;

    temp_s0 = arg0 + *M2C_FIELD(arg2, s32 **, 0xC) + 0xA0;
    func_00267620((s32) (D_00615E68 + 0x10));
    M2C_FIELD(D_00615E68, f32 *, 0x40) = (f32) M2C_FIELD(temp_s0, f32 *, 0);
    M2C_FIELD(D_00615E68, f32 *, 0x44) = (f32) M2C_FIELD(temp_s0, f32 *, 4);
    M2C_FIELD(D_00615E68, f32 *, 0x48) = (f32) M2C_FIELD(temp_s0, f32 *, 8);
}

/* pppParMatrixFrame (from auto/text_00180000_5.c). */
M2C_UNK func_002672f8(s32, s32, s32);
#define D_00615E68 ((s32 ) D_00615E68)
void pppParMatrixFrame(void *arg0) {
    s32 temp_a0;

    temp_a0 = D_00615E68 + 0x40;
    func_002672f8(temp_a0, M2C_FIELD(arg0, s32 *, 4) + 0x10, temp_a0);
}
#undef D_00615E68

/* pppChrSclXYZMatrixFrame (from auto/text_00180000_11.c). */
extern void *D_00615E60;
void func_00267328(s32, void *, s32);
#define D_00615E68 ((s32 ) D_00615E68)
void pppChrSclXYZMatrixFrame(s32 arg0, void *arg1) {
    s32 sp[16];    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f1;
    f32 temp_f1_2;
    f32 temp_f2;
    f32 temp_f3;
    s32 temp_a0;

    func_00267620(sp);
    temp_f3 = M2C_FIELD(arg1, f32 *, 4);
    temp_f0 = M2C_FIELD(D_00615E60, f32 *, 0x40);
    temp_f2 = M2C_FIELD(arg1, f32 *, 8);
    temp_f0_2 = temp_f0 + (temp_f0 * temp_f3);
    M2C_FIELD(sp, f32 *, 0x0) = temp_f0_2;
    if (temp_f2 < temp_f0_2) {
        M2C_FIELD(sp, f32 *, 0x0) = temp_f2;
    }
    M2C_FIELD(sp, f32 *, 0x28) = M2C_FIELD(sp, f32 *, 0x0);
    temp_f1 = M2C_FIELD(D_00615E60, f32 *, 0x44);
    temp_f1_2 = temp_f1 + (temp_f1 * temp_f3);
    M2C_FIELD(sp, f32 *, 0x14) = temp_f1_2;
    if (temp_f2 < temp_f1_2) {
        M2C_FIELD(sp, f32 *, 0x14) = temp_f2;
    }
    temp_a0 = D_00615E68 + 0x10;
    func_00267328(temp_a0, sp, temp_a0);
}
#undef D_00615E68

/* pppChrSclXZMatrixFrame (from auto/text_00180000_11.c). */
#define D_00615E68 ((s32 ) D_00615E68)
void pppChrSclXZMatrixFrame(s32 arg0, void *arg1) {
    s32 sp[16];    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f2;
    s32 temp_a0;

    func_00267620(sp);
    temp_f0 = M2C_FIELD(D_00615E60, f32 *, 0x40);
    temp_f2 = M2C_FIELD(arg1, f32 *, 8);
    temp_f0_2 = temp_f0 + (temp_f0 * M2C_FIELD(arg1, f32 *, 4));
    M2C_FIELD(sp, f32 *, 0x0) = temp_f0_2;
    if (temp_f2 < temp_f0_2) {
        M2C_FIELD(sp, f32 *, 0x0) = temp_f2;
    }
    M2C_FIELD(sp, f32 *, 0x28) = M2C_FIELD(sp, f32 *, 0x0);
    temp_a0 = D_00615E68 + 0x10;
    func_00267328(temp_a0, sp, temp_a0);
}
#undef D_00615E68

/* pppChrSclYMatrixFrame (from auto/text_00180000_11.c). */
#define D_00615E68 ((s32 ) D_00615E68)
void pppChrSclYMatrixFrame(s32 arg0, void *arg1) {
    s32 sp[16];    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f2;
    s32 temp_a0;

    func_00267620(sp);
    temp_f0 = M2C_FIELD(D_00615E60, f32 *, 0x44);
    temp_f2 = M2C_FIELD(arg1, f32 *, 8);
    temp_f0_2 = temp_f0 + (temp_f0 * M2C_FIELD(arg1, f32 *, 4));
    M2C_FIELD(sp, f32 *, 0x14) = temp_f0_2;
    if (temp_f2 < temp_f0_2) {
        M2C_FIELD(sp, f32 *, 0x14) = temp_f2;
    }
    temp_a0 = D_00615E68 + 0x10;
    func_00267328(temp_a0, sp, temp_a0);
}
#undef D_00615E68

/* pppChrYSclXYZMatrixFrame (from hand/text_00180000_h12.c). */
typedef struct PppSys PppSys;
typedef struct {
    void *fn[8];
} PppModule;
typedef struct {
    u8 pad[0x9C];
    u8 unk9C;
} PppInst;
typedef struct {
    s32 unk0;
    PppInst *inst;  /* +0x4 */
    s32 time;       /* +0x8 */
    s32 unkC;
} PppSlotE;
struct PppSys {
    u8 pad00[0x44];
    f32 scale;         /* +0x44 */
    u8 pad48[0xC];
    s32 end;           /* +0x54 */
    s32 time;          /* +0x58 */
    s32 prev;          /* +0x5C */
    u8 pad60[4];
    s32 nmod;          /* +0x64 */
    s32 nslot;         /* +0x68 */
    u8 pad6C[8];
    s32 unk74;         /* +0x74 */
    PppModule **mods;  /* +0x78 */
    s32 pad7C;
    PppSlotE *slots;   /* +0x80 */
    u8 unk84;          /* +0x84 */
    u8 unk85;          /* +0x85 */
    u8 pad86[0x2A];
    u64 unkB0;         /* +0xB0 */
};
typedef f32 PppMtx[4][4] __attribute__((aligned(16)));
void sceVu0UnitMatrix(PppMtx);
void sceVu0MulMatrix(PppMtx, PppMtx, PppMtx);
typedef struct {
    u8 pad[0x10];
    PppMtx m;    /* +0x10 */
    PppMtx m2;   /* +0x50 */
} PppMtxOwner;
typedef struct {
    s32 frame;
    f32 scale;  /* +0x4 */
    f32 max;    /* +0x8 */
} PppYSclKey;
#define D_00615E60 ((PppSys *) D_00615E60)
#define D_00615E68 ((PppMtxOwner *) D_00615E68)
void pppChrYSclXYZMatrixFrame(void *obj, PppYSclKey *k, PppEntry *e) {
    PppMtx m;
    f32 s;

    sceVu0UnitMatrix(m);
    s = D_00615E60->scale;
    m[1][1] = s + s * k->scale;
    if (k->max < m[1][1])
        m[1][1] = k->max;
    m[0][0] = m[1][1] = m[2][2];
    sceVu0MulMatrix(D_00615E68->m, m, D_00615E68->m);
}
#undef D_00615E60
#undef D_00615E68

/* pppChrXSclXYZMatrixFrame (from auto/text_00180000_12.c). */
#define D_00615E68 ((s32 ) D_00615E68)
void pppChrXSclXYZMatrixFrame(s32 arg0, void *arg1) {
  s32 sp[16];
  f32 new_var;
  f32 temp_f0;
  f32 temp_f0_2;
  f32 *new_var2;
  f32 temp_f2;
  s32 temp_a0;
  func_00267620(sp);
  temp_f0 = *((f32 *) (((s8 *) D_00615E60) + 0x40));
  new_var2 = (f32 *) (((s8 *) sp) + 0x14);
  temp_f2 = *((f32 *) (((s8 *) arg1) + 8));
  ;
  *((f32 *) (((s8 *) sp) + 0x0)) = temp_f0 * (*((f32 *) (((s8 *) arg1) + 4)));
  *((f32 *) (((s8 *) sp) + 0x0)) = temp_f0 + (*((f32 *) (((s8 *) sp) + 0x0)));
  if (temp_f2 < (temp_f0 + (temp_f0 * (*((f32 *) (((s8 *) arg1) + 4))))))
  {
    *((f32 *) (((s8 *) sp) + 0x0)) = temp_f2;
  }
  new_var = *((f32 *) (((s8 *) sp) + 0x0));
  *new_var2 = new_var;
  temp_a0 = D_00615E68 + 0x10;
  *((f32 *) (((s8 *) sp) + 0x28)) = new_var;
  func_00267328(temp_a0, sp, temp_a0);
}
#undef D_00615E68

/* pppDrawMatrixFrame (from auto/text_00180000_7.c). */
extern M2C_UNK D_00616080;
#define D_00615E68 ((s32 ) D_00615E68)
void pppDrawMatrixFrame(void) {
    func_00267328(D_00615E68 + 0x50, &D_00616080, D_00615E68 + 0x10);
}
#undef D_00615E68

/* pppDrawMatrixFrontFrame (from auto/text_00180000_7.c). */
M2C_UNK func_00267560(s32, s32, f32);
extern f32 D_00615FC0[];
extern M2C_UNK D_00616040;
#define D_00615FC0 (*(M2C_UNK (*)) &D_00615FC0)
#define D_00615E68 ((s32 ) D_00615E68)
void pppDrawMatrixFrontFrame(void) {
    s32 temp_a0;

    func_00267560(D_00615E68 + 0x50, D_00615E68 + 0x10, M2C_FIELD((M2C_UNK *)&D_003701F0, f32 *, 0));
    func_00267560(D_00615E68 + 0x60, D_00615E68 + 0x20, M2C_FIELD((M2C_UNK *)&D_003701F0, f32 *, 4));
    func_00267560(D_00615E68 + 0x70, D_00615E68 + 0x30, M2C_FIELD((M2C_UNK *)&D_003701F0, f32 *, 8));
    func_002672f8(D_00615E68 + 0x80, &D_00615FC0, D_00615E68 + 0x40);
    temp_a0 = D_00615E68 + 0x50;
    func_00267328(temp_a0, &D_00616040, temp_a0);
}
#undef D_00615FC0
#undef D_00615E68

/* pppDrawMatrixNoRotFrame (from auto/text_00180000_8.c). */
M2C_UNK func_00267548(void *, void *, M2C_UNK *);
void pppDrawMatrixNoRotFrame(void) {
    void *temp_a0;

    func_00267560(D_00615E68 + 0x50, D_00615E68 + 0x10, M2C_FIELD((M2C_UNK *)&D_003701F0, f32 *, 0));
    func_00267560(D_00615E68 + 0x60, D_00615E68 + 0x20, M2C_FIELD((M2C_UNK *)&D_003701F0, f32 *, 4));
    func_00267560(D_00615E68 + 0x70, D_00615E68 + 0x30, M2C_FIELD((M2C_UNK *)&D_003701F0, f32 *, 8));
    func_00267548(D_00615E68 + 0x80, D_00615E68 + 0x40, (M2C_UNK *)&D_003701F0);
    M2C_FIELD(D_00615E68, f32 *, 0x80) = (f32) (M2C_FIELD(D_00615E68, f32 *, 0x80) + D_00615FC0[12]);
    M2C_FIELD(D_00615E68, f32 *, 0x84) = (f32) (M2C_FIELD(D_00615E68, f32 *, 0x84) + D_00615FC0[13]);
    M2C_FIELD(D_00615E68, f32 *, 0x88) = (f32) (M2C_FIELD(D_00615E68, f32 *, 0x88) + D_00615FC0[14]);
    M2C_FIELD(D_00615E68, f32 *, 0x8C) = 1.0f;
    temp_a0 = D_00615E68 + 0x50;
    func_00267328(temp_a0, &D_00616040, temp_a0);
}

/* pppDrawMatrixWoodFn14 (from auto/text_00180000_5.c). */
void pppDrawMatrixWoodFn14(void) {

}

/* pppSMatrixFrame (from auto/text_00180000_5.c). */
extern s32 D_00616214;
void pppSMatrixFrame(s32 arg0, s32 arg1, void *arg2) {
    D_00616214 = arg0 + *M2C_FIELD(arg2, s32 **, 0xC) + 0xA0;
}


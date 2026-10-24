/* The ppp matrix-step classes, default flags (docs/modules.md "Session
 * 50"): pppKeMatSN keeps a rotation matrix from the change of the work
 * area's integer angles (func_00183be0) and publishes it in D_00616214;
 * pppKeParMatR, pppKeDMat / DMatFr and pppKeDMatPht / DMatPhtFr set the
 * owner's draw matrix from the parent (D_00615FC0), camera (D_00616040) or
 * photo (D_0061E780 / D_0061E7C0) matrices, keeping a copy in the work area;
 * pppKeTkFade's Con.  kemat.nostrict.c has pppKeTkFadeDraw and
 * pppKeMatPhtFrame.  Each section names the file its code came from.  Read
 * from the code, not proved by a boot. */

/* pppKeMatSNFrame (from hand/text_00180000_h40.c). */
#include "common.h"
#include "ppp.h"
#include "data/types/shared.h"
#include "data/types/text_00180000_h40.h"
#define PPP_WORK(T, obj, e, k) ((T *) ((u8 *) (obj) + (e)->offsets[k] + 0xA0))
typedef struct {
    s32 unk00, unk04, unk08;
    s32 frame; /* +0x0C */
    u8 pad10[0x8D];
    u8 unk9D;  /* +0x9D */
} PppObject;
typedef struct { s32 x, y, z; } PppIVec;
void func_00183be0(PppMtx, void *);
typedef struct {
    u8 pad00[0x40];
    f32 m[3][4];   /* +0x40 */
    u128 row3;     /* +0x70 */
    PppIVec prev;  /* +0x80 */
} PppMatSN;
extern PppMatSN *D_00616214;
extern u128 D_003727B0;
void pppKeMatSNFrame(PppObject *obj, void *key, PppEntry *e) {
    PppMatSN *w = PPP_WORK(PppMatSN, obj, e, 0);
    PppIVec *r = PPP_WORK(PppIVec, obj, e, 1);
    PppIVec d;

    D_00616214 = w;
    d = w->prev;
    w->prev.x = r->x;
    w->prev.y = r->y;
    w->prev.z = r->z;
    d.x -= w->prev.x;
    d.y -= w->prev.y;
    d.z -= w->prev.z;
    func_00183be0((void *) w->m, &d);
    w->row3 = D_003727B0;
}
#undef PPP_WORK

/* pppKeMatSNCon (from auto/text_00190000_2.c). */
#include "m2c.h"
void pppKeMatSNCon(s32 arg0, PppEntry *arg1) {
    void *temp_a0;

    temp_a0 = arg0 + arg1->offsets[0] + 0xA0;
    M2C_FIELD(temp_a0, s32 *, 0x80) = 0;
    M2C_FIELD(temp_a0, s32 *, 0x84) = 0;
    M2C_FIELD(temp_a0, s32 *, 0x88) = 0;
}

/* pppKeParMatRFrame (from auto/text_00190000_6.c). */
M2C_UNK func_002672f8(M2C_UNK *, s32, s32);
M2C_UNK func_00267328(s32, M2C_UNK *, s32);
M2C_UNK func_002673b8(M2C_UNK *, s32);
M2C_UNK func_002675a8(s32, M2C_UNK *);
extern s32 D_00615E68;
void pppKeParMatRFrame(void *arg0) {
    s32 sp[20];    s32 temp_a0;
    s32 temp_s0;
    s32 temp_s1;

    temp_s0 = M2C_FIELD(arg0, s32 *, 4);
    temp_s1 = temp_s0 + 0x10;
    func_002673b8(sp, temp_s1);
    func_002673b8(&M2C_FIELD(sp, M2C_UNK *, 0x10), temp_s0 + 0x20);
    func_002673b8(&M2C_FIELD(sp, M2C_UNK *, 0x20), temp_s0 + 0x30);
    func_002672f8(&M2C_FIELD(sp, M2C_UNK *, 0x40), temp_s1, D_00615E68 + 0x40);
    temp_a0 = D_00615E68 + 0x10;
    func_00267328(temp_a0, sp, temp_a0);
    func_002675a8(D_00615E68 + 0x40, &M2C_FIELD(sp, M2C_UNK *, 0x40));
}

/* pppKeTkFadeCon (from auto/text_00190000_2.c). */
void pppKeTkFadeCon(s32 arg0, PppEntry *arg1) {
    void *temp_a0;
    void *temp_a0_2;

    temp_a0 = arg0 + arg1->offsets[0];
    temp_a0_2 = temp_a0 + 0xA0;
    M2C_FIELD(temp_a0, s32 *, 0xA0) = 0;
    M2C_FIELD(temp_a0_2, s32 *, 4) = 0;
    M2C_FIELD(temp_a0_2, s32 *, 8) = 0;
}

/* pppKeDMatFrame (from hand/text_00180000_h12.c). */
#include "data/pieces/D_00364130.h"
#include "data/types/text_00180000_h12.h"
extern u8 D_00616040[];
typedef f32 PppMtx[4][4] __attribute__((aligned(16)));
void sceVu0MulMatrix(PppMtx, PppMtx, PppMtx);
void sceVu0CopyMatrix(PppMtx, PppMtx);
typedef struct {
    u8 pad[0x10];
    PppMtx m;    /* +0x10 */
    PppMtx m2;   /* +0x50 */
} PppMtxOwner;
extern PppMtx D_00615FC0;
#define D_00615E68 ((PppMtxOwner *) D_00615E68)
void pppKeDMatFrame(void *obj, void *k, PppEntry *e) {
    f32 (*w)[4] = (f32 (*)[4]) ((u8 *) obj + e->offsets[1] + 0xA0);

    sceVu0MulMatrix(D_00615E68->m2, D_00615FC0, D_00615E68->m);
    sceVu0CopyMatrix(w, D_00615E68->m2);
    sceVu0MulMatrix(D_00615E68->m2, (f32 (*)[4]) D_00616040, D_00615E68->m2);
}
#undef D_00615E68

/* pppKeDMatFrFrame (from auto/text_00190000_11.c). */
#include "data/pieces/D_003701F0.h"
M2C_UNK func_00267560(s32, s32, f32);
M2C_UNK func_002675b8(s32, s32);
#define D_00615FC0 (*(M2C_UNK (*)) &D_00615FC0)
#define D_00616040 (*(M2C_UNK (*)) &D_00616040)
void pppKeDMatFrFrame(s32 arg0, s32 arg1, void *arg2) {
  s32 temp_a0;
  int new_var;
  s32 temp_s2;
  temp_s2 = arg0 + (*((s32 *) (((s8 *) (*((void **) (((s8 *) arg2) + 0xC)))) + 4)));
  func_00267560(D_00615E68 + 0x50, D_00615E68 + 0x10, *((f32 *) (((s8 *) &D_003701F0) + 0)));
  func_00267560(D_00615E68 + 0x60, D_00615E68 + 0x20, *((f32 *) (((s8 *) &D_003701F0) + 4)));
  func_00267560(D_00615E68 + 0x70, D_00615E68 + 0x30, *((f32 *) (((s8 *) &D_003701F0) + 8)));
  new_var = temp_s2 + 0xA0;
  func_002672f8(D_00615E68 + 0x80, &D_00615FC0, D_00615E68 + 0x40);
  func_002675b8(new_var, D_00615E68 + 0x50);
  temp_a0 = D_00615E68 + 0x50;
  func_00267328(temp_a0, &D_00616040, temp_a0);
}
#undef D_00615FC0
#undef D_00616040

/* pppKeDMatPhtFrame (from auto/text_00190000_7.c). */
extern M2C_UNK D_0061E780;
extern M2C_UNK D_0061E7C0;
#define D_00615FC0 (*(M2C_UNK (*)) &D_00615FC0)
#define D_00616040 (*(M2C_UNK (*)) &D_00616040)
void pppKeDMatPhtFrame(void) {
    M2C_UNK *temp_a0;

    func_00267328(&D_0061E780, &D_00615FC0, &D_0061E7C0);
    func_00267560(D_00615E68 + 0x50, D_00615E68 + 0x10, M2C_FIELD((M2C_UNK *)&D_003701F0, f32 *, 0));
    func_00267560(D_00615E68 + 0x60, D_00615E68 + 0x20, M2C_FIELD((M2C_UNK *)&D_003701F0, f32 *, 4));
    func_00267560(D_00615E68 + 0x70, D_00615E68 + 0x30, M2C_FIELD((M2C_UNK *)&D_003701F0, f32 *, 8));
    func_002672f8(D_00615E68 + 0x80, &D_00615FC0, D_00615E68 + 0x40);
    temp_a0 = D_00615E68 + 0x50;
    func_00267328(temp_a0, &D_00616040, temp_a0);
}
#undef D_00615FC0
#undef D_00616040

/* pppKeDMatPhtFrFrame (from hand/text_00180000_h40.c). */
#define D_00615FC0 ((PppQv *) &D_00615FC0)
#define D_00616040 ((PppQv *) D_00616040)
#define D_00615E68 ((PppMtxOwner *) D_00615E68)
#define D_0061E7C0 (*(PppMtx (*)) &D_0061E7C0)
#define D_0061E780 (*(PppMtx (*)) &D_0061E780)
void pppKeDMatPhtFrFrame(PppObject *obj, void *key, PppEntry *e) {
    func_00267560(D_0061E780[0], D_0061E7C0[0], D_003701F0[0]);
    func_00267560(D_0061E780[1], D_0061E7C0[1], D_003701F0[1]);
    func_00267560(D_0061E780[2], D_0061E7C0[2], D_003701F0[2]);
    func_002672f8(D_0061E780[3], (f32 *) D_00615FC0, D_0061E7C0[3]);
    func_00267560(D_00615E68->m2[0], D_00615E68->m[0], D_003701F0[0]);
    func_00267560(D_00615E68->m2[1], D_00615E68->m[1], D_003701F0[1]);
    func_00267560(D_00615E68->m2[2], D_00615E68->m[2], D_003701F0[2]);
    func_002672f8(D_00615E68->m2[3], (f32 *) D_00615FC0, D_00615E68->m[3]);
    sceVu0MulMatrix(D_00615E68->m2, (f32 (*)[4]) D_00616040, D_00615E68->m2);
}
#undef D_00615FC0
#undef D_00616040
#undef D_00615E68
#undef D_0061E7C0
#undef D_0061E780

#include "data/pieces/D_003701F0.h"
#include "data/pieces/D_0035C710.h"
#include "data/pieces/D_002E2780.h"
#include "data/pieces/D_003727B0.h"
#include "data/types/text_00180000_h12_p.h"
#include "data/data_0037.h"

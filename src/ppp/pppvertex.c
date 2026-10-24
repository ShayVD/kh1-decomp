/* The ppp vertex classes' default-flag functions (docs/modules.md "Session
 * 50"): pppVertexAttend, the Cons of pppVertexAp / ApLc / ApAt, the empty
 * pppSegmentAp / FaceAp frames, func_00185000 and the pppVtMime frame, Con,
 * Reset and Des.  pppvertex.nostrict.c has the rest.  Read from the code,
 * not proved by a boot. */
#include "ppp.h"
#include "data/pieces/D_00364130.h"
#include "data/types/text_00180000_h39.h"
#include "m2c.h"
#include "data/pieces/D_00370130.h"
#include "common.h"
#include "data/types/text_00180000_h12.h"

/* pppVertexAttendFrame (from hand/text_00180000_h39.c). */
typedef union { f32 f[4]; } H39V4 __attribute__((aligned(16)));
typedef struct {
    s32 a, b, c;
    s32 pad0C, pad10;
    s16 *vtx;      /* +0x14 */
    void *p18;
    void *tex;
    s32 unk20;
} H39VSlot;
typedef struct {
    s16 slot;
    u16 *map;      /* +0x4 */
} H39VMap;
typedef struct {
    u8 pad00[0x10];
    H39VSlot *slots;  /* +0x10 */
    void *p14;
    H39VMap *maps;   /* +0x18 */
} H39VSys;
typedef struct {
    s32 unk00;
    u8 *mtx;        /* +0x4: matrix at +0x10 */
} H39VObj;
typedef struct {
    u8 pad[0xC];
    s16 map;        /* +0xC */
} H39VKey;
extern H39VSys *D_00615E64;
void func_002672f8(H39V4 *, void *, H39V4 *);
void pppVertexAttendFrame(H39VObj *obj, H39VKey *key, PppEntry *e) {
    H39V4 v;
    H39VMap *m;
    s16 *p;
    f32 *out;

    if (key->map < 0)
        return;
    m = &D_00615E64->maps[key->map];
    p = D_00615E64->slots[m->slot].vtx + m->map[*(u16 *) ((u8 *) obj + e->offsets[0] + 0xA0)] * 3;
    out = (f32 *) ((u8 *) obj + e->offsets[1] + 0xA0);
    v.f[0] = p[0];
    v.f[1] = p[1];
    v.f[2] = p[2];
    v.f[3] = 1.0f;
    func_002672f8(&v, obj->mtx + 0x10, &v);
    out[0] = v.f[0];
    out[1] = v.f[1];
    out[2] = v.f[2];
}

/* pppVertexApCon (from hand/ppp.c). */
#define PPP_WORK(T, obj, e, k) ((T *) ((u8 *) (obj) + (e)->offsets[k] + 0xA0))
typedef struct {
    s16 a, b;
} PppS16x2;
void pppVertexApCon(void *obj, PppEntry *e) {
    PppS16x2 *w = PPP_WORK(PppS16x2, obj, e, 0);

    w->a = 0;
    w->b = 0;
}

/* pppSegmentApFrame (from auto/text_00180000.c). */
void pppSegmentApFrame(void) {

}

/* pppFaceApFrame (from auto/text_00180000.c). */
void pppFaceApFrame(void) {

}

/* pppVertexApLcCon (from auto/text_00180000_14.c). */
void pppVertexApLcCon(s32 arg0, void *arg1) {
  void *temp_a0;
  void *new_var;
 do { temp_a0 = arg0 + (*(*((s32 **) (((s8 *) arg1) + 0xC)))); new_var = temp_a0 + 0xA0; *((s16 *) (((s8 *) new_var) + 2)) = 0; } while (0);
  *((s16 *) (((s8 *) temp_a0) + 0xA0)) = 0;
}

/* pppVertexApAtCon (from auto/text_00180000_15.c). */
void pppVertexApAtCon(s32 arg0, void *arg1) {
  void *new_var;
  void *temp_a0;
  temp_a0 = arg0 + (*(*((s32 **) (((s8 *) arg1) + 0xC))));
 do { *((s16 *) (((s8 *) (new_var = temp_a0 + 0xA0)) + 2)) = 0; } while (0);
  *((s16 *) (((s8 *) temp_a0) + 0xA0)) = 0;
}

/* func_00185000 (from auto/text_00180000_12.c). */
extern void *D_00615E60;
void *func_00182588(void *, s32, M2C_UNK);
void func_00185000(s32 arg0, void *arg1, unsigned short arg2) {
  s32 temp_v0;
  s32 temp_v0_2;
  void *var_a2;
  temp_v0 = *((s32 *) (((s8 *) arg1) + 0xC));
  if (temp_v0 != (-1))
  {
    var_a2 = 0;
    temp_v0_2 = (*((s32 *) (((s8 *) D_00615E60) + 0x80))) + (temp_v0 * 0x10);
    if (temp_v0_2 != 0)
    {
      var_a2 = func_00182588(D_00615E60, temp_v0_2, 0);
      *((s32 *) (((s8 *) var_a2) + 4)) = arg0;
    }
    *((s16 *) (((s8 *) (var_a2 + (*((s32 *) (((s8 *) arg1) + 0x10))))) + 0xA0)) = (s16) (arg2 & 0xFFFF);
  }
}

/* pppVtMimeFrame (from hand/text_00180000_h12.c). */
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
extern s32 D_0061621C;
typedef struct {
    s32 unk00, unk04, unk08;
    s32 frame; /* +0x0C */
} PppObject;
typedef union {
    f32 f;
    s32 i;
} PppWord;
typedef struct {
    s32 frame;
    s32 pad[2];
    f32 x, y, z;  /* +0xC */
} PppVtMimeKey;
typedef struct {
    PppWord x, y, z;
    s32 n;
} PppVtMime;
#define D_00615E60 ((PppSys *) D_00615E60)
void pppVtMimeFrame(PppObject *obj, PppVtMimeKey *k, PppEntry *e) {
    PppVtMime *w = (PppVtMime *) ((u8 *) obj + e->offsets[0] + 0xA0);

    if (D_0061621C != 0 || (D_00615E60->unkB0 & 0xFF0000FF00ULL))
        return;
    w->y.f += w->z.f;
    w->x.f += w->y.f;
    if (k->frame == obj->frame) {
        w->x.f += k->x;
        w->y.f += k->y;
        w->z.f += k->z;
    }
}
#undef D_00615E60

/* pppVtMimeCon (from hand/ppp.c). */
typedef struct {
    f32 x, y, z;
    s32 n;
} PppVtMime_854a0;
void pppVtMimeCon(void *obj, PppEntry *e) {
    PppVtMime_854a0 *w = PPP_WORK(PppVtMime_854a0, obj, e, 0);

    w->x = w->y = w->z = 0.0f;
    w->n = 0;
}

/* pppVtMimeReset (from auto/text_00180000_20.c). */
void pppVtMimeReset(s32 arg0, void *arg1) {
    void *temp_a0;
    void *temp_a0_2;

    temp_a0 = arg0 + *M2C_FIELD(arg1, s32 **, 0xC);
    temp_a0_2 = temp_a0 + 0xA0;
    M2C_FIELD(temp_a0, f32 *, 0xA0) = M2C_FIELD(temp_a0_2, f32 *, 4) = M2C_FIELD(temp_a0_2, f32 *, 8) = 0.0f;
}

/* pppVtMimeDes (from auto/text_00180000.c). */
M2C_UNK func_00183b20(s32, s32);
#define D_00615E64 ((s32 ) D_00615E64)
void pppVtMimeDes(s32 arg0, PppEntry *arg1) {
    s32 temp_v0;
    void *temp_s0;

    temp_s0 = arg0 + arg1->offsets[0] + 0xA0;
    temp_v0 = M2C_FIELD(temp_s0, s32 *, 0xC);
    if (temp_v0 != 0) {
        func_00183b20(D_00615E64, temp_v0);
        M2C_FIELD(temp_s0, s32 *, 0xC) = 0;
    }
}
#undef D_00615E64


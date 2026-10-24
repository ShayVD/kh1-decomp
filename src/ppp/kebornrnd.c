/* The ppp random spawner classes' default-flag functions (docs/modules.md
 * "Session 50"): the Cons of pppKeBornRnd ... KeBornRnd6 and
 * pppKeBornPtCmpl, and the frames of KeBornRnd2 / 3 / 5 / 6 (each gates on
 * a random number and its key's mask, then calls its spawner in
 * kebornrnd.nostrict.c).  Read from the code, not proved by a boot. */
#include "m2c.h"
#include "ppp.h"
#include "data/pieces/D_00370130.h"
#include "common.h"
#include "data/types/shared.h"
#include "data/types/text_00180000_h40.h"

/* pppKeBornRndCon (from auto/text_00180000.c). */
void pppKeBornRndCon(s32 arg0, PppEntry *arg1) {
    M2C_FIELD((arg0 + arg1->offsets[0]), s16 *, 0xA0) = 0;
}

/* pppKeBornRnd2Frame (from hand/text_00180000_h40.c). */
#define PPP_WORK(T, obj, e, k) ((T *) ((u8 *) (obj) + (e)->offsets[k] + 0xA0))
typedef struct {
    s32 unk0;
    u8 *inst;   /* +0x4 */
    s32 time;   /* +0x8 */
    s32 unkC;
} PppSlot;
typedef struct {
    u8 pad[0x80];
    PppSlot *slots; /* +0x80 */
    u8 pad84[0x2C];
    u64 flags;      /* +0xB0 */
} PppSystem;
extern s32 D_0061621C;
extern PppSystem *D_00615E60;
typedef struct {
    s32 unk00, unk04, unk08;
    s32 frame; /* +0x0C */
    u8 pad10[0x8D];
    u8 unk9D;  /* +0x9D */
} PppObject;
extern s32 D_00616234;
typedef struct {
    s32 frame;
    s16 n;        /* +0x4 */
    s16 pad6;
    f32 speed;    /* +0x8 */
    u8 c;         /* +0xC */
    u8 mask;      /* +0xD */
    u8 b;         /* +0xE */
    u8 padF;
    s32 slot;     /* +0x10 */
    s32 off0;     /* +0x14 */
    s32 off1;     /* +0x18 */
    s32 off2;     /* +0x1C */
} PppBornKey;
s32 func_001a8f30(void);
void func_001a5520(PppObject *, PppBornKey *, void *, void *, s16, u8, u8);
void func_0018d390(void *owner, PppBornKey *key, s16 *pos);
void pppKeBornRnd2Frame(PppObject *obj, PppBornKey *key, PppEntry *e) {
    PppObject **pp = &obj;
    if (D_00616234 == 0 && D_0061621C == 0 && !(D_00615E60->flags & 0xFF0000FF00ULL) &&
        key->mask != 0xFF && !((func_001a8f30() >> 8) & key->mask) && key->slot != -1 &&
        key->off1 != -1) {
        func_001a5520(obj, key, func_0018d390, PPP_WORK(void, obj, e, 0), key->n, key->b, key->c);
    }
}
#undef PPP_WORK

/* pppKeBornRnd2Con (from auto/text_00180000.c). */
void pppKeBornRnd2Con(s32 arg0, PppEntry *arg1) {
    M2C_FIELD((arg0 + arg1->offsets[0]), s16 *, 0xA0) = 0;
}

/* pppKeBornRnd3Frame (from hand/text_00180000_h40.c). */
#define PPP_WORK(T, obj, e, k) ((T *) ((u8 *) (obj) + (e)->offsets[k] + 0xA0))
typedef struct {
    s32 frame;
    s16 n;        /* +0x4 */
    u8 c;         /* +0x6 */
    u8 mask;      /* +0x7 */
    u8 b;         /* +0x8 */
    u8 pad9[3];
    s32 slot;     /* +0xC */
    s32 off0;     /* +0x10 */
    s32 off1;     /* +0x14 */
    s32 off2;     /* +0x18 */
} PppBorn3Key;
void func_0018d5c0(void *owner, PppBorn3Key *key, s16 *pos);
void pppKeBornRnd3Frame(PppObject *obj, PppBorn3Key *key, PppEntry *e) {
    PppObject **pp = &obj;
    if (D_00616234 == 0 && D_0061621C == 0 && !(D_00615E60->flags & 0xFF0000FF00ULL) &&
        key->mask != 0xFF && !((func_001a8f30() >> 8) & key->mask) && key->slot != -1 &&
        key->off1 != -1) {
        func_001a5520(obj, (PppBornKey *) key, func_0018d5c0, PPP_WORK(void, obj, e, 0), key->n, key->b, key->c);
    }
}
#undef PPP_WORK

/* pppKeBornRnd3Con (from auto/text_00180000.c). */
void pppKeBornRnd3Con(s32 arg0, PppEntry *arg1) {
    M2C_FIELD((arg0 + arg1->offsets[0]), s16 *, 0xA0) = 0;
}

/* pppKeBornRnd4Con (from auto/text_00180000.c). */
void pppKeBornRnd4Con(s32 arg0, PppEntry *arg1) {
    M2C_FIELD((arg0 + arg1->offsets[0]), s16 *, 0xA0) = 0;
}

/* pppKeBornRnd5Frame (from hand/text_00180000_h40.c). */
#define PPP_WORK(T, obj, e, k) ((T *) ((u8 *) (obj) + (e)->offsets[k] + 0xA0))
void func_0018dd08(void *owner, PppBornKey *key, s16 *pos);
typedef struct {
    s16 a;
    u8 count; /* +0x2 */
} PppBornCnt;
void pppKeBornRnd5Frame(PppObject *obj, PppBornKey *key, PppEntry *e) {
    PppBornCnt *w;
    u8 n;

    if (D_00616234 != 0 || D_0061621C != 0 || (D_00615E60->flags & 0xFF0000FF00ULL))
        return;
    n = key->mask;
    if (n == 0)
        return;
    w = PPP_WORK(PppBornCnt, obj, e, 0);
    if (w->count == 0) {
        w->count = n;
        if (key->slot == -1 || key->off1 == -1)
            return;
        func_001a5520(obj, key, func_0018dd08, w, key->n, key->b, key->c);
    }
    w->count--;
}

/* pppKeBornRnd5Con (from hand/ppp.c). */
typedef struct {
    s16 a;
    s8 b;
} PppS16S8;
void pppKeBornRnd5Con(void *obj, PppEntry *e) {
    PppS16S8 *w = PPP_WORK(PppS16S8, obj, e, 0);

    w->a = 0;
    w->b = 0;
}

/* pppKeBornRnd6Frame (from hand/text_00180000_h40.c). */
void func_0018e0b0(void *owner, PppBorn3Key *key, s16 *pos);
void pppKeBornRnd6Frame(PppObject *obj, PppBorn3Key *key, PppEntry *e) {
    PppBornCnt *w;
    u8 n;

    if (D_00616234 != 0 || D_0061621C != 0 || (D_00615E60->flags & 0xFF0000FF00ULL))
        return;
    n = key->mask;
    if (n == 0)
        return;
    w = PPP_WORK(PppBornCnt, obj, e, 0);
    if (w->count == 0) {
        w->count = n;
        if (key->slot == -1 || key->off1 == -1)
            return;
        func_001a5520(obj, (PppBornKey *) key, func_0018e0b0, w, key->n, key->b, key->c);
    }
    w->count--;
}

/* pppKeBornRnd6Con (from auto/text_00180000_17.c). */
void pppKeBornRnd6Con(s32 arg0, void *arg1) {
  void *temp_a0;
  void *new_var;
  temp_a0 = arg0 + (*(*((s32 **) (((s8 *) arg1) + 0xC))));
  new_var = temp_a0 + 0xA0;
  *((s16 *) (((s8 *) temp_a0) + 0xA0)) = 0;
  *((s8 *) (((s8 *) new_var) + 2)) = 0;
}

/* pppKeBornPtCmplCon (from auto/text_00180000.c). */
void pppKeBornPtCmplCon(s32 arg0, PppEntry *arg1) {
    M2C_FIELD((arg0 + arg1->offsets[0]), s32 *, 0xA0) = 0;
}


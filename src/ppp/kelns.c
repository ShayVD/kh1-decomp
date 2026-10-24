/* The KeLns helpers (docs/modules.md "Session 49"), 0x001a5688-0x001a67b8
 * less the -fno-strict-aliasing draws in kelns.nostrict.c: func_001a5688
 * starts an animation state from a shape, func_001a56a0 steps one (512 a
 * frame, looping when the key's bit 7 is set), func_001a5fd0 starts the Clm
 * entries with a pseudo-random phase each (x * 2061 + 7), and the Con / TCon
 * helpers point a work area at the empty object D_00575A00.
 * Read from the code, not proved by a boot. */
#include "m2c.h"

extern void *D_00615E60;
void func_00267620(s32);
extern u8 D_00575A00[];

void func_001a5688(void *arg0, void **arg1) {
    M2C_FIELD(arg0, u16 *, 0) = (u16) M2C_FIELD(*arg1, u16 *, 0x12);
    M2C_FIELD(arg0, s8 *, 2) = 0;
}

typedef struct {
    s16 unk0;
    s16 dur;    /* +0x2 */
    s8 flags;   /* +0x4 */
    u8 pad[3];
} PppAnimKey;
typedef struct {
    s16 pad[3];
    s16 n;              /* +0x6 */
    u8 pad8[8];
    PppAnimKey keys[1]; /* +0x10 */
} PppAnimHdr;
typedef struct {
    PppAnimHdr *hdr;
} PppAnim;
typedef struct {
    u16 time;
    u8 idx;
} PppAnimState;
typedef struct {
    PppAnim *anim;
    PppAnimState *st;
} PppAnimPlayer;

void func_001a56a0(PppAnimPlayer *p) {
    PppAnimState *st = p->st;
    PppAnimKey *k = &p->anim->hdr->keys[st->idx];

    st->time += 512;
    if ((s16) st->time >= k->dur) {
        st->time -= k->dur;
        st->idx++;
        if (st->idx >= p->anim->hdr->n) {
            if (k->flags & 0x80) {
                st->idx = 0;
                st->time = 0;
                return;
            }
            st->time = 0;
            st->idx--;
        }
    }
}

void func_001a5ca0(s32 arg0) {
    M2C_FIELD(D_00615E60, s8 *, 0xB0) = 2;
    func_00267620(arg0 + 0x40);
    M2C_FIELD(arg0, f32 *, 0xAC) = 1.0f;
}

typedef struct { s32 a; f32 r; } Ent8;
typedef struct { u8 pad[4]; s32 v; u8 n; u8 fl; u8 pad2[6]; Ent8 e[1]; } Rnd;

void func_001a5fd0(Rnd *r, s32 v, s32 seed) {
    s32 i;
    r->v = v;
    for (i = 0; i < r->n; i++) func_001a5688(&r->e[i], (void **)v);
    if (!(u8)(r->fl & 1)) {
        s32 x = seed;
        for (i = 0; i < r->n; i++) {
            x = (x * 2061 + 7) & 0xffff;
            r->e[i].r = (f32)x / 65535.0f;
        }
        r->fl |= 1;
    }
}

void func_001a60d0(void *arg0) {
    M2C_FIELD(arg0, s32 *, 4) = 0;
    M2C_FIELD(arg0, s8 *, 9) = 0;
    M2C_FIELD(arg0, M2C_UNK **, 0) = (M2C_UNK *)D_00575A00;
}

void func_001a62a8(void *arg0) {
    M2C_FIELD(arg0, s32 *, 4) = 0;
    M2C_FIELD(arg0, M2C_UNK **, 0) = (M2C_UNK *)D_00575A00;
}

void func_001a6518(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 4) = arg1;
    func_001a5688(arg0 + 8, (void **)arg1);
}

void func_001a6538(void *arg0) {
    M2C_FIELD(arg0, s32 *, 4) = 0;
    M2C_FIELD(arg0, M2C_UNK **, 0) = (M2C_UNK *)D_00575A00;
}

void func_001a67a0(void *arg0) {
    M2C_FIELD(arg0, s32 *, 4) = 0;
    M2C_FIELD(arg0, M2C_UNK **, 0) = (M2C_UNK *)D_00575A00;
}

#include "data/data_0037.h"

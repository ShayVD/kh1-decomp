/* The ppp lens flare classes' default-flag functions (docs/modules.md
 * "Session 50"): the Cons, Resets and Dess of pppKeLnsLp / Arnd / Clm / Crn
 * / Fls, their "T" versions and pppKeLnsLpSft, and the small setup helpers
 * (func_00191fc8, 00192208, 001924a8, 00192708 fill a flare's argument
 * block from the owner's matrix; func_00192f78, 00193408, 001936c0 run the
 * kelns.c draw helpers for the T versions).  The draws are in
 * kelnscls.nostrict.c.  Each section names the file its code came from.
 * Read from the code, not proved by a boot. */

/* pppKeLnsLpCon (from auto/text_00190000.c). */
#include "m2c.h"
#include "ppp.h"
M2C_UNK func_001a5ca0(void *);
void pppKeLnsLpCon(s32 arg0, PppEntry *arg1) {
    void *temp_s0;

    temp_s0 = arg0 + arg1->offsets[0] + 0xA0;
    func_001a5ca0(temp_s0);
    M2C_FIELD(temp_s0, s32 *, 0x9C) = 0;
    M2C_FIELD(temp_s0, s32 *, 0xA8) = 0;
}

/* pppKeLnsLpReset (from auto/text_00190000_2.c). */
void pppKeLnsLpReset(s32 arg0, PppEntry *arg1) {
    void *temp_a0;

    temp_a0 = arg0 + arg1->offsets[0] + 0xA0;
    M2C_FIELD(temp_a0, s32 *, 0x9C) = 0;
    M2C_FIELD(temp_a0, s32 *, 0xA8) = 0;
}

/* func_00191fc8 (from hand/text_00180000_h12.c). */
#include "common.h"
#include "data/pieces/D_00364130.h"
#include "data/types/text_00180000_h12.h"
typedef struct {
    s32 unk00, unk04, unk08;
    s32 frame; /* +0x0C */
} PppObject;
typedef struct {
    u8 pad[0x12];
    u16 unk12;
} PppAnmHdr;
typedef struct {
    s32 hdr;   /* a PppAnmHdr * */
    s32 unk4;
} PppAnmEnt;
typedef struct {
    u8 pad[0x14];
    PppAnmEnt *anms;   /* +0x14 */
} PppAnmSet;
extern PppAnmSet *D_00615E64;
typedef struct {
    s32 frame;
    s32 id;    /* +0x4 */
} PppAnmKey;
typedef struct {
    s32 p0;
    s32 cur;  /* +0x4 */
    u16 unk8;
    u8 unkA;
} PppAnmWork;
void func_00191fc8(PppObject *obj, PppAnmKey *k, PppEntry *e) {
    PppAnmWork *w = (PppAnmWork *) ((u8 *) obj + e->offsets[0] + 0xA0);
    PppAnmEnt *a;

    if (k->frame != obj->frame)
        return;
    w->p0 = (s32) obj + e->offsets[1] + 0xA0;
    if (k->id == 0xFFFF) {
        w->cur = 0;
        return;
    }
    a = &D_00615E64->anms[k->id];
    if ((s32) a != w->cur) {
        u16 t;

        w->cur = (s32) a;
        t = ((PppAnmHdr *) a->hdr)->unk12;
        w->unkA = 0;
        w->unk8 = t;
    }
}

/* pppKeLnsArndCon (from auto/text_00190000.c). */
M2C_UNK func_001a62a8(s32);
void pppKeLnsArndCon(s32 arg0, PppEntry *arg1) {
    func_001a62a8(arg0 + arg1->offsets[0] + 0xA0);
}

/* func_00192208 (from auto/text_00190000_2.c). */
void func_001a5fd0(s32, s32, s32);
#define D_00615E64 ((void *) D_00615E64)
void func_00192208(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_v0;
    s32 temp_v1_2;
    void *temp_a2;
    void *temp_s0;
    void *temp_v1;

    temp_a2 = M2C_FIELD(arg2, void **, 0xC);
    temp_v1 = arg0 + M2C_FIELD(temp_a2, s32 *, 0);
    temp_s0 = temp_v1 + 0xA0;
    if (M2C_FIELD(arg1, s32 *, 0) == M2C_FIELD(arg0, s32 *, 0xC)) {
        M2C_FIELD(temp_v1, s32 *, 0xA0) = (s32) (arg0 + M2C_FIELD(temp_a2, s32 *, 4) + 0xA0);
        temp_v1_2 = M2C_FIELD(arg1, s32 *, 4);
        if (temp_v1_2 == 0xFFFF) {
            M2C_FIELD(temp_s0, s32 *, 4) = 0;
        } else {
            temp_v0 = M2C_FIELD(D_00615E64, s32 *, 0x14) + (temp_v1_2 * 8);
            if (temp_v0 != M2C_FIELD(temp_s0, s32 *, 4)) {
                func_001a5fd0((s32) temp_s0, temp_v0, (s32) M2C_FIELD(arg1, u8 *, 0x16));
            }
        }
        M2C_FIELD(temp_s0, u16 *, 0xA) = (u16) M2C_FIELD(arg1, u16 *, 0x12);
        M2C_FIELD(temp_s0, u16 *, 0xC) = (u16) M2C_FIELD(arg1, u16 *, 0x10);
        M2C_FIELD(temp_s0, u8 *, 0xE) = (u8) M2C_FIELD(arg1, u8 *, 0x17);
    }
}
#undef D_00615E64

/* pppKeLnsClmCon (from auto/text_00190000_2.c). */
void func_001a60d0(s32);
void pppKeLnsClmCon(s32 arg0, s32 arg1) {
    s32 temp_s0;

    temp_s0 = arg0 + *M2C_FIELD(arg1, s32 **, 0xC) + 0xA0;
    func_001a60d0(temp_s0);
    M2C_FIELD(temp_s0, s8 *, 8) = 4;
}

/* func_001924a8 (from hand/text_00180000_h12.c). */
void func_001a6518(PppAnmWork *, PppAnmEnt *);
void func_001924a8(PppObject *obj, PppAnmKey *k, PppEntry *e) {
    PppAnmWork *w = (PppAnmWork *) ((u8 *) obj + e->offsets[0] + 0xA0);
    PppAnmEnt *a;

    if (k->frame != obj->frame)
        return;
    w->p0 = (s32) obj + e->offsets[1] + 0xA0;
    if (k->id == 0xFFFF) {
        w->cur = 0;
        return;
    }
    a = &D_00615E64->anms[k->id];
    if ((s32) a == w->cur)
        return;
    func_001a6518(w, a);
}

/* pppKeLnsCrnCon (from auto/text_00190000.c). */
M2C_UNK func_001a6538(s32);
void pppKeLnsCrnCon(s32 arg0, PppEntry *arg1) {
    func_001a6538(arg0 + arg1->offsets[0] + 0xA0);
}

/* func_00192708 (from hand/text_00180000_h12.c). */
void func_00192708(PppObject *obj, PppAnmKey *k, PppEntry *e) {
    PppAnmWork *w = (PppAnmWork *) ((u8 *) obj + e->offsets[0] + 0xA0);
    PppAnmEnt *a;

    if (k->frame != obj->frame)
        return;
    w->p0 = (s32) obj + e->offsets[1] + 0xA0;
    if (k->id == 0xFFFF) {
        w->cur = 0;
        return;
    }
    a = &D_00615E64->anms[k->id];
    if ((s32) a != w->cur) {
        u16 t;

        w->cur = (s32) a;
        t = ((PppAnmHdr *) a->hdr)->unk12;
        w->unkA = 0;
        w->unk8 = t;
    }
}

/* pppKeLnsFlsCon (from auto/text_00190000.c). */
M2C_UNK func_001a67a0(s32);
void pppKeLnsFlsCon(s32 arg0, PppEntry *arg1) {
    func_001a67a0(arg0 + arg1->offsets[0] + 0xA0);
}

/* pppKeLnsLpTCon (from auto/text_00190000_4.c). */
extern u8 D_00372708;
void pppKeLnsLpTCon(s32 arg0, PppEntry *arg1) {
    void *temp_s0;

    temp_s0 = arg0 + arg1->offsets[0] + 0xA0;
    func_001a5ca0(temp_s0);
    M2C_FIELD(temp_s0, s32 *, 0x9C) = 0;
    M2C_FIELD(temp_s0, s32 *, 0xA8) = 0;
    M2C_FIELD(temp_s0, u8 *, 0x8C) = (u8) D_00372708;
    M2C_FIELD(temp_s0, s8 *, 0x8D) = 2;
    M2C_FIELD(temp_s0, s8 *, 0xC0) = 0;
    M2C_FIELD(temp_s0, s8 *, 0xC1) = 0;
    D_00372708 += 1;
}

/* pppKeLnsLpTReset (from auto/text_00190000_2.c). */
void pppKeLnsLpTReset(s32 arg0, PppEntry *arg1) {
    void *temp_a0;

    temp_a0 = arg0 + arg1->offsets[0] + 0xA0;
    M2C_FIELD(temp_a0, s32 *, 0x9C) = 0;
    M2C_FIELD(temp_a0, s32 *, 0xA8) = 0;
}

/* pppKeLnsLpTDes (from auto/text_00190000.c). */
void pppKeLnsLpTDes(void) {

}

/* func_00192f78 (from auto/text_00190000_6.c). */
extern M2C_UNK D_00616040;
void func_001a60e8(s32, s32);
void func_00192f78(s32 arg0) {
    s32 sp[8];
    M2C_FIELD(sp, s32 *, 0x4) = M2C_FIELD(arg0, s32 *, 0x24);
    M2C_FIELD(sp, f32 *, 0xC) = M2C_FIELD(arg0, f32 *, 0x20);
    M2C_FIELD(sp, M2C_UNK * *, 0x8) = &D_00616040;
    M2C_FIELD(sp, s32 *, 0x10) = arg0 + 0x10;
    M2C_FIELD(sp, s32 *, 0x0) = arg0;
    func_001a60e8((s32) sp, 0);
}

/* pppKeLnsArndTCon (from auto/text_00190000_6.c). */
void pppKeLnsArndTCon(s32 arg0, PppEntry *arg1) {
    func_001a62a8(arg0 + arg1->offsets[0] + 0xA0);
}

/* pppKeLnsArndTDes (from auto/text_00190000_6.c). */
void pppKeLnsArndTDes(void) {

}

/* pppKeLnsClmTCon (from auto/text_00190000_6.c). */
void pppKeLnsClmTCon(s32 arg0, s32 arg1) {
    s32 temp_s0;

    temp_s0 = arg0 + *M2C_FIELD(arg1, s32 **, 0xC) + 0xA0;
    func_001a60d0(temp_s0);
    M2C_FIELD(temp_s0, s8 *, 8) = 4;
}

/* pppKeLnsClmTDes (from auto/text_00190000.c). */
void pppKeLnsClmTDes(void) {

}

/* func_00193408 (from hand/text_00180000_h40.c). */
#include "data/types/shared.h"
#include "data/types/text_00180000_h40.h"
typedef struct {
    u8 pad00[0x10];
    u8 unk10[0x10]; /* +0x10 */
    f32 unk20;      /* +0x20 */
    s32 unk24;      /* +0x24 */
    f32 w, h;       /* +0x28 */
} PppSprite;
typedef struct {
    PppSprite *s;  /* +0x0 */
    s32 unk4;      /* +0x4 */
    void *m;       /* +0x8 */
    f32 unkC;      /* +0xC */
    u16 w, h;      /* +0x10 */
    u8 *p;         /* +0x14 */
} PppSpriteArg;
void func_001a62c0(PppSpriteArg *, s32);
#define D_00616040 ((PppQv *) &D_00616040)
void func_00193408(PppSprite *s) {
    PppSpriteArg a;

    a.unk4 = s->unk24;
    a.w = (u32) s->w;
    a.h = (u32) s->h;
    a.p = s->unk10;
    a.s = s;
    a.unkC = s->unk20;
    a.m = D_00616040;
    func_001a62c0(&a, 0);
}
#undef D_00616040

/* pppKeLnsCrnTCon (from auto/text_00190000_6.c). */
void pppKeLnsCrnTCon(s32 arg0, PppEntry *arg1) {
    func_001a6538(arg0 + arg1->offsets[0] + 0xA0);
}

/* pppKeLnsCrnTDes (from auto/text_00190000_6.c). */
void pppKeLnsCrnTDes(void) {

}

/* func_001936c0 (from hand/text_00180000_h12.c). */
typedef struct {
    u8 pad[0x10];
    u8 unk10[0x10];
    f32 unk20;
    s32 unk24;
    f32 unk28;
    u16 unk2C;
} PppCbSrc2;
typedef struct {
    PppCbSrc2 *src;
    s32 unk4;
    void *tbl;
    f32 unkC;
    u16 unk10;
    u16 unk12;
    void *sub;
} PppCbArg2;
void func_001a6550(PppCbArg2 *, s32);
#define D_00616040 ((u8 *) &D_00616040)
void func_001936c0(PppCbSrc2 *p) {
    PppCbArg2 a;

    a.unk4 = p->unk24;
    a.unkC = p->unk20;
    a.unk10 = (u32) p->unk28;
    a.src = p;
    a.unk12 = p->unk2C;
    a.tbl = D_00616040;
    a.sub = p->unk10;
    func_001a6550(&a, 0);
}
#undef D_00616040

/* pppKeLnsFlsTCon (from auto/text_00190000_6.c). */
void pppKeLnsFlsTCon(s32 arg0, PppEntry *arg1) {
    func_001a67a0(arg0 + arg1->offsets[0] + 0xA0);
}

/* pppKeLnsFlsTDes (from auto/text_00190000_6.c). */
void pppKeLnsFlsTDes(void) {

}

/* pppKeLnsLpSftCon (from hand/ppp.c). */
#define PPP_WORK(T, obj, e, k) ((T *) ((u8 *) (obj) + (e)->offsets[k] + 0xA0))
typedef struct {
    s32 a, b;
} PppS32x2;
void pppKeLnsLpSftCon(void *obj, PppEntry *e) {
    PppS32x2 *w = PPP_WORK(PppS32x2, obj, e, 0);

    w->a = 0;
    w->b = 0;
}
#undef PPP_WORK


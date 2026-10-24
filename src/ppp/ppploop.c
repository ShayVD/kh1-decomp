/* The ppp loop classes' default-flag functions (docs/modules.md "Session
 * 50"): pppMoveLoop / AngMoveLoop / SclMoveLoop add a velocity (stepped at
 * the key's frame) to the work area's position, angle or scale each frame
 * (unless D_00616234 pauses them); pppPointLoop / AngleLoop / ScaleLoop
 * wrap a value between the key's bounds (func_0018ac28 / func_0018aeb8 set
 * them up); pppDrawMatrixLoop and the Con / Reset / Des of pppDrawMdlLoop
 * and DrawMdlLoopZ.  The Resets call their Cons through a no-prototype
 * declaration (a function view here).  The rest is in ppploop.nostrict.c.
 * Read from the code, not proved by a boot. */
#include "m2c.h"
#include "ppp.h"
#include "data/pieces/D_002BBFA0.h"
#include "common.h"
#include "data/types/shared.h"
#include "data/types/text_00180000_h40.h"
#include "data/pieces/D_00364130.h"
#include "data/pieces/D_00370130.h"

/* pppMoveLoopCon (from auto/text_00180000_20.c). */
void pppMoveLoopCon(s32 arg0, void *arg1) {
    void *temp_a0;
    void *temp_a0_2;

    temp_a0 = arg0 + M2C_FIELD(M2C_FIELD(arg1, void **, 0xC), s32 *, 4);
    temp_a0_2 = temp_a0 + 0xA0;
    M2C_FIELD(temp_a0, f32 *, 0xA0) = M2C_FIELD(temp_a0_2, f32 *, 4) = M2C_FIELD(temp_a0_2, f32 *, 8) = 0.0f;
}

/* pppMoveLoopReset (from auto/text_00180000_5.c). */
#define pppMoveLoopCon ((M2C_UNK (*)()) pppMoveLoopCon)
void pppMoveLoopReset(void) {
    pppMoveLoopCon();
}
#undef pppMoveLoopCon

/* pppMoveLoopFrame (from hand/text_00180000_h40.c). */
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
typedef struct { f32 x, y, z; } PppFVec;
typedef struct {
    s32 frame;
    PppFVec v; /* +0x4 */
} PppFVecKey;
void pppMoveLoopFrame(PppObject *obj, PppFVecKey *key, PppEntry *e) {
    PppFVec *pos = PPP_WORK(PppFVec, obj, e, 0);
    PppFVec *vel = PPP_WORK(PppFVec, obj, e, 1);

    if (D_0061621C != 0 || (D_00615E60->flags & 0xFF0000FF00ULL))
        return;
    if (key->frame == obj->frame) {
        vel->x += key->v.x;
        vel->y += key->v.y;
        vel->z += key->v.z;
    }
    if (D_00616234 == 0) {
        pos->x += vel->x;
        pos->y += vel->y;
        pos->z += vel->z;
    }
}
#undef PPP_WORK

/* pppAngMoveLoopCon (from auto/text_00180000_3.c). */
void pppAngMoveLoopCon(s32 arg0, PppEntry *arg1) {
    void *temp_a0;
    void *temp_a0_2;

    temp_a0 = arg0 + arg1->offsets[1];
    temp_a0_2 = temp_a0 + 0xA0;
    M2C_FIELD(temp_a0_2, s32 *, 8) = 0;
    M2C_FIELD(temp_a0_2, s32 *, 4) = 0;
    M2C_FIELD(temp_a0, s32 *, 0xA0) = 0;
}

/* pppAngMoveLoopReset (from auto/text_00180000_5.c). */
#define pppAngMoveLoopCon ((M2C_UNK (*)()) pppAngMoveLoopCon)
void pppAngMoveLoopReset(void) {
    pppAngMoveLoopCon();
}
#undef pppAngMoveLoopCon

/* pppAngMoveLoopFrame (from hand/text_00180000_h40.c). */
#define PPP_WORK(T, obj, e, k) ((T *) ((u8 *) (obj) + (e)->offsets[k] + 0xA0))
typedef struct { s32 x, y, z; } PppIVec;
typedef struct {
    s32 frame;
    PppIVec v; /* +0x4 */
} PppIVecKey;
void pppAngMoveLoopFrame(PppObject *obj, PppIVecKey *key, PppEntry *e) {
    PppIVec *pos = PPP_WORK(PppIVec, obj, e, 0);
    PppIVec *vel = PPP_WORK(PppIVec, obj, e, 1);

    if (D_0061621C != 0 || (D_00615E60->flags & 0xFF0000FF00ULL))
        return;
    if (key->frame == obj->frame) {
        vel->x += key->v.x;
        vel->y += key->v.y;
        vel->z += key->v.z;
    }
    if (D_00616234 == 0) {
        pos->x += vel->x;
        pos->y += vel->y;
        pos->z += vel->z;
    }
}
#undef PPP_WORK

/* pppSclMoveLoopCon (from auto/text_00180000_20.c). */
void pppSclMoveLoopCon(s32 arg0, void *arg1) {
    void *temp_a0;
    void *temp_a0_2;

    temp_a0 = arg0 + M2C_FIELD(M2C_FIELD(arg1, void **, 0xC), s32 *, 4);
    temp_a0_2 = temp_a0 + 0xA0;
    M2C_FIELD(temp_a0, f32 *, 0xA0) = M2C_FIELD(temp_a0_2, f32 *, 4) = M2C_FIELD(temp_a0_2, f32 *, 8) = 0.0f;
}

/* pppSclMoveLoopReset (from auto/text_00180000_5.c). */
#define pppSclMoveLoopCon ((M2C_UNK (*)()) pppSclMoveLoopCon)
void pppSclMoveLoopReset(void) {
    pppSclMoveLoopCon();
}
#undef pppSclMoveLoopCon

/* pppSclMoveLoopFrame (from hand/text_00180000_h40.c). */
#define PPP_WORK(T, obj, e, k) ((T *) ((u8 *) (obj) + (e)->offsets[k] + 0xA0))
void pppSclMoveLoopFrame(PppObject *obj, PppFVecKey *key, PppEntry *e) {
    PppFVec *pos = PPP_WORK(PppFVec, obj, e, 0);
    PppFVec *vel = PPP_WORK(PppFVec, obj, e, 1);

    if (D_0061621C != 0 || (D_00615E60->flags & 0xFF0000FF00ULL))
        return;
    if (key->frame == obj->frame) {
        vel->x += key->v.x;
        vel->y += key->v.y;
        vel->z += key->v.z;
    }
    if (D_00616234 == 0) {
        pos->x += vel->x;
        pos->y += vel->y;
        pos->z += vel->z;
    }
}
#undef PPP_WORK

/* func_0018ac28 (from auto/text_00180000_20.c). */
void func_0018ac28(s32 arg0, void *arg1) {
    M2C_FIELD(arg1, s32 *, 0xC) = arg0;
    M2C_FIELD(arg1, f32 *, 0) = M2C_FIELD(arg1, f32 *, 4) = M2C_FIELD(arg1, f32 *, 8) = 0.0f;
}

/* pppPointLoopCon (from auto/text_00180000.c). */
void pppPointLoopCon(s32 arg0, PppEntry *arg1) {
    M2C_FIELD((arg0 + arg1->offsets[0]), s32 *, 0xAC) = 0;
}

/* pppPointLoopReset (from auto/text_00180000.c). */
void pppPointLoopReset(s32 arg0, PppEntry *arg1) {
    void *temp_a0;
    void *temp_a0_2;
    void *temp_v0;

    temp_a0 = arg0 + arg1->offsets[0];
    temp_a0_2 = temp_a0 + 0xA0;
    temp_v0 = M2C_FIELD(temp_a0_2, void **, 0xC);
    M2C_FIELD(temp_a0, f32 *, 0xA0) = (f32) (M2C_FIELD(temp_a0, f32 *, 0xA0) - M2C_FIELD(temp_v0, f32 *, 4));
    M2C_FIELD(temp_a0_2, f32 *, 4) = (f32) (M2C_FIELD(temp_a0_2, f32 *, 4) - M2C_FIELD(temp_v0, f32 *, 8));
    M2C_FIELD(temp_a0_2, f32 *, 8) = (f32) (M2C_FIELD(temp_a0_2, f32 *, 8) - M2C_FIELD(temp_v0, f32 *, 0xC));
}

/* pppPointLoopFrame (from auto/text_00180000_10.c). */
#define D_00615E60 ((void *) D_00615E60)
void pppPointLoopFrame(s32 arg0, s32 arg1, s32 arg2) {
    void *temp_s0;
    void *temp_v0;

    temp_v0 = arg0 + *M2C_FIELD(arg2, s32 **, 0xC);
    temp_s0 = temp_v0 + 0xA0;
    if ((D_0061621C == 0) && !(M2C_FIELD(D_00615E60, s64 *, 0xB0) & (((s64) 0xFF << 0x20) | 0xFF00))) {
        if (M2C_FIELD(temp_s0, s32 *, 0xC) == 0) {
            func_0018ac28(arg1, (s32) temp_s0);
        }
        if (M2C_FIELD(arg1, s32 *, 0) == M2C_FIELD(arg0, s32 *, 0xC)) {
            M2C_FIELD(temp_v0, f32 *, 0xA0) = (f32) (M2C_FIELD(temp_v0, f32 *, 0xA0) + M2C_FIELD(arg1, f32 *, 4));
            M2C_FIELD(temp_s0, f32 *, 4) = (f32) (M2C_FIELD(temp_s0, f32 *, 4) + M2C_FIELD(arg1, f32 *, 8));
            M2C_FIELD(temp_s0, f32 *, 8) = (f32) (M2C_FIELD(temp_s0, f32 *, 8) + M2C_FIELD(arg1, f32 *, 0xC));
        }
    }
}
#undef D_00615E60

/* pppAngleLoopCon (from auto/text_00180000.c). */
void pppAngleLoopCon(s32 arg0, PppEntry *arg1) {
    M2C_FIELD((arg0 + arg1->offsets[0]), s32 *, 0xAC) = 0;
}

/* pppAngleLoopReset (from auto/text_00180000.c). */
void pppAngleLoopReset(s32 arg0, PppEntry *arg1) {
    void *temp_a0;
    void *temp_a0_2;
    void *temp_a3;

    temp_a0 = arg0 + arg1->offsets[0];
    temp_a0_2 = temp_a0 + 0xA0;
    temp_a3 = M2C_FIELD(temp_a0_2, void **, 0xC);
    M2C_FIELD(temp_a0, s32 *, 0xA0) = (s32) (M2C_FIELD(temp_a0, s32 *, 0xA0) - M2C_FIELD(temp_a3, s32 *, 4));
    M2C_FIELD(temp_a0_2, s32 *, 4) = (s32) (M2C_FIELD(temp_a0_2, s32 *, 4) - M2C_FIELD(temp_a3, s32 *, 8));
    M2C_FIELD(temp_a0_2, s32 *, 8) = (s32) (M2C_FIELD(temp_a0_2, s32 *, 8) - M2C_FIELD(temp_a3, s32 *, 0xC));
}

/* pppAngleLoopFrame (from auto/text_00180000_10.c). */
void func_0018ad70(s32, s32);
#define D_00615E60 ((void *) D_00615E60)
void pppAngleLoopFrame(s32 arg0, s32 arg1, s32 arg2) {
    void *temp_s0;
    void *temp_v0;

    temp_v0 = arg0 + *M2C_FIELD(arg2, s32 **, 0xC);
    temp_s0 = temp_v0 + 0xA0;
    if ((D_0061621C == 0) && !(M2C_FIELD(D_00615E60, s64 *, 0xB0) & (((s64) 0xFF << 0x20) | 0xFF00))) {
        if (M2C_FIELD(temp_s0, s32 *, 0xC) == 0) {
            func_0018ad70(arg1, (s32) temp_s0);
        }
        if (M2C_FIELD(arg1, s32 *, 0) == M2C_FIELD(arg0, s32 *, 0xC)) {
            M2C_FIELD(temp_v0, s32 *, 0xA0) = (s32) (M2C_FIELD(temp_v0, s32 *, 0xA0) + M2C_FIELD(arg1, s32 *, 4));
            M2C_FIELD(temp_s0, s32 *, 4) = (s32) (M2C_FIELD(temp_s0, s32 *, 4) + M2C_FIELD(arg1, s32 *, 8));
            M2C_FIELD(temp_s0, s32 *, 8) = (s32) (M2C_FIELD(temp_s0, s32 *, 8) + M2C_FIELD(arg1, s32 *, 0xC));
        }
    }
}
#undef D_00615E60

/* func_0018aeb8 (from auto/text_00180000_20.c). */
void func_0018aeb8(s32 arg0, void *arg1) {
    M2C_FIELD(arg1, s32 *, 0xC) = arg0;
    M2C_FIELD(arg1, f32 *, 0) = M2C_FIELD(arg1, f32 *, 4) = M2C_FIELD(arg1, f32 *, 8) = 0.0f;
}

/* pppScaleLoopCon (from auto/text_00180000.c). */
void pppScaleLoopCon(s32 arg0, PppEntry *arg1) {
    M2C_FIELD((arg0 + arg1->offsets[0]), s32 *, 0xAC) = 0;
}

/* pppScaleLoopReset (from auto/text_00180000.c). */
void pppScaleLoopReset(s32 arg0, PppEntry *arg1) {
    void *temp_a0;
    void *temp_a0_2;
    void *temp_v0;

    temp_a0 = arg0 + arg1->offsets[0];
    temp_a0_2 = temp_a0 + 0xA0;
    temp_v0 = M2C_FIELD(temp_a0_2, void **, 0xC);
    M2C_FIELD(temp_a0, f32 *, 0xA0) = (f32) (M2C_FIELD(temp_a0, f32 *, 0xA0) - M2C_FIELD(temp_v0, f32 *, 4));
    M2C_FIELD(temp_a0_2, f32 *, 4) = (f32) (M2C_FIELD(temp_a0_2, f32 *, 4) - M2C_FIELD(temp_v0, f32 *, 8));
    M2C_FIELD(temp_a0_2, f32 *, 8) = (f32) (M2C_FIELD(temp_a0_2, f32 *, 8) - M2C_FIELD(temp_v0, f32 *, 0xC));
}

/* pppScaleLoopFrame (from auto/text_00180000_10.c). */
#define D_00615E60 ((void *) D_00615E60)
void pppScaleLoopFrame(s32 arg0, s32 arg1, s32 arg2) {
    void *temp_s0;
    void *temp_v0;

    temp_v0 = arg0 + *M2C_FIELD(arg2, s32 **, 0xC);
    temp_s0 = temp_v0 + 0xA0;
    if ((D_0061621C == 0) && !(M2C_FIELD(D_00615E60, s64 *, 0xB0) & (((s64) 0xFF << 0x20) | 0xFF00))) {
        if (M2C_FIELD(temp_s0, s32 *, 0xC) == 0) {
            func_0018aeb8(arg1, (s32) temp_s0);
        }
        if (M2C_FIELD(arg1, s32 *, 0) == M2C_FIELD(arg0, s32 *, 0xC)) {
            M2C_FIELD(temp_v0, f32 *, 0xA0) = (f32) (M2C_FIELD(temp_v0, f32 *, 0xA0) + M2C_FIELD(arg1, f32 *, 4));
            M2C_FIELD(temp_s0, f32 *, 4) = (f32) (M2C_FIELD(temp_s0, f32 *, 4) + M2C_FIELD(arg1, f32 *, 8));
            M2C_FIELD(temp_s0, f32 *, 8) = (f32) (M2C_FIELD(temp_s0, f32 *, 8) + M2C_FIELD(arg1, f32 *, 0xC));
        }
    }
}
#undef D_00615E60

/* pppDrawMatrixLoopFrame (from auto/text_00180000.c). */
M2C_UNK func_00267328(s32, M2C_UNK *, s32);
extern M2C_UNK D_00616080;
extern s32 D_00615E68;
void pppDrawMatrixLoopFrame(void) {
    func_00267328(D_00615E68 + 0x50, &D_00616080, D_00615E68 + 0x10);
}

/* pppDrawMdlLoopCon (from auto/text_00180000.c). */
void pppDrawMdlLoopCon(s32 arg0, PppEntry *arg1) {
    M2C_FIELD((arg0 + arg1->offsets[2]), s32 *, 0xA0) = 0;
}

/* pppDrawMdlLoopReset (from auto/text_00180000_20.c). */
void pppDrawMdlLoopReset(s32 arg0, void *arg1) {
    void *temp_a0;

    temp_a0 = arg0 + M2C_FIELD(M2C_FIELD(arg1, void **, 0xC), s32 *, 8) + 0xA0;
    M2C_FIELD(temp_a0, f32 *, 8) = M2C_FIELD(temp_a0, f32 *, 0xC) = M2C_FIELD(temp_a0, f32 *, 0x14) = M2C_FIELD(temp_a0, f32 *, 0x18) = 0.0f;
}

/* pppDrawMdlLoopDes (from auto/text_00180000.c). */
void pppDrawMdlLoopDes(void) {

}

/* pppDrawMdlLoopZCon (from auto/text_00180000.c). */
void pppDrawMdlLoopZCon(s32 arg0, PppEntry *arg1) {
    M2C_FIELD((arg0 + arg1->offsets[2]), s32 *, 0xA0) = 0;
}

/* pppDrawMdlLoopZReset (from auto/text_00180000_20.c). */
void pppDrawMdlLoopZReset(s32 arg0, void *arg1) {
    void *temp_a0;

    temp_a0 = arg0 + M2C_FIELD(M2C_FIELD(arg1, void **, 0xC), s32 *, 8) + 0xA0;
    M2C_FIELD(temp_a0, f32 *, 8) = M2C_FIELD(temp_a0, f32 *, 0xC) = M2C_FIELD(temp_a0, f32 *, 0x14) = M2C_FIELD(temp_a0, f32 *, 0x18) = 0.0f;
}

/* pppDrawMdlLoopZDes (from auto/text_00180000.c). */
void pppDrawMdlLoopZDes(void) {

}


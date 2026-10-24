/* The basic ppp component classes, default flags (docs/modules.md "Session
 * 50"): pppPoint (the owner's position), pppMove / Accele (velocity,
 * acceleration), pppAngle / AngMove / AngAccele, pppScale / SclMove /
 * SclAccele and pppColor / ColMove / ColAccele: each Con clears its work
 * value, each frame adds the key's step at its frame and the next order's
 * value every frame.  pppDrawHookDraw calls the hook a program names.
 * pppColorFrame is in pppcomp.nostrict.c.  Read from the code, not proved by
 * a boot. */
#include "common.h"
#include "data/pieces/D_00364130.h"
#include "ppp.h"
#include "data/types/text_00180000_h12.h"
#include "m2c.h"

/* pppDrawHookDraw (from hand/text_00180000_h12.c). */
typedef struct {
    s32 unk0;
    s32 arg;     /* +0x4 */
} PppHookData;
extern PppHookFn *D_00616220;
void pppDrawHookDraw(PppHookObj *obj, PppHookData *data, PppEntry *e) {
    *(s32 *) ((u8 *) obj + e->offsets[0] + 0xA0) = data->arg;
    if (D_00616220) {
        PppHookFn fn = D_00616220[obj->hdr->hook];
        if (fn)
            fn(obj, data->arg);
    }
}

/* pppPointFrame (from auto/text_00180000_10.c). */
extern s32 D_0061621C;
extern void *D_00615E60;
void pppPointFrame(void *arg0, void *arg1, void *arg2) {
    void *temp_v0;
    void *temp_v0_2;

    if ((D_0061621C == 0) && !(M2C_FIELD(D_00615E60, s64 *, 0xB0) & (((s64) 0xFF << 0x20) | 0xFF00)) && (M2C_FIELD(arg1, s32 *, 0) == M2C_FIELD(arg0, s32 *, 0xC))) {
        temp_v0 = arg0 + *M2C_FIELD(arg2, s32 **, 0xC);
        temp_v0_2 = temp_v0 + 0xA0;
        M2C_FIELD(temp_v0, f32 *, 0xA0) = (f32) (M2C_FIELD(temp_v0, f32 *, 0xA0) + M2C_FIELD(arg1, f32 *, 4));
        M2C_FIELD(temp_v0_2, f32 *, 4) = (f32) (M2C_FIELD(temp_v0_2, f32 *, 4) + M2C_FIELD(arg1, f32 *, 8));
        M2C_FIELD(temp_v0_2, f32 *, 8) = (f32) (M2C_FIELD(temp_v0_2, f32 *, 8) + M2C_FIELD(arg1, f32 *, 0xC));
    }
}

/* pppPointCon (from hand/ppp.c). */
#define PPP_WORK(T, obj, e, k) ((T *) ((u8 *) (obj) + (e)->offsets[k] + 0xA0))
typedef struct {
    f32 x, y, z;
} PppVec3;
void pppPointCon(void *obj, PppEntry *e) {
    PppVec3 *w = PPP_WORK(PppVec3, obj, e, 0);

    w->x = w->y = w->z = 0.0f;
}
#undef PPP_WORK

/* pppMoveFrame (from auto/text_00180000_10.c). */
void pppMoveFrame(void *arg0, void *arg1, void *arg2) {
    void *temp_a3;
    void *temp_a3_2;
    void *temp_a5;
    void *temp_v0;
    void *temp_v1;

    temp_a3 = M2C_FIELD(arg2, void **, 0xC);
    temp_v0 = arg0 + M2C_FIELD(temp_a3, s32 *, 0);
    temp_v1 = arg0 + M2C_FIELD(temp_a3, s32 *, 4);
    temp_a3_2 = temp_v1 + 0xA0;
    temp_a5 = temp_v0 + 0xA0;
    if ((D_0061621C == 0) && !(M2C_FIELD(D_00615E60, s64 *, 0xB0) & (((s64) 0xFF << 0x20) | 0xFF00))) {
        if (M2C_FIELD(arg1, s32 *, 0) == M2C_FIELD(arg0, s32 *, 0xC)) {
            M2C_FIELD(temp_v1, f32 *, 0xA0) = (f32) (M2C_FIELD(temp_v1, f32 *, 0xA0) + M2C_FIELD(arg1, f32 *, 4));
            M2C_FIELD(temp_a3_2, f32 *, 4) = (f32) (M2C_FIELD(temp_a3_2, f32 *, 4) + M2C_FIELD(arg1, f32 *, 8));
            M2C_FIELD(temp_a3_2, f32 *, 8) = (f32) (M2C_FIELD(temp_a3_2, f32 *, 8) + M2C_FIELD(arg1, f32 *, 0xC));
        }
        M2C_FIELD(temp_v0, f32 *, 0xA0) = (f32) (M2C_FIELD(temp_v0, f32 *, 0xA0) + M2C_FIELD(temp_v1, f32 *, 0xA0));
        M2C_FIELD(temp_a5, f32 *, 4) = (f32) (M2C_FIELD(temp_a5, f32 *, 4) + M2C_FIELD(temp_a3_2, f32 *, 4));
        M2C_FIELD(temp_a5, f32 *, 8) = (f32) (M2C_FIELD(temp_a5, f32 *, 8) + M2C_FIELD(temp_a3_2, f32 *, 8));
    }
}

/* pppMoveCon (from auto/text_00180000_20.c). */
void pppMoveCon(s32 arg0, void *arg1) {
    void *temp_a0;
    void *temp_a0_2;

    temp_a0 = arg0 + M2C_FIELD(M2C_FIELD(arg1, void **, 0xC), s32 *, 4);
    temp_a0_2 = temp_a0 + 0xA0;
    M2C_FIELD(temp_a0, f32 *, 0xA0) = M2C_FIELD(temp_a0_2, f32 *, 4) = M2C_FIELD(temp_a0_2, f32 *, 8) = 0.0f;
}

/* pppAcceleFrame (from auto/text_00180000_10.c). */
void pppAcceleFrame(void *arg0, void *arg1, void *arg2) {
    void *temp_a3;
    void *temp_a3_2;
    void *temp_a5;
    void *temp_v0;
    void *temp_v1;

    temp_a3 = M2C_FIELD(arg2, void **, 0xC);
    temp_v0 = arg0 + M2C_FIELD(temp_a3, s32 *, 0);
    temp_v1 = arg0 + M2C_FIELD(temp_a3, s32 *, 4);
    temp_a3_2 = temp_v1 + 0xA0;
    temp_a5 = temp_v0 + 0xA0;
    if ((D_0061621C == 0) && !(M2C_FIELD(D_00615E60, s64 *, 0xB0) & (((s64) 0xFF << 0x20) | 0xFF00))) {
        if (M2C_FIELD(arg1, s32 *, 0) == M2C_FIELD(arg0, s32 *, 0xC)) {
            M2C_FIELD(temp_v1, f32 *, 0xA0) = (f32) (M2C_FIELD(temp_v1, f32 *, 0xA0) + M2C_FIELD(arg1, f32 *, 4));
            M2C_FIELD(temp_a3_2, f32 *, 4) = (f32) (M2C_FIELD(temp_a3_2, f32 *, 4) + M2C_FIELD(arg1, f32 *, 8));
            M2C_FIELD(temp_a3_2, f32 *, 8) = (f32) (M2C_FIELD(temp_a3_2, f32 *, 8) + M2C_FIELD(arg1, f32 *, 0xC));
        }
        M2C_FIELD(temp_v0, f32 *, 0xA0) = (f32) (M2C_FIELD(temp_v0, f32 *, 0xA0) + M2C_FIELD(temp_v1, f32 *, 0xA0));
        M2C_FIELD(temp_a5, f32 *, 4) = (f32) (M2C_FIELD(temp_a5, f32 *, 4) + M2C_FIELD(temp_a3_2, f32 *, 4));
        M2C_FIELD(temp_a5, f32 *, 8) = (f32) (M2C_FIELD(temp_a5, f32 *, 8) + M2C_FIELD(temp_a3_2, f32 *, 8));
    }
}

/* pppAcceleCon (from auto/text_00180000_20.c). */
void pppAcceleCon(s32 arg0, void *arg1) {
    void *temp_a0;
    void *temp_a0_2;

    temp_a0 = arg0 + M2C_FIELD(M2C_FIELD(arg1, void **, 0xC), s32 *, 4);
    temp_a0_2 = temp_a0 + 0xA0;
    M2C_FIELD(temp_a0, f32 *, 0xA0) = M2C_FIELD(temp_a0_2, f32 *, 4) = M2C_FIELD(temp_a0_2, f32 *, 8) = 0.0f;
}

/* pppAngleFrame (from auto/text_00180000_10.c). */
void pppAngleFrame(void *arg0, void *arg1, void *arg2) {
    void *temp_v0;
    void *temp_v0_2;

    if ((D_0061621C == 0) && !(M2C_FIELD(D_00615E60, s64 *, 0xB0) & (((s64) 0xFF << 0x20) | 0xFF00)) && (M2C_FIELD(arg1, s32 *, 0) == M2C_FIELD(arg0, s32 *, 0xC))) {
        temp_v0 = arg0 + *M2C_FIELD(arg2, s32 **, 0xC);
        temp_v0_2 = temp_v0 + 0xA0;
        M2C_FIELD(temp_v0, s32 *, 0xA0) = (s32) (M2C_FIELD(temp_v0, s32 *, 0xA0) + M2C_FIELD(arg1, s32 *, 4));
        M2C_FIELD(temp_v0_2, s32 *, 4) = (s32) (M2C_FIELD(temp_v0_2, s32 *, 4) + M2C_FIELD(arg1, s32 *, 8));
        M2C_FIELD(temp_v0_2, s32 *, 8) = (s32) (M2C_FIELD(temp_v0_2, s32 *, 8) + M2C_FIELD(arg1, s32 *, 0xC));
    }
}

/* pppAngleCon (from auto/text_00180000_3.c). */
void pppAngleCon(s32 arg0, PppEntry *arg1) {
    void *temp_a0;
    void *temp_a0_2;

    temp_a0 = arg0 + arg1->offsets[0];
    temp_a0_2 = temp_a0 + 0xA0;
    M2C_FIELD(temp_a0_2, s32 *, 8) = 0;
    M2C_FIELD(temp_a0_2, s32 *, 4) = 0;
    M2C_FIELD(temp_a0, s32 *, 0xA0) = 0;
}

/* pppAngMoveFrame (from auto/text_00180000_10.c). */
void pppAngMoveFrame(void *arg0, void *arg1, void *arg2) {
    void *temp_a3;
    void *temp_a3_2;
    void *temp_a5;
    void *temp_v0;
    void *temp_v1;

    temp_a3 = M2C_FIELD(arg2, void **, 0xC);
    temp_v0 = arg0 + M2C_FIELD(temp_a3, s32 *, 0);
    temp_v1 = arg0 + M2C_FIELD(temp_a3, s32 *, 4);
    temp_a3_2 = temp_v1 + 0xA0;
    temp_a5 = temp_v0 + 0xA0;
    if ((D_0061621C == 0) && !(M2C_FIELD(D_00615E60, s64 *, 0xB0) & (((s64) 0xFF << 0x20) | 0xFF00))) {
        if (M2C_FIELD(arg1, s32 *, 0) == M2C_FIELD(arg0, s32 *, 0xC)) {
            M2C_FIELD(temp_v1, s32 *, 0xA0) = (s32) (M2C_FIELD(temp_v1, s32 *, 0xA0) + M2C_FIELD(arg1, s32 *, 4));
            M2C_FIELD(temp_a3_2, s32 *, 4) = (s32) (M2C_FIELD(temp_a3_2, s32 *, 4) + M2C_FIELD(arg1, s32 *, 8));
            M2C_FIELD(temp_a3_2, s32 *, 8) = (s32) (M2C_FIELD(temp_a3_2, s32 *, 8) + M2C_FIELD(arg1, s32 *, 0xC));
        }
        M2C_FIELD(temp_v0, s32 *, 0xA0) = (s32) (M2C_FIELD(temp_v0, s32 *, 0xA0) + M2C_FIELD(temp_v1, s32 *, 0xA0));
        M2C_FIELD(temp_a5, s32 *, 4) = (s32) (M2C_FIELD(temp_a5, s32 *, 4) + M2C_FIELD(temp_a3_2, s32 *, 4));
        M2C_FIELD(temp_a5, s32 *, 8) = (s32) (M2C_FIELD(temp_a5, s32 *, 8) + M2C_FIELD(temp_a3_2, s32 *, 8));
    }
}

/* pppAngMoveCon (from auto/text_00180000_3.c). */
void pppAngMoveCon(s32 arg0, PppEntry *arg1) {
    void *temp_a0;
    void *temp_a0_2;

    temp_a0 = arg0 + arg1->offsets[1];
    temp_a0_2 = temp_a0 + 0xA0;
    M2C_FIELD(temp_a0_2, s32 *, 8) = 0;
    M2C_FIELD(temp_a0_2, s32 *, 4) = 0;
    M2C_FIELD(temp_a0, s32 *, 0xA0) = 0;
}

/* pppAngAcceleFrame (from auto/text_00180000_10.c). */
void pppAngAcceleFrame(void *arg0, void *arg1, void *arg2) {
    void *temp_a3;
    void *temp_a3_2;
    void *temp_a5;
    void *temp_v0;
    void *temp_v1;

    temp_a3 = M2C_FIELD(arg2, void **, 0xC);
    temp_v0 = arg0 + M2C_FIELD(temp_a3, s32 *, 0);
    temp_v1 = arg0 + M2C_FIELD(temp_a3, s32 *, 4);
    temp_a3_2 = temp_v1 + 0xA0;
    temp_a5 = temp_v0 + 0xA0;
    if ((D_0061621C == 0) && !(M2C_FIELD(D_00615E60, s64 *, 0xB0) & (((s64) 0xFF << 0x20) | 0xFF00))) {
        if (M2C_FIELD(arg1, s32 *, 0) == M2C_FIELD(arg0, s32 *, 0xC)) {
            M2C_FIELD(temp_v1, s32 *, 0xA0) = (s32) (M2C_FIELD(temp_v1, s32 *, 0xA0) + M2C_FIELD(arg1, s32 *, 4));
            M2C_FIELD(temp_a3_2, s32 *, 4) = (s32) (M2C_FIELD(temp_a3_2, s32 *, 4) + M2C_FIELD(arg1, s32 *, 8));
            M2C_FIELD(temp_a3_2, s32 *, 8) = (s32) (M2C_FIELD(temp_a3_2, s32 *, 8) + M2C_FIELD(arg1, s32 *, 0xC));
        }
        M2C_FIELD(temp_v0, s32 *, 0xA0) = (s32) (M2C_FIELD(temp_v0, s32 *, 0xA0) + M2C_FIELD(temp_v1, s32 *, 0xA0));
        M2C_FIELD(temp_a5, s32 *, 4) = (s32) (M2C_FIELD(temp_a5, s32 *, 4) + M2C_FIELD(temp_a3_2, s32 *, 4));
        M2C_FIELD(temp_a5, s32 *, 8) = (s32) (M2C_FIELD(temp_a5, s32 *, 8) + M2C_FIELD(temp_a3_2, s32 *, 8));
    }
}

/* pppAngAcceleCon (from auto/text_00180000_3.c). */
void pppAngAcceleCon(s32 arg0, PppEntry *arg1) {
    void *temp_a0;
    void *temp_a0_2;

    temp_a0 = arg0 + arg1->offsets[1];
    temp_a0_2 = temp_a0 + 0xA0;
    M2C_FIELD(temp_a0_2, s32 *, 8) = 0;
    M2C_FIELD(temp_a0_2, s32 *, 4) = 0;
    M2C_FIELD(temp_a0, s32 *, 0xA0) = 0;
}

/* pppScaleFrame (from auto/text_00180000_10.c). */
void pppScaleFrame(void *arg0, void *arg1, void *arg2) {
    void *temp_v0;
    void *temp_v0_2;

    if ((D_0061621C == 0) && !(M2C_FIELD(D_00615E60, s64 *, 0xB0) & (((s64) 0xFF << 0x20) | 0xFF00)) && (M2C_FIELD(arg1, s32 *, 0) == M2C_FIELD(arg0, s32 *, 0xC))) {
        temp_v0 = arg0 + *M2C_FIELD(arg2, s32 **, 0xC);
        temp_v0_2 = temp_v0 + 0xA0;
        M2C_FIELD(temp_v0, f32 *, 0xA0) = (f32) (M2C_FIELD(temp_v0, f32 *, 0xA0) + M2C_FIELD(arg1, f32 *, 4));
        M2C_FIELD(temp_v0_2, f32 *, 4) = (f32) (M2C_FIELD(temp_v0_2, f32 *, 4) + M2C_FIELD(arg1, f32 *, 8));
        M2C_FIELD(temp_v0_2, f32 *, 8) = (f32) (M2C_FIELD(temp_v0_2, f32 *, 8) + M2C_FIELD(arg1, f32 *, 0xC));
    }
}

/* pppScaleCon (from auto/text_00180000_20.c). */
void pppScaleCon(s32 arg0, void *arg1) {
    void *temp_a0;
    void *temp_a0_2;

    temp_a0 = arg0 + *M2C_FIELD(arg1, s32 **, 0xC);
    temp_a0_2 = temp_a0 + 0xA0;
    M2C_FIELD(temp_a0, f32 *, 0xA0) = M2C_FIELD(temp_a0_2, f32 *, 4) = M2C_FIELD(temp_a0_2, f32 *, 8) = 0.0f;
}

/* pppSclMoveFrame (from auto/text_00180000_10.c). */
void pppSclMoveFrame(void *arg0, void *arg1, void *arg2) {
    void *temp_a3;
    void *temp_a3_2;
    void *temp_a5;
    void *temp_v0;
    void *temp_v1;

    temp_a3 = M2C_FIELD(arg2, void **, 0xC);
    temp_v0 = arg0 + M2C_FIELD(temp_a3, s32 *, 0);
    temp_v1 = arg0 + M2C_FIELD(temp_a3, s32 *, 4);
    temp_a3_2 = temp_v1 + 0xA0;
    temp_a5 = temp_v0 + 0xA0;
    if ((D_0061621C == 0) && !(M2C_FIELD(D_00615E60, s64 *, 0xB0) & (((s64) 0xFF << 0x20) | 0xFF00))) {
        if (M2C_FIELD(arg1, s32 *, 0) == M2C_FIELD(arg0, s32 *, 0xC)) {
            M2C_FIELD(temp_v1, f32 *, 0xA0) = (f32) (M2C_FIELD(temp_v1, f32 *, 0xA0) + M2C_FIELD(arg1, f32 *, 4));
            M2C_FIELD(temp_a3_2, f32 *, 4) = (f32) (M2C_FIELD(temp_a3_2, f32 *, 4) + M2C_FIELD(arg1, f32 *, 8));
            M2C_FIELD(temp_a3_2, f32 *, 8) = (f32) (M2C_FIELD(temp_a3_2, f32 *, 8) + M2C_FIELD(arg1, f32 *, 0xC));
        }
        M2C_FIELD(temp_v0, f32 *, 0xA0) = (f32) (M2C_FIELD(temp_v0, f32 *, 0xA0) + M2C_FIELD(temp_v1, f32 *, 0xA0));
        M2C_FIELD(temp_a5, f32 *, 4) = (f32) (M2C_FIELD(temp_a5, f32 *, 4) + M2C_FIELD(temp_a3_2, f32 *, 4));
        M2C_FIELD(temp_a5, f32 *, 8) = (f32) (M2C_FIELD(temp_a5, f32 *, 8) + M2C_FIELD(temp_a3_2, f32 *, 8));
    }
}

/* pppSclMoveCon (from auto/text_00180000_20.c). */
void pppSclMoveCon(s32 arg0, void *arg1) {
    void *temp_a0;
    void *temp_a0_2;

    temp_a0 = arg0 + M2C_FIELD(M2C_FIELD(arg1, void **, 0xC), s32 *, 4);
    temp_a0_2 = temp_a0 + 0xA0;
    M2C_FIELD(temp_a0, f32 *, 0xA0) = M2C_FIELD(temp_a0_2, f32 *, 4) = M2C_FIELD(temp_a0_2, f32 *, 8) = 0.0f;
}

/* pppSclAcceleFrame (from auto/text_00180000_10.c). */
void pppSclAcceleFrame(void *arg0, void *arg1, void *arg2) {
    void *temp_a3;
    void *temp_a3_2;
    void *temp_a5;
    void *temp_v0;
    void *temp_v1;

    temp_a3 = M2C_FIELD(arg2, void **, 0xC);
    temp_v0 = arg0 + M2C_FIELD(temp_a3, s32 *, 0);
    temp_v1 = arg0 + M2C_FIELD(temp_a3, s32 *, 4);
    temp_a3_2 = temp_v1 + 0xA0;
    temp_a5 = temp_v0 + 0xA0;
    if ((D_0061621C == 0) && !(M2C_FIELD(D_00615E60, s64 *, 0xB0) & (((s64) 0xFF << 0x20) | 0xFF00))) {
        if (M2C_FIELD(arg1, s32 *, 0) == M2C_FIELD(arg0, s32 *, 0xC)) {
            M2C_FIELD(temp_v1, f32 *, 0xA0) = (f32) (M2C_FIELD(temp_v1, f32 *, 0xA0) + M2C_FIELD(arg1, f32 *, 4));
            M2C_FIELD(temp_a3_2, f32 *, 4) = (f32) (M2C_FIELD(temp_a3_2, f32 *, 4) + M2C_FIELD(arg1, f32 *, 8));
            M2C_FIELD(temp_a3_2, f32 *, 8) = (f32) (M2C_FIELD(temp_a3_2, f32 *, 8) + M2C_FIELD(arg1, f32 *, 0xC));
        }
        M2C_FIELD(temp_v0, f32 *, 0xA0) = (f32) (M2C_FIELD(temp_v0, f32 *, 0xA0) + M2C_FIELD(temp_v1, f32 *, 0xA0));
        M2C_FIELD(temp_a5, f32 *, 4) = (f32) (M2C_FIELD(temp_a5, f32 *, 4) + M2C_FIELD(temp_a3_2, f32 *, 4));
        M2C_FIELD(temp_a5, f32 *, 8) = (f32) (M2C_FIELD(temp_a5, f32 *, 8) + M2C_FIELD(temp_a3_2, f32 *, 8));
    }
}

/* pppSclAcceleCon (from auto/text_00180000_20.c). */
void pppSclAcceleCon(s32 arg0, void *arg1) {
    void *temp_a0;
    void *temp_a0_2;

    temp_a0 = arg0 + M2C_FIELD(M2C_FIELD(arg1, void **, 0xC), s32 *, 4);
    temp_a0_2 = temp_a0 + 0xA0;
    M2C_FIELD(temp_a0, f32 *, 0xA0) = M2C_FIELD(temp_a0_2, f32 *, 4) = M2C_FIELD(temp_a0_2, f32 *, 8) = 0.0f;
}

/* pppColorCon (from auto/text_00180000_4.c). */
void pppColorCon(s32 arg0, PppEntry *arg1) {
    void *temp_a0;
    void *temp_a0_2;

    temp_a0 = arg0 + arg1->offsets[0];
    temp_a0_2 = temp_a0 + 0xA0;
    M2C_FIELD(temp_a0_2, s16 *, 6) = 0;
    M2C_FIELD(temp_a0_2, s16 *, 4) = 0;
    M2C_FIELD(temp_a0_2, s16 *, 2) = 0;
    M2C_FIELD(temp_a0, s16 *, 0xA0) = 0;
}

/* pppColMoveFrame (from auto/text_00180000_10.c). */
void pppColMoveFrame(void *arg0, void *arg1, void *arg2) {
    void *temp_a3;
    void *temp_a3_2;
    void *temp_a4;
    void *temp_v0;
    void *temp_v1;

    temp_a3 = M2C_FIELD(arg2, void **, 0xC);
    temp_v0 = arg0 + M2C_FIELD(temp_a3, s32 *, 0);
    temp_v1 = arg0 + M2C_FIELD(temp_a3, s32 *, 4);
    temp_a3_2 = temp_v1 + 0xA0;
    temp_a4 = temp_v0 + 0xA0;
    if ((D_0061621C == 0) && !(M2C_FIELD(D_00615E60, s64 *, 0xB0) & (((s64) 0xFF << 0x20) | 0xFF00))) {
        if (M2C_FIELD(arg1, s32 *, 0) == M2C_FIELD(arg0, s32 *, 0xC)) {
            M2C_FIELD(temp_v1, u16 *, 0xA0) = (u16) (M2C_FIELD(temp_v1, u16 *, 0xA0) + M2C_FIELD(arg1, u16 *, 4));
            M2C_FIELD(temp_a3_2, u16 *, 2) = (u16) (M2C_FIELD(temp_a3_2, u16 *, 2) + M2C_FIELD(arg1, u16 *, 6));
            M2C_FIELD(temp_a3_2, u16 *, 4) = (u16) (M2C_FIELD(temp_a3_2, u16 *, 4) + M2C_FIELD(arg1, u16 *, 8));
            M2C_FIELD(temp_a3_2, u16 *, 6) = (u16) (M2C_FIELD(temp_a3_2, u16 *, 6) + M2C_FIELD(arg1, u16 *, 0xA));
        }
        M2C_FIELD(temp_v0, u16 *, 0xA0) = (u16) (M2C_FIELD(temp_v0, u16 *, 0xA0) + M2C_FIELD(temp_v1, u16 *, 0xA0));
        M2C_FIELD(temp_a4, u16 *, 2) = (u16) (M2C_FIELD(temp_a4, u16 *, 2) + M2C_FIELD(temp_a3_2, u16 *, 2));
        M2C_FIELD(temp_a4, u16 *, 4) = (u16) (M2C_FIELD(temp_a4, u16 *, 4) + M2C_FIELD(temp_a3_2, u16 *, 4));
        M2C_FIELD(temp_a4, u16 *, 6) = (u16) (M2C_FIELD(temp_a4, u16 *, 6) + M2C_FIELD(temp_a3_2, u16 *, 6));
    }
}

/* pppColMoveCon (from auto/text_00180000_4.c). */
void pppColMoveCon(s32 arg0, PppEntry *arg1) {
    void *temp_a0;
    void *temp_a0_2;

    temp_a0 = arg0 + arg1->offsets[1];
    temp_a0_2 = temp_a0 + 0xA0;
    M2C_FIELD(temp_a0_2, s16 *, 6) = 0;
    M2C_FIELD(temp_a0_2, s16 *, 4) = 0;
    M2C_FIELD(temp_a0_2, s16 *, 2) = 0;
    M2C_FIELD(temp_a0, s16 *, 0xA0) = 0;
}

/* pppColAcceleFrame (from auto/text_00180000_10.c). */
void pppColAcceleFrame(void *arg0, void *arg1, void *arg2) {
    void *temp_a3;
    void *temp_a3_2;
    void *temp_a4;
    void *temp_v0;
    void *temp_v1;

    temp_a3 = M2C_FIELD(arg2, void **, 0xC);
    temp_v0 = arg0 + M2C_FIELD(temp_a3, s32 *, 0);
    temp_v1 = arg0 + M2C_FIELD(temp_a3, s32 *, 4);
    temp_a3_2 = temp_v1 + 0xA0;
    temp_a4 = temp_v0 + 0xA0;
    if ((D_0061621C == 0) && !(M2C_FIELD(D_00615E60, s64 *, 0xB0) & (((s64) 0xFF << 0x20) | 0xFF00))) {
        if (M2C_FIELD(arg1, s32 *, 0) == M2C_FIELD(arg0, s32 *, 0xC)) {
            M2C_FIELD(temp_v1, u16 *, 0xA0) = (u16) (M2C_FIELD(temp_v1, u16 *, 0xA0) + M2C_FIELD(arg1, u16 *, 4));
            M2C_FIELD(temp_a3_2, u16 *, 2) = (u16) (M2C_FIELD(temp_a3_2, u16 *, 2) + M2C_FIELD(arg1, u16 *, 6));
            M2C_FIELD(temp_a3_2, u16 *, 4) = (u16) (M2C_FIELD(temp_a3_2, u16 *, 4) + M2C_FIELD(arg1, u16 *, 8));
            M2C_FIELD(temp_a3_2, u16 *, 6) = (u16) (M2C_FIELD(temp_a3_2, u16 *, 6) + M2C_FIELD(arg1, u16 *, 0xA));
        }
        M2C_FIELD(temp_v0, u16 *, 0xA0) = (u16) (M2C_FIELD(temp_v0, u16 *, 0xA0) + M2C_FIELD(temp_v1, u16 *, 0xA0));
        M2C_FIELD(temp_a4, u16 *, 2) = (u16) (M2C_FIELD(temp_a4, u16 *, 2) + M2C_FIELD(temp_a3_2, u16 *, 2));
        M2C_FIELD(temp_a4, u16 *, 4) = (u16) (M2C_FIELD(temp_a4, u16 *, 4) + M2C_FIELD(temp_a3_2, u16 *, 4));
        M2C_FIELD(temp_a4, u16 *, 6) = (u16) (M2C_FIELD(temp_a4, u16 *, 6) + M2C_FIELD(temp_a3_2, u16 *, 6));
    }
}

/* pppColAcceleCon (from auto/text_00180000_4.c). */
void pppColAcceleCon(s32 arg0, PppEntry *arg1) {
    void *temp_a0;
    void *temp_a0_2;

    temp_a0 = arg0 + arg1->offsets[1];
    temp_a0_2 = temp_a0 + 0xA0;
    M2C_FIELD(temp_a0_2, s16 *, 6) = 0;
    M2C_FIELD(temp_a0_2, s16 *, 4) = 0;
    M2C_FIELD(temp_a0_2, s16 *, 2) = 0;
    M2C_FIELD(temp_a0, s16 *, 0xA0) = 0;
}


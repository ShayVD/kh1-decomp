/* The ppp matrix classes, -fno-strict-aliasing (docs/modules.md "Session
 * 50"): pppMatrix and pppMatrixXZY ... ZYX build the owner's matrix from the
 * work area's position, angles (one rotation order each, pppmtx.c, through
 * the H39_MATRIX_FRAME macro as in their old file) and scale; pppMatrixScl
 * takes position and scale only; pppDrawMatrixWood is a billboard about the
 * camera's up axis.  Read from the code, not proved by a boot. */
#include "ppp.h"
#include "platform/vu.h"
#include "data/types/nostrict_text_00180000_h39.h"
#include "data/pieces/D_00362730.h"
#include "data/pieces/D_003701F0.h"
#include "data/pieces/D_00364130.h"

/* pppMatrixFrame (from hand/nostrict/text_00180000_h39.c). */
typedef struct {
    u8 pad[0x10];
    f32 m[4][4];  /* +0x10 */
    f32 m2[4][4]; /* +0x50 */
} H39MObj;
extern H39MObj *D_00615E68;
void func_00183be0(f32 (*)[4], f32 *);
static inline void h39ScaleRow(f32 *row, f32 s) {
    __asm__ volatile(
        "qmtc2 %1, $vf9\n"
        "lqc2 $vf10, 0(%0)\n"
        "vmulx.xyz $vf10xyz, $vf10xyz, $vf9x\n"
        "sqc2 $vf10, 0(%0)\n"
        :
        : "r"(row), "r"(s));
}
#define H39_MATRIX_FRAME(name, rot)                                       \
    void name(void *obj, void *key, PppEntry *e) {                        \
        f32 *pos = (f32 *) ((u8 *) obj + e->offsets[0] + 0xA0);           \
        f32 *ang = (f32 *) ((u8 *) obj + e->offsets[1] + 0xA0);           \
        f32 *scl = (f32 *) ((u8 *) obj + e->offsets[2] + 0xA0);           \
                                                                          \
        rot(D_00615E68->m, ang);                                          \
        h39ScaleRow(D_00615E68->m[0], scl[0]);                            \
        h39ScaleRow(D_00615E68->m[1], scl[1]);                            \
        h39ScaleRow(D_00615E68->m[2], scl[2]);                            \
        D_00615E68->m[3][0] = pos[0];                                     \
        D_00615E68->m[3][1] = pos[1];                                     \
        D_00615E68->m[3][2] = pos[2];                                     \
    }
H39_MATRIX_FRAME(pppMatrixFrame, func_00183be0)

/* pppMatrixXZYFrame (from hand/nostrict/text_00180000_h39.c). */
void func_001a5250(f32 (*)[4], f32 *);
H39_MATRIX_FRAME(pppMatrixXZYFrame, func_001a5250)

/* pppMatrixYZXFrame (from hand/nostrict/text_00180000_h39.c). */
void func_001a52e0(f32 (*)[4], f32 *);
H39_MATRIX_FRAME(pppMatrixYZXFrame, func_001a52e0)

/* pppMatrixYXZFrame (from hand/nostrict/text_00180000_h39.c). */
void func_001a5370(f32 (*)[4], f32 *);
H39_MATRIX_FRAME(pppMatrixYXZFrame, func_001a5370)

/* pppMatrixZXYFrame (from hand/nostrict/text_00180000_h39.c). */
void func_001a5400(f32 (*)[4], f32 *);
H39_MATRIX_FRAME(pppMatrixZXYFrame, func_001a5400)

/* pppMatrixZYXFrame (from hand/nostrict/text_00180000_h39.c). */
void func_001a5490(f32 (*)[4], f32 *);
H39_MATRIX_FRAME(pppMatrixZYXFrame, func_001a5490)

/* pppMatrixSclFrame (from hand/nostrict/text_00180000_h39.c). */
void pppMatrixSclFrame(void *obj, void *key, PppEntry *e) {
    f32 *pos = (f32 *) ((u8 *) obj + e->offsets[0] + 0xA0);
    f32 *scl = (f32 *) ((u8 *) obj + e->offsets[1] + 0xA0);

    PlatVu0UnitMatrix(D_00615E68->m);
    D_00615E68->m[0][0] = scl[0];
    D_00615E68->m[1][1] = scl[1];
    D_00615E68->m[2][2] = scl[2];
    D_00615E68->m[3][0] = pos[0];
    D_00615E68->m[3][1] = pos[1];
    D_00615E68->m[3][2] = pos[2];
}

/* pppDrawMatrixWoodFrame (from hand/nostrict/text_00180000_h39.c). */
typedef int u128 __attribute__((mode(TI)));
extern f32 D_006160C0[4][4];
extern f32 D_00616080[4][4];
void pppDrawMatrixWoodFrame(void) {
    PlatVu0ScaleVector(D_00615E68->m2[0], D_00615E68->m[0], D_003701F0[0]);
    PlatVu0ScaleVector(D_00615E68->m2[1], D_00615E68->m[1], D_003701F0[1]);
    PlatVu0ScaleVector(D_00615E68->m2[2], D_00615E68->m[2], D_003701F0[2]);
    *(u128 *) D_00615E68->m2[3] = *(u128 *) D_00615E68->m[3];
    PlatVu0MulMatrix(D_00615E68->m2, D_006160C0, D_00615E68->m2);
    PlatVu0ApplyMatrix(D_00615E68->m2[3], D_00616080, D_00615E68->m[3]);
}


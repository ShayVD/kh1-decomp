/* VU0 state shared by every port platform (the host build and the Vita):
 * what the game's inline VU0 asm keeps in VU0 registers across calls.
 * include/platform/vu.h's off-EE side reads and writes it. Not part of the
 * PS2 build (it lives outside src/). */
#include "common.h"
#include "platform/vu.h"

f32 cosf(f32);
f32 sinf(f32);

/* the random register R (vrinit / vrxor / vrnext / vrget): a float in [1, 2) */
u32 PlatVu0R = 0x3F800000;

/* VU0 microprogram P21 (src/hand/vu0.c's func_00162cd0, docs/renderer-spec.md):
 * rows 0-2 of Rx(x) * Ry(y) * Rz(z) in the row-vector convention. The VU0
 * code takes sin / cos by a Taylor series; libm's are close to it. */
void PlatVu0RotRows(f32 (*out)[4], const f32 *rot) {
    f32 t[3][3];
    f32 cx = cosf(rot[0]), sx = sinf(rot[0]);
    f32 cy = cosf(rot[1]), sy = sinf(rot[1]);
    f32 cz = cosf(rot[2]), sz = sinf(rot[2]);
    int i, j, k;
    /* Rx rows (1,0,0) (0,cx,sx) (0,-sx,cx); Ry (cy,0,-sy) (0,1,0) (sy,0,cy);
     * Rz (cz,sz,0) (-sz,cz,0) (0,0,1) */
    f32 rx[3][3] = {{1, 0, 0}, {0, 0, 0}, {0, 0, 0}};
    f32 ry[3][3] = {{0, 0, 0}, {0, 1, 0}, {0, 0, 0}};
    f32 rz[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 1}};
    rx[1][1] = cx; rx[1][2] = sx; rx[2][1] = -sx; rx[2][2] = cx;
    ry[0][0] = cy; ry[0][2] = -sy; ry[2][0] = sy; ry[2][2] = cy;
    rz[0][0] = cz; rz[0][1] = sz; rz[1][0] = -sz; rz[1][1] = cz;
    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++) {
            t[i][j] = 0.0f;
            for (k = 0; k < 3; k++)
                t[i][j] += rx[i][k] * ry[k][j];
        }
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            out[i][j] = 0.0f;
            for (k = 0; k < 3; k++)
                out[i][j] += t[i][k] * rz[k][j];
        }
        out[i][3] = 0.0f;
    }
}

/* xs_dh_break.x func_00f20820: draft (session 136), not byte-identical; the port runs it
 * (ovl/xs_dh_break/drafts.tsv). Sets up the shard at grid cell (row, col): its corners from
 * func_00f206a0's jittered 51 x 51 grid, a centre 30 apart (+-25), spins of 1-6 degrees a step,
 * and the time it starts to fall: later the farther it is from the two points D_00F311D0 /
 * D_00F311E0. */
#include "shard.h"

f32 func_00f20020(void);
void func_00f20798(DhShard *, s32, f32 *);
f32 func_001edc80(f32 *, f32 *);
extern f32 D_00F9CEB0[51][51][2];
extern OvlVec D_00F311D0[2];
extern f32 D_00F31200;
extern f32 D_00FA2400;

void func_00f20820(DhShard *s, s32 row, s32 col) {
    s32 k;
    f32 a, b;
    func_00f20798(s, 0, D_00F9CEB0[row][col]);
    func_00f20798(s, 1, D_00F9CEB0[row + 1][col]);
    func_00f20798(s, 2, D_00F9CEB0[row][col + 1]);
    func_00f20798(s, 3, D_00F9CEB0[row + 1][col + 1]);
    a = func_00f20020() * 50.0f;
    s->c[1] = 0.0f;
    s->c[0] = ((row + 0.5f) * 30.0f - 750.0f) + a - 25.0f;
    a = func_00f20020() * 50.0f;
    s->c[3] = 1.0f;
    s->c[2] = ((col + 0.5f) * 30.0f - 750.0f) + a - 25.0f;
    for (k = 0; k < 4; k++) {
        sceVu0SubVector(s->pt[k], s->pt[k], s->c);
        s->pt[k][3] = 1.0f;
    }
    s->rot[0] = s->rot[3] = s->rot[2] = s->rot[1] = 0.0f;
    for (k = 0; k < 3; k++)
        s->drot[k] = (func_00f20020() * 5.0f + 1.0f) / 180.0f * 3.1415927f;
    a = 1.0f - func_001edc80(s->c, D_00F311D0[0]) * 0.00066666666f;
    b = 1.0f - func_001edc80(s->c, D_00F311D0[1]) * 0.00088888884f;
    if (a < 0.0f) a = 0.0f;
    if (b < 0.0f) b = 0.0f;
    b = b + 0.0f;
    s->vel[3] = 0.0f;
    s->vel[1] = D_00F31200;
    s->vel[2] = 0.0f;
    s->vel[0] = 0.0f;
    s->start = 300.0f - (a + b) * 60.0f * 5.0f;
    s->vel[1] = s->vel[1] - (func_00f20020() + 0.5f) * 2.2049994f;
    D_00FA2400 = 0.0f;
}

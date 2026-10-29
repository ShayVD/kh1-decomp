/* xs_dh_break.x func_00f20820: matched by hand (session 141, wwm1 round 21): wwm2's round 29 draft (8 words: the 50.0f / 25.0f constants in $f21 / $f20 the wrong way round) with the first jitter written inline, s->c[0] = (...) + func_00f20020() * 50.0f - 25.0f, instead of through a. */
#include "ovl.h"
/* xs_dh_break.x func_00f20820: draft (session 136), not byte-identical; the port runs it
 * (ovl/xs_dh_break/drafts.tsv). Sets up the shard at grid cell (row, col): its corners from
 * func_00f206a0's jittered 51 x 51 grid, a centre 30 apart (+-25), spins of 1-6 degrees a step,
 * and the time it starts to fall: later the farther it is from the two points D_00F311D0 /
 * D_00F311E0. */
/* xs_dh_break.x (Dive to the Heart: the station's floor breaking into 2,500 falling shards): the
 * shard record of the session 136 drafts (0xB0 bytes, 2,500 from D_00F317F0). */

typedef struct {
    OvlVec pt[4];  /* 0x00: the corners, from the centre after func_00f20820 */
    OvlVec c;      /* 0x40: the centre (y 0, w 1) */
    OvlVec rot;    /* 0x50: the angles */
    OvlVec drot;   /* 0x60: the angles' steps (x y z) */
    OvlVec vel;    /* 0x70: the fall (y only) */
    f32 tu[4];     /* 0x80: the corners' texture u */
    f32 tv[4];     /* 0x90: and v (1 - grid y) */
    f32 start;     /* 0xA0: D_00F311C4's time it starts to fall */
    u8 padA4[0xB0 - 0xA4];
} DhShard;

extern DhShard D_00F317F0[2500];


f32 func_00f20020(void);
void func_00f20798(DhShard *, s32, f32 *);
f32 func_001edc80(f32 *, f32 *);
extern f32 D_00F9CEB0[51][51][2];
extern OvlVec D_00F311D0[2];
extern f32 D_00F31200;
extern f32 D_00FA2400;

void func_00f20820(DhShard *s, s32 row, s32 col) {
    f32 d[2];
    s32 k;
    f32 b;
    func_00f20798(s, 0, D_00F9CEB0[row][col]);
    func_00f20798(s, 1, D_00F9CEB0[row + 1][col]);
    func_00f20798(s, 2, D_00F9CEB0[row][col + 1]);
    func_00f20798(s, 3, D_00F9CEB0[row + 1][col + 1]);
    s->c[0] = ((row + 0.5f) * 30.0f - 750.0f) + func_00f20020() * 50.0f - 25.0f;
    s->c[1] = 0.0f;
    b = func_00f20020() * 50.0f;
    s->c[2] = ((col + 0.5f) * 30.0f - 750.0f) + b - 25.0f;
    s->c[3] = 1.0f;
    for (k = 0; k < 4; k++) {
        sceVu0SubVector(s->pt[k], s->pt[k], s->c);
        s->pt[k][3] = 1.0f;
    }
    s->rot[0] = s->rot[1] = s->rot[2] = s->rot[3] = 0.0f;
    for (k = 0; k < 3; k++)
        s->drot[k] = (func_00f20020() * 5.0f + 1.0f) / 180.0f * 3.1415928f;
    d[0] = func_001edc80(s->c, D_00F311D0[0]) * 0.00066666666f;
    d[1] = func_001edc80(s->c, D_00F311D0[1]) * 0.00088888888f;
    d[0] = 1.0f - d[0];
    if (d[0] < 0.0f) d[0] = 0.0f;
    d[1] = 1.0f - d[1];
    if (d[1] < 0.0f) d[1] = 0.0f;
    s->vel[1] = D_00F31200;
    s->vel[3] = 0.0f;
    d[1] += 0.0f;
    s->start = 300.0f - (d[0] + d[1]) * 60.0f * 5.0f;
    s->vel[2] = 0.0f;
    s->vel[0] = 0.0f;
    s->vel[1] = s->vel[1] - (func_00f20020() + 0.5f) * 2.2049995f;
    D_00FA2400 = 0.0f;
}

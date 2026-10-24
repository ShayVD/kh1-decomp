/* The menu models' camera and three matrix builders (docs/modules.md
 * "Session 45"), 0x00236a58-0x00236e40.
 * func_00236a58 steps the camera D_00425F70 (Cam_425f70; journalmdl.c's
 * func_0021ae28 points it at D_00425D80 and calls this each frame): with
 * x1e0 == 0 it aims from the position at the target (rx, ry from atan2f),
 * otherwise it places the position at `dist` from the target along the
 * angles; then it builds the view matrix m80 (libvu0's camera matrix from the
 * position and the rotated forward / up vectors v160 / v170), the rotation
 * mc0, m0 = m40 x m80 and the unit view direction v190.
 * func_00236c68(m, pos, z, y, rot) is the same camera matrix for a caller's
 * position, vectors and angles; func_00236d48 / func_00236d98 rotate by three
 * angles (z, x, y and x, y, z order); func_00236de8 is a scale matrix.
 * No C caller of the last four in the main ELF (overlays, most likely). */
#include "common.h"
#include "platform/math.h"
#include "data/pieces/D_00425CE0.h"
#include "data/pieces/D_00425F70.h"

typedef f32 MTX[4][4] __attribute__((aligned(16)));
typedef f32 VEC[4] __attribute__((aligned(16)));

f32 atan2f(f32, f32);
void func_00236d48(void *, void *, void *);
void func_002672f8(void *, void *, void *);
void func_002673b8(void *, void *);
void func_002676c0(void *, void *, f32);
void func_00267768(void *, void *, f32);
void func_00267810(void *, void *, f32);
void func_00267930(void *, void *, void *, void *);
void sceVu0UnitMatrix(void *);
void sceVu0MulMatrix(void *, void *, void *);

#define C D_00425F70
void func_00236a58(void) {
    MTX m;
    VEC v;
    VEC a;
    VEC b;
    f32 dx, dy, dz;
    if (C->x1e0 == 0) {
        dx = C->tx - C->px;
        dz = C->tz - C->pz;
        dy = C->ty - C->py;
        C->rz = 0;
        C->rx = atan2f(-dy, PlatSqrtf(dx * dx + dz * dz));
        C->ry = atan2f(dx, dz);
    } else {
        func_00236d48(m, D_00425CE0, &C->rx);
        v[0] = 0;
        v[1] = 0;
        v[2] = C->dist;
        v[3] = 1.0f;
        func_002672f8(v, m, v);
        C->px = C->tx + v[0];
        dx = C->tx - C->px;
        C->py = C->ty + v[1];
        dy = C->ty - C->py;
        C->pz = C->tz + v[2];
        dz = C->tz - C->pz;
    }
    func_00267768(m, D_00425CE0, C->rx);
    func_00267810(m, m, C->ry);
    func_002672f8(a, m, C->v160);
    func_002672f8(b, m, C->v170);
    func_00267930(C->m80, &C->px, a, b);
    sceVu0UnitMatrix(C->mc0);
    func_00236d48(C->mc0, C->mc0, &C->rx);
    sceVu0MulMatrix(C->m0, C->m40, C->m80);
    C->v190[0] = dx;
    C->v190[1] = dy;
    C->v190[2] = dz;
    C->v190[3] = 1.0f;
    func_002673b8(C->v190, C->v190);
}
#undef C

void func_00236c68(void *out, f32 *pos, f32 *z, f32 *y, f32 *rot) {
    MTX m;
    VEC rz;
    VEC ry;
    VEC rp;
    func_00267768(m, D_00425CE0, rot[0]);
    func_00267810(m, m, rot[1]);
    func_002676c0(m, m, rot[2]);
    func_002672f8(rz, m, z);
    func_002672f8(ry, m, y);
    func_002672f8(rp, m, pos);
    func_00267930(out, rp, rz, ry);
}

void func_00236d48(void *out, void *in, void *rot) {
    func_002676c0(out, in, ((f32 *)rot)[2]);
    func_00267768(out, out, ((f32 *)rot)[0]);
    func_00267810(out, out, ((f32 *)rot)[1]);
}

void func_00236d98(void *out, void *in, f32 *rot) {
    func_00267768(out, in, rot[0]);
    func_00267810(out, out, rot[1]);
    func_002676c0(out, out, rot[2]);
}

void func_00236de8(f32 (*m)[4], f32 s) {
    sceVu0UnitMatrix(m);
    m[0][0] *= s;
    m[1][1] *= s;
    m[2][2] *= s;
}

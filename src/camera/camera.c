/* The event camera, 0x001c5168-0x001ca9e8 (include/camera/camera.h,
 * docs/modules.md "src/camera/"), in address order:
 *
 * - func_001c5168: move the path output with the objects it follows;
 * - func_001c53c8 (in camera.nostrict_nofill.c): interpolate the path at a
 *   time;
 * - func_001c5b88 / func_001c5db8: the two path players (per-frame
 *   callbacks), func_001c5ee8 loads a path and starts func_001c5db8;
 *   func_001c62a0 (not matched; original bytes) is a second loader;
 * - func_001c6720 (reset), func_001c6890 (camera from the view) and
 *   func_001c6a20 (view from the camera).
 *
 * Then the camera's script functions, 0x001c6d08-0x001ca9e8 (entries of
 * func_001dcad0's table D_003D9FE0; eight of them are in camera.nostrict.c):
 * set / push the position, rotation and f120 / f124, start the five tween
 * channels and the shake (CamState in camera.h), and func_001ca800, which
 * runs the active channels every frame.  They need func_001c6890 defined
 * above them, so core and script functions were one translation unit. */
#include "common.h"
#include "camera/camera.h"
#include "vm/vm_mgr.h"
#include "data/types/vm_rec.h"
#include "data/types/fvec.h"
#include "data/pieces/D_0037A380.h"
#include "data/pieces/D_002E2780.h"
#include "data/pieces/D_002E2790.h"
#include "data/pieces/D_002E27A4.h"
#include "data/pieces/D_002BBDFC.h"
#include "data/pieces/D_002C5958.h"

extern VmMgr D_00389C90;
extern CamState D_003C5510;
extern CamVec D_003C55F0;           /* D_003C5510.rot */
extern s32 D_003C5500;
extern f32 D_002E27A0;

/* What D_00389C90.x306c / x3070 point at while the camera follows
 * objects (func_001c5168). */
typedef struct { u8 pad[16]; FVec4 pos; u8 pad32[28]; f32 roty; } CamObj;

/* D_0037A380's `cam` member, read through a cast as h42 did: a direct
 * read through the union (D_0037A380.cam.t) gets alias set 0, which
 * changes two words of func_001c5db8. */
#define CAM (*(Cam_37A380 *)&D_0037A380)

void *memcpy(void *, const void *, u32);
void *memset(void *, s32, u32);
void sceVu0UnitMatrix(f32 (*m)[4]);
void func_00267768(f32 (*d)[4], f32 (*s)[4], f32 r);
void func_00267810(f32 (*d)[4], f32 (*s)[4], f32 r);
void func_002676c0(f32 (*d)[4], f32 (*s)[4], f32 r);
void func_00267578(f32 (*d)[4], f32 (*s)[4], f32 *v);
void func_002672f8(void *d, f32 (*m)[4], void *s);
void func_002675a8(void *d, void *s);
void func_00124c68(f32);
void func_0011ef10(s32, void *);
void func_001e9d00(void *d, void *a, void *b, f32 t);
void func_001e9fe8(void *dst, void *src);
void func_001e9f18(void *dst, void *a, void *b, f32 t);
f32 func_001e9e58(void *a, void *b);

void func_001c5168(void) {
    FVec4 a;
    FVec4 b;
    f32 m[4][4] __attribute__((aligned(16)));
    VmMgr *g = &D_00389C90;
    switch ((u32)g->x3058) {
    case 0:
        break;
    case 1:
        CAM.a.x += ((CamObj *)g->x306c)->pos.x;
        CAM.a.y += ((CamObj *)g->x306c)->pos.y;
        CAM.a.z += ((CamObj *)g->x306c)->pos.z;
        break;
    case 2:
        CAM.d.y += ((CamObj *)g->x306c)->roty;
        sceVu0UnitMatrix(m);
        func_00267810(m, m, ((CamObj *)g->x306c)->roty);
        func_002672f8(&CAM.a, m, &CAM.a);
        CAM.a.x += ((CamObj *)g->x306c)->pos.x;
        CAM.a.y += ((CamObj *)g->x306c)->pos.y;
        CAM.a.z += ((CamObj *)g->x306c)->pos.z;
        break;
    case 3:
        func_001e9d00(&b, &((CamObj *)g->f3070.i[0])->pos, &((CamObj *)g->x306c)->pos, CAM.d.z);
        CAM.d.y += b.y;
        func_001e9fe8(&b, &CAM.d);
        func_001e9f18(&a, &CAM.a, &b, CAM.f60);
        a.x += ((CamObj *)g->f3070.i[0])->pos.x;
        a.y += ((CamObj *)g->f3070.i[0])->pos.y;
        a.z += ((CamObj *)g->f3070.i[0])->pos.z;
        sceVu0UnitMatrix(m);
        func_00267810(m, m, ((CamObj *)g->x306c)->roty);
        func_002672f8(&CAM.a, m, &CAM.a);
        CAM.a.x += ((CamObj *)g->x306c)->pos.x;
        CAM.a.y += ((CamObj *)g->x306c)->pos.y;
        CAM.a.z += ((CamObj *)g->x306c)->pos.z;
        CAM.f60 = func_001e9e58(&a, &CAM.a);
        func_001e9d00(&CAM.d, &CAM.a, &a, CAM.d.z);
        break;
    }
}

/* func_001c53c8 is in camera.nostrict_nofill.c. */

/* Copy a 16-byte vector as CamV4q (two ld / sd pairs) between CamState's
 * CamVec slots and the path output. */
static inline void cp_q(void *d, void *a) {
    *(CamV4q *)d = *(CamV4q *)a;
}

/* Per-frame callback: play the loaded path at half the frame time (scaled
 * by VmMgr.x314c) into the camera; at its end clear VmMgr flag 37. */
s32 func_001c5b88(void) {
    VmMgr *g = &D_00389C90;
    Cam_37A380 *c = &D_0037A380.cam;
    f32 t;
    t = c->t + D_002BBDFC * 0.5f * g->x314c;
    c->t = t;
    if ((f32)c->last->n < t) {
        c->t = (f32)c->last->n;
        func_001c53c8(c->t);
        cp_q(D_003C5510.pos, &c->a);
        cp_q(D_003C5510.rot, &c->d);
        cp_q(&D_003C5510.rx, &c->e);
        cp_q(D_003C5510.v110, &c->c);
        cp_q(D_003C5510.v100, &c->b);
        D_003C5510.f120 = c->f60;
        D_003C5510.f124 = c->fE0F4;
        func_001c6a20();
        g->f3070.x &= ~(1ULL << 37);
    } else {
        func_001c53c8(t);
        cp_q(D_003C5510.pos, &c->a);
        cp_q(D_003C5510.rot, &c->d);
        cp_q(&D_003C5510.rx, &c->e);
        cp_q(D_003C5510.v110, &c->c);
        cp_q(D_003C5510.v100, &c->b);
        D_003C5510.f120 = c->f60;
        D_003C5510.f124 = c->fE0F4;
        func_001c6a20();
        if ((s32)(D_003C5510.fl.x >> 8) & 1) func_002675a8(D_003C5510.base, D_003C5510.pos);
    }
    return 4;
}

/* The same copy as one lq / sq (V4_37A380 is 16-byte aligned). */
static inline void cp_v(void *d, void *s) {
    *(V4_37A380 *)d = *(V4_37A380 *)s;
}

/* Per-frame callback (started by func_001c5ee8): step the path one key
 * time per frame; returns 4 at its end. */
s32 func_001c5db8(void) {
    CAM.t += 1.0f;
    if ((f32)CAM.last->n < CAM.t) {
        CAM.t = (f32)CAM.last->n;
        return 4;
    }
    func_001c53c8(CAM.t);
    cp_v(D_003C5510.pos, &CAM.a);
    cp_v(D_003C5510.rot, &CAM.d);
    cp_v(&D_003C5510.rx, &CAM.e);
    cp_v(D_003C5510.v110, &CAM.c);
    cp_v(D_003C5510.v100, &CAM.b);
    D_003C5510.f120 = CAM.f60;
    D_003C5510.f124 = CAM.fE0F4;
    func_001c6a20();
    return 0;
}

static inline void cp16(B16_37A380 *d, B16_37A380 *s) {
    *d = *s;
}
static inline void cpm(void *d, void *s) {
    memcpy(d, s, 16);
}
static inline void lk_init(struct Lk_37A380 *l) {
    l->prev = 0;
    l->next = 0;
}
typedef union { f32 f[4]; Ent_37A380 *p[4]; } __attribute__((aligned(16))) A16;
static inline void inl_cpy(V4_37A380 *d, V4_37A380 *s) {
    *(A16 *)d = *(A16 *)s;
}

/* Load a camera path from the script file at `p` (a count, then the keys)
 * and start func_001c5db8. */
void func_001c5ee8(s32 *p) {
    s32 i;
    D_0037A380.cam.n = *p++;
    for (i = 0; i < D_0037A380.cam.n; i++) {
        Ent_37A380 *e = &D_0037A380.cam.ent[i];
        e->c0 = *(C4_37A380 *)p; p++;
        e->c4 = *(C4_37A380 *)p; p++;
        D_0037A380.cam.ent[i].n = *p; p++;
        cpm(&e->v[0], (B16_37A380 *)p); p += 4;
        cpm(&e->v[1], (B16_37A380 *)p); p += 4;
        cpm(&D_0037A380.cam.ent[i].v[2], (B16_37A380 *)p); p += 4;
        cpm(&D_0037A380.cam.ent[i].v[3], (B16_37A380 *)p); p += 4;
        cpm(&D_0037A380.cam.ent[i].v[4], (B16_37A380 *)p); p += 4;
        cpm(&D_0037A380.cam.ent[i].v[5], (B16_37A380 *)p); p += 4;
        cpm(&D_0037A380.cam.ent[i].v[6], (B16_37A380 *)p); p += 4;
        cpm(&D_0037A380.cam.ent[i].v[7], (B16_37A380 *)p); p += 4;
        cpm(&D_0037A380.cam.ent[i].v[8], (B16_37A380 *)p); p += 4;
        cpm(&D_0037A380.cam.ent[i].v[9], (B16_37A380 *)p); p += 4;
        cpm(&D_0037A380.cam.ent[i].v[10], (B16_37A380 *)p); p += 4;
        e->f[0] = *(f32 *)p; p++;
        e->f[1] = *(f32 *)p; p++;
        e->f[2] = *(f32 *)p; p++;
        e->f[3] = *(f32 *)p; p++;
        e->lk.f4 = *(f32 *)p; p++;
        e->lk.f5 = *(f32 *)p; p++;
        if (i == 0) {
            if (p) lk_init(&D_0037A380.cam.ent[0].lk); else lk_init(&D_0037A380.cam.ent[0].lk); /* identical arms, re-merged by jump2 */
        } else {
            Ent_37A380 *q = &D_0037A380.cam.ent[i - 1];
            if (i > 0) { /* identical arms (odd source): adds refs to i so it outranks lk in global-alloc; re-merged by jump2 */
                D_0037A380.cam.ent[i - 1].lk.next = &D_0037A380.cam.ent[i];
                e->lk.next = 0;
            } else {
                D_0037A380.cam.ent[i - 1].lk.next = &D_0037A380.cam.ent[i];
                e->lk.next = 0;
            }
            e->lk.prev = q;
        }
    }
    D_0037A380.cam.e.x = 0;
    D_0037A380.cam.e.y = 0;
    D_0037A380.cam.first = &D_0037A380.cam.ent[0];
    D_0037A380.cam.last = &D_0037A380.cam.ent[D_0037A380.cam.n - 1];
    D_0037A380.cam.t = (f32)D_0037A380.cam.ent[0].n;
    inl_cpy(&D_0037A380.cam.a, (V4_37A380 *)&D_0037A380.cam.ent[0].v[5]);
    D_0037A380.cam.e.z = 0;
    inl_cpy(&D_0037A380.cam.b, (V4_37A380 *)&D_0037A380.cam.ent[0].v[6]);
    inl_cpy(&D_0037A380.cam.c, (V4_37A380 *)&D_0037A380.cam.ent[0].v[7]);
    inl_cpy(&D_0037A380.cam.d, (V4_37A380 *)&D_0037A380.cam.ent[0].v[10]);
    D_0037A380.cam.f60 = D_0037A380.cam.ent[0].f[2];
    D_0037A380.cam.e.w = 0;
    D_0037A380.cam.fE0F4 = D_0037A380.cam.ent[0].lk.f5;
    D_003C5500 = *(s32 *)&D_0037A380.cam.ent[256] + 1;
    func_0011ef10(50000, func_001c5db8);
    i = 0; /* dead store kept: needed for the match */
}

/* func_001c62a0 (0x001c62a0-0x001c671c) is not matched. */

/* The camera's defaults: no tween running, unit / zero vectors, 1000 and
 * 53 in the scalars after them; then the camera from the current view. */
void func_001c6720(void) {
    FVec4 v;
    D_003C5510.fl.x &= ~1;
    D_003C5510.fl.x &= ~2;
    D_003C5510.fl.x &= ~4;
    D_003C5510.fl.x &= ~8;
    D_003C5510.fl.x &= ~16;
    D_003C5510.fl.x &= ~32;
    D_003C5510.fl.x &= ~64;
    D_003C5510.fl.x &= ~128;
    D_003C5510.fl.x &= ~256;
    D_003C5510.fl.s.dur[0] = 0.0f;
    D_003C5510.fl.s.dur[1] = 0.0f;
    D_003C5510.fl.s.dur[2] = 0.0f;
    D_003C5510.fl.s.dur[3] = 0.0f;
    D_003C5510.p0[0][0] = 0.0f;
    D_003C5510.p0[0][1] = 0.0f;
    D_003C5510.p0[0][2] = 0.0f;
    D_003C5510.p0[0][3] = 1.0f;
    D_003C5510.p0[1][0] = 0.0f;
    D_003C5510.p0[1][1] = 0.0f;
    D_003C5510.p0[1][2] = 0.0f;
    D_003C5510.p0[1][3] = 0.0f;
    D_003C5510.p0[2][0] = 1000.0f;
    D_003C5510.p0[2][1] = 53.0f;
    D_003C5510.p1[0][0] = 0.0f;
    D_003C5510.p1[0][1] = 0.0f;
    D_003C5510.p1[0][2] = 0.0f;
    D_003C5510.p1[0][3] = 1.0f;
    D_003C5510.p1[1][0] = 0.0f;
    D_003C5510.p1[1][1] = 0.0f;
    D_003C5510.p1[1][2] = 0.0f;
    D_003C5510.p1[1][3] = 0.0f;
    D_003C5510.p1[2][0] = 1000.0f;
    D_003C5510.p1[2][1] = 53.0f;
    D_003C5510.pos[0] = 0.0f;
    D_003C5510.pos[1] = 0.0f;
    D_003C5510.pos[2] = 0.0f;
    D_003C5510.pos[3] = 1.0f;
    D_003C5510.rot[0] = 0.0f;
    D_003C5510.rot[1] = 0.0f;
    D_003C5510.rot[2] = 0.0f;
    D_003C5510.rot[3] = 0.0f;
    D_003C5510.v100[0] = 0.0f;
    D_003C5510.v100[1] = 0.0f;
    D_003C5510.v100[2] = 1.0f;
    D_003C5510.v100[3] = 1.0f;
    D_003C5510.v110[0] = 0.0f;
    D_003C5510.v110[1] = 1.0f;
    D_003C5510.v110[2] = 0.0f;
    D_003C5510.v110[3] = 1.0f;
    D_003C5510.f120 = 1000.0f;
    D_003C5510.f124 = 53.0f;
    func_001c6890();
    func_002675a8(&v, D_003C5510.rot);
    v.y += 3.1415928f;
    func_001e9fe8(&v, &v);
    D_003C5510.f128 = v.y;
}

/* Set the camera from the current view (D_002E2780 eye, D_002E2790
 * target, D_002E27A0, D_002E27A4 roll). */
void func_001c6890(void) {
    FVec4 a;
    f32 m[4][4] __attribute__((aligned(16)));
    FVec4 r;

    memset(&a, 0, 16);
    a.w = 1.0f;
    memset(&r, 0, 16);
    func_002675a8(&a, &D_002E2780);
    func_002675a8(D_003C5510.pos, &D_002E2790);
    D_003C5510.f120 = func_001e9e58(&a, D_003C5510.pos);
    D_003C5510.f124 = D_002E27A0;
    func_001e9d00(&r, D_003C5510.pos, &a, D_002E27A4);
    D_003C5510.v100[0] = 0.0f;
    D_003C5510.v100[1] = 0.0f;
    D_003C5510.v100[2] = 1.0f;
    D_003C5510.v100[3] = 1.0f;
    D_003C5510.v110[0] = 0.0f;
    D_003C5510.v110[1] = 1.0f;
    D_003C5510.v110[2] = 0.0f;
    D_003C5510.v110[3] = 1.0f;
    sceVu0UnitMatrix(m);
    func_00267768(m, m, r.x);
    func_00267810(m, m, r.y);
    func_002672f8(D_003C5510.v100, m, D_003C5510.v100);
    func_002672f8(&a, m, &a);
    func_002675a8(D_003C5510.rot, &r);
    sceVu0UnitMatrix(m);
    func_00267768(m, m, r.x);
    func_00267810(m, m, r.y);
    func_002676c0(m, m, r.z);
    func_002672f8(D_003C5510.v110, m, D_003C5510.v110);
}

/* Set the view from the camera. */
void func_001c6a20(void) {
    CamVec rot;
    f32 m[4][4] __attribute__((aligned(16)));
    CamVec v;
    CamVec t;
    memset(rot, 0, 16);
    memset(v, 0, 16);
    v[3] = 1.0f;
    memset(t, 0, 16);
    t[3] = 1.0f;
    func_001e9fe8(rot, D_003C55F0);
    if (rot[0] > 1.5707964f || rot[0] < -1.5707964f) {
        if (rot[2] < 0.0f) rot[2] = rot[2] + 3.1415928f;
        else rot[2] = rot[2] - 3.1415928f;
    }
    func_00124c68(D_003C5510.f124);
    D_003C5510.v100[0] = 0.0f;
    D_003C5510.v100[2] = 1.0f;
    D_003C5510.v100[1] = 0.0f;
    t[2] = D_003C5510.f120;
    D_003C5510.v100[3] = 1.0f;
    D_003C5510.v110[1] = 1.0f;
    D_003C5510.v110[3] = 1.0f;
    D_003C5510.v110[0] = 0.0f;
    D_003C5510.v110[2] = 0.0f;
    sceVu0UnitMatrix(m);
    func_00267768(m, m, D_003C5510.rx);
    func_00267810(m, m, D_003C5510.ry);
    func_002676c0(m, m, D_003C5510.rz);
    func_00267578(m, m, t);
    func_00267768(m, m, rot[0]);
    func_00267810(m, m, rot[1]);
    func_002676c0(m, m, 0.0f);
    func_002672f8(v, m, v);
    sceVu0UnitMatrix(m);
    func_00267768(m, m, rot[0]);
    func_00267810(m, m, rot[1]);
    func_002676c0(m, m, 0.0f);
    func_002672f8(D_003C5510.v100, m, D_003C5510.v100);
    v[0] = -v[0];
    v[1] = -v[1];
    v[2] = -v[2];
    sceVu0UnitMatrix(m);
    func_00267768(m, m, rot[0]);
    func_00267810(m, m, rot[1]);
    func_002676c0(m, m, rot[2]);
    func_002672f8(D_003C5510.v110, m, D_003C5510.v110);
    v[0] += D_003C5510.pos[0];
    v[1] += D_003C5510.pos[1];
    v[2] += D_003C5510.pos[2];
    func_002675a8(&D_002E2780.x, v);
    func_002675a8(&D_002E2790.x, D_003C5510.pos);
    D_002E27A4 = rot[2];
}

/* ---- The camera's script functions (entries of D_003D9FE0) ---- */

/* func_001c6d08, func_001c71e8, func_001c7700, func_001c7c18 (play camera
 * path k, following 0, 1 or 2 objects) are in camera.nostrict.c. */

/* Look at (x, y, z) from the current position. */
s32 func_001c8168(VmRec *vm) {
    FVec4 t, r;
    func_001c6890();
    t.x = vm->stk[vm->sp - 2];
    t.y = vm->stk[vm->sp - 1];
    t.z = vm->stk[vm->sp];
    D_003C5510.f120 = func_001e9e58(&t, D_003C5510.pos);
    func_001e9d00(&r, D_003C5510.pos, &t, D_003C5510.rot[2]);
    func_002675a8(D_003C5510.rot, &r);
    func_001c6a20();
    if ((s32)(D_003C5510.fl.x >> 8) & 1) func_002675a8(D_003C5510.base, D_003C5510.pos);
    vm->sp -= 3;
    return 2;
}

/* Set the position. */
s32 func_001c8260(VmRec *vm) {
    func_001c6890();
    D_003C5510.pos[0] = vm->stk[vm->sp - 2];
    D_003C5510.pos[1] = vm->stk[vm->sp - 1];
    D_003C5510.pos[2] = vm->stk[vm->sp];
    func_001c6a20();
    if ((s32)(D_003C5510.fl.x >> 8) & 1) func_002675a8(D_003C5510.base, D_003C5510.pos);
    vm->sp -= 3;
    return 2;
}

/* Set the rotation (degrees). */
s32 func_001c8308(VmRec *vm) {
    func_001c6890();
    D_003C5510.rot[0] = vm->stk[vm->sp - 2] / 180.0f * 3.1415928f;
    D_003C5510.rot[1] = vm->stk[vm->sp - 1] / 180.0f * 3.1415928f;
    D_003C5510.rot[2] = vm->stk[vm->sp] / 180.0f * 3.1415928f;
    func_001c6a20();
    vm->sp -= 3;
    return 2;
}

/* Set f120. */
s32 func_001c83c8(VmRec *vm) {
    func_001c6890();
    D_003C5510.f120 = vm->stk[vm->sp];
    func_001c6a20();
    vm->sp--;
    return 2;
}

/* Set f124. */
s32 func_001c8420(VmRec *vm) {
    func_001c6890();
    D_003C5510.f124 = vm->stk[vm->sp];
    func_001c6a20();
    vm->sp--;
    return 2;
}

/* Push the position x / y / z, the rotation (degrees), f120, f124. */
s32 func_001c8478(VmRec *vm) {
    f32 f;
    func_001c6890();
    f = D_003C5510.pos[0];
    vm->sp++;
    vm->stk[vm->sp] = f;
    return 2;
}

s32 func_001c84c8(VmRec *vm) {
    f32 f;
    func_001c6890();
    f = D_003C5510.pos[1];
    vm->sp++;
    vm->stk[vm->sp] = f;
    return 2;
}

s32 func_001c8518(VmRec *vm) {
    f32 f;
    func_001c6890();
    f = D_003C5510.pos[2];
    vm->sp++;
    vm->stk[vm->sp] = f;
    return 2;
}

s32 func_001c8568(VmRec *vm) {
    f32 f;
    func_001c6890();
    f = D_003C5510.rot[0] / 3.1415928f * 180.0f;
    vm->sp++;
    vm->stk[vm->sp] = f;
    return 2;
}

s32 func_001c85d8(VmRec *vm) {
    f32 f;
    func_001c6890();
    f = D_003C5510.rot[1] / 3.1415928f * 180.0f;
    vm->sp++;
    vm->stk[vm->sp] = f;
    return 2;
}

s32 func_001c8648(VmRec *vm) {
    f32 f;
    func_001c6890();
    f = D_003C5510.rot[2] / 3.1415928f * 180.0f;
    vm->sp++;
    vm->stk[vm->sp] = f;
    return 2;
}

s32 func_001c86b8(VmRec *vm) {
    f32 f;
    func_001c6890();
    f = D_003C5510.f120;
    vm->sp++;
    vm->stk[vm->sp] = f;
    return 2;
}

s32 func_001c8708(VmRec *vm) {
    f32 f;
    func_001c6890();
    f = D_003C5510.f124;
    vm->sp++;
    vm->stk[vm->sp] = f;
    return 2;
}

/* Channel 0, linear (bit 0): move the position, keeping what it looks at. */
void func_001c8758(void) {
    CamState *c = &D_003C5510;
    f32 *f = c->p0[0];
    f32 *t = c->p1[0];
    f32 *o = c->pos;
    FVec4 m, q;
    c->t[0] += D_002BBDFC;
    if (c->fl.s.dur[0] < c->t[0]) {
        c->t[0] = c->fl.s.dur[0];
        c->fl.x &= ~1;
    }
    func_001e9fe8(&q, c->rot);
    func_001e9f18(&m, o, &q, c->f120);
    o[0] = f[0] + (t[0] - f[0]) / c->fl.s.dur[0] * c->t[0];
    c->pos[1] = f[1] + (t[1] - f[1]) / c->fl.s.dur[0] * c->t[0];
    c->pos[2] = f[2] + (t[2] - f[2]) / c->fl.s.dur[0] * c->t[0];
    func_001c6a20();
}

/* Start channel 0, linear: to (x, y, z) in n frames. */
s32 func_001c8878(VmRec *vm) {
    f32 d;
    func_001c6890();
    D_003C5510.fl.x |= 1;
    D_003C5510.p0[0][0] = D_003C5510.pos[0];
    D_003C5510.p0[0][1] = D_003C5510.pos[1];
    D_003C5510.p0[0][2] = D_003C5510.pos[2];
    d = vm->stk[vm->sp - 3] * 2.0f;
    D_003C5510.p1[0][0] = vm->stk[vm->sp - 2];
    D_003C5510.p1[0][1] = vm->stk[vm->sp - 1];
    D_003C5510.p1[0][2] = vm->stk[vm->sp];
    D_003C5510.t[0] = 0.0f;
    vm->sp -= 4;
    D_003C5510.fl.s.dur[0] = d;
    return 2;
}

static inline void inl_lerp2(f32 *f, f32 *t, f32 d, f32 s) {
    D_003C5510.rot[0] = f[0] + (t[0] - f[0]) / d * s;
    D_003C5510.rot[1] = f[1] + (t[1] - f[1]) / d * s;
    D_003C5510.rot[2] = f[2] + (t[2] - f[2]) / d * s;
}

/* Channel 1, linear (bit 1): the rotation. */
void func_001c8930(void) {
    CamState *c = &D_003C5510;
    c->t[1] += D_002BBDFC;
    if (c->fl.s.dur[1] < c->t[1]) {
        c->t[1] = c->fl.s.dur[1];
        c->fl.x &= ~2;
    }
    inl_lerp2(c->p0[1], c->p1[1], c->fl.s.dur[1], c->t[1]);
    do { func_001c6a20(); } while (0);
}

#define WRAP(a) while (1) { if (a > 3.1415928f) a -= 6.2831855f; else if (a < -3.1415928f) a += 6.2831855f; else break; }
/* Start channel 1, linear: to (x, y, z) degrees in n frames. */
s32 func_001c8a00(VmRec *vm) {
    f32 x, y, z, f;
    s32 sp;
    func_001c6890();
    D_003C5510.fl.x |= 2;
    D_003C5510.t[1] = 0;
    sp = vm->sp;
    x = vm->stk[sp - 2];
    y = vm->stk[sp - 1];
    f = vm->stk[sp - 3];
    z = vm->stk[sp];
    D_003C5510.p1[1][0] = x / 180.0f * 3.1415928f;
    D_003C5510.p1[1][1] = y / 180.0f * 3.1415928f;
    D_003C5510.p1[1][2] = z / 180.0f * 3.1415928f;
    D_003C5510.fl.s.dur[1] = f * 2.0f;
    WRAP(D_003C5510.p1[1][0]);
    WRAP(D_003C5510.p1[1][1]);
    WRAP(D_003C5510.p1[1][2]);
    D_003C5510.p0[1][0] = D_003C5510.rot[0];
    D_003C5510.p0[1][1] = D_003C5510.rot[1];
    D_003C5510.p0[1][2] = D_003C5510.rot[2];
    vm->sp = sp - 4;
    return 2;
}
#undef WRAP

/* Channel 2, linear (bit 2): f120. */
void func_001c8c10(void) {
    CamState *p = &D_003C5510;
    p->t[2] += D_002BBDFC;
    if (p->fl.s.dur[2] < p->t[2]) {
        p->t[2] = p->fl.s.dur[2];
        p->fl.x &= ~4;
    }
    p->f120 = p->p0[2][0] + (p->p1[2][0] - p->p0[2][0]) / p->fl.s.dur[2] * p->t[2];
    do { func_001c6a20(); break; } while (1);
}

/* func_001c8c90 (start channel 2, linear) is in camera.nostrict.c. */

/* Channel 3, linear (bit 3): f124. */
void func_001c8d18(void) {
    CamState *p = &D_003C5510;
    p->t[3] += D_002BBDFC;
    if (p->fl.s.dur[3] < p->t[3]) {
        p->t[3] = p->fl.s.dur[3];
        p->fl.x &= ~8;
    }
    p->f124 = p->p0[2][1] + (p->p1[2][1] - p->p0[2][1]) / p->fl.s.dur[3] * p->t[3];
    do { func_001c6a20(); break; } while (1);
}

/* func_001c8d98 (start channel 3, linear) is in camera.nostrict.c. */

s32 rand(void);
void func_00267518(void *d, void *a, void *b);

/* Bit 8, run as a task while set: shake the camera around `base` by
 * random offsets up to amp, scaled by smode's envelope over sdur frames. */
s32 func_001c8e20(void) {
    CamVec v;
    f32 m[4][4] __attribute__((aligned(16)));
    CamVec rot;
    f32 x, y, z, k;
    z = x = y = 0.0f;
    func_001c6890();
    switch (D_003C5510.smode) {
    case 0:
        x = (f32)rand() / 2147483647.0f * D_003C5510.amp[0]; x -= D_003C5510.amp[0] * 0.5f;
        y = (f32)rand() / 2147483647.0f * D_003C5510.amp[1]; y -= D_003C5510.amp[1] * 0.5f;
        z = (f32)rand() / 2147483647.0f * D_003C5510.amp[2]; z -= D_003C5510.amp[2] * 0.5f;
        break;
    case 1:
        k = D_003C5510.st / D_003C5510.sdur;
        if (0.5f < k) k = (1.0f - k) * 2.0f;
        else k = k * 2.0f;
        x = (f32)rand() / 2147483647.0f * D_003C5510.amp[0]; x -= D_003C5510.amp[0] * 0.5f; x *= k;
        y = (f32)rand() / 2147483647.0f * D_003C5510.amp[1]; y -= D_003C5510.amp[1] * 0.5f; y *= k;
        z = (f32)rand() / 2147483647.0f * D_003C5510.amp[2]; z -= D_003C5510.amp[2] * 0.5f; z *= k;
        break;
    case 2:
        k = D_003C5510.st / D_003C5510.sdur;
        x = (f32)rand() / 2147483647.0f * D_003C5510.amp[0]; x -= D_003C5510.amp[0] * 0.5f; x *= k;
        y = (f32)rand() / 2147483647.0f * D_003C5510.amp[1]; y -= D_003C5510.amp[1] * 0.5f; y *= k;
        z = (f32)rand() / 2147483647.0f * D_003C5510.amp[2]; z -= D_003C5510.amp[2] * 0.5f; z *= k;
        break;
    case 3:
        k = 1.0f - D_003C5510.st / D_003C5510.sdur;
        x = (f32)rand() / 2147483647.0f * D_003C5510.amp[0]; x -= D_003C5510.amp[0] * 0.5f; x *= k;
        y = (f32)rand() / 2147483647.0f * D_003C5510.amp[1]; y -= D_003C5510.amp[1] * 0.5f; y *= k;
        z = (f32)rand() / 2147483647.0f * D_003C5510.amp[2]; z -= D_003C5510.amp[2] * 0.5f; z *= k;
        break;
    }
    func_001e9fe8(rot, D_003C5510.rot);
    v[0] = x;
    v[1] = y;
    v[2] = z;
    v[3] = 1.0f;
    sceVu0UnitMatrix(m);
    func_00267768(m, m, rot[0]);
    func_00267810(m, m, rot[1]);
    func_002672f8(v, m, v);
    func_00267518(D_003C5510.pos, D_003C5510.base, v);
    func_001c6a20();
    D_003C5510.st += D_002BBDFC;
    if (D_003C5510.sdur <= D_003C5510.st) {
        D_003C5510.fl.s.b8 = 0;
        func_002675a8(D_003C5510.pos, D_003C5510.base);
    }
    return 4;
}

/* Start (n > 0) or stop the shake: amplitude (x, y, z), envelope, n frames. */
s32 func_001c91e8(VmRec *vm) {
    if (vm->stk[vm->sp] > 0) {
        func_001c6890();
        D_003C5510.st = 0;
        D_003C5510.fl.x |= 0x100;
        D_003C5510.amp[0] = vm->stk[vm->sp - 4];
        D_003C5510.amp[1] = vm->stk[vm->sp - 3];
        D_003C5510.amp[2] = vm->stk[vm->sp - 2];
        D_003C5510.smode = vm->stk[vm->sp - 1];
        D_003C5510.sdur = vm->stk[vm->sp] * 2.0f;
        func_002675a8(D_003C5510.base, D_003C5510.pos);
    } else {
        D_003C5510.fl.x &= ~0x100;
    }
    vm->sp -= 5;
    return 2;
}

extern u64 D_0038CD00;

/* Wait while D_0038CD00 bit 37 (a camera path playing) is set. */
s32 func_001c92e8(void) {
    return ((u32)(D_0038CD00 >> 37) & 1) ? 4 : 2;
}

/* Channel 0, curved (bit 4): the position, Hermite from p0 to p1 with the
 * end tangents mode[0] picks. */
void func_001c9308(void) {
    f32 a[4];
    f32 b[4];
    s32 i;
    f32 s, u, u2, u3, d;
    f32 *p0, *p1;
    for (i = 0; i < 3; i++) {
        a[i] = 0.0f;
        b[i] = 0.0f;
    }
    D_003C5510.t[0] += D_002BBDFC;
    p0 = D_003C5510.p0[0];
    p1 = D_003C5510.p1[0];
    switch (D_003C5510.mode[0]) {
    case 0:
    case 3:
        s = D_003C5510.fl.s.dur[0];
        for (i = 0; i < 3; i++) a[i] = (p1[i] - p0[i]) / s;
        break;
    case 1:
    case 2:
        for (i = 2; i >= 0; i--) a[i] = 0.0f;
        break;
    }
    switch (D_003C5510.mode[0]) {
    case 0:
    case 2:
        s = D_003C5510.fl.s.dur[0];
        for (i = 0; i < 3; i++) b[i] = (p1[i] - p0[i]) / s;
        break;
    case 1:
    case 3:
        for (i = 2; i >= 0; i--) b[i] = 0.0f;
        break;
    }
    s = 0.0f;
    if (D_003C5510.t[0] == s) {
        D_003C5510.pos[0] = p0[0];
        D_003C5510.pos[1] = p0[1];
        D_003C5510.pos[2] = p0[2];
    } else if (D_003C5510.fl.s.dur[0] <= D_003C5510.t[0]) {
        D_003C5510.pos[0] = p1[0];
        D_003C5510.pos[1] = p1[1];
        D_003C5510.pos[2] = p1[2];
    } else {
        d = D_003C5510.fl.s.dur[0] - s;
        u = (D_003C5510.t[0] - s) / d;
        u2 = u * u;
        u3 = u * u2;
        for (i = 0; i < 3; i++) {
            D_003C5510.pos[i] = (2.0f * u3 - 3.0f * u2 + 1.0f) * p0[i]
                + (-2.0f * u3 + 3.0f * u2) * p1[i]
                + ((u3 - 2.0f * u2 + u) * a[i] + (u3 - u2) * b[i]) * d;
        }
    }
    func_001c6a20();
    if (D_003C5510.t[0] > D_003C5510.fl.s.dur[0]) D_003C5510.fl.s.b4 = 0;
}

/* Start channel 0, curved: to (x, y, z), mode, in n frames. */
s32 func_001c95f8(VmRec *vm) {
    f32 d;
    func_001c6890();
    D_003C5510.fl.x |= 0x10;
    D_003C5510.p0[0][0] = D_003C5510.pos[0];
    D_003C5510.p0[0][1] = D_003C5510.pos[1];
    D_003C5510.p0[0][2] = D_003C5510.pos[2];
    d = vm->stk[vm->sp - 4] * 2.0f;
    D_003C5510.mode[0] = vm->stk[vm->sp - 3];
    D_003C5510.t[0] = 0.0f;
    D_003C5510.p1[0][0] = vm->stk[vm->sp - 2];
    D_003C5510.p1[0][1] = vm->stk[vm->sp - 1];
    D_003C5510.p1[0][2] = vm->stk[vm->sp];
    vm->sp -= 5;
    { f32 *p = &D_003C5510.fl.s.dur[0]; *p = d; }
    return 2;
}

/* Channel 1, curved (bit 5): the rotation. */
void func_001c96c0(void) {
    f32 a[4];
    f32 b[4];
    s32 i;
    f32 s, u, u2, u3, d;
    f32 *p0, *p1;
    for (i = 0; i < 3; i++) {
        a[i] = 0.0f;
        b[i] = 0.0f;
    }
    D_003C5510.t[1] += D_002BBDFC;
    p0 = D_003C5510.p0[1];
    p1 = D_003C5510.p1[1];
    s = D_003C5510.fl.s.dur[1];
    switch (D_003C5510.mode[1]) {
    case 0:
    case 3:
        for (i = 0; i < 3; i++) a[i] = (p1[i] - p0[i]) / s;
        break;
    case 1:
    case 2:
        for (i = 2; i >= 0; i--) a[i] = 0.0f;
        break;
    }
    switch (D_003C5510.mode[1]) {
    case 0:
    case 2:
        s = D_003C5510.fl.s.dur[1];
        for (i = 0; i < 3; i++) b[i] = (p1[i] - p0[i]) / s;
        break;
    case 1:
    case 3:
        for (i = 2; i >= 0; i--) b[i] = 0.0f;
        break;
    }
    s = 0.0f;
    if (D_003C5510.t[1] == s) {
        D_003C5510.rot[0] = p0[0];
        D_003C5510.rot[1] = p0[1];
        D_003C5510.rot[2] = p0[2];
    } else if (D_003C5510.fl.s.dur[1] <= D_003C5510.t[1]) {
        D_003C5510.rot[0] = p1[0];
        D_003C5510.rot[1] = p1[1];
        D_003C5510.rot[2] = p1[2];
    } else {
        d = D_003C5510.fl.s.dur[1] - s;
        u = (D_003C5510.t[1] - s) / d;
        u2 = u * u;
        u3 = u * u2;
        for (i = 0; i < 3; i++) {
            D_003C5510.rot[i] = (2.0f * u3 - 3.0f * u2 + 1.0f) * p0[i]
                + (-2.0f * u3 + 3.0f * u2) * p1[i]
                + ((u3 - 2.0f * u2 + u) * a[i] + (u3 - u2) * b[i]) * d;
        }
    }
    func_001c6a20();
    if (D_003C5510.t[1] > D_003C5510.fl.s.dur[1]) D_003C5510.fl.s.b5 = 0;
}

/* Start channel 1, curved: to (x, y, z) degrees, mode, in n frames. */
s32 func_001c99a8(VmRec *vm) {
    s32 m;
    f32 d;
    func_001c6890();
    D_003C5510.fl.w.b5 = 1;
    m = vm->stk[vm->sp - 3];
    d = (f32)vm->stk[vm->sp - 4] * 2.0f;
    D_003C5510.mode[1] = m;
    D_003C5510.p1[1][0] = vm->stk[vm->sp - 2] * 3.1415928f / 180.0f;
    D_003C5510.p1[1][1] = vm->stk[vm->sp - 1] * 3.1415928f / 180.0f;
    D_003C5510.p1[1][2] = vm->stk[vm->sp] * 3.1415928f / 180.0f;
    (&D_003C5510.fl.s)->dur[1] = d; /* through a pointer: a direct store through the union gets alias set 0 */
    func_001e9fe8(D_003C5510.p1[1], D_003C5510.p1[1]);
    D_003C5510.p0[1][0] = D_003C5510.rot[0];
    D_003C5510.p0[1][1] = D_003C5510.rot[1];
    D_003C5510.p0[1][2] = D_003C5510.rot[2];
    vm->sp -= 5;
    return 2;
}

/* Channel 2, curved (bit 6): f120. */
void func_001c9ac8(void) {
    f32 t0, t1, a, u, u2, u3, d;
    f32 *s, *e;
    t1 = t0 = 0.0f;
    D_003C5510.t[2] += D_002BBDFC;
    s = &D_003C5510.p0[2][0];
    e = &D_003C5510.p1[2][0];
    switch (D_003C5510.mode[2]) {
    case 0:
    case 3:
        t0 = (*e - *s) / D_003C5510.fl.s.dur[2];
        break;
    case 1:
    case 2:
        break;
    }
    switch (D_003C5510.mode[2]) {
    case 0:
    case 2:
        t1 = (*e - *s) / D_003C5510.fl.s.dur[2];
        break;
    case 1:
    case 3:
        t1 = 0.0f;
        break;
    }
    a = 0.0f;
    if (D_003C5510.t[2] == a) {
        D_003C5510.f120 = *s;
    } else if (D_003C5510.fl.s.dur[2] <= D_003C5510.t[2]) {
        D_003C5510.f120 = *e;
    } else {
        d = D_003C5510.fl.s.dur[2] - a;
        u = (D_003C5510.t[2] - a) / d;
        u2 = u * u;
        u3 = u * u2;
        D_003C5510.f120 = ((u3 + u3) - u2 * 3.0f + 1.0f) * *s
            + (u3 * -2.0f + u2 * 3.0f) * *e
            + ((u3 - (u2 + u2) + u) * t0 + (u3 - u2) * t1) * d;
    }
    func_001c6a20();
    if (D_003C5510.t[2] > D_003C5510.fl.s.dur[2]) D_003C5510.fl.x &= ~64;
}

/* func_001c9ca8 (start channel 2, curved) is in camera.nostrict.c. */

extern f32 D_0036266C;

/* Channel 4 (bit 9): D_0036266C, linear. */
void func_001c9d40(void) {
    CamState *p = &D_003C5510;
    p->t[4] += D_002BBDFC;
    if (p->fl.s.dur[4] < p->t[4]) {
        p->fl.x &= ~0x200;
        D_0036266C = p->p1[2][2];
        return;
    }
    D_0036266C = (p->p1[2][2] - p->p0[2][2]) * (p->t[4] / p->fl.s.dur[4]);
}

/* Start channel 4: from D_0036266C (saved in f12c) to v in n frames. */
s32 func_001c9db0(VmRec *vm) {
    f32 f, a, b;
    s32 sp;
    D_003C5510.fl.x |= 0x200;
    D_003C5510.t[4] = 0;
    f = D_0036266C;
    D_003C5510.p0[2][2] = f;
    D_003C5510.f12c = f;
    sp = vm->sp;
    a = vm->stk[sp - 1];
    b = vm->stk[sp];
    vm->sp = sp - 2;
    D_003C5510.p1[2][2] = b;
    D_003C5510.fl.s.dur[4] = a * 2.0f;
    return 2;
}

/* Start channel 4: back to the saved value in n frames. */
s32 func_001c9e20(VmRec *vm) {
    f32 a;
    s32 sp;
    D_003C5510.fl.x |= 0x200;
    D_003C5510.p1[2][2] = D_003C5510.f12c;
    D_003C5510.p0[2][2] = D_0036266C;
    D_003C5510.t[4] = 0;
    sp = vm->sp;
    a = vm->stk[sp];
    vm->sp = sp - 1;
    D_003C5510.fl.s.dur[4] = a * 2.0f;
    return 2;
}

/* Channel 3, curved (bit 7): f124. */
void func_001c9e80(void) {
    f32 t0, t1, a, u, u2, u3, d;
    f32 *s, *e;
    t1 = t0 = 0.0f;
    D_003C5510.t[3] += D_002BBDFC;
    s = &D_003C5510.p0[2][1];
    e = &D_003C5510.p1[2][1];
    switch (D_003C5510.mode[3]) {
    case 0:
    case 3:
        t0 = (*e - *s) / D_003C5510.fl.s.dur[3];
        break;
    case 1:
    case 2:
        break;
    }
    switch (D_003C5510.mode[0]) {
    case 0:
    case 2:
        t1 = (*e - *s) / D_003C5510.fl.s.dur[3];
        break;
    case 1:
    case 3:
        t1 = 0.0f;
        break;
    }
    a = 0.0f;
    if (D_003C5510.t[3] == a) {
        D_003C5510.f124 = *s;
    } else if (D_003C5510.fl.s.dur[3] <= D_003C5510.t[3]) {
        D_003C5510.f124 = *e;
    } else {
        d = D_003C5510.fl.s.dur[3] - a;
        u = (D_003C5510.t[3] - a) / d;
        u2 = u * u;
        u3 = u * u2;
        D_003C5510.f124 = ((u3 + u3) - u2 * 3.0f + 1.0f) * *s
            + (u3 * -2.0f + u2 * 3.0f) * *e
            + ((u3 - (u2 + u2) + u) * t0 + (u3 - u2) * t1) * d;
    }
    func_001c6a20();
    if (D_003C5510.t[3] > D_003C5510.fl.s.dur[3]) D_003C5510.fl.x &= ~128;
}

/* func_001ca060 (start channel 3, curved) is in camera.nostrict.c. */

void func_00177900(f32 *, f32 *, f32);

/* Move the camera to the view func_00177900 gives for angle a: at once
 * (n == 0) or by curved tweens of channels 0-3 over n frames.  Here and in
 * func_001ca368 the durations are stored through a pointer to fl.s: a
 * direct store through the union gets alias set 0, which changes the
 * delay slot filling (bnel for bne) and the store order. */
s32 func_001ca0f8(VmRec *vm) {
    CamVec a;
    CamVec b;
    CamVec c;
    f32 f;
    f32 v;
    f = vm->stk[vm->sp];
    func_00177900(a, b, vm->stk[vm->sp - 2] * 3.1415928f / 180.0f);
    if (vm->stk[vm->sp] == 0) {
        func_002675a8(&D_002E2780, a);
        func_002675a8(&D_002E2790, b);
        vm->sp -= 3;
        return 2;
    }
    func_001c6890();
    f += f;
    D_003C5510.fl.s.b4 = 1;
    (&D_003C5510.fl.s)->dur[0] = f;
    D_003C5510.mode[0] = vm->stk[vm->sp - 1];
    D_003C5510.fl.s.b5 = 1;
    D_003C5510.p1[0][0] = b[0];
    D_003C5510.p1[0][1] = b[1];
    D_003C5510.p1[0][2] = b[2];
    D_003C5510.p0[0][0] = D_003C5510.pos[0];
    D_003C5510.p0[0][1] = D_003C5510.pos[1];
    D_003C5510.p0[0][2] = D_003C5510.pos[2];
    D_003C5510.mode[1] = vm->stk[vm->sp - 1];
    D_003C5510.t[0] = 0.0f;
    (&D_003C5510.fl.s)->dur[1] = f;
    func_001e9d00(c, b, a, D_003C5510.rot[2]);
    D_003C5510.fl.s.b6 = 1;
    D_003C5510.p1[1][0] = c[0];
    D_003C5510.p1[1][1] = c[1];
    D_003C5510.p0[1][0] = D_003C5510.rot[0];
    D_003C5510.p0[1][1] = D_003C5510.rot[1];
    D_003C5510.mode[2] = vm->stk[vm->sp - 1];
    D_003C5510.p1[1][2] = 0.0f;
    D_003C5510.p0[1][2] = 0.0f;
    D_003C5510.t[1] = 0.0f;
    (&D_003C5510.fl.s)->dur[2] = f;
    v = func_001e9e58(b, a);
    D_003C5510.p0[2][0] = D_003C5510.f120;
    (&D_003C5510.fl.s)->dur[3] = f;
    D_003C5510.p1[2][1] = 53.0f;
    D_003C5510.fl.s.b7 = 1;
    D_003C5510.t[3] = 0.0f;
    D_003C5510.mode[3] = vm->stk[vm->sp - 1];
    D_003C5510.t[2] = 0.0f;
    D_00389C90.f3070.w.b37 = 0;
    D_003C5510.p0[2][1] = D_003C5510.f124;
    D_003C5510.p1[2][0] = v;
    vm->sp -= 3;
    return 2;
}

/* The same towards the view at f128, over n frames, the yaw taking the
 * short way round. */
s32 func_001ca368(VmRec *vm) {
    CamVec a;
    CamVec b;
    CamVec c;
    f32 f;
    f32 v;
    f32 d;
    s32 n = vm->stk[vm->sp];
    func_00177900(a, b, D_003C5510.f128);
    func_001c6890();
    D_003C5510.fl.s.b4 = 1;
    (&D_003C5510.fl.s)->dur[0] = n * 2.0f;
    D_003C5510.mode[0] = vm->stk[vm->sp - 1];
    D_003C5510.fl.s.b5 = 1;
    D_003C5510.p1[0][0] = b[0];
    D_003C5510.p1[0][1] = b[1];
    D_003C5510.p1[0][2] = b[2];
    D_003C5510.p0[0][0] = D_003C5510.pos[0];
    D_003C5510.p0[0][1] = D_003C5510.pos[1];
    D_003C5510.p0[0][2] = D_003C5510.pos[2];
    D_003C5510.mode[1] = vm->stk[vm->sp - 1];
    D_003C5510.t[0] = 0.0f;
    (&D_003C5510.fl.s)->dur[1] = n * 2.0f;
    func_001e9d00(c, b, a, D_003C5510.rot[2]);
    D_003C5510.p1[1][0] = c[0];
    D_003C5510.p1[1][1] = c[1];
    D_003C5510.p1[1][2] = 0.0f;
    func_001e9fe8(c, D_003C5510.rot);
    D_003C5510.p0[1][0] = c[0];
    D_003C5510.p0[1][1] = c[1];
    D_003C5510.p0[1][2] = 0.0f;
    d = c[1] - D_003C5510.p1[1][1];
    if (3.1415928f < d) D_003C5510.p0[1][1] = c[1] - 6.2831855f;
    else if (d < -3.1415928f) D_003C5510.p0[1][1] = c[1] + 6.2831855f;
    D_003C5510.fl.s.b6 = 1;
    D_003C5510.t[1] = 0.0f;
    (&D_003C5510.fl.s)->dur[2] = n * 2.0f;
    D_003C5510.mode[2] = vm->stk[vm->sp - 1];
    v = func_001e9e58(b, a);
    D_003C5510.fl.s.b7 = 1;
    D_003C5510.p1[2][0] = v;
    D_003C5510.p0[2][0] = D_003C5510.f120;
    D_003C5510.mode[3] = vm->stk[vm->sp - 1];
    D_00389C90.f3070.w.b37 = 0;
    (&D_003C5510.fl.s)->dur[3] = n * 2.0f;
    D_003C5510.p1[2][1] = 53.0f;
    D_003C5510.p0[2][1] = D_003C5510.f124;
    D_003C5510.t[2] = 0.0f;
    D_003C5510.t[3] = 0.0f;
    vm->sp -= 2;
    return 2;
}

/* Push x / y / z of the point the camera looks at (f120 along the rotation
 * from the position), all addressed from D_003C55F0. */
s32 func_001ca5f8(VmRec *vm) {
    FVec4 out, tmp;
    CamVec *b = &D_003C55F0;
    func_001c6890();
    func_001e9fe8(&tmp, b);
    func_001e9f18(&out, b - 1, &tmp, b[4][0]);
    vm->sp++;
    vm->stk[vm->sp] = out.x;
    return 2;
}

s32 func_001ca680(VmRec *vm) {
    FVec4 out, tmp;
    CamVec *b = &D_003C55F0;
    func_001c6890();
    func_001e9fe8(&tmp, b);
    func_001e9f18(&out, b - 1, &tmp, b[4][0]);
    vm->sp++;
    vm->stk[vm->sp] = out.y;
    return 2;
}

s32 func_001ca708(VmRec *vm) {
    FVec4 out, tmp;
    CamVec *b = &D_003C55F0;
    func_001c6890();
    func_001e9fe8(&tmp, b);
    func_001e9f18(&out, b - 1, &tmp, b[4][0]);
    vm->sp++;
    vm->stk[vm->sp] = out.z;
    return 2;
}

s32 func_0017e8c8(void);
s32 func_0017e910(void);

/* Unless D_002C5958 bit 1: func_0017e8c8 / func_0017e910. */
s32 func_001ca790(void) {
    if (!((D_002C5958 >> 1) & 1)) {
        func_0017e8c8();
    }
    return 2;
}

s32 func_001ca7c8(void) {
    if (!((D_002C5958 >> 1) & 1)) {
        func_0017e910();
    }
    return 2;
}

#define B(n) ((s32)(D_003C5510.fl.x >> (n)) & 1)
/* Every frame: start the path player if D_0038CD00 bit 37 is set, then run
 * the tweens whose bits are set. */
void func_001ca800(void) {
    if ((u32)(D_0038CD00 >> 37) % 2 == 1) {
        func_0011ef10(99999, func_001c5b88);
    }
    if (B(0)) {
        func_001c8758();
        if (B(8)) {
            func_002675a8(D_003C5510.base, D_003C5510.pos);
        }
    }
    if (B(4)) {
        func_001c9308();
        if (B(8)) {
            func_002675a8(D_003C5510.base, D_003C5510.pos);
        }
    }
    if (B(1)) func_001c8930();
    if (B(5)) func_001c96c0();
    if (B(2)) func_001c8c10();
    if (B(6)) func_001c9ac8();
    if (B(3)) func_001c8d18();
    if (B(7)) func_001c9e80();
    if (B(8)) func_0011ef10(99999, func_001c8e20);
    if (B(9)) func_001c9d40();
}
#undef B

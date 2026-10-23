/* The event camera, 0x001c5168-0x001c6d08 (include/camera/camera.h,
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
 * The script functions that drive the camera (0x001c6d08-0x001ca9e8) call
 * these and are the next part of this module. */
#include "common.h"
#include "camera/camera.h"
#include "vm/vm_mgr.h"
#include "data/types/fvec.h"
#include "data/pieces/D_0037A380.h"
#include "data/pieces/D_002E2780.h"
#include "data/pieces/D_002E2790.h"
#include "data/pieces/D_002E27A4.h"
#include "data/pieces/D_002BBDFC.h"

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

static inline void cp_q(CamV4q *d, CamV4q *a) {
    *d = *a;
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
        cp_q((CamV4q *)D_003C5510.pos, (CamV4q *)&c->a);
        cp_q((CamV4q *)D_003C5510.rot, (CamV4q *)&c->d);
        cp_q((CamV4q *)&D_003C5510.rx, (CamV4q *)&c->e);
        cp_q((CamV4q *)D_003C5510.v110, (CamV4q *)&c->c);
        cp_q((CamV4q *)D_003C5510.v100, (CamV4q *)&c->b);
        D_003C5510.f120 = c->f60;
        D_003C5510.f124 = c->fE0F4;
        func_001c6a20();
        g->f3070.x &= ~(1ULL << 37);
    } else {
        func_001c53c8(t);
        cp_q((CamV4q *)D_003C5510.pos, (CamV4q *)&c->a);
        cp_q((CamV4q *)D_003C5510.rot, (CamV4q *)&c->d);
        cp_q((CamV4q *)&D_003C5510.rx, (CamV4q *)&c->e);
        cp_q((CamV4q *)D_003C5510.v110, (CamV4q *)&c->c);
        cp_q((CamV4q *)D_003C5510.v100, (CamV4q *)&c->b);
        D_003C5510.f120 = c->f60;
        D_003C5510.f124 = c->fE0F4;
        func_001c6a20();
        if ((s32)(D_003C5510.fl.x >> 8) & 1) func_002675a8(D_003C5510.base, D_003C5510.pos);
    }
    return 4;
}

static inline void cp_v(V4_37A380 *d, V4_37A380 *s) {
    *d = *s;
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
    cp_v((V4_37A380 *)D_003C5510.pos, &CAM.a);
    cp_v((V4_37A380 *)D_003C5510.rot, &CAM.d);
    cp_v((V4_37A380 *)&D_003C5510.rx, &CAM.e);
    cp_v((V4_37A380 *)D_003C5510.v110, &CAM.c);
    cp_v((V4_37A380 *)D_003C5510.v100, &CAM.b);
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

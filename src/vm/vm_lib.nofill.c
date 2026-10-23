/* The library functions of src/vm/vm_lib.c that need nofill (docs/modules.md
 * "Session 32"). */
#include "common.h"
#include "vm/vm_obj.h"
#include "vm/script_vm.h"
#include "vm/vm_mgr.h"
#include "data/pieces/D_0037A378.h"
#include "data/pieces/D_0038D170.h"
#include "data/pieces/D_0039A580.h"
#include "data/data_0039.h"
#include "data/data_003A.h"
#include "data/pieces/D_002BBDFC.h"


/* func_001cd2d8 (session 9, w7) matched with this message view: u32 val:24
 * (VmMsg's u64 bit-field reads differently in `vm->f20 = m.val`), aligned(8),
 * m.type = 2 as a constant, the dead `d = f * 180 / pi; if (d < 0) d = -d;
 * g = d;` tail (only the libcall compare stays), and vm->sp -= 4 after the
 * f60 / f64 stores.  Written like its sibling func_001d5b58. */
typedef struct { u8 type; u32 val:24; s32 x; s32 a8; s32 ac; f32 v[4]; } __attribute__((aligned(8))) Msg2;
double sqrt(double);
double atan2(double, double);
extern VmFx *D_0038CD3C[];

/* Send message 2 (turn towards the point stk[sp-2..sp]). */
s32 func_001cd2d8(VmRec *vm) {
    Msg2 m;
    f32 v[3];
    f32 len, a, f, g;
    double d;
    vm->fl.x |= 1;
    v[0] = (f32)vm->stk[vm->sp - 2] - vm->obj->pos[0];
    v[1] = (f32)vm->stk[vm->sp - 1] - vm->obj->pos[1];
    v[2] = (f32)vm->stk[vm->sp] - vm->obj->pos[2];
    len = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);

    v[2] /= len;
    v[0] /= len;
    v[1] /= len;

    a = atan2(v[2], v[0]);
    d = a - (f32)atan2(vm->obj->rot[2], vm->obj->rot[0]);
    if (d < 0.0) d = -d;
    f = d;
    if (3.1415928f < f) f = 3.1415928f - (f - 3.1415928f);
    d = f * 180.0f / 3.1415928f;
    if (d < 0.0) d = -d;
    g = d;

    m.type = 2;
    m.val = vm->stk[vm->sp - 3];
    m.v[0] = vm->stk[vm->sp - 2];
    m.x = vm->x0;
    m.v[1] = vm->stk[vm->sp - 1];
    m.v[2] = vm->stk[vm->sp];
    m.v[3] = 179.99998f;

    func_001c4640((VmMsg *)&m);
    vm->f14[0] = m.v[0];
    vm->f14[1] = m.v[1];
    vm->f14[2] = m.v[2];
    vm->f20 = m.val;
    vm->f60 = 0;
    vm->f64 = 0;
    vm->sp -= 4;
    return 2;
}

/* The fade of effect D_0038CD3C[stk[sp-1]]: 1 - stk[sp] / 180. */
s32 func_001cede8(VmRec *vm) {
    s32 sp = vm->sp;
    VmFx *p = D_0038CD3C[vm->stk[sp - 1]];
    p->f0c = 1.0 - vm->stk[sp] / 180.0f;
    vm->sp = sp - 2;
    return 2;
}

/* The message of func_001d1080: VmMsg with the step d after v. */
typedef struct {
    u8 type;
    u64 val:24;
    s32 x;
    s32 a8;
    s32 ac;
    f32 v[4];
    f32 d[3];
} VmMsgD;

/* Step the move func_001d1230 / func_001d12b8 started: from p towards f14 by
 * f20 a frame (message 3), and clear flag bit 6 on arrival. */
void func_001d1080(VmRec *vm) {
    VmMsgD m;
    f32 dx, dy, dz, dist, spd;
    dx = vm->f14[0] - vm->p[0];
    dy = vm->f14[1] - vm->p[1];
    dz = vm->f14[2] - vm->p[2];
    dist = sqrt(dx * dx + dy * dy + dz * dz);
    spd = vm->f20;
    if (dist < spd) {
        m.type = 3;
        m.val = 0;
        m.x = vm->x0;
        m.v[0] = vm->f14[0];
        m.v[1] = vm->f14[1];
        m.v[2] = vm->f14[2];
        m.v[3] = 1.0f;
        func_001c4640((VmMsg *)&m);
        vm->fl.x &= ~0x40ULL;
    } else {
        m.type = 3;
        m.val = 0;
        m.x = vm->x0;
        m.v[3] = 1.0f;
        m.d[0] = (vm->f14[0] - vm->p[0]) / dist * spd;
        m.d[1] = (vm->f14[1] - vm->p[1]) / dist * spd;
        m.d[2] = (vm->f14[2] - vm->p[2]) / dist * spd;
        vm->p[0] += m.d[0];
        vm->p[1] += m.d[1];
        vm->p[2] += m.d[2];
        m.v[0] = vm->p[0];
        m.v[1] = vm->p[1];
        m.v[2] = vm->p[2];
        func_001c4640((VmMsg *)&m);
    }
}

/* The distance functions: from stk[sp-3..] or between the entities of VMs
 * stk[sp-1] and stk[sp]; func_001d17d0 / func_001d1948 / func_001d1b00 /
 * func_001d1ce0 store it in the story variable D_003888C4[stk[32]], the
 * others push it. */
extern s32 D_003888C4[];
static inline double inl_dist(f32 x1, f32 y1, f32 x2, f32 y2) {
    f32 dx = x2 - x1;
    f32 dy = y2 - y1;
    return sqrt(dx * dx + dy * dy);
}

s32 func_001d17d0(VmRec *vm) {
    f32 d = inl_dist(vm->stk[vm->sp - 3], vm->stk[vm->sp - 2], vm->stk[vm->sp - 1], vm->stk[vm->sp]);
    if (vm->stk[32] >= 2304) D_003888C4[vm->stk[32]] = d;
    vm->sp -= 5;
    return 2;
}

s32 func_001d1890(VmRec *vm) {
    f32 d = inl_dist(vm->stk[vm->sp - 3], vm->stk[vm->sp - 2], vm->stk[vm->sp - 1], vm->stk[vm->sp]);
    vm->sp -= 3;
    vm->stk[vm->sp] = d;
    return 2;
}

static inline double inl_dist3(f32 x1, f32 y1, f32 z1, f32 x2, f32 y2, f32 z2) {
    f32 dx = x2 - x1;
    f32 dy = y2 - y1;
    f32 dz = z2 - z1;
    return sqrt(dx * dx + dz * dz + dy * dy);
}

s32 func_001d1948(VmRec *vm) {
    f32 d = inl_dist3(vm->stk[vm->sp - 5], vm->stk[vm->sp - 4], vm->stk[vm->sp - 3], vm->stk[vm->sp - 2], vm->stk[vm->sp - 1], vm->stk[vm->sp]);
    if (vm->stk[32] >= 2304) D_003888C4[vm->stk[32]] = d;
    vm->sp -= 7;
    return 2;
}

s32 func_001d1a28(VmRec *vm) {
    f32 d = inl_dist3(vm->stk[vm->sp - 5], vm->stk[vm->sp - 4], vm->stk[vm->sp - 3], vm->stk[vm->sp - 2], vm->stk[vm->sp - 1], vm->stk[vm->sp]);
    vm->sp -= 5;
    vm->stk[vm->sp] = d;
    return 2;
}

VmRec *func_001e98d0(s32, s32);

s32 func_001d1b00(VmRec *vm) {
    VmRec *a = func_001e98d0((s32)(vm->fl.x >> 5) & 1, vm->stk[vm->sp - 1]);
    VmRec *b = func_001e98d0((s32)(vm->fl.x >> 5) & 1, vm->stk[vm->sp]);
    struct VmObj *p = a->obj;
    struct VmObj *q = b->obj;
    f32 d = inl_dist(p->pos[0], p->pos[2], q->pos[0], q->pos[2]);
    if (vm->stk[32] >= 2304) D_003888C4[vm->stk[32]] = d;
    vm->sp -= 3;
    return 2;
}

s32 func_001d1bf8(VmRec *vm) {
    VmRec *a = func_001e98d0((s32)(vm->fl.x >> 5) & 1, vm->stk[vm->sp - 1]);
    VmRec *b = func_001e98d0((s32)(vm->fl.x >> 5) & 1, vm->stk[vm->sp]);
    struct VmObj *p = a->obj;
    struct VmObj *q = b->obj;
    f32 d = inl_dist(p->pos[0], p->pos[2], q->pos[0], q->pos[2]);
    vm->sp -= 1;
    vm->stk[vm->sp] = d;
    return 2;
}

s32 func_001d1ce0(VmRec *vm) {
    VmRec *a = func_001e98d0((s32)(vm->fl.x >> 5) & 1, vm->stk[vm->sp - 1]);
    VmRec *b = func_001e98d0((s32)(vm->fl.x >> 5) & 1, vm->stk[vm->sp]);
    struct VmObj *p = a->obj;
    struct VmObj *q = b->obj;
    f32 d = inl_dist3(p->pos[0], p->pos[2], p->pos[1], q->pos[0], q->pos[2], q->pos[1]);
    if (vm->stk[32] >= 2304) D_003888C4[vm->stk[32]] = d;
    vm->sp -= 3;
    return 2;
}

s32 func_001d1df0(VmRec *vm) {
    VmRec *a = func_001e98d0((s32)(vm->fl.x >> 5) & 1, vm->stk[vm->sp - 1]);
    VmRec *b = func_001e98d0((s32)(vm->fl.x >> 5) & 1, vm->stk[vm->sp]);
    struct VmObj *p = a->obj;
    struct VmObj *q = b->obj;
    f32 d = inl_dist3(p->pos[0], p->pos[2], p->pos[1], q->pos[0], q->pos[2], q->pos[1]);
    vm->sp -= 1;
    vm->stk[vm->sp] = d;
    return 2;
}

/* func_001d1ef0 is in vm_lib.c. */

void func_00122f58(struct VmObj *, f32, f32, f32);

s32 func_001d1f48(VmRec *vm) {
    struct VmObj *o = vm->obj;
    if (o != 0) {
        func_00122f58(o, vm->stk[vm->sp], 0.0f, 1.0f);
    }
    vm->sp--;
    return 2;
}

s32 func_001d1fb0(VmRec *vm) {
    struct VmObj *o = vm->obj;
    if (o != 0) {
        func_00122f58(o, vm->stk[vm->sp], 0.0f, 2.0f);
    }
    vm->sp--;
    return 2;
}

s32 func_001d2018(VmRec *vm) {
    struct VmObj *o = vm->obj;
    if (o != 0) {
        func_00122f58(o, vm->stk[vm->sp], 0.0f, 3.0f);
    }
    vm->sp--;
    return 2;
}

/* func_001d2080 and func_001d2088 are in vm_lib.c. */

/* The heading (degrees, 0-360) from the entity of VM stk[sp-3] to the point
 * stk[sp-2..sp] (func_001d2090) or to the entity of VM stk[sp]
 * (func_001d2270), relative to its own heading. */
void func_001e9d00(f32 *out, f32 *to, f32 *from, f32 x);
static inline f32 inl_deg(f32 r) {
    f32 d = r * 180.0f / 3.1415928f;
    return d < 0.0f ? d + 360.0f : d;
}

s32 func_001d2090(VmRec *vm) {
    f32 from[4];
    f32 to[4];
    f32 out[4];
    VmRec *p;
    struct VmObj *e;
    f32 a, b;
    s32 *r;
    p = func_001e98d0((s32)(vm->fl.x >> 5) & 1, vm->stk[vm->sp - 3]);
    if (!p) {
        vm->sp -= 3;
        vm->stk[vm->sp] = 0;
        return 2;
    }
    e = p->obj;
    from[0] = e->pos[0];
    from[1] = e->pos[1];
    from[2] = e->pos[2];
    to[0] = vm->stk[vm->sp - 2];
    to[1] = vm->stk[vm->sp - 1];
    to[2] = vm->stk[vm->sp];
    to[3] = from[3] = 1.0f;
    func_001e9d00(out, to, from, 0.0f);
    vm->sp -= 3;
    a = inl_deg(p->obj->f3c);
    vm->stk[vm->sp] = inl_deg(out[1]) - a;
    if (vm->stk[vm->sp] < 0) vm->stk[vm->sp] += 360;
    return 2;
}

s32 func_001d2270(VmRec *vm) {
    f32 from[4];
    f32 to[4];
    f32 out[4];
    VmRec *p, *q;
    struct VmObj *e, *e2;
    f32 a;
    p = func_001e98d0((s32)(vm->fl.x >> 5) & 1, vm->stk[vm->sp - 1]);
    q = func_001e98d0((s32)(vm->fl.x >> 5) & 1, vm->stk[vm->sp]);
    if (!p || !q) {
        vm->sp -= 1;
        vm->stk[vm->sp] = 0;
        return 2;
    }
    e = p->obj;
    from[0] = e->pos[0];
    e2 = q->obj;
    from[1] = e->pos[1];
    from[2] = e->pos[2];
    from[3] = 1.0f;
    to[0] = e2->pos[0];
    to[1] = e2->pos[1];
    to[2] = e2->pos[2];
    to[3] = 1.0f;
    func_001e9d00(out, to, from, 0.0f);
    vm->sp -= 1;
    a = inl_deg(p->obj->f3c);
    vm->stk[vm->sp] = inl_deg(out[1]) - a;
    if (vm->stk[vm->sp] < 0) vm->stk[vm->sp] += 360;
    return 2;
}

/* func_001d35a0 .. func_001d3c70 are in vm_lib.c. */

/* Push the entity's home position x / y / z (0 without one). */
s32 func_001d3cb8(VmRec *vm) {
    vm->sp++;
    if (vm->obj) {
        vm->stk[vm->sp] = vm->obj->p50[0];
    } else {
        vm->stk[vm->sp] = 0;
    }
    return 2;
}

s32 func_001d3d08(VmRec *vm) {
    vm->sp++;
    if (vm->obj) {
        vm->stk[vm->sp] = vm->obj->p50[1];
    } else {
        vm->stk[vm->sp] = 0;
    }
    return 2;
}

s32 func_001d3d58(VmRec *vm) {
    vm->sp++;
    if (vm->obj) {
        vm->stk[vm->sp] = vm->obj->p50[2];
    } else {
        vm->stk[vm->sp] = 0;
    }
    return 2;
}

/* func_001d3da8 .. func_001d3e08 are in vm_lib.c. */

/* Step the move func_001d3ff0 started, as func_001d1080 (flag bit 9; it
 * also arrives at once while D_0037A378 bit 0 is set). */
void func_001d3e30(VmRec *vm) {
    VmMsgD m;
    f32 dx, dy, dz, dist, spd;
    dx = vm->f14[0] - vm->p[0];
    dy = vm->f14[1] - vm->p[1];
    dz = vm->f14[2] - vm->p[2];
    dist = sqrt(dx * dx + dy * dy + dz * dz);
    spd = vm->f20;
    if (dist < spd || (D_0037A378 & 1)) {
        m.type = 3;
        m.val = 0;
        m.x = vm->x0;
        m.v[0] = vm->f14[0];
        m.v[1] = vm->f14[1];
        m.v[2] = vm->f14[2];
        m.v[3] = 1.0f;
        func_001c4640((VmMsg *)&m);
        vm->fl.x &= ~0x200ULL;
    } else {
        m.type = 3;
        m.val = 0;
        m.x = vm->x0;
        m.v[3] = 1.0f;
        m.d[0] = (vm->f14[0] - vm->p[0]) / dist * spd;
        m.d[1] = (vm->f14[1] - vm->p[1]) / dist * spd;
        m.d[2] = (vm->f14[2] - vm->p[2]) / dist * spd;
        vm->p[0] += m.d[0];
        vm->p[1] += m.d[1];
        vm->p[2] += m.d[2];
        m.v[0] = vm->p[0];
        m.v[1] = vm->p[1];
        m.v[2] = vm->p[2];
        func_001c4640((VmMsg *)&m);
    }
}

/* func_001d3ff0 .. func_001d4710 are in vm_lib.c. */

/* func_001d4798's message: b10's 16-aligned one with a u32 bit-field header. */
typedef struct {
    u32 type:8, id:24;
    s32 x4;
    u8 pad8[8];
    f32 x, y, z;
    f32 ang;
} __attribute__((aligned(16))) VmMsgA;

/* Send message 2 (turn towards the entity of VM stk[sp]), as func_001cd2d8
 * does for a point; the sqrt / atan2 libcall sequences keep their delay-slot
 * nops (nofill). */
s32 func_001d4798(VmRec *vm) {
    VmMsgA m;
    f32 d[3];
    f32 len, a, b, f;
    double r;
    VmRec *rf;
    s32 type;
    rf = func_001e98d0(vm->fl.b.b5, vm->stk[vm->sp]);
    vm->fl.b.b0 = 1;
    d[0] = rf->obj->pos[0] - vm->obj->pos[0];
    d[1] = rf->obj->pos[1] - vm->obj->pos[1];
    d[2] = rf->obj->pos[2] - vm->obj->pos[2];
    len = sqrt(d[0] * d[0] + d[1] * d[1] + d[2] * d[2]);
    d[2] /= len;
    d[0] /= len;
    d[1] /= len;
    a = atan2(d[2], d[0]);
    b = atan2(vm->obj->rot[2], vm->obj->rot[0]);
    r = a - b;
    type = 2;
    if (r < 0.0) r = 0.0 - r;
    f = r;
    if (f > 3.1415928f) f = 3.1415928f - (f - 3.1415928f);
    if (f * 180.0f / 3.1415928f < 0.0) {
    }
    m.type = type;
    m.id = vm->stk[vm->sp - 1];
    m.x4 = vm->x0;
    m.x = rf->obj->pos[0];
    m.y = rf->obj->pos[1];
    m.z = rf->obj->pos[2];
    m.ang = 179.99998f;
    func_001c4640((VmMsg *)&m);
    vm->f14[0] = rf->obj->pos[0];
    vm->f14[1] = rf->obj->pos[1];
    vm->f14[2] = rf->obj->pos[2];
    vm->sp -= 2;
    vm->f20 = m.id;
    vm->f60 = (s32)rf->obj;
    vm->f64 = 0;
    return 2;
}

/* func_001d4ac8 .. func_001d4b60 are in vm_lib.c. */

/* 10000 sin / cos of stk[sp] degrees. */
double sin(double);
double cos(double);

s32 func_001d4c08(VmRec *vm) {
    f32 r = sin(vm->stk[vm->sp] * 3.1415928f / 180.0f) * 10000.0;
    vm->stk[vm->sp] = r;
    return 2;
}

s32 func_001d4cb8(VmRec *vm) {
    f32 r = cos(vm->stk[vm->sp] * 3.1415928f / 180.0f) * 10000.0;
    vm->stk[vm->sp] = r;
    return 2;
}

/* func_001d4d68 .. func_001d5118 are in vm_lib.c. */

/* Remove entity stk[sp], and unlink it from the field VMs D_0038D170 /
 * D_0039A580 that drive it. */
void func_001248e8(s32);

s32 func_001d5168(VmRec *vm) {
    s32 i, n;
    VmRec *p;
    func_001248e8(vm->stk[vm->sp]);
    vm->fl.x |= 4;
    vm->x2f4 = 2.0f;
    p = D_0038D170;
    n = D_0039A570;
    for (i = 0; i < n; i++, p++) {
        if (p->x0 == vm->stk[vm->sp]) p->obj = 0;
    }
    p = D_0039A580;
    n = D_003A7980;
    for (i = 0; i < n; i++, p++) {
        if (p->x0 == vm->stk[vm->sp]) p->obj = 0;
    }
    vm->sp--;
    return 2;
}

/* func_001d5408 .. func_001d58a0 are in vm_lib.c. */

extern VmMgr D_00389C90;

/* Remove the entity x3158[0] names, and unlink it from the field VMs.  Kept
 * h43's view of D_00389C90 with x3158[0] as a `struct VmObj *` (VmRec.obj's
 * type): the stores to p->obj then reload it every iteration, as the
 * original does (VmMgr's s32 is hoisted; a `*(struct VmObj **)&x3158[0]`
 * cast folds the offset into the base). */
typedef struct { u8 pad0[0x3158]; struct VmObj *f3158; } VmMgr3158;
#define MGR_OBJ (((VmMgr3158 *)&D_00389C90)->f3158)
s32 func_001d58c8(VmRec *vm) {
    s32 i, n;
    VmRec *p;
    func_001248e8((s32)MGR_OBJ);
    p = D_0038D170;
    n = D_0039A570;
    for (i = 0; i < n; i++, p++) {
        if (p->x0 == (s32)MGR_OBJ) p->obj = 0;
    }
    p = D_0039A580;
    n = D_003A7980;
    for (i = 0; i < n; i++, p++) {
        if (p->x0 == (s32)MGR_OBJ) p->obj = 0;
    }
    return 2;
}

/* func_001d5978 .. func_001d5b00 are in vm_lib.c. */

/* Send message 2 (walk to the point stk[sp-2..sp] at speed stk[sp-3]):
 * func_001cd2d8's sibling, with the same message view; the turn rate is
 * the angle over the time the walk takes. */
s32 func_001d5b58(VmRec *vm) {
    Msg2 m;
    f32 v[3];
    f32 len, a, f, g;
    double d;
    vm->fl.x |= 1;
    v[0] = (f32)vm->stk[vm->sp - 2] - vm->obj->pos[0];
    v[1] = (f32)vm->stk[vm->sp - 1] - vm->obj->pos[1];
    v[2] = (f32)vm->stk[vm->sp] - vm->obj->pos[2];
    len = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);

    v[2] /= len;
    v[0] /= len;
    v[1] /= len;

    a = atan2(v[2], v[0]);
    d = a - (f32)atan2(vm->obj->rot[2], vm->obj->rot[0]);
    if (d < 0.0) d = -d;
    f = d;
    if (3.1415928f < f) f = 3.1415928f - (f - 3.1415928f);
    d = f * 180.0f / 3.1415928f;
    if (d < 0.0) d = -d;
    g = d;

    m.type = 2;
    m.val = vm->stk[vm->sp - 3];
    m.v[0] = vm->stk[vm->sp - 2];
    m.x = vm->x0;
    m.v[1] = vm->stk[vm->sp - 1];
    m.v[2] = vm->stk[vm->sp];
    m.v[3] = g * 2.0f / (len / vm->stk[vm->sp - 3]);

    func_001c4640((VmMsg *)&m);
    vm->sp -= 4;
    vm->f14[0] = m.v[0];
    vm->f14[1] = m.v[1];
    vm->f14[2] = m.v[2];
    vm->f20 = m.val;
    vm->f60 = 0;
    vm->f64 = 0;
    return 2;
}

/* func_001d5ed8 .. func_001d6628 are in vm_lib.c. */

void func_00104268(f32, f32);

s32 func_001d6658(VmRec *vm) {
    func_00104268(vm->stk[vm->sp - 1], vm->stk[vm->sp]);
    vm->sp -= 2;
    return 2;
}

/* func_001d7678 .. func_001d7840 are in vm_lib.c. */

/* The jump (b11): func_001d7b88 starts it (message 2's Msg2 view, with the
 * 17 / 0x10004 sound), func_001d7898 steps it every frame and sends the
 * position with the step (VmMsgE: VmMsg plus e[3]). */
typedef struct { u8 type; u32 val:24; s32 x; s32 a8; s32 ac; f32 v[4]; f32 e[3]; } __attribute__((aligned(8))) VmMsgE;
f32 func_001e9ec0(f32 *, f32 *);

void func_001d7898(VmRec *vm) {
    VmMsgE m;
    f32 len, vx, vz;
    f32 dt = D_002BBDFC;
    vm->f4c -= dt;
    vm->f50 -= dt;
    if (vm->f4c <= 0.0f) {
        vm->fl.x &= ~0x400;
        if (vm->b5d) {
            m.type = 17;
            m.val = 0x10007;
            m.x = vm->x0;
            m.v[0] = 10.0f;
            func_001c4640((VmMsg *)&m);
        }
        m.type = 3;
        m.val = 0;
        m.x = vm->x0;
        m.v[0] = vm->f14[0];
        m.v[1] = vm->f14[1];
        m.v[2] = vm->f14[2];
        m.v[3] = 1.0f;
        func_001c4640((VmMsg *)&m);
        return;
    }
    if (vm->f50 < 0.0f && vm->b5c == 0) {
        if (vm->b5d) {
            m.type = 17;
            m.val = 0x10005;
            m.x = vm->x0;
            m.v[0] = 10.0f;
            func_001c4640((VmMsg *)&m);
        }
        vm->b5c = 1;
    }
    if (vm->f50 < 20.0f && vm->b5c == 1) {
        if (vm->b5d) {
            m.type = 17;
            m.val = 6;
            m.x = vm->x0;
            m.v[0] = 10.0f;
            func_001c4640((VmMsg *)&m);
        }
        vm->b5c = 2;
    }
    len = sqrt((vm->f14[0] - vm->p[0]) * (vm->f14[0] - vm->p[0]) + (vm->f14[2] - vm->p[2]) * (vm->f14[2] - vm->p[2]));
    vm->f54 += vm->f58;
    m.e[1] = vm->f54;
    vm->p[1] += vm->f54;
    vx = (vm->f14[0] - vm->p[0]) / len * vm->f20;
    vm->p[0] += vx;
    vz = (vm->f14[2] - vm->p[2]) / len * vm->f20;
    vm->p[2] += vz;
    m.type = 3;
    m.val = 0;
    m.x = vm->x0;
    m.v[0] = vm->p[0];
    m.v[1] = vm->p[1];
    m.v[2] = vm->p[2];
    m.v[3] = 1.0f;
    m.e[0] = vx;
    m.e[2] = vz;
    func_001c4640((VmMsg *)&m);
}

s32 func_001d7b88(VmRec *vm) {
    f32 v[3];
    Msg2 m;
    f32 tx, ty, tz, h, T, y0, H, r, t2, d;
    double dh, a, b;
    h = vm->stk[vm->sp - 4];
    tx = vm->stk[vm->sp - 3];
    T = vm->stk[vm->sp - 5];
    ty = vm->stk[vm->sp - 2];
    tz = vm->stk[vm->sp - 1];
    vm->f14[2] = tz;
    vm->f14[0] = tx;
    vm->f14[1] = ty;
    vm->p[0] = vm->obj->pos[0];
    vm->p[1] = y0 = vm->obj->pos[1];
    vm->p[2] = vm->obj->pos[2];
    dh = h;
    a = dh;
    if (a < 0.0) a = -a;
    H = a * 2.0 + ty - y0;
    b = dh;
    if (b < 0.0) b = -b;
    r = (b + ty - y0) / H;
    t2 = T - T * r;
    v[0] = tx;
    vm->f54 = h * 2.0f / t2;
    vm->f58 = (ty - y0) * 2.0f / T / T - vm->f54 * 2.0f / T;
    v[1] = ty;
    vm->fl.x |= 0x400;
    v[2] = tz;
    d = func_001e9ec0(v, vm->obj->pos);
    vm->f20 = d / T;
    vm->p[0] += (vm->f14[0] - vm->p[0]) / d * vm->f20;
    vm->p[2] += (vm->f14[2] - vm->p[2]) / d * vm->f20;
    vm->b5d = vm->stk[vm->sp];
    if (vm->b5d) {
        m.type = 17;
        m.val = 0x10004;
        m.x = vm->x0;
        m.v[0] = 10.0f;
        func_001c4640((VmMsg *)&m);
    }
    vm->f4c = T * D_002BBDFC;
    vm->f50 = t2 * D_002BBDFC;
    vm->sp -= 6;
    vm->b5c = 0;
    return 2;
}

typedef VmRec Ent;
extern s32 D_0039A570;
#include "data/pieces/D_0038D170.h"
extern s32 D_003A7980;
#include "data/pieces/D_0039A580.h"

/* func_001d7ef8 .. func_001d9268 are in vm_lib.c. */

/* Step the move from p to f14 over f24 (message 3 with the point; at the
 * end, clear flag 11). */
void func_001d9348(VmRec *vm) {
    VmMsg m;
    f32 t;
    vm->f28 += D_002BBDFC;
    if (vm->f24 < vm->f28) {
        m.type = 3;
        m.val = 0;
        m.x = vm->x0;
        m.v[0] = vm->f14[0];
        m.v[1] = vm->f14[1];
        m.v[2] = vm->f14[2];
        m.v[3] = 1.0f;
        func_001c4640(&m);
        vm->fl.x &= ~0x800ULL;
    } else {
        t = vm->f28 / vm->f24;
        m.type = 3;
        m.val = 0;
        m.x = vm->x0;
        m.v[0] = vm->p[0] + (vm->f14[0] - vm->p[0]) * t;
        m.v[1] = vm->p[1] + (vm->f14[1] - vm->p[1]) * t;
        m.v[2] = vm->p[2] + (vm->f14[2] - vm->p[2]) * t;
        m.v[3] = 1.0f;
        func_001c4640(&m);
    }
}

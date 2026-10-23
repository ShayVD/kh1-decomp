#include "common.h"
#include "data/types/vm_rec.h"
#include "data/types/fvec.h"
/* The entity a VM drives (VmRec's obj): the jump op reads its position, the
 * chase routine its direction and flags (session 30: b11's Actor and Obj). */
typedef FVec4 V4 __attribute__((aligned(16)));
typedef struct VmObj {
    u8 pad0[8];
    s32 f8;
    u8 padc[4];
    V4 pos;
    V4 dir;
    u8 pad30[0x60];
    u64 f90;
    u8 pad98[0xb8];
    f32 f150;
} Obj;
typedef VmRec VM;
typedef struct { u8 type; u32 val:24; s32 x; s32 a8; s32 ac; f32 v[4]; } __attribute__((aligned(8))) Msg;
typedef struct { u8 type; u32 val:24; s32 x; s32 a8; s32 ac; f32 v[4]; f32 e[3]; } __attribute__((aligned(8))) MsgE;
void func_001c4640();
double sqrt(double);
double atan2(double, double);
extern f32 D_002BBDFC;

f32 func_001e9ec0(f32 *, f32 *);

void func_001d7898(VM *vm) {
    MsgE m;
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
            func_001c4640(&m);
        }
        m.type = 3;
        m.val = 0;
        m.x = vm->x0;
        m.v[0] = vm->f14[0];
        m.v[1] = vm->f14[1];
        m.v[2] = vm->f14[2];
        m.v[3] = 1.0f;
        func_001c4640(&m);
        return;
    }
    if (vm->f50 < 0.0f && vm->b5c == 0) {
        if (vm->b5d) {
            m.type = 17;
            m.val = 0x10005;
            m.x = vm->x0;
            m.v[0] = 10.0f;
            func_001c4640(&m);
        }
        vm->b5c = 1;
    }
    if (vm->f50 < 20.0f && vm->b5c == 1) {
        if (vm->b5d) {
            m.type = 17;
            m.val = 6;
            m.x = vm->x0;
            m.v[0] = 10.0f;
            func_001c4640(&m);
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
    func_001c4640(&m);
}

s32 func_001d7b88(VM *vm) {
    f32 v[3];
    Msg m;
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
    vm->p[0] = vm->obj->pos.x;
    vm->p[1] = y0 = vm->obj->pos.y;
    vm->p[2] = vm->obj->pos.z;
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
    d = func_001e9ec0(v, &vm->obj->pos.x);
    vm->f20 = d / T;
    vm->p[0] += (vm->f14[0] - vm->p[0]) / d * vm->f20;
    vm->p[2] += (vm->f14[2] - vm->p[2]) / d * vm->f20;
    vm->b5d = vm->stk[vm->sp];
    if (vm->b5d) {
        m.type = 17;
        m.val = 0x10004;
        m.x = vm->x0;
        m.v[0] = 10.0f;
        func_001c4640(&m);
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
void func_00267530(V4 *, V4 *, V4 *);
void func_00121fc4(V4 *, V4 *);
f32 func_00121840(V4 *, V4 *);
void func_00121860(V4 *, V4 *, V4 *, f32);
void func_002675a8(V4 *, V4 *);
void func_00137688(Obj *, f32);
f32 atan2f(f32, f32);
f32 func_001dcb00(Obj *o, V4 *target, f32 a, f32 b) {
    V4 v;
    f32 len, t;
    s32 i;
    Ent *e;
    func_00267530(&v, target, &o->pos);
    func_00121fc4(&v, &v);
    if (b == 0.0f) {
        b = func_00121840(&o->dir, &v);
        t = v.w / a * 0.3f;
        if (1.0f < t) b /= t;
    }
    len = v.w;
    if (len < a) a = len;
    func_00121860(&o->dir, &v, &v, b);
    o->f150 = atan2f(v.x, v.z);
    func_00137688(o, o->f150);
    v.w = a;
    func_002675a8(&o->dir, &v);
    for (i = 0; i < D_0039A570; i++) {
        e = &D_0038D170[i];
        if (e->obj == o && e->f60 && e->f60 == o->f8) len = 0.0f;
    }
    for (i = 0; i < D_003A7980; i++) {
        e = &D_0039A580[i];
        if (e->obj == o && e->f60 && e->f60 == o->f8) len = 0.0f;
    }
    for (i = 0; i < D_0039A570; i++) {
        e = &D_0038D170[i];
        if (e->obj == o) {
            if (o->f90) {
                e->f64 += 1.0f;
                if (60.0f < e->f64) len = 0.0f;
            } else {
                e->f64 = 0.0f;
            }
        }
    }
    for (i = 0; i < D_003A7980; i++) {
        e = &D_0039A580[i];
        if (e->obj == o) {
            if (e->obj->f90) {
                e->f64 += 1.0f;
                if (60.0f < e->f64) len = 0.0f;
            } else {
                e->f64 = 0.0f;
            }
        }
    }
    return len;
}
#include "data/data_0039.h"
#include "data/data_003A.h"
#include "data/pieces/D_002BBDFC.h"

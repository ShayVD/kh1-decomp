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
double atan2(double, double);
extern f32 D_002BBDFC;


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

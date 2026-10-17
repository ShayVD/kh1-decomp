/* pppKeThDraw 0018c3f8, nostrict: 15 words off. Only the mode branch differs: gcc hoists t1=66 above beq (jump.c if-conversion); orig keeps bnel to out-of-line else + b with li 66 in slot. */
#include "common.h"
#include "ppp.h"

#define PPP_WORK(T, obj, e, k) ((T *) ((u8 *) (obj) + (e)->offsets[k] + 0xA0))

typedef struct {
    u8 pad0[0xC];
    f32 fC;
    u8 pad10[0x14];
    f32 f24;
    u8 pad28[4];
    f32 f2C;
} ThSub;

typedef struct {
    u8 pad0[0x10];
    ThSub s;          /* +0x10 */
    u8 pad[0x6C - 0x10 - sizeof(ThSub)];
    s32 f6C;
    u64 c[4];         /* +0x70 */
} ThWork;

typedef struct {
    u8 pad[0x54];
    u8 mode;
} ThKey;

typedef struct { f32 x, y; } ThV2;
extern f32 D_003701F0[3];
extern u8 D_00616080[];
extern u8 D_00616224[];

void func_001a8d78(ThWork *);
void func_001a8c40(ThWork *, void *, f32 *, ThSub *, void *, u64, u64);

typedef struct {
    s32 x0;
    f32 x4, x8;
    f32 xC, x10, x14, x18;
} B030Out;
typedef struct {
    u8 pad[8];
    f32 x8;
    u8 padC[8];
    f32 x14;
} B030In;

void func_0018b030(B030In *a, B030Out *b) {
    f32 z;
/*P*/
    b->x4 = a->x8;
    b->x0 = (s32)a;
    b->x10 = a->x14;
    z = 0.0f;
    b->x8 = z;
    b->x18 = z;
    b->x14 = z;
    b->xC = z;
/*Q*/
}

void func_0018b470(B030In *a, B030Out *b) {
    b->x4 = a->x8;
    b->x0 = (s32)a;
    b->x10 = a->x14;
    b->xC = b->x14 = b->x18 = b->x8 = 0.0f;
}

void pppKeThDraw(void *obj, ThKey *k, PppEntry *e) {
    f32 v[2];
    ThWork *w;
    u64 t1;
    u64 t2;
    u8 m;
    w = PPP_WORK(ThWork, obj, e, 0);
    v[0] = D_003701F0[0];
    v[1] = D_003701F0[1];
    m = k->mode;
    t1 = 72; t2 = 0x51801;
    if (m != 0) {
        if (m == 1) { t1 = 66; } else { t2 = 0x70000; t1 = 0x80000000a8ULL; }
    }

    func_001a8c40(w, D_00616080, v, &w->s, D_00616224, t1, t2);
}

void pppKeThCon(void *obj, PppEntry *e) {
    ThWork *w = PPP_WORK(ThWork, obj, e, 0);
    ThSub *s = &w->s;

    func_001a8d78(w);
    w->c[0] = 0;
    w->c[1] = 0;
    w->c[2] = 0;
    w->c[3] = 0;
    w->f6C = 0;
    s->fC = 0;
    s->f24 = 0;
    s->f2C = 0;
}

void pppKeThReset(void *obj, PppEntry *e) {
    ThWork *w = PPP_WORK(ThWork, obj, e, 0);
    ThSub *s = &w->s;

    w->c[0] = 0;
    w->c[1] = 0;
    w->c[2] = 0;
    w->c[3] = 0;
    w->f6C = 0;
    s->fC = 0;
    s->f24 = 0;
    s->f2C = 0;
}

typedef struct {
    u8 pad[0x30];
    u8 v30[0x10];
    f32 f40, f44;
    s32 i48;
} A8Obj;
typedef struct {
    A8Obj *o;
    s32 i;
    void *m;
    f32 f44;
    f32 f40;
    void *v;
} A8Arg;
extern u8 D_00616040[];
void func_001a5ce8(A8Arg *, s32);

void func_001931a8(A8Obj *o) {
    A8Arg a;
    a.o = o;
    a.f40 = o->f40;
    a.i = o->i48;
    a.f44 = o->f44;
    a.m = D_00616040;
    a.v = o->v30;
    func_001a5ce8(&a, 0);
}

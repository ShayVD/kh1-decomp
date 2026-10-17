/* func_0012cf48 only matches with its callee func_0012cd10 defined above it. */
#include "common.h"
typedef struct { u8 pad[0x44]; f32 r; u8 pad48[0x16]; u8 kind; } CdInfo;
typedef struct E15 {
    u8 pad[0x10];
    f32 pos[4];
    u8 pad20[0x10];
    f32 dir[4];
    u8 pad40[0x98 - 0x40];
    struct E15 *f98;
    u8 pad9c[0x130 - 0x9c];
    CdInfo *info;
} E15;
void func_00267530(f32 *, f32 *, f32 *);
void func_00121fc4(f32 *, f32 *);
f32 func_00120c18(f32 *);
f32 func_00120bf8(f32 *);
void func_0012ec88(E15 *, f32 *);
f32 func_00267390(f32 *, f32 *);

s32 func_0012cd10(E15 *o, E15 *t) {
    f32 d[4];
    f32 ay, k;
    switch (o->info->kind) {
    case 0:
        func_00267530(d, o->pos, t->pos);
        ay = fabsf(d[1]);
        d[1] = 0.0f;
        func_00121fc4(d, d);
        if (d[3] < o->info->r) {
            if (ay < o->info->r) {
                k = 1.0f - func_00267390(t->dir, d);
                if (k < 1.0f) return d[3] + d[3] * k * 0.5f;
            }
        }
        break;
    case 1:
        func_00267530(d, o->pos, t->pos);
        if (fabsf(d[1]) < o->info->r) {
            if (func_00120c18(d) < o->info->r) return 0;
        }
        break;
    case 2:
        func_0012ec88(o, d);
        func_00267530(d, d, t->pos);
        if (func_00120bf8(d) < o->info->r) {
            d[1] = 0.0f;
            func_00121fc4(d, d);
            k = 1.0f - func_00267390(t->dir, d);
            return d[3] + d[3] * k * 0.5f;
        }
        break;
    case 3:
        func_00267530(d, o->pos, t->pos);
        d[1] = 0.0f;
        func_00121fc4(d, d);
        if (d[3] < o->info->r) {
            k = 1.0f - func_00267390(t->dir, d);
            if (k < 1.0f) return d[3] + d[3] * k * 0.5f;
        }
        break;
    }
    return -1;
}

typedef struct { s32 d; E15 *e; } P15;
typedef struct S31b0 { E15 *f0; s32 f4; } S31b0;
extern s32 D_002E31B8;
extern S31b0 D_002E31B0;
extern s32 func_00122ff8(E15 *);
extern s32 func_00122fd0(E15 *);
extern E15 *func_001230a0(E15 *);
extern void func_00250360(void *, s32, s32, void *);
extern s32 func_0012cf38();
s32 func_0012cf48(E15 *e, P15 *out) {
    s32 n = 0;
    s32 d;
    P15 *p;
    E15 *it;
    if (D_002E31B8 >= 3) {
        if (func_00122ff8(D_002E31B0.f0)) {
            if (func_0012cd10(D_002E31B0.f0, e) >= 0) {
                out->d = 0;
                n = 1;
                out->e = D_002E31B0.f0;
            }
            goto done;
        }
    }
    it = 0;
    while ((it = func_001230a0(it)) != 0) {
        if (it != e && it != e->f98 && func_00122fd0(it)) {
            d = func_0012cd10(it, e);
            if (d >= 0) {
                out[n].d = d;
                out[n].e = it;
                n++;
            }
        }
    }
    func_00250360(out, n, 8, func_0012cf38);
done:
    return n;
}

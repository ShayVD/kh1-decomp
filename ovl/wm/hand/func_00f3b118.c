/* wm.x func_00f3b118: matched by hand. */
#include "ovl.h"

typedef struct {
    s32 a; s32 id; s32 zone; s32 pad0C; s32 pad10; s32 a14; void *obj; u8 *info;
    OvlMtx m0; OvlMtx m1; OvlMtx m2; OvlVec v0; OvlVec v1; f32 dist; void *mdl; u8 pad[8];
} S;
typedef struct { u8 pad[0x40]; OvlMtx m; u8 pad2[0x540 - 0x80]; s32 v; } G;
typedef struct { u8 pad[0xC8]; f32 dist; } M;
void func_001bf048(OvlMtx, OvlMtx);
S *func_00f3b0b0(s32);
s32 func_00f3c4d8(f32 *);
void *func_00f3f260(s32, s32);
M *func_00f64c38(u8, s32);
extern OvlMtx D_00F85180;
extern OvlMtx D_00F85200;
extern G *D_00F864C0;
extern s32 D_00F87020;
extern s32 D_00F9A534;
extern u8 D_00FDF7D8[];
extern S *D_00FDFFD8;

S *func_00f3b118(s32 arg0, s32 arg1, s32 id, u8 *info, OvlMtx m, f32 *v) {
    S *s;
    S *o;
    M *md;
    u8 *c;
    {
        /* pinned: gcc otherwise picks v1 for the count (pure register swap) */
        register s32 n KH1_REG("$4") = D_00F9A534;
        s = &D_00FDFFD8[n];
    }
    s->a = arg1;
    s->id = id;
    s->obj = func_00f3f260(id, D_00F864C0->v);
    s->info = info;
    s->zone = -1;
    s->a14 = 0;
    if (m != 0) {
        PlatVu0CopyMatrix(s->m0, m);
        PlatVu0MulMatrix(s->m2, D_00F85200, s->m0);
        PlatVu0MulMatrix(s->m2, D_00F85180, s->m2);
        func_001bf048(s->m1, m);
        PlatVu0MulMatrix(s->m1, D_00F864C0->m, s->m1);
        s->zone = func_00f3c4d8(s->m0[3]);
        o = func_00f3b0b0(id);
        if (o != 0) {
            PlatVu0SubVector(s->v1, s->m0[3], o->m0[3]);
            s->v1[3] = 1.0f;
        } else {
            s->v1[0] = 0.0f;
            s->v1[3] = 1.0f;
            s->v1[1] = 0.0f;
            s->v1[2] = 0.0f;
        }
    }
    if (v != 0) {
        PlatVu0CopyVector(s->v0, v);
    }
    c = &D_00FDF7D8[id & 0x7FF];
    if (*c < 4) (*c)++;
    if (info != 0 && *info != 0xFF) {
        md = func_00f64c38(*info, D_00F87020);
        s->mdl = md;
        s->dist = md->dist;
    } else {
        s->mdl = 0;
        s->dist = 0;
    }
    D_00F9A534++;
    return s;
}

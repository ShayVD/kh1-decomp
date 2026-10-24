/* The map collision file's tables (mapdata.c), its nostrict part: the flag mode's functions (the rest is
 * in the files beside it). Read from the
 * code, not proved by a boot (docs/modules.md "Session 55"). */
#include "common.h"
#include "data/types/nostrict_text_00100000_h51.h"
#include "data/pieces/D_002A624C.h"
#include "data/types/nostrict_text_00100000_h51_p2.h"
#include "data/pieces/D_002A6234.h"
#include "data/pieces/D_002A6308.h"
#include "data/pieces/D_002A6318.h"
#include "data/pieces/D_002A6324.h"
#include "data/pieces/D_002A6238.h"
#include "data/types/nostrict_text_00100000_h51_p.h"
#include "data/pieces/D_002A6274.h"

/* func_00104940 (from hand/nostrict/text_00100000_h51.c). */
typedef Vec3_2a624c Vec3;
void func_00104850(Vec3 *, IVec3 *);
s32 func_00104940(Vec3 *v, s32 *out) {
    IVec3 hi;
    IVec3 lo;
    s32 i, j, n;

    func_00104850(&v[0], &lo);
    func_00104850(&v[1], &hi);
    if (D_002A6324 == D_002A6234 && D_002A6308.x == hi.x && D_002A6308.z == hi.z
        && D_002A6318.x == lo.x && D_002A6318.z == lo.z) {
        return -1;
    }
    n = 0;
    for (i = lo.x; i < hi.x + 1; i++) {
        for (j = lo.z; j < hi.z + 1; j++) {
            *out++ = i * D_002A6234->nz + j;
            n++;
        }
    }
/*P*/
    D_002A6308.x = hi.x;
    D_002A6308.z = hi.z;
    D_002A6318.x = lo.x;
    D_002A6318.z = lo.z;
    D_002A6324 = D_002A6234;
/*Q*/
    return n;
}

/* func_00104c38 (from hand/nostrict/text_00100000_h51.c). */
typedef struct { f32 x, y, z, w; } Vec4;
s32 func_00104c38(s32 idx, Vec4 *out) {
    s32 a = D_002A6238[idx].v[0], b = D_002A6238[idx].v[1], c = D_002A6238[idx].v[2], d = D_002A6238[idx].v[3];

    switch (d) {
    case -1:
            out[0].x = ((Vec3_2a624c *)D_002A624C)[a].x[0];
            out[0].y = ((Vec3_2a624c *)D_002A624C)[a].x[1];
            out[0].z = ((Vec3_2a624c *)D_002A624C)[a].x[2];
            out[0].w = 1.0f;
            out[1].x = ((Vec3_2a624c *)D_002A624C)[b].x[0];
            out[1].y = ((Vec3_2a624c *)D_002A624C)[b].x[1];
            out[1].z = ((Vec3_2a624c *)D_002A624C)[b].x[2];
            out[1].w = 1.0f;
            out[2].x = ((Vec3_2a624c *)D_002A624C)[c].x[0];
            out[2].y = ((Vec3_2a624c *)D_002A624C)[c].x[1];
            out[2].z = ((Vec3_2a624c *)D_002A624C)[c].x[2];
            out[2].w = 1.0f;
            return 3;
    case -2:
            out[0].x = ((Vec3_2a624c *)D_002A624C)[c].x[0];
            out[0].y = ((Vec3_2a624c *)D_002A624C)[c].x[1];
            out[0].z = ((Vec3_2a624c *)D_002A624C)[c].x[2];
            out[0].w = 1.0f;
            out[1].x = ((Vec3_2a624c *)D_002A624C)[b].x[0];
            out[1].y = ((Vec3_2a624c *)D_002A624C)[b].x[1];
            out[1].z = ((Vec3_2a624c *)D_002A624C)[b].x[2];
            out[1].w = 1.0f;
            out[2].x = ((Vec3_2a624c *)D_002A624C)[a].x[0];
            out[2].y = ((Vec3_2a624c *)D_002A624C)[a].x[1];
            out[2].z = ((Vec3_2a624c *)D_002A624C)[a].x[2];
            out[2].w = 1.0f;
            return 3;
    default:
        out[0].x = ((Vec3_2a624c *)D_002A624C)[a].x[0];
        out[0].y = ((Vec3_2a624c *)D_002A624C)[a].x[1];
        out[0].z = ((Vec3_2a624c *)D_002A624C)[a].x[2];
        out[0].w = 1.0f;
        out[1].x = ((Vec3_2a624c *)D_002A624C)[b].x[0];
        out[1].y = ((Vec3_2a624c *)D_002A624C)[b].x[1];
        out[1].z = ((Vec3_2a624c *)D_002A624C)[b].x[2];
        out[1].w = 1.0f;
        out[2].x = ((Vec3_2a624c *)D_002A624C)[c].x[0];
        out[2].y = ((Vec3_2a624c *)D_002A624C)[c].x[1];
        out[2].z = ((Vec3_2a624c *)D_002A624C)[c].x[2];
        out[2].w = 1.0f;
        out[3].x = ((Vec3_2a624c *)D_002A624C)[d].x[0];
        out[3].y = ((Vec3_2a624c *)D_002A624C)[d].x[1];
        out[3].z = ((Vec3_2a624c *)D_002A624C)[d].x[2];
        out[3].w = 1.0f;
        return 4;
    }
}

/* func_001050d0 (from hand/nostrict/text_00100000_h51.c). */
extern s32 D_002A6230;
extern s32 D_002A6294;
extern u16 D_002A62F8[];
void func_0011d270(s32, s32, s32, s32);
void func_00104f10(s32, Vec4 *);
void func_00104eb0(s32, Vec4 *);
f32 func_00267390(Vec4 *, Vec4 *);
void func_001050d0(void) {
    Vec4 b;
    Vec4 a;
    s32 i;

    D_002A6230 = 0;
    for (i = 0; i < D_002A6294; i++) {
        Tri20 *t = &D_002A6274[i];
        if (t->f.t.b25 == 1) {
            func_0011d270(t->i, D_002A6230, i, 0);
            D_002A62F8[D_002A6230++] = D_002A6274[i].h;
            func_00104f10(i, &a);
            func_00104eb0(i, &b);
            {f32 r = func_00267390(&a, &b);
            Tri20 *e = D_002A6274;
            e[i].d = -r;
            e[i].f.t.b25 = 0;}
        }
    }
}


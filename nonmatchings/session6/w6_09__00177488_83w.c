/* ~83w (structure): nostrict. Orig loop entered via b to the top-calls block placed at the bottom (L59C), constants 1000/40 not hoisted; every C form tried (while-comma, goto into for/do) compiles to the same rotated loop with 1000/40 hoisted. Maybe different loop flags. Prefix up to the loop is right except bnez/bnezl. */
#include "common.h"
typedef struct { f32 x, y, z, w; } V4_74;
typedef struct { V4_74 p; V4_74 d; V4_74 hit; s16 id; u8 pad[14]; } Ray74;
typedef struct { V4_74 p; V4_74 d; f32 r; u8 pad[12]; V4_74 out; } Sph74;
void func_00267530(V4_74 *, V4_74 *, V4_74 *);
void func_002675a8(V4_74 *, V4_74 *);
void func_00267560(V4_74 *, V4_74 *, f32);
void func_00118d78(Ray74 *);
void func_00118608(Ray74 *, V4_74 *);
s32 func_00118868(Sph74 *);
f32 func_00120bf8(V4_74 *);

s32 func_00177488(V4_74 *out, V4_74 *a, V4_74 *b) {
    V4_74 v;
    Ray74 r;
    Sph74 s;
    s32 hit, n;
    f32 d, lim;
    func_00267530(&r.d, b, a);
    func_002675a8(&r.p, a);
    func_00118d78(&r);
    hit = r.id != -1;
    if (!hit) {
        func_00118608(&r, a);
        if (r.id != -1) hit = 1;
        if (!hit) return hit;
    }
    lim = 20.0f;
    func_002675a8(out, a);
    do {
        func_002675a8(&s.p, out);
        func_00267530(&v, &r.hit, out);
        d = func_00120bf8(&v);
        if (d >= 1000.0f) break;
        if (d >= lim) func_00267560(&v, &v, lim / d);
        func_002675a8(&s.d, &v);
        s.r = 40.0f;
        n = func_00118868(&s);
        func_002675a8(out, &s.out);
        if (n) break;
    } while (d >= lim);
    return hit;
}

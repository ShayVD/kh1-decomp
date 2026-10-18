#include "common.h"

/* func_00177488 (hand/nostrict, no context). func_00118608 takes one argument.
 * The compiled-out assert after the join's func_002675a8 call ends the basic
 * block there (an empty do-while), so gcse's hoisted &s / &r.hit setups land in
 * the next block; the call then has no in-block dependents and sched1 issues
 * lim = 20.0f before it (LUID tie), as in the original. */
#define ASSERT(x) do { } while (0)
typedef struct { f32 x, y, z, w; } V4_74;
typedef struct { V4_74 p; V4_74 d; V4_74 hit; s16 id; u8 pad[14]; } Ray74;
typedef struct { V4_74 p; V4_74 d; f32 r; u8 pad[12]; V4_74 out; } Sph74;
void func_00267530(V4_74 *, V4_74 *, V4_74 *);
void func_002675a8(V4_74 *, V4_74 *);
void func_00267560(V4_74 *, V4_74 *, f32);
void func_00118d78(Ray74 *);
void func_00118608(Ray74 *);
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
        func_00118608(&r);
        if (r.id != -1) hit = 1;
        if (!hit) goto done;
    }
    lim = 20.0f;
    func_002675a8(out, a);
    ASSERT(hit);
    goto test;
body:
    if (d >= lim) func_00267560(&v, &v, lim / d);
    func_002675a8(&s.d, &v);
    s.r = 40.0f;
    n = func_00118868(&s);
    func_002675a8(out, &s.out);
    if (n) goto done;
    if (!(d >= lim)) goto done;
test:
    func_002675a8(&s.p, out);
    func_00267530(&v, &r.hit, out);
    d = func_00120bf8(&v);
    if (!(d >= 1000.0f)) goto body;
done:
    return hit;
}

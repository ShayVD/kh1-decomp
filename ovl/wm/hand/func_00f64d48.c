/* wm.x func_00f64d48: matched by hand. */
#include "ovl.h"

typedef struct { s16 time; s16 pad; f32 v; f32 a; f32 b; } CKey;
typedef struct { u8 interp; u8 pre; u8 post; u8 pad; u16 n; u16 pad2; CKey *k; } Curve;

f32 func_00f64d48(Curve *c, f32 t)
{
    CKey *k = c->k;
    u32 n = c->n;
    CKey *kl;
    CKey *kp;
    f32 dt;
    CKey *k2;
    f32 slope, v, period, ts;

    ts = k->time;
    if (t < ts) {
        switch (c->pre) {
        case 1:
            if (n == 1) return k->v;
            {
            CKey *k1;
            kp = k;
            k2 = kp + 1;
            k1 = k2;
            dt = k1->time - kp->time;
            if (c->interp == 1 && dt != 0.0f) {
                slope = (k1->v - kp->v) / dt;
            } else {
                slope = k->a;
            }
            return k->v - (k->time - t) * slope;
            }
        case 2:
            if (n == 1) return k->v;
            period = k[n - 1].time - k->time;
            while (t < ts) t += period;
            break;
        case 0:
        default:
            return k->v;
        }
    }
    kl = &k[n - 1];
    ts = kl->time;
    if (ts <= t) {
        switch (c->post) {
        case 0:
        default:
            return kl->v;
        case 1:
            if (n == 1) return k->v;
            kp = kl - 1;
            dt = kl->time - kp->time;
            if (c->interp == 1 && dt != 0.0f) {
                slope = (kl->v - kp->v) / dt;
            } else {
                slope = kl->b;
            }
            return kl->v + (t - kl->time) * slope;
        case 2:
            if (n == 1) return k->v;
            period = kl->time - k->time;
            while (ts < t) t -= period;
            break;
        }
    }
    kp = k + 1;
    while (kp->time <= t) {
        if (t == kp->time) return kp->v;
        kp++;
    }
    {
        f32 v1 = kp->v;
        f32 ka = kp->a;
        f32 t1 = kp->time;
        f32 t0, kb, v0;
        kp--;
        t0 = kp->time;
        v0 = kp->v;
        kb = kp->b;
        switch (c->interp) {
        case 0:
        default:
            return v0;
        case 1:
            return v0 + (v1 - v0) * (t - t0) / (t1 - t0);
        case 2: {
            f32 d = 1.0f / (t1 - t0);
            f32 u = t - t0;
            f32 u2 = u * u;
            f32 u3 = u2 * u;
            f32 c3 = u2 * 3.0f;
            f32 d2 = d * d;
            f32 b, a, e;
            b = u2 * d;
            a = u3 * d2;
            c3 = c3 * d2;
            e = (a + a) * d;
            return v0 * (e - c3 + 1.0f) + v1 * (c3 - e) + kb * (a - b - b + u) + ka * (a - b);
        }
        }
    }
}

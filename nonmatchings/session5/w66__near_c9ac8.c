#include "common.h"
typedef struct {
    u64 flags; u8 pad8[4]; f32 dur; u8 pad16[16]; f32 t; u8 pad36[16]; u32 m; u8 pad56[40];
    f32 start; u8 pad100[44]; f32 end; u8 pad148[140]; f32 cur;
} Tw;
extern Tw D_003C5510;
extern f32 D_002BBDFC;
void func_001c6a20(void);
void func_001c9ac8(void) {
    f32 t0, t1, a, u, u2, u3, d;
    f32 *s, *e;
    t1 = t0 = 0.0f;
    D_003C5510.t += D_002BBDFC;
    s = &D_003C5510.start;
    e = &D_003C5510.end;
    switch (D_003C5510.m) {
    case 0:
        t0 = (*e - *s) / D_003C5510.dur;
        break;
    case 1:
    case 2:
        break;
    case 3:
        t0 = (*e - *s) / D_003C5510.dur;
        break;
    }
    switch (D_003C5510.m) {
    case 0:
    case 2:
        t1 = (*e - *s) / D_003C5510.dur;
        break;
    case 1:
    case 3:
        t1 = 0.0f;
        break;
    }
    a = 0.0f;
    if (D_003C5510.t == a) {
        D_003C5510.cur = *s;
    } else if (D_003C5510.dur <= D_003C5510.t) {
        D_003C5510.cur = *e;
    } else {
        d = D_003C5510.dur - a;
        u = (D_003C5510.t - a) / d;
        u2 = u * u;
        u3 = u * u2;
        D_003C5510.cur = ((u3 + u3) - u2 * 3.0f + 1.0f) * *s
            + (u3 * -2.0f + u2 * 3.0f) * *e
            + ((u3 - (u2 + u2) + u) * t0 + (u3 - u2) * t1) * d;
    }
    func_001c6a20();
    if (D_003C5510.t > D_003C5510.dur) D_003C5510.flags &= ~64;
}

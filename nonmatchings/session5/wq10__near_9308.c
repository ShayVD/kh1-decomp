#include "common.h"
typedef f32 Vec[4] __attribute__((aligned(16)));
typedef struct {
    u32 bf0:4, b4:1, bf5:3, b8:1, bf9:23;
    f32 dur;
    u8 pad8[0x10];
    f32 t;
    u8 pad1c[0x10];
    u32 mode;
    u8 pad30[0x10];
    Vec p0;
    u8 pad50[0x20];
    Vec p1;
    u8 pad80[0x50];
    Vec pos;
} __attribute__((aligned(16))) CamS;
extern CamS D_003C5510;
extern f32 D_002BBDFC;
void func_001c6a20(void);
void func_001c9308(void) {
    f32 a[4];
    f32 b[4];
    s32 i;
    f32 s, u, u2, u3, d;
    f32 *p0, *p1;
    for (i = 0; i < 3; i++) {
        a[i] = 0.0f;
        b[i] = 0.0f;
    }
    D_003C5510.t += D_002BBDFC;
    p0 = D_003C5510.p0;
    p1 = D_003C5510.p1;
    switch (D_003C5510.mode) {
    case 0:
    case 3:
        for (i = 0; i < 3; i++) a[i] = (p1[i] - p0[i]) / D_003C5510.dur;
        break;
    case 1:
    case 2:
        for (i = 2; i >= 0; i--) a[i] = 0.0f;
        break;
    }
    switch (D_003C5510.mode) {
    case 0:
    case 2:
        for (i = 0; i < 3; i++) b[i] = (p1[i] - p0[i]) / D_003C5510.dur;
        break;
    case 1:
    case 3:
        for (i = 2; i >= 0; i--) b[i] = 0.0f;
        break;
    }
    s = 0.0f;
    if (D_003C5510.t == s) {
        D_003C5510.pos[0] = p0[0];
        D_003C5510.pos[1] = p0[1];
        D_003C5510.pos[2] = p0[2];
    } else if (D_003C5510.dur <= D_003C5510.t) {
        D_003C5510.pos[0] = p1[0];
        D_003C5510.pos[1] = p1[1];
        D_003C5510.pos[2] = p1[2];
    } else {
        d = D_003C5510.dur - s;
        u = (D_003C5510.t - s) / d;
        u2 = u * u;
        u3 = u * u2;
        for (i = 0; i < 3; i++) {
            D_003C5510.pos[i] = (2.0f * u3 - 3.0f * u2 + 1.0f) * p0[i]
                + (-2.0f * u3 + 3.0f * u2) * p1[i]
                + ((u3 - 2.0f * u2 + u) * a[i] + (u3 - u2) * b[i]) * d;
        }
    }
    func_001c6a20();
    if (D_003C5510.t > D_003C5510.dur) D_003C5510.b4 = 0;
}

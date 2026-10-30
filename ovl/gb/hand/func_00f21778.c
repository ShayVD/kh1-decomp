/* gb.x func_00f21778: matched by hand. */
#include "ovl.h"

typedef struct {
    s32 p[3];
    s32 q[3];
    s32 r[3];
    s32 c[5];
    s32 pad[2];
} GbCam;
typedef struct { u8 pad0[0x76]; s16 cam; } GbWorld;
extern GbWorld *D_00F56DC0;
void func_00f215a8(GbCam *, s32);
void func_00f216b0(GbCam *);
void func_001bfac8(void);

void func_00f21778(s32 id, s32 n) {
    GbCam a;
    GbCam b;
    GbCam c;
    s32 i, j;
    func_00f215a8(&a, D_00F56DC0->cam);
    func_00f215a8(&b, id);
    for (i = 0; i < n; i++) {
        for (j = 0; j < 3; j++) {
            c.p[j] = (b.p[j] - a.p[j]) * i / n + a.p[j];
            c.q[j] = (b.q[j] - a.q[j]) * i / n + a.q[j];
            c.r[j] = (b.r[j] - a.r[j]) * i / n + a.r[j];
        }
        c.c[0] = (b.c[0] - a.c[0]) * i / n + a.c[0];
        c.c[1] = (b.c[1] - a.c[1]) * i / n + a.c[1];
        c.c[2] = (b.c[2] - a.c[2]) * i / n + a.c[2];
        c.c[3] = (b.c[3] - a.c[3]) * i / n + a.c[3];
        c.c[4] = (b.c[4] - a.c[4]) * i / n + a.c[4];
        func_00f216b0(&c);
        func_001bfac8();
    }
    func_00f216b0(&b);
}

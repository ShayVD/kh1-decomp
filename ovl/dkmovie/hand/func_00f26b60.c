/* dkmovie.x func_00f26b60: matched by hand. */
#include "ovl.h"

typedef struct {
    u8 *p[4];
    u8 pad[0x30];
    u64 c[2];
    u64 d[2];
    u8 *q[3];
    u8 pad2[4];
    u8 b0[0x300];
    u8 b1[0x180];
    u8 b2[4][0x300];
} IpuWork;
extern IpuWork *D_00F28464;
void func_00f26b60(void) {
    IpuWork *x = D_00F28464;
    x->q[0] = x->b0;
    x->q[1] = x->b1;
    x->q[2] = x->b2[0];
    x->p[0] = x->b2[0];
    x->p[1] = x->b2[1];
    x->p[2] = x->b2[2];
    x->p[3] = x->b2[3];
    x->c[0] = 0x8000800080008000;
    x->c[1] = 0x8000800080008000;
    x->d[0] = 0x7F007F007F007F00;
    x->d[1] = 0x7F007F007F007F00;
}

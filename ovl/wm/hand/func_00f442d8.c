/* wm.x func_00f442d8: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[0x540]; s32 f540; u8 pad2[0x14]; s32 f558; u8 pad3[0x34]; } P442d8;
typedef struct { s8 a[0x20]; s8 b[0x38]; } S442d8;
typedef struct { s32 x; s32 tex[1]; } T442d8;
CONTEXT_ONLY void func_00f43dd0(s32 a, s8 *b) {}
s32 func_00f62b90(s32);
u8 *func_00f62b98(s32, s32);
extern P442d8 D_00F86500[];
extern s32 D_00F87054;
extern S442d8 D_00F87E9C[];
extern s32 D_00F8BA88[];
extern s32 D_01080908[32];
extern s32 D_01080988;
extern s32 D_0108098C;
extern s32 D_01080990;

void func_00f442d8(s32 arg0) {
    P442d8 *p = &D_00F86500[arg0];
    s32 buf;
    s8 *s;
    s32 i, n;
    u8 *e;
    u8 *q;
    s32 *g;

    D_01080988 = 0;
    buf = D_00F87054;
    if (p->f558 >= 0) {
        s = D_00F87E9C[p->f558].b;
        if (s != NULL && *s != 0 && *s != '-') {
            func_00f43dd0(buf, s);
            D_01080988 = buf;
            buf += 0x1000;
        }
    }
    D_0108098C = 0;
    if (p->f558 >= 0) {
        s = D_00F87E9C[p->f558].a;
        if (s != NULL && *s != 0 && *s != '-') {
            func_00f43dd0(buf, s);
            D_0108098C = buf;
            buf += 0x1000;
        }
    }
    for (i = 31; i >= 0; i--) {
        D_01080908[i] = 0;
    }
    n = func_00f62b90(p->f540);
    for (i = 0; i < n; i++) {
        e = func_00f62b98(i, p->f540);
        if (e[4] == 1) {
            for (q = e + 8; *q != 0; q += 4) {
                if (*q == 5) {
                    func_00f43dd0(buf, (s8 *)D_00F8BA88[q[1] + 1]);
                    D_01080908[q[1]] = buf;
                    buf += 0x1000;
                }
            }
        }
    }
    D_01080990 = buf;
}

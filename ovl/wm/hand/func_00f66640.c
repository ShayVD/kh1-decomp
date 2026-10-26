/* wm.x func_00f66640: matched by hand. */
#include "ovl.h"

extern u8 D_00F7F830[];
extern u8 D_00F81000[];
extern u8 D_00F82770[];
extern u8 D_00F83DF0[];
extern s32 D_0108EEE0[68];

typedef struct {
    s32 w0;
    s32 addr;
    s64 d8;
} WmDmaTag;

WmDmaTag *func_00f66640(WmDmaTag *t, s32 *a, s32 *b, s32 *c, s32 n, u32 kind) {
    u8 *prog;
    s32 i;

    switch (kind) {
    case 2:
        prog = D_00F82770;
        break;
    case 1:
        prog = D_00F83DF0;
        break;
    case 4:
    case 5:
        prog = D_00F81000;
        break;
    case 0:
    case 3:
    default:
        prog = D_00F7F830;
        break;
    }
    if (c == NULL) {
        c = D_0108EEE0;
        for (i = 63; i >= 0; i--) {
            c[i + 4] = 0;
        }
    }
    a[0] = 0x6000000C;
    a[3] = 0x6C0C0000;
    a[1] = 0;
    a[2] = 0x01000101;
    b[0] = 0x60000008;
    b[3] = 0x6C08000D;
    b[1] = 0;
    b[2] = 0x01000101;
    c[0] = 0x60000010;
    c[2] = 0x01000101;
    c[3] = 0x6C1003E0;
    c[1] = 0;
    t[4].addr = n;
    t[1].d8 = 0x13000000;
    t[4].d8 = 0x14000000;
    t[0].addr = (s32)prog;
    t[1].addr = (s32)a;
    t[2].addr = (s32)b;
    t[3].addr = (s32)c;
    t[0].w0 = 0x50000000;
    t[0].d8 = 0;
    t[1].w0 = 0x50000000;
    t[2].w0 = 0x50000000;
    t[2].d8 = 0;
    t[3].w0 = 0x50000000;
    t[3].d8 = 0;
    t[4].w0 = 0x50000000;
    t[5].w0 = 0x70000000;
    t[5].addr = 0;
    t[5].d8 = 0;
    return t + 5;
}

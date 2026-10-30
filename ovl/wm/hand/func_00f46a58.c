/* wm.x func_00f46a58: matched by hand. */
#include "ovl.h"

typedef struct { u64 d; u64 r; } GP46a58;
s32 func_00f66ac8(u32);
s32 func_00f66ae0(GP46a58 *);
GP46a58 *func_00f66b78(s32);
void func_00f66b90(GP46a58 *);
void func_00f66fe8(s32, u32);
extern GP46a58 **D_00F85160;
extern void (*D_00FB6444)(GP46a58 **);

void func_00f46a58(void) {
    GP46a58 *b[2];
    GP46a58 *s;
    GP46a58 *p;

    p = *D_00F85160;
    s = p;
    b[0] = s;
    b[1] = s;
    D_00FB6444(b);
    p = *D_00F85160;
    if (p < b[0]) {
        func_00f66fe8(2, (u32)p);
        p = b[0];
        s = p;
    }
    if (s < b[1]) {
        func_00f66fe8(3, (u32)s);
        p = b[1];
    }
    p = func_00f66b78(func_00f66ac8((u32)p));
    p->d = 0x740000007000;
    p->r = 0x18;
    p++;
    p->d = 0x5000D;
    p->r = 0x47;
    p++;
    p->d = 0x44;
    p->r = 0x42;
    p++;
    func_00f66b90(p);
    func_00f66fe8(1, func_00f66ae0(p));
    p = func_00f66b78(func_00f66ac8((u32)p));
    p->d = 0x44;
    p->r = 0x42;
    p++;
    p->d = 0x44;
    p->r = 0x43;
    p++;
    p->d = 0x800D0;
    p->r = 0x4C;
    p++;
    p->d = 0x800D0;
    p->r = 0x4D;
    p++;
    p->d = 0x31000070;
    p->r = 0x4E;
    p++;
    p->d = 0x31000070;
    p->r = 0x4F;
    p++;
    p->d = 0x17F000001FF0000;
    p->r = 0x40;
    p++;
    p->d = 0x17F000001FF0000;
    p->r = 0x41;
    p++;
    p->d = 0x740000007000;
    p->r = 0x18;
    p++;
    p->d = 0x740000007000;
    p->r = 0x19;
    p++;
    func_00f66b90(p);
    func_00f66fe8(4, func_00f66ae0(p));
    *D_00F85160 = p;
}

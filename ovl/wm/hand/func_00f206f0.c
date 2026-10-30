/* wm.x func_00f206f0: matched by hand. */
#include "ovl.h"

typedef struct { u8 b[24]; } B206f0;
typedef struct { u64 *p; u8 pad[3972]; s32 flip; } C206f0;
extern C206f0 *D_00F85160;
extern B206f0 D_00FBA808[];
extern u8 D_00F87360[];
void func_00f63260(C206f0 *);
void func_00f66f78(s32, void *);
u64 *func_00f66ac8(u64 *);
u64 *func_00f66b78(u64 *);
void func_00f66b90(u64 *);
void *func_00f66ae0(u64 *);

static inline void put206f0(u64 *p, u64 a, u64 b) {
    p[0] = a;
    p[1] = b;
}

void func_00f206f0(void) {
    u64 *p;
    u64 *q;
    C206f0 *c;

    D_00F85160->flip ^= 1;
    *(B206f0 *)D_00F85160 = D_00FBA808[D_00F85160->flip];
    c = D_00F85160;
    func_00f63260(c);
    func_00f66f78(10000, D_00F87360);
    c->p = func_00f66ac8(c->p);
    p = func_00f66b78(c->p);
    put206f0(p + 0, 0x0000740000007000LL, 24);
    put206f0(p + 2, 0x0000740000007000LL, 25);
    put206f0(p + 4, 68, 66);
    put206f0(p + 6, 68, 67);
    put206f0(p + 8, 0, 73);
    put206f0(p + 10, 0x30000, 71);
    put206f0(p + 12, 0x5000D, 71);
    put206f0(p + 14, 0x0000740000007000LL, 24);
    put206f0(p + 16, 0x0000740000007000LL, 25);
    c->p = p + 18;
    func_00f66b90(p + 18);
    func_00f66f78(10001, func_00f66ae0(c->p));
    c->p = func_00f66ac8(c->p);
    q = func_00f66b78(c->p);
    put206f0(q + 0, 0x0000740000007000LL, 24);
    put206f0(q + 2, 0x0000740000007000LL, 25);
    put206f0(q + 4, 68, 66);
    put206f0(q + 6, 68, 67);
    put206f0(q + 8, 0x5000D, 71);
    put206f0(q + 10, 0x5000D, 72);
    put206f0(q + 12, 0, 73);
    c->p = q + 14;
    func_00f66b90(q + 14);
    func_00f66f78(100000, func_00f66ae0(c->p));
}

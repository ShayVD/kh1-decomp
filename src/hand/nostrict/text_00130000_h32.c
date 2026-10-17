/* Hand-matched functions near 0x130000 built without strict aliasing (worker 32). */
#include "common.h"

typedef struct {
    s32 a, b, c, d, e, f, g;
} W32Args;
typedef struct {
    u8 pad00[0x10];
    W32Args args;
    u8 pad2c[0x2C - 0x2C];
    s32 x2c;
} W32Task;
extern u8 D_00525A30[];
void func_00133278(void);
W32Task *func_0011f090(void *a, s32 b, void (*c)(void));
s32 func_0012b888(s32 a);
void func_0012ba30(s32 a, void *b, s32 c);
W32Args *func_001332f0(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6) {
    W32Task *t = func_0011f090(D_00525A30, 0, func_00133278);
    W32Args *p;
    s32 h;
    p = &t->args;
    p->a = a0;
    p->b = a1;
    p->c = a2;
    p->d = a3;
    p->e = a5;
    p->f = a6;
    p->g = 0;
    h = func_0012b888(a4);
    func_0012ba30(h, &p, 4);
    t->x2c = h;
    return p;
}

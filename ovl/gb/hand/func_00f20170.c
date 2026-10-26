/* gb.x func_00f20170: matched by hand. */
#include "ovl.h"

typedef struct { s32 a, b, c, d, e, f, g; } P;
void func_001bb480(void);
s32 func_001bb500(s32, s32);
void func_00f429b0(P *);
void func_001bb4b0(void);
void func_001bfac8(void);
extern s32 D_00F74204;
void func_00f20170(s32 a, s32 b) {
    P p;
    func_001bb480();
    p.a = a;
    p.b = b;
    p.c = D_00F74204;
    p.d = func_001bb500(0x32000, 128);
    p.e = func_001bb500(0x32000, 128);
    p.f = 12800;
    p.g = 12500;
    func_00f429b0(&p);
    func_001bb4b0();
    func_001bfac8();
}

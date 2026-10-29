/* wm.x func_00f601f0: matched by hand. */
#include "ovl.h"

typedef struct {
    u32 end;
    u32 lim;
    u32 start;
} Rng;

typedef struct {
    void (*init)(void *);
    void (*draw)(Rng *);
    s32 (*poll)(void);
    s32 xC;
    s32 x10;
    s32 x14;
    s32 x18;
    s32 x1C;
} Mode;

extern s32 D_00FA5FB4;
extern Mode D_00FB4F50;
extern u8 *D_00F9B540;
extern u32 D_00F9B548;
extern char D_00FB7A48[];
void func_001bb480(void);
void func_001bb870(void *);
void func_001bd470(void);
s32 printf(const char *, ...);
s32 func_00f47190(void);
void func_00f66fe8(s32, u32);
void func_00f66f78(s32, u32);
s32 func_00f66ac8(u32);
u64 *func_00f66b78(s32);
void func_00f66b90(u64 *);
u32 func_00f66ae0(u64 *);
void func_001bfac8(void);
void func_001bb4b0(void);
void func_00f48c98(void);

void func_00f601f0(void *arg) {
    Rng r;
    u32 p;
    u32 q;
    s32 res;

    D_00FA5FB4 = 1;
    func_001bb480();
    func_001bb870(D_00F9B540 + 160);
    func_001bd470();
    printf(D_00FB7A48, D_00FB4F50.x1C);
    D_00FB4F50.xC = 0x2E00;
    D_00FB4F50.x10 = 0x400;
    D_00FB4F50.x14 = func_00f47190();
    D_00FB4F50.x18 = 0x100000;
    D_00FB4F50.init(arg);
    while (1) {
        p = D_00F9B548;
        q = p;
        r.start = p;
        p += 0x2000;
        r.end = p;
        r.lim = p;
        D_00FB4F50.draw(&r);
        if (q < r.start) {
            func_00f66fe8(0, q);
        }
        if (p < r.end) {
            func_00f66f78(0x2941, p);
            p = r.end;
        }
        if (p < r.lim) {
            func_00f66f78(0x2D01, p);
            p = r.lim;
        }
        D_00F9B548 = p;
        p = (u32)func_00f66b78(func_00f66ac8(p));
        ((u64 *)p)[0] = 0x0000740000007000;
        ((u64 *)p)[1] = 24;
        p += 16;
        func_00f66b90((u64 *)p);
        func_00f66f78(0x2940, func_00f66ae0((u64 *)p));
        D_00F9B548 = p;
        p = (u32)func_00f66b78(func_00f66ac8(p));
        ((u64 *)p)[0] = 0x0000740000007000;
        ((u64 *)p)[1] = 24;
        p += 16;
        func_00f66b90((u64 *)p);
        func_00f66f78(0x2D00, func_00f66ae0((u64 *)p));
        D_00F9B548 = p;
        if ((res = D_00FB4F50.poll()) != 0) {
            break;
        }
        func_001bfac8();
        if ((res = D_00FB4F50.poll()) != 0) {
            break;
        }
    }
    func_001bb4b0();
    D_00FA5FB4 = 0;
    if (res == 1) {
        func_00f48c98();
    }
}

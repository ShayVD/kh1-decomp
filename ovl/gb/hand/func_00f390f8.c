/* gb.x func_00f390f8: matched by hand. */
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

extern s32 D_00F61834;
extern Mode D_00F707D0;
extern u8 *D_00F56DC0;
extern u32 D_00F56DC8;
extern char D_00F71998[];
void func_001bb480(void);
void func_001bb870(void *);
void func_001bd470(void);
s32 printf(const char *, ...);
s32 func_00f20098(void);
void func_00f3fef0(s32, u32);
void func_00f3fe80(s32, u32);
s32 func_00f3f9d0(u32);
u64 *func_00f3fa80(s32);
void func_00f3fa98(u64 *);
u32 func_00f3f9e8(u64 *);
void func_001bfac8(void);
void func_001bb4b0(void);
void func_00f21ba0(void);

void func_00f390f8(void *arg) {
    Rng r;
    u32 p;
    u32 q;
    s32 res;

    D_00F61834 = 1;
    func_001bb480();
    func_001bb870(D_00F56DC0 + 160);
    func_001bd470();
    printf(D_00F71998, D_00F707D0.x1C);
    D_00F707D0.xC = 0x2E00;
    D_00F707D0.x10 = 0x400;
    D_00F707D0.x14 = func_00f20098();
    D_00F707D0.x18 = 0x100000;
    D_00F707D0.init(arg);
    while (1) {
        p = D_00F56DC8;
        q = p;
        r.start = p;
        p += 0x2000;
        r.end = p;
        r.lim = p;
        D_00F707D0.draw(&r);
        if (q < r.start) {
            func_00f3fef0(0, q);
        }
        if (p < r.end) {
            func_00f3fe80(0x2941, p);
            p = r.end;
        }
        if (p < r.lim) {
            func_00f3fe80(0x2D01, p);
            p = r.lim;
        }
        D_00F56DC8 = p;
        p = (u32)func_00f3fa80(func_00f3f9d0(p));
        ((u64 *)p)[0] = 0x0000740000007000;
        ((u64 *)p)[1] = 24;
        p += 16;
        func_00f3fa98((u64 *)p);
        func_00f3fe80(0x2940, func_00f3f9e8((u64 *)p));
        D_00F56DC8 = p;
        p = (u32)func_00f3fa80(func_00f3f9d0(p));
        ((u64 *)p)[0] = 0x0000740000007000;
        ((u64 *)p)[1] = 24;
        p += 16;
        func_00f3fa98((u64 *)p);
        func_00f3fe80(0x2D00, func_00f3f9e8((u64 *)p));
        D_00F56DC8 = p;
        if ((res = D_00F707D0.poll()) != 0) {
            break;
        }
        func_001bfac8();
        if ((res = D_00F707D0.poll()) != 0) {
            break;
        }
    }
    func_001bb4b0();
    D_00F61834 = 0;
    if (res == 1) {
        func_00f21ba0();
    }
}

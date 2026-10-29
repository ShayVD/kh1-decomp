/* 143 words / score 182 (720 vs 736). Logic complete (init of ~30 globals, D_00F707CC vtable calls, PlatBreak bounds check). The 30-store block is a scheduling puzzle: a hill-climb over its order reached score 146 after 10+ min. Also left: &D_00F702D8/&D_00F702DC are materialised in s0/s1 before the func_001be278 call, and 1/128 constants sit in s8/s3 */
typedef struct { u8 pad0[8]; void (*add)(void *, s32, s32); } GbSys;
typedef struct { u8 pad0[0xC]; s32 f0c; u8 pad10[4]; s32 base; s32 size; } GbMem;
extern s32 D_00F829F4, D_00F702D4;
extern u32 D_003F34B0[];
extern s32 D_00F705B4, D_00F705B8, D_00F705CC;
extern s32 D_00F82A14, D_00F829D8, D_00F82A44, D_00F829FC, D_00F82A00, D_00F82A08, D_00F829D4;
extern f32 D_00F82A28, D_00F82A30, D_00F82A24, D_00F82A2C, D_00F702E0, D_00F7032C;
extern s32 D_00F82A1C, D_00F82A0C, D_00F82A10, D_00F82A20, D_00F82A04;
extern s32 D_00F82A98, D_00F829F8, D_00F829E0, D_00F829DC, D_00F82A34, D_00F829D0;
extern s32 D_00F702D8, D_00F702DC;
extern s8 D_00F7073B, D_00F70738, D_00F70739, D_00F7073A;
extern GbMem D_00F707D0;
extern s32 D_00F82A9C, D_00F82A94, D_00F702D0, D_00F829C0;
extern GbSys *D_00F707CC;
void sceGsSyncPath(s32, s32);
s32 func_001be278(void);
void func_00f43ca0(void);
s32 func_0024b778(s32);
GbSys *func_0024b7a0(s32, s32, s32, s32);
void func_00f42ea0(void);
void func_00f43d70(void);
void func_00f509f8(void);
void func_00f4d800(void);
void func_00f4d8e0(void);

void func_00f42ed8(s32 mode) {
    s32 n, base, v;
    GbSys *sys;
    if (mode == 0) {
        D_00F829F4 = 0;
        D_00F702D4 = 0;
    } else {
        D_00F829F4 = 1;
    }
    D_003F34B0[0] = 0xB4B4B4;
    D_003F34B0[1] = 0xB4B4B4;
    sceGsSyncPath(0, 0);
    D_00F82A14 = D_00F705CC;
    D_00F829D8 = -80;
    D_00F82A44 = 1;
    D_00F829FC = 0;
    D_00F82A00 = 0;
    D_00F82A28 = 128.0f;
    D_00F82A08 = D_00F705B8;
    D_00F829D4 = -80;
    D_00F82A30 = 128.0f;
    D_00F82A1C = 128;
    D_00F82A0C = D_00F705B4;
    D_00F82A10 = D_00F705B8;
    D_00F702E0 = D_00F7032C;
    D_00F82A24 = 128.0f;
    D_00F82A2C = 128.0f;
    D_00F82A20 = 128;
    D_00F82A04 = D_00F705B4;
    D_00F82A98 = 0;
    D_00F829F8 = 0;
    D_00F829E0 = 0;
    D_00F829DC = 0;
    D_00F82A34 = 0;
    D_00F829D0 = 0;
    v = func_001be278() + 1;
    D_00F702D8 = v;
    D_00F702DC = v;
    if (D_00F7073B == 0) {
        func_00f43ca0();
        D_00F82A9C = D_00F707D0.f0c;
        D_00F7073B = 1;
        D_00F82A94 = 1;
        D_00F702D0 = 1;
        D_00F70738 = 0;
        D_00F70739 = 0;
        D_00F7073A = 0;
        n = func_0024b778(5);
        base = D_00F707D0.base;
        sys = func_0024b7a0(5, base, 0, n);
        base += n;
        D_00F829C0 = base;
        D_00F707CC = sys;
        if (D_00F707D0.size < base + 0x8800 - D_00F707D0.base)
            __asm__ volatile("break");
        func_00f42ea0();
        D_00F707CC->add(func_00f43d70, 1, 0);
        D_00F707CC->add(func_00f509f8, 1, 0);
        D_00F707CC->add(func_00f4d800, 1, 1);
        D_00F707CC->add(func_00f4d8e0, 1, 3);
    }
}

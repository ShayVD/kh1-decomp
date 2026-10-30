/* Round 46 wwm2: score 127 -> 107, sceGsSyncPath and func_00f42ea0 declared s32. Earlier header below. */
/* Round 41 wwm2: score 144 -> 127, port.py of the wm twin func_00f69fd0 draft (r41/twins.py pairs wm and gb drafts with the same target mnemonics). Earlier header below. */
/* 142 words / score 144 (720 vs 736). Logic complete (init of ~30 globals, D_00F707CC vtable calls, PlatBreak bounds check). Store order is the hill-climb result (15 min, from score 182). Also left: &D_00F702D8/&D_00F702DC are materialised in s0/s1 before the func_001be278 call, and 1/128 constants sit in s8/s3; 16 bytes short */
/* 113 words, score 183 (732 vs 736; was 148/184). Round 33 wwm2: hill2 moved `D_00F82A9C = D_00F707D0.xC` and `D_00F70738 = 0` within the init block; ctx2 gives nothing. Earlier header: score 184. Init function: around 30 global stores, sceGsSyncPath, func_001be278, then a one-time block that loads a module via func_0024b778/func_0024b7a0 and registers four callbacks through o->fn. The original preloads 1 (s8) and 128 (s3) into saved registers before sceGsSyncPath, so the 128 and 1 constants are probably shared variables. The store schedule is still far off. */
typedef struct { void *x0; void *x4; void (*fn)(void (*)(void), s32, s32); } Obj;
typedef struct { s32 x0, x4, x8, xC, x10, x14, x18; } Hdr;
extern s32 D_00F829F4;
extern s32 D_00F702D4;
extern s32 D_003F34B0[];
extern s32 D_00F705B4;
extern s32 D_00F705B8;
extern s32 D_00F705CC;
extern s32 D_00F82A14;
extern s32 D_00F829D8;
extern f32 D_00F7032C;
extern s32 D_00F82A44;
extern s32 D_00F829FC;
extern s32 D_00F82A00;
extern f32 D_00F82A28;
extern s32 D_00F82A08;
extern s32 D_00F829D4;
extern f32 D_00F82A30;
extern s32 D_00F82A1C;
extern s32 D_00F82A0C;
extern s32 D_00F82A10;
extern f32 D_00F702E0;
extern f32 D_00F82A24;
extern f32 D_00F82A2C;
extern s32 D_00F82A20;
extern s32 D_00F82A04;
extern s32 D_00F82A98;
extern s32 D_00F829F8;
extern s32 D_00F829E0;
extern s32 D_00F829DC;
extern s32 D_00F82A34;
extern s32 D_00F829D0;
extern s32 D_00F702D8;
extern s32 D_00F702DC;
extern s8 D_00F7073B;
extern s8 D_00F70738;
extern s8 D_00F70739;
extern s8 D_00F7073A;
extern Hdr D_00F707D0;
extern s32 D_00F82A9C;
extern s32 D_00F82A94;
extern s32 D_00F702D0;
extern s32 D_00F829C0;
extern Obj *D_00F707CC;
s32 sceGsSyncPath(s32, s32);
s32 func_001be278(void);
void func_00f43ca0(void);
s32 func_0024b778(s32);
Obj *func_0024b7a0(s32, s32, s32, s32);
s32 func_00f42ea0(void);
void func_00f43d70(void);
void func_00f509f8(void);
void func_00f4d800(void);
void func_00f4d8e0(void);

void func_00f42ed8(s32 a)
{
    s32 v, sz, top;
    s32 a34, a4c, a38;

    if (a == 0) {
        D_00F829F4 = 0;
        D_00F702D4 = 0;
    } else {
        D_00F829F4 = 1;
    }
    D_003F34B0[0] = 0xB4B4B4;
    D_003F34B0[1] = 0xB4B4B4;
    sceGsSyncPath(0, 0);
    D_00F829FC = 0;
    D_00F82A44 = 1;
    a34 = D_00F705B4;
    D_00F829D8 = -80;
    D_00F82A24 = 128.0f;
    D_00F82A04 = a34;
    D_00F82A00 = 0;
    D_00F82A2C = 128.0f;
    a38 = D_00F705B8;
    D_00F829D4 = -80;
    a4c = D_00F705CC;
    D_00F82A14 = a4c;
    D_00F82A08 = a38;
    D_00F82A20 = 128;
    D_00F82A30 = 128.0f;
    D_00F82A28 = 128.0f;
    D_00F702E0 = D_00F7032C;
    D_00F82A0C = a34;
    D_00F82A1C = 128;
    D_00F82A98 = 0;
    D_00F829F8 = 0;
    D_00F829E0 = 0;
    D_00F82A10 = a38;
    D_00F829DC = 0;
    D_00F82A34 = 0;
    D_00F829D0 = 0;
    v = func_001be278() + 1;
    D_00F702D8 = v;
    D_00F702DC = v;
    if (D_00F7073B == 0) {
        func_00f43ca0();
        D_00F82A94 = 1;
        D_00F82A9C = D_00F707D0.xC;
        D_00F702D0 = 1;
        D_00F70738 = 0;
        D_00F70739 = 0;
        D_00F7073A = 0;
        D_00F7073B = 1;
        sz = func_0024b778(5);
        top = D_00F707D0.x14;
        D_00F707CC = func_0024b7a0(5, top, 0, sz);
        D_00F829C0 = top + sz;
        if (D_00F707D0.x18 < top + sz + 0x8800 - D_00F707D0.x14) {
            __asm__ volatile("break");
        }
        func_00f42ea0();
        D_00F707CC->fn(func_00f43d70, 1, 0);
        D_00F707CC->fn(func_00f509f8, 1, 0);
        D_00F707CC->fn(func_00f4d800, 1, 1);
        D_00F707CC->fn(func_00f4d8e0, 1, 3);
    }
}

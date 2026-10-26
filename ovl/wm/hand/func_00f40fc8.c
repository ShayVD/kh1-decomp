/* wm.x func_00f40fc8: matched by hand. */
#include "ovl.h"

typedef struct { s32 id; s32 a; s32 b; f32 val; s32 pad2; s32 dir; s32 c; } Sub;
typedef struct { OvlMtx m0; OvlMtx m1; OvlMtx m2; OvlMtx m3[16]; OvlMtx m4[2]; Sub s; u8 pad2[0x590 - 0x55C]; } W;
typedef struct { u8 pad[0x54]; s32 v; } P;
void func_00106978(s32);
void func_00106a58(s32);
void func_0011d140(s32, s32);
void func_001bfac8(void);
void func_001c0310(s32, void (*)(void), s32);
void func_00f218d8(void);
void func_00f294a0(s32, s32, s32);
void func_00f30938(void);
void func_00f309d0(s32);
void func_00f33998(void);
void func_00f35970(void);
void func_00f3a4c8(void);
void func_00f3c678(void);
void func_00f3e3a0(void);
void func_00f3f2f8(f32);
s32 func_00f3f320(s32);
void func_00f3f358(void);
void func_00f3f7c8(s32);
void func_00f3fd60(s32, s32, s32);
void func_00f3ff98(s32, s32, s32);
void func_00f46cb8(s32, s32);
void func_00f40f58(void);
extern s32 D_002BBE04;
extern s32 D_00F850E0;
extern W *D_00F864C0;
extern W D_00F86500[];
extern P D_00F87E88[];
extern s32 D_00F9B2B8;

void func_00f40fc8(s32 arg0, s32 arg1, s32 arg2) {
    s32 i = 59;
    register W *w KH1_REG("$3"); /* pinned: gcc otherwise picks v0 for this temp (pure register swap) */
    s32 o = D_00F850E0 ^ 1;
    D_00F9B2B8 = 3;
    func_00f3c678();
    func_00f3a4c8();
    func_00f3e3a0();
    func_001bfac8();
    func_00f218d8();
    func_00106978(60);
    do {
        func_001bfac8();
        i--;
    } while (i >= 0);
    func_00f33998();
    func_00f3fd60(o, arg0, 0);
    func_00f3fd60(o, arg0, 1);
    D_00F9B2B8 = 3;
    D_002BBE04 = 0;
    func_00f3ff98(o, 0, arg2);
    func_00f3f358();
    func_00f3f7c8(D_00F87E88[arg0].v);
    D_00F850E0 = o;
    D_00F864C0 = &D_00F86500[o];
    func_00f3f2f8(1.0f);
    func_00f294a0(15000, 10752, D_00F86500[D_00F850E0].s.b);
    w = D_00F864C0;
    func_0011d140(func_00f3f320(w->s.c), 0);
    func_00f46cb8(64, 2);
    D_00F9B2B8 = 1;
    func_00f30938();
    func_00106a58(60);
    D_00F9B2B8 = 0;
    func_00f309d0(0);
    func_00f35970();
    func_001c0310(-1, func_00f40f58, 60);
}

#include "common.h"
s32 WaitSema(s32);
s32 SignalSema(s32);
s32 PollSema(s32);
void ExitDeleteThread(void);
s32 scePrintf(const char *, ...);
s32 sceSifCallRpc(void *, u32, u32, void *, s32, void *, s32, void *, void *);
void *func_002654e0(void);
void func_00267560(f32 *, f32 *, f32);
void func_002673b8(f32 *, f32 *);
void func_002673f8(f32 *, f32 *);
extern s32 D_0046C620, D_0046C654, D_0046C630, D_0046C614, D_0067334C, D_0046C610, D_00673340, D_0046C658;
extern char D_004930E0[];
extern s32 D_0046E094;
typedef struct { u8 pad[0x24]; void *server; } SifClient;
extern SifClient D_00673600;
typedef struct { s32 x0; s32 x4; s32 pad[3]; s32 x14; } McArg;
extern McArg D_00673680;
extern s32 D_00674BC0[];
typedef struct { s16 h0, h2, h4, h6; } GsState;
typedef struct { u64 pmode, smode2, dispfb, display, bgcolor; } DispEnv;

void func_00265980(DispEnv *d) {
    if (((GsState *)func_002654e0())->h6 == 1) {
        *(volatile u64 *)0x12000000 = d->pmode;
        *(volatile u64 *)0x12000070 = d->dispfb;
        *(volatile u64 *)0x12000080 = d->display;
        *(volatile u64 *)0x120000c0 = d->bgcolor;
    } else {
        *(volatile u64 *)0x12000000 = d->pmode;
        *(volatile u64 *)0x12000020 = d->smode2;
        *(volatile u64 *)0x12000090 = d->dispfb;
        *(volatile u64 *)0x120000a0 = d->display;
        *(volatile u64 *)0x120000e0 = d->bgcolor;
    }
}
void func_002695f8(void) {
    while (1) {
        WaitSema(D_0046C620);
        if (D_0046C654 == -1) {
            D_0046C630 = 0;
            D_0046C654 = 0;
            D_0046C614 = 0;
            D_0067334C = 0;
            ExitDeleteThread();
        }
        if (D_0046C610 > 0) scePrintf(D_004930E0, D_00673340, D_0046C658);
        if (D_00673340 && D_0046C658) ((void (*)(s32))D_00673340)(D_0046C658);
        D_0046C630 = 0;
    }
}
void func_002679e0(f32 *m, f32 *a, f32 *b, f32 *c) {
    f32 v[4];
    func_00267560(v, a, -1.0f);
    func_002673b8(m, v);
    func_00267560(v, b, -1.0f);
    func_002673b8(m + 4, v);
    func_00267560(v, c, -1.0f);
    func_002673b8(m + 8, v);
    m[12] = 0.0f;
    m[15] = 1.0f;
    m[14] = 0.0f;
    m[13] = 0.0f;
    func_002673f8(m, m);
}
s32 func_00270e40(s32 a) {
    s32 r;
    if (PollSema(D_0046E094) < 0) return -200;
    if (D_00673600.server == 0) {
        SignalSema(D_0046E094);
        return -100;
    }
    D_00673680.x4 = a;
    r = sceSifCallRpc(&D_00673600, 21, 0, &D_00673680, 48, D_00674BC0, 4, 0, 0);
    if (r != 0) {
        SignalSema(D_0046E094);
        return r;
    }
    SignalSema(D_0046E094);
    return D_00674BC0[0];
}

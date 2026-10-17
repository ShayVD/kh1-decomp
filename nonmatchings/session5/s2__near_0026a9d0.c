#include "common.h"
s32 SignalSema(s32);
s32 PollSema(s32);
s32 sceSifCallRpc(void *, u32, u32, void *, s32, void *, s32, void *, void *);
s32 func_00269f38(void);
s32 func_00269dc8(s32);
void func_00260738(void *, s32);
void func_00269558(s32 *);
s32 func_002690d0(s32);
void *func_00269128(s32);
void func_00269210(u8 *, void *);
void *memcpy(void *, const void *, u32);
s32 GetThreadId(void);
s32 ReferThreadStatus(s32, void *);
s32 CreateThread(void *);
s32 StartThread(s32, void *);
s32 ChangeThreadPriority(s32, s32);
void func_002695f8(void);
void func_00266bd0(void *, s32);
void func_00266d10(void *);
extern s32 D_0046C700, D_0046C654, D_0046C630, D_0046C628, D_0046C614, D_00673350;
extern u8 D_0046D7D0[];
extern u8 D_00673358[];
typedef struct { s32 status; void *func; void *stack; s32 stack_size; void *gp_reg; s32 initial_priority; } ThreadParam;
extern ThreadParam D_00673388;
extern u8 D_00494050[];
typedef struct { u8 pad[124]; s32 cnt; } PadBuf;
typedef struct { s32 x0, x4, x8; PadBuf *buf; u8 x10[0x330 - 16]; } Pad2Slot;
extern Pad2Slot D_00670040[];
extern s32 D_0046E094, D_0046E090;
typedef struct { u8 pad[0x24]; void *server; } SifClient;
extern SifClient D_00673600;
typedef struct { s32 x0; s32 x4; s32 x8; s32 xc; s32 x10; s32 x14; } McArg;
extern McArg D_00673680;
extern s32 D_00674BC0[];
extern const s32 D_00492E78[];
typedef struct { u32 chcr; u32 p0[3]; u32 madr; u32 p1[3]; u32 qwc; u32 p2[3]; u32 tadr; u32 p3[3]; u32 asr0; u32 p4[3]; u32 asr1; u32 p5[11]; u32 sadr; } DmaChReg;
extern DmaChReg *D_0046C550[];

s32 func_0026a9d0(s32 a) {
    s32 *p = &D_0046C700;
    if (func_00269f38() == 6) return 0;
    if (!func_00269dc8(9)) return 0;
    D_0046C700 = a;
    func_00260738(p, 4);
    D_0046C654 = 4;
    D_0046C630 = 1;
    if (sceSifCallRpc(D_0046D7D0, 5, 1, p, 4, 0, 0, func_00269558, &D_0046C654) < 0) {
        D_0046C654 = 0;
        D_0046C630 = 0;
        SignalSema(D_0046C628);
        return 0;
    }
    return 1;
}
s32 scePad2Read(s32 s, u8 *buf) {
    u8 *b;
    if (D_00670040[s].x0 == 0) return -1;
    if (D_00670040[s].x4 == 0) {
        if (func_002690d0(s) < 0) return -1;
    }
    b = func_00269128(s);
    if (b[2]) {
        u8 *d = b + 28;
        if (d) {
            memcpy(buf, d, b[2]);
            func_00269210(b + (b[2] + 28), D_00670040[s].x10);
        }
    }
    if (((s32 *)b)[1]) return b[2];
    return -1;
}
s32 func_002696b8(s32 prio, void *stack, s32 size) {
    s32 r = 1;
    if (D_0046C614 == 0) {
        s32 id = GetThreadId();
        D_00673350 = id;
        ReferThreadStatus(id, D_00673358);
        D_00673388.stack_size = size;
        D_00673388.gp_reg = D_00494050;
        D_00673388.func = func_002695f8;
        D_00673388.stack = stack;
        D_00673388.initial_priority = prio;
        D_0046C614 = CreateThread(&D_00673388);
        StartThread(D_0046C614, 0);
        return r;
    }
    ChangeThreadPriority(D_0046C614, prio);
    r = 0;
    return r;
}
s32 func_00271128(s32 a, s32 b, s32 c) {
    s32 r;
    if (PollSema(D_0046E094) < 0) return -200;
    if (D_00673600.server == 0) {
        SignalSema(D_0046E094);
        return -100;
    }
    D_00673680.x0 = a;
    D_00673680.x10 = b;
    D_00673680.x14 = c;
    r = sceSifCallRpc(&D_00673600, 4, 1, &D_00673680, 48, D_00674BC0, 4, 0, 0);
    if (r == 0) D_0046E090 = 4;
    else SignalSema(D_0046E094);
    return r;
}
#define D_CTRL (*(volatile u32 *)0x1000e000)
#define D_STAT (*(volatile u32 *)0x1000e010)
s32 func_00266c30(s32 enable) {
    u32 env[8];
    s32 old;
    s32 i;
    old = D_CTRL & 1;
    for (i = 0; i < 10; i++) {
        if (D_00492E78[i]) {
            DmaChReg *c = D_0046C550[i];
            c->sadr = 0;
            c->chcr = 0;
            c->tadr = 0;
            c->madr = 0;
            c->asr1 = 0;
            c->asr0 = 0;
        }
    }
    D_STAT = 0xff1f;
    D_STAT = D_STAT & 0xff1f0000;
    func_00266bd0(env, 20);
    func_00266d10(env);
    if (enable == 1) D_CTRL |= 1;
    return old;
}

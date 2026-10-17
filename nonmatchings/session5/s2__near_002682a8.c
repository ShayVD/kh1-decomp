#include "common.h"
s32 SignalSema(s32);
s32 PollSema(s32);
void FlushCache(s32);
s32 sceSifCallRpc(void *, u32, u32, void *, s32, void *, s32, void *, void *);
s32 func_0026a0e0(s32);
void func_00260738(void *, s32);
void func_00260928(s32, s32);
s32 func_00260918(s32);
void func_002608d0(u32, void *, s32);
void func_00268a78(const char *, ...);
extern s32 D_0046C62C, D_0046E094, D_0046E090, D_0046C208;
extern u8 D_0046E048[];
extern s32 D_0046D800[];
extern s32 D_0046DC40;
extern u8 D_0046BE90[];
typedef struct { s32 a, b; } Pair;
extern Pair D_0046C210[];
typedef struct { u8 pad[0x24]; void *server; } SifClient;
extern SifClient D_00673600;
typedef struct { s32 x0; s32 x4; s32 x8; s32 pad[2]; s32 x14; } McArg;
extern McArg D_00673680;
extern s32 D_00674BC0[];
extern u8 D_0066FB08[];
extern s32 D_0066FB80[];
extern char D_00492F70[];
#define UNCACHED(p) ((s32 *)((u32)(p) | 0x20000000))
typedef struct { s32 w[5]; u8 name[16]; } DbcSockCfg;

void func_00260938(void) {
    Pair *p = D_0046C210;
    Pair *q;
    u32 i;
    func_00260928(p[0].a, p[0].b);
    func_002608d0(0x80075000, D_0046BE90, 816);
    FlushCache(0);
    FlushCache(2);
    func_00260928(p[1].a, p[1].b);
    func_00260928(p[2].a, p[2].b);
    q = &p[3];
    for (i = 3; i < 8; i++) {
        func_00260928(q->a, func_00260918(q->a));
        q++;
    }
    D_0046C208 = func_00260918(3);
}
s32 func_0026a728(s32 a) {
    s32 *p = &D_0046DC40;
    s32 r;
    if (!func_0026a0e0(34)) return 0;
    D_0046DC40 = a;
    func_00260738(p, 4);
    if (sceSifCallRpc(D_0046E048, 34, 0, p, 4, D_0046D800, 4, 0, 0) < 0) {
        SignalSema(D_0046C62C);
        return 0;
    }
    r = *UNCACHED(D_0046D800);
    SignalSema(D_0046C62C);
    return r;
}
s32 func_002721e8(s32 a, s32 b) {
    s32 r;
    if (PollSema(D_0046E094) < 0) return -200;
    if (D_00673600.server == 0) {
        SignalSema(D_0046E094);
        return -100;
    }
    D_00673680.x8 = b;
    D_00673680.x4 = a;
    r = sceSifCallRpc(&D_00673600, 17, 1, &D_00673680, 48, D_00674BC0, 4, 0, 0);
    if (r == 0) D_0046E090 = 17;
    else SignalSema(D_0046E094);
    return r;
}
s32 sceDbcCreateSocket(DbcSockCfg *cfg, s32 a, s32 b) {
    s32 *p = D_0066FB80;
    s32 i;
    p[10] = a;
    p[11] = b;
    D_0066FB80[0] = cfg->w[0];
    p[1] = cfg->w[1];
    p[2] = cfg->w[2];
    p[3] = cfg->w[3];
    p[4] = cfg->w[4];
    {
        u8 *src = cfg->name;
        u8 *dst = (u8 *)&p[5];
        for (i = 0; i < 16; i++) dst[i] = src[i];
    }
    if (sceSifCallRpc(D_0066FB08, 0x80000901, 0, D_0066FB80, 1024, D_0066FB80, 1024, 0, 0) < 0) {
        func_00268a78(D_00492F70);
        return 0;
    }
    return p[9];
}

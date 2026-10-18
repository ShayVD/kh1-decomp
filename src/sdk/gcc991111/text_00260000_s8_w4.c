#include "common.h"
/* sceCdInit: the -1 stores in the order below, and `goto out` to a shared `return r` so reorg fills the b delay slot from the target (the move v0 is not in the stores block, so sched2 keeps lui 620 after sw 62C). */
s32 sceSifCallRpc(void *, u32, u32, void *, s32, void *, s32, void *, void *);
void func_00268a78(const char *, ...);
extern u8 D_0066FB08[];
typedef struct { s32 w[5]; u8 name[16]; s32 ret; void *a; void *b; } DbcBuf;
extern DbcBuf D_0066FB80;
extern char D_00492F70[];
typedef struct { s32 w[5]; u8 name[16]; } DbcSockCfg;
s32 sceDbcCreateSocket(DbcSockCfg *cfg, void *a, void *b) {
    DbcBuf *p = &D_0066FB80;
    s32 i;
    p->a = a;
    p->b = b;
    D_0066FB80.w[0] = cfg->w[0];
    p->w[1] = cfg->w[1];
    p->w[2] = cfg->w[2];
    p->w[3] = cfg->w[3];
    p->w[4] = cfg->w[4];
    for (i = 0; i < 16; i++) {
        p->name[i] = cfg->name[i];
    }
    if (sceSifCallRpc(D_0066FB08, 0x80000901, 0, &D_0066FB80, 1024, &D_0066FB80, 1024, 0, 0) < 0) {
        func_00268a78(D_00492F70);
        return 0;
    }
    return p->ret;
}

void scePrintf(const char *fmt, ...);
void sceSifInitRpc(s32 mode);
s32 sceSifBindRpc(void *client, u32 rpc, s32 mode);
s32 sceSifCallRpc(void *client, u32 fno, u32 mode, void *send, s32 ssize, void *recv, s32 rsize, void *end_func, void *end_para);
s32 GetThreadId(void);
void func_00260738(void *addr, s32 size);
void func_00269830(void);
void func_002698c8(void);
void func_00269a18(void);
s32 func_0026a070(s32 mode);
#define VS(x) (*(volatile s32 *)&(x))
#define UNC(x) (*(s32 *)((u32)&(x) | 0x20000000))
typedef struct { u8 pad[0x24]; void *server; } SifClient;
extern s32 D_0046C610, D_0046C620, D_0046C624, D_0046C628, D_0046C62C, D_0046C634, D_0046C638, D_0046C63C, D_0046C640, D_0046C644, D_0046C648, D_0046C64C, D_0046C650;
extern s32 D_00673350;
extern u8 D_00673568[];
extern s32 D_006735C0;
extern s32 D_0046D800[];
extern char D_00493218[], D_00493238[];
s32 sceCdInit(s32 mode) {
    s32 r, b, j;
    s32 v3, v1, v2;
    s32 *res;
    if (func_0026a070(1)) return 0;
    sceSifInitRpc(0);
    j = GetThreadId();

    VS(D_0046C624) = 1;
    D_00673350 = j;
    D_0046C640 = -1;
    D_0046C638 = -1;
    D_0046C648 = -1;
    D_0046C644 = -1;
    VS(D_0046C64C) = -1;
    D_0046C63C = -1;
    D_0046C634 = 0;
    D_0046C650++;

    while (1) {
        if ((b = sceSifBindRpc(D_00673568, 0x80000592, 0)) < 0) {
            if (D_0046C610 > 0) scePrintf(D_00493218, b, D_0046C650);
            j = 0x100000;
            while (--j != -1);
            continue;
        }
        if (((SifClient *)D_00673568)->server) {
            D_006735C0 = mode;
            D_0046C64C = 0;
            func_00260738(&D_006735C0, 4);
            res = D_0046D800;
            if (sceSifCallRpc(D_00673568, 0, 0, &D_006735C0, 4, res, 16, 0, 0) < 0) {
                VS(D_0046C624) = 0;
                return 0;
            }
            break;
        }
        j = 0x100000;
        while (--j != -1);
    }
    r = 1;
    v1 = UNC(res[1]);
    v2 = UNC(res[2]);
    v3 = UNC(res[3]);
    if (v3 != 255) {
        if (v3 == 254) D_0046C610 = 1;
        else if (v1 / 256 < 2 || v2 / 256 < 2) r = 2;
    }
    VS(D_0046C624) = 0;
    switch (mode) {
    case 0:
    case 1:
        break;
    case 5:
        if (D_0046C610 > 0) scePrintf(D_00493238);
        func_002698c8();
        VS(D_0046C628) = -1;
        VS(D_0046C62C) = -1;
        VS(D_0046C620) = -1;
        goto out;
    }
    func_00269830();
    func_00269a18();
out:
    return r;
}

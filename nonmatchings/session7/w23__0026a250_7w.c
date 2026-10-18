/* sceCdInit 0x26a250: 7 words off (session-7 w6 draft 9w), sdk/gcc991111 (same in sdk/gcc991111_as296). The -1 stores as separate statements in the order 673350, 640, 638, 648, 644, 634, 650++, 64C, 63C give the a2/a3/t0/t1 lui registers; left: t2/t3/v1 for 644/63C/634 (3w) and the exit, where the lui of D_0046C620 is scheduled above the VS(62C) store (2w). Volatility sweeps (greedy single/double VS flips) and flagsweep: nothing better. */
#include "common.h"
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
    D_0046C634 = 0;
    D_0046C650++;
    VS(D_0046C64C) = -1;
    D_0046C63C = -1;

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
        return r;
    }
    func_00269830();
    func_00269a18();
    return r;
}

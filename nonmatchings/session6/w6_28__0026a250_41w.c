/* ~41 words off (sdk/gcc991111, needs void scePrintf/sceSifInitRpc protos): structure matches; init-block store scheduling (650 load before volatile 624 store), result-read local regs (a1/a0 vs t1/a1), one store/lui swap at exit. */
/* Context: near/ctx.h (header of src/sdk/gcc991111/text_00260000_s2.c plus extra declarations). */
#include "ctx.h"
s32 sceCdInit(s32 mode) {
    s32 r, b, j;
    s32 v3, v1, v2;
    s32 *res;
    if (func_0026a070(1)) return 0;
    ((void (*)(s32))sceSifInitRpc)(0);
    j = GetThreadId();
    D_0046C650++;
    VS(D_0046C624) = 1;
    VS(D_00673350) = j;
    D_0046C63C = -1;
    D_0046C640 = -1;
    D_0046C638 = -1;
    D_0046C648 = -1;
    D_0046C644 = -1;
    D_0046C634 = 0;
    D_0046C64C = -1;
    while (1) {
        if ((b = sceSifBindRpc(D_00673568, 0x80000592, 0)) < 0) {
            if (D_0046C610 > 0) ((void (*)(const char *, ...))scePrintf)(D_00493218, b, D_0046C650);
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
    v3 = UNC(res[3]);
    v1 = UNC(res[1]);
    v2 = UNC(res[2]);
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
        if (D_0046C610 > 0) ((void (*)(const char *, ...))scePrintf)(D_00493238);
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

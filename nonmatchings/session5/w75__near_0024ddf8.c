#include "common.h"
typedef struct { s32 unk0; char *(*unk4)(void); s32 unk8; s32 unkC; s32 unk10; } HddCtx;
extern HddCtx D_0046A688;
extern s32 D_0046A614, D_0046A67C, D_0046A680, D_0046A678, D_0046A6AC, D_0046A608;
extern char D_0046A628[];
extern char D_00491978[];
extern char D_004919B0[];
s32 abs(s32);
s32 func_0024d4a0(void);
char *func_0011fd30(void);
s32 memcmp(const void *, const void *, u32);
s32 func_0024d9a0(void);
s32 func_0025e990(const char *);
s32 func_0024dcc8(const char *, const char *);
s32 func_0024dd98(s32);
s32 func_0024daa0(void);
s32 func_0024db78(s32);
s32 func_0024d8f0(void);
s32 func_0024d9f0(void);

s32 func_0024ddf8(void) {
    s32 i, r, ok;
    char *s, *p, *dst;
    D_0046A614 = 0;
    D_0046A680 = 0;
    D_0046A67C = 0;
    if (!func_0024d4a0()) return D_0046A67C;
    i = 0;
    D_0046A614 = 10;
    s = func_0011fd30();
    dst = D_0046A688.unk4() + 8;
    while (memcmp("SLPS", p = s + i++, 4) != 0);
    s = p + 5;
    dst[0] = s[0];
    dst[1] = s[1];
    dst[2] = s[2];
    dst[3] = s[4];
    dst[4] = s[5];
    if (memcmp(dst, "25198", 5) == 0) D_0046A678 = 1;
    func_0024d9a0();
    if (func_0025e990(D_00491978) < 0) goto fail;
    if (func_0024dcc8(D_004919B0, D_0046A628)) {
        ok = 1;
        D_0046A6AC = 1;
    } else {
        ok = 0;
        D_0046A6AC = 0;
    }
    D_0046A608 = func_0024dd98(0);
    D_0046A614 = 20;
    r = func_0024daa0();
    D_0046A614 = 30;
    switch (abs(r) & 15) {
    case 0:
        func_0024db78(D_0046A608);
        if (func_0024d8f0()) {
            D_0046A67C = 1;
            if (ok) {
                D_0046A67C = 3;
                D_0046A680 = 2;
            }
        } else if (func_0024d9f0()) {
            D_0046A67C = 3;
            func_0024d9a0();
            D_0046A680 = 2;
        } else {
            D_0046A67C = 2;
        }
        break;
    case 1:
        D_0046A680 = 1;
        D_0046A67C = 1;
        break;
    case 2:
        D_0046A67C = 1;
        D_0046A680 = 4;
        break;
    default:
    fail:
        D_0046A67C = 0;
        D_0046A680 = 3;
        break;
    }
    D_0046A614 = 130;
    return D_0046A67C;
}

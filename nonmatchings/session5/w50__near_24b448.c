#include "common.h"
typedef struct { u8 pad[0xc]; s32 xc; s32 x10; s32 x14; s32 x18; s32 x1c; } UiSet;
typedef struct { u8 lo:3; u8 mode:2; u8 hi:3; } Bits8;
extern volatile Bits8 D_002C5968;
extern UiSet *D_0046A038;
extern s32 D_0046A03C;
extern s32 D_0046A040;
extern s32 D_0046A044;
extern s32 D_0046A048;
extern UiSet *D_00669A18[];
void func_0024e1d0(void);
void func_0024b448(s32 i) {
    s32 *p40 = &D_0046A040;
    s32 *p48 = &D_0046A048;
    s32 s40 = *p40;
    s32 s48 = *p48;
    switch (D_002C5968.mode) { default: return; case 0: break; }
    {
        UiSet *p = D_00669A18[i];
        D_0046A038 = p;
        D_0046A03C = p->xc;
        D_0046A044 = p->x14;
        *p40 = p->x10;
        *p48 = p->x18;
        p->x1c++;
        func_0024e1d0();
        *p40 = s40;
        *p48 = s48;
    }
}

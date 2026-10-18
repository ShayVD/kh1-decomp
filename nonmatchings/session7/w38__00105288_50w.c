/* 50w hand, right size 580 and 7 saved regs (w12 draft 97w, 568 bytes). New: (1) loop 2 reads the pointer as `p = (s32 *)((s32 *)&D_002A6274)[1]` (a different HIGH expression from the top store of D_002A6278) so gcse PRE does not keep %hi(D_002A6278) across the calls; the original re-materialises that lui like this. (2) top store order from anneal3 (6270 6274 6294 6280 62A4 6278 62A0 6288 6290 6298 629C 628C 62A8 627C 6284). (3) loop 1 with a block-local `s32 *q` fixes b/p regs. Left: top store order/lui register assignment (orig source order gives 105w with the fix); loop-2 a0/a1 swap. */
/* 97w, 568 vs 580 bytes: orig uses 7 saved regs (s0-s6), ours fewer; orig loop 2 re-materialises lui for D_002A6278/627C */
/* ~109 words off (hand, strict): orig hoists all %hi luis into many regs incl. s0/s1/s6 (7 saved regs), keeps h in a0, mode in s2; loops count down with bound loaded once. */
#include "common.h"
extern s32 D_002A6270, D_002A6274, D_002A6278, D_002A627C, D_002A6280;
extern s32 D_002A6284;
extern s32 D_002A6288, D_002A628C, D_002A6290;
extern u32 D_002A6294, D_002A6298, D_002A629C, D_002A62A0, D_002A62A4, D_002A62A8;
extern s32 D_002A3F28, D_002A62E8, D_002A62F0;
void func_00115d18(s32);
void func_00104528(void);
void func_00104908(void);
s32 func_00105020(void);
s32 func_00105078(void);
void func_00105218(void);
void func_001050d0(void);
void func_00105288(u32 *h, s32 mode) {
    s32 i, n, b;
    s32 *p;
    D_002A6270 = (s32)h + h[0];
    D_002A6274 = (s32)h + h[6];
    D_002A6294 = h[7] / 20;
    D_002A6280 = (s32)h + h[12];
    D_002A62A4 = h[9] / 16;
    D_002A6278 = (s32)h + h[10];
    D_002A62A0 = h[11] / 4;
    D_002A6288 = (s32)h + h[2];
    D_002A6290 = (s32)h + h[8];
    D_002A6298 = h[3] / 12;
    D_002A629C = h[5] / 8;
    D_002A628C = (s32)h + h[4];
    D_002A62A8 = h[13] / 4;
    D_002A627C = (s32)h + h[14];
    b = (s32)h + h[16];
    D_002A6284 = b;
    func_00115d18(b);
    func_00104528();
    D_002A3F28 = 0;
    func_00104908();
    if (mode != 1) return;
    n = D_002A62A8;
    if (n > 0) {
        s32 *q = (s32 *)D_002A6280;
        b = D_002A6284;
        do {
            *q++ += b;
        } while (--n);
    }
    n = D_002A62A0;
    if (n > 0) {
        p = (s32 *)((s32 *)&D_002A6274)[1];
        do {
            if (*p != -1) *p += D_002A627C;
            p++;
        } while (--n);
    }
    D_002A62E8 = func_00105020();
    D_002A62F0 = func_00105078();
    func_00105218();
    func_001050d0();
}

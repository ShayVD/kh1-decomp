/* 00105288: 2w LCS (posoff 4), mode hand (strict), no context, size 580 right. Levers: D_002A6280 (the pointer loop 1 walks) stored as a member of a pointer-typed struct (alias set != int: the h[] u32 loads may pass it; plain globals are alias set 0 and conflict with everything), and h[12] / h[13] read into locals q, m before the D_002A6288 store (so lw 48/52 precede it), stores 6280 / 6288 / 6298 / 62A8 after. Without locals, D_002A62A8 must also be a pointer member (w47 g2 shape). Left: sched2 cycle where sw D_002A6288 (prio 67 via lw h[3] -> divu) issues before addu a1,a0,a1 (h+h[12], prio 26); original has the addu first. Diagnosis: the original needs prio(addu 6280) == prio(sw 6288), i.e. sw 6280 must also feed lw h[3] (conflict) with sw 6288 -> sw 6280 output dep, then the class-3 tie-break picks the addu; but every source where the 6280 store conflicts with int loads (plain, s32 member, any order, locals) loses an s-register (560 bytes). Sweeps: orders x {plain,ptr-member,int-member} for 6288/6280/62A8/6298, u32/ptr header loads, local forms: floor 2. */
#include "common.h"
typedef struct { u8 *p; } P1;
typedef struct { s32 v; } I1;
extern s32 D_002A3F28, D_002A62E8, D_002A62F0;
void func_00115d18(void);
void func_00104528(void);
void func_00104908(void);
s32 func_00105020(void);
s32 func_00105078(void);
void func_00105218(void);
void func_001050d0(void);
extern s32 D_002A6270;
extern s32 D_002A6274;
extern s32 D_002A6294;
extern s32 D_002A6290;
extern s32 D_002A62A4;
extern s32 D_002A6278;
extern s32 D_002A62A0;
extern s32 D_002A6288;
extern P1 D_002A6280;
extern s32 D_002A62A8;
extern s32 D_002A6298;
extern s32 D_002A628C;
extern s32 D_002A629C;
extern s32 D_002A627C;
extern s32 D_002A6284;
void func_00105288(u32 *h, s32 mode) {
    s32 n, b, q, m;
    s32 *p;
    D_002A6270 = (s32)h + h[0];
    D_002A6274 = (s32)h + h[6];
    D_002A6294 = h[7] / 20;
    D_002A6290 = (s32)h + h[8];
    D_002A62A4 = h[9] / 16;
    D_002A6278 = (s32)h + h[10];
    D_002A62A0 = h[11] / 4;
    q = (s32)h + h[12];
    m = h[13] / 4;
    D_002A6280.p = (u8 *)q;
    D_002A6288 = (s32)h + h[2];
    D_002A6298 = h[3] / 12;
    D_002A62A8 = m;
    D_002A628C = (s32)h + h[4];
    D_002A629C = h[5] / 8;
    D_002A627C = (s32)h + h[14];
    D_002A6284 = (s32)h + h[16];
    func_00115d18();
    func_00104528();
    D_002A3F28 = 0;
    func_00104908();
    if (mode != 1) return;
    n = D_002A62A8;
    if (n > 0) {
        s32 *q;
        b = D_002A6284;
        q = (s32 *)(s32)D_002A6280.p;
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

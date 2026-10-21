#include "common.h"
/* 00105288 (hand, strict): MATCH, natural (no dead statements). h as a header struct pointer (field loads are MEM_IN_STRUCT_P), D_002A6280 a plain s32 global stored through the hoisted &D_002A6280 pseudo: in sched1 canon_rtx turns that address into the symbol, so fixed_scalar_and_varying_struct_p separates it from the h->f3 load; after reload ($21) the address varies and sched2 gets the sw 6280 -> lw h3 edge. D_002A62A8 is a one-field int struct so its store keeps conflicting with the h loads in sched1 (a plain scalar there frees sched1 and costs 25w). */
#include "data/types/text_00100000_s11_w68.h"
extern s32 D_002A3F28, D_002A62E8, D_002A62F0;
void func_00115d18(void);
void func_00104528(void);
void func_00104908(void);
s32 func_00105020(void);
s32 func_00105078(void);
void func_00105218(void);
void func_001050d0(void);
extern s32 D_002A6270;
#include "data/pieces/D_002A6274.h"
extern s32 D_002A6294;
extern s32 D_002A6290;
extern s32 D_002A62A4;
extern s32 D_002A6278;
extern s32 D_002A62A0;
extern s32 D_002A6288;
extern s32 D_002A6280;
#include "data/pieces/D_002A62A8.h"
extern s32 D_002A6298;
extern s32 D_002A628C;
extern s32 D_002A629C;
extern s32 D_002A627C;
extern s32 D_002A6284;
typedef struct { u32 f0; u32 f1; u32 f2; u32 f3; u32 f4; u32 f5; u32 f6; u32 f7; u32 f8; u32 f9; u32 f10; u32 f11; u32 f12; u32 f13; u32 f14; u32 f15; u32 f16; } H;
void func_00105288(H *h, s32 mode) {
    s32 n, b, q, m;
    s32 *p;
    D_002A6270 = (s32)h + h->f0;
    (*(s32 *)&D_002A6274) = (s32)h + h->f6;
    D_002A6294 = h->f7 / 20;
    D_002A6290 = (s32)h + h->f8;
    D_002A62A4 = h->f9 / 16;
    D_002A6278 = (s32)h + h->f10;
    D_002A62A0 = h->f11 / 4;
    q = (s32)h + h->f12;
    m = h->f13 / 4;
    D_002A6280 = q;
    D_002A6288 = (s32)h + h->f2;
    D_002A6298 = h->f3 / 12;
    D_002A62A8.v = m;
    D_002A628C = (s32)h + h->f4;
    D_002A629C = h->f5 / 8;
    D_002A627C = (s32)h + h->f14;
    D_002A6284 = (s32)h + h->f16;
    func_00115d18();
    func_00104528();
    D_002A3F28 = 0;
    func_00104908();
    if (mode != 1) return;
    n = D_002A62A8.v;
    if (n > 0) {
        s32 *q;
        b = D_002A6284;
        q = (s32 *)D_002A6280;
        do {
            *q++ += b;
        } while (--n);
    }
    n = D_002A62A0;
    if (n > 0) {
        p = (s32 *)((s32 *)((s32 *)&D_002A6274))[1];
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
#include "data/data_002A.h"

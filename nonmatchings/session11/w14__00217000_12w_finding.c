/* 00217000 finding: LCS 12 (best stays s7 w29 at 8), hand/nostrict. 'tbl = D_003F2C40; off = sel * 20; cd = D_00642CD8; if (a) c = ((E20 *)((u8 *)tbl + off))->x10; else c = <same>;' (tbl local in the head block, load in identical arms) gives the original's split la in ONE register (lui/addiu tied, interleaved with the index math) and keeps 'move t2,v0' before the jal func_00207870. Left: tbl reg v1 (orig a0), the D_00642CD8 load/shift and the D_003F4368 load (orig into t4) sit in the join block after the arms instead of interleaved; li 2/li 5 order after func_00170dd8. Single-block forms always fold sym+16 in combine (it merges high+lo_sum+addu+mem); a volatile load stops the +16 fold but combine still folds the la into the addu. */
/* func_00217000: hand/nostrict, 25 words off by position (w16 draft: 56), right size 1168 (was 1164), 11 by sequence diff. w29: the split `la a0,D_003F2C40; addu; lw 16(reg)` comes from a pointer set in both arms of an if/else after the third func_00206130 call: `if (a) tbl = D_003F2C40; else tbl = D_003F2C40; c = tbl[sel].x10;` (combine cannot fold the la across the block boundary; jump2 cross-jumps the identical arms and deletes the branch). Condition on a or k (s-regs, no extra insn); `sel == 1` leaves a dead li, `sel` swaps s5/s6. Left: (1) lui of the la lands in v0 with addiu a0,v0 and the la is scheduled ahead of the index math (orig lui a0 ... addiu a0,a0 interleaved: in the original the la was in the same block as its use at sched2 time); (2) `move t2,v0` before func_00207870 now sits in its delay slot (sched2 order in that block changed with the new block end); (3) after func_00170dd8 orig li v1,2; li a0,5; subu; sw (ours li a0 first, sw CD8 before subu): block locals, store order, `two` local all unchanged. No flag helps. */
#include "common.h"
typedef struct Obj { u8 pad[0x10]; struct Obj *x10; u8 p14[0x10]; struct Obj *x24; s32 x28; u8 p2c[0xCE - 0x2C]; s16 xce; s16 xd0; s16 xd2; } Obj;
typedef struct { u8 pad[4]; u32 x4; u32 x8; u32 xc; u32 x10; } Cfg;
typedef struct { u8 pad[0x40]; u8 items[0x30]; } Sub;
typedef struct { u8 pad[4]; Sub sub; } Rec74;
typedef struct { Rec74 r[10]; u8 pad[6]; u8 x48e[0x10b]; u8 x599[1]; } S4BE8;
typedef struct { s32 *p; s32 n; } PN;
typedef struct { s32 x0; s32 x4; s32 x8; u8 padc[0x20 - 0xC]; u8 x20[1]; } S34B8;
typedef struct { u8 pad[16]; s32 x10; } E20;
extern Cfg *D_00425BC8;
extern S4BE8 *D_00304BE8;
extern u32 D_003E3D68;
extern s32 D_00642CCC;
extern s32 D_00642CD8;
extern s32 D_00642CDC;
extern s32 D_00642CE0;
extern PN D_003F40F8[];
extern S34B8 *D_003F34B8;
extern s32 D_003F43F0[];
extern s32 D_003F4408[];
extern s32 D_003F4368[];
extern E20 D_003F2C40[];
s32 func_001f42b8(void *);
s32 func_001f3758(void *);
void func_0011d768(s32);
void func_001f3d58(void *, s32);
void func_00216ea8(void);
void func_0020bd18(void *, s32);
s32 func_001fe570(void *);
s32 func_00170dd8(s32, s32);
void func_0020be10(s32);
void func_001f3dc0(Obj *);
void func_00206130(void *, s32, s32, s32, s32, s32);
s32 func_001ee5f0(s32);
void func_00207870(void *, s32, s32, s32, s32, s32, s32);
void func_002078f0(void *, s32, s32, s32, s32, s32, s32, s32, s32);
s32 func_001fc308(void *, s32, s32, s32, s32, s32, s32, s32, s32);

void func_00217000(Obj *a) {
    s32 k, cur, ch, sel, c;
    s32 *pn;
    s32 *p, *p2;
    Obj *o;
    Cfg *cfg;
    E20 *tbl; s32 off, cd;
    k = D_00304BE8->x48e[D_00642CCC];
    pn = D_003F40F8[k].p;
    sel = 11;
    if (func_001f42b8(a)) {
        sel = 1;
        if (D_00425BC8->x8 & 0x4000) {
            func_001f3758(a);
            func_0011d768(3);
            func_001f3d58(a, 5);
            func_001f3d58(a->x24, 5);
            func_001f3758(a);
            func_00216ea8();
            goto draw;
        }
        cur = D_00642CCC;
        if (D_003E3D68 >= 3) {
            ch = 0;
            if (D_00425BC8->x10 & 0x10000010) {
                if (cur >= 2) {
                    cur--;
                    ch = 1;
                } else if (D_00425BC8->x8 & 0x10000010) {
                    cur = D_003E3D68 - 1;
                    ch = 1;
                }
            } else if (D_00425BC8->x10 & 0x40000040) {
                if (cur < D_003E3D68 - 1) {
                    cur++;
                    ch = 1;
                } else if (D_00425BC8->x8 & 0x40000040) {
                    cur = 1;
                    ch = 1;
                }
            }
            if (ch) {
                func_00216ea8();
                D_00642CCC = cur;
                { s32 n2 = D_00304BE8->x48e[cur];
                D_00642CD8 = D_003F34B8->x20[n2];
                D_00642CDC = 0;
                k = n2;
                pn = D_003F40F8[n2].p; }
                func_0011d768(1);
            }
        }
        func_0020bd18(a, 8);
        ch = 0;
        if (D_00425BC8->x10 & 0x80000080) {
            p = &D_00642CD8;
            if (*p > 0) {
                *p = *p - 1;
                ch = 1;
            } else if (D_00425BC8->x8 & 0x80000080) {
                *p = 5;
                ch = 1;
            }
        } else if (D_00425BC8->x10 & 0x20000020) {
            p2 = &D_00642CD8;
            if (*p2 < 5) {
                *p2 = *p2 + 1;
                ch = 1;
            } else if (D_00425BC8->x8 & 0x20000020) {
                *p2 = 0;

                ch = 1;
            }
        }
        if (ch) {
            if ((o = a->x10)) o->x24 = (Obj *)D_003F43F0[D_00642CD8];
            func_0011d768(1);
        }
        if (func_001fe570(a)) {
            s32 *pd, *pe;
            func_0011d768(2);
            func_00216ea8();
            D_003F34B8->x20[k] = 5;
            pd = &D_00642CDC;
            pe = &D_00642CE0;
            c = func_00170dd8(k, pn[*pd]);
            D_00642CD8 = 5;
            *pe = 2 - c;
            if ((o = a->x10)) o->x24 = (Obj *)D_003F4408[pn[*pd]];
            o = a->x24;
            o->xd2 = *(u16 *)pd << 4;
            func_0020be10(16);
            func_001f3dc0(o);
        }
    }
draw:
    func_00206130(a, -223, 12, 76, 2, 0x80FE7266);
    func_00207870(a, 11, 2, -148, 0, 122, func_001ee5f0(k));
    func_00206130(a, -26, 12, 26, 2, 0x80FE7266);
    tbl = D_003F2C40; off = sel * 20; cd = D_00642CD8; if (a) c = ((E20 *)((u8 *)tbl + off))->x10; else c = ((E20 *)((u8 *)tbl + off))->x10;
    func_002078f0(a, sel, 2, 2, 0, 0, 342, 171, D_003F4368[cd]);
    func_001fc308(a, 16, 7, 0, 0, 15, 0, c, c);
    func_001fc308(a, 316, 7, 0, 0, 16, 0, c, c);
}

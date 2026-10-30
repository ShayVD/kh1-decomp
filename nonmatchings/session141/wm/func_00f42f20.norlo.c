/* Round 27 wwm1: score 84 -> 26 at exact size (976). Value bug found by valaudit: func_00f29aa0 takes the packet-pointer cell (u64 **, as in f23018), and the draft passed *D_00F85160. Also D_002C5958 is u32 (srl, as in f33270/f3e988), and s.a for the D_00F850E0 calls is read through ssf() (direct D_00F86500[..].s.a folded +4 into the symbol). Left: v0/v1 for the 15032 index and a1/v1 for a in the else test (bne vs bnel). Earlier header below. */
/* Round 44 wwm2: score 104 -> 84 under the norlo build mode (r44/modescan.py). Earlier header below. */
/* 166 words, score 104 (1016 vs 976; was 205 words, score 118). Round 32 wwm2: a CONTEXT_ONLY func_00f42ce0 (ctx2) took it to 170, hill2 (D_00F9B1E0 = 1 before D_00F9B1DC = 1.0f) to 166. Earlier header: 205 words left (round 12): main world-map loop. Target hoists the plain D_00F86500 base and +128/+1216/+192 offsets into s5..s7 and keeps a/b on the stack. The ssf() helper for the x branch helps (from 228); a local W pointer or wb() helper for the D_00F850E0 accesses is worse. */
#include "ovl.h"
typedef struct { s32 id; s32 a; s32 b; f32 val; f32 v2; s32 dir; } Sub;
typedef struct { f32 m0[4][4]; f32 m1[4][4]; f32 m2[4][4]; f32 m3[16][4][4]; f32 m4[2][4][4]; Sub s; u8 pad2[0x590 - 0x558]; } W;
typedef struct { s32 w0; s32 w4; s32 w8; } J;
extern W D_00F86500[];
extern f32 D_00F9B1DC, D_00F9B1D8, D_00F9B1D0, D_00F9B1D4;
extern s32 D_00F9B1E0, D_00F850BC, D_00F850C0, D_00F9B2F0, D_00F87028, D_00F850E0;
extern u32 D_002C5958;
extern s32 D_00F9B1C8, D_00F87038, D_00F850F4, D_00F850AC, D_00F9B1CC, D_00F87024;
extern u64 **D_00F85160;
J *func_001ba488(s32);
CONTEXT_ONLY void func_00f42ce0(s32 a0) {}
void func_00f294a0(s32, s32, s32);
void func_00f29aa0(s32, u64 **, s32, f32 (*)[4], f32 (*)[4], f32 (*)[4], f32);
s32 func_00f40c98(void);
s32 func_00f66ac8(u64 *);
s32 func_00f66ae0(u64 *);
u64 *func_00f66b78(s32);
void func_00f66b90(u64 *);
void func_00f66f78(s32, s32);
void func_00f344f0(s32);
void func_00f3e988(void);
void func_00f33690(void);
void func_00f33270(void);
void func_00f32ac8(void);
void func_00f324f0(f32 (*)[4]);
s32 func_00f64c38(s32, s32);
void func_00f2a1e0(f32, f32);
void func_001bfac8(void);

static inline Sub *ssf(s32 idx) { s32 b_ = (s32)D_00F86500; return (Sub *)((u8 *)(Sub *)(idx * 0x590 + 0x540) + b_); }
void func_00f42f20(void) {
    f32 m[4][4];
    s32 a;
    s32 b;
    s32 x;
    s32 r;
    u64 *p;
    Sub *s;

    a = 0;
    D_00F9B1E0 = 1;
    b = 0;
    D_00F9B1DC = 1.0f;
    for (;;) {
        if (func_001ba488(0)->w8 & 0x200) {
            D_00F9B1E0++;
            D_00F9B1E0 %= 3;
        }
        if (D_00F850BC == 0 && D_00F850C0 == 0 && D_00F9B2F0 == 0) {
            func_00f42ce0(D_00F9B1E0);
        } else {
            func_00f42ce0(0);
        }
        func_00f294a0(0x11170, 10464, D_00F87028);
        if (func_00f40c98() == 2) {
            x = D_00F850E0 ^ 1;
            a = 0;
            s = ssf(x);
            func_00f294a0(15000, 10752, s->b);
            func_00f29aa0(15001, D_00F85160, s->a, D_00F86500[x].m3[0], D_00F86500[x].m4[0], D_00F86500[x].m2, 1.0f);
            func_00f294a0(15032, 10752, D_00F86500[D_00F850E0].s.b);
            func_00f29aa0(15033, D_00F85160, ssf(D_00F850E0)->a, D_00F86500[D_00F850E0].m3[0], D_00F86500[D_00F850E0].m4[0], D_00F86500[D_00F850E0].m2, D_00F9B1D8);
        } else {
            if (a == 0 || D_00F850BC != 0) {
                func_00f294a0(15000, 10752, D_00F86500[D_00F850E0].s.b);
            }
            a = 1;
            func_00f29aa0(15001, D_00F85160, ssf(D_00F850E0)->a, D_00F86500[D_00F850E0].m3[0], D_00F86500[D_00F850E0].m4[0], D_00F86500[D_00F850E0].m2, 1.0f);
        }
        p = func_00f66b78(func_00f66ac8(*D_00F85160));
        p[0] = 0x31000070;
        p[1] = 78;
        p += 2;
        p[0] = 0x5000D;
        p[1] = 71;
        p += 2;
        func_00f66b90(p);
        func_00f66f78(15063, func_00f66ae0(p));
        *D_00F85160 = p;
        func_00f40c98();
        if (D_00F9B1C8 != 0) {
            if (b == 0) {
                b = 1;
                func_00f294a0(50000, 9728, D_00F87038);
            }
            if (D_00F850F4 != 0) func_00f344f0(50001);
        }
        if (D_00F850AC != 0 && !((D_002C5958 >> 3) & 1)) {
            func_00f3e988();
            func_00f33690();
            func_00f33270();
        } else {
            func_00f32ac8();
            func_00f324f0(m);
        }
        if (D_00F9B1CC != 0 && func_00f40c98() < 2) {
            r = func_00f64c38(0, D_00F87024);
            if (r) func_00f294a0(20000, 11776, r);
            func_00f2a1e0(D_00F9B1D0, D_00F9B1D4);
        }
        func_001bfac8();
    }
}

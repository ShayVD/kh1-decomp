/* 00177ac0: 2w off, nostrict (no ctx). Only: orig 'bnez v0(b)' at 0x177d40 jumps to the 'beqz v0' test after the func_001770b8 call (0x177d58) and the a==0,b==0 path jumps straight to end; ours jumps into the body. Need a form of 'if (b || (a && func_001770b8()))' that is not threaded. */
#include "common.h"
typedef struct { f32 org[4]; f32 dir[4]; f32 hit[4]; s16 id; s16 pad32; s32 x34; u8 pad38[8]; } Ray7A;
typedef struct { f32 a[4]; f32 b[4]; u8 pad[32]; } Seg7A;
typedef struct { f32 x0, x4, x8; } S58F0;
extern f32 D_005758D0[4];
extern f32 D_005758E0[4];
extern S58F0 D_005758F0;
extern f32 D_00362684;
extern f32 D_002BBDFC;
extern f32 D_002C58D0[4];
extern f32 D_002C58A0[4];
typedef struct { f32 x0, x4; } S2680;
extern S2680 D_00362680;
extern u64 D_002C5BB0;
f32 sinf(f32);
void func_00105a70(s32, s32, f32 *);
void func_00118d78(Ray7A *);
s32 func_00119688(Seg7A *);
f32 func_00120c88(f32);
f32 func_00124d28(f32 *, f32 *);
s32 func_001770b8(void);
void func_002672f8(f32 *, f32 *, f32 *);
void func_00267370(f32 *, f32 *, f32 *);
void func_002673b8(f32 *, f32 *);
void func_00267518(f32 *, f32 *, f32 *);
void func_00267530(f32 *, f32 *, f32 *);
void func_00267560(f32 *, f32 *, f32);
void func_002675a8(f32 *, f32 *);
void func_00267810(f32 *, f32 *, f32);

s32 func_00177ac0(void) {
    Ray7A r;
    f32 v40[4];
    f32 v50[4];
    f32 v60[4];
    f32 v70[4];
    f32 v80[4];
    f32 unk[3][4];
    Seg7A s;
    s32 ok, a, b;
    f32 ang, d;

    if (D_005758F0.x8 > 0.0f) {
        f32 t = sinf((1.0f - D_005758F0.x8 / 40.0f) * 3.1415928f * 0.5f);
        D_00362684 = D_005758F0.x0 + D_005758F0.x4 * t;
        D_005758F0.x8 -= D_002BBDFC;
        return 1;
    }
    D_005758F0.x8 = 0.0f;
    func_00267530(v40, D_005758E0, D_005758D0);
    func_00267530(v50, D_005758D0, D_005758E0);
    func_002673b8(v70, v50);
    v70[1] = 0.0f;
    func_00267810(v80, D_002C58D0, 1.5707962f);
    func_002672f8(v70, v80, v70);
    func_00267560(v70, v70, 50.0f);
    func_002675a8(r.dir, v50);
    func_00267518(r.org, D_005758E0, v70);
    func_00118d78(&r);
    if (r.id != -1) ok = 1; else {
        func_00267560(v70, v70, -1.0f);
        func_00267518(r.org, D_005758E0, v70);
        func_00118d78(&r);
        ok = r.id != -1;
    }

    if (ok) {
        func_002673b8(v70, v40);
        func_00267560(v70, v70, 300.0f);
        func_002675a8(s.a, D_005758D0);
        func_00267810(v80, D_002C58D0, 0.52359875f);
        func_002672f8(s.b, v80, v70);
        a = func_00119688(&s) != -1;
        func_00267810(v80, D_002C58D0, -0.52359875f);
        func_002672f8(s.b, v80, v70);
        b = func_00119688(&s) != -1;
        if (a && b) return 0;
        if (b || (a && func_001770b8())) {
            func_00105a70(r.x34, r.id, v60);
            func_00267530(v70, r.hit, D_005758D0);
            v70[1] = v60[1] = 0.0f;
            func_002673b8(v70, v70);
            func_002673b8(v60, v60);
            ang = func_00124d28(v60, D_002C58A0);
            func_00267370(v70, v70, v60);
            d = func_00120c88(v70[1] >= 0.0f ? ang + 1.5707962f : ang - 1.5707962f);
            d = d - func_00120c88(D_00362680.x4);
            if (fabsf(d) > 3.1415928f) {
                if (d < 0.0f) d += 6.2831855f; else d -= 6.2831855f;
            }
            D_005758F0.x0 = func_00120c88(D_00362680.x4);
            D_005758F0.x4 = d;
            D_005758F0.x8 = 40.0f;

        }
    }
    if (D_002C5BB0 & ((u64)0xC000 << 30)) D_005758F0.x8 = 0.0f;
    return 1;
}

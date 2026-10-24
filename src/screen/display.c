/* The display and the frame counters, 0x00110000-0x00110fc8: func_00110218
 * runs once a frame (it reads the GS CSR field bit at 0x12001000 and steps
 * the counters D_002BBDF0 / D_002BBDF4 / D_002BBDF8, D_002BBDF4 being the
 * play timer's), func_001100a8 builds and sends the drawing environment
 * (sceGsPutDrawEnv), func_00110458 resets the frame state, func_00110a48
 * copies the six camera matrices and calls the unmatched func_00110618
 * (view, projection and screen matrices), and func_00110e68 a cosf wobble
 * of the screen scale. Read from the
 * code, not proved by a boot (docs/modules.md "Session 55"). */
#include "m2c.h"
#include "data/bss_004D.h"
#include "data/pieces/D_002BCCA0.h"
#include "data/pieces/D_002BCCE0.h"
#include "data/pieces/D_002BCD60.h"
#include "data/pieces/D_002BBDE0.h"
#include "data/pieces/D_002BC070.h"
#include "common.h"
#include "platform/thread.h"
#include "platform/gs.h"
#include "data/bss_004E.h"
#include "data/types/text_00110000_h29_p.h"
#include "data/pieces/D_002BBDF0.h"
#include "data/pieces/D_002BBDF4.h"
#include "data/pieces/D_002BBDF8.h"
#include "data/pieces/D_002A6208.h"
#include "data/pieces/D_002BCB60.h"
#include "vm/script_vm.h"
#include "data/bss_0049.h"
#include "data/types/text_00100000_h2.h"
#include "data/pieces/D_002B677C.h"
#include "data/pieces/D_002B6778.h"
#include "data/types/text_00100000_h2_p.h"
#include "data/pieces/D_002B75A0.h"
#include "data/pieces/D_002BD118.h"
#include "data/pieces/D_002BCAF0.h"
#include "data/pieces/D_002BC0A8.h"
#include "data/pieces/D_002BCDAC.h"
#include "data/types/text_00110000_h52.h"
#include "data/pieces/D_002BBF20.h"
#include "data/pieces/D_002BBEE0.h"
#include "data/pieces/D_002BBEA0.h"
#include "data/pieces/D_002BBE60.h"
#include "data/pieces/D_002BBE20.h"
#include "data/pieces/D_002BBF60.h"
#include "data/pieces/D_002BBFA0.h"
#include "data/pieces/D_002BBFE0.h"
#include "data/pieces/D_002BC020.h"
#include "data/pieces/D_002E2700.h"
#include "data/pieces/D_002BCDA0.h"
#include "data/pieces/D_002E26A0.h"
#include "data/pieces/D_002BC0F0.h"
#include "data/pieces/D_002A3F60.h"
#include "data/pieces/D_002A4060.h"
#include "data/pieces/D_002BCB40.h"
#include "data/pieces/D_002BCB50.h"

/* func_00110020 (from auto/text_00110000_11.c). */
extern s32 D_004D8EC0[];
void func_00110020(s32 arg0, s32 arg1) {
    D_004D90FC = 1;
    D_004D8EC0[6] = (s32) ((((D_004D8EC0[6] & ~0xFFF) | (arg0 & 0xFFF)) & 0xFF800FFF) | ((arg1 & 0x7FF) << 0xC));
}

/* func_00110068 (from auto/text_00110000_11.c). */
M2C_UNK func_0010fea0();
M2C_UNK func_00266c30(M2C_UNK);
M2C_UNK func_00267fe0();
extern f32 D_002BBDEC;
void func_00110068(void) {
    PlatGsResetPath();
    func_00266c30(1);
    func_00267fe0();
    D_002BBDEC = 1.0f;
    func_0010fea0();
}

/* func_001100a8 (from hand/text_00110000_h29.c). */
typedef unsigned int u128 __attribute__((mode(TI)));
typedef struct { u64 d, a; } W29Ad;
typedef struct {
    union {
        u128 q;
        struct {
            u64 nloop : 15;
            u64 eop : 1;
            u64 pad16 : 16;
            u64 id : 14;
            u64 pre : 1;
            u64 prim : 11;
            u64 flg : 2;
            u64 nreg : 4;
            u64 regs : 4;
            u64 regs_hi : 60;
        } b;
    } tag;
    W29Ad r[31];
} W29Env;
W29Env D_004D8EF0 ALIGNED(16);
extern u64 D_002BC750[];
extern u64 D_002BC7C0[];
extern u64 D_002BC830[];
void func_001100a8(void) {
    s32 i;
    for (i = 0; i < 13; i++) {
        D_004D8EF0.r[i].d = D_002BC830[i];
        D_004D8EF0.r[i].a = D_002BC750[i];
        D_004D8EF0.r[i + 13].d = D_002BC830[i];
        D_004D8EF0.r[i + 13].a = D_002BC7C0[i];
    }
    D_004D8EF0.tag.q = 0;
    D_004D8EF0.tag.b.nloop = 31;
    D_004D8EF0.tag.b.eop = 1;
    D_004D8EF0.tag.b.nreg = 1;
    D_004D8EF0.tag.b.regs = 0xe;
    D_004D8EF0.r[26].d = 1;
    D_004D8EF0.r[26].a = 0x1a;
    D_004D8EF0.r[27].d = 1;
    D_004D8EF0.r[27].a = 0x46;
    D_004D8EF0.r[28].d = 0;
    D_004D8EF0.r[28].a = 0x45;
    D_004D8EF0.r[29].d = 0;
    D_004D8EF0.r[29].a = 0x49;
    D_004D8EF0.r[30].d = -4;
    D_004D8EF0.r[30].a = 0x44;
    PlatFlushCache(0);
    PlatGsSyncPath(0, 0);
    PlatGsPutDrawEnv(&D_004D8EF0);
}

/* func_001101e8 (from auto/text_00110000_11.c). */
void func_001104c0();
#define func_001100a8 ((M2C_UNK (*)()) func_001100a8)
void func_001101e8(void) {
    PlatGsResetGraph(0, 1, 2, 0);
    func_001104c0();
    func_001100a8();
}
#undef func_001100a8

/* func_00110218 (from hand/text_00110000_h52.c). */
extern s32 D_002BBDE8;
extern volatile s32 D_002BD114;
extern s32 D_002BCC24;
extern volatile u32 D_004D90F0;
extern volatile s32 D_004D90F4;
s32 func_00111798(void);
void func_001117b8(void);
void func_0010c378(void);
s32 func_00110218(void) {
    if (PlatGsGetCsr() & PLAT_GS_CSR_FIELD) {
        D_002BBDE8 = 1;
    } else {
        D_002BBDE8 = 0;
    }
    if (D_002BD114 == 0 && D_002BCC24 == 0) {
        D_002BBDF0++;
    }
    if (D_002BBDF4 < D_004D90F0) {
        D_002BBDF4 = D_002BBDF4 + 1;
    } else if (func_00111798() < 3) {
        if (D_002BBDF4 < D_004D90F0 + 60) {
            D_002BBDF4 = D_002BBDF4 + 1;
        } else {
            func_001117b8();
            D_002BBDF4 = 0;
        }
    } else {
        D_002BBDF4 = D_004D90F0;
    }
    D_002BBDF8++;
    D_004D90F4++;
    func_0010c378();
    return 0;
}

/* func_00110360 (from auto/text_00110000_11.c). */
void func_00110360(void) {
    D_002BC070[0] = 0x80;
    D_002BC070[3] = 0x80;
    D_002BC070[2] = 0x80;
    D_002BC070[1] = 0x80;
}

/* func_00110380 (from auto/text_00110000_11.c). */
void func_00110380(void) {
    D_002BC070[0] = 0;
    D_002BC070[3] = 0;
    D_002BC070[2] = 0;
    D_002BC070[1] = 0;
}

/* func_001103a0 (from hand/text_00110000_h29.c). */
extern s32 D_002A61F4;
extern s32 D_002BBE18;
extern s32 D_002A61F0;
extern s32 D_002BBE04;
extern s32 D_002BBE14;
extern s32 D_002A6204;
extern s32 D_002BC738;
extern s32 D_002BC060[4];
extern s32 D_002BC080[4];
extern s32 D_002BC0B0[4];
void func_001103a0(void) {
    D_002BBE04 = 0;
    D_002BBE14 = 0;
    D_002BBE18 = 0;
    D_002A6208 = 0;
    D_002A61F4 = 0;
    D_002BC738 = 0;
    D_002A6204 = 0;
    D_002A61F0 = 0;
    D_002BC060[0] = D_002BC060[1] = D_002BC060[2] = 0;
    D_002BC060[3] = 0x80;
    D_002BC080[0] = D_002BC080[1] = D_002BC080[2] = 0x80;
    D_002BC080[3] = 0x60;
    D_002BC0B0[0] = D_002BC0B0[1] = D_002BC0B0[2] = 0xFF;
    D_002BC0B0[3] = 0;
    func_00110360();
}

/* func_00110448 (from auto/text_00110000_6.c). */
void func_00110448(s32 arg0) {
    D_002BBDF4 = arg0;
}

/* func_00110458 (from hand/text_00100000_h2.c). */
extern s32 D_002B6774;
extern f32 D_002BBDFC;
extern s32 D_002BBE10;
extern s32 D_002BBE0C;
extern s32 D_002BD110;
void sceVu0UnitMatrix(f32 (*)[4]);
void func_00110458(void) {
    D_002BBDF0 = 0;
    D_002BBDF8 = 0;
    D_002BBE10 = 0;
    D_002BBE0C = 0;
    D_002BBDFC = D_002BBDEC;
    sceVu0UnitMatrix(D_002BCAF0);
    D_002B6774 = 0;
    D_002BD110 = 0;
}

/* func_001104c0 (from auto/text_00110000.c). */
M2C_UNK func_00266a10(M2C_UNK *);
void func_001104c0(void) {
    func_00266a10(&func_00110218);
}

/* func_001104e0 (from hand/text_00110000_h29.c). */
extern f32 D_002BBE00;
extern s32 D_002BC740;
void func_0010c348(void);
void func_001104e0(void) {
    s32 i;
    func_0010c348();
    D_002BBDFC = (f32)D_004D90F4 * D_002BBDEC;
    if (D_004D90F4 < D_002BBE0C + 1) {
        for (i = 0; i < D_002BBE0C; i++) {
            func_0010c348();
            D_002BBDFC = (f32)D_004D90F4 * D_002BBDEC;
        }
    }
    if (D_002BBE10) D_002BBDFC = D_002BBDEC + D_002BBDEC;
    D_002BBDFC = D_002BBDFC * D_002BBE00;
    if (D_002BC740 != 1) {
        if (D_002BBDFC > 5.0f) D_002BBDFC = 5.0f;
    } else {
        D_002BBDFC = 128.0f;
    }
    D_004D90F4 = 0;
}

/* func_00110a48 (from hand/text_00110000_h52.c). */
extern Mtx52 D_004D9140;
extern Mtx52 D_004D9100;
extern Mtx52 D_004D91C0;
extern Mtx52 D_004D8E40;
extern Mtx52 D_004D9180;
extern Mtx52 D_004D8E80;
void func_00110ce0(void);
void sceVu0CopyMatrix(void *, void *);
void func_00110618(void *, void *, void *, void *, void *, void *, f32, f32, f32, f32, f32, f32, f32, f32, f32, f32);
void func_00110a48(f32 x) {
    func_00110ce0();
    sceVu0CopyMatrix(D_004D8E40, D_002BBE20);
    sceVu0CopyMatrix(D_004D9100, D_002BBE60);
    sceVu0CopyMatrix(D_004D9140, D_002BBEA0);
    sceVu0CopyMatrix(D_004D9180, D_002BBEE0);
    sceVu0CopyMatrix(D_004D91C0, D_002BBF20);
    sceVu0CopyMatrix(D_004D8E80, D_002BBF60);
    func_00110618(D_002BBE20, D_002BBE60, D_002BBEA0, D_002BBEE0, D_002BBF20, D_002BBF60, x,
                  0.7999999523162842f, 0.839999854564666748046875f, 2048.0f, 2048.0f, 1.0f, 16777000.0f, 1.0f,
                  400000000.0f, D_004D90F8);
}

/* func_00110ba8 (from auto/text_00110000_3.c). */
M2C_UNK func_00267328(M2C_UNK *, M2C_UNK *, M2C_UNK *);
M2C_UNK func_002675b8(M2C_UNK *, M2C_UNK *);
M2C_UNK D_004D9200[0x10] ALIGNED(64);
void func_00110ba8(void) {
    func_002675b8(&D_004D9200, (M2C_UNK *)&D_002BBFA0);
    func_00267328((M2C_UNK *)&D_002BBFA0, ((M2C_UNK *)&D_002BBE60), ((M2C_UNK *)&D_002E2700));
    func_00267328((M2C_UNK *)&D_002BBFE0, ((M2C_UNK *)&D_002BBEE0), ((M2C_UNK *)&D_002E2700));
    func_00267328((M2C_UNK *)&D_002BC020, ((M2C_UNK *)&D_002BBF20), ((M2C_UNK *)&D_002E2700));
}

/* func_00110c30 (from auto/text_00110000_3.c). */
#define D_004D8E40 (*(M2C_UNK (*)) &D_004D8E40)
#define D_004D8E80 (*(M2C_UNK (*)) &D_004D8E80)
#define D_004D9100 (*(M2C_UNK (*)) &D_004D9100)
#define D_004D9140 (*(M2C_UNK (*)) &D_004D9140)
#define D_004D9180 (*(M2C_UNK (*)) &D_004D9180)
#define D_004D91C0 (*(M2C_UNK (*)) &D_004D91C0)
void func_00110c30(void) {
    func_002675b8(((M2C_UNK *)&D_002BBE20), &D_004D8E40);
    func_002675b8(((M2C_UNK *)&D_002BBE60), &D_004D9100);
    func_002675b8(((M2C_UNK *)&D_002BBEA0), &D_004D9140);
    func_002675b8(((M2C_UNK *)&D_002BBEE0), &D_004D9180);
    func_002675b8(((M2C_UNK *)&D_002BBF20), &D_004D91C0);
    func_002675b8((M2C_UNK *)&D_002BBF60, &D_004D8E80);
    func_00267328((M2C_UNK *)&D_002BBFA0, ((M2C_UNK *)&D_002BBE60), ((M2C_UNK *)&D_002E2700));
}
#undef D_004D8E40
#undef D_004D8E80
#undef D_004D9100
#undef D_004D9140
#undef D_004D9180
#undef D_004D91C0

/* func_00110ce0 (from hand/text_00110000_s8_w5.c). */
extern u64 D_002BC9B0;
extern u8 D_002BC9F0[];
extern f32 D_002BC170[8];
extern f32 D_002BC120;
extern f32 D_002BC124;
void func_00106bd8(void *, s32);
static inline void mk(u64 *o, s32 r, s32 g, s32 b) { *o = (u64)r | ((u64)g << 8) | ((u64)b << 16); }
void func_00110ce0(void) {
    f32 n, f, t, b, d, p, q;
    s32 i;
    s32 unused[4];
    n = D_002BC0F0.camS.a[0];
    f = D_002BC0F0.camS.a[1];
    b = D_002BC0F0.camS.a[2];
    t = D_002BC0F0.camS.a[3];
    D_004D90F8 = f;
    mk(&D_002BC9B0, D_002BC0F0.camS.b[0], D_002BC0F0.camS.b[1], D_002BC0F0.camS.b[2]);
    d = n - f;
    p = (n * f * (t - b)) / d;
    q = ((b - t) * (n + f) / d + (b + t)) * 0.5f;
    D_002BC120 = q;
    D_002BC124 = p;
    D_002BC170[3] = q;
    D_002BC170[7] = p;
    func_00106bd8(D_002BC9F0, 10010);
    for (i = 0; i < 16; i++) {
        D_002A3F60.f[i][0] += D_002A4060.f[i][0] * D_002BBDFC;
        if (D_002A3F60.f[i][0] > 1.0f) D_002A3F60.f[i][0] -= 1.0f;
        D_002A3F60.f[i][1] += D_002A4060.f[i][1] * D_002BBDFC;
        if (D_002A3F60.f[i][1] > 1.0f) D_002A3F60.f[i][1] -= 1.0f;
    }
}

/* func_00110e38 (from auto/text_00110000_9.c). */
void func_00110e38(f32 fparg0, f32 fparg1, f32 fparg2, f32 fparg3) {
    M2C_FIELD((M2C_UNK *)&D_002BCB40, f32 *, 0) = fparg0;
    M2C_FIELD((M2C_UNK *)&D_002BCB40, f32 *, 4) = fparg1;
    M2C_FIELD((M2C_UNK *)&D_002BCB40, f32 *, 8) = fparg2;
    M2C_FIELD((M2C_UNK *)&D_002BCB40, f32 *, 0xC) = fparg3;
    M2C_FIELD((M2C_UNK *)&D_002BCB50, s32 *, 0) = 0;
    M2C_FIELD((M2C_UNK *)&D_002BCB50, s32 *, 4) = 0;
    M2C_FIELD((M2C_UNK *)&D_002BCB50, s32 *, 8) = 0;
}

/* func_00110e68 (from hand/text_00110000_s11_w38.c). */
extern f32 D_002BC190[];
f32 cosf(f32);
void func_002675a8(f32 *, s32);
void func_00176110(s32);
void func_00176150(s32);
/* func_00110e68: mode hand (strict), no context. s11w38 from w20's 2w, FLAGGED:
 *  - identical arms `if (a) { *p++ = v; } else { *p++ = v; }` (w20: keep p at 16 refs);
 *  - x written `D[i] + (1 - D[i]) * cosf(*ph)` (amp + t order, w25);
 *  - dead FP-condition set `if (x < p[-1]) v = 0;` at the end of the loop body (v is dead; flow2 deletes the
 *    empty test and the compare). The compare reads x in a block after the arms, so x is a GLOBAL pseudo
 *    (not tied to the dying amp2 load: *p gets $f1, amp2/x $f2 as in the original), and the p[-1] load adds
 *    a 17th ref to p, so p beats &D[i] for s0 in global-alloc (an `x < 1.0f` test lengthens p's life
 *    without the extra ref and loses s0: 15w). */
void func_00110e68(s32 a) {
    s32 i;
    f32 *p;
    f32 *ph;

    p = D_002BC190;
    func_002675a8(D_002BC190, a);
    if (D_002BCB40[3] != 1.0f) {
        p = D_002BC190;
        for (i = 0; i < 3; i++) {
            ph = &D_002BCB50[i];
            *ph += D_002BCB40[3];
            if (*ph > 3.141592801f) *ph -= 6.2831855f;
            if (*ph < -3.141592801f) *ph += 6.2831855f;
            {
                f32 v;
                f32 x = D_002BCB40[i] + (1.0f - D_002BCB40[i]) * cosf(*ph);
                v = *p * x;
                if (a) {
                    *p++ = v;
                } else {
                    *p++ = v;
                }
                if (x < p[-1]) v = 0; /* FLAGGED dead set */
            }
        }
    }
    func_00176110(a);
    func_00176150(a);
}


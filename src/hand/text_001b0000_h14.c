/* Hand-matched functions from 0x001bfed8-0x001c0700 (worker 14; its message-window
 * functions are in src/msgwin/msgwin.c since session 32). */
#include "common.h"
#include "data/bss_0062.h"

/* ---- types ---- */
/* 48-byte slots of the table D_0037A16C points to. */
#include "data/types/text_001b0000_h14_p.h"
/* D_00389C90 */
typedef struct {
    u8 b[4]; u8 c[8];
    union { u8 d[8]; struct { u8 pad[4]; u16 tbl[8][256]; } t; } u;
    s32 w[4]; u8 pad4128[16]; s8 idx[4]; u8 pad4148[8192];
    s32 w12340; s32 w12344; u8 pad12348[52]; u64 d12400; u64 d12408;
    u8 pad12416[192]; s32 w12608; s32 *p12612;
} Big;
#include "data/types/text_001b0000_h14.h"
typedef struct { f32 x, y, z, w; } V4;

/* ---- data ---- */
extern Slot *D_0037A16C;
extern s32 D_0037A168;
extern Big D_00389C90;
extern f32 D_002BBDFC;
extern f32 D_003C55E0, D_003C55E4, D_003C55E8, D_003C55F4, D_003C55F8, D_003C5630, D_003C5634;

/* ---- functions ---- */
void func_001bffa0(s32 i);
void func_001c07f0(void);
void func_001dd170(void);

s32 func_001bfed8(s32 a0) {
    s32 i;
    if (a0 == 0) {
        for (i = 1; i < 16; i++) {
            if (D_0037A16C[i].used == 0) return i;
        }
        return -1;
    }
    for (i = 0; i < 384; i++) {
        if (D_0037A16C[i + 16].used == 0) return i + 16;
    }
    return -1;
}

void func_001bffa0(s32 i) {
    if (i >= 0) {
        if (D_0037A16C[i].fn) D_0037A16C[i].fn();
        D_0037A16C[i].used = 0;
        D_0037A16C[i].h2 = 0;
        D_0037A16C[i].h4 = 0;
    }
}

typedef struct { u16 h0, h2, h4, h6; u8 *ctx; u8 *stk; u8 pad16[16]; void (*fn)(void); u8 pad36[12]; } Task;
#include "data/pieces/D_0037A170.h"
extern s32 D_0037A174;
#define D_0037A16C (*(Task **)&D_0037A16C)
void func_001c0460(void) {
    s16 order[1024];
    s32 i, j, k, n;
    Task *p;
    Task **pp;
    RunQ_37a170 *q;
    n = 1;
    for (i = 1; i < 400; i++) {
        if (D_0037A16C[i].h0 != 0) {
            if (D_0037A16C[i].h4 & 1) func_001bffa0(i);
        }
        if (D_0037A16C[i].h0 != 0) n++;
    }
    D_0037A174 = n;
    D_0037A170[0].arg = 0;
    D_0037A170[0].ctx = D_0037A16C[0].ctx;
    if (n < 2) return;
    order[0] = -1;
    n = 0;
    p = &D_0037A16C[1];
    for (i = 1; i < 400; i++, p++) {
        if (p->h0 == 0) continue;
        for (j = 0; j < n; j++) {
            if (D_0037A16C[i].h2 < D_0037A16C[order[j]].h2) break;
        }
        for (k = n - 1; k >= j; k--) order[k + 1] = order[k];
        order[j] = i;
        n++;
    }
    for (i = 0; i < n; i++) {
        D_0037A170[i + 1].arg = order[i];
        D_0037A170[i + 1].ctx = D_0037A16C[order[i]].ctx;
    }
    D_0037A170[i + 1].arg = -1;
    D_0037A170[i + 1].ctx = 0;
}
#undef D_0037A16C

void func_001c06c0(s32 i, void (*fn)(void)) {
    if (i < 0) i = D_0037A168;
    D_0037A16C[i].fn = fn;
}

void func_001c06f8(void) {
    Big **pb;
    Big *b = &D_00389C90;
    pb = &b;
    (*pb)->w12340 = 0;
    b->w12344 = 0;
    b->d12400 &= ~(1ULL << 58);
    func_001c07f0();
    func_001dd170();
}

/* func_001caa50, func_001caae0, func_001cac60, func_001cae00, func_001cae20, func_001caf58, func_001cc170 and func_001cc1c0 are in src/msgwin/msgwin.c. */

/* func_001c8478 .. func_001c8708, func_001c8c10, func_001c8d18, func_001c92e8, func_001c9d40 and func_001ca5f8 .. func_001ca708 are in src/camera/camera.c. */

#include "data/bss_0062_mixed.h"
#include "data/bss_0062_typed.h"
#include "data/data_0036.h"
#include "data/data_0037.h"
#include "data/data_003C.h"
#include "data/data_003F.h"
#include "data/pieces/D_0037A130.h"
#include "data/pieces/D_002BBDFC.h"

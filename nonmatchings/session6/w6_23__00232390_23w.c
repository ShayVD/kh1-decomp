/* func_00232390: 23w off, strict hand. a0 move scheduled first (orig: last) before func_001fc308 and func_0020dd38 calls; s1/s2 swap for y+7 / col. Tried proto deletion, callee stubs above, inline wrappers, arg types, modes. */
#include "common.h"
typedef struct { u8 pad[8]; s32 x8; } F8;
extern F8 *D_00425BC8;
typedef struct { u8 pad[0xb0]; s32 xb0; s32 xb4; u8 p1[6]; s16 xbe; s16 xc0; s16 xc2; s16 xc4; s16 xc6; u8 p2[0xd2-0xc8]; s16 xd2; u8 p3[4]; s16 xd8; s16 xda; } O;
extern s32 D_006469B0, D_006469B4;
extern s32 D_003F7308[];
extern u8 D_003F7210[], D_003F47A8[];
s32 func_001f42b8(void);
void func_001f3708(void *, s32);
void func_0011d768(s32);
s32 func_00219428(void);
void func_00219418(s32);
void func_0020bc48(s32, s32, s32);
void func_001fd858(void *);
s32 func_001fe570(void *);
s32 func_001fd518(void *);
void func_00201440(void *, s32, s32, s32, s32, s32, s32, void *, s32);
void func_002066b0(void *, s32, s32, s32, s32, s32);
void func_002053e8(void *, s32, s32, s32, s32, s32);
s32 func_001fa808(void *, s32, s32, s32, s32);
void func_001f9438(void *, s32, s32, s32, s32, s32, s32);
void func_00209820(void *, s32, s32, s32, void *);

typedef struct { u8 p0[4]; u8 r[0x48e - 4]; u8 sel[0x499 - 0x48e]; u8 cnt[1]; } Base4BE8;
extern Base4BE8 *D_00304BE8;
typedef struct { u8 b0, b1, start, count, b4, b5; } T7C48;
typedef struct { u16 id; u16 max; } T7A70;
typedef struct { u8 b[32]; } T7D88;
extern T7C48 D_003F7C48[];
extern T7A70 D_003F7A70[];
extern T7D88 D_003F7D88[];
extern s32 D_0064765C;
void func_00205b30(void *, void *);
s32 func_001fc308(void *, s32, s32, s32, s32, s32, s32, s32, s32);
void func_0020dd38(void *, s32, s32, s32, s32);
s32 func_00207ca0(s32);
void func_001fb428(void *, s32, s32, s32, s32, s32, s32, s32, s32);
void func_00207d60(void *, s32, s32, s32, s32, s32, s32);

void func_00232390(void *a0) {
    u32 i;
    s32 n, j, y, id, max, cnt, c, col;
    T7A70 *e;
    T7C48 *t;
    for (j = 0; (u32)j < 7; j++) func_00205b30(a0, &D_003F7D88[j]);
    func_001fc308(a0, 11, 13, 0, 0, 61, 0, 0x80009100, 0x8027E4D4);
    y = 63;
    func_001f9438(a0, 1, 490, 11, 426, 15, 0x4D508B2E);
    func_001f9438(a0, 0, 44, 42, 427, 15, 0x80C8C8C8);
    func_001f9438(a0, 0, 271, 42, 428, 15, 0x80C8C8C8);
    func_001f9438(a0, 1, 484, 42, 429, 15, 0x80C8C8C8);
    t = &D_003F7C48[D_0064765C];
    e = &D_003F7A70[t->start];
    n = t->count;
    for (j = 0; j < n; j++) {
        id = e->id;
        max = e->max;
        e++;
        cnt = D_00304BE8->cnt[id];
        c = cnt < max ? 2 : 0;
        func_0020dd38(a0, c, 247, y, 194);
        col = func_00207ca0(0);
        func_001f9438(a0, 0, 400, y + 7, 85, 12, col);
        func_001fb428(a0, 0, 1, 0, 418, y + 7, max, 12, col);
        func_00207d60(a0, c, 445, y, 480, cnt, 12);
        y += 28;
    }
}

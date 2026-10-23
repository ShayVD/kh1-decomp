#include "common.h"
#include "text/textwin.h"
#include "data/bss_0064.h"
s32 func_001fd518(void *);
s32 func_001f9438(void *, s32, s32, s32, s32, s32, s32);

/* func_00232390: func_0020dd38 takes 6 args (6th = id), y = 63 before the func_001fc308 call, callee return types as below. */
typedef struct { u8 pad[8]; s32 x8; } F8;
#include "data/pieces/D_00425BC8.h"
typedef struct { u8 pad[0xb0]; s32 xb0; s32 xb4; u8 p1[6]; s16 xbe; s16 xc0; s16 xc2; s16 xc4; s16 xc6; u8 p2[0xd2-0xc8]; s16 xd2; u8 p3[4]; s16 xd8; s16 xda; } O;
extern s32 D_006469B0, D_006469B4;
extern s32 D_003F7308[];
extern u8 D_003F7210[];
#include "data/pieces/D_003F47A8.h"
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
s32 func_001f9438(void *, s32, s32, s32, s32, s32, s32);
void func_00209820(void *, s32, s32, s32, void *);

#include "data/pieces/D_00304BE8_s.h"
#include "data/pieces/D_003F7C48.h"
typedef T7C48_3f7c48 T7C48;
#include "data/types/text_00200000_s7_w19_p.h"
#include "data/types/text_00200000_s7_w19.h"
#include "data/pieces/D_003F7A70.h"
extern T7D88 D_003F7D88[];
extern s32 D_0064765C;
void func_00205b30(void *, void *);
void func_001fc308(void *, s32, s32, s32, s32, s32, s32, s32, s32);
void func_0020dd38(void *, s32, s32, s32, s32, s32);
s32 func_00207ca0(s32);
void func_001fb428(void *, s32, s32, s32, s32, s32, s32, s32, s32);
void func_00207d60(void *, s32, s32, s32, s32, s32, s32);

void func_00232390(void *a0) {
    u32 i;
    s32 n, j, y, id, max, cnt, c, col;
    T7A70 *e;
    T7C48 *t;
    for (j = 0; (u32)j < 7; j++) func_00205b30(a0, &D_003F7D88[j]);
    y = 63;
    func_001fc308(a0, 11, 13, 0, 0, 61, 0, 0x80009100, 0x8027E4D4);
    func_001f9438(a0, 1, 490, 11, 426, 15, 0x4D508B2E);
    func_001f9438(a0, 0, 44, 42, 427, 15, 0x80C8C8C8);
    func_001f9438(a0, 0, 271, 42, 428, 15, 0x80C8C8C8);
    func_001f9438(a0, 1, 484, 42, 429, 15, 0x80C8C8C8);
    t = &((T7C48_3f7c48 *)&D_003F7C48)[D_0064765C];
    e = &D_003F7A70[t->b2];
    n = t->n;
    for (j = 0; j < n; j++) {
        id = e->id;
        max = e->max;
        e++;
        cnt = D_00304BE8->items[id];
        c = cnt < max ? 2 : 0;
        func_0020dd38(a0, c, 247, y, 194, id);
        col = func_00207ca0(0);
        func_001f9438(a0, 0, 400, y + 7, 85, 12, col);
        func_001fb428(a0, 0, 1, 0, 418, y + 7, max, 12, col);
        func_00207d60(a0, c, 445, y, 480, cnt, 12);
        y += 28;
    }
}

typedef struct { f32 x, y, z, w; } __attribute__((aligned(16))) V4a;

/* func_001c8a00 is in src/camera/camera.c. */
#include "data/pieces/D_003F7D88.h"

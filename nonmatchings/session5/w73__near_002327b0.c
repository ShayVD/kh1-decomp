#include "common.h"
typedef struct { u8 pad[8]; s32 x8; } F8;
extern F8 *D_00425BC8;
typedef struct { u8 pad[0xb0]; s32 xb0; s32 xb4; u8 p1[6]; s16 xbe; s16 xc0; s16 xc2; s16 xc4; s16 xc6; u8 p2[0xd2-0xc8]; s16 xd2; u8 p3[4]; s16 xd8; s16 xda; } O;
extern s32 D_006469B0, D_006469B4;
extern s32 D_003F7308[];
extern u8 D_003F7210[], D_003F47A8[];
s32 func_001f42b8(void *);
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

typedef struct { u8 pad[0xb0]; s32 xb0; s32 xb4; u8 p1[0xcc - 0xb8]; s16 xcc; } OCC;
extern u16 *D_00647700;
extern s32 D_003F7EC8;
extern void (*D_006476FC)(s32);
extern void (*D_006476F8)(s32);
extern u8 *D_00647704;
extern s32 D_00647708;
s32 func_001f4390(void);
void func_001fe180(void *);
s32 func_001fd548(void *);
void func_0010ea70(s32, s32, void *);
void func_001fea38(void *);
void func_002040c8(void *);
s32 func_001fd618(void *);
s32 func_001fd590(void *);
void func_001f8e18(void *);
void func_001f8f30(void);

void func_002327b0(OCC *a0) {
    s32 x, y, k, n;
    s32 i, y0;
    a0->xcc = *D_00647700;
    if (func_001f42b8(a0) != 0) {
        if (D_003F7EC8 != 0) {
            func_001fd858(a0);
            if (func_001fe570(a0) != 0) {
                D_003F7EC8 = 0;
                if (D_006476FC != 0) D_006476FC(func_001fd548(a0));
            }
        } else {
            func_001fe180(a0);
        }
    }
    k = 11;
    if (func_001f4390 != 0) {
        x = ((a0->xb0 - 0x7000) >> 4) + 28;
        y0 = (a0->xb4 - 0x7400) >> 4;
        func_0010ea70(x, y0 + 40, (void *)D_00647708);
        func_001fea38(a0);
        func_002040c8(a0);
        i = func_001fd618(a0);
        n = a0->xcc;
        y = y0 + func_001fd590(a0);
        func_001f8e18(a0);
        for (; k >= 0; k--) {
            if (i < n) func_0010ea70(x, y, D_00647704 + i * 32);
            i++;
            y += 24;
        }
        func_001f8f30();
    }
    if (D_006476F8 != 0) D_006476F8(func_001fd548(a0));
}

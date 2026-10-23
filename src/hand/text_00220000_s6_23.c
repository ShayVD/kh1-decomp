#include "common.h"
#include "data/bss_0064.h"
#include "data/pieces/D_00425BC8.h"
#include "data/types/text_00220000_s6_23.h"
extern T78D8 D_003F78D8[8];
extern s32 D_003F7A68;
extern void (*D_00646A00)(s32);
extern void (*D_00646A04)(s32);
extern s32 D_00646A1C;
extern s32 D_00646A28;
void func_0011d768(s32);
s32 func_001ef7a0(void);
s32 func_001f42b8(void *);
void func_001f8ee0(void *);
void func_001f8f30(void);
s32 func_001f9438(void *, s32, s32, s32, s32, s32, s32);
s32 func_001fb428(void *, s32, s32, s32, s32, s32, s32, s32, s32);
s32 func_001fbcb0(void *, s32, s32, s32, s32, s32, s32, s32);
s32 func_001fc308(void *, s32, s32, s32, s32, s32, s32, s32, s32);
s32 func_001fd518(void *);
s32 func_001fd548(void *);
s32 func_001fd590(void *);
void func_001fd5e0(void *, s32);
void func_001fd610(void *, s32);
s32 func_001fd618(void *);
void func_001fd688(void *);
void func_001fd858(void *);
s32 func_001fe5a0(void *);
void func_00202fc0(void *);
void func_00205b30(void *, void *);
s32 func_00206130(void *, s32, s32, s32, s32, s32);
void func_00207e20(void *, s32, s32, s32, s32);
void func_0020bc48(s32, s32, s32);
void func_0020bd18(void *, s32);

#define func_001ef7a0 func_001ef7a0_s1
extern s32 D_003F7A68;
extern void (*D_00646A00)(s32);
extern void (*D_00646A04)(s32);
extern s32 D_00646A28;
extern s32 D_00647640;
void func_0011d768(s32);
s32 func_001ba3f0(s32);
u32 func_001ef7a0(void) __asm__("func_001ef7a0");
s32 func_001f42b8(void *);
void func_001f8ee0(void *);
void func_001f8f30(void);
s32 func_001f9438(void *, s32, s32, s32, s32, s32, s32);
s32 func_001fb428(void *, s32, s32, s32, s32, s32, s32, s32, s32);
s32 func_001fbcb0(void *, s32, s32, s32, s32, s32, s32, s32);
s32 func_001fc308(void *, s32, s32, s32, s32, s32, s32, s32, s32);
s32 func_001fd518(void *);
s32 func_001fd548(void *);
s32 func_001fd590(void *);
s32 func_001fd618(void *);
void func_001fd858(void *);
s32 func_001fe5a0(void *);
void func_00202fc0(void *);
void func_00205b30(void *, void *);
s32 func_00206130(void *, s32, s32, s32, s32, s32);
void func_00207e20(void *, s32, s32, s32, s32);
void func_0020bc48(s32, s32, s32);
void func_0020bd18(void *, s32);
void func_0020e1c0(void *, s32, s32, s32, s32, s32);

#undef func_001ef7a0

#define func_001ef7a0 func_001ef7a0_s2
#define func_001ba3f0 func_001ba3f0_s2

extern s32 D_00646A28;
extern s32 D_00646A1C;
s32 func_001ba3f0(void) __asm__("func_001ba3f0");
u32 func_001ef7a0(void) __asm__("func_001ef7a0");

#undef func_001ba3f0
#undef func_001ef7a0

#define func_001ef7a0 func_001ef7a0_s3

extern T78D8 D_003F78D8[8];
extern s32 D_003F7A68;
extern void (*D_00646A00)(s32);
extern void (*D_00646A04)(s32);
extern s32 D_00646A1C;
extern s32 D_00646A28;
extern s32 D_00647640;
void func_0011d768(s32);
s32 func_001ba3f0(s32);
u32 func_001ef7a0(void) __asm__("func_001ef7a0");
s32 func_001f42b8(void *);
void func_001f8ee0(void *);
void func_001f8f30(void);
s32 func_001f9438(void *, s32, s32, s32, s32, s32, s32);
s32 func_001fb428(void *, s32, s32, s32, s32, s32, s32, s32, s32);
s32 func_001fbcb0(void *, s32, s32, s32, s32, s32, s32, s32);
s32 func_001fc308(void *, s32, s32, s32, s32, s32, s32, s32, s32);
s32 func_001fd518(void *);
s32 func_001fd548(void *);
s32 func_001fd590(void *);
void func_001fd5e0(void *, s32);
void func_001fd610(void *, s32);
s32 func_001fd618(void *);
void func_001fd688(void *);
void func_001fd858(void *);
s32 func_001fe5a0(void *);
void func_00202fc0(void *);
void func_00205b30(void *, void *);
s32 func_00206130(void *, s32, s32, s32, s32, s32);
void func_00207e20(void *, s32, s32, s32, s32);
void func_0020bc48(s32, s32, s32);
void func_0020bd18(void *, s32);
void func_0020e1c0(void *, s32, s32, s32, s32, s32);

#undef func_001ef7a0

#define func_001f9438 func_001f9438_s4
#define D_00425BC8 D_00425BC8_s4
typedef struct { u8 pad[8]; s32 x8; } F8;
extern F8 *D_00425BC8 __asm__("D_00425BC8");
typedef struct { u8 pad[0xb0]; s32 xb0; s32 xb4; u8 p1[6]; s16 xbe; s16 xc0; s16 xc2; s16 xc4; s16 xc6; u8 p2[0xd2-0xc8]; s16 xd2; u8 p3[4]; s16 xd8; s16 xda; } O;
extern s32 D_006469B0, D_006469B4;
extern s32 D_003F7308[];
extern u8 D_003F7210[];
#include "data/pieces/D_003F47A8.h"
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
void func_001f9438(void *, s32, s32, s32, s32, s32, s32) __asm__("func_001f9438");
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
        for (k = 11; k >= 0; k--) {
            if (i < n) func_0010ea70(x, y, D_00647704 + i * 32);
            i++;
            y += 24;
        }
        func_001f8f30();
    }
    if (D_006476F8 != 0) D_006476F8(func_001fd548(a0));
}

#undef D_00425BC8
#undef func_001f9438

typedef struct { s32 type; s32 x4; s32 a[6]; } Cmd;
extern Cmd D_006477B0[64];
extern s32 D_006477A8, D_00647FB0, D_00647FB4, D_00647FB8, D_00647FBC, D_00647FC4, D_00647FCC, D_00647FD0, D_00647FD4, D_00647FD8, D_00647FDC, D_00647FE0;
extern s32 D_00425C10, D_00425C14, D_00425CA8, D_00425CAC, D_00648020, D_00648024, D_00648028, D_0064802C, D_00648034;

/* rodata */
void func_00234910(void) {
    if (D_00647FB8 != D_00647FBC) {
        switch (D_006477B0[D_00647FBC].type) {
        case 1:
            D_00647FB0 = 1;
            D_00647FB4 = 0;
            D_00425C10 = D_006477B0[D_00647FBC].a[0];
            D_00425C14 = D_006477B0[D_00647FBC].a[1];
            D_00648034 = D_006477B0[D_00647FBC].a[2];
            D_00647FC4 = D_006477B0[D_00647FBC].x4;
            D_00647FBC = (D_00647FBC + 1) & 0x3f;
            break;
        case 2:
            D_00647FB0 = 2;
            D_00647FB4 = 0;
            D_00425C10 = D_006477B0[D_00647FBC].a[0];
            D_00425C14 = D_006477B0[D_00647FBC].a[1];
            D_00425CA8 = D_006477B0[D_00647FBC].a[2];
            D_00425CAC = D_006477B0[D_00647FBC].a[3];
            D_00648034 = D_006477B0[D_00647FBC].a[4];
            D_00647FC4 = D_006477B0[D_00647FBC].x4;
            D_00647FBC = (D_00647FBC + 1) & 0x3f;
            break;
        case 3:
            D_00647FB0 = 3;
            D_00647FB4 = 0;
            D_00425C10 = D_006477B0[D_00647FBC].a[0];
            D_00425C14 = D_006477B0[D_00647FBC].a[1];
            D_00648020 = D_006477B0[D_00647FBC].a[2];
            D_00425CA8 = D_006477B0[D_00647FBC].a[3];
            D_00425CAC = D_006477B0[D_00647FBC].a[4];
            D_00648034 = D_006477B0[D_00647FBC].a[5];
            D_00647FC4 = D_006477B0[D_00647FBC].x4;
            D_00647FBC = (D_00647FBC + 1) & 0x3f;
            break;
        case 4:
            D_00647FB0 = 4;
            D_00647FB4 = 0;
            D_00647FCC = 0;
            D_00647FD0 = 0;
            D_00425C10 = D_006477B0[D_00647FBC].a[0];
            D_00425C14 = D_006477B0[D_00647FBC].a[1];
            D_00648034 = D_006477B0[D_00647FBC].a[2];
            D_00647FC4 = D_006477B0[D_00647FBC].x4;
            D_00647FBC = (D_00647FBC + 1) & 0x3f;
            break;
        case 5:
            D_00647FB0 = 5;
            D_00647FB4 = 0;
            D_00647FCC = 0;
            D_00647FD0 = 0;
            D_00425C10 = D_006477B0[D_00647FBC].a[0];
            D_00425C14 = D_006477B0[D_00647FBC].a[1];
            D_00648034 = D_006477B0[D_00647FBC].a[2];
            D_00647FC4 = D_006477B0[D_00647FBC].x4;
            D_00647FBC = (D_00647FBC + 1) & 0x3f;
            break;
        case 6:
            D_00647FB0 = 6;
            D_00647FB4 = 0;
            D_00425C10 = D_006477B0[D_00647FBC].a[0];
            D_00425C14 = D_006477B0[D_00647FBC].a[1];
            D_00648020 = D_006477B0[D_00647FBC].a[2];
            D_00648034 = D_006477B0[D_00647FBC].a[3];
            D_00647FC4 = D_006477B0[D_00647FBC].x4;
            D_00647FBC = (D_00647FBC + 1) & 0x3f;
            break;
        case 7:
            D_00647FB0 = 7;
            D_00647FB4 = 0;
            D_00425C10 = D_006477B0[D_00647FBC].a[0];
            D_00425C14 = D_006477B0[D_00647FBC].a[1];
            D_00648020 = D_006477B0[D_00647FBC].a[2];
            D_00648034 = D_006477B0[D_00647FBC].a[3];
            D_00647FC4 = D_006477B0[D_00647FBC].x4;
            D_00647FBC = (D_00647FBC + 1) & 0x3f;
            break;
        case 8:
            D_00647FB0 = 8;
            D_00647FB4 = 0;
            D_00425C10 = D_006477B0[D_00647FBC].a[0];
            D_00425C14 = D_006477B0[D_00647FBC].a[1];
            D_00648020 = D_006477B0[D_00647FBC].a[2];
            D_00648028 = D_006477B0[D_00647FBC].a[3];
            D_0064802C = D_006477B0[D_00647FBC].a[4];
            D_00648034 = D_006477B0[D_00647FBC].a[5];
            D_00647FC4 = D_006477B0[D_00647FBC].x4;
            D_00647FBC = (D_00647FBC + 1) & 0x3f;
            break;
        case 9:
            D_00647FB0 = 9;
            D_00647FB4 = 0;
            D_00425C10 = D_006477B0[D_00647FBC].a[0];
            D_00425C14 = D_006477B0[D_00647FBC].a[1];
            D_00648020 = D_006477B0[D_00647FBC].a[2];
            D_00648034 = D_006477B0[D_00647FBC].a[3];
            D_00647FC4 = D_006477B0[D_00647FBC].x4;
            D_00647FBC = (D_00647FBC + 1) & 0x3f;
            break;
        case 10:
            D_00647FB0 = 10;
            D_00647FB4 = 0;
            D_00425C10 = D_006477B0[D_00647FBC].a[0];
            D_00425C14 = D_006477B0[D_00647FBC].a[1];
            D_00648020 = D_006477B0[D_00647FBC].a[2];
            D_00648028 = D_006477B0[D_00647FBC].a[3];
            D_0064802C = D_006477B0[D_00647FBC].a[4];
            D_00648034 = D_006477B0[D_00647FBC].a[5];
            D_00647FC4 = D_006477B0[D_00647FBC].x4;
            D_00647FBC = (D_00647FBC + 1) & 0x3f;
            break;
        case 11:
            D_00647FB0 = 11;
            D_00647FB4 = 0;
            D_00425C10 = D_006477B0[D_00647FBC].a[0];
            D_00425C14 = D_006477B0[D_00647FBC].a[1];
            D_00648020 = D_006477B0[D_00647FBC].a[2];
            D_00648028 = D_006477B0[D_00647FBC].a[3];
            D_0064802C = D_006477B0[D_00647FBC].a[4];
            D_00648034 = D_006477B0[D_00647FBC].a[5];
            D_00647FC4 = D_006477B0[D_00647FBC].x4;
            D_00647FBC = (D_00647FBC + 1) & 0x3f;
            break;
        case 12:
            D_00647FB0 = 12;
            D_00647FB4 = 0;
            D_00425C10 = D_006477B0[D_00647FBC].a[0];
            D_00425C14 = D_006477B0[D_00647FBC].a[1];
            D_00648020 = D_006477B0[D_00647FBC].a[2];
            D_00648024 = D_006477B0[D_00647FBC].a[3];
            D_00648034 = D_006477B0[D_00647FBC].a[4];
            D_00647FC4 = D_006477B0[D_00647FBC].x4;
            D_00647FBC = (D_00647FBC + 1) & 0x3f;
            break;
        case 13:
            D_00647FB0 = 13;
            D_00648034 = D_006477B0[D_00647FBC].a[0];
            D_00647FC4 = D_006477B0[D_00647FBC].x4;
            D_00647FBC = (D_00647FBC + 1) & 0x3f;
            break;
        }
    } else if (D_006477A8 != 0) {
        if (D_00647FD8 != 0) {
            D_00647FD8--;
        } else {
            D_00647FB0 = 1;
            D_00647FB4 = 0;
            D_00425C10 = D_00647FDC;
            D_00425C14 = D_00647FE0;
            D_00647FD8 = D_00647FD4;
            D_00648034 = 0;
        }
    }
}

#include "data/data_003F.h"
#include "data/pieces/D_003F7A68.h"
#include "data/pieces/D_00425C10.h"
#include "data/pieces/D_00425C14.h"
#include "data/pieces/D_00425CA8.h"
#include "data/pieces/D_00425CAC.h"
#include "data/pieces/D_003F78D8.h"

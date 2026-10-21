#include "common.h"
typedef struct { u8 b[116]; } R116;
typedef struct { u8 p0[4]; R116 r[(0x48e - 4) / 116]; u8 pr[(0x48e - 4) % 116]; u8 sel[0x499 - 0x48e]; u8 cnt[1]; } Base4BE8B;
#define Base4BE8 Base4BE8B
extern Base4BE8 *D_00304BE8; u32 func_001ef7a0(void);
typedef struct { u8 p0[8]; s32 x8; s32 xc; s32 x10; u8 name[0x24]; s32 x38; } S5B80;
typedef struct { u8 p0[0xda]; s16 xda; s16 xdc; s16 xde; u8 buf[1]; } S7ED0;
extern S5B80 D_00425B80;
extern S7ED0 D_003F7ED0;
#include "data/pieces/D_002BBDF4.h"
s32 func_002193f0(void);
u8 *func_0010fd18(void);

void func_00232e08(u32 a) {
    u8 *s;
    s32 i, q;
    u8 c;
    D_00425B80.x8 = D_00304BE8->r[D_00304BE8->sel[0]].b[0];
    D_00425B80.xc = func_001ef7a0();
    D_00425B80.x10 = *(volatile s32 *)&D_002BBDF4;
    D_00425B80.x38 = func_002193f0();
    s = func_0010fd18();
    i = 0;
    c = s[0];
    if (c != 0) {
        D_00425B80.name[i] = c;
        D_003F7ED0.buf[i] = c;
        while (1) {
            i++;
            if (i >= 20) goto out;
            {
                u8 d = s[i];
                if (d == 0) goto out;
                D_003F7ED0.buf[i] = d;
                D_00425B80.name[i] = d;
            }
        }
    }
out:
    D_003F7ED0.buf[i] = 0;
    D_00425B80.name[i] = 0;
    q = a / 10 + 0x824f;
    q = ((q & 0xff) << 8) | (q >> 8);
    D_003F7ED0.xda = q;
    q = a % 10 + 0x824f;
    q = ((q & 0xff) << 8) | (q >> 8);
    D_003F7ED0.xdc = q;
    if (func_002193f0() == 0) {
        D_003F7ED0.xde = 0x4081;
    } else if (func_002193f0() == 1) {
        D_003F7ED0.xde = 0x9981;
    } else {
        D_003F7ED0.xde = 0x9a81;
    }
}

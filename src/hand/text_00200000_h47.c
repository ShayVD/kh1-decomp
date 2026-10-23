#include "common.h"
#include "data/bss_0064.h"
#include "data/types/text_00200000_h47.h"
extern s32 D_003F3488[];
s32 func_001f31a8(s32, s32);
void func_001f3d58(s32, s32);
void func_001f3e20(s32, s32);
void func_001f3e90(s32, s32);

typedef struct { u8 pad[0x24]; s32 x24; s32 x28; } Obj7d8;
#include "data/pieces/D_00425BC8.h"
void func_0011d768(s32);
s32 func_001f42b8(void);
s32 func_001fe570(Obj7d8 *);
void func_0020bd18(Obj7d8 *, s32);
extern s32 D_00641C10[];
extern s32 D_00642410;
extern s32 D_00641C10[];
extern s32 D_00642410;

typedef struct { u8 pad[0xd2]; s16 xd2; } Oac38;
s32 func_001f31a8(s32, s32);
void func_001f3dc0(s32);
void func_001f3e20(s32, s32);
void func_001f3e90(s32, s32);
s32 func_001f42b8(void);
void func_00207830(s32, s32, s32, s32, s32, s32, s32);

#include "data/types/text_00200000_h47_p.h"

void func_0021b860(s32, s32, s32, s32, s32, s32);

void func_0021c450(s32 a0, s32 a1, s32 a2, s32 a3) {
    s32 y = a1 + 25;
    s32 h;
    s32 z;
    if (a3 < 75) a3 = 75;
    h = a3 - 75;
    z = y + h;
    func_0021b860(a0, a1, a2, 0, 0, 24);
    func_0021b860(a0, y, a2, h, 0, 25);
    func_0021b860(a0, z, a2, 0, 0, 26);
}

typedef struct {
    u8 pad[0x98];
    f32 x98;
    u8 pad2[0xb0 - 0x9c];
    s32 xb0;
    s32 xb4;
    u8 pad3[0xbe - 0xb8];
    s16 xbe;
    s16 xc0;
    s16 pad4;
    s16 xc4;
    u8 pad5[0xd2 - 0xc6];
    s16 xd2;
} Oc4f8;
f32 sinf(f32);
void func_0021b860(s32, s32, s32, s32, s32, s32);

void func_0021c4f8(Oc4f8 *o) {
    s32 a = (s32)(o->x98 * 256.0f);
    f32 s = sinf((a % 8192) * 0.0001220703125f * 6.2831855f);
    func_0021b860((s32)o, ((o->xb0 + o->xbe - 0x7000) >> 4) + ((s32)(s * 262144.0f) >> 16) - 36,
                  (o->xb4 + (o->xd2 * o->xc4 >> 4) + o->xc0 - 0x7400) >> 4, 0, 0, 38);
}

extern s32 D_003F5C08[];
extern s32 D_003F3488[];
s32 func_001f31a8(s32, s32);
void func_001f3d58(s32, s32);
void func_001f3e48(s32, s32);
void func_0020be10(s32);

s32 func_0021d9e0(s32 a0) {
    s32 buf[3];
    s32 i;
    for (i = 0; i < 3; i++) {
        buf[i] = func_001f31a8(D_003F5C08[i], 50);
        if (buf[i] != 0) {
            func_001f3e48(buf[i], a0);
            func_001f3d58(buf[i], D_003F3488[i]);
            a0 = buf[i];
        }
    }
    func_0020be10(16);
    return a0;
}

extern s32 D_003F34C8;
extern s32 D_003F350C;
extern s32 D_003F3510;
extern s32 D_003F5C50[];
extern s32 D_00643118;
extern s32 D_0064311C;
extern s32 D_00643120;
extern s32 D_0064324C;
void func_0021e508(void);
void func_00120748(s32, s32, void (*)(void), s32);

void func_0021e538(void) {
    s32 k;
    switch (D_00643118) {
    case 0:
        switch (D_003F350C) {
        case 0:
            k = D_0064324C;
            D_003F34C8++;
            D_003F350C = 1;
            D_00643118 = 1;
            D_00643120 = k;
            func_00120748(D_003F5C50[k], D_003F3510, func_0021e508, 0);
            return;
        case 1:
            D_00643118 = D_003F350C;
            return;
        default:
            if (D_00643120 != D_0064324C) {
                D_003F350C = 0;
                D_00643118 = 0;
            } else {
                D_0064311C = D_00643120;
                D_00643118 = 2;
            }
            break;
        }
        break;
    case 2:
        break;
    case 1:
        if (D_003F350C == 2) {
            if (D_00643120 != D_0064324C) {
                D_003F350C = 0;
                D_00643118 = 0;
                return;
            }
            D_00643118 = D_003F350C;
            D_0064311C = D_00643120;
        }
        break;
    }
}

extern u8 *D_006431F0[];
extern s32 D_00643200[];
extern u8 D_00643210[];
extern s32 D_0064324C;
void func_00207000(s32);
void func_00207048(s32);
s32 func_00207180(s32);
s32 func_0021dc08(u8);

void func_0021f278(void) {
    s32 i;
    for (i = D_00643200[D_0064324C] - 1; i >= 0; i--) {
        if (func_00207180(func_0021dc08(D_006431F0[D_0064324C][i])) == 0) {
            if (D_0064324C != 2) {
                func_00207000(D_0064324C);
                return;
            }
            if (D_00643210[i] != 0) {
                func_00207000(2);
                return;
            }
        }
    }
    func_00207048(D_0064324C);
}

extern u8 D_003F5F30[];
extern u8 D_003F5F60[];
extern u8 D_003F5F90[];
extern s32 D_0064324C;
s32 func_001f31a8(s32, s32);
void func_001f3e48(s32, s32);

void func_0021f858(s32 a0) {
    s32 b[3];
    b[0] = func_001f31a8((s32)D_003F5F90, 50);
    if (b[0] == 0) return;
    func_001f3e48(b[0], a0);
    b[1] = func_001f31a8((s32)D_003F5F60, 50);
    if (b[1] == 0) return;
    func_001f3e48(b[1], b[0]);
    b[2] = func_001f31a8((s32)D_003F5F30, 50);
    if (b[2] == 0) return;
    func_001f3e48(b[2], b[1]);
    ((Oac38 *)b[2])->xd2 = *(u16 *)&D_0064324C * 16;
}

typedef struct { u8 pad[0xa0]; f32 xa0; } Oaf0;
typedef struct { u8 pad[0x10]; s32 x10; } O3428;
extern O3428 *D_00643428; /* src/data/bss_0064.c: s32 D_00643428 */
extern S90a0 D_003E90A0;
extern u8 D_003F6270[];
extern u8 D_003F62A0[];
void func_0011d768(s32);
s32 func_001f31a8(s32, s32);
void func_001f3758(s32);
void func_001f3e48(s32, s32);
s32 func_001f42b8(void);
void func_0021b820(void);
void func_0021cb88(s32, s32, s32, s32, s32);

void func_00220af0(s32 a0) {
    s32 b[2];
    if (func_001f42b8() != 0) {
        s32 fl = D_00425BC8->x8;
        if (fl & 0x4000) {
            func_001f3758((s32)D_00643428);
            func_0011d768(3);
        } else if (fl & 0x1000) {
            func_0011d768(2);
            func_001f3758(D_00643428->x10);
            b[0] = func_001f31a8((s32)D_003F62A0, 50);
            if (b[0] != 0) {
                func_001f3e48(b[0], a0);
                ((Oaf0 *)b[0])->xa0 = D_003E90A0.x64;
                b[1] = func_001f31a8((s32)D_003F6270, 50);
                if (b[1] != 0) {
                    func_001f3e48(b[1], b[0]);
                    ((Oaf0 *)b[1])->xa0 = ((Oaf0 *)b[0])->xa0 + D_003E90A0.x64;
                }
            }
        }
    }
    func_0021b820();
    func_0021cb88(a0, 176, 8, 320, 7);
}

typedef struct { u8 pad[0xcc]; s16 xcc; u8 pad2[4]; s16 xd2; } O29a0;
extern u8 D_003F6590[];
extern u8 D_003F65C0[];
extern u8 D_003F65F0[];
extern s32 D_00643674;
extern s32 D_00643690;
s32 func_001f31a8(s32, s32);
void func_001f3e48(s32, s32);

void func_002229a0(s32 a0) {
    s32 b[3];
    b[0] = func_001f31a8((s32)D_003F65F0, 50);
    if (b[0] == 0) return;
    func_001f3e48(b[0], a0);
    b[1] = func_001f31a8((s32)D_003F65C0, 50);
    if (b[1] == 0) return;
    func_001f3e48(b[1], b[0]);
    b[2] = func_001f31a8((s32)D_003F6590, 50);
    if (b[2] == 0) return;
    func_001f3e48(b[2], b[1]);
    ((O29a0 *)b[2])->xcc = D_00643674;
    if (D_00643690 >= D_00643674) {
        D_00643690 = D_00643674 - 1;
    }
    ((O29a0 *)b[2])->xd2 = (u16)D_00643690 * 16;
}

extern s32 D_003F5C34;
extern u8 D_006436A8[];
extern s32 D_006436B8;
s32 func_001ebc38(s32);
s32 func_00206fb8(u8);
void func_00207298(s32);
void func_002072e0(s32);

void func_00222ba8(void) {
    s32 i;
    D_006436B8 = 0;
    for (i = 0; i < 13; i++) {
        if (func_001ebc38(i) != 0) {
            D_006436A8[D_006436B8++] = i;
        }
    }
    for (i = 0; i < D_006436B8; i++) {
        if (func_00206fb8(D_006436A8[i]) == 0) {
            func_00207298(1);
            goto end;
        }
    }
    func_002072e0(1);
end:
    D_003F5C34 = D_006436B8 == 13;
}

extern S5C30 D_003F5C30;
extern s32 D_003F6740[];
extern s32 D_003F6758[];
extern s32 D_003F6770[];
extern s32 D_003F6828[];
extern s32 D_003F6840[];
extern s32 D_003F6854;
#include "vm/script_vm.h"
s32 func_001ec5d8(s32);

void func_00223508(void) {
    s32 i;
    D_003F6854 = 0;
    for (i = 0; i < 5; i++) {
        if (func_001ec5d8(i) != 0) {
            D_003F6828[D_003F6854] = i;
            func_001c0da0(D_003F6758[i], D_003F6770[i], &D_003F6840[D_003F6854]);
            D_003F6854++;
        }
    }
    D_003F5C30.x10 = 0;
    if (D_003F6854 == 5) {
        for (i = 0; i < 5; i++) {
            if (D_003F6840[i] != D_003F6740[i]) return;
        }
        D_003F5C30.x10 = 1;
    }
}

void func_0011d768(s32);
s32 func_001f42b8(void);
s32 func_001fe570(Obj7d8 *);
void func_0020bd18(Obj7d8 *, s32);
void func_001f36b8(Obj7d8 *);
extern s32 D_006436D4;
extern s32 D_00643750;
#include "data/pieces/D_003E8E08.h"
s32 func_00233f40(s32, s32);
void func_00233ff8(s32, s32);
void func_002246f8(Obj7d8 *);
void func_00207bb0(Obj7d8 *, s32);

void func_002251b0(Obj7d8 *a0) {
    if (func_001f42b8() != 0) {
        if (func_00233f40(D_006436D4, 0) != 0) {
            func_00233ff8(D_006436D4, 0);
            func_002246f8(a0);
        } else if (D_00425BC8->x8 & 0x4000) {
            func_001f36b8(a0);
            func_0011d768(3);
        } else {
            func_0020bd18(a0, 8);
            if (func_001fe570(a0) != 0) {
                func_001f36b8(a0);
            }
        }
    }
    (*(S4_3e8e08 *)&D_003E8E08).b = 132;
    (*(S4_3e8e08 *)&D_003E8E08).a = D_00643750;
    func_00207bb0(a0, 398);
}

typedef struct { u8 pad[0xb4]; s32 xb4; u8 p2[2]; u16 xba; u8 p3[4]; u16 xc0; } Of90;
void func_0011d768(s32);
s32 func_001f31a8(s32, s32);
void func_001f3e48(s32, s32);
void func_001f4058(s32, s32);
void func_001f3d58(s32, s32);
s32 func_001efd98(s32);
void func_0020bda8();
extern u8 D_003F6BA0[];
extern s32 D_003F6BC8[];
extern s32 D_006436D4;

void func_00227f90(s32 a0) {
    Of90 *p;
    s32 v, c0, ba, b4;
    func_0011d768(4);
    p = (Of90 *)func_001f31a8((s32)D_003F6BA0, 6);
    if (p != 0) {
        func_001f3e48((s32)p, a0);
        func_001f4058((s32)p, 1);
        func_001f3d58((s32)p, 6);
        v = func_001efd98(D_003F6BC8[D_006436D4]) * 0x170;
        b4 = p->xb4 - v;
        ba = p->xba + v;
        c0 = p->xc0 + v;
        p->xb4 = b4;
        p->xba = ba;
        p->xc0 = c0;
        func_0020bda8(16, c0, ba, b4);
    }
}

typedef struct { u8 pad[0xCC]; u16 cc; u16 ce; u16 d0; s16 d2; } O9088;
extern u8 D_003F6CE0[];
extern u8 D_003F6CA0[];
extern u16 D_00643730; /* src/data/bss_0064.c: s32 D_00643730 */
extern u16 D_006436D0; /* src/data/bss_0064.c: s32 D_006436D0 */
s32 func_001f31a8(s32, s32);
void func_001f3dc0(s32);
void func_001f3e48(s32, s32);
s32 func_001f42b8(void);
void func_00207830(s32, s32, s32, s32, s32, s32, s32);

void func_00229088(s32 a0) {
    s32 b[2];
    if (func_001f42b8() != 0) {
        b[0] = func_001f31a8((s32)D_003F6CE0, 6);
        if (b[0] != 0) {
            func_001f3e48(b[0], a0);
            ((O9088 *)b[0])->cc = ((O9088 *)b[0])->ce = D_00643730;
            ((O9088 *)b[0])->d2 = D_006436D0 * 16;
            b[1] = func_001f31a8((s32)D_003F6CA0, 6);
            if (b[1] != 0) {
                func_001f3e48(b[1], b[0]);
                func_001f3dc0(b[0]);
            }
        }
    }
    func_00207830(a0, 4, 2, 0, 0, 122, 112);
}

extern u8 D_003F6D68[];
void func_00205e30(s32, void *);
void func_00206130(s32, s32, s32, s32, s32, s32);
void func_0020ca30(s32, s32, s32, s32);
void func_001fc308(s32, s32, s32, s32, s32, s32, s32, s32, s32);
s32 func_0010fd18(void);
void func_001f9e48(s32, s32, s32, s32, s32, s32, s32);
void func_0020b3d8(s32, s32, s32);

void func_00229150(s32 a0) {
    func_00205e30(a0, D_003F6D68);
    func_00206130(a0, 0, 62, 512, 2, 0x8078C850);
    func_0020ca30(a0, 0, 0x80283212, 0x8050C846);
    func_001fc308(a0, 160, 35, 0, 19, 20, 0, 0x80399BFF, 0x80399BFF);
    func_001f9e48(a0, 0, 173, 35, func_0010fd18(), 19, 0x80399BFF);
    func_0020b3d8(a0, 401, 4);
}

extern s32 D_003F6E18[];
extern s32 D_003F3488[];
extern s32 D_003F3468[];
extern u8 D_003F6D40[];
s32 func_001f31a8(s32, s32);
void func_001f3d58(s32, s32);
void func_001f3e48(s32, s32);
void func_002293f0(s32);
void func_0020bb90(s32, s32);
void func_0020bd18(Obj7d8 *, s32);
void func_0020bda8();

s32 func_00229338(s32 a0) {
    s32 buf[3];
    s32 i;
    for (i = 0; i < 3; i++) {
        buf[i] = func_001f31a8(D_003F6E18[i], 1);
        if (buf[i] != 0) {
            func_001f3e48(buf[i], a0);
            func_001f3d58(buf[i], D_003F3488[i]);
            a0 = buf[i];
        }
    }
    return a0;
}

void func_00229490(s32 a0) {
    s32 buf[3];
    s32 i;
    for (i = 0; i < 3; i++) {
        buf[i] = func_001f31a8(D_003F6E18[i], D_003F3468[i]);
        if (buf[i] != 0) {
            func_001f3e48(buf[i], a0);
            func_001f3d58(buf[i], D_003F3488[i]);
            a0 = buf[i];
        }
    }
    buf[0] = func_001f31a8((s32)D_003F6D40, 4);
    if (buf[0] != 0) {
        func_001f3e48(buf[0], a0);
        func_002293f0(buf[0]);
    }
    func_0020bb90(133, 0);
    func_0020bd18((Obj7d8 *)buf[0], 8);
    func_0020bda8(16);
}

/* Pointer tables only this file uses (phase 4, tools/shift/define_ptr_tables.py). */
extern u8 D_003F5B30[];
extern u8 D_003F5BA0[];
extern u8 D_003F5BE0[];
s32 D_003F5C08[0x4] ALIGNED(8) = {
    (s32)D_003F5BE0, (s32)D_003F5BA0, (s32)D_003F5B30, 0,
};
extern u8 D_00491030[];
extern u8 D_00491048[];
extern u8 D_00491060[];
s32 D_003F5C50[0x4] ALIGNED(16) = {
    (s32)D_00491060, (s32)D_00491048, (s32)D_00491030, 0,
};
#include "data/data_003F.h"
#include "data/data_0049.h"
#include "data/pieces/D_003E90A0.h"
#include "data/pieces/D_003F5C30.h"
#include "data/pieces/D_003F6DF0.h"
#include "data/pieces/D_003F3488.h"
#include "data/pieces/D_003F34C8.h"

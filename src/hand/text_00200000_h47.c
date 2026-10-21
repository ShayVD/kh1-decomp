#include "common.h"
#include "data/bss_0064.h"
#include "data/types/text_00200000_h47.h"
extern S3530 D_003F3530;
extern s32 D_003F3870;
s32 func_001ef8f8(s32);
void func_00122f20(s32, void *);
void func_0020a248(s32);

void func_00209d48(void) {
    s32 i;
    s32 p;
    D_003F3870 = 0;
    for (i = 0; i < 3; i++) {
        p = func_001ef8f8(i);
        if (p == 0) {
            D_003F3530.e[i].active = 0;
        } else {
            D_003F3530.e[i].active = 1;
            func_00122f20(p, &D_003F3530.e[i]);
            func_0020a248(i);
            D_003F3870++;
        }
    }
    D_003F3530.x33c = 0;
}

extern s32 D_006411E0;
extern f32 D_006411E4;
extern s32 D_006411E8; /* src/data/bss_0064.c: f32 D_006411E8 */
extern f32 D_006411EC;
extern f32 D_006411F0;
extern f32 D_006411F4;
extern f32 D_006411F8;
extern f32 D_00641210;
extern f32 D_00641214;

void func_0020bc48(s32 a0, s32 a1, s32 a2) {
    if ((a1 - (s32)D_00641210 + 1) >> 1 == 0 && (a2 - (s32)D_00641214 + 1) >> 1 == 0) {
        D_00641210 = a1;
        D_00641214 = a2;
        D_006411E0 = 0;
        return;
    }
    D_006411E0 = 1;
    D_006411E4 = a0;
    D_006411E8 = 0;
    D_006411EC = D_00641210;
    D_006411F0 = D_00641214;
    D_006411F4 = a1;
    D_006411F8 = a2;
}

extern s32 D_003F3448[];
extern s32 D_003F3488[];
s32 func_001f31a8(s32, s32);
void func_001f3d58(s32, s32);
void func_001f3e20(s32, s32);
void func_001f3e90(s32, s32);

s32 func_0020d1d8(s32 a0) {
    s32 buf[3];
    s32 i;
    for (i = 0; i < 3; i++) {
        buf[i] = func_001f31a8(D_003F3448[i], 1);
        if (buf[i] != 0) {
            func_001f3e90(a0, buf[i]);
            func_001f3e20(buf[i], a0);
            func_001f3d58(buf[i], D_003F3488[i]);
            a0 = buf[i];
        }
    }
    return a0;
}

typedef struct { u8 pad[0x24]; s32 x24; s32 x28; } Obj7d8;
typedef struct { u8 pad[8]; s32 flags; } G5bc8;
extern G5bc8 *D_00425BC8;
void func_0011d768(s32);
void func_001f3708(Obj7d8 *, s32);
s32 func_001f42b8(void);
void func_001f9438(Obj7d8 *, s32, s32, s32, s32, s32, s32);
s32 func_001fe570(Obj7d8 *);
void func_002079c8(Obj7d8 *);
void func_0020bd18(Obj7d8 *, s32);
void func_0020c100(Obj7d8 *, s32);

void func_0020d7d8(Obj7d8 *a0) {
    if (func_001f42b8() != 0) {
        if (D_00425BC8->flags & 0x4000) {
            func_001f3708(a0, 6);
            func_0011d768(3);
        } else {
            func_0020bd18(a0, 8);
            if (func_001fe570(a0) != 0) {
                func_001f3708(a0, 6);
            }
        }
    }
    func_0020c100(a0, a0->x28);
    func_001f9438(a0, 0, 0x80, 0xE, a0->x24, 0xF, 0x801EC8C8);
    func_002079c8(a0);
}

typedef struct { u8 pad[0x25]; u8 n; u8 v[0x4e]; } E4BE8;
extern u32 D_003E3D68;
typedef struct { u8 pad[0x48e]; u8 x48e[11]; u8 x499[256]; } G4BE8;
extern G4BE8 *D_00304BE8;
extern s32 D_00641378[];
extern s32 D_00641278[][16];

void func_0020eb98(void) {
    u32 i;
    s32 j;
    for (i = 0; i < D_003E3D68; i++) {
        E4BE8 *e = (E4BE8 *)((u8 *)D_00304BE8 + D_00304BE8->x48e[i] * 0x74);
        D_00641378[i] = e->n;
        for (j = 0; j < D_00641378[i]; j++) {
            D_00641278[i][j] = e->v[j];
        }
    }
}

extern s32 D_00641BAC;
extern s32 D_00641C10[];
extern s32 D_00642010[];
extern s32 D_00642410;
s32 func_001ef270(s32, s32);
void func_0020f290(s32 *, s32, s32);

void func_00211da0(void) {
    s32 i;
    D_00642410 = 0;
    for (i = 1; i < 256; i++) {
        if (D_00304BE8->x499[i] != 0 && func_001ef270(i, D_00641BAC) != 0) {
            D_00641C10[D_00642410] = i;
            D_00642410++;
        }
    }
    func_0020f290(D_00641C10, 0, D_00642410 - 1);
    for (i = 0; i < D_00642410; i++) {
        D_00642010[i] = D_00304BE8->x499[D_00641C10[i]];
    }
}

u32 func_0020f260(s32);

void func_0020f290(s32 *a, s32 l, s32 r) {
    s32 i, j, t;
    u32 p;
    p = func_0020f260(a[(l + r) / 2]);
    i = l;
    j = r;
    for (;;) {
        while (func_0020f260(a[i]) < p) i++;
        while (p < func_0020f260(a[j])) j--;
        if (i >= j) break;
        t = a[i];
        a[i] = a[j];
        a[j] = t;
        i++;
        j--;
    }
    if (l < i - 1) func_0020f290(a, l, i - 1);
    if (j + 1 < r) func_0020f290(a, j + 1, r);
}

extern s32 D_00641BC4;
extern s32 D_00641BD0;
extern s32 D_00641BD4;
extern s32 D_00641BF0[];
extern s32 D_00641C10[];
extern s32 D_00642410;

void func_002122b8(void) {
    s32 i;
    s32 n;
    s32 k = D_00641BD0 + D_00641BD4;
    if (D_00642410 >= k && D_00641BF0[D_00641BC4] == D_00641C10[k]) return;
    for (i = 0; i < D_00642410; i++) {
        if (D_00641C10[i] == D_00641BF0[D_00641BC4]) {
            n = D_00642410;
            if (n < 7) {
                D_00641BD0 = 0;
                D_00641BD4 = i;
                return;
            }
            n -= 7;
            if (i < n) {
                D_00641BD0 = i;
                D_00641BD4 = 0;
                return;
            }
            D_00641BD0 = n;
            D_00641BD4 = i - n;
            return;
        }
    }
}

extern s32 D_00642CA8[];
extern s32 D_00642CC8;
s32 func_0013c188(s32, s32);

void func_00216280(void) {
    s32 i;
    D_00642CC8 = 0;
    for (i = 0; i < 7; i++) {
        if (func_0013c188(0, i) != 0) {
            D_00642CA8[D_00642CC8++] = i;
        }
    }
    D_00642CA8[D_00642CC8] = 7;
    D_00642CC8++;
}

typedef struct { u8 pad[0xd2]; s16 xd2; } Oac38;
extern u8 D_003F4BF0[];
extern u8 D_003F4C90[];
extern u16 D_00642D24; /* src/data/bss_0064.c: s32 D_00642D24 */
extern s32 D_00642D20;
s32 func_001f31a8(s32, s32);
void func_001f3dc0(s32);
void func_001f3e20(s32, s32);
void func_001f3e90(s32, s32);
s32 func_001f42b8(void);
void func_00207830(s32, s32, s32, s32, s32, s32, s32);

void func_0021ac38(s32 a0) {
    s32 b[2];
    if (func_001f42b8() != 0) {
        b[0] = func_001f31a8((s32)D_003F4C90, 6);
        if (b[0] != 0) {
            func_001f3e90(a0, b[0]);
            func_001f3e20(b[0], a0);
            ((Oac38 *)b[0])->xd2 = D_00642D24 * 16;
            b[1] = func_001f31a8((s32)D_003F4BF0, 6);
            if (b[1] != 0) {
                func_001f3e90(b[0], b[1]);
                func_001f3e20(b[1], b[0]);
                func_001f3dc0(b[0]);
            }
        }
    }
    func_00207830(a0, 4, 2, 0, 0, 122, 111);
}

void func_0021ad08(s32 a0) {
    s32 b[2];
    b[0] = func_001f31a8((s32)D_003F4C90, 6);
    if (b[0] != 0) {
        func_001f3e90(a0, b[0]);
        func_001f3e20(b[0], a0);
        ((Oac38 *)b[0])->xd2 = D_00642D24 * 16;
        b[1] = func_001f31a8((s32)D_003F4BF0, 6);
        if (b[1] != 0) {
            func_001f3e90(b[0], b[1]);
            func_001f3e20(b[1], b[0]);
            func_001f3dc0(b[0]);
        }
    }
    D_00642D20 = a0;
}

typedef struct {
    u8 pad[0x40];
    u8 x40[0x100];
    f32 f[20];
} S5D80;
extern S5D80 D_00425D80;
extern S5D80 *D_00425F70;
void func_00267b08(void *, f32, f32, f32, f32, f32, f32, f32, f32, f32);

void func_0021ae28(void) {
    D_00425F70 = &D_00425D80;
    func_00267b08(D_00425D80.x40, 512.0f, 0.7999999523162842f, 0.839999854564666748046875f, 2048.0f, 2048.0f, 65792.0f, 16777000.0f, 1.0f, 5000.0f);
    D_00425F70->f[0] = 0.0f;
    D_00425F70->f[1] = -170.0f;
    D_00425F70->f[2] = -400.0f;
    D_00425F70->f[3] = 1.0f;
    D_00425F70->f[4] = 0.0f;
    D_00425F70->f[5] = -150.0f;
    D_00425F70->f[6] = 0.0f;
    D_00425F70->f[7] = 1.0f;
    D_00425F70->f[8] = 0.0f;
    D_00425F70->f[9] = 0.0f;
    D_00425F70->f[10] = 1.0f;
    D_00425F70->f[11] = 1.0f;
    D_00425F70->f[12] = 0.0f;
    D_00425F70->f[13] = 1.0f;
    D_00425F70->f[14] = 0.0f;
    D_00425F70->f[15] = 1.0f;
    D_00425F70->f[16] = 0.0f;
    D_00425F70->f[17] = 0.0f;
    D_00425F70->f[18] = 0.0f;
    D_00425F70->f[19] = 1.0f;
}

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

extern s32 D_003F3504;
extern s32 D_003F59A4;
extern f32 D_003F59B0;
extern s32 D_003F59B4;
extern s32 D_003F59B8;
extern s32 D_006430F0;
extern s32 D_006430F4;
extern s32 D_006430F8;
extern s32 D_006430FC;
extern s32 D_00643100;
extern s32 D_00643104;
extern s32 D_00643108;
extern s32 D_0064310C;

void func_0021b5c8(s32 a0, s32 a1, s32 a2, s32 a3, f32 f) {
    D_006430F4 = -1;
    D_006430FC = a0;
    D_003F59B0 = f;
    D_003F59A4 = 0;
    D_00643108 = a2;
    D_0064310C = a3;
    D_003F59B4 = a2 - 0x100;
    D_003F59B8 = a3 - 0xC0;
    D_00643104 = a1;
    if (D_006430F0 == 0) {
        D_006430F0 = 1;
        D_006430F8 = -1;
        D_00643100 = 0;
        D_003F3504 = 0;
    } else if (D_006430F0 == 4) {
        if (D_006430F8 != a0) {
            D_006430F0 = 1;
            D_00643100 = 0;
            D_003F3504 = 0;
        }
    }
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
        s32 fl = D_00425BC8->flags;
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
void func_001c0da0(s32, s32, s32 *);
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
typedef struct { s32 x0; s32 x4; } S8E08;
extern S8E08 D_003E8E08;
s32 func_00233f40(s32, s32);
void func_00233ff8(s32, s32);
void func_002246f8(Obj7d8 *);
void func_00207bb0(Obj7d8 *, s32);

void func_002251b0(Obj7d8 *a0) {
    if (func_001f42b8() != 0) {
        if (func_00233f40(D_006436D4, 0) != 0) {
            func_00233ff8(D_006436D4, 0);
            func_002246f8(a0);
        } else if (D_00425BC8->flags & 0x4000) {
            func_001f36b8(a0);
            func_0011d768(3);
        } else {
            func_0020bd18(a0, 8);
            if (func_001fe570(a0) != 0) {
                func_001f36b8(a0);
            }
        }
    }
    D_003E8E08.x4 = 132;
    D_003E8E08.x0 = D_00643750;
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

extern s32 D_00641388, D_00641790;
extern s32 D_00641390[], D_00641798[];
s32 func_001eea60(s32);
s32 func_001eeac0(s32);
void func_0020f3c8(void) {
    s32 i;
    D_00641388 = 0; D_00641790 = 0;
    for (i = 1; i < 256; i++) {
        if (D_00304BE8->x499[i]) {
            if (func_001eea60(i)) { D_00641390[D_00641388++] = i; }
            if (func_001eeac0(i)) { D_00641798[D_00641790++] = i; }
        }
    }
    if (D_00641388) func_0020f290(D_00641390, 0, D_00641388 - 1);
    if (D_00641790) func_0020f290(D_00641798, 0, D_00641790 - 1);
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
#include "data/pieces/D_003F3530.h"
#include "data/pieces/D_003F5C30.h"
#include "data/pieces/D_003F6DF0.h"

/* func_002134c8: 2 words off (right size) in hand (o32). Only sched2 order in case 0: orig 'sh v0,186; addiu a0,%lo(D_003F3D20); sh a3,206', ours puts sh a3,206 first. Keys: s32 w[4] local array (Ob* casts, so x28 store reloads w[2]), case 3 placed last with goto, end switch has case 0, void func_00211da0/func_002127e0, (x*14+0x7fff)<<5 keeps the 0xfffe0 at-macro, sub-struct D_003E3D70[k].s.d/.s.c gives the split la+addiu 64+addu. Flag sweep: none better. */
#include "common.h"
typedef struct {
    u8 pad0[0x28];
    s32 x28, x2c;
    u8 pad30[0xba - 0x30];
    s16 xba;
    u8 padbc[0xcc - 0xbc];
    s16 xcc, xce, xd0, xd2;
} Ob;
typedef struct { u8 pad0[0x18]; u8 x18; } Mem;
typedef struct { s32 a, b, c, d; } S4;
typedef struct { u8 pad0[0x40]; S4 s; u8 pad50[0xe4 - 0x50]; } E3D70;
extern s32 D_00641BA4;
extern s32 D_00641BA8;
extern s32 D_00641BAC;
extern s32 D_00641BB0;
extern s32 D_00641BB4;
extern s32 D_00641BB8;
extern s32 D_00641BBC;
extern s32 D_00641BC0;
extern s32 D_00641BC4;
extern u16 D_00641BC8;
extern u16 D_00641BCC;
extern u16 D_00641BD0;
extern u16 D_00641BD4;
extern u16 D_00641BD8;
extern u16 D_00641BDC;
extern s32 D_00641BF0[];
extern s32 D_00641C00;
extern s32 D_00642410;
extern s32 D_00642C18;
extern s32 D_003E3D68;
extern E3D70 D_003E3D70[];
typedef struct { u8 pad[0x40]; u8 items[0x30]; } Sub;
typedef struct { u8 pad[4]; Sub sub; } Rec74;
typedef struct { Rec74 r[10]; u8 pad[6]; u8 x48e[0x10b]; u8 x599[1]; } S4BE8;
extern S4BE8 *D_00304BE8;
extern u8 D_003F3B70[], D_003F3BA0[], D_003F3BD0[], D_003F3C00[], D_003F3C30[], D_003F3C60[], D_003F3C90[], D_003F3CC0[], D_003F3CF0[], D_003F3D20[], D_003F3D50[];
s32 func_001f42b8(Ob *);
Ob *func_001f31a8(void *, s32);
void func_001f3e90(Ob *, Ob *);
void func_001f3e20(Ob *, Ob *);
void func_001f3e48(Ob *, Ob *);
void func_001f3dc0(Ob *);
void func_00211da0(void);
void func_002122b8(Ob *);
void func_001fd5e0(Ob *, s32);
void func_001fd610(Ob *, s32);
void func_001fd688(Ob *);
void func_0020a6c0(s32);
void func_002127e0(void);
void func_00206690(Ob *, s32, s32, s32);
void func_00207870(Ob *, s32, s32, s32, s32, s32, s32);
s32 func_001ee5f0(s32);
void func_002114f0(Ob *, s32, s32, s32, s32, s32);

void func_002134c8(Ob *o) {
    s32 w[4];
    s32 *st;
    s32 n;
    s32 *p, *q, *pa;
    if (func_001f42b8(o)) {
        st = &D_00641BA4;
        switch (*st) {
        case 0:
            w[0] = (s32)func_001f31a8(D_003F3D50, 6);
            if (w[0] == 0) break;
            func_001f3e90(o, (Ob *)w[0]);
            func_001f3e20((Ob *)w[0], o);
            p = &D_003E3D68;
            q = &D_00641BC4;
            ((Ob *)w[0])->xd2 = *(u16 *)q * 16;
            ((Ob *)w[0])->xba = (*p * 14 + 0x7fff) << 5;
            ((Ob *)w[0])->xce = ((Ob *)w[0])->xcc = *p;
            w[1] = (s32)func_001f31a8(D_003F3D20, 6);
            if (w[1] == 0) break;
            func_001f3e90((Ob *)w[0], (Ob *)w[1]);
            func_001f3e20((Ob *)w[1], (Ob *)w[0]);
            w[2] = (s32)func_001f31a8(D_003F3CF0, 6);
            if (w[2] == 0) break;
            func_001f3e90((Ob *)w[1], (Ob *)w[2]);
            func_001f3e20((Ob *)w[2], (Ob *)w[1]);
            D_00641BAC = D_00304BE8->x48e[*q];
            D_00641BB0 = (s32)&D_00304BE8->r[D_00641BAC].sub;
            n = ((Mem *)D_00641BB0)->x18 + 1;
            ((Ob *)w[2])->xcc = n;
            if (n < 9) {
                ((Ob *)w[2])->xce = n;
                ((Ob *)w[2])->xba = n * 448 - 32;
            } else {
                ((Ob *)w[2])->xce = 8;
                ((Ob *)w[2])->xba = 3552;
            }
            ((Ob *)w[2])->xd0 = D_00641BC8 * 16;
            ((Ob *)w[2])->xd2 = D_00641BCC * 16;
            func_001f3dc0((Ob *)w[0]);
            break;
        case 1:
        c1:
            w[0] = (s32)func_001f31a8(D_003F3CF0, 6);
            if (w[0] == 0) break;
            func_001f3e90(o, (Ob *)w[0]);
            func_001f3e20((Ob *)w[0], o);
            n = ((Mem *)D_00641BB0)->x18 + 1;
            ((Ob *)w[0])->xcc = n;
            if (n < 9) {
                ((Ob *)w[0])->xce = n;
                ((Ob *)w[0])->xba = n * 448 - 32;
            } else {
                ((Ob *)w[0])->xce = 8;
                ((Ob *)w[0])->xba = 3552;
            }
            ((Ob *)w[0])->xd0 = D_00641BC8 * 16;
            ((Ob *)w[0])->xd2 = D_00641BCC * 16;
            ((Ob *)w[0])->x28 = 1;
            w[1] = (s32)func_001f31a8(D_003F3CC0, 6);
            if (w[1] == 0) break;
            func_001f3e90((Ob *)w[0], (Ob *)w[1]);
            func_001f3e20((Ob *)w[1], (Ob *)w[0]);
            func_001f3dc0((Ob *)w[0]);
            break;
        case 2:
            if (D_00641BB8 == 0) {
                pa = &D_00641BA8;
                D_00641BBC = D_00641BF0[*pa];
                func_00211da0();
                D_00641C00 = 1;
                w[0] = (s32)func_001f31a8(D_003F3C00, 6);
                if (w[0] == 0) break;
                func_001f3e48((Ob *)w[0], o);
                func_002122b8(o);
                ((Ob *)w[0])->xd0 = D_00641BD0 * 16;
                ((Ob *)w[0])->xd2 = D_00641BD4 * 16;
                func_001fd5e0((Ob *)w[0], D_00642410);
                func_001fd610((Ob *)w[0], 7);
                func_001fd688((Ob *)w[0]);
                w[1] = (s32)func_001f31a8(D_003F3BD0, 6);
                if (w[1] == 0) break;
                func_001f3e48((Ob *)w[1], (Ob *)w[0]);
                w[2] = (s32)func_001f31a8(D_003F3BA0, 6);
                if (w[2] != 0) {
                    func_001f3e48((Ob *)w[2], (Ob *)w[1]);
((Ob *)w[2])->x28 = D_003E3D70[D_00641BAC].s.d;
                    ((Ob *)w[2])->x2c = D_003E3D70[D_00641BAC].s.c;
                    if (D_00641BC4 != 3) {
                        w[3] = (s32)func_001f31a8(D_003F3B70, 6);
                        if (w[3] != 0) {
                            func_001f3e48((Ob *)w[3], (Ob *)w[2]);
                            func_0020a6c0(*pa);
                        }
                    }
                }
                func_001f3dc0((Ob *)w[0]);
            } else {
                D_00641BB4 = D_00641BB8 - 1;
                D_00641BBC = ((u8 *)(D_00641BB8 + D_00641BB0))[24];
                func_002127e0();
                w[0] = (s32)func_001f31a8(D_003F3C90, 6);
                if (w[0] == 0) break;
                func_001f3e90(o, (Ob *)w[0]);
                func_001f3e20((Ob *)w[0], o);
                ((Ob *)w[0])->xd0 = D_00641BD8 * 16;
                ((Ob *)w[0])->xd2 = D_00641BDC * 16;
                func_001fd5e0((Ob *)w[0], D_00642C18);
                func_001fd610((Ob *)w[0], 7);
                func_001fd688((Ob *)w[0]);
                w[1] = (s32)func_001f31a8(D_003F3C60, 6);
                if (w[1] == 0) break;
                func_001f3e90((Ob *)w[0], (Ob *)w[1]);
                func_001f3e20((Ob *)w[1], (Ob *)w[0]);
                w[2] = (s32)func_001f31a8(D_003F3C30, 6);
                if (w[2] != 0) {
                    func_001f3e90((Ob *)w[1], (Ob *)w[2]);
                    func_001f3e20((Ob *)w[2], (Ob *)w[1]);
                }
                func_001f3dc0((Ob *)w[0]);
            }
            break;
        case 3:
            *st = 1;
            goto c1;
        }
    }
    switch (D_00641BA4) {
    case 0:
        break;
    case 1:
        func_00206690(o, 0, 83, 11);
        func_00207870(o, 11, 0, 11, 71, 122, func_001ee5f0(D_00641BAC));
        break;
    case 2:
        func_00206690(o, 0, 83, 11);
        func_00207870(o, 11, 0, 11, 71, 122, func_001ee5f0(D_00641BAC));
        func_00206690(o, 133, 83, 26);
        func_002114f0(o, 11, 159, 71, 166, D_00641BBC);
        func_00206690(o, 325, 83, 187);
        break;
    case 3:
        func_00206690(o, 0, 83, 11);
        func_00207870(o, 11, 0, 11, 71, 122, func_001ee5f0(D_00641BAC));
        func_00206690(o, 133, 83, 26);
        func_002114f0(o, 11, 159, 71, 166, D_00641BBC);
        func_00206690(o, 325, 83, 187);
        func_00206690(o, 0, 111, 159);
        func_002114f0(o, 11, 159, 99, 166, D_00641BC0);
        func_00206690(o, 325, 111, 187);
        break;
    }
}

/* Page 5 of the menu, part 3 (docs/modules.md "Session 41"),
 * 0x0021cd68-0x0021dbb8: the frame of page 5 (message 0x6e; its open
 * function is func_0021daa0, set up func_0021dad8, reset func_0021db30).
 * func_0021d348 is its first window: steps D_00642EA4 through loading six
 * files (D_00490F58 ... D_00490FD0, each finished by one of func_0021d228 ...
 * func_0021d318), asks for the model (journalmdl.c's func_0021b5c8), and
 * sets D_003F34B8->b112[1] (the top menu's marker, settings.c's neighbour
 * func_0021add8 reads it) once all six D_003F5C30 flags are set.
 * func_0021cd68 is the list of sections (D_00642E98, D_00642EA0 of them,
 * filled by func_0021cfc8 from D_003F5C18); a section opens a window from
 * D_003F59E8 and calls its opener D_003F5A00[k] (src/menu/journal_s0.c ...
 * journal_s5.c, include/menu/journal.h), whose set up and reset are in
 * func_0021dad8 / func_0021db30.  Most
 * likely Jiminy's journal; not proved by a boot.
 *
 * Window views: JWin (plain s16 at +0xcc / +0xd2: TextWin's +0xd0 union
 * reorders), JcWin (the list's +0xc) and topmenu.c's N_3f34c4. */
#include "common.h"
#include "platform/pad.h"
#include "platform/thread.h"
#include "vm/script_vm.h"
#include "data/bss_0064.h"
#include "data/bss_0064_mixed.h"
#include "data/data_003E.h"
#include "data/data_003F.h"
#include "data/data_0049.h"
#include "data/pieces/D_003F34B8.h"
#include "data/pieces/D_003F34C4.h"
#include "data/pieces/D_003F34C8.h"
#include "data/pieces/D_00425BC8.h"

typedef struct JWin {
    u8 pad[0x24];
    struct JWin *x24; /* holds a byte id; pointer type matches the original aliasing */
    u8 pad28[0xA0 - 0x28];
    f32 xa0;
    u8 pada4[0xBA - 0xA4];
    s16 xba;
    u8 padbc[0xCA - 0xBC];
    s16 xca;
    s16 xcc;
    s16 xce;
    u8 padd0[2];
    s16 xd2;
    u8 padd4[4];
    s16 xd8;
    s16 xda;
} JWin;
typedef struct { u8 pad[0xC]; void *xc; } JcWin;

extern u8 *D_003F59E8[];
extern void (*D_003F5A00[])(JWin *);
extern s32 D_003F5A18[];
extern s32 D_003F59D0[];
extern s32 D_003F5C08[];
extern s32 D_003F5C18[];
extern s32 D_003F5C30[];
extern s32 D_003F3488[];
extern u8 D_00490F58[], D_00490F70[], D_00490F88[], D_00490FA0[], D_00490FB8[], D_00490FD0[];
extern u8 D_00642EB0[];
extern u8 D_00642F60[];
s32 D_00642E90 ALIGNED(16);

void func_0011d768(s32);
void *func_0011fbb0(s32, s32, s32, s32, s32, s32, s32, s32, s32, void *);
void func_00120748(void *, s32, void *, s32);
void *func_001f31a8(void *, s32);
s32 func_001f3758(void *);
void func_001f37c0(void *, s32);
void func_001f3d58(void *, s32);
void func_001f3e48(void *, void *);
s32 func_001f42b8(void *);
void *func_001f4468(void *);
s32 func_001f44a0(u8 *);
s32 func_001f9438(void *, s32, s32, s32, s32, s32, u32);
s32 func_001fc308(void *, s32, s32, s32, s32, s32, s32, u32, u32);
s32 func_001fd518(void *);
void func_001fd858(void *);
s32 func_001fe570(void *);
void func_00205b30(void *, void *);
void func_00205e30(void *, void *);
void func_00206130(void *, s32, s32, s32, s32, u32);
s32 func_00207320(s32);
void func_002073b0(s32);
void func_00207428(void *, s32, s32);
void func_00207560(void *, s32, s32);
void func_00207830(void *, s32, s32, s32, s32, s32, s32);
void func_0020bda8(s32);
void func_0020be10(s32);
void func_0020ca30(void *, s32, u32, u32);
void func_0020d1d8(void *);
void func_0021ae28(void);
void func_0021af38(void *);
void func_0021b418(void);
void func_0021b4a0(void);
void func_0021b5c8(s32, s32, s32, s32, f32);
void func_0021b6a0(void);
void func_0021b820(void);
void func_0021c4f8(void *);
void func_0021c5e0(void *, s32, s32);
void func_0021ccd0(void *, s32);
void func_0021d188(void);
void func_0021d228(void);
void func_0021d258(void);
void func_0021d288(void);
void func_0021d2b8(void);
void func_0021d2e8(void);
void func_0021d318(void);
void func_0021cfc8(void);
void func_0021fb10(void);
void func_0021fb28(void);
void func_0021fb50(void);
void func_00220590(void);
void func_002205c0(void);
void func_002210c0(void);
void func_002210f0(void);
void func_00222b50(void);
void func_00222b80(void);
void func_002234b8(void);
void func_002234e8(void);
void func_00223948(void);
void func_00223978(void);
void func_00223e10(void);

void func_0021cd68(JcWin *a) {
    JWin *o[2];
    s32 i, y, k, v;
    s32 *p;
    if (func_001f42b8(a)) {
        if (D_00425BC8->x8 & PAD_CROSS) {
            func_001f3758(a->xc);
            func_0011d768(3);
            D_00642E94 = 1;
        } else {
            func_001fd858(a);
            v = func_001fd518(a);
            D_00643010 = v;
            p = &D_00643014;
            *p = D_00642E98[v];
            if (func_001fe570(a)) {
                func_001f3758(a->xc);
                if ((o[0] = func_001f31a8(D_003F59E8[*p], D_003F5A18[*p]))) {
                    func_001f3e48(o[0], a->xc);
                    D_003F5A00[*p](o[0]);
                    o[0]->xa0 = D_003E90AC;
                }
            }
        }
    }
    func_0021b820();
    func_0021c5e0(a, 257, 72);
    y = 108;
    for (i = 0; i < D_00642EA0; i++) {
        k = D_00642E98[i];
        func_001f9438(a, 0, 330, y, D_003F59D0[k], 15, 0x80B4DCF5);
        if (D_003F5C30[k]) func_00207560(a, 450, y - 2);
        if (!func_00207320(k)) func_00207428(a, 435, y + 7);
        y += 28;
    }
    do { func_0021c4f8(a); } while (0);
}

void func_0021cf90(void *arg0) {
    func_0021b820();
    func_0021ccd0(arg0, 0);
    func_0021af38(arg0);
}

void func_0021cfc8(void) {
    s32 i;
    D_00642EA0 = 0;
    for (i = 0; i < 6; i++) {
        if (D_003F5C18[i]) D_00642E98[D_00642EA0++] = i;
    }
}

void func_0021d028(void *a) {
    JWin *o[2];
    if (!func_001f42b8(a)) return;
    switch (D_00642E94) {
    case 0:
        if (!D_00643100) return;
        if (!(o[0] = func_001f31a8(D_003F5A60, 50))) return;
        func_001f3e48(o[0], a);
        if (!(o[1] = func_001f31a8(D_003F5A30, 6))) return;
        func_001f3e48(o[1], o[0]);
        {
            s32 *n = &D_00642EA0;
            s32 *c = &D_00643010;
            o[1]->xcc = *n;
            if (*c >= *n) *c = *n - 1;
            o[1]->xd2 = *c << 4;
        }
        break;
    case 1:
        if (func_001f44a0(D_003F5A60)) return;
        func_001f37c0(D_003F34C4->x10, 50);
        func_001f3d58(D_003F34C4->x10->x10, 2);
        func_001f3d58(D_003F34C4->x10->x10->x10, 2);
        func_0020d1d8(func_001f4468(a));
        func_0020bda8(16);
        break;
    }
}

void func_0021d188(void) {
    func_0011fbb0(0x3600, 4, 0x13, 0, 0, 0x100, 0x100, 0x1000, D_003F34E0, D_00642EB0);
    func_0011fbb0(0x3700, 1, 0, 0, 0, 0x10, 0x10, 0x40, D_003F34E0 + 0x10000, D_00642F60);
}

void func_0021d228(void) {
    D_003F34DC += 1;
    D_003F34C8 -= 1;
}

void func_0021d258(void) {
    D_003F34E4 += 1;
    D_003F34C8 -= 1;
}

void func_0021d288(void) {
    D_003F34EC += 1;
    D_003F34C8 -= 1;
}

void func_0021d2b8(void) {
    D_003F34F4 += 1;
    D_003F34C8 -= 1;
}

void func_0021d2e8(void) {
    D_003F3514 += 1;
    D_003F34C8 -= 1;
}

void func_0021d318(void) {
    D_003F351C += 1;
    D_003F34C8 -= 1;
}

void func_0021d348(void *o) {
    void *p;
    s32 i;
    if (func_001f42b8(o)) {
        switch (D_00642EA4) {
        case 0:
            switch (D_003F34FC) {
            default:
                D_00642EA4 = 2;
                break;
            case 0:
                func_00223e10();
                D_00642EA4++;
                break;
            case 1:
                D_00642EA4++;
                break;
            }
            break;
        case 1:
            if (D_003F34FC == 2) D_00642EA4++;
            break;
        case 2:
            switch (D_003F34DC) {
            default:
                D_00642EA4 = 4;
                break;
            case 0:
                D_003F34DC = 1;
                D_003F34C8++;
                D_00642EA4++;
                func_00120748(D_00490F58, D_003F34E0, func_0021d228, 0);
                break;
            case 1:
                D_00642EA4++;
                break;
            }
            break;
        case 3:
            if (D_003F34DC == 2) D_00642EA4++;
            break;
        case 4:
            switch (D_003F34E4) {
            default:
                D_00642EA4 = 6;
                break;
            case 0:
                D_003F34E4 = 1;
                D_003F34C8++;
                D_00642EA4++;
                func_00120748(D_00490F70, D_003F34E8, func_0021d258, 0);
                break;
            case 1:
                D_00642EA4++;
                break;
            }
            break;
        case 5:
            if (D_003F34E4 == 2) D_00642EA4++;
            break;
        case 6:
            switch (D_003F34EC) {
            default:
                D_00642EA4 = 8;
                break;
            case 0:
                D_003F34EC = 1;
                D_003F34C8++;
                D_00642EA4++;
                func_00120748(D_00490F88, D_003F34F0, func_0021d288, 0);
                break;
            case 1:
                D_00642EA4++;
                break;
            }
            break;
        case 7:
            if (D_003F34EC == 2) D_00642EA4++;
            break;
        case 8:
            switch (D_003F34F4) {
            default:
                D_00642EA4 = 10;
                break;
            case 0:
                D_003F34F4 = 1;
                D_003F34C8++;
                D_00642EA4++;
                func_00120748(D_00490FA0, D_003F34F8, func_0021d2b8, 0);
                break;
            case 1:
                D_00642EA4++;
                break;
            }
            break;
        case 9:
            if (D_003F34F4 == 2) D_00642EA4++;
            break;
        case 10:
            switch (D_003F3514) {
            default:
                D_00642EA4 = 12;
                break;
            case 0:
                D_003F3514 = 1;
                D_003F34C8++;
                D_00642EA4++;
                func_00120748(D_00490FB8, D_003F3518, func_0021d2e8, 0);
                break;
            case 1:
                D_00642EA4++;
                break;
            }
            break;
        case 11:
        case 13:
            if (D_003F3514 == 2) D_00642EA4++;
            break;
        case 12:
            switch (D_003F351C) {
            default:
                D_00642EA4 = 14;
                break;
            case 0:
                D_003F351C = 1;
                D_003F34C8++;
                D_00642EA4++;
                func_00120748(D_00490FD0, D_003F3520, func_0021d318, 0);
                break;
            case 1:
                D_00642EA4++;
                break;
            }
            break;
        case 14:
            PlatFlushCache(0);
            func_0021b5c8(0xC009B, 0, 128, 128, 5.0f);
            D_00642E94 = 0;
            p = func_001f31a8(D_003F5A90, 0);
            if (p) func_001f3e48(p, o);
            func_0021fb10();
            if (!D_003F34B8->b112[1]) {
                for (i = 0; i < 6; i++) {
                    if (!D_003F5C30[i]) goto inc;
                }
                D_003F34B8->b112[1] = 1;
                func_0011d768(18);
            }
        inc:
            D_00642EA4++;
            break;
        case 15:
            break;
        }
    }
    if (D_00642EA4 == 15) func_0021b6a0();
    func_00207830(o, 4, 2, 0, 0, 122, 110);
}

void func_0021d848(void) {
    func_002073b0(0);
}

/* func_001f9438 / func_001fc308 declared void put this 7 words off (the move
 * of D_003F59D0[...] into t3 is scheduled early); s32 matches. */
void func_0021d860(void *a) {
    func_00205b30(a, D_003F5AE8);
    func_00205b30(a, D_003F5AE8 + 32);
    func_00206130(a, 0, 62, 512, 2, 0x80364B2C);
    func_0020ca30(a, 0, 0x804C7F33, 0x805BB66A);
    func_001fc308(a, 160, 35, 0, 19, 20, 0, 0x80399BFF, 0x80399BFF);
    func_001f9438(a, 0, 173, 35, D_003F59D0[D_00643014], 19, 0x80399BFF);
}

void func_0021d948(void *a) {
    func_00205b30(a, D_003F5B58);
    func_00205b30(a, D_003F5B58 + 32);
    func_00206130(a, 0, 0, 512, 2, 0x80364B2C);
}

void func_0021d9a8(void *a) {
    func_00205e30(a, D_003F5BC8);
}

void func_0021d9c8(void) {
    func_0021b418();
}

void *func_0021d9e0(void *a0) {
    void *buf[3];
    s32 i;
    for (i = 0; i < 3; i++) {
        buf[i] = func_001f31a8((void *)D_003F5C08[i], 50);
        if (buf[i] != 0) {
            func_001f3e48(buf[i], a0);
            func_001f3d58(buf[i], D_003F3488[i]);
            a0 = buf[i];
        }
    }
    func_0020be10(16);
    return a0;
}

void func_0021daa0(JWin *arg0) {
    arg0->xa0 = (f32) D_003E9104;
    D_00642E90 = (s32)arg0;
    D_00642EA4 = 0;
    func_0021b4a0();
}

void func_0021dad8(void) {
    func_0021d188();
    func_0021fb28();
    func_00220590();
    func_002210c0();
    func_00223948();
    func_00222b50();
    func_002234b8();
    func_0021cfc8();
    func_0021ae28();
}

void func_0021db30(void) {
    s32 i;
    D_00643010 = 0;
    D_00643014 = 0;
    D_003F34B8->b112[1] = 0;
    for (i = 5; i >= 0; i--) D_003F5C30[i] = 0;
    func_0021fb50();
    func_002205c0();
    func_002210f0();
    func_00223978();
    func_00222b80();
    func_002234e8();
}

/* Pointer tables only this file uses (phase 4, tools/shift/define_ptr_tables.py;
 * moved from h71 and h47 in session 41): the sections' window descriptors
 * and openers, and func_0021d9e0's descriptors. */
extern u8 D_003F5FC0[];
extern u8 D_003F61B0[];
extern u8 D_003F6330[];
extern u8 D_003F6620[];
extern u8 D_003F6710[];
extern u8 D_003F6800[];
u8 *D_003F59E8[0x6] ALIGNED(8) = {
    (void *)D_003F61B0, (void *)D_003F6710, (void *)D_003F5FC0, (void *)D_003F6330,
    (void *)D_003F6800, (void *)D_003F6620,
};
void func_0021faf8();
void func_00220580();
void func_002210b0();
void func_00222b40();
void func_002234a8();
void func_00223938();
void (*D_003F5A00[0x6])(JWin *) ALIGNED(16) = {
    (void *)func_00220580, (void *)func_002234a8, (void *)func_0021faf8, (void *)func_002210b0,
    (void *)func_00223938, (void *)func_00222b40,
};
extern u8 D_003F5B30[];
extern u8 D_003F5BA0[];
extern u8 D_003F5BE0[];
s32 D_003F5C08[0x4] ALIGNED(8) = {
    (s32)D_003F5BE0, (s32)D_003F5BA0, (s32)D_003F5B30, 0,
};

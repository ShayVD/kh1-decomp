/* The load screen, part 2 (docs/modules.md "Session 43"), 0x0022b248-0x0022bd58:
 * its frame.  func_0022bcb8 opens it by itself (D_003F34A4 = 1, the window
 * chain D_003F71A0 of func_0022bb48: five windows D_003F71C8[i]) and starts
 * the task func_0022bc28 (func_0011ef10), which closes the screen when its
 * windows are gone (func_001f40c8).  The port window D_003F7000 / D_003F7028
 * (func_0022b410) sets D_006437C4 and opens the frame D_00646990
 * (D_003F6FA0, loadmenu.c's windows) with the card task's status line
 * D_003F6E40; a port with no card (D_00425C28[port].x0 == 3) opens the box
 * func_0022b2e0 (D_003F6FD0, title D_003F6FF8[port]).  func_0022b648 is the
 * free-space bar (D_006469A0 free, D_00646998 used, of 60), func_0022b8a0
 * the screen's open (both ports' state reset to 3), func_0022bd20 the reset
 * of the cursors.  Most likely the title menu's "load"; not proved by a boot. */
#include "common.h"
#include "platform/pad.h"
#include "data/bss_0064.h"
#include "data/data_003F.h"
#include "data/pieces/D_00425BC8.h"
#include "data/pieces/D_00425C28.h"
#include "data/pieces/D_003F6E40.h"
#include "menu/page7.h"

extern s32 D_006437C4;
extern s32 D_006437C8[];
extern s32 D_006437D0[];
extern s32 D_006437DC;
extern s32 D_006437E4;
extern s32 D_00646990;
extern s32 D_006469A0;
extern void *D_003F71C8[];

void func_00109268(void);
void func_00109278(void);
s32 func_0011d768(s32);
s16 *func_0011ef10(s32, void *);
s32 func_001efd98(s32);
void func_001f3110(void);
void *func_001f31a8(void *, s32);
void func_001f36b8(void *);
void func_001f3840(void *);
void func_001f3d58(void *, s32);
void func_001f3dc0(void *);
void func_001f3e48(void *, void *);
void func_001f4040(void *, s32);
void func_001f4058(void *, s32);
void func_001f40a0(void *, s32);
s32 func_001f40c8(void);
s32 func_001f42b8(void *);
s32 func_001f4390(void *);
void func_001f82b0(void);
void func_001f9010(s32);
s32 func_001f9438(void *, s32, s32, s32, s32, s32, u32);
void func_001fb428(void *, s32, s32, s32, s32, s32, s32, s32, u32);
void func_001fc308(void *, s32, s32, s32, s32, s32, s32, u32, u32);
s32 func_001fd518(void *);
void func_001fd858(void *);
s32 func_001fe570(void *);
s32 func_001fe5a0(void *);
void func_00205938(void *, s32);
void func_00205e30(void *, void *);
void func_00206130(void *, s32, s32, s32, s32, u32);
void func_00206370(void *, s32, s32, s32, s32, u32, u32, u32, u32);
void func_00207830(void *, s32, s32, s32, s32, s32, s32);
s32 func_00207bb0(void *, s32);
void func_00209340(void *, s32, void *);
void func_0020a8f0(void);
void func_0020ab88(s32);
void func_0020b968(void);
void func_0020b998(void);
void func_0020bb90(s32, s32);
void func_0020bd18(void *, s32);
void func_0020bda8(s32);
void func_0020be10(s32);
void func_0020ca30(void *, s32, u32, u32);
void func_002336f8(void);
void func_00233ef8(s32);
s32 func_00233f18(void);
void func_00233f28(s32, s32);
s32 func_00233f40(s32, s32);
void func_00233fb0(s32, s32);
void func_00233ff8(s32, s32);
void func_002365e0(void);

void func_0022b248(PtWin *arg0) {
    if (func_001f42b8(arg0) != 0) {
        if (D_00425BC8->x8 & PAD_CROSS) {
            func_001f36b8(arg0);
            func_0011d768(3);
        } else {
            func_0020bd18(arg0, 8);
            if (func_001fe570(arg0) != 0) {
                func_001f36b8(arg0);
            }
        }
    }
    func_00207bb0(arg0, D_003F6FC8[D_006437C4]);
}

void func_0022b2e0(PtWin *arg0) {
    PtWin *o;
    s32 d;

    func_0011d768(4);
    o = func_001f31a8(D_003F6FD0, 6);
    if (o != NULL) {
        func_001f3e48(o, arg0);
        func_001f4058(o, 2);
        func_001f3d58(o, 6);
        d = func_001efd98(D_003F6FF8[D_006437C4]) * 0x170;
        o->xb4 -= d;
        o->xba += d;
        o->xc0 += d;
        func_0020bda8(0x10);
    }
}

void func_0022b3c8(PtWin *arg0) {
    func_001f9010(0x17);
    func_001f9438(arg0, 0, 0xAE, 0xC, 0x199, 0x11, 0x80399BFF);
}

void func_0022b410(PtWin *a0) {
    PtWin *objs[2];

    if (func_001f42b8(a0)) {
        if (D_00425BC8->x8 & PAD_CROSS) {
            func_001f3840(a0);
            func_0020be10(16);
            func_0011d768(3);
        } else {
            if (a0->x10 == 0) {
                objs[0] = func_001f31a8(D_003F7000, 6);
                if (objs[0]) {
                    func_001f3e48(objs[0], a0);
                    func_001f3dc0(a0);
                }
            }
            func_001fd858(a0);
            func_0020bd18(a0, 8);
            D_006437C4 = func_001fd518(a0);
            func_00233f28(D_006437C4, 0);
            D_00425C28[D_006437C4 ^ 1].x0 = 3;
            if (func_001fe5a0(a0)) {
                if (D_00425C28[D_006437C4].x0 != 3) {
                    if (func_00233f40(D_006437C4, 0)) {
                        func_00233fb0(D_006437C4, 0);
                        func_00233ff8(D_006437C4, 0);
                        D_006469A4 = 0;
                    }
                    if (D_006437D8 != D_006437C4) D_006469A4 = 0;
                    func_0011d768(2);
                    func_00233f18();
                    D_006437E0 = 0;
                    D_006437DC = 0;
                    func_001f36b8(a0->x10);
                    objs[0] = func_001f31a8(D_003F6FA0, 0);
                    if (objs[0]) {
                        func_001f3e48(objs[0], a0);
                        D_00646990 = (s32)objs[0];
                        objs[1] = func_001f31a8(D_003F6E40, 6);
                        if (objs[1]) {
                            func_001f3e48(objs[1], objs[0]);
                            func_001f3dc0(objs[0]);
                        }
                    }
                } else {
                    func_0022b2e0(a0);
                }
            }
        }
    }
    func_00209340(a0, 2, D_003F7028);
}

void func_0022b630(void) {
    func_00109268();
}

void func_0022b648(PtWin *a0) {
    s32 a, b, c, w, x;

    if (D_006437E4 == 0) return;
    a = D_006469A0;
    b = D_00646998;
    c = 60 - a - b;
    func_001f9438(a0, 0, 20, 8, 404, 15, 0x802b803f);
    func_001fb428(a0, 1, 0, 0, 113, 30, a, 15, 0x8040be5d);
    func_001f9438(a0, 0, 20, 66, 405, 15, 0x801b7de1);
    func_001fb428(a0, 1, 0, 0, 113, 88, b, 15, 0x80399bff);
    func_001f9438(a0, 0, 20, 124, 406, 15, 0x80995d3f);
    w = (u32)(a * 33536) / 60;
    if (a) func_00206370(a0, 8, 9, 6, w >> 8, 0x802b803f, 0x802b803f, 0x802b803f, 0x802b803f);
    x = w + 2304;
    w = (u32)(b * 33536) / 60;
    if (b) func_00206370(a0, 8, x >> 8, 6, w >> 8, 0x80399bff, 0x80399bff, 0x80399bff, 0x80399bff);
    x += w;
    w = (u32)(c * 33536) / 60;
    if (c) func_00206370(a0, 8, x >> 8, 6, w >> 8, 0x80d98659, 0x80d98659, 0x80d98659, 0x80d98659);
}

void func_0022b8a0(PtWin *arg0) {
    PtWin *o[3];

    if (func_001f42b8(arg0) != 0) {
        func_00109278();
        func_00233ef8(0);
        D_006469A4 = 0;
        D_006437E4 = 0;
        D_00425C28[0].x0 = 3;
        D_00425C28[1].x0 = 3;
        o[0] = func_001f31a8(D_003F7060, 6);
        if (o[0] != NULL) {
            func_001f3e48(o[0], arg0);
            func_001f4040(o[0], 4);
            func_001f40a0(o[0], 0x5A000000);
            o[1] = func_001f31a8(D_003F7030, 6);
            if (o[1] != NULL) {
                func_001f3e48(o[1], o[0]);
                o[1]->xd2 = *(u16 *)&D_006437C4 << 4;
                o[2] = func_001f31a8(D_003F7000, 6);
                if (o[2] != NULL) {
                    func_001f3e48(o[2], o[1]);
                    func_001f3dc0(o[1]);
                }
            }
        }
    }
}

void func_0022b9a8(PtWin *arg0) {
    func_00207830(arg0, 4, 2, 0, 0, 0x7A, 0x192);
}

void func_0022b9d8(PtWin *arg0) {
    func_00205e30(arg0, &D_003F70E8);
    func_00206130(arg0, 0, 0x3E, 0x200, 2, 0x80399BFF);
    func_0020ca30(arg0, 0, 0x80221F8F, 0x806360E1);
}

void func_0022ba40(PtWin *arg0) {
    func_00205e30(arg0, D_003F7128);
    func_00206130(arg0, 0, 0, 0x200, 2, 0x80399BFF);
    func_001fc308(arg0, 0xA0, 0xC, 0, 0x3F, 0x14, 0, 0x80399BFF, 0x80399BFF);
}

void func_0022bac0(PtWin *arg0) {
    func_0020ab88(arg0->x90 / 2);
    func_00205938(arg0, 0x64000000);
}

void func_0022bb00(void *a0) {
    if (func_001f4390(a0) != 0 && (D_00425BC8->x8 & 8)) {
        func_0011d768(4);
    }
}

void func_0022bb48(PtWin *arg0) {
    PtWin *objs[5];
    s32 i;

    for (i = 0; i < 5; i++) {
        objs[i] = func_001f31a8(D_003F71C8[i], D_003F71E0[i]);
        if (objs[i] != 0) {
            func_001f3e48(objs[i], arg0);
            func_001f3d58(objs[i], D_003F71F8[i]);
            arg0 = objs[i];
        }
    }
    func_001f3dc0(objs[4]);
    func_0020bb90(0, 0);
    func_0020bda8(0x10);
}

s32 func_0022bc28(void) {
    if (func_001f40c8() != 0) {
        func_002336f8();
        func_002365e0();
        func_001f82b0();
        func_0020b998();
        return 0;
    }
    D_003F34A4 = 0;
    return 4;
}

void func_0022bc80(void) {
    D_003F34A4 = 1;
    func_0020a8f0();
    func_0020b968();
    D_003F720C = 0;
}

void func_0022bcb8(s32 arg0) {
    PtWin *w;

    func_001f3110();
    func_0022bc80();
    w = func_001f31a8(&D_003F71A0, 0);
    if (w != 0) {
        func_0022bb48(w);
    }
    func_0011ef10(0x2BFE7, func_0022bc28)[1] = arg0;
}

void func_0022bd20(void) {
    D_006437C4 = 0;
    D_006437D8 = 0;
    D_006437C8[0] = 0;
    D_006437C8[1] = 0;
    D_006437D0[0] = 0;
    D_006437D0[1] = 0;
}

/* The five windows of func_0022bb48's chain (moved from h48 in session 44,
 * phase 4, tools/shift/define_ptr_tables.py). */
extern u8 D_003F7090[];
extern u8 D_003F70C0[];
extern u8 D_003F7100[];
extern u8 D_003F7140[];
extern u8 D_003F7170[];
void *D_003F71C8[0x6] ALIGNED(8) = {
    (void *)D_003F7170, (void *)D_003F7140, (void *)D_003F7100, (void *)D_003F70C0,
    (void *)D_003F7090, 0,
};

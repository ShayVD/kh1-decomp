/* Page 7 of the menu, part 3 (docs/modules.md "Session 42"),
 * 0x00228760-0x002298e0: the page's frame (message 0x70).  Its open
 * func_002293f0 opens the list D_003F6CE0 (func_002287f8: D_00643730 rows of
 * D_00643720, the cursor D_006436D0; 0 save (savemenu.c, the port window
 * D_003F6C00 / D_003F6BD0), 1 the party change (party.c), 2 a message box
 * (D_003F6C60) unless D_003F6E2C == 3, 3 leaves) with its status line
 * D_003F6CA0 (func_00228760); set up func_00229820, reset func_00229850.
 * func_002295a0 opens the menu on this page by itself (D_003F34A8 = 1, the
 * window chain of func_00229490 with the panels func_00229150 /
 * func_00229220 / func_002292a8; arg1 == 1 drops the message box row), and
 * func_002297a0 opens the party change by itself (D_003F34A8 = 2,
 * func_00229690 -> func_00228e70).  Most likely the save point's menu (save,
 * change the party); not proved by a boot. */
#include "common.h"
#include "data/bss_0064.h"
#include "data/pieces/D_00425BC8.h"
#include "data/pieces/D_00425C28.h"
#include "data/pieces/D_00304BE8.h"
#include "data/pieces/D_003E3D68.h"
#include "data/pieces/D_003F3488.h"
#include "data/pieces/D_003F34C4.h"
#include "menu/page7.h"

extern s32 D_006436D0;
extern s32 D_006436D4;
extern s32 D_006436D8[2];
extern s32 D_006436E0[2];
extern s32 D_006436E8;
extern s32 D_006436EC;
extern s32 D_006436F8[2];
extern s32 D_00643700[2];
extern s32 D_00643720[4]; /* src/data/bss_0064.c: s32 D_00643720[0x4] */
extern s32 D_00643730;
extern s32 D_00643760[];
extern s32 D_003F34A8;
extern s32 D_003F34C0;
extern s32 D_003F6C90[];
extern s32 D_003F6CC8[];
extern s32 D_003F3468[];
extern void *D_003F6E18[];
extern s32 D_003F6E24;
extern s32 D_003F6E28;
extern s32 D_003F6E2C;
extern s32 D_003F6E30;
extern u8 D_003F6860[], D_003F68C0[], D_003F68F0[];
extern u8 D_003F6BD0[], D_003F6C00[], D_003F6C30[], D_003F6C60[];
extern u8 D_003F6CA0[], D_003F6CE0[], D_003F6D10[], D_003F6D40[];
extern u8 D_003F6D68[], D_003F6DA8[];

void func_00109278(void);
void *func_0010fd18(void);
void func_0011d768(s32);
s16 *func_0011ef10(s32, void *);
void func_001f3110(void);
void *func_001f31a8(void *, s32);
void *func_001f3520(void *, s32);
void func_001f3758(void *);
void func_001f37c0(void *, s32);
void func_001f3840(void *);
void func_001f3d58(void *, s32);
void func_001f3dc0(void *);
void func_001f3e48(void *, void *);
void func_001f4040(void *, s32);
void func_001f4058(void *, s32);
void func_001f40a0(void *, s32);
s32 func_001f42b8(void *);
void *func_001f4468(void *);
void func_001f9010(s32);
s32 func_001f9438(void *, s32, s32, s32, s32, s32, u32);
s32 func_001f9e48(void *, s32, s32, s32, void *, s32, s32);
void func_001fc308(void *, s32, s32, s32, s32, s32, s32, u32, u32);
s32 func_001fd518(void *);
void func_001fd858(void *);
s32 func_001fe5a0(void *);
void func_00205e30(void *, void *);
void func_00206130(void *, s32, s32, s32, s32, u32);
void func_002075f8(void);
void func_00207830(void *, s32, s32, s32, s32, s32, s32);
void func_0020a9b0(s32);
void func_0020ab88(s32);
void func_0020b120(s32, s32, u32, u32, u32, u32);
void func_0020b3d8(void *, s32, s32);
void func_0020bb90(s32, s32);
void func_0020bd18(void *, s32);
void func_0020bda8(s32);
void func_0020be10(s32);
void func_0020ca30(void *, s32, u32, u32);
void func_0020ccb0(void *);
s32 func_0020d030(void);
void func_0020d1d8(void *);
void func_0020d2f8(void);
void func_0020d530(void);
void func_00223a30(void *);
void func_00228700(void *);
void func_00233ef8(s32);

void func_00228760(PtWin *arg0) {
    s32 var_s0;

    var_s0 = D_003F6C90[D_00643720[D_006436D0]];
    if (var_s0 == 0x16A) {
        var_s0 = ((D_003F6E2C ^ 3) != 0) ? 0x16C : var_s0;
    }
    func_001f9010(0x17);
    func_001f9438(arg0, 0, 0xAE, 0xC, var_s0, 0x11, 0x8078C850);
}

void func_002287f8(PtWin *arg0) {
    PtWin *objs[3];
    s32 i, n, cur, k, c, y;

    if (func_001f42b8(arg0)) {
        if (D_00425BC8->x8 & 0x4000) {
            func_001f3840(arg0);
            func_0011d768(3);
            func_0020be10(16);
        } else {
            func_001fd858(arg0);
            func_0020bd18(arg0, 8);
            D_006436D0 = func_001fd518(arg0);
            if (func_001fe5a0(arg0)) {
                k = D_00643720[D_006436D0];
                switch (k) {
                case 0:
                    func_0011d768(2);
                    func_001f3d58(arg0, 5);
                    func_001f3758(arg0);
                    func_00109278();
                    D_003F34C0 |= 2;
                    func_00233ef8(0);
                    D_00643758 = 0;
                    D_0064373C = 0;
                    D_00425C28[0].x0 = 3;
                    D_00425C28[1].x0 = 3;

                    objs[0] = func_001f31a8(D_003F6C30, 6);
                    if (objs[0]) {
                        func_001f3e48(objs[0], arg0);
                        func_001f4040(objs[0], 4);
                        func_001f40a0(objs[0], 0x5A000000);
                        objs[1] = func_001f31a8(D_003F6C00, 6);
                        if (objs[1]) {
                            func_001f3e48(objs[1], objs[0]);
                            D_006436D4 = D_006436F0;
                            objs[1]->xd2 = *(u16 *)&D_006436D4 << 4;
                            objs[2] = func_001f31a8(D_003F6BD0, 6);
                            if (objs[2]) {
                                func_001f3e48(objs[2], objs[1]);
                                func_001f3dc0(objs[1]);
                            }
                        }
                    }
                    break;
                case 1:
                    if ((n = D_003E3D68 - 1) != 0) {
                        D_003F34C0 |= 2;
                        func_0011d768(2);
                        for (i = 0; i < 4; i++) {
                            D_00643760[i] = i;
                            D_00643770[i] = (((u8 *)D_00304BE8) + 0x48E)[i];
                            D_00643780[i] = 96;

                        }
                        D_0064375C = 0;
                        D_00643790 = 0;
                        D_00643794 = 0;
                        D_0064379C = 0;
                        for (i = 0; i < 4; i++) {
                            D_00643778[i] = (((u8 *)D_00304BE8) + 0x48E)[i];
                        }
                        func_001f3d58(arg0, 5);
                        func_001f3758(arg0);
                        objs[0] = func_001f31a8(D_003F68F0, 6);
                        if (objs[0]) {
                            func_001f3e48(objs[0], arg0);
                            n = D_003E3D68;
                            objs[0]->xcc = n;
                            objs[0]->xba = n * 448 - 32;
                            objs[0]->xce = n;
                            if (D_00643708 >= n) {
                                D_00643708 = 0;
                            }
                            objs[0]->xd2 = *(u16 *)&D_00643708 << 4;
                            objs[1] = func_001f31a8(D_003F68C0, 6);
                            if (objs[1]) {
                                func_001f3e48(objs[1], objs[0]);
                                func_001f3dc0(objs[0]);
                            }
                        }
                    } else {
                        func_0011d768(4);
                        func_001f3d58(arg0, 5);
                        func_001f3758(arg0);
                        objs[0] = func_001f31a8(D_003F6860, 6);
                        if (objs[0]) {
                            func_001f3e48(objs[0], arg0);
                            func_001f4058(objs[0], 1);
                            func_001f3d58(objs[0], 6);
                            func_00223a30(objs[0]);
                        }
                    }
                    break;
                case 2:
                    if (D_003F6E2C == 3) {
                        func_0011d768(6);
                        func_001f3d58(arg0, 5);
                        func_001f3758(arg0);
                        objs[0] = func_001f3520(D_003F6C60, 6);
                        if (objs[0]) {
                            func_001f3e48(objs[0], arg0);
                            func_001f4058(objs[0], 1);
                            func_001f3d58(objs[0], 6);
                            func_00228700(objs[0]);
                        }
                    } else {
                        func_0011d768(4);
                    }
                    break;
                case 3:
                    func_001f37c0(D_003F34C4->x10, 1);
                    func_001f3d58(D_003F34C4->x10->x10, 2);
                    func_001f3d58(D_003F34C4->x10->x10->x10, 2);
                    func_0020d1d8(func_001f4468(arg0));
                    func_0011d768(2);
                    func_002075f8();
                    break;
                }
            }
        }
    }
    cur = D_00643720[func_001fd518(arg0)];
    for (i = 0, y = 0; i < D_00643730; i++, y += 28) {
        k = D_00643720[i];
        c = cur == k;
        if (k == 2) {
            if (D_003F6E2C != 3) {
                c = cur == k ? 3 : 2;
            }
        } else if (k == 3) {
            c = cur == k ? 7 : 6;
        }
        func_00207830(arg0, c, 2, 0, y, 122, D_003F6CC8[k]);
    }
}

void func_00228e18(PtWin *arg0) {
    if (func_001f42b8(arg0) != 0) {
        func_001f3840(arg0);
        func_0020be10(0x10);
    }
    func_00207830(arg0, 4, 2, 0, 0, 0x7A, 0x165);
}

void func_00228e70(PtWin *arg0) {
    PtWin *objs[3];
    s32 i, n;
    if ((n = D_003E3D68 - 1) != 0) {
        D_003F34C0 |= 2;
        for (i = 0; i < 4; i++) {
            D_00643760[i] = i;
            D_00643770[i] = (((u8 *)D_00304BE8) + 0x48E)[i];
            if (i == D_00643708 + 1) D_00643780[i] = 96; else D_00643780[i] = 32;
        }
        D_0064375C = 0;
        D_00643790 = 0;
        D_00643794 = 0;
        D_0064379C = 0;
        for (i = 0; i < 4; i++) {
            D_00643778[i] = (((u8 *)D_00304BE8) + 0x48E)[i];
        }
        objs[0] = func_001f31a8(D_003F68F0, 6);
        if (objs[0]) {
            func_001f3e48(objs[0], arg0);
            n = D_003E3D68;
            objs[0]->xcc = n;
            objs[0]->xba = n * 448 - 32;
            objs[0]->xce = n;
            if (D_00643708 >= n) {
                D_00643708 = 0;
            }
            objs[0]->xd2 = *(u16 *)&D_00643708 << 4;
            objs[1] = func_001f31a8(D_003F68C0, 6);
            if (objs[1]) {
                func_001f3e48(objs[1], objs[0]);
                func_001f3dc0(objs[0]);
            }
        }
    } else {
        func_0011d768(4);
        objs[0] = func_001f31a8(D_003F6860, 6);
        if (objs[0]) {
            func_001f3e48(objs[0], arg0);
            func_001f4058(objs[0], 1);
            func_001f3d58(objs[0], 6);
            func_00223a30(objs[0]);
        }
    }
    D_00643718 = arg0;
}

void func_00229088(PtWin *a0) {
    PtWin *b[2];
    if (func_001f42b8(a0) != 0) {
        b[0] = func_001f31a8(D_003F6CE0, 6);
        if (b[0] != 0) {
            func_001f3e48(b[0], a0);
            b[0]->xcc = b[0]->xce = *(u16 *)&D_00643730;
            b[0]->xd2 = *(u16 *)&D_006436D0 * 16;
            b[1] = func_001f31a8(D_003F6CA0, 6);
            if (b[1] != 0) {
                func_001f3e48(b[1], b[0]);
                func_001f3dc0(b[0]);
            }
        }
    }
    func_00207830(a0, 4, 2, 0, 0, 122, 112);
}

void func_00229150(PtWin *a0) {
    func_00205e30(a0, D_003F6D68);
    func_00206130(a0, 0, 62, 512, 2, 0x8078C850);
    func_0020ca30(a0, 0, 0x80283212, 0x8050C846);
    func_001fc308(a0, 160, 35, 0, 19, 20, 0, 0x80399BFF, 0x80399BFF);
    func_001f9e48(a0, 0, 173, 35, func_0010fd18(), 19, 0x80399BFF);
    func_0020b3d8(a0, 401, 4);
}

void func_00229220(PtWin *arg0) {
    func_00205e30(arg0, D_003F6DA8);
    func_00206130(arg0, 0, 0, 0x200, 2, 0x8078C850);
    func_0020ccb0(arg0);
    func_001fc308(arg0, 0xA0, 0xC, 0, 0x3F, 0x14, 0, 0x4078C850, 0x4078C850);
}

void func_002292a8(PtWin *arg0) {
    s32 temp_s0;

    temp_s0 = arg0->x90;
    func_0020b120(2, temp_s0, 0x80080808, 0x80080808, 0x80080808, 0x80080808);
    func_0020b120(1, temp_s0, 0x80101010, 0x80101010, 0x80101010, 0x80101010);
    func_0020b120(2, temp_s0, 0x80080808, 0x80080808, 0x80080808, 0x80080808);
    func_0020a9b0(temp_s0);
    func_0020ab88(temp_s0);
}

PtWin *func_00229338(PtWin *a0) {
    PtWin *buf[3];
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

void func_002293f0(PtWin *arg0) {
    PtWin *h[2];
    h[0] = func_001f31a8(D_003F6CE0, 6);
    if (h[0] != 0) {
        func_001f3e48(h[0], arg0);
        h[0]->xcc = h[0]->xce = *(u16 *)&D_00643730;
        h[0]->xd2 = *(u16 *)&D_006436D0 * 16;
        h[1] = func_001f31a8(D_003F6CA0, 6);
        if (h[1] != 0) {
            func_001f3e48(h[1], h[0]);
            func_001f3dc0(h[0]);
        }
    }
    D_00643718 = arg0;
}

void func_00229490(PtWin *a0) {
    PtWin *buf[3];
    s32 i;
    for (i = 0; i < 3; i++) {
        buf[i] = func_001f31a8(D_003F6E18[i], D_003F3468[i]);
        if (buf[i] != 0) {
            func_001f3e48(buf[i], a0);
            func_001f3d58(buf[i], D_003F3488[i]);
            a0 = buf[i];
        }
    }
    buf[0] = func_001f31a8(D_003F6D40, 4);
    if (buf[0] != 0) {
        func_001f3e48(buf[0], a0);
        func_002293f0(buf[0]);
    }
    func_0020bb90(133, 0);
    func_0020bd18(buf[0], 8);
    func_0020bda8(16);
}

void func_002295a0(s32 arg0, s32 arg1) {
    s32 r;
    func_001f3110();
    D_003F34A8 = 1;
    func_0020d530();
    D_003F6E24 = 1;
    D_003F6E2C = arg1;
    if (arg1 != 1) {
        D_00643720[0] = 0;
        D_00643720[1] = 1;
        D_00643720[2] = 2;
        D_00643720[3] = 3;
        D_00643730 = 4;
    } else {
        D_00643730 = 3;
        D_00643720[1] = arg1;
        D_00643720[2] = 3;
        D_00643720[0] = 0;
    }
    func_0011d768(6);
    r = func_0020d030();
    D_003F34C4 = (N_3f34c4 *)r;
    if (r != 0) {
        func_00229490((PtWin *)r);
    }
    func_0011ef10(0x270FF, func_0020d2f8)[1] = arg0;
}

void func_00229690(PtWin *arg0) {
    PtWin *objs[3];
    s32 i;
    for (i = 0; i < 3; i++) {
        objs[i] = func_001f31a8(D_003F6E18[i], D_003F3468[i]);
        if (objs[i] != 0) {
            func_001f3e48(objs[i], arg0);
            func_001f3d58(objs[i], D_003F3488[i]);
            arg0 = objs[i];
        }
    }
    objs[0] = func_001f31a8(D_003F6D10, 4);
    if (objs[0] != 0) {
        func_001f3e48(objs[0], arg0);
        func_00228e70(objs[0]);
    }
    func_0020bb90(0x85, 0);
    func_0020bd18(objs[0], 8);
    func_0020bda8(0x10);
}

void func_002297a0(unsigned int arg0) {
  s32 temp_v0;
  s32 new_var;
  func_001f3110();
  D_003F34A8 = 2;
  func_0020d530();
  D_00643708 = 0;
  func_0011d768(6);
  new_var = func_0020d030();
  temp_v0 = new_var;
  D_003F34C4 = (N_3f34c4 *)temp_v0;
  if (temp_v0 != 0)
  {
    func_00229690((PtWin *)temp_v0);
  }
  func_0011ef10(0x270FF, func_0020d2f8)[1] = arg0;
}

void func_00229820(void) {
    D_00643798 = 0;
    D_003F6E30 = 0;
    D_003F6E28 = 0;
    D_006436D0 = 0;
    D_00643708 = 0;
}

void func_00229850(void) {
    D_006436D0 = 0;
    D_006436D4 = 0;
    D_006436D8[0] = 0;
    D_006436D8[1] = 0;
    D_006436E0[0] = 0;
    D_006436E0[1] = 0;
    D_006436E8 = 0;
    D_006436EC = 0;
    D_006436F0 = 0;
    D_006436F8[0] = 0;
    D_006436F8[1] = 0;
    D_00643700[0] = 0;
    D_00643700[1] = 0;
    D_00643708 = 0;
    D_0064370C = 0;
    D_003F6E24 = 0;
    D_003F6E28 = 0;
}

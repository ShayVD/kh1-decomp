/* Page 7 of the menu, part 2 (docs/modules.md "Session 42"),
 * 0x002245c8-0x00228760: the save and load windows.  func_002280c0 picks the
 * memory card port D_006436D4 (D_00425C28[port] the card state, func_00233f28
 * / func_00233f40 / func_00233fb0 / func_00233ff8 the card requests), then
 * opens the task window D_003F6B70 (savemenu.nostrict.c's func_00225ea8) with
 * the status line D_003F6920 (func_002245c8, message D_00643734 when not 0).
 * func_00225330 is the list of the 99 slots of D_00351E10 (magic 'KHSQ',
 * version 0x01317f14: name, place D_003F6B28[x38], play time, level),
 * D_006436E8 the chosen one; func_00228330 the free-space bar (D_00643750
 * free blocks, D_00643748 used).  Each message box (D_003F6950 ...
 * D_003F6AD0: func_00224610 ... func_002251b0, titles messages 0x176 ...
 * 0x18f) has a title setter (func_00224698 ...) like party.c's
 * func_00223a30; func_002259c8 ... func_00225dd8 close the task window and
 * open one.  func_00228588 is the "load the party" box (func_0013c778).
 * Not proved by a boot.  The card calls are the candidates for a platform
 * wrapper (docs/portability.md). */
#include "common.h"
#include "data/bss_0064.h"
#include "data/pieces/D_00425BC8.h"
#include "data/pieces/D_00425C28.h"
#include "data/pieces/D_00304BE8_s.h"
#include "data/pieces/D_003E8E08.h"
#include "data/types/text_00220000_c16.h"
#include "menu/page7.h"

typedef struct {
    u8 pad[0x18c0];
    s32 flags[100];
    Save3C saves[1];
} Sys1E10;

extern Sys1E10 D_00351E10;
extern PtWin *D_00643740; /* src/data/bss_0064.c: s32 D_00643740 */
extern s32 D_006436D4;
extern s32 D_006436D8[2];
extern s32 D_006436E0[2];
extern s32 D_006436E8;
extern s32 D_006436EC;
extern s32 D_00643734;
extern s32 D_00643738;
extern s32 D_0064373C;
extern s32 D_00643748;
extern s32 D_00643750;
extern s32 D_00643758;
extern s32 D_003F34C0;
extern s32 D_003F34C8;
extern s32 D_003F34D4;
extern s32 D_003F6B28[];
extern s32 D_003F6B98[];
extern s32 D_003F6BC8[];
extern s32 D_003F6E28;
extern u8 D_003F6920[], D_003F6950[], D_003F6980[], D_003F69B0[], D_003F69E0[];
extern u8 D_003F6A10[], D_003F6A40[], D_003F6A70[], D_003F6AA0[], D_003F6AD0[];
extern u8 D_003F6B70[], D_003F6BA0[], D_003F6BD0[], D_003F6BF8[];

void func_00109268(void);
void func_0011d768(s32);
void func_0013c778(s32, s32, s32);
s32 func_001ee428(s32);
s32 func_001ee440(s32);
s32 func_001efd98(s32);
void *func_001f31a8(void *, s32);
void *func_001f3520(void *, s32);
void func_001f36b8(void *);
void func_001f3758(void *);
void func_001f3840(void *);
void func_001f3d58(void *, s32);
void func_001f3dc0(void *);
void func_001f3e48(void *, void *);
void func_001f4058(void *, s32);
s32 func_001f42b8(void *);
s32 func_001f44a0(void *);
void func_001f8ba8(void *);
void func_001f8f30(void);
void func_001f9010(s32);
s32 func_001f9438(void *, s32, s32, s32, s32, s32, u32);
s32 func_001f9e48(void *, s32, s32, s32, void *, s32, s32);
void func_001fb428(void *, s32, s32, s32, s32, s32, s32, s32, u32);
s32 func_001fd518(void *);
s32 func_001fd538(void *);
s32 func_001fd548(void *);
s32 func_001fd590(void *);
s32 func_001fd618(void *);
void func_001fd858(void *);
void func_001fdfd0(void *);
s32 func_001fe570(void *);
s32 func_001fe5a0(void *);
void func_001ff488(void *, s32, s32, s32, s32, u32);
void func_00202fc0(void *);
void func_00206370(void *, s32, s32, s32, s32, u32, u32, u32, u32);
s32 func_00207bb0(void *, s32);
void func_00207c28(void *, s32);
void func_00209340(void *, s32, void *);
void func_0020bd18(void *, s32);
void func_0020bda8();   /* func_00227f90 passes three more registers */
void func_0020be10(s32);
void func_00233ef8(s32);
s32 func_00233f18(void);
void func_00233f28(s32, s32);
s32 func_00233f40(s32, s32);
void func_00233fb0(s32, s32);
void func_00233ff8(s32, s32);

void func_002245c8(PtWin *arg0) {
    func_001f9010(0x17);
    func_001f9438(arg0, 0, 0xAE, 0xC, 0x188, 0x11, 0x8078C850);
}

void func_00224610(PtWin *arg0) {
    if (func_001f42b8(arg0) != 0) {
        if (D_00425BC8->x8 & 0x4000) {
            func_001f3758(D_00643740);
            func_0011d768(3);
        } else {
            func_0020bd18(arg0, 8);
            if (func_001fe570(arg0) != 0) {
                func_001f3758(D_00643740);
            }
        }
    }
    func_00207bb0(arg0, 0x18F);
}

void func_00224698(PtWin *a) {
    s32 h;

    h = func_001efd98(0x18F) * 0x170;
    a->xb4 -= h;
    a->xba += h;
    a->xc0 += h;
}

void func_002246f8(PtWin *arg0) {
    PtWin *temp_v0;

    func_001f3758(D_00643740->x10);
    func_0011d768(3);
    D_0064373C = 0;
    D_00643758 = 0;
    D_00643738 = 0;
    func_00223980(D_006436D4, 0, 0);
    func_00233ef8(0);
    temp_v0 = func_001f31a8(D_003F6950, 6);
    if (temp_v0 != 0) {
        func_001f3e48(temp_v0, arg0);
        func_001f4058(temp_v0, 1);
        func_001f3d58(temp_v0, 6);
        func_00224698(temp_v0);
    }
}

void func_002247c8(PtWin *a0) {
    PtWin *o;
    if (func_001f42b8(a0)) {
        if (func_00233f40(D_006436D4, 0)) {
            func_00233ff8(D_006436D4, 0);
            func_002246f8(a0);
        } else if (D_00425BC8->x8 & 0x4000) {
            func_001f36b8(a0);
            func_0011d768(3);
        } else {
            func_001fdfd0(a0);
            func_0020bd18(a0, 8);
            if (func_001fe570(a0)) {
                switch (func_001fd538(a0)) {
                case 0:
                    func_001f3758(a0->xc->xc);
                    o = func_001f31a8(D_003F6920, 6);
                    if (o) {
                        func_001f3e48(o, a0);
                        func_001f3dc0(D_00643740);
                    }
                    func_0020be10(16);
                    D_00643734 = 71;
                    func_00233f18();
                    break;
                case 1:
                    func_001f36b8(a0);
                    break;
                }
            }
        }
    }
    func_00207c28(a0, 393);
}

void func_00224920(PtWin *a) {
    s32 h;

    h = func_001efd98(0x189) * 0x170;
    a->xb4 -= h;
    a->xba += h;
    a->xc0 += h;
}

void func_00224980(PtWin *a0) {
    PtWin *o;
    if (func_001f42b8(a0)) {
        if (func_00233f40(D_006436D4, 0)) {
            func_00233ff8(D_006436D4, 0);
            func_002246f8(a0);
        } else if (D_00425BC8->x8 & 0x4000) {
            func_001f36b8(a0);
            func_0011d768(3);
        } else {
            func_001fdfd0(a0);
            func_0020bd18(a0, 8);
            if (func_001fe570(a0)) {
                switch (func_001fd538(a0)) {
                case 0:
                    func_001f3758(a0->xc->xc);
                    o = func_001f31a8(D_003F6920, 6);
                    if (o) {
                        func_001f3e48(o, a0);
                        func_001f3dc0(D_00643740);
                    }
                    func_0020be10(16);
                    D_00643734 = 55;
                    func_00233f18();
                    break;
                case 1:
                    func_001f36b8(a0);
                    break;
                }
            }
        }
    }
    func_00207c28(a0, 394);
}

void func_00224ad8(PtWin *a) {
    s32 h;

    h = func_001efd98(0x18A) * 0x170;
    a->xb4 -= h;
    a->xba += h;
    a->xc0 += h;
}

s32 func_00224b38(PtWin *arg0) {
    PtWin *temp_v0;

    if (func_001f42b8(arg0) != 0) {
        if (func_00233f40(D_006436D4, 0) != 0) {
            func_00233fb0(D_006436D4, 0);
            func_0011d768(2);
            func_001f3758(arg0);
            func_0020be10(0x10);
            D_00643734 = 0;
            func_00233f18();
            temp_v0 = func_001f31a8(D_003F6920, 6);
            if (temp_v0 != 0) {
                func_001f3e48(temp_v0, arg0);
                func_001f3dc0(D_00643740);
            }
        } else if (D_00425BC8->x8 & 0x4000) {
            func_001f3758(D_00643740);
            func_0011d768(3);
        } else {
            func_0020bd18(arg0, 8);
            if (func_001fe570(arg0) != 0) {
                func_001f3758(D_00643740);
            }
        }
    }
    return func_00207bb0(arg0, 0x18B);
}

void func_00224c48(PtWin *a) {
    s32 h;

    h = func_001efd98(0x18B) * 0x170;
    a->xb4 -= h;
    a->xba += h;
    a->xc0 += h;
}

s32 func_00224ca8(PtWin *arg0) {
    if (func_001f42b8(arg0) != 0) {
        if (func_00233f40(D_006436D4, 0) != 0) {
            func_00233ff8(D_006436D4, 0);
            func_002246f8(arg0);
        } else if (D_00425BC8->x8 & 0x4000) {
            func_001f3758(D_00643740);
            func_0011d768(3);
        } else {
            func_0020bd18(arg0, 8);
            if (func_001fe570(arg0) != 0) {
                func_001f3758(D_00643740);
            }
        }
    }
    return func_00207bb0(arg0, 0x176);
}

void func_00224d68(PtWin *a) {
    s32 h;

    h = func_001efd98(0x176) * 0x170;
    a->xb4 -= h;
    a->xba += h;
    a->xc0 += h;
}

s32 func_00224dc8(PtWin *arg0) {
    if (func_001f42b8(arg0) != 0) {
        if (func_00233f40(D_006436D4, 0) != 0) {
            func_00233ff8(D_006436D4, 0);
            func_002246f8(arg0);
        } else if (D_00425BC8->x8 & 0x4000) {
            func_001f3758(D_00643740);
            func_0011d768(3);
        } else {
            func_0020bd18(arg0, 8);
            if (func_001fe570(arg0) != 0) {
                func_001f3758(D_00643740);
            }
        }
    }
    return func_00207bb0(arg0, 0x17E);
}

void func_00224e88(PtWin *a) {
    s32 h;

    h = func_001efd98(0x17E) * 0x170;
    a->xb4 -= h;
    a->xba += h;
    a->xc0 += h;
}

void func_00224ee8(PtWin *a0) {
    PtWin *o;
    if (func_001f42b8(a0)) {
        if (func_00233f40(D_006436D4, 0)) {
            func_00233ff8(D_006436D4, 0);
            func_002246f8(a0);
        } else if (D_00425BC8->x8 & 0x4000) {
            func_001f3758(D_00643740);
            func_0011d768(3);
        } else {
            func_001fdfd0(a0);
            func_0020bd18(a0, 8);
            if (func_001fe570(a0)) {
                switch (func_001fd538(a0)) {
                case 0:
                    func_001f36b8(a0);
                    func_0020be10(16);
                    D_00643734 = 6;
                    o = func_001f31a8(D_003F6920, 6);
                    if (o) {
                        func_001f3e48(o, a0);
                        func_001f3dc0(D_00643740);
                    }
                    break;
                case 1:
                    func_001f3758(D_00643740);
                    break;
                }
            }
        }
    }
    func_00207c28(a0, 396);
}

void func_00225030(PtWin *a) {
    s32 h;

    h = func_001efd98(0x18C) * 0x170;
    a->xb4 -= h;
    a->xba += h;
    a->xc0 += h;
}

s32 func_00225090(PtWin *arg0) {
    if (func_001f42b8(arg0) != 0) {
        if (func_00233f40(D_006436D4, 0) != 0) {
            func_00233ff8(D_006436D4, 0);
            func_002246f8(arg0);
        } else if (D_00425BC8->x8 & 0x4000) {
            func_001f3758(D_00643740);
            func_0011d768(3);
        } else {
            func_0020bd18(arg0, 8);
            if (func_001fe570(arg0) != 0) {
                func_001f3758(D_00643740);
            }
        }
    }
    return func_00207bb0(arg0, 0x18D);
}

void func_00225150(PtWin *a) {
    s32 h;

    h = func_001efd98(0x18D) * 0x170;
    a->xb4 -= h;
    a->xba += h;
    a->xc0 += h;
}

void func_002251b0(PtWin *a0) {
    if (func_001f42b8(a0) != 0) {
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
    ((S4_3e8e08 *)D_003E8E08)->b = 132;
    ((S4_3e8e08 *)D_003E8E08)->a = D_00643750;
    func_00207bb0(a0, 398);
}

void func_00225288(PtWin *a) {
    s32 h;

    h = func_001efd98(0x18E) * 0x170;
    a->xb4 -= h;
    a->xba += h;
    a->xc0 += h;
}

void func_002252e8(PtWin *arg0) {
    func_001f9010(0x17);
    func_001f9438(arg0, 0, 0xAE, 0xC, 0x187, 0x11, 0x8078C850);
}

void func_00225330(PtWin *arg0) {
    s32 sel, i, n, y;
    PtWin *o;
    Save3C *s;

    if (func_001f42b8(arg0) != 0) {
        if (func_00233f40(D_006436D4, 0) != 0) {
            func_00233ff8(D_006436D4, 0);
            func_001f3d58(arg0, 6);
            func_002246f8(arg0);
        } else if (D_00425BC8->x8 & 0x4000) {
            func_001f3d58(arg0, 6);
            func_001f3758(D_00643740);
            func_0011d768(3);
            D_0064373C = 0;
        } else {
            func_001fd858(arg0);
            func_0020bd18(arg0, 8);
            D_006436D8[D_006436D4] = func_001fd618(arg0);
            D_006436E0[D_006436D4] = func_001fd518(arg0);
            D_006436E8 = func_001fd548(arg0);
            if (func_001fe5a0(arg0) != 0) {
                if (D_00351E10.flags[D_006436E8] != 0) {
                    if (D_00351E10.saves[D_006436E8].magic != 0x5153484B || D_00351E10.saves[D_006436E8].ver != 0x01317F14) {
                        if (D_00643750 == 0) {
                            goto nosave;
                        }
                        func_0011d768(6);
                        o = func_001f3520(D_003F6980, 6);
                        if (o) {
                            func_001f3e48(o, arg0->x10);
                            func_001f4058(o, 1);
                            func_001f3d58(o, 6);
                            func_00224920(o);
                            o->xda = 16;
                        }
                    } else {
                        func_0011d768(6);
                        o = func_001f3520(D_003F69B0, 6);
                        if (o) {
                            func_001f3e48(o, arg0->x10);
                            func_001f4058(o, 1);
                            func_001f3d58(o, 6);
                            func_00224ad8(o);
                            o->xda = 16;
                        }
                    }
                } else if (D_00643750 == 0) {
                nosave:
                    func_0011d768(4);
                    o = func_001f31a8(D_003F6AD0, 6);
                    if (o) {
                        func_001f3e48(o, arg0->x10);
                        func_001f4058(o, 1);
                        func_001f3d58(o, 6);
                        func_00225288(o);
                    }
                } else {
                    func_0011d768(2);
                    func_001f3758(arg0);
                    func_0020be10(16);
                    D_00643734 = 26;
                    func_00233f18();
                    o = func_001f31a8(D_003F6920, 6);
                    if (o) {
                        func_001f3e48(o, arg0);
                        func_001f3dc0(D_00643740);
                    }
                }
            }
        }
    }
    func_00202fc0(arg0);
    sel = func_001fd518(arg0);
    n = func_001fd618(arg0);
    y = func_001fd590(arg0);
    func_001f8ba8(arg0);

    for (i = 0; i < 5 && n < 99; i++, n++, y += 56) {
        func_001ff488(arg0, 0, y, 330, 50, i == sel ? 0x5A040422 : 0x5A000000);
        if (D_0064373C != 0) {
            if (D_00351E10.flags[n] != 0) {
                s = &D_00351E10.saves[n];
                if (s->magic == 0x5153484B && s->ver == 0x01317F14) {
                    func_001fb428(arg0, 0, 2, 1, 10, y + 18, n + 1, 15, 0x80399BFF);
                    func_001f9e48(arg0, 0, 52, y + 5, s->name, 15, 0x80399BFF);
                    func_001f9438(arg0, 0, 261, y + 5, D_003F6B28[s->x38], 15, 0x80399BFF);
                    ((S4_3e8e08 *)D_003E8E08)->a = func_001ee428(s->x10);
                    ((S4_3e8e08 *)D_003E8E08)->b = func_001ee440(s->x10);
                    ((S4_3e8e08 *)D_003E8E08)->c = s->xC;
                    ((S4_3e8e08 *)D_003E8E08)->d = s->x8;
                    func_001f9438(arg0, 0, 52, y + 30, 390, 15, 0x80399BFF);
                } else {
                    func_001fb428(arg0, 0, 2, 1, 10, y + 18, n + 1, 15, 0x804040C0);
                    func_001f9438(arg0, 0, 52, y + 18, 386, 15, 0x804040C0);
                }
            } else if (D_00643750 == 0) {
                func_001fb428(arg0, 0, 2, 1, 10, y + 18, n + 1, 15, 0x802B803F);
                func_001f9438(arg0, 0, 52, y + 18, 388, 15, 0x802B803F);
            } else {
                func_001fb428(arg0, 0, 2, 1, 10, y + 18, n + 1, 15, 0x802B803F);
                func_001f9438(arg0, 0, 52, y + 18, 389, 15, 0x802B803F);
            }
        }
    }
    func_001f8f30();
}

void func_00225988(void) {
    D_003F34D4 += 1;
    D_00643734 += 1;
    D_003F34C8 -= 1;
}

void func_002259c8(PtWin *arg0) {
    PtWin *temp_v0;

    func_001f36b8(arg0->x10);
    func_0011d768(3);
    D_0064373C = 0;
    D_00643758 = 0;
    func_00223980(D_006436D4, 0, 0);
    func_00233ef8(0);
    temp_v0 = func_001f31a8(D_003F6950, 6);
    if (temp_v0 != 0) {
        func_001f3e48(temp_v0, arg0);
        func_001f4058(temp_v0, 1);
        func_001f3d58(temp_v0, 6);
        func_00224698(temp_v0);
        func_0020bda8(0x10);
    }
}

void func_00225a90(PtWin *arg0) {
    PtWin *temp_v0;

    func_001f36b8(arg0->x10);
    func_0011d768(4);
    D_00643734 = 0;
    D_0064373C = 0;
    D_00643758 = 0;
    func_00223980(D_006436D4, 0, 0);
    func_00233ef8(0);
    temp_v0 = func_001f31a8(D_003F69E0, 6);
    if (temp_v0 != 0) {
        func_001f3e48(temp_v0, arg0);
        func_001f4058(temp_v0, 1);
        func_001f3d58(temp_v0, 6);
        func_00224c48(temp_v0);
        func_0020bda8(0x10);
    }
}

void func_00225b60(PtWin *arg0) {
    PtWin *temp_v0;

    func_001f36b8(arg0->x10);
    func_0011d768(4);
    D_00643734 = 0;
    D_0064373C = 0;
    D_00643758 = 0;
    func_00223980(D_006436D4, 0, 0);
    func_00233ef8(0);
    temp_v0 = func_001f31a8(D_003F6A10, 6);
    if (temp_v0 != 0) {
        func_001f3e48(temp_v0, arg0);
        func_001f4058(temp_v0, 1);
        func_001f3d58(temp_v0, 6);
        func_00224d68(temp_v0);
        func_0020bda8(0x10);
    }
}

void func_00225c30(PtWin *arg0) {
    PtWin *temp_v0;

    func_001f36b8(arg0->x10);
    func_0011d768(6);
    D_00643734 = 0;
    D_0064373C = 0;
    D_00643758 = 0;
    func_00233ef8(0);
    func_00223980(D_006436D4, 0, 0);
    temp_v0 = func_001f3520(D_003F6A70, 6);
    if (temp_v0 != 0) {
        func_001f3e48(temp_v0, arg0);
        func_001f4058(temp_v0, 1);
        func_001f3d58(temp_v0, 6);
        func_00225030(temp_v0);
        temp_v0->xda = 0x10;
        func_0020bda8(0x10);
    }
}

void func_00225d08(PtWin *arg0) {
    PtWin *temp_v0;

    func_001f36b8(arg0->x10);
    func_0011d768(4);
    D_00643734 = 0;
    D_0064373C = 0;
    D_00643758 = 0;
    func_00223980(D_006436D4, 0, 0);
    func_00233ef8(0);
    temp_v0 = func_001f31a8(D_003F6AA0, 6);
    if (temp_v0 != 0) {
        func_001f3e48(temp_v0, arg0);
        func_001f4058(temp_v0, 1);
        func_001f3d58(temp_v0, 6);
        func_00225150(temp_v0);
        func_0020bda8(0x10);
    }
}

void func_00225dd8(PtWin *arg0) {
    PtWin *temp_v0;

    func_001f36b8(arg0->x10);
    func_0011d768(4);
    D_00643734 = 0;
    D_0064373C = 0;
    D_00643758 = 0;
    func_00223980(D_006436D4, 0, 0);
    func_00233ef8(0);
    temp_v0 = func_001f31a8(D_003F6A40, 6);
    if (temp_v0 != 0) {
        func_001f3e48(temp_v0, arg0);
        func_001f4058(temp_v0, 1);
        func_001f3d58(temp_v0, 6);
        func_00224e88(temp_v0);
        func_0020bda8(0x10);
    }
}

void func_00227ef8(PtWin *arg0) {
    if (func_001f42b8(arg0) != 0) {
        if (D_00425BC8->x8 & 0x4000) {
            func_001f36b8(arg0);
            func_0011d768(3);
        } else {
            func_0020bd18(arg0, 8);
            if (func_001fe570(arg0) != 0) {
                func_001f36b8(arg0);
            }
        }
    }
    func_00207bb0(arg0, D_003F6B98[D_006436D4]);
}

void func_00227f90(PtWin *a0) {
    PtWin *p;
    s32 v, c0, ba, b4;
    func_0011d768(4);
    p = func_001f31a8(D_003F6BA0, 6);
    if (p != 0) {
        func_001f3e48(p, a0);
        func_001f4058(p, 1);
        func_001f3d58(p, 6);
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

void func_00228078(PtWin *arg0) {
    func_001f9010(0x17);
    func_001f9438(arg0, 0, 0xAE, 0xC, 0x173, 0x11, 0x8078C850);
}

void func_002280c0(PtWin *a0) {
    PtWin *objs[2];
    if (func_001f42b8(a0)) {
        if (func_001f44a0(D_003F6A70)) goto end;
        if (D_00425BC8->x8 & 0x4000) {
            func_001f3758(a0->xc);
            func_0011d768(3);
        } else {
            if (a0->x10 == 0) {
                objs[0] = func_001f31a8(D_003F6BD0, 6);
                if (objs[0]) {
                    func_001f3e48(objs[0], a0);
                    func_001f3dc0(a0);
                }
            }
            func_001fd858(a0);
            func_0020bd18(a0, 8);
            D_006436D4 = func_001fd518(a0);
            func_00233f28(D_006436D4, 0);
            D_00425C28[D_006436D4 ^ 1].x0 = 3;
            if (func_001fe5a0(a0)) {
                if (D_00425C28[D_006436D4].x0 != 3) {
                    if (func_00233f40(D_006436D4, 0)) {
                        func_00233fb0(D_006436D4, 0);
                        func_00233ff8(D_006436D4, 0);
                        func_00223980(D_006436D4, 0, 0);
                        D_00643758 = 0;
                    }
                    if (D_006436EC != D_006436D4) D_00643758 = 0;
                    func_0011d768(2);
                    func_00233f18();
                    D_00643738 = 0;
                    D_00643734 = 0;
                    func_001f36b8(a0->x10);
                    objs[0] = func_001f31a8(D_003F6B70, 0);
                    if (objs[0]) {
                        func_001f3e48(objs[0], a0);
                        D_00643740 = objs[0];
                        objs[1] = func_001f31a8(D_003F6920, 6);
                        if (objs[1]) {
                            func_001f3e48(objs[1], objs[0]);
                            func_001f3dc0(objs[0]);
                        }
                    }
                } else {
                    func_00227f90(a0);
                }
            }
        }
    }
end:
    func_00209340(a0, 2, D_003F6BF8);
}

void func_002282f8(void) {
    func_00109268();
    D_003F34C0 &= ~2;
}

void func_00228330(PtWin *a0) {
    s32 a, b, c, w, x;
    if (D_0064373C == 0) return;
    a = D_00643750;
    b = D_00643748;
    c = 60 - a - b;
    func_001f9438(a0, 0, 20, 8, 366, 15, 0x802b803f);
    func_001fb428(a0, 1, 0, 0, 113, 30, a, 15, 0x8040be5d);
    func_001f9438(a0, 0, 20, 66, 367, 15, 0x801b7de1);
    func_001fb428(a0, 1, 0, 0, 113, 88, b, 15, 0x80399bff);
    func_001f9438(a0, 0, 20, 124, 368, 15, 0x80995d3f);
    w = (u32)(a * 33536) / 60;
    if (a) func_00206370(a0, 8, 9, 6, w >> 8, 0x802b803f, 0x802b803f, 0x802b803f, 0x802b803f);
    x = w + 2304;
    w = (u32)(b * 33536) / 60;
    if (b) func_00206370(a0, 8, x >> 8, 6, w >> 8, 0x80399bff, 0x80399bff, 0x80399bff, 0x80399bff);
    x += w;
    w = (u32)(c * 33536) / 60;
    if (c) func_00206370(a0, 8, x >> 8, 6, w >> 8, 0x80d98659, 0x80d98659, 0x80d98659, 0x80d98659);
}

void func_00228588(PtWin *a0) {
    u8 buf[4];
    s32 i, j, c;
    if (func_001f42b8(a0)) {
        if (D_00425BC8->x8 & 0x4000) {
            func_001f36b8(a0);
            func_0011d768(3);
        } else {
            func_001fdfd0(a0);
            func_0020bd18(a0, 8);
            if (func_001fe570(a0)) {
                switch (func_001fd538(a0)) {
                case 0:
                    func_001f3840(a0);
                    func_0020be10(16);
                    D_003F6E28 = 1;
                    j = 1;
                    for (i = 1; i < 4 && (c = D_00304BE8->x48e[i]) != 255; i++) {
                        if ((u32)(c - 1) < 2) buf[j++] = c;
                    }
                    for (; j < 4; j += 2) buf[j] = -1;
                    func_0013c778(buf[1], buf[2], buf[3]);
                    break;
                case 1:
                    func_001f36b8(a0);
                    break;
                }
            }
        }
    }
    func_00207c28(a0, 365);
}

void func_00228700(PtWin *a) {
    s32 h;

    h = func_001efd98(0x16D) * 0x170;
    a->xb4 -= h;
    a->xba += h;
    a->xc0 += h;
}

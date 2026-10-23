/* The load screen, part 1 (docs/modules.md "Session 43"), 0x002298e0-0x0022b248:
 * a second set of memory card windows like page 7's savemenu.c, on the frame
 * D_00646990 (loadframe.c's func_0022b410 opens it).  func_0022a698 is the
 * card task: it reads the directory of port D_006437C4 ("BISLPS-25198-??",
 * up to 99 entries in D_00643800, D_006450C0[slot] the entry of each slot),
 * the 60-byte head of each save into D_00645250 (magic 'KHSQ', version
 * 0x01317f14), then opens the slot list D_003F6F70 (func_00229ec0: five rows,
 * slot number, name, place D_003F6F58[x38], play time) on the newest save;
 * step 20 loads the chosen slot into D_003F8380 (0x16c00 bytes) and starts
 * it (func_00110448, func_00223980).  D_006437E0 is the status line's
 * message (func_002298e0 / func_00229e78, drawn by the task), D_006437DC the
 * step.  The message boxes D_003F6E40 / D_003F6E70 ... D_003F6F00 (titles
 * 0x1a7 ... 0x1a9, 0x19c) each have a title setter (func_002299b0 ...) and
 * an opener (func_0022a3a0 ...).  Most likely the title menu's "load";
 * not proved by a boot.  The card calls (func_00233d08 ... func_002348d0) are
 * the candidates for a platform wrapper (docs/portability.md). */
#include "common.h"
#include "data/bss_0064.h"
#include "data/bss_0064_typed.h"
#include "data/data_0042.h"
#include "data/pieces/D_00425BC8.h"
#include "data/pieces/D_00425C1C.h"
#include "data/pieces/D_00425CAC.h"
#include "data/pieces/D_003E8E08.h"
#include "data/pieces/D_003F6E40.h"
#include "data/types/text_00220000_c16.h"
#include "menu/page7.h"

extern s32 D_006437C0;
extern s32 D_006437C4;
extern s32 D_006437C8[];
extern s32 D_006437D0[];
extern s32 D_006437DC;
extern s32 D_006437E4;
extern s32 D_00646990;
extern u32 D_006469A0; /* src/data/bss_0064.c: s32 D_006469A0 */
extern s32 D_003F6E24;
extern s32 D_003F720C;
extern s32 D_003F6F58[];
extern u8 D_003F6E70[], D_003F6EA0[], D_003F6ED0[], D_003F6F00[];
extern u8 D_003F6F30[], D_003F6F70[], D_003F8380[];

s32 func_0011d768(s32);
void func_00110448(s32);
s32 func_001ee428(s32);
s32 func_001ee440(s32);
void func_001edaf0(s32);
s32 func_001efd98(s32);
void *func_001f31a8(void *, s32);
void func_001f36b8(void *);
void func_001f3758(void *);
void func_001f3840(void *);
void func_001f3d58(void *, s32);
void func_001f3dc0(void *);
void func_001f3e48(void *, void *);
void func_001f4058(void *, s32);
s32 func_001f42b8(void *);
void func_001f8ba8(void *);
void func_001f8f30(void);
void func_001f9010(s32);
s32 func_001f9438(void *, s32, s32, s32, s32, s32, u32);
s32 func_001f9e48(void *, s32, s32, s32, void *, s32, s32);
void func_001fb428(void *, s32, s32, s32, s32, s32, s32, s32, u32);
s32 func_001fd518(void *);
s32 func_001fd548(void *);
s32 func_001fd590(void *);
s32 func_001fd618(void *);
void func_001fd858(void *);
s32 func_001fe570(void *);
s32 func_001fe5a0(void *);
void func_001ff488(void *, s32, s32, s32, s32, u32);
void func_00202fc0(void *);
void func_002066b0(void *, s32, s32, s32, s32, s32);
s32 func_00207bb0(void *, s32);
void func_0020bd18(void *, s32);
void func_0020bda8(s32);
void func_0020be10(s32);
s32 func_00219380(void);
void *func_00232fc8(s32);
void *func_00233018(s32);
s32 func_00233d08(s32);
void func_00233ef8(s32);
s32 func_00233f18(void);
s32 func_00233f40(s32, s32);
void func_00233f68(s32, s32);
void func_00233fb0(s32, s32);
void func_00233ff8(s32, s32);
s32 func_00234018(s32, s32, s32);
s32 func_00234148(s32, s32, char *, void *, s32, s32);
s32 func_002345a0(s32, s32, void *, void *, s32, s32);
s32 func_00234860(void);
s32 func_002348d0(void);

s32 D_006469A8 ALIGNED(8);
s32 D_006469AC ALIGNED(4);
Dir40 D_00643800[0x63] ALIGNED(64);
s32 D_00646994 ALIGNED(4);
u32 D_0064699C ALIGNED(4);
s32 D_0064524C ALIGNED(4);

#define LdFrame ((PtWin *)D_00646990)

void func_002298e0(PtWin *arg0) {
    func_001f9010(0x17);
    func_001f9438(arg0, 0, 0xAE, 0xC, 0x1A6, 0x11, 0x80399BFF);
}

void func_00229928(PtWin *arg0) {
    if (func_001f42b8(arg0) != 0) {
        if (D_00425BC8->x8 & 0x4000) {
            func_001f3758(LdFrame);
            func_0011d768(3);
        } else {
            func_0020bd18(arg0, 8);
            if (func_001fe570(arg0) != 0) {
                func_001f3758(LdFrame);
            }
        }
    }
    func_00207bb0(arg0, 0x1A9);
}

void func_002299b0(PtWin *a) {
    s32 h;

    h = func_001efd98(0x1A9) * 0x170;
    a->xb4 -= h;
    a->xba += h;
    a->xc0 += h;
}

void func_00229a10(PtWin *arg0) {
    PtWin *temp_v0;

    func_001f3758(LdFrame->x10);
    func_0011d768(3);
    D_006437E4 = 0;
    D_006469A4 = 0;
    D_006437E0 = 0;
    func_00233ef8(0);
    temp_v0 = func_001f31a8(D_003F6E70, 6);
    if (temp_v0 != 0) {
        func_001f3e48(temp_v0, arg0);
        func_001f4058(temp_v0, 2);
        func_001f3d58(temp_v0, 6);
        func_002299b0(temp_v0);
    }
}

s32 func_00229ad0(PtWin *arg0) {
    PtWin *temp_v0;

    if (func_001f42b8(arg0) != 0) {
        if (func_00233f40(D_006437C4, 0) != 0) {
            func_00233fb0(D_006437C4, 0);
            func_001f3758(arg0);
            func_0011d768(2);
            func_0020be10(0x10);
            func_00233f18();
            temp_v0 = func_001f31a8(D_003F6E40, 6);
            if (temp_v0 != 0) {
                func_001f3e48(temp_v0, arg0);
                func_001f3dc0(LdFrame);
            }
        } else if (D_00425BC8->x8 & 0x4000) {
            func_001f3758(LdFrame);
            func_0011d768(3);
        } else {
            func_0020bd18(arg0, 8);
            if (func_001fe570(arg0) != 0) {
                func_001f3758(LdFrame);
            }
        }
    }
    return func_00207bb0(arg0, 0x1A7);
}

void func_00229bd8(PtWin *a) {
    s32 h;

    h = func_001efd98(0x1A7) * 0x170;
    a->xb4 -= h;
    a->xba += h;
    a->xc0 += h;
}

s32 func_00229c38(PtWin *arg0) {
    if (func_001f42b8(arg0) != 0) {
        if (func_00233f40(D_006437C4, 0) != 0) {
            func_00233ff8(D_006437C4, 0);
            func_00229a10(arg0);
        } else if (D_00425BC8->x8 & 0x4000) {
            func_001f3758(LdFrame);
            func_0011d768(3);
        } else {
            func_0020bd18(arg0, 8);
            if (func_001fe570(arg0) != 0) {
                func_001f3758(LdFrame);
            }
        }
    }
    return func_00207bb0(arg0, 0x19C);
}

void func_00229cf8(PtWin *a) {
    s32 h;

    h = func_001efd98(0x19C) * 0x170;
    a->xb4 -= h;
    a->xba += h;
    a->xc0 += h;
}

s32 func_00229d58(PtWin *arg0) {
    if (func_001f42b8(arg0) != 0) {
        if (func_00233f40(D_006437C4, 0) != 0) {
            func_00233ff8(D_006437C4, 0);
            func_00229a10(arg0);
        } else if (D_00425BC8->x8 & 0x4000) {
            func_001f3758(LdFrame);
            func_0011d768(3);
        } else {
            func_0020bd18(arg0, 8);
            if (func_001fe570(arg0) != 0) {
                func_001f3758(LdFrame);
            }
        }
    }
    return func_00207bb0(arg0, 0x1A8);
}

void func_00229e18(PtWin *a) {
    s32 h;

    h = func_001efd98(0x1A8) * 0x170;
    a->xb4 -= h;
    a->xba += h;
    a->xc0 += h;
}

void func_00229e78(PtWin *arg0) {
    func_001f9010(0x17);
    func_001f9438(arg0, 0, 0xAE, 0xC, 0x1A5, 0x11, 0x80399BFF);
}

void func_00229ec0(PtWin *arg0) {
    s32 sel, i, n, y;
    void *o;
    Save3C *s;

    if (func_001f42b8(arg0) != 0) {
        if (func_00233f40(D_006437C4, 0) != 0) {
            func_00233ff8(D_006437C4, 0);
            func_001f3d58(arg0, 6);
            func_00229a10(arg0);
        } else if (D_00425BC8->x8 & 0x4000) {
            func_001f3d58(arg0, 6);
            func_001f3758(LdFrame);
            func_0011d768(3);
            D_006437E4 = 0;
        } else {
            func_001fd858(arg0);
            func_0020bd18(arg0, 8);
            D_006437C8[D_006437C4] = func_001fd618(arg0);
            D_006437D0[D_006437C4] = func_001fd518(arg0);
            D_006437C0 = func_001fd548(arg0);
            if (func_001fe5a0(arg0) != 0) {
                if (D_006450C0[D_006437C0] != 0) {
                    if (D_00645250[D_006437C0].magic != 0x5153484B || D_00645250[D_006437C0].ver != 0x01317F14) {
                        func_0011d768(4);
                    } else {
                        func_0011d768(2);
                        func_001f3758(arg0);
                        func_0020be10(16);
                        D_006437DC = 20;
                        func_00233f18();
                        o = func_001f31a8(D_003F6E40, 6);
                        if (o != 0) {
                            func_001f3e48(o, arg0);
                            func_001f3dc0(LdFrame);
                        }
                    }
                } else {
                    func_0011d768(4);
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
        if (D_006437E4 != 0) {
            if (D_006450C0[n] != 0) {
                s = &D_00645250[n];
                if (s->magic == 0x5153484B && s->ver == 0x01317F14) {
                    func_001fb428(arg0, 0, 2, 1, 10, y + 18, n + 1, 15, 0x80399BFF);
                    func_001f9e48(arg0, 0, 52, y + 5, s->name, 15, 0x80399BFF);
                    func_001f9438(arg0, 0, 261, y + 5, D_003F6F58[s->x38], 15, 0x80399BFF);
                    (*(S4_3e8e08 *)&D_003E8E08).a = func_001ee428(s->x10);
                    (*(S4_3e8e08 *)&D_003E8E08).b = func_001ee440(s->x10);
                    (*(S4_3e8e08 *)&D_003E8E08).c = s->xC;
                    (*(S4_3e8e08 *)&D_003E8E08).d = s->x8;
                    func_001f9438(arg0, 0, 52, y + 30, 420, 15, 0x80399BFF);
                } else {
                    func_001fb428(arg0, 0, 2, 1, 10, y + 18, n + 1, 15, 0x804040C0);
                    func_001f9438(arg0, 0, 52, y + 18, 418, 15, 0x804040C0);
                }
            } else {
                func_001fb428(arg0, 0, 2, 1, 10, y + 18, n + 1, 15, 0x802B803F);
                func_001f9438(arg0, 0, 52, y + 18, 419, 15, 0x802B803F);
            }
        }
    }
    func_001f8f30();
}

void func_0022a3a0(PtWin *arg0) {
    PtWin *temp_v0;

    func_001f36b8(arg0->x10);
    func_0011d768(3);
    D_006437E4 = 0;
    D_006469A4 = 0;
    func_00233ef8(0);
    temp_v0 = func_001f31a8(D_003F6E70, 6);
    if (temp_v0 != 0) {
        func_001f3e48(temp_v0, arg0);
        func_001f4058(temp_v0, 2);
        func_001f3d58(temp_v0, 6);
        func_002299b0(temp_v0);
        func_0020bda8(0x10);
    }
}

void func_0022a458(PtWin *arg0) {
    PtWin *temp_v0;

    func_001f36b8(arg0->x10);
    func_0011d768(4);
    D_006437DC = 0;
    D_006437E4 = 0;
    D_006469A4 = 0;
    func_00233ef8(0);
    temp_v0 = func_001f31a8(D_003F6EA0, 6);
    if (temp_v0 != 0) {
        func_001f3e48(temp_v0, arg0);
        func_001f4058(temp_v0, 2);
        func_001f3d58(temp_v0, 6);
        func_00229bd8(temp_v0);
        func_0020bda8(0x10);
    }
}

void func_0022a518(PtWin *arg0) {
    PtWin *temp_v0;

    func_001f36b8(arg0->x10);
    func_0011d768(4);
    D_006437DC = 0;
    D_006437E4 = 0;
    D_006469A4 = 0;
    func_00233ef8(0);
    temp_v0 = func_001f31a8(D_003F6ED0, 6);
    if (temp_v0 != 0) {
        func_001f3e48(temp_v0, arg0);
        func_001f4058(temp_v0, 2);
        func_001f3d58(temp_v0, 6);
        func_00229cf8(temp_v0);
        func_0020bda8(0x10);
    }
}

void func_0022a5d8(PtWin *arg0) {
    PtWin *temp_v0;

    func_001f36b8(arg0->x10);
    func_0011d768(4);
    D_006437DC = 0;
    D_006437E4 = 0;
    D_006469A4 = 0;
    func_00233ef8(0);
    temp_v0 = func_001f31a8(D_003F6F00, 6);
    if (temp_v0 != 0) {
        func_001f3e48(temp_v0, arg0);
        func_001f4058(temp_v0, 2);
        func_001f3d58(temp_v0, 6);
        func_00229e18(temp_v0);
        func_0020bda8(0x10);
    }
}

/* The card task (see the top). */
void func_0022a698(PtWin *arg0) {
    PtWin *objs[2];
    s32 ok[99];
    s32 num, i, n, bi, y, w;
    u64 best, t;
    Dir40 *p;

    num = -1;
    if (func_001f42b8(arg0)) {
        switch (D_006437DC) {
        case 0:
            if (func_00233f40(D_006437C4, 0)) {
                func_00233ff8(D_006437C4, 0);
                D_006469A4 = 0;
            }
            D_006437E0 = 410;
            func_00234018(D_006437C4, 0, 0);
            D_006437E4 = 0;
            D_006437DC = 1;
            break;
        case 1:
            D_006437E0 = 410;
            if (func_00233d08(0)) break;
            D_006469A8 = D_00425C18;
            D_006469AC = D_00425C20;
            D_006437DC = 2;
            break;
        case 2:
            D_006437E0 = 410;
            func_00234018(D_006437C4, 0, 0);
            D_006437DC = 3;
            break;
        case 3:
            D_006437E0 = 410;
            if (func_00233d08(0)) break;
            if (func_00233f40(D_006437C4, 0)) {
                func_00233ff8(D_006437C4, 0);
                D_006437E0 = 415;
                func_0022a3a0(arg0);
                break;
            }
            if (D_006469A8 == 2 && D_00425C18 == 2 && D_006469AC == 0 && D_00425C20 == 0) {
                D_006437DC = 4;
                break;
            }
        tail3:
            if (D_006469A4) {
                D_006437DC = 18;
            } else {
                D_006437DC = 6;
            }
            break;
        case 4:
            D_006437E0 = 410;
            func_00234018(D_006437C4, 0, 0);
            D_006437DC = 5;
            break;
        case 5:
            D_006437E0 = 410;
            if (func_00233d08(0)) break;
            if (func_00233f40(D_006437C4, 0)) {
                func_00233ff8(D_006437C4, 0);
                D_006437E0 = 415;
                func_0022a3a0(arg0);
                break;
            }
            if (D_00425C20 != 0) {
                goto tail3;
            }
            D_006437E0 = 413;
            func_0022a5d8(arg0);
            break;
        case 6:
            D_006437E0 = 410;
            func_00234148(D_006437C4, 0, "BISLPS-25198-??", D_00643800, 99, 0);
            D_006437DC = 7;
            break;
        case 7:
            D_006437E0 = 410;
            if (func_00233d08(0)) break;
            if (func_00234860() == 4) {
                D_006437E0 = 415;
                D_006437DC = 8;
            } else {
                D_006437DC = 10;
            }
            break;
        case 8:
            D_006437E0 = 415;
            func_00234018(D_006437C4, 0, 0);
            D_006437DC = 9;
            break;
        case 9:
            D_006437E0 = 415;
            if (func_00233d08(0)) break;
            func_00233f68(D_006437C4, 0);
            func_00233ff8(D_006437C4, 0);
            func_0022a3a0(arg0);
            break;
        case 10:
            D_006437E0 = 410;
            for (n = 0; n < 99; n++) {
                D_006450C0[n] = 0;
            }
            n = D_00425CAC;
            p = D_00643800;
            D_00646994 = n;
            if (n > 0) {
                do {
                    D_006450C0[(((u8 *)p->name)[13] - '0') * 10 + (((u8 *)p->name)[14] - '0') - 1] = p;
                    p++;
                } while (--n);
            }
            D_006437DC = 11;
            break;
        case 11:
            D_006437E0 = 410;
            D_0064524C = 0;
            D_006437DC = 12;
            break;
        case 12:
            D_006437E0 = 411;
            while (D_006450C0[D_0064524C] == 0) {
                if (++D_0064524C >= 99) {
                    D_006437DC = 16;
                    D_006437E0 = 410;
                    goto end;
                }
            }
            num = D_0064524C + 1;
            D_00645250[D_0064524C].magic = 0;
            func_002345a0(D_006437C4, 0, func_00233018(num), &D_00645250[D_0064524C], 60, 0);
            D_006437DC = 13;
            break;
        case 13:
            num = D_0064524C + 1;
            D_006437E0 = 411;
            if (func_00233d08(0)) break;
            if (func_002348d0() == 7) {
                D_006437E0 = 415;
                num = -1;
                D_006437DC = 14;
            } else if (++D_0064524C >= 99) {
                D_006437DC = 16;
            } else {
                D_006437DC = 12;
            }
            break;
        case 14:
            D_006437E0 = 415;
            func_00234018(D_006437C4, 0, 0);
            D_006437DC = 15;
            break;
        case 15:
            D_006437E0 = 415;
            if (func_00233d08(0)) break;
            func_00233f68(D_006437C4, 0);
            func_00233ff8(D_006437C4, 0);
            func_0022a3a0(arg0);
            break;
        case 16:
            D_006437E0 = 410;
            func_00234018(D_006437C4, 0, 0);
            D_006437DC = 17;
            break;
        case 17:
            D_006437E0 = 410;
            if (func_00233d08(0)) break;
            if (func_00233f40(D_006437C4, 0)) {
                func_00233ff8(D_006437C4, 0);
                D_006437E0 = 415;
                func_0022a3a0(arg0);
                break;
            }
            D_006437DC = 18;
            break;
        case 18:
            D_006437E0 = 0;
            D_00646998 = 0;
            for (i = 0; i < 99; i++) {
                if (D_006450C0[i]) {
                    if (D_00645250[i].magic == 0x5153484B && D_00645250[i].ver == 0x01317F14) {
                        if ((u32)D_00645250[i].x38 >= 3) {
                            D_00645250[i].x38 = 2;
                        }
                        ok[i] = 1;
                        D_00646998++;
                    } else {
                        ok[i] = 0;
                    }
                }
            }
            D_0064699C = D_00425C1C;
            D_006469A0 = D_00425C1C / 132;
            D_006437E4 = 1;
            D_006469A4 = 1;
            D_006437D8 = D_006437C4;
            D_006437DC = 19;
            func_00233ef8(0);
            func_0011d768(55);
            func_001f36b8(arg0->x10);
            objs[0] = func_001f31a8(D_003F6F70, 6);
            if (!objs[0]) break;
            func_001f3e48(objs[0], arg0);
            func_0020bda8(16);
            bi = 0;
            best = 0;
            for (i = 0; i < 99; i++) {
                if (D_006450C0[i] && ok[i]) {
                    t = D_006450C0[i]->x8 & ~0xFFULL;
                    if (best < t) {
                        best = t;
                        bi = i;
                    }
                }
            }
            if (bi < 96) {
                D_006437C8[D_006437C4] = bi;
                D_006437D0[D_006437C4] = 0;
            } else {
                D_006437C8[D_006437C4] = 95;
                D_006437D0[D_006437C4] = bi - 95;
            }
            objs[0]->xd0 = D_006437C8[D_006437C4] << 4;
            objs[0]->xd2 = D_006437D0[D_006437C4] << 4;
            D_006437C0 = D_006437C8[D_006437C4] + D_006437D0[D_006437C4];
            objs[1] = func_001f31a8(D_003F6F30, 6);
            if (objs[1]) {
                func_001f3e48(objs[1], objs[0]);
                func_001f3dc0(objs[0]);
            }
            break;
        case 19:
            break;
        case 20:
            D_006437E0 = 414;
            func_002345a0(D_006437C4, 0, func_00232fc8(D_006437C0 + 1), D_003F8380, 0x16c00, 0);
            D_006437DC = 21;
            break;
        case 21:
            D_006437E0 = 414;
            if (func_00233d08(0)) break;
            if (func_002348d0()) {
                D_006437E0 = 412;
                if (func_002348d0() == 7) {
                    D_006437DC = 22;
                } else {
                    func_0022a518(arg0);
                }
            } else {
                func_0011d768(55);
                func_00110448(D_00645250[D_006437C0].x10);
                func_001f3840(arg0);
                func_0020be10(16);
                D_003F720C = 1;
                D_003F6E24 = 1;
                func_00223980(D_006437C4, D_006437C8[D_006437C4], D_006437D0[D_006437C4]);
                func_001edaf0(func_00219380() == 0);
            }
            break;
        case 22:
            D_006437E0 = 412;
            func_00234018(D_006437C4, 0, 0);
            D_006437DC = 23;
            break;
        case 23:
            D_006437E0 = 412;
            if (func_00233d08(0)) break;
            func_00233f68(D_006437C4, 0);
            func_00233ff8(D_006437C4, 0);
            func_0022a3a0(arg0);
            break;
        }
    }
end:
    if (D_006437E0) {
        if (num != -1) {
            (*(S4_3e8e08 *)&D_003E8E08).a = num;
        }
        y = D_006437C4 * 28 + 83;
        w = func_001f9438(arg0, 0, 200, y - 7, D_006437E0, 15, 0x80399bff);
        func_002066b0(arg0, 0, y, 11, 0x001428c8, 0x801428c8);
        func_002066b0(arg0, 133, y, 63, 0x801428c8, 0x801428c8);
        func_002066b0(arg0, w + 4, y, 512 - w, 0x801428c8, 0x001428c8);
    }
}

/* Page 7 of the menu, part 1 (docs/modules.md "Session 42"),
 * 0x00223980-0x002245c8: the party change.  func_00224060 is its list
 * (window D_003F68F0, from func_00228e70): Sora (D_00643770[0]) and the
 * members D_00643770[1..] (names func_001ee5f0), the cursor D_00643708;
 * choosing a member opens func_00223a90's list of the others to swap with
 * (D_003F6890, the cursor D_0064370C), or func_002239b0's message box
 * (D_003F6860) when there is no one; leaving with a changed party calls
 * func_0013c778(D_00643770[1], [2], [3]) and waits for func_0024f098's load
 * (func_00224030).  D_00643780 are the models' colours (partymdl.c's
 * func_0020a518 draws them, D_00643760 their slots); func_00223ea8 steps
 * D_00643794 through loading the fourth model (func_00223e10 loads the
 * file D_003F3500 into the model data, journal.c's func_0021d348 calls it
 * too).  func_00223980 sets the step of D_006436F0 for the save windows
 * (part 2).  Window titles: func_00207bb0 / func_001efd98 on message 0x190.
 * Not proved by a boot. */
#include "common.h"
#include "platform/pad.h"
#include "data/bss_0064.h"
#include "data/bss_0064_mixed.h"
#include "data/pieces/D_00425BC8.h"
#include "data/pieces/D_00304BE8_s.h"
#include "data/pieces/D_003E3D68.h"
#include "menu/partymdl.h"
#include "menu/page7.h"

extern s32 D_003F34A8;
extern s32 D_003F34C0;
extern s32 D_003F34C8;
extern s32 D_003F34FC;
extern s32 D_003F3500;
extern s32 D_003F3504;
extern u8 D_003F37A0[];
extern PartyMdl D_003F3530[4];
extern s32 D_003F6E30;
extern u8 D_003F6860[], D_003F6890[];

void func_0011d768(s32);
s32 func_00132ec8(s32, s32);
void func_0013c778(s32, s32, s32);
s32 func_001ee5f0(s32);
s32 func_001efd98(s32);
void *func_001f31a8(void *, s32);
void func_001f36b8(void *);
void func_001f3758(void *);
void func_001f37c0(void *, s32);
void func_001f3840(void *);
void func_001f3d58(void *, s32);
void func_001f3e48(void *, void *);
void func_001f4058(void *, s32);
s32 func_001f42b8(void *);
void *func_001f4468(void *);
void func_001f9010(s32);
s32 func_001f9438(void *, s32, s32, s32, s32, s32, u32);
s32 func_001fd518(void *);
void func_001fd858(void *);
s32 func_001fe570(void *);
s32 func_001fe5a0(void *);
void func_00206690(void *, s32, s32, s32);
void func_00207830(void *, s32, s32, s32, s32, s32, s32);
void func_00207870(void *, s32, s32, s32, s32, s32, s32);
s32 func_00207bb0(void *, s32);
void func_0020a518(void *, s32, void *, void *);
void func_0020bd18(void *, s32);
void func_0020be10(s32);
void func_0024f098(void *, void (*)(void));
void func_0024f210(void *, void (*)(void));
void func_00223de0(void);
void func_00223e68(void);
void func_00224030(void);

void func_00223980(s32 k, s32 a, s32 b) {
    D_006436F0 = k;
    D_006436F8[k] = a;
    D_00643700[k] = b;
}

s32 func_002239b0(PtWin *arg0) {
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
    return func_00207bb0(arg0, 0x190);
}

void func_00223a30(PtWin *a) {
    s32 h;

    h = func_001efd98(0x190) * 0x170;
    a->xb4 -= h;
    a->xba += h;
    a->xc0 += h;
}

void func_00223a90(PtWin *a) {
    s32 buf[4];
    s32 i, j, n, sel, y, v, t;
    n = 0;
    for (i = 1; i < D_003E3D68; i++) {
        if (i != D_00643708 + 1) buf[n++] = D_00643770[i];
        else j = i;
    }
    if (func_001f42b8(a)) {
        if (D_00425BC8->x8 & PAD_CROSS) {
            func_001f3758(a);
            func_0011d768(3);
        } else {
            func_001fd858(a);
            func_0020bd18(a, 8);
            D_0064370C = func_001fd518(a);
            for (i = 0; i < D_003E3D68; i++) {
                if (D_00643770[i] == buf[D_0064370C]) D_00643780[i] = 140;
                else if (D_00643770[i] == D_00643770[D_00643708 + 1]) D_00643780[i] = 96; else D_00643780[i] = 48;
            }
            if (func_001fe570(a)) {
                for (i = 0; i < D_003E3D68; i++)
                    if (i == D_00643760[D_00643708 + 1]) D_00643780[i] = 96; else D_00643780[i] = 32;
                sel = buf[D_0064370C];
                for (i = 1; i < D_003E3D68; i++) {
                    if (D_00643770[i] == sel) {
                        t = D_00643770[j];
                        buf[D_0064370C] = t;
                        D_00643770[i] = t;
                        D_00643770[j] = sel;
                        sel = D_00643760[i];
                        D_00643760[i] = D_00643760[j];
                        D_00643760[j] = sel;
                        break;
                    }
                }
                func_001f3d58(a, 5);
                func_001f3758(a);
            }
        }
    }
    sel = func_001fd518(a);
    for (i = 0, y = 0; i < n; i++, y += 28)
        func_00207870(a, i == sel, 1, 0, y, 122, func_001ee5f0(buf[i]));
}

void func_00223d98(PtWin *arg0) {
    func_001f9010(0x17);
    func_001f9438(arg0, 0, 0xAE, 0xC, 0x191, 0x11, 0x8078C850);
}

void func_00223de0(void) {
    D_003F34FC += 1;
    D_003F34C8 -= 1;
}

void func_00223e10(void) {
    if (D_003F34FC == 0) {
        D_003F34FC = 1;
        D_003F34C8 += 1;
        func_00132ec8(D_003F3500, (s32)func_00223de0);
    }
}

void func_00223e68(void) {
    D_00643798 += 1;
    D_00643794 += 1;
    D_003F34C8 -= 1;
}

void func_00223ea8(void) {
    switch (D_00643794) {
    case 0:
        if (D_00304BE8->x48e[3] != 255) {
            switch (D_003F34FC) {
            case 0:
                func_00223e10();
            case 1:
                D_00643794++;
                break;
            default:
                D_00643794 = 2;
                break;
            }
        } else {
            D_00643794 = 5;
            D_00643790 = 1;
        }
        break;
    case 1:
        if (D_003F34FC == 2) D_00643794 = 2;
        break;
    case 2:
        D_00643798 = 1;
        D_00643794++;
        D_003F34C8++;
        D_003F3504 = 0;
        func_0024f210(D_003F37A0, func_00223e68);
        return;
    case 3:
        break;
    case 5:
        break;
    case 4:
        if (D_003F3530[3].active == 0) {
            func_0020a248(3);
            D_003F3530[3].active = 1;
        }
        D_00643790 = 1;
        D_0064379C = 1;
        D_00643794++;
        break;
    }
}

void func_00224030(void) {
    D_0064375C++;
    D_003F34C8--;
}

void func_00224060(PtWin *o) {
    s32 n1 = o->xce - 1;
    s32 i, k, y, sel, m, s;
    u32 cnt;
    PtWin *p, *r;
    if (func_001f42b8(o)) {
        switch (D_0064375C) {
        case 0:
            if (D_00425BC8->x8 & PAD_CROSS) {
                if (D_003F34A8 != 2 && D_00643770[1] == D_00643778[1] && D_00643770[2] == D_00643778[2] && D_00643770[3] == D_00643778[3]) {
                    func_001f37c0(o, 5);
                    func_0011d768(3);
                } else {
                    D_00643708 = o->xce - 1;
                    o->xd2 = *(u16 *)&D_00643708 << 4;
                    func_0011d768(3);
                }
                break;
            }
            func_001fd858(o);
            func_0020bd18(o, 8);
            D_00643708 = func_001fd518(o);
            for (i = 0; i < D_003E3D68; i++) {
                if (D_00643708 == D_003E3D68 - 1) {
                    if (i != 3) D_00643780[i] = 96;
                    else D_00643780[i] = 32;
                } else {
                    D_00643780[i] = (i == D_00643708 + 1) ? 96 : 32;
                }
            }
            if (!func_001fe5a0(o)) break;
            if (D_00643794 == 5) {
            if (D_00643708 < n1) {
                if (n1 >= 2) {
                func_0011d768(2);
                r = func_001f4468(o);
                p = func_001f31a8(D_003F6890, 6);
                if (!p) break;
                i = n1 - 1;
                func_001f3e48(p, r);
                p->xb4 += D_00643708 * 448;
                p->xba = i * 448 - 32;
                p->xcc = i;
                p->xce = i;
                if (D_0064370C >= n1) D_0064370C = 0;
                p->xd2 = *(u16 *)&D_0064370C << 4;
                break;
                }
                func_0011d768(4);
                p = func_001f31a8(D_003F6860, 6);
                if (!p) break;
                func_001f3e48(p, o);
                func_001f4058(p, 1);
                func_001f3d58(p, 6);
                func_00223a30(p);
                break;
            }
            func_0011d768(2);
            if (D_00643770[1] == D_00643778[1] && D_00643770[2] == D_00643778[2] && D_00643770[3] == D_00643778[3]) {
                func_001f37c0(o, 5);
            } else {
                D_003F6E30 = 1;
                func_0020a1d8();
                func_0013c778(D_00643770[1], D_00643770[2], D_00643770[3]);
                D_003F34C8++;
                D_0064375C++;
                func_0024f098(D_00643778, func_00224030);
            }
            } else {
                func_0011d768(4);
            }
            break;
        case 1:
            break;
        case 2:
            func_001f3d58(o, 5);
            func_001f3840(o);
            func_0020be10(16);
            break;
        }
    }
    func_00206690(o, -75, -16, 75);
    func_00207870(o, 11, 2, 0, -28, 122, func_001ee5f0(D_00643770[0]));
    func_00206690(o, 122, -16, 623);
    sel = func_001fd518(o);
    y = 0;
    for (i = 0; i < n1; i = k) {
        k = i + 1;
        func_00207870(o, i == sel, 0, 0, y, 122, func_001ee5f0(D_00643770[k]));
        y += 28;
    }
    func_00207830(o, i == sel, 2, 0, y, 122, 55);
    if (D_0064375C == 0) {
        func_00223ea8();
        if (D_00643790) do { func_0020a518(o, 0, D_00643760, D_00643780); } while (0);
    }
}

void func_002245a8(void) {
    D_003F34C0 &= ~2;
}

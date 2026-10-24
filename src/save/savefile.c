/* The save files (docs/modules.md "Session 44"), 0x00232de0-0x002335d8.
 * A save is the directory "BISLPS-25198-NN" (NN = 01-99) of a memory card
 * holding NN's data (the save image D_003F8380, 0x16c00 bytes,
 * src/game/saveimage.c), system.bin (the 0x3c-byte head D_00425B80 the
 * load screen lists: the magic 0x5153484B "KHSQ" / 0x01317F14, the leader's
 * level, the munny, the play time, the name, a word of func_002193f0),
 * icon.sys, mc_icon.bin, mc_copy.bin and mc_del.bin.  func_00232f88 ...
 * func_00233118 write NN into those names and return them; func_00232de0
 * sets the magic, func_00232e08(NN) the rest of the head and the icon's
 * title D_003F7ED0 (the name and NN in Shift-JIS digits).  func_00233168 is
 * a card check task over both ports (D_00351E10, func_00233158 resets it):
 * card type 2, formatted, free space for a save (132 clusters), the
 * directory "BISLPS-25198-??" and each save's system.bin; D_003F8370[port]
 * gets 0 (a save with the magic), 1 (none, room for one), 2 (no room), 3
 * (not formatted) or 4 (no card / an error).  The requests are the card
 * module's (func_00234018 ..., src/hand/ for now).  Not proved by a boot. */
#include "common.h"
#include "data/pieces/D_00304BE8_s.h"
#include "data/pieces/D_00425B80.h"
#include "data/pieces/D_003F7ED0.h"
#include "data/pieces/D_002BBDF4.h"
#include "data/pieces/D_003F82A8.h"
#include "data/pieces/D_00425C1C.h"
#include "data/types/text_00230000_s8_w7.h"

extern char D_003F8298[];
extern char D_003F82D0[];
extern char D_003F82F0[];
extern char D_003F8310[];
extern char D_003F8330[];
extern char D_003F8350[];
extern St D_00351E10;
extern s32 D_003F8370[];
extern s32 D_00425C18;
extern s32 D_00425C20;
extern s32 D_00425CAC;

u8 *func_0010fd18(void);
u32 func_001ef7a0(void);
s32 func_002193f0(void);
s32 func_00233d08(s32);
s32 func_00234018(s32, s32, s32);
s32 func_00234148(s32, s32, s32, s32, s32, s32);
s32 func_002345a0(s32, s32, s32, s32, s32, s32);
s32 func_00234840(void);
s32 func_00234860(void);
s32 func_002348d0(void);
void func_002365e0(void);

/* func_00233168's ways out: the port's answer, then step 11. */
#define FAIL(K) D_003F8370[D_00351E10.x4] = K; D_00351E10.x0 = 11; goto end

void func_00232de0(void) {
    D_00425B80.x0 = 0x5153484B;
    D_00425B80.x4 = 0x01317F14;
}

void func_00232e08(u32 a) {
    u8 *s;
    s32 i, q;
    u8 c;
    D_00425B80.x8 = D_00304BE8->m[D_00304BE8->x48e[0]].sub.lv;
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

char *func_00232f88(u32 arg0) {
    D_003F8298[13] = (s8) ((arg0 / 10U) + 0x30);
    D_003F8298[14] = (s8) ((arg0 % 10U) + 0x30);
    return D_003F8298;
}

Str82A8 *func_00232fc8(u32 arg0) {
    D_003F82A8.e = arg0 / 10 + '0';
    D_003F82A8.f = arg0 % 10 + '0';
    D_003F82A8.e2 = arg0 / 10 + '0';
    D_003F82A8.f2 = arg0 % 10 + '0';
    return &D_003F82A8;
}

char *func_00233018(u32 arg0) {
    D_003F82D0[14] = (s8) ((arg0 / 10U) + 0x30);
    D_003F82D0[15] = (s8) ((arg0 % 10U) + 0x30);
    return D_003F82D0;
}

char *func_00233058(u32 arg0) {
    D_003F82F0[14] = (s8) ((arg0 / 10U) + 0x30);
    D_003F82F0[15] = (s8) ((arg0 % 10U) + 0x30);
    return D_003F82F0;
}

char *func_00233098(u32 arg0) {
    D_003F8310[14] = (s8) ((arg0 / 10U) + 0x30);
    D_003F8310[15] = (s8) ((arg0 % 10U) + 0x30);
    return D_003F8310;
}

char *func_002330d8(u32 arg0) {
    D_003F8330[14] = (s8) ((arg0 / 10U) + 0x30);
    D_003F8330[15] = (s8) ((arg0 % 10U) + 0x30);
    return D_003F8330;
}

char *func_00233118(u32 arg0) {
    D_003F8350[14] = (s8) ((arg0 / 10U) + 0x30);
    D_003F8350[15] = (s8) ((arg0 % 10U) + 0x30);
    return D_003F8350;
}

void func_00233158(void) {
    D_00351E10.x0 = 0;
}

/* Matched in session 8 (w7); case 7 is a goto loop (k = q->n; goto t7; i7:
 * k = q->n + 1; q->n = k; ...; t7: if (!q->flag[k]) goto i7;). */
s32 func_00233168(void) {
    s32 i, r, k;
    R64 *p;
    St *q;
    func_002365e0();
    switch (D_00351E10.x0) {
    case 0:
        D_00351E10.x0 = 1;
        D_00351E10.x4 = 0;
        break;
    case 1:
        func_00234018(D_00351E10.x4, 0, 0);
        D_00351E10.x0 = 2;
        break;
    case 2:
        if (func_00233d08(0)) return 0;
        if (D_00425C18 != 2) {
            FAIL(4);
        }
        if (!D_00425C20) {
            FAIL(3);
        }
        D_00351E10.x0 = 3;
        break;
    case 3:
        func_00234148(D_00351E10.x4, 0, (s32)"BISLPS-25198-??", (s32)D_00351E10.rec, 99, 0);
        D_00351E10.x0 = 4;
        break;
    case 4:
        if (func_00233d08(0)) return 0;
        r = func_00234860();
        if (r == 4) {
            FAIL(r);
        }
        if (D_00425CAC == 0 && D_00425C1C < 132) {
            FAIL(2);
        }
        D_00351E10.x0 = 5;
        break;
    case 5:
        for (i = 0; i < 99; i++) D_00351E10.flag[i] = 0;
        p = D_00351E10.rec;
        for (i = 0; i < D_00425CAC; i++, p++) {
            D_00351E10.tbl[p->x2d][p->x2e - 1] = p;
        }
        D_00351E10.x0 = 6;
        break;
    case 6:
        D_00351E10.x0 = 7;
        D_00351E10.n = 0;
        break;
    case 7:
        q = &D_00351E10;
        k = q->n;
        goto t7;
    i7:
        k = q->n + 1;
        q->n = k;
        if (k >= 99) goto done;
    t7:
        if (!q->flag[k]) goto i7;
        D_00351E10.r[D_00351E10.n].x0 = 0;
        r = (s32)func_00233018(D_00351E10.n + 1);
        func_002345a0(D_00351E10.x4, 0, r, (s32)&D_00351E10.r[D_00351E10.n], 60, 0);
        D_00351E10.x0 = 8;
        break;
    case 8:
        if (func_00233d08(0)) return 0;
        if (func_002348d0() == 7) {
            FAIL(4);
        }
        q = &D_00351E10;
        if (++q->n >= 99) goto done;
        q->x0 = 7;
        break;
    case 9:
        func_00234018(D_00351E10.x4, 0, 0);
        D_00351E10.x0 = 10;
        break;
    case 10:
        if (func_00233d08(0)) return 0;
        if (func_00234840() == 1) {
            FAIL(4);
        }
        for (i = 0; i < 99; i++) {
            if (D_00351E10.flag[i] && D_00351E10.r[i].x0 == 0x5153484B && D_00351E10.r[i].x4 == 0x01317F14) {
                goto found;
            }
        }
        if (D_00425C1C < 132) D_003F8370[D_00351E10.x4] = 2;
        else D_003F8370[D_00351E10.x4] = 1;
        D_00351E10.x0 = 11;
        break;
    case 11:
        if (D_00351E10.x4 == 0) {
            D_00351E10.x4 = 1;
            D_00351E10.x0 = 1;
            break;
        }
        D_00351E10.x0 = 0;
        return 1;
    found:
        FAIL(0);
    done:
        q->x0 = 9;
    }
end:
    return 0;
}

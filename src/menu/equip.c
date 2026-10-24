/* The equipment page of the menu (docs/modules.md "Session 40"),
 * 0x002113f0-0x00213d80: page 1 of the top menu (message 0x6a; its open
 * function is func_00213c90, set up func_00213d00, reset func_00213d30).
 * Its windows are opened from the descriptors D_003F3B10 ... D_003F3DB0.
 * The member list (func_00213258, equip.nostrict.c) picks a member
 * (D_00641BC4 the cursor, D_00641BA8 the party slot, D_00641BAC the member,
 * D_00641BB0 its Sub_304be8); its slot list (func_00212cc0) shows the weapon
 * (row 0) and the D_00641BB0->x18 accessory slots.  func_00211da0 collects the
 * weapons of the member's kind (func_001ef270) into D_00641C10 / D_00642010
 * (D_00642410 of them), func_002127e0 the accessories (func_001ef370) into
 * D_00642418 / D_00642818 (D_00642C18); func_00211ed0 / func_00212930 are
 * their lists, func_002119a8 / func_002123b8 compare the stats before and
 * after.  D_00641BE0 / D_00641BF0 are the weapon each slot shows and the one
 * chosen: func_00211840 swaps the party model's weapon (func_00149f10 loads
 * it, func_00211718 is its callback).  D_00641BA4 is the page state.
 * Most likely the equipment page (weapons and accessories); not proved by a boot.
 *
 * Window views: TextWin (include/text/textwin.h) where the types agree; the
 * others stay file-local views of a TextWin with the field types their
 * functions need (an f32 at +0x24 / +0x28, a u8 at +0x24, plain s16 / u16 at
 * +0xd0 / +0xd2: TextWin's +0xd0 is a union, and a union access reorders). */
#include "common.h"
#include "platform/pad.h"
#include "text/textwin.h"
#include "data/bss_0064.h"
#include "data/pieces/D_00304BE8_s.h"
#include "data/pieces/D_003E3D68.h"
#include "data/pieces/D_00425BC8.h"
#include "data/pieces/D_003E8E08.h"
#include "data/pieces/D_003F34C8.h"
#include "data/pieces/D_002BBDFC.h"
#include "data/pieces/D_003E3D70.h"
#include "data/pieces/D_003E3E50.h"

typedef struct { u8 pad[0x24]; f32 x24; } WinF24;
typedef struct WinF28 { u8 pad[0x10]; struct WinF28 *x10; u8 p14[0x10]; s32 x24; f32 x28; } WinF28;
typedef struct { u8 pad[0x24]; u8 x24; } WinB24;
typedef struct {
    u8 pad0[0x10]; void *x10; u8 pad14[0x14]; s32 x28; s32 x2c;
    u8 pad30[0xcc - 0x30]; s16 xcc; s16 xce; u16 xd0; u16 xd2;
} WinU16;
typedef struct {
    u8 pad0[0x28];
    s32 x28, x2c;
    u8 pad30[0xba - 0x30];
    s16 xba;
    u8 padbc[0xcc - 0xbc];
    s16 xcc, xce, xd0, xd2;
} WinS16;
/* D_00304BE8 seen from +0: m[n].sub at e[n].x4 (func_00212cc0). */
typedef struct { u8 pad[4]; u8 x4; u8 pad5[0x17]; u8 x1c[0x58]; } Mem74;
typedef struct { Mem74 e[10]; u8 pad[0x48e - 0x488]; u8 x48e[11]; } Save74;
typedef struct { u8 pad[0x38]; s8 x38; } It14;

extern u8 D_003F3B10[], D_003F3B40[], D_003F3B70[], D_003F3BA0[], D_003F3BD0[], D_003F3C00[];
extern u8 D_003F3C30[], D_003F3C60[], D_003F3C90[], D_003F3CC0[], D_003F3CF0[], D_003F3D20[];
extern u8 D_003F3D50[], D_003F3D80[];
extern s32 D_003F34C0;
extern void *D_00641BA0;
extern s32 D_00641BAC;
extern Sub_304be8 *D_00641BB0;
extern s32 D_00641BB4, D_00641BB8, D_00641BBC, D_00641BC0, D_00641BC4;
extern s32 D_00641BC8, D_00641BCC, D_00641BD0, D_00641BD4, D_00641BD8, D_00641BDC;
extern s32 D_00641BE0[], D_00641BF0[];
extern s32 D_00641C00, D_00641C04, D_00641C08;
extern s32 D_00641C10[], D_00642010[], D_00642410;
extern s32 D_00642418[], D_00642818[], D_00642C18;

void func_0011d768(s32);
void func_00141b10(s32, void *);
It14 *func_001496c8(s32, s32);
void func_00149f10(s32, void (*)(void));
s32 func_001ee5f0(s32);
s32 func_001ee618(s32);
u8 *func_001eeb88(s32);
s32 func_001eebd8(s32);
s32 func_001eec00(s32);
s32 func_001eec28(s32, s32);
s32 func_001eec48(s32, s32);
s32 func_001eed80(s32, s32, s32);
s32 func_001ef0c0(s32);
s32 func_001ef270(s32, s32);
s32 func_001ef320(void);
s32 func_001ef370(s32);
s32 func_001ef720(s32);
void func_001ef830(void);
s32 func_001efbb8(s32);
s32 func_001efd98(s32);
void *func_001f31a8(void *, s32);
void func_001f36b8(void *);
void func_001f3708(void *, s32);
void func_001f3758(void *);
void func_001f3d58(void *, s32);
void func_001f3dc0(void *);
void func_001f3e20(void *, void *);
void func_001f3e48(void *, void *);
void func_001f3e90(void *, void *);
s32 func_001f42b8(void *);
void func_001f8ba8(void *);
void func_001f8ee0(void *);
void func_001f8f30(void);
void func_001f9010(s32);
s32 func_001f9270(void *, s32, s32, s32, s32, s32);
void func_001f9438(void *, s32, s32, s32, s32, s32, s32);
s32 func_001f94f0(void *, s32, s32, s32, s32, s32, s32);
s32 func_001fb428(void *, s32, s32, s32, s32, s32, s32, s32, s32);
s32 func_001fd518(void *);
s32 func_001fd548(void *);
s32 func_001fd590(void *);
void func_001fd5e0(void *, s32);
void func_001fd610(void *, s32);
s32 func_001fd618(void *);
s32 func_001fd638(void *);
void func_001fd688(void *);
void func_001fd858(void *);
s32 func_001fe570(void *);
s32 func_001fe5a0(void *);
void func_00202fc0(void *);
void func_00206690(void *, s32, s32, s32);
void func_002066b0(void *, s32, s32, s32, s32, s32);
void func_00207830(void *, s32, s32, s32, s32, s32, s32);
void func_00207870(void *, s32, s32, s32, s32, s32, s32);
void func_00207bb0(void *, s32);
void func_00207f80(void *, s32, s32, s32, s32);
/* src/menu/partymdl.c: both take only the slot, but func_00211840 has the
 * window in a1 (the original moves it there) and the others do not. */
void func_0020a6c0();
void func_0020a728();
void func_0020a758(void *, s32, s32, s32);
void func_0020bd18(void *, s32);
void func_0020f290(s32 *, s32, s32);
void func_002114f0(void *, s32, s32, s32, s32, s32);

void func_002113f0(TextWin *a0) {
    if (func_001f42b8(a0)) {
        if (D_00425BC8->x8 & PAD_CROSS) {
            func_001f3708(a0, 6);
            func_0011d768(3);
        } else {
            func_0020bd18(a0, 8);
            if (func_001fe570(a0)) func_001f3708(a0, 6);
        }
    }
    func_00207bb0(a0, a0->x24);
}

void func_00211480(TextWin *a0, s32 a1) {
    s32 v = func_001efd98(a1) * 368;
    a0->xb4 -= v;
    a0->xba += v;
    a0->xc0 += v;
    a0->x24 = a1;
}

/* func_002114f0 (the row of an item) is in equip.n32.c. */

void func_002115e0(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    func_002114f0(arg0, arg1, arg2, arg3, arg4, arg5);
    if (arg5 != 0) {
        if (arg6 >= 2) {
            func_00207f80(arg0, arg1, arg2 + arg4 + 4, arg3, arg6);
        }
    }
}

void func_00211698(void) {
    u32 i;
    for (i = 0; i < D_003E3D68; i++) {
        s32 v = D_00304BE8->m[((u8 *)D_00304BE8)[0x48e + i]].sub.x32;
        D_00641BF0[i] = D_00641BE0[i] = v;
    }
}

void func_00211718(void) {
    D_00641C04 = 0;
    D_003F34C8 -= 1;
}

/* func_00211738 is in equip.nogcse.c. */

void func_00211840(WinF24 *o) {
    s32 s;
    if (D_003F34C0 & 1) return;
    if (!D_00641C00) return;
    s = D_00641C08;
    switch (s) {
    case 0:
        o->x24 += D_002BBDFC;
        func_0020a758(o, D_00641BA8, 10, 50);
        return;
    case 1:
        func_0020a728(D_00641BA8, o);
        D_003F34C8++;
        D_00641C04 = s;
        D_00641C08 = 2;
        func_00149f10(D_00641BE0[D_00641BA8], func_00211718);
        return;
    case 2:
        if (!D_00641C04) D_00641C08 = 3;
        break;
    case 3:
        func_0020a6c0(D_00641BA8, o);
        D_00641C08 = 0;
        break;
    }
}

void func_002119a8(TextWin *w) {
    u8 *s;
    s32 n, id, n2;
    func_001f9270(w, 0, 16, D_00641BAC == 0 ? 171 : 172, 15, 0x801ec8c8);
    if (D_00641BBC) {
        s = func_001eeb88(D_00641BBC);
        n = func_001eec28(D_00641BAC, D_00641BBC);
    } else {
        s = (u8 *)func_001efbb8(167);
        n = 0;
    }
    func_001f94f0(w, 0, 12, 31, (s32)s, 14, 0x80808080);
    func_001fb428(w, 1, 3, 0, 130, 53, n, 14, 0x80808080);
    func_002066b0(w, 12, 67, 118, 0x80323232, 0x80323232);
    id = w->x24;
    if (id) {
        s = func_001eeb88(id);
        n2 = func_001eec28(D_00641BAC, id);
    } else {
        s = (u8 *)func_001efbb8(167);
        n2 = 0;
    }
    func_001f94f0(w, 0, 12, 71, (s32)s, 14, 0x8080e680);
    func_001fb428(w, 1, 2, 0, 130, 93, n2, 14, 0x8080e680);
    func_002066b0(w, 12, 107, 118, 0x80323232, 0x80323232);
    (*(S4_3e8e08 *)&D_003E8E08).a = w->x28;
    (*(S4_3e8e08 *)&D_003E8E08).c = func_001eec48(D_00641BAC, id);
    if ((*(S4_3e8e08 *)&D_003E8E08).a < (*(S4_3e8e08 *)&D_003E8E08).c) {
        (*(S4_3e8e08 *)&D_003E8E08).b = 0x80fc927a;
    } else if ((*(S4_3e8e08 *)&D_003E8E08).a == (*(S4_3e8e08 *)&D_003E8E08).c) {
        (*(S4_3e8e08 *)&D_003E8E08).b = 0x80808080;
    } else {
        (*(S4_3e8e08 *)&D_003E8E08).b = 0x806e6eff;
    }
    func_001f9438(w, 0, 12, 111, 173, 15, 0x80e6e6e6);
    func_002066b0(w, 12, 147, 118, 0x80323232, 0x80323232);
    (*(S4_3e8e08 *)&D_003E8E08).a = 0;
    (*(S4_3e8e08 *)&D_003E8E08).a = w->x2c;
    (*(S4_3e8e08 *)&D_003E8E08).c = 0;
    if (id) {
        (*(S4_3e8e08 *)&D_003E8E08).c = w->x2c + func_001496c8(D_00641BAC, id)->x38;
        if (D_00641BBC) {
            (*(S4_3e8e08 *)&D_003E8E08).c -= func_001496c8(D_00641BAC, D_00641BBC)->x38;
        }
        if ((*(S4_3e8e08 *)&D_003E8E08).c < 0) (*(S4_3e8e08 *)&D_003E8E08).c = 0;
    }
    if ((*(S4_3e8e08 *)&D_003E8E08).a < (*(S4_3e8e08 *)&D_003E8E08).c) {
        (*(S4_3e8e08 *)&D_003E8E08).b = 0x80fc927a;
    } else if ((*(S4_3e8e08 *)&D_003E8E08).a == (*(S4_3e8e08 *)&D_003E8E08).c) {
        (*(S4_3e8e08 *)&D_003E8E08).b = 0x80808080;
    } else {
        (*(S4_3e8e08 *)&D_003E8E08).b = 0x806e6eff;
    }
    func_001f9438(w, 0, 12, 151, 479, 15, 0x80e6e6e6);
    func_002066b0(w, 12, 187, 118, 0x80323232, 0x80323232);
}

void func_00211d28(TextWin *arg0) {
    s32 temp_s1;

    temp_s1 = arg0->x24;
    if (temp_s1 != 0) {
        func_001f9010(0x17);
        func_001f94f0(arg0, 0, 0xAE, 0xC, temp_s1, 0x11, 0x80C87850);
    }
}

void func_00211da0(void) {
    s32 i;
    D_00642410 = 0;
    for (i = 1; i < 256; i++) {
        if (D_00304BE8->items[i] != 0 && func_001ef270(i, D_00641BAC) != 0) {
            D_00641C10[D_00642410] = i;
            D_00642410++;
        }
    }
    func_0020f290(D_00641C10, 0, D_00642410 - 1);
    for (i = 0; i < D_00642410; i++) {
        D_00642010[i] = D_00304BE8->items[D_00641C10[i]];
    }
}

void func_00211ed0(WinF28 *a) {
    s32 v, sel, i, y, k;
    WinF28 *o;
    if (func_001f42b8(a)) {
        if (D_00425BC8->x8 & PAD_CROSS) {
            func_001f3758(a);
            func_0011d768(3);
            D_00641BA4 = 1;
            D_00641C00 = 0;
            func_0020a728(D_00641BA8);
        } else {
            func_001fd858(a);
            func_0020bd18(a, 8);
            D_00641BD0 = func_001fd618(a);
            D_00641BD4 = func_001fd638(a);
            k = func_001fd548(a);
            v = D_00641C10[k];
            if (a->x24 == v) {
                a->x28 += D_002BBDFC;
                if (a->x28 >= 30.0f) a->x28 = 30.0f;
            } else {
                a->x28 = 0;
            }
            a->x24 = v;
            if (D_00641BC4 != 3) {
                s32 *e = &D_00641BE0[D_00641BA8];
                if (v != *e && v != 0 && a->x28 >= 30.0f && D_00641C08 == 0) {
                    *e = v;
                    D_00641C08 = 1;
                }
            }
            if ((o = a->x10)) {
                if (v) o->x24 = func_001eebd8(v);
                else o->x24 = (s32)func_001efbb8(169);
                if ((o = o->x10)) o->x24 = v;
            }
            if (func_001fe5a0(a) && !(D_00425BC8->x8 & 8)) {
                func_0011d768(5);
                if (v) {
                    if (D_00641BC4 != 3) {
                        if (v != D_00641BE0[D_00641BA8]) {
                            D_00641BF0[D_00641BA8] = v;
                            func_001ef830();
                        } else {
                            D_00641BB0->x32 = v;
                            D_00641BF0[D_00641BA8] = v;
                            func_001ef830();
                        }
                    } else {
                        D_00641BB0->x32 = v;
                        D_00641BF0[D_00641BC4] = v;
                        func_001ef830();
                    }
                } else {
                    D_00641BB0->x32 = 0;
                    D_00641BF0[D_00641BA8] = 0;
                }
                func_001f3d58(a, 5);
                func_001f3758(a);
                D_00641BA4 = 3;
                D_00641BC0 = v;
                D_00641C00 = 0;
            }
        }
    }
    func_00202fc0(a);
    sel = func_001fd518(a);
    i = func_001fd618(a);
    y = func_001fd590(a);
    func_001f8ee0(a);
    for (k = 0; k < 8 && i < D_00642410; k++, i++, y += 28) {
        func_002115e0(a, k == sel, 0, y, 166, D_00641C10[i], D_00642010[i]);
    }
    func_001f8f30();
}

void func_00212270(void) {
    if (D_00641BC4 != 3) {
        func_001f31a8(D_003F3B40, 0);
        D_003F34C0 |= 2;
    }
}

void func_002122b8(void *unused) {
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

void func_002123b8(WinB24 *a) {
    Rec_3E3D70 buf;
    Rec_3E3D70 *r;
    u8 s;
    u8 *p;
    func_001f9270(a, 0, 16, 174, 15, 0x801EC8C8);
    { s32 o = (s32)D_00641BB0; p = (u8 *)D_00641BB4 + o + 25; }
    s = *p;
    *p = a->x24;
    func_00141b10(D_00641BAC, &buf);
    { s32 o = (s32)D_00641BB0; ((u8 *)D_00641BB4 + o)[25] = s; }
    (*(S4_3e8e08 *)&D_003E8E08).c = buf.x40;
    r = &D_003E3D70.rec[D_00641BAC];
    (*(S4_3e8e08 *)&D_003E8E08).a = r->x40;
    if (r->x40 < buf.x40) (*(S4_3e8e08 *)&D_003E8E08).b = 0x80FC927A;
    else if (r->x40 == buf.x40) (*(S4_3e8e08 *)&D_003E8E08).b = 0x80808080;
    else (*(S4_3e8e08 *)&D_003E8E08).b = 0x806E6EFF;
    func_001f9438(a, 0, 12, 37, 175, 15, 0x80E6E6E6);
    func_002066b0(a, 12, 53, 118, 0x80323232, 0x80323232);
    (*(S4_3e8e08 *)&D_003E8E08).a = r->x48;
    (*(S4_3e8e08 *)&D_003E8E08).c = buf.x48;
    if (r->x48 < buf.x48) (*(S4_3e8e08 *)&D_003E8E08).b = 0x80FC927A;
    else if (r->x48 == buf.x48) (*(S4_3e8e08 *)&D_003E8E08).b = 0x80808080;
    else (*(S4_3e8e08 *)&D_003E8E08).b = 0x806E6EFF;
    func_001f9438(a, 0, 12, 69, 176, 15, 0x80E6E6E6);
    func_002066b0(a, 12, 85, 118, 0x80323232, 0x80323232);
    (*(S4_3e8e08 *)&D_003E8E08).a = r->xe0;
    (*(S4_3e8e08 *)&D_003E8E08).c = buf.xe0;
    if (r->xe0 < buf.xe0) (*(S4_3e8e08 *)&D_003E8E08).b = 0x80FC927A;
    else if (r->xe0 == buf.xe0) (*(S4_3e8e08 *)&D_003E8E08).b = 0x80808080;
    else (*(S4_3e8e08 *)&D_003E8E08).b = 0x806E6EFF;
    func_001f9438(a, 0, 12, 101, 177, 15, 0x80E6E6E6);
    func_002066b0(a, 12, 117, 118, 0x80323232, 0x80323232);
    (*(S4_3e8e08 *)&D_003E8E08).a = r->x4c;
    (*(S4_3e8e08 *)&D_003E8E08).c = buf.x4c;
    if (r->x4c < buf.x4c) (*(S4_3e8e08 *)&D_003E8E08).b = 0x80FC927A;
    else if (r->x4c == buf.x4c) (*(S4_3e8e08 *)&D_003E8E08).b = 0x80808080;
    else (*(S4_3e8e08 *)&D_003E8E08).b = 0x806E6EFF;
    func_001f9438(a, 0, 12, 133, 178, 15, 0x80E6E6E6);
    func_002066b0(a, 12, 149, 118, 0x80323232, 0x80323232);
    (*(S4_3e8e08 *)&D_003E8E08).a = r->x50;
    (*(S4_3e8e08 *)&D_003E8E08).c = buf.x50;
    if (r->x50 < buf.x50) (*(S4_3e8e08 *)&D_003E8E08).b = 0x80FC927A;
    else if (r->x50 == buf.x50) (*(S4_3e8e08 *)&D_003E8E08).b = 0x80808080;
    else (*(S4_3e8e08 *)&D_003E8E08).b = 0x806E6EFF;
    func_001f9438(a, 0, 12, 165, 179, 15, 0x80E6E6E6);
    func_002066b0(a, 12, 181, 118, 0x80323232, 0x80323232);
}

void func_00212768(TextWin *arg0) {
    s32 temp_s1;

    temp_s1 = arg0->x24;
    if (temp_s1 != 0) {
        func_001f9010(0x17);
        func_001f94f0(arg0, 0, 0xAE, 0xC, temp_s1, 0x11, 0x80C87850);
    }
}

void func_002127e0(void) {
    s32 i, v;
    D_00642818[0] = 0;
    D_00642C18 = 1;
    D_00642418[0] = 0;
    for (i = 1; i < 256; i++) {
        if (D_00304BE8->items[i] && func_001ef370(i) && func_001ef0c0(i) > 0) {
            s32 n = D_00642C18;
            D_00642C18 = n + 1;
            D_00642418[n] = i;
        }
    }
    if (D_00642C18 < 2) return;
    func_0020f290(&D_00642418[1], 0, D_00642C18 - 2);
    for (i = 1; i < D_00642C18; i++) {
        v = func_001ef0c0(D_00642418[i]);
        if (v > 0) D_00642818[i] = v;
    }
}

void func_00212930(TextWin *a) {
    TextWin *o;
    TextWin *q[2];
    s32 k, t, s, n, y, i, j, r;
    if (func_001f42b8(a)) {
        if (D_00425BC8->x8 & PAD_CROSS) {
            func_001f3758(a);
            func_0011d768(3);
            D_00641BA4 = 1;
        } else {
            func_001fd858(a);
            func_0020bd18(a, 8);
            D_00641BD8 = func_001fd618(a);
            D_00641BDC = func_001fd638(a);
            t = func_001fd548(a);
            k = D_00642418[t];
            if ((o = a->next)) {
                if (k) o->x24 = func_001eec00(k);
                else o->x24 = func_001efbb8(169);
                if ((o = o->next)) o->x24 = k;
            }
            if (func_001fe5a0(a)) {
                if (k) func_0011d768(5);
                else func_0011d768(75);
                t = func_001ef720(D_00641BAC);
                j = D_00641BAC; r = D_003E3E50[j].x0;
                if (t >= r - func_001eed80(j, D_00641BB4, k)) {
                    ((u8 *)D_00641BB4 + (s32)D_00641BB0)[25] = k;
                    func_001ef830();
                    func_001f3d58(a, 5);
                    func_001f3758(a);
                    D_00641BA4 = 3;
                    D_00641BC0 = k;
                } else {
                    func_0011d768(4);
                    if ((q[0] = func_001f31a8(D_003F3B10, 6))) {
                        func_001f3e48(q[0], a);
                        func_00211480(q[0], 170);
                    }
                }
            }
        }
    }
    func_00202fc0(a);
    s = func_001fd518(a);
    n = func_001fd618(a);
    y = func_001fd590(a);
    func_001f8ee0(a);
    for (i = 0; i < 8 && n < D_00642C18; i++) {
        func_002115e0(a, i == s, 0, y, 166, D_00642418[n], D_00642818[n]);
        n++;
        y += 28;
    }
    do { func_001f8f30(); } while (0);
}

void func_00212c20(TextWin *a0) {
    s32 v;
    if (D_00641BC8 + D_00641BCC == 0) {
        v = func_001eebd8(D_00641BB0->x32);
    } else {
        v = func_001eec00(D_00641BB0->x19[D_00641BCC - 1]);
    }
    func_001f9010(23);
    func_001f94f0(a0, 0, 174, 12, v, 17, 0x80c87850);
}

/* The slot list.  Matched from a 6-word draft: `func_002114f0(o, m, 0, cur, 166, v); cur += 28;`
 * (cur passed directly) and `j++; i++;` (j first: loop.c then initialises the t[j+24] giv before
 * cur, so the giv gets s1 and cur s2 as the original), with the identical-arm
 * `if (j) m = i == sel; else m = i == sel;` (jump2 merges the arms; the copies give sel the refs
 * it needs for s6).  Natural spellings of m without the identical arms are 7 words off. */
void func_00212cc0(WinU16 *o) {
    s32 w[4];
    u8 *t;
    s32 n, s;
    Mem74 *e;
    s32 i, j, sel, cur, cnt, lim, a, b;
    u8 *pc;
    s32 *p;
    void *q;

    n = D_00304BE8->x48e[D_00641BC4];
    e = &((Save74 *)D_00304BE8)->e[n];
    t = &e->x4;
    if (func_001f42b8(o)) {
        if (D_00425BC8->x8 & PAD_CROSS) {
            func_001f3758(o);
            func_0011d768(3);
            D_00641BA4 = 0;
        } else {
            func_001fd858(o);
            func_0020bd18(o, 8);
            D_00641BC8 = (s16)o->xd0 >> 4;
            D_00641BCC = (s16)o->xd2 >> 4;
            s = D_00641BC8 + D_00641BCC;
            if (!func_001fe5a0(o)) goto done;
            if (s == 0) {
                if (n == 0 && !func_001ef320()) {
                    func_0011d768(4);
                    goto done;
                }
                func_0011d768(2);
                D_00641BA4 = 2;
                D_00641BB8 = s;
                func_001f3708(o, 5);
                {
                    q = o->x10;
                    if (q) {
                        func_001f36b8(q);
                        D_00641BBC = D_00641BF0[D_00641BC4];
                        func_00211da0();
                        D_00641C00 = 1;
                        if ((w[0] = (s32)func_001f31a8(D_003F3C00, 6))) {
                            func_001f3e48((void *)w[0], o);
                            func_002122b8(o);
                            ((WinU16 *)w[0])->xd0 = (u16)D_00641BD0 << 4;
                            ((WinU16 *)w[0])->xd2 = (u16)D_00641BD4 << 4;
                            func_001fd5e0((void *)w[0], D_00642410);
                            func_001fd610((void *)w[0], 7);
                            func_001fd688((void *)w[0]);
                            if ((w[1] = (s32)func_001f31a8(D_003F3BD0, 6))) {
                                func_001f3e48((void *)w[1], (void *)w[0]);
                                if ((w[2] = (s32)func_001f31a8(D_003F3BA0, 6))) {
                                    func_001f3e48((void *)w[2], (void *)w[1]);
                                    ((WinU16 *)w[2])->x28 = D_003E3D70.e3D70c[D_00641BAC].s.d;
                                    ((WinU16 *)w[2])->x2c = D_003E3D70.e3D70c[D_00641BAC].s.c;
                                    if (D_00641BC4 != 3) {
                                        if ((w[3] = (s32)func_001f31a8(D_003F3B70, 1))) {
                                            func_001f3e48((void *)w[3], (void *)w[2]);
                                            func_0020a6c0(D_00641BC4);
                                        }
                                    }
                                }
                                func_001f3dc0((void *)w[0]);
                            }
                        }
                    }
                }
            } else {
                func_0011d768(2);
                D_00641BA4 = 2;
                D_00641BB8 = s;
                func_001f3708(o, 5);
                {
                    q = o->x10;
                    if (q) {
                        func_001f36b8(q);
                        D_00641BB4 = s - 1;
                        D_00641BBC = e->x1c[s];
                        func_002127e0();
                        if ((w[0] = (s32)func_001f31a8(D_003F3C90, 6))) {
                            func_001f3e90(q, (void *)w[0]);
                            func_001f3e20((void *)w[0], q);
                            ((WinU16 *)w[0])->xd0 = (u16)D_00641BD8 << 4;
                            ((WinU16 *)w[0])->xd2 = (u16)D_00641BDC << 4;
                            func_001fd5e0((void *)w[0], D_00642C18);
                            func_001fd610((void *)w[0], 7);
                            func_001fd688((void *)w[0]);
                            if ((w[1] = (s32)func_001f31a8(D_003F3C60, 6))) {
                                func_001f3e90((void *)w[0], (void *)w[1]);
                                func_001f3e20((void *)w[1], (void *)w[0]);
                                if ((w[2] = (s32)func_001f31a8(D_003F3C30, 6))) {
                                    func_001f3e90((void *)w[1], (void *)w[2]);
                                    func_001f3e20((void *)w[2], (void *)w[1]);
                                }
                                func_001f3dc0((void *)w[0]);
                            }
                        }
                    }
                }
            }
        }
    }
done:
/*P*/
    func_00202fc0(o);
    sel = func_001fd518(o);
    j = func_001fd618(o);
    cur = func_001fd590(o);
    i = 0;
    a = o->x28;
    lim = o->xcc;
    cnt = o->xce + 1;
    func_001f8ba8(o);
/*Q*/
    for (; i < cnt && j < lim; ) {
        s32 v;
        s32 m;
        if (j == 0) v = D_00641BF0[D_00641BC4];
        else v = t[j + 24];
        m = 2;
        if (a) { if (j) m = i == sel; else m = i == sel; }
        func_002114f0(o, m, 0, cur, 166, v);
        cur += 28;
        j++;
        i++;
    }
    func_001f8f30();
}

void func_002131e8(TextWin *a0) {
    s32 x;
    s32 t;
    func_001f9010(23);
    t = D_00641BC4;
    x = 165;
    if (t) {
        (*(s32 *)&D_003E8E08) = func_001ee618(t);
        x = 166;
    }
    func_001f9438(a0, 0, 174, 12, x, 17, 0x80c87850);
}

/* func_00213258 (the member list) is in equip.nostrict.c. */

/* The page's first window: by the state D_00641BA4 it opens the member, slot
 * and list windows.  Block-local u16 / s16 values give the stores in the
 * order xd2, xcc, xce, xba. */
void func_002134c8(WinS16 *o) {
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
            func_001f3e90(o, (WinS16 *)w[0]);
            func_001f3e20((WinS16 *)w[0], o);
            p = (s32 *)&D_003E3D68;
            q = &D_00641BC4;
            {
                s16 a = *(u16 *)q * 16;
                s16 b = (*p * 14 + 0x7fff) << 5;
                u16 c = *p;
            ((WinS16 *)w[0])->xd2 = a;
            ((WinS16 *)w[0])->xcc = c;
            ((WinS16 *)w[0])->xce = c;
            ((WinS16 *)w[0])->xba = b;}
            w[1] = (s32)func_001f31a8(D_003F3D20, 6);
            if (w[1] == 0) break;
            func_001f3e90((WinS16 *)w[0], (WinS16 *)w[1]);
            func_001f3e20((WinS16 *)w[1], (WinS16 *)w[0]);
            w[2] = (s32)func_001f31a8(D_003F3CF0, 6);
            if (w[2] == 0) break;
            func_001f3e90((WinS16 *)w[1], (WinS16 *)w[2]);
            func_001f3e20((WinS16 *)w[2], (WinS16 *)w[1]);
            D_00641BAC = D_00304BE8->x48e[*q];
            D_00641BB0 = &D_00304BE8->m[D_00641BAC].sub;
            n = D_00641BB0->x18 + 1;
            ((WinS16 *)w[2])->xcc = n;
            if (n < 9) {
                ((WinS16 *)w[2])->xce = n;
                ((WinS16 *)w[2])->xba = n * 448 - 32;
            } else {
                ((WinS16 *)w[2])->xce = 8;
                ((WinS16 *)w[2])->xba = 3552;
            }
            ((WinS16 *)w[2])->xd0 = (u16)D_00641BC8 * 16;
            ((WinS16 *)w[2])->xd2 = (u16)D_00641BCC * 16;
            func_001f3dc0((WinS16 *)w[0]);
            break;
        case 1:
        c1:
            w[0] = (s32)func_001f31a8(D_003F3CF0, 6);
            if (w[0] == 0) break;
            func_001f3e90(o, (WinS16 *)w[0]);
            func_001f3e20((WinS16 *)w[0], o);
            n = D_00641BB0->x18 + 1;
            ((WinS16 *)w[0])->xcc = n;
            if (n < 9) {
                ((WinS16 *)w[0])->xce = n;
                ((WinS16 *)w[0])->xba = n * 448 - 32;
            } else {
                ((WinS16 *)w[0])->xce = 8;
                ((WinS16 *)w[0])->xba = 3552;
            }
            ((WinS16 *)w[0])->xd0 = (u16)D_00641BC8 * 16;
            ((WinS16 *)w[0])->xd2 = (u16)D_00641BCC * 16;
            ((WinS16 *)w[0])->x28 = 1;
            w[1] = (s32)func_001f31a8(D_003F3CC0, 6);
            if (w[1] == 0) break;
            func_001f3e90((WinS16 *)w[0], (WinS16 *)w[1]);
            func_001f3e20((WinS16 *)w[1], (WinS16 *)w[0]);
            func_001f3dc0((WinS16 *)w[0]);
            break;
        case 2:
            if (D_00641BB8 == 0) {
                pa = &D_00641BA8;
                D_00641BBC = D_00641BF0[*pa];
                func_00211da0();
                D_00641C00 = 1;
                w[0] = (s32)func_001f31a8(D_003F3C00, 6);
                if (w[0] == 0) break;
                func_001f3e48((WinS16 *)w[0], o);
                func_002122b8(o);
                ((WinS16 *)w[0])->xd0 = (u16)D_00641BD0 * 16;
                ((WinS16 *)w[0])->xd2 = (u16)D_00641BD4 * 16;
                func_001fd5e0((WinS16 *)w[0], D_00642410);
                func_001fd610((WinS16 *)w[0], 7);
                func_001fd688((WinS16 *)w[0]);
                w[1] = (s32)func_001f31a8(D_003F3BD0, 6);
                if (w[1] == 0) break;
                func_001f3e48((WinS16 *)w[1], (WinS16 *)w[0]);
                w[2] = (s32)func_001f31a8(D_003F3BA0, 6);
                if (w[2] != 0) {
                    func_001f3e48((WinS16 *)w[2], (WinS16 *)w[1]);
((WinS16 *)w[2])->x28 = D_003E3D70.e3D70_2[D_00641BAC].s.d;
                    ((WinS16 *)w[2])->x2c = D_003E3D70.e3D70_2[D_00641BAC].s.c;
                    if (D_00641BC4 != 3) {
                        w[3] = (s32)func_001f31a8(D_003F3B70, 6);
                        if (w[3] != 0) {
                            func_001f3e48((WinS16 *)w[3], (WinS16 *)w[2]);
                            func_0020a6c0(*pa);
                        }
                    }
                }
                func_001f3dc0((WinS16 *)w[0]);
            } else {
                D_00641BB4 = D_00641BB8 - 1;
                D_00641BBC = ((u8 *)(D_00641BB8 + (s32)D_00641BB0))[24];
                func_002127e0();
                w[0] = (s32)func_001f31a8(D_003F3C90, 6);
                if (w[0] == 0) break;
                func_001f3e90(o, (WinS16 *)w[0]);
                func_001f3e20((WinS16 *)w[0], o);
                ((WinS16 *)w[0])->xd0 = (u16)D_00641BD8 * 16;
                ((WinS16 *)w[0])->xd2 = (u16)D_00641BDC * 16;
                func_001fd5e0((WinS16 *)w[0], D_00642C18);
                func_001fd610((WinS16 *)w[0], 7);
                func_001fd688((WinS16 *)w[0]);
                w[1] = (s32)func_001f31a8(D_003F3C60, 6);
                if (w[1] == 0) break;
                func_001f3e90((WinS16 *)w[0], (WinS16 *)w[1]);
                func_001f3e20((WinS16 *)w[1], (WinS16 *)w[0]);
                w[2] = (s32)func_001f31a8(D_003F3C30, 6);
                if (w[2] != 0) {
                    func_001f3e90((WinS16 *)w[1], (WinS16 *)w[2]);
                    func_001f3e20((WinS16 *)w[2], (WinS16 *)w[1]);
                }
                func_001f3dc0((WinS16 *)w[0]);
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

void func_00213c60(TextWin *arg0) {
    func_00207830(arg0, 4, 2, 0, 0, 0x7A, 0x6A);
}

void func_00213c90(TextWin *arg0) {
    TextWin *temp_v0;

    temp_v0 = func_001f31a8(D_003F3D80, 0);
    if (temp_v0 != 0) {
        func_001f3e90(arg0, temp_v0);
        func_001f3e20(temp_v0, arg0);
    }
    D_00641BA0 = arg0;
    D_00641BA4 = 0;
    func_00211698();
}

void func_00213d00(void) {
  u32 new_var;
  u32 temp_a0;
  new_var = (u32) D_00641BC4;
  temp_a0 = D_003E3D68 - 1;
  if (temp_a0 < new_var)
  {
    D_00641BC4 = temp_a0;
  }
}

void func_00213d30(void) {
    D_00641BC4 = 0;
    D_00641BC8 = 0;
    D_00641BCC = 0;
    D_00641BD0 = 0;
    D_00641BD4 = 0;
    D_00641BD8 = 0;
    D_00641BDC = 0;
    D_00641C04 = 0;
    D_00641C08 = 0;
}

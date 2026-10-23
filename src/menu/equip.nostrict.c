/* The equipment page's member list (src/menu/equip.c; docs/modules.md
 * "Session 40"): func_00213258 is the callback of its window.  The cursor is
 * D_00641BC4; it sets the slot list's size from the member's accessory count
 * (Sub_304be8 +0x18, plus the weapon row), and a choice sets D_00641BA8 /
 * D_00641BAC / D_00641BB0 and opens the slot list (D_003F3CC0).  It needs
 * -fno-strict-aliasing (was in src/hand/nostrict/text_00200000_h70.c). */
#include "common.h"
#include "text/textwin.h"
#include "data/bss_0064.h"
#include "data/pieces/D_00304BE8_s.h"
#include "data/pieces/D_00425BC8.h"
#include "data/pieces/D_003E3D68.h"

extern void *D_00641BA0;
extern s32 D_00641BAC, D_00641BC4;
extern Sub_304be8 *D_00641BB0;
extern u8 D_003F3CC0[];
s32 func_001f42b8(void *);
s32 func_001f3758(void *);
void func_0011d768(s32);
void func_001fd858(TextWin *);
void func_0020bd18(TextWin *, s32);
s32 func_001fd518(TextWin *);
s32 func_001fe5a0(TextWin *);
void func_001f3708(TextWin *, s32);
void func_001f36b8(TextWin *);
TextWin *func_001f31a8(void *, s32);
void func_001f3e90(TextWin *, TextWin *);
void func_001f3e20(TextWin *, TextWin *);
void func_001f3dc0(TextWin *);
s32 func_001ee5f0(s32);
void func_00207870(TextWin *, s32, s32, s32, s32, s32, s32);

void func_00213258(TextWin *a0) {
    TextWin *o, *c;
    u32 i;
    s32 sel, k;
    if (func_001f42b8(a0) != 0) {
        if (D_00425BC8->x8 & 0x4000) {
            func_001f3758(D_00641BA0);
            func_0011d768(3);
        } else {
            func_001fd858(a0);
            func_0020bd18(a0, 8);
            D_00641BC4 = func_001fd518(a0);
            o = a0->next;
            if (o != 0 && (o = o->next) != 0) {
                s32 v = D_00304BE8->m[D_00304BE8->x48e[D_00641BC4]].sub.x18 + 1;
                o->xcc = v;
                if (v < 9) {
                    o->xce = v;
                    o->xba = v * 448 - 32;
                } else {
                    o->xce = 8;
                    o->xba = 3552;
                }
            }
            if (func_001fe5a0(a0)) {
                func_0011d768(2);
                D_00641BA4 = 1;
                D_00641BA8 = D_00641BC4;
                D_00641BAC = D_00304BE8->x48e[D_00641BC4];
                D_00641BB0 = &D_00304BE8->m[D_00641BAC].sub;
                func_001f3708(a0, 5);
                o = a0->next;
                if (o != 0) {
                    func_001f36b8(o);
                    o = o->next;
                    if (o != 0) {
                        o->x28 = 1;
                        c = func_001f31a8(D_003F3CC0, 6);
                        if (c != 0) {
                            func_001f3e90(o, c);
                            func_001f3e20(c, o);
                        }
                        func_001f3dc0(o);
                    }
                }
            }
        }
    }
    sel = func_001fd518(a0);
    for (i = 0, k = 0; i < D_003E3D68; k += 28) {
        s32 eq = i == sel;
        s32 v = func_001ee5f0(D_00304BE8->x48e[i++]);
        func_00207870(a0, eq, 0, 0, k, 122, v);
    }
}


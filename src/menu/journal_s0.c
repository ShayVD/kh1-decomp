/* Page 5's section 0 (D_003F5A00[0]; docs/modules.md "Session 42"),
 * 0x0021fbb8-0x002205e0.  Opener func_00220580 keeps the section's window in
 * D_006433F0; set up func_00220590 (fills the list, D_003F5C18[0] = "not
 * empty"), reset func_002205c0.
 *
 * func_0021fbb8 lists the entries i < 31 that func_001eb9a8(D_003F5FF0[i],
 * D_003F6070[i]) accepts into D_006433F8 (D_00643418 of them), sets the
 * section's "new" mark (func_00207298 / func_002072e0 on mark 0) and
 * D_003F5C30[0] (journal.c's "complete" flag) once the run of D_003F5FF0
 * values 9, 8, ... is all accepted.  func_0021ff68 is the list (four rows a
 * page, names are messages D_003F5FF0[i] + 0x20, func_0021fd60), func_0021fd90
 * an entry's text (func_001c2df0 on D_003F3518).  Not proved by a boot. */
#include "common.h"
#include "data/bss_0064.h"
#include "data/pieces/D_00425BC8.h"
#include "data/pieces/D_003F5C18.h"
#include "data/pieces/D_003F5FF0.h"
#include "vm/script_vm.h"
#include "menu/journal.h"

extern JsWin *D_006433F0; /* src/data/bss_0064.c: s32 D_006433F0 */
extern s32 D_003F5C30[];
extern s32 D_003F6070[];
extern s32 D_003F3518;
extern u16 D_003E9104;
extern u8 D_003F60F0[];
extern u8 D_003F6120[], D_003F6150[], D_003F6180[];

void func_0011d768(s32);
s32 func_0010eb78(s32);
s32 func_0010edb0(s32, s32, s32, s32, s32, s32);
s32 func_001eb9a8(s32, s32);
void *func_001f31a8(void *, s32);
s32 func_001f3758(void *);
void func_001f3e48(void *, void *);
s32 func_001f42b8(void *);
s32 func_001f94f0(void *, s32, s32, s32, s32, s32, s32);
s32 func_001fd518(void *);
s32 func_001fd668(void *);
void func_001fd858(void *);
s32 func_001fe570(void *);
void func_00203788(void *, s32, s32, s32, u32);
void func_00206ea8(s32);
s32 func_00206ee8(s32);
void func_00207298(s32);
void func_002072e0(s32);
void func_00207428(void *, s32, s32);
void func_0021af38(void *);
s32 func_0021b800(s32);
void func_0021b820(void);
void func_0021c4f8(void *);
void func_0021c780(void *, s32, s32);
void func_0021c9a0(void *, s32, s32);
void func_0021cb00(void *, s32, s32, s32, s32);
void func_0021ccd0(void *, s32);

void func_0021fbb8(void) {
    s32 i, k;
    D_00643418 = 0;
    for (i = 0; i < 31; i++) {
        if (func_001eb9a8(D_003F5FF0[i], D_003F6070[i])) D_006433F8[D_00643418++] = i;
    }
    for (i = 0; i < D_00643418; i++) {
        if (!func_00206ee8(D_006433F8[i])) {
            func_00207298(0);
            goto next;
        }
    }
    func_002072e0(0);
next:
    D_003F5C30[0] = 0;
    for (k = 9, i = 30;; k--) {
        if (!func_001eb9a8(D_003F5FF0[i], D_003F6070[i])) return;
        while (i != 0) {
            i--;
            if (D_003F5FF0[i] != k) goto cont;
        }
        D_003F5C30[0] = 1;
        return;
    cont:;
    }
}

s32 func_0021fd60(s32 i) {
    return func_0021b800(D_003F5FF0[i] + 0x20);
}

s32 func_0021fd88(s32 arg0) {
    return arg0;
}

s32 func_0021fd90(JsWin *a) {
    s32 x, y, k;
    if (func_001f42b8(a)) {
        if (D_00425BC8->x8 & 0x4000) {
            func_001f3758(a);
            func_0011d768(3);
        } else {
            u32 b = D_00425BC8->x10;
            s32 n;
            k = 0;
            n = a->xd8;
            if (b & 0x80000480) {
                if (a->xda > 0) {
                    a->xda -= 16;
                    k = 1;
                }
            } else if (b & 0x20000820) {
                s32 m = n - 1;
                if (a->xda < m * 16) {
                    a->xda += 16;
                    k = 1;
                }
            }
            if (k) func_0011d768(k);
            D_00643424 = func_001fd668(a);
        }
    }
    func_00203788(a, 372, 40, 486, 0x80C8C8C8);
    func_0021b820();
    func_0021c9a0(a, 16, 72);
    func_0021cb00(a, 32, 108, 9, 30);
    func_0021cb00(a, 280, 108, 9, 30);
    x = ((a->xb0 - 0x7000) >> 4) + 32;
    y = ((a->xb4 - 0x7400) >> 4) + 84;
    k = func_0021fd88(a->x24);
    return func_0010edb0(x, y, 256, D_00643424 * 2, a->x90, (s32)func_001c2df0((s8 *)D_003F3518, k));
}

void func_0021ff50(JsWin *a) {
    func_00206ea8(a->x24);
}

void func_0021ff68(JsWin *a) {
    s32 i, j, y, step, id;
    JsWin *o;
    if (func_001f42b8(a)) {
        if (D_00425BC8->x8 & 0x4000) {
            func_001f3758(D_006433F0);
            func_0011d768(3);
        } else {
            u32 b;
            s32 n, k;
            func_001fd858(a);
            D_0064341C = func_001fd518(a);
            b = D_00425BC8->x10;
            k = 0;
            n = a->xd8;
            if (b & 0x80000480) {
                if (a->xda > 0) {
                    a->xda -= 16;
                    k = 1;
                }
            } else if (b & 0x20000820) {
                s32 m = n - 1;
                if (a->xda < m * 16) {
                    a->xda += 16;
                    k = 1;
                }
            }
            D_00643420 = func_001fd668(a);
            if (k) {
                func_0011d768(1);
                if (D_00643418 < 4 || D_00643420 == n - 1) {
                    a->xcc = a->xce = (D_00643418 - 1) % 4 + 1;
                } else {
                    a->xcc = a->xce = 4;
                }
            }
            if (func_001fe570(a)) {
                func_001f3758(D_006433F0->x10);
                o = func_001f31a8(D_003F60F0, 50);
                if (o) {
                    func_001f3e48(o, a);
                    D_00643424 = 0;
                    id = D_006433F8[D_00643420 * 4 + D_0064341C];
                    o->xa0 = D_003E9104;
                    k = func_0010eb78((s32)func_001c2df0((s8 *)D_003F3518, func_0021fd88(id)));
                    o->xd8 = (k + 1) / 2;
                    o->xda = D_00643424 << 4;
                    o->x24 = id;
                }
            }
        }
    }
    func_00203788(a, 372, 40, 486, 0x80C8C8C8);
    step = a->xc4 >> 4;
    y = 116;
    for (i = D_00643420 * 4, j = 0; j < 4 && i < D_00643418; j++) {
        id = D_006433F8[i++];
        func_001f94f0(a, 0, 322, y, func_0021fd60(id), 15, 0x80461E00);
        if (!func_00206ee8(id)) func_00207428(a, 450, y + 10);
        y += step;
    }
    func_0021b820();
    func_0021c4f8(a);
}

void func_002202b8(JsWin *arg0) {
    func_0021b820();
    func_0021ccd0(arg0, 2);
    func_0021af38(arg0);
}

void func_002202f0(JsWin *arg0) {
    func_0021b820();
    func_0021c780(arg0, 0x10, 0x48);
    func_0021cb00(arg0, 0x118, 0x6C, 9, 0x1E);
}

void func_00220338(JsWin *a) {
    JsWin *o[3];
    if (!(o[0] = func_001f31a8(D_003F6180, 50))) return;
    func_001f3e48(o[0], a);
    if (!(o[1] = func_001f31a8(D_003F6150, 50))) return;
    func_001f3e48(o[1], o[0]);
    if (!(o[2] = func_001f31a8(D_003F6120, 50))) return;
    func_001f3e48(o[2], o[1]);
    if (D_00643420 * 4 > D_00643418 / 4 * 4) D_00643420 = 0;
    if (D_00643418 < D_00643420 * 4 + D_0064341C) D_0064341C = 0;
    o[2]->xca = D_00643418;
    o[2]->xd8 = (D_00643418 + 3) / 4;
    o[2]->xda = D_00643420 << 4;
    if (D_00643418 < 4 || D_00643420 == o[2]->xd8 - 1) o[2]->xcc = (D_00643418 - 1) % 4 + 1;
    else o[2]->xcc = 4;
    o[2]->xd2 = D_0064341C << 4;
}

void func_002204b0(JsWin *arg0) {
    if (func_001f42b8(arg0) != 0) {
        func_00220338(arg0);
    }
}

void func_002204f0(void) {
    s32 i;
    for (i = 0; i < D_00643418; i++) {
        if (!func_00206ee8(D_006433F8[i])) {
            func_00207298(0);
            return;
        }
    }
    func_002072e0(0);
}

void func_00220580(JsWin *a) {
    D_006433F0 = a;
}

void func_00220590(void) {
    func_0021fbb8();
    D_003F5C18[0] = D_00643418 != 0;
}

void func_002205c0(void) {
    D_0064341C = 0;
    D_00643420 = 0;
    D_00643424 = 0;
}

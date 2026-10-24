/* Page 5's section 1 (D_003F5A00[1]; docs/modules.md "Session 42"),
 * 0x00222ba8-0x00223508.  Opener func_002234a8 keeps the section's window in
 * D_006436A0; set up func_002234b8 (D_003F5C1C = "not empty"), reset
 * func_002234e8.
 *
 * func_00222ba8 lists the entries i < 13 that func_001ebc38(i) has into
 * D_006436A8 (D_006436B8 of them; D_003F5C34 once all 13 are there) and sets
 * the section's "new" mark (mark 1).  func_00222e90 is the list (four rows a
 * page, names are messages 0x13 + i, func_00222c98), func_00222cb8 an entry's
 * text (func_001c2df0 on D_003F3520).  Not proved by a boot. */
#include "common.h"
#include "platform/pad.h"
#include "data/bss_0064.h"
#include "data/pieces/D_00425BC8.h"
#include "vm/script_vm.h"
#include "menu/journal.h"

extern JsWin *D_006436A0; /* src/data/bss_0064.c: s32 D_006436A0 */
extern s32 D_003F5C1C;
extern s32 D_003F5C34;
extern s32 D_003F3520;
extern u16 D_003E9104;
extern u8 D_003F6650[];
extern u8 D_003F6680[], D_003F66B0[], D_003F66E0[];

void func_0011d768(s32);
s32 func_0010eb78(s32);
s32 func_0010edb0(s32, s32, s32, s32, s32, s32);
s32 func_001ebc38(s32);
void *func_001f31a8(void *, s32);
void func_001f3758(void *);
void func_001f3e48(void *, void *);
s32 func_001f42b8(void *);
s32 func_001f94f0(void *, s32, s32, s32, s32, s32, s32);
s32 func_001fd518(void *);
s32 func_001fd668(void *);
void func_001fd858(void *);
s32 func_001fe570(void *);
void func_00203788(void *, s32, s32, s32, u32);
void func_00206f78(s32);
s32 func_00206fb8(s32);
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

void func_00222ba8(void) {
    s32 i;
    D_006436B8 = 0;
    for (i = 0; i < 13; i++) {
        if (func_001ebc38(i) != 0) {
            D_006436A8[D_006436B8++] = i;
        }
    }
    for (i = 0; i < D_006436B8; i++) {
        if (func_00206fb8(D_006436A8[i]) == 0) {
            func_00207298(1);
            goto end;
        }
    }
    func_002072e0(1);
end:
    D_003F5C34 = D_006436B8 == 13;
}

s32 func_00222c98(s32 i) {
    return func_0021b800(i + 0x13);
}

s32 func_00222cb0(s32 arg0) {
    return arg0;
}

s32 func_00222cb8(JsWin *a0) {
    s32 x, y, r;
    if (func_001f42b8(a0)) {
        PadSt_425bc8 *p = D_00425BC8;
        if (p->x8 & PAD_CROSS) {
            func_001f3758(a0);
            func_0011d768(3);
        } else {
            s32 f = 0;
            s32 n = a0->xd8;
            u32 b = p->x10;
            if (b & (PAD_DIR(PAD_LEFT) | PAD_L1)) {
                if (a0->xda > 0) {
                    a0->xda -= 16;
                    f = 1;
                }
            } else if (b & (PAD_DIR(PAD_RIGHT) | PAD_R1)) {
                if (a0->xda < (n - 1) << 4) {
                    a0->xda += 16;
                    f = 1;
                }
            }
            if (f) func_0011d768(f);
            D_006436C4 = func_001fd668(a0);
        }
    }
    func_00203788(a0, 372, 40, 486, 0x80c8c8c8);
    func_0021b820();
    func_0021c9a0(a0, 16, 72);
    func_0021cb00(a0, 32, 108, 9, 30);
    func_0021cb00(a0, 280, 108, 9, 30);
    x = ((a0->xb0 - 0x7000) >> 4) + 32;
    y = ((a0->xb4 - 0x7400) >> 4) + 84;
    r = func_00222cb0(a0->x24);
    return func_0010edb0(x, y, 256, D_006436C4 * 2, a0->x90, (s32)func_001c2df0((s8 *)D_003F3520, r));
}

void func_00222e78(JsWin *a) {
    func_00206f78(a->x24);
}

void func_00222e90(JsWin *a) {
    s32 i, j, y, step, id;
    JsWin *o;
    if (func_001f42b8(a)) {
        if (D_00425BC8->x8 & PAD_CROSS) {
            func_001f3758(D_006436A0);
            func_0011d768(3);
        } else {
            u32 b;
            s32 n, k;
            func_001fd858(a);
            D_006436BC = func_001fd518(a);
            b = D_00425BC8->x10;
            k = 0;
            n = a->xd8;
            if (b & (PAD_DIR(PAD_LEFT) | PAD_L1)) {
                if (a->xda > 0) {
                    a->xda -= 16;
                    k = 1;
                }
            } else if (b & (PAD_DIR(PAD_RIGHT) | PAD_R1)) {
                s32 m = n - 1;
                if (a->xda < m * 16) {
                    a->xda += 16;
                    k = 1;
                }
            }
            D_006436C0 = func_001fd668(a);
            if (k) {
                func_0011d768(1);
                if (D_006436B8 < 4 || D_006436C0 == n - 1) {
                    a->xcc = a->xce = (D_006436B8 - 1) % 4 + 1;
                } else {
                    a->xcc = a->xce = 4;
                }
            }
            if (func_001fe570(a)) {
                func_001f3758(D_006436A0->x10);
                o = func_001f31a8(D_003F6650, 50);
                if (o) {
                    func_001f3e48(o, a);
                    id = D_006436A8[D_006436C0 * 4 + D_006436BC];
                    o->xa0 = D_003E9104;
                    k = func_0010eb78((s32)func_001c2df0((s8 *)D_003F3520, func_00222cb0(id)));
                    o->xd8 = (k + 1) / 2;
                    D_006436C4 = 0;
                    o->xda = D_006436C4 << 4;
                    o->x24 = id;
                }
            }
        }
    }
    func_00203788(a, 372, 40, 486, 0x80C8C8C8);
    step = a->xc4 >> 4;
    y = 116;
    for (i = D_006436C0 * 4, j = 0; j < 4 && i < D_006436B8; j++) {
        id = D_006436A8[i++];
        func_001f94f0(a, 0, 322, y, func_00222c98(id), 15, 0x80461E00);
        if (!func_00206fb8(id)) func_00207428(a, 450, y + 10);
        y += step;
    }
    func_0021b820();
    func_0021c4f8(a);
}

void func_002231e0(JsWin *arg0) {
    func_0021b820();
    func_0021ccd0(arg0, 0xC);
    func_0021af38(arg0);
}

void func_00223218(JsWin *arg0) {
    func_0021b820();
    func_0021c780(arg0, 0x10, 0x48);
    func_0021cb00(arg0, 0x118, 0x6C, 9, 0x1E);
}

void func_00223260(JsWin *a0) {
    JsWin *objs[3];
    s32 *pa, *pb, *pc;
    s32 n, sel;
    JsWin *o;
    objs[0] = func_001f31a8(D_003F66E0, 50);
    if (!objs[0]) return;
    func_001f3e48(objs[0], a0);
    objs[1] = func_001f31a8(D_003F66B0, 50);
    if (!objs[1]) return;
    func_001f3e48(objs[1], objs[0]);
    objs[2] = func_001f31a8(D_003F6680, 50);
    if (!objs[2]) return;
    func_001f3e48(objs[2], objs[1]);
    pa = &D_006436C0;
    pb = &D_006436B8;
    if ((*pb / 4) * 4 < *pa * 4) {
        *pa = 0;
    }
    sel = *pa;
    n = *pb;
    if (n < sel * 4 + D_006436BC) D_006436BC = 0;
    o = objs[2];
    o->xca = *(u16 *)pb;
    o->xd8 = (n + 3) / 4;
    o->xda = *pa << 4;
    if (n < 4 || sel == o->xd8 - 1) o->xcc = (n - 1) % 4 + 1;
    else o->xcc = 4;
    o->xd2 = *(u16 *)&D_006436BC << 4;
}

void func_002233d8(JsWin *arg0) {
    if (func_001f42b8(arg0) != 0) {
        func_00223260(arg0);
    }
}

void func_00223418(void) {
    s32 i;
    for (i = 0; i < D_006436B8; i++) {
        if (func_00206fb8(D_006436A8[i]) == 0) {
            func_00207298(1);
            return;
        }
    }
    func_002072e0(1);
}

void func_002234a8(JsWin *a) {
    D_006436A0 = a;
}

void func_002234b8(void) {
    func_00222ba8();
    D_003F5C1C = D_006436B8 != 0;
}

void func_002234e8(void) {
    D_006436BC = 0;
    D_006436C0 = 0;
    D_006436C4 = 0;
}

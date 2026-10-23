/* Page 5's section 5 (D_003F5A00[5]; docs/modules.md "Session 42"),
 * 0x002210f8-0x00222ba8.  Opener func_00222b40 keeps the section's window in
 * D_00643660; set up func_00222b50 (D_003F5C2C = "not empty"), reset
 * func_00222b80.
 *
 * func_002210f8 lists the pages that have a record (D_00643668, D_00643674
 * of them; D_003F5C44 once all eight are there) from func_001ec538's flags:
 * page 1 has D_00643678 levels (flags 1-5), page 2 four (6-9), pages 3-7 one
 * flag each (10-14), page 8 the D_0064368C entries of flags 20-23
 * (D_00643680).  func_00222670 is the page list (titles: messages 0x30 + page,
 * func_00221390), each page a window from D_003F6568[page] drawing five rows
 * of func_001eb5f0(table, row) with three numbers each (func_001ee440 /
 * 458 / 470: most likely a time) into D_003E8E08 (messages 57 / 58, or one
 * number with 59 ... 64).  Not proved by a boot; most likely the records of
 * the mini games and fights. */
#include "common.h"
#include "data/bss_0064.h"
#include "data/pieces/D_00425BC8.h"
#include "data/pieces/D_003E8E08.h"
#include "menu/journal.h"

extern JsWin *D_00643660; /* src/data/bss_0064.c: s32 D_00643660 */
extern s32 D_003F5C2C;
extern s32 D_003F5C44;
extern s32 D_003F6360[];
extern u8 D_003F63C0[], D_003F63F0[], D_003F6420[], D_003F6450[], D_003F6480[];
extern u8 D_003F64B0[], D_003F64E0[], D_003F6510[], D_003F6540[];
u8 *D_003F6568[0xa] ALIGNED(8) = {
    D_003F63C0, D_003F63F0, D_003F6420, D_003F6450,
    D_003F6480, D_003F64B0, D_003F64E0, D_003F6510,
    D_003F6540, 0,
};
extern u8 D_003F6390[];
extern u8 D_003F6590[], D_003F65C0[], D_003F65F0[];
extern u16 D_003E9104;

void func_0011d768(s32);
s32 func_001eb5f0(s32, s32);
s32 func_001ec538(s32);
s32 func_001ec6f8(s32, s32);
s32 func_001ee440(s32);
s32 func_001ee458(s32);
s32 func_001ee470(s32);
void *func_001f31a8(void *, s32);
void func_001f3758(void *);
void func_001f3e48(void *, void *);
s32 func_001f42b8(void *);
s32 func_001f4390(void *);
s32 func_001f94f0(void *, s32, s32, s32, s32, s32, s32);
s32 func_001fd518(void *);
void func_001fd858(void *);
s32 func_001fe570(void *);
s32 func_001fe9a8(void *, s32, s32);
void func_00203788(void *, s32, s32, s32, u32);
void func_00206130(void *, s32, s32, s32, s32, u32);
void func_00207210(s32);
s32 func_00207250(s32);
void func_00207298(s32);
void func_002072e0(s32);
void func_00207428(void *, s32, s32);
void func_0021af38(void *);
s32 func_0021b800(s32);
void func_0021b820(void);
s32 func_0021b860(void *, s32, s32, s32, s32, s32);
void func_0021c4f8(void *);
void func_0021c780(void *, s32, s32);
void func_0021c9a0(void *, s32, s32);
void func_0021cb00(void *, s32, s32, s32, s32);
void func_0021cb88(void *, s32, s32, s32, s32);
void func_0021ccd0(void *, s32);

void func_002210f8(void) {
    s32 i, j;
    for (i = 0; i < 5 && func_001ec538(i + 1); i++);
    D_0064367C = 0;
    D_00643678 = i;
    for (i = 0; i < 4; i++) {
        if (func_001ec538(i + 6)) {
            D_0064367C = 4;
            break;
        }
    }
    D_0064368C = 0;
    for (i = 0; i < 4; i++) {
        if (func_001ec538(i + 20)) D_00643680[D_0064368C++] = i;
    }
    D_00643674 = 0;
    if (D_00643678) D_00643668[D_00643674++] = 1;
    if (D_0064367C) D_00643668[D_00643674++] = 2;
    if (func_001ec538(10)) D_00643668[D_00643674++] = 3;
    if (func_001ec538(11)) D_00643668[D_00643674++] = 4;
    if (func_001ec538(12)) D_00643668[D_00643674++] = 5;
    if (func_001ec538(13)) D_00643668[D_00643674++] = 6;
    if (func_001ec538(14)) D_00643668[D_00643674++] = 7;
    if (D_0064368C) D_00643668[D_00643674++] = 8;
    for (j = 0; j < D_00643674; j++) {
        if (!func_00207250(D_00643668[j])) {
            func_00207298(5);
            goto next;
        }
    }
    func_002072e0(5);
next:
    D_003F5C44 = D_00643674 == 8;
}

s32 func_00221390(s32 i) {
    return func_0021b800(i + 0x30);
}

void func_002213a8(s32 a0) {
    if (a0 <= 0) func_0021b800(48);
    else if (a0 < 6) func_0021b800(49);
    else if (a0 < 10) func_0021b800(50);
    else if (a0 < 15) func_0021b800(a0 + 41);
    else func_0021b800(56);
}

s32 func_00221428(s32 i) {
    return D_003F6360[i];
}

void func_00221440(JsWin *arg0) {
    if ((func_001f42b8(arg0) != 0) && (D_00425BC8->x8 & 0x4000)) {
        func_001f3758(arg0->xc);
        func_0011d768(3);
    }
    func_0021b820();
    func_0021ccd0(arg0, arg0->x24);
    func_0021af38(arg0);
}

void func_002214a8(JsWin *a0) {
    s32 i, j, y, r, k;
    S4_3e8e08 *d;
    func_0021b820();
    func_0021c9a0(a0, 16, 72);
    func_0021cb00(a0, 32, 108, 9, 30);
    func_0021cb00(a0, 280, 108, 9, 30);
    func_00206130(a0, 287, 94, 20, 2, 0x80202020);
    func_00206130(a0, 453, 94, 20, 2, 0x80202020);
    func_001f94f0(a0, 2, 380, 86, func_00221390(0), 15, 0x80461e00);
    d = ((S4_3e8e08 *)&D_003E8E08);
    y = 144;
    for (i = 0; i < 5; i = j) {
        r = func_001eb5f0(0, i);
        j = i + 1;
        d->a = j;
        if (r != -1) {
            d->b = func_001ee440(r);
            d->c = func_001ee458(r);
            d->d = func_001ee470(r);
            k = 57;
        } else k = 58;
        func_001f94f0(a0, 0, 287, y, func_0021b800(k), 15, 0x80461e00);
        y += 30;
    }
}

void func_00221648(void) {
    func_00207210(0);
}

void func_00221660(JsWin *a) {
    s32 i, n, y, id, msg;
    if (func_001f42b8(a)) {
        if (D_00425BC8->x8 & 0x4000) {
            func_001f3758(a);
            func_0011d768(3);
        } else {
            if (func_001fe9a8(a, 0, D_00643678)) {
                func_0011d768(1);
                a->xda = a->x24 << 4;
            }
            D_00643694 = a->x24;
        }
    }
    func_00203788(a, 372, 40, 486, 0x80C8C8C8);
    y = 144;
    func_0021b820();
    func_0021cb88(a, 176, 8, 320, 5);
    func_0021c9a0(a, 16, 72);
    func_0021cb00(a, 32, 108, 9, 30);
    func_0021cb00(a, 280, 108, 9, 30);
    n = D_00643694 + 1;
    for (i = 0; i < n; i++) {
        func_001f94f0(a, 0, 39, y, func_0021b800(i + 65), 15, 0x80461E00);
        y += 30;
    }
    func_00206130(a, 287, 94, 20, 2, 0x80202020);
    func_00206130(a, 453, 94, 20, 2, 0x80202020);
    func_001f94f0(a, 2, 380, 86, func_00221390(1), 15, 0x80461E00);
    id = (*(S4_3e8e08 *)&D_003E8E08).a = func_001eb5f0(D_00643694 + 15, 0);
    func_001f94f0(a, 0, 302, 146, func_0021b800(id != -1 ? 70 : 71), 15, 0x80461E00);
    func_0021b860(a, 378, 140, 0, 0, 39);
    y = 204;
    n = D_00643694 + 1;
    for (i = 0; i < 5; i++) {
        id = func_001eb5f0(n, i);
        msg = 58;
        (*(S4_3e8e08 *)&D_003E8E08).a = i + 1;
        if (id != -1) {
            (*(S4_3e8e08 *)&D_003E8E08).b = func_001ee440(id);
            (*(S4_3e8e08 *)&D_003E8E08).c = func_001ee458(id);
            (*(S4_3e8e08 *)&D_003E8E08).d = func_001ee470(id);
            msg = 57;
        }
        func_001f94f0(a, 0, 287, y, func_0021b800(msg), 15, 0x80461E00);
        y += 30;
    }
}

void func_00221980(void) {
    func_00207210(1);
}

void func_00221998(JsWin *a0) {
    s32 i, j, y, r, k, base;
    S4_3e8e08 *d;
    if (func_001f4390(a0)) {
        if (func_001fe9a8(a0, 0, D_0064367C)) {
            func_0011d768(1);
            a0->xda = (u16)a0->x24 << 4;
        }
        D_00643698 = a0->x24;
    }
    func_00203788(a0, 372, 40, 486, 0x80c8c8c8);
    func_0021b820();
    func_0021c9a0(a0, 16, 72);
    func_0021cb00(a0, 32, 108, 9, 30);
    func_0021cb00(a0, 280, 108, 9, 30);
    func_00206130(a0, 287, 94, 20, 2, 0x80202020);
    func_00206130(a0, 453, 94, 20, 2, 0x80202020);
    func_001f94f0(a0, 2, 380, 86, func_00221390(2), 15, 0x80461e00);
    func_001f94f0(a0, 0, 296, 144, func_0021b800(D_00643698 + 72), 15, 0x80461e00);
    y = 204;
    base = D_00643698 + 6;
    d = ((S4_3e8e08 *)&D_003E8E08);
    for (i = 0; i < 5; i = j) {
        r = func_001eb5f0(base, i);
        j = i + 1;
        d->a = j;
        if (r != -1) {
            d->b = func_001ee440(r);
            d->c = func_001ee458(r);
            d->d = func_001ee470(r);
            k = 57;
        } else k = 58;
        func_001f94f0(a0, 0, 287, y, func_0021b800(k), 15, 0x80461e00);
        y += 30;
    }
}

void func_00221be0(void) {
    func_00207210(2);
}

void func_00221bf8(JsWin *a0) {
    s32 i, j, y, r, k;
    S4_3e8e08 *d;
    func_0021b820();
    func_0021c9a0(a0, 16, 72);
    func_0021cb00(a0, 32, 108, 9, 30);
    func_0021cb00(a0, 280, 108, 9, 30);
    func_00206130(a0, 287, 94, 20, 2, 0x80202020);
    func_00206130(a0, 453, 94, 20, 2, 0x80202020);
    func_001f94f0(a0, 2, 380, 86, func_00221390(3), 15, 0x80461e00);
    d = ((S4_3e8e08 *)&D_003E8E08);
    y = 144;
    for (i = 0; i < 5; i = j) {
        r = func_001eb5f0(10, i);
        j = i + 1;
        d->a = j;
        if (r != -1) {
            d->b = r;
            k = 59;
        } else k = 60;
        func_001f94f0(a0, 0, 287, y, func_0021b800(k), 15, 0x80461e00);
        y += 30;
    }
}

void func_00221d68(void) {
    func_00207210(3);
}

void func_00221d80(JsWin *a0) {
    s32 i, j, y, r, k;
    S4_3e8e08 *d;
    func_0021b820();
    func_0021c9a0(a0, 16, 72);
    func_0021cb00(a0, 32, 108, 9, 30);
    func_0021cb00(a0, 280, 108, 9, 30);
    func_00206130(a0, 287, 94, 20, 2, 0x80202020);
    func_00206130(a0, 453, 94, 20, 2, 0x80202020);
    func_001f94f0(a0, 2, 380, 86, func_00221390(4), 15, 0x80461e00);
    d = ((S4_3e8e08 *)&D_003E8E08);
    y = 144;
    for (i = 0; i < 5; i = j) {
        r = func_001eb5f0(11, i);
        j = i + 1;
        d->a = j;
        if (r != -1) {
            d->b = r;
            k = 61;
        } else k = 62;
        func_001f94f0(a0, 0, 287, y, func_0021b800(k), 15, 0x80461e00);
        y += 30;
    }
}

void func_00221ef0(void) {
    func_00207210(4);
}

void func_00221f08(JsWin *a0) {
    s32 i, j, y, r, k;
    S4_3e8e08 *d;
    func_0021b820();
    func_0021c9a0(a0, 16, 72);
    func_0021cb00(a0, 32, 108, 9, 30);
    func_0021cb00(a0, 280, 108, 9, 30);
    func_00206130(a0, 287, 94, 20, 2, 0x80202020);
    func_00206130(a0, 453, 94, 20, 2, 0x80202020);
    func_001f94f0(a0, 2, 380, 86, func_00221390(5), 15, 0x80461e00);
    d = ((S4_3e8e08 *)&D_003E8E08);
    y = 144;
    for (i = 0; i < 5; i = j) {
        r = func_001eb5f0(12, i);
        j = i + 1;
        d->a = j;
        if (r != -1) {
            d->b = r;
            k = 63;
        } else k = 64;
        func_001f94f0(a0, 0, 287, y, func_0021b800(k), 15, 0x80461e00);
        y += 30;
    }
}

void func_00222078(void) {
    func_00207210(5);
}

void func_00222090(JsWin *a0) {
    s32 i, j, y, r, k;
    S4_3e8e08 *d;
    func_0021b820();
    func_0021c9a0(a0, 16, 72);
    func_0021cb00(a0, 32, 108, 9, 30);
    func_0021cb00(a0, 280, 108, 9, 30);
    func_00206130(a0, 287, 94, 20, 2, 0x80202020);
    func_00206130(a0, 453, 94, 20, 2, 0x80202020);
    func_001f94f0(a0, 2, 380, 86, func_00221390(6), 15, 0x80461e00);
    d = ((S4_3e8e08 *)&D_003E8E08);
    y = 144;
    for (i = 0; i < 5; i = j) {
        r = func_001eb5f0(13, i);
        j = i + 1;
        d->a = j;
        if (r != -1) {
            d->b = func_001ee440(r);
            d->c = func_001ee458(r);
            d->d = func_001ee470(r);
            k = 57;
        } else k = 58;
        func_001f94f0(a0, 0, 287, y, func_0021b800(k), 15, 0x80461e00);
        y += 30;
    }
}

void func_00222230(void) {
    func_00207210(6);
}

void func_00222248(JsWin *a0) {
    s32 i, j, y, r, k;
    S4_3e8e08 *d;
    func_0021b820();
    func_0021c9a0(a0, 16, 72);
    func_0021cb00(a0, 32, 108, 9, 30);
    func_0021cb00(a0, 280, 108, 9, 30);
    func_00206130(a0, 287, 94, 20, 2, 0x80202020);
    func_00206130(a0, 453, 94, 20, 2, 0x80202020);
    func_001f94f0(a0, 2, 380, 86, func_00221390(7), 15, 0x80461e00);
    d = ((S4_3e8e08 *)&D_003E8E08);
    y = 144;
    for (i = 0; i < 5; i = j) {
        r = func_001eb5f0(14, i);
        j = i + 1;
        d->a = j;
        if (r != -1) {
            d->b = func_001ee440(r);
            d->c = func_001ee458(r);
            d->d = func_001ee470(r);
            k = 57;
        } else k = 58;
        func_001f94f0(a0, 0, 287, y, func_0021b800(k), 15, 0x80461e00);
        y += 30;
    }
}

void func_002223e8(void) {
    func_00207210(7);
}

void func_00222400(JsWin *a0) {
    s32 i, j, y, r, k, base;
    S4_3e8e08 *d;
    if (func_001f4390(a0)) {
        if (func_001fe9a8(a0, 0, D_0064368C)) {
            func_0011d768(1);
            a0->xda = (u16)a0->x24 << 4;
        }
        D_0064369C = a0->x24;
    }
    func_00203788(a0, 372, 40, 486, 0x80c8c8c8);
    func_0021b820();
    func_0021c9a0(a0, 16, 72);
    func_0021cb00(a0, 32, 108, 9, 30);
    func_0021cb00(a0, 280, 108, 9, 30);
    func_00206130(a0, 287, 94, 20, 2, 0x80202020);
    func_00206130(a0, 453, 94, 20, 2, 0x80202020);
    func_001f94f0(a0, 2, 380, 86, func_00221390(8), 15, 0x80461e00);
    func_001f94f0(a0, 0, 296, 144, func_0021b800(D_00643680[D_0064369C] + 76), 15, 0x80461e00);
    y = 204;
    base = D_00643680[D_0064369C];
    d = ((S4_3e8e08 *)&D_003E8E08);
    for (i = 0; i < 5; i = j) {
        r = func_001ec6f8(base, i);
        j = i + 1;
        d->a = j;
        if (r != -1) {
            d->b = func_001ee440(r);
            d->c = func_001ee458(r);
            d->d = func_001ee470(r);
            k = 57;
        } else k = 58;
        func_001f94f0(a0, 0, 287, y, func_0021b800(k), 15, 0x80461e00);
        y += 30;
    }
}

void func_00222658(void) {
    func_00207210(8);
}

/* The store to the page window's +0x24 needs a union of s32 and u16 (its
 * alias set): with JsWin's plain s32 one load moves (8 words). */
typedef struct { u8 pad[0x24]; union { s32 i; u16 h; } x24; } JsWin24;
void func_00222670(JsWin *a0) {
    JsWin *objs[2];
    s32 s, i, y, step;
    if (func_001f42b8(a0)) {
        if (D_00425BC8->x8 & 0x4000) {
            func_001f3758(D_00643660);
            func_0011d768(3);
        } else {
            func_001fd858(a0);
            D_00643690 = func_001fd518(a0);
            if (func_001fe570(a0)) {
                func_001f3758(D_00643660->x10);
                s = D_00643668[D_00643690];
                objs[0] = func_001f31a8(D_003F6568[s], 50);
                if (objs[0]) {
                    func_001f3e48(objs[0], a0);
                    objs[0]->xa0 = D_003E9104;
                    if (s == 1) {
                        D_00643694 = 0;
                        objs[0]->xd8 = *(u16 *)&D_00643678;
                        objs[0]->xda = *(u16 *)&D_00643694 << 4;
                    } else {
                    if (s == 2) {
                        objs[0]->xd8 = *(u16 *)&D_0064367C;
                        D_00643698 = 0;
                        objs[0]->xda = *(u16 *)&D_00643698 << 4;
                    } else if (s == 8) {
                        objs[0]->xd8 = *(u16 *)&D_0064368C;
                        D_0064369C = 0;
                        objs[0]->xda = *(u16 *)&D_0064369C << 4;
                    }
                    objs[1] = func_001f31a8(D_003F6390, 50);
                    if (objs[1]) {
                        func_001f3e48(objs[1], objs[0]);
                        ((JsWin24 *)objs[1])->x24.i = func_00221428(s);
                        objs[1]->xa0 = objs[0]->xa0;
                    }
                    }
                }
            }
        }
    }
    step = a0->xc4 >> 4;
    y = 116;
    for (i = 0; i < D_00643674; ) {
        s = D_00643668[i];
        i++;
        func_001f94f0(a0, 0, 322, y, func_00221390(s), 15, 0x80461e00);
        if (!func_00207250(s)) func_00207428(a0, 450, y + 10);
        y += step;
    }
    func_0021b820();
    func_0021c4f8(a0);
}

void func_002228f0(JsWin *arg0) {
    if ((func_001f42b8(arg0) != 0) && (D_00425BC8->x8 & 0x4000)) {
        func_001f3758(D_00643660);
        func_0011d768(3);
    }
    func_0021b820();
    func_0021ccd0(arg0, 4);
    func_0021af38(arg0);
}

void func_00222958(JsWin *arg0) {
    func_0021b820();
    func_0021c780(arg0, 0x10, 0x48);
    func_0021cb00(arg0, 0x118, 0x6C, 9, 0x1E);
}

void func_002229a0(JsWin *a0) {
    JsWin *b[3];
    b[0] = func_001f31a8(D_003F65F0, 50);
    if (b[0] == 0) return;
    func_001f3e48(b[0], a0);
    b[1] = func_001f31a8(D_003F65C0, 50);
    if (b[1] == 0) return;
    func_001f3e48(b[1], b[0]);
    b[2] = func_001f31a8(D_003F6590, 50);
    if (b[2] == 0) return;
    func_001f3e48(b[2], b[1]);
    b[2]->xcc = D_00643674;
    if (D_00643690 >= D_00643674) {
        D_00643690 = D_00643674 - 1;
    }
    b[2]->xd2 = (u16)D_00643690 * 16;
}

void func_00222a70(JsWin *arg0) {
    if (func_001f42b8(arg0) != 0) {
        func_002229a0(arg0);
    }
}

void func_00222ab0(void) {
    s32 i;
    for (i = 0; i < D_00643674; i++) {
        if (!func_00207250(D_00643668[i])) {
            func_00207298(5);
            return;
        }
    }
    func_002072e0(5);
}

void func_00222b40(JsWin *a) {
    D_00643660 = a;
}

void func_00222b50(void) {
    func_002210f8();
    D_003F5C2C = D_00643674 != 0;
}

void func_00222b80(void) {
    D_00643690 = 0;
    D_00643694 = 0;
    D_00643698 = 0;
    D_0064369C = 0;
}

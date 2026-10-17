#include "common.h"
typedef struct { s32 a, b, c, d; } S4;
extern S4 D_003E8E08;
void func_0021b820(void);
void func_0021c9a0(void *, s32, s32);
void func_0021cb00(void *, s32, s32, s32, s32);
void func_00206130(void *, s32, s32, s32, s32, s32);
s32 func_00221390(s32);
s32 func_001f94f0(void *, s32, s32, s32, s32, s32, s32);
s32 func_001eb5f0(s32, s32);
s32 func_001ee440(s32);
s32 func_001ee458(s32);
s32 func_001ee470(s32);
s32 func_0021b800(s32);

typedef struct { u8 pad[0x24]; union { s32 i; u16 h; } x24; u8 p1[0xa0 - 0x28]; f32 xa0; u8 p2[0xc4 - 0xa4]; u16 xc4; u8 p3[0xd8 - 0xc6]; u16 xd8; u16 xda; } O98;
extern s32 D_0064367C;
extern s32 D_00643698;
s32 func_001f4390(void);
s32 func_001fe9a8(void *, s32, s32);
void func_0011d768(s32);
void func_00203788(void *, s32, s32, s32, s32);
extern s32 D_0064368C;
extern s32 D_0064369C;
extern u8 D_00643680[];
s32 func_001ec6f8(s32, s32);
typedef struct { u8 pad[8]; s32 x8; } F8;
typedef struct { u8 pad[0x10]; s32 x10; } P10;
extern F8 *D_00425BC8;
extern P10 *D_00643660;
extern u8 D_00643668[];
extern s32 D_00643674;
extern s32 D_00643678;
extern s32 D_00643690;
extern s32 D_00643694;
extern u16 D_003E9104;
extern s32 D_003F6568[];
extern u8 D_003F6390[];
s32 func_001f42b8(void);
void func_001f3758(s32);
void func_001fd858(void *);
s32 func_001fd518(void *);
s32 func_001fe570(void *);
O98 *func_001f31a8(s32, s32);
void func_001f3e48(void *, void *);
s32 func_00221428(s32);
s32 func_00207250(s32);
void func_00207428(void *, s32, s32);
void func_0021c4f8(void *);


void func_002214a8(void *a0) {
    s32 i, j, y, r, k;
    S4 *d;
    func_0021b820();
    func_0021c9a0(a0, 16, 72);
    func_0021cb00(a0, 32, 108, 9, 30);
    func_0021cb00(a0, 280, 108, 9, 30);
    func_00206130(a0, 287, 94, 20, 2, 0x80202020);
    func_00206130(a0, 453, 94, 20, 2, 0x80202020);
    func_001f94f0(a0, 2, 380, 86, func_00221390(0), 15, 0x80461e00);
    d = &D_003E8E08;
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

void func_00221bf8(void *a0) {
    s32 i, j, y, r, k;
    S4 *d;
    func_0021b820();
    func_0021c9a0(a0, 16, 72);
    func_0021cb00(a0, 32, 108, 9, 30);
    func_0021cb00(a0, 280, 108, 9, 30);
    func_00206130(a0, 287, 94, 20, 2, 0x80202020);
    func_00206130(a0, 453, 94, 20, 2, 0x80202020);
    func_001f94f0(a0, 2, 380, 86, func_00221390(3), 15, 0x80461e00);
    d = &D_003E8E08;
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

void func_00221d80(void *a0) {
    s32 i, j, y, r, k;
    S4 *d;
    func_0021b820();
    func_0021c9a0(a0, 16, 72);
    func_0021cb00(a0, 32, 108, 9, 30);
    func_0021cb00(a0, 280, 108, 9, 30);
    func_00206130(a0, 287, 94, 20, 2, 0x80202020);
    func_00206130(a0, 453, 94, 20, 2, 0x80202020);
    func_001f94f0(a0, 2, 380, 86, func_00221390(4), 15, 0x80461e00);
    d = &D_003E8E08;
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

void func_00221f08(void *a0) {
    s32 i, j, y, r, k;
    S4 *d;
    func_0021b820();
    func_0021c9a0(a0, 16, 72);
    func_0021cb00(a0, 32, 108, 9, 30);
    func_0021cb00(a0, 280, 108, 9, 30);
    func_00206130(a0, 287, 94, 20, 2, 0x80202020);
    func_00206130(a0, 453, 94, 20, 2, 0x80202020);
    func_001f94f0(a0, 2, 380, 86, func_00221390(5), 15, 0x80461e00);
    d = &D_003E8E08;
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

void func_00221998(O98 *a0) {
    s32 i, j, y, r, k, base;
    S4 *d;
    if (func_001f4390()) {
        if (func_001fe9a8(a0, 0, D_0064367C)) {
            func_0011d768(1);
            a0->xda = a0->x24.h << 4;
        }
        D_00643698 = a0->x24.i;
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
    d = &D_003E8E08;
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

void func_00222090(void *a0) {
    s32 i, j, y, r, k;
    S4 *d;
    func_0021b820();
    func_0021c9a0(a0, 16, 72);
    func_0021cb00(a0, 32, 108, 9, 30);
    func_0021cb00(a0, 280, 108, 9, 30);
    func_00206130(a0, 287, 94, 20, 2, 0x80202020);
    func_00206130(a0, 453, 94, 20, 2, 0x80202020);
    func_001f94f0(a0, 2, 380, 86, func_00221390(6), 15, 0x80461e00);
    d = &D_003E8E08;
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


void func_00222248(void *a0) {
    s32 i, j, y, r, k;
    S4 *d;
    func_0021b820();
    func_0021c9a0(a0, 16, 72);
    func_0021cb00(a0, 32, 108, 9, 30);
    func_0021cb00(a0, 280, 108, 9, 30);
    func_00206130(a0, 287, 94, 20, 2, 0x80202020);
    func_00206130(a0, 453, 94, 20, 2, 0x80202020);
    func_001f94f0(a0, 2, 380, 86, func_00221390(7), 15, 0x80461e00);
    d = &D_003E8E08;
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

void func_00222400(O98 *a0) {
    s32 i, j, y, r, k, base;
    S4 *d;
    if (func_001f4390()) {
        if (func_001fe9a8(a0, 0, D_0064368C)) {
            func_0011d768(1);
            a0->xda = a0->x24.h << 4;
        }
        D_0064369C = a0->x24.i;
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
    d = &D_003E8E08;
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

void func_00222670(O98 *a0) {
    O98 *objs[2];
    s32 s, i, y, step;
    if (func_001f42b8()) {
        if (D_00425BC8->x8 & 0x4000) {
            func_001f3758((s32)D_00643660);
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
                    objs[1] = func_001f31a8((s32)D_003F6390, 50);
                    if (objs[1]) {
                        func_001f3e48(objs[1], objs[0]);
                        objs[1]->x24.i = func_00221428(s);
                        objs[1]->xa0 = objs[0]->xa0;
                    }
                    }
                }
            }
        }
    }
    step = (s16)a0->xc4 >> 4;
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

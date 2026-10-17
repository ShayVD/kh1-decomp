#include "common.h"
typedef struct Ob {
    u8 pad[0x24];
    s32 x24;
    u8 pad28[0xA0 - 0x28];
    f32 xa0;
    u8 pada4[0xC4 - 0xA4];
    s16 xc4;
    u8 padc6[0xCC - 0xC6];
    s16 xcc;
    s16 xce;
    u8 padd0[0xD8 - 0xD0];
    s16 xd8;
    s16 xda;
} Ob;
typedef struct { u8 pad[4]; u32 x4; s32 x8; u8 padc[4]; u32 x10; } Cfg;
typedef struct { u8 pad[16]; void *x10; } P10;
extern Cfg *D_00425BC8;
extern P10 *D_006433F0;
extern s32 D_00643418;
extern s32 D_0064341C;
extern s32 D_00643420;
extern s32 D_00643424;
extern u8 D_006433F8[];
extern u8 D_003F60F0[];
extern u16 D_003E9104;
extern s32 D_003F3518;
s32 func_001f42b8(void *);
s32 func_001f3758(void *);
void func_0011d768(s32);
void func_001fd858(void *);
s32 func_001fd518(void *);
s32 func_001fd668(void *);
s32 func_001fe570(void *);
Ob *func_001f31a8(u8 *, s32);
void func_001f3e48(Ob *, void *);
s32 func_0021fd88(s32);
s32 func_0021fd60(s32);
s32 func_001c2df0(s32, s32);
s32 func_0010eb78(s32);
void func_00203788(void *, s32, s32, s32, u32);
s32 func_001f94f0(void *, s32, s32, s32, s32, s32, s32);
s32 func_00206ee8(s32);
void func_00207428(void *, s32, s32);
void func_0021b820(void);
void func_0021c4f8(void *);
void func_0021ff68(Ob *a) {
    s32 i, j, y, step, id;
    Ob *o;
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
                    k = func_0010eb78(func_001c2df0(D_003F3518, func_0021fd88(id)));
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

s32 func_00207250(s32);
void func_00207298(s32);
void func_002072e0(s32);
extern s32 D_00643678;
extern s32 D_0064367C;
extern u8 D_00643680[];
extern s32 D_0064368C;
extern s32 D_00643674;
extern u8 D_00643668[];
extern s32 D_003F5C44;
s32 func_001ec538(s32);

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

extern s32 D_00643694;
typedef struct { s32 a, b, c, d; } S4;
extern S4 D_003E8E08;
s32 func_001fe9a8(void *, s32, s32);
void func_0021cb88(void *, s32, s32, s32, s32);
void func_0021c9a0(void *, s32, s32);
void func_0021cb00(void *, s32, s32, s32, s32);
void func_00206130(void *, s32, s32, s32, s32, s32);
s32 func_00221390(s32);
s32 func_001eb5f0(s32, s32);
s32 func_001ee440(s32);
s32 func_001ee458(s32);
s32 func_001ee470(s32);
s32 func_0021b860(void *, s32, s32, s32, s32, s32);

void func_00221660(Ob *a) {
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
    id = D_003E8E08.a = func_001eb5f0(D_00643694 + 15, 0);
    func_001f94f0(a, 0, 302, 146, func_0021b800(id != -1 ? 70 : 71), 15, 0x80461E00);
    func_0021b860(a, 378, 140, 0, 0, 39);
    y = 204;
    n = D_00643694 + 1;
    for (i = 0; i < 5; i++) {
        id = func_001eb5f0(n, i);
        msg = 58;
        D_003E8E08.a = i + 1;
        if (id != -1) {
            D_003E8E08.b = func_001ee440(id);
            D_003E8E08.c = func_001ee458(id);
            D_003E8E08.d = func_001ee470(id);
            msg = 57;
        }
        func_001f94f0(a, 0, 287, y, func_0021b800(msg), 15, 0x80461E00);
        y += 30;
    }
}

extern u32 D_003E3D68;
extern s32 D_00643708;
extern s32 D_0064370C;
extern u8 D_00643770[];
extern s32 D_00643760[];
extern s32 D_00643780[];
void func_0020bd18(void *, s32);
void func_001f3d58(void *, s32);
s32 func_001ee5f0(s32);
void func_00207870(void *, s32, s32, s32, s32, s32, s32);

void func_00223a90(void *a) {
    s32 buf[4];
    s32 i, j, n, sel, y, v, t;
    n = 0;
    for (i = 1; i < D_003E3D68; i++) {
        if (i != D_00643708 + 1) buf[n++] = D_00643770[i];
        else j = i;
    }
    if (func_001f42b8(a)) {
        if (D_00425BC8->x8 & 0x4000) {
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

extern P10 *D_006436A0;
extern s32 D_006436B8;
extern s32 D_006436BC;
extern s32 D_006436C0;
extern s32 D_006436C4;
extern u8 D_006436A8[];
extern u8 D_003F6650[];
extern s32 D_003F3520;
s32 func_00222cb0(s32);
s32 func_00222c98(s32);
s32 func_00206fb8(s32);

void func_00222e90(Ob *a) {
    s32 i, j, y, step, id;
    Ob *o;
    if (func_001f42b8(a)) {
        if (D_00425BC8->x8 & 0x4000) {
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
                    k = func_0010eb78(func_001c2df0(D_003F3520, func_00222cb0(id)));
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

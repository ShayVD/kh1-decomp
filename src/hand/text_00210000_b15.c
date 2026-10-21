#include "common.h"
#include "data/bss_0064.h"
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
extern P10 *D_006433F0; /* src/data/bss_0064.c: s32 D_006433F0 */
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

extern P10 *D_006436A0; /* src/data/bss_0064.c: s32 D_006436A0 */
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

extern s32 D_00647FB4, D_00647FC8, D_00647FD8, D_00647FD4, D_00647FB0, D_00647FC4;
typedef struct { s32 x0, x4; } S2;
extern S2 D_00647FE8;
extern void (*D_00648034)(s32);
extern s32 D_00425C10, D_00425C14, D_00425C18, D_00425C1C, D_00425C20;
extern s32 D_00425C28[][4], D_00425C48[][4], D_00425C68[][4], D_00425C88[][4];
s32 func_002716d8(s32, s32, s32 *, s32 *, s32 *);
s32 func_002715a0(s32, s32, s32 *);

void func_00234f80(void) {
    switch (D_00647FB4) {
    case 0:
        func_002716d8(D_00425C10, D_00425C14, &D_00425C18, &D_00425C1C, &D_00425C20);
        D_00647FB4++;
        return;
    case 1:
        if (func_002715a0(1, 0, &D_00647FC8)) D_00647FB4++;
        return;
    case 2:
        if (D_00425C18 == 3) {
            D_00425C28[D_00425C10][D_00425C14] = 3;
        } else {
            switch (D_00647FC8) {
            case 0:
                D_00647FE8.x4 = 0;
                D_00425C28[D_00425C10][D_00425C14] = 0;
                break;
            case -1:
                D_00647FE8.x4 = 0;
                D_00425C28[D_00425C10][D_00425C14] = 1;
                D_00425C48[D_00425C10][D_00425C14] = 1;
                D_00425C68[D_00425C10][D_00425C14] = 1;
                break;
            case -2:
                D_00647FE8.x4 = 0;
                D_00425C28[D_00425C10][D_00425C14] = 2;
                D_00425C48[D_00425C10][D_00425C14] = 1;
                D_00425C68[D_00425C10][D_00425C14] = 1;
                break;
            default:
                D_00425C28[D_00425C10][D_00425C14] = 3;
                if (!D_00647FE8.x4) {
                    D_00425C48[D_00425C10][D_00425C14] = 1;
                    D_00425C88[D_00425C10][D_00425C14] = 1;
                }
                D_00647FE8.x4 = 1;
                break;
            }
        }
        D_00647FB0 = 0;
        D_00647FD8 = D_00647FD4;
        if (D_00648034) D_00648034(D_00647FC4);
        break;
    }
}

/* needs make: uses rodata */
extern s32 D_00647FB4, D_00647FC8, D_00647FD8, D_00647FD4, D_00647FB0, D_00647FC4;
extern s32 D_00648008, D_00648020, D_00648028, D_0064802C, D_00648030;
extern void (*D_00648034)(s32);
extern s32 D_00425C10, D_00425C14;
s32 func_00270f00(s32, s32, s32, s32);
s32 func_002713b0(s32, s32, s32);
s32 func_00271070(s32);
s32 func_002715a0(s32, s32, s32 *);

void func_00235ab0(void) {
    s32 r, q;
    switch (D_00647FB4) {
    case 0:
        func_00270f00(D_00425C10, D_00425C14, D_00648020, 515);
        D_00647FB4++;
        break;
    case 1:
        if (func_002715a0(1, 0, &D_00647FC8)) D_00647FB4++;
        break;
    case 2:
        r = D_00647FC8;
        if (r >= 0) {
            D_00648030 = r;
            D_00647FB4++;
            break;
        }
        if (r == -2) { D_00648008 = 1; goto tail; }
        else if (r == -3) { D_00648008 = 2; goto tail; }
        else if (r == -4) { D_00648008 = 3; goto tail; }
        else if (r == -5) { D_00648008 = 4; goto tail; }
        else if (r == -7) { D_00648008 = 5; goto tail; }
        else { D_00648008 = 7; goto tail; }
    case 3:
        func_002713b0(D_00648030, D_00648028, D_0064802C);
        D_00647FB4++;
        break;
    case 4:
        if (func_002715a0(1, 0, &D_00647FC8)) D_00647FB4++;
        break;
    case 5:
        q = D_00647FC8;
        if (q >= 0) {
            if (q == D_0064802C) D_00648008 = 0;
            else D_00648008 = 6;
        }
        else if (q == -2) D_00648008 = 1;
        else if (q == -3) D_00648008 = 2;
        else if (q == -4) D_00648008 = 5;
        else if (q == -5) D_00648008 = 4;
        else if (q == -8) D_00648008 = 6;
        else D_00648008 = 7;
        D_00647FB4++;
        break;
    case 6:
        func_00271070(D_00648030);
        D_00647FB4++;
        break;
    case 7:
        if (func_002715a0(1, 0, &D_00647FC8)) {
        tail:
            D_00647FB0 = 0;
            D_00647FD8 = D_00647FD4;
            if (D_00648034) D_00648034(D_00647FC4);
        }
        break;
    }
}

extern s32 D_00647FB4, D_00647FC8, D_00647FD8, D_00647FD4, D_00647FB0, D_00647FC4;
extern s32 D_00648010, D_00648020, D_00648028, D_0064802C, D_00648030;
extern void (*D_00648034)(s32);
extern s32 D_00425C10, D_00425C14;
s32 func_00270f00(s32, s32, s32, s32);
s32 func_00271290(s32, s32, s32);
s32 func_00271070(s32);
s32 func_002715a0(s32, s32, s32 *);

void func_00235ee8(void) {
    s32 r, q;
    switch (D_00647FB4) {
    case 0:
        func_00270f00(D_00425C10, D_00425C14, D_00648020, 1);
        D_00647FB4++;
        break;
    case 1:
        if (func_002715a0(1, 0, &D_00647FC8)) D_00647FB4++;
        break;
    case 2:
        r = D_00647FC8;
        if (r >= 0) {
            D_00648030 = r;
            D_00647FB4++;
            break;
        }
        if (r == -2) { D_00648010 = 1; goto tail; }
        else if (r == -3) { D_00648010 = 2; goto tail; }
        else if (r == -4) { D_00648010 = 3; goto tail; }
        else if (r == -5) { D_00648010 = 4; goto tail; }
        else if (r == -7) { D_00648010 = 5; goto tail; }
        else { D_00648010 = 7; goto tail; }
    case 3:
        func_00271290(D_00648030, D_00648028, D_0064802C);
        D_00647FB4++;
        break;
    case 4:
        if (func_002715a0(1, 0, &D_00647FC8)) D_00647FB4++;
        break;
    case 5:
        q = D_00647FC8;
        if (q >= 0) {
            if (q == D_0064802C) D_00648010 = 0;
            else D_00648010 = 6;
        }
        else if (q == -2) D_00648010 = 1;
        else if (q == -3) D_00648010 = 6;
        else if (q == -4) D_00648010 = 5;
        else if (q == -5) D_00648010 = 4;
        else D_00648010 = 7;
        D_00647FB4++;
        break;
    case 6:
        func_00271070(D_00648030);
        D_00647FB4++;
        break;
    case 7:
        if (func_002715a0(1, 0, &D_00647FC8)) {
        tail:
            D_00647FB0 = 0;
            D_00647FD8 = D_00647FD4;
            if (D_00648034) D_00648034(D_00647FC4);
        }
        break;
    }
}


typedef struct { u8 pad[0xD2]; s16 xd2; u8 padd4[0xDA - 0xD4]; s16 xda; } ObC;
extern s32 D_006469B0;
extern s32 D_006469B4;
extern s32 D_003F73A4;
extern u8 D_003F7350[];
extern u8 D_003F7320[];
extern u8 D_003F72E0[];
extern u8 D_003F72B0[];
extern u8 D_003F7280[];
extern u8 D_003F7250[];
void func_001f36b8(void *);
void func_001f3e90(void *, void *);
void func_001f3e20(void *, void *);
void func_00205938(void *, s32);
void func_002193e0(s32);
void func_00219418(s32);
void func_00219320(s32);
void func_00219370(s32);
void func_002193a8(s32);
s32 func_002193b8(void);
s32 func_002193f0(void);
s32 func_002192f8(void);
s32 func_00219348(void);
s32 func_00219380(void);
ObC *func_001f3520(u8 *, s32);
void func_0020be10(s32);

void func_0022cde8(ObC *a) {
    ObC *o;
    s32 k;
    if (func_001f42b8(a)) {
        k = D_006469B0 < D_006469B4 ? 11 : 12;
        switch (D_006469B0) {
        case 0:
            func_001f36b8(a);
            func_0020be10(16);
            func_002193e0(0);
            func_00219418(1);
            func_00219320(0);
            func_00219370(0);
            func_002193a8(0);
            break;
        case 1:
            if (!(o = func_001f3520(D_003F7350, k))) break;
            func_001f3e90(a, o);
            func_001f3e20(o, a);
            o->xda = func_002193b8() << 4;
            break;
        case 2:
            if (!(o = (ObC *)func_001f31a8(D_003F7320, k))) break;
            func_001f3e90(a, o);
            func_001f3e20(o, a);
            o->xd2 = func_002193f0() << 4;
            break;
        case 3:
            if (!(o = (ObC *)func_001f31a8(D_003F72E0, k))) break;
            func_001f3e90(a, o);
            func_001f3e20(o, a);
            o->xd2 = func_002192f8() << 4;
            break;
        case 4:
            if (!(o = func_001f3520(D_003F72B0, k))) break;
            func_001f3e90(a, o);
            func_001f3e20(o, a);
            o->xda = func_00219348() << 4;
            break;
        case 5:
            if (!(o = func_001f3520(D_003F7280, k))) break;
            func_001f3e90(a, o);
            func_001f3e20(o, a);
            o->xda = func_00219380() << 4;
            break;
        case 6:
            if (!(o = func_001f3520(D_003F7250, k))) break;
            func_001f3e90(a, o);
            func_001f3e20(o, a);
            break;
        case 7:
            func_001f36b8(a);
            func_0020be10(16);
            D_003F73A4 = 1;
            break;
        }
    }
    func_00205938(a, 0x70000000);
}

typedef struct { u32 a; s32 b; u32 c; } Rec;
extern Cfg D_002C5AD0;
extern Cfg D_00647710;
extern s32 D_00647780;
extern Rec *D_00647784; /* src/data/bss_0064.c: s32 D_00647784 */
extern s32 D_00647788;
extern s32 D_0064778C;
extern Rec *D_00647790; /* src/data/bss_0064.c: s32 D_00647790 */
extern s32 D_00647794;
extern s32 D_00647798;
extern u8 *D_0064779C; /* src/data/bss_0064.c: s32 D_0064779C */
s32 D_006477A0 ALIGNED(16);
extern f32 D_006477A4;
extern f32 D_002BBDFC;

void func_002336f8(void) {
    Rec *p;
    switch (D_00647780) {
    case 0:
        break;
    case 1:
        if (--D_00647788) {
            D_00647784->a = D_002C5AD0.x4;
            D_00647784->b = D_002C5AD0.x8;
            D_00647784->c = D_002C5AD0.x10;
            D_00647784++;
        } else {
            D_00647780 = 0;
        }
        break;
    }
    switch (D_0064778C) {
    case 0:
        break;
    case 1:
        if (--D_00647794) {
            D_00425BC8 = &D_00647710;
            D_00647710.x4 = D_00647790->a;
            D_00647710.x8 = D_00647790->b;
            D_00647710.x10 = D_00647790->c;
            D_00647790++;
        } else {
            D_0064778C = 0;
            D_00425BC8 = &D_002C5AD0;
        }
        break;
    }
    switch (D_00647798) {
    case 1:
        D_00425BC8 = &D_00647710;
        switch (*D_0064779C) {
        case 0:
            D_00647710.x4 = 0x10000010;
            D_00647710.x8 = 0x10000010;
            D_00647710.x10 = 0x10000010;
            D_006477A0 = D_0064779C[1];
            D_0064779C += 2;
            if (D_006477A0) D_00647798 = 2;
            break;
        case 1:
            D_00647710.x4 = 0x40000040;
            D_00647710.x8 = 0x40000040;
            D_00647710.x10 = 0x40000040;
            D_006477A0 = D_0064779C[1];
            D_0064779C += 2;
            if (D_006477A0) D_00647798 = 2;
            break;
        case 2:
            D_00647710.x4 = 0x80000080;
            D_00647710.x8 = 0x80000080;
            D_00647710.x10 = 0x80000080;
            D_006477A0 = D_0064779C[1];
            D_0064779C += 2;
            if (D_006477A0) D_00647798 = 2;
            break;
        case 3:
            D_00647710.x4 = 0x20000020;
            D_00647710.x8 = 0x20000020;
            D_00647710.x10 = 0x20000020;
            D_006477A0 = D_0064779C[1];
            D_0064779C += 2;
            if (D_006477A0) D_00647798 = 2;
            break;
        case 4:
            D_00647710.x4 = 0x2000;
            D_00647710.x8 = 0x2000;
            D_00647710.x10 = 0x2000;
            D_006477A0 = D_0064779C[1];
            D_0064779C += 2;
            if (D_006477A0) D_00647798 = 2;
            break;
        case 5:
            D_00647710.x4 = 0x4000;
            D_00647710.x8 = 0x4000;
            D_00647710.x10 = 0x4000;
            D_006477A0 = D_0064779C[1];
            D_0064779C += 2;
            if (D_006477A0) D_00647798 = 2;
            break;
        case 6:
            D_006477A0 = D_0064779C[1];
            D_0064779C += 2;
            if (D_006477A0) D_00647798 = 2;
            break;
        case 7:
            D_00647798 = 0;
            D_00425BC8 = &D_002C5AD0;
            break;
        }
        break;
    case 2:
        D_00425BC8 = &D_00647710;
        D_00647710.x4 = 0;
        D_00647710.x8 = 0;
        D_00647710.x10 = 0;
        if (--D_006477A0 <= 0) D_00647798 = 1;
        break;
    case 0:
        break;
    }
    if (D_00425BC8->x4) D_006477A4 = 0.0f;
    else D_006477A4 += D_002BBDFC;
}

/* Split out of the func_0022cde8 and func_00233168 layout entries. */
extern s32 D_003F34A4;
s32 func_001f40c8(void);
void func_001f82b0(void);
void func_0020b998(void);
s32 func_0022d038(void) {
    if (func_001f40c8()) {
        func_001f82b0();
        func_0020b998();
        return 0;
    }
    D_003F34A4 = 0;
    return 4;
}


extern s32 D_00425BC0[];
void D_00F20000(s32, s32);
void func_001205f0(s32, void *);
void func_002335d8(s32 i) {
    func_001205f0(D_00425BC0[i], D_00F20000);
    D_00F20000(0, 0);
}

/* D_00425BC0 stays extern: func_002335d8 indexes it with i, and D_00425BC4 (named by
 * text_001d0000.c) is its next entry, so the table is longer than its extent; floating
 * it alone hung the SHIFT_FLOAT build at boot (session 17). */
#include "data/data_003F.h"
#include "data/data_0042.h"
#include "data/data_003E.h"
#include "data/pieces/D_002BBDFC.h"
#include "data/pieces/D_00425C10.h"
#include "data/pieces/D_00425C14.h"

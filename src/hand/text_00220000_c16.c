#include "common.h"

typedef struct {
    s32 magic;
    s32 ver;
    s32 x8;
    s32 xC;
    s32 x10;
    char name[36];
    s32 x38;
} Save3C;

typedef struct { s32 a, b, c, d; } S4;
extern S4 D_003E8E08;
typedef struct O98 {
    u8 pad[0xc];
    struct O98 *xc;
    s32 x10;
    u8 pad14[0x24 - 0x14];
    union { s32 i; u16 h; } x24;
    u8 p0[0x8c - 0x28];
    s32 x8c;
    s32 x90;
    u8 p1[0xa0 - 0x94];
    f32 xa0;
    u8 p2[0xb0 - 0xa4];
    s32 xb0;
    s32 xb4;
    u8 p3[0xba - 0xb8];
    s16 xba;
    s16 xbc;
    s16 xbe;
    s16 xc0;
    s16 xc2;
    s16 xc4;
    s16 xc6;
    s16 xc8;
    s16 xca;
    s16 xcc;
    s16 xce;
    s16 xd0;
    s16 xd2;
    u8 p6[0xd8 - 0xd4];
    s16 xd8;
    s16 xda;
} O98;
typedef struct { u8 pad[8]; s32 x8; s32 xc; u32 x10; } F8;
extern F8 *D_00425BC8;
extern s32 D_006469B0;
extern s32 D_006469B4;
extern u8 D_003F7210[];
extern s32 D_003F7228[];
extern s32 D_003F7230[];
extern s32 D_003F7238[];
extern s32 D_003F7248[];
void func_0011d768(s32);
s32 func_001f42b8(void);
s32 func_001fe570(void *);
void func_001fdfd0(void *);
s32 func_001fd538(void *);
s32 func_001f9438(void *, s32, s32, s32, s32, s32, s32);
void func_001f3708(void *, s32);
void func_0020bc48(s32, s32, s32);
void func_00201440(void *, s32, s32, s32, s32, s32, s32, void *, s32);
void func_002066b0(void *, s32, s32, s32, s32, s32);
void func_002053e8(void *, s32, s32, s32, s32, s32);
void func_002078f0(void *, s32, s32, s32, s32, s32, s32, s32, s32);
s32 func_001efbb8(s32);
s32 func_002192f8(void);
s32 func_00219348(void);
s32 func_00219380(void);
s32 func_002193b8(void);
s32 func_002193f0(void);
s32 func_00219428(void);
s32 func_00219458(s32);

extern u8 D_003F6E40[];
extern s32 D_003F6F58[];
extern s32 D_006437C0;
extern s32 D_006437C4;
extern s32 D_006437C8[];
extern s32 D_006437D0[];
extern s32 D_006437DC;
extern s32 D_006437E4;
typedef struct { u8 pad0[8]; u64 x8; u8 pad10[0x10]; char name[0x20]; } Dir40;
extern Dir40 *D_006450C0[];
extern Save3C D_00645250[];
extern void *D_00646990;
s32 func_001ee428(s32);
s32 func_001ee440(s32);
void *func_001f31a8(void *, s32);
void func_001f3758(void *);
void func_001f3d58(void *, s32);
void func_001f3dc0(void *);
void func_001f3e48(void *, void *);
void func_001f8ba8(void *);
void func_001f8f30(void);
s32 func_001f9e48(void *, s32, s32, s32, void *, s32, s32);
void func_001fb428(void *, s32, s32, s32, s32, s32, s32, s32, s32);
s32 func_001fd518(void *);
s32 func_001fd548(void *);
s32 func_001fd590(void *);
s32 func_001fd618(void *);
void func_001fd858(void *);
s32 func_001fe5a0(void *);
void func_001ff488(void *, s32, s32, s32, s32, s32);
void func_00202fc0(void *);
void func_0020bd18(void *, s32);
void func_0020be10(s32);
void func_00229a10(void *);
void func_00233f18(void);
s32 func_00233f40(s32, s32);
void func_00233ff8(s32, s32);

void func_00229ec0(void *arg0) {
    s32 sel, i, n, y;
    void *o;
    Save3C *s;

    if (func_001f42b8() != 0) {
        if (func_00233f40(D_006437C4, 0) != 0) {
            func_00233ff8(D_006437C4, 0);
            func_001f3d58(arg0, 6);
            func_00229a10(arg0);
        } else if (D_00425BC8->x8 & 0x4000) {
            func_001f3d58(arg0, 6);
            func_001f3758(D_00646990);
            func_0011d768(3);
            D_006437E4 = 0;
        } else {
            func_001fd858(arg0);
            func_0020bd18(arg0, 8);
            D_006437C8[D_006437C4] = func_001fd618(arg0);
            D_006437D0[D_006437C4] = func_001fd518(arg0);
            D_006437C0 = func_001fd548(arg0);
            if (func_001fe5a0(arg0) != 0) {
                if (D_006450C0[D_006437C0] != 0) {
                    if (D_00645250[D_006437C0].magic != 0x5153484B || D_00645250[D_006437C0].ver != 0x01317F14) {
                        func_0011d768(4);
                    } else {
                        func_0011d768(2);
                        func_001f3758(arg0);
                        func_0020be10(16);
                        D_006437DC = 20;
                        func_00233f18();
                        o = func_001f31a8(D_003F6E40, 6);
                        if (o != 0) {
                            func_001f3e48(o, arg0);
                            func_001f3dc0(D_00646990);
                        }
                    }
                } else {
                    func_0011d768(4);
                }
            }
        }
    }
    func_00202fc0(arg0);
    sel = func_001fd518(arg0);
    n = func_001fd618(arg0);
    y = func_001fd590(arg0);
    func_001f8ba8(arg0);

    for (i = 0; i < 5 && n < 99; i++, n++, y += 56) {
        func_001ff488(arg0, 0, y, 330, 50, i == sel ? 0x5A040422 : 0x5A000000);
        if (D_006437E4 != 0) {
            if (D_006450C0[n] != 0) {
                s = &D_00645250[n];
                if (s->magic == 0x5153484B && s->ver == 0x01317F14) {
                    func_001fb428(arg0, 0, 2, 1, 10, y + 18, n + 1, 15, 0x80399BFF);
                    func_001f9e48(arg0, 0, 52, y + 5, s->name, 15, 0x80399BFF);
                    func_001f9438(arg0, 0, 261, y + 5, D_003F6F58[s->x38], 15, 0x80399BFF);
                    D_003E8E08.a = func_001ee428(s->x10);
                    D_003E8E08.b = func_001ee440(s->x10);
                    D_003E8E08.c = s->xC;
                    D_003E8E08.d = s->x8;
                    func_001f9438(arg0, 0, 52, y + 30, 420, 15, 0x80399BFF);
                } else {
                    func_001fb428(arg0, 0, 2, 1, 10, y + 18, n + 1, 15, 0x804040C0);
                    func_001f9438(arg0, 0, 52, y + 18, 418, 15, 0x804040C0);
                }
            } else {
                func_001fb428(arg0, 0, 2, 1, 10, y + 18, n + 1, 15, 0x802B803F);
                func_001f9438(arg0, 0, 52, y + 18, 419, 15, 0x802B803F);
            }
        }
    }
    func_001f8f30();
}

void func_0022bd58(O98 *a0) {
    s32 s, x, y;
    if (func_001f42b8()) {
        if (D_00425BC8->x8 & 0x4000) {
            func_001f3708(a0, 12);
            func_0011d768(3);
            D_006469B4 = D_006469B0;
            D_006469B0 = D_006469B0 - 1;
        } else {
            func_001fdfd0(a0);
            x = a0->xb0 + a0->xda * 96 + (u32)(a0->xbe - 0x7000);
            y = a0->xb4 + a0->xc4 * a0->xd2 / 16;
            func_0020bc48(8, (s32)(x + a0->xc2 - a0->xc6) >> 4, (y + a0->xc0 - 0x7400) >> 4);
            if (func_001fe570(a0)) {
                if (func_001fd538(a0) == 0) {
                    D_006469B4 = D_006469B0;
                    D_006469B0 = D_006469B0 + 1;
                    func_001f3708(a0, 11);
                } else {
                    D_006469B4 = D_006469B0;
                    D_006469B0 = func_00219428() ? 1 : 2;
                    func_001f3708(a0, 12);
                }
            }
        }
    }
    func_00201440(a0, 2, 2, 11, 81, 122, 72, D_003F7210, 87);
    func_002066b0(a0, -64, 112, 640, 0x80c2726e, 0x80c2726e);
    func_002053e8(a0, -64, 114, 640, 156, 0x40000000);
    func_002066b0(a0, -64, 270, 640, 0x80c2726e, 0x80c2726e);
    if (func_00219428()) {
        func_001f9438(a0, 0, 40, 230, 94, 15, 0x80e6e6e6);
        D_003E8E08.a = func_001efbb8(D_003F7230[func_002193b8()]);
        func_001f9438(a0, 0, 128, 126, 450, 15, 0x66ffc8b4);
        D_003E8E08.a = func_00219458(func_002193f0());
        func_001f9438(a0, 0, 128, 146, 92, 15, 0x66ffc8b4);
        D_003E8E08.a = func_001efbb8(D_003F7238[func_002192f8()]);
        func_001f9438(a0, 0, 128, 166, 471, 15, 0x66ffc8b4);
        D_003E8E08.a = func_001efbb8(D_003F7228[func_00219348()]);
        func_001f9438(a0, 0, 128, 186, 93, 15, 0x66ffc8b4);
        D_003E8E08.a = func_001efbb8(D_003F7248[func_00219380()]);
        func_001f9438(a0, 0, 128, 206, 476, 15, 0x66ffc8b4);
    } else {
        func_001f9438(a0, 0, 40, 230, 94, 15, 0x80e6e6e6);
        D_003E8E08.a = func_00219458(func_002193f0());
        func_001f9438(a0, 0, 128, 130, 92, 15, 0x66ffc8b4);
        D_003E8E08.a = func_001efbb8(D_003F7238[func_002192f8()]);
        func_001f9438(a0, 0, 128, 150, 471, 15, 0x66ffc8b4);
        D_003E8E08.a = func_001efbb8(D_003F7228[func_00219348()]);
        func_001f9438(a0, 0, 128, 170, 93, 15, 0x66ffc8b4);
        D_003E8E08.a = func_001efbb8(D_003F7248[func_00219380()]);
        func_001f9438(a0, 0, 128, 190, 476, 15, 0x66ffc8b4);
    }
    s = func_001fd538(a0);
    func_002078f0(a0, s == 0, 2, 2, 256, a0->xc0 >> 4, 90, 301, 44);
    func_002078f0(a0, s == 1, 2, 2, 352, a0->xc0 >> 4, 90, 397, 45);
}

extern s32 D_003F7778;
extern f32 D_002BBDFC;
extern s32 D_006469D0;
extern s32 D_006469D4;
extern f32 D_006469D8;
extern s32 D_006469DC;
extern f32 D_006469E0;
extern s32 D_006469E4;
extern f32 D_006469E8;
extern s32 D_006469EC;
extern f32 D_006469F0;
extern s32 D_006469F4;
extern f32 D_006469F8;
extern char D_003F76C0[][20];
extern s32 D_003F7710[];
void func_001fd648(void *, s32);
void func_001f3840(void *);
f32 sinf(f32);

void func_0022e460(O98 *a0) {
    s32 v[2];
    s32 base, cur, half, sel, c;

    base = a0->x90;
    cur = base;
    half = base / 2;
    if (func_001f42b8()) {
        switch (D_006469E4) {
        case 0:
            if (D_00425BC8->x8 & 0x4000) {
                D_003F7778 = 0;
                func_001fd648(a0, 0);
                func_0011d768(3);
            } else {
                func_001fd858(a0);
                func_0020bd18(a0, 8);
                D_003F7778 = func_001fd518(a0);
                if (func_001fe570(a0)) {
                    D_006469E4++;
                }
            }
            break;
        case 1:
            D_006469E8 = 0.0f;
            D_006469E4 = 2;

        case 2:
            D_006469E8 += D_002BBDFC;
            if (D_006469E8 <= 8.0f) {
                cur = (f32)base + (f32)(255 - base) * sinf(D_006469E8 * 3.1415928f * 0.125f);
            } else {
                cur = base;
                func_001f3840(a0);
                func_0020be10(16);
            }
            break;
        }
    }
    switch (a0->x8c) {
    case 2:
        switch (D_006469EC) {
        case 0:
            D_006469EC = 1;
            D_006469F0 = 40.0f;
        case 1:
            D_006469F0 -= D_002BBDFC;
            if (!(D_006469F0 > 0.0f)) {
                D_006469EC++;
            }
            break;        case 2:
            break;
        }
        break;
    case 5:
        switch (D_006469F4) {
        case 0:
            D_006469F4 = 1;
            D_006469F8 = 40.0f;
        case 1:
            D_006469F8 -= D_002BBDFC;
            if (!(D_006469F8 > 0.0f)) {
                D_006469F4++;
            }
            break;        case 2:
            break;
        }
        break;
    }
    sel = func_001fd518(a0);
    v[sel] = cur;
    if (D_006469D0 != sel) {
        D_006469D4 = 0;
        D_006469DC = 0;
    }
    D_006469D0 = sel;
    switch (D_006469D4) {
    case 0:
        D_006469D4 = 1;
        D_006469D8 = 10.0f;
    case 1:
        D_006469D8 -= D_002BBDFC;
        if (D_006469D8 > 0.0f) {
            v[sel ^ 1] = (f32)half + (f32)(cur - half) * D_006469D8 / 10.0f;
        } else {
            v[sel ^ 1] = half;
            D_006469D4++;
        }
        break;
    case 2:
        v[sel ^ 1] = half;
        break;
    }
    switch (D_006469DC) {
    case 0:
        D_006469DC = 1;
        D_006469E0 = 8.0f;
    case 1:
        D_006469D8 -= D_002BBDFC;
        if (D_006469D8 > 0.0f) {
            v[sel] = (f32)cur + (f32)(half - cur) * D_006469D8 * 0.125f;
        } else {
            v[sel] = cur;
            D_006469DC++;
        }
        break;
    case 2:
        v[sel] = cur;
        break;
    }
    c = D_003F7710[sel];
    a0->x90 = v[0];

    func_002066b0(a0, 0, 176, 174, c, 0x330096ff);
    func_00201440(a0, 2, 2, 173, 164, 166, 256, D_003F76C0[sel], 99);
    func_002066b0(a0, 339, 176, 173, 0x330096ff, c);
    c = D_003F7710[sel + 2];
    a0->x90 = v[1];

    func_002066b0(a0, 0, 206, 174, c, 0x33ffc12c);
    func_00201440(a0, 2, 2, 173, 194, 166, 256, D_003F76C0[sel + 2], 100);
    func_002066b0(a0, 339, 206, 173, 0x33ffc12c, c);
    a0->x90 = base;
}
typedef struct {
    u8 pad[0x18c0];
    s32 flags[100];
    Save3C saves[1];
} Sys1E10;
extern Sys1E10 D_00351E10;
extern s32 D_006436D4;
extern s32 D_006436D8[];
extern s32 D_006436E0[];
extern s32 D_006436E8;
extern s32 D_00643734;
extern s32 D_0064373C;
extern void *D_00643740;
extern s32 D_00643750;
extern u8 D_003F6980[];
extern u8 D_003F69B0[];
extern u8 D_003F6AD0[];
extern u8 D_003F6920[];
extern s32 D_003F6B28[];
void *func_001f3520(void *, s32);
void func_001f4058(void *, s32);
void func_002246f8(void *);
void func_00224920(void *);
void func_00224ad8(void *);
void func_00225288(void *);

void func_00225330(O98 *arg0) {
    s32 sel, i, n, y;
    O98 *o;
    Save3C *s;

    if (func_001f42b8() != 0) {
        if (func_00233f40(D_006436D4, 0) != 0) {
            func_00233ff8(D_006436D4, 0);
            func_001f3d58(arg0, 6);
            func_002246f8(arg0);
        } else if (D_00425BC8->x8 & 0x4000) {
            func_001f3d58(arg0, 6);
            func_001f3758(D_00643740);
            func_0011d768(3);
            D_0064373C = 0;
        } else {
            func_001fd858(arg0);
            func_0020bd18(arg0, 8);
            D_006436D8[D_006436D4] = func_001fd618(arg0);
            D_006436E0[D_006436D4] = func_001fd518(arg0);
            D_006436E8 = func_001fd548(arg0);
            if (func_001fe5a0(arg0) != 0) {
                if (D_00351E10.flags[D_006436E8] != 0) {
                    if (D_00351E10.saves[D_006436E8].magic != 0x5153484B || D_00351E10.saves[D_006436E8].ver != 0x01317F14) {
                        if (D_00643750 == 0) {
                            goto nosave;
                        }
                        func_0011d768(6);
                        o = func_001f3520(D_003F6980, 6);
                        if (o) {
                            func_001f3e48(o, (void *)arg0->x10);
                            func_001f4058(o, 1);
                            func_001f3d58(o, 6);
                            func_00224920(o);
                            o->xda = 16;
                        }
                    } else {
                        func_0011d768(6);
                        o = func_001f3520(D_003F69B0, 6);
                        if (o) {
                            func_001f3e48(o, (void *)arg0->x10);
                            func_001f4058(o, 1);
                            func_001f3d58(o, 6);
                            func_00224ad8(o);
                            o->xda = 16;
                        }
                    }
                } else if (D_00643750 == 0) {
                nosave:
                    func_0011d768(4);
                    o = func_001f31a8(D_003F6AD0, 6);
                    if (o) {
                        func_001f3e48(o, (void *)arg0->x10);
                        func_001f4058(o, 1);
                        func_001f3d58(o, 6);
                        func_00225288(o);
                    }
                } else {
                    func_0011d768(2);
                    func_001f3758(arg0);
                    func_0020be10(16);
                    D_00643734 = 26;
                    func_00233f18();
                    o = func_001f31a8(D_003F6920, 6);
                    if (o) {
                        func_001f3e48(o, arg0);
                        func_001f3dc0(D_00643740);
                    }
                }
            }
        }
    }
    func_00202fc0(arg0);
    sel = func_001fd518(arg0);
    n = func_001fd618(arg0);
    y = func_001fd590(arg0);
    func_001f8ba8(arg0);

    for (i = 0; i < 5 && n < 99; i++, n++, y += 56) {
        func_001ff488(arg0, 0, y, 330, 50, i == sel ? 0x5A040422 : 0x5A000000);
        if (D_0064373C != 0) {
            if (D_00351E10.flags[n] != 0) {
                s = &D_00351E10.saves[n];
                if (s->magic == 0x5153484B && s->ver == 0x01317F14) {
                    func_001fb428(arg0, 0, 2, 1, 10, y + 18, n + 1, 15, 0x80399BFF);
                    func_001f9e48(arg0, 0, 52, y + 5, s->name, 15, 0x80399BFF);
                    func_001f9438(arg0, 0, 261, y + 5, D_003F6B28[s->x38], 15, 0x80399BFF);
                    D_003E8E08.a = func_001ee428(s->x10);
                    D_003E8E08.b = func_001ee440(s->x10);
                    D_003E8E08.c = s->xC;
                    D_003E8E08.d = s->x8;
                    func_001f9438(arg0, 0, 52, y + 30, 390, 15, 0x80399BFF);
                } else {
                    func_001fb428(arg0, 0, 2, 1, 10, y + 18, n + 1, 15, 0x804040C0);
                    func_001f9438(arg0, 0, 52, y + 18, 386, 15, 0x804040C0);
                }
            } else if (D_00643750 == 0) {
                func_001fb428(arg0, 0, 2, 1, 10, y + 18, n + 1, 15, 0x802B803F);
                func_001f9438(arg0, 0, 52, y + 18, 388, 15, 0x802B803F);
            } else {
                func_001fb428(arg0, 0, 2, 1, 10, y + 18, n + 1, 15, 0x802B803F);
                func_001f9438(arg0, 0, 52, y + 18, 389, 15, 0x802B803F);
            }
        }
    }
    func_001f8f30();
}

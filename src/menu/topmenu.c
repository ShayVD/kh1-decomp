/* The top menu (docs/modules.md "Session 39"), 0x0020c1c8-0x0020d7d8: the
 * list of the menu's pages D_00640E00 (D_00640E20 of them, the cursor
 * D_00640E24, the page D_00640E28; 5 and 7 only when func_001ec510 /
 * D_003F34A8 allow them), func_0020c1c8 the list window (fades the items in
 * and out, opens the page's window from D_003F32C8 / D_003F3308 and calls
 * its D_003F32E8 open), func_0020ca68 / func_0020d050 open the window
 * chains (D_003F3200 ... D_003F3358, D_003F3448), func_0020ccb0 /
 * func_0020ce78 the play time and munny panel, func_0020d530 sets the menu
 * up (its old file had -fno-strict-aliasing; it matches without), func_0020d6c8 opens it (a task running
 * func_0020d2f8 until the windows close), func_0020d2a0 closes it,
 * func_0020d748 resets the cursors of the pages. */
#include "common.h"
#include "text/textwin.h"
#include "data/pieces/D_00304BE8_s.h"
#include "data/pieces/D_003F34C4.h"
typedef N_3f34c4 N;
#include "data/pieces/D_00425BC8.h"
#include "data/pieces/D_003E3D68.h"
#include "data/pieces/D_003F3448.h"
#include "data/pieces/D_003F34D8.h"
#include "data/pieces/D_003F3488.h"
#include "data/pieces/D_003F34C8.h"
#include "data/pieces/D_002BC140.h"
#include "data/pieces/D_002BC144.h"
typedef struct { u8 pad[0x10]; s32 x10; u8 pad14[0x70]; s32 x84; u8 pad88[0x28]; s32 xb0; u8 padb4[4]; u16 xb8; u8 padba[4]; s16 xbe; u8 padc0[2]; s16 xc2; u8 padc4[8]; u16 xcc; u16 xce; u8 padd0[2]; s16 xd2; } Obj;   /* the u16s: lhu */
typedef struct { s16 f0; s16 f2; } Task;

extern s32 D_00640E00[];
extern s32 D_00640E20, D_00640E24, D_00640E28, D_00640E2C, D_00640E30;
extern s32 D_003F32A8[];
extern void *D_003F32C8[];
extern s32 D_003F3308[];
extern void (*D_003F32E8[])(N *);
extern u8 D_003F3330[], D_003F3280[], D_003F3230[], D_003F3200[], D_003F3358[];
extern s32 D_003F3398[];
extern u8 D_003F33A8[];
extern s32 D_003F3420;
extern s32 D_003F3468[];
extern s32 D_003F34A4, D_003F34A8, D_003F34C0;
extern s32 D_003F6E30;
extern s32 D_003F34CC;
extern s32 D_003F34D0;
extern s32 D_003F34D4;
extern s32 D_003F34DC;
extern s32 D_003F34E0;
extern s32 D_003F34E4;
extern s32 D_003F34E8;
extern s32 D_003F34EC;
extern s32 D_003F34F0;
extern s32 D_003F34F4;
extern s32 D_003F34F8;
extern s32 D_003F34FC;
extern s32 D_003F3500;
extern s32 D_003F3504;
extern s32 D_003F3508;
extern s32 D_003F350C;
extern s32 D_003F3510;
extern s32 D_003F3514;
extern s32 D_003F3518;
extern s32 D_003F351C;
extern s32 D_003F3520;

s32 func_0010fd18(void);
s32 func_00111798(void);
void func_0011d768(s32);
Task *func_0011ef10(s32, void (*)(void));
void func_00142000(void);
s32 func_001559f0(s32, s32);
s32 func_001ee2d0(void);
s32 func_001ee308(void);
s32 func_001ee348(void);
s32 func_001ef7a0(void);
void func_001f3110(void);
void *func_001f31a8(void *, s32);
void func_001f36b8(void *);
void func_001f3708(void *, s32);
void func_001f37c0(void *, s32);
void func_001f3840(void *);
void func_001f3d58(void *, s32);
void func_001f3dc0(void *);
void func_001f3e20(void *, void *);
void func_001f3e90(void *, void *);
s32 func_001f40c8(void);
s32 func_001f42b8(void *);
s32 func_001f4390(void *);
void *func_001f4468(void *);
void func_001f82b0(void);
void func_001f9e48(void *, s32, s32, s32, s32, s32, s32);
s32 func_001fbcb0(void *, s32, s32, s32, s32, s32, s32, s32);
s32 func_001fc308(void *, s32, s32, s32, s32, s32, s32, s32, s32);
s32 func_001fd518(void *);
void func_001fd858(void *);
s32 func_001fe570(void *);
void func_00205e30(void *, void *);
void func_00206130(void *, s32, s32, s32, s32, s32);
void func_00206e28(void);
void func_00206f20(void);
void func_00206ff0(void);
void func_002070c0(void);
void func_002071b8(void);
void func_00207288(void);
s32 func_00207358(void);
void func_00207428(void *, s32, s32);
void func_00207560(void *, s32, s32);
void func_00207598(void);
void func_00207618(void);
void func_00207830(void *, s32, s32, s32, s32, s32, s32);
void func_0020a1d8(void);
void func_0020a9b0(s32);
void func_0020ab88(s32);
void func_0020b120(s32, s32, u32, u32, u32, u32);
void func_0020b3d8(void *, s32, s32);
void func_0020b998(void);
void func_0020bb90(s32, s32);
void func_0020bd18(void *, s32);
void func_0020bda8(s32);
void func_0020ca30(void *, s32, s32, s32);
void func_0020ccb0(void *);
void *func_0020d030(void);
void func_0020d050(Obj *);
void func_0020d2a0(void);
s32 func_0020d2f8(void);
void func_0020d530(void);
s32 func_0020d6c0(s32);
void func_00211398(void);
void func_00213d30(void);
void func_00216140(void);
void func_00217fe8(void);
void func_00219118(void);
s32 func_0021add8(void);
void func_0021adc8(void);
void func_0021db30(void);
void *func_0021d9e0(void *);
void *func_00229338(void *);
void func_00229850(void);
void func_002336f8(void);
s32 func_001ec510(void);
void func_001ef830(void);
void func_00209f70(void);
void func_0020a8f0(void);
void func_0020b338(void);
void func_0020b968(void);
void func_0020d360(void);
void func_00211358(void);
void func_00213d00(void);
void func_00216118(void);
void func_00217fb0(void);
void func_002190e8(void);
void func_0021adb0(void);
void func_0021dad8(void);
void func_00229820(void);
void func_002365e0(void);

#include "data/pieces/D_003F34B8.h"
/* callee defined in src/game/bitsets.c */
CONTEXT_ONLY u32 func_002073f0(s32 n) {
    return D_003F34B8->b112[n / 32] & (1 << n);
}
#define ITEM(n) { \
    s32 s; \
    if (n != 7) s = n == D_00640E28; \
    else s = (D_00640E28 == n) ? 19 : 18; \
    func_00207830(o, s, 2, 11, k, 122, D_003F32A8[n]); \
    if (n == 5) { if (func_0021add8()) func_00207560(o, 109, 215); if (!func_002073f0(0)) func_00207428(o, 92, 223); } \
}

/* rodata */
void func_0020c1c8(N *o) {
    f32 t = o->x94;
    s32 i, k, a, sel;
    switch (o->x24) {
    case 0:
        D_00640E24 = func_001fd518(o);
        D_00640E28 = D_00640E00[D_00640E24];
        a = o->x90;
        for (i = 0, k = 71; i < o->xcc; k += 28, i++) {
            f32 d = (f32)(i * 2);
            if (d <= t) {
                f32 e = t - d;
                if (e < 6.0f) o->x90 = (f32)a * (e / 6.0f);
                else o->x90 = a;
            } else o->x90 = 0;
            { s32 n = D_00640E00[i]; ITEM(n) }
        }
        o->x90 = a;
        if ((f32)(o->xcc * 2 + 4) <= t) o->x24++;
        break;
    case 1:
        if (func_001f42b8(o)) {
            if (D_00425BC8->x8 & 0x4000) {
                func_001f3840(o);
                func_0011d768(3);
                func_00207618();
            } else {
                func_001fd858(o);
                func_0020bd18(o, 8);
                D_00640E24 = func_001fd518(o);
                D_00640E28 = D_00640E00[D_00640E24];
                if (func_001fe570(o)) {
                    N *c, *d;
                    o->x24++;
                    o->x28 = t;
                    c = o->x10;
                    if (c) {
                        func_001f3708(c, 6);
                        c = c->x10;
                        if (c) {
                            func_001f36b8(c);
                            c = c->x10;
                            if (c) func_001f36b8(c);
                        }
                    }
                    c = func_001f4468(o);
                    switch (D_00640E28) {
                    case 5:
                        func_001f37c0(D_003F34C4->x10, 1);
                        func_001f3d58(D_003F34C4->x10->x10, 2);
                        func_001f3d58(D_003F34C4->x10->x10->x10, 2);
                        c = func_0021d9e0(c);
                        o->x24 = 4;
                        break;
                    case 7:
                        func_001f37c0(D_003F34C4->x10, 1);
                        func_001f3d58(D_003F34C4->x10->x10, 2);
                        func_001f3d58(D_003F34C4->x10->x10->x10, 2);
                        c = func_00229338(c);
                        o->x24 = 4;
                        break;
                    }
                    d = func_001f31a8(D_003F32C8[D_00640E28], D_003F3308[D_00640E28]);
                    if (d) {
                        func_001f3e90(c, d);
                        func_001f3e20(d, c);
                        { f32 v = 4.0f; s32 m = D_00640E28; d->xa0 = v; D_003F32E8[m](d); }
                    }
                }
            }
        }
        D_00640E24 = func_001fd518(o);
        D_00640E28 = D_00640E00[D_00640E24];
        for (i = 0, k = 71; i < o->xcc; k += 28, i++)
            { s32 n = D_00640E00[i]; ITEM(n) }
        break;
    case 2:
        t -= o->x28;
        D_00640E24 = func_001fd518(o);
        D_00640E28 = D_00640E00[D_00640E24];
        a = o->x90;
        for (i = 0, k = 71; i < o->xcc; k += 28, i++) {
            f32 d = (f32)((o->xcc - i) * 2 - 2);
            if (d <= t) {
                d = t - d;
                if (d < 6.0f) { d = 6.0f - d; o->x90 = (f32)a * (d / 6.0f); }
                else o->x90 = 0;
            } else o->x90 = a;
            { s32 n = D_00640E00[i]; ITEM(n) }
        }
        o->x90 = a;
        if ((f32)(o->xcc * 2 + 4) <= t) {
            o->x24++;
            if (func_001f4390(o)) func_001f36b8(o);
        }
        break;
    case 3:
        break;
    case 4:
        for (i = 0, k = 71; i < o->xcc; k += 28, i++)
            { s32 n = D_00640E00[i]; ITEM(n) }
        break;
    }
}

void func_0020ca30(void *a0, s32 a1, s32 a2, s32 a3) {
    func_001fc308(a0, 12, 11, 0, 0, 3, a1, a2, a3);
}

void func_0020ca68(Obj *a0) {
    Obj *o[4];
    s32 d;
    if (func_001f4390(a0) && a0->x10 == 0) {
        o[0] = func_001f31a8(D_003F3330, 1);
        if (o[0]) {
            func_001f3e90(a0, o[0]);
            func_001f3e20(o[0], a0);
            o[0]->xcc = o[0]->xce = D_00640E20;
            func_00207598();
            o[0]->xd2 = (u16)D_00640E24 * 16;
            o[1] = func_001f31a8(D_003F3280, 6);
            if (o[1]) {
                func_001f3e90(o[0], o[1]);
                func_001f3e20(o[1], o[0]);
                func_001f3d58(o[1], 4);
                o[2] = func_001f31a8(D_003F3230, 1);
                if (o[2]) {
                    func_001f3e90(o[1], o[2]);
                    func_001f3e20(o[2], o[1]);
                    o[3] = func_001f31a8(D_003F3200, 54);
                    if (o[3]) {
                        func_001f3e90(o[2], o[3]);
                        func_001f3e20(o[3], o[2]);
                        func_001f3d58(o[3], 6);
                        d = 4 - D_003E3D68;
                        d *= 0x4f0;
                        o[3]->xb0 += d;
                        o[3]->xb8 -= d;
                        o[3]->x84 = 6;
                        func_001f3dc0(o[0]);
                    }
                }
            }
        }
    }
    func_00205e30(a0, D_003F3358);
    func_00206130(a0, 0, 62, 512, 2, 0x80f04646);
    func_0020ca30(a0, 0, 0x808f1f22, 0x80e16063);
    func_001fc308(a0, 160, 35, 0, 19, 20, 0, 0x80399bff, 0x80399bff);
    func_001f9e48(a0, 0, 173, 35, func_0010fd18(), 19, 0x80399bff);
    func_0020b3d8(a0, 401, 4);
}

void func_0020ccb0(void *a0) {
    s32 c, a, b, d, x;
    func_001fc308(a0, 10, 54, 0, 0, 5, 0, 0x40ff8a00, 0x40ff8a00);
    c = D_003F3398[func_00111798()];
    a = func_001ee2d0();
    b = func_001ee308();
    d = func_001ee348();
    x = func_001fbcb0(a0, 0, 2, 1, 51, 51, a, c);
    x = func_001fc308(a0, x - 2, 51, 0, 0, 0, c, 0x80808080, 0x80808080);
    x = func_001fbcb0(a0, 0, 2, 1, x - 3, 51, b, c);
    x = func_001fc308(a0, x - 2, 51, 0, 0, 0, c, 0x80808080, 0x80808080);
    x = func_001fbcb0(a0, 0, 2, 1, x - 3, 51, d, c);
    func_001fc308(a0, 9, 20, 0, 0, 4, 0, 0x402760f5, 0x402760f5);
    func_001fbcb0(a0, 1, 5, 1, x, 18, func_001ef7a0(), 1);
}

void func_0020ce78(void *a0) {
    func_00205e30(a0, D_003F33A8);
    func_00206130(a0, 0, 0, 512, 2, 0x80f04646);
    func_0020ccb0(a0);
    func_001fc308(a0, 160, 12, 0, 63, 20, 0, 0x40c87878, 0x40c87878);
}

void func_0020cf00(TextWin *w) {
    s32 al = w->x90;
    func_0020b120(2, al, 0x80080808, 0x80080808, 0x80080808, 0x80080808);
    func_0020b120(1, al, 0x80101010, 0x80101010, 0x80101010, 0x80101010);
    func_0020b120(2, al, 0x80080808, 0x80080808, 0x80080808, 0x80080808);
    func_0020a9b0(al);
    func_0020ab88(al);
}

void func_0020cf90(void *a0) {
    if (func_001f4390(a0) && (D_00425BC8->x8 & 8)) {
        if (!(D_003F34C0 & 3)) {
            func_001f3840(a0);
            func_0011d768(3);
            func_00207618();
            D_003F34C0 |= 1;
        } else {
            func_0011d768(4);
        }
    }
}

void *func_0020d030(void) {
    return func_001f31a8(&D_003F3420, 0);
}

void func_0020d050(Obj *a0) {
    Obj *o[7];
    s32 i, d;
    for (i = 0; i < 7; i++) {
        o[i] = func_001f31a8(((u8 **)&D_003F3448)[i], D_003F3468[i]);
        if (o[i]) {
            func_001f3e90(a0, o[i]);
            func_001f3e20(o[i], a0);
            func_001f3d58(o[i], D_003F3488[i]);
            a0 = o[i];
        }
    }
    o[3]->xcc = o[3]->xce = D_00640E20;
    func_00207598();
    o[3]->xd2 = (u16)D_00640E24 * 16;
    d = 4 - D_003E3D68;
    i = d * 0x4f0;
    o[6]->xb0 += i;
    o[6]->xb8 -= i;
    o[6]->x84 = 6;
    func_001f3dc0(o[3]);
    func_0020bb90((o[3]->xb0 + o[3]->xc2 + o[3]->xbe - 0x7000) >> 4, 0);
    func_0020bd18(o[3], 8);
    func_0020bda8(16);
}

void *func_0020d1d8(void *a0) {
    void *buf[3];
    s32 i;
    for (i = 0; i < 3; i++) {
        buf[i] = func_001f31a8((void *)D_003F3448[i], 1);
        if (buf[i] != 0) {
            func_001f3e90(a0, buf[i]);
            func_001f3e20(buf[i], a0);
            func_001f3d58(buf[i], D_003F3488[i]);
            a0 = buf[i];
        }
    }
    return a0;
}

void func_0020d2a0(void) {
    D_003F34A4 = 0;
    if (D_003F6E30 == 0) {
        func_0020a1d8();
    }
    func_00142000();
    D_002BC144 = D_00640E2C;
    D_002BC140 = D_00640E30;
}

s32 func_0020d2f8(void) {
    if (func_001f40c8() != 0 || D_003F34C8 != 0) {
        func_002336f8();
        func_002365e0();
        func_001f82b0();
        func_0020b998();
        return 0;
    }
    func_0020d2a0();
    return 4;
}

void func_0020d360(void) {
    D_003F34CC = 0; { s32 *p = &D_003F34D0; *p = func_001559f0(52, 1); }
    D_003F34D4 = 0; { s32 *p = ((s32 *)&D_003F34D8); *p = func_001559f0(52, 1) + 0x4000; }
    D_003F34DC = 0; { s32 *p = &D_003F34E0; *p = func_001559f0(52, 1) + 0x1c000; }
    D_003F34E4 = 0; { s32 *p = &D_003F34E8; *p = func_001559f0(52, 1) + 0x2d000; }
    D_003F34EC = 0; { s32 *p = &D_003F34F0; *p = func_001559f0(52, 1) + 0x31000; }
    D_003F34F4 = 0; { s32 *p = &D_003F34F8; *p = func_001559f0(52, 1) + 0x34000; }
    D_003F34FC = 0; { s32 *p = &D_003F3500; *p = func_001559f0(53, 1); }
    D_003F3504 = 0; { s32 *p = &D_003F3508; *p = func_001559f0(54, 1); }
    D_003F350C = 0; { s32 *p = &D_003F3510; *p = func_001559f0(62, 1); }
    D_003F3514 = 0; { s32 *p = &D_003F3518; *p = func_001559f0(62, 1) + 0x54000; }
    D_003F351C = 0; { s32 *p = &D_003F3520; *p = func_001559f0(62, 1) + 0x5c000; }
}

void func_0020d530(void) {
    s32 n;
    D_00640E00[2] = 2;
    D_00640E00[3] = 3;
    D_00640E00[4] = 4;
    D_00640E00[0] = 0;
    D_00640E00[1] = 1;
    D_00640E20 = 5;
    if (func_001ec510()) {
        D_00640E00[D_00640E20++] = 5;
    }
    D_00640E00[D_00640E20++] = 6;
    if (D_003F34A8 == 1) {
        D_00640E00[D_00640E20++] = 7;
    }
    func_00207598();
    D_003F34A4 = 1;
    D_00640E2C = D_002BC144;
    D_00640E30 = D_002BC140;
    D_003F34C0 &= ~1;
    D_003F34C0 &= ~2;
    D_003F34C8 = 0;
    func_0020d360();
    func_001ef830();
    func_00209f70();
    func_0020b338();
    func_0020a8f0();
    func_0020b968();
    func_00211358();
    func_00213d00();
    func_00216118();
    func_00217fb0();
    func_002190e8();
    func_0021adb0();
    func_0021dad8();
    func_00229820();
}

s32 func_0020d6c0(s32 a0) {
    return 0;
}

void func_0020d6c8(s32 a0) {
    void *v;
    D_003F34A4 = 0;
    func_001f3110();
    if (func_0020d6c0(a0)) return;
    D_003F34A8 = 0;
    func_0020d530();
    v = func_0020d030();
    D_003F34C4 = v;
    if (v) func_0020d050(v);
    func_0011ef10(0x270ff, (void (*)(void))func_0020d2f8)->f2 = a0;
}

void func_0020d748(void) {
    D_00640E24 = 0;
    D_00640E28 = 0;
    func_00211398();
    func_00213d30();
    func_00216140();
    func_00217fe8();
    func_00219118();
    func_0021adc8();
    func_0021db30();
    func_00229850();
    func_00206e28();
    func_00206f20();
    func_00206ff0();
    func_002070c0();
    func_002071b8();
    func_00207288();
    func_00207358();
}

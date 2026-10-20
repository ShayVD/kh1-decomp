#include "common.h"
#include "data/bss_0064.h"
typedef struct { u8 pad[0x24]; s32 x24, x28, x2c; } W14;
typedef struct { s32 a, col, b; } St14;
typedef struct { u8 pad[0x38]; s8 x38; } It14;
extern s32 D_00641BAC;
extern s32 D_00641BBC;
extern St14 D_003E8E08;
void func_001f9270(void *, s32, s32, s32, s32, s32);
u8 *func_001eeb88(s32);
s32 func_001eec28(s32, s32);
u8 *func_001efbb8(s32);
s32 func_001f94f0(void *, s32, s32, s32, u8 *, s32, s32);
s32 func_001fb428(void *, s32, s32, s32, s32, s32, s32, s32, s32);
void func_002066b0(void *, s32, s32, s32, s32, s32);
s32 func_001eec48(s32, s32);
void func_001f9438(void *, s32, s32, s32, s32, s32, s32);
It14 *func_001496c8(s32, s32);
void func_002119a8(W14 *w) {
    u8 *s;
    s32 n, id, n2;
    func_001f9270(w, 0, 16, D_00641BAC == 0 ? 171 : 172, 15, 0x801ec8c8);
    if (D_00641BBC) {
        s = func_001eeb88(D_00641BBC);
        n = func_001eec28(D_00641BAC, D_00641BBC);
    } else {
        s = func_001efbb8(167);
        n = 0;
    }
    func_001f94f0(w, 0, 12, 31, s, 14, 0x80808080);
    func_001fb428(w, 1, 3, 0, 130, 53, n, 14, 0x80808080);
    func_002066b0(w, 12, 67, 118, 0x80323232, 0x80323232);
    id = w->x24;
    if (id) {
        s = func_001eeb88(id);
        n2 = func_001eec28(D_00641BAC, id);
    } else {
        s = func_001efbb8(167);
        n2 = 0;
    }
    func_001f94f0(w, 0, 12, 71, s, 14, 0x8080e680);
    func_001fb428(w, 1, 2, 0, 130, 93, n2, 14, 0x8080e680);
    func_002066b0(w, 12, 107, 118, 0x80323232, 0x80323232);
    D_003E8E08.a = w->x28;
    D_003E8E08.b = func_001eec48(D_00641BAC, id);
    if (D_003E8E08.a < D_003E8E08.b) {
        D_003E8E08.col = 0x80fc927a;
    } else if (D_003E8E08.a == D_003E8E08.b) {
        D_003E8E08.col = 0x80808080;
    } else {
        D_003E8E08.col = 0x806e6eff;
    }
    func_001f9438(w, 0, 12, 111, 173, 15, 0x80e6e6e6);
    func_002066b0(w, 12, 147, 118, 0x80323232, 0x80323232);
    D_003E8E08.a = 0;
    D_003E8E08.a = w->x2c;
    D_003E8E08.b = 0;
    if (id) {
        D_003E8E08.b = w->x2c + func_001496c8(D_00641BAC, id)->x38;
        if (D_00641BBC) {
            D_003E8E08.b -= func_001496c8(D_00641BAC, D_00641BBC)->x38;
        }
        if (D_003E8E08.b < 0) D_003E8E08.b = 0;
    }
    if (D_003E8E08.a < D_003E8E08.b) {
        D_003E8E08.col = 0x80fc927a;
    } else if (D_003E8E08.a == D_003E8E08.b) {
        D_003E8E08.col = 0x80808080;
    } else {
        D_003E8E08.col = 0x806e6eff;
    }
    func_001f9438(w, 0, 12, 151, 479, 15, 0x80e6e6e6);
    func_002066b0(w, 12, 187, 118, 0x80323232, 0x80323232);
}

typedef struct O15 { u8 pad[0x10]; struct O15 *x10; u8 p14[0x10]; s32 x24; f32 x28; } O15;
typedef struct { u8 pad[4]; u32 x4; s32 x8; u8 padc[4]; u32 x10; } Cfg;
typedef struct { u8 pad[0x32]; u8 x32; } S1BB0;
extern Cfg *D_00425BC8;
extern s32 D_00641BA4, D_00641BA8, D_00641BC0, D_00641BC4, D_00641BD0, D_00641BD4, D_00641C00, D_00641C08, D_00642410;
extern s32 D_00641C10[], D_00641BE0[], D_00641BF0[], D_00642010[];
extern S1BB0 *D_00641BB0; /* src/data/bss_0064.c: s32 D_00641BB0 */
extern f32 D_002BBDFC;
s32 func_001f42b8(O15 *);
void func_001f3758(O15 *);
void func_0011d768(s32);
void func_0020a728(s32);
void func_001fd858(O15 *);
void func_0020bd18(O15 *, s32);
s32 func_001fd618(O15 *);
s32 func_001fd638(O15 *);
s32 func_001fd548(O15 *);
s32 func_001eebd8(s32);
s32 func_001fe5a0(O15 *);
void func_001ef830(void);
void func_001f3d58(O15 *, s32);
void func_00202fc0(O15 *);
s32 func_001fd518(O15 *);
s32 func_001fd590(O15 *);
void func_001f8ee0(O15 *);
void func_002115e0(O15 *, s32, s32, s32, s32, s32, s32);
void func_001f8f30(void);
void func_00211ed0(O15 *a) {
    s32 v, sel, i, y, k;
    O15 *o;
    if (func_001f42b8(a)) {
        if (D_00425BC8->x8 & 0x4000) {
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

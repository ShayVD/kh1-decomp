typedef unsigned char u8;
typedef short s16;
typedef int s32;
typedef float f32;
typedef struct N { u8 pad[0x10]; struct N *x10; u8 pad14[0x10]; s32 x24; f32 x28; u8 pad2c[0x90 - 0x2c]; s32 x90; f32 x94; u8 pad98[0xa0 - 0x98]; f32 xa0; u8 pada4[0xcc - 0xa4]; s16 xcc; s16 xce; } N;
typedef struct { u8 pad[8]; s32 x8; } P5BC8;
extern P5BC8 *D_00425BC8;
extern s32 D_00640E00[];
extern s32 D_00640E24, D_00640E28;
extern s32 D_003F32A8[];
extern s32 D_003F32C8[];
extern s32 D_003F3308[];
extern void (*D_003F32E8[])(N *);
extern N *D_003F34C4;
s32 func_001fd518(N *);
void func_00207830(N *, s32, s32, s32, s32, s32, s32);
s32 func_0021add8(void);
void func_00207560(N *, s32, s32);
s32 func_002073f0(s32);
void func_00207428(N *, s32, s32);
s32 func_001f42b8(N *);
void func_001f3840(N *);
void func_0011d768(s32);
void func_00207618(void);
void func_001fd858(N *);
void func_0020bd18(N *, s32);
s32 func_001fe570(N *);
void func_001f3708(N *, s32);
void func_001f36b8(N *);
N *func_001f4468(N *);
void func_001f37c0(N *, s32);
void func_001f3d58(N *, s32);
N *func_0021d9e0(N *);
N *func_00229338(N *);
N *func_001f31a8(s32, s32);
void func_001f3e90(N *, N *);
void func_001f3e20(N *, N *);
s32 func_001f4390(N *);

static inline void inl5(N *o) { if (func_0021add8()) func_00207560(o, 109, 215); if (!func_002073f0(0)) func_00207428(o, 92, 223); }
#define ITEM(n) { \
    s32 s; \
    if (n != 7) s = n == D_00640E28; \
    else s = (D_00640E28 == n) ? 19 : 18; \
    func_00207830(o, s, 2, 11, k, 122, D_003F32A8[n]); \
    if (n == 5) { if (func_0021add8()) func_00207560(o, 109, 215); if (!func_002073f0(0)) func_00207428(o, 92, 223); } \
}

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

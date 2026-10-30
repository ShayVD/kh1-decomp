/* wm.x func_00f6a530: matched by hand. */
#include "ovl.h"

typedef struct Obj {
    u8 pad0[108];
    s32 x6C;
    s32 x70;
    u8 pad74[28];
    s32 x90;
    u8 pad94[28];
    s32 xB0;
    s32 xB4;
    s16 xB8;
    s16 xBA;
} Obj;
typedef struct Ent {
    s8 b0, b1, b2, b3, b4, b5, b6, b7;
    s16 h8, hA, hC;
    s16 padE;
    s32 x10;
    f32 x, y, tx, ty, vx, vy;
    f32 a, at, as;
    u8 r, g, b, al;
    void (*fn3C)(void);
    void (*fn40)(struct Ent *, Obj *);
} Ent;
extern s32 D_00FB49F0;
extern s32 D_00FB4A20;
extern s32 D_00FB4DF8;
extern s32 D_00FB4DFC;
extern s32 D_00FB4E00;
extern s32 D_00FB4E04;
extern s32 D_00FB4E98;
extern s32 D_00FB4E9C;
extern s32 D_00FB4EA0;
extern s32 D_00FB4EA4;
extern s32 D_00FB4EA8;
extern s32 D_00FB4EAC;
extern s32 D_00FB4EB0;
extern Ent *D_0108F180;
extern s32 D_0108F184;
extern s32 D_0108F1A4;
extern s32 D_0108F1B8;
extern s32 D_0108F254;
extern s32 D_0108F258;
s32 func_001efbe0(s32, s32);
void func_001f3840(Obj *);
void func_001f4090(Obj *, s32 *);
s32 func_001f4390(Obj *);
void func_001f4778(Obj *);
void func_001f54f8(Obj *);
void func_001f8f30(void);
void func_001f9438(Obj *, s32, s32, s32, s32, s32, s32);
void func_001f94f0(Obj *, s32, s32, s32, s32, s32, s32);
void func_001fb428(Obj *, s32, s32, s32, s32, s32, s32, s32, s32);
void func_001fc308(Obj *, s32, s32, s32, s32, s32, s32, s32, s32);
void func_00206130(Obj *, s32, s32, s32, s32, s32);
void func_002078f0(Obj *, s32, s32, s32, s32, s32, s32, s32, s32);
void func_00207938(Obj *, s32, s32, s32, s32, s32, s32, s32, s32);
s32 func_00f47110(void);
void func_00f68bc0(Obj *, s32, s32, s32, s32);
void func_00f68d90(Obj *, s32, s32, s32, s32);
void func_00f6a448(void);
void func_00f74440(void);

#define COL(e) ((e)->r | ((e)->g << 8) | ((e)->b << 16) | ((e)->al << 24))

void func_00f6a530(Obj *o)
{
    s32 layer, j, x, y, alpha;
    s32 *tbl;
    Ent *e;
    s32 s0, s1;
    s16 s2, s3;

    for (layer = 0; layer < 5; layer++) {
        e = D_0108F180;
        for (j = 0; j < 512; j++, e++) {
            if (e->b0 == 0 || e->hC != layer) continue;
            if (e->a == e->at) {
                alpha = e->a * 0.5f;
            } else {
                if (e->a < e->at) {
                    e->a += e->as;
                    if (e->a >= e->at) {
                        e->a = e->at;
                        e->as = 0;
                    }
                } else {
                    e->a += e->as;
                    if (e->a <= e->at) {
                        e->a = e->at;
                        e->as = 0;
                    }
                }
                alpha = e->a * 0.5f;
            }
            if (e->x != e->tx) {
                if (e->x < e->tx) {
                    e->x += e->vx;
                    if (e->x >= e->tx) {
                        e->x = e->tx;
                        e->vx = 0;
                    }
                } else {
                    e->x -= e->vx;
                    if (e->x <= e->tx) {
                        e->x = e->tx;
                        e->vx = 0;
                    }
                }
            }
            if (e->y != e->ty) {
                if (e->y < e->ty) {
                    e->y += e->vy;
                    if (e->y >= e->ty) {
                        e->y = e->ty;
                        e->vy = 0;
                    }
                } else {
                    e->y -= e->vy;
                    if (e->y <= e->ty) {
                        e->y = e->ty;
                        e->vy = 0;
                    }
                }
            }
            e->fn3C();
            x = e->x;
            o->x90 = alpha;
            y = e->y;
            switch (e->b1) {
            case 0:
                func_002078f0(o, e->b4, e->b2, e->b3, x, y, e->h8, x + e->b7, e->x10);
                break;
            case 1:
                func_001f9438(o, e->b3, x, y, e->x10, e->b5, COL(e));
                break;
            case 2:
                if (D_0108F1B8 == 0) {
                    func_001f9438(o, e->b3, x, y, e->x10, e->b5, COL(e));
                } else if (D_0108F1B8 > 0) {
                    func_001f9438(o, e->b3, x, y, D_0108F1B8, e->b5, COL(e));
                }
                break;
            case 3:
                func_00206130(o, x, y, e->h8, e->hA, COL(e));
                break;
            case 4:
                func_001fb428(o, e->b3, e->b5, 0, x, y, e->x10, 15, COL(e));
                break;
            case 5:
                if (e->x10 < 4) {
                    func_001f9438(o, e->b3, x, y, e->x10 + 110, e->b5, COL(e));
                } else {
                    func_001f9438(o, e->b3, x, y, 113, e->b5,
                                  D_00FB4DF8 | (D_00FB4DFC << 8) | (D_00FB4E00 << 16) | (D_00FB4E04 << 24));
                }
                break;
            case 6:
                if (e->x10 != 1) {
                    tbl = &D_00FB49F0;
                } else {
                    tbl = &D_00FB4A20;
                }
                s0 = o->xB0;
                s1 = o->xB4;
                s2 = o->xB8;
                s3 = o->xBA;
                func_001f4090(o, tbl);
                o->xB8 = (u16)e->h8 * 16;
                o->xB0 = x * 16 + 0x7000;
                o->xB4 = y * 16 + 0x7400;
                o->x70 = 1;
                o->xBA = (u16)e->hA * 16;
                o->x6C = COL(e);
                func_001f4778(o);
                func_001f54f8(o);
                o->xB0 = s0;
                o->xB4 = s1;
                o->xB8 = s2;
                o->xBA = s3;
                break;
            case 8:
                func_00f68d90(o, e->x10, 3, 1, 1);
                break;
            case 9:
                func_00f68d90(o, e->x10, 3, 0, 1);
                func_00f68bc0(o, D_0108F1A4, x, y, e->h8);
                break;
            case 10:
                func_00f68d90(o, e->x10, 3, 0, 0);
                func_00f68bc0(o, D_0108F1A4, x, y, e->h8);
                break;
            case 11:
                func_001fc308(o, e->x, e->y, 0, e->hA, e->x10, 0, COL(e), COL(e));
                break;
            case 12:
                func_001f94f0(o, e->b3, x, y, func_001efbe0(e->x10, e->b6), e->b5, COL(e));
                break;
            case 13:
                func_00207938(o, e->b4, e->b2, e->b3, x, y, e->h8, x + 32, e->x10);
                break;
            case 14:
                func_001f94f0(o, e->b3, x, y, e->x10, e->b5, COL(e));
                break;
            }
            if (e->fn40) e->fn40(e, o);
        }
    }
    if (D_0108F258 == 0 && func_00f47110()) {
        o->x90 = 128;
        func_00f6a448();
        func_001f9438(o, 0, D_00FB4E98, D_00FB4E9C, 223, D_00FB4EA0,
                      D_00FB4EA4 | (D_00FB4EA8 << 8) | (D_00FB4EAC << 16) | (D_00FB4EB0 << 24));
    }
    func_001f8f30();
    if (D_0108F254) func_00f74440();
    if (D_0108F184 >= 0 && func_001f4390(o)) func_001f3840(o);
}

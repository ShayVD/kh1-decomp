#include "common.h"

typedef struct { s32 x, y; } Pt17;
typedef struct {
    s32 cur; s32 t[6]; s32 a[6]; Pt17 p[6]; s32 b[6]; f32 f7c; f32 f80;
} St17;
typedef struct { s32 x0; u8 pad4[8]; s32 xc; s32 x10; } It17;
typedef struct { u8 b[0x1d0]; } Ob17;
extern St17 D_00449908;
extern s32 D_002C5960;
extern f32 D_002BBDFC;
extern Ob17 D_00650120[];
extern It17 *D_002E3170[];
void func_0023a8d0(Ob17 *);
void func_0023a7e8(void);
void func_0023a720(void);
void func_0023a318(s32, It17 *, s32, s32, Ob17 *, s32, s32, f32);
void func_0023a608(s32, It17 *, s32, s32, f32);

s32 func_0023a968(void) {
    It17 **list;
    It17 *o;
    s32 chg, k, x, y, last;
    f32 v;
    k = -1;
    if (D_00449908.f80 != 0.0f) {
        if (!(D_002C5960 & 1)) D_00449908.f7c += D_00449908.f80 * D_002BBDFC;
        v = D_00449908.f7c;
        if (v <= 0.0f) {
            D_00449908.f80 = D_00449908.f7c = 0.0f;
        } else if (1.0f <= v) {
            D_00449908.f80 = 0.0f;
            D_00449908.f7c = 1.0f;
        }
    }
    chg = 0;
    func_0023a8d0(&D_00650120[0]);
    func_0023a7e8();
    list = D_002E3170;
    o = *list;
    if (o) do {
        if (list[1] == 0 && o->x0 != D_00449908.cur) {
            func_0023a720();
            if (D_00449908.cur < o->x0) {
                D_00449908.t[o->x0] = -1;
                chg = 1;
            }
            D_00449908.cur = o->x0;
        }
        last = list[1] == 0;
        switch (o->x0) {
        case 0:
            func_0023a318(0, o, last, chg, &D_00650120[0], 16, 260, D_00449908.f7c);
            D_00449908.a[0] = o->xc;
            D_00449908.p[0].x = 16;
            D_00449908.p[0].y = 260;
            D_00449908.b[0] = o->x10;
            break;
        case 1:
            x = D_00449908.p[0].x + 11;
            if (o->x10 < 3) y = D_00449908.p[0].y + 22;
            else y = 348 - o->x10 * 22;
            func_0023a318(1, o, last, chg, &D_00650120[1], x, y, D_00449908.f7c);
            D_00449908.a[1] = o->xc;
            D_00449908.p[1].x = x;
            D_00449908.p[1].y = y;
            D_00449908.b[1] = o->x10;
            break;
        case 2:
            x = D_00449908.p[0].x + 11;
            if (o->x10 < 2) y = D_00449908.p[0].y + 44;
            else y = 348 - o->x10 * 22;
            func_0023a318(2, o, last, chg, &D_00650120[2], x, y, D_00449908.f7c);
            D_00449908.a[2] = o->xc;
            D_00449908.p[2].x = x;
            D_00449908.p[2].y = y;
            D_00449908.b[2] = o->x10;
            break;
        case 3:
            x = D_00449908.p[1].x + 11;
            if (D_00449908.p[1].y + o->x10 * 22 + D_00449908.a[1] * 22 + 20 < 369) y = D_00449908.p[1].y + D_00449908.a[1] * 22;
            else y = 348 - o->x10 * 22;
            func_0023a318(3, o, last, chg, &D_00650120[3], x, y, D_00449908.f7c);
            D_00449908.a[3] = o->xc;
            D_00449908.p[3].x = x;
            D_00449908.p[3].y = y;
            D_00449908.b[3] = o->x10;
            break;
        case 4:
            if (list[-1]->x0 == 1) k = 1;
            else if (list[-1]->x0 == 5) k = 5;
            else if (list[-1]->x0 == 2) k = 2;
            if (k != 5) {
                x = D_00449908.p[k].x + 11;
                if (D_00449908.p[k].y + o->x10 * 22 + D_00449908.a[k] * 22 + 20 < 369) y = D_00449908.p[k].y + D_00449908.a[k] * 22;
                else y = 348 - o->x10 * 22;
            } else {
                x = D_00449908.p[5].x;
                y = 348 - o->x10 * 22;
            }
            if (k != 2) func_0023a318(4, o, last, chg, &D_00650120[4], x, y, D_00449908.f7c);
            else func_0023a318(4, o, last, chg, &D_00650120[6], x, y, D_00449908.f7c);
            D_00449908.a[4] = o->xc;
            D_00449908.p[4].x = x;
            D_00449908.p[4].y = y;
            D_00449908.b[4] = o->x10;
            break;
        case 5:
            func_0023a608(0, o, 16, 282, D_00449908.f7c);
            D_00449908.a[5] = -1;
            D_00449908.p[5].x = 16;
            D_00449908.p[5].y = 282;
            D_00449908.b[5] = o->x10;
            break;
        }
        list++;
        o = *list;
    } while (o);
    return 0;
}

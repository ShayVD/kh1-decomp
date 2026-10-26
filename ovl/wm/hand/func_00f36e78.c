/* wm.x func_00f36e78: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[4]; u8 kind; u8 pad2[3]; } En;
typedef struct { s32 n; En e[1]; } Lst;
typedef struct { u8 pad[0xF4]; Lst *lst; } Obj;
typedef struct { u8 pad[0x14]; s32 a; s32 b; s32 c; s32 d; } Src;
typedef struct { Obj *obj; En *e; s32 t; s32 z; s32 c; s32 b; s32 d; s32 a; } Task;
s32 func_00f36380(void);
Task *func_00f363c0(s32);
void func_001c0310(s32, void (*)(s32), s32);
void func_00f36498(s32);
void func_00f36bc0(s32);
void func_00f36e78(s32 arg0, Obj *arg1, Src *arg2) {
    s32 i, t, h, kd;
    En *e;
    Task *k;
    for (i = 0, e = arg1->lst->e; i < arg1->lst->n; i++, e++) {
        t = -1;
        kd = e->kind - 1;
        if (arg0 == 0) {
            switch (kd) {
            case 61: t = 40; break;
            case 62: t = 42; break;
            case 63: t = 45; break;
            }
        } else {
            switch (kd) {
            case 58: t = 33; break;
            case 59: t = 35; break;
            case 60: t = 37; break;
            }
        }
        if (t < 0) continue;
        h = func_00f36380();
        if (h < 0) return;
        k = func_00f363c0(h);
        k->obj = arg1;
        k->a = arg2->a;
        k->e = e;
        k->b = arg2->b;
        k->c = arg2->c;
        k->d = arg2->d;
        k->t = t;
        k->z = 0;
        if (arg0 == 0) {
            func_001c0310(11, func_00f36bc0, h);
        } else {
            func_001c0310(11, func_00f36498, h);
        }
    }
}

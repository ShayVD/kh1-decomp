/* gb.x func_00f4a048: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[4]; u8 state; } Obj;
void func_00f4d880(Obj *, s32);
extern s32 D_00F702D8;
extern s32 D_00F702DC;
extern s32 D_00F82B48;
extern Obj *D_00F82B78[];
extern s32 D_00F82BC8[];
extern s32 D_00F82C58;
extern s32 D_00F82C5C;
extern s32 D_00F82C60;

void func_00f4a048(s32 col, s32 row) {
    s32 i;
    s32 sel;
    Obj *o;
    for (i = 0; i < D_00F82B48; i++) {
        D_00F82B78[i]->state = 0;
    }
    sel = row * 2 + col;
    for (i = 0; i < D_00F82B48; i++) {
        o = D_00F82B78[i];
        if (i == sel) {
            o->state = 1;
            func_00f4d880(o, 8);
        } else {
            o->state = 0;
        }
        if (i == D_00F82C58) {
            if (D_00F82C5C != 0) o->state = 7; else if (i != sel) o->state = 9; else o->state = 7;
        }
        if (i == D_00F82C60) {
            if (D_00F82C5C != 0) o->state = 1; else o->state = 3;
        }
    }
    if (sel >= 0) {
        D_00F702D8 = D_00F702DC = D_00F82BC8[sel] + 1;
    }
}

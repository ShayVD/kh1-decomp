/* gb.x func_00f4a1c0: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[4]; u8 state; } Obj;
void func_00f4d880(Obj *, s32);
extern s32 D_00F702D8;
extern s32 D_00F702DC;
extern s32 D_00F71268;
extern s32 D_00F82BA0[];
extern s32 D_00F82BF0;
extern Obj *D_00F82C30[];

void func_00f4a1c0(s32 col, s32 row) {
    s32 i;
    s32 sel;
    D_00F71268 = row;
    sel = row * 2 + col;
    for (i = 0; i < D_00F82BF0; i++) {
        Obj *o = D_00F82C30[i]; if (i == sel) { o->state = 1; func_00f4d880(o, 8); } else if (i / 2 == row) { o->state = 7; } else { o->state = 9; }
    }
    if (sel >= 0) {
        D_00F702D8 = D_00F702DC = D_00F82BA0[sel] + 1;
    }
}

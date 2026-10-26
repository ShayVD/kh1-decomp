/* dkmovie.x func_00f26d30: matched by hand. */
#include "ovl.h"

typedef struct {
    u8 pad[0x3DD5C];
    s32 dd5c;
    u8 pad1[0x3DEF8 - 0x3DD60];
    s32 def8;
    u8 pad2[0x3DF51 - 0x3DEFC];
    s8 flag;
} MovieWork;
void func_00f227e0(void *, MovieWork *, s32, s32);
void func_00f27fc8(s32, void *, MovieWork *);
extern MovieWork *D_00F28460;

void func_00f26d30(s32 arg0) {
    MovieWork *w = D_00F28460;
    if (w->flag != 0) {
        func_00f227e0((u8 *)w + 0x100, w, w->def8, w->dd5c);
        return;
    }
    func_00f27fc8(arg0, (u8 *)w + 0x100, w);
}

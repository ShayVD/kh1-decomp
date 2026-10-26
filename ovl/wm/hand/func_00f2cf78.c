/* wm.x func_00f2cf78: matched by hand. */
#include "ovl.h"

typedef struct { u8 active; u8 pad[0xD]; u16 snd; u8 pad2[0x80]; } WmS90;
void func_00f68a40(u16);
extern WmS90 D_00FBEBC0[];
void func_00f2cf78(s32 arg0) {
    if (arg0 >= 0) {
        WmS90 *e = &D_00FBEBC0[arg0];
        if (e->active != 0) {
            if (e->snd != 0xFFFF) {
                func_00f68a40(e->snd);
            }
            e->active = 0;
        }
    }
}

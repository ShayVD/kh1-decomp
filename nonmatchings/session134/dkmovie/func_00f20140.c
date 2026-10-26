/* dkmovie.x func_00f20140 (the per-frame callback func_00f20258 installs): draft, 29 words off
 * (the packet base is built in a2 then moved to a1; the original has it in a1, and one
 * instruction fewer). The port compiles it (ovl/dkmovie/drafts.tsv). */
#include "ovl.h"

typedef struct { u8 pad[0x10]; u64 f10; u8 pad2[0x70]; u64 f88; } MoviePkt;
typedef struct { s32 (*open)(s32); s32 (*start)(void); s32 (*close)(void); s32 (*status)(void); s32 (*frame)(void); } MovieTbl;
s32 func_001110d0(void);
s32 func_00106b18(void *, void *);
void sceGsSyncPath(s32, s32);
void func_00f200f8(void);
void func_001111b0(void);
extern s32 D_002BCB34;
extern MoviePkt D_00F28300;
extern u8 D_00F28390[];
extern MovieTbl D_00F28478;

s32 func_00f20140(void) {
    s32 w;
    s32 st;
    if (D_002BCB34 != 1) {
        w = func_001110d0();
        D_00F28300.f10 = ((u64)(w / 64) << 16) | 0x0100008C;
        D_00F28300.f88 = (u64)(w * 16 + 0x7000) | ((u64)0xC800 << 17);
        func_00106b18(D_00F28390, &D_00F28300);
        sceGsSyncPath(0, 0);
        D_00F28478.frame();
        st = D_00F28478.status();
        switch (st) {
        case 4:
            func_00f200f8();
            return 0;
        default:
            return 0;
        case 5:
            break;
        }
    }
    func_001111b0();
    return 4;
}

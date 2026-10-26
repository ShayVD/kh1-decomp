/* dkmovie.x func_00f20258 (entry 0, open movie n): draft, 3 words off (the lui of D_002BCB34
 * is scheduled two slots early). The port compiles it (ovl/dkmovie/drafts.tsv). */
#include "ovl.h"

typedef struct { s32 (*open)(s32); u8 pad[0x18]; s32 f1C; } MovieTbl;
void func_0011ef10(s32, s32 (*)(void));
s32 func_00f20140(void);
extern s32 D_002BCB34;
extern MovieTbl D_00F28478;

void func_00f20258(u32 n) {
    D_002BCB34 = 0;
    func_0011ef10(0x2E630, func_00f20140);
    D_00F28478.open(n);
    switch (n) {
    case 0:
    case 1:
        D_00F28478.f1C = 0x28;
        break;
    case 2:
        D_00F28478.f1C = 0x58;
        break;
    case 4:
        D_00F28478.f1C = 0x30;
        break;
    case 5:
        D_00F28478.f1C = 0x10;
        break;
    default:
        D_00F28478.f1C = 0;
        break;
    }
}

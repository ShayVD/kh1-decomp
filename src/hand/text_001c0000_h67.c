#include "common.h"
#include "vm/script_vm.h"
#include "data/types/vm_rec.h"
#include "data/types/text_001c0000_h67.h"
extern Str D_00389C90;

/* func_001cb7d0, func_001cb960, func_001cbbd0 and func_001cbfc0 (and D_0062A1F0) are in src/msgwin/msgwin.c. */

/* func_001cf478 and func_001cf5d0 are in src/vm/vm_lib.c. */

#include "data/pieces/D_003A7990.h"
#include "data/pieces/D_003C3A70.h"
#include "data/pieces/D_0038D170.h"
#include "data/pieces/D_0039A580.h"

#include "data/types/text_001c0000_h67_p.h"
extern V4 D_00490630;


#include "data/pieces/D_002BC0F0.h"
extern f32 D_002BBDFC;

/* func_001dcfd0 is in src/vm/vm_lib.c. */

#include "data/pieces/D_002E2790.h"
#include "data/pieces/D_002E2780.h"
/* func_001dedd8, func_001def20 are in src/event/effect.c. */


extern s32 D_003DAD38;
#include "data/pieces/D_003DAD3C.h"
extern f32 D_003DACB0;
extern f32 D_003DACB4;
extern s32 D_003DACB8;
extern s32 D_003DACBC;
extern u64 D_003DAE40[];
extern u8 D_003DAF60[];
void func_001e06c8(s32);
void func_001e05a8(void *);
s32 func_001e08d8(void) {
    f32 sx, sy;
    s32 ox, oy;
    u64 v, w;
    if (!D_003DAD38) return 4;
    func_001e06c8(D_003DAD3C);
    D_003DAE40[26] = 0x8080;
    sx = D_003DACB0;
    ox = D_003DACB8;
    D_003DAE40[15] = 0x180808080ULL;
    v = (f32)(ox + 0x7000) + (4096.0f - sx * 4096.0f);
    oy = D_003DACBC;
    sy = D_003DACB4;
    w = (f32)(oy + 0x73f8) + (3072.0f - sy * 3072.0f);
    D_003DAE40[31] = 0x180808080ULL;
    D_003DAE40[33] = v | (w << 16) | 0xFFFFFFFE00000000ULL;
    v = (sx * 8192.0f * 0.5f - 4096.0f + 36864.0f) + (f32)ox;
    w = (sy * 6144.0f * 0.5f - 3072.0f + 35840.0f - 8.0f) + (f32)oy;
    D_003DAE40[35] = v | (w << 16) | 0xFFFFFFFE00000000ULL;
    func_001e05a8(D_003DAF60);
    return 0;
}

/* needs make: uses rodata */
extern char D_003DABD8[][6];
/* func_001ddc78 and func_001dde08 (and D_0062A228) are in src/event/effect.c. */

#include "data/data_0039.h"
#include "data/data_003A.h"
#include "data/data_003B.h"
#include "data/data_003C.h"
#include "data/data_003D.h"
#include "data/pieces/D_00389C90.h"
#include "data/pieces/D_002BBDFC.h"
#include "data/pieces/D_003DABD8.h"
#include "data/pieces/D_00490630.h"

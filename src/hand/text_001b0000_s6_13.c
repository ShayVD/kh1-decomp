#include "common.h"
#include "data/types/vm_rec.h"
#include "data/bss_0062.h"

#include "data/pieces/D_0037A378.h"
#include "data/types/text_001b0000_s6_13.h"
/* rodata */

typedef struct { u16 used; u16 h2; u16 h4; u8 pad6[26]; void (*fn)(void); u8 pad36[12]; } Slot;
extern Slot *D_0037A16C;
CONTEXT_ONLY void func_001bfcd8(void) { D_0037A16C = 0; }
CONTEXT_ONLY void func_001bffa0(s32 i) {
    if (i >= 0) {
        if (D_0037A16C[i].fn) D_0037A16C[i].fn();
        D_0037A16C[i].used = 0;
        D_0037A16C[i].h2 = 0;
        D_0037A16C[i].h4 = 0;
    }
}

#include "data/pieces/D_003B4DA0.h"
#include "data/pieces/D_003A7990.h"
extern f32 D_002BBDFC;
#include "vm/script_vm.h"
typedef struct { u64 a, b, c, d; } MsgQ; extern s32 D_006297F0, D_006297F4; extern MsgQ D_006277F0[256];
#include "data/pieces/D_0039A580.h"
#include "data/pieces/D_0038D170.h"
CONTEXT_ONLY s32 func_001c1ce8(s8 *a, s32 b) { return a[b * 4 + 3]; }
#include "data/data_0037.h"
#include "data/data_0039.h"
#include "data/data_003A.h"
#include "data/data_003B.h"
#include "data/data_003C.h"
#include "data/pieces/D_002BBDFC.h"

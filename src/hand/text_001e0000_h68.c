#include "common.h"
#include "data/bss_0062.h"

typedef int u128 __attribute__((mode(TI)));
#include "data/types/text_001e0000_h68.h"

#include "data/pieces/D_00304BE8_s.h"
extern s32 D_003F7A68;
#include "data/pieces/D_003DBA68.h"
#include "data/pieces/D_003DC2A8.h"
#include "data/pieces/D_003DC370.h"
#include "data/pieces/D_003DCB90.h"
#include "data/pieces/D_003DD230.h"
extern s32 D_003DD258;
extern s32 D_003DD28C;
extern s32 D_003C21A0;
#include "data/pieces/D_003C3A70.h"
extern s32 D_003C54F0;
extern u8 D_00490940[];

void func_0011fbb0(s32, s32, s32, s32, s32, s32, s32, s32, void *, void *);
s32 func_001205f0(void *, void *);
void *func_001559f0(s32, s32);
s32 func_00266c08(s32);
void func_00266f38(s32, void *);
s32 sceGsSyncPath(s32, s32);
void FlushCache(s32);

/* func_001e2a88, func_001e2d08, func_001e2f98, func_001e4070, func_001e4318, func_001e4578 are in src/shop/shop.c. */

/* func_001e5d78, func_001e5ee0, func_001e61c0, func_001e72a0, func_001e7ba8 are in src/list/list.c. */

/* func_001e9670 is in src/screen/wave.c. */

/* func_001e9b98 is in src/vm/vm_find.nofill.c. */

void func_001ef950(void)
{
    u128 b[11];
    u128 a[11];
    u8 *p;

    p = func_001559f0(52, 12);
    func_001205f0(D_00490940, p);
    func_0011fbb0(16380, 1, 0, 0, 0, 16, 16, 64, p + 0x10000, a);
    FlushCache(0);
    func_00266f38(func_00266c08(2), a);
    sceGsSyncPath(0, 0);
    func_0011fbb0(4096, 4, 36, 0, 0, 256, 256, 2048, p, b);
    FlushCache(0);
    func_00266f38(func_00266c08(2), b);
    sceGsSyncPath(0, 0);
    func_0011fbb0(4096, 4, 44, 0, 0, 256, 256, 2048, p + 0x8000, b);
    FlushCache(0);
    func_00266f38(func_00266c08(2), b);
    sceGsSyncPath(0, 0);
}

#include "data/data_0039.h"
#include "data/data_003A.h"
#include "data/data_003B.h"
#include "data/data_003D.h"
#include "data/data_003E.h"
#include "data/data_0049.h"
#include "data/pieces/D_003DD258.h"
#include "data/pieces/D_003DD28C.h"
#include "data/pieces/D_003F7A68.h"

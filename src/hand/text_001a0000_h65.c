#include "common.h"
#include "data/bss_0062.h"

typedef struct { u8 b[64]; } Blk64;
typedef struct { u8 pad[0x9c20]; Blk64 a; u8 pad2[0xa420 - 0x9c60]; Blk64 b; } SaveRow;
void func_001b9b30(void);
Blk64 *func_00232cc0(s32);
s32 func_001baf70(s32, Blk64 *, Blk64 *);

s32 func_001bafb0(s32 i, Blk64 *src) {
    SaveRow *r;
    func_001b9b30();
    r = (SaveRow *)(i * 64 + (u32)func_00232cc0(4));
    r->a = *src;
    if (func_001baf70(i, src, &r->b) > 0) {
        r->b = *src;
        return 1;
    }
    return 0;
}

/* needs make: uses rodata */

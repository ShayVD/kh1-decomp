/* Hand-matched functions near 0x130000 (worker 6). */
#include "common.h"
#include "data/bss_0052.h"

typedef struct {
    s32 a;
    s32 b;
} W6Pair;
W6Pair D_0052A110[0x8] ALIGNED(16);

#include "data/pieces/D_00304BE8_s.h"
typedef W606Mem_304be8 W6SEnt;

typedef struct {
    u8 pad00[0x40];
    u8 b40;
    u8 pad41[0x48 - 0x41];
    s32 w48;
    u8 pad4c[0xF0 - 0x4C];
} W6Info;

u8 D_0052AD58[0x10] ALIGNED(8);
void func_00141b10(s32 i, W6Info *info);
void func_0014f830(s32 a, s32 b, s32 c, s32 d, void (*e)(void), void (*f)(void), void (*g)(void), s32 h, s32 i);

s32 func_00120748(s32 a, s32 b, void (*c)(void), s32 d);
void func_0011ef10(s32 a, void (*b)(void));

void func_0013bf90(s32 on) {
    if (on) {
        D_00304BE8->f880 = 1;
    } else {
        D_00304BE8->f880 = 0;
    }
}

void func_0013c078(void) {
    W6Info info;
    W6SEnt *e;
    s32 i;
    for (i = 0; i < 10; i++) {
        e = &D_00304BE8->m[i];
        func_00141b10(i, &info);
        e->sub.x1 = info.b40;
        if (e->sub.x3 < info.w48) {
            e->sub.x38 = 0;
            e->sub.x3 = info.w48;
        }
    }
}
#include "data/data_002B.h"
#include "data/data_0030.h"

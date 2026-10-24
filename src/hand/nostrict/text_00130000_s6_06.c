#include "common.h"
#include "data/bss_0052.h"
/* Hand-matched functions (session 6, worker w606), all -fno-strict-aliasing. */

/* Hand-matched functions near 0x13C000-0x145000 (worker 7). */

#include "data/pieces/D_00304BE8_s.h"
typedef W606Mem_304be8 W606Mem;

typedef struct W606Ch W606Ch;
struct W606Ch {
    u32 flags;
    f32 x4[4];
    f32 x14;
    f32 x18;
    f32 x1c;
    u8 pad020[0x6c - 0x20];
    void *x6c;
    s32 x70;
    u8 pad074[0x130 - 0x74];
    u8 *info;
    u8 pad134[0x148 - 0x134];
    s32 x148;
    u8 pad14c[0x2D4 - 0x14C];
    f32 x2d4;
    u8 pad2d8[0x360 - 0x2D8];
    s32 x360;
    u8 pad364[0x370 - 0x364];
    u64 x370;
    u8 pad378[0x398 - 0x378];
    W606Ch *x398;
};

extern u16 *D_00304BB0[];
extern u16 *D_00304B88[];
void *func_001477c8(void *p);
u16 *func_0013c3f8(s32 i);
void func_0015b268(s32 i);
void func_0015b438(s32 i);
s32 func_0013c458(s32 i, s32 n) {
    W606Mem *m = &D_00304BE8->m[i];
    u16 *p = func_0013c3f8(i);
    s32 lv = 1;
    s32 first = 1;
    s32 e = n + m->sub.exp;
    if (e > 999999) e = 999999;
    m->sub.exp = e;
    while (lv < 100) {
        e -= *p++;
        if (e < 0) break;
        lv++;
        if (m->sub.lv < lv) {
            func_0015b268(i);
            if (first) {
                first = 0;
                func_0015b438(i);
            }
        }
    }
    return m->sub.exp;
}

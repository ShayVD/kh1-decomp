/* Hand-matched functions near 0x130000 (worker 32). */
#include "common.h"
#include "data/bss_0052.h"

#include "data/types/text_00130000_h32.h"
typedef struct {
    u8 pad00[0x70];
    u8 x70;
    u8 pad71[0x74 - 0x71];
} W32SEnt;
s32 func_001331d8(s32 i, s32 j, void (*cb)(void));
typedef struct {
    u8 pad00[0x48];
    void (*x48)(s32);
} W32Proc;
W32Proc *func_001208e0(void (*f)(void));
s32 func_0011ef38(void (*f)(void));
void func_0011ef10(s32 a, void (*f)(void));
typedef struct {
    u32 flags;
    u8 pad004[0x1C - 0x4];
    f32 x1c;
    u8 pad020[0x60 - 0x20];
    f32 x60;
    u8 pad064[0xA0 - 0x64];
    f32 xa0[4];
    u8 pad0b0[0xD0 - 0xB0];
    f32 xd0[4][4];
    f32 x110[2];
    f32 x118;
    f32 x11c;
    u8 pad120[0x154 - 0x120];
    s32 x154;
    u8 pad158[0x350 - 0x158];
    s32 tgt[4];
    u8 pad360[0x370 - 0x360];
    union {
        u64 x;
        u8 c[4];
    } u370;
    u8 pad378[0x38C - 0x378];
    s32 x38c;
    u8 pad390[0x394 - 0x390];
    s32 x394;
} W32Col;
/* func_00135d38 moved to src/obj/objvis.c (session 53); this CONTEXT_ONLY copy keeps
   func_00136bc0 below matching (without it 3 words differ). */
CONTEXT_ONLY void func_00135d38(W32Col *o) {
    s32 i;
    if ((s32)(o->u370.x >> 46) & 1) {
        for (i = 0; i < 4; i++) {
            u8 *q = &o->u370.c[i];
            s32 cur = *q;
            s32 d = o->tgt[i] - cur;
            s32 c;
                        if (d >= -4) c = cur + (d < 5 ? d : 4);
            else c = cur - 4;
            *q = c;
        }
    } else {
        for (i = 0; i < 4; i++) o->u370.c[i] = o->tgt[i];
    }
    o->u370.x |= 1ULL << 46;
}
extern u32 D_002C5958;
s32 D_0052ABF0[2][32] ALIGNED(16);
extern u32 D_002C5958;
#include "data/types/text_00130000_h32_p.h"
typedef struct {
    u8 pad00[0x30];
    f32 x30;
    f32 x34;
    f32 x38;
    f32 x3c;
} W32Spr;
W32Spr *D_0052AD00 ALIGNED(16);
extern s32 D_0052AE54;
extern s32 D_00304B40;
extern s32 D_00304B44;
extern void *D_0052AE5C;
s32 func_00120748(char *name, void *dst, void (*cb)(void), s32 d);
void func_0011ef10(s32 a, void (*f)(void));
extern s32 D_0052AE54;
extern void *D_0052AE5C;
void func_00146a68(void *p, s32 a, void (*cb)(void), s32 b);
void func_0011ef58(void (*f)(void));
typedef struct { u16 x0; u16 x2; } W32Ent;
extern W32Ent *func_001478a0(s32 id);
void func_0013bfb8(u8 *a) {
    s32 i, j;
    u8 t;
    for (i = 47; i > 0; i--) {
        if (a[i] == 0) continue;
        for (j = 0; j < i; j++) {
            W32Ent *p = func_001478a0(a[j]);
            W32Ent *q = func_001478a0(a[j + 1]);
            if (p->x2 > q->x2) {
                t = a[j];
                a[j] = a[j + 1];
                a[j + 1] = t;
            }
        }
    }
}
/* needs make: uses rodata */

/* Pointer tables only this file uses (phase 4, tools/shift/define_ptr_tables.py). */
extern u8 D_0048DCA0[];
s32 D_00304B40 ALIGNED(16) = (s32)D_0048DCA0;
extern u8 D_0048DCA8[];
s32 D_00304B44 ALIGNED(4) = (s32)D_0048DCA8;
#include "data/data_002B.h"
#include "data/data_0030.h"
#include "data/data_0048.h"
#include "data/pieces/D_002C5958.h"

/* The heaps: the main heap D_004F45B0 of 128-byte aligned blocks over
 * D_00820000 (func_00121e28 allocates for an owner pointer, func_00121eb0
 * frees the last, func_00121c78 the set up, func_00121b98 the ageing pass,
 * func_00121d00 / func_00121d60 / func_00121de0 the block list) and the
 * scratchpad stack D_004F6EB8 at 0x70000000 (func_00122028 resets it,
 * func_00122048 pushes an aligned frame, func_001220b8 pops). Flag mode:
 * default (the other modes are in the sibling files). Read from the code,
 * not proved by a boot (docs/modules.md "Session 54"). */
#include "m2c.h"
#include "actor.h"
#include "data/bss_004F.h"
#include "data/pieces/D_002E26A0.h"
#include "common.h"
#include "platform/thread.h"
#include "platform/dma.h"
#include "platform/math.h"
#include "data/pieces/D_002BBDE0.h"
#include "data/types/text_00110000_h4_p.h"
#include "data/pieces/D_002C5C80.h"
#include "data/types/text_00110000_h4.h"

/* func_00121b98 (from auto/text_00120000_3.c). */
M2C_UNK func_00121f6c(s32, s32, s32);
extern Block D_004F45B0[];
#define D_004F45B0 (*(M2C_UNK (*)) &D_004F45B0)
s32 func_00121b98(void) {
    M2C_UNK *var_a1;
    M2C_UNK *var_s0;
    s32 temp_s1;
    s32 temp_v0;
    u32 temp_a0;
    u32 var_s2;

    var_a1 = &D_004F45B0;
    var_s0 = M2C_FIELD(&D_004F45B0, M2C_UNK **, 0x10);
    var_s2 = 0;
    if (var_s0 != NULL) {
        do {
            temp_a0 = M2C_FIELD(var_s0, u32 *, 0) + 1;
            M2C_FIELD(var_s0, u32 *, 0) = temp_a0;
            if (M2C_FIELD(var_s0, s32 **, 0xC) == NULL) {
                M2C_FIELD(var_s0, s32 *, 4) = 0;
                M2C_FIELD(var_a1, M2C_UNK **, 0x10) = (M2C_UNK *) M2C_FIELD(var_s0, M2C_UNK **, 0x10);
            } else {
                if ((var_s2 <= 0x1FFFFU) && (temp_a0 >= 4U)) {
                    temp_v0 = M2C_FIELD(var_s0, s32 *, 4);
                    temp_s1 = M2C_FIELD(var_a1, s32 *, 4) + M2C_FIELD(var_a1, s32 *, 8);
                    if ((temp_v0 - temp_s1) > 0) {
                        func_00121f6c(temp_v0, temp_s1, M2C_FIELD(var_s0, s32 *, 8));
                        M2C_FIELD(var_s0, s32 *, 4) = temp_s1;
                        *M2C_FIELD(var_s0, s32 **, 0xC) = temp_s1;
                        var_s2 += M2C_FIELD(var_s0, s32 *, 8);
                    }
                }
                var_a1 = var_s0;
            }
            var_s0 = M2C_FIELD(var_s0, M2C_UNK **, 0x10);
        } while (var_s0 != NULL);
    }
    return 0;
}
#undef D_004F45B0

/* func_00121d00 (from hand/text_00110000_h4.c). */
extern Block *D_004F6DB0;
Block *func_00121d00(void) {
    Block *p = D_004F6DB0;
    s32 i;
    for (i = 1; i < 512; i++) {
        p++;
        if (p >= &D_004F45B0[512]) p = &D_004F45B0[1];
        if (p->addr == 0) { D_004F6DB0 = p; return p; }
    }
    return 0;
}

/* func_00121d60 (from hand/text_00110000_h4.c). */
extern u8 D_009A0000[];
Block *func_00121d60(u32 size) {
    Block *p = D_004F45B0;
    Block *n;
    while ((n = (Block *)p->next) != 0) {
        if (n->addr - (p->addr + p->size) >= size) return p;
        p = n;
    }
    if ((u32)D_009A0000 - (p->addr + p->size) >= size) return p;
    return 0;
}

/* func_00121de0 (from hand/text_00110000_h4.c). */
Block *func_00121de0(u32 addr) {
    Block *p;
    for (p = (Block *)D_004F45B0[0].next; p; p = (Block *)p->next) {
        if (p->addr == addr) return p;
    }
    return 0;
}

/* func_00121e28 (from hand/text_00110000_h4.c). */
u32 func_00121e28(u32 size, u32 *out) {
    Block *b, *p;
    size = (size + 127) & ~127;
    b = func_00121d00();
    p = func_00121d60(size);
    b->addr = p->addr + p->size;
    if (out) *out = b->addr;
    b->size = size;
    b->owner = (u32)out;
    b->f0 = 0;
    b->next = p->next;
    p->next = (u32)b;
    return b->addr;
}

/* func_00121eb0 (from auto/text_00120000.c). */
#define func_00121de0 ((void *(*)()) func_00121de0)
void func_00121eb0(u32 addr) {
    s32 *temp_v1;
    void *temp_v0;

    temp_v0 = func_00121de0(addr);
    temp_v1 = M2C_FIELD(temp_v0, s32 **, 0xC);
    if (temp_v1 != NULL) {
        *temp_v1 = 0;
    }
    M2C_FIELD(temp_v0, s32 **, 0xC) = NULL;
}
#undef func_00121de0

/* func_00121ee0 (from hand/text_00110000_h4.c). */
void func_00121ee0(u32 addr) {
    Block *prev = D_004F45B0;
    Block *p;
    while ((p = (Block *)prev->next) != 0 && p->addr != addr) prev = p;
    if (p->owner) *(u32 *)p->owner = 0;
    p->owner = 0;
    p->addr = 0;
    prev->next = p->next;
}

/* func_00121f30 (from auto/text_00120000_15.c). */
#define func_00121de0 ((s32 (*)(s32)) func_00121de0)
void func_00121f30(s32 arg0, s32 arg1) {
    s32 temp_v0;

    temp_v0 = func_00121de0(arg0);
    *(M2C_UNK *)arg1 = arg0;
    M2C_FIELD(temp_v0, s32 *, 0xC) = arg1;
    M2C_FIELD(temp_v0, s32 *, 0) = 0;
}
#undef func_00121de0

/* func_00122028 (from auto/text_00120000_16.c). */
extern volatile M2C_UNK *D_004F6EB8;
extern volatile M2C_UNK D_004F6DB8;
void func_00122028(void) {
  volatile M2C_UNK *new_var;
  s8 *new_var2;
  new_var2 = (s8 *) (new_var = &D_004F6DB8);
  *((s32 *) (new_var2 + 4)) = PLAT_SPR_BASE;
  *((s32 *) (0 + ((s8 *) new_var))) = PLAT_SPR_BASE;
  D_004F6EB8 = &D_004F6DB8;
}

/* func_00122048 (from hand/text_00110000_h4.c). */
extern u32 *D_004F6EB8_00122048 __asm__("D_004F6EB8");
#define D_004F6EB8 D_004F6EB8_00122048
u32 func_00122048(u32 size, u32 align) {
    u32 *p = D_004F6EB8;
    u32 *old = p;
    u32 v;
    p += 2;
    D_004F6EB8 = p;
    v = (old[1] + align - 1) / align * align;
    p[0] = v;
    if (size) D_004F6EB8[1] = v + size;
    else D_004F6EB8[1] = PLAT_SPR_END;
    return v;
}
#undef D_004F6EB8

/* func_001220b8 (from auto/text_00120000.c). */
extern s32 D_004F6EB8_001220b8 __asm__("D_004F6EB8");
#define D_004F6EB8 D_004F6EB8_001220b8
void func_001220b8(void) {
    D_004F6EB8 -= 8;
}
#undef D_004F6EB8

/* func_001220d0 (from auto/text_00120000.c). */
void func_001220d0(void) {
    PlatPcStop();
}


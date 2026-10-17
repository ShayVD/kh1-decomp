/* 1 word off: original uses dsrl for the second >>2 (u8 kept in a u64 somewhere?); ours srl. mode hand (strict) */
#include "common.h"
typedef struct {
    u8 pad[7];
    u8 f7;
    u8 pad8[0x14];
} It28;
extern It28 *D_0062321C;

s32 func_001bb6d0(s32 i) {
    u8 x = D_0062321C[i].f7; s32 a, b, c; a = (x & 3) + 1; x >>= 2; b = (x & 3) * 16 + 16; x >>= 2; c = (x & 3) + 1; return b | a | (c << 8);
}

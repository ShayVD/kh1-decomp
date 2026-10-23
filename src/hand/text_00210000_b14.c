#include "common.h"
#include "data/pieces/D_00304BE8_s.h"
#include "data/bss_0064.h"
#include "data/types/text_00210000_b14_p.h"
typedef Sub_304be8 Sub;
typedef W606Mem_304be8 Rec74;
#include "data/types/text_00210000_b14.h"
extern Sub *D_00642C30; /* src/data/bss_0064.c: s32 D_00642C30 */
s32 D_00642C34 ALIGNED(4);
s32 D_00642C38 ALIGNED(8);
extern s32 D_00642C3C;
s32 D_00642C40 ALIGNED(16);
s32 D_00642C4C ALIGNED(4);
s32 D_00642C50 ALIGNED(16);
extern s32 D_00642C6C;

static inline s32 col(s32 x, s32 y) {
    if (x < y) return 0x80FC927A;
    if (x == y) return 0x80808080;
    return 0x806E6EFF;
}

#define D_00642C3C (*(u32 *)&D_00642C3C)
#define BYTE D_00642C30->name[D_00642C34]
#undef D_00642C3C
#undef BYTE

#define D_00642C6C (*(u16 *)&D_00642C6C)
#undef D_00642C6C

#define D_00642C6C (*(u16 *)&D_00642C6C)
#undef D_00642C6C
#include "data/data_003F.h"
#include "data/pieces/D_003F40D0.h"

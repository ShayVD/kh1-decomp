#include "common.h"

#include "platform/math.h"
#include "data/bss_0054.h"

typedef struct { u8 pad[0x70]; s32 x70; u8 pad74[0x164 - 0x74]; s32 x164; } A3e80;
CONTEXT_ONLY void func_00153d88(A3e80 *a) { a->x70 = 0; }

typedef struct { s8 id; u8 n; u8 x2; u8 x3; u8 pad[0x44 - 4]; s32 x44; } E5878;
extern E5878 D_00550400[]; /* src/data/bss_0055.c: E550400 D_00550400[0x34] */

CONTEXT_ONLY void func_00155be0(s32 a) { D_00550400[a].x3 = 0; }

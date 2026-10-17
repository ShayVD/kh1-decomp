/* func_001c1718: matches ONLY when compiled with -fno-sched-interblock (or -fno-sched-spec)
   plus CONTEXT_ONLY func_001c0bf0 above (strict mode). With normal -O2 it is 32 words off:
   sched1 interblock speculatively hoists `li a1,4` and the index shifts. Our version has 10
   basic blocks at sched1 = one region; the original must have had >10 (or the file used
   no interblock). */
#include "common.h"
typedef struct {
    u8 pad[380]; s32 pc; s32 sp; s32 stack[33]; s32 regs[26]; s32 vars[32]; s32 vidx;
    s32 w756; s32 ret[8]; s32 depth; u8 pad796[12]; u64 flags;
} VM;
u8 *func_00232cc0(s32);
extern s32 D_0038B4C4[];
extern s32 D_0038ACC4[];
CONTEXT_ONLY s64 func_001c0bf0(s64 x, u32 type) {
    switch (type) {
    case 0:
    case 1:
        x &= 1;
    case 2:
        if (x < -128) x = -128;
        else if (x >= 127) x = 127;
        break;
    case 3:
        if (x < -32768) x = -32768;
        else if (x >= 32767) x = 32767;
        break;
    case 4:
        if (x < -0x800000) x = -0x800000;
        else if (x >= 0x7fffff) x = 0x7fffff;
        break;
    case 5:
        if (x < 0) x = 0;
        else if (x >= 255) x = 255;
        break;
    case 6:
        if (x < 0) x = 0;
        else if (x >= 0xffff) x = 0xffff;
        break;
    case 7:
        if (x < 0) x = 0;
        else if (x >= 0xffffff) x = 0xffffff;
        break;
    }
    return x;
}
s32 func_001c1718(VM *v, s32 a) {
u8 *p1 = func_00232cc0(1); u8 *p2 = func_00232cc0(2); if (a < 2048) { *(s32 *)(p1 + a) = func_001c0bf0(v->stack[v->sp], 4); v->sp--; } else if (a < 2304) { a -= 2048; *(s32 *)(p1 + a + 2048) = func_001c0bf0(v->stack[v->sp], 4); v->sp--; } else if (a < 2816) { a -= 2304; if ((s32)(v->flags >> 5) & 1) { D_0038B4C4[a] = v->stack[v->sp]; v->sp--; } else { D_0038ACC4[a] = v->stack[v->sp]; v->sp--; } } else { a -= 3392; *(s32 *)(p2 + a) = func_001c0bf0(v->stack[v->sp], 4); v->sp--; } return 2;
}


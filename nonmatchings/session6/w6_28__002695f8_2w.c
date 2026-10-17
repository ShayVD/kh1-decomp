/* 2 words off (sdk/gcc991111): original has 'L: b top; sw zero,D_0046C630' with beqz to L; ours 'L: sw; b; nop' (assembler won't move labeled sw into b slot). Non-volatile final store gives beqzl instead. */
/* Context: near/ctx.h (header of src/sdk/gcc991111/text_00260000_s2.c plus extra declarations). */
#include "ctx.h"
void func_002695f8(void) {
    while (1) {
        WaitSema(D_0046C620);
        if (D_0046C654 == -1) {
            VS(D_0046C630) = 0;
            D_0046C654 = 0;
            D_0046C614 = 0;
            D_0067334C = 0;
            ExitDeleteThread();
        }
        if (D_0046C610 > 0) scePrintf(D_004930E0, D_00673340, D_0046C658);
        if (D_00673340 && VS(D_0046C658)) ((void (*)(s32))D_00673340)(D_0046C658);
        VS(D_0046C630) = 0;
    }
}

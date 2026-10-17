/* 2 words off (sdk/gcc991111): sw D_0046C628 must sit in the 2nd CreateSema jal slot; ours puts move a0,sp there (scheduler order of move a0 vs the store). */
/* Context: near/ctx.h (header of src/sdk/gcc991111/text_00260000_s2.c plus extra declarations). */
#include "ctx.h"
void func_00269830(void) {
    SemaParam p;
    if (D_0046C628 == -1 || D_0046C62C == -1) {
        p.option = 0;
        p.init_count = 1;
        p.max_count = 1;
        D_0046C628 = CreateSema(&p);
        D_0046C62C = CreateSema(&p);
        p.init_count = 0;
        VS(D_0046C620) = CreateSema(&p);
        VS(D_0046C630) = 0;
    }
}

/* func_001db658: 32 words off (hand). Item address computed D+(i+off) instead of (i+off)+D, extra move a2,a3 + nop before loop. */
typedef struct { u8 pad0[0x1c]; u8 n; u8 it[0x74 - 0x1d]; } ChrB;
#define SB ((ChrB *)D_00304BE8)
s32 func_001db658(VM *vm) {
    s32 i;
    for (i = 0; i < SB[vm->stk[vm->sp - 1]].n; i++) {
        u8 *p = &((u8 *)D_00304BE8)[i + vm->stk[vm->sp - 1] * 0x74 + 0x1d];
        if (*p == 0) { *p = vm->stk[vm->sp]; break; }
    }
    vm->sp -= 2;
    return 2;
}

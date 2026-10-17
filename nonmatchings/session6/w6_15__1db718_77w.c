/* func_001db718: 77 words off (hand). Logic right; orig recomputes &stk[sp] inside the loops (no hoist) and keeps a copy of sp. */
typedef struct { u8 pad0[0x590]; u8 pad590[9]; u8 a599[48]; } SaveK;
#define SK ((SaveK *)D_00304BE8)
s32 func_001db718(VM *vm) {
    s32 i;
    u8 b;
    if (vm->stk[vm->sp - 1] == 11) {
        for (i = 0; i < 48 && (SK->a599[i] & 0x7f); i++) {
            b = SK->a599[i];
            if ((b & 0x7f) == vm->stk[vm->sp] && (b & 0x80)) {
                SK->a599[i] = b & 0x7f;
                break;
            }
        }
    } else {
        u8 *e = (u8 *)D_00304BE8 + vm->stk[vm->sp - 1] * 0x74 + 4;
        for (i = 0; i < 48 && (e[i + 0x40] & 0x7f); i++) {
            b = e[i + 0x40];
            if ((b & 0x7f) == vm->stk[vm->sp] && (b & 0x80)) {
                e[i + 0x40] = b & 0x7f;
                break;
            }
        }
    }
    vm->sp -= 2;
    return 2;
}

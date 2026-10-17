/* func_001d63e8: 22 words off (mode hand). Logic matches; register numbering shifted (k in a1 not a0, vm in t5 not t3). */
typedef struct { s32 key; s32 pad; u64 d[5]; } E48;
typedef struct { u8 pad0[0x3178]; s32 n; s32 pad317c; E48 e[8]; } Big63;
extern Big63 D_00389C90;
s32 func_001d63e8(VM *vm) {
    s32 i, j, k, m;
    for (i = 0; i < D_00389C90.n; i = k) {
        k = i + 1;
        if (D_00389C90.e[i].key == vm->stk[vm->sp]) {
            m = D_00389C90.n; if (k < m) { j = k; do { D_00389C90.e[j - 1] = D_00389C90.e[j]; j++; } while (j < D_00389C90.n); k = i; m = D_00389C90.n; } D_00389C90.n = m - 1;
        }
    }
    vm->sp--;
    return 2;
}

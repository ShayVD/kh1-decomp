/* func_001cb3c0: 21 words off (strict or nostrict). Off: scheduling of the D_00388480 store vs the w[n] address; orig loads h (lhu) right after i. */
typedef struct {
    u8 b[4]; u8 c[8];
    union { u8 d[8]; struct { u8 pad[4]; u16 tbl[8][256]; } t; } u;
    s32 w[4]; u8 pad4128[16]; s8 idx[4]; u8 pad4148[8192];
    s32 w12340; s32 w12344; u8 pad12348[52]; u64 d12400; u64 d12408;
    u8 pad12416[192]; s32 w12608; s32 *p12612;
} Big;
extern Big D_00389C90;
extern union { s32 i; u16 h; } D_00389C80;
extern s32 D_00388480[];
extern u8 D_003C57E0[];
s32 func_001cb3c0(VM *vm) {
    s32 n, i, k;
    u16 h;
    Big *b;
    b = &D_00389C90;
    n = vm->stk[vm->sp];
    i = D_00389C80.i;
    h = D_00389C80.h;
    D_00388480[i] = (s32)D_003C57E0;
    k = b->w[n];
    b->w[n] = k + 1;
    b->u.t.tbl[n][k] = h;
    vm->sp--;
    return 2;
}

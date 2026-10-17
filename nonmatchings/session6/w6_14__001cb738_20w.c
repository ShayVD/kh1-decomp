/* func_001cb738: ~20 words off (src/hand; same in nostrict). Sibling of cb3c0; scheduling/register order of the D_00389C80/D_00389C90/D_003C5640 address setup and final stores. */
typedef struct {
    u8 b[4]; u8 c[8];
    union { u8 d[8]; struct { u8 pad[4]; u16 tbl[8][256]; } t; } u;
    s32 w[4]; u8 pad4128[16]; s8 idx[4]; u8 pad4148[8192];
    s32 w12340; s32 w12344; u8 pad12348[52]; u64 d12400; u64 d12408;
    u8 pad12416[192]; s32 w12608; s32 *p12612;
} Big;
extern Big D_00389C90;
extern union { s32 i; u16 h; } D_00389C80;
extern void *D_00388480[];
extern u8 D_003C5640[];
extern s32 D_002BBAB0;
s32 func_001cb738(VM *vm) {
    s32 n, v, k, i;
    u16 h;
    n = vm->stk[vm->sp - 1];
    v = vm->stk[vm->sp];
    vm->sp -= 2;
    k = D_00389C90.w[n];
    i = D_00389C80.i;
    h = D_00389C80.h;
    D_002BBAB0 = v;
    D_00388480[i] = D_003C5640;
    D_00389C90.u.t.tbl[n][k] = h;
    D_00389C90.w[n] = k + 1;
    D_00389C80.i = i + 1;
    return 2;
}

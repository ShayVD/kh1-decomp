/* func_001cac98: 6 words off, mode hand/nostrict. Off: D_0062A1E0.fn store must precede the stk[sp-1] load (a,fn,b order) but that order flips a0/a1/v1 allocation (7 words). */
typedef struct {
    u8 b[4]; u8 c[8];
    union { u8 d[8]; struct { u8 pad[4]; u16 tbl[8][256]; } t; } u;
    s32 w[4]; u8 pad4128[16]; s8 idx[4]; s32 arr[2048];
    s32 w12340; s32 w12344; u8 pad12348[52]; u64 d12400; u64 d12408;
    u8 pad12416[192]; s32 w12608; s32 *p12612;
} BigE;
extern BigE D_00389C90;
typedef struct { s32 a; s32 b; void (*fn)(); s32 d; } Cb;
extern Cb D_0062A1E0;
typedef struct { u8 pad[176]; } E176;
extern E176 D_00629E70[];
typedef struct { s32 x0; u8 pad4[0x17c]; s32 sp; s32 stk[33]; s32 x20c; } VMe;
void func_001cac60();
void func_0010f558(void *, void *, s32);
s32 func_001cac98(VMe *vm) {
    s32 i;
    s32 v = vm->stk[32];
    for (i = 0; i < 4; i++) {
        if (D_00389C90.b[i] && D_00389C90.idx[i] == vm->stk[vm->sp - 3]) break;
    }
    if (i >= 4) return 2;
    {
        D_0062A1E0.a = vm->stk[vm->sp - 2];
        D_0062A1E0.b = vm->stk[vm->sp - 1];
        D_0062A1E0.fn = func_001cac60;
        if (v >= 256) { v -= 2304; D_00389C90.p12612 = &D_00389C90.arr[v]; }
        func_0010f558(&D_0062A1E0, &D_00629E70[i], D_0062A1E0.a);
        D_00389C90.d12400 |= 0x100000000ULL;
        vm->sp -= 4;
    }
    return 2;
}

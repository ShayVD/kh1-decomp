/* func_001d9268: 2 words off in hand/nostrict: 'or a2,a2,s1' and 'sw zero,13412(a1)' swapped. */
typedef struct { u64 d[6]; } B48;
typedef struct { u8 pad0[0x3078]; u64 flags; u8 pad3080[0x3460 - 0x3080]; f32 f3460; s32 f3464; u8 pad3468[8]; B48 a; B48 b; } Big92;
extern Big92 D_00389C90;
extern B48 D_002BC0C0, D_002BC0F0;
s32 func_001d9268(VM *vm) {
    f32 x;
    s32 i;
    D_00389C90.b = D_002BC0C0;
    D_00389C90.a = D_002BC0F0;
    i = vm->sp; D_00389C90.f3464 = 0; x = vm->stk[i] * 2.0f; D_00389C90.flags |= 2; vm->sp--; D_00389C90.f3460 = x;
    return 2;
}

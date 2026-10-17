/* func_001d0380: ~26 score / size 200 vs 192 (src/hand, vmb.inc types). Off: stack value n gets v1 instead of a1 so the else block starts with addiu instead of lui; return-8 tail shape. flags must be u32 bitfields direct in an 8-aligned VM (ld; dsll 27; dsra32). */
typedef struct { u8 pad0[0x10]; f32 pos[3]; u8 pad1c[0x20]; f32 f3c; u8 pad40[0x330]; u64 f370; } Ent;
typedef struct {
    s32 x0;
    Ent *ent;
    u8 pad8[0x60];
    f32 f68;
    s32 f6c;
    s32 code;
    u8 pad74[8];
    s32 lbl[64];
    s32 pc;
    s32 sp;
    s32 stk[92];
    f32 f2f4;
    u8 pad2f8[0x30];
    u32 b0:1, b1:1, b2:1, b3:1, b4:1, b5:1, brest:26;
    u32 hi;
    f32 f330;
    u32 pad334;
    u64 q338;
} VM;
typedef struct { u8 pad[12340]; s32 w12340; s32 w12344; } BigD;
extern BigD D_00389C90;
extern s32 D_002BCDE4, D_002BCC90;
void func_001c2ec8(s32 a, s32 b);
void func_001c3770(s32 a, s32 b);
s32 func_001d0380(VM *vm) {
    s32 a = D_00389C90.w12340;
    s32 b = D_00389C90.w12344;
    s32 n = vm->stk[vm->sp];
    if (n < 100) {
        func_001c2ec8(D_002BCDE4, n);
    } else {
        n -= 100;
        func_001c3770(D_002BCC90, n);
    }
    if (vm->b5 == 1) {
        if (b != 0) return 8;
    } else if (a != 0) {
        return 8;
    }
    vm->sp--;
    return 10;
}

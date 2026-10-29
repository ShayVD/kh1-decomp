/* Round 41 wwm2: score 13 -> 4, port.py of the wm twin func_00f47610 draft (r41/twins.py pairs wm and gb drafts with the same target mnemonics). Earlier header below. */
/* 72 words / score 13 (492 vs 496 bytes). An inline alloc(&global, size, align) helper gives the original's precomputed global addresses in s-registers; the loop fields stay plain assignments. Left: loop address givs. The original forms buf[i].d as s2+base+28 and buf[i].e as base+(s2+24)+8, then does move s2,a0. Tried do-while, buf[i++].e, x[] array fields, a 2D array, and pointer arithmetic. Round 16 (wwm1): looked at, not changed. The target forms .d as s2 + 28 (not s0 + 12) and .e through the incremented biv (s2 + 24, then move s2,a0), so d and e are reached through different expressions from a, b and c. */
typedef struct { s32 w[6]; } E47610;
typedef union { struct { u8 p0[0]; E47610 e[4]; } v0; struct { u8 p8[8]; E47610 e[4]; } v8; struct { u8 p16[16]; E47610 e[4]; } v16; } W47610;
s32 func_001bb500(s32, s32);
extern W47610 *D_00F56DC0;
extern s32 D_00F56DC4;
extern s32 D_00F56DE8;
extern s32 D_00F74204;
extern s32 D_00F74214;
extern s32 D_00F74210;
extern s32 D_00F74218;
extern s32 D_00F74220;
extern s32 D_00F74224;
extern s32 D_00F7421C;
extern s32 D_00F56DE0;
extern s32 D_00F56DE4;

static inline void alloc47610(s32 *p, s32 size, s32 align) {
    *p = func_001bb500(size, align);
}

void func_00f20518(void) {
    s32 i;

    alloc47610((s32 *)&D_00F56DC0, 9216, 16);
    alloc47610(&D_00F56DC4, 0x13008, 16);
    for (i = 0; i < 2; i++) {
        D_00F56DC0->v0.e[i].w[4] = func_001bb500(0xC0000, 128);
        D_00F56DC0->v0.e[i].w[5] = func_001bb500(0x4E000, 16);
        D_00F56DC0->v8.e[i].w[4] = func_001bb500(0xA000, 16);
        D_00F56DC0->v16.e[i].w[3] = func_001bb500(0xA000, 16);
        D_00F56DC0->v8.e[i + 1].w[0] = func_001bb500(0xA000, 16);
    }
    alloc47610(&D_00F56DE8, 0xC8000, 128);
    alloc47610(&D_00F74204, 0xC0000, 128);
    alloc47610(&D_00F74214, 0x90000, 128);
    alloc47610(&D_00F74210, 0x440000, 128);
    alloc47610(&D_00F74218, 0x10000, 128);
    alloc47610(&D_00F74220, 0x40000, 128);
    alloc47610(&D_00F74224, 0x100000, 128);
    alloc47610(&D_00F7421C, 0x40000, 128);
    D_00F56DE0 = func_001bb500(16384, 16);
    D_00F56DE4 = func_001bb500(4096, 128);
}

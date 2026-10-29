/* 2 words. Inline alloc(&global, size, align) helper gives the s-reg addresses; loop fields need mixed views of W (union of offset 0/8/16 rows; searched all 243). Left: field b is addressed as W+s2+20, target W+(s2+16)+4. 10-min permuter run as well. */
typedef struct { s32 w[6]; } E47610;
typedef union { struct { u8 p0[0]; E47610 e[4]; } v0; struct { u8 p8[8]; E47610 e[4]; } v8; struct { u8 p16[16]; E47610 e[4]; } v16; } W47610;
s32 func_001bb500(s32, s32);
extern W47610 *D_00F9B540;
extern s32 D_00F9B544;
extern s32 D_00F9B568;
extern s32 D_010809BC;
extern s32 D_010809CC;
extern s32 D_010809C8;
extern s32 D_010809D0;
extern s32 D_010809D8;
extern s32 D_010809DC;
extern s32 D_010809D4;
extern s32 D_00F9B560;
extern s32 D_00F9B564;

static inline void alloc47610(s32 *p, s32 size, s32 align) {
    *p = func_001bb500(size, align);
}

void func_00f47610(void) {
    s32 i;

    alloc47610((s32 *)&D_00F9B540, 9216, 16);
    alloc47610(&D_00F9B544, 0x13008, 16);
    for (i = 0; i < 2; i++) {
        D_00F9B540->v0.e[i].w[4] = func_001bb500(0xC0000, 128);
        D_00F9B540->v0.e[i].w[5] = func_001bb500(0x4E000, 16);
        D_00F9B540->v8.e[i].w[4] = func_001bb500(0xA000, 16);
        D_00F9B540->v16.e[i].w[3] = func_001bb500(0xA000, 16);
        D_00F9B540->v8.e[i + 1].w[0] = func_001bb500(0xA000, 16);
    }
    alloc47610(&D_00F9B568, 0xC8000, 128);
    alloc47610(&D_010809BC, 0xC0000, 128);
    alloc47610(&D_010809CC, 0x90000, 128);
    alloc47610(&D_010809C8, 0x440000, 128);
    alloc47610(&D_010809D0, 0x10000, 128);
    alloc47610(&D_010809D8, 0x40000, 128);
    alloc47610(&D_010809DC, 0x100000, 128);
    alloc47610(&D_010809D4, 0x40000, 128);
    D_00F9B560 = func_001bb500(16384, 16);
    D_00F9B564 = func_001bb500(4096, 128);
}

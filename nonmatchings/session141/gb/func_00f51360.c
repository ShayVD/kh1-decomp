/* 6 words / score 11: store order of the ten globals (li 8 vs lui order); hill-climbed over the store order. */
s32 func_001f31a8(void *, s32);
void func_0024e468(s32);
extern u8 D_00F713B0[];
extern s32 D_00F829E0;
extern s32 D_00F829E8;
extern s32 D_00F829EC;
extern s32 D_00F829F0;
extern s32 D_00F82A98;
extern s32 D_00F82DA8;
extern s32 D_00F82DAC;
extern s32 D_00F82DB0;
extern s32 D_00F82DB4;
extern s32 D_00F82DB8;

s32 func_00f51360(s32 arg0) {
    D_00F82DA8 = arg0;
    D_00F829E0 = 8;
    D_00F829F0 = 0xE0;
    D_00F82A98 = 1;
    D_00F82DAC = arg0;
    D_00F829E8 = 1;
    D_00F82DB4 = 0;
    D_00F82DB0 = 0;
    D_00F82DB8 = -8;
    D_00F829EC = 0;
    func_001f31a8(D_00F713B0, 1);
    if (D_00F829EC != 1) {
        do {
            func_0024e468(1);
        } while (D_00F829EC != 1);
    }
    D_00F829E0 = 0x10;
    return D_00F82DAC;
}

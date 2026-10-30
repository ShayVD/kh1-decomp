/* Round 37 (wgb): no change (2 words, score 3). Writing the live D_00F829E0 = 8 before D_00F82DA8 = arg (no dead store) gives the target store order (sched1 ranks the two stores equal and takes the lower LUID), but local-alloc then hands t4/t5/t6 to arg/8/high(D_00F82DA8) instead of high(D_00F82DA8)/arg/8 (13 words). The dead first store only raises the 8 pseudo's ref count. Tried: dead duplicates of D_00F829E0 and D_00F82DA8 at every pair of positions, rotations and reversals of the target store order, about 1300 random orders with one or two dead stores, hill3 (120 s), every build mode (all 2 words or worse). */
/* Round 41 wwm2: score 11 -> 3, port.py of the wm twin func_00f78458 draft (r41/twins.py pairs wm and gb drafts with the same target mnemonics). Earlier header below. */
/* 6 words / score 11: store order of the ten globals (li 8 vs lui order); hill-climbed over the store order. Round 16 (wwm1): target store order is DB8, 9F0, 9E0, DA8, DAC, A98, 9E8, DB4, DB0, 9EC (t6 = 8). Two more hill seeds stayed at 6. 72 chained-assignment variants (arg, 1 and 0 chains, six orders) were all 11 or worse. */

extern u8 D_00F713B0[];
extern s32 D_00F82DB8;
extern s32 D_00F829F0;
extern s32 D_00F829E0;
extern s32 D_00F82DA8;
extern s32 D_00F82DAC;
extern s32 D_00F82A98;
extern s32 D_00F829E8;
extern s32 D_00F82DB4;
extern s32 D_00F82DB0;
extern s32 D_00F829EC;
s32 func_001f31a8(void *, s32);
void func_0024e468(s32);

s32 func_00f51360(s32 arg) {
    D_00F829EC = 0;
    D_00F829E0 = 8;
    D_00F82DA8 = arg;
    D_00F829F0 = 224;
    D_00F829E0 = 8;
    D_00F82DAC = arg;
    D_00F82A98 = 1;
    D_00F829E8 = 1;
    D_00F82DB4 = 0;
    D_00F82DB0 = 0;
    D_00F82DB8 = -8;
    func_001f31a8(D_00F713B0, 1);
    while (D_00F829EC != 1) {
        func_0024e468(1);
    }
    D_00F829E0 = 16;
    return D_00F82DAC;
}

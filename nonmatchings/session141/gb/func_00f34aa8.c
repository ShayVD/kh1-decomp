/* 65 words / score 26: switch block layout (the original's case 44 steals move a0,sp into a beql slot and shares the f41678 call tail); tried case orders, if chains. Round 16 (wwm1): the target predicts the case-44 beq as taken (beql stealing `move a0,sp`); ours fills it from the default path (`move a0,s3`). An explicit default at the top or bottom, continue instead of break, a k local, and switching on h4 with cases 45-48 did not change it (65 or 73). */
typedef struct { u8 pad[4]; u16 h4; u8 pad6[6]; } Ent;
typedef struct { u8 pad[164]; u16 n; u16 h166; u16 h168; u16 h170; u8 pad172[100]; Ent e[1]; } G;
extern G *D_00F56DC0;
extern s32 D_00F56DE8;
void func_00f33d18(OvlMtx, s32);
s32 func_00f41678(s32, s32, OvlMtx, OvlVec, s32);
void func_00f33da0(s32, s32);

void func_00f34aa8(void) {
    OvlMtx m;
    OvlVec v;
    s32 i;
    v[0] = -1.0f;
    v[1] = 1.0f;
    v[2] = 1.0f;
    v[3] = 1.0f;
    for (i = 0; i < D_00F56DC0->n; i++) {
        switch (D_00F56DC0->e[i].h4 - 1) {
        case 44:
            func_00f33d18(m, i);
            func_00f33da0(func_00f41678(56, 1, m, 0, D_00F56DE8), 6);
            break;
        case 45:
            func_00f33d18(m, i);
            func_00f33da0(func_00f41678(56, 1, m, v, D_00F56DE8), 6);
            break;
        case 46:
            func_00f33d18(m, i);
            func_00f33da0(func_00f41678(57, 1, m, 0, D_00F56DE8), 6);
            break;
        case 47:
            func_00f33d18(m, i);
            func_00f33da0(func_00f41678(57, 1, m, v, D_00F56DE8), 6);
            break;
        }
    }
}

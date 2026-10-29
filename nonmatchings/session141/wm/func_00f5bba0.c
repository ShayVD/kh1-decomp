/* 68 words (score 32, 400 vs 392). Switch cases 44-47 call func_00f68770; s[] store order 3,0,1,2 and cross-jumped tails differ. Shared-call variant was worse. */
typedef struct { u8 p[4]; u16 kind; u16 fl; u8 q[4]; } Typ5bba0;
typedef struct { u8 pad[0xA4]; u16 ntyp; u8 pad2[0x110 - 0xA6]; Typ5bba0 typ[1]; } W5bba0;
void func_00f5ae10(f32 (*)[4], s32);
void func_00f5ae98(s32, s32);
s32 func_00f68770(s32, s32, f32 (*)[4], f32 *, s32);
extern W5bba0 *D_00F9B540;
extern s32 D_00F9B568;

void func_00f5bba0(void) {
    f32 m[4][4];
    f32 s[4];
    s32 i;

    s[3] = 1.0f;
    s[0] = -1.0f;
    s[1] = 1.0f;
    s[2] = 1.0f;
    for (i = 0; i < D_00F9B540->ntyp; i++) {
        switch (D_00F9B540->typ[i].kind - 1) {
        case 44:
            func_00f5ae10(m, i);
            func_00f5ae98(func_00f68770(56, 1, m, NULL, D_00F9B568), 6);
            break;
        case 45:
            func_00f5ae10(m, i);
            func_00f5ae98(func_00f68770(56, 1, m, s, D_00F9B568), 6);
            break;
        case 46:
            func_00f5ae10(m, i);
            func_00f5ae98(func_00f68770(57, 1, m, NULL, D_00F9B568), 6);
            break;
        case 47:
            func_00f5ae10(m, i);
            func_00f5ae98(func_00f68770(57, 1, m, s, D_00F9B568), 6);
            break;
        }
    }
}

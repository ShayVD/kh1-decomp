/* func_00f78978: score 45, 104 words differ. original keeps a dead D_0108FA74 == 66 compare that this draft lacks */
typedef struct {
    u32 c[2];
} Cols;

extern s32 D_0108F6C8;
extern s32 D_0108F6CC;
extern s32 D_0108F6C4;
extern Cols D_00FBA708;
extern s32 D_00FB5ED0;
extern s32 D_00FB5EC4;
extern s32 D_00FB5EC0;
extern s32 D_00FB5BB0;
extern s32 D_0108FA74;
extern s32 D_0108F730[2];
extern s32 D_0108FA78;
extern s32 D_0108FA7C;
extern s32 D_0108FA68;
extern s32 D_0108FA6C;
extern s32 D_00FB6130[];
void func_001efb18(s32, s32);
void func_001f9438(void *, s32, s32, s32, s32, s32, u32);
void func_00207830(void *, s32, s32, s32, s32, s32, u32);
void func_001f8f30(void);
void func_001f3840(void *);

void func_00f78978(void *o) {
    Cols cols = D_00FBA708;
    u32 col;
    s32 x;
    s32 y;

    func_001efb18(D_0108F6C8, D_0108F6CC);
    func_001f9438(o, 0, 339, 12, 14, 16, 0x6664FF6F);
    x = 0;
    if (D_00FB5ED0 && D_00FB5EC4 == 0 && D_0108FA74 == 66) {
        x = 1;
    }

    if ((D_0108F730[0] || D_0108F730[1]) && D_0108FA74 != 67 && D_00FB5BB0) {
        col = D_00FB5EC4 ? 0x30FFFFFF : 0x80FFFFFF;
    } else {
        col = 0x30FFFFFF;
    }
    func_001f9438(o, 0, 442, 358, 18, 15, col);
    if (D_00FB5EC4 == 0) {
        x = (D_0108FA78 >> 4) - 2001;
        y = (D_0108FA7C >> 4) - 1894;
        if (D_0108F730[0]) {
            func_00207830(o, D_00FB6130[D_00FB5EC0 ? 0 : 1], 2, x, y, 140, cols.c[0]);
            y += 30;
        }
        if (D_0108F730[1]) {
            func_00207830(o, D_00FB6130[D_00FB5EC0 != 1 ? 2 : 3], 2, x, y, 140, cols.c[1]);
        }
    }
    D_0108FA78 = D_0108FA68;
    D_0108FA7C = D_0108FA6C;
    func_001f8f30();
    if (D_0108F6C4 >= 0) {
        func_001f3840(o);
    }
}

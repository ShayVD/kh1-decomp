/* 9 words left; tried 15 variants (a-o) Round 14: the target loads -19744(a0) twice with one shared lui, so case 4 reads the same symbol twice without CSE. volatile reproduces the reload but computes the full address (12 words); using D_00F9B2E0 or .x10 in both places CSEs the load (32 words). All modes: no change. */
typedef struct { u8 pad[0x554]; s32 x554; } G465a8;
extern G465a8 *D_00F864C0;
extern s32 D_00F8508C;
extern s32 D_00F85090;
extern s32 D_00F9B2E0;
typedef struct { s32 x0; s32 pad[3]; s32 x10; } B465a8;
extern B465a8 D_00F9B2D0;
extern s32 D_00F850C4;
extern s32 D_00F850BC;
s32 func_00f3b080(void);
s32 func_00f309e0(void);

s32 func_00f465a8(u32 arg0) {
    s32 r;
    s32 x;
    switch (arg0) {
    case 0:
        return func_00f3b080();
    case 1:
        return D_00F8508C;
    case 2:
        return D_00F85090;
    case 3:
        return func_00f309e0();
    case 4:
        x = D_00F9B2D0.x10;
        if (x >= 0) {
            r = x + 1;
        } else if (x >= -2) {
            r = 0;
        } else {
            r = D_00F9B2E0 + 1;
        }
        return r;
    case 5:
        return D_00F9B2D0.x0;
    case 6:
        return D_00F864C0->x554;
    case 7:
        return D_00F850C4;
    case 8:
        return D_00F850BC;
    }
    return 0;
}

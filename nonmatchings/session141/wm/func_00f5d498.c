/* 13 words. Menu loop; left: prologue sd ra order and bnezl/slti duplication of the clamp. Tried clamp spellings, 6 min permuter.. Round 6: if-clamp forms (>=, <=, > n-1) and decl/for(;;) variants did not help; the target writes s0 directly in the bnezl path. */
typedef struct { u8 pad[8]; s32 x8; u8 pad2[4]; s32 x10; } Pad5d498;
void func_001bfac8(void);
Pad5d498 *func_001ba488(s32);
s32 func_001bb720(void);
void func_00f4fba0(void *, s32, s32);
extern u8 D_00F9B548[];

void func_00f5d498(void) {
    s32 sel = 0;
    s32 top = 0;
    Pad5d498 *p;

    while (1) {
        func_001bfac8();
        p = func_001ba488(0);
        if (p->x8 & 0x4000) {
            return;
        }
        if (p->x10 & 0x10) {
            sel--;
        }
        if (p->x10 & 0x40) {
            sel++;
        }
        sel = (sel < func_001bb720()) ? sel : func_001bb720() - 1;
        if (sel < 0) {
            sel = 0;
        }
        if (sel - top >= 10) {
            top = sel - 9;
        }
        if (sel < top) {
            top = sel;
        }
        func_00f4fba0(D_00F9B548, sel, top);
    }
}

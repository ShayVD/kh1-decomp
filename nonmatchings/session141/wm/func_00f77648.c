/* Round 48 wwm2: the hill3o order from 4ea501d2 (wm func_00f77648 near miss, score 166 -> 158, hill3o statement order (wwm2 round) moved a control line (break/case/label/return/goto) or broke a dependency, so its score 158 was not valid. Restored the last valid statement order: score 166. Earlier header below. */
/* score 168 (first draft); round 30 wgb: 228 words, score 166, 1192 vs 1192 bytes with func_00f6b5b0 declared (Win *, f32, f32) and called (*pw++, 256.0f, ...) like its matched callers, plus a CONTEXT_ONLY definition so the call is nothrow; was 253/168). Confirm dialog: builds a title, a box and three option windows with func_00f6b6a0 (19 args), fades them in, then loops on pad input (0x4000 cancel returns, 0x2000 confirm calls func_00f4d528(sel) and never returns, 0x10/0x40 move the selection with wraparound). Two S3 copies (D_00FBA218 -> sp+112, D_00FBA220 -> sp+128); declare w[3] first. Left: gcc CSEs the 256 constant into s6 across calls (the original reloads it with li each time); sel/k/loop registers are shifted from that. */
typedef struct { s32 x0, x4; u32 x8; u32 xC; u32 x10; } Pad;
typedef struct { u8 pad[4]; u8 b4; } Win;
typedef struct { u8 pad[16]; s32 x10; } Hdl;
typedef struct { s16 v[3]; } S3;
extern Pad D_002C5AD0;
extern S3 D_00FBA218;
extern S3 D_00FBA220;
extern s32 D_00FB4A70;
extern s32 D_00FB4C24, D_00FB4C28, D_00FB4C2C;
extern s32 D_00FB4C98, D_00FB4C9C, D_00FB4CA0, D_00FB4CA4, D_00FB4CA8, D_00FB4CAC, D_00FB4CB0;
extern s32 D_00FB4B38, D_00FB4B3C, D_00FB4B6C, D_00FB4DA0;
extern s32 D_0108F1B8, D_0108F184, D_00FB4EB4;
extern u8 D_00FB4EBA;
void func_00f6b5d0(s32, s32, s32);
void *func_00f6b6a0(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
s32 func_00f47110(void);
void func_00f74978(Win *, s32);
CONTEXT_ONLY void func_00f6b5b0(Win *a0, f32 a1, f32 a2) {}
void func_0024e468(s32);
void func_0011d768(s32);
void func_00f6ade8(s32);
void func_00106880(s32);
void func_00f4d528(s32);

void func_00f77648(void)
{
    Win *w[3];
    S3 a = D_00FBA218;
    S3 b = D_00FBA220;
    Hdl *h;
    s32 sel = 0;
    s32 k = 1;
    s32 i, y, prev;
    s16 *pa;
    Win **pw;

    func_00f6b5d0(2, 0, D_00FB4A70);
    func_00f6b6a0(20, 0, 2, 1, 0, 15, 213, 4, D_00FB4C24, D_00FB4C28, 0, D_00FB4C2C, 0, 0, 0, 0, 0, 256, D_00FB4A70);
    if (func_00f47110() == 0) k = D_00FB4A70;
    h = func_00f6b6a0(20, 2, 0, 2, 0, D_00FB4C98, b.v[0], 0, D_00FB4C9C, D_00FB4CA0, 0, 0, 0, D_00FB4CA4, D_00FB4CA8, D_00FB4CAC, D_00FB4CB0, 256, k);
    y = D_00FB4B3C;
    pa = a.v;
    pw = w;
    for (i = 2; i >= 0; i--) {
        *pw++ = func_00f6b6a0(20, 0, 2, 1, 0, 15, *pa++, 1, D_00FB4B38, y, 0, D_00FB4DA0, 0, 0, 0, 0, 0, 0, D_00FB4A70);
        y += D_00FB4B6C;
    }
    w[0]->b4 = 1;
    w[1]->b4 = 0;
    w[2]->b4 = 0;
    func_00f74978(w[0], 8);
    pw = w;
    for (i = 2; i >= 0; i--) {
        func_00f6b5b0(*pw++, 256.0f, D_00FB4A70);
        func_0024e468(2);
    }
    func_0024e468(D_00FB4A70);
    for (;;) {
        if (D_002C5AD0.x8 & 0x4000) {
            func_0011d768(3);
            func_00f6b5d0(20, 0, D_00FB4A70);
            func_0024e468(D_00FB4A70);
            func_00f6ade8(20);
            if (D_0108F1B8 > 0) D_0108F1B8 = -1;
            func_00f6b5d0(2, 256, D_00FB4A70);
            return;
        }
        if (D_002C5AD0.x8 & 0x2000) {
            func_0011d768(2);
            func_00106880(30);
            func_0024e468(60);
            D_0108F184 = 0;
            D_00FB4EBA = 3;
            D_00FB4EB4 = -1;
            func_00f4d528(sel);
            for (;;)
                func_0024e468(1);
        }
        prev = sel;
        if (((D_002C5AD0.x8 | D_002C5AD0.x8 >> 24) & 0x10) && sel == 0) {
            sel = 2;
        } else if ((D_002C5AD0.x10 | D_002C5AD0.x10 >> 24) & 0x10) {
            sel--;
            if (sel < 0) sel = 0;
        }
        if (((D_002C5AD0.x8 | D_002C5AD0.x8 >> 24) & 0x40) && sel == 2) {
            sel = 0;
        } else if ((D_002C5AD0.x10 | D_002C5AD0.x10 >> 24) & 0x40) {
            sel++;
            if (sel >= 3) sel = 2;
        }
        h->x10 = b.v[sel];
        w[0]->b4 = 0;
        w[1]->b4 = 0;
        w[2]->b4 = 0;
        w[sel]->b4 = 1;
        func_00f74978(w[sel], 8);
        if (sel != prev) func_0011d768(1);
        func_0024e468(1);
    }
}

/* drafttwins.py: score 166 -> 158, port.py of the wm twin func_00f77648 draft. Earlier header below. */
/* 253 words / score 168 (1184 vs 1192); round 30 wgb: 228 words, score 166, 1192 vs 1192 bytes with func_00f444b8 declared (Win *, f32, f32) and called (*pw++, 256.0f, ...) like its matched callers, plus a CONTEXT_ONLY definition so the call is nothrow; was 253/168). Ported unchanged from the wm twin near miss func_00f77648 (port.py wm -> gb). Same open issue: gcc CSEs the 256 constant into an s-reg across calls where the original reloads it with li each time. */
typedef struct { s32 x0, x4; u32 x8; u32 xC; u32 x10; } Pad;
typedef struct { u8 pad[4]; u8 b4; } Win;
typedef struct { u8 pad[16]; s32 x10; } Hdl;
typedef struct { s16 v[3]; } S3;
extern Pad D_002C5AD0;
extern S3 D_00F74168;
extern S3 D_00F74170;
extern s32 D_00F702F0;
extern s32 D_00F704A4, D_00F704A8, D_00F704AC;
extern s32 D_00F70518, D_00F7051C, D_00F70520, D_00F70524, D_00F70528, D_00F7052C, D_00F70530;
extern s32 D_00F703B8, D_00F703BC, D_00F703EC, D_00F70620;
extern s32 D_00F829F8, D_00F829C4, D_00F70734;
extern u8 D_00F7073A;
void func_00f444d8(s32, s32, s32);
void *func_00f445a8(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
s32 func_00f20018(void);
void func_00f4d880(Win *, s32);
CONTEXT_ONLY void func_00f444b8(Win *a0, f32 a1, f32 a2) {}
void func_0024e468(s32);
void func_0011d768(s32);
void func_00f43cf0(s32);
void func_00106880(s32);
void func_00f26430(s32);

void func_00f50550(void)
{

    Win *w[3];
    Hdl *h;
    S3 a = D_00F74168;
    s32 k = 1;
    Win **pw;
    s16 *pa;
    s32 sel = 0;
    S3 b = D_00F74170;
    s32 i, y, prev;
    func_00f444d8(2, 0, D_00F702F0);
    func_00f445a8(20, 0, 2, 1, 0, 15, 213, 4, D_00F704A4, D_00F704A8, 0, D_00F704AC, 0, 0, 0, 0, 0, 256, D_00F702F0);
    if (func_00f20018() == 0) k = D_00F702F0;
    h = func_00f445a8(20, 2, 0, 2, 0, D_00F70518, b.v[0], 0, D_00F7051C, D_00F70520, 0, 0, 0, D_00F70524, D_00F70528, D_00F7052C, D_00F70530, 256, k);
    pw = w;
    y = D_00F703BC;
    pa = a.v;
    for (i = 2; i >= 0; i--) {
        *pw++ = func_00f445a8(20, 0, 2, 1, 0, 15, *pa++, 1, D_00F703B8, y, 0, D_00F70620, 0, 0, 0, 0, 0, 0, D_00F702F0);
        y += D_00F703EC;
    }
    w[0]->b4 = 1;
    w[1]->b4 = 0;
    w[2]->b4 = 0;
    func_00f4d880(w[0], 8);
    pw = w;
    for (i = 2; i >= 0; i--) {
        func_00f444b8(*pw++, 256.0f, D_00F702F0);
        func_0024e468(2);
    }
    func_0024e468(D_00F702F0);
    for (;;) {
        if (D_002C5AD0.x8 & 0x4000) {
            func_0011d768(3);
            func_00f444d8(20, 0, D_00F702F0);
            func_0024e468(D_00F702F0);
            func_00f43cf0(20);
            if (D_00F829F8 > 0) D_00F829F8 = -1;
            func_00f444d8(2, 256, D_00F702F0);
            return;
        }
        if (D_002C5AD0.x8 & 0x2000) {
            func_0011d768(2);
            func_00106880(30);
            func_0024e468(60);
            D_00F829C4 = 0;
            D_00F7073A = 3;
            D_00F70734 = -1;
            func_00f26430(sel);
            for (;;)
                func_0024e468(1);
        }
        prev = sel;
        if (((D_002C5AD0.x8 | D_002C5AD0.x8 >> 24) & 0x10) && sel == 0) {
            sel = 2;
        } else if ((D_002C5AD0.x10 | D_002C5AD0.x10 >> 24) & 0x10) {
            if (sel < 0) sel = 0;
            sel--;
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
        func_00f4d880(w[sel], 8);
        if (sel != prev) func_0011d768(1);
        func_0024e468(1);
    }
}

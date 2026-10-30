/* Round 64 wwm2: score 37 -> 35 with CONTEXT_ONLY definitions of func_0024e468 (tools/ovl/nothrow.py: the call becomes nothrow, so reorg picks the original's plain/-likely branch next to it). Earlier header below. */
/* Round 46 wwm2: score 39 -> 37, outer goto loop written as while (!((a = D_002C5AD0.x8) & 0x4000)), 1252 vs 1232 bytes. Earlier header below. */
/* score 39 (1244 vs 1232, was 128). The first window loop is `for (k = 0; k < 2; k++)` (gcc reverses it; the final k == 2 is then reused for the constant 2 argument), and the clear loop is `for (k = 0; k < 2; k++) w[k]->b4 = 0; D_0108F52C = k;` (this gives `li s3,2; sw s3`). Both pad loops stay goto/for(;;) loops; a for loop with the test in its header duplicates the test at the top. Left: the original hoists only `lui s2,0x2c` into the delay slot of the jump to the outer test, while this draft schedules it before the second func_00f6b6a0 call (in s6). That costs 12 bytes plus register drift. */
typedef struct { s32 x0, x4; u32 x8; u32 xC; u32 x10; } Pad;
typedef struct { u8 pad[4]; u8 b4; u8 pad5[2]; u8 b7; } Win;
typedef struct { u8 pad[16]; s32 x10; } Hdl;
typedef struct { u8 b0; u8 pad[3]; s32 x4; } Itm;
extern Pad D_002C5AD0;
extern s32 D_00FB4A70;
extern s32 D_00FB4B18;
extern u8 D_00FB4B1C;
extern s32 D_00FB4B20;
extern s32 D_00FB4B38;
extern s32 D_00FB4B3C;
extern s32 D_00FB4B6C;
extern s32 D_00FB4B70;
extern s32 D_00FB4CB8, D_00FB4CBC, D_00FB4CC0, D_00FB4CC4;
extern s16 D_00FB5A20[];
extern s32 D_0108F18C;
extern s32 D_0108F52C;
void func_0011d768(s32);
Itm *func_001bc4f0(void);
s32 func_001bc520(void);
void func_001bdb58(void);
void func_001f3dc0(s32);
void func_0024e468(s32); CONTEXT_ONLY void func_0024e468(s32 a0) {}
void func_00f6ade8(s32);
void func_00f6b5d0(s32, s32, s32);
void *func_00f6b6a0(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
void func_00f74978(Win *, s32);

void func_00f72a70(s32 arg0, Hdl *h)
{
    Win *w[8];
    Win **pw;
    Win **pw2;
    s16 *ps;
    s32 t, y, k, sel, n;
    u32 a, b;
    Itm *e;

    pw = w;
    t = D_00FB4A70;
    h->x10 = 109;
    y = D_00FB4B3C;
    ps = D_00FB5A20;
    for (k = 0; k < 2; k++) {
        *pw = func_00f6b6a0(14, 0, 2, 1, 2, 15, *ps++, 1, D_00FB4B18, y, 0, D_00FB4B20, 0, 0, 0, 0, 0, 256, t);
        (*pw)->b7 = D_00FB4B1C;
        (*pw++)->b4 = 0;
        y += D_00FB4B6C;
    }
    func_00f6b6a0(14, 3, 0, 2, 0, 0, 0, 0, 0, D_00FB4B3C + 12, 0, D_00FB4B38, 2, D_00FB4CB8, D_00FB4CBC, D_00FB4CC0, D_00FB4CC4, 256, t);
    func_00f6b6a0(14, 0, 2, 1, 0, 15, 86, 7, D_00FB4B38, D_00FB4B3C, 0, D_00FB4B70, 0, 0, 0, 0, 0, 256, t);
    while (!((a = D_002C5AD0.x8) & 0x4000)) {
        if (a & 0x2000) {
            func_0011d768(2);
            D_0108F52C = 0;
            sel = 1;
            func_001f3dc0(D_0108F18C);
            func_0024e468(1);
            for (;;) {
                a = D_002C5AD0.x8 | D_002C5AD0.x8 >> 24;
                b = D_002C5AD0.x10 | D_002C5AD0.x10 >> 24;
                if (a & 0x4000) {
                    func_0011d768(3);
                    break;
                }
                if (a & 0x2000) {
                    func_0011d768(2);
                    if (sel == 0) {
                        n = func_001bc520();
                        for (k = 0; k < n; k++) {
                            e = func_001bc4f0() + k;
                            switch (e->b0) {
                            case 0:
                                e->x4 = 0x4000;
                                break;
                            case 1:
                                e->x4 = 0x8000;
                                break;
                            case 2:
                                e->x4 = 0x400;
                                break;
                            case 3:
                            case 4:
                            case 5:
                                e->x4 = 0x2000;
                                break;
                            case 6:
                            case 7:
                            case 8:
                                e->x4 = 0x1000;
                                break;
                            case 9:
                            default:
                                e->x4 = 0;
                                break;
                            }
                        }
                    }
                    func_001bdb58();
                    break;
                }
                if (b & 0x10) {
                    sel--;
                    if (sel < 0) {
                        if (a & 0x10) {
                            sel = 1;
                            func_0011d768(1);
                        } else {
                            sel = 0;
                        }
                    } else {
                        func_0011d768(1);
                    }
                    a = 0;
                    b = 0;
                }
                if (b & 0x40) {
                    sel++;
                    if (sel >= 2) {
                        if (a & 0x40) {
                            sel = 0;
                            func_0011d768(1);
                        } else {
                            sel = 1;
                        }
                    } else {
                        func_0011d768(1);
                    }
                }
                for (k = 0; k < 2; k++) {
                    if (sel == k)
                        w[k]->b4 = 1;
                    else
                        w[k]->b4 = 0;
                }
                func_00f74978(w[sel], 8);
                func_0024e468(1);
            }
            for (k = 0; k < 2; k++) w[k]->b4 = 0;
            D_0108F52C = k;
            func_001f3dc0(arg0);
        }
        func_0024e468(1);
    }
    func_0011d768(3);
    func_00f6b5d0(14, 0, D_00FB4A70);
    func_0024e468(D_00FB4A70);
    func_00f6ade8(14);
}

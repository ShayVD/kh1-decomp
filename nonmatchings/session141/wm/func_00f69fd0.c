/* Round 46 wwm2: score 127 -> 107, sceGsSyncPath and func_00f69f98 declared s32. Earlier header below. */
/* Round 36 (wwm2): wm.x func_00f69fd0 near miss: score 183 -> 127 (113 -> 145 words, 724 vs 736); statement order from the score-ranked dependency-safe hill3 (r35/hill3.py, two passes, seeds 362/363 then 364). Earlier header below. */
/* 113 words, score 183 (732 vs 736; was 148/184). Round 33 wwm2: hill2 moved `D_0108F25C = D_00FB4F50.xC` and `D_00FB4EB8 = 0` within the init block; ctx2 gives nothing. Earlier header: score 184. Init function: around 30 global stores, sceGsSyncPath, func_001be278, then a one-time block that loads a module via func_0024b778/func_0024b7a0 and registers four callbacks through o->fn. The original preloads 1 (s8) and 128 (s3) into saved registers before sceGsSyncPath, so the 128 and 1 constants are probably shared variables. The store schedule is still far off. */
typedef struct { void *x0; void *x4; void (*fn)(void (*)(void), s32, s32); } Obj;
typedef struct { s32 x0, x4, x8, xC, x10, x14, x18; } Hdr;
extern s32 D_0108F1B4;
extern s32 D_00FB4A54;
extern s32 D_003F34B0[];
extern s32 D_00FB4D34;
extern s32 D_00FB4D38;
extern s32 D_00FB4D4C;
extern s32 D_0108F1D4;
extern s32 D_0108F198;
extern f32 D_00FB4AAC;
extern s32 D_0108F204;
extern s32 D_0108F1BC;
extern s32 D_0108F1C0;
extern f32 D_0108F1E8;
extern s32 D_0108F1C8;
extern s32 D_0108F194;
extern f32 D_0108F1F0;
extern s32 D_0108F1DC;
extern s32 D_0108F1CC;
extern s32 D_0108F1D0;
extern f32 D_00FB4A60;
extern f32 D_0108F1E4;
extern f32 D_0108F1EC;
extern s32 D_0108F1E0;
extern s32 D_0108F1C4;
extern s32 D_0108F258;
extern s32 D_0108F1B8;
extern s32 D_0108F1A0;
extern s32 D_0108F19C;
extern s32 D_0108F1F4;
extern s32 D_0108F190;
extern s32 D_00FB4A58;
extern s32 D_00FB4A5C;
extern s8 D_00FB4EBB;
extern s8 D_00FB4EB8;
extern s8 D_00FB4EB9;
extern s8 D_00FB4EBA;
extern Hdr D_00FB4F50;
extern s32 D_0108F25C;
extern s32 D_0108F254;
extern s32 D_00FB4A50;
extern s32 D_0108F180;
extern Obj *D_00FB4F4C;
s32 sceGsSyncPath(s32, s32);
s32 func_001be278(void);
void func_00f6ad98(void);
s32 func_0024b778(s32);
Obj *func_0024b7a0(s32, s32, s32, s32);
s32 func_00f69f98(void);
void func_00f6ae68(void);
void func_00f77af0(void);
void func_00f748f8(void);
void func_00f749d8(void);

void func_00f69fd0(s32 a)
{
    s32 v, sz, top;
    s32 a34, a4c, a38;

    if (a == 0) {
        D_0108F1B4 = 0;
        D_00FB4A54 = 0;
    } else {
        D_0108F1B4 = 1;
    }
    D_003F34B0[0] = 0xB4B4B4;
    D_003F34B0[1] = 0xB4B4B4;
    sceGsSyncPath(0, 0);
    D_0108F1BC = 0;
    D_0108F204 = 1;
    a34 = D_00FB4D34;
    D_0108F198 = -80;
    D_0108F1E4 = 128.0f;
    D_0108F1C4 = a34;
    D_0108F1C0 = 0;
    D_0108F1EC = 128.0f;
    a38 = D_00FB4D38;
    D_0108F194 = -80;
    a4c = D_00FB4D4C;
    D_0108F1D4 = a4c;
    D_0108F1C8 = a38;
    D_0108F1E0 = 128;
    D_0108F1F0 = 128.0f;
    D_0108F1E8 = 128.0f;
    D_00FB4A60 = D_00FB4AAC;
    D_0108F1CC = a34;
    D_0108F1DC = 128;
    D_0108F258 = 0;
    D_0108F1B8 = 0;
    D_0108F1A0 = 0;
    D_0108F1D0 = a38;
    D_0108F19C = 0;
    D_0108F1F4 = 0;
    D_0108F190 = 0;
    v = func_001be278() + 1;
    D_00FB4A58 = v;
    D_00FB4A5C = v;
    if (D_00FB4EBB == 0) {
        func_00f6ad98();
        D_0108F254 = 1;
        D_0108F25C = D_00FB4F50.xC;
        D_00FB4A50 = 1;
        D_00FB4EB8 = 0;
        D_00FB4EB9 = 0;
        D_00FB4EBA = 0;
        D_00FB4EBB = 1;
        sz = func_0024b778(5);
        top = D_00FB4F50.x14;
        D_00FB4F4C = func_0024b7a0(5, top, 0, sz);
        D_0108F180 = top + sz;
        if (D_00FB4F50.x18 < top + sz + 0x8800 - D_00FB4F50.x14) {
            __asm__ volatile("break");
        }
        func_00f69f98();
        D_00FB4F4C->fn(func_00f6ae68, 1, 0);
        D_00FB4F4C->fn(func_00f77af0, 1, 0);
        D_00FB4F4C->fn(func_00f748f8, 1, 1);
        D_00FB4F4C->fn(func_00f749d8, 1, 3);
    }
}

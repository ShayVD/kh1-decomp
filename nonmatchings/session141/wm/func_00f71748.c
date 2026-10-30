/* Round 36 (wgb): no change. Same note as gb func_00f4a650: the o3->f24 / o3->h8 stores sit above the o4 stores, valid only if o3 and o4 are distinct objects. */
/* Round 35 (wgb): wm.x func_00f71748 near miss: 35 -> 21 words, score 62 -> 38 (1040 = 1040). port.py of gb func_00f4a650's round 35 draft (statement order from the dependency-safe hill climb); left: FP temporary numbering in the panel blocks. Earlier header below. */
/* score 62 (35 words; 1040 vs 1040 bytes). Startup and layout: resets the tables, pairs linked entries (96-byte records, link at +9), then lays out six panels. Fixes: write the 0x100 clear loop as an ascending `for (i = 0; i < 256; i++)` (gcc reverses it to match the original); D_0108F3B0 updated with ++ in place, not through a local k; a brute-forced statement order in the first panel block. Left: float scheduling and register choice in the two panel blocks (512-x sub.s placement, the halfword -10 stores), and two lui/sd swaps in the prologue and pair block. */
typedef struct { u8 pad[5]; s8 b5; u8 pad2[2]; s16 h8; u8 pad3[10]; f32 f20; f32 f24; } Obj;
typedef struct { u8 b0; u8 b1; u8 b2; u8 b3; u8 b4[4]; u8 b8; u8 b9; u8 pad[86]; } Ent;
extern s32 D_0108F418, D_0108F41C, D_0108F420;
extern s32 D_0108F338[];
extern Ent *D_0108F310[];
extern u8 D_0108F3B8[];
extern s32 D_0108F3F0[];
extern s8 D_0108F428[];
extern s32 D_0108F3B0;
extern s32 D_0108F308;
extern Ent *D_0108F3C8[];
extern s32 D_0108F360[];
extern s32 D_0108F388[];
extern s32 D_00FB4DD0;
extern s32 D_00FB4DD4;
extern s32 D_00FB4DC0;
extern s32 D_00FB4DC4;
s32 func_001bc4e0(void);
s32 func_001bc510(void);
void func_00f70f40(void);
void func_00f71058(void);
void func_00f71508(void);
void func_00f712b8(s32, s32);
void func_00f71690(void);
void func_00f6a448(void);
s32 func_001f0118(s32, s32);

void func_00f71748(Obj *o1, Obj *o2, Obj *o3, Obj *o4, Obj *o5, Obj *o6)
{
    s32 i, j, k, n, v, found;
    Ent *base, *e, *f;
    f32 x, w;
    s8 *p;

    D_0108F418 = -1;
    D_0108F41C = 0;
    D_0108F420 = -1;
    for (i = 0; i < 10; i++) {
        D_0108F310[i] = 0;
        D_0108F338[i] = 0;
        D_0108F3B8[i] = 0;
        D_0108F3F0[i] = 0;
    }
    for (i = 0; i < 256; i++) {
        D_0108F428[i] = 0;
    }
    base = (Ent *)(func_001bc4e0() + 96);
    n = func_001bc510() - 1;
    D_0108F3B0 = 0;
    D_0108F308 = 0;
    if (n >= 256) {
        __asm__ volatile("break");
    }
    for (i = 0; i < n; i++) {
        e = &base[i];
        if (D_0108F428[i] != 0) continue;
        if (e->b0 == 0) continue;
        if (e->b8 != 0) continue;
        if (e->b3 == 0) continue;
        found = 0;
        if (e->b9 != 0) {
            j = e->b9 - 1;
            f = &base[j];
            if (f->b0 != 0 && f->b8 == 0 && f->b3 != 0 && f->b9 == i + 1) {
                D_0108F3C8[D_0108F3B0] = e;
                D_0108F360[D_0108F3B0] = i;
                D_0108F428[i] = 1;
                D_0108F428[j] = 1;
                D_0108F3B0++;
                D_0108F3C8[D_0108F3B0] = f;
                found = 1;
                D_0108F360[D_0108F3B0] = j;
                D_0108F3B0++;
            }
        }
        if (!found) {
            D_0108F428[i] = 1;
            k = D_0108F308;
            D_0108F310[k] = e;
            D_0108F308 = k + 1;
            D_0108F388[k] = i;
        }
    }
    func_00f70f40();
    func_00f71058();
    func_00f71508();
    func_00f712b8(-1, -1);
    func_00f71690();
    func_00f6a448();
    v = func_001f0118(83, o1->b5);
    o1->f20 = D_00FB4DD0;
    w = D_00FB4DC0 - 20;
    o1->f24 = w;
    o3->f24 = w + 8.0f;
    x = D_00FB4DD0 + v + 10;
    o3->h8 = D_00FB4DD0 - 10;
    o4->f24 = w + 8.0f;
    o4->h8 = 512.0f - x;
    o3->f20 = 0.0f;
    o4->f20 = x;
    v = func_001f0118(84, o2->b5);
    o2->f20 = D_00FB4DD4;
    x = D_00FB4DD0 + v + 10;
    w = D_00FB4DC4 - D_0108F3B0 / 2 * 28 + 8;
    o2->f24 = w;
    o6->f24 = w + 8.0f;
    o5->f24 = w + 8.0f;
    o5->f20 = 0.0f;
    o5->h8 = D_00FB4DD4 - 10;
    o6->h8 = 512.0f - x;
    o6->f20 = x;
}

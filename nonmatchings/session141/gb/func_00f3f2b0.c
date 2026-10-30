/* drafttwins.py: score 69 -> 67, port.py of the wm twin func_00f663a8 draft. Earlier header below. */
/* Round 36 (wgb): gb.x func_00f3f2b0 near miss: 151 -> 150 words, score 71 -> 69 (aligned diff 50 -> 47). Statement order from tools/ovl/hill3.py (score-ranked, strict dependency rules). Tried: hill3 sweep of every gb RANKING row and wm RANKING rows 1-100 (85-90 s, seed 1; strict rules; the order kept passes hill3.py --check against the previous draft), and port.py from the twin (not better). Earlier header below. */
typedef struct { f32 m[16]; } M64;
extern s32 D_00F82700;
extern s32 D_00F82704;
extern f32 D_00F82708;
extern f32 D_00F8270C;
extern f32 D_00F82710;
extern f32 D_00F82714;
void func_00f3f2b0(M64 *a, M64 *b, M64 *c, kh1_u128 *src, s32 n) {
    s32 i;
    f32 *v = (f32 *)0x1100FFA0;
    kh1_u128 *d;
    v[0] = 2048.0f - D_00F82700 * 0.5f;
    v[1] = 2048.0f - D_00F82704 * 0.5f;
    d = (kh1_u128 *)0x1100C0C0;
    ((s32 *)v)[2] = 0;
    v[3] = D_00F8270C;
    v[5] = D_00F82704 * 0.5f + 2048.0f;
    v[4] = D_00F82700 * 0.5f + 2048.0f;
    ((s32 *)v)[6] = 0;
    v[11] = D_00F8270C;
    v[7] = D_00F82708;
    v[10] = D_00F82714;
    v[8] = D_00F82708;
    v[9] = D_00F82710;
    *(M64 *)0x1100C000 = *a;
    *(M64 *)0x1100C040 = *b;
    *(M64 *)0x1100C080 = *c;
    for (i = 0; i < n; i++) {
        *d++ = *src++;
    }
}

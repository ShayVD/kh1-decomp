/* Round 41 wwm2: score 73 -> 71, port.py of the gb twin func_00f3f2b0 draft (r41/twins.py pairs wm and gb drafts with the same target mnemonics). Earlier header below. */
/* score 73 in nostrict (151 words; 612 vs 664 bytes). Writes 12 floats to VU memory 0x1100FFA0, copies three 64-byte unaligned blocks (ldl/sdl) to 0x1100C000/40/80, then lq/sq copies n qwords to 0x1100C0C0. The original reloads every global (D_0108EEC0..EED4) after each VU store, and keeps their addresses in registers. Ours CSEs the loads because gcc can tell the constant VU address from the globals. Volatile f or volatile globals did not reproduce it. */
typedef struct { f32 m[16]; } M64;
extern s32 D_0108EEC0;
extern s32 D_0108EEC4;
extern f32 D_0108EEC8;
extern f32 D_0108EECC;
extern f32 D_0108EED0;
extern f32 D_0108EED4;
void func_00f663a8(M64 *a, M64 *b, M64 *c, kh1_u128 *src, s32 n) {
    f32 *v = (f32 *)0x1100FFA0;
    kh1_u128 *d;
    s32 i;
    v[0] = 2048.0f - D_0108EEC0 * 0.5f;
    v[1] = 2048.0f - D_0108EEC4 * 0.5f;
    ((s32 *)v)[2] = 0;
    v[3] = D_0108EECC;
    v[4] = D_0108EEC0 * 0.5f + 2048.0f;
    v[5] = D_0108EEC4 * 0.5f + 2048.0f;
    ((s32 *)v)[6] = 0;
    v[7] = D_0108EEC8;
    v[8] = D_0108EEC8;
    v[9] = D_0108EED0;
    v[10] = D_0108EED4;
    v[11] = D_0108EECC;
    *(M64 *)0x1100C000 = *a;
    *(M64 *)0x1100C040 = *b;
    *(M64 *)0x1100C080 = *c;
    d = (kh1_u128 *)0x1100C0C0;
    for (i = 0; i < n; i++) {
        *d++ = *src++;
    }
}

/* Round 35 (wgb): wm.x func_00f4c610 near miss: 69 -> 42 words, score 77 -> 71 (now 276 vs 280 bytes, was 284). port.py of gb func_00f25518's round 35 draft (store order from the dependency-safe hill climb; bitfield layout as gb). Earlier header below. */
/* 69 words (score 77, 284 vs 280). Fills 24-float struct from D_00F9B540; 0x58 read as u64 bitfield at bit 36. Store-scheduling puzzle. */
typedef struct {
    u8 pad0[0x58];
    u64 lo : 32;
    u16 b0 : 4;
    u16 b1 : 4;
    u16 b2 : 4;
    u16 b3 : 4;
    u16 hi;
    u8 pad60[0x88 - 0x60];
    f32 fov;
    u8 pad8c[0xA6 - 0x8C];
    u16 w;
    u16 pad_a8;
    u16 h;
    u8 padac[0x10D4 - 0xAC];
    s32 rx;
    s32 ry;
} GbWorld;
extern GbWorld *D_00F9B540;

void func_00f4c610(f32 *o) {
    GbWorld *w = D_00F9B540;
    o[2] = w->fov;
    o[18] = -(w->h * 200.0f) * 0.5f;
    o[7] = 1.0f;
    o[3] = 0.0f;
    o[4] = 0.0f;
    o[5] = 0.0f;
    o[23] = 1.0f;
    o[1] = 0.0f;
    o[16] = -(w->w * 200.0f) * 0.5f;
    o[8] = 0.0f;
    o[15] = 0.0f;
    o[10] = 0.0f;
    o[6] = 1.0f;
    o[12] = 0.0f;
    o[13] = 0.0f;
    o[14] = 0.0f;
    o[11] = 1.0f;
    o[17] = w->b1 * 200.0f + 100.0f;
    o[0] = 0.0f;
    o[22] = 0.0f;
    o[19] = 1.0f;
    o[20] = w->rx * 3.1415927f * (1.0f / 2048);
    o[21] = w->ry * 3.1415927f * (1.0f / 2048);
    o[9] = 1.0f;
}

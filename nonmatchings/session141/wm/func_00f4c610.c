/* 69 words (score 77, 284 vs 280). Fills 24-float struct from D_00F9B540; 0x58 read as u64 bitfield at bit 36. Store-scheduling puzzle. */
typedef struct {
    u8 pad[0x58];
    u64 b0 : 36;
    u64 lv : 16;
    u64 b1 : 12;
    u8 pad60[0x88 - 0x60];
    f32 f88;
    u8 pad8c[0xA6 - 0x8C];
    u16 w;
    u16 pad2;
    u16 h;
    u8 padac[0x10D4 - 0xAC];
    s32 ry;
    s32 rx;
} W4c610;
typedef struct { f32 v[4]; } V4c610;
typedef struct { V4c610 a, b, c, d; f32 x, y, z, w; f32 rx, ry, rz, rw; } O4c610;
extern W4c610 *D_00F9B540;

void func_00f4c610(O4c610 *o) {
    W4c610 *w = D_00F9B540;

    o->a.v[0] = 0;
    o->a.v[1] = 0;
    o->a.v[2] = w->f88;
    o->a.v[3] = 0;
    o->b.v[0] = 0;
    o->b.v[1] = 0;
    o->b.v[2] = 1.0f;
    o->b.v[3] = 1.0f;
    o->c.v[0] = 0;
    o->c.v[1] = 1.0f;
    o->c.v[2] = 0;
    o->c.v[3] = 1.0f;
    o->d.v[0] = 0;
    o->d.v[1] = 0;
    o->d.v[2] = 0;
    o->d.v[3] = 0;
    o->x = -(w->w * 200.0f) * 0.5f;
    o->y = (w->lv & 0xF) * 200.0f + 100.0f;
    o->z = -(w->h * 200.0f) * 0.5f;
    o->w = 1.0f;
    o->rx = w->ry * 3.1415925026f * (1.0f / 2048.0f);
    o->ry = w->rx * 3.1415925026f * (1.0f / 2048.0f);
    o->rz = 0;
    o->rw = 1.0f;
}

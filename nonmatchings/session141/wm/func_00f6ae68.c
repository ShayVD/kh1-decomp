/* Round 47 wwm2: score 215 -> 207, hill3o statement order. Earlier header below. */
/* Round 36 (wwm2): wm.x func_00f6ae68 near miss: score 245 -> 215 (428 -> 419 words, 1852 vs 1864); statement order from the score-ranked dependency-safe hill3 (r35/hill3.py, 120 s, seed 363). Earlier header below. */
/* score 245 (1852 vs 1864). The endless draw loop was read from the asm. It draws a 6x8 grid of 64x64 tiles with func_00f693e0, then an optional func_00f696a0 sprite (when D_0108F1BC == 0 and D_0108F204 and D_0108F254 are set), four func_00f69df0 gradient quads from the Fx block at D_0108F208, and four fixed func_00f693e0 images. Last comes the jump-table image picked by D_00FB4A50 (1..10; default, 1 and 7 share one entry; table read from wm.elf at 0x00FBA0A0). Left: the 68/72 alpha selects come out as movz where the original uses movn with 68 and 72 kept in s1/s4; the s-register assignment around &D_00FB4F50 and &D_00FB4C30 differs; the size is 12 bytes short. */
typedef struct { u8 r, g, b, a; } Rgba;
typedef struct { u8 pad[28]; u8 *base; } Res;
typedef struct {
    s32 c0[4];
    s32 f10;
    s32 c1[4];
    s32 f24;
    s32 c2[4];
    s32 y38;
    s32 y3C;
} Fx;
extern s32 D_00FB4A50;
extern f32 D_00FB4A60;
extern s32 D_00FB4A84;
extern s32 D_00FB4A88;
extern s32 D_00FB4A8C;
extern s32 D_00FB4A90;
extern s32 D_00FB4A94;
extern s32 D_00FB4A98;
extern s32 D_00FB4A9C;
extern s32 D_00FB4AA0;
extern s32 D_00FB4AA4;
extern s32 D_00FB4AA8;
extern s32 D_00FB4C14;
extern s32 D_00FB4C18;
extern s32 D_00FB4C1C;
extern s32 D_00FB4C20;
extern s32 D_00FB4C30;
extern s32 D_00FB4C34;
extern s32 D_00FB4C38;
extern s32 D_00FB4C3C;
extern Res D_00FB4F50;
extern s32 D_0108F1BC;
extern s32 D_0108F1C4;
extern s32 D_0108F1C8;
extern f32 D_0108F1E4;
extern s32 D_0108F204;
extern Fx D_0108F208;
extern s32 D_0108F254;
void func_0024e468(s32);
void func_00f693e0(void *, void *, s32, s32, s32, s32, s32, Rgba *, s32, u64, s32, u64);
void func_00f696a0(void *, void *, s32, s32, s32, s32, s32, Rgba *, f32, s32, u64, s32, u64);
void func_00f69df0(Rgba *, s32 *, s32 *, u32);

void func_00f6ae68(void)
{
    Rgba c[4];
    s32 x[4];
    s32 y[4];

    s32 i, j, h;
    u32 img, clut;
    Fx *f;
    u32 a2;
    u64 al;
loop:
    {
        al = 68;
        c[0].r = D_00FB4A84;
        c[0].g = D_00FB4A88;
        c[0].b = D_00FB4A8C;
        c[0].a = D_00FB4A90;
        if (D_00FB4A94) al = 72;
        for (i = 0; i < 6; i++) {
            for (j = 0; j < 8; j++) {
                func_00f693e0(D_00FB4F50.base + 0x18800, D_00FB4F50.base + 0x1C000, j * 64, i * 64, 64, 64, 4, c, 0, al, 0, 0x5001D);
            }
        }
        if (D_0108F1BC == 0 && D_0108F204 && D_0108F254) {
            c[0].r = D_00FB4A9C;
            c[0].g = D_00FB4AA0;
            c[0].b = D_00FB4AA4;
            c[0].a = (s32)(D_00FB4AA8 * D_0108F1E4 * 0.0078125f);
            h = (s32)(D_00FB4A60 * 128.0f) / 2;
            func_00f696a0(D_00FB4F50.base + 0x14800, D_00FB4F50.base + 0x1BC00, D_0108F1C4 - h, D_0108F1C8 - h, 128, 128, 8, c, D_00FB4A60, 0, D_00FB4A98 ? 72 : 68, 0, 0x5001D);
        }
        f = &D_0108F208;
        c[0].r = c[1].r = f->c2[0];
        c[0].g = c[1].g = f->c2[1];
        c[0].b = c[1].b = f->c2[2];
        c[0].a = c[1].a = f->c2[3];
        c[2].r = c[3].r = f->c1[0];
        c[2].g = c[3].g = f->c1[1];
        c[2].b = c[3].b = f->c1[2];
        c[2].a = c[3].a = f->c1[3];
        x[0] = 0; x[1] = 512; x[2] = 0; x[3] = 512;
        y[0] = 0; y[1] = 0; y[2] = f->y38; y[3] = f->y38;
        func_00f69df0(c, x, y, f->f24 == 0 ? 68 : 72);
        c[0].r = c[1].r = f->c1[0];
        c[0].g = c[1].g = f->c1[1];
        c[0].b = c[1].b = f->c1[2];
        c[0].a = c[1].a = f->c1[3];
        c[2].r = c[3].r = f->c2[0];
        c[2].g = c[3].g = f->c2[1];
        c[2].b = c[3].b = f->c2[2];
        c[2].a = c[3].a = f->c2[3];
        x[0] = 0; x[1] = 512; x[2] = 0; x[3] = 512;
        y[0] = f->y3C; y[1] = f->y3C; y[2] = 384; y[3] = 384;
        a2 = 68;
        func_00f69df0(c, x, y, f->f24 == 0 ? 68 : 72);
        y[0] = f->y38 - 2; y[1] = f->y38 - 2; y[2] = f->y38; y[3] = f->y38;
        c[0].r = c[1].r = c[2].r = c[3].r = f->c0[0];
        c[0].g = c[1].g = c[2].g = c[3].g = f->c0[1];
        c[0].b = c[1].b = c[2].b = c[3].b = f->c0[2];
        x[0] = 0; x[1] = 512; x[2] = 0; x[3] = 512;
        c[0].a = c[1].a = c[2].a = c[3].a = f->c0[3];
        if (f->f10 == 0) a2 = 68; else a2 = 72;
        func_00f69df0(c, x, y, a2);
        y[0] = f->y3C; y[1] = f->y3C; y[2] = f->y3C + 2; y[3] = f->y3C + 2;
        func_00f69df0(c, x, y, a2);
        c[0].r = c[0].g = c[0].b = c[0].a = 128;
        func_00f693e0(D_00FB4F50.base, D_00FB4F50.base + 0x19000, D_00FB4C14, D_00FB4C18, 512, 112, 8, c, 0, 68, 0, 0x5001D);
        func_00f693e0(D_00FB4F50.base + 0x22C00, D_00FB4F50.base + 0x23C00, D_00FB4C1C, D_00FB4C20, 256, 32, 4, c, 0, 68, 0, 0x5001D);
        c[0].a = 76;
        func_00f693e0(D_00FB4F50.base + 0xE000, D_00FB4F50.base + 0x19400, D_00FB4C30, D_00FB4C34, 64, 64, 8, c, 0, 68, 0, 0x5001D);
        c[0].a = 38;
        func_00f693e0(D_00FB4F50.base + 0xF000, D_00FB4F50.base + 0x19800, D_00FB4C30, D_00FB4C34, 64, 64, 8, c, 0, 72, 0, 0x5001D);
        switch (D_00FB4A50) {
        default:
        case 1:
        case 7:
            img = 0x10000; clut = 0x19C00; break;
        case 2:
            img = 0x21400; clut = 0x21C00; break;
        case 3:
            img = 0x11000; clut = 0x1A400; break;
        case 4:
            img = 0x11800; clut = 0x1A800; break;
        case 5:
            img = 0x12000; clut = 0x1AC00; break;
        case 6:
            img = 0x12800; clut = 0x1B000; break;
        case 8:
            img = 0x22000; clut = 0x22800; break;
        case 9:
            img = 0x13000; clut = 0x1B400; break;
        case 10:
            img = 0x10800; clut = 0x1A000; break;
        }
        c[0].r = c[0].g = c[0].b = 128;
        c[0].a = 64;
        func_00f693e0(D_00FB4F50.base + img, D_00FB4F50.base + clut, D_00FB4C38, D_00FB4C3C, 64, 64, 4, c, 0, 68, 0, 0x5001D);
        func_0024e468(1);
    }
    goto loop;
}

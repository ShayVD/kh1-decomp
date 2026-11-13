/* Round 47 wwm2: score 215 -> 213, port.py of the wm twin func_00f6ae68 draft. Earlier header below. */
/* Round 40 (wgb): gb.x func_00f43d70 near miss: 419 words, score 221 -> 215. msd showed lui 0x109 / addiu -3576 in ours where the target has lui 0xf8 / addiu 10824: the Fx block was the wm symbol D_0108F208 (wm address); the gb one is D_00F82A48. hill3 (200 s, every build mode the same) found nothing further. Earlier header below. */
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
extern s32 D_00F702D0;
extern f32 D_00F702E0;
extern s32 D_00F70304;
extern s32 D_00F70308;
extern s32 D_00F7030C;
extern s32 D_00F70310;
extern s32 D_00F70314;
extern s32 D_00F70318;
extern s32 D_00F7031C;
extern s32 D_00F70320;
extern s32 D_00F70324;
extern s32 D_00F70328;
extern s32 D_00F70494;
extern s32 D_00F70498;
extern s32 D_00F7049C;
extern s32 D_00F704A0;
extern s32 D_00F704B0;
extern s32 D_00F704B4;
extern s32 D_00F704B8;
extern s32 D_00F704BC;
extern Res D_00F707D0;
extern s32 D_00F829FC;
extern s32 D_00F82A04;
extern s32 D_00F82A08;
extern f32 D_00F82A24;
extern s32 D_00F82A44;
extern Fx D_00F82A48; /* gb.x's own block (lui 0xf8 / addiu 10824); D_0108F208 was the wm twin's address: the GUMMI BLOCK MENU's darkening panel came out black and clear (overlay-verify) */
extern s32 D_00F82A94;
void func_0024e468(s32);
void func_00f422e8(void *, void *, s32, s32, s32, s32, s32, Rgba *, s32, u64, s32, u64);
void func_00f425a8(void *, void *, s32, s32, s32, s32, s32, Rgba *, f32, s32, u64, s32, u64);
void func_00f42cf8(Rgba *, s32 *, s32 *, u32);

void func_00f43d70(void)
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
        c[0].r = D_00F70304;
        c[0].g = D_00F70308;
        c[0].b = D_00F7030C;
        c[0].a = D_00F70310;
        if (D_00F70314) al = 72;
        for (i = 0; i < 6; i++) {
            for (j = 0; j < 8; j++) {
                func_00f422e8(D_00F707D0.base + 0x18800, D_00F707D0.base + 0x1C000, j * 64, i * 64, 64, 64, 4, c, 0, al, 0, 0x5001D);
            }
        }
        if (D_00F829FC == 0 && D_00F82A44 && D_00F82A94) {
            c[0].r = D_00F7031C;
            c[0].g = D_00F70320;
            c[0].b = D_00F70324;
            c[0].a = (s32)(D_00F70328 * D_00F82A24 * 0.0078125f);
            h = (s32)(D_00F702E0 * 128.0f) / 2;
            func_00f425a8(D_00F707D0.base + 0x14800, D_00F707D0.base + 0x1BC00, D_00F82A04 - h, D_00F82A08 - h, 128, 128, 8, c, D_00F702E0, 0, D_00F70318 ? 72 : 68, 0, 0x5001D);
        }
        f = &D_00F82A48;
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
        func_00f42cf8(c, x, y, f->f24 == 0 ? 68 : 72);
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
        func_00f42cf8(c, x, y, f->f24 == 0 ? 68 : 72);
        y[0] = f->y38 - 2; y[1] = f->y38 - 2; y[2] = f->y38; y[3] = f->y38;
        c[0].r = c[1].r = c[2].r = c[3].r = f->c0[0];
        c[0].g = c[1].g = c[2].g = c[3].g = f->c0[1];
        c[0].b = c[1].b = c[2].b = c[3].b = f->c0[2];
        x[0] = 0; x[1] = 512; x[2] = 0; x[3] = 512;
        c[0].a = c[1].a = c[2].a = c[3].a = f->c0[3];
        if (f->f10 == 0) a2 = 68; else a2 = 72;
        func_00f42cf8(c, x, y, a2);
        y[0] = f->y3C; y[1] = f->y3C; y[2] = f->y3C + 2; y[3] = f->y3C + 2;
        func_00f42cf8(c, x, y, a2);
        c[0].r = c[0].g = c[0].b = c[0].a = 128;
        func_00f422e8(D_00F707D0.base, D_00F707D0.base + 0x19000, D_00F70494, D_00F70498, 512, 112, 8, c, 0, 68, 0, 0x5001D);
        func_00f422e8(D_00F707D0.base + 0x22C00, D_00F707D0.base + 0x23C00, D_00F7049C, D_00F704A0, 256, 32, 4, c, 0, 68, 0, 0x5001D);
        c[0].a = 76;
        func_00f422e8(D_00F707D0.base + 0xE000, D_00F707D0.base + 0x19400, D_00F704B0, D_00F704B4, 64, 64, 8, c, 0, 68, 0, 0x5001D);
        c[0].a = 38;
        func_00f422e8(D_00F707D0.base + 0xF000, D_00F707D0.base + 0x19800, D_00F704B0, D_00F704B4, 64, 64, 8, c, 0, 72, 0, 0x5001D);
        switch (D_00F702D0) {
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
        func_00f422e8(D_00F707D0.base + img, D_00F707D0.base + clut, D_00F704B8, D_00F704BC, 64, 64, 4, c, 0, 68, 0, 0x5001D);
        func_0024e468(1);
    }
    goto loop;
}

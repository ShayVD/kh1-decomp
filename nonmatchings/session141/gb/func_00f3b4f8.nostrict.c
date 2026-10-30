/* Round 45 wwm2: score 185 -> 179, hill3o statement order under this build mode. Earlier header below. */
/* Round 44 wwm2: score 217 -> 185 under the nostrict build mode (r44/modescan.py). Earlier header below. */
/* gb.x func_00f3b4f8 near miss: 324 words differ, score 217 (ours 1372 bytes, original 1352). Port of wm func_00f625f0's near miss. port.py could not map D_00FA5FC8, so I mapped it by hand to D_00F61848 (D_00F61838 + 0x10). Same frame problem as the wm draft: the original keeps h on the stack at sp+16 and reloads 360.0f each time. */
typedef struct { u8 b[0x50]; u8 x50; u8 pad51[0x7e - 0x51]; s16 x7e; s16 x80; } World;
typedef struct { s32 r, g, b, a; } Col;
typedef struct { s32 x0; s32 x4; s32 x8; } Pad;
extern u8 D_00379F28[];
extern World *D_00F56DC0;
extern f32 D_00F61838;
extern s32 D_00F6183C;
extern s32 D_00F61840;
extern u8 D_00F61848[];
extern Col D_00F82640[];
extern Col D_00F826C0[];
extern s32 D_00F826F0;
extern s32 D_00F826F4;
void func_0011d768(s32);
Pad *func_001ba488(s32);
void func_001baa58(World *);
f32 func_001befc8(s32, void *);
void func_001bfac8(void);
void func_001c0078(s32);
s32 func_001c00e8(s32, void *, kh1_u128);
s32 func_00f20060(void);
void func_00f20170(s32, s32);
s32 func_00f39e50(s32);
s32 func_00f39e90(void);
void func_00f3b078(void);
void func_00f3b348(s32);

s32 func_00f3b4f8(void)
{
    u8 *p;

    Col *c;
    f32 f;
    s32 b8;
    s32 h;
    u8 save[8];
    Pad *pad;
    u8 *rgb;
    s32 i;
    c = D_00F82640;
    for (i = 0; i < 8; i++) {
        p = &D_00F56DC0->b[i];
        c->a = 128;
        rgb = &D_00379F28[*p * 4];
        c->r = rgb[0] >> 1;
        save[i] = *p;
        c->g = rgb[1] >> 1;
        c->b = rgb[2] >> 1;
        c++;
    }
    for (i = 0; i < 3; i++) {
        D_00F826C0[i].r = 0;
        D_00F826C0[i].g = 0;
        D_00F826C0[i].b = 0;
        D_00F826C0[i].a = 0;
    }
    D_00F826F4 = 0;
    D_00F826F0 = 0;
    D_00F6183C = D_00F56DC0->x80;
    D_00F61838 = D_00F6183C * 45.0f;
    func_0011d768(21);
    h = func_001c00e8(-1, func_00f3b078, 0);
    for (i = 0; i < 128; i += 8) {
        D_00F61840 = i;
        func_001bfac8();
    }
    for (;;) {
        pad = func_001ba488(0);
        b8 = pad->x8;
        if (b8 & 1) {
            func_00f20170(1, 0);
        } else if (b8 & 8) {
            if (func_00f20060() == 0) {
                for (i = 0; i < 8; i++) D_00F56DC0->b[i] = save[i];
                for (i = 128; i >= 0; i -= 8) {
                    D_00F61840 = i;
                    func_001bfac8();
                }
                func_001c0078(h);
                return 2;
            }
        } else if (b8 & 0xD000) {
            func_0011d768(3);
            if (pad->x8 & 0x8000) {
                for (i = 0; i < 8; i++) D_00F56DC0->b[i] = save[i];
            }
            for (i = 128; i >= 0; i -= 8) {
                D_00F61840 = i;
                func_001bfac8();
            }
            func_001bfac8();
            func_001c0078(h);
            func_001baa58(D_00F56DC0);
            D_00F56DC0->x7e = D_00F56DC0->b[D_00F56DC0->x80];
            D_00F56DC0->x50 = D_00F56DC0->x7e;
            return 1;
        } else if (pad->x4 & 0x400) {
            func_0011d768(20);
            f = D_00F61838;
            for (i = 0; i < 40; i++) {
                D_00F61838 = f + func_001befc8(i, D_00F61848);
                func_001bfac8();
            }
            D_00F6183C = (D_00F6183C + 9) & 7;
            D_00F61838 = D_00F6183C * 45.0f;
        } else if (pad->x4 & 0x800) {
            func_0011d768(20);
            f = D_00F61838;
            for (i = 0; i < 40; i++) {
                D_00F61838 = f - func_001befc8(i, D_00F61848);
                func_001bfac8();
            }
            D_00F6183C = (D_00F6183C + 7) & 7;
            D_00F61838 = D_00F6183C * 45.0f;
        } else if (b8 & 0x2000) {
            if (func_00f39e50(func_00f39e90()) == 0) {
                func_0011d768(71);
                func_00f3b348(D_00F6183C);
            }
        } else if (b8 & 0x10) {
            func_0011d768(20);
            D_00F826F4--;
        } else if (b8 & 0x40) {
            func_0011d768(20);
            D_00F826F4++;
        } else if (b8 & 0x80) {
            func_0011d768(20);
            D_00F826F0--;
        } else if (b8 & 0x20) {
            func_0011d768(20);
            D_00F826F0++;
        }
        D_00F826F0 &= 7;
        D_00F826F4 &= 7;
        if (D_00F61838 > 180.0f) {
            f = D_00F61838 - 360.0f;
            while (f > 180.0f) f -= 360.0f;
            D_00F61838 = f;
        }
        if (D_00F61838 < -180.0f) {
            f = D_00F61838 + 360.0f;
            D_00F61838 = f;
            while (f < -180.0f) f += 360.0f;
        }
        func_001bfac8();
    }
}

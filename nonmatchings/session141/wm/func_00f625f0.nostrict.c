/* Round 47 wwm2: score 181 -> 179, hill3o statement order. Earlier header below. */
/* Round 45 wwm2: score 183 -> 181, hill3o statement order under this build mode. Earlier header below. */
/* Round 44 wwm2: score 215 -> 183 under the nostrict build mode (r44/modescan.py). Earlier header below. */
/* Round 36 (wwm2): wm.x func_00f625f0 near miss: score 217 -> 215 (324 -> 324 words, 1372 vs 1352); statement order from the score-ranked dependency-safe hill3 (r35/hill3.py, 120 s, seed 363). Earlier header below. */
/* score 217 (1372 vs 1352). First draft from asm; the control flow is right. func_00f47158 takes no arguments and func_001c00e8 takes a kh1_u128 0 (por a2). Left: the frame. The original keeps h = func_001c00e8(...) on the stack at sp+16, with save[] at sp+0 and s0 at sp+32, because all of s0-s8 are taken by hoisted 0xfa/0x109 bases (s7 is a copy of s6). This draft keeps h in s8 and hoists 360.0f into f22, which the original reloads each time. The colour loop loads r/g/b through three copies of one pointer (a2 -> a0 -> v0); a struct array, locals and an inline helper did not reproduce that. */
typedef struct { u8 b[0x50]; u8 x50; u8 pad51[0x7e - 0x51]; s16 x7e; s16 x80; } World;
typedef struct { s32 r, g, b, a; } Col;
typedef struct { s32 x0; s32 x4; s32 x8; } Pad;
extern u8 D_00379F28[];
extern World *D_00F9B540;
extern f32 D_00FA5FB8;
extern s32 D_00FA5FBC;
extern s32 D_00FA5FC0;
extern u8 D_00FA5FC8[];
extern Col D_0108EE00[];
extern Col D_0108EE80[];
extern s32 D_0108EEB0;
extern s32 D_0108EEB4;
void func_0011d768(s32);
Pad *func_001ba488(s32);
void func_001baa58(World *);
f32 func_001befc8(s32, void *);
void func_001bfac8(void);
void func_001c0078(s32);
s32 func_001c00e8(s32, void *, kh1_u128);
s32 func_00f47158(void);
void func_00f47268(s32, s32);
s32 func_00f60f48(s32);
s32 func_00f60f88(void);
void func_00f62170(void);
void func_00f62440(s32);

s32 func_00f625f0(void)
{
    Col *c;
    u8 *p;
    u8 save[8];
    f32 f;

    u8 *rgb;
    s32 h;
    s32 b8;
    s32 i;
    Pad *pad;
    c = D_0108EE00;
    for (i = 0; i < 8; i++) {
        p = &D_00F9B540->b[i];
        rgb = &D_00379F28[*p * 4];
        c->r = rgb[0] >> 1;
        save[i] = *p;
        c->g = rgb[1] >> 1;
        c->a = 128;
        c->b = rgb[2] >> 1;
        c++;
    }
    for (i = 0; i < 3; i++) {
        D_0108EE80[i].r = 0;
        D_0108EE80[i].g = 0;
        D_0108EE80[i].b = 0;
        D_0108EE80[i].a = 0;
    }
    D_0108EEB4 = 0;
    D_0108EEB0 = 0;
    D_00FA5FBC = D_00F9B540->x80;
    D_00FA5FB8 = D_00FA5FBC * 45.0f;
    func_0011d768(21);
    h = func_001c00e8(-1, func_00f62170, 0);
    for (i = 0; i < 128; i += 8) {
        D_00FA5FC0 = i;
        func_001bfac8();
    }
    for (;;) {
        pad = func_001ba488(0);
        b8 = pad->x8;
        if (b8 & 1) {
            func_00f47268(1, 0);
        } else if (b8 & 8) {
            if (func_00f47158() == 0) {
                for (i = 0; i < 8; i++) D_00F9B540->b[i] = save[i];
                for (i = 128; i >= 0; i -= 8) {
                    D_00FA5FC0 = i;
                    func_001bfac8();
                }
                func_001c0078(h);
                return 2;
            }
        } else if (b8 & 0xD000) {
            func_0011d768(3);
            if (pad->x8 & 0x8000) {
                for (i = 0; i < 8; i++) D_00F9B540->b[i] = save[i];
            }
            for (i = 128; i >= 0; i -= 8) {
                D_00FA5FC0 = i;
                func_001bfac8();
            }
            func_001bfac8();
            func_001c0078(h);
            func_001baa58(D_00F9B540);
            D_00F9B540->x7e = D_00F9B540->b[D_00F9B540->x80];
            D_00F9B540->x50 = D_00F9B540->x7e;
            return 1;
        } else if (pad->x4 & 0x400) {
            func_0011d768(20);
            f = D_00FA5FB8;
            for (i = 0; i < 40; i++) {
                D_00FA5FB8 = f + func_001befc8(i, D_00FA5FC8);
                func_001bfac8();
            }
            D_00FA5FBC = (D_00FA5FBC + 9) & 7;
            D_00FA5FB8 = D_00FA5FBC * 45.0f;
        } else if (pad->x4 & 0x800) {
            func_0011d768(20);
            f = D_00FA5FB8;
            for (i = 0; i < 40; i++) {
                D_00FA5FB8 = f - func_001befc8(i, D_00FA5FC8);
                func_001bfac8();
            }
            D_00FA5FBC = (D_00FA5FBC + 7) & 7;
            D_00FA5FB8 = D_00FA5FBC * 45.0f;
        } else if (b8 & 0x2000) {
            if (func_00f60f48(func_00f60f88()) == 0) {
                func_0011d768(71);
                func_00f62440(D_00FA5FBC);
            }
        } else if (b8 & 0x10) {
            func_0011d768(20);
            D_0108EEB4--;
        } else if (b8 & 0x40) {
            func_0011d768(20);
            D_0108EEB4++;
        } else if (b8 & 0x80) {
            func_0011d768(20);
            D_0108EEB0--;
        } else if (b8 & 0x20) {
            func_0011d768(20);
            D_0108EEB0++;
        }
        D_0108EEB0 &= 7;
        D_0108EEB4 &= 7;
        if (D_00FA5FB8 > 180.0f) {
            f = D_00FA5FB8 - 360.0f;
            while (f > 180.0f) f -= 360.0f;
            D_00FA5FB8 = f;
        }
        if (D_00FA5FB8 < -180.0f) {
            f = D_00FA5FB8 + 360.0f;
            D_00FA5FB8 = f;
            while (f < -180.0f) f += 360.0f;
        }
        func_001bfac8();
    }
}

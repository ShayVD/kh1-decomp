/* NEAR MISS 567 words, score 544 (3008 vs 3040 bytes). Port of gb func_00f2ac20 (same score); ease tables mapped by hand: D_00FA5B38 / D_00FA5B60 = gb D_00F613B8 / D_00F613E0. See the gb file for what was tried. Round 19 (wwm1): 567 -> 547 raw words with sclimb.py (CONTEXT_ONLY toggles plus dependency-checked statement moves). Round 19 (wwm1): score 484 -> 460 with sclimb.py (CONTEXT_ONLY toggles plus dependency-checked statement moves). */
typedef struct {
    u64 pad0[9];
    u8 x48[4];
    u16 x4C;
    u8 pad4E[88 - 78];
    s32 x58;
    u16 h0 : 4;
    u16 h1 : 4;
    u16 h2 : 4;
    u16 h3 : 4;
    u16 pad5E;
    u16 f0 : 4;
    u16 f1 : 4;
    u16 f2 : 4;
    u16 f3 : 4;
    u16 g0 : 4;
    u16 g1 : 4;
    u16 g2 : 4;
    u16 g3 : 4;
    u8 pad64[116 - 100];
    u16 x74;
    u16 pad76;
    s16 x78;
    u16 pad7A;
    s16 x7C;
    u8 pad7E[148 - 126];
    s32 x94;
    u8 pad98[8];
    u16 xA0;
    u16 xA2;
    u16 xA4;
    u16 xA6;
    u16 xA8;
    u16 xAA;
    u8 padAC[0x10D4 - 172];
    s32 x10D4;
    s32 x10D8;
} World;
typedef struct { u8 pad[4]; u32 x4; u32 x8; } Pad;
extern World *D_00F9B540;
extern void *D_00F9B544;
extern s32 D_00FA5AF0;
extern s32 D_00FA5AFC;
extern s32 D_0108CD40;
extern s8 D_00F9B528[];
extern u8 D_00FA5B38[];
extern u8 D_00FA5B60[];
s32 func_00f4ca10(s32);
s32 func_00f4ca70(s32);
void func_00f530d0(void *, s32, s32, s32);
void func_00f50598(s32);
void func_00f516e0(s32);
Pad *func_001ba488(s32);
s32 func_00f4c510(Pad *);
void func_00f47268(s32, s32);
void func_00f51568(s32 *, s32 *);
s32 func_00f47158(void); CONTEXT_ONLY s32 func_00f47158() { return 0; }
void func_00f504f8(s32);
void func_00f48aa8(s32);
f32 func_001befc8(s32, void *);
void func_001bfac8(void); CONTEXT_ONLY void func_001bfac8() {}
void func_0011d768(s32);
void func_00f4b338(void *, s32);
void func_00f50968(void); CONTEXT_ONLY void func_00f50968() {}
void func_00f4b668(s32, void *);
void func_00f4b878(void *);
void func_00f51bc0(void); CONTEXT_ONLY void func_00f51bc0() {}
void func_00f57e78(s32);
s32 func_00f78350(s32, s32);
void func_00f51cd0(void);
void func_00f4afd0(void); CONTEXT_ONLY void func_00f4afd0() {}
void func_00f4bdf8(s32, s32);
s32 func_00f4bca8(s32, s32, s32, void *);

void func_00f51d18(void) {
    Pad *pad;
    s32 dx;
    s32 a0, a1;
    s32 nx, ny, nz, ox, oy, oz;
    s32 dir;
    s32 rx, ry, ax, ay;
    s32 id;
    s32 dz;
    s32 mode;
    s32 i, k;
    s32 dy;
    u8 *sub;
    s32 buf[20];
    s16 sv[8];
    s32 sel;
    u32 b;

    D_00FA5AF0 = 0;
    sel = 0;
    mode = 0;
    id = D_00F9B540->x4C - 1;
    D_00F9B540->x78 = 1;
    a0 = func_00f4ca10(id);
    a1 = func_00f4ca70(id);
    func_00f530d0(D_00F9B540->x48, a0, a1, 0);
    func_00f50598(1);
    for (;;) {
        func_00f516e0(mode);
        sub = (u8 *)D_00F9B540 + 160;
        pad = func_001ba488(0);
        dir = func_00f4c510(pad);
        D_00F9B540->x58 = 0;
        if (pad->x8 & 1) {
            D_0108CD40 = 0;
            func_00f47268(0, 0);
            D_0108CD40 = 1;
        }
        dy = 0;
        dx = 0;
        func_00f51568(&dx, &dy);
        dz = 0;
        b = pad->x8;
        if (b & 0x400) dz = 1;
        if (b & 0x100) dz = -1;
        if (b & 8) {
            if (func_00f47158() == 0) {
                func_00f504f8(0);
                func_00f48aa8(3);
                return;
            }
            b = pad->x8;
        }
        if (b & 0x800) {
            D_00F9B540->x78 = -1;
            func_00f48aa8(0);
            func_00f530d0(0, 0, 0, 0);
            func_00f50598(1);
            return;
        }
        if (b & 0x200) {
            D_00F9B540->x78 = -1;
            func_00f48aa8(2);
            func_00f530d0(0, 0, 0, 0);
            func_00f50598(1);
            return;
        }
        if (dir & 0xF000) {
            rx = D_00F9B540->x10D4;
            ax = 0;
            ry = D_00F9B540->x10D8;
            if (rx < 1024) {
                ax = (dir & 0x4000) ? 256 : 0;
            }
            if (rx >= -1023) {
                if (dir & 0x1000) {
                    ax = -256;
                }
            }
            ay = (dir & 0x8000) ? 1024 : 0;
            if (dir & 0x2000) {
                ay = -1024;
            }
            if (ax | ay) {
                for (i = 0; i < 15; i++) {
                    f32 fa = (f32)ax * func_001befc8(i, D_00FA5B38);
                    f32 fc = (f32)ay * func_001befc8(i, D_00FA5B60);
                    s32 y;
                    D_00F9B540->x10D4 = rx + (s32)(fa / 22.5f);
                    y = ry + (s32)(fc / 90.0f);
                    D_00F9B540->x10D8 = y;
                    if (y >= 2048) {
                        D_00F9B540->x10D8 = y - 4096;
                    }
                    if (D_00F9B540->x10D8 < -2048) {
                        D_00F9B540->x10D8 += 4096;
                    }
                    func_001bfac8();
                }
                D_00F9B540->x10D8 = ry + ay;
                D_00F9B540->x10D4 = rx + ax;
                if (ry + ay >= 2048) {
                    D_00F9B540->x10D8 = ry + ay - 4096;
                }
                if (D_00F9B540->x10D8 < -2048) {
                    D_00F9B540->x10D8 += 4096;
                }
            }
        } else switch (mode) {
        case 0:
            if (b & 0x8000) {
                if (*(u16 *)(sub + 4) == 0) goto move;
                mode = 1;
                func_0011d768(2);
                D_00F9B540->x78 = 4;
                func_00f530d0(0, 0, 0, 0);
                func_00f50598(2);
                func_00f4b338(D_00F9B544, 0);
                if (D_00F9B540->x7C == 0) {
                    D_00FA5AFC = 128;
                }
                goto tail;
            }
            if (pad->x4 & 0x2000) {
                func_00f50968();
                dy = 0;
                dx = 0;
                dz = 0;
            } else if (b & 0x4000) {
                if (D_00F9B540->x74 & 2) {
                    func_0011d768(3);
                    sv[0] = *(u16 *)((u8 *)D_00F9B540 + 96);
                    func_00f4b668(*(u16 *)((u8 *)D_00F9B540 + 96), D_00F9B544);
                    {
                        s32 c2 = D_00F9B540->f2;
                        s32 c0 = D_00F9B540->f0;
                        D_00F9B540->h0 = c0;
                        D_00F9B540->g0 = 1;
                        D_00F9B540->h2 = c2;
                        D_00F9B540->g1 = 1;
                        D_00F9B540->g2 = 1;
                    }
                    func_00f4b878(D_00F9B544);
                    func_00f4b338(D_00F9B544, 0);
                }
            } else if (pad->x4 & 0x1000) {
                if (D_00F9B540->x94 > 0) {
                    func_00f51bc0();
                }
            } else if (dir & 0xF0) {
                if (dir & 0x10) {
                    func_00f57e78(1);
                } else if (dir & 0x40) {
                    func_00f57e78(0);
                } else if (dir & 0x20) {
                    func_00f57e78(2);
                } else if (dir & 0x80) {
                    func_00f57e78(3);
                }
            }
        move:
            if (dx | dz | dy) {
                ox = D_00F9B540->h0;
                nx = ox + dx;
                oy = D_00F9B540->h1;
                if (nx < 0) nx = 0;
                if (nx > *(u16 *)(sub + 6) - 1) nx = *(u16 *)(sub + 6) - 1;
                ny = oy + dz;
                if (ny < 0) ny = 0;
                oz = D_00F9B540->h2;
                if (ny > *(u16 *)(sub + 8) - 1) ny = *(u16 *)(sub + 8) - 1;
                nz = oz + dy;
                if (nz < 0) nz = 0;
                if (nz > *(u16 *)(sub + 10) - 1) nz = *(u16 *)(sub + 10) - 1;
                D_00F9B540->h0 = nx;
                D_00F9B540->h1 = ny;
                D_00F9B540->h2 = nz;
                if (ox != nx || oy != ny || oz != nz) {
                    func_0011d768(20);
                }
                func_00f4b338(D_00F9B544, 0);
            }
            break;
        case 1:
            if (b & 0x8000) {
                mode = 0;
                func_0011d768(3);
                D_00F9B540->x78 = 1;
                func_00f50598(1);
                if (D_00F9B540->x7C == 0) {
                    for (i = 0; i < 5; i++) {
                        D_00FA5AFC = 128 - i * 38 / 5;
                        func_001bfac8();
                    }
                    D_00FA5AFC = 90;
                }
                goto tail;
            }
            if ((b & 0x1000) && D_00F9B540->x94 > 0) {
                D_00F9B540->x58 = mode;
                func_00f50598(3);
                func_0011d768(2);
                if (func_00f78350(235, 1)) goto cancel;
                func_00f51cd0();
                mode = 0;
                func_00f4b878(D_00F9B544);
                func_00f4b338(D_00F9B544, 0);
                D_00F9B540->x78 = 1;
                goto done;
            }
            if (b & 0x4000) {
                D_00F9B540->x58 = 1;
                func_00f50598(3);
                func_0011d768(2);
                if (func_00f78350(30, 1)) {
                cancel:
                    func_00f50598(2);
                    goto tail;
                }
                func_00f4afd0();
                mode = 0;
                func_00f4b878(D_00F9B544);
                func_00f4b338(D_00F9B544, 0);
                D_00F9B540->x78 = 1;
            done:
                func_00f50598(1);
                a0 = func_00f4ca10(id);
                a1 = func_00f4ca70(id);
                func_00f530d0(D_00F9B540->x48, a0, a1, 0);
                if (D_00F9B540->x7C == 0) {
                    D_00FA5AFC = 90;
                }
                func_001bfac8();
                func_001bfac8();
                goto tail;
            }
            if (dir & 0xF0) {
                s32 q;
                dy = 0;
                dx = 0;
                q = D_00F9B540->x10D8 / 1024;
                if (dir & 0x10) {
                    dx = D_00F9B528[q * 4 + 8];
                    dy = D_00F9B528[q * 4 + 10];
                }
                if (dir & 0x40) {
                    dy = -D_00F9B528[q * 4 + 10];
                    dx = -D_00F9B528[q * 4 + 8];
                }
                k = 0;
                if (dx != 0) {
                    k = dx;
                    sel = 0;
                }
                if (dy != 0) {
                    k = dy;
                    sel = 2;
                }
                if (dir & 0x20) {
                    k = 1;
                    sel = 1;
                }
                if (dir & 0x80) {
                    sel = 1;
                    k = -1;
                }
                if (k == 0) goto tail;
                func_00f4bdf8(sel, k);
                func_00f4b878(D_00F9B544);
                func_00f4b338(D_00F9B544, 0);
                for (i = 0; i < 4; i++) {
                    func_001bfac8();
                }
                goto tail;
            }
            if (*(u16 *)(sub + 4) != 0) {
                D_00F9B540->x58 = 1;
                if (func_00f4bca8(dx, dz, dy, D_00F9B544)) {
                    func_0011d768(20);
                    ny = D_00F9B540->h1 + dz;
                    if (ny < 0) ny = 0;
                    if (ny > *(u16 *)(sub + 8) - 1) ny = *(u16 *)(sub + 8) - 1;
                    D_00F9B540->h1 = ny;
                    func_00f4b878(D_00F9B544);
                    func_00f4b338(D_00F9B544, 0);
                }
            }
            break;
        }
    tail:
        if ((D_00F9B540->x74 & 2) || mode != 0) {
            func_00f530d0(0, 0, 0, 0);
        } else {
            a0 = func_00f4ca10(id);
            a1 = func_00f4ca70(id);
            func_00f530d0(D_00F9B540->x48, a0, a1, 0);
        }
        func_001bfac8();
    }
}

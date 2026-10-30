/* Round 44 wwm2: score 460 -> 430 under the norlo build mode (r44/modescan.py). Earlier header below. */
/* Round 42 wwm2: score 544 -> 460, port.py of the wm twin func_00f51d18 draft, with its ease tables mapped by hand (wm D_00FA5B38 / D_00FA5B60 = gb D_00F613B8 / D_00F613E0). Earlier header below. */
/* NEAR MISS 567 words, score 544 (3008 vs 3040 bytes). Grid-cursor edit loop (sibling of func_00f31ea0): camera rotation on dir&0xF000, mode 0 = move cursor (x5C nibble bitfields clamped to sub xA6/xA8/xAA) / reset from x60 nibbles, mode 1 = menu actions (func_00f51258 confirm, func_00f24d00 layer step, fade D_00F6137C). Tried: World 8-aligned (u64 pad, gives the ld/sd bitfields), buf[20]+s16 sv[8] for the 256 frame, switch vs if on mode, dz and bitfield-order spellings. Left: dz comes out sra/andi instead of andi/sltu, D_00F56DC0 address-reg choices, and the mode-1 movement block ordering. */
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
extern World *D_00F56DC0;
extern void *D_00F56DC4;
extern s32 D_00F61370;
extern s32 D_00F6137C;
extern s32 D_00F80580;
extern s8 D_00F56DA8[];
extern u8 D_00F613B8[];
extern u8 D_00F613E0[];
s32 func_00f25918(s32);
s32 func_00f25978(s32);
void func_00f2bfd8(void *, s32, s32, s32);
void func_00f294a0(s32);
void func_00f2a5e8(s32);
Pad *func_001ba488(s32);
s32 func_00f25418(Pad *);
void func_00f20170(s32, s32);
void func_00f2a470(s32 *, s32 *);
s32 func_00f20060(void); CONTEXT_ONLY s32 func_00f20060() { return 0; }
void func_00f29400(s32);
void func_00f219b0(s32);
f32 func_001befc8(s32, void *);
void func_001bfac8(void); CONTEXT_ONLY void func_001bfac8() {}
void func_0011d768(s32);
void func_00f24240(void *, s32);
void func_00f29870(void); CONTEXT_ONLY void func_00f29870() {}
void func_00f24570(s32, void *);
void func_00f24780(void *);
void func_00f2aac8(void); CONTEXT_ONLY void func_00f2aac8() {}
void func_00f30d80(s32);
s32 func_00f51258(s32, s32);
void func_00f2abd8(void);
void func_00f23ed8(void); CONTEXT_ONLY void func_00f23ed8() {}
void func_00f24d00(s32, s32);
s32 func_00f24bb0(s32, s32, s32, void *);

void func_00f2ac20(void) {
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

    D_00F61370 = 0;
    sel = 0;
    mode = 0;
    id = D_00F56DC0->x4C - 1;
    D_00F56DC0->x78 = 1;
    a0 = func_00f25918(id);
    a1 = func_00f25978(id);
    func_00f2bfd8(D_00F56DC0->x48, a0, a1, 0);
    func_00f294a0(1);
    for (;;) {
        func_00f2a5e8(mode);
        sub = (u8 *)D_00F56DC0 + 160;
        pad = func_001ba488(0);
        dir = func_00f25418(pad);
        D_00F56DC0->x58 = 0;
        if (pad->x8 & 1) {
            D_00F80580 = 0;
            func_00f20170(0, 0);
            D_00F80580 = 1;
        }
        dy = 0;
        dx = 0;
        func_00f2a470(&dx, &dy);
        dz = 0;
        b = pad->x8;
        if (b & 0x400) dz = 1;
        if (b & 0x100) dz = -1;
        if (b & 8) {
            if (func_00f20060() == 0) {
                func_00f29400(0);
                func_00f219b0(3);
                return;
            }
            b = pad->x8;
        }
        if (b & 0x800) {
            D_00F56DC0->x78 = -1;
            func_00f219b0(0);
            func_00f2bfd8(0, 0, 0, 0);
            func_00f294a0(1);
            return;
        }
        if (b & 0x200) {
            D_00F56DC0->x78 = -1;
            func_00f219b0(2);
            func_00f2bfd8(0, 0, 0, 0);
            func_00f294a0(1);
            return;
        }
        if (dir & 0xF000) {
            rx = D_00F56DC0->x10D4;
            ax = 0;
            ry = D_00F56DC0->x10D8;
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
                    f32 fa = (f32)ax * func_001befc8(i, D_00F613B8);
                    f32 fc = (f32)ay * func_001befc8(i, D_00F613E0);
                    s32 y;
                    D_00F56DC0->x10D4 = rx + (s32)(fa / 22.5f);
                    y = ry + (s32)(fc / 90.0f);
                    D_00F56DC0->x10D8 = y;
                    if (y >= 2048) {
                        D_00F56DC0->x10D8 = y - 4096;
                    }
                    if (D_00F56DC0->x10D8 < -2048) {
                        D_00F56DC0->x10D8 += 4096;
                    }
                    func_001bfac8();
                }
                D_00F56DC0->x10D8 = ry + ay;
                D_00F56DC0->x10D4 = rx + ax;
                if (ry + ay >= 2048) {
                    D_00F56DC0->x10D8 = ry + ay - 4096;
                }
                if (D_00F56DC0->x10D8 < -2048) {
                    D_00F56DC0->x10D8 += 4096;
                }
            }
        } else switch (mode) {
        case 0:
            if (b & 0x8000) {
                if (*(u16 *)(sub + 4) == 0) goto move;
                mode = 1;
                func_0011d768(2);
                D_00F56DC0->x78 = 4;
                func_00f2bfd8(0, 0, 0, 0);
                func_00f294a0(2);
                func_00f24240(D_00F56DC4, 0);
                if (D_00F56DC0->x7C == 0) {
                    D_00F6137C = 128;
                }
                goto tail;
            }
            if (pad->x4 & 0x2000) {
                func_00f29870();
                dy = 0;
                dx = 0;
                dz = 0;
            } else if (b & 0x4000) {
                if (D_00F56DC0->x74 & 2) {
                    func_0011d768(3);
                    sv[0] = *(u16 *)((u8 *)D_00F56DC0 + 96);
                    func_00f24570(*(u16 *)((u8 *)D_00F56DC0 + 96), D_00F56DC4);
                    {
                        s32 c2 = D_00F56DC0->f2;
                        s32 c0 = D_00F56DC0->f0;
                        D_00F56DC0->h0 = c0;
                        D_00F56DC0->g0 = 1;
                        D_00F56DC0->h2 = c2;
                        D_00F56DC0->g1 = 1;
                        D_00F56DC0->g2 = 1;
                    }
                    func_00f24780(D_00F56DC4);
                    func_00f24240(D_00F56DC4, 0);
                }
            } else if (pad->x4 & 0x1000) {
                if (D_00F56DC0->x94 > 0) {
                    func_00f2aac8();
                }
            } else if (dir & 0xF0) {
                if (dir & 0x10) {
                    func_00f30d80(1);
                } else if (dir & 0x40) {
                    func_00f30d80(0);
                } else if (dir & 0x20) {
                    func_00f30d80(2);
                } else if (dir & 0x80) {
                    func_00f30d80(3);
                }
            }
        move:
            if (dx | dz | dy) {
                ox = D_00F56DC0->h0;
                nx = ox + dx;
                oy = D_00F56DC0->h1;
                if (nx < 0) nx = 0;
                if (nx > *(u16 *)(sub + 6) - 1) nx = *(u16 *)(sub + 6) - 1;
                ny = oy + dz;
                if (ny < 0) ny = 0;
                oz = D_00F56DC0->h2;
                if (ny > *(u16 *)(sub + 8) - 1) ny = *(u16 *)(sub + 8) - 1;
                nz = oz + dy;
                if (nz < 0) nz = 0;
                if (nz > *(u16 *)(sub + 10) - 1) nz = *(u16 *)(sub + 10) - 1;
                D_00F56DC0->h0 = nx;
                D_00F56DC0->h1 = ny;
                D_00F56DC0->h2 = nz;
                if (ox != nx || oy != ny || oz != nz) {
                    func_0011d768(20);
                }
                func_00f24240(D_00F56DC4, 0);
            }
            break;
        case 1:
            if (b & 0x8000) {
                mode = 0;
                func_0011d768(3);
                D_00F56DC0->x78 = 1;
                func_00f294a0(1);
                if (D_00F56DC0->x7C == 0) {
                    for (i = 0; i < 5; i++) {
                        D_00F6137C = 128 - i * 38 / 5;
                        func_001bfac8();
                    }
                    D_00F6137C = 90;
                }
                goto tail;
            }
            if ((b & 0x1000) && D_00F56DC0->x94 > 0) {
                D_00F56DC0->x58 = mode;
                func_00f294a0(3);
                func_0011d768(2);
                if (func_00f51258(235, 1)) goto cancel;
                func_00f2abd8();
                mode = 0;
                func_00f24780(D_00F56DC4);
                func_00f24240(D_00F56DC4, 0);
                D_00F56DC0->x78 = 1;
                goto done;
            }
            if (b & 0x4000) {
                D_00F56DC0->x58 = 1;
                func_00f294a0(3);
                func_0011d768(2);
                if (func_00f51258(30, 1)) {
                cancel:
                    func_00f294a0(2);
                    goto tail;
                }
                func_00f23ed8();
                mode = 0;
                func_00f24780(D_00F56DC4);
                func_00f24240(D_00F56DC4, 0);
                D_00F56DC0->x78 = 1;
            done:
                func_00f294a0(1);
                a0 = func_00f25918(id);
                a1 = func_00f25978(id);
                func_00f2bfd8(D_00F56DC0->x48, a0, a1, 0);
                if (D_00F56DC0->x7C == 0) {
                    D_00F6137C = 90;
                }
                func_001bfac8();
                func_001bfac8();
                goto tail;
            }
            if (dir & 0xF0) {
                s32 q;
                dy = 0;
                dx = 0;
                q = D_00F56DC0->x10D8 / 1024;
                if (dir & 0x10) {
                    dx = D_00F56DA8[q * 4 + 8];
                    dy = D_00F56DA8[q * 4 + 10];
                }
                if (dir & 0x40) {
                    dy = -D_00F56DA8[q * 4 + 10];
                    dx = -D_00F56DA8[q * 4 + 8];
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
                func_00f24d00(sel, k);
                func_00f24780(D_00F56DC4);
                func_00f24240(D_00F56DC4, 0);
                for (i = 0; i < 4; i++) {
                    func_001bfac8();
                }
                goto tail;
            }
            if (*(u16 *)(sub + 4) != 0) {
                D_00F56DC0->x58 = 1;
                if (func_00f24bb0(dx, dz, dy, D_00F56DC4)) {
                    func_0011d768(20);
                    ny = D_00F56DC0->h1 + dz;
                    if (ny < 0) ny = 0;
                    if (ny > *(u16 *)(sub + 8) - 1) ny = *(u16 *)(sub + 8) - 1;
                    D_00F56DC0->h1 = ny;
                    func_00f24780(D_00F56DC4);
                    func_00f24240(D_00F56DC4, 0);
                }
            }
            break;
        }
    tail:
        if ((D_00F56DC0->x74 & 2) || mode != 0) {
            func_00f2bfd8(0, 0, 0, 0);
        } else {
            a0 = func_00f25918(id);
            a1 = func_00f25978(id);
            func_00f2bfd8(D_00F56DC0->x48, a0, a1, 0);
        }
        func_001bfac8();
    }
}

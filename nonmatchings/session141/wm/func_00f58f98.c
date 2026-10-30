/* Round 47 wwm2: score 152 -> 150, hill3o statement order. Earlier header below. */
/* Round 46 wwm2: score 168 -> 152, hill3o statement order. Earlier header below. */
/* Round 46 wwm2: score 176 -> 168, func_00f55190 and func_00f4e3f8 declared s32. Earlier header below. */
/* wm.x func_00f58f98 near miss: 463 words differ, score 176 (ours 2032 bytes, original 1992). Port of gb func_00f31ea0 (nonmatchings/session141/gb) via tools/ovl/port.py, with the ease tables mapped by hand (D_00FA5D50 / D_00FA5D78 = gb D_00F615D0 / D_00F615F8); same diff, see the gb file for notes. */
typedef struct {
    u8 pad0[72];
    u16 x48;
    u16 x4A : 4;
    u16 y4A : 4;
    u16 z4A : 4;
    u16 r4A : 4;
    u16 x4C;
    u16 x4E;
    u8 pad50[4];
    u16 x54;
    u8 pad56[94 - 86];
    u16 x5E;
    u16 x60;
    u8 pad62[130 - 98];
    s16 x82;
    u8 pad84[148 - 132];
    s32 x94;
    u8 pad98[0x1010 - 152];
    OvlMtx m[3];
    s32 dma;
    s32 x10D4;
    s32 x10D8;
} World;
typedef struct { u8 pad[4]; u32 x4; u32 x8; } Pad;
extern World *D_00F9B540;
extern void *D_00F9B544;
extern s32 D_00FA5CE0;
extern s32 D_00F9B50C;
extern s32 D_00FA5D48;
extern u8 D_00FA5D50[];
extern u8 D_00FA5D78[];
extern s32 D_0108CE88;
extern u64 D_0108CE90[8];
extern u8 D_00379F28[][4];
s32 func_00f55190(void);
void func_00f551e8(void);
void func_00f55298(void);
void func_00f49430(s32, s32, s32, s32);
Pad *func_001ba488(s32);
s32 func_00f4c510(Pad *);
f32 func_001befc8(s32, void *);
void func_001bfac8(void);
s32 func_00f47158(void);
void func_00f47268(s32, s32);
void func_00f48aa8(s32);
s32 func_00f4e3f8(s32);
void func_00f58140(void);
void func_00f57db0(s32);
void func_00f59820(s32, s32);
void func_00f58300(void);
s32 func_00f625f0(void);
void func_00f504f8(s32);
s32 func_00f4cad0(s32);
void func_0011d768(s32);
void func_00f58bd0(s32);
s32 func_00f58128(s32);
void func_00f57cf0(s32);
void func_00f57e78(s32);
s32 func_001bb6d0(s32);
void func_00f4b338(void *, s32);

#define RGBAQ(r, g, b, a) ((u64)(r) | ((u64)(g) << 8) | ((u64)(b) << 16) | ((u64)(a) << 24) | ((u64)0x3F800000 << 32))

void func_00f58f98(void) {
    s32 i;
    s32 dir;
    s32 rx;
    s32 dx;
    s32 r;
    Pad *pad;
    s32 ry;
    s32 dy;
    u32 b;
    s32 unused[4];
    s32 prev;
    s32 flag;
    func_00f55190();
    D_00F9B540->x5E = D_00F9B540->x60;
    D_00FA5CE0 = 0;
    func_00f49430(1, D_00F9B540->x82, 0x801FA64C, 0x80077328);
    for (;;) {
        pad = func_001ba488(0);
        flag = 0;
        dir = func_00f4c510(pad);
        prev = D_00F9B540->x4C;
        if (dir != 0) {
            rx = D_00F9B540->x10D4;
            ry = D_00F9B540->x10D8;
            dx = 0;
            if (rx < 1024) {
                dx = (dir & 0x4000) ? 256 : 0;
            }
            if (rx >= -1023) {
                if (dir & 0x1000) {
                    dx = -256;
                }
            }
            dy = (dir & 0x8000) ? 1024 : 0;
            if (dir & 0x2000) {
                dy = -1024;
            }
            if (dx | dy) {
                for (i = 0; i < 15; i++) {
                    f32 a = (f32)dx * func_001befc8(i, D_00FA5D50);
                    f32 c = (f32)dy * func_001befc8(i, D_00FA5D78);
                    s32 y;
                    D_00F9B540->x10D4 = rx + (s32)(a / 22.5f);
                    y = ry + (s32)(c / 90.0f);
                    D_00F9B540->x10D8 = y;
                    if (y >= 2048) {
                        D_00F9B540->x10D8 = y - 4096;
                    }
                    if (D_00F9B540->x10D8 < -2048) {
                        D_00F9B540->x10D8 += 4096;
                    }
                    func_001bfac8();
                }
                D_00F9B540->x10D4 = rx + dx;
                D_00F9B540->x10D8 = ry + dy;
                if (ry + dy >= 2048) {
                    D_00F9B540->x10D8 = ry + dy - 4096;
                }
                if (D_00F9B540->x10D8 < -2048) {
                    D_00F9B540->x10D8 += 4096;
                }
            }
            goto tail;
        }
        if (D_00FA5CE0 == 0) {
            b = pad->x8;
            if (b & 0x4008) {
                if (func_00f47158() == 0) {
                    goto quit;
                }
                b = pad->x8;
            }
            if (b & 1) {
                func_00f47268(1, 0);
            } else if (b & 0x2800) {
                func_00f48aa8(1);
                return;
            } else if (b & 0x8000) {
                if (D_00F9B540->x94 > 0) {
                    func_00f49430(2, 164, 0x80077328, 0);
                    D_00FA5D48 = 0;
                    D_00F9B50C = 0;
                    D_00FA5CE0 = 1;
                    func_00f4e3f8(1);
                    func_00f58140();
                    flag = 1;
                }
            } else if (pad->x4 & 0x80) {
                func_00f57db0(1);
                func_00f49430(1, D_00F9B540->x82, 0x801FA64C, 0x80077328);
                flag = 1;
            } else if (pad->x4 & 0x20) {
                func_00f57db0(0);
                flag = 1;
                func_00f49430(1, D_00F9B540->x82, 0x801FA64C, 0x80077328);
            }
            func_00f59820(7, 0);
            goto tail;
        }
        b = pad->x8;
        if (b & 8) {
            if (func_00f47158() == 0) {
                goto quit;
            }
            b = pad->x8;
        }
        if (b & 1) {
            func_00f47268(1, 0);
        } else if (b & 0x2800) {
            func_00f58300();
            func_00f4e3f8(0);
            D_00F9B50C = 1;
            D_00FA5CE0 = 0;
            func_00f48aa8(1);
            return;
        } else if (b & 0x1000) {
            if (D_00F9B540->x94 >= 2) {
                func_00f49430(2, 165, 0x80077328, 0);
                r = func_00f625f0();
                if (r == 1) {
                    func_00f55190();
                    func_00f551e8();
                }
                if (r == 2 && func_00f47158() == 0) {
                    return;
                    func_00f504f8(0);
                    func_00f48aa8(3);
                quit:
                }
                func_00f49430(2, 164, 0x80077328, 0);
            }
        } else if (b & 0xC000) {
            flag = 1;
            func_00f58300();
            func_00f4e3f8(0);
            D_00F9B50C = flag;
            D_00FA5CE0 = 0;
            func_00f49430(1, D_00F9B540->x82, 0x801FA64C, 0x80077328);
        } else if (b & 0x80) {
            if (func_00f4cad0(D_00F9B540->x82)) {
                D_00FA5D48 = 0;
                func_00f58bd0(1);
                flag = 1;
            } else {
                func_0011d768(4);
            }
        } else if (b & 0x20) {
            if (func_00f4cad0(D_00F9B540->x82)) {
                D_00FA5D48 = 0;
                func_00f58bd0(0);
                flag = 1;
            } else {
                func_0011d768(4);
            }
        }
        for (i = 0; i < 8; i++) {
            s32 k = func_00f58128(D_0108CE88 + i);
            u8 rr = D_00379F28[k][0];
            u8 g = D_00379F28[k][1];
            u8 b2 = D_00379F28[k][2];
            D_0108CE90[i] = RGBAQ(rr / 2, g / 2, b2 / 2, 102);
        }
    tail:
        func_00f55298();
        if (flag == 0) {
            if (pad->x4 & 0x40) {
                func_00f57cf0(0);
                func_00f49430(1, D_00F9B540->x82, 0x801FA64C, 0x80077328);
            } else if (pad->x4 & 0x10) {
                func_00f57cf0(1);
                func_00f49430(1, D_00F9B540->x82, 0x801FA64C, 0x80077328);
            } else if (dir & 0x10) {
                func_00f57e78(1);
            } else if (dir & 0x40) {
                func_00f57e78(0);
            } else if (dir & 0x20) {
                func_00f57e78(2);
            } else if (dir & 0x80) {
                func_00f57e78(3);
            }
        }
        if (prev != D_00F9B540->x4C) {
            D_00F9B540->x60 = D_00F9B540->x5E;
            D_00F9B540->x4A = 0;
            D_00F9B540->y4A = 2;
            D_00F9B540->z4A = 4;
            D_00F9B540->x54 = func_001bb6d0(D_00F9B540->x4C - 1);
            func_00f4b338(D_00F9B544, 0);
        }
        func_001bfac8();
    }
}

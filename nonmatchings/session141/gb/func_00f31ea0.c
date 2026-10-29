/* gb.x func_00f31ea0 near miss: 464 words differ, score 176 (ours 2032 bytes, original 1992). Free-camera / map-view input loop: pad direction rotates the World x10D4/x10D8 angles over 15 eased frames (func_001befc8 on D_00F615D0 / D_00F615F8, / 22.5 and / 90, with +-4096 wrap); buttons drive func_00f20170 / func_00f219b0 / func_00f31208 / func_00f3b4f8 and the D_00F61560 sub-mode; palette refresh into D_00F806D0 (RGBAQ(r/2, g/2, b/2, 102), as in func_00f31208); then the func_00f30bf8 / func_00f30d80 shortcuts and the World x4C change handler. Logic is complete. An unused s32[4] local gives the 160-byte frame. Left: every D_00F56DC0 access comes out as lui/addiu + lw 0 (the outer for (;;) loop hoists &D_00F56DC0, and reload rematerializes it), where the original uses lw %lo directly; that is the 40-byte excess. A goto loop gets the size close (1984, 366 words) but GCSE then keeps &D_00F56DC0 and &D_00F61560 in s-registers (score 196). Modes nogcse/nosi/nofill/nostrict/norlo/faddr/fmam/nosib and nostrict_norcse do not help. */
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
extern World *D_00F56DC0;
extern void *D_00F56DC4;
extern s32 D_00F61560;
extern s32 D_00F56D8C;
extern s32 D_00F615C8;
extern u8 D_00F615D0[];
extern u8 D_00F615F8[];
extern s32 D_00F806C8;
extern u64 D_00F806D0[8];
extern u8 D_00379F28[][4];
void func_00f2e098(void);
void func_00f2e0f0(void);
void func_00f2e1a0(void);
void func_00f22338(s32, s32, s32, s32);
Pad *func_001ba488(s32);
s32 func_00f25418(Pad *);
f32 func_001befc8(s32, void *);
void func_001bfac8(void);
s32 func_00f20060(void);
void func_00f20170(s32, s32);
void func_00f219b0(s32);
void func_00f27300(s32);
void func_00f31048(void);
void func_00f30cb8(s32);
void func_00f32728(s32, s32);
void func_00f31208(void);
s32 func_00f3b4f8(void);
void func_00f29400(s32);
s32 func_00f259d8(s32);
void func_0011d768(s32);
void func_00f31ad8(s32);
s32 func_00f31030(s32);
void func_00f30bf8(s32);
void func_00f30d80(s32);
s32 func_001bb6d0(s32);
void func_00f24240(void *, s32);

#define RGBAQ(r, g, b, a) ((u64)(r) | ((u64)(g) << 8) | ((u64)(b) << 16) | ((u64)(a) << 24) | ((u64)0x3F800000 << 32))

void func_00f31ea0(void) {
    s32 unused[4];
    Pad *pad;
    s32 dir;
    s32 prev;
    s32 flag;
    s32 rx;
    s32 ry;
    s32 dx;
    s32 dy;
    s32 i;
    s32 r;
    u32 b;
    func_00f2e098();
    D_00F56DC0->x5E = D_00F56DC0->x60;
    D_00F61560 = 0;
    func_00f22338(1, D_00F56DC0->x82, 0x801FA64C, 0x80077328);
    for (;;) {
        flag = 0;
        pad = func_001ba488(0);
        dir = func_00f25418(pad);
        prev = D_00F56DC0->x4C;
        if (dir != 0) {
            rx = D_00F56DC0->x10D4;
            ry = D_00F56DC0->x10D8;
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
                    f32 a = (f32)dx * func_001befc8(i, D_00F615D0);
                    f32 c = (f32)dy * func_001befc8(i, D_00F615F8);
                    s32 y;
                    D_00F56DC0->x10D4 = rx + (s32)(a / 22.5f);
                    y = ry + (s32)(c / 90.0f);
                    D_00F56DC0->x10D8 = y;
                    if (y >= 2048) {
                        D_00F56DC0->x10D8 = y - 4096;
                    }
                    if (D_00F56DC0->x10D8 < -2048) {
                        D_00F56DC0->x10D8 += 4096;
                    }
                    func_001bfac8();
                }
                D_00F56DC0->x10D4 = rx + dx;
                D_00F56DC0->x10D8 = ry + dy;
                if (ry + dy >= 2048) {
                    D_00F56DC0->x10D8 = ry + dy - 4096;
                }
                if (D_00F56DC0->x10D8 < -2048) {
                    D_00F56DC0->x10D8 += 4096;
                }
            }
            goto tail;
        }
        if (D_00F61560 == 0) {
            b = pad->x8;
            if (b & 0x4008) {
                if (func_00f20060() == 0) {
                    goto quit;
                }
                b = pad->x8;
            }
            if (b & 1) {
                func_00f20170(1, 0);
            } else if (b & 0x2800) {
                func_00f219b0(1);
                return;
            } else if (b & 0x8000) {
                if (D_00F56DC0->x94 > 0) {
                    flag = 1;
                    func_00f22338(2, 164, 0x80077328, 0);
                    D_00F56D8C = 0;
                    D_00F615C8 = 0;
                    D_00F61560 = 1;
                    func_00f27300(1);
                    func_00f31048();
                }
            } else if (pad->x4 & 0x80) {
                flag = 1;
                func_00f30cb8(1);
                func_00f22338(1, D_00F56DC0->x82, 0x801FA64C, 0x80077328);
            } else if (pad->x4 & 0x20) {
                flag = 1;
                func_00f30cb8(0);
                func_00f22338(1, D_00F56DC0->x82, 0x801FA64C, 0x80077328);
            }
            func_00f32728(7, 0);
            goto tail;
        }
        b = pad->x8;
        if (b & 8) {
            if (func_00f20060() == 0) {
                goto quit;
            }
            b = pad->x8;
        }
        if (b & 1) {
            func_00f20170(1, 0);
        } else if (b & 0x2800) {
            func_00f31208();
            func_00f27300(0);
            D_00F56D8C = 1;
            D_00F61560 = 0;
            func_00f219b0(1);
            return;
        } else if (b & 0x1000) {
            if (D_00F56DC0->x94 >= 2) {
                func_00f22338(2, 165, 0x80077328, 0);
                r = func_00f3b4f8();
                if (r == 1) {
                    func_00f2e098();
                    func_00f2e0f0();
                }
                if (r == 2 && func_00f20060() == 0) {
                quit:
                    func_00f29400(0);
                    func_00f219b0(3);
                    return;
                }
                func_00f22338(2, 164, 0x80077328, 0);
            }
        } else if (b & 0xC000) {
            func_00f31208();
            flag = 1;
            func_00f27300(0);
            D_00F61560 = 0;
            D_00F56D8C = flag;
            func_00f22338(1, D_00F56DC0->x82, 0x801FA64C, 0x80077328);
        } else if (b & 0x80) {
            if (func_00f259d8(D_00F56DC0->x82)) {
                D_00F615C8 = 0;
                func_00f31ad8(1);
                flag = 1;
            } else {
                func_0011d768(4);
            }
        } else if (b & 0x20) {
            if (func_00f259d8(D_00F56DC0->x82)) {
                D_00F615C8 = 0;
                func_00f31ad8(0);
                flag = 1;
            } else {
                func_0011d768(4);
            }
        }
        for (i = 0; i < 8; i++) {
            s32 k = func_00f31030(D_00F806C8 + i);
            u8 b2 = D_00379F28[k][2];
            u8 g = D_00379F28[k][1];
            u8 rr = D_00379F28[k][0];
            D_00F806D0[i] = RGBAQ(rr / 2, g / 2, b2 / 2, 102);
        }
    tail:
        func_00f2e1a0();
        if (flag == 0) {
            if (pad->x4 & 0x40) {
                func_00f30bf8(0);
                func_00f22338(1, D_00F56DC0->x82, 0x801FA64C, 0x80077328);
            } else if (pad->x4 & 0x10) {
                func_00f30bf8(1);
                func_00f22338(1, D_00F56DC0->x82, 0x801FA64C, 0x80077328);
            } else if (dir & 0x10) {
                func_00f30d80(1);
            } else if (dir & 0x40) {
                func_00f30d80(0);
            } else if (dir & 0x20) {
                func_00f30d80(2);
            } else if (dir & 0x80) {
                func_00f30d80(3);
            }
        }
        if (prev != D_00F56DC0->x4C) {
            D_00F56DC0->x60 = D_00F56DC0->x5E;
            D_00F56DC0->x4A = 0;
            D_00F56DC0->y4A = 2;
            D_00F56DC0->z4A = 4;
            D_00F56DC0->x54 = func_001bb6d0(D_00F56DC0->x4C - 1);
            func_00f24240(D_00F56DC4, 0);
        }
        func_001bfac8();
    }
}

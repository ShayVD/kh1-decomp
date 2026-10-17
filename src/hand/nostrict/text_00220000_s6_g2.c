#include "common.h"

typedef struct { u8 pad0[0x2D]; u8 a, b; u8 pad[0x11]; } SvE;
typedef struct { s32 x0, x4; u8 pad[0x30]; s32 x38; } SvF;
typedef struct { SvE e[66]; SvE *tbl[528]; SvE *ptr[99]; s32 idx; SvF f[99]; } SvD;
typedef struct { s32 pad[4]; s32 x10; } SvCtx;
typedef struct { u8 pad[0xD0]; s16 xD0, xD2; } SvWin;

extern SvD D_00351E10;
extern SvF D_00425B80;
extern s32 D_006436D4;
extern s32 D_006436D8[2];
extern s32 D_006436E0[2];
extern s32 D_006436E8;
extern s32 D_006436EC;
extern s32 D_006436F0;
extern s32 D_006436F8[2];
extern s32 D_00643700[2];
extern s32 D_00643710;
extern s32 D_00643714;
extern s32 D_00643734;
extern s32 D_00643738;
extern s32 D_0064373C;
extern s32 D_00643744;
extern s32 D_00643748;
extern u32 D_0064374C;
extern u32 D_00643750;
extern s32 D_00643754;
extern s32 D_00643758;
extern s32 D_003E8E08;
extern s32 D_003F34C8;
extern s32 D_003F34D4;
extern void *D_003F34D8;
extern s32 D_00425C18;
extern u32 D_00425C1C;
extern s32 D_00425C20;
extern s32 D_00425CAC;
extern u8 D_004910B8[];
extern u8 D_004910C8[];
extern u8 D_003F6B00[];
extern u8 D_003F6B40[];
extern u8 D_003F7ED0[];
extern u8 D_003F8380[];

void func_0011d768(s32);
void func_00120748(void *, void *, void *, s32);
SvWin *func_001f31a8(void *, s32);
void func_001f36b8(s32);
void func_001f3dc0(SvWin *);
void func_001f3e48(SvWin *, void *);
s32 func_001f42b8(void *);
s32 func_001f9438(void *, s32, s32, s32, s32, s32, u32);
void func_002066b0(void *, s32, s32, s32, u32, u32);
void func_0020bda8(s32);
void func_00223980(s32, s32, s32);
void func_00225988(void);
void func_002259c8(void *);
void func_00225b60(void *);
void func_00225c30(void *);
void func_00225d08(void *);
void func_00232e08(s32);
void *func_00232f88(s32);
void *func_00232fc8(s32);
void *func_00233018(s32);
void *func_00233058(s32);
void *func_00233098(s32);
s32 func_00233d08(s32);
void func_00233ef8(s32);
s32 func_00233f40(s32, s32);
void func_00233f68(s32, s32);
void func_00233ff8(s32, s32);
s32 func_00234018(s32, s32, s32);
s32 func_00234148(s32, s32, void *, void *, s32, s32);
s32 func_00234210(s32, s32, s32);
s32 func_002343a8(s32, s32, void *, s32);
s32 func_00234440(s32, s32, void *, void *, s32, s32);
s32 func_00234508(s32, s32, void *, s32);
s32 func_002345a0(s32, s32, void *, void *, s32, s32);
s32 func_00234668(s32, s32, void *, void *, s32, s32);
s32 func_00234860(void);
s32 func_00234870(void);
s32 func_002348a0(void);
s32 func_002348b0(void);
s32 func_002348c0(void);
s32 func_002348d0(void);
s32 func_002348e0(void);

#define SV_S D_00351E10
#define SV_PORT D_006436D4
#define SV_SLOT1 (D_006436E8 + 1)

/* request: msg, start op, next state */
#define SV_WAITCLOSE(m) \
    D_00643738 = m; \
    if (func_00233d08(0) == 0) { \
        func_00233f68(SV_PORT, 0); \
        func_00233ff8(SV_PORT, 0); \
        func_002259c8(arg0); \
    } \
    break;

#define SV_CLOSE(m, nx) \
    D_00643738 = m; \
    func_00234018(SV_PORT, 0, 0); \
    D_00643734 = nx; \
    break;

#define SV_CHECK(m, fn, okv, ok, bad) \
    D_00643738 = m; \
    if (func_00233d08(0) == 0) { \
        if (fn() != 0) { \
            D_00643738 = 374; \
            if (fn() == okv) { \
                D_00643734 = ok; \
            } else { \
                func_00225b60(arg0); \
            } \
        } else { \
            D_00643734 = bad; \
        } \
    } \
    break;

#define SV_CHECK5(m, ok, bad) \
    D_00643738 = m; \
    if (func_00233d08(0) == 0) { \
        if (func_002348c0() == 5) { \
            D_00643738 = 382; \
            D_00643734 = ok; \
        } else { \
            D_00643734 = bad; \
        } \
    } \
    break;

/* rodata */
void func_00225ea8(SvCtx *arg0) {
    s32 slot;
    s32 i;
    s32 n;
    s32 w;
    SvWin *win[2];
    SvE *e;

    slot = -1;
    if (func_001f42b8(arg0) != 0) {
        switch (D_00643734) {
        case 0:
            if (func_00233f40(SV_PORT, 0) != 0) {
                func_00233ff8(SV_PORT, 0);
                func_00223980(SV_PORT, 0, 0);
                D_00643758 = 0;
            }
            D_00643738 = 372;
            func_00234018(SV_PORT, 0, 0);
            D_0064373C = 0;
            D_00643754 = 0;
            D_00643734 = 1;
            break;
        case 1:
            D_00643738 = 372;
            if (func_00233d08(0) == 0) {
                D_00643710 = D_00425C18;
                D_00643714 = D_00425C20;
                D_00643734 = 2;
            }
            break;
        case 2:
            SV_CLOSE(372, 3)
        case 3:
            D_00643738 = 372;
            if (func_00233d08(0) == 0) {
                if (func_00233f40(SV_PORT, 0) == 0) {
                    if (D_00643710 == 2 && D_00425C18 == D_00643710 && D_00643714 == 0 && D_00425C20 == 0) {
                        D_00643734 = 4;
                    } else {
                    c3:
                        if (D_00643758 == 0) {
                            D_00643734 = 12;
                        } else {
                            D_00643734 = 24;
                        }
                    }
                } else {
                    func_00233ff8(SV_PORT, 0);
                    D_00643738 = 380;
                    func_002259c8(arg0);
                }
            }
            break;
        case 4:
            SV_CLOSE(372, 5)
        case 5:
            D_00643738 = 372;
            if (func_00233d08(0) == 0) {
                if (func_00233f40(SV_PORT, 0) == 0) {
                    if (D_00425C20 == 0) {
                        D_00643738 = 375;
                        func_00225c30(arg0);
                    } else {
                        goto c3;
                    }
                } else {
                    func_00233ff8(SV_PORT, 0);
                    D_00643738 = 380;
                    func_002259c8(arg0);
                }
            }
            break;
        case 6:
            SV_CLOSE(375, 7)
        case 7:
            D_00643738 = 375;
            if (func_00233d08(0) == 0) {
                if (func_00233f40(SV_PORT, 0) != 0) {
                    func_00233ff8(SV_PORT, 0);
                    D_00643738 = 381;
                    func_002259c8(arg0);
                } else {
                    D_00643734 = 8;
                }
            }
            break;
        case 8:
            D_00643738 = 376;
            func_00234210(SV_PORT, 0, 0);
            D_00643734 = 9;
            break;
        case 9:
            D_00643738 = 376;
            if (func_00233d08(0) == 0) {
                if (func_00234870() == 0) {
                    D_00643734 = 12;
                    D_00643754 = 1;
                    D_006436D8[SV_PORT] = 0;
                    D_006436E0[SV_PORT] = 0;
                    D_006436E8 = 0;
                } else {
                    D_00643738 = 381;
                    D_00643734 = 10;
                }
            }
            break;
        case 10:
            SV_CLOSE(381, 11)
        case 11:
            D_00643738 = 381;
            if (func_00233d08(0) == 0) {
                if (func_00233f40(SV_PORT, 0) != 0) {
                    func_00233ff8(SV_PORT, 0);
                    func_002259c8(arg0);
                } else {
                    func_00225d08(arg0);
                }
            }
            break;
        case 12:
            D_00643738 = 372;
            func_00234148(SV_PORT, 0, D_004910B8, &SV_S, 99, 0);
            D_00643734 = 13;
            break;
        case 13:
            D_00643738 = 372;
            if (func_00233d08(0) == 0) {
                if (func_00234860() == 4) {
                    D_00643738 = 380;
                    D_00643734 = 14;
                } else {
                    D_00643734 = 16;
                }
            }
            break;
        case 14:
            SV_CLOSE(380, 15)
        case 15:
            SV_WAITCLOSE(380)
        case 16:
            D_00643738 = 372;
            for (i = 98; i >= 0; i--) {
                SV_S.ptr[i] = 0;
            }
            {
                s32 cnt = D_00425CAC;
                D_00643744 = cnt;
                e = SV_S.e;
                for (i = 0; i < cnt; i++, e++) {
                    SV_S.tbl[e->a * 10 + e->b - 1] = e;
                }
            }
            D_00643734 = 17;
            break;
        case 17:
            D_00643738 = 372;
            SV_S.idx = 0;
            D_00643734 = 18;
            break;
        case 18:
            D_00643738 = 373;
            while (SV_S.ptr[SV_S.idx] == 0) {
                if (++SV_S.idx >= 99) {
                    goto nf;
                }
            }
            slot = SV_S.idx + 1;
            SV_S.f[SV_S.idx].x0 = 0;
            func_002345a0(SV_PORT, 0, func_00233018(SV_S.idx + 1), &SV_S.f[SV_S.idx], 60, 0);
            D_00643734 = 19;
            break;
        case 19:
            D_00643738 = 373;
            slot = SV_S.idx + 1;
            if (func_00233d08(0) == 0) {
                if (func_002348d0() == 7) {
                    D_00643738 = 380;
                    slot = -1;
                    D_00643734 = 20;
                } else if (++SV_S.idx >= 99) {
                    D_00643734 = 22;
                } else {
                    D_00643734 = 18;
                }
            }
            break;
        case 20:
            SV_CLOSE(380, 21)
        case 21:
            SV_WAITCLOSE(380)
        case 22:
            SV_CLOSE(372, 23)
        case 23:
            D_00643738 = 372;
            if (func_00233d08(0) == 0) {
                if (func_00233f40(SV_PORT, 0) == 0) {
                    D_00643734 = 24;
                } else {
                    func_00233ff8(SV_PORT, 0);
                    D_00643738 = 380;
                    func_002259c8(arg0);
                }
            }
            break;
        case 24:
            D_00643738 = 0;
            D_00643748 = 0;
            for (i = 0; i < 99; i++) {
                if (SV_S.ptr[i] != 0 && SV_S.f[i].x0 == 0x5153484B && SV_S.f[i].x4 == 0x01317F14) {
                    if ((u32)SV_S.f[i].x38 >= 3) {
                        SV_S.f[i].x38 = 2;
                    }
                    D_00643748++;
                }
            }
            D_0064374C = D_00425C1C;
            D_00643750 = D_00425C1C / 132;
            if (D_00643754 != 0) {
                D_00643738 = 372;
                D_00643734 = 26;
                D_00643754 = 0;
            } else {
                D_0064373C = 1;
                D_00643758 = 1;
                D_006436EC = SV_PORT;
                D_00643734 = 25;
                func_00233ef8(0);
                func_0011d768(55);
                func_001f36b8(arg0->x10);
                win[0] = func_001f31a8(D_003F6B40, 6);
                if (win[0] != 0) {
                    func_001f3e48(win[0], arg0);
                    func_0020bda8(16);
                    D_006436D8[SV_PORT] = D_006436F8[SV_PORT];
                    D_006436E0[SV_PORT] = D_00643700[SV_PORT];
                    {
                        s32 sum;
                        u16 x, y;
                        x = *(u16 *)&D_006436E0[SV_PORT];
                        y = *(u16 *)&D_006436D8[SV_PORT];
                        sum = D_006436D8[SV_PORT] + D_006436E0[SV_PORT];
                        {
                            SvWin *w0 = win[0];
                            w0->xD2 = x * 16;
                            w0->xD0 = y * 16;
                        }
                        D_006436E8 = sum;
                    }
                    win[1] = func_001f31a8(D_003F6B00, 6);
                    if (win[1] != 0) {
                        func_001f3e48(win[1], win[0]);
                        func_001f3dc0(win[0]);
                    }
                }
            }
            break;
        case 26:
            D_00643738 = 372;
            switch (D_003F34D4) {
            case 0:
                D_003F34D4 = 1;
                D_00643734 = 27;
                D_003F34C8++;
                func_00120748(D_004910C8, D_003F34D8, func_00225988, 0);
                break;
            case 1:
                D_00643734 = 27;
                break;
            default:
                D_00643734 = 28;
                break;
            }
            break;
        case 27:
            D_00643738 = 383;
            break;
        case 28:
            D_00643738 = 377;
            func_002343a8(SV_PORT, 0, func_00232f88(SV_SLOT1), 0);
            D_00643734 = 29;
            break;
        case 29:
            SV_CHECK(377, func_002348a0, 4, 30, 32)
        case 30:
            SV_CLOSE(374, 31)
        case 31:
            SV_WAITCLOSE(374)
        case 32:
            D_00643738 = 377;
            func_00232e08(SV_SLOT1);
            func_00234440(SV_PORT, 0, func_00233058(SV_SLOT1), D_003F7ED0, 964, 0);
            D_00643734 = 33;
            break;
        case 33:
            SV_CHECK(377, func_002348b0, 7, 34, 36)
        case 34:
            SV_CLOSE(374, 35)
        case 35:
            SV_WAITCLOSE(374)
        case 36:
            D_00643738 = 377;
            func_00234440(SV_PORT, 0, func_00233098(SV_SLOT1), D_003F34D8, 0x8A58, 0);
            D_00643734 = 37;
            break;
        case 37:
            SV_CHECK(377, func_002348b0, 7, 38, 40)
        case 38:
            SV_CLOSE(374, 39)
        case 39:
            SV_WAITCLOSE(374)
        case 40:
            D_00643738 = 377;
            func_00234440(SV_PORT, 0, func_00232fc8(SV_SLOT1), D_003F8380, 0x16C00, 0);
            D_00643734 = 41;
            break;
        case 41:
            SV_CHECK(377, func_002348b0, 7, 42, 44)
        case 42:
            SV_CLOSE(374, 43)
        case 43:
            SV_WAITCLOSE(374)
        case 44:
            D_00643738 = 377;
            func_00234440(SV_PORT, 0, func_00233018(SV_SLOT1), &D_00425B80, 0x400, 0);
            D_00643734 = 45;
            break;
        case 45:
            SV_CHECK(377, func_002348b0, 7, 46, 48)
        case 46:
            SV_CLOSE(374, 47)
        case 47:
            SV_WAITCLOSE(374)
        case 48:
            D_00643738 = 372;
            func_00234148(SV_PORT, 0, func_00232f88(SV_SLOT1), &SV_S.e[D_00643744], 99, 0);
            D_00643734 = 49;
            break;
        case 49:
            SV_CHECK(372, func_00234860, 4, 50, 52)
        case 50:
            SV_CLOSE(374, 51)
        case 51:
            SV_WAITCLOSE(374)
        case 52:
            D_00643738 = 372;
            SV_S.ptr[D_006436E8] = &SV_S.e[D_00643744];
            D_00643744++;
            D_00643734 = 53;
            SV_S.f[D_006436E8] = D_00425B80;
            break;
        case 53:
            SV_CLOSE(372, 54)
        case 54:
            D_00643738 = 372;
            if (func_00233d08(0) == 0) {
                if (func_00233f40(SV_PORT, 0) == 0) {
                    D_00643754 = 0;
                    D_00643734 = 24;
                    D_006436F0 = SV_PORT;
                    D_006436F8[SV_PORT] = D_006436D8[SV_PORT];
                    D_00643700[SV_PORT] = D_006436E0[SV_PORT];
                } else {
                    func_00233ff8(SV_PORT, 0);
                    D_00643738 = 380;
                    func_002259c8(arg0);
                }
            }
            break;
        case 55:
            D_00643738 = 378;
            func_00234508(SV_PORT, 0, func_00233018(SV_SLOT1), 0);
            D_00643734 = 56;
            break;
        case 56:
            SV_CHECK(378, func_002348c0, 5, 57, 59)
        case 57:
            SV_CLOSE(374, 58)
        case 58:
            SV_WAITCLOSE(374)
        case 59:
            D_00643738 = 378;
            func_00232e08(SV_SLOT1);
            func_00234668(SV_PORT, 0, func_00233058(SV_SLOT1), D_003F7ED0, 964, 0);
            D_00643734 = 60;
            break;
        case 60:
            SV_CHECK(378, func_002348e0, 7, 61, 63)
        case 61:
            SV_CLOSE(374, 62)
        case 62:
            SV_WAITCLOSE(374)
        case 63:
            D_00643738 = 378;
            func_00234668(SV_PORT, 0, func_00232fc8(SV_SLOT1), D_003F8380, 0x16C00, 0);
            D_00643734 = 64;
            break;
        case 64:
            SV_CHECK(378, func_002348e0, 7, 65, 67)
        case 65:
            SV_CLOSE(374, 66)
        case 66:
            SV_WAITCLOSE(374)
        case 67:
            D_00643738 = 378;
            func_00234440(SV_PORT, 0, func_00233018(SV_SLOT1), &D_00425B80, 0x400, 0);
            D_00643734 = 68;
            break;
        case 68:
            D_00643738 = 378;
            if (func_00233d08(0) == 0) {
                if (func_002348b0() != 0) {
                    D_00643738 = 374;
                    if (func_002348b0() == 7) {
                        D_00643734 = 69;
                    } else {
                        func_00225b60(arg0);
                    }
                } else {
                    D_00643734 = 53;
                    SV_S.f[D_006436E8] = D_00425B80;
                }
            }
            break;
        case 69:
            SV_CLOSE(374, 70)
        case 70:
            SV_WAITCLOSE(374)
        case 71:
            D_00643738 = 379;
            func_00234508(SV_PORT, 0, func_00233018(SV_SLOT1), 0);
            D_00643734 = 72;
            break;
        case 72:
            SV_CHECK5(379, 73, 75)
        case 73:
            SV_CLOSE(382, 74)
        case 74:
            SV_WAITCLOSE(382)
        case 75:
            D_00643738 = 379;
            func_00234508(SV_PORT, 0, func_00232fc8(SV_SLOT1), 0);
            D_00643734 = 76;
            break;
        case 76:
            SV_CHECK5(379, 77, 79)
        case 77:
            SV_CLOSE(382, 78)
        case 78:
            SV_WAITCLOSE(382)
        case 79:
            D_00643738 = 379;
            func_00234508(SV_PORT, 0, func_00233098(SV_SLOT1), 0);
            D_00643734 = 80;
            break;
        case 80:
            SV_CHECK5(379, 81, 83)
        case 81:
            SV_CLOSE(382, 82)
        case 82:
            SV_WAITCLOSE(382)
        case 83:
            D_00643738 = 379;
            func_00234508(SV_PORT, 0, func_00233058(SV_SLOT1), 0);
            D_00643734 = 84;
            break;
        case 84:
            SV_CHECK5(379, 85, 87)
        case 85:
            SV_CLOSE(382, 86)
        case 86:
            SV_WAITCLOSE(382)
        case 87:
            D_00643738 = 379;
            func_00234508(SV_PORT, 0, func_00232f88(SV_SLOT1), 0);
            D_00643734 = 88;
            break;
        case 88:
            SV_CHECK5(379, 89, 91)
        case 89:
            SV_CLOSE(382, 90)
        case 90:
            SV_WAITCLOSE(382)
        case 91:
            D_00643744--;
            D_00643738 = 372;
            D_00643734 = 92;
            SV_S.ptr[D_006436E8] = 0;
            break;
        case 92:
            SV_CLOSE(372, 93)
        case 93:
            D_00643738 = 372;
            if (func_00233d08(0) == 0) {
                if (func_00233f40(SV_PORT, 0) != 0) {
                    func_00233ff8(SV_PORT, 0);
                    D_00643738 = 380;
                    func_002259c8(arg0);
                } else {
                    D_00643754 = 1;
                    D_00643734 = 24;
                }
            }
            break;
        }
        goto end;
    nf:
        D_00643734 = 22;
        D_00643738 = 372;
    }
end:
    if (D_00643738 != 0) {
        if (slot != -1) {
            D_003E8E08 = slot;
        }
        {
            s32 y = SV_PORT * 28 + 83;
            w = func_001f9438(arg0, 0, 200, y - 7, D_00643738, 15, 0x80399BFF);
            func_002066b0(arg0, 0, y, 11, 0x1428C8, 0x801428C8);
            func_002066b0(arg0, 133, y, 63, 0x801428C8, 0x801428C8);
            func_002066b0(arg0, w + 4, y, 512 - w, 0x801428C8, 0x1428C8);
        }
    }
}

#undef SV_S
#undef SV_PORT
#undef SV_SLOT1
#undef SV_WAITCLOSE
#undef SV_CLOSE
#undef SV_CHECK
#undef SV_CHECK5

/* score 139 (same 1232 size; w[8] gives the 224 frame, so the window array or another local is bigger than w[2]). Two option windows, a box and a title via func_00f6b6a0, then a nested pad loop (0x2000 enters selection, 0x4000 leaves) with a 10-entry jump-table switch on Itm.b0. Left: 256 is li-loaded fresh (s2) for the 2nd/3rd calls while the first loop keeps it in s6; k/ps/y registers are rotated (target s3/s1/s2). */
typedef struct { s32 x0, x4; u32 x8; u32 xC; u32 x10; } Pad;
typedef struct { u8 pad[4]; u8 b4; u8 pad5[2]; u8 b7; } Win;
typedef struct { u8 pad[16]; s32 x10; } Hdl;
typedef struct { u8 b0; u8 pad[3]; s32 x4; } Itm;
extern Pad D_002C5AD0;
extern s32 D_00FB4A70;
extern s32 D_00FB4B18;
extern u8 D_00FB4B1C;
extern s32 D_00FB4B20;
extern s32 D_00FB4B38;
extern s32 D_00FB4B3C;
extern s32 D_00FB4B6C;
extern s32 D_00FB4B70;
extern s32 D_00FB4CB8, D_00FB4CBC, D_00FB4CC0, D_00FB4CC4;
extern s16 D_00FB5A20[];
extern s32 D_0108F18C;
extern s32 D_0108F52C;
void func_0011d768(s32);
Itm *func_001bc4f0(void);
s32 func_001bc520(void);
void func_001bdb58(void);
void func_001f3dc0(s32);
void func_0024e468(s32);
void func_00f6ade8(s32);
void func_00f6b5d0(s32, s32, s32);
void *func_00f6b6a0(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
void func_00f74978(Win *, s32);

void func_00f72a70(s32 arg0, Hdl *h)
{
    Win *w[8];
    Win **pw;
    s16 *ps;
    s32 t, y, k, sel, n;
    u32 a, b;
    Itm *e;

    k = 1;
    pw = w;
    t = D_00FB4A70;
    h->x10 = 109;
    y = D_00FB4B3C;
    ps = D_00FB5A20;
    do {
        *pw = func_00f6b6a0(14, 0, 2, 1, 2, 15, *ps++, 1, D_00FB4B18, y, 0, D_00FB4B20, 0, 0, 0, 0, 0, 256, t);
        (*pw)->b7 = D_00FB4B1C;
        (*pw++)->b4 = 0;
        y += D_00FB4B6C;
    } while (--k >= 0);
    func_00f6b6a0(14, 3, 0, 2, 0, 0, 0, 0, 0, D_00FB4B3C + 12, 0, D_00FB4B38, 2, D_00FB4CB8, D_00FB4CBC, D_00FB4CC0, D_00FB4CC4, 256, t);
    func_00f6b6a0(14, 0, 2, 1, 0, 15, 86, 7, D_00FB4B38, D_00FB4B3C, 0, D_00FB4B70, 0, 0, 0, 0, 0, 256, t);
    for (;;) {
        a = D_002C5AD0.x8;
        if (a & 0x4000) break;
        if (a & 0x2000) {
            func_0011d768(2);
            D_0108F52C = 0;
            sel = 1;
            func_001f3dc0(D_0108F18C);
            func_0024e468(1);
            for (;;) {
                a = D_002C5AD0.x8 | D_002C5AD0.x8 >> 24;
                b = D_002C5AD0.x10 | D_002C5AD0.x10 >> 24;
                if (a & 0x4000) {
                    func_0011d768(3);
                    break;
                }
                if (a & 0x2000) {
                    func_0011d768(2);
                    if (sel == 0) {
                        n = func_001bc520();
                        for (k = 0; k < n; k++) {
                            e = func_001bc4f0() + k;
                            switch (e->b0) {
                            case 0:
                                e->x4 = 0x4000;
                                break;
                            case 1:
                                e->x4 = 0x8000;
                                break;
                            case 2:
                                e->x4 = 0x400;
                                break;
                            case 3:
                            case 4:
                            case 5:
                                e->x4 = 0x2000;
                                break;
                            case 6:
                            case 7:
                            case 8:
                                e->x4 = 0x1000;
                                break;
                            case 9:
                            default:
                                e->x4 = 0;
                                break;
                            }
                        }
                    }
                    func_001bdb58();
                    break;
                }
                if (b & 0x10) {
                    sel--;
                    if (sel < 0) {
                        if (a & 0x10) {
                            sel = 1;
                            func_0011d768(1);
                        } else {
                            sel = 0;
                        }
                    } else {
                        func_0011d768(1);
                    }
                    a = 0;
                    b = 0;
                }
                if (b & 0x40) {
                    sel++;
                    if (sel >= 2) {
                        if (a & 0x40) {
                            sel = 0;
                            func_0011d768(1);
                        } else {
                            sel = 1;
                        }
                    } else {
                        func_0011d768(1);
                    }
                }
                for (k = 0; k < 2; k++) {
                    if (sel == k)
                        w[k]->b4 = 1;
                    else
                        w[k]->b4 = 0;
                }
                func_00f74978(w[sel], 8);
                func_0024e468(1);
            }
            pw = w;
            for (k = 1; k >= 0; k--)
                (*pw++)->b4 = 0;
            D_0108F52C = 2;
            func_001f3dc0(arg0);
        }
        func_0024e468(1);
    }
    func_0011d768(3);
    func_00f6b5d0(14, 0, D_00FB4A70);
    func_0024e468(D_00FB4A70);
    func_00f6ade8(14);
}

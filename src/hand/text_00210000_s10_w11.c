#include "common.h"
#include "data/bss_0064.h"

/* rodata: jump tables at 0x00490e30. Matched from session-9 r2_7 draft + a dead `n = D_003E3D68;` in the case-4 arm (gives gcse a partially available hi(D_003E3D68), so PRE puts lui s5 in both arms). */
typedef struct Ob Ob;
struct Ob {
    u8 pad0[0x24];
    Ob *x24, *x28;
    Ob *x2c;
    u8 pad30[0x70 - 0x30];
    s32 x70;
    u8 pad74[0x88 - 0x74];
    s32 x88;
    u8 pad8c[0xb4 - 0x8c];
    s32 xb4;
    s16 xb8;
    s16 xba;
    u8 padbc[0xc2 - 0xbc];
    s16 xc2;
    u8 padc4[0xc6 - 0xc4];
    s16 xc6;
    u8 padc8[0xcc - 0xc8];
    s16 xcc, xce, xd0, xd2;
    u8 padd4[0xd8 - 0xd4];
    s16 xd8, xda;
};
typedef struct { s32 x0, x4; } B50;
typedef struct { u8 pad[0x40]; u8 items[0x30]; } Sub;
typedef struct { u8 pad[4]; Sub sub; } Rec74;
typedef struct { Rec74 r[10]; u8 pad[6]; u8 x48e[0x10b]; u8 x599[1]; } S4BE8;
extern S4BE8 *D_00304BE8;
extern u32 D_003E3D68;
extern u8 D_003F3980[], D_003F39C0[], D_003F39F0[], D_003F3A20[], D_003F3A50[], D_003F3A80[];
extern s32 D_00641224;
extern s32 D_00641228;
extern s32 D_0064122C;
extern s32 D_00641234;
extern s32 D_00641238;
extern s32 D_0064123C;
extern s32 D_00641240;
extern s32 D_00641248;
extern B50 D_00641250;
extern u16 D_00641258; /* src/data/bss_0064.c: s32 D_00641258 */
extern u16 D_0064125C; /* src/data/bss_0064.c: s32 D_0064125C */
extern u16 D_00641260; /* src/data/bss_0064.c: s32 D_00641260 */
extern u16 D_00641264; /* src/data/bss_0064.c: s32 D_00641264 */
extern u16 D_00641268; /* src/data/bss_0064.c: s32 D_00641268 */
extern u16 D_0064126C; /* src/data/bss_0064.c: s32 D_0064126C */
extern u16 D_00641270; /* src/data/bss_0064.c: s32 D_00641270 */
extern u16 D_00641274; /* src/data/bss_0064.c: s32 D_00641274 */
extern s32 D_00641388;
s32 func_001f42b8(Ob *);
Ob *func_001f31a8(void *, s32);
void func_001f3e48(Ob *, Ob *);
void func_001f3dc0(Ob *);
s32 func_001ebea8(void);
void func_001f40a0(Ob *, s32);
s32 func_001fd518(Ob *);
void func_0020eb98(void);
void func_0020f3c8(void);
void func_0020fbe0(void);
void func_00206690(Ob *, s32, s32, s32);
void func_00207870(Ob *, s32, s32, s32, s32, s32, s32);
void func_00207830(Ob *, s32, s32, s32, s32, s32, s32);
void func_0020dd38(Ob *, s32, s32, s32, s32, s32);
s32 func_001ee5f0(s32);
s32 func_001efbb8(s32);

/* rodata */
void func_002106b8(Ob *o) {
    Ob *w[3];
    s32 n;
    u32 sel;
    s32 shift;
    s32 *pc;
    s32 v;
    if (func_001f42b8(o)) {
        switch (D_00641224) {
        case 0:
        case 3:
            w[0] = func_001f31a8(D_003F3A80, 6);
            if (w[0] == 0) break;
            func_001f3e48(w[0], o);
            if (D_00641224 == 0) {
                shift = 0;
                n = D_003E3D68 + 1;
                n += func_001ebea8();
                sel = D_00641250.x0;
            } else {
                w[0]->xb4 += 448;
                shift = 1;
                if (D_00641228 == -1) n = D_003E3D68;
                else n = D_003E3D68 + 1;
                switch (D_00641238) {
                case 0:
                    if (D_00641228 == -1) D_00641250.x4 = 0;
                    else D_00641250.x4 = D_00641250.x0;
                    n = D_003E3D68;
                    break;
                case 1:
                    D_00641250.x4 = 0;
                    break;
                case 2:
                    D_00641250.x4 = D_003E3D68;
                    break;
                }
                sel = D_00641250.x4;
            }
            w[0]->xd2 = sel * 16;
            w[0]->xcc = n;
            w[0]->xba = n * 448 - 32;
            w[0]->xce = n;
            w[1] = func_001f31a8(D_003F3A50, 6);
            if (w[1] == 0) break;
            func_001f3e48(w[1], w[0]);
            w[1]->x24 = 0;
            if (D_00641224 != 3 || D_00641238 != 0) {
                w[2] = func_001f31a8(D_003F3A20, 6);
                if (w[2] != 0) {
                    func_001f3e48(w[2], w[1]);
                    if (sel < D_003E3D68) {
                        w[2]->xd0 = D_00641258 * 16;
                        w[2]->xd2 = D_0064125C * 16;
                        w[2]->xb8 = 0xa60;
                        w[2]->xd8 = 1;
                        w[2]->xc2 = 0xa60;
                        w[2]->x88 &= ~1;
                    } else if (sel == D_003E3D68) {
                        w[2]->xd0 = D_00641260 * 16;
                        w[2]->xd2 = D_00641264 * 16;
                        w[2]->xda = D_00641268 * 16;
                        w[2]->xd8 = 2;
                        w[2]->xb8 = 0x14c0;
                        w[2]->xc2 = 0xa60;
                        w[2]->x88 |= 1;
                        w[2]->x70 = 4;
                        w[2]->xc6 = 0;
                    } else {
                        w[2]->xd0 = D_0064126C * 16;
                        w[2]->xd2 = D_00641270 * 16;
                        w[2]->xb8 = 0xa60;
                        w[2]->xd8 = 1;
                        w[2]->xc2 = 0xa60;
                        w[2]->x88 &= ~1;
                    }
                    if (shift) {
                        w[2]->xb4 += 448;
                        w[2]->xba -= 448;
                    }
                    func_001f40a0(w[2], 0x40000000);
                    w[2]->x24 = (Ob *)sel;
                    w[2]->x2c = (Ob *)D_00641224;
                }
            }
            func_001f3dc0(w[0]);
            break;
        case 1:
        case 4:
        c1:
            w[0] = func_001f31a8(D_003F3A20, 6);
            if (w[0] == 0) break;
            func_001f3e48(w[0], o);
            if (D_00641224 == 1) {
                shift = 0;
                sel = D_00641250.x0;
            } else {
                sel = D_00641250.x4;
                n = D_003E3D68;
                shift = 1;
            }
            if (sel < D_003E3D68) {
                w[0]->xd0 = D_00641258 * 16;
                w[0]->xd2 = D_0064125C * 16;
                w[0]->xb8 = 0xa60;
                w[0]->xd8 = 1;
                w[0]->xc2 = 0xa60;
                w[0]->x88 &= ~1;
            } else if (sel == D_003E3D68) {
                w[0]->xd0 = D_00641260 * 16;
                w[0]->xd2 = D_00641264 * 16;
                w[0]->xda = D_00641268 * 16;
                w[0]->xd8 = 2;
                w[0]->xb8 = 0x14c0;
                w[0]->xc2 = 0xa60;
                w[0]->x88 |= 1;
                w[0]->x70 = 4;
                w[0]->xc6 = 0;
            } else {
                w[0]->xd0 = D_0064126C * 16;
                w[0]->xd2 = D_00641270 * 16;
                w[0]->xb8 = 0xa60;
                w[0]->xd8 = 1;
                w[0]->xc2 = 0xa60;
                w[0]->x88 &= ~1;
            }
            if (shift) {
                w[0]->xb4 += 448;
                w[0]->xba -= 448;
            }
            func_001f40a0(w[0], 0x40000000);
            w[0]->x24 = (Ob *)sel;
            w[0]->x28 = (Ob *)1;
            w[0]->x2c = (Ob *)D_00641224;
            func_001f40a0(w[0], 0x60000000);
            w[1] = func_001f31a8(D_003F39F0, 6);
            if (w[1] == 0) break;
            func_001f3e48(w[1], w[0]);
            func_001f3dc0(w[0]);
            break;
        case 2:
            w[0] = func_001f31a8(D_003F39C0, 6);
            if (w[0] == 0) break;
            func_001f3e48(w[0], o);
            w[0]->xd2 = D_00641274 * 16;
            w[1] = func_001f31a8(D_003F3980, 6);
            if (w[1] == 0) break;
            func_001f3e48(w[1], w[0]);
            w[1]->x24 = (Ob *)func_001fd518(w[0]);
            func_001f3dc0(w[0]);
            break;
        case 5:
            func_0020eb98();
            func_0020f3c8();
            func_0020fbe0();
            if (D_00641228 == -2) {
            z5:
                D_00641224 = 0;
                break;
            }
            if (D_00641228 == -1 && D_00641388 == 0) goto z5;
            D_00641224 = 1;
            goto c1;
            break;
        }
    }
    switch (D_00641224) {
    case 0:
        break;
    case 1:
        func_00206690(o, 0, 83, 11);
        func_00207870(o, 11, 0, 11, 71, 122, D_0064122C);
        break;
    case 2:
        func_00206690(o, 0, 83, 11);
        func_00207870(o, 11, 0, 11, 71, 122, D_0064122C);
        func_00206690(o, 133, 83, 26);
        func_0020dd38(o, 11, 159, 71, 166, D_00641234);
        break;
    case 3:
        func_00206690(o, 0, 83, 11);
        func_00207870(o, 11, 0, 11, 71, 122, D_0064122C);
        func_00206690(o, 133, 83, 26);
        pc = &D_00641234;
        func_0020dd38(o, 11, 159, 71, 166, *pc);
        func_00206690(o, 325, 83, 26);
        switch (D_00641238) {
        case 1: v = 148; break;
        case 0: v = 145; break;
        case 2: v = *pc ? 146 : 149; break;
        default: v = 147; break;
        }
        func_00207830(o, 11, 2, 351, 71, 122, v);
        func_00206690(o, 473, 83, 39);
        break;
    case 4:
        func_00206690(o, 0, 83, 11);
        func_00207870(o, 11, 0, 11, 71, 122, D_0064122C);
        func_00206690(o, 133, 83, 26);
        pc = &D_00641234;
        func_0020dd38(o, 11, 159, 71, 166, *pc);
        func_00206690(o, 325, 83, 26);
        switch (D_00641238) {
        case 1: v = 148; break;
        case 0: v = 145; break;
        case 2: v = *pc ? 146 : 149; break;
        default: v = 147; break;
        }
        func_00207830(o, 11, 2, 351, 71, 122, v);
        func_00206690(o, 473, 83, 39);
        func_00207870(o, 11, 1, 11, 99, 122, D_00641240 != -1 ? func_001ee5f0(D_00304BE8->x48e[D_00641240]) : func_001efbb8(56));
        func_00206690(o, 0, 111, 11);
        break;
    case 5:
        func_00206690(o, 0, 83, 11);
        func_00207870(o, 11, 0, 11, 71, 122, D_0064122C);
        func_00206690(o, 133, 83, 26);
        pc = &D_00641234;
        func_0020dd38(o, 11, 159, 71, 166, *pc);
        func_00206690(o, 325, 83, 26);
        switch (D_00641238) {
        case 1: v = 148; break;
        case 0: v = 145; break;
        case 2: v = *pc ? 146 : 149; break;
        default: v = 147; break;
        }
        func_00207830(o, 11, 2, 351, 71, 122, v);
        func_00206690(o, 473, 83, 39);
        switch (D_00641238) {
        case 1:
            func_00206690(o, 0, 111, 11);
            if (D_00641240 != -1) v = func_001ee5f0(D_00304BE8->x48e[D_00641240]);
            else v = func_001efbb8(56);
            func_00207870(o, 11, 1, 11, 99, 122, v);
            func_00206690(o, 133, 111, 26);
            if (D_00641238 == 1) func_0020dd38(o, 11, 159, 99, 166, D_00641248);
            func_00206690(o, 325, 111, 187);
            break;
        case 0:
            if (D_0064123C == 0) break;
            func_00206690(o, 0, 111, 11);
            func_00207870(o, 11, 1, 11, 99, 122, func_001ee5f0(D_00304BE8->x48e[D_00641240]));
            func_00206690(o, 133, 111, 379);
            break;
        case 2:
            break;
        }
        break;
    }
}
#include "data/data_003F.h"

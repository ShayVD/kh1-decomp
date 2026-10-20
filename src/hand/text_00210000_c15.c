#include "common.h"
#include "data/bss_0064.h"
typedef struct { u8 pad0[0xb4]; s32 xb4; u8 padb8[2]; s16 xba; u8 padbc[0xcc - 0xbc]; s16 xcc, xce; u8 padd0[2]; s16 xd2; } Obj;
typedef struct { u8 pad0[8]; u32 x8; u8 padc[4]; u32 x10; } Pad;
extern Pad *D_00425BC8;
extern s32 D_0064375C;
extern s32 D_003F34A8;
extern u8 D_00643770[];
extern u8 D_00643778[];
extern s32 D_00643708;
extern s32 D_0064370C;
extern u32 D_003E3D68;
extern s32 D_00643780[];
extern s32 D_00643794;
extern s32 D_003F6E30;
extern s32 D_003F34C8;
extern s32 D_00643790;
extern u8 D_00643760[]; /* src/data/bss_0064.c: s32 D_00643760[0x4] */
extern u8 D_003F6890[];
extern u8 D_003F6860[];
s32 func_001f42b8(Obj *);
void func_001f37c0(Obj *, s32);
void func_0011d768(s32);
void func_001fd858(Obj *);
void func_0020bd18(Obj *, s32);
s32 func_001fd518(Obj *);
s32 func_001fe5a0(Obj *);
Obj *func_001f4468(Obj *);
Obj *func_001f31a8(void *, s32);
void func_001f3e48(Obj *, Obj *);
void func_001f4058(Obj *, s32);
void func_001f3d58(Obj *, s32);
void func_00223a30(Obj *);
void func_0020a1d8(void);
void func_0013c778(s32, s32, s32);
void func_0024f098(void *, void *);
void func_00224030();
void func_001f3840(Obj *);
void func_0020be10(s32);
void func_00206690(Obj *, s32, s32, s32);
s32 func_001ee5f0(s32);
void func_00207870(Obj *, s32, s32, s32, s32, s32, s32);
void func_00207830(Obj *, s32, s32, s32, s32, s32, s32);
void func_00223ea8(void);
void func_0020a518(Obj *, s32, void *, void *);

void func_00224060(Obj *o) {
    s32 n1 = o->xce - 1;
    s32 i, k, y, sel, m, s;
    u32 cnt;
    Obj *p, *r;
    if (func_001f42b8(o)) {
        switch (D_0064375C) {
        case 0:
            if (D_00425BC8->x8 & 0x4000) {
                if (D_003F34A8 != 2 && D_00643770[1] == D_00643778[1] && D_00643770[2] == D_00643778[2] && D_00643770[3] == D_00643778[3]) {
                    func_001f37c0(o, 5);
                    func_0011d768(3);
                } else {
                    D_00643708 = o->xce - 1;
                    o->xd2 = *(u16 *)&D_00643708 << 4;
                    func_0011d768(3);
                }
                break;
            }
            func_001fd858(o);
            func_0020bd18(o, 8);
            D_00643708 = func_001fd518(o);
            for (i = 0; i < D_003E3D68; i++) {
                if (D_00643708 == D_003E3D68 - 1) {
                    if (i != 3) D_00643780[i] = 96;
                    else D_00643780[i] = 32;
                } else {
                    D_00643780[i] = (i == D_00643708 + 1) ? 96 : 32;
                }
            }
            if (!func_001fe5a0(o)) break;
            if (D_00643794 == 5) {
            if (D_00643708 < n1) {
                if (n1 >= 2) {
                func_0011d768(2);
                r = func_001f4468(o);
                p = func_001f31a8(D_003F6890, 6);
                if (!p) break;
                i = n1 - 1;
                func_001f3e48(p, r);
                p->xb4 += D_00643708 * 448;
                p->xba = i * 448 - 32;
                p->xcc = i;
                p->xce = i;
                if (D_0064370C >= n1) D_0064370C = 0;
                p->xd2 = *(u16 *)&D_0064370C << 4;
                break;
                }
                func_0011d768(4);
                p = func_001f31a8(D_003F6860, 6);
                if (!p) break;
                func_001f3e48(p, o);
                func_001f4058(p, 1);
                func_001f3d58(p, 6);
                func_00223a30(p);
                break;
            }
            func_0011d768(2);
            if (D_00643770[1] == D_00643778[1] && D_00643770[2] == D_00643778[2] && D_00643770[3] == D_00643778[3]) {
                func_001f37c0(o, 5);
            } else {
                D_003F6E30 = 1;
                func_0020a1d8();
                func_0013c778(D_00643770[1], D_00643770[2], D_00643770[3]);
                D_003F34C8++;
                D_0064375C++;
                func_0024f098(D_00643778, func_00224030);
            }
            } else {
                func_0011d768(4);
            }
            break;
        case 1:
            break;
        case 2:
            func_001f3d58(o, 5);
            func_001f3840(o);
            func_0020be10(16);
            break;
        }
    }
    func_00206690(o, -75, -16, 75);
    func_00207870(o, 11, 2, 0, -28, 122, func_001ee5f0(D_00643770[0]));
    func_00206690(o, 122, -16, 623);
    sel = func_001fd518(o);
    y = 0;
    for (i = 0; i < n1; i = k) {
        k = i + 1;
        func_00207870(o, i == sel, 0, 0, y, 122, func_001ee5f0(D_00643770[k]));
        y += 28;
    }
    func_00207830(o, i == sel, 2, 0, y, 122, 55);
    if (D_0064375C == 0) {
        func_00223ea8();
        if (D_00643790) do { func_0020a518(o, 0, D_00643760, D_00643780); } while (0);
    }
}

/* needs make: uses rodata (jump table jtbl_00490FF0).
 * NEEDS LAYOUT SPLIT: layout symbol func_0021d348 (0x21d348-0x21d9dc) is six functions:
 *   func_0021d348 0x21d348-0x21d844, func_0021d848 0x21d848-0x21d860,
 *   func_0021d860 0x21d860-0x21d944, func_0021d948 0x21d948-0x21d9a8,
 *   func_0021d9a8 0x21d9a8-0x21d9c4, func_0021d9c8 0x21d9c8-0x21d9dc.
 * func_0021d348 matches (rotry 00490ff0, 0 words differ over its 1276 bytes);
 * the five small ones compile to the original instruction sequences.
 * Uncomment once layout.tsv is split. */
typedef struct { u8 pad[0x74]; s32 x74; } S34B8;
extern s32 D_00642EA4;
extern s32 D_003F34FC;
extern s32 D_003F34DC, D_003F34E0, D_003F34E4, D_003F34E8, D_003F34EC, D_003F34F0, D_003F34F4, D_003F34F8;
extern s32 D_003F3514, D_003F3518, D_003F351C, D_003F3520;
extern s32 D_003F34C8;
extern u8 D_00490F58[], D_00490F70[], D_00490F88[], D_00490FA0[], D_00490FB8[], D_00490FD0[];
extern s32 D_00642E94;
extern u8 D_003F5A90[];
extern S34B8 *D_003F34B8;
extern s32 D_003F5C30[];
void func_00223e10(void);
void func_00120748(void *, s32, void *, s32);
void func_0021d228();
void func_0021d258();
void func_0021d288();
void func_0021d2b8();
void func_0021d2e8();
void func_0021d318();
void FlushCache(s32);
void func_0021b5c8(s32, s32, s32, s32, f32);
void func_0021fb10(void);
void func_0021b6a0(void);

void func_0021d348(Obj *o) {
    Obj *p;
    s32 i;
    if (func_001f42b8(o)) {
        switch (D_00642EA4) {
        case 0:
            switch (D_003F34FC) {
            default:
                D_00642EA4 = 2;
                break;
            case 0:
                func_00223e10();
                D_00642EA4++;
                break;
            case 1:
                D_00642EA4++;
                break;
            }
            break;
        case 1:
            if (D_003F34FC == 2) D_00642EA4++;
            break;
        case 2:
            switch (D_003F34DC) {
            default:
                D_00642EA4 = 4;
                break;
            case 0:
                D_003F34DC = 1;
                D_003F34C8++;
                D_00642EA4++;
                func_00120748(D_00490F58, D_003F34E0, func_0021d228, 0);
                break;
            case 1:
                D_00642EA4++;
                break;
            }
            break;
        case 3:
            if (D_003F34DC == 2) D_00642EA4++;
            break;
        case 4:
            switch (D_003F34E4) {
            default:
                D_00642EA4 = 6;
                break;
            case 0:
                D_003F34E4 = 1;
                D_003F34C8++;
                D_00642EA4++;
                func_00120748(D_00490F70, D_003F34E8, func_0021d258, 0);
                break;
            case 1:
                D_00642EA4++;
                break;
            }
            break;
        case 5:
            if (D_003F34E4 == 2) D_00642EA4++;
            break;
        case 6:
            switch (D_003F34EC) {
            default:
                D_00642EA4 = 8;
                break;
            case 0:
                D_003F34EC = 1;
                D_003F34C8++;
                D_00642EA4++;
                func_00120748(D_00490F88, D_003F34F0, func_0021d288, 0);
                break;
            case 1:
                D_00642EA4++;
                break;
            }
            break;
        case 7:
            if (D_003F34EC == 2) D_00642EA4++;
            break;
        case 8:
            switch (D_003F34F4) {
            default:
                D_00642EA4 = 10;
                break;
            case 0:
                D_003F34F4 = 1;
                D_003F34C8++;
                D_00642EA4++;
                func_00120748(D_00490FA0, D_003F34F8, func_0021d2b8, 0);
                break;
            case 1:
                D_00642EA4++;
                break;
            }
            break;
        case 9:
            if (D_003F34F4 == 2) D_00642EA4++;
            break;
        case 10:
            switch (D_003F3514) {
            default:
                D_00642EA4 = 12;
                break;
            case 0:
                D_003F3514 = 1;
                D_003F34C8++;
                D_00642EA4++;
                func_00120748(D_00490FB8, D_003F3518, func_0021d2e8, 0);
                break;
            case 1:
                D_00642EA4++;
                break;
            }
            break;
        case 11:
        case 13:
            if (D_003F3514 == 2) D_00642EA4++;
            break;
        case 12:
            switch (D_003F351C) {
            default:
                D_00642EA4 = 14;
                break;
            case 0:
                D_003F351C = 1;
                D_003F34C8++;
                D_00642EA4++;
                func_00120748(D_00490FD0, D_003F3520, func_0021d318, 0);
                break;
            case 1:
                D_00642EA4++;
                break;
            }
            break;
        case 14:
            FlushCache(0);
            func_0021b5c8(0xC009B, 0, 128, 128, 5.0f);
            D_00642E94 = 0;
            p = func_001f31a8(D_003F5A90, 0);
            if (p) func_001f3e48(p, o);
            func_0021fb10();
            if (!D_003F34B8->x74) {
                for (i = 0; i < 6; i++) {
                    if (!D_003F5C30[i]) goto inc;
                }
                D_003F34B8->x74 = 1;
                func_0011d768(18);
            }
        inc:
            D_00642EA4++;
            break;
        case 15:
            break;
        }
    }
    if (D_00642EA4 == 15) func_0021b6a0();
    func_00207830(o, 4, 2, 0, 0, 122, 110);
}
extern u8 D_003F5AE8[];
extern u8 D_003F5B58[];
extern u8 D_003F5BC8[];
extern s32 D_00643014;
extern s32 D_003F59D0[];
void func_002073b0(s32);
void func_00205b30(void *, void *);
void func_00206130(void *, s32, s32, s32, s32, u32);
void func_0020ca30(void *, s32, u32, u32);
void func_001fc308(void *, s32, s32, s32, s32, s32, s32, u32, u32);
void func_001f9438(void *, s32, s32, s32, s32, s32, u32);
void func_00205e30(void *, void *);
void func_0021b418();

void func_0021d848(void) {
    func_002073b0(0);
}

#if 0 /* 7 words off: the move of D_003F59D0[...] into t3 is scheduled early */
void func_0021d860(void *a) {
    func_00205b30(a, D_003F5AE8);
    func_00205b30(a, D_003F5AE8 + 32);
    func_00206130(a, 0, 62, 512, 2, 0x80364B2C);
    func_0020ca30(a, 0, 0x804C7F33, 0x805BB66A);
    func_001fc308(a, 160, 35, 0, 19, 20, 0, 0x80399BFF, 0x80399BFF);
    func_001f9438(a, 0, 173, 35, D_003F59D0[D_00643014], 19, 0x80399BFF);
}
#endif

void func_0021d948(void *a) {
    func_00205b30(a, D_003F5B58);
    func_00205b30(a, D_003F5B58 + 32);
    func_00206130(a, 0, 0, 512, 2, 0x80364B2C);
}

void func_0021d9a8(void *a) {
    func_00205e30(a, D_003F5BC8);
}

void func_0021d9c8(void) {
    func_0021b418();
}
#include "data/data_003F.h"
#include "data/data_0049.h"

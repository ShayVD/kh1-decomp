#include "common.h"
#include "data/bss_0064.h"
typedef struct { u8 pad0[0xb4]; s32 xb4; u8 padb8[2]; s16 xba; u8 padbc[0xcc - 0xbc]; s16 xcc, xce; u8 padd0[2]; s16 xd2; } Obj;
#include "data/pieces/D_00425BC8.h"
extern s32 D_0064375C;
extern s32 D_003F34A8;
extern u8 D_00643770[];
extern u8 D_00643778[];
extern s32 D_00643708;
extern s32 D_0064370C;
#include "data/pieces/D_003E3D68.h"
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

#include "data/data_003F.h"
#include "data/data_0049.h"
#include "data/pieces/D_003F34C8.h"

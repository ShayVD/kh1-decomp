#include "common.h"
#include "data/pieces/D_00304BE8_s.h"
#include "data/bss_0064.h"

#include "data/pieces/D_003E8E08.h"
#include "data/pieces/D_003E3D70.h"
typedef Rec_3E3D70 Rec;
typedef struct { u8 pad[0x24]; u8 x24; } Arg;
typedef struct Obj { u8 pad[0x10]; struct Obj *x10; u8 p14[0x10]; s32 x24; s32 x28; u8 p2c[0xCE - 0x2C]; s16 xce; s16 xd0; s16 xd2; } Obj;
typedef struct Obj7 { u8 pad[0x10]; struct Obj7 *x10; u8 p14[0x10]; struct Obj7 *x24; s32 x28; u8 p2c[0xBA - 0x2C]; s16 xba; u8 pbc[0xCC - 0xBC]; s16 xcc; s16 xce; s16 xd0; s16 xd2; } Obj7;
#include "data/pieces/D_00425BC8.h"
#include "data/types/text_00210000_b14_p.h"
typedef Sub_304be8 Sub;
typedef W606Mem_304be8 Rec74;
typedef Save_304be8 S4BE8;
#include "data/types/text_00210000_b14.h"
#include "data/pieces/D_003F34B8.h"
#include "data/pieces/D_003E3D68.h"
#include "data/pieces/D_003E3E50.h"
extern u8 D_003F3B10[];
extern u8 D_003F3DF0[];
extern u8 D_003F3E90[];
extern s32 D_003F3EB8[];
extern u8 D_003F3ED0[];
extern u8 D_003F3F00[];
extern u8 D_003F3F30[];
extern PN D_003F40F8[];
extern s32 D_003F4368[];
extern s32 D_003F4380[];
extern s32 *D_003F43C8[];
extern u8 D_003F4430[];
extern u8 D_003F4460[];
extern u8 D_003F44A0[];
extern s32 D_003F44C8[];
extern u8 D_003F44E0[];
extern s32 D_003F45A8[];
extern u8 D_003F45C0[];
extern u8 D_003F45F0[];
extern u8 D_003F4620[];
extern s32 D_00641BA4;
extern s32 D_00641BAC;
extern s32 D_00641BB0;
extern u8 *D_00641BB4; /* src/data/bss_0064.c: s32 D_00641BB4 */
extern s32 D_00641BC0;
extern s32 D_00641BD8;
extern s32 D_00641BDC;
extern s32 D_00642418[];
extern s32 D_00642818[];
extern s32 D_00642C18;
extern void *D_00642C20;
extern s32 D_00642C24;
extern s32 D_00642C28;
extern s32 D_00642C2C;
extern Sub *D_00642C30; /* src/data/bss_0064.c: s32 D_00642C30 */
s32 D_00642C34 ALIGNED(4);
s32 D_00642C38 ALIGNED(8);
extern s32 D_00642C3C;
s32 D_00642C40 ALIGNED(16);
extern s32 D_00642C44;
s32 D_00642C4C ALIGNED(4);
s32 D_00642C50 ALIGNED(16);
extern s32 D_00642C54;
extern u32 D_00642C58;
extern s32 D_00642C5C;
extern s32 D_00642C60;
extern s32 D_00642C64;
extern s32 D_00642C68;
extern s32 D_00642C6C;
extern s32 D_00642C78[];
extern s32 D_00642C88;
extern s32 D_00642C94;
extern s32 D_00642C98;
extern s32 D_00642C9C;
extern s32 D_00642CA0;
extern u16 D_00642CC8; /* src/data/bss_0064.c: s32 D_00642CC8 */
extern s32 D_00642CCC;
extern u16 D_00642CD0; /* src/data/bss_0064.c: s32 D_00642CD0 */
extern u16 D_00642CD4; /* src/data/bss_0064.c: s32 D_00642CD4 */

s32 func_00132f88(s32);
s32 func_0013c288(s32);
s32 func_00170dd8(s32, s32);
s32 func_001ee5f0(s32);
s32 func_001eec00(s32);
s32 func_001eed80(s32, u8 *, s32);
s32 func_001ef580(s32);
s32 func_001ef5c0(s32);
s32 func_001ef720(s32);
s32 func_001efbb8(s32);
s32 func_001f3758(void *);
s32 func_001f42b8(void *);
s32 func_001f94f0(void *, s32, s32, s32, s32, s32, s32);
s32 func_001fd518(void *);
s32 func_001fd548(void *);
s32 func_001fd590(void *);
s32 func_001fd618(void *);
s32 func_001fd638(void *);
s32 func_001fe5a0(void *);
void *func_001f31a8(u8 *, s32);
void *func_001f4468(void *);
void func_0011d768(s32);
void func_00141b10(s32, void *);
void func_001ef830(void);
void func_001f36b8(void *);
void func_001f3708(void *, s32);
void func_001f3d58(void *, s32);
void func_001f3dc0(void *);
void func_001f3e20(void *, void *);
void func_001f3e48(void *, void *);
void func_001f3e90(void *, void *);
void func_001f40a0(void *, s32);
void func_001f8ee0(void *);
void func_001f8f30(void);
void func_001f9270(void *, s32, s32, s32, s32, s32);
void func_001f9438(void *, s32, s32, s32, s32, s32, s32);
void func_001fd5e0(void *, s32);
void func_001fd610(void *, s32);
void func_001fd688(void *);
void func_001fd858(void *);
void func_001fe158(void *);
void func_001ff488(void *, s32, s32, s32, s32, s32);
void func_00202fc0(void *);
void func_00206690(void *, s32, s32, s32);
void func_002066b0(void *, s32, s32, s32, s32, s32);
void func_00207830(void *, s32, s32, s32, s32, s32, s32);
void func_00207870(void *, s32, s32, s32, s32, s32, s32);
void func_00209340(void *, s32, s32 *);
void func_0020bd18(void *, s32);
void func_00211480(void *, s32);
void func_002115e0(void *, s32, s32, s32, s32, s32, s32);
void func_002140c0(void *, s32);
void func_00214130(void *, s32, s32, s32, s32, s32);
void func_00214290(void *, s32, s32, s32, s32, s32);

static inline s32 col(s32 x, s32 y) {
    if (x < y) return 0x80FC927A;
    if (x == y) return 0x80808080;
    return 0x806E6EFF;
}

void func_002123b8(Arg *a) {
    Rec buf;
    Rec *r;
    u8 s;
    u8 *p;
    func_001f9270(a, 0, 16, 174, 15, 0x801EC8C8);
    { s32 o = D_00641BB0; p = D_00641BB4 + o + 25; }
    s = *p;
    *p = a->x24;
    func_00141b10(D_00641BAC, &buf);
    { s32 o = D_00641BB0; (D_00641BB4 + o)[25] = s; }
    (*(S4_3e8e08 *)&D_003E8E08).c = buf.x40;
    r = &D_003E3D70.rec[D_00641BAC];
    (*(S4_3e8e08 *)&D_003E8E08).a = r->x40;
    if (r->x40 < buf.x40) (*(S4_3e8e08 *)&D_003E8E08).b = 0x80FC927A;
    else if (r->x40 == buf.x40) (*(S4_3e8e08 *)&D_003E8E08).b = 0x80808080;
    else (*(S4_3e8e08 *)&D_003E8E08).b = 0x806E6EFF;
    func_001f9438(a, 0, 12, 37, 175, 15, 0x80E6E6E6);
    func_002066b0(a, 12, 53, 118, 0x80323232, 0x80323232);
    (*(S4_3e8e08 *)&D_003E8E08).a = r->x48;
    (*(S4_3e8e08 *)&D_003E8E08).c = buf.x48;
    if (r->x48 < buf.x48) (*(S4_3e8e08 *)&D_003E8E08).b = 0x80FC927A;
    else if (r->x48 == buf.x48) (*(S4_3e8e08 *)&D_003E8E08).b = 0x80808080;
    else (*(S4_3e8e08 *)&D_003E8E08).b = 0x806E6EFF;
    func_001f9438(a, 0, 12, 69, 176, 15, 0x80E6E6E6);
    func_002066b0(a, 12, 85, 118, 0x80323232, 0x80323232);
    (*(S4_3e8e08 *)&D_003E8E08).a = r->xe0;
    (*(S4_3e8e08 *)&D_003E8E08).c = buf.xe0;
    if (r->xe0 < buf.xe0) (*(S4_3e8e08 *)&D_003E8E08).b = 0x80FC927A;
    else if (r->xe0 == buf.xe0) (*(S4_3e8e08 *)&D_003E8E08).b = 0x80808080;
    else (*(S4_3e8e08 *)&D_003E8E08).b = 0x806E6EFF;
    func_001f9438(a, 0, 12, 101, 177, 15, 0x80E6E6E6);
    func_002066b0(a, 12, 117, 118, 0x80323232, 0x80323232);
    (*(S4_3e8e08 *)&D_003E8E08).a = r->x4c;
    (*(S4_3e8e08 *)&D_003E8E08).c = buf.x4c;
    if (r->x4c < buf.x4c) (*(S4_3e8e08 *)&D_003E8E08).b = 0x80FC927A;
    else if (r->x4c == buf.x4c) (*(S4_3e8e08 *)&D_003E8E08).b = 0x80808080;
    else (*(S4_3e8e08 *)&D_003E8E08).b = 0x806E6EFF;
    func_001f9438(a, 0, 12, 133, 178, 15, 0x80E6E6E6);
    func_002066b0(a, 12, 149, 118, 0x80323232, 0x80323232);
    (*(S4_3e8e08 *)&D_003E8E08).a = r->x50;
    (*(S4_3e8e08 *)&D_003E8E08).c = buf.x50;
    if (r->x50 < buf.x50) (*(S4_3e8e08 *)&D_003E8E08).b = 0x80FC927A;
    else if (r->x50 == buf.x50) (*(S4_3e8e08 *)&D_003E8E08).b = 0x80808080;
    else (*(S4_3e8e08 *)&D_003E8E08).b = 0x806E6EFF;
    func_001f9438(a, 0, 12, 165, 179, 15, 0x80E6E6E6);
    func_002066b0(a, 12, 181, 118, 0x80323232, 0x80323232);
}

void func_00212930(Obj *a) {
    Obj *o;
    Obj *q[2];
    s32 k, t, s, n, y, i, j, r;
    if (func_001f42b8(a)) {
        if (D_00425BC8->x8 & 0x4000) {
            func_001f3758(a);
            func_0011d768(3);
            D_00641BA4 = 1;
        } else {
            func_001fd858(a);
            func_0020bd18(a, 8);
            D_00641BD8 = func_001fd618(a);
            D_00641BDC = func_001fd638(a);
            t = func_001fd548(a);
            k = D_00642418[t];
            if ((o = a->x10)) {
                if (k) o->x24 = func_001eec00(k);
                else o->x24 = func_001efbb8(169);
                if ((o = o->x10)) o->x24 = k;
            }
            if (func_001fe5a0(a)) {
                if (k) func_0011d768(5);
                else func_0011d768(75);
                t = func_001ef720(D_00641BAC);
                j = D_00641BAC; r = D_003E3E50[j].x0;
                if (t >= r - func_001eed80(j, D_00641BB4, k)) {
                    (D_00641BB4 + D_00641BB0)[25] = k;
                    func_001ef830();
                    func_001f3d58(a, 5);
                    func_001f3758(a);
                    D_00641BA4 = 3;
                    D_00641BC0 = k;
                } else {
                    func_0011d768(4);
                    if ((q[0] = func_001f31a8(D_003F3B10, 6))) {
                        func_001f3e48(q[0], a);
                        func_00211480(q[0], 170);
                    }
                }
            }
        }
    }
    func_00202fc0(a);
    s = func_001fd518(a);
    n = func_001fd618(a);
    y = func_001fd590(a);
    func_001f8ee0(a);
    for (i = 0; i < 8 && n < D_00642C18; i++) {
        func_002115e0(a, i == s, 0, y, 166, D_00642418[n], D_00642818[n]);
        n++;
        y += 28;
    }
    do { func_001f8f30(); } while (0);
}

#define D_00642C3C (*(u32 *)&D_00642C3C)
#define BYTE D_00642C30->name[D_00642C34]
void func_002145d8(Obj *a) {
    s32 buf[3];
    s32 f, v;
    Obj *o, *p;
    f = D_00642C3C & 0x80;
    if (func_001f42b8(a)) {
        if (D_00425BC8->x8 & 0x4000) {
            func_001f3758(a);
            func_0011d768(3);
            D_00642C24 = 1;
        } else {
            func_001fd858(a);
            func_0020bd18(a, 8);
            v = func_001fd518(a);
            D_00642C6C = v;
            if ((p = a->x10)) {
                if (v == 0) p->x24 = f ? 181 : 184;
                else p->x24 = D_003F3EB8[v];
            }
            if (func_001fe5a0(a)) {
                func_001f3d58(a, 5);
                p = func_001f4468(a);
                D_00642C44 = D_00642C6C;
                switch (D_00642C6C) {
                case 0:
                    func_001f3758(a);
                    if (D_00642C28 != -1) {
                        if (!f) {
                            func_0011d768(75);
                            BYTE |= 0x80;
                            D_00642C24 = 5;
                        } else if (D_00642C40 == 0) {
                            func_0011d768(5);
                            BYTE &= 0x7f;
                            D_00642C24 = 5;
                        } else {
                            func_0011d768(4);
                            if ((o = func_001f31a8(D_003F3DF0, 6))) {
                                func_001f3e90(p, o);
                                func_001f3e20(o, p);
                                func_002140c0(o, 202);
                            }
                        }
                    } else {
                        if (!f) func_0011d768(75);
                        else func_0011d768(5);
                        D_00304BE8->list599[D_00642C34] ^= 0x80;
                        D_00642C24 = 5;
                    }
                    break;
                case 1:
                    func_001f3758(a);
                    func_0011d768(2);
                    D_00642C24 = 4;
                    break;
                case 2:
                    func_001f3758(a);
                    func_0011d768(2);
                    D_00642C24 = 3;
                    break;
                }
            }
        }
    }
    buf[0] = f ? 185 : 186;
    buf[1] = 187;
    buf[2] = 188;
    func_00209340(a, 2, buf);
}
#undef D_00642C3C
#undef BYTE

#define D_00642C6C (*(u16 *)&D_00642C6C)
void func_00214b20(Obj *a) {
    Obj *o[2];
    s32 n;
    Sub *sub;
    s32 money;
    s32 k, m, lim, idx, it, id, sel, i, j, y, c, fl;
    Obj *p;
    k = a->x24;
    n = D_00642C78[k];
    k = D_00304BE8->x48e[k];
    sub = &D_00304BE8->m[k].sub;
    if (n == 0) return;
    if (D_00642C24 < 3) {
        m = 0;
        lim = 8;
    } else {
        m = 1;
        lim = 7;
    }
    func_001fd5e0(a, n);
    func_001fd610(a, lim);
    func_001fd688(a);
    money = func_001ef720(k);
    if (func_001f42b8(a)) {
        if (D_00425BC8->x8 & 0x4000) {
            func_001f3758(a);
            func_0011d768(3);
            if (!m) D_00642C24 = 0;
            else D_00642C24 = 2;
        } else {
            func_001fd858(a);
            func_0020bd18(a, 8);
            D_00642C5C = a->xd0 >> 4;
            D_00642C60 = a->xd2 >> 4;
            idx = func_001fd548(a);
            it = sub->name[idx];
            id = it & 0x7f;
            if ((p = a->x10)) p->x24 = func_001ef580(id);
            if (func_001fe5a0(a)) {
                p = func_001f4468(a);
                func_001f3d58(a, 5);
                func_001f3758(a);
                if (!m) {
                    func_0011d768(2);
                    D_00642C34 = idx;
                    D_00642C38 = id;
                    D_00642C3C = it;
                    D_00642C40 = 0;
                    if (money < func_001ef5c0(id)) D_00642C40 = 1;
                    D_00642C24 = 2;
                    if ((o[0] = func_001f31a8(D_003F3ED0, 6))) {
                        func_001f3e90(p, o[0]);
                        func_001f3e20(o[0], p);
                        o[0]->xd2 = D_00642C6C << 4;
                        if ((o[1] = func_001f31a8(D_003F3E90, 6))) {
                            func_001f3e90(o[0], o[1]);
                            func_001f3e20(o[1], o[0]);
                            func_001f3dc0(o[0]);
                        }
                    }
                } else {
                    func_0011d768(74);
                    D_00642C4C = idx;
                    D_00642C54 = it;
                    D_00642C50 = id;
                    D_00642C24 = 5;
                    sub->name[D_00642C34] = *(u8 *)&D_00642C54;
                    sub->name[D_00642C4C] = *(u8 *)&D_00642C3C;
                }
            }
        }
    }
    func_00202fc0(a);
    sel = func_001fd518(a);
    i = func_001fd618(a);
    y = func_001fd590(a);
    fl = a->x28;
    lim = a->xce + 1;
    func_001f8ee0(a);
    for (j = 0; j < lim && i < n; j++, i++) {
        idx = sub->name[i];
        func_00214290(a, !fl ? 2 : !(idx & 0x80) ? j == sel : money < func_001ef5c0(idx & ~0x80) ? (j == sel ? 3 : 2) : j == sel, 0, y, 166, idx);
        y += 28;
    }
    func_001f8f30();
}
#undef D_00642C6C

#define D_00642C6C (*(u16 *)&D_00642C6C)
void func_00214fc8(Obj *a) {
    Obj *o[2];
    s32 m, lim, idx, it, id, sel, i, j, y, fl;
    Obj *p;
    if (D_00642C88 == 0) return;
    if (D_00642C24 < 3) {
        m = 0;
        lim = 8;
    } else {
        m = 1;
        lim = 7;
    }
    func_001fd5e0(a, D_00642C88);
    func_001fd610(a, lim);
    func_001fd688(a);
    if (func_001f42b8(a)) {
        if (D_00425BC8->x8 & 0x4000) {
            func_001f3758(a);
            func_0011d768(3);
            if (!m) D_00642C24 = 0;
            else D_00642C24 = 2;
        } else {
            S4BE8 **b = &D_00304BE8;
            func_001fe158(a);
            func_0020bd18(a, 8);
            D_00642C64 = a->xd0 >> 4;
            D_00642C68 = a->xd2 >> 4;
            idx = func_001fd548(a);
            it = (*b)->list599[idx];
            id = it & 0x7f;
            if ((p = a->x10)) p->x24 = func_001ef580(id);
            if (func_001fe5a0(a)) {
                p = func_001f4468(a);
                func_001f3d58(a, 5);
                func_001f3758(a);
                if (!m) {
                    func_0011d768(2);
                    D_00642C34 = idx;
                    D_00642C38 = id;
                    D_00642C3C = it;
                    D_00642C40 = 0;
                    D_00642C24 = 2;
                    if ((o[0] = func_001f31a8(D_003F3ED0, 6))) {
                        func_001f3e90(p, o[0]);
                        func_001f3e20(o[0], p);
                        o[0]->xd2 = D_00642C6C << 4;
                        if ((o[1] = func_001f31a8(D_003F3E90, 6))) {
                            func_001f3e90(o[0], o[1]);
                            func_001f3e20(o[1], o[0]);
                            func_001f3dc0(o[0]);
                        }
                    }
                } else {
                    func_0011d768(74);
                    D_00642C4C = idx;
                    D_00642C54 = it;
                    D_00642C50 = id;
                    D_00642C24 = 5;
                    (*b)->list599[D_00642C34] = *(u8 *)&D_00642C54;
                    (*b)->list599[D_00642C4C] = *(u8 *)&D_00642C3C;
                }
            }
        }
    }
    func_00202fc0(a);
    sel = func_001fd518(a);
    i = func_001fd618(a);
    y = func_001fd590(a);
    fl = a->x28;
    lim = a->xce + 1;
    func_001f8ee0(a);
    for (j = 0; j < lim && i < D_00642C88; j++, i++) {
        s32 c = 2;
        idx = D_00304BE8->list599[i];
        if (fl) c = j == sel;
        func_00214130(a, c, 0, y, 166, idx);
        y += 28;
    }
    func_001f8f30();
}
#undef D_00642C6C

void func_00215420(Obj *a) {
    Obj *q[2];
    Obj *o;
    u32 v, i;
    s32 sel, y, c, k;
    if (func_001f42b8(a)) {
        if (D_00425BC8->x8 & 0x4000) {
            func_001f3758(D_00642C20);
            func_0011d768(3);
        } else {
            func_001fd858(a);
            func_0020bd18(a, 8);
            v = func_001fd518(a);
            D_00642C58 = v;
            if ((o = a->x10) && (o = o->x10)) {
                o->x24 = v;
                if (v < D_003E3D68) {
                    o->xd0 = D_00642C5C << 4;
                    o->xd2 = D_00642C60 << 4;
                } else {
                    o->xd0 = D_00642C64 << 4;
                    o->xd2 = D_00642C68 << 4;
                }
            }
            if (func_001fe5a0(a)) {
                if (D_00642C58 < D_003E3D68) {
                    if (D_00642C78[D_00642C58]) {
                        func_0011d768(2);
                        D_00642C28 = D_00642C58;
                        k = D_00304BE8->x48e[D_00642C28];
                        D_00642C2C = k;
                        D_00642C30 = &D_00304BE8->m[k].sub;
                        D_00642C24 = 1;
                        func_001f3708(a, 5);
                        if ((o = a->x10)) {
                            func_001f36b8(o);
                            if ((o = o->x10)) {
                                o->x28 = 1;
                                if ((q[0] = func_001f31a8(D_003F3F30, 6))) {
                                    func_001f3e90(o, q[0]);
                                    func_001f3e20(q[0], o);
                                    if ((q[1] = func_001f31a8(D_003F3F00, 6))) {
                                        func_001f3e90(q[0], q[1]);
                                        func_001f3e20(q[1], q[0]);
                                    }
                                }
                                func_001f3dc0(o);
                            }
                        }
                    } else {
                        func_0011d768(4);
                    }
                } else if (D_00642C88) {
                    D_00642C28 = -1;
                    func_0011d768(2);
                    D_00642C24 = 1;
                    func_001f3708(a, 5);
                    if ((o = a->x10)) {
                        func_001f36b8(o);
                        if ((o = o->x10)) {
                            o->x28 = 1;
                            if ((q[0] = func_001f31a8(D_003F3F30, 6))) {
                                func_001f3e90(o, q[0]);
                                func_001f3e20(q[0], o);
                                func_001f40a0(o, 0x60000000);
                            }
                            func_001f3dc0(o);
                        }
                    }
                } else {
                    func_0011d768(4);
                }
            }
        }
    }
    sel = func_001fd518(a);
    y = 0;
    for (i = 0; i < D_003E3D68; i++) {
        if (D_00642C78[i]) c = i == sel;
        else c = i == sel ? 3 : 2;
        func_00207870(a, c, 0, 0, y, 122, func_001ee5f0(D_00304BE8->x48e[i]));
        y += 28;
    }
    if (D_00642C88) c = D_003E3D68 == sel;
    else c = D_003E3D68 == sel ? 3 : 2;
    func_00207830(a, c, 0, 0, y, 122, 192);
}

void func_00217490(void *a) {
    s32 i, y, t, k, n, id, c, r;
    s32 *p;
    if (D_00642CCC == 0) {
        y = 0;
        for (i = 0; i < 3; i++) {
            func_00207830(a, 2, 2, 0, y, 180, D_003F45A8[i]);
            func_001f9438(a, 0, 86, y + 5, 51, 15, 0x20E6E6E6);
            t = func_00132f88(func_0013c288(i));
            if (!t) t = func_001efbb8(212);
            func_001f94f0(a, 0, 96, y + 5, t, 15, 0x20E6E6E6);
            y += 28;
        }
    } else {
        k = D_00304BE8->x48e[D_00642CCC];
        n = D_003F40F8[k].n;
        p = D_003F40F8[k].p;
        func_00207830(a, 2, 2, 0, 0, 342, D_003F4368[D_003F34B8->a[k]]);
        func_001ff488(a, 0, 28, 342, n * 28 + 10, 0x40000000);
        y = 57;
        for (i = 0; i < n; i++) {
            id = p[i];
            if (k == 2 && id == 7) c = 255;
            else c = D_003F4380[id];
            func_002066b0(a, 12, y, 318, 0x20E6E6E6, 0x20E6E6E6);
            func_001f9438(a, 0, 12, y - 15, c, 15, 0x20E6E6E6);
            r = func_00170dd8(k, id);
            func_001f9438(a, 0, 191, y - 15, D_003F43C8[id][2 - r], 15, 0x20E6E6E6);
            y += 26;
        }
    }
}

void func_00217b38(void *a) {
    Obj7 *o[3];
    s32 *p;
    if (func_001f42b8(a)) {
        p = &D_00642C94;
        switch (*p) {
        case 0:
            if ((o[0] = func_001f31a8(D_003F4620, 6))) {
                u32 *n;
                func_001f3e48(o[0], a);
                n = &D_003E3D68;
                o[0]->xcc = o[0]->xce = *n;
                o[0]->xba = *n * 448 - 32;
                o[0]->xd2 = D_00642CCC << 4;
                if ((o[1] = func_001f31a8(D_003F45F0, 6))) {
                    func_001f3e48(o[1], o[0]);
                    if ((o[2] = func_001f31a8(D_003F45C0, 6))) {
                        func_001f3e48(o[2], o[1]);
                        func_001f3dc0(o[0]);
                    }
                }
            }
            break;
        case 1:
        case1:
            if ((o[0] = func_001f31a8(D_003F44E0, 6))) {
                func_001f3e48(o[0], a);
                o[0]->xd2 = D_00642CD0 << 4;
                if ((o[1] = func_001f31a8(D_003F44A0, 6))) {
                    func_001f3e48(o[1], o[0]);
                    func_001f3dc0(o[0]);
                }
            }
            break;
        case 2:
            if ((o[0] = func_001f31a8(D_003F4460, 6))) {
                func_001f3e48(o[0], a);
                o[0]->xcc = o[0]->xce = D_00642CC8;
                o[0]->xd2 = D_00642CD4 << 4;
                if ((o[1] = func_001f31a8(D_003F4430, 6))) {
                    func_001f3e48(o[1], o[0]);
                    func_001f3dc0(o[0]);
                }
            }
            break;
        case 3:
            if (D_00642CCC == 0) {
                *p = 1;
                goto case1;
            }
            break;
        }
    }
    switch (D_00642C94) {
    default:
    case 0:
        break;
    case 1:
        func_00206690(a, 0, 83, 11);
        func_00207870(a, 11, 0, 11, 71, 122, func_001ee5f0(D_00642C98));
        break;
    case 2:
        func_00206690(a, 0, 83, 11);
        func_00207870(a, 11, 0, 11, 71, 122, func_001ee5f0(D_00642C98));
        func_00206690(a, 133, 83, 26);
        func_00207830(a, 11, 2, 159, 71, 166, D_003F44C8[D_00642C9C]);
        break;
    case 3:
        func_00206690(a, 0, 83, 11);
        func_00207870(a, 11, 0, 11, 71, 122, func_001ee5f0(D_00642C98));
        func_00206690(a, 133, 83, 26);
        func_00207830(a, 11, 2, 159, 71, 166, D_003F44C8[D_00642C9C]);
        func_00206690(a, 325, 83, 26);
        func_00207870(a, 11, 2, 351, 71, 122, D_00642CA0);
        func_00206690(a, 473, 83, 39);
        break;
    }
}
#include "data/data_003F.h"
#include "data/pieces/D_003F40D0.h"

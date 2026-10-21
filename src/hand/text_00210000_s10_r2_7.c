/* func_00212cc0 (hand), s10 r2_7. From r2_1's 6w draft: `func_002114f0(o, m, 0, cur, 166, v); cur += 28;` (cur passed directly, no copy b) and `j++; i++;` (j first:
   loop.c then initialises the t[j+24] giv before cur, so the giv gets s1 and cur s2 as the original), with the identical-arm `if (j) m = i == sel; else m = i == sel;`
   (jump2 merges the arms; the copies give sel the refs it needs for s6). Natural spellings of m without the identical arms are 7w. */
#include "common.h"
#include "data/bss_0064.h"

typedef struct { u8 pad[4]; u8 x4; u8 pad5[0x17]; u8 x1c[0x58]; } T74c;
typedef struct { T74c e[10]; u8 pad[0x48e - 0x488]; u8 x48e[11]; } G4BE8c;
extern G4BE8c *D_00304BE8;
typedef struct { u8 pad[8]; s32 f8; } S5bc8c;
#include "data/pieces/D_00425BC8.h"
#include "data/pieces/D_003E3D70.h"
typedef S4c_3E3D70 S4c;
typedef E3D70c_3E3D70 E3D70c;

typedef struct {
    u8 pad0[0x10]; void *x10; u8 pad14[0x14]; s32 x28; s32 x2c;
    u8 pad30[0xcc - 0x30]; s16 xcc; s16 xce; u16 xd0; u16 xd2;
} Obj2cc0;
extern s32 D_00641BA4, D_00641BAC, D_00641BB4, D_00641BB8, D_00641BBC, D_00641BC4;
extern s32 D_00641BC8, D_00641BCC, D_00641C00, D_00642410, D_00642C18;
extern u16 D_00641BD0, D_00641BD4, D_00641BD8, D_00641BDC;
extern s32 D_00641BF0[];
extern u8 D_003F3C00[], D_003F3BD0[], D_003F3BA0[], D_003F3B70[], D_003F3C90[], D_003F3C60[], D_003F3C30[];
void func_0011d768(s32);
s32 func_001ef320(void);
s32 func_001f31a8(void *, s32);
void func_001f36b8(void *);
void func_001f3708(Obj2cc0 *, s32);
void func_001f3758(Obj2cc0 *);
void func_001f3dc0(Obj2cc0 *);
void func_001f3e20(void *, void *);
void func_001f3e48(void *, void *);
void func_001f3e90(void *, void *);
s32 func_001f42b8(Obj2cc0 *);
void func_001f8ba8(Obj2cc0 *);
void func_001f8f30(void);
s32 func_001fd518(Obj2cc0 *);
s32 func_001fd590(Obj2cc0 *);
void func_001fd5e0(Obj2cc0 *, s32);
void func_001fd610(Obj2cc0 *, s32);
s32 func_001fd618(Obj2cc0 *);
void func_001fd688(Obj2cc0 *);
void func_001fd858(Obj2cc0 *);
s32 func_001fe5a0(Obj2cc0 *);
void func_00202fc0(Obj2cc0 *);
void func_0020a6c0(s32);
void func_0020bd18(Obj2cc0 *, s32);
void func_002114f0(Obj2cc0 *, s32, s32, s32, s32, s32);
void func_00211da0(void);
void func_002122b8(Obj2cc0 *);
void func_002127e0(void);

static inline void INL(s32 w, s32 *p) { ((Obj2cc0 *)w)->x28 = p[3]; ((Obj2cc0 *)w)->x2c = p[2]; }
static inline void INL2(Obj2cc0 *w, s32 *p) { w->x28 = p[3]; w->x2c = p[2]; }
void func_00212cc0(Obj2cc0 *o) {
    s32 w[4];
    u8 *t;
    s32 n, s;
    T74c *e;
    s32 i, j, sel, cur, cnt, lim, a, b;
    u8 *pc;
    s32 *p;
    void *q;

    n = D_00304BE8->x48e[D_00641BC4];
    e = &D_00304BE8->e[n];
    t = &e->x4;
    if (func_001f42b8(o)) {
        if (((S5bc8c *)D_00425BC8)->f8 & 0x4000) {
            func_001f3758(o);
            func_0011d768(3);
            D_00641BA4 = 0;
        } else {
            func_001fd858(o);
            func_0020bd18(o, 8);
            D_00641BC8 = (s16)o->xd0 >> 4;
            D_00641BCC = (s16)o->xd2 >> 4;
            s = D_00641BC8 + D_00641BCC;
            if (!func_001fe5a0(o)) goto done;
            if (s == 0) {
                if (n == 0 && !func_001ef320()) {
                    func_0011d768(4);
                    goto done;
                }
                func_0011d768(2);
                D_00641BA4 = 2;
                D_00641BB8 = s;
                func_001f3708(o, 5);
                {
                    q = o->x10;
                    if (q) {
                        func_001f36b8(q);
                        D_00641BBC = D_00641BF0[D_00641BC4];
                        func_00211da0();
                        D_00641C00 = 1;
                        if ((w[0] = func_001f31a8(D_003F3C00, 6))) {
                            func_001f3e48((void *)w[0], o);
                            func_002122b8(o);
                            ((Obj2cc0 *)w[0])->xd0 = D_00641BD0 << 4;
                            ((Obj2cc0 *)w[0])->xd2 = D_00641BD4 << 4;
                            func_001fd5e0((void *)w[0], D_00642410);
                            func_001fd610((void *)w[0], 7);
                            func_001fd688((void *)w[0]);
                            if ((w[1] = func_001f31a8(D_003F3BD0, 6))) {
                                func_001f3e48((void *)w[1], (void *)w[0]);
                                if ((w[2] = func_001f31a8(D_003F3BA0, 6))) {
                                    func_001f3e48((void *)w[2], (void *)w[1]);
                                    ((Obj2cc0 *)w[2])->x28 = D_003E3D70.e3D70c[D_00641BAC].s.d;
                                    ((Obj2cc0 *)w[2])->x2c = D_003E3D70.e3D70c[D_00641BAC].s.c;
                                    if (D_00641BC4 != 3) {
                                        if ((w[3] = func_001f31a8(D_003F3B70, 1))) {
                                            func_001f3e48((void *)w[3], (void *)w[2]);
                                            func_0020a6c0(D_00641BC4);
                                        }
                                    }
                                }
                                func_001f3dc0((void *)w[0]);
                            }
                        }
                    }
                }
            } else {
                func_0011d768(2);
                D_00641BA4 = 2;
                D_00641BB8 = s;
                func_001f3708(o, 5);
                {
                    q = o->x10;
                    if (q) {
                        func_001f36b8(q);
                        D_00641BB4 = s - 1;
                        D_00641BBC = e->x1c[s];
                        func_002127e0();
                        if ((w[0] = func_001f31a8(D_003F3C90, 6))) {
                            func_001f3e90(q, (void *)w[0]);
                            func_001f3e20((void *)w[0], q);
                            ((Obj2cc0 *)w[0])->xd0 = D_00641BD8 << 4;
                            ((Obj2cc0 *)w[0])->xd2 = D_00641BDC << 4;
                            func_001fd5e0((void *)w[0], D_00642C18);
                            func_001fd610((void *)w[0], 7);
                            func_001fd688((void *)w[0]);
                            if ((w[1] = func_001f31a8(D_003F3C60, 6))) {
                                func_001f3e90((void *)w[0], (void *)w[1]);
                                func_001f3e20((void *)w[1], (void *)w[0]);
                                if ((w[2] = func_001f31a8(D_003F3C30, 6))) {
                                    func_001f3e90((void *)w[1], (void *)w[2]);
                                    func_001f3e20((void *)w[2], (void *)w[1]);
                                }
                                func_001f3dc0((void *)w[0]);
                            }
                        }
                    }
                }
            }
        }
    }
done:
/*P*/
    func_00202fc0(o);
    sel = func_001fd518(o);
    j = func_001fd618(o);
    cur = func_001fd590(o);
    i = 0;
    a = o->x28;
    lim = o->xcc;
    cnt = o->xce + 1;
    func_001f8ba8(o);
/*Q*/
    for (; i < cnt && j < lim; ) {
        s32 v;
        s32 m;
        if (j == 0) v = D_00641BF0[D_00641BC4];
        else v = t[j + 24];
        m = 2;
        if (a) { if (j) m = i == sel; else m = i == sel; }
        func_002114f0(o, m, 0, cur, 166, v);
        cur += 28;
        j++;
        i++;
    }
    func_001f8f30();
}
#include "data/data_003F.h"

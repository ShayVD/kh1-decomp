#include "common.h"
#include "data/bss_0064.h"
/* Sections were separate scratch files; their local typedefs carry a _qN suffix and
   conflicting extern/prototype declarations use __asm__ labels so each function keeps
   the exact declarations it matched with. func_0022a698 rodata (0x491260) was verified
   with wqb03_rr.py in a copy without func_0021b6a0 (the tool puts all .rodata at one address). */

/* ---- faf38/match.c ---- */
typedef struct { u8 pad[0xc]; s32 xc; } PC_q1;
extern PC_q1 *D_006430E8;
extern s32 D_006430F8;
extern s32 D_00643100;
extern f32 D_002BBDFC;

/* ---- fb6a0/d.c ---- */
extern s32 D_006430F8;
extern s32 D_00643100;

/* rodata */

/* ---- fd860/MATCH_d860.c ---- */
s32 func_001f9438(void *, s32, s32, s32, s32, s32, u32);

/* ---- fdc40/MATCH_dc40.c ---- */

extern u8 *D_006431F0[3];
extern s32 D_00643200[3];
extern s32 D_00643278[3]; /* src/data/bss_0064.c: s32 D_00643278[0x6] */
extern u8 D_00643128[];
extern u8 D_00643160[];
extern u8 D_006431B0[];
extern u8 D_00643210[];
extern s32 D_003F50E0[];
extern s32 D_003F5C38;
u16 func_0021dc08_q4(s32) __asm__("func_0021dc08");
char *func_0021dc20_q4(s32) __asm__("func_0021dc20");
s32 func_001eb038(s32);
s32 func_00131c30(s32);
s32 func_00207180(s32);
void func_00207000(s32);
void func_00207048(s32);
s32 func_00207088(s32);
void func_002072e0(s32);
void func_00207298(s32);
s32 strcmp(const char *, const char *);

void func_0021dc40(void) {
    s32 i, j;
    s32 *c;
    char *p, *s;
    c = D_00643200;
    D_006431F0[0] = D_00643128;
    c[0] = 0;
    for (i = 0; i < 49; i++) {
        if (func_001eb038(func_0021dc08_q4(i))) { s32 n = D_00643200[0]; D_00643200[0] = n + 1; D_00643128[n] = i; }
    }
    D_006431F0[1] = D_00643160;
    D_00643200[1] = 0;
    for (; i < 127; i++) {
        if (func_001eb038(func_0021dc08_q4(i))) { D_00643160[D_00643200[1]] = i; D_00643200[1]++; }
    }
    D_006431F0[2] = D_006431B0;
    D_00643200[2] = 0;
    for (; i < 184; i++) {
        if (func_001eb038(func_0021dc08_q4(i)) || func_00131c30(D_003F50E0[i])) D_00643210[D_00643200[2]] = 1;
        else D_00643210[D_00643200[2]] = 0;
        D_006431B0[D_00643200[2]] = i;
        D_00643200[2]++;
    }
    for (j = D_00643200[0] - 1; j >= 0; j--) {
        if (!func_00207180(func_0021dc08_q4(D_00643128[j]))) {
            func_00207000(0);
            goto l1;
        }
    }
    func_00207048(0);
l1:
    for (j = D_00643200[1] - 1; j >= 0; j--) {
        if (!func_00207180(func_0021dc08_q4(D_00643160[j]))) {
            func_00207000(1);
            goto l2;
        }
    }
    func_00207048(1);
l2:
    for (j = D_00643200[2] - 1; j >= 0; j--) {
        if (!func_00207180(func_0021dc08_q4(D_006431B0[j])) && D_00643210[j]) {
            func_00207000(2);
            goto l3;
        }
    }
    func_00207048(2);
l3:
    if (func_00207088(0) && func_00207088(1) && func_00207088(2)) {
        func_002072e0(2);
    } else {
        func_00207298(2);
    }
    s = func_0021dc20_q4(0);
    for (i = 1; i < 49; i++) {
        p = s;
        s = func_0021dc20_q4(i);
        if (i != 38 && strcmp(p, s) && !func_001eb038(func_0021dc08_q4(i - 1))) goto z0;
    }
    if (!func_001eb038(func_0021dc08_q4(48))) { z0: D_00643278[0] = 0; }
    else D_00643278[0] = 1;
    s = func_0021dc20_q4(49);
    for (i = 50; i < 127; i++) {
        p = s;
        s = func_0021dc20_q4(i);
        if (strcmp(p, s) && !func_001eb038(func_0021dc08_q4(i - 1))) goto z1;
    }
    if (!func_001eb038(func_0021dc08_q4(126))) { z1: D_00643278[1] = 0; }
    else D_00643278[1] = 1;
    for (i = 127; i < 184; i++) {
        if (!func_001eb038(func_0021dc08_q4(i)) && !func_00131c30(D_003F50E0[i])) { D_00643278[2] = 0; goto e2; }
    }
    D_00643278[2] = 1;
e2:
    if (D_00643278[0] && D_00643278[1] && D_00643278[2]) D_003F5C38 = 1;
    else D_003F5C38 = 0;
}

/* ---- fed60/MATCH_ed60.c ---- */

typedef struct { u8 pad0[0xc4]; u16 xc4; u8 padc6[0xcc - 0xc6]; s16 xcc, xce; u8 padd0[0xd8 - 0xd0]; s16 xd8, xda; } Obj_q5;
#include "data/pieces/D_00425BC8.h"
typedef struct { u8 pad0[0x24]; s32 x24; u8 pad28[0x40 - 0x28]; s32 x40; u8 pad44[0xa0 - 0x44]; f32 xa0; u8 pada4[0xd8 - 0xa4]; s16 xd8, xda; } Eff_q5;
typedef struct { u8 pad0[0x10]; s32 x10; } S3110_q5;
extern S3110_q5 *D_00643110; /* src/data/bss_0064.c: s32 D_00643110 */
extern s32 D_0064324C;
extern s32 D_00643268[];
extern s32 D_00643258[];
extern s32 D_00643200_q5[] __asm__("D_00643200");
extern u8 D_00643210[];
extern u8 *D_006431F0_q5[] __asm__("D_006431F0");
extern s32 D_00643274;
extern s32 D_00643250;
extern u8 D_003F5E60[];
extern s32 D_003F50E0[];
extern u16 D_003E9104;
extern s32 D_003F34F8;
s32 func_001f42b8(void);
void func_001f3758(s32);
void func_0011d768(s32);
void func_0021e538(void);
void func_001fd858(Obj_q5 *);
s32 func_001fd518(Obj_q5 *);
s32 func_001fd668(Obj_q5 *);
s32 func_001fe5a0(Obj_q5 *);
Eff_q5 *func_001f31a8(void *, s32);
s32 func_00131c30(s32);
s32 func_0021dc08(s32);
void func_001f3e48(Eff_q5 *, Obj_q5 *);
s32 func_0021dc38(s32);
#include "vm/script_vm.h"
s32 func_0010eb78(s32);
void func_00203788(Obj_q5 *, s32, s32, s32, u32);
s32 func_0021dc20(s32);
s32 func_001effc0(s32);
s32 func_001fade0(Obj_q5 *, s32, s32, s32, s32, u32);
void func_001f94f0(Obj_q5 *, s32, s32, s32, s32, s32, u32);
s32 func_00207180(s32);
void func_00207428(Obj_q5 *, s32, s32);
void func_0021b820(void);
void func_0021c4f8(Obj_q5 *);

extern u16 D_003F5C90[];
s32 func_0021b800(s32);
CONTEXT_ONLY s32 func_0021dc08(s32 i) { return D_003F5C90[i]; }
CONTEXT_ONLY s32 func_0021dc20(s32 i) { return func_0021b800(i + 81); }
CONTEXT_ONLY s32 func_0021dc38(s32 i) { return i; }
void func_0021ed60(Obj_q5 *o) {
    s32 ch, n, k, v, j, i, y, dy, c, x, cnt;
    Eff_q5 *p;
    if (func_001f42b8()) {
        if (D_00425BC8->x8 & 0x4000) {
            func_001f3758(D_00643110->x10);
            func_0011d768(3);
            goto draw;
        }
        func_0021e538();
        func_001fd858(o);
        D_00643268[D_0064324C] = func_001fd518(o);
        ch = 0;
        n = o->xd8;
        if (D_00425BC8->x10 & 0x80000480) {
            if (o->xda > 0) {
                o->xda -= 16;
                ch = 1;
            }
        } else if (D_00425BC8->x10 & 0x20000820) {
            if (o->xda < (n - 1) << 4) {
                o->xda += 16;
                ch = 1;
            }
        }
        D_00643258[D_0064324C] = func_001fd668(o);
        if (ch) {
            func_0011d768(1);
            k = D_00643200_q5[D_0064324C];
            if (k < 8 || D_00643258[D_0064324C] == n - 1) {
                v = (k - 1) % 8 + 1;
                o->xce = v;
                o->xcc = v;
            } else {
                o->xce = 8;
                o->xcc = 8;
            }
        }
        if (func_001fe5a0(o)) {
            if (D_0064324C == 2 && !D_00643210[D_00643258[2] * 8 + D_00643268[2]]) {
                func_0011d768(4);
                goto draw;
            }
            func_0011d768(2);
            D_00643274 = D_006431F0_q5[D_0064324C][D_00643258[D_0064324C] * 8 + D_00643268[D_0064324C]];
            func_001f3758(D_00643110->x10);
            p = func_001f31a8(D_003F5E60, 50);
            if (p) {
                p->x24 = func_00131c30(D_003F50E0[D_00643274]);
                p->x40 = func_0021dc08(D_00643274);
                func_001f3e48(p, o);
                { f32 f = D_003E9104; D_00643250 = 0; p->xa0 = f; }
                n = func_0010eb78((s32)func_001c2df0((s8 *)D_003F34F8, func_0021dc38(D_00643274)));
                p->xda = D_00643250 << 4;
                p->xd8 = (n + 1) / 2;
            }
        }
    }
draw:
    func_00203788(o, D_0064324C != 1 ? 372 : 329, 40, 486, 0x80C8C8C8);
    dy = (s16)o->xc4 >> 4;
    y = 116;
    for (i = 0, j = D_00643258[D_0064324C] * 8; i < 8 && j < D_00643200_q5[D_0064324C]; i++, j++) {
        c = D_006431F0_q5[D_0064324C][j];
        if (D_0064324C == 2 && !D_00643210[j]) {
            cnt = func_001effc0(func_0021dc20(c));
            x = 322;
            for (; cnt > 0; cnt--) x = func_001fade0(o, x, y, 41, 15, 0x40461E00);
        } else {
            func_001f94f0(o, 0, 322, y, func_0021dc20(D_006431F0_q5[D_0064324C][j]), 15, 0x80461E00);
            if (!func_00207180(func_0021dc08(c))) func_00207428(o, 450, y + 10);
        }
        y += dy;
    }
    func_0021b820();
    func_0021c4f8(o);
}

/* ---- f8e70/MATCH_8e70.c ---- */

typedef struct {
    s32 magic;
    s32 ver;
    s32 x8;
    s32 xC;
    s32 x10;
    char name[36];
    s32 x38;
} Save3C_q6;

typedef struct { s32 a, b, c, d; } S4_q6;
#include "data/pieces/D_003E8E08.h"
typedef struct O98_q6 {
    u8 pad[0xc];
    struct O98_q6 *xc;
    s32 x10;
    u8 pad14[0x24 - 0x14];
    union { s32 i; u16 h; } x24;
    u8 p0[0x90 - 0x28];
    s32 x90;
    u8 p1[0xa0 - 0x94];
    f32 xa0;
    u8 p2[0xb0 - 0xa4];
    s32 xb0;
    s32 xb4;
    u8 p3[0xba - 0xb8];
    s16 xba;
    s16 xbc;
    s16 xbe;
    s16 xc0;
    s16 xc2;
    s16 xc4;
    s16 xc6;
    s16 xc8;
    s16 xca;
    s16 xcc;
    s16 xce;
    u8 p5[0xd2 - 0xd0];
    s16 xd2;
    u8 p6[0xd8 - 0xd4];
    s16 xd8;
    s16 xda;
} O98_q6;
typedef struct { u8 pad[8]; s32 x8; s32 xc; u32 x10; } F8_q6;
extern F8_q6 *D_00425BC8_q6 __asm__("D_00425BC8");
extern s32 D_006469B0;
extern s32 D_006469B4;
extern u8 D_003F7210[];
extern s32 D_003F7228[];
extern s32 D_003F7230[];
#include "data/pieces/D_003F7238.h"
extern s32 D_003F7248[];
void func_0011d768(s32);
s32 func_001f42b8(void);
s32 func_001fe570(void *);
void func_001fdfd0(void *);
s32 func_001fd538(void *);
s32 func_001f9438_q6(void *, s32, s32, s32, s32, s32, s32) __asm__("func_001f9438");
void func_001f3708(void *, s32);
void func_0020bc48(s32, s32, s32);
void func_00201440(void *, s32, s32, s32, s32, s32, s32, void *, s32);
void func_002066b0(void *, s32, s32, s32, s32, s32);
void func_002053e8(void *, s32, s32, s32, s32, s32);
void func_002078f0(void *, s32, s32, s32, s32, s32, s32, s32, s32);
s32 func_001efbb8(s32);
s32 func_002192f8(void);
s32 func_00219348(void);
s32 func_00219380(void);
s32 func_002193b8(void);
s32 func_002193f0(void);
s32 func_00219428(void);
s32 func_00219458(s32);

#include "data/pieces/D_003F6E40.h"
extern s32 D_003F6F58[];
extern s32 D_006437C0;
extern s32 D_006437C4;
extern s32 D_006437C8[];
extern s32 D_006437D0[];
extern s32 D_006437DC;
extern s32 D_006437E4;
extern s32 D_006450C0[];
extern Save3C_q6 D_00645250[];
extern void *D_00646990;
s32 func_001ee428(s32);
s32 func_001ee440(s32);
void *func_001f31a8_q6(void *, s32) __asm__("func_001f31a8");
void func_001f3758_q6(void *) __asm__("func_001f3758");
void func_001f3d58(void *, s32);
void func_001f3dc0(void *);
void func_001f3e48_q6(void *, void *) __asm__("func_001f3e48");
void func_001f8ba8(void *);
void func_001f8f30(void);
s32 func_001f9e48(void *, s32, s32, s32, void *, s32, s32);
void func_001fb428(void *, s32, s32, s32, s32, s32, s32, s32, s32);
s32 func_001fd518_q6(void *) __asm__("func_001fd518");
s32 func_001fd548(void *);
s32 func_001fd590(void *);
s32 func_001fd618(void *);
void func_001fd858_q6(void *) __asm__("func_001fd858");
s32 func_001fe5a0_q6(void *) __asm__("func_001fe5a0");
void func_001ff488(void *, s32, s32, s32, s32, s32);
void func_00202fc0(void *);
void func_0020bd18(void *, s32);
void func_0020be10(s32);
void func_00229a10(void *);
void func_00233f18(void);
s32 func_00233f40(s32, s32);
void func_00233ff8(s32, s32);

typedef struct Nd_q6 { u8 pad[0x10]; struct Nd_q6 *x10; } Nd_q6;
typedef struct { s32 x0; u8 pad[0xc]; s32 x10; } C28_q6;
extern s32 D_006436D0;
extern s32 D_006436D4;
extern s32 D_006436F0;
extern s32 D_00643708;
extern s32 D_00643720[];
extern s32 D_00643730;
extern s32 D_0064373C;
extern s32 D_00643758;
extern s32 D_0064375C;
extern s32 D_00643760[];
extern u8 D_00643770[];
extern u8 D_00643778[];
extern s32 D_00643780[];
extern s32 D_00643790;
extern s32 D_00643794;
extern s32 D_0064379C;
#include "data/pieces/D_00304BE8.h"
#include "data/pieces/D_003E3D68.h"
extern s32 D_003F34C0;
#include "data/pieces/D_003F34C4.h"
extern s32 D_003F6E2C;
#include "data/pieces/D_00425C28.h"
extern u8 D_003F6C30[];
extern u8 D_003F6C00[];
extern u8 D_003F6BD0[];
extern u8 D_003F68F0[];
extern u8 D_003F68C0[];
extern u8 D_003F6860[];
extern u8 D_003F6C60[];
extern s32 D_003F6CC8[];
void func_001f3840(void *);
void func_00109278(void);
void func_00233ef8(s32);
void func_001f4040(void *, s32);
void func_001f40a0(void *, s32);
void func_001f4058(void *, s32);
void func_00223a30(void *);
void *func_001f3520(void *, s32);
void func_00228700(void *);
void func_001f37c0(void *, s32);
void *func_001f4468(void *);
void func_0020d1d8(void *);
void func_002075f8(void);
void func_00207830(void *, s32, s32, s32, s32, s32, s32);

extern void *D_00643718;
void func_00228e70(void *arg0) {
    O98_q6 *objs[3];
    s32 i, n;
    if ((n = D_003E3D68 - 1) != 0) {
        D_003F34C0 |= 2;
        for (i = 0; i < 4; i++) {
            D_00643760[i] = i;
            D_00643770[i] = (((u8 *)D_00304BE8) + 0x48E)[i];
            if (i == D_00643708 + 1) D_00643780[i] = 96; else D_00643780[i] = 32;
        }
        D_0064375C = 0;
        D_00643790 = 0;
        D_00643794 = 0;
        D_0064379C = 0;
        for (i = 0; i < 4; i++) {
            D_00643778[i] = (((u8 *)D_00304BE8) + 0x48E)[i];
        }
        objs[0] = func_001f31a8_q6(D_003F68F0, 6);
        if (objs[0]) {
            func_001f3e48_q6(objs[0], arg0);
            n = D_003E3D68;
            objs[0]->xcc = n;
            objs[0]->xba = n * 448 - 32;
            objs[0]->xce = n;
            if (D_00643708 >= n) {
                D_00643708 = 0;
            }
            objs[0]->xd2 = *(u16 *)&D_00643708 << 4;
            objs[1] = func_001f31a8_q6(D_003F68C0, 6);
            if (objs[1]) {
                func_001f3e48_q6(objs[1], objs[0]);
                func_001f3dc0(objs[0]);
            }
        }
    } else {
        func_0011d768(4);
        objs[0] = func_001f31a8_q6(D_003F6860, 6);
        if (objs[0]) {
            func_001f3e48_q6(objs[0], arg0);
            func_001f4058(objs[0], 1);
            func_001f3d58(objs[0], 6);
            func_00223a30(objs[0]);
        }
    }
    D_00643718 = arg0;
}

/* ---- fa698/noctx.c ---- */

typedef struct {
    s32 magic;
    s32 ver;
    s32 x8;
    s32 xC;
    s32 x10;
    char name[36];
    s32 x38;
} Save3C_q7;

typedef struct { s32 a, b, c, d; } S4_q7;
extern S4_q7 D_003E8E08_q7 __asm__("D_003E8E08");
typedef struct O98_q7 {
    u8 pad[0xc];
    struct O98_q7 *xc;
    s32 x10;
    u8 pad14[0x24 - 0x14];
    union { s32 i; u16 h; } x24;
    u8 p0[0x8c - 0x28];
    s32 x8c;
    s32 x90;
    u8 p1[0xa0 - 0x94];
    f32 xa0;
    u8 p2[0xb0 - 0xa4];
    s32 xb0;
    s32 xb4;
    u8 p3[0xba - 0xb8];
    s16 xba;
    s16 xbc;
    s16 xbe;
    s16 xc0;
    s16 xc2;
    s16 xc4;
    s16 xc6;
    s16 xc8;
    s16 xca;
    s16 xcc;
    s16 xce;
    s16 xd0;
    s16 xd2;
    u8 p6[0xd8 - 0xd4];
    s16 xd8;
    s16 xda;
} O98_q7;
typedef struct { u8 pad[8]; s32 x8; s32 xc; u32 x10; } F8_q7;
extern F8_q7 *D_00425BC8_q7 __asm__("D_00425BC8");
extern s32 D_006469B0;
extern s32 D_006469B4;
extern u8 D_003F7210[];
extern s32 D_003F7228[];
extern s32 D_003F7230[];
extern s32 D_003F7248[];
s32 func_0011d768_q7(s32) __asm__("func_0011d768");
s32 func_001f42b8(void);
s32 func_001fe570(void *);
void func_001fdfd0(void *);
s32 func_001fd538(void *);
s32 func_001f9438_q7(void *, s32, s32, s32, s32, s32, s32) __asm__("func_001f9438");
void func_001f3708(void *, s32);
void func_0020bc48(s32, s32, s32);
void func_00201440(void *, s32, s32, s32, s32, s32, s32, void *, s32);
void func_002066b0(void *, s32, s32, s32, s32, s32);
void func_002053e8(void *, s32, s32, s32, s32, s32);
void func_002078f0(void *, s32, s32, s32, s32, s32, s32, s32, s32);
s32 func_001efbb8(s32);
s32 func_002192f8(void);
s32 func_00219348(void);
s32 func_00219380(void);
s32 func_002193b8(void);
s32 func_002193f0(void);
s32 func_00219428(void);
s32 func_00219458(s32);

extern s32 D_003F6F58[];
extern s32 D_006437C0;
extern s32 D_006437C4;
extern s32 D_006437C8[];
extern s32 D_006437D0[];
extern s32 D_006437DC;
extern s32 D_006437E4;
typedef struct { u8 pad0[8]; u64 x8; u8 pad10[0x10]; u8 name[0x20]; } Dir40_q7;
extern Dir40_q7 *D_006450C0_q7[] __asm__("D_006450C0");
extern Save3C_q7 D_00645250_q7[] __asm__("D_00645250");
extern void *D_00646990;
s32 func_001ee428(s32);
s32 func_001ee440(s32);
void *func_001f31a8_q7(void *, s32) __asm__("func_001f31a8");
void func_001f3758_q7(void *) __asm__("func_001f3758");
void func_001f3d58(void *, s32);
void func_001f3dc0(void *);
void func_001f3e48_q7(void *, void *) __asm__("func_001f3e48");
void func_001f8ba8(void *);
void func_001f8f30(void);
s32 func_001f9e48(void *, s32, s32, s32, void *, s32, s32);
void func_001fb428(void *, s32, s32, s32, s32, s32, s32, s32, s32);
s32 func_001fd518_q7(void *) __asm__("func_001fd518");
s32 func_001fd548(void *);
s32 func_001fd590(void *);
s32 func_001fd618(void *);
void func_001fd858_q7(void *) __asm__("func_001fd858");
s32 func_001fe5a0_q7(void *) __asm__("func_001fe5a0");
void func_001ff488(void *, s32, s32, s32, s32, s32);
void func_00202fc0(void *);
void func_0020bd18(void *, s32);
void func_0020be10(s32);
void func_00229a10(void *);
void func_00233f18(void);
s32 func_00233f40(s32, s32);
void func_00233ff8(s32, s32);

extern s32 D_003F7778;
extern f32 D_002BBDFC;
extern s32 D_006469D0;
extern s32 D_006469D4;
extern f32 D_006469D8;
extern s32 D_006469DC;
extern f32 D_006469E0;
extern s32 D_006469E4;
extern f32 D_006469E8;
extern s32 D_006469EC;
extern f32 D_006469F0;
extern s32 D_006469F4;
extern f32 D_006469F8;
extern char D_003F76C0[][20];
extern s32 D_003F7710[];
void func_001fd648(void *, s32);
void func_001f3840_q7(void *) __asm__("func_001f3840");
f32 sinf(f32);

typedef struct {
    u8 pad[0x18c0];
    s32 flags[100];
    Save3C_q7 saves[1];
} Sys1E10_q7;
extern Sys1E10_q7 D_00351E10;
extern s32 D_006436D4;
extern s32 D_006436D8[];
extern s32 D_006436E0[];
extern s32 D_006436E8;
extern s32 D_00643734;
extern s32 D_0064373C;
extern void *D_00643740;
extern s32 D_00643750;
extern u8 D_003F6980[];
extern u8 D_003F69B0[];
extern u8 D_003F6AD0[];
#include "data/pieces/D_003F6920.h"
extern s32 D_003F6B28[];
void *func_001f3520(void *, s32);
void func_001f4058(void *, s32);
void func_002246f8(void *);
void func_00224920(void *);
void func_00224ad8(void *);
void func_00225288(void *);

extern s32 D_006437D8;
extern s32 D_006437E0;
extern s32 D_006469A4;
s32 D_006469A8 ALIGNED(8);
s32 D_006469AC ALIGNED(4);
extern s32 D_00425C18;
#include "data/pieces/D_00425C1C.h"
extern s32 D_00425C20;
extern s32 D_00425CAC;
Dir40_q7 D_00643800[0x63] ALIGNED(64);
s32 D_00646994 ALIGNED(4);
extern s32 D_00646998;
u32 D_0064699C ALIGNED(4);
extern u32 D_006469A0; /* src/data/bss_0064.c: s32 D_006469A0 */
s32 D_0064524C ALIGNED(4);
extern u8 D_003F6F70[];
extern u8 D_003F6F30[];
extern u8 D_003F8380[];
extern s32 D_003F6E24;
extern s32 D_003F720C;
s32 func_00233d08(s32);
s32 func_00234018(s32, s32, s32);
s32 func_00234148(s32, s32, char *, void *, s32, s32);
s32 func_00234860(void);
s32 func_002348d0(void);
void *func_00233018(s32);
s32 func_002345a0(s32, s32, void *, void *, s32, s32);
void *func_00232fc8(s32);
void func_0022a3a0(void *);
void func_0022a5d8(void *);
void func_0022a518(void *);
void func_00233f68(s32, s32);
void func_00233ef8(s32);
void func_001f36b8(void *);
void func_0020bda8(s32);
void func_00110448(s32);
void func_001f3840_q7(void *) __asm__("func_001f3840");
void func_00223980(s32, s32, s32);
void func_001edaf0(s32);

/* rodata */
void func_0022a698(O98_q7 *arg0) {
    O98_q7 *objs[2];
    s32 ok[99];
    s32 num, i, n, bi, y, w;
    u64 best, t;
    Dir40_q7 *p;

    num = -1;
    if (func_001f42b8()) {
        switch (D_006437DC) {
        case 0:
            if (func_00233f40(D_006437C4, 0)) {
                func_00233ff8(D_006437C4, 0);
                D_006469A4 = 0;
            }
            D_006437E0 = 410;
            func_00234018(D_006437C4, 0, 0);
            D_006437E4 = 0;
            D_006437DC = 1;
            break;
        case 1:
            D_006437E0 = 410;
            if (func_00233d08(0)) break;
            D_006469A8 = D_00425C18;
            D_006469AC = D_00425C20;
            D_006437DC = 2;
            break;
        case 2:
            D_006437E0 = 410;
            func_00234018(D_006437C4, 0, 0);
            D_006437DC = 3;
            break;
        case 3:
            D_006437E0 = 410;
            if (func_00233d08(0)) break;
            if (func_00233f40(D_006437C4, 0)) {
                func_00233ff8(D_006437C4, 0);
                D_006437E0 = 415;
                func_0022a3a0(arg0);
                break;
            }
            if (D_006469A8 == 2 && D_00425C18 == 2 && D_006469AC == 0 && D_00425C20 == 0) {
                D_006437DC = 4;
                break;
            }
        tail3:
            if (D_006469A4) {
                D_006437DC = 18;
            } else {
                D_006437DC = 6;
            }
            break;
        case 4:
            D_006437E0 = 410;
            func_00234018(D_006437C4, 0, 0);
            D_006437DC = 5;
            break;
        case 5:
            D_006437E0 = 410;
            if (func_00233d08(0)) break;
            if (func_00233f40(D_006437C4, 0)) {
                func_00233ff8(D_006437C4, 0);
                D_006437E0 = 415;
                func_0022a3a0(arg0);
                break;
            }
            if (D_00425C20 != 0) {
                goto tail3;
            }
            D_006437E0 = 413;
            func_0022a5d8(arg0);
            break;
        case 6:
            D_006437E0 = 410;
            func_00234148(D_006437C4, 0, "BISLPS-25198-??", D_00643800, 99, 0);
            D_006437DC = 7;
            break;
        case 7:
            D_006437E0 = 410;
            if (func_00233d08(0)) break;
            if (func_00234860() == 4) {
                D_006437E0 = 415;
                D_006437DC = 8;
            } else {
                D_006437DC = 10;
            }
            break;
        case 8:
            D_006437E0 = 415;
            func_00234018(D_006437C4, 0, 0);
            D_006437DC = 9;
            break;
        case 9:
            D_006437E0 = 415;
            if (func_00233d08(0)) break;
            func_00233f68(D_006437C4, 0);
            func_00233ff8(D_006437C4, 0);
            func_0022a3a0(arg0);
            break;
        case 10:
            D_006437E0 = 410;
            for (n = 0; n < 99; n++) {
                D_006450C0_q7[n] = 0;
            }
            n = D_00425CAC;
            p = D_00643800;
            D_00646994 = n;
            if (n > 0) {
                do {
                    D_006450C0_q7[(p->name[13] - '0') * 10 + (p->name[14] - '0') - 1] = p;
                    p++;
                } while (--n);
            }
            D_006437DC = 11;
            break;
        case 11:
            D_006437E0 = 410;
            D_0064524C = 0;
            D_006437DC = 12;
            break;
        case 12:
            D_006437E0 = 411;
            while (D_006450C0_q7[D_0064524C] == 0) {
                if (++D_0064524C >= 99) {
                    D_006437DC = 16;
                    D_006437E0 = 410;
                    goto end;
                }
            }
            num = D_0064524C + 1;
            D_00645250_q7[D_0064524C].magic = 0;
            func_002345a0(D_006437C4, 0, func_00233018(num), &D_00645250_q7[D_0064524C], 60, 0);
            D_006437DC = 13;
            break;
        case 13:
            num = D_0064524C + 1;
            D_006437E0 = 411;
            if (func_00233d08(0)) break;
            if (func_002348d0() == 7) {
                D_006437E0 = 415;
                num = -1;
                D_006437DC = 14;
            } else if (++D_0064524C >= 99) {
                D_006437DC = 16;
            } else {
                D_006437DC = 12;
            }
            break;
        case 14:
            D_006437E0 = 415;
            func_00234018(D_006437C4, 0, 0);
            D_006437DC = 15;
            break;
        case 15:
            D_006437E0 = 415;
            if (func_00233d08(0)) break;
            func_00233f68(D_006437C4, 0);
            func_00233ff8(D_006437C4, 0);
            func_0022a3a0(arg0);
            break;
        case 16:
            D_006437E0 = 410;
            func_00234018(D_006437C4, 0, 0);
            D_006437DC = 17;
            break;
        case 17:
            D_006437E0 = 410;
            if (func_00233d08(0)) break;
            if (func_00233f40(D_006437C4, 0)) {
                func_00233ff8(D_006437C4, 0);
                D_006437E0 = 415;
                func_0022a3a0(arg0);
                break;
            }
            D_006437DC = 18;
            break;
        case 18:
            D_006437E0 = 0;
            D_00646998 = 0;
            for (i = 0; i < 99; i++) {
                if (D_006450C0_q7[i]) {
                    if (D_00645250_q7[i].magic == 0x5153484B && D_00645250_q7[i].ver == 0x01317F14) {
                        if ((u32)D_00645250_q7[i].x38 >= 3) {
                            D_00645250_q7[i].x38 = 2;
                        }
                        ok[i] = 1;
                        D_00646998++;
                    } else {
                        ok[i] = 0;
                    }
                }
            }
            D_0064699C = D_00425C1C;
            D_006469A0 = D_00425C1C / 132;
            D_006437E4 = 1;
            D_006469A4 = 1;
            D_006437D8 = D_006437C4;
            D_006437DC = 19;
            func_00233ef8(0);
            func_0011d768_q7(55);
            func_001f36b8((void *)arg0->x10);
            objs[0] = func_001f31a8_q7(D_003F6F70, 6);
            if (!objs[0]) break;
            func_001f3e48_q7(objs[0], arg0);
            func_0020bda8(16);
            bi = 0;
            best = 0;
            for (i = 0; i < 99; i++) {
                if (D_006450C0_q7[i] && ok[i]) {
                    t = D_006450C0_q7[i]->x8 & ~0xFFULL;
                    if (best < t) {
                        best = t;
                        bi = i;
                    }
                }
            }
            if (bi < 96) {
                D_006437C8[D_006437C4] = bi;
                D_006437D0[D_006437C4] = 0;
            } else {
                D_006437C8[D_006437C4] = 95;
                D_006437D0[D_006437C4] = bi - 95;
            }
            objs[0]->xd0 = D_006437C8[D_006437C4] << 4;
            objs[0]->xd2 = D_006437D0[D_006437C4] << 4;
            D_006437C0 = D_006437C8[D_006437C4] + D_006437D0[D_006437C4];
            objs[1] = func_001f31a8_q7(D_003F6F30, 6);
            if (objs[1]) {
                func_001f3e48_q7(objs[1], objs[0]);
                func_001f3dc0(objs[0]);
            }
            break;
        case 19:
            break;
        case 20:
            D_006437E0 = 414;
            func_002345a0(D_006437C4, 0, func_00232fc8(D_006437C0 + 1), D_003F8380, 0x16c00, 0);
            D_006437DC = 21;
            break;
        case 21:
            D_006437E0 = 414;
            if (func_00233d08(0)) break;
            if (func_002348d0()) {
                D_006437E0 = 412;
                if (func_002348d0() == 7) {
                    D_006437DC = 22;
                } else {
                    func_0022a518(arg0);
                }
            } else {
                func_0011d768_q7(55);
                func_00110448(D_00645250_q7[D_006437C0].x10);
                func_001f3840_q7(arg0);
                func_0020be10(16);
                D_003F720C = 1;
                D_003F6E24 = 1;
                func_00223980(D_006437C4, D_006437C8[D_006437C4], D_006437D0[D_006437C4]);
                func_001edaf0(func_00219380() == 0);
            }
            break;
        case 22:
            D_006437E0 = 412;
            func_00234018(D_006437C4, 0, 0);
            D_006437DC = 23;
            break;
        case 23:
            D_006437E0 = 412;
            if (func_00233d08(0)) break;
            func_00233f68(D_006437C4, 0);
            func_00233ff8(D_006437C4, 0);
            func_0022a3a0(arg0);
            break;
        }
    }
end:
    if (D_006437E0) {
        if (num != -1) {
            D_003E8E08_q7.a = num;
        }
        y = D_006437C4 * 28 + 83;
        w = func_001f9438_q7(arg0, 0, 200, y - 7, D_006437E0, 15, 0x80399bff);
        func_002066b0(arg0, 0, y, 11, 0x001428c8, 0x801428c8);
        func_002066b0(arg0, 133, y, 63, 0x801428c8, 0x801428c8);
        func_002066b0(arg0, w + 4, y, 512 - w, 0x801428c8, 0x001428c8);
    }
}

/* ---- febf8/MATCH_ebf8.c ---- */

typedef struct {
    u8 pad00[0x21];
    u8 n;
    u8 items[0x74 - 0x22];
} EbMember_q8;
typedef struct {
    u8 pad000[4];
    EbMember_q8 m[10];
    u8 x48c;
    u8 x48d;
    u8 party[11];
    u8 cnt[1];
} EbSave_q8;
extern EbSave_q8 *D_00304BE8_q8 __asm__("D_00304BE8");
extern s32 *D_00646A0C;
extern s32 D_00646A18;
extern u32 D_00646A20;
extern s32 D_00646A28;
#include "data/pieces/D_003E3D6C.h"
extern EbMember_q8 *D_00647634; /* src/data/bss_0064.c: s32 D_00647634 */
extern s32 D_00647638;
extern u32 D_0064763C; /* src/data/bss_0064.c: s32 D_0064763C */
s32 func_001ee708(s32);
u32 func_001ef7a0(void);
s32 func_001ee9e0(s32);

void func_0022ebf8(s32 idx) {
    s32 id, i, n, r;
    EbMember_q8 *m;

    id = D_00646A0C[idx];
    D_00646A18 = id;
    D_0064763C = func_001ee708(id) * D_00646A28;
    if (func_001ef7a0() < D_0064763C) goto err;
    if (D_00646A20 < D_003E3D6C) {
        if (D_00646A28 == 1) {
        if (func_001ee9e0(id)) {
            m = &D_00304BE8_q8->m[D_00304BE8_q8->party[D_00646A20]];
            D_00647634 = m;
            n = m->n;
            for (i = 0; i < n; i++) {
                if (!m->items[i]) goto found;
            }
            D_00646A18 = -2;
            return;
        }
        D_00646A18 = -3;
        return;
        }
        D_00646A18 = -4;
        return;
    }
    if (D_00304BE8_q8->cnt[D_00646A18] == 99) {
        D_00646A18 = -2;
        return;
    }
    if (D_00304BE8_q8->cnt[D_00646A18] + D_00646A28 >= 100) {
        D_00646A18 = -4;
        return;
    }
    D_00647634 = 0;
    D_00647638 = D_00646A18;
    return;
found:
    D_00647638 = i;
    return;
err:
    D_00646A18 = -1;
}

#include "data/data_003F.h"
#include "data/data_0042.h"
#include "data/data_003E.h"
#include "data/pieces/D_002BBDFC.h"
#include "data/pieces/D_003F50E0.h"
#include "data/pieces/D_00425CAC.h"

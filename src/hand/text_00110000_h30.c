#include "common.h"
#include "data/pieces/D_002C5968.h"
#include "data/bss_004E.h"
#include "data/bss_004F.h"
typedef int u128 __attribute__((mode(TI)));
typedef struct { s32 id, x4, x8, handle, x10; u8 active, x15, kind, x17; } SndSlot;
typedef struct { s32 x0, x4, x8; } Slot12;
#include "data/types/text_00110000_h30.h"
extern s32 D_004E344C;
extern SndSlot *D_004E3450;
extern Slot12 *D_004E3454;
extern SndSlot D_004E3458[];
Slot12 D_004E3818[0x28] ALIGNED(8);
extern Pair D_004E39F8[];
void *func_001559f0(s32, s32);
typedef struct { s32 off, size; } Chunk;
typedef struct { u8 pad[16]; Chunk c[2]; } SndHdr;
extern s32 D_002C1368[];
extern void (*D_004E3430)(void);
s32 func_001ed128(s32, s32);
void func_001ed460(s32, void *, s32);
void func_001ed658(s32, void *, s32);
void *func_0011ef10(s32, void *);
s32 func_0011cba0(void);
extern V4 D_004E3A20;
extern V4 D_004E3A30;
typedef struct { u32 b0 : 1; u32 rest : 31; } Bits5958;
extern Bits5958 D_002C5958;
extern s32 D_004E3438, D_004E343C, D_004E3440;
extern s32 D_002C1378[];
extern s32 D_004E3448;
void func_0011c7c0(s32, s32, s32);
void func_0011c7a8(s32, s32, s32, s32, s32, s32);
int sprintf(char *, const char *, ...);
char *strcat(char *, const char *);
TNode *func_0011f058(TPool *, TNode *);
typedef struct {
    u16 active;
    u8 x2;
    u8 x3;
    u32 cur;
    u32 press;
    u32 release;
    u32 rep;
    u32 rep2;
    s32 x18;
    s32 t1;
    s32 t2;
    u8 pad24[12];
    V4 a[2];
    V4 b[2];
} PadState;
extern s32 D_002C5C24, D_002C5C28;
extern u8 D_002C5C38[];
s32 sceCdDiskReady(s32);
s32 sceCdRead(u32, u32, void *, void *);
s32 func_00269fd0(s32);
s32 func_0026aaa0(void);
void func_002672f8(f32 *, V4 *, f32 *);
void func_002675a8(f32 *, f32 *);
#include "data/pieces/D_002C5910.h"

extern s32 D_002BD150[];
extern s32 D_002BD160[];
s32 func_0011aa18(s32, s32, V4 *);

static inline void vsubv(f32 *d, f32 *a, f32 *b) {
    __asm__ volatile(
        "lqc2 $vf4, 0(%1)\n"
        "lqc2 $vf5, 0(%2)\n"
        "vsub.xyzw $vf6xyzw, $vf4xyzw, $vf5xyzw\n"
        "sqc2 $vf6, 0(%0)\n"
        "nop\n"
        : : "r"(d), "r"(a), "r"(b) : "memory");
}

static inline void vcross(f32 *d, f32 *a, f32 *b) {
    __asm__ volatile(
        "lqc2 $vf4, 0(%1)\n"
        "lqc2 $vf5, 0(%2)\n"
        "vopmula.xyz ACC, $vf4xyz, $vf5xyz\n"
        "vopmsub.xyz $vf6xyz, $vf5xyz, $vf4xyz\n"
        "vsub.w $vf6w, $vf6w, $vf6w\n"
        "sqc2 $vf6, 0(%0)\n"
        "nop\n"
        : : "r"(d), "r"(a), "r"(b) : "memory");
}

s32 func_0011b908(s32 a0, s32 a1, f32 *a2) {
    V4 e, f, c;
    V4 pts[4];
    s32 i;
    s32 *idx;
    s32 n = func_0011aa18(a0, a1, pts);
    if (n == 3) idx = D_002BD150;
    else idx = D_002BD160;
    for (i = 0; i < n; i++) {
        vsubv(e, pts[idx[i]], pts[i]);
        vsubv(f, a2, pts[i]);
        vcross(c, e, f);
        if (c[1] < 0.0f) return 0;
    }
    return 1;
}

void func_0011c898(s32 a0) {
    s32 i;
    SndSlot *e;
    Slot12 *p;
    if (a0 == 0) {
        D_004E3450 = D_004E3458;
        D_004E3454 = D_004E3818;
        D_004E344C = 40;
    } else {
        D_004E3450 = func_001559f0(16, 1);
        D_004E3454 = func_001559f0(17, 1);
        D_004E344C = 128;
    }
    e = D_004E3450;
    p = D_004E3454;
    for (i = 0; i < D_004E344C; i++, e++, p++) {
        e->active = 0;
        p->x0 = 0;
        p->x4 = 0;
        p->x8 = 0;
    }
    for (i = 0; i < 4; i++) {
        D_004E39F8[i].a = 0;
        D_004E39F8[i].b = 0;
    }
}

void func_0011cbe0(s32 a0, SndHdr *a1, s32 a2, void (*a3)(void)) {
    Chunk *c = &a1->c[0];
    s32 off0 = c->off, sz0 = c->size;
    s32 off1, sz1;
    u8 *p0, *p1;
    c = &a1->c[1];
    off1 = c->off; sz1 = c->size;
    D_004E3430 = a3;
    p0 = (u8 *)a1 + off0;
    if (((s32 *)(p1 = (u8 *)a1 + off1))[1] > 0x7547f) {
        func_001ed128(0, 0);
        func_001ed128(1, 0);
        func_001ed128(0, 1);
        func_001ed128(1, 1);
        D_002C1368[1] = D_002C1368[0] = -2;
        if (a0 == 1) {
            a0 = 0;
            goto skip;
        }
    }
    D_002C1368[a0] = a2;
    func_001ed128(0, a0);
    func_001ed128(1, a0);
skip:
    func_001ed460(a0, p0, sz0);
    func_001ed658(a0, p1, sz1);
    func_0011ef10(10000, func_0011cba0);
}

extern s32 D_002C1360;
void func_0011db50(s32 *, s32 *);

static inline f32 vdist(void *a, void *b) {
    f32 r;
    __asm__ volatile(
        "lqc2 $vf6, 0(%1)\n"
        "lqc2 $vf4, 0(%2)\n"
        "vsub.xyzw $vf5xyzw, $vf6xyzw, $vf4xyzw\n"
        "vmove.xyzw $vf4xyzw, $vf5xyzw\n"
        "vmul.xyz $vf5xyz, $vf4xyz, $vf5xyz\n"
        "vaddy.x $vf5x, $vf5x, $vf5y\n"
        "vaddz.x $vf5x, $vf5x, $vf5z\n"
        "vsqrt Q, $vf5x\n"
        "vwaitq\n"
        "vaddq.x $vf5x, $vf0x, Q\n"
        "qmfc2 $2, $vf5\n"
        "mtc1 $2, %0\n"
        : "=f"(r) : "r"(a), "r"(b) : "$2");
    return r;
}

void func_0011dcf0(void *a0, s32 *a1, s32 *a2) {
    f32 n = D_002C1360;
    f32 d;
    d = vdist(&D_004E3A20, a0);
    *a1 = 16383.0f - d * d / n;
    d = vdist(&D_004E3A30, a0);
    *a2 = 16383.0f - d * d / n;
    func_0011db50(a1, a2);
}

#include "data/pieces/D_002BBDE0.h"
#include "data/pieces/D_002BC140.h"
extern V4 D_002C1320, D_002C1330, D_002C1340, D_002C1350;
void func_00267440(V4 *, s32);

void func_0011ddd0(void) {
    V4 m[4];
    func_00267440(m, D_002BC140);
    if (D_002BBDE0 == 3) {
        func_002672f8(D_004E3A30, m, D_002C1350);
        func_002672f8(D_004E3A20, m, D_002C1340);
        return;
    }
    func_002672f8(D_004E3A30, m, D_002C1330);
    func_002672f8(D_004E3A20, m, D_002C1320);
    D_004E3A20[2] = D_004E3A30[2] = 1000.0f;
}

extern s32 D_004E3A18;
s32 func_00157090(void);
s32 func_001ecd08(s32, s32, s32);

s32 func_0011e248(s32 a0) {
    s32 i, r;
    Pair *p;
    if (func_00157090()) return 8;
    if (a0 == 0) {
        if (D_004E3A18) return 9;
        r = func_001ecd08(-1, -1, 0);
        if (r == 0) {
            for (i = 3; i >= 0; i--) D_004E39F8[i].a = 0;
        }
        return r;
    }
    p = D_004E39F8;
    for (i = 0; i < 4; i++, p++) {
        if (p->a == a0) {
            if (p->b) return 9;
            r = func_001ecd08(-1, -1, a0);
            if (r == 0) p->a = 0;
            return r;
        }
    }
    return 0;
}

extern s32 D_004E3A1C;
s32 func_001ecb08(s32, s32, s32);

s32 func_0011e368(s32 a0, s32 a1) {
    s32 i, r;
    Slot12 *p = D_004E3454;
    if (a0 == -1) {
        if (D_004E3A1C) return 1;
        r = func_001ecb08(-8, -1, -1);
        if (r == 0) {
            for (i = 0; i < D_004E344C; i++) {
                p->x0 = 0;
                p->x4 = 0;
            }
        }
        return r;
    }
    for (i = 0; i < D_004E344C; i++, p++) {
        if (p->x0 == a0 && p->x4 == a1) {
            if (p->x8) return 1;
            r = func_001ecb08(-8, a0, a1);
            if (r == 0) {
                p->x0 = 0;
                p->x4 = 0;
            }
            return r;
        }
    }
    return 0;
}

extern s32 D_002BCDC4;
extern s32 D_002C1390;
extern s32 D_002C138C;
void func_0011e480(void);
void func_0011e4d0(void);

void func_0011e538(void) {
    if (D_002BCDC4) return;
    if (D_002C1390 == 0 && D_002C1368[0] != D_002C1368[1]) {
        if (D_002C5958.b0 == 1) {
            if (D_002C138C == 0) func_0011e480();
        } else {
            if (D_002C138C == 1) func_0011e4d0();
        }
    }
    D_002C138C = D_002C5958.b0;
}

extern s32 D_002C1364;

void func_0011e610(void) {
    if (D_002C5958.b0 == 1) {
        func_0011c7c0(0, 0, 240);
        if (D_004E3440 == 0) func_0011c7a8(1, 0x3000, 0x3000, 0, 0, 120);
        else func_0011c7a8(1, 0, D_004E3438, D_004E343C, 0, 120);
        D_002C1364 = 1;
    } else {
        func_0011c7c0(1, 0, 240);
        if (D_004E3440 == 0) func_0011c7a8(0, 0x3000, 0x3000, 0, 0, 120);
        else func_0011c7a8(0, 0, D_004E3438, D_004E343C, 0, 120);
        D_002C1364 = 0;
    }
}

void func_0011c7d8(s32);
void func_0011ca68(s32, char *);
void func_0011e758(void);
void func_0011e7c8(void);
s32 func_00120748(char *, s32, void (*)(void), s32);

void func_0011e7f8(void) {
    char buf[64];
    if (D_002C1368[0] != D_002C1378[0] && D_002C1378[0] != 0) {
        if (D_002C1368[1] == -2) func_0011c7d8(0);
        else func_0011c7c0(0, 0, 100);
        func_0011ca68(D_002C1378[0], buf);
        func_00120748(buf, D_004E3448, func_0011e7c8, 0);
        return;
    }
    func_0011e758();
}

#include "data/types/text_00110000_h30_p.h"
extern char D_0048D1A0[];
extern Str12 D_0048D1A8;
extern char D_0048D1B8[];

void func_0011eae0(s32 a0, char *a1) {
    char buf[80];
    sprintf(buf, D_0048D1A0, a0);
    if (buf[0] == ' ') {
        buf[0] = '0';
        if (buf[1] == ' ') {
            buf[1] = '0';
            if (buf[2] == ' ') buf[2] = '0';
        }
    }
    *(Str12 *)a1 = D_0048D1A8;
    strcat(a1, buf);
    strcat(a1, D_0048D1B8);
}

void func_0011ec08(s32 a0, s32 *a1, s32 a2, void (*a3)(void)) {
    D_004E3430 = a3;
    if (a1[1] > 0x7547f) {
        D_002C1368[1] = D_002C1368[0] = -2;
        func_001ed128(0, 0);
        func_001ed128(0, 1);
        if (a0 == 1) a0 = 0;
    } else {
        D_002C1368[a0] = -1;
        func_001ed128(0, a0);
    }
    func_001ed658(a0, a1, a2);
    func_0011ef10(10000, func_0011cba0);
}

typedef struct { u16 type; s16 f2; } NodeHd;
#include "data/pieces/D_002C58D0.h"
extern s32 D_002C5950;
extern s32 D_002C596C;
extern u8 D_004E3A48[];
u8 D_004E3A58[0x828] ALIGNED(8);
void sceVu0UnitMatrix(V4 *);
void func_0011efa8(void *, void *, s32, s32);
void func_0015ec68(void);
void func_00121c78(void);
void func_00122028(void);
void func_00120a70(void);
void func_00147628(void);
void func_0011fb00(void);
void func_0012fc20(void);
void func_0011eda8(void);

void func_0011edc8(void) {
    s32 i, j;
    sceVu0UnitMatrix(D_002C58D0);
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) D_002C5910[i][j] = 0;
    }
    D_002C5950 = 0;
    *(s32 *)&D_002C5958 = 0;
    D_002C596C = 0;
    func_0011efa8(D_004E3A48, D_004E3A58, 16, 128);
    func_0015ec68();
    func_00121c78();
    func_00122028();
    func_00120a70();
    func_00147628();
    func_0011fb00();
    func_0012fc20();
    ((NodeHd *)func_0011ef10(150000, func_0011eda8))->f2 = -1;
}

void func_0015f010(void);

s32 func_0011f130(TPool *p, u32 mask) {
    TNode *prev = 0;
    TNode *n;
    s32 cnt = 0;
    s32 r;
    for (n = p->head; n; n = n->next) {
        if ((n->mask & mask) != mask) continue;
        r = n->fn(n);
        func_0015f010();
        n->flags &= ~0x10;
        if (r & 4) {
            if (prev) {
                if (prev->next != n) prev = func_0011f058(p, n);
                prev->next = n->next;
            } else {
                p->head = n->next;
            }
            n->flags = 0;
        } else {
            prev = n;
        }
        cnt++;
        if (r & 8) break;
    }
    p->cur = 0;
    return cnt;
}

s32 func_0011f228(TPool *p, s32 (*fn)(TNode *)) {
    s32 cnt = 0;
    TNode *n, *prev;
    for (n = p->head; n; n = n->next, cnt++) {
        if ((n->flags | fn(n)) & 4) {
            prev = func_0011f058(p, n);
            if (prev) prev->next = n->next;
            else p->head = n->next;
            n->flags = 0;
        }
    }
    return cnt;
}

extern f32 D_002C5C20;
extern s32 D_002C5C2C;
extern PadState D_002C5AD0[2];
extern PadState D_002C5BB0;
#include "data/pieces/D_002C58B0.h"
extern s32 D_004E4280, D_004E44F0;

void func_0011f988(void) {
    s32 i, j;
    PadState *p;
    D_002C5C20 = 60.0f;
    D_002C5C24 = 30;
    D_002C5C28 = 4;
    D_002C5C2C = 32;
    for (i = 0; i < 2; i++) {
        p = &D_002C5AD0[i];
        p->rep = 0;
        p->press = 0;
        p->cur = 0;
        p->active = 0;
        p->x3 = 0;
        p->x2 = 0;
        for (j = 0; j < 2; j++) {
            func_002675a8(p->a[j], &D_002C58B0.x);
            func_002675a8(p->b[j], &D_002C58B0.x);
        }
    }
    D_002C5BB0.rep = 0;
    D_002C5BB0.press = 0;
    D_002C5BB0.cur = 0;
    D_004E4280 = 0;
    D_004E44F0 = 0;
}

void func_0011fd40(void);

void func_0011fd60(u32 lsn, u32 n, void *buf) {
    do {
        while (sceCdDiskReady(1) != 2 || !sceCdRead(lsn, n, buf, D_002C5C38)) func_0011fd40();
        while (func_00269fd0(1)) func_0011fd40();
    } while (func_0026aaa0());
}

extern s32 D_002C5C3C, D_002C5C40;
extern s32 D_004F3208;
extern char D_00351E10[], D_004F2A00[];
s32 func_001ecfb0(void);
int strncmp(const char *, const char *, u32);

void func_0011fec0(void) {
    if (func_001ecfb0() == 1) {
        if (D_002C5C3C > 30) {
            (*(volatile Fl_2c5968 *)&D_002C5968).b1 = 1;
            return;
        }
        D_002C5C3C++;
        return;
    }
    if ((*(volatile Fl_2c5968 *)&D_002C5968).b1) {
        if (D_002C5C40 > 0) {
            D_002C5C40--;
            return;
        }
        func_0011fd60(D_004F3208, 1, D_00351E10);
        if (strncmp(D_00351E10, D_004F2A00, 2048)) {
            D_002C5C40 = 60;
            return;
        }
    }
    D_002C5C3C = 0;
    (*(volatile Fl_2c5968 *)&D_002C5968).b1 = 0;
}
#ifdef KH1_OVL_FIXUPS
#endif

extern char D_0048D278[] __attribute__((aligned(8)));
#include "data/bss_004E_mixed.h"
#include "data/bss_004F_mixed.h"
#include "data/bss_004F_typed.h"
#include "data/data_002B.h"
#include "data/data_002C.h"
#include "data/data_0035.h"
#include "data/data_0049.h"
#include "data/data_0048.h"
#include "data/pieces/D_002C1378.h"
#include "data/pieces/D_002C1368.h"
#include "data/pieces/D_002C1320.h"
#include "data/pieces/D_002C1330.h"
#include "data/pieces/D_002C1340.h"
#include "data/pieces/D_002C1350.h"
#include "data/pieces/D_0048D1A8.h"

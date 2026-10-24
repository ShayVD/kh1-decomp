/* The target's gauge (docs/modules.md "Session 46"), 0x00246570-0x00246cf0.
 * D_00668370 (TgtGauge): state, alpha, the value and the maximum, the
 * frame's and the bar's sprites.  func_00246a70 (called from marker.c's
 * func_0023c1b0 with the lock-on target's numbers) shows it for this frame;
 * func_00246aa8 is the draw hook (func_00246bc8, the set up, registers it
 * and builds the sprites from D_0045D6E0): it fades the gauge in and out
 * by D_002BBDFC / 5 and draws it (func_00246750) at (16, 24) (65 or 80 by
 * func_002485f0's bits, 28 lower while the sign is on) with its own drawing
 * environment D_00668120: a frame as wide as half the maximum (at most 150,
 * func_002466e8) and the value in up to five bars of 300 (func_00246658),
 * each sprite resized with func_00246708.  func_00246a60 is the HUD's step
 * (off).  "The target's HP" is a guess from its caller; not proved by a
 * boot. */
#include "common.h"
#include "data/pieces/D_004268B0.h"
#include "data/pieces/D_004267F0.h"
#include "data/pieces/D_002BBDFC.h"

typedef struct { s32 a, b, c, d; } Q4;
typedef struct { u64 a; s32 unk8; u8 pad[0xC0 - 12]; } Blk;
typedef struct {
    u32 state;
    f32 t;
    s32 x8;
    s32 xc;
    s32 x10;
    u8 pad14[0x20 - 0x14];
    Blk b20;
    Blk bE0;
    Blk b1A0;
    Blk b260[3];
    Blk b4A0;
    Blk b560;
    Blk b620[5];
    Blk b9E0;
    s32 xaa0;
    s32 xaa4;
    s32 xaa8;
    u8 padaac[4];
} TgtGauge;
typedef struct { u8 pad[0x60]; Q4 q[4]; Q4 r[4]; } Panel;
typedef struct { u8 pad[0x60]; u64 unk60; u8 pad68[0xE0 - 0x68]; u64 unkE0; u8 tail[0x160 - 0xE8]; } Q;

extern TgtGauge D_00668370; /* src/data/bss_0066.c: s32 D_00668370[0x2ac] */
Panel D_00668290 ALIGNED(16);
Q D_00668120 ALIGNED(32);
Q4 *D_00668284 ALIGNED(4);
extern Q4 *D_00668280;
extern Q4 D_00351E10[];
extern f32 D_002BBDFC;
extern u8 D_0045D6E0[];
extern u8 D_0045E190[];
extern u8 D_0045E198[];
extern u8 D_0045E1A0[];
extern u8 D_0045E1A8[];
extern u8 D_0045E1B8[];
extern u8 D_0045E1C0[];
extern u8 D_0045E1C8[];
extern u8 D_0045E1E0[];
void func_0011ef10(s32, void *);
s32 func_0011ef38(void *);
void func_00237018(void *, s32, s32);
void func_002370c8(void *);
Q4 *func_002388b8(void *, s32, Q4 *);
void func_0024aa48(void *, void *, void *);
void func_0024aac8(void *);
void func_0024af40(void *, void *, void *);
void *memset(void *, s32, u32);
s32 func_002485f0(void);
s32 func_0023cfc8(void);

void func_00246570(Blk *a0, void *a1, s32 dx, s32 dy, f32 s) {
    s32 i;
    Panel *d = &D_00668290;
    func_0024aa48(a0, d, a1);
    for (i = 0; i < 4; i++) { s32 *r = &d->r[i].b; r[-1] += dx << 4; r[0] += dy << 4; }
    for (i = 0; i < 4; i++) {
        D_00668290.q[i].d = D_00668290.q[i].d * s;
    }
    D_00668280 = func_002388b8(&D_00668290, 1, D_00668280);
}

void func_00246658(s32 x, s32 *out) {
    s32 t[5];
    s32 i;
    for (i = 0; i < 5; i++) out[i] = 0;
    for (i = 0; i < 5; i++) {
        if (x >= 0) {
            t[i] = x + 1;
            if (x + 1 > 300) t[i] = 300;
            x -= 300;
            out[i] = t[i] / 2;
        }
    }
}

s32 func_002466e8(s32 a) {
    s32 v = a / 2;
    if (v > 150)
        v = 150;
    return v;
}

void func_00246708(Blk *d, Blk *s, s32 v) {
    *d = *s;
    d->unk8 = v;
}

/* func_00246aa8 passes four arguments; only the first is read. */
void func_00246750(s32 a0, s32 a1, s32 a2, f32 a3) {
    s32 t[5];
    Blk blk;
    TgtGauge *p;
    s32 y = 24;
    s32 i, n, c;
    Blk *q;
    Blk *bp;
    func_002370c8(&D_00668120);
    D_00668120.unkE0 = 5;
    D_00668120.unk60 = 0x30003;
    func_00237018(&D_00668120, 22, 1);
    D_00668284 = D_00351E10;
    D_00668280 = D_00351E10 + 1;
    p = &D_00668370;
    if (func_002485f0() & 2) y = 80;
    else if (func_002485f0() & 1) y = 65;
    if (func_0023cfc8()) y += 28;
    func_00246570(&p->b20, (*(u8 (*)[0x30])&D_004268B0), 16, y, p->t);
    for (i = 0; i < 3; i++) func_00246570(&p->b260[i], D_004267F0, 16, y, p->t);
    n = func_002466e8(p->x10);
    c = n < 150;
    bp = &blk;
    q = &p->bE0;
    if (c) {
        func_00246708(bp, q, n);
        func_00246570(bp, (*(u8 (*)[0x30])&D_004268B0), 16, y, p->t);
    } else func_00246570(q, (*(u8 (*)[0x30])&D_004268B0), 16, y, p->t);
    q = &p->b4A0;
    if (c) {
        func_00246708(bp, q, n);
        func_00246570(bp, D_004267F0, 16, y, p->t);
    } else func_00246570(q, D_004267F0, 16, y, p->t);
    func_00246658(a0, t);
    for (i = 0; i < 5; i++) {
        func_00246708(&blk, &p->b620[i], t[i]);
        func_00246570(&blk, D_004267F0, 16, y, p->t);
    }
    func_00246570(&p->b1A0, (*(u8 (*)[0x30])&D_004268B0), n + 44, y, p->t);
    func_00246570(&p->b560, D_004267F0, n + 44, y, p->t);
    for (i = 4; i >= 0; i--) if (t[i] > 0) break;
    if (i > 0) func_00246570(&p->b9E0, D_004267F0, t[i] + 44, y, p->t);
    func_00237018(D_00668284, D_00668280 - D_00668284, 1);
}

void func_00246a60(void) {
    D_00668370.state = 0;
}

void func_00246a70(s32 a0, s32 a1, s32 a2, s32 a3) {
    D_00668370.xc = a2;
    D_00668370.x10 = a3;
    D_00668370.xaa4 = a0;
    D_00668370.xaa8 = a1;
    D_00668370.xaa0 = 1;
    if (D_00668370.state == 0) {
        D_00668370.state = 1;
    }
}

s32 func_00246aa8(void) {
    TgtGauge *p = &D_00668370;
    s32 f = p->xaa0;
    p->xaa0 = 0;
    switch (p->state) {
    case 0:
        return 0;
    case 1:
        p->t = 0.0f;
        p->state++;
        break;
    case 2:
        p->t += D_002BBDFC * 0.199999988079071044921875f;
        if (p->t >= 1.0f) {
            p->t = 1.0f;
            p->state++;
        }
        break;
    case 3:
        if (f == 0) p->state++;
        break;
    case 4:
        p->state++;
        p->t = 1.0f;
        break;
    case 5:
        p->t -= D_002BBDFC * 0.199999988079071044921875f;
        if (p->t <= 0.0f) {
            p->t = 0.0f;
            p->state = 0;
        }
        break;
    }
    func_00246750(p->xc, p->x10, f, p->t);
    return 0;
}

void func_00246bc8(void) {
    memset(&D_00668370, 0, 0xAB0);
    func_0024aac8(D_0045D6E0);
    func_0024af40(D_0045E190, &D_00668370.b20, D_0045D6E0);
    func_0024af40(D_0045E198, &D_00668370.bE0, D_0045D6E0);
    func_0024af40(D_0045E1A0, &D_00668370.b1A0, D_0045D6E0);
    func_0024af40(D_0045E1A8, D_00668370.b260, D_0045D6E0);
    func_0024af40(D_0045E1B8, &D_00668370.b4A0, D_0045D6E0);
    func_0024af40(D_0045E1C0, &D_00668370.b560, D_0045D6E0);
    func_0024af40(D_0045E1C8, D_00668370.b620, D_0045D6E0);
    func_0024af40(D_0045E1E0, &D_00668370.b9E0, D_0045D6E0);
    if (func_0011ef38(func_00246aa8) == 0) {
        func_0011ef10(0x28489, func_00246aa8);
    }
}

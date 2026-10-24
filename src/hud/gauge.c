/* The gauges (include/hud/gauge.h, docs/modules.md "Session 47"): the parts
 * built with the default flags.  The low warning's sound (func_0023d128 /
 * func_0023d1a0, sound 0x2D, D_00651E50.unk4120 while it plays), the angle's
 * eighth (func_0023d1e0), a slot's position (func_0023d528), the round gauge
 * draw (func_0023f688), kind 3's (func_00240118 / func_002403d0), the frame
 * sprite (func_002407b0), the party's slot for an actor (func_00240910, by
 * its party index) and its fades' flags (func_00240978, func_002409b0,
 * func_00242b00, func_00242b38), a fade's sprite (func_00240ae0), the
 * player's flash timer (func_00240b28, func_00241948), dropping the slots
 * whose actor is gone (func_00241560), the slots' set up (func_00241b60,
 * func_00241c00 kind 3's values), the set up of the gauges (func_00242a38:
 * the six sprite files, the table, the draw hook func_002416a8 at 0x29811)
 * and small entry points (func_00242b68 ... func_00242bf0).  D_00652888,
 * D_00652898, D_00654570 and D_00655264 are fields of D_00651E50 defined as
 * their own variables (ent[0].unkA18, ent[0].unkA28, ent[3] and
 * ent[3].unkAA0.unk254); they keep those names. Session 69: D_00651E50 is one
 * definition here (func_00242a38 clears all 0x4130 bytes; on the host the
 * table had no definition and the three fields were separate objects), the
 * three names are declared inside it (vita-port-plan 5.1i). */
#include "common.h"
#include "hud/gauge.h"
#include "data/data_0045.h"
#include "data/pieces/D_00454A20.h"
#include "data/pieces/D_002BBDFC.h"
#include "data/pieces/D_002C5958.h"
#include "data/pieces/D_00426850.h"
#include "data/pieces/D_0044A830.h"
#include "data/pieces/D_0044C5A0.h"
#include "data/pieces/D_0044DFD0.h"
#include "data/pieces/D_0044F380.h"
#include "data/pieces/D_0044F4D0.h"
#include "data/pieces/D_00451040.h"

typedef struct { s32 x, y, z, w; } T16;

GaugeTbl D_00651E50 ALIGNED(16);
extern Gauge D_00651E70[];
extern s32 D_00652888[0x4]; /* D_00651E50.ent[0].unkA18 */
extern s32 D_00652898;      /* D_00651E50.ent[0].unkA28 */
extern s32 D_00654570[0x33d]; /* D_00651E50.ent[3] */
extern s32 D_00655264;
extern T16 D_00454600[];
extern T16 D_00454650[];
extern T16 D_00454680[];
extern T16 D_004546C0[];
extern T16 D_00454700[];
extern s32 D_00454A24;

void func_0011d790(s32, s32);
s32 func_0011d7c0(s32);
s32 func_0011ef10(s32, s32 (*)(void));
s32 func_0011ef38(s32 (*)(void));
s32 func_00122ff8(s32);
s32 func_0013c318(u16);
void *memset(void *, s32, u32);
void func_0024aac8(void *);
void func_0024ac08(void *, s32 *);
void func_0024ae00(void *);
/* gauge.nofill.c */
s32 func_0023d490(Gauge *);
QW *func_0023d700(UiSpr *, Tex_4268b0 *, s32, s32, QW *, f32);
/* gauge.nostrict.c */
QW *func_0023dd48(Gauge *, QW *);
QW *func_0023f0d8(Gauge *, QW *);
QW *func_0023f250(Gauge *, QW *);
QW *func_0023feb8(Gauge *, QW *);
QW *func_0023ff38(Gauge *, QW *);
QW *func_00240170(Gauge *, QW *);
QW *func_002401f0(Gauge *, QW *);
s32 func_00240810(Gauge *);
void func_002414a8(s32, s32);
s32 func_002416a8(void);
void func_00241d60(void);
void func_0023d1a0(void);

void func_0023d128(s32 arg0) {
    func_0011d790(0x2D, arg0);
}

void func_0023d1a0(void) {
    if (D_00651E50.unk4120 == 1) {
        func_0011d7c0(0x2D);
        D_00651E50.unk4120 = 0;
    }
}

s32 func_0023d1e0(f32 x) {
    return x / 0.7853981f; /* original constant is 0x3F490FD9 */
}

void func_0023d528(Gauge *o, s32 *p1, s32 *p2) {
    s32 r[2];
    register T16 *t KH1_REG("$5");
    switch (o->unk0) {
    case 0:
        t = D_00454650;
        p1[0] = D_00454600[0].x;
        p1[1] = D_00454600[0].y;
        goto idx;
    case 1:
        p1[0] = D_00454600[1].x;
        p1[1] = D_00454600[1].y;
        p2[0] = D_00454680[0].x;
        p2[1] = D_00454680[0].y;
        break;
    case 2:
        p1[0] = D_00454600[2].x;
        p1[1] = D_00454600[2].y;
        p2[0] = D_004546C0[0].x;
        p2[1] = D_004546C0[0].y;
        break;
    case 3:
        t = D_00454700;
        p1[0] = D_00454600[3].x;
        p1[1] = D_00454600[3].y;
        goto idx;
    case 4:
        t = D_00454650;
        p1[0] = D_00454600[4].x;
        p1[1] = D_00454600[4].y;
    idx:
        p2[0] = t[o->unk94].x;
        p2[1] = t[o->unk94].y;
        break;
    }
    if (o->unk9C != 0) {
        func_0024ac08(o->unk9C, r);
        p2[0] += r[0];
        p2[1] += r[1];
    }
}

QW *func_0023dfc0(Gauge *g, QW *r) {
    return func_0023dd48(g, r);
}

QW *func_0023f688(Gauge *g, QW *r) {
    s32 n;

    if (g->unk0 == 4) {
        n = D_00454A24;
    } else {
        n = g->unk4->unk6C->unk3C;
    }
    if (n == 0) {
        return r;
    }
    return func_0023f250(g, func_0023f0d8(g, r));
}

QW *func_00240118(Gauge *g, QW *r) {
    if (*g->unkA88 != 0.0f) {
        return func_0023ff38(g, func_0023feb8(g, r));
    }
    return r;
}

QW *func_002403d0(Gauge *g, QW *r) {
    return func_002401f0(g, func_00240170(g, r));
}

void func_002407b0(Gauge *e, s32 k) {
    switch (k) {
    case 0: e->unk9C = &e->unkA0[0]; break;
    case 1: e->unk9C = &e->unkA0[1]; break;
    case 2: e->unk9C = &e->unkA0[2]; break;
    case 3: e->unk9C = &e->unkA0[3]; break;
    case 4: e->unk9C = &e->unkA0[4]; break;
    }
    func_0024ae00(e->unk9C);
}

s32 func_002408d8(s32 i) {
    return func_00240810(&D_00651E70[i]);
}

Gauge *func_00240910(GActor *o) {
    Gauge *p;
    Gauge *r;
    s32 k = func_0013c318(o->unk130->unk4C);
    r = 0;
    if (k == 1 || k == 2) {
        if (k == 1) {
            if (D_00651E50.used[1]) { p = &D_00651E50.ent[1]; goto set; }
        } else {
            if (D_00651E50.used[2]) { p = &D_00651E50.ent[2]; goto set; }
        }
    }
    return r;
set:
    r = p;
    return r;
}

void func_00240978(GActor *a) {
    Gauge *g = func_00240910(a);
    if (g != NULL && g->unk780.unk250 == 0) {
        g->unk780.unk250 = 1;
    }
}

void func_002409b0(GActor *a) {
    Gauge *g = func_00240910(a);
    if (g != NULL) {
        g->unk780.unk254 = 1;
    }
}

QW *func_00240ae0(GFade *f, s32 x, s32 y, QW *r, f32 a) {
    if (!(f->unk250 != 0)) {
        return r;
    }
    return func_0023d700(f->unk0, D_00426850, x, y, r, a);
    return r;
}

s32 func_00240b28(Gauge *e) {
    s32 r;
    if (e->unkA30 > 0) {
        e->unkA30 = e->unkA30 - D_002BBDFC;
        r = 1;
    } else {
        r = 2;
        if (e->unkA24 == 0) r = 0;
    }
    return r;
}

void func_00241560(void) {
    s32 i;
    Gauge *p = D_00651E50.ent;
    for (i = 0; i < 5; i++, p++) {
        if (D_00651E50.used[i] && (u32)p->unk0 < 3) {
            if (!func_00122ff8((s32)p->unk4)) {
                D_00651E50.used[i] = 0;
                if (p->unk0 == 0) func_0023d1a0();
            }
        }
    }
}

void func_00241948(s32 i, s32 k) {
    Gauge *e; s32 on = D_00651E50.used[i]; e = &D_00651E50.ent[i];
    if (e->unk9C != 0) return;
    switch (k) {
    case 0:
        func_002407b0(e, 2);
        e->unkA30 = D_00454810;
        break;
    case 1:
        func_002407b0(e, 3);
        e->unkA30 = D_00454814;
        break;
    case 2:
        func_002407b0(e, 4);
        e->unkA30 = D_00454818;
        break;
    }
}

void func_00241a10(s32 i, s32 v) {
    *(s32 *)((s8 *)&D_00652888 + (i * 0xD00)) = v;
}

Gauge *func_00241b60(s32 i, s32 b) {
    Gauge *p;
    D_00651E50.used[i] = 1;
    D_00651E50.ent[i].unk4i = b;
    p = &D_00651E50.ent[i];
    p->unkA18 = 1;
    p->unk0 = i;
    p->unk98 = p->unk94 = func_0023d490(p);
    p->unkA24 = 0;
    p->unk520.unk250 = 0;
    p->unk780.unk250 = 0;
    p->unk9C = 0;
    func_002414a8(i, 1);
    return p;
}

void func_00241c00(f32 *a, f32 *b, f32 *c, f32 *d, s32 actor) {
    Gauge *g = func_00241b60(3, actor);
    g->unkA88 = a;
    g->unkA8C = b;
    g->unkA90 = c;
    g->unkA94 = d;
}

void func_00242a38(void) {
    func_0024aac8(&D_0044A830);
    func_0024aac8(&D_0044C5A0);
    func_0024aac8(&D_0044DFD0);
    func_0024aac8(&D_0044F380);
    func_0024aac8(&D_0044F4D0);
    func_0024aac8(&D_00451040);
    memset(&D_00651E50, 0, 0x4130);
    D_00651E50.unk4124 = (D_002C5958 >> 3) & 1;
    func_00241d60();
    if (func_0011ef38(func_002416a8) == 0) {
        func_0011ef10(0x29811, func_002416a8);
    }
}

void func_00242b00(GActor *a) {
    Gauge *g = func_00240910(a);
    if (g != NULL && g->unk520.unk250 == 0) {
        g->unk520.unk250 = 1;
    }
}

void func_00242b38(GActor *a) {
    Gauge *g = func_00240910(a);
    if (g != NULL) {
        g->unk520.unk254 = 1;
    }
}

void func_00242b68(s32 i) {
    D_00651E50.used[i] = 0;
    if (i == 4) {
        func_0023d1a0();
    }
}

void func_00242ba0(void) {
    if (D_00654570[828] == 0) {
        D_00654570[828] = 1;
    }
}

void func_00242bc0(void) {
    D_00655264 = 1;
}

void func_00242bd0(void) {
    D_00652898 = 0;
}

void func_00242be0(void) {
    D_00652898 = 1;
}

s32 func_00242bf0(s32 i) {
    return D_00651E50.used[i];
}

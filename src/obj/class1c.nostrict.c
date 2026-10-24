/* Object class 0x1C, without strict aliasing (docs/modules.md "Session 52"):
 * the handlers func_00153d28 registers in the class table D_00350D88
 * (func_0014f830(0x1C, ...): one 32-byte record of a parameter and seven
 * handlers per class) and their helpers. The rest is in class1c.c. Read from
 * the code, not proved by a boot. */
#include "common.h"
#include "data/pieces/D_002C58A0.h"
#include "data/types/nostrict_text_00140000_h34.h"
#include "data/pieces/D_00308CDC.h"
#include "data/pieces/D_00304BE8_s.h"
#include "platform/math.h"
#include "data/types/nostrict_text_00150000_h58_p.h"
#include "data/pieces/D_002E31B0.h"
#include "data/pieces/D_002E26A0.h"
#include "m2c.h"
#include "data/bss_0055.h"

/* func_00152688 (from hand/nostrict/text_00140000_h34.c). */
void *func_0014a4a8();
typedef struct { u64 x0; s32 x8; f32 xc; f32 x10[4]; } W34Eff2;
typedef struct { u8 pad[0x40]; W34Eff2 *x40; } W34S144;
typedef struct { u8 pad[0x68]; s32 x68; u8 pad6c[0x144 - 0x6c]; W34S144 *x144; } W34Pl11;
void func_00152648();
s32 func_0014a408(void);
s32 func_001477e0(s32);
void func_00135640(W34Eff2 *, W34Pl11 *);
W34Eff2 *func_00152688(W34Pl11 *o, s32 a, s32 b) {
    W34Eff2 *e;
    s32 id;
    func_00152648(o);
    id = func_0014a408();
    e = func_0014a4a8(a, id, func_001477e0(b));
    o->x144->x40 = e;
    e->x0 = (e->x0 & ~0x3000LL) | 0x100;
    e->x8 = o->x68;
    func_00135640(e, o);
    return e;
}

/* func_00152770 (from hand/nostrict/text_00140000_h34.c). */
void func_001315c0(void *, s32, f32 *, f32);
void func_002675a8(f32 *, f32 *);
void func_00147ed8(s32, s32, s32, f32 *);
typedef struct { s32 x0; f32 x4; f32 x8; f32 xc; f32 v[4]; } W34Qry;
void *func_001230a0(void *);
s32 func_0015bd78(W34Qry *, void *, s32);
void func_001354b8(W34Eff2 *, void *);
void func_00152730(W34Pl11 *);
void func_00152770(W34Pl11 *o) {
    f32 p[4] __attribute__((aligned(16)));
    W34Qry q __attribute__((aligned(16)));
    W34Eff2 *e;
    void *a;
    func_001315c0(o, 0x8003, p, 0.0f);
    func_00147ed8(o->x68, 4, -10000, p);
    e = func_0014a4a8(o, 0x80000000, func_001477e0(19));
    e->x0 = (e->x0 & ~0x3000LL) | 0x40;
    e->x8 = o->x68;
    func_002675a8(e->x10, p);
    q.x0 = 1;
    q.x4 = q.x8 = e->xc;
    func_002675a8(q.v, p);
    for (a = 0; (a = func_001230a0(a)); ) {
        if (a != o && func_0015bd78(&q, a, 0)) func_001354b8(e, a);
    }
    func_00152730(o);
}

/* func_00152928 (from hand/nostrict/text_00150000_s11_w22.c). */
typedef struct { union { u64 x; struct { u64 b0:2; u64 b2:2; u64 r:60; } b; } f; u8 pad8[8]; f32 v10[4]; } Q40;
typedef struct { s32 x0; s32 x4; u8 pad8[0x1c - 8]; f32 f1c; u32 x20; u8 pad24[0x40 - 0x24]; Q40 *x40; } P144;
typedef struct { u8 pad[4]; s32 x4; } X40;
typedef struct { u8 pad[0x4c]; u16 x4c; } C130h;
typedef struct {
    u8 pad0[8];
    s32 x8;
    u8 padc[0x30 - 0xc];
    f32 x30;
    u8 pad34[0x70 - 0x34];
    s32 x70;
    u8 pad74[0x90 - 0x74];
    u64 x90;
    u8 pad98[0x130 - 0x98];
    C130h *x130;
    u8 pad134[0x144 - 0x134];
    P144 *x144;
    u8 pad148[0x2cc - 0x148];
    s32 x2cc;
    u8 pad2d0[0x2dc - 0x2d0];
    u16 x2dc;
} Ah;
extern f32 D_002BBDFC;
void func_00152880(Ah *);
void func_0014aab0(Q40 *);
CONTEXT_ONLY void func_00152648(Ah *a) {
    if (a->x144->x40) {
        func_0014aab0(a->x144->x40);
        a->x144->x40 = 0;
    }
}
void func_00145008(Ah *, s32);
f32 func_00120c88(f32);
void func_00147138(Ah *, s32);
s32 func_00105c18(s32, u16);
#define func_001315c0 ((void (*)(Ah *, s32, f32, f32 *)) func_001315c0)
/* func_00152928 (hand/nostrict) */
void func_00152928(Ah *a) {
    P144 *p;
    s32 k;

    a->x144->f1c += D_002BBDFC;
    p = a->x144;
    if (300.0f <= p->f1c) {
        func_00152880(a);
        return;
    }
    if (a->x144->x40) {
        if (((X40 *)a->x144->x40)->x4 == 0) {
            if (a->x130->x4c != 204 && a->x144->x20 != 3) goto set;
            p = 0; /* dead set: kills the gcse PRE copy of p (move a1,a2) for CPROP pass 2 */
            if (a->x90 == 0) goto set;
        }
        func_00152648(a);
        func_00145008(a, 1);
        func_00152880(a);
        return;
    set:
        func_001315c0(a, 0x8003, 0.0f, a->x144->x40->v10);
        a->x144->x40->f.b.b2 = 1;
        p = a->x144;
    } else if (a->x130->x4c == 204 && a->x8) {
        func_00152880(a);
        return;
    }
    if (p->x20 == 3) a->x30 = func_00120c88(a->x30 - D_002BBDFC * 0.2617993727f);
    if (a->x70) return;
    func_00152648(a);
    switch (a->x144->x20) {
    case 0:
        k = 3;
        break;
    case 2:
        k = 1;
        break;
    case 3:
        func_00145008(a, 0);
        func_00152880(a);
        return;
    default:
        k = 2;
        break;
    }
    func_00147138(a, k);
    if ((a->x130->x4c == 204 ? 60.0f : 120.0f) <= a->x144->f1c || func_00105c18(a->x2cc, a->x2dc)) func_00152880(a);

    a->x144->x4 = 0;
}
#undef func_001315c0

/* func_00152e10 (from hand/nostrict/text_00140000_h34.c). */
s32 func_00130010(void *);
void func_0014f658(void *, s32);
extern W34Tbl D_0035193C[];
typedef struct { u64 x0; u8 pad8[0x14]; f32 x1c; s32 x20; u8 pad24[0xc]; f32 x30[4]; } W34S144b;
typedef struct { u8 pad[0x30]; f32 x30[4]; u8 pad40[0x120]; s32 x160; } W34Tg2;
typedef struct { u8 pad[0x10]; f32 x10[4]; u8 pad20[0x78]; W34Tg2 *x98; u8 pad9c[0x84]; f32 x120[4]; u8 pad130[0x14]; W34S144b *x144; } W34Pl13;
void func_00267530(f32 *, f32 *, f32 *);
void func_00152c28(W34Pl13 *, f32 *, f32);
void func_00152d50(W34Pl13 *, s32, f32 *);
void func_001586a8(s32);
void func_00152e10(W34Pl13 *o) {
    W34S144b *s;
    f32 v[4] __attribute__((aligned(16)));
    if (o->x98->x160 & 1) return;
    if (func_00130010(o->x98)) return;
    o->x144->x1c -= D_002BBDFC;
    if (o->x144->x1c > 0.0f) {
        func_001315c0(o->x98, 0x30, v, 0.0f);
        func_00267530(o->x120, v, o->x10);
        return;
    }
    func_0014f658(o->x98, 0);
    s = o->x144;
    {
        s32 i = s->x20;
        f32 f = D_0035193C[i].x0;
        if ((s32)(s->x0 >> 1) & 1) func_00152c28(o, s->x30, f);
        else func_00152d50(o, i, o->x98->x30);
    }
    func_001586a8(18);
}

/* func_00152f10 (from hand/nostrict/text_00140000_h34.c). */
typedef struct { u8 pad[4]; s32 x4; u8 pad8[0xc]; f32 x14; u8 pad18[4]; f32 x1c; u8 pad20[0x10]; f32 x30[4]; } W34S144c;
typedef struct { u8 pad[0x3c]; f32 x3c; u8 pad40[0x120]; s32 x160; } W34Tg3;
typedef struct { u32 x0; u8 pad4[0xc]; f32 x10[4]; u8 pad20[0x1c]; f32 x3c; u8 pad40[0x58]; W34Tg3 *x98; u8 pad9c[0xa8]; W34S144c *x144; } W34Pl14;
void func_00152f10(W34Pl14 *o) {
    f32 v[4] __attribute__((aligned(16)));
    o->x0 |= 0x20;
    if (o->x98->x160 & 1) return;
    if (func_00130010(o->x98)) return;
    o->x144->x1c -= D_002BBDFC;
    if (o->x144->x1c <= 0.0f) {
        o->x144->x4 = 2;
        o->x144->x14 = func_00120c88(o->x3c - o->x98->x3c);
        func_001315c0(o->x98, 0x30, v, 0.0f);
        func_00267530(o->x144->x30, o->x10, v);
        o->x144->x1c = 12.0f;
    }
}

/* func_00152ff8 (from hand/nostrict/text_00150000_h58.c). */
typedef S31b0_2e31b0 P8;
typedef struct {
    u32 w0; s32 w4; s32 w8; s32 wC; s32 x10; f32 f14; s32 x18; f32 f1c; s32 x20; u8 pad24[0xc]; V4 v30; f32 f40; f32 f44; s32 x48; s32 x4c;
} S144;
typedef struct {
    u8 pad0[0x10]; V4 pos; u8 pad20[0x10]; V4 v30; u8 pad40[0x30]; s32 x70; u8 pad74[0xf0]; s32 x164;
} S98;
typedef struct { u8 pad0[5]; u8 b5; u8 pad6[0xe]; struct { u8 pad0[1]; u8 b1; } *x14; } S134;
#define ACT_BODY(T144) \
    u32 w0; u8 pad4[4]; s32 x8; u8 padc[4]; V4 pos; V4 x20; V4 x30; V4 x40; u8 pad50[0x18]; s32 x68; struct { u8 pad[0x3c]; s32 x3c; } *x6c; s32 x70; P8 x74; u8 pad7c[0xc]; s32 x88; s32 x8c; u64 x90; S98 *x98; u8 pad9c[0x24]; V4 xc0; f32 xd0[4][4]; u8 pad110[0x10]; V4 x120; \
    struct { u8 pad[0x44]; f32 x44; s16 x48; u8 pad4a[2]; u16 x4c; } *x130; S134 *x134; u8 pad138[0xc]; T144 *x144; \
    struct { u8 pad[0x160]; V4 v160; } *x148; u8 pad14c[0x1d4]; V4 x320; u8 pad330[0x40]; u64 x370; u8 pad378[0x26]; u8 x39e; u8 pad39f[0x11]; f32 x3b0; u8 pad3b4[0xc]; V4 x3c0; u8 pad3d0[0x14]; f32 x3e4; u8 pad3e8[8]; V4 x3f0; s32 x400; u8 pad404[0x9c]; void *x4a0;
typedef struct Actor_52ff8 { ACT_BODY(S144) } Act;
void func_00267518(void *, void *, void *);
void func_00267560(void *, void *, f32);
void func_00137688(void *, f32);
s32 func_001375d8(void *);
s32 func_001443a8(void *);
#define func_001315c0 ((void (*)(void *, s32, void *, f32)) func_001315c0)
#define func_00267530 ((void (*)(void *, void *, void *)) func_00267530)
#define func_002675a8 ((void (*)(void *, void *)) func_002675a8)
#define func_00152d50 ((void (*)(void *, s32, void *)) func_00152d50)
/* ---- func_00152ff8 ---- */
void func_00152ff8(Act *a) {
    V4 tmp;
    V4 v;
    V4 buf;
    V4 *p = &a->x120;
    S98 *q;
    s32 k;

    func_001315c0(a->x98, 48, &buf, 0.0f);
    func_00267530(p, &buf, &a->pos);
    if (a->x144->f1c > 0.0f) {
        a->x144->f1c -= D_002BBDFC;
        if (a->x144->f1c > 0.0f) {
            func_00267560(&tmp, &a->x144->v30, a->x144->f1c / 12.0f);
            func_00267518(p, p, &tmp);
            a->w0 |= 0x20;
        }
    }
    func_00137688(a, a->x98->v30.w + a->x144->f14);
    if (a->x98->x70 == 28 && !func_001375d8(a->x98) && !a->x90 && !a->x8 && !func_001443a8(a->x98))
        return;
    func_0014f658(a, 0);
    q = a->x98;
    k = q->x164;
    if (k >= 72 && (k < 74 || k == 76)) {
        func_002675a8(&v, &q->v30);
    } else {
        func_00267530(&v, &D_002C58A0, &q->v30);
    }
    func_002675a8(p, (&D_002C58A0 + 1));
    func_00152d50(a, 1, &v);
}
#undef func_001315c0
#undef func_00267530
#undef func_002675a8
#undef func_00152d50

/* func_00153210 (from hand/nostrict/text_00150000.c). */
s32 func_0014f600(s32);
#define func_00152880 ((M2C_UNK (*)(void *)) func_00152880)
void func_00153210(void *arg0) {
    s32 temp_v0;
    void *temp_v1;

    temp_v0 = M2C_FIELD(arg0, s32 *, 8);
    if ((temp_v0 != 0) && (func_0014f600(temp_v0) != 0)) {
        temp_v1 = M2C_FIELD(arg0, void **, 0x144);
        M2C_FIELD(temp_v1, f32 *, 0x10) = (f32) (M2C_FIELD(temp_v1, f32 *, 0x10) + D_002BBDFC);
        if (M2C_FIELD(M2C_FIELD(arg0, void **, 0x144), f32 *, 0x10) >= 1.2e+02f) {
            func_00152880(arg0);
            return;
        }
        goto block_6;
    }
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x144), f32 *, 0x10) = 0.0f;
block_6:
    if (M2C_FIELD(arg0, s32 *, 0x8C) >= 2) {
        M2C_FIELD(M2C_FIELD(arg0, void **, 0x144), f32 *, 0x18) = 12.0f;
        M2C_FIELD(M2C_FIELD(arg0, void **, 0x144), s32 *, 4) = 5;
    }
}
#undef func_00152880

/* func_00153360 (from hand/nostrict/text_00140000_s6_07.c). */
typedef struct { u8 pad[4]; s32 x4; u8 pad8[8]; f32 v10[4]; } B3360;
typedef struct { u8 pad[0x30]; s32 x30; f32 x34; s32 x38; u8 pad3c[0x370 - 0x3c]; union { u64 x370; struct { u64 lo:44; u64 b44:1; u64 hi:19; } b370; }; } A3360;
f32 atan2f(f32, f32);
#define func_00152688 ((s32 (*)(A3360 *, s32, s32)) func_00152688)
#define func_00152d50 ((void (*)(A3360 *, s32, f32 *)) func_00152d50)
void func_00153360(A3360 *a, B3360 *b) {
    func_00152688(a, b->x4, 17);
    a->x370 = 0x100000000000ULL | a->x370;
    a->x30 = 0;
    a->x34 = atan2f(b->v10[0], b->v10[2]);
    a->x38 = 0;
    func_00152d50(a, 3, b->v10);
}
#undef func_00152688
#undef func_00152d50

/* func_00153418 (from hand/nostrict/text_00150000_h35.c). */
typedef union { u64 d; s32 w; struct { u32 lo; u32 x:6; u32 kind:4; u32 hi:22; } b; } F8_153418;
typedef struct { u8 pad[8]; F8_153418 f8; } Msg153418;
typedef struct { u8 pad[4]; s32 w4; s32 w8; s32 wC; } S144_153418;
typedef struct { u8 pad[0x144]; S144_153418 *p144; } Obj153418;
s32 func_00153300(Obj153418 *, Msg153418 *);
void func_001533d0(Obj153418 *, Msg153418 *);
#define func_00147138 ((void (*)(Obj153418 *, s32)) func_00147138)
#define func_00153360 ((void (*)(Obj153418 *, Msg153418 *)) func_00153360)
#define func_00145008 ((void (*)(Obj153418 *, s32)) func_00145008)
/* ---- func_00153418 ---- */
void func_00153418(Obj153418 *a, Msg153418 *m) {
    s32 n;
    if (m->f8.b.kind == 1) func_00147138(a, 4);
    if (func_00153300(a, m)) {
        func_00153360(a, m);
    } else {
        n = m->f8.w;
        if (n > 0) {
            a->p144->w8 += n;
            if (a->p144->w8 >= a->p144->wC) {
                func_00145008(a, 0);
                a->p144->w4 = 6;
            } else {
                func_001533d0(a, m);
            }
        }
    }
}
#undef func_00147138
#undef func_00153360
#undef func_00145008

/* func_00153668 (from hand/nostrict/text_00150000_h58.c). */
typedef struct Actor_53668 { ACT_BODY(S144) } Act_53668;
s32 func_0012cc38(s32, s32);
void func_0012ec60(struct Actor_53668 *, s32, void *);
void func_00130340(void *, s32, f32);
void *func_00130578(void *, s32, f32);
void func_0013dfa0(void *);
void func_00152520(void *, void *);
void func_00152dc8(void *, s32);
void func_00153c50();
#define func_002675a8 ((void (*)(void *, void *)) func_002675a8)
#define func_00152688 ((void (*)(void *, void *, s32)) func_00152688)
#define func_00153c50 ((void (*)(void *, struct Actor_53668 *)) func_00153c50)
/* ---- func_00153668 ---- */
s32 func_00153668(Act_53668 *a, S98 *b, s32 c) {
    S144 *p = a->x144;
    f32 d;
    s32 k;
    if (!p) return 0;
    switch (c) {
    case -1:
        k = p->w4;
        if (k) {
            if (k >= 0) {
                if (k < 3) func_0012cc38(0, 30);
            }
            break;
        }
        if (a->x8c) break;
        d = b->pos.y - a->pos.y;
        if (!(d > -10.0f && d < 110.0f)) break;
        switch (b->x70) {
        case 0:
            func_0012cc38(3, 28);
            break;
        case 6:
        case 28:
            if (p->w0 & 1) func_0012cc38(3, 29);
            break;
        }
        break;
    case 28:
        func_00152520(a, b);
        func_0013dfa0(b);
        a->x144->w4 = 1;
        a->x144->f1c = 12.0f;
        func_002675a8(&a->x3c0, (&D_002C58A0 + 1));
        func_0014f658(a, 4);
        break;
    case 29:
        func_00153c50(b, D_002E31B0.f0);
        break;
    case 30:
        func_00130340(b, 0x10000bb, 8.0f);
        func_00130578(b, 0x40000000, 0.0f);
        a->x74 = D_002E31B0;
        func_00152dc8(a, 2);
        if (a->x74.f0) {
            *(u64 *)&a->x144->w0 |= 2;
            func_0012ec60(a->x74.f0, a->x74.f4, &a->x144->v30);
        }
        func_00152688(a, b, a->x130->x4c == 0xcc ? 20 : 17);
        break;
    }
    return 0;
}
#undef func_002675a8
#undef func_00152688
#undef func_00153c50

/* func_001538d8 (from hand/nostrict/text_00150000_h35.c). */
typedef struct { u8 pad[0x44]; f32 f44; f32 f48; } S144_1538d8;
typedef struct { u8 pad[0xA4]; f32 fA4; f32 fA8; u8 padac[0x98]; S144_1538d8 *p144; } Obj1538d8;
f32 cosf(f32);
#define func_00152770 ((void (*)(Obj1538d8 *)) func_00152770)
/* ---- func_001538d8 ---- */
s32 func_001538d8(Obj1538d8 *a) {
    f32 s, c;
    a->p144->f44 -= D_002BBDFC;
    if (a->p144->f44 <= 0.0f) {
        func_00152770(a);
        return 1;
    }
    s = a->p144->f44 / 300.0f;
    s = s * -0.18849556148052216f + 0.20943952f;
    a->p144->f48 = func_00120c88(a->p144->f48 + s * D_002BBDFC);
    c = (cosf(a->p144->f48) + 1.0f) * 0.5f;
    a->fA8 = c;
    a->fA4 = c;
    return 0;
}
#undef func_00152770

/* func_001539c0 (from hand/nostrict/text_00150000_h58.c). */
typedef struct Actor_539c0 { ACT_BODY(S144) } Act_539c0;
typedef union { u64 d; s32 w; struct { u32 lo; u32 x:6; u32 kind:4; u32 hi:22; } b; } F8;
typedef struct { u8 pad[8]; F8 f8; } Msg;
void *func_00121e28(s32, void *);
void func_001528f0(void *);
void func_00146678(void *, void *);
extern void (*D_00351970[])(void *);
void func_00153500(Act_539c0 *, Msg *);
#define func_001538d8 ((s32 (*)(void *)) func_001538d8)
/* ---- func_001539c0 ---- */
void func_001539c0(Act_539c0 *a) {
    S144 *p = a->x144;
    S134 *q;
    s32 v;
    if (!p) {
        p = func_00121e28(80, &a->x144);
        p->w0 = 0;
        q = a->x134;
        if (q && q->b5 && (u8)(q->x14->b1 - 2) < 2) *(u64 *)&p->w0 |= 1;
        p->w4 = 0;
        p->w8 = 0;
        p->x10 = 0;
        p->x18 = 0;
        p->f40 = 0;
        p->f44 = 0;
        p->x4c = 0;
        switch (a->x130->x4c) {
        case 202:
            p->wC = 5;
            break;
        case 203:
            p->wC = 5;
            break;
        case 204:
            p->wC = 1;
            break;
        }
        a->x4a0 = func_00153668;
    }
    a->w0 &= ~0x20;
    if (p->f44 > 0.0f && func_001538d8(a)) return;
    if ((a->w0 & 0x400) && a->x70 == 2) {
        p->x20 = 4;
        func_001528f0(a);
    }
    func_00146678(a, a->x130->x4c == 203 ? (void *)func_00153500 : (void *)func_00153418);
    D_00351970[p->w4](a);
}
#undef func_001538d8

/* func_00153c50 (from hand/nostrict/text_00150000_h35.c). */
typedef struct { u64 d0; u8 pad[0x28]; u8 x30[0x10]; s32 w40; } S144_153c50;
typedef struct { u8 pad[0x74]; s32 w74; u8 pad78[0xCC]; S144_153c50 *p144; } S98_153c50;
typedef struct { u8 pad[0x98]; S98_153c50 *p98; } Obj153c50;
#define func_00130340 ((s32 (*)(void *, s32, f32)) func_00130340)
#define func_00130578 ((s32 (*)(void *, s32, f32)) func_00130578)
#define func_00152dc8 ((void (*)(S98_153c50 *, s32)) func_00152dc8)
#define func_001315c0 ((void (*)(s32, s32, void *, f32)) func_001315c0)
/* ---- func_00153c50 ---- */
void func_00153c50(Obj153c50 *a, s32 b) {
    func_00130340(a, 0x010000BA, 8.0f);
    func_00130578(a, 0x40000000, 0.0f);
    a->p98->w74 = b;
    func_00152dc8(a->p98, 0);
    if (b) {
        a->p98->p144->d0 |= 2;
        func_001315c0(b, 0x8003, a->p98->p144->x30, 0.0f);
    }
    a->p98->p144->w40 = 0;
}
#undef func_00130340
#undef func_00130578
#undef func_00152dc8
#undef func_001315c0


/* The class's action table (func_001539c0 calls D_00351970[p->w4]; phase 4,
 * tools/shift/define_ptr_tables.py; moved from hand/nostrict/text_00150000_h58.c). */
void func_00152880();
void func_00152928();
void func_00152e10();
void func_00152f10();
void func_001531c0();
void func_00153210();
void (*D_00351970[0x8])(void *) ALIGNED(16) = {
    (void *)func_00153210, (void *)func_00152f10, (void *)func_00152ff8, (void *)func_00152e10,
    (void *)func_00152928, (void *)func_001531c0, (void *)func_00152880, 0,
};

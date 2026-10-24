/* The command menu (a guess from the code): the command lists in D_002E2FD8
 * (func_0012cb78 / func_0012cc38 add an entry, func_0012cb40 sets one), the
 * submenu stack D_00524F40 over D_002E3170 (func_0012dce0 pushes,
 * func_0012dd38 pops), the pad input func_0012e1b0, the choice func_0012dea0
 * (an entry's record from func_001478c8; a beep through func_0011d768 when
 * it is greyed out), the per-frame update func_0012e4b0; then the action
 * command: its target and kind D_002E31B0 / D_002E31B8 (func_0012fb20 sets
 * them, func_0012fc20 clears, func_0012f868 picks the nearest target) and
 * the range test func_0012fa98. Flag mode: nostrict_nofill (the other modes
 * are in the sibling files). Read from the code, not proved by a boot
 * (docs/modules.md "Session 54"). */
#include "common.h"
#include "platform/vu.h"
#include "data/bss_0052.h"
#include "data/pieces/D_002E31B0.h"
#include "data/pieces/D_002E319C.h"
#include "data/types/nostrict_nofill_text_00120000_h54.h"
#include "data/pieces/D_002E31A4.h"
#include "data/pieces/D_002E31B8.h"
#include "data/pieces/D_002E3170.h"
#include "data/pieces/D_002E31A0.h"
#include "data/pieces/D_002E2780.h"

/* func_0012dea0 (from hand/nostrict_nofill/text_00120000_h54.c). */
typedef struct { s32 f0, f4, f8, fc; s32 n; u8 ids[0x24]; } Q38;
extern Q38 D_002E2FD8[7];
typedef S31b0_2e31b0 S31b0;
typedef struct { u32 b0:8; u32 b1:16; u32 b24:1; u32 flag:1; u32 rest:6; S31b0 f4; } St8;
typedef O8_2e319c O8;
extern St8 D_002E3190;
extern Q8 D_002E30B8;
extern Q8 **D_00524F40;
extern struct Actor *D_00524F58[];
extern s32 D_002E3160[];
extern O8 *func_001478c8(s32);
extern void func_0011d768(s32);
extern void func_0012dce0(Q38 *);
extern s32 func_0012dd70(O8 *);
extern s32 func_0012dd38_dea0(void) __asm__("func_0012dd38");
extern s32 func_00219288(void);
extern void func_0012fb20(S31b0 *, s32);
s32 func_0012dea0(Q8 *q, s32 i) {
    O8 *o;
    s32 f;
    S31b0 tmp;
    if (q->f8 & (1 << i)) {
        if (D_002E3190.flag) func_0011d768(4);
        return 0;
    }
    o = func_001478c8(q->ids[i]);
    if (o->f8 > 0) {
        q->f34 = i;
        func_0012dce0(&D_002E2FD8[o->f8]);
        return 0;
    }
    f = 0;
    if (q->f0 == 4) {
        if (q == &D_002E30B8) tmp.f0 = D_00524F58[i];
        else tmp.f0 = (struct Actor *)D_002E3160[i];
        tmp.f4 = 0;
        q = D_00524F40[-1];
        o = func_001478c8(q->ids[q->f34]);
    } else if (D_002E31B8) {
        tmp = D_002E31B0;
        f = 1;
    } else {
        tmp.f0 = 0;
        tmp.f4 = 0;
    }
    if (!func_0012dd70(o)) return 0;
    if (f && func_00219288() != 1 && (o->f0 & 4)) {
        if (D_002E31B8 - 1 < 2u || D_002E31B8 == 4) func_0012fb20(&D_002E31B0, 4);
    }
    if (q->f0 == 2) (*(s32 *)&D_002E31A4) = D_00524F68[q->fc];
    D_002E3190.f4 = tmp;
    D_002E3190.b0 = o->f6;
    D_002E3190.b1 = o->f7;
    D_002E319C = o;
    while (D_00524F40 != D_002E3170) func_0012dd38_dea0();
    return 1;
}

/* func_0012e1b0 (from hand/nostrict_nofill/text_00120000_s10_r2_7.c). */
typedef struct { u32 x0; u32 x4; u32 x8; } Pad;
CONTEXT_ONLY Q8 *func_0012dd38(void) {
    Q8 **p = D_00524F40;
    if (p > D_002E3170) {
        *p = 0;
        D_00524F40 = --p;
    }
    return *p;
}
extern Q8 D_002E2FD8_0012e1b0[7] __asm__("D_002E2FD8");
#define D_002E2FD8 D_002E2FD8_0012e1b0
#define func_0012dce0 ((void (*)(Q8 *)) func_0012dce0)
/* func_0012e1b0 (hand/nostrict_nofill), s10 r2_7. From r2_1's 1w draft plus a CONTEXT_ONLY copy of the leaf func_0012dd38 above it:
   a call to a function defined earlier in the TU that cannot throw gets a REG_EH_REGION 0 note, so reorg's live scan (find_dead_or_set_registers)
   continues past the call instead of stopping at it (can_throw), sees v0 set by the call, and fills `beqz v0` non-annulled as the original. */
s32 func_0012e1b0(Pad *pad) {
    Q8 *q;
    Q8 *cur;
    O8 *o;
    u32 k;
    s32 r;
    s32 snd;

    D_00524F40 = D_002E3170;
    q = D_00524F40[1];
    if (q == 0 || q->n == 0 || ((*D_00524F40)->f8 & (1 << (*D_00524F40)->f34)))
        goto done;
    for (;;) {
    cur = *D_00524F40;
    o = func_001478c8(cur->ids[cur->f34]);
    if (q != &D_002E2FD8[o->f8])
        goto done;
    q = *++D_00524F40;
    if (q->fc >= 0) {
        if (q->fc >= q->n) q->fc = q->n - 1;
        if (q->f8 & (1 << q->fc))
            goto done;
    }
    q = D_00524F40[1];
    if (q && q->n && !((*D_00524F40)->f8 & (1 << (*D_00524F40)->f34)))
        continue;
        break;
    }
done:
    D_00524F40[1] = 0;
    q = *D_00524F40;
    if (q->fc < 0) return 1;
    r = 0;
    o = func_001478c8(q->ids[q->fc]);
    k = pad->x8;
    if (k == 0x100) {
        if (q->f8 & (1 << q->fc)) {
            func_0011d768(4);
        } else if (o->f8 > 0) {
            q->f34 = q->fc;
            func_0012dce0(&D_002E2FD8[o->f8]);
        }
    } else if (k == 0x80 || (k & 2)) {
        if (D_00524F40 > D_002E3170) {
            q = func_0012dd38();
            if ((pad->x8 & 2) && q->fc >= 0) q->fc = 0;
            func_0011d768(3);
        } else if (k & 0x80) {
            if (q->fc >= 0) q->fc = 0;
            func_0011d768(1);
        } else {
            r = 1;
        }
    } else if (k == 0x20) {
        s32 v = q->fc;
        if (v <= 0) v = q->n;
        q->fc = v - 1;
        goto one;
    } else if (k == 0x40) {
        if (q->fc < q->n - 1) q->fc = q->fc + 1;
        else q->fc = 0;
    one:
        func_0011d768(1);
    } else {
        r = 1;
    }
    D_002E319C = (*(O8 **)&D_002E31A0) = func_001478c8(q->ids[q->fc]);
    return r;
}
#undef D_002E2FD8
#undef func_0012dce0

/* func_0012f218 (from hand/nostrict_nofill/text_00120000_h54.c). */
typedef struct { f32 x, y, z, w; } V4;
typedef union { u64 x; struct { u32 lo0; u32 x32:3; u32 f35:1; u32 x36:1; u32 kind:2; u32 hi:25; } b; } F370b;
typedef struct { u8 pad[4]; u32 f4; } I9;
typedef struct Actor_2f218 { u8 pad[0x130]; I9 *f130; u8 p134[0x370-0x134]; F370b f370; } E9;
typedef struct { E9 *f0; s32 f4; } A9;
extern f32 func_0012ec60(E9 *, s32, f32 *);
extern f32 func_00120bf8(f32 *);
extern s32 func_0012eaf8(E9 *);
extern s32 func_0012f0f8(f32 *, f32 *, s32);
s32 func_0012f218(f32 *pos, A9 *a, s32 lim) {
    f32 tmp[4];
    f32 d[4];
    f32 r;
    s32 s, v;
    r = func_0012ec60(a->f0, a->f4, tmp);
    PlatVu0SubVector((V4 *)d, (V4 *)tmp, (V4 *)pos);
    r = func_00120bf8(d) - r;
    if (func_0012eaf8(a->f0) && r > 1200.0f) return -1;
    s = r;
    if (!(r > 0.0f)) s = 0;
    if (D_002E319C) {
        switch (a->f0->f370.b.kind) {
        case 1:
            v = D_002E319C->f9;
            if (v < 0) return -1;
            s |= v << 24;
            break;
        case 2:
            v = D_002E319C->fa;
            if (v < 0) return -1;
            s |= v << 24;
            break;
        case 0:
        case 3:
            v = D_002E319C->fb;
            if (v < 0) return -1;
            s |= v << 24;
            break;
        }
    }
    if (lim >= 0 && !(s < lim)) return -1;
    if (a->f0->f370.b.f35 && func_0012f0f8(&D_002E2780.x, tmp, 0)) return s;
    if (!func_0012f0f8(pos, tmp, 0)) return -1;
    if (func_0012eaf8(a->f0)) s |= 0x10000;
    return s;
}

/* func_0012f560 (from hand/nostrict_nofill/text_00120000_h54.c). */
extern S31b0 *D_00525288;
extern S31b0 D_00524F80[];
void func_0012f560(S31b0 *v) {
    if (D_00525288 == 0) {
        D_00525288 = D_00524F80;
        D_0052528C = 0;
    } else {
        D_00525288++;
    }
    *D_00525288 = *v;
    D_0052528C++;
}

/* func_0012f690 (from hand/nostrict_nofill/text_00120000_h54.c). */
void func_0012f690(S31b0 *out) {
    s32 n = D_0052528C;
    if (n == 1) {
        out->f0 = 0;
        return;
    }
    if (D_00525288 == D_00524F80) {
        S31b0 *q = D_00525288 - 1;
        D_00525288 = q + n;
    } else {
        D_00525288--;
    }
    *out = *D_00525288;
}

/* func_0012f700 (from hand/nostrict_nofill/text_00120000_h54.c). */
typedef struct Actor_2f700 { u8 pad[0x130]; I9 *f130; u8 p134[0x370-0x134]; F370b f370; } E9_2f700;
typedef struct { E9_2f700 *f0; s32 f4; } A9_2f700;
extern s32 func_0012f3d0(A9_2f700 *);
extern s32 func_0012f040(E9_2f700 *, s32);
extern s32 func_002192c0(void);
extern void func_0012fc58(void);
extern void func_0012f5c0(S31b0 *);
void func_0012f700(Q8 *q) {
    S31b0 cur; cur.f0 = 0;
    switch (D_002E31B8) {
    case 0: if (q->f8 & 0x400) func_0012f3d0((A9_2f700 *)&cur); break;
    case 1: case 2: case 4:
        if (q->f8 & 0x400) { if (func_0012f040(D_002E31B0.f0, D_002E31B0.f4)) cur = D_002E31B0; }
        break;
    case 3:
        if (func_002192c0() == 1) { if (!(q->f4 & 0x400)) goto snd; }
        else if (q->f8 & 0x400) { snd: func_0011d768(69); func_0012fc58(); break; }
        if (q->f8 & 0x800) func_0012f5c0(&cur);
        else if (q->f8 & 0x20000) func_0012f690(&cur);
        break;
    }
    if (cur.f0) { if (!D_00525288) func_0012f560(&cur); func_0012fb20(&cur, 3); }
}


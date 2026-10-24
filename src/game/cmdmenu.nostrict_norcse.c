/* The command menu (a guess from the code): the command lists in D_002E2FD8
 * (func_0012cb78 / func_0012cc38 add an entry, func_0012cb40 sets one), the
 * submenu stack D_00524F40 over D_002E3170 (func_0012dce0 pushes,
 * func_0012dd38 pops), the pad input func_0012e1b0, the choice func_0012dea0
 * (an entry's record from func_001478c8; a beep through func_0011d768 when
 * it is greyed out), the per-frame update func_0012e4b0; then the action
 * command: its target and kind D_002E31B0 / D_002E31B8 (func_0012fb20 sets
 * them, func_0012fc20 clears, func_0012f868 picks the nearest target) and
 * the range test func_0012fa98. Flag mode: nostrict_norcse (the other modes
 * are in the sibling files). Read from the code, not proved by a boot
 * (docs/modules.md "Session 54"). */
#include "common.h"
#include "data/bss_0052.h"
#include "data/pieces/D_002E31B0.h"
#include "data/pieces/D_00304BE8_s.h"

/* func_0012d468 (from hand/nostrict_norcse/text_00120000_s7_w3.c). */
typedef struct { s32 f0, f4, f8, fc; s32 n; u8 ids[0x24]; } Q38;
typedef S31b0_2e31b0 S31b0;
typedef struct { u16 f0; u8 p2[0xc]; u16 fe; } O8;
extern Q38 D_002E2FD8[7];
extern s32 func_0013c188(s32, s32);
extern s32 func_00132fe0(s32);
extern s32 func_00133000(s32, s32);
extern O8 *func_001478c8(s32);
extern s32 func_00122ff8(struct Actor *);
extern f32 func_0012ed88(s32, S31b0 *, void *, void *);
extern u32 D_00524F44;
CONTEXT_ONLY void func_0012cb40(Q38 *a, s32 i, u8 v) {
    u32 m;
    a->ids[i] = v;
    m = ~(1 << i);
    a->f4 &= m;
    a->f8 &= m;
}
CONTEXT_ONLY void func_0012ccb0(s32 i) {
    u32 m = 1 << i;
    D_002E2FD8[0].f4 |= m;
    D_002E2FD8[0].f8 |= m;
    D_00524F44 &= ~m;
}
extern void func_0012d188(s32, u32 *);
CONTEXT_ONLY void func_0012d368(s32 a0, u32 *a1, s32 *fl) {
    Q38 *d = &D_002E2FD8[5];
    s32 mask = -1;
    s32 i;
    for (i = 0; i < 3; i++) {
        s32 id = D_00304BE8->x844[i];
        if (id == -1) {
            d->ids[i] = 66;
        } else {
            d->ids[i] = id * 3 + func_00132fe0(id) + 6;
            if (fl[id]) mask &= ~(1 << i);
            D_00524F50 = 1;
        }
    }
    d->f4 = d->f8 = mask;
}
/* func_0012d468 matches in hand/nostrict only with -fno-rerun-cse-after-loop (without it: s4/s6 swap, 6w). Includes CONTEXT_ONLY func_0012cb40, func_0012ccb0, func_0012d368. */
void func_0012d468(s32 a0, u32 *a1) {
    s32 v0[4];
    f32 v1[4];
    s32 list[8];
    s32 fl[8];
    s32 mask, n, i, k;
    O8 *o;
    Q38 *q;
    Q38 *base;

    D_00524F50 = 0;
    if (D_00304BE8->f874 & 8) return;
    base = D_002E2FD8;
    mask = -1;
    n = 0;
    i = 0;
    do {
        if (func_0013c188(0, i)) {
            k = func_00132fe0(i);
            base[1].ids[n] = i * 3 + k + 6;
            list[n] = i;
            n++;
            fl[i] = 0;
        }
        i++;
    } while (i < 7);
    q = &D_002E2FD8[1];
    q->n = n;
    if ((*a1 >> 5) & 1) {
        i = 0;
        if (n > 0) {
            do {
                k = list[i];
                if (func_00133000(a0, k)) {
                    o = func_001478c8(q->ids[i]);
                    if (func_00122ff8(D_002E31B0.f0) && (o->f0 & 8)) {
                        if (func_0012ed88(a0, &D_002E31B0, v0, v1) > (f32)o->fe) goto next;
                    }
                    mask &= ~(1 << i);
                    fl[k] = 1;
                }
            next:
                i++;
            } while (i < n);
        }
    }
    q->f8 = mask;
    q->f4 = mask;
    if (n > 0) {
        func_0012cb40(base, 1, 2);
        if (D_00304BE8->f874 & 1) {
            func_0012ccb0(1);
            return;
        }
        if (mask == -1) base->f4 |= 2;
        func_0012d368(a0, a1, fl);
        func_0012d188(a0, a1);
    }
}


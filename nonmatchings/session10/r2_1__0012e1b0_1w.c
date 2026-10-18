/* 0012e1b0 1w (LCS 1), hand/nostrict_nofill (4 LCS in hand/nostrict: there ee-as fills the jal func_0012dce0 slot with the la-macro addu, the orig leaves nop), no context. From r2_6 39w: the goto loop as `for (;;) { ...; if (cond) continue; break; }` (real loop notes: label aligned, only the lui hoisted, li 1 per use as the orig); the tail written without snd/r1 gotos: each arm calls func_0011d768(N) itself and the two r1 arms say `r = 1;` (jump2 cross-jumps the copies; the extra refs fix pad s4 / r s3 and the 0x100 layout); keep `goto one;` from 0x20 into 0x40. Left: reorg fills `beqz v0,L3e0` (D_00524F40 > D_002E3170 test) with the andi k&0x80 stolen from the target as beqzl (annulled), the orig uses plain beqz: reorg thinks v0 is needed on the fall-through (the func_0012dd38 call); m = k & 0x80 in the block before gives beqz but andi a1 (tied to k). */
#include "common.h"
typedef struct { s32 f0, f4; u32 f8; s32 fc; s32 n; u8 ids[0x20]; s32 f34; } Q8;
typedef struct { u16 f0; u8 p2[4]; u8 f6; s8 f7; s8 f8; } O8;
typedef struct { u32 x0; u32 x4; u32 x8; } Pad;
extern Q8 D_002E2FD8[7];
extern Q8 *D_002E3170[];
extern Q8 **D_00524F40;
extern O8 *D_002E319C;
extern O8 *D_002E31A0;
extern O8 *func_001478c8(s32);
extern void func_0011d768(s32);
extern void func_0012dce0(Q8 *);
extern Q8 *func_0012dd38(void);

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
    D_002E319C = D_002E31A0 = func_001478c8(q->ids[q->fc]);
    return r;
}

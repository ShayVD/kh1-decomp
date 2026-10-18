/* 0012e1b0 near miss (w13, s9): LCS 46 (session-6 draft was LCS 85, 792 vs 768 bytes; now right size), hand/nostrict, no context. Changes: the walk is a goto loop (no loop.c: `li 1` and the D_002E2FD8 lo_sum stay in the body after the call like the original), the key dispatch is an if/else-if chain that sets snd and falls into one shared func_0011d768(snd); goto end; with `r1: r = 1;` after it, snd = 3 set after the pad->x8 & 2 test. Left: (1) the original loop head is aligned (nop at 12e224), so it was a real loop that loop.c did not hoist from; -dL shows loop.c's threshold is ~57-61 real insns (lo_sum life 1 is 'not desirable' once the loop has 62 insns; ours as a while has 55, and the two `1` constants merge, savings 2), so the original loop body was bigger before combine or the two 1s did not match; (2) pad/r swap s3<->s4 and fc in a1 vs a0; (3) 0x100 case: ours `bnez v1,play; li a0,4`, orig `beqzl v1,L; lb; b play; li a0,4` (reorg relax vs eager fill). */
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
loop:
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
        goto loop;
done:
    D_00524F40[1] = 0;
    q = *D_00524F40;
    if (q->fc < 0) return 1;
    r = 0;
    o = func_001478c8(q->ids[q->fc]);
    k = pad->x8;
    if (k == 0x100) {
        if (q->f8 & (1 << q->fc)) {
            snd = 4;
        } else {
            if (o->f8 > 0) {
                q->f34 = q->fc;
                func_0012dce0(&D_002E2FD8[o->f8]);
            }
            goto end;
        }
    } else if (k == 0x80 || (k & 2)) {
        if (D_00524F40 > D_002E3170) {
            q = func_0012dd38();
            if ((pad->x8 & 2) && q->fc >= 0) q->fc = 0;
            snd = 3;
        } else if (k & 0x80) {
            snd = 1;
            if (q->fc >= 0) q->fc = 0;
        } else {
            goto r1;
        }
    } else if (k == 0x20) {
        s32 v = q->fc;
        if (v <= 0) v = q->n;
        q->fc = v - 1;
        snd = 1;
    } else if (k == 0x40) {
        if (q->fc < q->n - 1) q->fc = q->fc + 1;
        else q->fc = 0;
        snd = 1;
    } else {
        goto r1;
    }
    func_0011d768(snd);
    goto end;
r1:
    r = 1;
end:
    D_002E319C = D_002E31A0 = func_001478c8(q->ids[q->fc]);
    return r;
}

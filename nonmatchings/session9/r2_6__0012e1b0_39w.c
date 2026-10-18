/* 0012e1b0 near miss (r2_6): LCS 39 (w13 46), hand/nostrict, 760 vs 768. From w13's draft: the 0x20 case ends 'goto one;' into the 0x40 case's 'one: snd = 1;' (jump2 now cross-jumps the li a0,1 like the orig: 0x20/0x40/0x80 tails exact). Left: (1) goto loop vs the orig's aligned real loop (while/for/do forms: 65-66); (2) pad s3 vs r s4 swap: global-alloc tie pad .0353 vs r .0341; one more ref of r flips it (an extra 'r = 0;' after func_0011d768(snd) gives 30 LCS but adds a move in the jal slot); (3) 0x100 case: ours 'bnez v1,play; li a0,4' (snd=4 block placed out of line, reorg threads it), orig 'beqzl v1,else; lb; b play; li a0,4' (snd=4 block on the fall-through); all if/goto spellings of that case give the same code. */
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
        goto one;
    } else if (k == 0x40) {
        if (q->fc < q->n - 1) q->fc = q->fc + 1;
        else q->fc = 0;
    one:
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

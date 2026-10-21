/* func_0012e1b0 (hand/nostrict_nofill), s10 r2_7. From r2_1's 1w draft plus a CONTEXT_ONLY copy of the leaf func_0012dd38 above it:
   a call to a function defined earlier in the TU that cannot throw gets a REG_EH_REGION 0 note, so reorg's live scan (find_dead_or_set_registers)
   continues past the call instead of stopping at it (can_throw), sees v0 set by the call, and fills `beqz v0` non-annulled as the original. */
#include "common.h"
typedef struct { s32 f0, f4; u32 f8; s32 fc; s32 n; u8 ids[0x20]; s32 f34; } Q8;
typedef struct { u16 f0; u8 p2[4]; u8 f6; s8 f7; s8 f8; } O8;
typedef struct { u32 x0; u32 x4; u32 x8; } Pad;
extern Q8 D_002E2FD8[7];
#include "data/pieces/D_002E3170.h"
extern Q8 **D_00524F40; /* src/data/bss_0052.c: void **D_00524F40 */
#include "data/pieces/D_002E319C.h"
#include "data/pieces/D_002E31A0.h"
extern O8 *func_001478c8(s32);
extern void func_0011d768(s32);
extern void func_0012dce0(Q8 *);
CONTEXT_ONLY Q8 *func_0012dd38(void) {
    Q8 **p = D_00524F40;
    if (p > ((Q8 **)&D_002E3170)) {
        *p = 0;
        D_00524F40 = --p;
    }
    return *p;
}

s32 func_0012e1b0(Pad *pad) {
    Q8 *q;
    Q8 *cur;
    O8 *o;
    u32 k;
    s32 r;
    s32 snd;

    D_00524F40 = ((Q8 **)&D_002E3170);
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
        if (D_00524F40 > ((Q8 **)&D_002E3170)) {
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
    D_002E319C = (u16 *)(*(O8 **)&D_002E31A0) = func_001478c8(q->ids[q->fc]);
    return r;
}

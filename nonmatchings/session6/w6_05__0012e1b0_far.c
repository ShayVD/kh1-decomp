/* func_0012e1b0: ~117-189 words off (nostrict). Body logic believed right; loop at 0x12e228: original does not hoist li 1 / addiu D_002E2FD8 out of the loop (only lui via PRE), ours hoists (while form) or rotates with an entry jump (do-while form). */
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
    while ((q = D_00524F40[1]) && q->n && !((*D_00524F40)->f8 & (1 << (*D_00524F40)->f34))) {
        cur = *D_00524F40;
        o = func_001478c8(cur->ids[cur->f34]);
        if (q != &D_002E2FD8[o->f8]) break;
        q = *++D_00524F40;
        if (q->fc >= 0) {
            if (q->fc >= q->n) q->fc = q->n - 1;
            if (q->f8 & (1 << q->fc)) break;
        }
    }
    D_00524F40[1] = 0;
    q = *D_00524F40;
    if (q->fc < 0) return 1;
    r = 0;
    o = func_001478c8(q->ids[q->fc]);
    k = pad->x8;
    if (k == 0x100) {
        if (q->f8 & (1 << q->fc)) {
            snd = 4;
            goto play;
        }
        if (o->f8 > 0) {
            q->f34 = q->fc;
            func_0012dce0(&D_002E2FD8[o->f8]);
        }
        goto end;
    } else if (k == 0x80 || (k & 2)) {
        if (D_00524F40 > D_002E3170) {
            q = func_0012dd38();
            snd = 3;
            if ((pad->x8 & 2) && q->fc >= 0) q->fc = 0;
            goto play;
        } else if (k & 0x80) {
            snd = 1;
            if (q->fc >= 0) q->fc = 0;
            goto play;
        }
        r = 1;
        goto end;
    } else if (k == 0x20) {
        s32 v = q->fc;
        if (v <= 0) v = q->n;
        q->fc = v - 1;
        snd = 1;
        goto play;
    } else if (k == 0x40) {
        if (q->fc < q->n - 1) q->fc = q->fc + 1;
        else q->fc = 0;
        snd = 1;
        goto play;
    }
    r = 1;
    goto end;
play:
    func_0011d768(snd);
end:
    D_002E319C = D_002E31A0 = func_001478c8(q->ids[q->fc]);
    return r;
}

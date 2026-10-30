/* Round 61 (wwm2): the size-exact version (808 vs 808 bytes, score 110), kept next to the main draft func_00f23750.nofill.c (score 84, 816 bytes). */
/* Round 59 (wwm2): score 130 -> 110, now 808 vs 808 bytes. The inner search keeps a pointer p = &tbl[k], and the done block reads p[-1] - b, where b = tbl[idx] + rem is set inside the loop (the target reuses the loop's sum at done, and the 8 extra bytes are gone). hill3 then reordered the set-up (score 114 -> 110). The p[-1] read: the target loads tbl[k - 1] as -4 off the loop's tbl[k] address (valaudit's lw -4(r)). Left: the target spills tbl to 0(sp) where ours spills cur. In the greg dump cur is 7 uses over 258 insns and tbl 9 over 100, so cur loses; declaration order makes no difference. */
/* Round 48 wwm2: the hill3o order from 30871a17 (dkmovie func_00f23750 near miss, score 130 -> 84, hill3o order under the new bui) moved a control line (break/case/label/return/goto) or broke a dependency, so its score 84 was not valid. Restored the last valid statement order: score 130. Earlier header below. */
/* Round 45 wwm2: score 132 -> 130 under the nofill build mode (tools/ovl/modescan.py). Earlier header below. */
/* dkmovie.x func_00f23750: near miss (session 141, wwm1), 824 vs 808 bytes (175 words shown, mostly shift): structure complete; the inner tbl[] search is a goto loop (no alignment nop in the original); left: tbl local is spilled to sp[0] in the original while ours spills cur, and the inner loop computes idx*4 once before its label. */
#include "ovl.h"
typedef unsigned int size_t;
void *memcpy(void *, const void *, size_t);
typedef struct {
    u8 pad0[0x100];
    s32 tbl[(0x3DD20 - 0x100) / 4];
    s32 f3DD20;
    s32 f3DD24;
    u8 pad3DD28[0x3DD50 - 0x3DD28];
    s32 a[3];
    u8 *buf[6];
    s32 st[4];
    u8 *ptr[4];
    u8 pad3DD94[0x3DDD0 - 0x3DD94];
    s32 f3DDD0;
    s32 f3DDD4;
    u8 pad3DDD8[0x3DF0C - 0x3DDD8];
    s32 f3DF0C;
    u8 pad3DF10[0x3DF1C - 0x3DF10];
    s32 f3DF1C;
    u8 pad3DF20[0x3DF50 - 0x3DF20];
    s8 f3DF50;
    s8 f3DF51;
    s8 f3DF52;
    u8 pad3DF53[0x3DF67 - 0x3DF53];
    s8 f3DF67;
} MovieWork;
extern MovieWork *D_00F28460;
extern s32 D_00F284A0;
void func_00f26d30(s32 *);
void func_00f279f8(s32, s32);
void func_00f23480(void);
void func_00f22738(u8 *, s32);
void func_00f28198(u8 *, s32);
void func_00f28208(MovieWork *);

void func_00f23750(void) {
    s32 n, i, k, lim;
    s32 cur, len, rem, idx, size;
    u8 *off;
    s32 *tbl;
    s32 *p;
    s32 b;
    D_00F28460->f3DF52 = 0;
    cur = 0;
    n = D_00F28460->f3DF50;
    len = 0;
    for (i = 0; i < n; i++) {
        D_00F28460->st[i] = 0;
        D_00F28460->ptr[i] = 0;
        D_00F28460->a[i] = 0;
    }
    rem = 0;
    idx = 0;
    off = 0;
    func_00f26d30(&D_00F28460->f3DDD4);
    func_00f279f8(D_00F28460->f3DD20, D_00F28460->f3DD24);
    D_00F284A0 = D_00F28460->f3DF1C;
    D_00F28460->f3DF67 = 0;
    tbl = D_00F28460->tbl;
    for (;;) {
        while (D_00F28460->st[cur] != 0) {
            func_00f23480();
        }
        D_00F28460->st[cur] = 1;
        if (rem == 0) {
            lim = D_00F28460->f3DF0C;
        } else {
            memcpy(D_00F28460->buf[cur] + 2048 - rem, off + len - rem, rem);
            lim = D_00F28460->f3DF0C - 2048;
        }
        k = idx;
    again:
        p = &tbl[k];
        b = tbl[idx] + rem;
        size = *p - b;
        if (size > lim) goto done;
        if (D_00F28460->f3DF1C < k) goto done;
        k++;
        goto again;
    done:
        off = D_00F28460->buf[cur];
        size = p[-1] - b;
        idx = k - 2;
        if (rem == 0) {
            D_00F28460->ptr[cur] = off;
        } else {
            off += 2048;
            D_00F28460->ptr[cur] = off - rem;
        }
        len = (size + 2047) & ~2047;
        if (D_00F28460->f3DDD0 & 8) {
            break;
        }
        if (D_00F28460->f3DF51) {
            func_00f22738(off, len);
        } else {
            func_00f28198(off, len);
        }
        D_00F28460->a[cur] = idx++;
        rem = len - size;
        D_00F28460->st[cur] = 2;
        if (!((u32)idx < (u32)D_00F28460->f3DF1C)) {
            break;
        }
        cur = (cur + 1) % n;
    }
    func_00f28208(D_00F28460);
    for (;;) {
        func_00f23480();
    }
}

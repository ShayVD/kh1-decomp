/* 1 word left (score 3, 420 vs 424 bytes; was 72 words, score 45): recursive path search. Round 29 (wgb): `a == n || b == n` as one test, n == 0 jumps to the final return 0 (goto end), and the body after the n == 0 test sits in do { } while (0) followed by return 0, which keeps the loop-exit return 0 apart from the n == 0 one (a 10-minute permuter found the do/while). Left: the first address is `addu v1,a2,a1` (table base + o) in the target and o + base here; the y/n addresses match (o + base). Tried every x index order (k/a*24/8, o first or last, 8 + o), pointer and cast forms (they fold the base into %lo), [][3][8] and [][24] tables, u32/s16 index, o assigned inline or later, a base pointer local, a switch for the 13/27 remap (worse), all flag modes and a second 10-minute -j1 permuter run (no gain). Round 30: a static inline chk(v) helper for the x/y validity tests (still 1 word); a pointer helper chk(&D[o + 8]) flips the y/n adds to base + o but leaves x as o + base (y only through the helper: 3 words; x through it folds +8 into the base, 8 words); chkp(p, i), a base local t, and a j = 1..2 loop over v[j] (100 words) were all worse. */
#include "ovl.h"

extern s8 D_00FB6168[];
extern u8 D_00FB64AC[];

s32 func_00f7c078(s32 a, s32 b, s32 k) {
    s32 x;
    s32 y;
    s32 n;
    s32 r;
    s32 i;
    s32 o = k + a * 24;

    x = D_00FB6168[o + 1 * 8];
    if (x != 0 && !(D_00FB64AC[x] & 1)) {
        x = 0;
    }
    y = D_00FB6168[o + 2 * 8];
    if (y != 0 && !(D_00FB64AC[y] & 1)) {
        y = 0;
    }
    if (x != 0 || y != 0) {
        n = D_00FB6168[o + 0 * 8];
        if (n == 0) {
            goto end;
        }
        do {
            if (n == 13) {
                if (!(D_00FB64AC[13] & 4)) {
                    n = 27;
                }
            } else if (n == 27) {
                if (!(D_00FB64AC[27] & 4)) {
                    n = 13;
                }
            }
            if (a == n || b == n) {
                return 0;
            }
            if (D_00FB64AC[n] & 4) {
                return n;
            }
            r = func_00f7c078(n, a, k);
            if (r != 0 && a != r && b != r) {
                return r;
            }
            for (i = 0; i < 8; i++) {
                if (i == k) {
                    continue;
                }
                r = func_00f7c078(n, a, i);
                if (r != 0 && a != r && b != r) {
                    return r;
                }
            }
        } while (0);
        return 0;
    }
end:
    return 0;
}

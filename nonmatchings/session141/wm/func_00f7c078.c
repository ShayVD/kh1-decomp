/* score 45 (72 words, mostly a shift): recursive path search. Structure right; the x/y "both zero" test comes out bnezl/beqz instead of bnez/beqzl and the return-0 v0 setting is placed differently. */
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
            return 0;
        }
        if (n == 13) {
            if (!(D_00FB64AC[13] & 4)) {
                n = 27;
            }
        } else if (n == 27) {
            if (!(D_00FB64AC[27] & 4)) {
                n = 13;
            }
        }
        if (a == n) {
            return 0;
        }
        if (b == n) {
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
    }
    return 0;
}

/* wm.x func_00f7c078: matched by hand. */
#include "ovl.h"

typedef struct { s8 n[8]; s8 x[8]; s8 y[8]; } Node;
extern Node D_00FB6168[];
extern u8 D_00FB64AC[];

s32 func_00f7c078(s32 a, s32 b, s32 k) {
    s32 x;
    s32 y;
    s32 n;
    s32 r;
    s32 i;

    x = D_00FB6168[a].x[k];
    if (x != 0 && !(D_00FB64AC[x] & 1)) {
        x = 0;
    }
    y = D_00FB6168[a].y[k];
    if (y != 0 && !(D_00FB64AC[y] & 1)) {
        y = 0;
    }
    if (x != 0 || y != 0) {
        n = D_00FB6168[a].n[k];
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

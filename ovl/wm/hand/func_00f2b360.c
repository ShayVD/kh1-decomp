/* wm.x func_00f2b360: matched by hand. */
#include "ovl.h"

typedef struct { s16 a; s16 b; s32 pad; } Q;
s32 func_0010fce8(s32, s32);
s32 func_00f2ab48(s32);
s32 func_00f2b1e8(s32);
s32 func_00f2b2f8(s32);
extern Q D_00F8BC98[];
extern s32 D_00F8BD88[];

s32 func_00f2b360(s32 *arg0, s32 *arg1, s32 arg2) {
    s32 id, mask, base, n, i, cnt;
    id = func_00f2b2f8(arg2);
    if (id < 0) return 0;
    mask = func_00f2b1e8(id);
    if (mask == 0) {
        base = func_00f2ab48(id);
        n = func_0010fce8(0, 0);
        *arg1 = base;
        *arg0 = n;
        return 1;
    }
    base = func_00f2ab48(id);
    if (base < 0) return 0;
    n = D_00F8BD88[id];
    if (n == 0) n = 1;
    cnt = 0;
    for (i = 0; i < n; i++) {
        if ((mask >> i) & 1) {
            s32 k = base + i;
            arg0[cnt] = func_0010fce8(D_00F8BC98[k].a, *(s16 *)((u8 *)&D_00F8BC98[k] + 2));
            arg1[cnt] = k;
            cnt++;
        }
    }
    return cnt;
}

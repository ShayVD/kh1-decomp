#include "common.h"
extern s8 D_0046A070[];
s32 strlen(const char *);
s32 memcmp(const void *, const void *, s32);

s32 func_0024ba28(s32 *p, char *name, s32 idx, u8 *out) {
    s32 len = strlen(name);
    s32 n, w, type, cnt, sz;
    u8 *src, *dst;
    for (;;) {
        n = *p++;
        w = (n + 3) / 4;
        if (n == 0) return -1;
        if (len == n) {
            if (memcmp(p, name, n) == 0) {
                p += w;
                type = *p++;
                cnt = *p++;
                sz = D_0046A070[type];
                if (idx >= cnt) return -1;
                src = (u8 *)p + idx * sz;
                dst = out;
                if (sz > 0) do { *dst++ = *src++; } while (--sz);
                return type;
            }
        }
        p += w;
        type = *p++;
        cnt = *p++;
        w = (D_0046A070[type] * cnt + 3) / 4;
        p += w;
    }
}

#include "common.h"
/* 241948 */

/* 2433e8 */

/* 243bd8 */

/* 243da0 */
extern s32 D_00656420;

/* 243e58 */
extern s32 D_00656420;

/* 244d00 */
#include "data/types/text_00240000_s6_25.h"

/* 249a48 */
#include "data/types/text_00240000_s6_25_p.h"
void sceGsSetDefLoadImage(void *, s32, s32, s32, s32, s32, s32, s32);
s32 sceGsExecLoadImage(void *, void *);
s32 sceGsSyncPath(s32, s32);
void func_00237018(void *, s32, s32);

/* 249dc8 */
s32 sceGsExecLoadImage(void *, void *);
s32 sceGsSyncPath(s32, s32);
void sceGsSetDefLoadImage(void *, s32, s32, s32, s32, s32, s32, s32);
void func_00237018(void *, s32, s32);

/* 24aac8 */

/* 24b448 */

/* 24ba28 */
extern s8 D_0046A070[];
s32 strlen(const char *);
s32 memcmp(const void *, const void *, s32);

s32 func_0024ba28(s32 *p, char *name, s32 idx, u8 *out) {
    s32 len = strlen(name);
    s32 n, w, type, cnt, sz;
    u8 *src, *dst;
    for (;;) {
        n = *p++;
        if (n == 0) return -1;
        w = (n + 3) / 4;
        if (len == n && memcmp(p, name, n) == 0) {
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
        p += w;
        type = *p++;
        cnt = *p++;
        sz = D_0046A070[type];
        w = (sz * cnt + 3) / 4;
        p += w;
    }
}
#include "data/bss_0065_mixed.h"
#include "data/data_0046.h"
#include "data/data_0045.h"
#include "data/data_0049.h"

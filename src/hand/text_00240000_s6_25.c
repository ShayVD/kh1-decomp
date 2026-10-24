#include "common.h"
#include "data/pieces/D_002C5968.h"
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
extern Prm *D_0046A038;
#include "data/pieces/D_0046A03C.h"
#include "data/pieces/D_0046A040.h"
#include "data/pieces/D_0046A044.h"
extern s32 D_0046A048;
extern Prm *D_00669A18[8]; /* src/data/bss_0066.c: s32 D_00669A18[8] */
void func_0024e1d0(void);
void func_0024b448(s32 i) {
    s32 o40, o48, t10, t18;
    Prm *p;
    o40 = D_0046A040;
    o48 = D_0046A048;
    switch ((*(volatile Sema_2c5968 *)&D_002C5968).mode) { default: return; case 0: break; }
    p = D_00669A18[i];
    D_0046A038 = p;
    D_0046A03C = p->unkC;
    t10 = p->unk10;
    (*(s32 *)&D_0046A044) = p->unk14;
    D_0046A040 = t10;
    t18 = p->unk18;
    D_0046A048 = t18;
    p->unk1C++;
    func_0024e1d0();
    D_0046A040 = o40;
    D_0046A048 = o48;
}

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
#include "data/pieces/D_0046A038.h"

/* Small list helpers at 0x249c48-0x249d50 (layout symbol func_00249c48 split
 * into four functions). */
#include "common.h"
typedef struct { s32 n; s32 a[1]; } Lst;
void func_00249a48(s32, s32);
void func_00249d48(Lst *p);

void func_00249c48(Lst *p) {
    func_00249d48(p);
}

void func_00249c60(Lst *p) {
    s32 i;
    if (p->n == 0) return;
    for (i = 0; i < p->n - 1; i++) func_00249a48(p->a[i], 0);
    func_00249a48(p->a[i], 1);
}

s32 func_00249d20(Lst *p, s32 v) {
    p->a[p->n] = v;
    p->n++;
    return v + 16;
}

void func_00249d48(Lst *p) {
    p->n = 0;
}

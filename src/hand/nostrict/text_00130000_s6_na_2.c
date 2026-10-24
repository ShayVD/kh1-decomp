#include "common.h"
void func_00267518(f32 *, f32 *, f32 *);
void func_00267530(f32 *, f32 *, f32 *);
void func_002675a8(f32 *, f32 *);

typedef struct {
    union { u64 flags; s32 w; } u;
    u8 pad8[4];
    f32 f0c;
    f32 v10[4];
    s32 i20;
    f32 f24;
    f32 f28;
    u8 pad2c[0x34-0x2c];
    s32 i34;
    u8 pad38[0x3c-0x38];
    f32 f3c;
    f32 v40[4];
    u8 pad50[0x54-0x50];
    s32 i54;
    u8 pad58[0x70-0x58];
    f32 v70[4];
    f32 v80[4];
    s32 i90;
} Src57;
typedef struct { s32 kind; s32 a4; s32 a8; Src57 *src; s32 a10; f32 f14; f32 f18; s32 pad1c; f32 v[4]; } Ent57;
void func_002675a8(f32 *, f32 *);
void func_00267530(f32 *, f32 *, f32 *);
void func_00267518(f32 *, f32 *, f32 *);
void func_00267e90(f32 *, f32 *, f32);
void func_00121fc4(f32 *, f32 *);
void func_0014b550(Ent57 *, Ent57 *, s32);

s32 func_0014b9e0(Src57 *s, f32 *a, f32 *b, f32 f0, f32 f1, Ent57 *tbl, s32 n) {
    f32 p[4];
    f32 zero;
    f32 d[4];
    f32 len;
    s32 cnt;
    Ent57 *e;

    len = (f0 + f1) * 0.5f;
    if ((s32)(s->u.flags >> 27) & 1) len += len;
    if (len == 0.0f) return 0;
    e = &tbl[n];
    func_00267530(d, b, a);
    func_00121fc4(d, d);
    cnt = 0;
    func_00267e90(d, d, len);
    zero = 0.0f;
    func_002675a8(p, a);
    f1 = (f1 - f0) / (d[3] / len);
    do {
        e->kind = (s32)(s->u.flags >> 12) & 3;
        e->a4 = s->i34;
        e->a8 = s->i54;
        e->src = s;
        e->a10 = 1;
        func_002675a8(e->v, p);
        e->f14 = e->f18 = f0;
        f0 += f1;
        func_0014b550(e, tbl, n);
        if (n + cnt < 254) {
            e++;
            cnt++;
        }
        func_00267518(p, p, d);
        d[3] -= len;
    } while (zero < d[3]);
    return cnt;
}
#include "data/bss_0057_mixed.h"
#include "data/data_0036.h"

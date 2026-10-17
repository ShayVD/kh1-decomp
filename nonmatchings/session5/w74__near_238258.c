#include "common.h"
typedef int u128 __attribute__((mode(TI)));
typedef struct Nd { struct Nd *next; s32 type; u8 pad8[8]; u128 v[3]; u128 n[3]; u64 t0, t1; u128 c[3]; } Nd;
typedef struct { Nd *head; s32 pad; } NBk;
typedef struct { s32 bits; NBk *tbl; } NHt;
s32 func_00237548(u128 *, u128 *, u128 *, s32);
f32 func_00237a48(u128 *, s32, u128 *, s32);
void func_00267560(u128 *, u128 *, f32);
void func_002675f0(u128 *, u128 *);
void func_00237018(u128 *, s32, s32);

void func_00238258(NHt *h, s32 a1, u128 *dst, s32 a3, s32 a4) {
    u128 t0, t1, t2;
    s32 k, num;
    NBk *bk;
    s32 n = 1 << h->bits;
    s32 i, j;
    Nd *p;
    u128 *d, *o, *pv, *pn, *pc;
    bk = h->tbl;
    k = 2;
    num = 0;
    for (i = 0; i < n; i++, bk++) {
        if (bk->head != 0) {
            p = bk->head;
            do {
                d = p->v;
                if (func_00237548(d, &p->v[1], &p->v[2], a4) == 0) {
                    pv = d;
                    pn = p->n;
                    pc = p->c;
                    d = (u128 *)((k << 4) + (s32)dst);
                    ((u64 *)d)[0] = p->t0;
                    d++;
                    ((u64 *)d)[-1] = p->t1;
                    for (j = 0; j < 3; j++) {
                        func_00267560(&t1, pc, func_00237a48(&t0, a4, pv, 1));
                        func_002675f0(&t2, pn);
                        pv++; pc++; pn++;
                        { u128 x = t1, y = t2, z;
                        *d++ = x;
                        z = t0;
                        *d++ = y;
                        *d++ = z; }
                    }
                    k += 10;
                    num++;
                }
                if (p->next == 0) break;
                p = p->next;
            } while (p != 0);
        }
    }
    if (num != 0) {
        dst[1] = 0;
        ((u64 *)dst)[2] = num | 0x8000 | 0xA02DC00000000000ULL;
        ((u64 *)dst)[3] = 0x512512512EULL;
        func_00237018(dst, k, 1);
    }
}

/* Pad vibration, without strict aliasing (docs/modules.md "Session 51"):
 * func_00176ba8 starts a type-20 pattern on pad i, func_00176cc8 steps pad i's
 * two motors, writes their 0-255 levels to D_002C5AD2[i][j] and repeats or
 * stops the pattern at its end.  padvib.c has the rest.  Read from the code,
 * not proved by a boot. */
#include "common.h"
#include "data/types/nostrict_text_00170000_h38.h"
#include "data/pieces/D_0035C440.h"
#include "data/pieces/D_0035C460.h"
#include "data/pieces/D_0035C490.h"
#include "data/types/nostrict_text_00170000_h61.h"

/* func_00176ba8 (from hand/nostrict/text_00170000_h38.c). */
typedef struct { u8 *a; u8 *b; s32 c; s32 d; s32 e; } E20;
typedef struct { H20 *h; E20 e[2]; } S44;
extern S44 D_005757B0[];
void *memset(void *, s32, u32);
void func_00176ba8(H20 *h, s32 i) {
    S44 *s;
    s32 j;
    E20 *e;
    if (h->type != 20) return;
    s = &D_005757B0[i];
    memset(s, 0, 44);
    s->h = h;
    for (j = 0, e = s->e; j < 2; j++, e++) {
        e->a = e->b = (u8 *)(h->off[j] + (s32)h);
        e->c = h->x10[j];
        e->d = 0;
        e->e = 0;
    }
}

/* func_00176cc8 (from hand/nostrict/text_00170000_h61.c). */
extern f32 D_002BBDFC;
extern u8 D_002C5AD2[][112];
void func_00176c60(s32);
#define D_005757B0 ((T44 *) D_005757B0)
void func_00176cc8(s32 i) {
    T44 *s = &D_005757B0[i];
    s32 j;
    F20 *e;
    if (!s->h) return;
    for (j = 0; j < 2; j++) {
        u8 *p;
        e = &s->e[j];
        if (e->c <= 0) continue;
        p = e->b;
        if (p == e->a) {
            e->e = p[1];
        } else {
            e->e = ((f32)p[1] - (f32)p[-1]) / p[0] * e->d + p[-1];
            e->d += D_002BBDFC;
        }
        if (e->e < 0.0f) e->e = 0.0f;
        if (e->e >= 256.0f) e->e = 255.0f;
        D_002C5AD2[i][j] = e->e;
        if (p[0] <= e->d) {
            e->d -= p[0];
            e->b = p + 2;
            e->c--;
        }
    }
    if (s->e[0].c > 0) return;
    if (s->e[1].c > 0) return;
    if (s->h->x4 & 1) {
        func_00176ba8(s->h, i);
        return;
    }
    func_00176c60(i);
}
#undef D_005757B0


/* Numbers over the field (docs/modules.md "Session 46"), nostrict part.
 * func_00245b08 steps a number's sprites and, when its position is on screen,
 * draws its digits 13 pixels apart centred 20 pixels above it, then the
 * frame, in one GIF send; func_00245920 sends one sprite moved by (x, y)
 * with its alpha scaled by s through D_00662950. */
#include "common.h"
#include "data/types/nostrict_text_00240000_s7_w36.h" /* QW */
#include "data/pieces/D_002E26C0.h"
#include "data/pieces/D_00426820.h"
#include "data/pieces/D_004267F0.h"

typedef struct { s32 x, y, z, w; } I4;
typedef struct { u8 pad[0x60]; I4 c[4]; I4 p[4]; } Pkt;
typedef struct { u8 pad[0xC0]; } Item;
typedef struct { u8 pad0[8]; s32 unk8; u8 padC[4]; u8 unk10[0x10]; Item unk20; Item items[10]; } Pan;
typedef struct { s32 x, y, z, w; } V4;

Pkt D_00662950 ALIGNED(16);
QW *D_00662944 ALIGNED(4);
extern QW *D_00662940; /* src/data/bss_0066.c: s32 D_00662940 */
extern QW D_00351E10[]; /* the staging arena as quadwords */
void func_00237018(void *, s32, s32);
void func_0024aa48(void *, Pkt *, void *);
s32 func_002388b8(Pkt *, s32, s32);
s32 func_00249580(void *);
f32 func_00237a48(V4 *, void *, void *, s32);
void func_00249558(V4 *, V4 *);
void func_0024ae00(void *);
void func_0024af00(void *);

void func_00245920(Item *a0, void *a1, s32 x, s32 y, f32 s) {
    s32 i;
    s32 *p;
    s32 dx, dy;
    func_0024aa48(a0, &D_00662950, a1);
    dx = x * 16;
    dy = y * 16;
    p = &D_00662950.p[0].y;
    for (i = 0; i < 4; i++) {
        p[-1] += dx;
        *p += dy;
        p += 4;
    }
    for (i = 0; i < 4; i++) {
        D_00662950.c[i].w = D_00662950.c[i].w * s;
    }
    D_00662940 = (QW *)func_002388b8(&D_00662950, 1, (s32)D_00662940);
}

/* func_00245b08 matches only with copies of func_00245a08 / func_00245ad8
 * (dmgnum.c) above it. */
CONTEXT_ONLY s32 func_00245a08(s32 v, s32 *d) {
    s32 *p;
    s32 n = 5;
    s32 i = 0;
    d[0] = v / 10000;
    d[1] = v % 10000 / 1000;
    d[2] = v % 1000 / 100;
    d[3] = v % 100 / 10;
    d[4] = v % 10;
    if (d[0] == 0) {
        p = d;
        do {
            i++;
            p++;
            n--;
        } while (i < 4 && *p == 0);
    }
    return n;
}

CONTEXT_ONLY void func_00245ad8(s32 on, Item *spr) {
    if (on != 0) {
        func_0024ae00(spr);
    }
    func_0024af00(spr);
}

void func_00245b08(s32 a, Pan *p) {
    s32 d[5];
    V4 v;
    s32 i, n, x, y;
    s32 *q;
    for (n = 0; n < 10; n++) func_00245ad8(a, &p->items[n]);
    func_00245ad8(a, &p->unk20);
    if (!func_00249580(p->unk10)) {
    n = func_00245a08(p->unk8, d);
    func_00237a48(&v, D_002E26C0, p->unk10, 1);
    func_00249558(&v, &v);
    v.x -= (n * 16 + 9) / 2;
    v.y -= 20;
    a = v.x;
    y = v.y;
    D_00662944 = D_00351E10;
    D_00662940 = D_00351E10 + 1;
    for (i = 0; i < n; i++) {
        func_00245920(&p->items[d[5 - n + i]], D_00426820, a, y, 1.0f);
        a += 13;
    }
    func_00245920(&p->unk20, D_004267F0, a + 2, y, 1.0f);
    func_00237018(D_00662944, D_00662940 - D_00662944, 1);
    }
}

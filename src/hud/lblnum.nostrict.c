/* Labelled numbers over the field (docs/modules.md "Session 46"), nostrict
 * part.  func_00246ed8 steps a number's sprites and, when its position is on
 * screen, draws the label, the digits (13 pixels apart) and the frame 40
 * pixels above it in one GIF send.  One Item *it is reused for the steps and
 * the draw loop (its kill keeps the gcse PRE copy of &p->unk30). */
#include "common.h"
#include "data/types/nostrict_text_00240000_s7_w36.h" /* QW */
#include "data/pieces/D_002E26C0.h"
#include "data/pieces/D_00426820.h"
#include "data/pieces/D_004267F0.h"

typedef struct { u8 pad[0xC0]; } Item;
typedef struct { u8 pad0[0x10]; u8 unk10[0x10]; s32 unk20; u8 pad24[0xC]; Item unk30; Item unkF0; Item items[10]; } Pan2;
typedef struct { s32 x, y, z, w; } V4;

QW *D_00668F84 ALIGNED(4);
extern QW D_00351E10[]; /* the staging arena as quadwords */
extern QW *D_00668F80; /* src/data/bss_0066.c: Q4 *D_00668F80 */
s32 func_00249580(void *);
void func_00237a48(V4 *, void *, void *, s32);
void func_00249558(V4 *, V4 *);
void func_00246dc0(Item *, void *, s32, s32, f32);
void func_00237018(void *, s32, s32);
void func_0024ae00(void *);
void func_0024af00(void *);

/* func_00246ed8 matches only with copies of func_00246cf0 / func_00246ea8
 * (lblnum.c) above it. */
CONTEXT_ONLY s32 func_00246cf0(s32 arg0, s32 *arg1) {
    s32 *var_a1;
    s32 temp_lo;
    s32 var_s0;
    s32 var_t9;
    var_s0 = 5;
    var_t9 = 0;
    temp_lo = arg0 / 10000;
    arg1[0] = temp_lo;
    arg1[1] = arg0 % 10000 / 1000;
    arg1[2] = arg0 % 1000 / 100;
    arg1[3] = arg0 % 100 / 10;
    arg1[4] = arg0 % 10;
    if (temp_lo == 0) {
        var_a1 = arg1;
loop_2:
        var_t9 += 1;
        var_a1 += 1;
        var_s0 -= 1;
        if (var_t9 < 4) {
            if (*var_a1 == 0) {
                goto loop_2;
            }
        }
    }
    return var_s0;
}
CONTEXT_ONLY void func_00246ea8(s32 arg0, Item *arg1) {
    if (arg0 != 0) {
        func_0024ae00(arg1);
    }
    func_0024af00(arg1);
}

void func_00246ed8(s32 a, Pan2 *p) {
    s32 d[5];
    V4 v;
    s32 i, n, y;
    Item *it;
    for (n = 0; n < 10; n++) func_00246ea8(a, &p->items[n]);
    it = &p->unk30;
    func_00246ea8(a, it);
    it = &p->unkF0;
    func_00246ea8(a, it);
    if (!func_00249580(p->unk10)) {
    n = func_00246cf0(p->unk20, d);
    func_00237a48(&v, D_002E26C0, p->unk10, 1);
    func_00249558(&v, &v);
    v.x = v.x - n * 8 - 25;
    v.y -= 20;
    a = v.x;
    y = v.y - 20;
    D_00668F84 = D_00351E10;
    D_00668F80 = D_00351E10 + 1;
    func_00246dc0(&p->unk30, D_004267F0, a, y, 1.0f);
    a += 43;
    for (i = 0; i < n; i++) {
        it = &p->items[d[5 - n + i]];
        func_00246dc0(it, D_00426820, a, y, 1.0f);
        a += 13;
    }
    func_00246dc0(&p->unkF0, D_004267F0, a + 2, y, 1.0f);
    func_00237018(D_00668F84, D_00668F80 - D_00668F84, 1);
    }
}

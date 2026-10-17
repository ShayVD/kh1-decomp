#include "common.h"
typedef struct { u64 lo, hi; } QW;
extern u8 D_00351E10[];
extern QW *D_00662940;
extern QW *D_00662944;
extern u8 D_002E26C0[];
extern u8 D_00426820[];
extern u8 D_004267F0[];
typedef struct { u8 pad[0xC0]; } Item;
typedef struct { u8 pad0[8]; s32 unk8; u8 padC[4]; u8 unk10[0x10]; Item unk20; Item items[10]; } Pan;
typedef struct { s32 x, y, z, w; } V4;
s32 func_00249580(void *);
void func_00237a48(V4 *, void *, void *, s32);
void func_00249558(V4 *, V4 *);
void func_00245920(Item *, void *, s32, s32, f32);
void func_00237018(void *, s32, s32);

void func_0024ae00(void *);
void func_0024af00(void *);
s32 func_00245a08(s32 arg0, s32 *arg1) {
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
void func_00245ad8(void *arg0, Item *arg1) {
    if (arg0 != 0) {
        func_0024ae00(arg1);
    }
    func_0024af00(arg1);
}
void func_00245b08(void *a, Pan *p) {
    s32 d[5];
    V4 v;
    s32 i, n, x, y;
    s32 *q;
    for (i = 9; i >= 0; i--) func_00245ad8(a, &p->items[9 - i]);
    func_00245ad8(a, &p->unk20);
    if (!func_00249580(p->unk10)) {
    n = func_00245a08(p->unk8, d);
    func_00237a48(&v, D_002E26C0, p->unk10, 1);
    func_00249558(&v, &v);
    v.x -= (n * 16 + 9) / 2;
    v.y -= 20;
    x = v.x;
    y = v.y;
    D_00662944 = (QW *)D_00351E10;
    D_00662940 = (QW *)(D_00351E10 + 0x10);
    if (n > 0) {
        q = d - n + 5;
        do {
            func_00245920(&p->items[*q++], D_00426820, x, y, 1.0f);
            x += 13;
        } while (--n);
    }
    func_00245920(&p->unk20, D_004267F0, x + 2, y, 1.0f);
    func_00237018(D_00662944, D_00662940 - D_00662944, 1);
    }
}

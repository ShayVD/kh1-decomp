#include "common.h"
typedef struct { u64 lo, hi; } QW;
extern u8 D_00351E10[];
extern QW *D_00668F80;
extern QW *D_00668F84;
extern u8 D_002E26C0[];
extern u8 D_00426820[];
extern u8 D_004267F0[];
typedef struct { u8 pad[0xC0]; } Item;
typedef struct { u8 pad0[0x10]; u8 unk10[0x10]; s32 unk20; u8 pad24[0xC]; Item unk30; Item unkF0; Item items[10]; } Pan2;
typedef struct { s32 x, y, z, w; } V4;
s32 func_00249580(void *);
s32 func_00246cf0(s32, s32 *);
void func_00237a48(V4 *, void *, void *, s32);
void func_00249558(V4 *, V4 *);
void func_00246dc0(Item *, void *, s32, s32, f32);
void func_00237018(void *, s32, s32);
void func_0024ae00(void *);
void func_0024af00(void *);
void func_00246ea8(s32 arg0, Item *arg1) {
    if (arg0 != 0) {
        func_0024ae00(arg1);
    }
    func_0024af00(arg1);
}

void func_00246ed8(s32 a, Pan2 *p) {
    s32 d[5];
    V4 v;
    s32 i, y;
    s32 *q;
    Item *t30, *tF0;
    void *u;
    for (i = 0; i < 10; i++) func_00246ea8(a, &p->items[i]);
    t30 = &p->unk30;
    tF0 = &p->unkF0;
    u = p->unk10;
    func_00246ea8(a, t30);
    func_00246ea8(a, tF0);
    if (!func_00249580(u)) {
        i = func_00246cf0(p->unk20, d);
        func_00237a48(&v, D_002E26C0, u, 1);
        func_00249558(&v, &v);
        a = v.x - i * 8;
        y = v.y - 40;
        v.y -= 20;
        v.x = a - 25;
        D_00668F80 = (QW *)(D_00351E10 + 0x10);
        D_00668F84 = (QW *)D_00351E10;
        func_00246dc0(t30, D_004267F0, a - 25, y, 1.0f);
        a += 18;
        if (i > 0) {
            q = d - i + 5;
            do {
                func_00246dc0(&p->items[*q++], D_00426820, a, y, 1.0f);
                a += 13;
            } while (--i);
        }
        func_00246dc0(tF0, D_004267F0, a + 2, y, 1.0f);
        func_00237018(D_00668F84, D_00668F80 - D_00668F84, 1);
    }
}

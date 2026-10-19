#include "common.h"
typedef struct { u16 pos; u16 rot; u16 id; u16 x6; u8 pad8[4]; } CdPiece;
typedef struct { s32 x0; u16 n; u16 m; u8 pad8[4]; u8 c12; u8 pad13[0x50 - 13]; char name[32]; CdPiece p[(0xF70 - 0x70) / 12]; } CdEnt;
typedef struct { s32 x0, x4, x8, lv, x16, x20, x24, x28, x32, x36; } Stat;
typedef struct { u8 pad[4]; u8 type; u8 pad5[7]; u8 b12; u8 b13; u8 b14; u8 pad15[9]; f32 f24; } ItemInfo;
void func_001be820(void *, s32);
s32 func_001ba3f0(s32);
ItemInfo *func_001bb658(s32);

/* func_001bd090 (hand, strict). num/b/maxid/cnt/flag are plain locals that global-alloc spills
   (all nine s-registers are taken), so they live in reload stack slots 0..16(sp); the old drafts' local
   struct was a stand-in for those spill slots. The lv sets in the 68/69 arms are dead (lv is assigned on
   every path after the loop): life1 deletes them, which is what makes the 69 arm convert at the ce pass
   (fresh zero pseudo, first num = 3 store kept). */
void func_001bd090(CdEnt *a, Stat *st) {
    s32 i, id, n, sum, lv;
    s32 num, b, maxid, cnt, flag;
    f32 f;
    ItemInfo *it;
    n = 0;
    sum = 0;
    func_001be820(st, 40);
    f = 0.0f;
    if (func_001ba3f0(68) > 0) lv = 1;
    num = 3;
    cnt = 0;
    if (func_001ba3f0(69) > 0) { num = 5; lv = 2; }
    maxid = 0;
    flag = 0;
    b = 0;
    if (func_001ba3f0(70) > 0) num = num < 8 ? 8 : num;
    for (i = 0; i < a->n; i++) {
        id = a->p[i].id - 1;
        it = func_001bb658(id);
        switch (id) {
        case 0: case 1: case 2: case 3: st->x28 = id; break;
        case 52: if (st->x20 <= 0) st->x20 = 1; break;
        case 53: if (st->x20 < 2) st->x20 = 2; break;
        case 54: if (st->x16 <= 0) st->x16 = 1; break;
        case 55: if (st->x16 < 2) st->x16 = 2; break;
        case 50: if (st->x24 <= 0) st->x24 = 1; break;
        case 51: if (st->x24 < 2) st->x24 = 2; break;
        case 61: case 62: case 63: flag = 1; cnt++; break;
        case 48: st->x36 = 1; break;
        case 131: case 132: n++; sum += it->b12; break;
        }
        switch (it->type) {
        case 2: if (maxid < id) maxid = id; break;
        case 6: n++; sum += it->b12; break;
        }
        f += it->f24;
        b += it->b14;
    }
    if (flag) st->x32 = cnt;
    st->x0 = f * 4.0f / 100.0f;
    if (st->x0 > 96) st->x0 = 96;
    st->x4 = num;
    if (maxid == 0) lv = 0;
    else {
        it = func_001bb658(maxid);
        if (a->n) lv = it->b13 * b / a->n;
        else lv = it->b12;
        if (lv > it->b13) lv = it->b13;
        if (lv < it->b12) lv = it->b12;
    }
    st->lv = lv;
    if (n != 0 && sum > 0) st->x8 = sum / n;
    else st->x8 = 100;
}

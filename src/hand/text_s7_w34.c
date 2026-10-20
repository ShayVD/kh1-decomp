/* func_001bc900: strict, rodata jtbl 0x4900C0 (test with tools/matching/wqb03_rr.py 004900C0). 51 words off (ndiff 30): frame 208 vs 192 because loop 2 makes a giv s6=a+2 for p[i].rot (orig: addu v1,s4,s0; lhu 2(v1)) needing extra s7; b6 tier movn/movz order and lv tier reg a0 vs a1 differ. */
#include "common.h"
/* func_001bc900 (s7 w34): MATCH with wqb03_rr.py 004900C0 (rodata jtbl 0x4900C0), mode hand. From the s6 51w draft: (1) loop 2 reads rot as *(u16 *)((u8 *)a + off + 2) with a block-local s32 off = i * 12 + 0x70 (no a+2 giv, frame 192); (2) the size tier written out with the function-level t: t = total; if (t < 75) t = 1; else if (t < 150) t = 2; else t = 3; (gives the param-copy move, xori 0 and t in a1 in the lv block too). */
typedef struct { u16 pos; u16 rot; u16 id; u16 x6; u8 pad8[4]; } CdPiece;
typedef struct { s32 x0; u16 n; u16 m; u8 pad8[4]; u8 c12; u8 pad13[0x50 - 13]; char name[32]; u8 pad70[0x70 - 0x70]; CdPiece p[(0xF70 - 0x70) / 12]; } CdEnt;
typedef struct { f32 x, y, z, w; } V4;
typedef struct {
    u8 b0, b1, b2, b3, b4, b5, b6, b7, b8, b9, b10, b11;
    u8 pad12[4];
    V4 v16;
    V4 v32;
    f32 f48;
    char name[32];
} Out;
typedef struct { u8 pad0[12]; s32 lv; u8 b16; u8 pad17[19]; u8 b36; u8 pad37[11]; } Stat;
typedef struct { u8 pad[4]; u8 type; u8 pad5[19]; f32 f24; } ItemInfo;
extern CdEnt D_00622290;
extern u8 D_00625640; /* src/data/bss_0062.c: s32 D_00625640 */
void func_001bd090(CdEnt *, Stat *);
s32 func_001bcd10(CdEnt *, CdEnt *);
s32 func_001ba3f0(s32);
ItemInfo *func_001bb658(s32);
s32 func_001bb678(void);
void func_001bc530(V4 *, V4 *, V4 *, CdEnt *);
/* rodata */
void func_001bc900(CdEnt *a, Out *o) {
    V4 v;
    s32 cnt[16];
    Stat st;
    s32 i, k, r, t, total, flag;
    ItemInfo *it;
    func_001bd090(a, &st);
    o->b10 = 0;
    r = func_001bcd10(&D_00622290, a);
    if (r) o->b10 |= r << 4;
    for (i = 0; i < 16; i++) cnt[i] = 0;
    o->b3 = st.b36;
    o->b7 = st.b16;
    o->b4 = 0;
    if (func_001ba3f0(49) > 0) o->b4 = 1;
    if (st.lv == 0) t = 0;
    else if (st.lv < 100) t = 1;
    else if (st.lv < 120) t = 2;
    else t = 3;
    o->b5 = t;
    total = 0;
    o->b11 = 0;
    for (i = 0; i < a->n; i++) {
        s32 id = a->p[i].id;
        it = func_001bb658(id - 1);
        switch (id) {
        case 55: if (o->b7 == 0) o->b7 = 1; break;
        case 56: if (o->b7 < 2) o->b7 = 2; break;
        case 49: o->b3 = 1; break;
        case 59: if (o->b11 == 0) o->b11 = 1; break;
        case 60: if (o->b11 < 2) o->b11 = 2; break;
        case 62: if (o->b11 == 0) o->b11 = 1; break;
        case 63: if (o->b11 < 2) o->b11 = 2; break;
        case 61: case 64: if (o->b11 < 3) o->b11 = 3; break;
        }
        cnt[it->type] = 1;
        if (it->type != 1) total = total + it->f24;
    }
    t = total;
    if (t < 75) t = 1; else if (t < 150) t = 2; else t = 3;
    o->b6 = t;
    if (cnt[2]) {
        flag = 1;
        for (i = 0; i < a->n; i++) {
            if (func_001bb658(a->p[i].id - 1)->type == 2) {
                { s32 off = i * 12 + 0x70; if (((*(u16 *)((u8 *)a + off + 2) >> 8) & 0xf) == 4) flag = 0; }
            }
        }
    } else {
        flag = 0;
    }
    if (cnt[1] == 0) o->b10 |= 1;
    if (cnt[2] == 0) o->b10 |= 2;
    else if (flag) o->b10 |= 4;
    if (a->m > func_001bb678()) o->b10 |= 8;
    if ((o->b10 & 0xf) == 0) o->b2 = 1;
    else { o->b2 = 0; o->b3 = 0; }
    o->b0 = *(u8 *)&a->n;
    for (i = 0; i < 32; i++) o->name[i] = a->name[i];
    if (a->c12) o->b9 = a->c12 + D_00625640;
    else o->b9 = 0;
    o->b8 = 1;
    func_001bc530(&o->v16, &o->v32, &v, a);
    o->f48 = v.w;
}

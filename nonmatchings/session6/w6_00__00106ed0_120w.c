/* ~120 words off (hand; nostrict similar): structure decoded; orig indexes h as a float array ((f32*)h)[i*32+K] (separate addr regs per field), D_00494BAC[i] fields at 8,12,24 (member array at +8?), clear loop ascends, reloads D_00494BB0/BA8/BAC per iteration. Needs rework. */
#include "common.h"
typedef struct { s32 a, b, c, d; } Ent16;
typedef struct { u8 pad[8]; f32 x, y; u8 pad10[8]; f32 z; u8 pad1c[4]; } Ent32;
typedef struct { f32 v[8][4]; } E128;
typedef struct { s32 n; s32 off; } Hdr;
extern Ent16 D_0046E140, D_00472180, D_004761C0, D_0047A200;
extern Ent16 D_0046E150[1024];
extern Ent32 D_00472190[];
extern Ent16 *D_00494BA8;
extern Ent32 *D_00494BAC;
extern s32 D_00494BB0;
extern s32 D_002A6C50;
extern s32 D_002A6C54;
void func_00106ed0(E128 *h, s32 sz) {
    s32 i, j, a, b;
    Ent16 *sub;
    E128 *e;
    D_00494BAC = D_00472190;
    D_00494BA8 = D_0046E150;
    for (i = 0; i < 1024; i++) D_0046E150[i].c = 0;
    D_00494BB0 = ((Hdr *)h)->n;
    sub = (Ent16 *)((u8 *)h + ((Hdr *)h)->off);
    a = sub->a;
    D_004761C0.a = a;
    D_00472180.a = a;
    D_0046E140.a = a;
    D_0047A200.a = a;
    b = sub->b + (s32)h;
/*P*/
    D_00472180.c = 0;
    D_0046E140.c = 0;
    D_004761C0.b = b;
    D_0047A200.c = 0;
    D_004761C0.c = 0;
    D_00472180.b = b;
    D_0046E140.b = b;
    D_0047A200.b = b;
    D_00472180.d = 0;
    D_0046E140.d = 0;
    D_0047A200.d = 0;
    D_004761C0.d = 0;
/*Q*/
    D_002A6C50 = 0;
    if (h->v[7][3] != 1.0f) {
        D_002A6C50 = (s32)h->v[7][3] - 20;
        D_002A6C54 = (s32)h + sz - (D_002A6C50 << 16);
        h->v[7][3] = 1.0f;
    }
    for (i = 0; i < D_00494BB0; i = j) {
        j = i + 1;
        e = &h[i];
        sub[j].b += (s32)h;
        sub[j].d += (s32)h;
        if (e->v[1][3] != 0.0f) {
            f32 t;
            e->v[1][3] = 1.0f;
            t = e->v[5][3];
            e->v[5][3] = 1.0f;
            D_00494BAC[i].x = e->v[2][3];
            D_00494BAC[i].y = e->v[3][3];
            D_00494BA8[i].c = 1 << (s32)t;
            D_00494BAC[i].z = e->v[4][3];
            e->v[2][3] = 1.0f;
            e->v[3][3] = 1.0f;
            e->v[4][3] = 1.0f;
            e->v[6][3] = 1.0f;
        }
    }
}

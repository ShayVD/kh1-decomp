#include "common.h"

typedef struct {
    u8 a[2048];
    u8 b[256];
    u8 c[384];
    u8 l0[10];
    u8 l1[10];
    u8 l2[10];
    u8 l3[50];
    u32 f0:1;
    u32 f1:1;
    u32 f2:1;
    u32 f3:1;
    char name[10];
    u8 padade[0xb14 - 0xadb];
    s32 tab[32][5];
    u8 padd94[0xdc4 - 0xd94];
    u32 g0:1;
    u32 g1:1;
    u32 g2:1;
    u32 g3:1;
    u32 g4:1;
    u8 padg[3];
    u8 h[8];
    u8 dd0;
    s32 dd4;
} SaveInit;
#include "data/types/text_001d0000_b11.h"
typedef struct {
    u8 pad0[0x10];
    f32 pos[3];
    u8 pad1c[0x30 - 0x1c];
    f32 f30;
    f32 f34;
    f32 f38;
} Actor;
typedef struct {
    s32 x0;
    Actor *obj;
    f32 p[3];
    f32 f14[3];
    f32 f20;
    u8 pad24[0x28];
    f32 f4c;
    f32 f50;
    f32 f54;
    f32 f58;
    s8 b5c;
    s8 b5d;
    u8 pad5e[2];
    s32 f60;
    s32 f64;
    u8 pad68[0x118];
    s32 sp;
    s32 stk[92];
    f32 f2f4;
    u8 pad2f8[0x30];
    union { u64 x; s32 i[2]; } flags;
} VM;

extern Str10 D_004908F0;
#include "data/pieces/D_003DCB90.h"
#include "data/pieces/D_003DD230.h"
extern s32 D_003DD258;
extern s32 D_003DD28C;

void *func_00232cc0(s32);
void func_001ec758(s32, s32, s32);

/* func_001e4d50, func_001e6f28, func_001e7228, func_001e74b0 are in src/list/list.c. */


void func_001eacd0(void) {
    Str10 tmp = D_004908F0;
    SaveInit *s;
    u8 *q;
    s32 i, j;

    s = (SaveInit *)func_00232cc0(1);
    q = (u8 *)func_00232cc0(2);
    for (i = 0; i < 2048; i++) s->a[i] = 0;
    for (i = 0; i < 256; i++) s->b[i] = 0;
    for (i = 0; i < 384; i++) s->c[i] = 0;
    for (i = 0; i < 1024; i++) q[i] = 0;
    for (i = 0; i < 10; i++) {
        if (i == 9) {
            s->l2[i] = 0;
            s->l1[i] = 0;
            s->l0[i] = 0;
        } else {
            s->l2[i] = i + 1;
            s->l1[i] = i + 1;
            s->l0[i] = i + 1;
        }
    }
    for (i = 0; i < 50; i++) {
        if (i == 49) s->l3[i] = 0;
        else s->l3[i] = i + 1;
    }
    s->f2 = 0;
    s->f1 = 0;
    s->f0 = 0;
    s->f3 = 0;
    for (i = 0; i < sizeof(tmp); i++) s->name[i] = tmp.s[i];
    s->g0 = 0;
    s->g1 = 0;
    s->g2 = 0;
    s->g3 = 0;
    s->g4 = 0;
    for (i = 0; i < 32; i++)
        for (j = 0; j < 5; j++) s->tab[i][j] = -1;
    for (i = 0; i < 8; i++) s->h[i] = 0;
    s->dd0 = 0;
    s->dd4 = 0;
    for (i = 0; i < 5; i++) {
        func_001ec758(0, i, -1);
        func_001ec758(1, i, -1);
        func_001ec758(2, i, -1);
        func_001ec758(3, i, -1);
    }
}

/* Split out of the func_001e6f28 layout entry. */
extern s32 D_003DD258;
extern s32 D_003DD28C;

#include "data/bss_0063_mixed.h"
#include "data/data_003D.h"
#include "data/pieces/D_003DD258.h"
#include "data/pieces/D_003DD28C.h"
#include "data/pieces/D_004908F0.h"

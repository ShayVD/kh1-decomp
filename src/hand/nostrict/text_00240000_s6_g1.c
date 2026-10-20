#include "common.h"
typedef struct { s32 v[48]; } __attribute__((aligned(8))) Spr;
typedef struct { u8 pad[8]; s32 off; } Blob;
typedef struct {
    u8 pad0[8];
    Spr *a[7];      /* 0x08 */
    s32 na;         /* 0x24 */
    Spr *b[4];      /* 0x28 */
    s32 nb;         /* 0x38 */
    Spr *c[2];      /* 0x3C */
    s32 nc;         /* 0x44 */
    Spr *d[8];      /* 0x48 */
    s32 nd;         /* 0x68 */
    void *p6c;      /* 0x6C */
    void *p70;      /* 0x70 */
    u8 pad74[0x90 - 0x74];
    void *p90;      /* 0x90 */
    u8 pad94[0xA0 - 0x94];
    Spr e[6];       /* 0xA0 */
    u8 pad520[0x10];
    Spr f[3];       /* 0x530 */
    u8 pad770[0x20];
    Spr g[3];       /* 0x790 */
    u8 pad9d0[0xA84 - 0x9D0];
    Spr *pA84;      /* 0xA84 */
    u8 padA88[0xAB0 - 0xA88];
    Spr h[3];       /* 0xAB0 */
    u8 padCF0[0x10];
} Slot;
extern Slot D_00651E70[];
extern Blob D_0044A830, D_0044C5A0, D_0044DFD0, D_0044F380, D_0044F4D0, D_00451040;
extern s32 D_00454430[], D_00454448[], D_00454450[], D_00454468[];
extern s32 D_00454488[], D_00454498[], D_004544A0[], D_004544B0[];
extern s32 D_004544C0[], D_004544C8[], D_004544D0[];
extern s32 D_004544D8[], D_004544F8[], D_00454518[], D_00454538[];
extern u8 D_00426880[], D_004268B0[], D_004268E0[], D_00426910[];
extern u8 D_00454730[], D_00454780[], D_004547C0[];

#define BASE(B) (b = &B, (Spr *)((u8 *)b + b->off))

/* rodata: jump table jtbl_004916D0 */
void func_00241d60(void) {
    s32 i, j;
    Slot *s;
    Spr *base, *src;
    Blob *b;

    for (i = 0; i < 5; i++) {
        s = &D_00651E70[i];
        switch (i) {
        case 0:
            base = BASE(D_0044A830);
            s->na = 6;
            for (j = 0; j < s->na; j++) s->a[j] = base + D_00454430[j];
            s->nc = 2;
            for (j = 0; j < s->nc; j++) s->c[j] = base + D_004544C0[j];
            s->nd = 8;
            for (j = 0; j < s->nd; j++) s->d[j] = base + D_004544D8[j];
            s->nb = 4;
            for (j = 0; j < s->nb; j++) s->b[j] = base + D_00454488[j];
            s->p6c = D_00426880;
            s->p70 = D_004268E0;
            s->p90 = D_00454730;
            base = BASE(D_0044DFD0);
            s->e[0] = base[3];
            s->e[1] = base[4];
            s->e[2] = base[0];
            s->e[3] = base[1];
            s->e[4] = base[2];
            base = BASE(D_0044F380);
            s->e[5] = base[0];
            break;
        case 1:
        case 2:
            base = BASE(D_0044C5A0);
            s->na = 1;
            for (j = 0; j < s->na; j++) s->a[j] = base + D_00454448[j];
            s->nc = 2;
            for (j = 0; j < s->nc; j++) s->c[j] = base + D_004544C8[j];
            s->nd = 8;
            for (j = 0; j < s->nd; j++) s->d[j] = base + D_004544F8[j];
            s->nb = 1;
            for (j = 0; j < s->nb; j++) s->b[j] = base + D_00454498[j];
            s->p6c = D_004268B0;
            s->p70 = D_004268E0;
            s->p90 = D_00454780;
            s->f[0] = base[26];
            s->f[1] = base[27];
            s->f[2] = base[28];
            s->g[0] = base[29];
            s->g[1] = base[30];
            s->g[2] = base[31];
            base = BASE(D_0044DFD0);
            s->e[0] = base[8];
            s->e[1] = base[9];
            s->e[2] = base[5];
            s->e[3] = base[6];
            s->e[4] = base[7];
            base = BASE(D_0044F380);
            s->e[5] = base[0];
            break;
        case 3:
            base = BASE(D_0044F4D0);
            s->na = 6;
            for (j = 0; j < s->na; j++) s->a[j] = base + D_00454450[j];
            s->nd = 8;
            for (j = 0; j < s->nd; j++) s->d[j] = base + D_00454518[j];
            s->nb = 4;
            for (j = 0; j < s->nb; j++) s->b[j] = base + D_004544A0[j];
            s->p6c = D_00426880;
            s->p70 = D_00426910;
            s->p90 = D_004547C0;
            s->h[0] = base[32];
            s->h[1] = base[33];
            s->h[2] = base[34];
            break;
        case 4:
            base = BASE(D_00451040);
            s->na = 7;
            for (j = 0; j < s->na; j++) s->a[j] = base + D_00454468[j];
            s->nb = 4;
            for (j = 0; j < s->nb; j++) s->b[j] = base + D_004544B0[j];
            s->nd = 8;
            for (j = 0; j < s->nd; j++) s->d[j] = base + D_00454538[j];
            s->nc = 2;
            for (j = 0; j < s->nc; j++) s->c[j] = base + D_004544D0[j];
            s->pA84 = &base[68];
            s->p6c = D_00426880;
            s->p70 = D_004268E0;
            s->p90 = D_00454730;
            base = BASE(D_0044DFD0);
            s->e[0] = base[3];
            s->e[1] = base[4];
            s->e[2] = base[0];
            s->e[3] = base[1];
            s->e[4] = base[2];
            base = BASE(D_0044F380);
            s->e[5] = base[0];
            break;
        }
    }
}
#include "data/data_0045.h"

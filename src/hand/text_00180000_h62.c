/* Camera/effect helpers around 0x17f000, by hand (worker 62). */
#include "common.h"

typedef struct {
    u8 pad[0x1C];
    s32 id; /* +0x1C */
} Rec20;

typedef struct {
    f32 a[3];   /* +0x0 */
    f32 b[3];   /* +0xC */
    f32 c;      /* +0x18 */
    u8 mode;    /* +0x1C */
    u8 id;      /* +0x1D */
    u8 kind;    /* +0x1E */
} CamArg;

extern s32 D_00575890;
extern f32 D_002E2780[];
extern f32 D_005758D0[];
extern f32 D_002E2790[];
extern f32 D_005758E0[];
extern f32 D_002E27A0;
extern Rec20 *D_00362428;
extern s32 D_0036242C;
extern Rec20 *D_00362434;
extern Rec20 *D_00362438;
extern s32 D_00362440;
extern s32 D_00362444;
void func_00176f08(s32, f32);
Rec20 *func_0017adf8(s32, s32);

void func_0017f290(CamArg *a) {
    s32 i, j;
    Rec20 *r;
    Rec20 *q;

    D_00575890 |= 4;
    for (j = 0; j < 3; j++) {
        D_002E2780[j] = D_005758D0[j] = a->a[j];
        D_002E2790[j] = D_005758E0[j] = a->b[j];
    }
    D_002E27A0 = a->c;
    func_00176f08(a->mode, 0.0f);
    if (a->mode == 9) {
    switch (a->kind) {
    case 0:
        for (i = 0; i < D_00362440; i++) {
            r = (Rec20 *) ((i * 32) + (s32) D_00362428);
            if (r->id == a->id) {
                D_00362434 = r;
                D_00362438 = 0;
                break;
            }
        }
        break;
    case 1:
        i = 0;
    loop:
        if (i < D_00362444) {
            q = func_0017adf8(D_0036242C, i++);
            if (q->id != a->id)
                goto loop;
            D_00362438 = q;
            D_00362434 = 0;
        }
        break;
    }
    }
}

/* needs make: uses rodata */
extern s32 D_00362704;
extern s32 D_00362708;
extern s32 D_0036270C;
extern f32 D_00362710;
extern f32 D_00362714;
extern f32 D_00362718;
extern f32 D_0036271C;
extern f32 D_00362720;
extern f32 D_00362724;
extern f32 D_00362728;
extern f32 D_0036272C;
extern f32 D_002BBDFC;
void func_00110020(s32, s32);
f32 func_00120c88(f32);
f32 func_00176850(void);
f32 sinf(f32);

void func_0017f688(void) {
    f32 x, y;

    if (D_00362710 < 0.0f) {
        D_00362704 = 0;
        func_00110020(D_00362708, D_0036270C);
        D_00362728 = func_00176850() * 3.1415928f;
        D_0036272C = func_00176850() * 3.1415928f;
    } else {
        D_00362710 -= D_002BBDFC;
        D_00362728 = D_00362728 + 6.2831854820251465 / D_00362714 * D_002BBDFC;
        D_00362728 = func_00120c88(D_00362728);
        D_0036272C = D_0036272C + 6.2831854820251465 / D_00362714 * D_002BBDFC;
        D_0036272C = func_00120c88(D_0036272C);
        x = D_00362718 * sinf(D_00362728);
        y = D_0036271C * sinf(D_0036272C);
        func_00110020(D_00362708 + (s32) x, D_0036270C + (s32) y);
        D_00362718 -= D_00362720;
        D_0036271C -= D_00362724;
        if (D_00362718 < 0.0f)
            D_00362718 = 0.0f;
        if (D_0036271C < 0.0f)
            D_0036271C = 0.0f;
    }
}

/* needs make: uses rodata (jump table) */
typedef struct {
    s8 unk0;
    s8 type;   /* +0x1 */
    s16 count; /* +0x2 */
    s32 unk4;
    union {
        u32 w;
        u16 h;
    } u8_;     /* +0x8 */
    union {
        u32 w;
        struct {
            u32 lo : 5;
            u32 y : 14;
            u32 rest : 13;
        } b;
    } uc;      /* +0xC */
} TexItem;

typedef struct {
    s32 unk0;
    s32 off; /* +0x4 */
} TexHdr;

typedef struct {
    u16 unk0;
    u16 x; /* +0x2 */
    u16 y; /* +0x4 */
} TexRef;

void func_0017ffd8(TexHdr *h, TexRef *r, s16 x, s16 y) {
    TexItem *p = (TexItem *) ((u8 *) h + h->off);
    s16 dx, dy;
    s32 size;
    s32 flag;
    s32 v;
    u32 w;

    if (x == 0 && y == 0)
        return;
    if (x != 0)
        dx = x - r->x;
    if (y != 0)
        dy = y - r->y;
    if (dx == 0 && dy == 0)
        return;
    while (p->type != -1) {
        flag = 1;
        switch (p->type) {
        case 0:
            size = 20;
            flag = 0;
            break;
        case 1:
            size = 28;
            flag = 0;
            break;
        case 2:
            size = 32;
            break;
        case 4:
            size = 24;
            flag = 0;
            break;
        case 5:
            size = 32;
            flag = 0;
            break;
        case 3:
        case 6:
            size = 40;
            break;
        case 7:
            size = 48;
            break;
        }
        if (flag) {
            if (x != 0 && dx != 0) {
                v = p->u8_.h & 0x3FFF;
                if (v >= 0x3800)
                    p->u8_.w = (p->u8_.w & ~0x3FFF) + (v + dx);
            }
            if (y != 0 && dy != 0) {
                w = p->uc.w;
                v = (w >> 5) & 0x3FFF;
                if (v >= 0x3D40)
                    p->uc.w = (w & 0xFFF8001F) + ((v + dy) << 5);
            }
        }
        p = (TexItem *) ((u8 *) p + size * p->count);
        p++;
    }
}
#include "data/bss_0057_mixed.h"
#include "data/data_002E.h"
#include "data/data_0036.h"
#include "data/pieces/D_002BBDFC.h"

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
#include "data/pieces/D_002E2780.h"
extern f32 D_005758D0[];
#include "data/pieces/D_002E2790.h"
extern f32 D_005758E0[];
extern f32 D_002E27A0;
#include "data/pieces/D_00362428.h"
#include "data/pieces/D_0036242C.h"
#include "data/pieces/D_00362434.h"
#include "data/pieces/D_00362438.h"
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
        ((f32 *)&D_002E2780)[j] = D_005758D0[j] = a->a[j];
        ((f32 *)&D_002E2790)[j] = D_005758E0[j] = a->b[j];
    }
    D_002E27A0 = a->c;
    func_00176f08(a->mode, 0.0f);
    if (a->mode == 9) {
    switch (a->kind) {
    case 0:
        for (i = 0; i < D_00362440; i++) {
            r = (Rec20 *) ((i * 32) + (s32) D_00362428);
            if (r->id == a->id) {
                (*(Rec20 **)&D_00362434) = r;
                D_00362438 = 0;
                break;
            }
        }
        break;
    case 1:
        i = 0;
    loop:
        if (i < D_00362444) {
            q = func_0017adf8(((s32)D_0036242C), i++);
            if (q->id != a->id)
                goto loop;
            D_00362438 = (Path_362438 *)((s32)q);
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
#include "data/pieces/D_00362710.h"
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
#include "data/bss_0057_mixed.h"
#include "data/data_002E.h"
#include "data/data_0036.h"
#include "data/pieces/D_002BBDFC.h"

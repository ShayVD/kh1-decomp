#include "common.h"
typedef struct {
    s32 x0, x4, x8;
    s16 xc, xe;
    u16 x10, x12, x14, x16, x18, x1a, x1c, x1e, x20;
} WDesc;
typedef struct Win {
    void (*x0)(struct Win *);
    void (*x4)(struct Win *);
    s32 x8, xc, x10;
    struct Win *x14, *x18, *x1c, *x20;
    s32 x24, x28, x2c, x30, x34, x38, x3c;
    u32 x40 : 32;
    u32 b44 : 1;
    u32 r44 : 31;
    u32 b48 : 1;
    u32 r48 : 31;
    u32 x4c;
    u64 x50;
    u8 pad58[8];
    WDesc *x60;
    void *x64;
    s32 x68, x6c, x70;
    f32 x74, x78;
    s32 x7c, x80, x84, x88, x8c, x90;
    f32 x94, x98, x9c, xa0, xa4, xa8;
    s32 xac, xb0, xb4;
    s16 xb8, xba, xbc, xbe, xc0, xc2, xc4, xc6, xc8, xca, xcc, xce, xd0, xd2, xd4, xd6, xd8, xda;
    u8 xdc[16];
} Win;
extern Win D_0063F758[]; /* src/data/bss_0063.c: Obj D_0063F758[24] */
extern Win *D_00640DD8; /* src/data/bss_0064.c: s32 D_00640DD8 */
extern Win *D_00640DDC; /* src/data/bss_0064.c: s32 D_00640DDC */
extern f32 D_002BBDFC;
extern u16 D_003E90A0[];
void func_001f8270(void);
void func_001f8108(Win *);
void func_001f8120(Win *);
void func_001f8150(Win *);
void func_001f8170(Win *);
void func_001f81e8(Win *);
void func_001f46b0(Win *);
void func_001f3680(Win *);
void func_001f3648(Win *);
void func_001f3d70(Win *);
/* needs make: uses rodata */
void func_001f82b0(void) {
    Win *list[24];
    Win *w, *t;
    s32 n;
    w = D_00640DD8;
    if (w == 0) return;
    func_001f8270();
    n = 0;
    do {
        list[n++] = w;
        if (!(w->x88 & 0x40) && w->x0) {
            switch (w->x8c) {
            case 1:
            case 2:
                if (w->xa0 != 0.0f) break;
            case 3:
                w->x0(w);
                break;
            case 4:
            case 5:
                w->x0(w);
                break;
            }
        }
        w = w->x18;
    } while (w);
    for (n--; ; n--) {
    w = list[n];
    {
        if (!(w->x88 & 0x40)) {
            switch (w->x8c) {
            case 0:
                break;
            case 1:
                func_001f8108(w);
                w->x8c++;
            case 2:
                if (w->xa0 != 0.0f) {
                    w->xa0 -= D_002BBDFC;
                    if (w->xa0 < 0.0f) w->xa0 = 0.0f;
                } else {
                    func_001f8120(w);
                    func_001f46b0(w);
                    w->x4(w);
                    w->x94 += D_002BBDFC;
                    w->x98 += D_002BBDFC;
                    if (w->xa8 != 0.0f) {
                        w->xa8 -= D_002BBDFC;
                        if (w->xa8 < 0.0f) w->xa8 = 0.0f;
                    }
                }
                break;
            case 3:
                func_001f46b0(w);
                w->x4(w);
                w->x94 += D_002BBDFC;
                w->x98 += D_002BBDFC;
                if (w->xa8 != 0.0f) {
                    w->xa8 -= D_002BBDFC;
                    if (w->xa8 < 0.0f) w->xa8 = 0.0f;
                }
                if (w->xa4 != 0.0f) {
                    w->xa4 -= D_002BBDFC;
                    if (w->xa4 <= 0.0f) func_001f3680(w);
                }
                break;
            case 4:
                func_001f8150(w);
                w->x8c++;
            case 5:
                func_001f81e8(w);
                func_001f46b0(w);
                w->x4(w);
                w->x94 += D_002BBDFC;
                w->x98 += D_002BBDFC;
                if (w->xa8 != 0.0f) {
                    w->xa8 -= D_002BBDFC;
                    if (w->xa8 < 0.0f) w->xa8 = 0.0f;
                }
                break;
            }
        }
    }
    if (n == 0) break;
    }
    for (n = 0, w = D_0063F758; n < 24; n++, w++) {
        if (w->x8c == 0) continue;
        if (w->x88 & 0x40) {
            if (w->b44) {
                func_001f3648(w);
                func_001f8170(w);
            }
        } else if (w->b44) {
            if (w->x8c == 3) {
                w->x9c = D_003E90A0[w->x84];
                w->b44 = 0;
                func_001f3648(w);
            } else if (w->x88 & 0x20) {
                w->b44 = 0;
                func_001f3648(w);
            }
        }
    }
    if (D_00640DDC == 0) return;
    w = D_00640DDC;
    while (w->x20) w = w->x20;
    do {
        func_001f3d70(w);
        t = w;
        w = w->x1c;
        t->x1c = 0;
        t->x20 = 0;
    } while (w);
    D_00640DDC = 0;
}
#include "data/pieces/D_002BBDFC.h"

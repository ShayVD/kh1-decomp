#include "common.h"
#include "data/bss_0064.h"
typedef struct { s32 a, b, c, d; } Q4;
typedef struct { u8 pad[0x60]; u64 unk60; u8 pad68[0xE0 - 0x68]; u64 unkE0; u8 tail[0x160 - 0xE8]; } Q;

typedef struct { u8 pad[0x24]; s32 x; s32 y; s32 on; u8 pad30[4]; s32 v34; s32 v38; s32 v3C; s32 v40; } Clk;
extern void *D_00669358[]; /* src/data/bss_0066.c: u8 D_00669358[0x30] */
u8 D_006692F0[0x18] ALIGNED(16);
void func_00247678(s32, s32 *, s32 *);
void func_002474e8(void *, void *, s32, s32, f32);

void func_002476a0(Clk *o) {
    s32 a, b;
    s32 x, y;
    x = o->x; x += 73; y = o->y;
    if (o->on) {
        func_00247678(o->v40, &a, &b);
        func_002474e8(D_00669358[a], D_006692F0, x, y, 1.0f);
        x += 15;
        func_002474e8(D_00669358[b], D_006692F0, x, y, 1.0f);
        x += 16;
        func_002474e8(D_00669358[10], D_006692F0, x, y, 1.0f);
        x += 13;
    }
    func_00247678(o->v3C, &a, &b);
    func_002474e8(D_00669358[a], D_006692F0, x, y, 1.0f);
    x += 15;
    func_002474e8(D_00669358[b], D_006692F0, x, y, 1.0f);
    x += 17;
    func_002474e8(D_00669358[11], D_006692F0, x, y, 1.0f);
    x += 9;
    func_00247678(o->v38, &a, &b);
    func_002474e8(D_00669358[a], D_006692F0, x, y, 1.0f);
    x += 15;
    func_002474e8(D_00669358[b], D_006692F0, x, y, 1.0f);
    x += 17;
    func_002474e8(D_00669358[11], D_006692F0, x, y, 1.0f);
    x += 5;
    func_002474e8(D_00669358[11], D_006692F0, x, y, 1.0f);
    x += 4;
    func_00247678(o->v34, &a, &b);
    func_002474e8(D_00669358[a], D_006692F0, x, y, 1.0f);
    func_002474e8(D_00669358[b], D_006692F0, x + 15, y, 1.0f);
}

/* needs make: uses rodata */

typedef struct { u8 pad[8]; s32 on; s32 mode; s32 a; s32 b; } Sc;
#include "data/pieces/D_00467408.h"
int sprintf(char *, const char *, ...);
void func_002475d0(s32, s32, u8 *, f32, char *, s32);
extern char D_004917D8[];

void func_00247cf8(Sc *p) {
    char buf[16];
    u8 col[3];
    col[0] = 0xff;
    col[1] = 0xff;
    col[2] = 0xff;
    switch (p->mode) {
    case 1:
        sprintf(buf, "%01d", p->a);
        func_002475d0(69, 22, col, 1.0f, buf, D_00467408);
        if (p->on) {
            sprintf(buf, "/");
            func_002475d0(84, 22, col, 1.0f, buf, D_00467408);
            sprintf(buf, "%01d", p->b);
            func_002475d0(97, 22, col, 1.0f, buf, D_00467408);
        }
        break;
    case 2:
        sprintf(buf, D_004917D8, p->a);
        func_002475d0(69, 22, col, 1.0f, buf, D_00467408);
        if (p->on) {
            sprintf(buf, "/");
            func_002475d0(97, 22, col, 1.0f, buf, D_00467408);
            sprintf(buf, D_004917D8, p->b);
            func_002475d0(110, 22, col, 1.0f, buf, D_00467408);
        }
        break;
    case 3:
        sprintf(buf, "%03d", p->a);
        func_002475d0(69, 22, col, 1.0f, buf, D_00467408);
        if (p->on) {
            sprintf(buf, "/");
            func_002475d0(110, 22, col, 1.0f, buf, D_00467408);
            sprintf(buf, "%03d", p->b);
            func_002475d0(123, 22, col, 1.0f, buf, D_00467408);
        }
        break;
    case 4:
        sprintf(buf, "%04d", p->a);
        func_002475d0(69, 22, col, 1.0f, buf, D_00467408);
        if (p->on) {
            sprintf(buf, "/");
            func_002475d0(123, 22, col, 1.0f, buf, D_00467408);
            sprintf(buf, "%04d", p->b);
            func_002475d0(136, 22, col, 1.0f, buf, D_00467408);
        }
        break;
    }
}

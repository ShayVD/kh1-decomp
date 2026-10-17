#include "common.h"

extern s32 D_003DD308;
extern s32 D_003DD30C;
extern s32 D_003DD310;
extern s32 D_003DD314;
extern f32 D_003DD318;
extern f32 D_003DD31C;
double sin(double);
s32 func_0011ef10(s32, void (*)());
void func_001e93c8();
typedef int u128 __attribute__((mode(TI)));
typedef struct { s32 a, b, c, d; } Q4;
typedef union { u128 q; u32 w; } U128;
typedef struct { U128 dma; u64 gif[8]; Q4 v[400]; U128 end; } Pkt620;
extern Pkt620 D_00631620;
s32 func_001e9418(void) {
    s32 i;
    Q4 *p;
    Pkt620 *q;
    D_003DD318 += D_003DD31C;
    if (D_003DD318 >= 360.0f) D_003DD318 = 0.0f;
    D_003DD308 += D_003DD310;
    if (D_003DD308 > 112) D_003DD308 = 112;
    else if (D_003DD308 < 0) D_003DD308 = 0;
    D_003DD30C += D_003DD314;
    if (D_003DD30C > 112) D_003DD30C = 112;
    else if (D_003DD30C < 0) { D_003DD30C = 0; return 4; }
    q = &D_00631620;
    p = q->v;
    for (i = 0; i < 100; i++) {
        s32 v = sin((D_003DD318 + (f32)(i * 2)) * 3.1415928f / 180.0f) * 20.0;
        s32 x = i + 32;
        s32 y = i - v + 96;
        p->a = x;
        p->b = y;
        p->c = x;
        p->d = D_003DD308;
        p++;
        p->a = (v + 1928) << 4;
        p->b = (i + 2098) << 4;
        p->c = 0xFFFFFF;
        p->d = 0;
        p++;
        p->a = x;
        p->b = x;
        p->c = y;
        p->d = D_003DD30C;
        p++;
        p->a = (v + 2168) << 4;
        p->b = (i + 2098) << 4;
        p->c = 0xFFFFFF;
        p->d = 0;
        p++;
    }
    func_0011ef10(0x2BF20, func_001e93c8);
    return 0;
}

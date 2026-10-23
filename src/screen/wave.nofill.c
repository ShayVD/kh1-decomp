/* The functions of src/screen/wave.c that need nofill (gcc's delay-slot
 * filling off; h68 and h21 had them in src/hand/nofill/). */
#include "common.h"
#include "screen/wave.h"
#include "data/data_003D.h"

extern WavePkt D_00631620;

double sin(double);
s32 func_0011ef10(s32, void *);
s32 func_001e93c8(void);

s32 func_001e9418(void) {
    s32 i;
    WaveQ *p;
    WavePkt *q;
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

/* Round to the nearest integer, halves away from zero.  Nothing calls it. */
s32 func_001e9830(double x) {
    s32 i = (s32)x;
    double d = x - (double)i;
    if (d >= 0.5) {
        i++;
    } else if (d <= -0.5) {
        i--;
    }
    return i;
}

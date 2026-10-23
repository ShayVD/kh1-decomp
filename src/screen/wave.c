/* The wave transition (docs/modules.md "Session 35"), 0x001e92b8-0x001e9830.
 *
 * VM library entry func_001e9310 (D_003D9FE0 2019) opens the window
 * D_00631570 with the text D_003DD2F0 and starts the wave: func_001e9670
 * builds the GS packet D_00631620 (include/screen/wave.h) and queues
 * func_001e9418 (wave.nofill.c), which bends the 100 strips along a sine
 * (phase D_003DD318 += D_003DD31C) while the two levels D_003DD308 /
 * D_003DD30C fade in by D_003DD310 / D_003DD314, and sends the packet
 * (func_001e93c8: DMA channel 2, platform calls).  Closing the window
 * (func_001e92b8) fades the levels out (func_001e9650). */
#include "common.h"
#include "data/types/vm_rec.h"
#include "msgwin/msgwin.h"
#include "screen/wave.h"
#include "data/data_003D.h"

/* The packet (include/screen/wave.h).  Declared here, not in the header:
 * tools/shift/cover_check.py sizes only the externs of .c files. */
extern WavePkt D_00631620;
extern MsgWin D_00631570;   /* src/data/bss_0063.c: Win D_00631570 */

void func_0010bd90(void *, void *);
void func_0010bdd0(void *, void *);
void func_0010ef70(void *, void *, void *);
s32 func_0011ef10(s32, void *);
void func_002583e0(s32);
void func_00265bc0(s32, s32);
s32 func_00266c08(s32);
void func_00266f38(s32, void *);

void func_001e92b8(void);
void func_001e92e0(void);
s32 func_001e9310(VmRec *vm);
s32 func_001e93c8(void);
void func_001e9650(void);
void func_001e9670(void);
void func_001e97d8(s32 a0, s32 a1, s32 a2, s32 a3);

void func_001e92b8(void) {
    func_0010bd90(&D_00631570, 0);
    func_001e9650();
}

void func_001e92e0(void) {
    func_0010ef70(&D_00631570, &D_003DD2F0, func_001e92b8);
}

s32 func_001e9310(VmRec *vm) {
    D_00631570.v30[0] = 0.0f;
    D_00631570.v30[1] = 110.0f;
    D_00631570.v40[0] = 10.0f;
    D_00631570.v40[1] = 3.0f;
    D_00631570.h4 = 0;
    D_00631570.hc = 2;
    D_00631570.he = 2;
    D_00631570.h6 = 0;
    D_00631570.h8 = 0;
    D_00631570.b90 = 0;
    D_00631570.f1c = 45.0f;
    D_00631570.x0 = -1;
    D_00631570.f94 = 1.0f;
    func_001e9670();
    func_0010bdd0(&D_00631570, func_001e92e0);
    vm->sp -= 1;
    return 2;
}

s32 func_001e93c8(void) {
    s32 ch = func_00266c08(2);
    func_002583e0(0);
    func_00265bc0(0, 0);
    func_00266f38(ch, &D_00631620);
    return 4;
}

/* func_001e9418 is in src/screen/wave.nofill.c. */

void func_001e9650(void) {
    D_003DD310 = -4;
    D_003DD314 = -2;
}

void func_001e9670(void) {
#define pk (&D_00631620)
    WaveQ *p;
    s32 i;
    WavePkt *q;
    WaveTag *e;
    pk->dma.q = 0;
    pk->dma.w = 0x10000194;
    pk->gif[0] = 0x1000000000000002ULL;
    pk->gif[1] = 14;
    pk->gif[2] = 0x4000d;
    pk->gif[3] = 71;
    pk->gif[4] = 68;
    pk->gif[5] = 66;
    pk->gif[6] = 0x2024c000000080c8ULL;
    pk->gif[7] = 65;
    p = pk->v;
    for (i = 0; i < 100; i++) {
        p->a = i + 32;
        p->b = i + 96;
        p->c = i + 16;
        p->d = 96;
        p++;
        p->a = 0x7880;
        p->b = (i + 2098) << 4;
        p->c = 0xFFFFFF;
        p->d = 0;
        p++;
        p->a = i + 32;
        p->b = i + 96;
        p->c = i + 16;
        p->d = 96;
        p++;
        p->a = 0x8780;
        p->b = (i + 2098) << 4;
        p->c = 0xFFFFFF;
        p->d = 0;
        p++;
    }
#undef pk
    q = &D_00631620;
    e = &q->end;
    e->q = 0;
    e->w = 0x70000000;
    D_003DD308 = 0;
    D_003DD30C = 0;
    D_003DD310 = 4;
    D_003DD314 = 2;
    func_0011ef10(0xC350, func_001e9418);
}

/* Set the first strip's UV corners: the rectangle (a0, a1) + (a2, a3) of the
 * texture (h21's view: the second qword of strips 0 and 1). */
void func_001e97d8(s32 a0, s32 a1, s32 a2, s32 a3) {
    s32 x0 = (a0 + 0x700) << 4;
    s32 y0 = (a1 + 0x740) << 4;
    s32 x1 = (a0 + a2 + 0x700) << 4;
    s32 y1 = (a1 + a3 + 0x740) << 4;
    D_00631620.v[1].a = x0;
    D_00631620.v[1].b = y0;
    D_00631620.v[3].a = x1;
    D_00631620.v[3].b = y0;
    D_00631620.v[5].a = x0;
    D_00631620.v[5].b = y1;
    D_00631620.v[7].a = x1;
    D_00631620.v[7].b = y1;
}

/* func_001e9830 is in src/screen/wave.nofill.c. */

#include "common.h"
/* No u16 member: the n bitfield read gets Tex's alias set, so it does not depend on the u16
   prev/frame stores in case 0 (sched1 then issues sh prev after the idx*160 sll). */
#include "data/types/text_00100000_s11_w3.h"
/* func_0015ed80 task object (same as 00102118's Obj): union fields, alias set 0. */
typedef struct { u8 pad[0x10]; union { f32 f10; void *p10; } u10; union { f32 f14; void *p14; } u14; } Obj10;
typedef struct { u8 pad[0x10]; u8 state; u8 idx; u16 prev; u16 frame; u16 max; f32 t; } Anim;
#include "data/pieces/D_0029B420.h"
extern f32 D_002BBDFC;
s32 D_004945F0 ALIGNED(16);
Obj10 *func_0015ed80(s32, void (*)(void));
void func_001019c8(void);
void *func_00121e28(s32, void *);
void func_00101a18(Tex *, u8, void *);
void func_00101a70(Tex *, u16, u16, void *);
void func_00101970(s32, void *, void *);
s32 func_00101bb8(Anim *o) {
    Obj10 *h;
    void *a, *b;
    switch (o->state) {
    case 0: {
        Tex *x = &D_0029B420[o->idx];
        o->prev = 1;
        o->frame = 0;
        o->t = 0;
        o->max = x->n;
        o->state++;
        break; }
    case 1:
        o->t += D_002BBDFC / D_0029B420[o->idx].spd;
        o->frame = o->t * 0.5f;
        if (o->frame >= o->max) {
            o->frame = 0;
            o->t = 0;
        }
        break;
    }
    switch (D_0029B420[o->idx].type) {
    case 0:
        if (o->frame != o->prev) {
            h = func_0015ed80(D_004945F0++ + 10000, func_001019c8);
            a = func_00121e28(32, &h->u10);
            b = func_00121e28(64, &h->u14);
            h->u10.p10 = a;
            h->u14.p14 = b;
            func_00101a18(&D_0029B420[o->idx], o->frame, b);
            func_00101970(0, a, b);
        }
        break;
    case 1:
    case 2:
        if (o->frame != o->prev) {
            h = func_0015ed80(D_004945F0++ + 10000, func_001019c8);
            a = func_00121e28(32, &h->u10);
            b = func_00121e28(128, &h->u14);
            h->u10.p10 = a;
            h->u14.p14 = b;
            func_00101a70(&D_0029B420[o->idx], o->frame, o->max, b);
            func_00101970(1, a, b);
        }
        break;
    }
    o->prev = o->frame;
    return 0;
}
#include "data/pieces/D_002BBDFC.h"

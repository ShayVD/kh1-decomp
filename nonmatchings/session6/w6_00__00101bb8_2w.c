/* 2 words off, mode hand/nostrict: case 0 constant 1 for o->prev lands in v0, original v1 (li v1,1; sh v1,18(s3)). */
#include "common.h"
typedef struct { u16 n; u8 pad2[6]; u16 spd; s8 type; u8 padb[0x95]; } Tex;
typedef struct { u8 pad[0x10]; s32 a; s32 b; } Obj10;
typedef struct { u8 pad[0x10]; u8 state; u8 idx; u16 prev; u16 frame; u16 max; f32 t; } Anim;
extern Tex D_0029B420[];
extern f32 D_002BBDFC;
extern s32 D_004945F0;
Obj10 *func_0015ed80(s32, void (*)(void));
void func_001019c8(void);
s32 func_00121e28(s32, s32 *);
void func_00101a18(Tex *, u8, s32);
void func_00101a70(Tex *, u16, u16, s32);
void func_00101970(s32, s32, s32);
s32 func_00101bb8(Anim *o) {
    Obj10 *h;
    s32 a, b;
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
            a = func_00121e28(32, &h->a);
            b = func_00121e28(64, &h->b);
            h->a = a;
            h->b = b;
            func_00101a18(&D_0029B420[o->idx], o->frame, b);
            func_00101970(0, a, b);
        }
        break;
    case 1:
    case 2:
        if (o->frame != o->prev) {
            h = func_0015ed80(D_004945F0++ + 10000, func_001019c8);
            a = func_00121e28(32, &h->a);
            b = func_00121e28(128, &h->b);
            h->a = a;
            h->b = b;
            func_00101a70(&D_0029B420[o->idx], o->frame, o->max, b);
            func_00101970(1, a, b);
        }
        break;
    }
    o->prev = o->frame;
    return 0;
}

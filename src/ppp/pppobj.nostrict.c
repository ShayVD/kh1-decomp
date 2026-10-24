/* The ppp object controls, without strict aliasing (docs/modules.md
 * "Session 51"): kill the objects of D_00364130 with a key or in a key range
 * (func_0017fb98 ... func_0017fe60) and pause or resume every object
 * (func_0017ff38: flags xb7 / xb1).  pppobj.c has the rest.  Read from the
 * code, not proved by a boot. */
#include "common.h"
#include "data/types/nostrict_text_00170000_s6_10.h"
#include "data/pieces/D_00362438.h"
#include "data/pieces/D_00362424.h"
#include "data/pieces/D_0036244C.h"
#include "data/pieces/D_00362454.h"
#include "data/pieces/D_00362710.h"
#include "data/pieces/D_00364130.h"

/* func_0017fb98 (from hand/nostrict/text_00170000_s6_10.c). */
typedef Sub80_364130 Sub80;
typedef E0C0_364130 E0C0;
void func_0011d3c8(s32, s32, s32);
void func_00182788(E0C0 *);
void func_001827f0(E0C0 *);
void func_0017fb98(s32 key) {
    s32 i;
    s32 off;
    E0C0 *t;
    Sub80 *s;
    off = 0;
    t = D_00364130.e0C0;
    i = 0;
    s = &t->s;
    for (; i < 256; i++) {
        if ((s->flags & 1) && s->key == key) {
            E0C0 *e;
            if (s->p8c->xfc) func_0011d3c8(s->p8c->xfc, s->xa8, 60);
            e = (E0C0 *)(off + (u32)t);
            func_00182788(e);
            func_001827f0(e);
            return;
        }
        s = (Sub80 *)((u8 *)s + sizeof(E0C0));
        off += sizeof(E0C0);
    }
}

/* func_0017fcd8 (from hand/nostrict/text_00170000_s6_10.c). */
void func_00182840(E0C0 *);
void func_0017fcd8(s32 key) {
    s32 i;
    s32 off;
    E0C0 *t;
    Sub80 *s;
    off = 0;
    t = D_00364130.e0C0;
    i = 0;
    s = &t->s;
    for (; i < 256; i++) {
        if ((s->flags & 1) && s->key == key) {
            E0C0 *e;
            if (s->p8c->xfc) func_0011d3c8(s->p8c->xfc, s->xa8, 60);
            e = (E0C0 *)(off + (u32)t);
            func_00182788(e);
            func_00182840(e);
            return;
        }
        s = (Sub80 *)((u8 *)s + sizeof(E0C0));
        off += sizeof(E0C0);
    }
}

/* func_0017fd88 (from hand/nostrict/text_00170000_s6_10.c). */
void func_0017fd88(s32 lo, s32 n) {
    s32 i;
    s32 off = 0;
    E0C0 *t = D_00364130.e0C0;
    Sub80 *s = &t->s;
    for (i = 0; i < 256; i++) {
        if (s->flags & 1) {
            s32 d = s->x88 - lo;
            if (d >= 0 && d < n) {
                E0C0 *e;
                if (s->p8c->xfc) func_0011d3c8(s->p8c->xfc, s->xa8, 60);
                e = (E0C0 *)(off + (u32)t);
                func_00182788(e);
                func_001827f0(e);
            }
        }
        s = (Sub80 *)((u8 *)s + sizeof(E0C0));
        off += sizeof(E0C0);
    }
}

/* func_0017fe60 (from hand/nostrict/text_00170000_s6_10.c). */
void func_0017fe60(s32 lo, s32 n) {
    s32 i;
    s32 off = 0;
    E0C0 *t = D_00364130.e0C0;
    Sub80 *s = &t->s;
    for (i = 0; i < 256; i++) {
        if (s->flags & 1) {
            s32 d = s->x88 - lo;
            if (d >= 0 && d < n) {
                E0C0 *e;
                if (s->p8c->xfc) func_0011d3c8(s->p8c->xfc, s->xa8, 60);
                e = (E0C0 *)(off + (u32)t);
                func_00182788(e);
                func_00182840(e);
            }
        }
        s = (Sub80 *)((u8 *)s + sizeof(E0C0));
        off += sizeof(E0C0);
    }
}

/* func_0017ff38 (from hand/nostrict/text_00170000_s6_10.c). */
#define D_00364130 D_00364130_ff38
typedef struct E0C0_7ff38 {
    u8 pad0[0x86];
    u16 flags;
    u8 pad88[0xb1 - 0x88];
    u8 xb1;
    u8 padb2[5];
    u8 xb7;
    u8 padb8[0xc0 - 0xb8];
} E0C0_7ff38;
extern E0C0_7ff38 D_00364130[256] __asm__("D_00364130");
void func_0017ff38(s32 on) {
    s32 i;
    for (i = 0; i < 256; i++) {
        if (D_00364130[i].flags & 1) {
            if (on) {
                D_00364130[i].xb7 = 1;
                D_00364130[i].xb1 |= 0x80;
            } else {
                D_00364130[i].xb7 = 0;
                D_00364130[i].xb1 &= 0x7f;
            }
        }
    }
}
#undef D_00364130


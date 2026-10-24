#include "common.h"
#include "platform/math.h"

#include "data/pieces/D_002BBDE0.h"
extern s32 D_002C1310[];

void func_0011dc28(s32 *a, s32 *b, s32 *c) {
    s32 i = 3;
    s32 *p;
    if (D_002BBDE0 == i) return;
    p = D_002C1310;
    for (; i >= 0; i--) {
        if (*a == *p++) {
            if (*b < 9216 && *c < 9216) { *b = 9216; *c = 9216; }
        }
    }
}

typedef struct { s32 id; u8 pad[16]; u8 f14; } S0011dc98;

void func_0011dc98(S0011dc98 *a) {
    s32 i;
    s32 *p;
    if (D_002BBDE0 == 3) return;
    p = D_002C1310;
    for (i = 3; i >= 0; i--) {
        if (a->id == *p++) {
            a->f14 = 0;
        }
    }
}

typedef struct Node { u16 type; u16 f2; s32 key; struct Node *next; s32 data; } Node;
typedef struct { u16 size; u16 count; u8 *base; Node *head; u8 *cur; } Pool;

u8 *func_0011efe8(Pool *p) {
    u8 *cur = p->cur;
    u8 *base;
    u8 *end;
    s32 i;
    if (cur == 0) cur = p->base;
    base = p->base;
    end = base + p->size * p->count;
    for (i = 0; i < p->count; i++) {
        cur += p->size;
        if (cur >= end) cur = base;
        if (*(u16 *)cur == 0) return cur;
    }
    return 0;
}

Node *func_0011f2e0(Pool *p, s32 data) {
    Node *it;
    for (it = p->head; it; it = it->next) {
        if (it->data == data) return it;
    }
    return 0;
}

s32 func_0011f320(Pool *p, Node *n) {
    Node *it, *prev = 0;
    for (it = p->head; it; it = it->next) {
        if (it == n) {
            if (prev) prev->next = it->next; else p->head = it->next;
            it->next = 0;
            return 1;
        }
        prev = it;
    }
    return 0;
}

#include "data/types/text_00110000_h4_p.h"
extern MaskEnt D_002C5990[];

u32 func_0011f628(u32 m) {
    u32 r = 0;
    u32 i;
    for (i = 0; i < 30; i++) {
        if ((m & D_002C5990[i].mask) == D_002C5990[i].mask) r |= D_002C5990[i].val;
    }
    return r;
}

typedef struct { u64 a, b; } Q128;

void func_0011fb78(Q128 *p, u64 a1, Q128 *end) {
    u64 v = (end - p - 1) | (a1 << 28);
    if ((u32)end > 0x6fffffff) v |= 0x8000000000000000;
    *(u64 *)p = v;
}

typedef struct { u32 flags; u8 pad[44]; s32 x30; s32 x34; } Slot;
Slot D_004F3230[0x10] ALIGNED(16);
extern s32 D_002C5C44;
Slot *func_0011ffd0(void) {
    s32 i;
    Slot *s = D_004F3230;
    for (i = 0; i < 16; i++, s++) {
        if (!(s->flags & 1)) {
            s->flags |= 1;
            s->x34 = D_002C5C44++;
            s->x30 = -1;
            return s;
        }
    }
    return 0;
}

typedef struct { u8 pad[68]; s32 x44; s32 x48; } Ent4C;
Ent4C D_004E4528[0x10] ALIGNED(8);
u8 D_004F35B0[0x1000] ALIGNED(16);

#include "data/pieces/D_002C5C80.h"

/* Heap block table: 512 entries, D_004F6DB0 (the rover) sits right after it. */
#include "data/types/text_00110000_h4.h"

/* Actor table: 1200-byte entries from D_002C64A0 up to D_002E26A0. */

/* needs make: uses rodata */
/* "%3d" at D_0048D110, "amusic/music" at D_0048D118 (inlined strcpy). */
int sprintf(char *, const char *, ...);
char *strcat(char *, const char *);
char *strcpy(char *, const char *);
extern char D_0048D198[]; /* ".bgm", shared with a later function */

void func_0011ea40(s32 n, char *out) {
    char buf[80];
    sprintf(buf, "%3d", n);
    if (buf[0] == ' ') {
        buf[0] = '0';
        if (buf[1] == ' ') buf[1] = '0';
    }
    strcpy(out, "amusic/music");
    strcat(out, buf);
    strcat(out, D_0048D198);
}
#include "data/bss_004F_mixed.h"
#include "data/data_002C.h"
#include "data/data_0048.h"
#include "data/pieces/D_002C5990.h"

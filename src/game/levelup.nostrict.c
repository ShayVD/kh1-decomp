/* Level-up, without strict aliasing (docs/modules.md "Session 52"):
 * func_0015b268 raises a party member's level (D_00304BE8->m[i].sub.lv) and
 * applies the level's bonus through func_0015ae48 (HP and MP maximums,
 * abilities ...); func_0015b098 builds the notice lines in the ring of 32
 * string buffers D_00551970 (defined here, func_0015b060 hands them out).  Read from the code, not proved by a boot. */
#include "common.h"
#include "data/pieces/D_00308CDC.h"
#include "data/pieces/D_00304BE8_s.h"
#include "platform/math.h"
#include "data/types/nostrict_text_00150000_h58_p.h"
#include "data/pieces/D_002E31B0.h"
#include "data/pieces/D_002C58A0.h"
#include "data/pieces/D_002E26A0.h"
#include "data/pieces/D_002C58B0.h"
#include "data/pieces/D_00351A30.h"
#include "data/pieces/D_002E31A8.h"
#include "data/pieces/D_002E3168.h"
#include "data/pieces/D_002E2790.h"
#include "data/pieces/D_002E2780.h"
#include "data/types/nostrict_text_00150000_h58.h"
#include "data/pieces/D_00304BE8.h"
#include "data/pieces/D_002BBDE4.h"

/* func_0015ae48 (from hand/nostrict/text_00150000_h58.c). */
typedef Sub_304be8 Sub116;
typedef struct { u8 pad[0x40]; s32 x40; u8 pad44[4]; s32 x48; s32 x4c; s32 x50; u8 pad54[0x8c]; s32 xe0; } St6c;
typedef struct { u8 pad[0x6c]; St6c *x6c; } P6c;
P6c *func_0013daf8(s32);
void func_00141468(P6c *, s32);
void func_00141540(P6c *, s32);
void func_0013c8c8(s32, s32);
/* ---- func_0015ae48 ---- */
void func_0015ae48(s32 i, u32 k) {
    Sub116 *s = &D_00304BE8->m[i].sub;
    P6c *p = func_0013daf8(i);
    s32 v;
    switch (k) {
    case 0:
        break;
    case 1:
        s->hpmax += 3;
        if (p) {
            p->x6c->x40 += 3;
            func_00141468(p, 3);
            return;
        }
        s->x1 += 3;
        break;
    case 2:
        s->mpmax += 1;
        if (p) {
            p->x6c->x48 += 1;
            func_00141540(p, 1);
            return;
        }
        s->x3 += 1;
        break;
    case 3:
        s->x5 = s->x5 + 2 > 100 ? 100 : s->x5 + 2;
        if (p) {
            v = p->x6c->xe0 + 2;
            p->x6c->xe0 = v < 101 ? v : 100;
        }
        break;
    case 4:
        s->x6 = s->x6 + 2 > 100 ? 100 : s->x6 + 2;
        if (p) {
            v = p->x6c->x4c + 2;
            p->x6c->x4c = v < 101 ? v : 100;
        }
        break;
    case 5:
        s->x7 = s->x7 + 2 > 100 ? 100 : s->x7 + 2;
        if (p) {
            v = p->x6c->x50 + 2;
            p->x6c->x50 = v < 101 ? v : 100;
        }
        break;
    case 6:
        s->x21++;
        break;
    case 7:
        s->x18++;
        break;
    default:
        func_0013c8c8(k & ~0x80, i);
        break;
    }
}

/* func_0015b060 (from hand/nostrict/text_00150000_h58.c). */
typedef struct { u8 b[32]; } E551970;
E551970 D_00551970[0x20] ALIGNED(16);
extern s32 D_00351AC0;
/* At the end, not with the includes: declaring D_005516C0 earlier changes how func_0015b060 forms
   the D_00551970 address (gcc 2.96 rtx ordering), so the header comes after the code here. */
char *func_0015b060(void) {
    E551970 *r = &D_00551970[D_00351AC0++];
    if (D_00351AC0 >= 32) D_00351AC0 = 0;
    return (char *)r;
}

/* func_0015b098 (from hand/nostrict/text_00150000_h58.c). */
char *strcpy(char *, const char *);
char *strcat(char *, const char *);
typedef struct { s32 x0; char *x4; } R478a0;
extern s32 D_00351B20[][2];
char *func_00147808(s32);
R478a0 *func_001478a0(s32);
void func_00244670(s32, char *, char *);
void func_0015b098(s32 a, s32 *ids) {
    char *buf[2];
    s32 i;
    R478a0 *r;
    for (i = 0; i < 2; i++) {
        buf[i] = 0;
        if (ids[i] == 0) continue;
        if (ids[i] >= 0) {
            if (ids[i] < 8) {
                char *b = func_0015b060();
                buf[i] = b;
                strcpy(b, func_00147808(D_00351B20[ids[i]][i]));
                continue;
            }
        }
        r = func_001478a0(ids[i] & ~0x80);
        buf[i] = func_0015b060();
        switch (D_002BBDE4) {
        case 0:
        case 4:
        case 7:
            strcpy(buf[i], r->x4);
            strcat(buf[i], func_00147808(344));
            break;
        case 1:
        case 2:
        case 5:
        case 6:
            strcpy(buf[i], func_00147808(344));
            strcat(buf[i], r->x4);
            strcat(buf[i], "h");
            break;
        case 3:
            strcpy(buf[i], func_00147808(344));
            strcat(buf[i], r->x4);
            break;
        }
    }
    if (buf[0]) func_00244670(a, buf[0], buf[1]);
}

/* func_0015b268 (from hand/nostrict/text_00150000_h59.c). */
typedef W606Mem_304be8 Mem59;
extern void *D_00351AC8[][2];
extern void *D_00351B18[];
u8 *func_001477c8(void *p);
void func_00153e80(void *);
#define func_0015ae48 ((void (*)(s32, s32)) func_0015ae48)
#define func_0013daf8 ((void *(*)(s32)) func_0013daf8)
#define func_0015b098 ((void (*)(void *, s32 *)) func_0015b098)
void func_0015b268(s32 i) {
    s32 buf[2];
    Mem59 *m = &D_00304BE8->m[i];
    u8 *p;
    void *o, *o2;
    s32 v, j, n, cnt;

    buf[0] = func_001477c8(D_00351AC8[i][0])[m->sub.lv - 1];
    func_0015ae48(i, buf[0]);
    m->sub.lv++;
    o = func_0013daf8(i);
    if (o) func_00153e80(o);
    buf[1] = 0;
    if (i == 0) {
        o2 = D_00351B18[D_00304BE8->x48c];
    } else {
        o2 = D_00351AC8[i][1];
    }
    p = func_001477c8(o2) + m->sub.w34.h.x34 - 1;
    if (!o && (D_00304BE8->x83e >> i & 1)) {
        cnt = 0;
        n = 100 - m->sub.w34.h.x34;
        for (j = 0; j < n; j++) {
            if (p[j]) cnt++;
        }
        if (cnt < 100 - m->sub.lv) return;
    }
    buf[1] = 0;
    n = m->sub.lv - m->sub.w34.h.x34;
    for (j = 0; j < n; j++) {
        m->sub.w34.h.x34++;
        buf[1] = *p++;
        if (buf[1]) {
            func_0015ae48(i, buf[1]);
            break;
        }
    }
    if (o) func_0015b098(o, buf);
}
#undef func_0015ae48
#undef func_0013daf8
#undef func_0015b098


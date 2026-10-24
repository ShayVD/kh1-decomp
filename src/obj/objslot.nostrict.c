/* Object data slots, without strict aliasing (docs/modules.md "Session
 * 52"): func_00155d70 (is a slot loaded with this name), the load task
 * func_00155ef8, func_001557d0.  Read from the code, not proved by a boot. */
#include "common.h"
#include "data/bss_0055.h"
#include "data/pieces/D_00308CDC.h"
#include "data/pieces/D_002C58B0.h"
#include "data/pieces/D_002C58A0.h"
#include "data/pieces/D_002E26A0.h"
#include "data/types/nostrict_text_00150000_h35.h"
#include "data/pieces/D_00304BE8_s.h"
#include "platform/math.h"
#include "data/types/nostrict_text_00150000_h58_p.h"
#include "data/pieces/D_002E31B0.h"

/* func_001557d0 (from hand/nostrict/text_00150000_h35.c). */
extern u32 D_002C5958;
extern E550400 D_00550400[];
void func_00146928(s32);
void func_00155760(void *);
/* ---- func_001557d0 / func_00155878 ---- */
typedef struct { u8 pad[0x130]; void *p130; } Act_557d0;
extern Act_557d0 *D_002E26A0_557d0[3] __asm__("D_002E26A0");
#define D_002E26A0 D_002E26A0_557d0
void func_001557d0(void) {
    s32 i;
    D_002C5958 &= ~0x40000;
    func_00146928(-6);
    for (i = 0; i < 64; i++) {
        D_00550400[i].h.w &= ~0x10000;
    }
    for (i = 0; i < 3; i++) {
        if (D_002E26A0[i]) func_00155760(D_002E26A0[i]->p130);
    }
}
#undef D_002E26A0

/* func_00155d70 (from hand/nostrict/text_00150000_h35.c). */
typedef struct { u8 pad[0x1C]; s32 w1C; s32 w20; u8 rest[0x40000 - 0x24]; } EFE0000;
extern EFE0000 D_00FE0000[];
s32 strcmp(const char *, const char *);
/* ---- func_00155d70 ---- */
s32 func_00155d70(s32 i, const char *name) {
    E550400 *e = &D_00550400[i];
    s32 j, n;
    if (e->h.b.id != i || strcmp(e->name, name) != 0) return 0;
    n = (e->w44 - (s32)&D_00FE0000[i] + 0x3FFFF) / 0x40000;
    for (j = 0; j < n; j++) {
        if (e[j].h.b.id != i) return 0;
    }
    return 1;
}

/* func_00155ef8 (from hand/nostrict/text_00150000_h58.c). */
char *strcpy(char *, const char *);
s32 func_00120748(char *, void *, void *, s32);
typedef struct { union { u32 w; struct { u8 b[3]; u8 st; } s; } u; char n1[32]; char n2[32]; void *x44; } E550400_55ef8;
typedef struct { u8 pad[0x1c]; s32 x1c; s32 x20; } R8;
typedef struct { s32 x0; u32 x4; R8 *x8; u8 padc[0x49]; s8 b55; s8 b56; u8 pad57[9]; char *x60; char *x64; } R14;
typedef struct { u8 pad[0x14]; R14 *x14; void (*x18)(s32); } T155ef8;
void func_00155ad8(s32, s32);
s32 func_00155e48(s32, s32, char *);
s32 func_00146b90(void *, s32, void *, void *);
void func_00155c68(), func_00155cf8(), func_00155ee8();
extern E550400_55ef8 D_00550400_00155ef8[] __asm__("D_00550400");
#define D_00550400 D_00550400_00155ef8
/* ---- func_00155ef8 ---- */
s32 func_00155ef8(T155ef8 *a) {
    R14 *r = a->x14;
    E550400_55ef8 *e = &D_00550400[r->b55];
    switch (e->u.s.st) {
    case 0:
        e->u.s.st = 1;
        if (!func_00155d70(r->b55, r->x60)) {
            func_00155ad8(r->b55, r->b56);
            func_00120748(r->x60, r->x8, func_00155c68, 0);
            strcpy(e->n1, r->x60);
            e->n2[0] = 0;
            e->x44 = r->x8;
            return 8;
        }
        e->u.s.st++;
    case 2:
        e->u.s.st++;
        if (!func_00155e48(r->b55, r->b56, r->x64)) {
            func_00155ad8(r->b55, r->b56);
            func_00120748(r->x64, e->x44, func_00155cf8, 0);
            strcpy(e->n2, r->x64);
            return 8;
        }
        e->u.s.st++;
    case 4:
        e->u.s.st++;
        if (!(r->x4 & 0x4000) && r->x8->x20 - r->x8->x1c > 0) {
            e->u.w |= 0x10000;
            if (func_00146b90((u8 *)r->x8 + r->x8->x1c, -6, func_00155ee8, e)) return 8;
        }
        e->u.s.st++;
    case 6:
        e->u.w |= 0x40000;
        if (a->x18) a->x18(r->x0);
        return 4;
    }
    return 8;
}
#undef D_00550400


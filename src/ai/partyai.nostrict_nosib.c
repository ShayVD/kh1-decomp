/* The party members' AI, without strict aliasing or scheduling across
 * branches (docs/modules.md "Session 51"): func_00170170 turns the stick
 * values f124 / f12C into a move for some actor states.  partyai.c has the
 * rest.  Read from the code, not proved by a boot. */
#include "common.h"

/* func_00170170 (from hand/nostrict_nosib/text_00170000_s7_w30.c). */
typedef struct { u8 pad[4]; f32 f4; f32 f8; } Spd70;
typedef struct { u8 pad[0x6C]; Spd70 *p6C; s32 w70; } Act70;
typedef struct { u8 pad[0x120]; f32 f120, f124, f128, f12C; } Pad70;
/* func_00170170: MATCH hand/nostrict + -fno-optimize-sibling-calls (wqb03_rr 0048ea00), plain if/else chains, no gotos: the sibling pass cleanup_cfg moves the y = 8.0f block */
void func_00170170(Act70 *a, Pad70 *p) {
    f32 x = p->f124;
    f32 y = p->f12C;
    switch (a->w70) {
    case 10:
    case 15:
        p->f120 = p->f128 = 0.0f;
        if (x < -5.0f) x = -1.0f;
        else if (x > 5.0f) x = 1.0f;
        else x = 0.0f;
        y = 1.0f;
        break;
    case 13:
        p->f120 = p->f128 = 0.0f;
        if (x < -5.0f) x = -1.0f;
        else if (x > 5.0f) x = 1.0f;
        else x = 0.0f;
        y = 2.0f;
        break;
    case 4:
    case 8:
        if (x < -5.0f) x = -8.0f;
        else if (x > 5.0f) x = 8.0f;
        else x = 0.0f;
        if (y < 5.0f) y = 0.0f;
        else if (y < 15.0f) y = 8.0f;
        else y = 16.0f;
        break;
    case 24:
    case 25:
        if (x < -5.0f) x = -8.0f;
        else if (x > 5.0f) x = 8.0f;
        else x = 0.0f;
        if (y < 5.0f) y = 0.0f;
        else if (y < 15.0f) y = 4.0f;
        else y = 8.0f;
        break;
    case 26:
        y = 0.0f;
        x = 0.0f;
        break;
    default:
        if (y < 5.0f) y = 0.0f;
        else if (y < 15.0f) y = a->p6C->f4;
        else if (y < 25.0f) y = a->p6C->f8;
        else y = a->p6C->f8;
        x = 0.0f;
        break;
    }
    p->f124 = x;
    p->f12C = y;
}


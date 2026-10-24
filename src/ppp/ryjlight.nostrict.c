/* The pppRyjLight class's frame, -fno-strict-aliasing (docs/modules.md
 * "Session 49"): it takes a light from func_001226f0 (type and three flag
 * bits from the key) on the first frame and each frame sets its position
 * (the work's position plus D_003701D0), direction, colour (the work's RGBA
 * / 255) and intensity.  ryjlight.c has the Con and Des.
 * Read from the code, not proved by a boot. */
#include "common.h"
#include "platform/vu.h"
#include "ppp.h"
#include "data/pieces/D_003701D0.h"

typedef FV4_3701d0 FV4;
typedef struct {
    u8 pad0[0xc];
    f32 intensity;
    FV4 pos;
    FV4 dir;
    FV4 col;
} Light;
typedef struct {
    u8 pad0[4];
    f32 x, y, z;
    f32 f10;
    u8 type, b15, b16, b17;
} LtKey;
typedef struct { u8 pad[8]; u8 r, g, b, a; } LtCol;
Light *func_001226f0(s32, s32, s32);

void pppRyjLightFrame(void *obj, LtKey *k, PppEntry *e) {
    Light **w = (Light **)((u8 *)obj + e->offsets[2] + 0xA0);
    Light *l = *w;
    FV4 *p;
    LtCol *c;
    s32 fl = 0;
    if (k->b15) fl |= 1;
    if (k->b16) fl |= 2;
    if (k->b17) fl |= 4;
    if (l == NULL) {
        *w = func_001226f0(k->type, fl, 0);
        if (*w == NULL)
            return;
        l = *w;
    }
    p = (FV4 *)((u8 *)obj + e->offsets[1] + 0xA0);
    c = (LtCol *)((u8 *)obj + e->offsets[0] + 0xA0);
    l->pos.x = p->x + D_003701D0.x;
    l->pos.y = p->y + D_003701D0.y;
    l->pos.z = p->z + D_003701D0.z;
    l->pos.w = 1.0f;
    l->dir.x = k->x;
    l->dir.y = k->y;
    l->dir.z = k->z;
    l->dir.w = 1.0f;
    l->col.x = c->r;
    l->col.y = c->g;
    l->col.z = c->b;
    l->col.w = c->a;
    PlatVu0ScaleVector(&l->col, &l->col, 0.00392156851f);
    l->intensity = k->f10;
}

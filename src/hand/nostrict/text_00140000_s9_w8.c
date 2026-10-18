#include "common.h"
/* func_00149c80 (hand/nostrict): func_001477c8 result read into a local `u8 *s` in its own statement before sprintf; this lengthens id's live range so param i (s1) outranks id (s2) in global-alloc. */
typedef struct { u8 x0[6]; u8 x6; u8 x7; } Q9c;
typedef struct { u8 pad[0x2c]; Q9c x2c; u8 pad34[0x74 - 0x34]; } M9c;
typedef struct { u8 pad[4]; M9c m[10]; } S9c;
extern S9c *D_00304BE8;
typedef struct {
    u32 used : 1;
    u32 state : 2;
    u32 b3 : 1;
    u32 rest : 28;
    s32 x4;
    s32 x8;
    u8 padc[4];
    s32 x10;
    u8 pad14[8];
    s32 x1c;
} Ent9c;
typedef struct { u8 pad[6]; s16 x6; } R9c;
extern Ent9c D_0054C1B0[];
extern void *D_00350CE8[];
extern s32 D_00350D14;
extern char D_0048E410[];
R9c *func_00147840(s32);
u8 *func_001477c8(void *);
s32 sprintf(char *, const char *, ...);
void func_00120748(char *, s32, void *, s32);
void func_00149bd0();
s32 func_00149c80(s32 i, s32 a) {
    char buf[32];
    Q9c *m = (Q9c *)((u32)D_00304BE8 + (u32)(i * 0x74 + 0x30));
    Ent9c *e;
    s32 id, j;
    u8 *s;
    if (m->x6 == 0) return 0;
    id = func_00147840(m->x6)->x6;
    for (e = D_0054C1B0, j = 0; j < 3; j++, e++) {
        if (e->used && e->x4 == i && e->x8 == id) {
            e->state = 1;
            return 0;
        }
    }
    e = D_0054C1B0;
    if (i != 0) {
        e++;
        for (j = 0; j < 2; j++, e++) {
            if (!e->used || !e->state) break;
        }
    }
    e->used = 1;
    e->state = 1;
    e->b3 = 0;
    e->x1c = a;
    e->x4 = i;
    e->x8 = id;
    if (id == 0) return 0;
    s = func_001477c8(D_00350CE8[i]);
    sprintf(buf, D_0048E410, s + id * 0x58 - 0x58, D_00350D14);
    func_00120748(buf, e->x10, func_00149bd0, 0);
    return 1;
}

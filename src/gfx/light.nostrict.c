/* The scene lights: the light set D_002C5C80 (func_00122c70 / func_00122cb8
 * reset it, func_00122cf0 the per-frame update), func_001226f0 /
 * func_00122768 a light's colour and its release (the ppp light effects use
 * them), the light matrices for a model (func_00122770, func_001229c0),
 * func_00122588 the light vector for an object, func_00122ab0 the room's
 * light file. Flag mode: nostrict (the other modes are in the sibling
 * files). Read from the code, not proved by a boot (docs/modules.md "Session
 * 54"). */
#include "common.h"
#include "data/pieces/D_002C5968.h"
#include "data/bss_004E.h"
#include "data/bss_004F.h"
#include "data/types/nostrict_text_00110000_s6_04_p.h"
#include "data/pieces/D_002C5960.h"
#include "data/pieces/D_002C58B0.h"
#include "data/types/nostrict_text_00110000_s6_04.h"
#include "data/pieces/D_002C5C48.h"
#include "data/pieces/D_002C5C80.h"
#include "data/pieces/D_002C5910.h"

/* func_001229c0 (from hand/nostrict/text_00110000_s6_04.c). */
void func_002675a8(void *, void *);
typedef Lt64_2c5c80 Lt64;
typedef struct { u8 pad[0x420]; u32 mask; u8 pad2[0xc]; f32 pos[4]; } Obj430;
void sceVu0CopyMatrix(f32 (*)[4], f32 (*)[4]);
void func_001229c0(Obj430 *o, f32 m[4][4]) {
    s32 i;
    s32 b;
    f32 *row;
    Lt64 *e;
    sceVu0CopyMatrix(m, D_002C5910);
    { s32 j; for (j = 3; j >= 0; j--) m[3][j] = 1.0f; }
    for (i = 0, e = &D_002C5C80, b = 1, row = m[0]; i < 31; i++, e++) {
        if (o->mask & (b << i)) {
            if (e->kind < 5) if (e->kind >= 2) {
                func_002675a8(row, &e->col.x);
                row += 4;
            }
        }
    }
    func_002675a8(m[3], o->pos);
}


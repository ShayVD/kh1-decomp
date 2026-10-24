/* The object scripts' second command table, without strict aliasing
 * (docs/modules.md "Session 51"): func_00176960 turns an s16 angle vector
 * into radians.  objcmd2.c has the rest of D_00362340.  Read from the code,
 * not proved by a boot. */
#include "common.h"
#include "data/pieces/D_0035BD40.h"
#include "data/pieces/D_002E27C8.h"
#include "data/pieces/D_0035C440.h"
#include "data/pieces/D_0035C460.h"
#include "data/pieces/D_002C58B0.h"

/* func_00176960 (from hand/nostrict/text_00160000_s6_09.c). */
void func_002675a8(void *, void *);
typedef struct { f32 x, y, z, w; } V4_69;
typedef struct { u8 pad[4]; s32 *x4; } Y69;
typedef struct { Y69 *x0; void *x4; } A69;
void func_00176960(A69 *a) {
    V4_69 v;
    v.x = a->x0->x4[0];
    v.y = a->x0->x4[1];
    v.z = a->x0->x4[2];
    v.x = v.x * 3.14159251f * (1.0f / 32768.0f);
    v.y = v.y * 3.14159251f * (1.0f / 32768.0f);
    v.z = v.z * 3.14159251f * (1.0f / 32768.0f);
    v.w = 0.0f;
    func_002675a8(a->x4, &v);
}


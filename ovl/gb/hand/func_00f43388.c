/* gb.x func_00f43388: matched by hand. */
#include "ovl.h"
#include "platform/thread.h"

typedef struct {
    s8 used;      /* 0 */
    s8 b1;        /* 1 */
    s8 b2;        /* 2 */
    s8 b3;        /* 3 */
    s8 pad4[2];
    s8 b6;        /* 6 */
    u8 b7;        /* 7 */
    s8 pad8[4];
    s16 h12;      /* 12 */
    s8 pad14[14];
    s32 w28, w32, w36, w40, w44; /* 28..44 */
    f32 f48;      /* 48 */
    s32 w52;      /* 52 */
    s8 c56, c57, c58, c59;
    void (*fn)(void); /* 60 */
    s32 w64;      /* 64 */
} E68;
void func_00f43350(void);
extern E68 *D_00F829C0;
extern u8 D_00F703C4;
E68 *func_00f43388(void) {
    E68 *e = D_00F829C0;
    s32 i;
    for (i = 0; i < 512; i++, e++) {
        if (e->used == 0) {
            e->c56 = -128;
            e->c57 = -128;
            e->c58 = -128;
            e->c59 = -128;
            e->b3 = 2;
            e->b2 = 0;
            e->b6 = 0;
            e->h12 = 0;
            e->b7 = D_00F703C4;
            e->f48 = 256.0f;
            e->fn = func_00f43350;
            e->b1 = 0;
            e->w28 = 0;
            e->w32 = 0;
            e->w36 = 0;
            e->w40 = 0;
            e->w44 = 0;
            e->w52 = 0;
            e->w64 = 0;
            return e;
        }
    }
    PlatBreak();
    return 0;
}

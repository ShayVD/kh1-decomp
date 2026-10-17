#include "common.h"
/* Hand-matched functions 0x1689d0-0x172690 (worker 60). */
typedef struct { u8 pad[0x10]; f32 pos[4]; } ObjP;
typedef struct {
    u8 pad[0x20]; f32 v20[4]; u8 pad30[8]; u64 w38; u8 pad40[0x18]; s32 w58; u8 pad5c[0x34];
    ObjP *tgt; u8 pad94[0xC]; f32 fA0; u8 padA4[0x40]; f32 fE4;
} L60;
extern ObjP *D_0035BD40[];
void func_00267518(f32 *, f32 *, f32 *);
void func_00267530(f32 *, f32 *, f32 *);
s32 func_00119688(f32 *);
f32 func_00162a58(f32 *);

void func_001689d0(ObjP *self, L60 *l) {
    f32 a[4];
    f32 b[4];
    f32 c[8]; /* unused, sizes the frame */
    if (((s32)((s64)(l->w38 << 22) >> 32) & 1) || l->tgt == 0) {
        if (l->fE4 < 0.0f) {
            func_00267518(a, D_0035BD40[0]->pos, l->v20);
            func_00267530(b, self->pos, D_0035BD40[0]->pos);
        } else {
            func_00267518(a, self->pos, l->v20);
            func_00267530(b, D_0035BD40[0]->pos, self->pos);
        }
    } else {
        if (l->fA0 < 0.0f) {
            func_00267518(a, l->tgt->pos, l->v20);
            func_00267530(b, self->pos, l->tgt->pos);
        } else {
            func_00267518(a, self->pos, l->v20);
            func_00267530(b, l->tgt->pos, self->pos);
        }
    }
    if (func_00119688(a) < 0 && func_00162a58(b) < 500.0f) l->w58 = 0;
}

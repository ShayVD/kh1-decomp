/* func_0023fad0 10w off (nostrict): orig hoists li v1,128 before the bc1t and stores c[3],c[0],c[2],c[1]; ours li v0,128 in the slot. Store-order permutations, k=128 local, aggregate init, early return all tried. */
#include "common.h"
typedef struct { s32 x, y, z, w; } I4b;
typedef struct { s32 c[4]; } __attribute__((aligned(16))) Col;
typedef struct { u8 pad[0x40]; s32 v[2]; } R90;
typedef struct {
    u8 pad[0x80]; s32 c[2]; u8 p88[8]; R90 *x90; u8 p94[0xA00 - 0x94];
    f32 xa00, xa04, xa08, xa0c; u8 pa10[0xC]; f32 xa1c;
} Ofad0;
extern Col D_00491600;
I4b *func_0023e160(s32 *c, s32 *r, s32 *col, I4b *d, f32 a0, f32 a1, f32 al);
void func_0023fad0(Ofad0 *o, I4b *d) {
    Col q = D_00491600;
    d = func_0023e160(o->c, o->x90->v, q.c, d, 0.0f, o->xa00, o->xa1c);
    if (o->xa0c != 0.0f) {
        q.c[0] = 128;
        q.c[1] = 128;
        q.c[2] = 128;
        q.c[3] = o->xa08;
        func_0023e160(o->c, o->x90->v, q.c, d, o->xa00, o->xa04, o->xa1c);
    }
}

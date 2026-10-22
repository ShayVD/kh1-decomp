#include "common.h"
#include "data/pieces/D_0037A380.h"
typedef V4_37A380 V4;
void *memcpy(void *, const void *, u32);
typedef C4_37A380 C4;
typedef B16_37A380 B16;
typedef Ent_37A380 Ent;
static inline void cp16(B16 *d, B16 *s) {
    *d = *s;
}
static inline void cpm(void *d, void *s) {
    memcpy(d, s, 16);
}
static inline void lk_init(struct Lk_37A380 *l) {
    l->prev = 0;
    l->next = 0;
}
extern s32 D_003C5500;
typedef union { f32 f[4]; Ent *p[4]; } __attribute__((aligned(16))) A16;
static inline void inl_cpy(V4 *d, V4 *s) {
    *(A16 *)d = *(A16 *)s;
}
s32 func_001c5db8(void);
void func_0011ef10(s32, void *);
void func_001c5ee8(s32 *p) {
    s32 i;
    D_0037A380.cam.n = *p++;
    for (i = 0; i < D_0037A380.cam.n; i++) {
        Ent *e = &D_0037A380.cam.ent[i];
        e->c0 = *(C4 *)p; p++;
        e->c4 = *(C4 *)p; p++;
        D_0037A380.cam.ent[i].n = *p; p++;
        cpm(&e->v[0], (B16 *)p); p += 4;
        cpm(&e->v[1], (B16 *)p); p += 4;
        cpm(&D_0037A380.cam.ent[i].v[2], (B16 *)p); p += 4;
        cpm(&D_0037A380.cam.ent[i].v[3], (B16 *)p); p += 4;
        cpm(&D_0037A380.cam.ent[i].v[4], (B16 *)p); p += 4;
        cpm(&D_0037A380.cam.ent[i].v[5], (B16 *)p); p += 4;
        cpm(&D_0037A380.cam.ent[i].v[6], (B16 *)p); p += 4;
        cpm(&D_0037A380.cam.ent[i].v[7], (B16 *)p); p += 4;
        cpm(&D_0037A380.cam.ent[i].v[8], (B16 *)p); p += 4;
        cpm(&D_0037A380.cam.ent[i].v[9], (B16 *)p); p += 4;
        cpm(&D_0037A380.cam.ent[i].v[10], (B16 *)p); p += 4;
        e->f[0] = *(f32 *)p; p++;
        e->f[1] = *(f32 *)p; p++;
        e->f[2] = *(f32 *)p; p++;
        e->f[3] = *(f32 *)p; p++;
        e->lk.f4 = *(f32 *)p; p++;
        e->lk.f5 = *(f32 *)p; p++;
        if (i == 0) {
            if (p) lk_init(&D_0037A380.cam.ent[0].lk); else lk_init(&D_0037A380.cam.ent[0].lk); /* identical arms, re-merged by jump2 */
        } else {
            Ent *q = &D_0037A380.cam.ent[i - 1];
            if (i > 0) { /* identical arms (odd source): adds refs to i so it outranks lk in global-alloc; re-merged by jump2 */
                D_0037A380.cam.ent[i - 1].lk.next = &D_0037A380.cam.ent[i];
                e->lk.next = 0;
            } else {
                D_0037A380.cam.ent[i - 1].lk.next = &D_0037A380.cam.ent[i];
                e->lk.next = 0;
            }
            e->lk.prev = q;
        }
    }
    D_0037A380.cam.e.x = 0;
    D_0037A380.cam.e.y = 0;
    D_0037A380.cam.first = &D_0037A380.cam.ent[0];
    D_0037A380.cam.last = &D_0037A380.cam.ent[D_0037A380.cam.n - 1];
    D_0037A380.cam.t = (f32)D_0037A380.cam.ent[0].n;
    inl_cpy(&D_0037A380.cam.a, (V4_37A380 *)&D_0037A380.cam.ent[0].v[5]);
    D_0037A380.cam.e.z = 0;
    inl_cpy(&D_0037A380.cam.b, (V4_37A380 *)&D_0037A380.cam.ent[0].v[6]);
    inl_cpy(&D_0037A380.cam.c, (V4_37A380 *)&D_0037A380.cam.ent[0].v[7]);
    inl_cpy(&D_0037A380.cam.d, (V4_37A380 *)&D_0037A380.cam.ent[0].v[10]);
    D_0037A380.cam.f60 = D_0037A380.cam.ent[0].f[2];
    D_0037A380.cam.e.w = 0;
    D_0037A380.cam.fE0F4 = D_0037A380.cam.ent[0].lk.f5;
    D_003C5500 = *(s32 *)&D_0037A380.cam.ent[256] + 1;
    func_0011ef10(50000, func_001c5db8);
    i = 0; /* dead store kept: needed for the match */
}
#include "data/data_003C.h"

#include "common.h"
#include "ppp.h"

void *memset(void *, s32, u32);
void *func_0017f958(s32, s32);
s32 func_0019f1a8(void *, void *);
void func_001a0628(void *, void *, void *);
void func_002673b8(void *, void *);
extern s32 D_00615E64;

typedef struct {
    f32 x, y, z, w;
    void *p10;
    void *p14;
    void *p18;
    s32 n;
} MbmW;

typedef struct {
    u8 pad0[0x1c];
    u16 n;
    u8 pad1e[0xd0 - 0x1e];
    f32 x, y, z;
    u8 paddc[0x101 - 0xdc];
    u8 b101;
    u8 pad102[4];
    u8 b106;
} MbmK;

void pppRyjMegaBirthModelFrame(void *obj, MbmK *k, PppEntry *e) {
    MbmW *w = (MbmW *)((u8 *)obj + e->offsets[2] + 0xA0);
    void *w2 = (u8 *)obj + e->offsets[1] + 0xA0;

    if (w->p10 == NULL) {
        w->n = k->n;
        w->p10 = func_0017f958(D_00615E64, w->n * 0xB0);
        if (w->p10 != NULL)
            memset(w->p10, 0, w->n * 0xB0);
        if (k->b106) {
            w->p14 = func_0017f958(D_00615E64, w->n << 6);
            if (w->p14 != NULL)
                memset(w->p14, 0, w->n << 6);
        }
        if (k->b101) {
            w->p18 = func_0017f958(D_00615E64, w->n << 5);
            if (w->p18 != NULL)
                memset(w->p18, 0, w->n << 5);
        }
        w->x = k->x;
        w->y = k->y;
        w->z = k->z;
        w->w = 0;
        func_002673b8(w, w);
    }
    if (func_0019f1a8(w, k))
        func_001a0628(w, k, w2);
}

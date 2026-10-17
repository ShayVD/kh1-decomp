/* ppp component frame/draw callbacks, by hand (worker 40). */
#include "ppp.h"

#define PPP_WORK(T, obj, e, k) ((T *) ((u8 *) (obj) + (e)->offsets[k] + 0xA0))

typedef struct {
    u8 pad[0xB0];
    u64 flags; /* +0xB0 */
} PppSystem;

extern s32 D_0061621C;
extern PppSystem *D_00615E60;

typedef struct {
    s32 unk00, unk04, unk08;
    s32 frame; /* +0x0C */
} PppObject;

typedef struct { f32 a, b, c; } PppV12;

typedef struct {
    s32 frame;
    PppV12 v;    /* +0x4 */
    f32 x, y;    /* +0x10 */
    f32 d[3];    /* +0x18 */
} PppWindKey;

typedef struct {
    PppV12 v;
    f32 x, y;    /* +0xC */
    f32 r;       /* +0x14 */
    f32 d[3];    /* +0x18 */
} PppWindWork;

static inline f32 vu0Sqrt(f32 x) {
    f32 r;
    __asm__ volatile(
        "mfc1 $2, %1\n"
        "qmtc2 $2, $vf2\n"
        "vsqrt Q, $vf2x\n"
        "vwaitq\n"
        "vaddq.x $vf2x, $vf0x, Q\n"
        "qmfc2 $2, $vf2\n"
        "mtc1 $2, %0\n"
        : "=f"(r) : "f"(x) : "$2");
    return r;
}

void pppEiWindFunFrame(PppObject *obj, PppWindKey *key, PppEntry *e) {
    PppWindWork *w = PPP_WORK(PppWindWork, obj, e, 0);
    f32 x, y;

    if (D_0061621C == 0 && !(D_00615E60->flags & 0xFF0000FF00ULL)) {
        w->d[1] += w->d[2];
        w->d[0] += w->d[1];
    }
    if (key->frame != obj->frame)
        return;
    w->v = key->v;
    w->x = x = key->x;
    w->y = y = key->y;
    w->r = x / vu0Sqrt(x * x + y * y);
    if (D_0061621C == 0 && !(D_00615E60->flags & 0xFF0000FF00ULL)) {
        w->d[0] += key->d[0];
        w->d[1] += key->d[1];
        w->d[2] += key->d[2];
    }
}

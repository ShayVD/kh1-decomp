/* pppKeBornPtCmplFrame and its spawner func_0018e348, -fno-strict-aliasing
 * without delay-slot filling (docs/modules.md "Session 50"): starts an
 * effect at each point of a list in turn.  Read from the code, not proved
 * by a boot. */
#include "common.h"
#include "platform/vu.h"
#include "ppp.h"

/* func_0018e348 (from hand/nostrict_nofill/text_s7_w3.c). */
#define PPP_WORK(T, obj, e, k) ((T *) ((u8 *) (obj) + (e)->offsets[k] + 0xA0))
typedef struct {
    s32 unk0;
    u8 *inst;
    s32 time;
    s32 unkC;
} PppSlot;
typedef struct {
    u8 pad[0x80];
    PppSlot *slots;
    u8 pad84[0x2C];
    u64 flags;
} PppSystem;
extern PppSystem *D_00615E60;
u8 *func_00182588(PppSystem *, PppSlot *);
typedef struct { f32 x, y, z, w; } V4;
typedef struct {
    s32 frame;
    u8 n;          /* +0x04 */
    u8 pad5[3];
    s32 slot;      /* +0x08 */
    s32 off;       /* +0x0C */
    s32 off10;     /* +0x10 */
} BornKey;
typedef struct {
    u8 *p;
    s32 pad4;
    f32 f8;
} BornWork;
void func_001a9098(u8 *, u8 *);
void func_001a9110(u8 *, V4 *, V4 *);
/* func_0018e348 (session 7, w3): the slot spawn is written out twice with shared locals (an inline helper gave the first result a0 instead of a2). */
void func_0018e348(void *obj, BornKey *key, PppEntry *e) {
    V4 a, b, c;
    u8 *inst;
    u8 *d;
    BornWork *w;
    f32 t, s;

    {
        PppSystem *sys = D_00615E60;
        PppSlot *sl = &sys->slots[key->slot];
        inst = 0;
        if (sl) {
            inst = func_00182588(sys, sl);
            *(void **) (inst + 4) = obj;
        }
    }
    d = inst + key->off + 0xA0;
    func_001a9098(d, (u8 *) obj + e->offsets[1] + 0xA0);

    w = PPP_WORK(BornWork, obj, e, 0);
    if (w->p == 0) {
        w->f8 = 1.0f / (f32) (key->n + 1);
    } else {
        PlatVu0CopyVector(&a, w->p);
        PlatVu0SubVector(&b, d, &a);
        t = (f32) key->n;
        s = w->f8;
        while (0.0f < t) {
            u8 *d2;
            {
                PppSystem *sys = D_00615E60;
                PppSlot *sl = &sys->slots[key->slot];
                inst = 0;
                if (sl) {
                    inst = func_00182588(sys, sl);
                    *(void **) (inst + 4) = obj;
                }
            }
            d2 = inst + key->off + 0xA0;
            PlatVu0ScaleVector(&c, &b, s * t);
            t -= 1.0f;
            func_001a9110(d2, &a, &c);
        }
    }
    w->p = d;
}
#undef PPP_WORK

/* pppKeBornPtCmplFrame (from hand/nostrict_nofill/text_00180000_s6_11.c). */
extern s32 D_0061621C;
void pppKeBornPtCmplFrame(void *obj, BornKey *key, PppEntry *e) {
    if (D_0061621C != 0 || (D_00615E60->flags & 0xFF0000FF00ULL))
        return;
    if (key->slot == -1 || key->off10 == -1)
        return;
    do { func_0018e348(obj, key, e); } while (0);
}


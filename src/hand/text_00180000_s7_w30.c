#include "common.h"
/* pppPointRApFrame 0x186ab0: MATCH hand (and hand/nostrict). The VU0 random helper as a statement macro writing a local (not a static inline returning f32): the two 32768.0f constants then stay separate pseudos, and post-reload cse reuses f1. */
#include "ppp.h"

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

u8 *func_00182588(PppSystem *, PppSlot *);

static inline u8 *inl_spawn(PppSystem *sys, s32 id, void *o) {
    PppSlot *s = &sys->slots[id];
    u8 *i = 0;

    if (s) {
        i = func_00182588(sys, s);
        *(void **) (i + 4) = o;
    }
    return i;
}
#include "data/data_0037.h"

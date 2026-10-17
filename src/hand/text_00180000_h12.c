/* ppp manager and component callbacks, by hand (worker 12). */
#include "common.h"

/* D_00364130: 256 effect managers of 0xC0 bytes. */
typedef struct {
    u8 pad[0xFC];
    u16 unkFC;
} PppOwner;

typedef struct PppMng {
    u8 pad00[0x86];
    u16 st;          /* +0x86 */
    u8 pad88[4];
    PppOwner *owner; /* +0x8C */
    u8 pad90[8];
    s32 unk98;       /* +0x98 */
    u8 pad9C[0xC];
    s32 unkA8;       /* +0xA8 */
    u8 padAC[0x14];
} PppMng;

extern PppMng D_00364130[256];
void func_0011d3c8(s32, s32, s32);
void func_00182788(PppMng *);
void func_00182840(PppMng *);

s32 func_00181410(void) {
    PppMng *m = D_00364130;
    s32 i;

    for (i = 0; i < 256; i++, m++) {
        if ((m->st & 1) && !(m->st & 4) && m->unk98 < 0) {
            if (m->owner->unkFC != 0)
                func_0011d3c8(m->owner->unkFC, m->unkA8, 60);
            func_00182788(m);
            func_00182840(m);
            return 1;
        }
    }
    return 0;
}

/* A system with a table of modules; each module is a table of hooks. */
typedef struct PppSys PppSys;
typedef void (*PppSysFn)(PppSys *);
typedef struct {
    void *fn[8];
} PppModule;

struct PppSys {
    u8 pad00[0x64];
    s32 nmod;          /* +0x64 */
    u8 pad68[0x10];
    PppModule **mods;  /* +0x78 */
};

void func_001822f8(PppSys *s) {
    s32 i;

    for (i = 0; i < s->nmod; i++) {
        PppSysFn fn = (PppSysFn) s->mods[i]->fn[4];
        if (fn)
            fn(s);
    }
}

void func_00182368(PppSys *s) {
    s32 i;

    for (i = 0; i < s->nmod; i++) {
        PppSysFn fn = (PppSysFn) s->mods[i]->fn[5];
        if (fn)
            fn(s);
    }
}

void func_001823d8(PppSys *s) {
    s32 i;

    for (i = 0; i < s->nmod; i++) {
        PppSysFn fn = (PppSysFn) s->mods[i]->fn[6];
        if (fn)
            fn(s);
    }
}

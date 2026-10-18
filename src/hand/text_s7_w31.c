#include "common.h"

/* func_00123488 (w31): matches in hand and hand/nostrict. All "return 0" go to one shared r0 label at the end (keeps the explicit move v0,zero after each loop and the reloaded li 1 in case 0), and case 1 first loop shares the found: return e stub with the default loop. Needs func_001230a0 defined above it (CONTEXT_ONLY copy). */
typedef struct { u8 pad[0x4c]; u16 x4c; u16 x4e; } Prm;
typedef struct Ent { u32 x0; u32 x4; u8 pad[0x128]; Prm *x130; } Ent;
extern Ent *D_002E26A0[3];
Ent *func_001230a0(Ent *);
typedef struct CA { u8 pad[0x370]; u64 x370; u8 pad2[0x4b0 - 0x378]; } CA;
extern CA D_002C64A0[], D_002E26A0_ca[] __asm__("D_002E26A0");
CONTEXT_ONLY Ent *func_001230a0(Ent *e0) {
    CA *a = (CA *)e0;
    if (a == 0) a = D_002C64A0; else a++;
    for (; a < D_002E26A0_ca; a++) {
        if ((a->x370 & 0x300000000) == 0x100000000) return (Ent *)a;
    }
    return 0;
}
Ent *func_00123488(u32 id) {
    Ent *e;
    s32 i;
    s32 t = (id >> 16) & 0xff;
    switch (t) {
    case 1:
        for (i = 0; i < 3; i++) {
            e = D_002E26A0[i];
            if (e && e->x130->x4c == (id & 0xffff)) goto found;
        }
        e = 0;
        while ((e = func_001230a0(e)) != 0) {
            if (e->x130->x4c == (id & 0xffff)) return e;
        }
        goto r0;
    case 0:
        switch ((s32)(id & 0xffff)) {
        case 0: return D_002E26A0[0];
        case 1: return D_002E26A0[1];
        case 2: return D_002E26A0[2];
        }
        goto r0;
    found:
        return e;
    case 11:
        e = 0;
        while ((e = func_001230a0(e)) != 0) {
            if (e->x130->x4e == (id & 0xffff)) return e;
        }
        goto r0;
    default:
        for (e = func_001230a0(0); e; e = func_001230a0(e)) {
            if (e->x4 == id) goto found;
        }
        goto r0;
    }
r0:
    return 0;
}

/* func_00123488: 61w off (412 vs 400 bytes), hand/nostrict. New: needs func_001230a0 above it (CONTEXT_ONLY copy here; it is defined in src/hand/text_00110000_h4.c): then the dispatch uses plain beqz/beq with move a0,zero in the slots like the original. Still off: t in v1 (orig a0) with 1 in a1 (orig v1, case 0 reloads li 1), loop-exit return 0 blocks get folded (orig keeps move v0,zero), the default loop's return-e stub is placed before default instead of after case 0. */
#include "common.h"
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
            if (e && e->x130->x4c == (id & 0xffff)) return e;
        }
        e = 0;
        while ((e = func_001230a0(e)) != 0) {
            if (e->x130->x4c == (id & 0xffff)) return e;
        }
        return 0;
    case 0:
        switch ((s32)(id & 0xffff)) {
        case 0: return D_002E26A0[0];
        case 1: return D_002E26A0[1];
        case 2: return D_002E26A0[2];
        }
        return 0;
    found:
        return e;
    case 11:
        e = 0;
        while ((e = func_001230a0(e)) != 0) {
            if (e->x130->x4e == (id & 0xffff)) return e;
        }
        return 0;
    default:
        for (e = func_001230a0(0); e; e = func_001230a0(e)) {
            if (e->x4 == id) goto found;
        }
        return 0;
    }
}

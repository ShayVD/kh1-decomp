/* func_00123488: ~64 words off (nostrict). Same code, different block layout: orig places default-loop "return e" stub after case 0, case-0 switch reloads li 1, dispatch var in a0. */
#include "common.h"
typedef struct { u8 pad[0x4c]; u16 x4c; u16 x4e; } Prm;
typedef struct Ent { u32 x0; u32 x4; u8 pad[0x128]; Prm *x130; } Ent;
extern Ent *D_002E26A0[3];
Ent *func_001230a0(Ent *);
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
    case 11:
        e = 0;
        while ((e = func_001230a0(e)) != 0) {
            if (e->x130->x4e == (id & 0xffff)) return e;
        }
        return 0;
    default:
        for (e = func_001230a0(0); e; e = func_001230a0(e)) {
            if (e->x4 == id) return e;
        }
        return 0;
    }
}

/* The ppp effect system's interface to the game, default flags (docs/modules.md
 * "Session 51"): func_00175918 registers the three per-frame tasks (update
 * func_00175af0, draw func_00175b70, and func_0017f8e0) with the task list
 * (func_0011ef10); the manager's enable flags (D_0035C6F0 ...); a table of 64
 * entries of 0x3C bytes (func_00175ba0 ... func_00175f10) and the many entry
 * points for the three effect banks D_0035E710, D_0035FB20 and D_00360F30
 * (func_00175f58 ... func_00176290: start, find, stop an effect in each
 * bank), wrappers that kill objects by owner or kind (func_001762b0 ...
 * func_00176388, func_001763a0), the relocatable effect pack (func_001763f0
 * relocates it, func_00176488 starts an item by id, func_00176578 finds one
 * by its masks).  pppapi.nostrict.c has
 * func_00175be0 (start an effect in a bank) and func_00176658 (spawn an
 * object from a pack item).  Each section names the file its code came
 * from.  Read from the code, not proved by a boot. */
#include "m2c.h"
#include "data/bss_0057.h"
#include "data/pieces/D_00362438.h"
#include "data/pieces/D_0035E710.h"
#include "data/pieces/D_003626C0.h"
#include "data/pieces/D_003626F0.h"
#include "data/pieces/D_00362424.h"
#include "data/pieces/D_00362428.h"
#include "data/pieces/D_0036242C.h"
#include "data/pieces/D_00362430.h"
#include "data/pieces/D_00362434.h"
#include "data/pieces/D_0036243C.h"
#include "data/pieces/D_00362710.h"
#include "data/pieces/D_0035C710.h"
#include "data/pieces/D_002E2780.h"
#include "data/pieces/D_002E2790.h"
#include "data/pieces/D_002E26A0.h"
#include "data/pieces/D_0036244C.h"
#include "data/pieces/D_00362450.h"
#include "data/pieces/D_00362454.h"
#include "common.h"
#include "platform/vu.h"
#include "data/bss_0055.h"
#include "data/pieces/D_00304BE8_s.h"
#include "data/pieces/D_00351A30.h"
#include "data/pieces/D_00308CDC.h"
#include "data/pieces/D_002C58B0.h"
#include "data/pieces/D_002C58A0.h"
#include "data/pieces/D_002BBDF8.h"
#include "data/pieces/D_002BC144.h"
#include "data/pieces/D_002BC140.h"
#include "data/pieces/D_002C58D0.h"
#include "data/pieces/D_0035BD40.h"
#include "data/types/text_00170000_h11_p4.h"
#include "data/pieces/D_00364130.h"
#include "data/types/text_00170000_h11.h"
#include "data/pieces/D_002C5960.h"
#include "data/pieces/D_003626F8.h"

/* func_00175918 (from auto/text_00170000_2.c). */
void func_00175a48();
s32 func_00175af0(void);
s32 func_00175b70(void);
void func_0017f8e0();
void *func_0011ef10(M2C_UNK, M2C_UNK *);
void func_00175918(void) {
    M2C_FIELD(func_0011ef10(0x222E0, &func_00175af0), s16 *, 2) = -1;
    M2C_FIELD(func_0011ef10(0x27100, &func_00175b70), s16 *, 2) = -1;
    func_0011ef10(0x2E630, &func_0017f8e0);
    func_00175a48();
}

/* func_00175980 (from auto/text_00170000.c). */
M2C_UNK func_00176ea8();
extern M2C_UNK func_00176ee0;
void func_00175980(void) {
    func_00176ea8();
    func_0011ef10(0x4E21, &func_00176ee0);
}

/* func_001759a8 (from auto/text_00170000.c). */
void func_00175a98();
void func_001759a8(void) {
    func_00175a98();
}

/* func_001759c0 (from auto/text_00170000.c). */
M2C_UNK func_00250054(M2C_UNK *, M2C_UNK, M2C_UNK);
void func_001759c0(void) {
    func_00250054(((M2C_UNK *)&D_0035E710), 0, 0x1410);
}

/* func_001759e8 (from auto/text_00170000.c). */
extern M2C_UNK D_0035FB20;
extern M2C_UNK D_00360F30;
void func_001759e8(void) {
    func_00250054(&D_0035FB20, 0, 0x1410);
    func_00250054(&D_00360F30, 0, 0x1410);
}

/* func_00175a20 (from auto/text_00170000_8.c). */
M2C_UNK memset(M2C_UNK *, M2C_UNK, M2C_UNK);
void func_00175a20(void) {
    memset(((M2C_UNK *)&D_0035C710), 0, 0x2000);
}

/* func_00175a48 (from auto/text_00170000_9.c). */
extern s32 D_0035C6F8;
extern s32 D_0035C6FC;
void func_00182058(void);
void func_00182270(void);
void func_00175a48(void) {
    func_00182270();
    func_00182058();
    func_001759c0();
    func_001759e8();
    func_00175a20();
    D_0035C6F8 = 1;
    D_0035C6FC = 0;
}

/* func_00175a98 (from auto/text_00170000_4.c). */
extern M2C_UNK D_00278B50;
extern s32 D_0035C700;
void func_00180540(s32);
void func_00180aa8(s32);
void func_00175a98(void) {
    if (D_0035C700 == 0) {
        func_00180540((s32) &D_00278B50);
        func_00180aa8((s32) &D_00278B50);
        D_0035C700 = 1;
    }
}

/* func_00175af0 (from hand/text_00150000_h10.c). */
extern s32 D_0035C6F4;
extern s32 D_0061621C;
extern s32 D_0035C6F0;
void func_00182148(s32, s32, void *, void *);
void func_00181738(void);
s32 func_00175af0(void) {
    if (D_0035C6F0 == 0) return 0;
    if (D_0035C6F4) D_0061621C = 1;
    else D_0061621C = 0;
    func_00182148(D_002BC140, D_002BC144, &D_002E2780, &D_002E2790);
    func_00181738();
    return 0;
}

/* func_00175b70 (from auto/text_00170000_10.c). */
void func_00181b30(void);
s32 func_00175b70(void) {
    if (D_0035C6F0 == 0) {
        return 0;
    }
    func_00181b30();
    return 0;
}

/* func_00175ba0 (from hand/text_00170000_h11.c). */
typedef struct { u8 pad0[0x20]; s32 flags; u8 pad24[0x3c - 0x24]; } E3C;
/* --- 0x3C-byte entry table (func_00175ba0..func_00175da8) --- */
s32 func_00175ba0(E3C *a) {
    s32 i;
    for (i = 0; i < 64; i++) {
        if (!(a[i].flags & 3)) return i;
    }
    return -1;
}

/* func_00175d60 (from hand/text_00170000_h11.c). */
typedef struct Ent {
    u8 pad0[0xC];
    s32 unkC;     /* 0x0C */
    u8 pad10[4];
    s32 flags;    /* 0x14: bit 0 = in use */
    u8 pad18[4];
    struct { u8 pad[8]; s32 id; } *unk1C; /* 0x1C */
    u8 pad20[0xC];
    struct { u8 pad[0x8c]; u8 *unk8C; } *unk2C; /* 0x2C */
    u8 pad30[0xC];
} Ent; /* 0x3C */
typedef struct Mgr {
    u8 pad0[0xC];
    Ent ents[64];        /* 0x00C */
    u8 padF0C[0x1010 - 0xF0C];
    u8 m1010[64][16];    /* 0x1010 */
} Mgr;
Ent *func_00175d60(Mgr *m, s32 id) {
    s32 i;
    Ent *e = m->ents;
    for (i = 0; i < 64; i++, e++) {
        if ((e->flags & 1) && e->unk1C->id == id) return e;
    }
    return 0;
}

/* func_00175da8 (from hand/text_00170000_h11.c). */
void func_00175da8(Mgr *m, s32 arg1) {
    s32 i = 0;
    Ent *e = m->ents;
    u8 *p = m->m1010[0];
loop:
    if ((e->flags & 1) && e->unk2C->unk8C[0xfb] == 0)
        PlatVu0MulVector(e->unkC, p, arg1);
    i++; e++; p += 16;
    if (i < 64) goto loop;
}

/* func_00175e38 (from auto/text_00170000_7.c). */
void func_00176340();
#define func_00176340 ((M2C_UNK (*)(s32)) func_00176340)
void func_00175e38(s32 arg0) {
    s32 var_a0;
    s32 var_s0;
    s32 var_s1;

    var_s0 = arg0 + 0xC;
    var_s1 = 0x3F;
    var_a0 = var_s0;
    do {
        var_s1 -= 1;
        func_00176340(var_a0);
        var_s0 += 0x3C;
        var_a0 = var_s0;
    } while (var_s1 >= 0);
}
#undef func_00176340

/* func_00175e80 (from auto/text_00170000_7.c). */
void func_00176310();
#define func_00176310 ((M2C_UNK (*)(s32)) func_00176310)
void func_00175e80(s32 arg0) {
    s32 var_a0;
    s32 var_s0;
    s32 var_s1;

    var_s0 = arg0 + 0xC;
    var_s1 = 0x3F;
    var_a0 = var_s0;
    do {
        var_s1 -= 1;
        func_00176310(var_a0);
        var_s0 += 0x3C;
        var_a0 = var_s0;
    } while (var_s1 >= 0);
}
#undef func_00176310

/* func_00175ec8 (from auto/text_00170000_7.c). */
M2C_UNK func_0017fae8(s32);
void func_00175ec8(s32 arg0) {
    s32 var_a0;
    s32 var_s0;
    s32 var_s1;

    var_s0 = arg0 + 0xC;
    var_s1 = 0x3F;
    var_a0 = var_s0;
    do {
        var_s1 -= 1;
        func_0017fae8(var_a0);
        var_s0 += 0x3C;
        var_a0 = var_s0;
    } while (var_s1 >= 0);
}

/* func_00175f10 (from auto/text_00170000_7.c). */
M2C_UNK func_0017fb40(s32);
void func_00175f10(s32 arg0) {
    s32 var_a0;
    s32 var_s0;
    s32 var_s1;

    var_s0 = arg0 + 0xC;
    var_s1 = 0x3F;
    var_a0 = var_s0;
    do {
        var_s1 -= 1;
        func_0017fb40(var_a0);
        var_s0 += 0x3C;
        var_a0 = var_s0;
    } while (var_s1 >= 0);
}

/* func_00175f58 (from auto/text_00170000_8.c). */
M2C_UNK func_00175be0(M2C_UNK *, s32, s32, s32, s32, M2C_UNK, M2C_UNK);
void func_00175f58(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_00175be0(((M2C_UNK *)&D_0035E710), arg0, arg1, arg2, arg3, -1, 1);
}

/* func_00175f98 (from auto/text_00170000_9.c). */
void func_00175f98(s32 arg0, s32 arg1, s32 arg2) {
    func_00175be0(&D_0035FB20, arg0, arg1, -1, arg2, -1, 2);
}

/* func_00175fd0 (from auto/text_00170000_9.c). */
void func_00175fd0(s32 arg0, s32 arg1, s32 arg2) {
    func_00175be0(&D_00360F30, arg0, arg1, -1, arg2, -1, 3);
}

/* func_00176008 (from auto/text_00170000_4.c). */
void func_00176008(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_00175be0(((M2C_UNK *)&D_0035E710), arg0, arg1, -1, arg3, arg2, 1);
}

/* func_00176040 (from auto/text_00170000_4.c). */
void func_00176040(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_00175be0(&D_0035FB20, arg0, arg1, -1, arg3, arg2, 2);
}

/* func_00176078 (from auto/text_00170000_4.c). */
void func_00176078(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_00175be0(&D_00360F30, arg0, arg1, -1, arg3, arg2, 3);
}

/* func_001760b0 (from auto/text_00170000.c). */
void func_001760b0(s32 arg0) {
    func_00175d60(((M2C_UNK *)&D_0035E710), arg0);
}

/* func_001760d0 (from auto/text_00170000.c). */
void func_001760d0(s32 arg0) {
    func_00175d60(&D_0035FB20, arg0);
}

/* func_001760f0 (from auto/text_00170000.c). */
void func_001760f0(s32 arg0) {
    func_00175d60(&D_00360F30, arg0);
}

/* func_00176110 (from auto/text_00170000_8.c). */
void func_00176110(s32 arg0) {
    func_00175da8(((M2C_UNK *)&D_0035E710), arg0);
}

/* func_00176130 (from auto/text_00170000_8.c). */
void func_00176130(s32 arg0) {
    func_00175da8(&D_0035FB20, arg0);
}

/* func_00176150 (from auto/text_00170000_8.c). */
void func_00176150(s32 arg0) {
    func_00175da8(&D_00360F30, arg0);
}

/* func_00176170 (from auto/text_00170000_8.c). */
void func_00176170(void) {
    func_00175e38(((M2C_UNK *)&D_0035E710));
    func_001759c0();
}

/* func_00176190 (from auto/text_00170000_8.c). */
void func_00176190(void) {
    func_00175e38(&D_0035FB20);
    func_001759e8();
}

/* func_001761b0 (from auto/text_00170000_1.c). */
void func_001761b0(void) {
    func_00175e38(&D_00360F30);
    func_001759e8();
}

/* func_001761d0 (from auto/text_00170000.c). */
void func_001761d0(void) {
    func_00175e80(&D_0035FB20);
}

/* func_001761f0 (from auto/text_00170000_8.c). */
void func_001761f0(void) {
    func_00175ec8(((M2C_UNK *)&D_0035E710));
}

/* func_00176210 (from auto/text_00170000_8.c). */
void func_00176210(void) {
    func_00175ec8(&D_0035FB20);
}

/* func_00176230 (from auto/text_00170000_8.c). */
void func_00176230(void) {
    func_00175ec8(&D_00360F30);
}

/* func_00176250 (from auto/text_00170000_8.c). */
void func_00176250(void) {
    func_00175f10(((M2C_UNK *)&D_0035E710));
}

/* func_00176270 (from auto/text_00170000_8.c). */
void func_00176270(void) {
    func_00175f10(&D_0035FB20);
}

/* func_00176290 (from auto/text_00170000_8.c). */
void func_00176290(void) {
    func_00175f10(&D_00360F30);
}

/* func_001762b0 (from auto/text_00170000_8.c). */
M2C_UNK func_0017f910();
void func_001762b0(void) {
    func_0017f910();
}

/* func_001762c8 (from auto/text_00170000_8.c). */
M2C_UNK func_0017f9d8();
void func_001762c8(void) {
    func_0017f9d8();
}

/* func_001762e0 (from auto/text_00170000_8.c). */
M2C_UNK func_0017fa68();
void func_001762e0(void) {
    func_0017fa68();
}

/* func_001762f8 (from auto/text_00170000_8.c). */
M2C_UNK func_0017faa8();
void func_001762f8(void) {
    func_0017faa8();
}

/* func_00176310 (from auto/text_00170000_8.c). */
M2C_UNK func_0017fb98();
void func_00176310(void) {
    func_0017fb98();
}

/* func_00176328 (from auto/text_00170000_8.c). */
M2C_UNK func_0017fc48();
void func_00176328(void) {
    func_0017fc48();
}

/* func_00176340 (from auto/text_00170000.c). */
M2C_UNK func_0017fcd8();
void func_00176340(void) {
    func_0017fcd8();
}

/* func_00176358 (from auto/text_00170000_8.c). */
M2C_UNK func_0017fd88();
void func_00176358(void) {
    func_0017fd88();
}

/* func_00176370 (from auto/text_00170000_8.c). */
M2C_UNK func_0017fe60();
void func_00176370(void) {
    func_0017fe60();
}

/* func_00176388 (from auto/text_00170000.c). */
M2C_UNK func_0017ff38();
void func_00176388(void) {
    func_0017ff38();
}

/* func_001763a0 (from hand/text_00170000_h11.c). */
s32 func_00181368(s32);
void func_001763a0(s32 a) {
    s32 i;
    for (i = 0; i < 256; i++) {
        if (!func_00181368(a)) break;
    }
}

/* func_001763f0 (from hand/text_s7_w24.c). */
/* --- relocatable pack: header, n items of 0x20 bytes, then a count and
 * that many offsets (func_001763f0..func_00176578) --- */
typedef struct { s32 x0; u8 pad[28]; } E63;
typedef struct { u8 pad[0xc]; s32 n; E63 e[1]; } H63;
void func_00176640();
#define func_00176640 ((void (*)(s32)) func_00176640)
void func_001763f0(H63 *h) {
    s32 base = (s32)h;
    s32 *p = (s32 *)base;
    s32 i = 0;
    h = (H63 *)base;
    p += 4;
    for (; i < h->n; i++) {
        if (*p) *p += base;
        p += 8;
    }
    {
        s32 k = *p++;
        if (k > 0) {
            i = k;
            do {
                func_00176640(*p++ + base);
            } while (--i);
        }
    }
}
#undef func_00176640

/* func_00176488 (from hand/text_00170000_h11.c). */
typedef struct Item {
    s32 data;   /* 0x00: offset, relocated to a pointer */
    s32 size;   /* 0x04 */
    s32 id;     /* 0x08 */
    s32 pad0C;
    s32 mask1;  /* 0x10 */
    s32 mask2;  /* 0x14 */
    u64 mask3;  /* 0x18 */
} Item;
typedef struct Pack {
    u8 pad0[0xC];
    s32 n;      /* 0x0C */
    Item items[1];
} Pack;
s32 func_00176658(s32, void *, s32, s32);
typedef struct { u8 pad[0x38]; Pack *pack; } Obj38;
s32 func_00176488(Pack *h, Obj38 *obj, s32 id, s32 arg3) {
    s32 i;
    Item *it = h->items;
    s32 found = 0;
    for (i = 0; i < h->n; i++, it++) {
        if (it->id == id) { found = 1; break; }
    }
    if (!found) return 0;
    if (!func_00176658(it->data, obj, it->size, arg3)) return 0;
    obj->pack = h;
    return 1;
}

/* func_00176528 (from auto/text_00170000_2.c). */
s32 func_00176528(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0xC);
}

/* func_00176530 (from auto/text_00170000_7.c). */
s32 func_00176530(void *arg0, s32 *arg1) {
    s32 *var_a1;
    s32 temp_v0;
    s32 var_a2;
    s32 var_a3;
    void *var_v1;

    var_a1 = arg1;
    var_v1 = arg0 + 0x10;
    var_a2 = 0;
    var_a3 = 0;
    if (M2C_FIELD(arg0, s32 *, 0xC) > 0) {
        do {
            temp_v0 = M2C_FIELD(var_v1, s32 *, 8);
            var_v1 += 0x20;
            var_a2 += 1;
            var_a3 += 1;
            *var_a1 = temp_v0;
            var_a1 += 1;
        } while (var_a2 < M2C_FIELD(arg0, s32 *, 0xC));
    }
    return var_a3;
}

/* func_00176578 (from hand/text_00170000_h11.c). */
s32 func_00176578(Pack *h, s32 m1, s32 m2, u64 m3) {
    s32 i;
    Item *it = h->items;
    for (i = 0; i < h->n; i++, it++) {
        if (m1 != (m1 & it->mask1) && m1) continue;
        if (m2 != (m2 & it->mask2) && m2) continue;
        if (m3 != (m3 & it->mask3) && m3) continue;
        return it->id;
    }
    return -1;
}

/* func_001765f8 (from auto/text_00170000_8.c). */
M2C_UNK func_0017ff98();
void func_001765f8(void) {
    func_0017ff98();
}

/* func_00176610 (from auto/text_00170000_8.c). */
u16 func_00176610(void *arg0) {
    return M2C_FIELD(M2C_FIELD(M2C_FIELD(arg0, void **, 0x2C), void **, 0x8C), u16 *, 0xFC);
}

/* func_00176620 (from auto/text_00170000_2.c). */
s32 func_00176620(void *arg0) {
    return M2C_FIELD(M2C_FIELD(arg0, void **, 0x2C), s32 *, 0xA8);
}

/* func_00176630 (from auto/text_00170000_2.c). */
s32 func_00176630(void *arg0) {
    return M2C_FIELD(M2C_FIELD(arg0, void **, 0x2C), s32 *, 0x8C);
}

/* func_00176640 (from auto/text_00170000.c). */
#define func_00180540 ((M2C_UNK (*)()) func_00180540)
void func_00176640(void) {
    func_00180540();
}
#undef func_00180540

void func_00176838(void) {
    func_00182270();
}

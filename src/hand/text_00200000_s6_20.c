#include "common.h"
#include "data/pieces/D_00304BE8_s.h"
#include "data/bss_0064.h"
#include "data/pieces/D_003F34C4.h"
typedef N_3f34c4 N;
extern s32 D_003F32C8[];
extern void (*D_003F32E8[])(N *);
s32 func_0021add8(void);
void func_00207560(N *, s32, s32);
void func_00207428(N *, s32, s32);
void func_0011d768(s32);
N *func_001f31a8(s32, s32);

#include "data/pieces/D_003F34B8.h"
/* callee defined above (from src/hand/text_001f0000_h23.c) */
CONTEXT_ONLY u32 func_002073f0(s32 n) {
    return D_003F34B8->b112[n / 32] & (1 << n);
}
static inline void inl5(N *o) { if (func_0021add8()) func_00207560(o, 109, 215); if (!func_002073f0(0)) func_00207428(o, 92, 223); }

/* rodata */

/* party member: 0x74 bytes; item slots at +0x22 */
typedef W606Mem_304be8 DbMember;
/* same member viewed from +2 (indexed with item + 32) */
typedef Save_304be8 DbSave;
typedef struct { u8 pad[0x28]; s32 x28; } DbObj;
#include "data/pieces/D_003E3D68.h"
extern u8 D_003F3880[];
extern u8 D_003F38E0[];
s32 func_00149600(s32, s32);
s32 func_001ee7c8(s32);
void func_001ef830(void);
void func_001f3e48(DbObj *, s32);
void func_0020d890(DbObj *, s32);
void func_0020da90(DbObj *, s32);

s32 func_0020db00(s32 a0, s32 slot, s32 item, s32 a3) {
    s32 id, n, i, bits, first;
    DbObj *o;
    if (slot != -1) {
        DbMember *mp = &D_00304BE8->m[D_00304BE8->x48e[slot]];
        id = mp->sub.x22[item];
    } else {
        id = item;
    }
    if (func_001ee7c8(id)) {
        a3 = 0;
        n = D_003E3D68;
    } else {
        n = 1;
    }
    first = a3;
    bits = 0;
    do {
        n--;
        bits |= func_00149600(id, D_00304BE8->x48e[a3++]);
    } while (n != 0);
    for (i = 0; i < 7; i++) {
        if ((bits >> i) & 1) {
            if (slot != -1) {
                Sub_304be8 *mq = &D_00304BE8->m[D_00304BE8->x48e[slot]].sub;
                mq->x22[item] = 0;
            } else {
                D_00304BE8->items[item]--;
            }
            func_001ef830();
            if (i < 4) func_0011d768(14);
            else func_0011d768(7);
            o = (DbObj *)func_001f31a8((s32)D_003F3880, 6);
            if (o) {
                func_001f3e48(o, a0);
                func_0020d890(o, i + 153);
                o->x28 = first;
            }
            return 1;
        }
    }
    func_0011d768(4);
    o = (DbObj *)func_001f31a8((s32)D_003F38E0, 6);
    if (o) {
        func_001f3e48(o, a0);
        func_0020da90(o, 160);
    }
    return 0;
}

/* Pointer tables only this file uses (phase 4, tools/shift/define_ptr_tables.py). */
extern u8 D_003F3AE0[];
extern u8 D_003F3DB0[];
extern u8 D_003F4020[];
extern u8 D_003F4680[];
extern u8 D_003F4760[];
extern u8 D_003F4CC0[];
extern u8 D_003F5AC0[];
extern u8 D_003F6D40[];
s32 D_003F32C8[0x8] ALIGNED(8) = {
    (s32)D_003F3AE0, (s32)D_003F3DB0, (s32)D_003F4020, (s32)D_003F4680,
    (s32)D_003F4760, (s32)D_003F5AC0, (s32)D_003F4CC0, (s32)D_003F6D40,
};
void func_002112f8();
void func_00213c90();
void func_002160a8();
void func_00217f58();
void func_00218f88();
void func_0021ad08();
void func_0021daa0();
void func_002293f0();
void (*D_003F32E8[0x8])(N *) ALIGNED(8) = {
    (void *)func_002112f8, (void *)func_00213c90, (void *)func_002160a8, (void *)func_00217f58,
    (void *)func_00218f88, (void *)func_0021daa0, (void *)func_0021ad08, (void *)func_002293f0,
};
#include "data/bss_0064_mixed.h"
#include "data/data_003F.h"

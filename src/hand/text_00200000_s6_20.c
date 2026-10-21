#include "common.h"
#include "data/bss_0064.h"
#include "data/pieces/D_003F34C4.h"
typedef N_3f34c4 N;
#include "data/pieces/D_00425BC8.h"
extern s32 D_00640E00[];
extern s32 D_00640E24, D_00640E28;
extern s32 D_003F32A8[];
extern s32 D_003F32C8[];
extern s32 D_003F3308[];
extern void (*D_003F32E8[])(N *);
s32 func_001fd518(N *);
void func_00207830(N *, s32, s32, s32, s32, s32, s32);
s32 func_0021add8(void);
void func_00207560(N *, s32, s32);
void func_00207428(N *, s32, s32);
s32 func_001f42b8(N *);
void func_001f3840(N *);
void func_0011d768(s32);
void func_00207618(void);
void func_001fd858(N *);
void func_0020bd18(N *, s32);
s32 func_001fe570(N *);
void func_001f3708(N *, s32);
void func_001f36b8(N *);
N *func_001f4468(N *);
void func_001f37c0(N *, s32);
void func_001f3d58(N *, s32);
N *func_0021d9e0(N *);
N *func_00229338(N *);
N *func_001f31a8(s32, s32);
void func_001f3e90(N *, N *);
void func_001f3e20(N *, N *);
s32 func_001f4390(N *);

#include "data/pieces/D_003F34B8.h"
/* callee defined above (from src/hand/text_001f0000_h23.c) */
CONTEXT_ONLY u32 func_002073f0(s32 n) {
    return D_003F34B8->b112[n / 32] & (1 << n);
}
static inline void inl5(N *o) { if (func_0021add8()) func_00207560(o, 109, 215); if (!func_002073f0(0)) func_00207428(o, 92, 223); }
#define ITEM(n) { \
    s32 s; \
    if (n != 7) s = n == D_00640E28; \
    else s = (D_00640E28 == n) ? 19 : 18; \
    func_00207830(o, s, 2, 11, k, 122, D_003F32A8[n]); \
    if (n == 5) { if (func_0021add8()) func_00207560(o, 109, 215); if (!func_002073f0(0)) func_00207428(o, 92, 223); } \
}

/* rodata */
void func_0020c1c8(N *o) {
    f32 t = o->x94;
    s32 i, k, a, sel;
    switch (o->x24) {
    case 0:
        D_00640E24 = func_001fd518(o);
        D_00640E28 = D_00640E00[D_00640E24];
        a = o->x90;
        for (i = 0, k = 71; i < o->xcc; k += 28, i++) {
            f32 d = (f32)(i * 2);
            if (d <= t) {
                f32 e = t - d;
                if (e < 6.0f) o->x90 = (f32)a * (e / 6.0f);
                else o->x90 = a;
            } else o->x90 = 0;
            { s32 n = D_00640E00[i]; ITEM(n) }
        }
        o->x90 = a;
        if ((f32)(o->xcc * 2 + 4) <= t) o->x24++;
        break;
    case 1:
        if (func_001f42b8(o)) {
            if (D_00425BC8->x8 & 0x4000) {
                func_001f3840(o);
                func_0011d768(3);
                func_00207618();
            } else {
                func_001fd858(o);
                func_0020bd18(o, 8);
                D_00640E24 = func_001fd518(o);
                D_00640E28 = D_00640E00[D_00640E24];
                if (func_001fe570(o)) {
                    N *c, *d;
                    o->x24++;
                    o->x28 = t;
                    c = o->x10;
                    if (c) {
                        func_001f3708(c, 6);
                        c = c->x10;
                        if (c) {
                            func_001f36b8(c);
                            c = c->x10;
                            if (c) func_001f36b8(c);
                        }
                    }
                    c = func_001f4468(o);
                    switch (D_00640E28) {
                    case 5:
                        func_001f37c0(D_003F34C4->x10, 1);
                        func_001f3d58(D_003F34C4->x10->x10, 2);
                        func_001f3d58(D_003F34C4->x10->x10->x10, 2);
                        c = func_0021d9e0(c);
                        o->x24 = 4;
                        break;
                    case 7:
                        func_001f37c0(D_003F34C4->x10, 1);
                        func_001f3d58(D_003F34C4->x10->x10, 2);
                        func_001f3d58(D_003F34C4->x10->x10->x10, 2);
                        c = func_00229338(c);
                        o->x24 = 4;
                        break;
                    }
                    d = func_001f31a8(D_003F32C8[D_00640E28], D_003F3308[D_00640E28]);
                    if (d) {
                        func_001f3e90(c, d);
                        func_001f3e20(d, c);
                        { f32 v = 4.0f; s32 m = D_00640E28; d->xa0 = v; D_003F32E8[m](d); }
                    }
                }
            }
        }
        D_00640E24 = func_001fd518(o);
        D_00640E28 = D_00640E00[D_00640E24];
        for (i = 0, k = 71; i < o->xcc; k += 28, i++)
            { s32 n = D_00640E00[i]; ITEM(n) }
        break;
    case 2:
        t -= o->x28;
        D_00640E24 = func_001fd518(o);
        D_00640E28 = D_00640E00[D_00640E24];
        a = o->x90;
        for (i = 0, k = 71; i < o->xcc; k += 28, i++) {
            f32 d = (f32)((o->xcc - i) * 2 - 2);
            if (d <= t) {
                d = t - d;
                if (d < 6.0f) { d = 6.0f - d; o->x90 = (f32)a * (d / 6.0f); }
                else o->x90 = 0;
            } else o->x90 = a;
            { s32 n = D_00640E00[i]; ITEM(n) }
        }
        o->x90 = a;
        if ((f32)(o->xcc * 2 + 4) <= t) {
            o->x24++;
            if (func_001f4390(o)) func_001f36b8(o);
        }
        break;
    case 3:
        break;
    case 4:
        for (i = 0, k = 71; i < o->xcc; k += 28, i++)
            { s32 n = D_00640E00[i]; ITEM(n) }
        break;
    }
}

/* party member: 0x74 bytes; item slots at +0x22 */
typedef struct {
    u8 pad00[0x22];
    u8 items[0x74 - 0x22];
} DbMember;
/* same member viewed from +2 (indexed with item + 32) */
typedef struct {
    u8 pad00[2];
    u8 a[0x72];
} DbMemberB;
typedef struct {
    u8 pad000[4];
    DbMember m[10];
    u8 x48c;
    u8 x48d;
    u8 party[4];
} DbSave;
typedef struct {
    u8 pad000[4];
    DbMemberB m[10];
} DbSaveB;
typedef struct { u8 pad[9]; u8 x[1]; } DbSave9;
typedef struct { u8 pad[0x28]; s32 x28; } DbObj;
#include "data/pieces/D_00304BE8.h"
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
        DbMember *mp = &((DbSave *)D_00304BE8)->m[((DbSave *)D_00304BE8)->party[slot]];
        id = mp->items[item];
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
        bits |= func_00149600(id, ((DbSave *)D_00304BE8)->party[a3++]);
    } while (n != 0);
    for (i = 0; i < 7; i++) {
        if ((bits >> i) & 1) {
            if (slot != -1) {
                DbMemberB *mq = &((DbSaveB *)((DbSave *)D_00304BE8))->m[((DbSave *)D_00304BE8)->party[slot]];
                mq->a[item + 32] = 0;
            } else {
                ((DbSave9 *)((DbSave *)D_00304BE8))->x[item + 0x490]--;
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

#include "common.h"
typedef int u128 __attribute__((mode(TI)));

typedef struct {
    s32 key;
    s32 mask;
    s8 start;
    s8 len;
    u8 used;
} Slot;

typedef struct {
    u8 pad[0x88];
    s32 key;
    u8 pad8c[7];
    u8 bit;
} SlotOwner;

void func_00180e80(Slot *);

s32 func_00180f18(Slot *slots, s32 cnt, SlotOwner *o, u8 n) {
    union { u128 q; u8 b[16]; } buf;
    s32 i;
    s32 j;
    s32 run;
    s32 found;
    s32 key;
    s32 bit;
    Slot *best;
    Slot *s;

    key = o->key;
    bit = o->bit;
    for (i = 0; i < cnt; i++) {
        if (slots[i].used && key == slots[i].key) {
            s32 m = slots[i].mask;
            j = 1 << bit;
            if (m & j) return -1;
            slots[i].mask = m | j;
            return slots[i].start;
        }
    }
    buf.q = 0;
    for (i = 0; i < cnt; i++) {
        if (slots[i].used) {
            j = slots[i].len;
            if (j > 0) {
                u8 *p = (u8 *)((u32)slots[i].start + (u32)buf.b);
                do {
                    j--;
                    *p++ = 1;
                } while (j != 0);
            }
        }
    }
    run = 0;
    found = -1;
    for (i = 0; i < cnt; i++) {
        if (buf.b[i]) {
            run = 0;
        } else {
            run++;
            if (run == n) {
                found = i - n + 1;
                break;
            }
        }
    }
    if (found > 0) {
        for (i = 0; i < cnt; i++) {
            if (!slots[i].used) {
                slots[i].key = key;
                slots[i].mask = 1 << bit;
                slots[i].used = 1;
                slots[i].len = n;
                slots[i].start = found;
                return found;
            }
        }
    }
    best = 0;
    found = -1;
    for (i = 0; i < cnt; i++) {
        s = &slots[i];
        if (s->used) {
            if (n == s->len) {
                s->key = key;
                s->mask = 1 << bit;
                return s->start;
            }
            if (n < s->len) {
                if (best == 0 || s->len - n < found) {
                    found = s->len - n;
                    best = s;
                }
            }
        }
    }
    if (best) {
        best->key = key;
        best->len = n;
        best->mask = 1 << bit;
        return best->start;
    }
    for (i = 0; i < cnt; i++) {
        if (slots[i].used && slots[i].start < n) func_00180e80(&slots[i]);
    }
    for (i = 0; i < cnt; i++) {
        if (!slots[i].used) {
            slots[i].key = key;
            slots[i].mask = 1 << bit;
                slots[i].used = 1;
            slots[i].len = n;
            slots[i].start = 0;
            return 0;
        }
    }
    return -1;
}

/* --- effect objects: D_00364130 / D_00575A10 entries (0xC0 bytes) --- */

typedef struct {
    u8 pad[0x14];
    s32 flags;
} PLink;

typedef struct {
    u8 pad[0xb0];
    u8 xb0[0x48];
    u8 xf8;
    u8 padf9[3];
    u16 xfc;
    u16 xfe;
} POwner;

typedef struct PObj {
    u8 pad0[0x58];
    s32 x58;
    u8 pad5c[4];
    s32 x60;
    u8 pad64[0x22];
    u16 flags;
    s32 key;
    POwner *own;
    u8 x90;
    u8 x91;
    u8 pad92;
    u8 x93;
    PLink *link;
    s32 x98;
    f32 x9c;
    union {
        u64 d;
        struct {
            s32 lo;
            s16 a4;
            s16 a6;
        } s;
    } xa0;
    s32 xa8;
    f32 xac;
    union {
        u64 d;
        u8 b[8];
    } xb0;
    u8 padb8[8];
} PObj;

typedef struct {
    s32 key;
    s32 bit;
} PCur;

typedef struct {
    s32 a, b, c;
} V12;

typedef struct {
    V12 a[16];
} SEA0;

PObj *D_00575A10[0x10c] ALIGNED(16);
extern PCur D_003701B0;
#include "data/pieces/D_00370130.h"
extern u8 D_00370140[];
extern u8 D_00370170[];
extern s32 D_00372908;
extern s32 D_0061621C;
extern s32 D_00616224;
extern s32 D_00616228;
extern s32 D_0061622C;
extern f32 D_002BBDEC;
extern f32 D_002BBDFC;

void func_00180ea0(SEA0 *);
void func_001aa008(void);
void func_001aa8d0(void);
void *func_00122048(s32, s32);
void func_0017f948(void);
s32 func_00181608(PObj **);
void func_00180280(PObj *);
void func_00180ce0(void *);
void func_00180e10(void *);
void FlushCache(s32);
s32 sceGsSyncPath(s32, s32);
void func_00266f38(s32, void *);
void func_00181238(SEA0 *, PObj *);
void func_00181280(SEA0 *, PObj *);
void func_00180c20(s32, void *, s32);
void func_00180d50(s32, void *, s32);
void func_00180a48(PObj *);
void func_001807d8(PObj *);
s32 func_00183878(PObj *, s32);
void func_0011d3c8(u16, s32, s32);
void func_00182788(PObj *);
void func_001827f0(PObj *);
void func_0017f970(void);
void func_00182840(PObj *);
s32 func_00183958(PObj *);
void func_001220b8(void *);

void func_00181b30(void) {
    SEA0 tmp;
    void *h;
    PCur *cur;
    s32 first;
    s32 i;
    s32 n;

    first = 1;
    D_003701B0.bit = -1;
    D_003701B0.key = 0;
    func_00180ea0(&tmp);
    func_001aa008();
    func_001aa8d0();
    h = func_00122048(0x4000, 16);
    func_0017f948();
    n = func_00181608(D_00575A10);
    for (i = 0; i < n; i++) {
        PObj *e = D_00575A10[i];

        if ((e->flags & 1) && !(e->flags & 4)) {
            f32 lim = 0.0f;
            s32 same;
            s32 k;

            if (e->link->flags & 0x20) lim -= D_002BBDEC + D_002BBDEC;
            if (lim < e->xac) {
                if (D_0061621C) continue;
                if (e->xb0.d & 0xFF0000FF00) continue;
                e->xac -= D_002BBDFC;
                continue;
            }
            func_00180280(e);
            if (e->x90 && e->own->xf8) continue;
            if (e->flags & 0x20) continue;
            if (first) {
                func_00180ce0(D_00370130);
                first = 0;
                func_00180e10(D_00370130);
                FlushCache(0);
                sceGsSyncPath(0, 0);
                func_00266f38(D_00372908, D_00370140);
            }
            if (!e->x90 && !e->xb0.b[7] && e->x91) {
                func_00181238(&tmp, e);
                func_00181280(&tmp, e);
                if (e->xa0.s.a4) func_00180c20(e->key, e->own->xb0, e->xa0.s.a4);
                if (e->xa0.s.a6) func_00180d50(e->key, e->own->xb0, e->xa0.s.a6);
                if (e->xa0.d & 0xFFFFFFFF00000000) {
                    FlushCache(0);
                    sceGsSyncPath(0, 0);
                    func_00266f38(D_00372908, D_00370140);
                }
            } else {
                e->xa0.s.a4 = 0;
                e->xa0.s.a6 = 0;
            }
            same = 0;
            if (D_003701B0.key == e->key) same = D_003701B0.bit == e->x93;
            if (!same) func_00180a48(e);
            func_001807d8(e);
            k = 1;
            if (e->x90 || e->xb0.b[7]) k = 0;
            D_00616228 = 0;
            D_00616224 = D_0061622C;
            if (func_00183878(e, k)) {
                if (e->own->xfc) func_0011d3c8(e->own->xfc, e->xa8, 60);
                func_00182788(e);
                func_001827f0(e);
            }
            if (!e->x90 && !e->xb0.b[7]) func_0017f970();
            cur = &D_003701B0;
            cur->key = e->key;
            cur->bit = e->x93;
        } else if (e->flags & 2) {
            if (e->flags & 0x10) e->flags &= ~0x10;
            else func_00182840(e);
        } else if (e->flags & 4) {
            if (func_00183958(e)) {
                e->flags &= ~4;
                func_001827f0(e);
            }
        }
    }
    FlushCache(0);
    sceGsSyncPath(0, 0);
    func_00266f38(D_00372908, D_00370170);
    func_001220b8(h);
}
#include "data/bss_0061_mixed.h"
#include "data/data_0037.h"
#include "data/pieces/D_002BBDEC.h"
#include "data/pieces/D_002BBDFC.h"

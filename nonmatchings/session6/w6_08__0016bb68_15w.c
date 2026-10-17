/* func_0016bb68: 15 words off, hand/nostrict. Only reg alloc of t (orig t0) vs e=w->x98 (orig a2) is swapped; everything else matches. No CONTEXT needed. */
#include "common.h"
typedef struct { u8 pad[0x3c]; s32 x3c; s32 x40; } HpB;
typedef struct { u8 pad[0x21]; u8 n; u8 ids[1]; } ItB;
typedef struct { u8 pad[0xc8]; ItB *xc8; } SubB;
typedef struct { u32 x0; u8 pad4[0x68]; HpB *x6c; s32 w70; } EntB;
typedef struct { u32 x0; u8 pad4[0x68]; SubB *x6c; s32 w70; } ObjB;
typedef union { u64 x; struct { u64 lo:40; u64 id:16; u64 hi:8; } b; struct { u32 lo; u8 b4; } c; } BfB;
typedef struct {
    u32 x0; u8 pad4[0x7c]; BfB w80; EntB *x88; s32 x8c; u8 pad90[8]; EntB *x98;
} WkB;
typedef struct { u8 pad[0x78]; u8 x78; u8 pad79[3]; u8 x7c; } PrmB;
typedef struct { u8 pad[4]; u32 x4; } ResB;
extern PrmB D_0035AE80;
extern EntB *D_0035BD40[];
extern s32 D_0035BCC8[2][5];
s32 func_0012ca98(void);
void func_00157a30(ObjB *, s32);
ResB *func_00147840(u16);

static inline s32 inl_hp(EntB *e, s32 k) {
    if (e->x0 & 0x200) return 0;
    if (e->x6c->x40 * k < e->x6c->x3c * 255) return 0; return 1;
}

static inline s32 inl_has(ObjB *o, s32 id) {
    ItB *p; s32 n;
    s32 i;
    if (!func_0012ca98()) return 0;
    switch (o->w70) {
    case 0:
    case 8:
    case 24:
        p = o->x6c->xc8;
        for (i = 0; i < p->n; i++) {
            if (p->ids[i] == id) return 1;
        }
    }
    return 0;
}

s32 func_0016bb68(ObjB *o, WkB *w, s32 unused, s32 mode) {
    EntB *arr[3];
    s32 cnt = 0; s32 k;
    EntB *t, *e; s32 r;
    s32 i, id;
    
    arr[0] = (EntB *)o;
    arr[1] = D_0035BD40[0];
    arr[2] = D_0035BD40[w->x0 ^ 3];
    e = w->x98;
    if (e != 0 && inl_hp(e, D_0035AE80.x78)) t = e;
    else t = 0;
    for (i = 0; i < 3; i++) {
        if (arr[i] != 0 && inl_hp(arr[i], D_0035AE80.x78)) {
            if (t == 0) t = arr[i];
            cnt++;
        }
    }
    switch (mode) {
    case 1:
        if (cnt == 0) return 0;
        for (i = 0; i < 5; i++) {
            id = D_0035BCC8[0][i];
            r = inl_has(o, id); if (r) break;
        }
        if (i >= 5) return 0; break;
    case 2:
        w->w80.c.b4 = 3;
        w->x8c = 0;
        w->x88 = t;
        if (t != 0 && t != (EntB *)o && t == e) func_00157a30(o, 26);
        if (cnt >= 2) {
            for (i = 0; i < 5; i++) {
                r = inl_has(o, D_0035BCC8[1][i]);
                if (r) {
                    w->w80.b.id = D_0035BCC8[1][i];
                    break;
                }
            }
        } else {
            for (i = 0; i < 5; i++) {
                r = inl_has(o, D_0035BCC8[0][i]);
                if (r) {
                    w->w80.b.id = D_0035BCC8[0][i];
                    break;
                }
            }
        }
        if (func_00147840(w->w80.b.id)->x4 & 1) {
            w->x88 = 0;
            w->x8c = -1;
        }
    }
    return 1;
}

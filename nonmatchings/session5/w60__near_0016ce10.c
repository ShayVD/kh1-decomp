#include "common.h"
typedef struct { u8 pad[0x80]; u8 b80; } Prm6x;
extern Prm6x D_0035AE80;
typedef struct { u8 pad[0x3C]; s32 w3C; s32 w40; } Hp6C;
typedef struct { u32 flags; u8 pad4[0x68]; Hp6C *p6C; s32 w70; } Act6C;
extern Act6C *D_0035BD40[];
typedef struct {
    s32 w0; u8 pad4[0x34]; u64 w38; u8 pad40[0x40];
    union { u64 w; struct { u64 lo:32; u64 m:8; u64 z:16; u64 hi:8; } b; } w80;
    Act6C *p88; s32 w8C; void *p90; u8 pad94[4]; Act6C *p98;
} Wk6CE;
s32 func_00133000(Act6C *, s32);
void func_00157a30(Act6C *, s32);

static inline s32 inl_ok(Act6C *e, s32 K) {
    switch (e->w70) {
    case 0:
    case 8:
    case 24:
        if (func_00133000(e, K) == 0) break;
        return 1;
    }
    return 0;
}

static inline s32 inl_alive(Act6C *a) {
    s32 k = D_0035AE80.b80;
    if (a->flags & 0x200) return 0;
    if (a->p6C->w40 * k < a->p6C->w3C * 255) return 0;
    return 1;
}

s32 func_0016ce10(Act6C *e, Wk6CE *w, s32 unused, s32 mode) {
    Act6C *list[3];
    Act6C *t;
    Act6C *s;
    s32 i;
    list[0] = e;
    list[1] = D_0035BD40[0];
    list[2] = D_0035BD40[w->w0 ^ 3];
    t = w->p98;
    if (t != 0 && inl_alive(t)) s = t;
    else s = 0;
    for (i = 0; i < 3; i++) {
        if (list[i] != 0 && inl_alive(list[i]) && s == 0) {
            s = list[i];
            break;
        }
    }
    switch (mode) {
    case 0:
        return 0;
    case 1:
        if (!((s32)((s64)(w->w38 << 30) >> 32) & 1)) return 0;
        if (!inl_ok(e, 3)) return 0;
        if (s == 0) return 0;
        break;
    case 2:
        w->w80.b.m = mode;
        w->w8C = 0;
        w->p88 = s;
        w->w80.b.z = 3;
        if (s != 0 && e != s && t == s) func_00157a30(e, 26);
        break;
    }
    return 1;
}

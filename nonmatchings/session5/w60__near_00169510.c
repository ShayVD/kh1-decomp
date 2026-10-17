#include "common.h"
typedef struct { u8 pad[0x70]; s32 w70; u8 pad74[0xF0]; s32 w164; } Ent6C;
typedef struct { u8 pad[0x4C]; s32 w4C; u8 pad50[0x40]; void *p90; } Wk6C;
s32 func_00122ff8(void *);
s32 func_00123368(void *);

static inline s32 inl_a(s32 k, Wk6C *w) {
    if (k < 3) { if (k >= 0) return 1; }
    return k == w->w4C;
}
static inline s32 inl_b(s32 k, Wk6C *w) {
    if (k < 124) { if (k >= 117) return 1; }
    return k == w->w4C;
}
static inline s32 inl_c(s32 k, Wk6C *w) {
    if (k >= 0) { if (k < 3) return 1; if (k < 131) { if (k < 124) return k == w->w4C; return 1; } }
    return k == w->w4C;
}

s32 func_00169510(Ent6C *e, Wk6C *w, s32 flag) {
    s32 ok;
    s32 r;
    s32 m;
    switch (e->w70) {
    case 0:
        {
            s32 ma = inl_a(e->w164, w);
            ok = 0;
            if (ma) {
                if (flag & 6) break;
                goto yes;
            }
        }
        break;
    case 8:
        m = inl_b(e->w164, w);
        ok = 0;
        if (m) {
            if (flag & 3) break;
            goto yes;
        }
        break;
    case 24:
        {
            s32 mc = inl_c(e->w164, w);
            ok = 0;
            if (mc) {
                if (flag & 5) break;
                goto yes;
            }
        }
        break;
    default:
        ok = 0;
        break;
    }
    if (0) { yes: ok = 1; }
    r = 0;
    if (ok && w->p90 != 0) {
        r = func_00122ff8(w->p90);
        if (r) r = func_00123368(w->p90) != 0;
    }
    return r;
}

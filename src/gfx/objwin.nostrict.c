/* Windows drawn at objects (objwin.c), its nostrict part: the flag mode's functions (the rest is
 * in the files beside it). Read from the
 * code, not proved by a boot (docs/modules.md "Session 55"). */
#include "common.h"
#include "platform/vu.h"
#include "data/pieces/D_002E26C0.h"
#include "data/bss_0049.h"
#include "data/types/nostrict_text_00100000_s6_01_p2.h"
#include "data/types/nostrict_text_00100000_s6_01.h"
#include "data/pieces/D_0029B280.h"
#include "data/pieces/D_002A3F30.h"
#include "data/types/nostrict_text_00100000_s6_01_p.h"
#include "data/pieces/D_002BBDE0.h"
#include "data/pieces/D_002BCAF0.h"

/* func_0010a5d0 (from hand/nostrict/text_00100000_s7_w5.c). */
typedef int u128 __attribute__((mode(TI)));
extern u64 D_002B70B0[];
extern s32 D_00495250;
void func_0010a4d8(u64 *, s32, s32, s32, s32, s32, s32);
CONTEXT_ONLY s32 func_0010a550(u64 *p, s32 a1, s32 a2, s32 a3, s32 a4, s32 idx, s32 a6) {
    p[0] = D_002B70B0[idx];
    p[1] = 0;
    p += 2;
    func_0010a4d8(p, a2, a6, a4, 4, a3, D_00495250);
    ((s32 *)p)[7] = 0x8000;
    ((s32 *)p)[19] = 0x8000;
    return a1 + 13;
}
extern u8 D_002B72D0[];
extern u8 D_002B7210[];
extern u8 D_002B7350[];
extern u8 D_002B71D0[];
extern u8 D_002B7290[];
extern u8 D_002B7310[];
extern u8 D_002B7250[];
/* func_0010a5d0: mode hand/nostrict; needs CONTEXT_ONLY func_0010a550 above; `two = 2` local makes CSE share the constant. */
void func_0010a5d0(s32 a0, u8 *p, s32 n, s32 mode, s32 sub) {
    s32 loc[2];
    s32 two;
    u64 *q;
    *(u128 *)p = 0;
    *(s32 *)p = 0x7000000e;
    q = (u64 *)(p + 16);
    q[0] = ((u64)n << 47) | 0xd000400000008001ULL;
    q[1] = 0x4124124124128ULL;
    two = 2;
    loc[0] = 0;
    loc[1] = 0;
    switch (mode) {
    case 0:
        switch (sub) {
        case 1: func_0010a550((u64 *)(p + 32), two, a0, (s32)loc, (s32)D_002B7210, 23, (s32)D_002B71D0); break;
        case 2: func_0010a550((u64 *)(p + 32), two, a0, (s32)loc, (s32)D_002B72D0, 26, (s32)D_002B71D0); break;
        }
        break;
    case 1:
        switch (sub) {
        case 1: func_0010a550((u64 *)(p + 32), two, a0, (s32)loc, (s32)D_002B7250, 22, (s32)D_002B71D0); break;
        case 2: func_0010a550((u64 *)(p + 32), two, a0, (s32)loc, (s32)D_002B7310, 25, (s32)D_002B71D0); break;
        }
        break;
    case 2:
        switch (sub) {
        case 1: func_0010a550((u64 *)(p + 32), two, a0, (s32)loc, (s32)D_002B7290, 24, (s32)D_002B71D0); break;
        case 2: func_0010a550((u64 *)(p + 32), two, a0, (s32)loc, (s32)D_002B7350, 27, (s32)D_002B71D0); break;
        }
        break;
    }
}

/* func_0010a780 (from hand/nostrict/text_00100000_s10_w1.c). */
typedef struct { u8 pad[0xa]; u16 kind; u8 padc[0x34]; f32 w, h; } Win;
CONTEXT_ONLY f32 D_002B67F0[4][4] = { { 0 } };
extern u8 D_002B6830[];
extern u8 D_002B6870[];
extern u8 D_002B68F0[];
extern u8 D_002B68B0[];
extern u8 D_002B6A30[];
extern u8 D_002B69F0[];
extern u8 D_002B6930[];
extern u8 D_002B6970[];
extern u8 D_002B6A70[];
extern u8 D_002B69B0[];
extern u8 D_002B6AB0[];
extern u8 D_002B6C30[];
extern u8 D_002B6C70[];
extern u8 D_002B6B70[];
extern u8 D_002B6AF0[];
extern u8 D_002B6BB0[];
extern u8 D_002B6BF0[];
extern u8 D_002B6B30[];
extern u8 D_002B6D70[];
extern u8 D_002B6CB0[];
extern u8 D_002B6CF0[];
extern u8 D_002B6D30[];
extern u8 D_002B6DF0[];
extern u8 D_002B6E30[];
extern u8 D_002B6E70[];
extern u8 D_002B6DB0[];
extern u8 D_002B6F70[];
extern u8 D_002B6EF0[];
extern u8 D_002B6EB0[];
extern u8 D_002B6F30[];
extern u8 D_002B6FB0[];
extern u8 D_002B7070[];
extern u8 D_002B6FF0[];
extern u8 D_002B7030[];
/* kh1-decomp session 10, worker w1: func_0010a780 (hand/nostrict), plain C
   and stock 2.96 gas. CONTEXT_ONLY func_0010a550 above it.
   The `lui t2; jal; addiu t2,%lo(D_002B67F0)` tail: jump2 cross-jumps the
   two arms' lo_sum sets into one `la $10,D_002B67F0` (REG_EQUAL), which gcc
   leaves to gas in a reorder-mode jal. ee-as 2.96 moves the la's addiu into
   the jal slot only when the symbol is defined earlier in the same file (an
   undefined extern gets a variant frag: it might be small data). So the
   original file defined the D_002B67F0 vertex table above this function.
   It is a CONTEXT_ONLY data definition here (weak, .ctx: the build makes it
   undefined again, so it resolves to 0x002B67F0). */
void func_0010a780(Win *win, void *a1, u128 *buf, s32 a3, s32 mode) {
    f32 pos[2];
    u64 *q;
    s32 nx, ny, cnt, n, i, j;

    nx = win->w;
    ny = win->h;
    *buf = 0;
    if (mode == 1) {
        cnt = (nx + 2) * (ny + 2);
        *(u32 *)buf = cnt * 13 + 0x70000001;
    } else {
        cnt = (nx + ny) * 2 + 4;
        *(u32 *)buf = cnt * 13 + 0x70000001;
    }
    q = (u64 *)(buf + 1);
    q[0] = (cnt | 0x8000) | ((u64)a3 << 47) | 0xd000400000000000;
    q[1] = 0x4124124124128;
    pos[1] = -(win->h * 0.5f * 24.0f + 12.0f);
    pos[0] = -(win->w * 0.5f * 24.0f + 12.0f);
    switch (win->kind) {
    case 3:
        n = func_0010a550((u64 *)(buf + 2), 2, (s32)a1, (s32)pos, (s32)D_002B6DB0, 10, (s32)D_002B6CB0);
        break;
    case 4:
        n = func_0010a550((u64 *)(buf + 2), 2, (s32)a1, (s32)pos, (s32)D_002B6EB0, 14, (s32)D_002B67F0);
        break;
    case 1:
        n = func_0010a550((u64 *)(buf + 2), 2, (s32)a1, (s32)pos, (s32)D_002B6FB0, 18, (s32)D_002B67F0);
        break;
    default:
        n = func_0010a550((u64 *)(buf + 2), 2, (s32)a1, (s32)pos, (s32)D_002B6830, 0, (s32)D_002B67F0);
        break;
    }
    pos[0] += 24.0f;
    for (i = 0; i < nx; i++) {
        switch (win->kind) {
        case 4:
            n = func_0010a550((u64 *)(buf + n), n, (s32)a1, (s32)pos, (s32)D_002B6AF0, 28, (s32)D_002B67F0);
            break;
        case 1:
            n = func_0010a550((u64 *)(buf + n), n, (s32)a1, (s32)pos, (s32)D_002B6BF0, 32, (s32)D_002B67F0);
            break;
        default:
            n = func_0010a550((u64 *)(buf + n), n, (s32)a1, (s32)pos, (s32)D_002B69F0, 6, (s32)D_002B67F0);
            break;
        }
        pos[0] += 24.0f;
    }
    switch (win->kind) {
    case 3:
        n = func_0010a550((u64 *)(buf + n), n, (s32)a1, (s32)pos, (s32)D_002B6DF0, 11, (s32)D_002B6CF0);
        break;
    case 4:
        n = func_0010a550((u64 *)(buf + n), n, (s32)a1, (s32)pos, (s32)D_002B6EF0, 15, (s32)D_002B67F0);
        break;
    case 1:
        n = func_0010a550((u64 *)(buf + n), n, (s32)a1, (s32)pos, (s32)D_002B6FF0, 19, (s32)D_002B67F0);
        break;
    default:
        n = func_0010a550((u64 *)(buf + n), n, (s32)a1, (s32)pos, (s32)D_002B6870, 1, (s32)D_002B67F0);
        break;
    }
    pos[1] += 24.0f;
    for (j = 0; j < ny; j++) {
        pos[0] = -(win->w * 0.5f * 24.0f + 12.0f);
        switch (win->kind) {
        case 4:
            n = func_0010a550((u64 *)(buf + n), n, (s32)a1, (s32)pos, (s32)D_002B6AB0, 29, (s32)D_002B67F0);
            break;
        case 1:
            n = func_0010a550((u64 *)(buf + n), n, (s32)a1, (s32)pos, (s32)D_002B6BB0, 33, (s32)D_002B67F0);
            break;
        default:
            n = func_0010a550((u64 *)(buf + n), n, (s32)a1, (s32)pos, (s32)D_002B69B0, 7, (s32)D_002B67F0);
            break;
        }
        pos[0] += 24.0f;
        for (i = 0; i < nx; i++) {
            if (mode == 1) {
                if (win->kind == mode) {
                    n = func_0010a550((u64 *)(buf + n), n, (s32)a1, (s32)pos, (s32)D_002B6970, 5, (s32)D_002B67F0);
                } else {
                    n = func_0010a550((u64 *)(buf + n), n, (s32)a1, (s32)pos, (s32)D_002B6930, 4, (s32)D_002B67F0);
                }
            }
            pos[0] += 24.0f;
        }
        switch (win->kind) {
        case 4:
            n = func_0010a550((u64 *)(buf + n), n, (s32)a1, (s32)pos, (s32)D_002B6B30, 30, (s32)D_002B67F0);
            break;
        case 1:
            n = func_0010a550((u64 *)(buf + n), n, (s32)a1, (s32)pos, (s32)D_002B6C30, 34, (s32)D_002B67F0);
            break;
        default:
            n = func_0010a550((u64 *)(buf + n), n, (s32)a1, (s32)pos, (s32)D_002B6A30, 8, (s32)D_002B67F0);
            break;
        }
        pos[1] += 24.0f;
    }
    pos[0] = -(win->w * 0.5f * 24.0f + 12.0f);
    switch (win->kind) {
    case 3:
        n = func_0010a550((u64 *)(buf + n), n, (s32)a1, (s32)pos, (s32)D_002B6E30, 12, (s32)D_002B6D30);
        break;
    case 4:
        n = func_0010a550((u64 *)(buf + n), n, (s32)a1, (s32)pos, (s32)D_002B6F30, 16, (s32)D_002B67F0);
        break;
    case 1:
        n = func_0010a550((u64 *)(buf + n), n, (s32)a1, (s32)pos, (s32)D_002B7030, 20, (s32)D_002B67F0);
        break;
    default:
        n = func_0010a550((u64 *)(buf + n), n, (s32)a1, (s32)pos, (s32)D_002B68B0, 2, (s32)D_002B67F0);
        break;
    }
    pos[0] += 24.0f;
    for (i = 0; i < nx; i++) {
        switch (win->kind) {
        case 4:
            n = func_0010a550((u64 *)(buf + n), n, (s32)a1, (s32)pos, (s32)D_002B6B70, 31, (s32)D_002B67F0);
            break;
        case 1:
            n = func_0010a550((u64 *)(buf + n), n, (s32)a1, (s32)pos, (s32)D_002B6C70, 35, (s32)D_002B67F0);
            break;
        default:
            n = func_0010a550((u64 *)(buf + n), n, (s32)a1, (s32)pos, (s32)D_002B6A70, 9, (s32)D_002B67F0);
            break;
        }
        pos[0] += 24.0f;
    }
    switch (win->kind) {
    case 3:
        func_0010a550((u64 *)(buf + n), n, (s32)a1, (s32)pos, (s32)D_002B6E70, 13, (s32)D_002B6D70);
        break;
    case 4:
        func_0010a550((u64 *)(buf + n), n, (s32)a1, (s32)pos, (s32)D_002B6F70, 17, (s32)D_002B67F0);
        break;
    case 1:
        func_0010a550((u64 *)(buf + n), n, (s32)a1, (s32)pos, (s32)D_002B7070, 21, (s32)D_002B67F0);
        break;
    default:
        func_0010a550((u64 *)(buf + n), n, (s32)a1, (s32)pos, (s32)D_002B68F0, 3, (s32)D_002B67F0);
        break;
    }
}

/* func_0010b390 (from hand/nostrict/text_00100000_s11_w13.c). */
typedef struct {
    s32 id;
    s16 pad4;
    s16 f6;
    u16 anim;
    u16 kind;
    u8 padc[0x10];
    f32 f1c;
    u8 pad20[0x10];
    f32 x, y;
    u8 pad38[8];
    f32 w, h;
    u8 pad48[0x18];
    u8 m60[0x40];
} Win_0b390;
extern void func_00133830(s32, void *);
void func_0010b390(Win_0b390 *w, f32 *o) {
    s32 t[4];
    f32 a[4];
    f32 b[4];
    s32 x, y;
    f32 lim;
    u32 k;
    s32 id;
    f32 W, H, D, f, yy;
    f32 zero = 0.0f, one = 1.0f;

    o[0] = zero;
    o[3] = one;
    o[2] = zero;
    id = w->id;
    o[1] = w->h * 0.5f * 24.0f;
    if (id != -1) {
        w->f6 = 0;
        PlatVu0RotTransPers(t, D_002E26C0, w->m60, 1);
        x = w->x + 256.0f;
        y = w->y + 192.0f;
        t[0] = (t[0] >> 4) - 1792;
        t[1] = (t[1] >> 4) - 1856;
        o[0] = t[0] - x;
        if (o[0] < -w->w * 0.5f * 24.0f) {
            o[0] = -w->w * 0.5f * 24.0f;
        }
        lim = w->w * 0.5f * 24.0f;
        if (lim < o[0]) {
            o[0] = lim;
        }
        a[0] = x;
        a[1] = y;
        a[2] = zero;
        a[3] = one;
        b[0] = t[0];
        b[1] = t[1];
        b[2] = zero;
        b[3] = one;
        PlatVu0Normalize(a, a);
        PlatVu0Normalize(b, b);
        w->f1c = zero;
        if (t[2] <= 0) w->f6 = 0;
        if (t[0] < 0) w->f6 = 1;
        if (t[0] > 512) w->f6 = 1;
        if (t[1] < 0) w->f6 = 1;
        if (t[1] > 384) w->f6 = 1;
        func_00133830(w->id, w->m60);
        return;
    }
    if (w->anim < 5) {
        D = w->w * 0.5f * 24.0f;
        W = D * 0.5f * (f32)w->anim;
        f = W - D;
        o[0] = f;
        o[1] = -(w->h * 0.5f * 24.0f);
    } else if (w->anim < 10) {
        f32 c = (f32)(w->anim - 5);
        o[0] = w->w * 0.5f * 24.0f;
        D = w->h * 0.5f * 24.0f;
        W = D * 0.5f * c;
        o[1] = W - D;
    } else if (w->anim < 15) {
        f32 c = (f32)abs(14 - w->anim);
        D = w->w * 0.5f * 24.0f;
        W = D * 0.5f * c;
        o[0] = W - D;
        o[1] = w->h * 0.5f * 24.0f;
    } else {
        f32 c = (f32)abs(19 - w->anim);
        o[0] = -(w->w * 0.5f * 24.0f);
        D = w->h * 0.5f * 24.0f;
        W = D * 0.5f * c;
        o[1] = W - D;
    }
}

/* func_0010b6c0 (from hand/nostrict/text_00100000_s6_01.c). */
extern s32 func_00106b18(void *);
typedef struct {
    s32 id;
    s16 pad4;
    u16 f6;
    u16 anim;
    u16 kind;
    u8 padc[0x10];
    f32 f1c;
    u8 pad20[0x10];
    f32 x, y;
    u8 pad38[8];
    f32 w, h;
    u8 pad48[8];
    f32 f50, f54;
} Win_0b6c0;
typedef struct { u8 pad[0x1c]; f32 ry; } Rot;
extern Mtx D_00495190;
extern Mtx D_00495210;
extern u8 D_004951D0[];
extern s32 D_002BBE18;
extern u8 D_002B74C0[];
extern u8 D_002B73E0[];
extern u8 D_002B73B0[];
extern u8 D_002B7450[];
extern u8 D_002B7490[];
extern u8 D_002B67D0[];
extern u8 D_002B67E0[];
extern void func_0010b208(void *, void *, void *);
extern s32 func_00121e28(s32, s32 *);
extern void func_0010b190(Win_0b6c0 *);
extern void func_0010b270(void *, Win_0b6c0 *);
extern void func_00121eb0(s32);
extern s32 func_00122048(s32, s32);
extern void func_00106b58(s32);
extern void func_001220b8(s32);
CONTEXT_ONLY void func_0010b2d0(Mtx out, Rot *r, void *t) {
    Mtx m;
    f32 a = r->ry;
    if (a > 180.0f) {
        a -= 180.0f;
    } else {
        a += -180.0f;
    }
    PlatVu0RotMatrixZ(m, D_002BCAF0, a / 180.0f * 3.1415928f);
    PlatVu0TransMatrix(m, m, t);
    PlatVu0MulMatrix(m, D_00495190, m);
    PlatVu0MulMatrix(out, D_00495210, m);
}
extern void *D_00495250_0010b6c0 __asm__("D_00495250");
#define D_00495250 D_00495250_0010b6c0
#define func_0010a780 ((void (*)(Win_0b6c0 *, void *, s32, s32, s32)) func_0010a780)
#define func_0010b390 ((void (*)(Win_0b6c0 *, f32 *)) func_0010b390)
/* func_0010b6c0 needs func_0010a5d0 and func_0010b2d0 defined above (CONTEXT_ONLY copies). */
void func_0010b6c0(Win_0b6c0 *w) {
    u8 m[64] __attribute__((aligned(16)));
    f32 v[4];
    s32 p;
    s32 h = 0;
    f32 k;

    func_0010b208(D_00495190, D_004951D0, &w->f50);
    if (D_002BBE18 == 0) {
        func_00106b18(D_002B73B0);
    } else {
        func_00106b18(D_002B73E0);
    }
    switch (w->kind) {
    case 0:
        break;
    case 1:
        func_00106b18(D_002B7490);
        p = func_00121e28((s32)((w->w + 2.0f) * (w->h + 2.0f) * 13.0f + 2.0f) << 4, &p);
        D_00495250 = D_002B67D0;
        func_0010b190(w);
        func_0010b270(m, w);
        func_0010a780(w, m, p, 84, 1);
        func_00106b18((void *)p);
        func_00121eb0(p);
        break;
    default:
        k = 3.0f;
        func_00106b18(D_002B7450);
        w->x += w->f50 * k;
        w->y += w->f54 * k;
        D_00495250 = D_002B67E0;
        func_0010b190(w);
        func_0010b390(w, v);
        if (w->f6) {
            h = func_00122048(240, 128);
            func_0010b2d0((void *)m, (Rot *)w, v);
            func_0010a5d0((s32)m, (u8 *)h, 84, 0, w->f6);
            func_00106b58(h);
        }
        p = func_00121e28((s32)((w->w + 2.0f) * (w->h + 2.0f) * 13.0f + 2.0f) << 4, &p);
        func_0010b270(m, w);
        func_0010a780(w, m, p, 84, 0);
        func_00106b18((void *)p);
        func_00106b18(D_002B7490);
        w->x -= w->f50 * k;
        w->y -= w->f54 * k;
        D_00495250 = D_002B67D0;
        func_0010b190(w);
        if (w->f6 && (u16)(w->anim - 5) < 10) {
            func_0010b2d0((void *)m, (Rot *)w, v);
            func_0010a5d0((s32)m, (u8 *)h, 84, 0, w->f6);
            func_00106b58(h);
        }
        if (w->f6 && !((u16)(w->anim - 5) < 10)) {
            func_0010b2d0((void *)m, (Rot *)w, v);
            func_0010a5d0((s32)m, (u8 *)h, 84, 1, w->f6);
            func_00106b58(h);
        }
        func_0010b270(m, w);
        func_0010a780(w, m, p, 84, 1);
        func_00106b18((void *)p);
        if (w->f6) {
            func_0010b2d0((void *)m, (Rot *)w, v);
            func_0010a5d0((s32)m, (u8 *)h, 84, 2, w->f6);
            func_00106b58(h);
        }
        func_00121eb0(p);
        if (w->f6) {
            func_001220b8(h);
        }
        break;
    }
    func_00106b18(D_002B74C0);
}
#undef D_00495250
#undef func_0010a780
#undef func_0010b390


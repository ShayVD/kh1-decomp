#include "common.h"

typedef struct { u8 pad[8]; u32 x8; u8 padc[4]; u32 x10; } Pad;
typedef struct {
    u8 pad0[0xca];
    s16 ca;
    u8 padcc[0xd0 - 0xcc];
    s16 d0;
    s16 d2;
    u8 padd4[0xd8 - 0xd4];
    s16 n;
    s16 cur;
} WinK;
typedef struct { u8 pad[0xd8]; s16 n; } WinM;
typedef struct {
    u8 pad0[0xbe];
    s16 be;
    u8 padc0[2];
    s16 c2;
    s16 c4;
    s16 c6;
    u8 padc8[0xcc - 0xc8];
    s16 cc;
    s16 ce;
    u8 padd0[0xd8 - 0xd0];
    s16 d8;
} Win;
typedef struct {
    u8 pad0[0x48];
    u64 flags;
    s32 x50, x54, x58, x5c;
    u8 pad60[0x80 - 0x60];
    u32 kind;
    u8 pad84[0xac - 0x84];
    s32 xac;
    s32 xb0;
    s32 xb4;
} Wn;

#include "data/pieces/D_00425BC8.h"
extern u32 D_00640DF0; /* src/data/bss_0064.c: s32 D_00640DF0 */
extern u32 D_00640DF4; /* src/data/bss_0064.c: s32 D_00640DF4 */
extern u32 D_00640DF8; /* src/data/bss_0064.c: s32 D_00640DF8 */

void func_0011d768(s32);
u8 *func_001efbb8(s32);
u8 *func_001efc10(s32);
void func_001f8e18(void *);
void func_001f8f30(void);
s32 func_001f94f0(void *, s32, s32, s32, u8 *, s32, s32);
s32 func_001fb428(void *, s32, s32, s32, s32, s32, s32, s32, s32);
s32 func_001fc308(void *, s32, s32, s32, s32, s32, s32, s32, s32);
s32 func_001fd518(void *);
s32 func_001fd538(void *);
s32 func_001fd590(void *);
s32 func_001fd618(void *);
s32 func_001fd658(void *);
void func_00207830(Win *, s32, s32, s32, s32, s32, s32);
void func_00207870(Win *, s32, s32, s32, s32, s32, s32);
void func_002078b0(Win *, s32, s32, s32, s32, s32, s32);
void func_002078f0(Win *, s32, s32, s32, s32, s32, s32, s32, s32);
void func_00207938(Win *, s32, s32, s32, s32, s32, s32, s32, s32);
void func_00207980(Win *, s32, s32, s32, s32, s32, s32, s32, s32);

s32 func_001fa318(void *o, s32 a1, s32 x, s32 y, s32 str, s32 a5, s32 col, s32 ecol) {
    u8 *s;
    if (str == 0) return x;
    s = func_001efbb8(str);
    func_001f94f0(o, a1, x - 1, y - 1, s, a5, ecol);
    func_001f94f0(o, a1, x + 1, y - 1, s, a5, ecol);
    func_001f94f0(o, a1, x - 1, y + 1, s, a5, ecol);
    func_001f94f0(o, a1, x + 1, y + 1, s, a5, ecol);
    return func_001f94f0(o, a1, x, y, s, a5, col);
}

s32 func_001fbb50(void *a0, s32 a1, s32 a2, s32 a3, s32 x, s32 y, s32 a6, s32 a7, s32 col, s32 ecol) {
    func_001fb428(a0, a1, a2, a3, x - 1, y - 1, a6, a7, ecol);
    func_001fb428(a0, a1, a2, a3, x + 1, y - 1, a6, a7, ecol);
    func_001fb428(a0, a1, a2, a3, x - 1, y + 1, a6, a7, ecol);
    func_001fb428(a0, a1, a2, a3, x + 1, y + 1, a6, a7, ecol);
    return func_001fb428(a0, a1, a2, a3, x, y, a6, a7, col);
}

void func_001fdfd0(WinK *w) {
    s32 n = w->n;
    s32 moved;
    s32 k, r;
    Pad *pd;
    u32 m;
    if (n < 2) {
        w->cur = 0;
        return;
    }
    if ((w->cur >> 4) >= n) w->cur = (n - 1) << 4;
    pd = ((Pad *)D_00425BC8);
    m = pd->x10 & D_00640DF8;
    moved = 0;
    if (m & D_00640DF0) {
        if (w->cur > 0) {
            w->cur -= 16;
            moved = 1;
        } else if (pd->x8 & D_00640DF0) {
            moved = 1;
            w->cur = (n - 1) << 4;
        }
    } else if (m & D_00640DF4) {
        if (w->cur < (n - 1) << 4) {
            w->cur += 16;
            moved = 1;
        } else if (pd->x8 & D_00640DF4) {
            w->cur = 0;
            moved = 1;
        }
    }
    k = w->ca;
    if (w->d0 + w->d2 >= (k + n - 1) / n * 16 - 24) {
        r = k % n;
        if (r != 0 && (w->cur >> 4) >= r) {
            w->cur = 0;
            moved = 0;
        }
    }
    if (moved) func_0011d768(1);
}

void func_00203890(WinM *o, s32 x, s32 y, s32 x2, s32 col) {
    s32 cur, mid, a, b;
    if (o->n < 2) return;
    cur = func_001fd538(o);
    a = cur == 0 ? 17 : 15;
    b = cur == o->n - 1 ? 18 : 16;
    func_001fc308(o, x, y, 0, 0, a, 0, col, col);
    func_001fc308(o, x2, y, 0, 0, b, 0, col, col);
    y--;
    mid = x + (x2 - x + 9) / 2;
    func_001fb428(o, 1, 0, 0, mid - 7, y, func_001fd538(o) + 1, 15, col);
    func_001f94f0(o, 0, mid - 7, y, func_001efc10(84), 15, col);
    func_001fb428(o, 0, 0, 0, mid + 6, y, func_001fd658(o), 15, col);
}

void func_00209340(Win *o, s32 a1, s32 *strs) {
    s32 x0 = o->be >> 4;
    s32 dx = o->c2 >> 4;
    s32 dy = o->c4 >> 4;
    s32 sr = func_001fd518(o);
    s32 sc = func_001fd538(o);
    s32 idx = func_001fd618(o);
    s32 y = func_001fd590(o);
    s32 rows = o->ce;
    s32 w = dx - (o->c6 >> 4);
    s32 cnt = o->cc;
    s32 cols = o->d8;
    s32 r, c, x;
    func_001f8e18(o);
    for (r = 0; r < rows + 1; r++) {
        x = x0;
        for (c = 0; c < cols; c++) {
            if (idx >= cnt) goto done;
            func_00207830(o, r == sr && c == sc, a1, x, y, w, strs[idx]);
            idx++;
            x += dx;
        }
        y += dy;
    }
done:
    func_001f8f30();
}

void func_002094e0(Win *o, s32 a1, s32 *strs) {
    s32 x0 = o->be >> 4;
    s32 dx = o->c2 >> 4;
    s32 dy = o->c4 >> 4;
    s32 sr = func_001fd518(o);
    s32 sc = func_001fd538(o);
    s32 idx = func_001fd618(o);
    s32 y = func_001fd590(o);
    s32 rows = o->ce;
    s32 w = dx - (o->c6 >> 4);
    s32 cnt = o->cc;
    s32 cols = o->d8;
    s32 r, c, x;
    func_001f8e18(o);
    for (r = 0; r < rows + 1; r++) {
        x = x0;
        for (c = 0; c < cols; c++) {
            if (idx >= cnt) goto done;
            func_00207870(o, r == sr && c == sc, a1, x, y, w, strs[idx]);
            idx++;
            x += dx;
        }
        y += dy;
    }
done:
    func_001f8f30();
}

void func_00209680(Win *o, s32 a1, s32 *strs) {
    s32 x0 = o->be >> 4;
    s32 dx = o->c2 >> 4;
    s32 dy = o->c4 >> 4;
    s32 sr = func_001fd518(o);
    s32 sc = func_001fd538(o);
    s32 idx = func_001fd618(o);
    s32 y = func_001fd590(o);
    s32 rows = o->ce;
    s32 w = dx - (o->c6 >> 4);
    s32 cnt = o->cc;
    s32 cols = o->d8;
    s32 r, c, x;
    func_001f8e18(o);
    for (r = 0; r < rows + 1; r++) {
        x = x0;
        for (c = 0; c < cols; c++) {
            if (idx >= cnt) goto done;
            func_002078b0(o, r == sr && c == sc, a1, x, y, w, strs[idx]);
            idx++;
            x += dx;
        }
        y += dy;
    }
done:
    func_001f8f30();
}

void func_00209820(Win *o, s32 a1, s32 a2, s32 a3, s32 *strs) {
    s32 x0 = o->be >> 4;
    s32 dx = o->c2 >> 4;
    s32 dy = o->c4 >> 4;
    s32 sr = func_001fd518(o);
    s32 sc = func_001fd538(o);
    s32 idx = func_001fd618(o);
    s32 y = func_001fd590(o);
    s32 rows = o->ce;
    s32 w = dx - (o->c6 >> 4);
    s32 cnt = o->cc;
    s32 cols = o->d8;
    s32 r, c, x;
    func_001f8e18(o);
    for (r = 0; r < rows + 1; r++) {
        x = x0;
        for (c = 0; c < cols; c++) {
            if (idx >= cnt) goto done;
            func_002078f0(o, r == sr && c == sc, a1, a2, x, y, w, a3, strs[idx]);
            idx++;
            x += dx;
        }
        y += dy;
    }
done:
    func_001f8f30();
}

void func_002099d8(Win *o, s32 a1, s32 a2, s32 a3, s32 *strs) {
    s32 x0, dx, dy, sr, sc, idx, y, rows, w, r, cnt, cols, c, x;
    x0 = o->be >> 4;
    dx = o->c2 >> 4;
    dy = o->c4 >> 4;
    sr = func_001fd518(o);
    sc = func_001fd538(o);
    idx = func_001fd618(o);
    y = func_001fd590(o);
    rows = o->ce;
    w = dx - (o->c6 >> 4);
    cnt = o->cc;
    cols = o->d8;
    func_001f8e18(o);
    for (r = 0; r < rows + 1; r++) {
        x = x0;
        for (c = 0; c < cols; c++) {
            if (idx >= cnt) goto done;
            func_00207938(o, r == sr && c == sc, a1, a2, x, y, w, a3, strs[idx]);
            idx++;
            x += dx;
            a3 += dx;
        }
        y += dy;
    }
done:
    func_001f8f30();
}

void func_00209b90(Win *o, s32 a1, s32 a2, s32 a3, s32 *strs) {
    s32 x0, dx, dy, sr, sc, idx, y, rows, w, r, cnt, cols, c, x;
    x0 = o->be >> 4;
    dx = o->c2 >> 4;
    dy = o->c4 >> 4;
    sr = func_001fd518(o);
    sc = func_001fd538(o);
    idx = func_001fd618(o);
    y = func_001fd590(o);
    rows = o->ce;
    w = dx - (o->c6 >> 4);
    cnt = o->cc;
    cols = o->d8;
    func_001f8e18(o);
    for (r = 0; r < rows + 1; r++) {
        x = x0;
        for (c = 0; c < cols; c++) {
            if (idx >= cnt) goto done;
            func_00207980(o, r == sr && c == sc, a1, a2, x, y, w, a3, strs[idx]);
            idx++;
            x += dx;
            a3 += dx;
        }
        y += dy;
    }
done:
    func_001f8f30();
}

/* needs make: uses rodata */
void func_001f5e10(Wn *o) {
    switch (o->kind) {
    case 0:
    case 1:
    case 2:
        break;
    case 3:
    case 4:
        o->x50 = o->xb4;
        break;
    case 5:
    case 6:
        o->x50 = o->xb0;
        break;
    case 7:
    case 8:
    case 9:
    case 10:
    case 25:
    case 26:
        o->x50 = o->xb0;
        o->x54 = o->xb4;
        break;
    case 27:
        o->flags |= 1;
        o->x50 = o->xb0;
        o->x54 = o->xb4;
        break;
    case 11: case 12: case 13: case 14: case 15: case 16: case 17: case 18:
    case 19: case 20: case 21: case 22: case 23: case 24:
    case 28: case 29: case 30: case 31: case 32: case 33: case 34: case 35:
        o->flags |= 1;
        break;
    case 36:
        o->flags |= 1;
        o->xac = 2;
        o->x50 = o->xb4;
        break;
    case 37:
        o->flags |= 1;
        o->xac = 1;
        o->x50 = o->xb4;
        break;
    case 39:
        o->flags |= 1;
        o->xac = 3;
        o->x50 = o->xb0;
        break;
    case 40:
        o->flags |= 1;
        o->xac = 1;
        o->x50 = o->xb4;
        break;
    case 41:
        o->flags |= 1;
        o->xac = 2;
        o->x50 = o->xb4;
        break;
    case 42:
        o->flags |= 1;
        o->xac = 3;
        o->x50 = o->xb0;
        break;
    case 48:
        {
            s32 b = o->xb0;
            o->x58 = b + 0xa0;
            o->x54 = b - 0x200;
            o->x5c = b;
            o->x50 = b + 0xd00;

        }
        break;
    case 49:
        {
            s32 b = o->xb0;
            o->x54 = b + 0x2a0;
            o->x58 = b;
            o->x50 = b - 0x500;
        }
        break;
    case 52:
        o->flags |= 1;
        o->xac = 1;
        o->x50 = o->xb4;
        break;
    case 53:
        o->flags |= 1;
        o->xac = 2;
        o->x50 = o->xb4;
        break;
    case 38:
    case 43:
    case 54:
        o->flags |= 1;
        o->xac = 4;
        o->x50 = o->xb0;
        break;
    }
}

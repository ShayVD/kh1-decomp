/* Menus in the text windows (docs/modules.md "Session 38"),
 * 0x001fd248-0x001fea38.
 *
 * The text area of a window (TextWin +0xb0 ... +0xdb), in 1/16 pixels unless
 * noted: the origin +0xb0 / +0xb4 (with the GS offset 0x7000), the size
 * +0xb8 / +0xba, the margins and cell size +0xbe ... +0xc8, the item count
 * +0xca (+0xcc rows of +0xd8 columns, rounded up), +0xce, the scroll
 * +0xd0, the cursor +0xd2, the scroll / cursor steps +0xd4 / +0xd6 (the sign
 * is the direction), the columns +0xd8 and the column cursor +0xda.  The
 * getters and setters convert to and from whole pixels.
 *
 * The pad masks (func_001fd720): mode 0 takes both the d-pad and the left
 * stick bits, 1 the d-pad only, 2 the stick only (up / down / left / right
 * in D_00640DE4 ... D_00640DF0, D_00640DF4 and the union D_00640DF8).
 * Then the cursor movers: on a window (func_001fdfd0, wrapping, with the
 * pad's repeat x10 and trigger x8), the smooth scroll (func_001fe1b8: a
 * quarter cell per frame at speed D_002BBDFC), the row highlight fade +0xdc,
 * the confirm (func_001fe5a0: button 0x2000, waiting for the high word of
 * +0xd0 to clear) and six movers of a menu's own cursor array (MenuCur, not
 * a window): up / down, left / right and either, with or without wrap. */
#include "common.h"
#include "text/textwin.h"
#include "data/pieces/D_00425BC8.h"
#include "data/pieces/D_002BBDFC.h"

/* A menu that keeps its cursors in an s32 array at +0x24 (not a window). */
typedef struct {
    u8 pad0[0x24];
    s32 cur[1];
} MenuCur;

extern s32 D_00640DE0;
extern s32 D_00640DE4;
extern s32 D_00640DE8;
extern s32 D_00640DEC;
extern s32 D_00640DF0;
extern s32 D_00640DF4;
extern s32 D_00640DF8;

void func_0011d768(s32);
void func_001fd5e0(TextWin *w, s32 n);
void func_001fd610(TextWin *w, s32 v);
void func_001fd660(TextWin *w, s32 v);
s32 func_001fd538(TextWin *w);
void func_001fd720(s32 m);
void func_001fd858(TextWin *w);
void func_001fdfd0(TextWin *w);
s32 func_001fe1b8(s32 a);
s32 func_001fe5a0(TextWin *w);

s32 func_001fd248(TextWin *w) {
    return (s32)(w->xb0 - 0x7000) >> 4;
}

void func_001fd258(TextWin *w, s32 v) {
    w->xb0 = (s32)((v * 0x10) + 0x7000);
}

s32 func_001fd268(TextWin *w) {
    return (s32)(w->xb4 - 0x7000) >> 4;
}

void func_001fd278(TextWin *w, s32 v) {
    w->xb4 = (s32)((v * 0x10) + 0x7000);
}

s32 func_001fd288(TextWin *w) {
    return (s32)((u16)w->xb8 << 0x10) >> 0x14;
}

void func_001fd298(TextWin *w, s32 v) {
    w->xb8 = (s16)(v * 0x10);
}

s32 func_001fd2a8(TextWin *w) {
    return (s32)((u16)w->xba << 0x10) >> 0x14;
}

void func_001fd2b8(TextWin *w, s32 v) {
    w->xba = (s16)(v * 0x10);
}

s32 func_001fd2c8(TextWin *w) {
    return (s32)((u16)w->xbe << 0x10) >> 0x14;
}

void func_001fd2d8(TextWin *w, s32 v) {
    w->xbe = (s16)(v * 0x10);
}

s32 func_001fd2e8(TextWin *w) {
    return (s32)((u16)w->xc0 << 0x10) >> 0x14;
}

void func_001fd2f8(TextWin *w, s32 v) {
    w->xc0 = (s16)(v * 0x10);
}

s32 func_001fd308(TextWin *w) {
    return (s32)((u16)w->xc2 << 0x10) >> 0x14;
}

void func_001fd318(TextWin *w, s32 v) {
    w->xc2 = (s16)(v * 0x10);
}

s32 func_001fd328(TextWin *w) {
    return (s32)((u16)w->xc4 << 0x10) >> 0x14;
}

void func_001fd338(TextWin *w, s32 v) {
    w->xc4 = (s16)(v * 0x10);
}

s32 func_001fd348(TextWin *w) {
    return (s32)((u16)w->xc6 << 0x10) >> 0x14;
}

void func_001fd358(TextWin *w, s32 v) {
    w->xc6 = (s16)(v * 0x10);
}

s32 func_001fd368(TextWin *w) {
    return (s32)((u16)w->xc8 << 0x10) >> 0x14;
}

void func_001fd378(TextWin *w, s32 v) {
    w->xc8 = (s16)(v * 0x10);
}

void func_001fd388(TextWin *w, s32 a, s32 b, s32 c, s32 d, s32 e, s32 f) {
    w->xbe = (s16)(a * 0x10);
    w->xc0 = (s16)(b * 0x10);
    w->xc2 = (s16)(c * 0x10);
    w->xc4 = (s16)(d * 0x10);
    w->xc6 = (s16)(e * 0x10);
    w->xc8 = (s16)(f * 0x10);
}

void func_001fd3c0(TextWin *w, s32 a, s32 b, s32 c, s32 d, s32 e) {
    w->xbe = (s16)(a * 0x10);
    w->xc0 = (s16)(b * 0x10);
    w->xc2 = (s16)(c * 0x10);
    w->xc4 = (s16)(d * 0x10);
    w->xc6 = (s16)(e * 0x10);
}

void func_001fd3f0(TextWin *w, s32 a, s32 b, s32 c, s32 d, s32 e) {
    w->xbe = (s16)(a * 0x10);
    w->xc0 = (s16)(b * 0x10);
    w->xc2 = (s16)(c * 0x10);
    w->xc4 = (s16)(d * 0x10);
    w->xc8 = (s16)(e * 0x10);
}

/* Items n, columns cols, and +0xce. */
void func_001fd420(TextWin *w, s32 n, s32 cols, s32 v) {
    func_001fd660(w, cols);
    func_001fd610(w, v);
    func_001fd5e0(w, n);
}

void func_001fd478(TextWin *w, s32 n, s32 cols) {
    func_001fd660(w, cols);
    func_001fd610(w, 1);
    func_001fd5e0(w, n);
}

void func_001fd4c0(TextWin *w, s32 n, s32 v) {
    func_001fd660(w, 1);
    func_001fd5e0(w, n);
    func_001fd610(w, v);
}

s32 func_001fd518(TextWin *w) {
    return (s32)(w->ud0.s.xd2 + (w->ud0.u.xd0 & 0xF) + 8) >> 4;
}

s32 func_001fd538(TextWin *w) {
    return (s32)(w->xda + 8) >> 4;
}

/* The item under the cursor: row (scroll + cursor) times columns, plus the
 * column. */
s32 func_001fd548(TextWin *w) {
    return (((s32)(w->ud0.s.xd2 + w->ud0.s.xd0 + 8) >> 4) * w->xd8) + func_001fd538(w);
}

s32 func_001fd590(TextWin *w) {
    return (w->xc0 >> 4) - (w->xc4 >> 4) * (w->ud0.s.xd0 & 0xf) / 16;
}

s16 func_001fd5d0(TextWin *w) {
    return w->xca;
}

s16 func_001fd5d8(TextWin *w) {
    return w->xcc;
}

void func_001fd5e0(TextWin *w, s32 n) {
    s16 cols;

    cols = w->xd8;
    w->xcc = (s16)((s32)((n + cols) - 1) / cols);
    w->xca = (s16)n;
}

s16 func_001fd608(TextWin *w) {
    return w->xce;
}

void func_001fd610(TextWin *w, s32 v) {
    w->xce = v;
}

s32 func_001fd618(TextWin *w) {
    return (s32)((u16)w->ud0.s.xd0 << 0x10) >> 0x14;
}

void func_001fd628(TextWin *w, s32 v) {
    w->ud0.s.xd0 = (s16)(v * 0x10);
}

s32 func_001fd638(TextWin *w) {
    return (s32)(w->ud0.s.xd2 + 8) >> 4;
}

void func_001fd648(TextWin *w, s32 v) {
    w->ud0.s.xd2 = (s16)(v * 0x10);
}

s16 func_001fd658(TextWin *w) {
    return w->xd8;
}

void func_001fd660(TextWin *w, s32 v) {
    w->xd8 = v;
}

s32 func_001fd668(TextWin *w) {
    return (s32)(w->xda + 8) >> 4;
}

void func_001fd678(TextWin *w, s32 v) {
    w->xda = (s16)(v * 0x10);
}

/* Keeps the scroll and the cursor inside the item count. */
void func_001fd688(TextWin *w) {
    s32 a = w->xcc;
    s32 d;
    if (a == 0) return;
    d = (a - w->xce) << 4;
    if (d <= 0) {
        a = (a - 1) << 4;
        w->ud0.s.xd0 = 0;
        w->ud0.s.xd6 = 0;
        if (a < w->ud0.s.xd2) {
            w->ud0.s.xd2 = a;
            w->ud0.s.xd4 = 0;
        }
    } else if (d < w->ud0.s.xd0) {
        w->ud0.s.xd0 = d;
        w->ud0.s.xd6 = 0;
    }
}

s32 func_001fd6f0(TextWin *w) {
    s32 a = w->xcc;
    s32 b = w->xce;
    return a < b ? a : b;
}

void func_001fd708(void) {
    func_001fd720(0);
}

void func_001fd720(s32 m) {
    switch (m) {
    case 0:
        D_00640DE0 = m;
        D_00640DE4 = 0x10000010;
        D_00640DE8 = 0x40000040;
        D_00640DEC = 0x50000050;
        D_00640DF0 = 0x80000080;
        D_00640DF4 = 0x20000020;
        D_00640DF8 = 0xA00000A0;
        break;
    case 1:
        D_00640DE0 = m;
        D_00640DE4 = 0x10;
        D_00640DE8 = 0x40;
        D_00640DEC = 0x50;
        D_00640DF0 = 0x80;
        D_00640DF4 = 0x20;
        D_00640DF8 = 0xA0;
        break;
    case 2:
        D_00640DE0 = m;
        D_00640DE4 = 0x10000000;
        D_00640DE8 = 0x40000000;
        D_00640DEC = 0x50000000;
        D_00640DF0 = 0x80000000;
        D_00640DF4 = 0x20000000;
        D_00640DF8 = 0xA0000000;
        break;
    }
}

s32 func_001fd848(void) {
    return D_00640DE0;
}

/* func_001fd858 (the cursor input) is not matched yet. */

/* Left / right on the column cursor +0xda, wrapping. */
void func_001fdfd0(TextWin *w) {
    s32 n = w->xd8;
    s32 moved;
    s32 k, r;
    PadSt_425bc8 *pd;
    u32 m;
    if (n < 2) {
        w->xda = 0;
        return;
    }
    if ((w->xda >> 4) >= n) w->xda = (n - 1) << 4;
    pd = D_00425BC8;
    m = pd->x10 & D_00640DF8;
    moved = 0;
    if (m & D_00640DF0) {
        if (w->xda > 0) {
            w->xda -= 16;
            moved = 1;
        } else if (pd->x8 & D_00640DF0) {
            moved = 1;
            w->xda = (n - 1) << 4;
        }
    } else if (m & D_00640DF4) {
        if (w->xda < (n - 1) << 4) {
            w->xda += 16;
            moved = 1;
        } else if (pd->x8 & D_00640DF4) {
            w->xda = 0;
            moved = 1;
        }
    }
    k = w->xca;
    if (w->ud0.s.xd0 + w->ud0.s.xd2 >= (k + n - 1) / n * 16 - 24) {
        r = k % n;
        if (r != 0 && (w->xda >> 4) >= r) {
            w->xda = 0;
            moved = 0;
        }
    }
    if (moved) func_0011d768(1);
}

void func_001fe158(TextWin *w) {
    func_001fd858(w);
    func_001fdfd0(w);
}

void func_001fe180(TextWin *w) {
    if (func_001fe1b8((s32)w) != 0) {
        func_0011d768(1);
    }
}

/* The window comes as an s32: the dead set of a below is the lever. */
s32 func_001fe1b8(s32 a) {
    s32 t, f, g, u;
    s32 b;
    s32 r = 0;
    TextWin *o = (TextWin *)a;
    /* s11w33 (flagged): dead one-path set `if (a <= 0) a = 0;` (s11w22 lever).
     * The test reads a after `o = a`, so combine cannot fold the param copy
     * into `o = a0`; the set of a on one path stops gcse CPROP from rewriting
     * the first load through a. Life1 deletes the dead set, then the empty
     * test goes too. */
    if (a <= 0) a = 0;
    a = o->ud0.u.xd2;
    b = a << 16;
    if (o->ud0.s.xd4 < 0) {
        t = (s16)(a & 0xfff0);
        f = a & 0xf;
        if (f) {
            o->ud0.u.xd2 = (s32)((b >> 16) - D_002BBDFC * 4.0f);
            if ((s16)o->ud0.u.xd2 <= 0) {
                o->ud0.u.xd2 = 0;
            } else if (t < (s16)o->ud0.u.xd2) {
                goto next;
            } else {
                o->ud0.u.xd2 = t;
            }
        }
        o->ud0.s.xd4 = 0;
    } else if (o->ud0.s.xd4 > 0) {
        t = (s16)(a & ~0xf) + 16;
        f = a & 0xf;
        a = (o->xce - 1) << 4;
        if (f) {
            o->ud0.u.xd2 = (s32)((b >> 16) + D_002BBDFC * 4.0f);
            if ((s16)o->ud0.u.xd2 >= a) {
                o->ud0.u.xd2 = a;
            } else if ((s16)o->ud0.u.xd2 < t) {
                goto next;
            } else {
                o->ud0.u.xd2 = t;
            }
            r = 1;
        }
        o->ud0.s.xd4 = 0;
    }
next:
    if (o->ud0.s.xd6 < 0) {
        a = o->ud0.u.xd0;
        u = (s16)(a & 0xfff0);
        g = a & 0xf;
        if (g) {
            o->ud0.u.xd0 = (s32)((s16)a - D_002BBDFC * 4.0f);
            if ((s16)o->ud0.u.xd0 <= 0) {
                o->ud0.u.xd0 = 0;
                o->ud0.s.xd6 = 0;
                goto end;
            }
            if (u < (s16)o->ud0.u.xd0) goto end;
            o->ud0.u.xd0 = u;
        }
        o->ud0.s.xd6 = 0;
    } else if (o->ud0.s.xd6 > 0) {
        b = o->ud0.u.xd0;
        u = (s16)(b & 0xfff0) + 16;
        a = (o->xcc - o->xce) << 4;
        g = b & 0xf;
        if (g) {
            o->ud0.u.xd0 = (s32)((s16)b + D_002BBDFC * 4.0f);
            if ((s16)o->ud0.u.xd0 >= a) {
                o->ud0.u.xd0 = a;
            } else if ((s16)o->ud0.u.xd0 < u) {
                goto end;
            } else {
                o->ud0.u.xd0 = u;
            }
            r = 1;
        }
        o->ud0.s.xd6 = 0;
    }
end:
    a = r;
    return a;
}

/* The row highlight: the cursor's row at 0x80, the others fade to 64. */
void func_001fe408(TextWin *o) {
    s32 i;
    s32 n1 = o->xce + 1;
    s32 cnt = (o->ud0.s.xd0 & 0xf) ? n1 : o->xce;
    s32 k = (o->ud0.s.xd0 >> 4) % n1;
    s32 sel = o->ud0.s.xd2 >> 4;
    for (i = 0; i < cnt; i++) {
        u8 *p = &o->xdc[k];
        if (i == sel) {
            *p = 0x80;
        } else {
            s32 d = D_002BBDFC * 4.0f;
            if (d + 64 >= *p) *p = 64;
            else *p -= d;
        }
        k = (k + 1) % n1;
    }
}

void func_001fe4e0(TextWin *o) {
    s32 i;
    s32 n1 = o->xce + 1;
    s32 cnt = (o->ud0.s.xd0 & 0xf) ? n1 : o->xce;
    s32 k = (o->ud0.s.xd0 >> 4) % n1;
    for (i = 0; i < cnt; i++) {
        o->xdc[k] = 64;
        k = (k + 1) % n1;
    }
}

/* Still scrolling (the cursor or its step). */
s32 func_001fe558(TextWin *o) {
    return (o->ud0.q & 0xffffffff00000000) != 0;
}

s32 func_001fe570(TextWin *w) {
    s32 r;

    r = func_001fe5a0(w);
    if (r != 0) {
        func_0011d768(2);
        r = 1;
    }
    return r;
}

s32 func_001fe5a0(TextWin *o) {
    switch (o->xbc) {
    case 0:
        if (D_00425BC8->x8 & 0x2000) {
            if (func_001fe558(o)) o->xbc++;
            else o->xbc = 2;
        }
        break;
    case 1:
        if (!func_001fe558(o)) o->xbc++;
        break;
    case 2:
        break;
    }
    if (o->xbc == 2) { o->xbc = 0; return 1; }
    return 0;
}

/* Up / down on m->cur[i] of n, wrapping on a new press. */
s32 func_001fe660(MenuCur *m, s32 i, s32 n) {
    s32 r = 0;
    if (D_00425BC8->x10 & 0x10000010) {
        if (m->cur[i] > 0) {
            m->cur[i]--;
            r = 1;
        } else if (D_00425BC8->x8 & 0x10000010) {
            m->cur[i] = n - 1;
            r = 1;
        }
    } else if (D_00425BC8->x10 & 0x40000040) {
        if (m->cur[i] < n - 1) {
            m->cur[i]++;
            r = 1;
        } else if (D_00425BC8->x8 & 0x40000040) {
            m->cur[i] = 0;
            r = 1;
        }
    }
    return r;
}

/* Up / down without wrap. */
s32 func_001fe718(MenuCur *m, s32 i, s32 n) {
    s32 r = 0;
    u32 f = D_00425BC8->x10;
    if (f & 0x10000010) {
        if (m->cur[i] > 0) {
            m->cur[i]--;
            r = 1;
        }
    } else if (f & 0x40000040) {
        if (m->cur[i] < n - 1) {
            m->cur[i]++;
            r = 1;
        }
    }
    return r;
}

/* Left / right, wrapping. */
s32 func_001fe7a8(MenuCur *m, s32 i, s32 n) {
    s32 r = 0;
    if (D_00425BC8->x10 & 0x80000080) {
        if (m->cur[i] > 0) {
            m->cur[i]--;
            r = 1;
        } else if (D_00425BC8->x8 & 0x80000080) {
            m->cur[i] = n - 1;
            r = 1;
        }
    } else if (D_00425BC8->x10 & 0x20000020) {
        if (m->cur[i] < n - 1) {
            m->cur[i]++;
            r = 1;
        } else if (D_00425BC8->x8 & 0x20000020) {
            m->cur[i] = 0;
            r = 1;
        }
    }
    return r;
}

s32 func_001fe860(MenuCur *m, s32 i, s32 n) {
    s32 r = 0;
    u32 f = D_00425BC8->x10;
    if (f & 0x80000080) {
        if (m->cur[i] > 0) {
            m->cur[i]--;
            r = 1;
        }
    } else if (f & 0x20000020) {
        if (m->cur[i] < n - 1) {
            m->cur[i]++;
            r = 1;
        }
    }
    return r;
}

/* Left / right or the shoulder buttons (0x400 / 0x800), wrapping. */
s32 func_001fe8f0(MenuCur *m, s32 i, s32 n) {
    s32 r = 0;
    if (D_00425BC8->x10 & 0x80000480) {
        if (m->cur[i] > 0) {
            m->cur[i]--;
            r = 1;
        } else if (D_00425BC8->x8 & 0x80000480) {
            m->cur[i] = n - 1;
            r = 1;
        }
    } else if (D_00425BC8->x10 & 0x20000820) {
        if (m->cur[i] < n - 1) {
            m->cur[i]++;
            r = 1;
        } else if (D_00425BC8->x8 & 0x20000820) {
            m->cur[i] = 0;
            r = 1;
        }
    }
    return r;
}

s32 func_001fe9a8(MenuCur *m, s32 i, s32 n) {
    s32 r = 0;
    u32 f = D_00425BC8->x10;
    if (f & 0x80000480) {
        if (m->cur[i] > 0) {
            m->cur[i]--;
            r = 1;
        }
    } else if (f & 0x20000820) {
        if (m->cur[i] < n - 1) {
            m->cur[i]++;
            r = 1;
        }
    }
    return r;
}

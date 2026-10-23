/* The text windows (docs/modules.md "Session 37"), 0x001f3110-0x001f4570:
 * opening, closing, the open / focus / chain lists and their queries.  The
 * slots, lists and states are described in include/text/textwin.h.
 * func_001f3110 empties every slot and resets the text colour
 * (D_003F1A60) and width (D_003F1A64). */
#include "common.h"
#include "text/textwin.h"
#include "data/pieces/D_00490AE0.h"

extern TextWin D_0063F758[24]; /* src/data/bss_0063.c: Obj D_0063F758[24] */
extern TextWin *D_00640DD8; /* src/data/bss_0064.c: s32 D_00640DD8 */
extern TextWin *D_00640DDC; /* src/data/bss_0064.c: s32 D_00640DDC */
extern s32 D_003F1A60, D_003F1A64;
extern s32 D_003F1A68;
extern TextWinDesc D_003E9630;

void func_001efb78(s32);
void func_001efb98(s32);
s32 func_002366d8(s32, s32);
void func_001fd708(void);

TextWin *func_001f31a8(TextWinDesc *a, s32 b);
TextWin *func_001f3520(TextWinDesc *a, s32 b);
void func_001f3680(TextWin *);
void func_001f3698(TextWin *, s32);
void func_001f3dc0(TextWin *);
s32 func_001f4378(TextWin *);
s32 func_001f4390(TextWin *);
s32 func_001f43c8(TextWin *);
s32 func_001f4400(TextWin *);

void func_001f3110(void) {
    s32 i;
    TextWin *p = D_0063F758;
    for (i = 24; i > 0; i--, p++) p->state = 0;
    D_00640DD8 = 0;
    D_00640DDC = 0;
    D_003F1A60 = 0x80e6e6e6;
    D_003F1A64 = 320;
    func_001efb78(0);
    func_001efb98(0);
    func_001fd708();
}

TextWin *func_001f3190(TextWinDesc *a) {
    return func_001f31a8(a, 6);
}

TextWin *func_001f31a8(TextWinDesc *a, s32 b) {
    s32 i;
    TextWin *p;
    s32 v;
    s32 j;

    if (a->x8 & 0xc) {
        p = D_0063F758;
        for (i = 0; i < 24; i++, p++) {
            switch (p->state) {
            case 0:
                break;
            case 1:
            case 2:
            case 3:
                if (p->desc == a) {
                    if (a->x8 & 8) return 0;
                    if (!((s32)p->u40.a.hi & 1)) return 0;
                }
                break;
            case 4:
            case 5:
                if (p->desc == a) {
                    if (a->x8 & 8) return 0;
                }
                break;
            }
        }
    }
    p = D_0063F758;
    for (i = 0; i < 24; i++, p++) {
        if (p->state != 0) continue;

        p->x4 = a->x0;
        p->x8 = a->x4;
        p->u40.a.lo = 0;
        p->u40.b.b0 = 0;
        p->c0 = 0;
        p->x0 = 0;
        p->prev = 0;
        p->x64 = D_00490AE0;
        p->next = 0;
        p->x6c = 0x60000000;
        p->x1c = 0;
        p->x20 = 0;
        p->x24 = 0;
        p->x28 = 0;
        p->x2c = 0;
        p->x30 = 0;
        p->x34 = 0;
        p->x38 = 0;
        p->x3c = 0;
        p->x50 = 0;
        p->desc = a;
        p->x68 = 0;
        p->x70 = 1;
        p->x74 = 1.0f;
        p->x78 = 1.0f;
        p->x7c = 0;
        if (b == -1) v = func_002366d8(4, 54) + 1; else v = b;
        p->x80 = v;
        p->x84 = v;
        p->x88 = a->x8;
        p->x90 = 128;
        p->state = 1;
        p->x94 = 0;
        p->xb0 = a->xc * 16 + 0x7000;
        p->xb4 = a->xe * 16 + 0x7400;
        p->x98 = 0;
        p->xb8 = a->x10 << 4;
        p->xba = a->x12 << 4;
        p->xbc = 0;
        p->x9c = 0;
        p->xbe = a->x14 << 4;
        p->xc0 = a->x16 << 4;
        p->xa0 = 0;
        p->xa4 = 0;
        p->xc2 = a->x18 << 4;
        p->xa8 = 0;
        p->xc4 = a->x1a << 4;
        p->xc6 = 0;
        p->xac = 0;
        p->xc8 = a->x1c << 4;
        p->xca = a->x1e;
        p->xcc = a->x1e;
        p->xce = a->x20;
        p->xd8 = 1;
        p->xd0 = 0;
        p->xd2 = 0;
        p->xd4 = 0;
        p->xd6 = 0;
        p->xda = 0;

        for (j = 0; j < 16; j++) p->xdc[j] = 64;
        if (D_00640DD8) {
            D_00640DD8->x14 = p;
            p->x18 = D_00640DD8;
        } else {
            p->x18 = 0;
        }
        p->x14 = 0;
        D_00640DD8 = p;
        func_001f3dc0(p);
        return p;
    }
    return 0;
}

TextWin *func_001f34d0(TextWinDesc *a) {
    return func_001f31a8(a, func_002366d8(4, 54) + 1);
}

TextWin *func_001f3508(TextWinDesc *a) {
    return func_001f3520(a, 6);
}

TextWin *func_001f3520(TextWinDesc *a, s32 b) {
    TextWin *w;

    w = func_001f31a8(a, b);
    if (w != 0) {
        w->xc6 = (s16)(a->x22 * 16);
        w->xd8 = (u16)a->x24;
        w->xca = (u16)a->x28;
    }
    return w;
}

TextWin *func_001f3570(TextWinDesc *a) {
    return func_001f3520(a, func_002366d8(4, 54) + 1);
}

TextWin *func_001f35a8(s32 flags, s32 fn) {
    D_003E9630.x0 = fn;
    D_003E9630.x8 = flags;
    return func_001f31a8(&D_003E9630, 6);
}

TextWin *func_001f35d8(s32 flags, s32 fn, s32 b) {
    D_003E9630.x0 = fn;
    D_003E9630.x8 = flags;
    return func_001f31a8(&D_003E9630, b);
}

TextWin *func_001f3608(s32 flags, s32 fn) {
    D_003E9630.x0 = fn;
    D_003E9630.x8 = flags;
    return func_001f31a8(&D_003E9630, func_002366d8(4, 54) + 1);
}

/* Free a window: state 4, out of its chain. */
void func_001f3648(TextWin *w) {
    TextWin *p = w->prev;
    w->state = 4;
    if (p != 0) p->next = w->next;
    p = w->next;
    if (p != 0) p->prev = w->prev;
}

void func_001f3680(TextWin *w) {
    *(s64 *)&w->u40 |= (s64)0x8000 << 17;
}

void func_001f3698(TextWin *w, s32 n) {
    w->x84 = n;
    *(s64 *)&w->u40 |= (s64)0x8000 << 17;
}

s32 func_001f36b8(TextWin *p) {
    if (!p) return -1;
    switch (p->state) {
    case 0: return 0;
    case 4: case 5: break;
    default: func_001f3680(p);
    }
    return 0;
}

s32 func_001f3708(TextWin *p, s32 a) {
    if (!p) return -1;
    switch (p->state) {
    case 0: return 0;
    case 4: case 5: break;
    default: func_001f3698(p, a);
    }
    return 0;
}

s32 func_001f3758(TextWin *p) {
    if (!p) return -1;
    for (; p; p = p->next) {
        switch (p->state) {
        case 0: break;
        case 4: case 5: break;
        default: func_001f3680(p);
        }
    }
    return 0;
}

s32 func_001f37c0(TextWin *p, s32 a) {
    if (!p) return -1;
    for (; p; p = p->next) {
        switch (p->state) {
        case 0: break;
        case 4: case 5: break;
        default: func_001f3698(p, a);
        }
    }
    return 0;
}

s32 func_001f3840(TextWin *p) {
    if (!p) return -1;
    while (p->prev) p = p->prev;
    do {
        switch (p->state) {
        case 0: break;
        case 4: case 5: break;
        default: func_001f3680(p);
        }
        p = p->next;
    } while (p);
    return 0;
}

s32 func_001f38d0(TextWin *w, s32 n) {
    s32 s;
    s32 r;
    TextWin *t;
    TextWin *p;
    TextWin *q;

    r = -1;
    p = w;
    if (p != 0) {
        q = p->prev;
        if (q != 0) {
            do {
                p = q;
                t = p->prev;
                q = t;
            } while (t != 0);
        }
        do {
            s = p->state;
            if (s != 0) {
                if (s >= 0) {
                    if (s < 6) {
                        if (s < 4) {
                            goto close;
                        }
                    } else {
                        goto close;
                    }
                } else {
close:
                    func_001f3698(p, n);
                }
            }
            p = p->next;
        } while (p != 0);
        r = 0;
    }
    return r;
}

s32 func_001f3978(TextWin *n, s32 skip, s32 cnt) {
    s32 i;
    if (n == 0) return -1;
    for (i = 0; i < skip && n->prev; i++) n = n->prev;
    i = i + cnt + 1;
    do {
        if (i <= 0) return 0;
        switch (n->state) {
        case 0:
        case 4:
        case 5:
            break;
        default:
            func_001f3680(n);
            break;
        }
        n = n->next;
        i--;
    } while (n);
    return 0;
}

s32 func_001f3a30(TextWin *n, s32 skip, s32 cnt, s32 arg) {
    s32 i;
    if (n == 0) return -1;
    for (i = 0; i < skip && n->prev; i++) n = n->prev;
    i = i + cnt + 1;
    do {
        if (i <= 0) return 0;
        switch (n->state) {
        case 0:
        case 4:
        case 5:
            break;
        default:
            func_001f3698(n, arg);
            break;
        }
        n = n->next;
        i--;
    } while (n);
    return 0;
}

void func_001f3b00(s32 a) {
    s32 i;
    TextWin *p = D_0063F758;
    for (i = 24; i > 0; i--, p++) {
        switch (p->state) {
        case 0: break;
        case 4: case 5: break;
        default:
            if (p->x7c == a) func_001f3680(p);
        }
    }
}

void func_001f3b88(s32 a, s32 b) {
    s32 i;
    TextWin *p = D_0063F758;
    for (i = 24; i > 0; i--, p++) {
        switch (p->state) {
        case 0: break;
        case 4: case 5: break;
        default:
            if (p->x7c == a) func_001f3698(p, b);
        }
    }
}

void func_001f3c20(void) {
    s32 i;
    TextWin *p = D_0063F758;
    for (i = 24; i > 0; i--, p++) {
        switch (p->state) {
        case 0: break;
        case 4: case 5: break;
        default: func_001f3680(p);
        }
    }
}

void func_001f3c90(s32 n) {
    TextWin *p;
    s32 s;
    s32 i;

    p = D_0063F758;
    i = 24;
    do {
        s = p->state;
        if (s != 0) {
            if (s >= 0) {
                if (s < 6) {
                    if (s < 4) {
                        goto close;
                    }
                } else {
                    goto close;
                }
            } else {
close:
                func_001f3698(p, n);
            }
        }
        i -= 1;
        p++;
    } while (i > 0);
}

/* 1 if the window is closing or asked to close. */
s32 func_001f3d10(TextWin *w) {
    if ((w != 0) && (((u32)(w->state - 4) < 2U) || ((s32)((u64)((s64)w->u40.v.x44 << 0x20) >> 0x20) & 1))) {
        return 1;
    }
    return 0;
}

void func_001f3d58(TextWin *w, s32 n) {
    w->x84 = n;
}

void func_001f3d60(TextWin *w) {
    w->x84 = w->x80;
}

/* Move a window to the head of the open list. */
void func_001f3d70(TextWin *p) {
    TextWin **h;
    TextWin *t;
    if (!p->x14) return;
    p->x14->x18 = p->x18;
    if (p->x18) p->x18->x14 = p->x14;
    p->x14 = 0;
    h = &D_00640DD8;
    t = *h;
    p->x18 = t;
    t->x14 = p;
    *h = p;
}

/* Give a window the focus (head of the focus list). */
void func_001f3dc0(TextWin *p) {
    TextWin **h = &D_00640DDC;
    TextWin *t = *h;
    if (t && t != p) {
        if (p->x1c) p->x1c->x20 = p->x20;
        if (p->x20) p->x20->x1c = p->x1c;
        t = *h;
        p->x1c = 0;
        p->x20 = t;
        t->x1c = p;
    }
    D_00640DDC = p;
}

void func_001f3e20(TextWin *w, TextWin *p) {
    w->prev = p;
}

void func_001f3e28(TextWin *w) {
    TextWin *p = w->prev;
    if (p != 0) {
        p->next = 0;
        w->prev = 0;
    }
}

/* Unlink w and put it after p. */
void func_001f3e48(TextWin *w, TextWin *p) {
    TextWin *t;
    TextWin *q;

    q = w->prev;
    if (q != 0) q->next = w->next;
    q = w->next;
    if (q != 0) q->prev = w->prev;
    t = p->next;
    p->next = w;
    w->prev = p;
    w->next = t;
    if (t != 0) t->prev = w;
}

void func_001f3e90(TextWin *w, TextWin *n) {
    w->next = n;
}

void func_001f3e98(TextWin *w) {
    TextWin *n = w->next;
    if (n != 0) {
        n->prev = 0;
        w->next = 0;
    }
}

/* Unlink w and put it before p. */
void func_001f3eb8(TextWin *w, TextWin *p) {
    TextWin *t;
    TextWin *q;

    q = w->prev;
    if (q != 0) q->next = w->next;
    q = w->next;
    if (q != 0) q->prev = w->prev;
    t = p->prev;
    p->prev = w;
    w->next = p;
    w->prev = t;
    if (t != 0) t->next = w;
}

/* Append w after the last window of p's chain. */
void func_001f3f00(TextWin *w, TextWin *p) {
    TextWin *t;
    TextWin *q;

    q = p->next;
    if (q != 0) {
        do {
            p = q;
            t = p->next;
            q = t;
        } while (t != 0);
    }
    t = w->prev;
    if (t != 0) t->next = 0;
    p->next = w;
    w->prev = p;
}

/* Join chain b after chain a. */
void func_001f3f48(TextWin *a, TextWin *b) {
    while (a->next) a = a->next;
    while (b->prev) b = b->prev;
    a->next = b;
    b->prev = a;
}

void func_001f3fa8(TextWin *w) {
    TextWin *p = w->prev;
    TextWin *n = w->next;
    if (p != 0) p->next = n;
    if (n != 0) n->prev = p;
}

/* Swap two windows' places in their chains. */
void func_001f3fc8(TextWin *a, TextWin *b) {
    TextWin *ap = a->prev;
    TextWin *an = a->next;
    TextWin *bp = b->prev;
    TextWin *bn = b->next;
    if (ap != 0) ap->next = b;
    if (an != 0) an->prev = b;
    if (bp != 0) bp->next = a;
    if (bn != 0) bn->prev = a;
    a->prev = bp;
    a->next = bn;
    b->prev = ap;
    b->next = an;
}

void *func_001f4010(TextWin *w) {
    void *p = w->x64;
    if (p == 0) p = D_00490AE0;
    return p;
}

void func_001f4030(TextWin *w, void *p) {
    w->x64 = p;
}

s32 func_001f4038(TextWin *w) {
    return w->x70;
}

void func_001f4040(TextWin *w, s32 n) {
    w->x70 = n;
}

void func_001f4048(s32 n) {
    D_003F1A68 = n;
}

/* func_001f4058 is in textwin.nofill.c. */

void func_001f4090(TextWin *w, void *p) {
    w->x68 = p;
}

void func_001f4098(TextWin *w) {
    w->x68 = 0;
}

void func_001f40a0(TextWin *w, s32 n) {
    w->x6c = n;
}

void func_001f40a8(TextWin *w) {
    w->x6c = 0x60000000;
}

TextWin *func_001f40b8(void) {
    return D_0063F758;
}

/* The number of open windows. */
s32 func_001f40c8(void) {
    s32 n;
    TextWin *t;
    TextWin *p;

    if (D_00640DD8 == 0) return 0;
    p = D_00640DD8->x18;
    n = 1;
    if (p != 0) {
        do {
            t = p->x18;
            n += 1;
            p = t;
        } while (t != 0);
    }
    return n;
}

s32 func_001f4110(void) {
    s32 i, n = 0;
    TextWin *p = D_0063F758;
    for (i = 0; i < 24; i++, p++) {
        if (p->state) n++;
    }
    return n;
}

s32 func_001f4148(void) {
    s32 i, n = 0;
    TextWin *p = D_0063F758;
    for (i = 0; i < 24; i++, p++) {
        if (p->state == 0) n++;
    }
    return n;
}

s32 func_001f4180(void) {
    s32 i, n = 0;
    TextWin *p = D_0063F758;
    for (i = 0; i < 24; i++, p++) {
        if (p->state == 3) n++;
    }
    return n;
}

s32 func_001f41c0(void) {
    s32 i, n = 0;
    TextWin *p = D_0063F758;
    for (i = 0; i < 24; i++, p++) {
        switch (p->state) {
        case 1:
        case 2:
            n++;
        }
    }
    return n;
}

s32 func_001f4208(void) {
    s32 i, n = 0;
    TextWin *p = D_0063F758;
    for (i = 0; i < 24; i++, p++) {
        if (p->state < 6) {
            if (p->state >= 4) n++;
        }
    }
    return n;
}

TextWin *func_001f4250(void) {
    return D_00640DD8;
}

/* The oldest open window. */
TextWin *func_001f4260(void) {
    TextWin *t;
    TextWin *q;
    TextWin *p;

    p = D_00640DD8;
    if (p != 0) {
        q = p->x18;
        if (q != 0) {
            do {
                p = q;
                t = p->x18;
                q = t;
            } while (t != 0);
        }
    }
    return p;
}

TextWin *func_001f42a8(void) {
    return D_00640DDC;
}

s32 func_001f42b8(TextWin *w) {
    if (func_001f4378(w) != 0) {
        return func_001f4390(w);
    }
    return 0;
}

s32 func_001f42f8(TextWin *w) {
    if (func_001f4378(w) != 0) {
        return func_001f43c8(w);
    }
    return 0;
}

s32 func_001f4338(TextWin *w) {
    if (func_001f4378(w) != 0) {
        return func_001f4400(w);
    }
    return 0;
}

s32 func_001f4378(TextWin *w) {
    return D_00640DD8 == w;
}

s32 func_001f4390(TextWin *o) {
    s32 s = o->state;
    if (s < 4) {
        if (s > 0) return ((s32)o->u40.a.hi & 1) ^ 1;
    }
    return 0;
}

s32 func_001f43c8(TextWin *o) {
    s32 s = o->state;
    if (s < 4) {
        if (s > 0) return ((s32)o->u40.a.hi & 1) ^ 1;
    }
    return 0;
}

s32 func_001f4400(TextWin *o) {
    if (o->state == 3) return ((s32)o->u40.a.hi & 1) ^ 1;
    return 0;
}

/* The first window of w's chain. */
TextWin *func_001f4430(TextWin *w) {
    TextWin *t;
    TextWin *p;

    p = w->prev;
    if (p != 0) {
        do {
            w = p;
            t = w->prev;
            p = t;
        } while (t != 0);
    }
    return w;
}

/* The last window of w's chain. */
TextWin *func_001f4468(TextWin *w) {
    TextWin *t;
    TextWin *p;

    p = w->next;
    if (p != 0) {
        do {
            w = p;
            t = w->next;
            p = t;
        } while (t != 0);
    }
    return w;
}

s32 func_001f44a0(TextWinDesc *desc) {
    s32 i;
    TextWin *p = D_0063F758;
    for (i = 0; i < 24; i++, p++) {
        if (p->state != 0 && p->desc == desc) return 1;
    }
    return 0;
}

s32 func_001f44e8(TextWin *o, TextWinDesc *desc) {
    if (o == 0) return 0;
    while (o->prev != 0) o = o->prev;
    do {
        if (o->state != 0 && o->desc == desc) return 1;
        o = o->next;
    } while (o != 0);
    return 0;
}

s32 func_001f4558(TextWin *w) {
    return w->x7c;
}

void func_001f4560(TextWin *w, s32 n) {
    w->x7c = n;
}

void func_001f4568(TextWin *w) {
    w->x7c = 0;
}

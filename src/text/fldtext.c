/* The field's text (a guess at the name), 0x0010c3c0-0x0010ef90: the
 * kanji font kanji.knj (func_0010c3c0 loads it, func_0010c4b0 uploads it),
 * glyph packets (func_0010c720), a printf to glyph codes (func_0010d388),
 * timed text sequences (func_0010cf38), and text objects (func_0010e4f0,
 * func_0010ea70 ...) around the unmatched layout func_0010d470. Read from the
 * code, not proved by a boot (docs/modules.md "Session 55"). */
#include "common.h"
#include "platform/gs.h"
#include "data/bss_0049.h"
#include "data/bss_004D.h"
#include "data/types/text_00100000_h2.h"
#include "data/pieces/D_002B677C.h"
#include "data/pieces/D_002BC070.h"
#include "data/pieces/D_002B6778.h"
#include "data/types/text_00100000_h2_p.h"
#include "data/pieces/D_002B75A0.h"
#include "m2c.h"
#include "data/pieces/D_0029B280.h"
#include "data/pieces/D_002BC0A8.h"
#include "data/pieces/D_002A6238.h"
#include "data/pieces/D_002A3F48.h"
#include "data/pieces/D_002C5968.h"
#include "data/pieces/D_002BD118.h"
#include "data/pieces/D_002BCCE0.h"
#include "data/pieces/D_002B7590.h"
#include "data/pieces/D_0037A378.h"
#include "data/types/text_00100000_h28.h"
#include "data/pieces/D_002BC0C0.h"
#include "data/pieces/D_002E2780.h"
#include "data/pieces/D_002A6234.h"
#include "data/types/text_00100000_h28_p.h"
#include "data/pieces/D_002B1C60.h"
#include "data/pieces/D_002AA060.h"
#include "data/pieces/D_002A62B0.h"
#include "data/pieces/D_002A3F60.h"
#include "data/pieces/D_002A4060.h"
#include "data/pieces/D_002BC0F0.h"
#include "data/pieces/D_002A3E20.h"
#include "data/pieces/D_002A3F30.h"
#include "data/pieces/D_002A3F50.h"
#include "data/pieces/D_002A62D0.h"
#include "data/pieces/D_002BBDE4.h"
#include "data/pieces/D_002BC720.h"
#include "data/pieces/D_002BCAF0.h"
#include "data/pieces/D_002BC140.h"
#include "data/pieces/D_002BC144.h"
#include "data/pieces/D_002A6208.h"
#include "data/pieces/D_002A6C60.h"
#include "data/pieces/D_002BBAA0.h"
#include "data/pieces/D_002BBD48.h"
#include "data/pieces/D_002BBD90.h"
#include "data/pieces/D_0048C630.h"
#include "data/pieces/D_0048C690.h"
#include "data/pieces/D_002E2700.h"
#include "data/pieces/D_002E2740.h"
#include "data/pieces/D_002BBDE0.h"
#include "data/pieces/D_002A623C.h"
#include "data/pieces/D_002A6244.h"
#include "data/pieces/D_002A624C.h"
#include "data/pieces/D_002A6250.h"
#include "data/pieces/D_002A6274.h"
#include "data/pieces/D_002A62A8.h"
#include "data/pieces/D_0048CC30.h"
#include "data/pieces/D_002A3F3C.h"

/* func_0010c3c0 (from hand/text_00100000_h2.c). */
void *func_001559f0(s32, s32);
extern u8 D_0048CD50[];
extern u8 D_00495280[];
s32 func_001205f0(void *, void *);
void *memcpy(void *, const void *, u32);
void *func_0010c3c0(void) {
    void *p = func_001559f0(52, 12);
    s32 n = func_001205f0(D_0048CD50, p);
    return memcpy(D_00495280, p, n);
}

/* func_0010c410 (from auto/text_00100000.c). */
M2C_UNK func_00109230(void *, void *);
void func_0010c410(s32 arg0) {
    void *temp_a0;
    void *temp_a0_2;

    temp_a0 = arg0 + 0x10;
    temp_a0_2 = temp_a0 + M2C_FIELD(temp_a0, u16 *, 0xC);
    func_00109230(temp_a0_2, temp_a0_2 + M2C_FIELD(temp_a0, s32 *, 8));
}

/* func_0010c438 (from auto/text_00100000_3.c). */
M2C_UNK FlushCache(M2C_UNK);
extern M2C_UNK D_002BC1B0;
void func_0010c438(s16 arg0, s32 arg1) {
    PlatGsSetDefLoadImage(&D_002BC1B0, arg0, 1, 0, 0, 0, 8, 2);
    PlatGsSyncPath(0, 0);
    FlushCache(0);
    PlatGsExecLoadImage(&D_002BC1B0, arg1);
}

/* func_0010c4b0 (from hand/text_00100000_h2.c). */
#define FlushCache ((void (*)(s32)) FlushCache)
#define D_002BC1B0 (*(GsImagePacket (*)) &D_002BC1B0)
s32 func_0010c4b0(void) {
    switch (D_002BD118) {
    case 5:
    case 6:
        return 0;
    }
    PlatGsSetDefLoadImage(&D_002BC1B0, 0x3600, 4, 0, 0, 0, 256, 256);
    PlatGsSyncPath(0, 0);
    FlushCache(0);
    PlatGsExecLoadImage(&D_002BC1B0, D_00495280);
    return 0;
}
#undef FlushCache
#undef D_002BC1B0

/* func_0010c540 (from auto/text_00100000_12.c). */
M2C_UNK func_00106cd0(void *, s32);
void *func_00106ca8(s32);
void func_0010c540(s32 arg0, void **arg1) {
    s32 temp_s1;
    void *temp_v0;

    temp_s1 = (arg0 * 3) + 1;
    temp_v0 = func_00106ca8(temp_s1);
    M2C_FIELD(temp_v0, s64 *, 8) = 0x535316;
    M2C_FIELD(temp_v0, s64 *, 0) = (s64) (arg0 | 0x8000 | ((s64) 0xC800 << 0x2F));
    func_00106cd0(temp_v0, temp_s1);
    *arg1 = temp_v0 + 0x10;
}

/* func_0010c5c8 (from hand/text_00100000_h51.c). */
void func_0010c5c8(u64 *p, s32 mode, s32 psm) {
    s32 tbp;
    switch (psm) {
    case 0x11: tbp = 0x3FEC; break;
    case 0x12: tbp = 0x3FEE; break;
    case 0x13: tbp = 0x3FF0; break;
    case 0x14: tbp = 0x3FF2; break;
    default: tbp = 0x3FDC; break;
    case 0x22: tbp = 0x3FDE; break;
    case 0x23: tbp = 0x3FE0; break;
    case 0x24: tbp = 0x3FE2; break;
    case 0x31: tbp = 0x3FE4; break;
    case 0x32: tbp = 0x3FE6; break;
    case 0x33: tbp = 0x3FE8; break;
    case 0x34: tbp = 0x3FEA; break;
    }
    switch (mode) {
    case 0: *p = (u64)tbp << 37 | 0x2000000665423600; break;
    case 1: *p = (u64)(tbp + 1) << 37 | 0x2000000665423600; break;
    case 2: *p = (u64)tbp << 37 | 0x2000000665423800; break;
    case 3: *p = (u64)(tbp + 1) << 37 | 0x2000000665423800; break;
    }
}

/* func_0010c720 (from hand/text_00100000_s9_w6.c). */
extern u16 D_002BB5C0[];
extern u8 D_002C4C20[];
static inline u64 xyz(s32 x, s32 y) {
    x = x * 16 + 0x7000;
    y = y * 16 + 0x7400;
    return (u64)x | ((u64)y << 16) | 0xFFFFFFFE00000000;
}
static inline u64 xyz8(s32 x, s32 y) {
    x = x * 16 + 0x7008;
    y = y * 16 + 0x7408;
    return (u64)x | ((u64)y << 16) | 0xFFFFFFFE00000000;
}
static inline u64 uv(s32 x, s32 y) {
    x = x * 16 + 8;
    y = y * 16 + 8;
    return (u64)x | ((u64)y << 16);
}
void func_0010c720(s32 x, s32 y, s32 id, u64 **pp, s32 arg4, s32 a, s32 w) {
    u64 *p;
    s32 row = 0, col = 0;
    s32 k, off, page;

    p = *pp;
    p[1] = ((u64)a << 24) | 0x100808080ULL;
    if (id >= 10000) {
        k = id - 10000;
        p[0] = 0x2007FE85E1B11800ULL;
        p[2] = D_002BB5C0[k * 4 + 0] | ((u64)D_002BB5C0[k * 4 + 1] << 16);
        p[4] = D_002BB5C0[k * 4 + 2] | ((u64)D_002BB5C0[k * 4 + 3] << 16);
        switch (k) {
        case 4:
            off = (w == 20) ? -6 : -4;
            p[3] = xyz(x, y + off);
            p[5] = xyz(x + 0x28, y + off + 0x20);
            break;
        case 5:
            off = (w == 20) ? -10 : -8;
            p[3] = xyz(x, y + off);
            p[5] = xyz(x + 0x28, y + off + 0x28);
            break;
        case 6:
        case 7:
        case 8:
        case 9:
            func_0010c410(D_002C4C20);
            p[0] = 0x20078005DD413A00ULL;
            off = (w == 20) ? -2 : 0;
            p[2] = D_002BB5C0[k * 4 + 0] | ((u64)D_002BB5C0[k * 4 + 1] << 16);
            p[4] = D_002BB5C0[k * 4 + 2] | ((u64)D_002BB5C0[k * 4 + 3] << 16);
            p[3] = xyz8(x, y + off);
            p[5] = xyz8(x + 0x20, y + off + 0x15);
            break;
        default:
            off = (w == 20) ? -2 : 0;
            p[3] = xyz(x, y + off);
            p[5] = xyz(x + 0x18, y + off + 0x18);
            break;
        }
        *pp = p + 6;
        return;
    } else {
        page = id / 441;
        switch (page) {
        case 0:
            k = id;
            col = k % 21;
            row = k / 21;
            break;
        case 1:
            k = id - 441;
            col = k % 21;
            row = k / 21;
            break;
        case 2:
            k = id - 882;
            col = k % 21;
            row = k / 21;
            break;
        case 3:
            k = id - 1323;
            col = k % 21;
            row = k / 21;
            break;
        }
        func_0010c5c8(p, page, arg4);
        if (id == 9999) {
            p[2] = 0;
            p[4] = 0;
            p[3] = 0xFFFFFFFE73C06FC0ULL;
            p[5] = 0xFFFFFFFE73C06FC0ULL;
        } else {
            p[2] = uv(col * 24, row * 24);
            p[4] = uv(col * 24 + 24, row * 24 + 24);
            p[3] = xyz(x, y);
            p[5] = xyz(x + w, y + w);
        }
    }
    *pp = p + 6;
}

/* func_0010cb80 (from hand/text_00100000_h28.c). */
typedef struct { u16 code; u16 v; u16 x; u16 y; u16 lw; u16 w; u16 padc[2]; } Glyph;
typedef struct { u16 n; u8 pad2[0xb]; s8 col; u8 pade[2]; Glyph g[1]; } GlyphStr;
typedef struct { u8 pad0[4]; u16 mode; u8 pad6[2]; u16 w; u8 pada[2]; s16 cx; u8 pade[0x22]; f32 x, y; u8 pad38[0x38]; f32 ox, oy; } TextBox;
#define func_0010c720 ((s32 (*)(s32, s32, s32, s32 *, s32, s32, s32)) func_0010c720)
void func_0010cb80(GlyphStr *s, s32 max, s32 v, TextBox *b) {
    s32 dx, dy, dv;
    s32 i;
    Glyph *g;
    if (b == NULL) {
        dx = 0;
        dy = 0;
        dv = 48;
    } else {
        dx = b->x - b->ox;
        dy = b->y - b->oy;
        switch (b->mode) {
        case 0:
        case 1:
            dv = 32;
            break;
        default:
            dv = 16;
            break;
        }
    }
    for (i = 0; i < s->n; i++) {
        if (i >= max) return;
        g = &s->g[i];
        v = func_0010c720(g->x + dx, g->y + dy, g->code, &v, g->v + dv, g->w, s->col);
    }
}
#undef func_0010c720

/* func_0010cc98 (from hand/text_00100000_h28.c). */
typedef struct { u16 pad0; u16 n; f32 a; f32 b; s8 state; u8 padd[0x1803]; f32 t[1]; } Track;
s32 func_0010cc98(Track *p) {
    s32 i;
    if (p->n >= 2) {
        for (i = 0; i < p->n - 1; i++) {
            if (p->t[i] != 0.0f) return 0;
        }
    }
    if (p->t[p->n - 1] != 0.0f && p->b == p->a) return 1;
    return 0;
}

/* func_0010cd40 (from hand/text_00100000_h28.c). */
typedef struct { u8 pad[0x24]; s32 b; s32 a; } Seq;
extern s32 func_0010f258(s32, s32);
extern s32 func_0010f368(s32, s32);
void func_0010cd40(Track *t, Seq *s) {
    if (s->a == 0) return;
    switch (t->state) {
    case 0:
        if ((t->state = func_0010cc98(t)) == 0) break;
    case 1:
        func_0010f258(s->a, s->b);
        t->state = 2;
    case 2:
        if (func_0010f368(s->a, s->b) != 0) {
            t->state = 0;
            s->a = 0;
        }
        break;
    }
}

/* func_0010ce00 (from hand/text_00100000_h28.c). */
typedef struct {
    u16 pad0;
    u16 n;
    u8 pad[0x180c];
    f32 w[1];
} WeightBlk;
s32 func_0010ce00(WeightBlk *b) {
    s32 i;
    for (i = 0; i < b->n; i++) {
        if (b->w[i] != 0.0f) return 0;
    }
    return 1;
}

/* func_0010ce50 (from hand/text_00100000_h2.c). */
typedef struct {
    u8 pad[10];
    u16 a;
    u8 pad2[4];
} El16;
typedef struct {
    u8 pad[0x18];
    f32 add;
    u8 pad2[4];
    El16 *e;
} Fader;
void func_0010ce50(Fader *f, s32 n) {
    El16 *e;
    if (n <= 0) return;
    e = f->e + 1;
    do {
        if (e->a < 128) e->a = e->a + f->add;
        else e->a = 128;
        e++;
    } while (--n);
}

/* func_0010ced0 (from auto/text_00100000_14.c). */
void func_0010ced0(void *arg0, s32 arg1) {
  s8 *new_var2;
  s32 temp_f2;
  s8 *new_var;
  s32 var_a1;
  void *var_v1;
  var_a1 = arg1;
  *((s32 *) (((s8 *) arg0) + 0x18)) = 0;
  if (var_a1 > 0)
  {
    var_v1 = (*((s32 *) (((s8 *) arg0) + 0x20))) + 0x10;
    do
    {
      new_var2 = (s8 *) arg0;
      new_var = new_var2 + 0x1C;
      temp_f2 = (s32) (((f32) (*((u16 *) (((s8 *) var_v1) + 0xA)))) + (*((f32 *) new_var)));
      if (!(temp_f2 >= 0))
      {
        *((u16 *) (((s8 *) var_v1) + 0xA)) = 0U;
      }
      else
      {
        *((u16 *) (((s8 *) var_v1) + 0xA)) = temp_f2;
      }
      var_a1 -= 1;
      var_v1 += 0x10;
    }
    while (var_a1 != 0);
  }
}

/* func_0010cf20 (from auto/text_00100000_3.c). */
extern s32 D_002C5BB8;
s32 func_0010cf20(void) {
    if ((D_002C5BB8 & 1) != 0) {
        return 1;
    }
    return 0;
}

/* func_0010d0c0 (from hand/text_00100000_h2.c). */
typedef struct {
    u8 pad[0xc];
    f32 v;
} E16;
typedef struct { u16 n; u16 pad; f32 a; f32 b; u8 pad2[4]; E16 e[1]; } Acc;
void func_0010cf38(Acc *);
s32 func_0010d0c0(Acc *p) {
    s32 i;
    f32 sum, lim;
    func_0010cf38(p);
    lim = p->b;
    if (p->a <= lim) return p->n;
    sum = 0.0f;
    for (i = 0; i < p->n; i++) {
        sum += p->e[i].v;
        if (lim <= sum) return i + 1;
    }
    return 1;
}

/* func_0010d138 (from hand/text_00100000_h28.c). */
void func_0010d138(TextBox *b, GlyphStr *s) {
    s32 lines[32];
    s32 i, j, k, start, last, off;
    k = 0;
    for (j = 0; j < s->n - 1; j++) {
        if (s->g[j].y != s->g[j + 1].y) {
            lines[k++] = j;
        }
    }
    lines[k++] = s->n - 1;
    start = 0;
    for (j = 0; j < k; j++) {
        last = lines[j];
        off = b->cx - (((Glyph *)s)[last + 1].lw >> 1) - b->w;
        for (i = start; i < last + 1; i++) {
            ((Glyph *)s)[i + 1].x += off;
        }
        start = last + 1;
    }
}

/* func_0010d230 (from hand/text_00100000_h28.c). */
void func_0010d230(TextBox *b, GlyphStr *s) {
    s32 lines[32];
    s32 i, j, k, start, last, off;
    k = 0;
    for (j = 0; j < s->n - 1; j++) {
        if (s->g[j].y != s->g[j + 1].y) {
            lines[k++] = j;
        }
    }
    lines[k++] = s->n - 1;
    if (k - 2 < 2) return;
    start = lines[k - 3] + 1;
    for (j = k - 2; j < k; j++) {
        last = lines[j];
        off = b->cx + (b->cx - b->w) - ((Glyph *)s)[last + 1].lw - b->w;
        for (i = start; i < last + 1; i++) {
            ((Glyph *)s)[i + 1].x += off;
        }
        start = last + 1;
    }
}

/* func_0010d350 (from auto/text_00100000.c). */
s32 func_0010d350(s8 *arg0) {
    s32 var_v1;
    s8 *var_a0;

    var_a0 = arg0;
    var_v1 = 0;
    if (*var_a0 != 0) {
        do {
            var_a0 += 1;
            var_v1 += 1;
        } while (*var_a0 != 0);
    }
    return var_v1;
}

/* func_0010d388 (from hand/text_00100000_h28.c). */
typedef __builtin_va_list va_list;
extern void vsprintf(char *, const char *, va_list);
s32 func_0010d388(char *buf, const char *fmt, ...) {
    va_list ap;
    s32 n;
    __builtin_stdarg_start(ap, fmt);
    vsprintf(buf, fmt, ap);
    for (n = 0; *buf != 0; n++) {
        if (*buf == ' ') {
            *buf = 1;
        } else {
            *buf -= 15;
        }
        buf++;
    }
    return n;
}

/* func_0010d438 (from hand/text_00100000_h2.c). */
s16 func_0010d438(s32 *pos, u8 *buf) {
    s32 i = *pos;
    s32 lo = buf[++i];
    s32 hi = buf[++i];
    *pos = i;
    return lo + (hi << 8);
}

/* func_0010e3f0 (from auto/text_00100000_1.c). */
M2C_UNK func_00121ee0(s32);
void func_0010e3f0(void *arg0) {
    s32 temp_v0;

    M2C_FIELD(arg0, s8 *, 0x12) = 0;
    temp_v0 = M2C_FIELD(arg0, s32 *, 0x20);
    if (temp_v0 != 0) {
        func_00121ee0(temp_v0);
        M2C_FIELD(arg0, s32 *, 0x20) = 0;
    }
}

/* func_0010e430 (from hand/text_00100000_h28.c). */
typedef struct {
    void (*cb)(u16, s32);
    u8 pad4[0xa];
    u16 cnt;
    u8 pad10;
    u8 state;
    u8 b12;
    u8 flags;
    u8 pad14[0xc];
    void *res;
    s32 arg;
} Fade;
#define func_00121ee0 ((s32 (*)(void *)) func_00121ee0)
void func_0010e430(Fade *f) {
    switch (f->state) {
    case 1:
        if (f->cb != NULL) {
            if (!(f->flags & 1)) {
                f->flags |= 1;
                f->cnt++;
            }
            f->cb(f->cnt, f->arg);
        }
        break;
    case 0:
        f->b12 = 0;
        if (f->res != NULL) {
            func_00121ee0(f->res);
            f->res = NULL;
        }
        if (f->cb != NULL) {
            f->cnt++;
            f->cb(f->cnt, f->arg);
        }
        break;
    }
}
#undef func_00121ee0

/* func_0010e4f0 (from hand/text_00100000_h28.c). */
extern s32 D_002C1304;
typedef struct { u16 x0; u8 pad2[10]; u8 xc; } W29Sub;
typedef struct { u8 pad0[0x12]; u8 x12; u8 pad13[0xd]; W29Sub *x20; s32 x24; } W29Obj;
typedef struct { u32 lo:13; u32 b13:1; u32 hi:18; } F29;
extern F29 D_002C5958;
void func_00106d48(s32);
void func_0010d470(W29Obj *, W29Sub *);
W29Sub *func_00121e28(s32, W29Sub **);
#define func_0010c540 ((s32 (*)(s32, s32 *)) func_0010c540)
#define func_0010ce50 ((void (*)(W29Obj *, s32)) func_0010ce50)
#define func_0010d0c0 ((s32 (*)(W29Sub *, W29Obj *)) func_0010d0c0)
void func_0010e4f0(W29Obj *o) {
    s32 n, r;
    s32 buf[2];
    if (D_002C1304 == 1) return;
    if (D_002C5958.b13 == 1) return;
    switch (o->x12) {
    case 0:
        if (o->x20 == NULL) {
            o->x20 = func_00121e28(0x1890, &o->x20);
        }
        func_0010d470(o, o->x20);
        o->x12 = 1;
        o->x20->xc = 0;
    case 1:
        n = func_0010d0c0(o->x20, o);
        func_0010ce50(o, n);
        r = func_0010c540(n, buf);
        func_0010cb80((GlyphStr *)o->x20, n, buf[0], (TextBox *)o->x24);
        func_00106d48(r);
        if (n == o->x20->x0 && func_0010ce00((WeightBlk *)o->x20)) {
            func_0010e430((Fade *)o);
        }
        break;
    }
}
#undef func_0010c540
#undef func_0010ce50
#undef func_0010d0c0

/* func_0010e750 (from auto/text_00100000_9.c). */
M2C_UNK func_0010e610(s32, s32, M2C_UNK);
#define func_0010c438 ((M2C_UNK (*)(M2C_UNK, s32)) func_0010c438)
#define func_00121e28 ((s32 (*)(M2C_UNK, s32 *)) func_00121e28)
void func_0010e750(void) {
    s32 sp[8];
    M2C_FIELD(sp, s32 *, 0x0) = func_00121e28(0x40, sp);
    M2C_FIELD(sp, s32 *, 0x4) = func_00121e28(0x40, &M2C_FIELD(sp, s32 *, 0x4));
    M2C_FIELD(sp, s32 *, 0x8) = func_00121e28(0x40, &M2C_FIELD(sp, s32 *, 0x8));
    M2C_FIELD(sp, s32 *, 0xC) = func_00121e28(0x40, &M2C_FIELD(sp, s32 *, 0xC));
    M2C_FIELD(sp, s32 *, 0x10) = func_00121e28(0x40, &M2C_FIELD(sp, s32 *, 0x10));
    M2C_FIELD(sp, s32 *, 0x14) = func_00121e28(0x40, &M2C_FIELD(sp, s32 *, 0x14));
    M2C_FIELD(sp, s32 *, 0x18) = func_00121e28(0x40, &M2C_FIELD(sp, s32 *, 0x18));
    M2C_FIELD(sp, s32 *, 0x1C) = func_00121e28(0x40, &M2C_FIELD(sp, s32 *, 0x1C));
    func_0010e610(M2C_FIELD(sp, s32 *, 0x0), M2C_FIELD(sp, s32 *, 0x4), 0);
    func_0010e610(M2C_FIELD(sp, s32 *, 0x8), M2C_FIELD(sp, s32 *, 0xC), 1);
    func_0010e610(M2C_FIELD(sp, s32 *, 0x10), M2C_FIELD(sp, s32 *, 0x14), 2);
    func_0010e610(M2C_FIELD(sp, s32 *, 0x18), M2C_FIELD(sp, s32 *, 0x1C), 3);
    func_0010c438(0x3FEC, M2C_FIELD(sp, s32 *, 0x0));
    func_0010c438(0x3FED, M2C_FIELD(sp, s32 *, 0x4));
    func_0010c438(0x3FEE, M2C_FIELD(sp, s32 *, 0x8));
    func_0010c438(0x3FEF, M2C_FIELD(sp, s32 *, 0xC));
    func_0010c438(0x3FF0, M2C_FIELD(sp, s32 *, 0x10));
    func_0010c438(0x3FF1, M2C_FIELD(sp, s32 *, 0x14));
    func_0010c438(0x3FF2, M2C_FIELD(sp, s32 *, 0x18));
    func_0010c438(0x3FF3, M2C_FIELD(sp, s32 *, 0x1C));
    PlatGsSyncPath(0, 0);
    func_00121ee0(M2C_FIELD(sp, s32 *, 0x0));
    func_00121ee0(M2C_FIELD(sp, s32 *, 0x4));
    func_00121ee0(M2C_FIELD(sp, s32 *, 0x8));
    func_00121ee0(M2C_FIELD(sp, s32 *, 0xC));
    func_00121ee0(M2C_FIELD(sp, s32 *, 0x10));
    func_00121ee0(M2C_FIELD(sp, s32 *, 0x14));
    func_00121ee0(M2C_FIELD(sp, s32 *, 0x18));
    func_00121ee0(M2C_FIELD(sp, s32 *, 0x1C));
}
#undef func_0010c438
#undef func_00121e28

/* func_0010e8d0 (from auto/text_00100000_6.c). */
extern M2C_UNK D_002BB620;
extern M2C_UNK D_002BB660;
extern M2C_UNK D_002BB6A0;
extern M2C_UNK D_002BB6E0;
extern M2C_UNK D_002BB720;
extern M2C_UNK D_002BB760;
extern M2C_UNK D_002BB7A0;
extern M2C_UNK D_002BB7E0;
extern M2C_UNK D_002BB820;
extern M2C_UNK D_002BB860;
extern M2C_UNK D_002BB8A0;
extern M2C_UNK D_002BB8E0;
extern M2C_UNK D_002BB920;
extern M2C_UNK D_002BB960;
extern M2C_UNK D_002BB9A0;
extern M2C_UNK D_002BB9E0;
void *func_0011ef10(M2C_UNK, M2C_UNK *);
#define func_0010c438 ((M2C_UNK (*)(M2C_UNK, M2C_UNK *)) func_0010c438)
void func_0010e8d0(void) {
    M2C_FIELD(func_0011ef10(0x2BFB6, &func_0010c4b0), s16 *, 2) = -1;
    func_0010c438(0x3FDC, &D_002BB620);
    func_0010c438(0x3FDD, &D_002BB660);
    func_0010c438(0x3FDE, &D_002BB6A0);
    func_0010c438(0x3FDF, &D_002BB6E0);
    func_0010c438(0x3FE0, &D_002BB720);
    func_0010c438(0x3FE1, &D_002BB760);
    func_0010c438(0x3FE2, &D_002BB7A0);
    func_0010c438(0x3FE3, &D_002BB7E0);
    func_0010c438(0x3FE4, &D_002BB820);
    func_0010c438(0x3FE5, &D_002BB860);
    func_0010c438(0x3FE6, &D_002BB8A0);
    func_0010c438(0x3FE7, &D_002BB8E0);
    func_0010c438(0x3FE8, &D_002BB920);
    func_0010c438(0x3FE9, &D_002BB960);
    func_0010c438(0x3FEA, &D_002BB9A0);
    func_0010c438(0x3FEB, &D_002BB9E0);
}
#undef func_0010c438

/* func_0010ea00 (from auto/text_00100000_9.c). */
M2C_UNK func_00106b18(M2C_UNK *);
#define func_0010e4f0 ((M2C_UNK (*)(void *)) func_0010e4f0)
void func_0010ea00(void *arg0) {
    func_00106b18((M2C_UNK *)&D_002BBAA0);
    M2C_FIELD(arg0, s8 *, 0x11) = 1;
    func_0010e4f0(arg0);
}
#undef func_0010e4f0

/* func_0010ea38 (from auto/text_00100000_9.c). */
#define func_0010e4f0 ((M2C_UNK (*)(void *)) func_0010e4f0)
void func_0010ea38(void *arg0) {
    func_00106b18((M2C_UNK *)&D_002BBAA0);
    M2C_FIELD(arg0, s32 *, 0x24) = 0;
    M2C_FIELD(arg0, s8 *, 0x11) = 0;
    func_0010e4f0(arg0);
}
#undef func_0010e4f0

/* func_0010ea70 (from hand/text_00100000_s10_r2_3.c). */
typedef struct {
    s32 x0; s32 x4; s16 x8; s16 xa; s16 xc; s16 xe;
    u8 x10; u8 x11; u8 x12; u8 x13; f32 x14; f32 x18; f32 x1c; s32 x20; struct TBox *x24; s32 x28;
} TObj;
typedef struct TBox {
    u8 pad0[4]; s16 h4; u8 pad6[0x2a]; f32 x30, x34; u8 pad38[0x38]; f32 x70, x74;
} TBox;
#define func_00106b18 ((s32 (*)(void *)) func_00106b18)
#define func_0010e4f0 ((void (*)(TObj *)) func_0010e4f0)
#define func_00121e28 ((void *(*)(s32, void *)) func_00121e28)
#define func_00121ee0 ((void (*)(void *)) func_00121ee0)
/* func_0010ea70 (s10 r2_3): x1c is an f32 (zeroed); its f32 output deps on the B->x30.. stores give sw x1c the right sched2 rank. */
void func_0010ea70(s32 x, s32 y, s32 p) {
    void *v[2];
    v[0] = func_00121e28(0xb0, &v[0]);
    v[1] = func_00121e28(0x2c, &v[1]);
#define O ((TObj *)v[1])
#define B ((TBox *)v[0])
    O->x12 = 0;
    O->x0 = 0;
    O->x10 = 1;
    O->x14 = 0.0f;
    O->x8 = x;
    O->x24 = B;
    O->xa = y;
    O->x4 = p;
    O->x13 = 0;
    O->x13 |= 2;
    O->x11 = 0;
    O->x18 = 0.0f;
    O->x20 = 0;
    O->xc = 0;
    O->x1c = 0.0f;
    O->xe = 0;
    O->x28 = 0;
    B->h4 = 2;
    B->x30 = B->x34 = B->x70 = B->x74 = O->x18;
    func_00106b18(D_002BBAA0);
    func_0010e4f0(O);
    func_00121ee0(O);
    func_00121ee0(B);
}
#undef func_00106b18
#undef func_0010e4f0
#undef func_00121e28
#undef func_00121ee0

/* func_0010eb78 (from hand/text_00100000_h2.c). */
s32 func_0010eb78(u8 *s) {
    s32 cnt = 0, run = 1, i = 0;
    u8 c;
    do {
        c = s[i];
        if (c < 32) {
            if (c < 9) {
                if (c == 0) run = 0;
                else if (c == 4) run = 0;
            } else if (c == 15) {
                i++;
                if (s[i] == 1) cnt++;
            } else {
                i++;
            }
        }
        i++;
    } while (run);
    return cnt;
}

/* func_0010edb0 (from auto/text_00100000_10.c). */
M2C_UNK func_0010ec08(s32, void *, s32);
M2C_UNK func_0010ed20(s32, s32, s32, void *, void *);
#define func_0010c4b0 ((M2C_UNK (*)()) func_0010c4b0)
#define func_00121ee0 ((M2C_UNK (*)(void *)) func_00121ee0)
#define func_00121e28 ((void *(*)(M2C_UNK, void **)) func_00121e28)
void func_0010edb0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 sp[4];
    M2C_FIELD(sp, void * *, 0x0) = func_00121e28(0x2C, sp);
    M2C_FIELD(sp, void * *, 0x4) = func_00121e28(0x400, &M2C_FIELD(sp, void * *, 0x4));
    func_0010c4b0();
    func_0010ec08(arg5, M2C_FIELD(sp, void * *, 0x4), arg3);
    M2C_FIELD(M2C_FIELD(sp, void * *, 0x0), u8 *, 0x13) = 0U;
    M2C_FIELD(M2C_FIELD(sp, void * *, 0x0), u8 *, 0x13) = (u8) (M2C_FIELD(M2C_FIELD(sp, void * *, 0x0), u8 *, 0x13) | 4);
    M2C_FIELD(M2C_FIELD(sp, void * *, 0x0), u8 *, 0x13) = (u8) (M2C_FIELD(M2C_FIELD(sp, void * *, 0x0), u8 *, 0x13) | 8);
    func_0010ed20(arg0, arg1, arg4, M2C_FIELD(sp, void * *, 0x4), M2C_FIELD(sp, void * *, 0x0));
    func_0010ec08(arg5, M2C_FIELD(sp, void * *, 0x4), arg3 + 1);
    M2C_FIELD(M2C_FIELD(sp, void * *, 0x0), u8 *, 0x13) = 0U;
    M2C_FIELD(M2C_FIELD(sp, void * *, 0x0), u8 *, 0x13) = (u8) (M2C_FIELD(M2C_FIELD(sp, void * *, 0x0), u8 *, 0x13) | 4);
    M2C_FIELD(M2C_FIELD(sp, void * *, 0x0), u8 *, 0x13) = (u8) (M2C_FIELD(M2C_FIELD(sp, void * *, 0x0), u8 *, 0x13) | 8);
    func_0010ed20(arg0 + arg2, arg1, arg4, M2C_FIELD(sp, void * *, 0x4), M2C_FIELD(sp, void * *, 0x0));
    func_00121ee0(M2C_FIELD(sp, void * *, 0x4));
    func_00121ee0(M2C_FIELD(sp, void * *, 0x0));
}
#undef func_0010c4b0
#undef func_00121ee0
#undef func_00121e28

/* func_0010eee0 (from auto/text_00100000_11.c). */
#define func_0010c4b0 ((M2C_UNK (*)()) func_0010c4b0)
#define func_0010ed20 ((M2C_UNK (*)(s32, s32, s32, s32, void *)) func_0010ed20)
#define func_00121ee0 ((M2C_UNK (*)(void *)) func_00121ee0)
#define func_00121e28 ((void *(*)(M2C_UNK, void *)) func_00121e28)
void func_0010eee0(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 sp[4];
    M2C_FIELD(sp, void * *, 0x0) = func_00121e28(0x2C, sp);
    func_0010c4b0();
    M2C_FIELD(M2C_FIELD(sp, void * *, 0x0), u8 *, 0x13) = 0U;
    M2C_FIELD(M2C_FIELD(sp, void * *, 0x0), u8 *, 0x13) = (u8) (M2C_FIELD(M2C_FIELD(sp, void * *, 0x0), u8 *, 0x13) | 4);
    func_0010ed20(arg0, arg1, arg2, arg3, M2C_FIELD(sp, void * *, 0x0));
    func_00121ee0(M2C_FIELD(sp, void * *, 0x0));
}
#undef func_0010c4b0
#undef func_0010ed20
#undef func_00121ee0
#undef func_00121e28


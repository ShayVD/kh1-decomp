/* ttlib/ui.c (include/hud/ui.h, docs/modules.md "Session 47"),
 * 0x00249fb0-0x0024b0c8 except ui.nostrict.c's two.  The UiSpr tracks: a
 * step for each (func_00249fb0 a, func_0024a1c8 b, func_0024a490 c; the end
 * sets the track's bit 4), the value now (func_0024a0e0 a's colour,
 * func_0024a300 b's four, func_0024a588 c's rectangle), start / stop / reset
 * of each (func_0024a088 ... func_0024a698) and their flags
 * (func_0024a1c0, func_0024a488, func_0024a6b0); the sprite into a GS packet
 * (func_0024a6b8, func_0024aa48 with a texture's TEX0), the sprite file's
 * set up (func_0024aac8), the rectangle and colours now (func_0024ac08,
 * func_0024ac68), start / stop / step of all tracks (func_0024ae00,
 * func_0024ae90, func_0024af00), one colour for all four vertices
 * (func_0024b008) and a packet's positions (func_0024b058). */
#include "m2c.h"
#include "hud/ui.h"
#include "data/pieces/D_004268B0.h"

/* The first tag of a UiPkt as TEX0 fields (func_0024aa48). */
typedef struct {
    u64 lo : 20;
    u64 f20 : 6;
    u64 mid : 30;
    u64 f56 : 5;
    u64 f61 : 3;
} Tag;
/* The sprite file: the elements and the keys of each track. */
typedef struct { u8 pad[8]; s32 ui_off; u32 ui_size; s32 fa_off; u8 pad14[4]; s32 fb_off; u8 pad1c[4]; s32 fc_off; } UiFile;

void __assert(const char *, s32, const char *);
extern char D_00491848[], D_00491860[];

void func_00249fb0(UiSpr *u, s32 dt) {
    if ((u->h.flags & 10) == 10) {
        UiAnim *ra = &u->s.a;
        if (!ra) __assert("ttlib/ui.c", 14, "ra");
        if (ra->idx < ra->n - 1) {
            ra->time += dt;
            while (ra->time >= ra->fr[ra->idx].dur) {
                ra->time -= ra->fr[ra->idx].dur;
                ra->idx++;
                if (ra->idx == ra->n - 1) {
                    u->s.a.flags |= 4;
                    break;
                }
            }
        }
    }
}

void func_0024a088(UiSpr *g) {
    g->s.flags |= 8;
    g->s.a.flags |= 2;
}

void func_0024a0a8(UiSpr *g) {
    g->s.a.flags = 0;
    g->s.flags &= ~8;
}

void func_0024a0c0(UiSpr *g) {
    UiAnim *s = &g->s.a;
    s->idx = 0;
    s->time = 0;
    s->flags &= ~4;
}

void func_0024a0e0(UiSpr *u, s32 *out) {
    UiAnim *a = &u->s.a;
    s32 i;
    if (a->idx < a->n - 1) {
        f32 t = (f32)a->time / (f32)a->fr[a->idx].dur;
        UiKey *f = &a->fr[a->idx];
        for (i = 0; i < 4; i++)
            out[i] = f->v[i] + (f[1].v[i] - f->v[i]) * t;
    } else {
        UiKey *f = &a->fr[a->idx];
        for (i = 0; i < 4; i++)
            out[i] = f->v[i];
    }
}

s32 func_0024a1c0(UiSpr *u) {
    return u->s.a.flags;
}

void func_0024a1c8(UiSpr *u, s32 dt) {
    if ((u->h.flags & 0xc0) == 0xc0) {
        UiAnim4 *ra = &u->s.b;
        if (!ra) __assert("ttlib/ui.c", 100, "ra");
        if (ra->idx < ra->n - 1) {
            ra->time += dt;
            while (ra->time >= ra->fr[ra->idx].dur) {
                ra->time -= ra->fr[ra->idx].dur;
                ra->idx++;
                if (ra->idx == ra->n - 1) {
                    u->s.b.flags |= 4;
                    break;
                }
            }
        }
    }
}

void func_0024a2e0(UiSpr *g) {
    UiAnim4 *s = &g->s.b;
    s->idx = 0;
    s->time = 0;
    s->flags &= ~4;
}

void func_0024a300(UiSpr *u, s32 (*out)[4]) {
    UiAnim4 *ra = &u->s.b;
    s32 i, j;
    if (!ra) __assert("ttlib/ui.c", 137, "ra");
    if (ra->idx < ra->n - 1) {
        f32 t = (f32)ra->time / (f32)ra->fr[ra->idx].dur;
        UiKey4 *f = &ra->fr[ra->idx];
        for (i = 0; i < 4; i++)
            for (j = 0; j < 4; j++)
                out[i][j] = f->v[i][j] + (f[1].v[i][j] - f->v[i][j]) * t;
    } else {
        UiKey4 *f = &ra->fr[ra->idx];
        for (i = 0; i < 4; i++)
            for (j = 0; j < 4; j++)
                out[i][j] = f->v[i][j];
    }
}

void func_0024a450(UiSpr *g) {
    g->s.flags |= 0x80;
    g->s.b.flags |= 2;
}

void func_0024a470(UiSpr *g) {
    g->s.b.flags = 0;
    g->s.flags &= ~0x80;
}

s32 func_0024a488(UiSpr *u) {
    return u->s.b.flags;
}

void func_0024a490(UiSpr *u, s32 dt) {
    if ((u->h.flags & 0x14) == 0x14) {
        UiAnim *ra = &u->s.c;
        if (!ra) __assert("ttlib/ui.c", 199, "ra");
        if (ra->idx < ra->n - 1) {
            ra->time += dt;
            while (ra->time >= ra->fr[ra->idx].dur) {
                ra->time -= ra->fr[ra->idx].dur;
                ra->idx++;
                if (ra->idx == ra->n - 1) {
                    u->s.c.flags |= 4;
                    break;
                }
            }
        }
    }
}

void func_0024a568(UiSpr *g) {
    UiAnim *s = &g->s.c;
    s->idx = 0;
    s->time = 0;
    s->flags &= ~4;
}

void func_0024a588(UiSpr *u, s32 *out) {
    UiAnim *a = &u->s.c;
    s32 i;
    if (a->idx < a->n - 1) {
        f32 c0[4], c1[4];
        f32 t = (f32)a->time / (f32)a->fr[a->idx].dur;
        UiKey *f = &a->fr[a->idx];
        for (i = 0; i < 4; i++) {
            c0[i] = f->v[i];
            c1[i] = f[1].v[i];
            out[i] = c0[i] + (c1[i] - c0[i]) * t;
        }
    } else {
        UiKey *f = &a->fr[a->idx];
        for (i = 0; i < 4; i++)
            out[i] = f->v[i];
    }
}

void func_0024a678(UiSpr *g) {
    g->s.flags |= 0x10;
    g->s.c.flags |= 2;
}

void func_0024a698(UiSpr *g) {
    g->s.c.flags = 0;
    g->s.flags &= ~0x10;
}

s32 func_0024a6b0(UiSpr *u) {
    return u->s.c.flags;
}

static inline void inl_0024a6b8_setxy(UiPkt *p, s32 rx, s32 ry, s32 rw, s32 rh) {
    s32 x0, y0, x1, y1;
    y1 = ((ry + rh) << 4) + 0x7400;
    x0 = (rx << 4) + 0x7000;
    y0 = (ry << 4) + 0x7400;
    x1 = ((rx + rw) << 4) + 0x7000;
    p->xy[0][0] = x0; p->xy[0][1] = y0; p->xy[0][2] = -256; p->xy[0][3] = 0;
    p->xy[1][0] = x0; p->xy[1][1] = y1; p->xy[1][2] = -256; p->xy[1][3] = 0;
    p->xy[2][0] = x1; p->xy[2][1] = y0; p->xy[2][2] = -256; p->xy[2][3] = 0;
    p->xy[3][0] = x1; p->xy[3][1] = y1; p->xy[3][2] = -256; p->xy[3][3] = 0;
}

void func_0024a6b8(UiPkt *p, UiSpr *u, u64 x) {
    s32 t[4];
    s32 r[4];
    s32 t2[4][4];
    s32 i, j;
    p->unk0 = x;
    p->unk8 = 6;
    p->unk10 = x;
    p->unk18 = 6;
    if ((u->h.flags & 10) == 10) {
        func_0024a0e0(u, t);
        for (i = 0; i < 4; i++)
            for (j = 0; j < 4; j++)
                p->m[i][j] = t[j];
    } else if ((u->h.flags & 0xC0) == 0xC0) {
        func_0024a300(u, t2);
        for (i = 0; i < 4; i++)
            for (j = 0; j < 4; j++)
                p->m[i][j] = t2[i][j];
    } else if (*(u32 *)&u->h.flags & 0x20) {
        for (i = 0; i < 4; i++)
            for (j = 0; j < 4; j++)
                p->m[i][j] = u->s.m[i][j];
    } else {
        for (i = 0; i < 4; i++)
            for (j = 0; j < 4; j++)
                p->m[i][j] = u->s.m[0][j];
    }
    if ((u->h.flags & 20) == 20) {
        func_0024a588(u, r);
        inl_0024a6b8_setxy(p, r[0], r[1], r[2], r[3]);
    } else {
        inl_0024a6b8_setxy(p, u->s.r[0], u->s.r[1], u->s.r[2], u->s.r[3]);
    }
    if (u->s.t[0] < u->s.t[2]) {
        p->uv[0][0] = u->s.t[0] * 16 + 8;
        p->uv[1][0] = u->s.t[0] * 16 + 8;
        p->uv[2][0] = u->s.t[2] * 16 + 24;
        p->uv[3][0] = u->s.t[2] * 16 + 24;
    } else {
        p->uv[0][0] = u->s.t[0] * 16 + 8;
        p->uv[1][0] = u->s.t[0] * 16 + 8;
        p->uv[2][0] = u->s.t[2] * 16 - 8;
        p->uv[3][0] = u->s.t[2] * 16 - 8;
    }
    if (u->s.t[1] < u->s.t[3]) {
        p->uv[0][1] = u->s.t[1] * 16 + 8;
        p->uv[1][1] = u->s.t[3] * 16 + 24;
        p->uv[2][1] = u->s.t[1] * 16 + 8;
        p->uv[3][1] = u->s.t[3] * 16 + 24;
    } else {
        p->uv[0][1] = u->s.t[1] * 16 + 8;
        p->uv[1][1] = u->s.t[3] * 16 - 8;
        p->uv[2][1] = u->s.t[1] * 16 + 8;
        p->uv[3][1] = u->s.t[3] * 16 - 8;
    }
}

void func_0024aa48(UiSpr *a, UiPkt *p, Tex_4268b0 *s) {
    Tag *t = (Tag *)p;
    func_0024a6b8(p, a, s->tb.unk18);
    t->f56 = 0;
    t->f61 = 1;
    t->f20 = 0x13;
}

void func_0024aac8(UiFile *buffer) {
    UiSpr *u;
    s32 i, n;
    UiKey *fa, *fc;
    UiKey4 *fb;
    if ((s32)buffer & 0xf) __assert(D_00491848, 524, D_00491860);
    n = buffer->ui_size / sizeof(UiSpr);
    i = buffer->ui_size / sizeof(UiKey4);
    u = (UiSpr *)((u8 *)buffer + buffer->ui_off);
    fa = (UiKey *)((u8 *)buffer + buffer->fa_off);
    fb = (UiKey4 *)((u8 *)buffer + buffer->fb_off);
    fc = (UiKey *)((u8 *)buffer + buffer->fc_off);
    for (i = 0; i < n; i++, u++) {
        u32 fl = u->s.flags;
        if (fl & 2) {
            if ((s32)u->s.a.fr <= 0xfffff) u->s.a.fr = &fa[(s32)u->s.a.fr];
        }
        if (fl & 0x40) {
            if ((s32)u->s.b.fr <= 0xfffff) u->s.b.fr = &fb[(s32)u->s.b.fr];
        }
        if (fl & 4) {
            if ((s32)u->s.c.fr <= 0xfffff) u->s.c.fr = &fc[(s32)u->s.c.fr];
        }
    }
}

void func_0024abd8(s32 arg0, void *arg1) {
    s32 var_a0;
    void *var_a1;

    var_a0 = arg0;
    var_a1 = arg1;
    if (var_a0 > 0) {
        do {
            var_a0 -= 1;
            M2C_FIELD(var_a1, s32 *, 0x10) = 0;
            M2C_FIELD(var_a1, s32 *, 0x14) = 0;
            var_a1 += 0x20;
        } while (var_a0 != 0);
    }
}

void func_0024ac08(UiSpr *u, s32 *out) {
    if ((u->h.flags & 0x14) == 0x14) {
        func_0024a588(u, out);
        return;
    }
    out[0] = u->s.r[0];
    out[1] = u->s.r[1];
    out[2] = u->s.r[2];
    out[3] = u->s.r[3];
}

void func_0024ac68(UiSpr *u, s32 (*out)[4]) {
    s32 i, j;
    if ((u->h.flags & 10) == 10) {
        s32 t[4];
        func_0024a0e0(u, t);
        for (i = 0; i < 4; i++)
            for (j = 0; j < 4; j++)
                out[i][j] = t[j];
    } else if ((u->h.flags & 0xC0) == 0xC0) {
        s32 t[4][4];
        func_0024a300(u, t);
        for (i = 0; i < 4; i++)
            for (j = 0; j < 4; j++)
                out[i][j] = t[i][j];
    } else if (u->s.flags & 0x20) {
        for (i = 0; i < 4; i++)
            for (j = 0; j < 4; j++)
                out[i][j] = u->s.m[i][j];
    } else {
        for (i = 0; i < 4; i++)
            for (j = 0; j < 4; j++)
                out[i][j] = u->s.m[0][j];
    }
}

void func_0024ae00(UiSpr *g) {
    if (g->s.flags & 4) { func_0024a568(g); func_0024a678(g); }
    if (g->s.flags & 2) { func_0024a0c0(g); func_0024a088(g); }
    if (g->s.flags & 0x40) { func_0024a2e0(g); func_0024a450(g); }
}

void func_0024ae90(UiSpr *g) {
    if (g->s.flags & 4) func_0024a698(g);
    if (g->s.flags & 2) func_0024a0a8(g);
    if (g->s.flags & 0x40) func_0024a470(g);
}

void func_0024af00(UiSpr *u) {
    func_0024a490(u, 1);
    func_00249fb0(u, 1);
    func_0024a1c8(u, 1);
}

void func_0024b008(UiSpr *u, s32 *c) {
    s32 i, j;
    for (i = 0; i < 4; i++) {
        s32 *d = u->s.m[i];
        s32 *p = c;
        j = 3;
        do {
            *d++ = *p++;
        } while (--j >= 0);
    }
}

void func_0024b058(UiPkt *p, s32 x, s32 y, s32 w, s32 h) {
    s32 x0, y0, x1, y1;

    x0 = (x * 0x10) + 0x7000;
    y0 = (y * 0x10) + 0x7400;
    y1 = ((y + h) * 0x10) + 0x7400;
    x1 = ((x + w) * 0x10) + 0x7000;
    p->xy[0][0] = x0;
    p->xy[0][1] = y0;
    p->xy[0][2] = -0x100;
    p->xy[0][3] = 0;
    p->xy[1][0] = x0;
    p->xy[1][1] = y1;
    p->xy[1][2] = -0x100;
    p->xy[1][3] = 0;
    p->xy[2][0] = x1;
    p->xy[2][1] = y0;
    p->xy[2][2] = -0x100;
    p->xy[2][3] = 0;
    p->xy[3][0] = x1;
    p->xy[3][1] = y1;
    p->xy[3][2] = -0x100;
    p->xy[3][3] = 0;
}

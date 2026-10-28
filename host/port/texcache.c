/* A port's decoded-texture cache keyed by the layout and the page stamp, the texels' hash on a stamp
 * miss (include/platform/texcache.h, docs/renderer-spec.md 4.13 "Session 118"), checked by
 * tests/host/texcache_test.c on 4.13 "Session 117"'s cases and on render targets.  Not part of the
 * PS2 build (it lives outside src/). */
#include "common.h"
#include "platform/texcache.h"

void *memset(void *, int, __SIZE_TYPE__);
int memcmp(const void *, const void *, __SIZE_TYPE__);
void *memcpy(void *, const void *, __SIZE_TYPE__);
void *malloc(__SIZE_TYPE__);
void free(void *);

#define SCRATCH (1u << 20)

static u32 fnv(const u32 *t, u32 n) {
    u32 h = 2166136261u, i;
    for (i = 0; i < n; i++) h = (h ^ t[i]) * 16777619u;
    return h;
}

int kh1_texcache_init(KH1TexCache *c) {
    u32 *s = c->scratch;
    if (s) kh1_texcache_free(c);
    memset(c, 0, sizeof *c);
    c->scratch = malloc(SCRATCH * 4);
    c->frame = 1;
    return c->scratch ? 0 : -1;
}

void kh1_texcache_free(KH1TexCache *c) {
    u32 i;
    for (i = 0; i < KH1_TEXCACHE_SLOTS; i++) {
        free(c->slot[i].tex);
        free(c->slot[i].raw);
    }
    free(c->scratch);
    free(c->rawbuf);
    memset(c, 0, sizeof *c);
}

void kh1_texcache_frame(KH1TexCache *c) { c->frame++; }

static void drop(KH1TexCache *c, KH1TexSlot *s) {
    c->texels -= s->n;
    free(s->tex);
    free(s->raw);
    memset(s, 0, sizeof *s);
}

/* the least recently drawn entry no draw of this frame reads, 0 for none */
static KH1TexSlot *lru(KH1TexCache *c) {
    KH1TexSlot *best = 0;
    u32 i;
    for (i = 0; i < KH1_TEXCACHE_SLOTS; i++) {
        KH1TexSlot *s = &c->slot[i];
        if (s->n && s->frame != c->frame && (!best || s->use < best->use)) best = s;
    }
    return best;
}

/* a slot for n texels: older entries dropped while the budget is short, then an empty slot or the
 * least recently drawn one.  0 when none can be had */
static KH1TexSlot *take(KH1TexCache *c, u32 n) {
    KH1TexSlot *s = 0;
    u32 i;
    if (n > KH1_TEXCACHE_TEXELS) return 0;
    while (c->texels + n > KH1_TEXCACHE_TEXELS) {
        if (!(s = lru(c))) return 0;
        drop(c, s);
    }
    for (i = 0; i < KH1_TEXCACHE_SLOTS && c->slot[i].n; i++) ;
    if (i < KH1_TEXCACHE_SLOTS) s = &c->slot[i];
    else if ((s = lru(c)) != 0) drop(c, s);
    else return 0;
    s->tex = malloc(n * 4);
    return s->tex ? s : 0;
}

/* session 142: the pages' raw words the entry's texels came from (none kept when they cannot be had) */
static void keep_raw(KH1TexSlot *s, const u32 *raw, u32 n) {
    if (s->nraw != n) {
        free(s->raw);
        s->raw = n ? malloc(n * 4) : 0;
        s->nraw = s->raw ? n : 0;
    }
    if (s->nraw) memcpy(s->raw, raw, n * 4);
}

const u32 *kh1_texcache_get(KH1TexCache *c, u32 lo, u32 hi, u32 stamp, u32 target, KH1TexRead read, void *ctx,
                            int *decoded) {
    u32 tw = lo >> 26 & 15, th = (lo >> 30 | hi << 2) & 15, n, h, i, nraw;
    KH1TexSlot *s;
    *decoded = 0;
    hi &= 3; /* lo is TBP0, TBW, PSM, TW and TH's low bits; hi's low 2 are TH's high ones */
    c->draws++;
    c->use++;
    if (target) {
        c->targets++;
        return 0;
    }
    if (tw > 10 || th > 10) {
        c->full++;
        return 0;
    }
    n = 1u << tw << th;
    for (i = 0; i < KH1_TEXCACHE_SLOTS; i++) {
        s = &c->slot[i];
        if (s->n && s->lo == lo && s->hi == hi && s->stamp == stamp) {
            s->frame = c->frame;
            s->use = c->use;
            c->stamp_hits++;
            return s->tex;
        }
    }
    /* session 142: the pages' raw words, when an entry of this layout last saw the same ones */
    nraw = 0;
    if (c->raw && (c->rawbuf || (c->rawbuf = malloc(KH1_TEXCACHE_RAW * 4)) != 0))
        nraw = c->raw(lo, hi, c->rawbuf, KH1_TEXCACHE_RAW);
    for (i = 0; nraw && i < KH1_TEXCACHE_SLOTS; i++) {
        s = &c->slot[i];
        if (s->n && s->lo == lo && s->hi == hi && s->nraw == nraw && memcmp(s->raw, c->rawbuf, nraw * 4) == 0) {
            s->stamp = stamp;
            s->frame = c->frame;
            s->use = c->use;
            c->hash_hits++;
            c->raw_hits++;
            return s->tex;
        }
    }
    read(lo, hi, c->scratch, ctx);
    h = fnv(c->scratch, n);
    c->hashed += n;
    for (i = 0; i < KH1_TEXCACHE_SLOTS; i++) {
        s = &c->slot[i];
        if (s->n && s->lo == lo && s->hi == hi && s->hash == h && memcmp(s->tex, c->scratch, n * 4) == 0) {
            s->stamp = stamp; /* the bytes are back: the new stamp is this entry's */
            s->frame = c->frame;
            s->use = c->use;
            c->hash_hits++;
            keep_raw(s, c->rawbuf, nraw);
            return s->tex;
        }
    }
    s = take(c, n);
    if (!s) {
        c->full++;
        return 0;
    }
    s->lo = lo;
    s->hi = hi;
    s->stamp = stamp;
    s->hash = h;
    s->n = n;
    s->frame = c->frame;
    s->use = c->use;
    memcpy(s->tex, c->scratch, n * 4);
    keep_raw(s, c->rawbuf, nraw);
    c->texels += n;
    c->decodes++;
    c->decoded += n;
    *decoded = 1;
    return s->tex;
}

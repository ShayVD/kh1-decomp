/* A port's palette cache keyed by the CLUT entries loaded (include/platform/palcache.h,
 * docs/renderer-spec.md 4.13 "Session 116"), checked by tests/host/palcache_test.c on 4.13
 * "Session 115"'s cases.  Not part of the PS2 build (it lives outside src/). */
#include "common.h"
#include "platform/palcache.h"

void *memset(void *, int, __SIZE_TYPE__);

static u32 fnv(const u32 *col, u32 n) {
    u32 h = 2166136261u, i, k;
    for (i = 0; i < n; i++)
        for (k = 0; k < 32; k += 8) h = (h ^ (col[i] >> k & 0xFF)) * 16777619u;
    return h ^ n;
}

static int same(const KH1PalSlot *s, const u32 *col, u32 n) {
    u32 i;
    if (s->n != n) return 0;
    for (i = 0; i < n; i++)
        if (s->col[i] != col[i]) return 0;
    return 1;
}

void kh1_palcache_init(KH1PalCache *c) {
    memset(c, 0, sizeof *c);
    c->frame = 1;
}

void kh1_palcache_frame(KH1PalCache *c) { c->frame++; }

int kh1_palcache_get(KH1PalCache *c, const u32 *col, u32 n, int *fill) {
    u32 h, i;
    int best = -1;
    *fill = 0;
    if (n != 16 && n != 256) return -1;
    h = fnv(col, n);
    c->use++;
    for (i = 0; i < KH1_PALCACHE_SLOTS; i++) {
        KH1PalSlot *s = &c->slot[i];
        if (s->n && s->hash == h && same(s, col, n)) {
            s->frame = c->frame;
            s->use = c->use;
            c->hits++;
            return (int)i;
        }
        /* an empty slot first, then the least recently used one no draw of this frame reads */
        if (s->frame != c->frame && (best < 0 || (c->slot[best].n && (!s->n || s->use < c->slot[best].use))))
            best = (int)i;
    }
    if (best < 0) {
        c->full++;
        return -1;
    }
    {
        KH1PalSlot *s = &c->slot[best];
        s->hash = h;
        s->n = n;
        s->frame = c->frame;
        s->use = c->use;
        for (i = 0; i < n; i++) s->col[i] = col[i];
    }
    c->misses++;
    *fill = 1;
    return best;
}

/* A port's palette cache keyed by the CLUT entries loaded (include/platform/palcache.h,
 * docs/renderer-spec.md 4.13 "Session 116"), checked by tests/host/palcache_test.c on 4.13
 * "Session 115"'s cases.  Not part of the PS2 build (it lives outside src/). */
#include "common.h"
#include "platform/palcache.h"

void *memset(void *, int, __SIZE_TYPE__);

/* session 146: a word a step, not a byte (a multiply a byte, 1,024 for a 256-entry CLUT, was ~3% of the GS
 * worker in the Dive); the hash only picks the slots same() compares, so any good one does */
static u32 fnv(const u32 *col, u32 n) {
    u32 h = 2166136261u, i;
    for (i = 0; i < n; i++) {
        h = (h ^ col[i]) * 16777619u;
        h ^= h >> 15;
    }
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

/* session 147c: slot k to the front of the recent four */
static void recent(KH1PalCache *c, u32 k) {
    u32 i;
    for (i = 0; i < 3 && c->recent[i] != k; i++) ;
    for (; i > 0; i--) c->recent[i] = c->recent[i - 1];
    c->recent[0] = k;
}

int kh1_palcache_get(KH1PalCache *c, const u32 *col, u32 n, int *fill) {
    u32 h, i;
    int best = -1;
    *fill = 0;
    if (n != 16 && n != 256) return -1;
    /* session 147c: the title menu's text loads one of a few CLUTs before each of ~60 glyphs a frame: the slots the
     * last four gets answered are tried first, and a match is the hit the scan below would find (two slots never
     * hold the same entries: a fill comes only when no slot matched), without the hash and the 256 slots' scan */
    for (i = 0; i < 4; i++)
        if (c->recent[i] < KH1_PALCACHE_SLOTS && same(&c->slot[c->recent[i]], col, n)) {
            KH1PalSlot *s = &c->slot[c->recent[i]];
            int k = (int)c->recent[i];
            c->use++;
            s->frame = c->frame;
            s->use = c->use;
            c->hits++;
            recent(c, (u32)k);
            return k;
        }
    h = fnv(col, n);
    c->use++;
    for (i = 0; i < KH1_PALCACHE_SLOTS; i++) {
        KH1PalSlot *s = &c->slot[i];
        if (s->n && s->hash == h && same(s, col, n)) {
            s->frame = c->frame;
            s->use = c->use;
            c->hits++;
            recent(c, i);
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
    recent(c, (u32)best);
    return best;
}

void kh1_palcache_use(KH1PalCache *c, int slot) {
    if (slot < 0 || slot >= KH1_PALCACHE_SLOTS || !c->slot[slot].n) return;
    c->slot[slot].frame = c->frame;
    c->slot[slot].use = ++c->use;
}

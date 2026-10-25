/* A decoded-texture cache's key (renderer-spec 4.13 "Session 117", vita-port-plan 5.1be), tested on
 * host/null/gsmem.c's model with made-up texels (no game data): tests/selftest.sh builds it with gcc
 * -m32 when that works.  Three keys for the same cache, each checked against a fresh read at every
 * draw (a stale texture is a failure):
 *
 *   stamp   (TBP0, TBW, PSM, TW, TH) and kh1_gsmem_tex_stamp: the newest write to the pages the
 *           texture covers.  No texel is read on a hit; any write to one of its pages is a miss.
 *   bytes   (TBP0, TBW, PSM, TW, TH) and a hash of the stored texels: every draw reads and hashes all
 *           of them; textures whose bytes came back (a re-upload, a scroll's cycle) hit.
 *   both    the stamp first; on a stamp miss the hash, and a decode only for bytes not seen.
 *
 * The texels are the stored values (indices for PSMT4 / PSMT8): the palette is the palette cache's
 * (host/port/palcache.c), so the CLUT is not in the key.  Two cases: renderer-spec 3.1's texture slot
 * `0x3600` rewritten per draw (the minigame timer's font and its icon, §4.9 "Session 115": hud.c
 * func_002393d8 uploads the font again at every timer draw), and a room texture under texanim's
 * scroll (§4.13 "The texture steps", gsmem_test's `scroll`) with a second texture in the same page. */
#include "common.h"
#include "../../host/null/gsmem.h"

int printf(const char *, ...);
void *memset(void *, int, __SIZE_TYPE__);

static int fails, checks;
#define CHECK(name, cond) do { checks++; if (!(cond)) { printf("texcache_test: %s\n", name); fails++; } } while (0)

#define ENTRIES 32
#define TEXELS (64 * 64)
enum { KEY_STAMP, KEY_BYTES, KEY_BOTH, KEYS };
static const char *key_name[KEYS] = { "stamp", "bytes", "both" };

typedef struct {
    u32 used, lo, hi, stamp, hash, age;
    u32 tex[TEXELS];
} Entry;
typedef struct {
    Entry e[ENTRIES];
    u32 age, draws, decodes, hashed; /* hashed: texels read to hash */
} Cache;
static Cache cache[KEYS];
static u32 fresh[TEXELS];

static u32 tex_w(u32 lo) { return 1u << (lo >> 26 & 15); }
static u32 tex_h(u32 lo, u32 hi) { return 1u << ((lo >> 30 | hi << 2) & 15); }

static void read_texels(u32 lo, u32 hi, u32 *out) {
    u32 w = tex_w(lo), h = tex_h(lo, hi), x, y;
    for (y = 0; y < h; y++)
        for (x = 0; x < w; x++) out[y * w + x] = kh1_gsmem_read_pixel(lo >> 20 & 63, lo & 0x3FFF, lo >> 14 & 63, x, y);
}

static u32 hash_texels(Cache *c, const u32 *t, u32 n) {
    u32 h = 2166136261u, i;
    for (i = 0; i < n; i++) h = (h ^ t[i]) * 16777619u;
    c->hashed += n;
    return h;
}

/* the cache's texture for this draw; lo / hi: TEX0 with the layout fields only */
static const u32 *draw_tex(int k, u32 lo, u32 hi) {
    Cache *c = &cache[k];
    u32 n = tex_w(lo) * tex_h(lo, hi), st = kh1_gsmem_tex_stamp(lo, hi), hash = 0, i;
    int hit = -1, old = 0;
    c->draws++;
    c->age++;
    read_texels(lo, hi, fresh); /* what a key would read to hash (counted only when it does) */
    for (i = 0; i < ENTRIES && k != KEY_BYTES; i++)
        if (c->e[i].used && c->e[i].lo == lo && c->e[i].hi == hi && c->e[i].stamp == st) { hit = (int)i; break; }
    if (hit < 0 && k != KEY_STAMP) {
        hash = hash_texels(c, fresh, n);
        for (i = 0; i < ENTRIES; i++)
            if (c->e[i].used && c->e[i].lo == lo && c->e[i].hi == hi && c->e[i].hash == hash) { hit = (int)i; break; }
        if (hit >= 0) c->e[hit].stamp = st; /* the bytes are back: the new stamp is this entry's */
    }
    if (hit < 0) {
        for (i = 1; i < ENTRIES; i++)
            if (!c->e[i].used || (c->e[old].used && c->e[i].age < c->e[old].age)) old = (int)i;
        hit = old;
        c->e[hit].used = 1;
        c->e[hit].lo = lo;
        c->e[hit].hi = hi;
        c->e[hit].stamp = st;
        c->e[hit].hash = k == KEY_STAMP ? 0 : hash;
        for (i = 0; i < n; i++) c->e[hit].tex[i] = fresh[i];
        c->decodes++;
    }
    c->e[hit].age = c->age;
    return c->e[hit].tex;
}

/* every key's draw, each checked against the fresh read */
static int stale;
static void draw(u32 lo, u32 hi) {
    int k;
    u32 n = tex_w(lo) * tex_h(lo, hi), i;
    for (k = 0; k < KEYS; k++) {
        const u32 *t = draw_tex(k, lo, hi);
        for (i = 0; i < n; i++)
            if (t[i] != fresh[i]) { stale++; break; }
    }
}

static void reset(void) {
    memset(cache, 0, sizeof cache);
    stale = 0;
    kh1_gsmem_reset();
}

/* an upload of w x h pixels in psm at block bp (BW bw), texel (x, y) = f(x, y, seed) */
static u32 words[TEXELS];
static void upload(u32 psm, u32 bp, u32 bw, u32 w, u32 h, u32 seed) {
    u32 x, y, i, n = 0;
    memset(words, 0, sizeof words);
    for (y = 0; y < h; y++)
        for (x = 0; x < w; x++, n++) {
            u32 v = (x * 5 + y * 3 + seed) * 2654435761u >> 24;
            if (psm == KH1_PSMT4) words[n >> 3] |= (v & 15) << (n & 7) * 4;
            else if (psm == KH1_PSMT8) words[n >> 2] |= (v & 0xFF) << (n & 3) * 8;
            else words[n] = v | v << 8 | v << 16 | 0x80000000u;
        }
    kh1_gsmem_trxdir(0, 0, bp | bw << 16 | psm << 24, 0, 0, w, h);
    n = psm == KH1_PSMT4 ? (n + 7) / 8 : psm == KH1_PSMT8 ? (n + 3) / 4 : n;
    for (i = 0; i < n; i += 4) kh1_gsmem_image(words + i, 4);
}

/* texanim.nostrict.c func_00101a70's two local->local copies at step y (as gsmem_test's scroll): the
 * 16 x 8 CT32 sheet at 0x2800 to 0x2900, rotated up by y rows; at y 0 both are 0 rows high */
static void scroll(u32 y) {
    u32 h = 8, m1 = y % h, m2 = (h - y) % h;
    u32 bb_lo = 0x2800 | 1 << 16 | KH1_PSMCT32 << 24, bb_hi = 0x2900 | 1 << 16 | KH1_PSMCT32 << 24;
    kh1_gsmem_trxdir(2, bb_lo, bb_hi, m1 << 16, 0, 16, m2);
    if (y) kh1_gsmem_trxdir(2, bb_lo, bb_hi, 0, m2 << 16, 16, y);
}

static void report(const char *name) {
    int k;
    for (k = 0; k < KEYS; k++)
        printf("texcache_test: %s, %s key: %u draws, %u decodes, %u texels hashed\n", name, key_name[k],
               cache[k].draws, cache[k].decodes, cache[k].hashed);
}

#define TEX0(bp, bw, psm, tw, th) ((u32)(bp) | (u32)(bw) << 14 | (u32)(psm) << 20 | (u32)(tw) << 26 | (u32)(th) << 30)
#define TEX0_HI(th) ((u32)(th) >> 2)

int main(void) {
    u32 f, y, step;

    /* (1) the 0x3600 slot, three frames: the timer's font (PSMT4 64 x 64, BW 1) uploaded and drawn,
     * then its icon (PSMT4 32 x 32) uploaded over it and drawn; the same bytes every frame */
    reset();
    for (f = 0; f < 3; f++) {
        upload(KH1_PSMT4, 0x3600, 1, 64, 64, 1);
        draw(TEX0(0x3600, 1, KH1_PSMT4, 6, 6), TEX0_HI(6));
        upload(KH1_PSMT4, 0x3600, 1, 32, 32, 2);
        draw(TEX0(0x3600, 1, KH1_PSMT4, 5, 5), TEX0_HI(5));
    }
    report("0x3600 slot");
    CHECK("slot: no stale texture", stale == 0);
    CHECK("slot: the stamp decodes every draw", cache[KEY_STAMP].decodes == 6 && cache[KEY_STAMP].hashed == 0);
    CHECK("slot: the bytes decode each picture once", cache[KEY_BYTES].decodes == 2 &&
          cache[KEY_BYTES].hashed == 3 * (64 * 64 + 32 * 32));
    CHECK("slot: both: the bytes' decodes, a hash every draw", cache[KEY_BOTH].decodes == 2 &&
          cache[KEY_BOTH].hashed == cache[KEY_BYTES].hashed);

    /* (1b) the same slot drawn twice per upload (the timer's three fonts: one upload, CSA 0 / 2 / 6) */
    reset();
    for (f = 0; f < 3; f++) {
        upload(KH1_PSMT4, 0x3600, 1, 64, 64, 1);
        draw(TEX0(0x3600, 1, KH1_PSMT4, 6, 6), TEX0_HI(6));
        draw(TEX0(0x3600, 1, KH1_PSMT4, 6, 6), TEX0_HI(6));
        draw(TEX0(0x3600, 1, KH1_PSMT4, 6, 6), TEX0_HI(6));
    }
    report("0x3600 slot, three draws an upload");
    CHECK("slot x3: no stale texture", stale == 0);
    CHECK("slot x3: the stamp decodes once an upload", cache[KEY_STAMP].decodes == 3);
    CHECK("slot x3: both: one decode, a hash an upload", cache[KEY_BOTH].decodes == 1 &&
          cache[KEY_BOTH].hashed == 3 * 64 * 64 && cache[KEY_BYTES].hashed == 9 * 64 * 64);

    /* (2) texanim's scroll: the 16 x 8 destination at 0x2900 and a 16 x 8 room texture at 0x2902 (the
     * same page, other blocks), both drawn each step, two cycles of 8 steps (y 1 .. 7, 0) */
    reset();
    for (y = 0; y < 8; y++) {
        u32 x;
        for (x = 0; x < 16; x++) kh1_gsmem_write_pixel(KH1_PSMCT32, 0x2800, 1, x, y, y << 8 | x | 0x80000000u);
    }
    upload(KH1_PSMCT32, 0x2900, 1, 16, 8, 7);
    upload(KH1_PSMCT32, 0x2902, 1, 16, 8, 9);
    for (step = 1; step <= 16; step++) {
        scroll(step % 8);
        draw(TEX0(0x2900, 1, KH1_PSMCT32, 4, 3), TEX0_HI(3));
        draw(TEX0(0x2902, 1, KH1_PSMCT32, 4, 3), TEX0_HI(3));
    }
    report("texanim scroll");
    CHECK("scroll: no stale texture", stale == 0);
    /* the stamp: 14 steps copy (y 0 copies nothing), and each also invalidates the page's neighbour */
    CHECK("scroll: the stamp decodes both at every copying step", cache[KEY_STAMP].decodes == 28);
    /* the bytes: the destination's 7 rotations seen (y 0 keeps y 7's rows) once each, the neighbour once */
    CHECK("scroll: the bytes decode each rotation once", cache[KEY_BYTES].decodes == 8 &&
          cache[KEY_BYTES].hashed == 32 * 16 * 8);
    CHECK("scroll: both: the bytes' decodes, hashing only after a write", cache[KEY_BOTH].decodes == 8 &&
          cache[KEY_BOTH].hashed == 28 * 16 * 8);

    if (fails) { printf("texcache_test: %d of %d failed\n", fails, checks); return 1; }
    printf("texcache_test: PASS (%d checks)\n", checks);
    return 0;
}

/* host/port/palcache.c, the port's palette cache (include/platform/palcache.h), on renderer-spec 4.13
 * "Session 115"'s cases with made-up colours (no game data), the CLUTs uploaded into and loaded from
 * host/null/gsmem.c's model the way the game's packets do: tests/selftest.sh builds it with gcc -m32
 * when that works. */
#include "common.h"
#include "platform/palcache.h"
#include "../../host/null/gsmem.h"

int printf(const char *, ...);

static int fails, checks;
#define CHECK(name, cond) do { checks++; if (!(cond)) { printf("palcache_test: %s\n", name); fails++; } } while (0)

static KH1PalCache pc;
static u32 words[256], pal[256];

/* a CT32 CLUT of w x h (16 x 16 for 256 colours, 8 x 2 for 16) at block bp, colour i = base + i */
static void upload_clut(u32 bp, u32 w, u32 h, u32 base) {
    u32 i;
    for (i = 0; i < w * h; i++) words[i] = base + i;
    kh1_gsmem_trxdir(0, 0, bp | 1u << 16 | (u32)KH1_PSMCT32 << 24, 0, 0, w, h);
    for (i = 0; i < w * h; i += 4) kh1_gsmem_image(words + i, 4);
}

/* a TEX0 for a PSMT8 or PSMT4 texture, CPSM CT32, CSA csa, that loads the CLUT at cbp (CLD 1; CLD 0
 * with cld 0: the buffer as the last load left it); then the palette the draw reads, through the cache */
static int draw_cld(u32 psm, u32 cbp, u32 csa, u32 cld, int *fill) {
    u32 lo = (u32)psm << 20 | 4u << 26, hi = cbp << 5 | csa << 24 | cld << 29, n;
    kh1_gsmem_tex0(lo, hi);
    n = (u32)kh1_gsmem_clut(lo, hi, 0, 0, pal);
    return kh1_palcache_get(&pc, pal, n, fill);
}
static int draw(u32 psm, u32 cbp, u32 csa, int *fill) { return draw_cld(psm, cbp, csa, 1, fill); }

int main(void) {
    int a, b, c, d, f, f2, i, s;
    u32 n;

    kh1_gsmem_reset();
    kh1_palcache_init(&pc);

    /* kh1_gsmem_clut: an 8-bit CLUT's entries 8-15 / 16-23 swapped (CSM 1), a 4-bit one's CSA */
    upload_clut(0x3700, 16, 16, 0x1000);
    kh1_gsmem_tex0(KH1_PSMT8 << 20, 0x3700 << 5 | 1u << 29);
    n = (u32)kh1_gsmem_clut(KH1_PSMT8 << 20, 0x3700 << 5, 0, 0, pal);
    CHECK("clut: 256, swizzle", n == 256 && pal[0] == 0x1000 && pal[8] == 0x1010 && pal[16] == 0x1008 &&
          pal[255] == 0x10FF);
    CHECK("clut: not indexed", kh1_gsmem_clut(KH1_PSMCT32 << 20, 0, 0, 0, pal) == 0);

    /* (1) renderer B's 0x3700: two model records, two palettes in one block in one frame */
    upload_clut(0x3700, 16, 16, 0x10000);
    a = draw(KH1_PSMT8, 0x3700, 0, &f);
    CHECK("0x3700: record 1 filled", a >= 0 && f == 1);
    upload_clut(0x3700, 16, 16, 0x20000);
    b = draw(KH1_PSMT8, 0x3700, 0, &f);
    CHECK("0x3700: record 2 its own slot", b >= 0 && b != a && f == 1 && pc.slot[b].col[0] == 0x20000);
    kh1_palcache_frame(&pc);
    upload_clut(0x3700, 16, 16, 0x10000);
    CHECK("0x3700: record 1 next frame hits", draw(KH1_PSMT8, 0x3700, 0, &f) == a && f == 0);
    upload_clut(0x3700, 16, 16, 0x20000);
    CHECK("0x3700: record 2 next frame hits", draw(KH1_PSMT8, 0x3700, 0, &f) == b && f == 0);

    /* (2) the timer's 0x3A00: the window font's 256 colours, then its icon's 16, same block, one frame */
    kh1_palcache_frame(&pc);
    upload_clut(0x3A00, 16, 16, 0x30000);
    c = draw(KH1_PSMT8, 0x3A00, 0, &f);
    upload_clut(0x3A00, 8, 2, 0x40000);
    d = draw(KH1_PSMT4, 0x3A00, 0, &f2);
    CHECK("0x3A00: font then icon, two slots", c >= 0 && d >= 0 && c != d && f == 1 && f2 == 1 &&
          pc.slot[d].n == 16 && pc.slot[d].col[15] == 0x4000F);
    upload_clut(0x3A00, 16, 16, 0x30000);
    CHECK("0x3A00: the font again hits", draw(KH1_PSMT8, 0x3A00, 0, &f) == c && f == 0);
    /* a 4-bit draw's CSA: a 256-colour load fills every 16-entry slot, then CLD 0 draws at CSA 0 and 1
     * read two palettes (a 4-bit load itself always reads the 8 x 2 at CBP's origin) */
    upload_clut(0x3A00, 16, 16, 0x50000);
    draw(KH1_PSMT8, 0x3A00, 0, &f);
    a = draw_cld(KH1_PSMT4, 0x3A00, 0, 0, &f);
    b = draw_cld(KH1_PSMT4, 0x3A00, 1, 0, &f2);
    CHECK("CSA 0 / 1: two slots", a >= 0 && b >= 0 && a != b && pc.slot[a].col[0] == 0x50000 &&
          pc.slot[b].col[0] == 0x50008);

    /* (3) a room CLUT (0x3E00) the cross-fade changes between frames, no load: a new key that frame */
    kh1_palcache_frame(&pc);
    upload_clut(0x3E00, 16, 16, 0x60000);
    a = draw(KH1_PSMT8, 0x3E00, 0, &f);
    kh1_palcache_frame(&pc);
    CHECK("room: unchanged hits", draw(KH1_PSMT8, 0x3E00, 0, &f) == a && f == 0);
    kh1_palcache_frame(&pc);
    kh1_gsmem_write_pixel(KH1_PSMCT32, 0x3E00, 1, 3, 0, 0x00FF00FF); /* texanim's blend into entry 3 */
    b = draw(KH1_PSMT8, 0x3E00, 0, &f);
    CHECK("room: blended entry is a miss", b >= 0 && b != a && f == 1 && pc.slot[b].col[3] == 0x00FF00FF);
    CHECK("room: the old palette kept", pc.slot[a].col[3] == 0x60003);

    /* (4) the window font's boot CLUT (0x3DFC) overwritten by a shadow window, re-sent: the old slot */
    kh1_palcache_frame(&pc);
    upload_clut(0x3DFC, 16, 16, 0x70000);
    a = draw(KH1_PSMT8, 0x3DFC, 0, &f);
    for (i = 0; i < 16; i++) kh1_gsmem_write_pixel(KH1_PSMCT32, 0x3DFC, 1, (u32)i, 5, 0xDEAD0000u + (u32)i);
    b = draw(KH1_PSMT8, 0x3DFC, 0, &f); /* the PS2 would read the shadow here; the game re-sends first */
    CHECK("0x3DFC: overwritten reads differently", b >= 0 && b != a);
    upload_clut(0x3DFC, 16, 16, 0x70000);
    CHECK("0x3DFC: re-sent hits the boot slot", draw(KH1_PSMT8, 0x3DFC, 0, &f) == a && f == 0);

    /* eviction: the least recently used slot of an earlier frame; a full frame draws uncached */
    kh1_palcache_init(&pc);
    for (i = 0; i < KH1_PALCACHE_SLOTS; i++) {
        for (n = 0; n < 16; n++) pal[n] = (u32)i << 8 | n;
        s = kh1_palcache_get(&pc, pal, 16, &f);
        if (s != i || f != 1) break;
    }
    CHECK("fill: every slot", i == KH1_PALCACHE_SLOTS && pc.misses == KH1_PALCACHE_SLOTS);
    for (n = 0; n < 16; n++) pal[n] = 0xAB00 | n;
    CHECK("full frame: -1", kh1_palcache_get(&pc, pal, 16, &f) == -1 && f == 0 && pc.full == 1);
    kh1_palcache_frame(&pc);
    for (n = 0; n < 16; n++) pal[n] = n; /* palette 0, used again: now the most recent */
    CHECK("next frame: palette 0 hits", kh1_palcache_get(&pc, pal, 16, &f) == 0 && f == 0);
    for (n = 0; n < 16; n++) pal[n] = 0xAB00 | n;
    CHECK("next frame: evicts the least recent (1)", kh1_palcache_get(&pc, pal, 16, &f) == 1 && f == 1);
    for (n = 0; n < 16; n++) pal[n] = 1u << 8 | n;
    CHECK("evicted palette is a miss", kh1_palcache_get(&pc, pal, 16, &f) == 2 && f == 1);
    CHECK("bad count", kh1_palcache_get(&pc, pal, 17, &f) == -1);

    printf("palcache_test: %d checks, %s\n", checks, fails ? "FAIL" : "PASS");
    return fails != 0;
}

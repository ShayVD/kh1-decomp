/* GS local memory on the host (docs/renderer-spec.md 5.2), the third step of the Vita's GIF parser
 * after host/null/dmawalk.c's packet reader and host/null/gsregs.c's register file: 4 MB laid out
 * the way the GS lays out each pixel storage mode (pages of 8 KB, 32 blocks of 256 bytes a page, the
 * columns inside a block), written by the uploads (TRXDIR 0 then the IMAGE data) and the
 * local->local copies, and read back as RGBA8 for a TEX0: the texture cache the Vita renderer needs.
 *
 * The swizzles are written as bit formulas, not tables: CT32's pixel inside a block takes x's bits 0,
 * 1, 2 and y's bits 0, 1-2 in the order x0 y0 x1 x2 y1 y2; T8 and T4 read the same word order with
 * every other row pair's halves swapped (the "column" swap of each 4-row group), the byte / nibble in
 * the word from x's bit 3 (and 4) and y's bit 1.  PSMCT24, PSMT8H, PSMT4HL and PSMT4HH share CT32's
 * addresses: CT24 writes the low 24 bits, T8H the top byte, T4HL / T4HH its two nibbles, so the
 * message font in the Z buffer's top byte (renderer-spec 5.1) leaves the Z bits alone.  PSMCT16S
 * orders a page's blocks y0 x0 y2 y1 x1 (CT16's columns inside each).  The Z formats (session 82)
 * are their colour twin (Z32 / Z24 CT32's, Z16 CT16's, Z16S CT16S's) with the final block number
 * XORed with 0x18: a page's four block quarters swap diagonally, so a CT24 read of a Z24 buffer
 * sees its blocks in another order.  Not modelled: CSM 1 (TEXCLUT), local->host.
 *
 * The CLUT buffer is the GS's: 512 halfwords, a CT32 entry e in halfwords e and e + 256, a CT16 entry
 * in one; a 4-bit CLUT loads 16 entries at CSA * 16 (an 8 x 2 rectangle), an 8-bit one 256 at 0 (16 x
 * 16, entries 8-15 and 16-23 of each 32 swapped; an 8-bit CLUT with CSA not 0 is not modelled); CLD
 * decides at each TEX0 / TEX2 write whether to load.  Checked against PCSX2's swizzle and CLUT
 * tables in session 80 (every pixel of a page in each of the four orders, outside the repo); the
 * CT16S block order and the Z formats' XOR against PCSX2's GSTables.cpp / GSLocalMemory.h (its
 * swizzle32Z / 16Z / 16SZ: the colour tables with a block XOR of 0x18) in session 82.
 * Fed, like gsregs.c, only while KH1_HOST_TRACE >= 2 walks the chains. */
#include "common.h"
#include "gsmem.h"
#include "bytesame.h"

void *memset(void *, int, __SIZE_TYPE__);
void *memcpy(void *, const void *, __SIZE_TYPE__);
void *malloc(__SIZE_TYPE__);

#define VM_BYTES (4u << 20)
#define LOG 256
#define TARGETS 32

static u8 vm[VM_BYTES];
/* session 142: the pages any store reached since the last kh1_gsmem_snap_take (stored bits changed or not,
 * the drawn sprites' pixels too), so the snapshot copies only those */
static u8 dirty_pg[512];
/* session 146: seq at the last store into each page (bytes changed or not; a draw's mark alone is not one) */
static u32 wr_pg[512];
#define STORED(pg) (dirty_pg[(pg) & 511] = 1, wr_pg[(pg) & 511] = seq)
static u16 clut[512];
/* session 147c: the kept entries (clut_kept) the last load wrote into the CLUT buffer and how (CPSM, 8-bit, CSA): a
 * load that finds the same entries kept and loads them the same way would store what the buffer already holds */
static const u32 *clut_done;
static u32 clut_done_how;
static u32 clut_ver = 1; /* session 147c: moved by every load that stores into the buffer, and by a reset */
static u32 cbp0, cbp1;
static u32 seq, page_seq[512], clut_seq;
static KH1GsMemStats st;
static KH1GsUpload log_[LOG];
static u32 nlog;
static KH1GsTarget tgt[TARGETS];
static u32 ntgt, useq, tgt_useq[TARGETS]; /* useq counts uploads, copies and pixel writes; tgt_useq: its
                                            * value when the target's pages were last marked */
static u32 page_drawn[512];          /* the word bits a draw changed and no upload wrote since */
static int flat_on, flat_raw;        /* session 95: kh1_gsmem_flat's switch; a flat sprite's writes in progress */
static u8 page_tgt[512];             /* 1 + the target that drew there last */
static u32 marks;                    /* session 135: moves with page_seq / page_drawn / page_tgt (tex_scan's memo) */

/* the transfer in progress */
static struct {
    u32 active, psm, bp, bw, x0, y0, w, h, x, y;
    u32 acc, nacc, bytes; /* the pixel being assembled, its bytes so far, bytes a pixel (0: 4 bits) */
    KH1GsUpload *log;
    const u32 *at; u32 ai; /* session 135: the pixels' addresses (trx_addrs), 0 for none; the next's */
    int key;               /* session 137: their at_key entry, -1 for none */
} trx;

/* Session 135: an upload's addresses kept (the title uploads the same rectangles, ~800,000 pixels,
 * every frame: kh1_gsmem_addr's swizzle per pixel was a fifth of the frame), each pixel's in the
 * transfer's order; the store starts again when full */
#define AT_POOL (1u << 20)
#define AT_KEYS 256 /* session 141: 64 ran out on the late menu page, every upload then a miss */
static u32 at_pool[AT_POOL], at_used, at_n;
/* session 137: with each, the bytes the last whole upload there brought (dlen 0: none) at doff in
 * same_pool, seq when it ended and the pages the rectangle spans (kh1_gsmem_image_same) */
static struct { u32 psm, bp, bw, x, y, w, h, off, doff, dlen, stamp, plo, phi, pg[16]; } at_key[AT_KEYS];
/* session 146: pg, the pages the rectangle's pixels lie in (bit p of pg[p >> 5]) */
#define SAME_POOL (4u << 20)
static u8 same_pool[SAME_POOL] __attribute__((aligned(16))); /* session 147: each run at 16 (bytesame.h) */
static u32 same_used;
static const u32 *trx_addrs(u32 psm, u32 bp, u32 bw, u32 x0, u32 y0, u32 w, u32 h);

void kh1_gsmem_reset(void) {
    u32 i;
    memset(vm, 0, sizeof vm);
    memset(dirty_pg, 1, sizeof dirty_pg);
    memset(wr_pg, 0, sizeof wr_pg);
    memset(clut, 0, sizeof clut);
    memset(page_seq, 0, sizeof page_seq);
    memset(&st, 0, sizeof st);
    memset(&trx, 0, sizeof trx);
    memset(tgt, 0, sizeof tgt);
    memset(page_drawn, 0, sizeof page_drawn);
    memset(page_tgt, 0, sizeof page_tgt);
    marks++;
    for (i = 0; i < AT_KEYS; i++) at_key[i].dlen = 0; /* the pages' stamps start again at 0 */
    same_used = 0;
    cbp0 = cbp1 = clut_seq = nlog = ntgt = useq = 0;
    clut_done = 0; /* session 147c: the buffer is cleared */
    clut_ver++;
    /* session 118: seq goes on counting, so a texture cache's stamp from before a reset is never one
     * after it (the pages start again at 0, which only memory never written since a reset has) */
    seq++;
}

const KH1GsMemStats *kh1_gsmem_stats(void) { return &st; }
u32 kh1_gsmem_clut_stamp(void) { return clut_seq; }

int kh1_gsmem_log(KH1GsUpload *out, int max) {
    int i;
    for (i = 0; i < (int)nlog && i < max; i++) out[i] = log_[i];
    return nlog;
}

void kh1_gsmem_clear_log(void) {
    u32 i;
    nlog = 0;
    trx.log = 0;
    for (i = 0; i < ntgt; i++) tgt[i].sent = 0;
}

/* a pixel inside a CT32 block (x, y 0-7): x0 y0 x1 x2 y1 y2 */
static u32 col32(u32 x, u32 y) { return (x & 1) | (y & 1) << 1 | (x & 6) << 1 | (y & 6) << 3; }
/* a block inside a page, CT32 / T8 (8 x 4 blocks: x0 y0 x1 y1 x2) and CT16 / T4 (4 x 8: y0 x0 y1 x1 y2) */
static u32 blk32(u32 x, u32 y) { return (x & 1) | (y & 1) << 1 | (x & 2) << 1 | (y & 2) << 2 | (x & 4) << 2; }
static u32 blk16(u32 x, u32 y) { return (y & 1) | (x & 1) << 1 | (y & 2) << 1 | (x & 2) << 2 | (y & 4) << 2; }
/* CT16S / Z16S (4 x 8: y0 x0 y2 y1 x1) */
static u32 blk16s(u32 x, u32 y) { return (y & 1) | (x & 1) << 1 | (y & 4) | (y & 2) << 2 | (x & 2) << 3; }

/* the word of a T8 / T4 block row (by 0-15) and column x (0-7): CT32's order on 8 rows of words,
 * the halves swapped in rows 2-3 of even 4-row groups and 0-1 of odd ones */
static u32 col8w(u32 x, u32 by) {
    u32 swap = (by >> 1 ^ by >> 2) & 1;
    return col32((x & 7) ^ swap << 2, (by >> 2) * 2 + (by & 1));
}

/* the Z formats' final block XOR (0 for the colour ones) */
static u32 zxor(u32 psm) { return (psm & 0x30) == 0x30 ? 0x18 : 0; }

u32 kh1_gsmem_addr(u32 psm, u32 bp, u32 bw, u32 x, u32 y) {
    u32 b;
    x &= 2047;
    y &= 2047;
    switch (psm) {
    case KH1_PSMCT32: case KH1_PSMCT24: case KH1_PSMT8H: case KH1_PSMT4HL: case KH1_PSMT4HH:
    case KH1_PSMZ32: case KH1_PSMZ24:
        b = (bp + (y >> 5) * bw * 32 + (x >> 6) * 32 + blk32(x >> 3 & 7, y >> 3 & 3)) ^ zxor(psm);
        return (b & 0x3FFF) * 64 + col32(x & 7, y & 7);
    case KH1_PSMCT16: case KH1_PSMCT16S: case KH1_PSMZ16: case KH1_PSMZ16S:
        b = bp + (y >> 6) * bw * 32 + (x >> 6) * 32;
        b += (psm & 8 ? blk16s : blk16)(x >> 4 & 3, y >> 3 & 7);
        b ^= zxor(psm);
        return (b & 0x3FFF) * 128 + ((x >> 3 & 1) | (x & 1) << 1 | (y & 1) << 2 | (x & 6) << 2 | (y & 6) << 4);
    case KH1_PSMT8:
        b = bp + (y >> 6) * (bw >> 1) * 32 + (x >> 7) * 32 + blk32(x >> 4 & 7, y >> 4 & 3);
        return (b & 0x3FFF) * 256 + col8w(x, y & 15) * 4 + (x >> 3 & 1) * 2 + (y >> 1 & 1);
    case KH1_PSMT4:
        b = bp + (y >> 7) * (bw >> 1) * 32 + (x >> 7) * 32 + blk16(x >> 5 & 3, y >> 4 & 7);
        return (b & 0x3FFF) * 512 + col8w(x, y & 15) * 8 + (x >> 3 & 3) * 2 + (y >> 1 & 1);
    }
    return ~0u;
}

/* session 135: a whole word as rd32 / wr32 read and write it, in one access on a little-endian host
 * (the PS2, x86 and the Vita all are); no page mark */
static u32 ld32(u32 w) {
#if defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    u32 v;
    __builtin_memcpy(&v, vm + w * 4, 4);
    return v;
#else
    const u8 *p = vm + w * 4;
    return p[0] | p[1] << 8 | p[2] << 16 | (u32)p[3] << 24;
#endif
}
static void st32(u32 w, u32 v) {
    STORED(w >> 11);
#if defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    __builtin_memcpy(vm + w * 4, &v, 4);
#else
    u8 *p = vm + w * 4;
    p[0] = v; p[1] = v >> 8; p[2] = v >> 16; p[3] = v >> 24;
#endif
}
static u32 rd32(u32 w) { const u8 *p = vm + w * 4; return p[0] | p[1] << 8 | p[2] << 16 | (u32)p[3] << 24; }
/* a write into page pg: the bits no longer a draw's, and the page's stamp moved when the stored bits
 * changed.  Session 135: the same bits again keep the stamp (the title uploads every texture and CLUT
 * again each frame, the same bytes; a texture's stamp, kh1_gsmem_tex_stamp, then stays and the
 * present's cache hits without reading the texels back: docs/vita-build.md "Speed") */
static void mark(u32 pg, int changed, u32 bits) {
    if (changed) page_seq[pg] = seq;
    else if (!(page_drawn[pg] & bits)) return;
    page_drawn[pg] &= ~bits;
    marks++;
}
/* bits: the word bits the write stores, no longer a draw's */
static void wr32(u32 w, u32 v, u32 bits) {
    u32 o = ld32(w);
    st32(w, v);
    if (flat_raw) return; /* a flat sprite's pixels stay the draw's (kh1_gsmem_flat_sprite) */
    mark(w >> 11, o != v, bits);
}

/* a pixel's stored bits at address a (kh1_gsmem_addr's units for the PSM), in memory m (the model's, or the
 * frame copy's: session 146) */
static u32 at_in(const u8 *m, u32 psm, u32 a) {
    switch (psm) {
    case KH1_PSMCT32: case KH1_PSMZ32: case KH1_PSMCT24: case KH1_PSMZ24:
    case KH1_PSMT8H: case KH1_PSMT4HL: case KH1_PSMT4HH: {
        const u8 *p = m + a * 4;
        u32 w = p[0] | p[1] << 8 | p[2] << 16 | (u32)p[3] << 24;
        switch (psm) {
        case KH1_PSMCT24: case KH1_PSMZ24: return w & 0xFFFFFF;
        case KH1_PSMT8H: return w >> 24;
        case KH1_PSMT4HL: return w >> 24 & 15;
        case KH1_PSMT4HH: return w >> 28;
        }
        return w;
    }
    case KH1_PSMCT16: case KH1_PSMCT16S: case KH1_PSMZ16: case KH1_PSMZ16S: return m[a * 2] | m[a * 2 + 1] << 8;
    case KH1_PSMT8:   return m[a];
    case KH1_PSMT4:   return m[a >> 1] >> (a & 1) * 4 & 15;
    }
    return 0;
}
static u32 read_at(u32 psm, u32 a) { return at_in(vm, psm, a); }

u32 kh1_gsmem_read_pixel(u32 psm, u32 bp, u32 bw, u32 x, u32 y) {
    return read_at(psm, kh1_gsmem_addr(psm, bp, bw, x, y));
}

static void put_at(u32 psm, u32 a, u32 v) {
    switch (psm) {
    case KH1_PSMCT32: case KH1_PSMZ32: wr32(a, v, ~0u); return;
    case KH1_PSMCT24: case KH1_PSMZ24: wr32(a, (rd32(a) & 0xFF000000u) | (v & 0xFFFFFF), 0x00FFFFFF); return;
    case KH1_PSMT8H:  wr32(a, (rd32(a) & 0x00FFFFFF) | v << 24, 0xFF000000u); return;
    case KH1_PSMT4HL: wr32(a, (rd32(a) & 0xF0FFFFFFu) | (v & 15) << 24, 0x0F000000); return;
    case KH1_PSMT4HH: wr32(a, (rd32(a) & 0x0FFFFFFF) | v << 28, 0xF0000000u); return;
    /* the 16-, 8- and 4-bit layouts do not share CT32's word: the page is no longer a draw's */
    case KH1_PSMCT16: case KH1_PSMCT16S: case KH1_PSMZ16: case KH1_PSMZ16S: {
        u32 o = vm[a * 2] | vm[a * 2 + 1] << 8;
        vm[a * 2] = v; vm[a * 2 + 1] = v >> 8;
        STORED(a >> 12);
        if (!flat_raw) mark(a >> 12, o != (v & 0xFFFF), ~0u);
        return;
    }
    case KH1_PSMT8: {
        u32 o = vm[a];
        vm[a] = v;
        STORED(a >> 13);
        mark(a >> 13, o != (v & 0xFF), ~0u);
        return;
    }
    case KH1_PSMT4: {
        u32 o = vm[a >> 1];
        vm[a >> 1] = (o & (0xF0 >> (a & 1) * 4)) | (v & 15) << (a & 1) * 4;
        STORED(a >> 14);
        mark(a >> 14, o != vm[a >> 1], ~0u);
        return;
    }
    }
}

static void put(u32 psm, u32 bp, u32 bw, u32 x, u32 y, u32 v) { put_at(psm, kh1_gsmem_addr(psm, bp, bw, x, y), v); }

/* Session 135 (the Vita's speed, docs/vita-build.md "Speed"): a rectangle's addresses as a column part
 * plus a row part, so the sprites and the present compute two short tables instead of the swizzle for
 * every pixel.  The CT32 / CT16 / CT16S layouts' block and in-block numbers are fields of x's and y's
 * bits that do not overlap, so kh1_gsmem_addr(x, y) = cx[x - x0] + ry[y - y0] as long as the block
 * number does not wrap at 0x4000.  0 (the caller uses kh1_gsmem_addr) for T8 / T4 (their word order
 * swaps by row), the Z formats (the block XOR), a wrap, or under kh1_gsmem_fast(0), which the tests use
 * to compare (tests/host/gsfast_test.c). */
static int fast_on = 1;
void kh1_gsmem_fast(int on) { fast_on = on; }

/* slot: which pair of tables (SPLIT_*), each keeping the rectangle it holds: the frame copy's 16 strips
 * read one texture, the present one buffer, every frame */
enum { SPLIT_FRAME, SPLIT_TEX, SPLIT_RECT, SPLIT_SNAP, SPLITS }; /* SPLIT_SNAP: the copy's reader */
static struct { u32 psm, bp, bw; s32 x0, x1, y0, y1; int ok; } split_had[SPLITS];
static int addr_split(int slot, u32 psm, u32 bp, u32 bw, s32 x0, s32 x1, s32 y0, s32 y1, u32 *cx, u32 *ry) {
    u32 a0, bmax;
    s32 i;
    if (split_had[slot].ok && fast_on && split_had[slot].psm == psm && split_had[slot].bp == bp &&
        split_had[slot].bw == bw && split_had[slot].x0 == x0 && split_had[slot].x1 == x1 &&
        split_had[slot].y0 == y0 && split_had[slot].y1 == y1)
        return 1;
    split_had[slot].ok = 0;
    if (!fast_on || x0 < 0 || y0 < 0 || x1 <= x0 || y1 <= y0 || x1 > 2048 || y1 > 2048) return 0;
    switch (psm) {
    case KH1_PSMCT32: case KH1_PSMCT24: case KH1_PSMT8H: case KH1_PSMT4HL: case KH1_PSMT4HH:
        bmax = bp + ((u32)(y1 - 1) >> 5) * bw * 32 + ((u32)(x1 - 1) >> 6) * 32 + 31;
        break;
    case KH1_PSMCT16: case KH1_PSMCT16S:
        bmax = bp + ((u32)(y1 - 1) >> 6) * bw * 32 + ((u32)(x1 - 1) >> 6) * 32 + 31;
        break;
    default:
        return 0;
    }
    if (bmax > 0x3FFF) return 0;
    a0 = kh1_gsmem_addr(psm, bp, bw, x0, y0);
    for (i = 0; i < x1 - x0; i++) cx[i] = kh1_gsmem_addr(psm, bp, bw, x0 + i, y0);
    for (i = 0; i < y1 - y0; i++) ry[i] = kh1_gsmem_addr(psm, bp, bw, x0, y0 + i) - a0;
    split_had[slot].psm = psm; split_had[slot].bp = bp; split_had[slot].bw = bw;
    split_had[slot].x0 = x0; split_had[slot].x1 = x1; split_had[slot].y0 = y0; split_had[slot].y1 = y1;
    split_had[slot].ok = 1;
    return 1;
}

/* a word of memory m as ld32 reads the model's */
static u32 ld32_in(const u8 *m, u32 w) {
#if defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    u32 v;
    __builtin_memcpy(&v, m + w * 4, 4);
    return v;
#else
    const u8 *p = m + w * 4;
    return p[0] | p[1] << 8 | p[2] << 16 | (u32)p[3] << 24;
#endif
}

/* T8 / T4's place inside a block by (x, y)'s low bits (the read_rect fast path's); made by the GS side's thread
 * (kh1_gsmem_read_rect, kh1_gsmem_snap_take) before the copy's readers on another thread use them */
static u16 in8[16][16], in4[16][32];
static int in_made;
static void in_tables(void) {
    u32 i, j;
    if (in_made) return;
    for (j = 0; j < 16; j++)
        for (i = 0; i < 32; i++) {
            if (i < 16) in8[j][i] = (u16)(col8w(i, j) * 4 + (i >> 3 & 1) * 2 + (j >> 1 & 1));
            in4[j][i] = (u16)(col8w(i, j) * 8 + (i >> 3 & 3) * 2 + (j >> 1 & 1));
        }
    in_made = 1;
}

/* kh1_gsmem_read_rect from memory m, with split slot `slot` and its tables cx / ry (one set a thread) */
static int rect_in(const u8 *m, int slot, u32 *cx, u32 *ry, u32 psm, u32 bp, u32 bw, u32 x0, u32 y0, u32 w, u32 h,
                   u32 *out, u32 stride) {
    u32 x, y;
    if (kh1_gsmem_addr(psm, 0, 1, 0, 0) == ~0u || x0 + w > 2048 || y0 + h > 2048) return -1;
    if (!w || !h) return 0;
    if (addr_split(slot, psm, bp, bw, (s32)x0, (s32)(x0 + w), (s32)y0, (s32)(y0 + h), cx, ry)) {
        for (y = 0; y < h; y++, out += stride) {
            u32 r = ry[y];
            if (psm == KH1_PSMCT32)
                for (x = 0; x < w; x++) out[x] = ld32_in(m, cx[x] + r);
            else if (psm == KH1_PSMCT24)
                for (x = 0; x < w; x++) out[x] = ld32_in(m, cx[x] + r) & 0xFFFFFF;
            else
                for (x = 0; x < w; x++) out[x] = at_in(m, psm, cx[x] + r);
        }
        return 0;
    }
    if (fast_on && (psm == KH1_PSMT8 || psm == KH1_PSMT4)) {
        /* session 137v (the real Vita's speed: the recorder decodes a few indexed textures a frame, a sixth
         * of a Dive frame pixel by pixel): T8 / T4 as kh1_gsmem_addr has them, the in-block part (it
         * depends on x's and y's low bits together, so no split) from a table, the block once per block */
        int t4 = psm == KH1_PSMT4;
        u32 bxs = t4 ? 5 : 4, bmask = (1u << bxs) - 1;
        in_tables();
        for (y = 0; y < h; y++, out += stride) {
            u32 yy = y0 + y, cbx = ~0u, base = 0;
            const u16 *row = t4 ? in4[yy & 15] : in8[yy & 15];
            for (x = 0; x < w; x++) {
                u32 xx = x0 + x, a;
                if (xx >> bxs != cbx) {
                    u32 b;
                    cbx = xx >> bxs;
                    if (t4) b = bp + (yy >> 7) * (bw >> 1) * 32 + (xx >> 7) * 32 + blk16(xx >> 5 & 3, yy >> 4 & 7);
                    else b = bp + (yy >> 6) * (bw >> 1) * 32 + (xx >> 7) * 32 + blk32(xx >> 4 & 7, yy >> 4 & 3);
                    base = (b & 0x3FFF) * (t4 ? 512 : 256);
                }
                a = base + row[xx & bmask];
                out[x] = t4 ? m[a >> 1] >> (a & 1) * 4 & 15 : m[a];
            }
        }
        return 0;
    }
    for (y = 0; y < h; y++, out += stride)
        for (x = 0; x < w; x++) out[x] = at_in(m, psm, kh1_gsmem_addr(psm, bp, bw, x0 + x, y0 + y));
    return 0;
}

int kh1_gsmem_read_rect(u32 psm, u32 bp, u32 bw, u32 x0, u32 y0, u32 w, u32 h, u32 *out, u32 stride) {
    static u32 cx[2048], ry[2048];
    return rect_in(vm, SPLIT_RECT, cx, ry, psm, bp, bw, x0, y0, w, h, out, stride);
}

void kh1_gsmem_read_block(u32 b, u32 *out) {
    u32 i;
    for (i = 0; i < 64; i++) out[i] = ld32((b & 0x3FFF) * 64 + i);
}

void kh1_gsmem_write_pixel(u32 psm, u32 bp, u32 bw, u32 x, u32 y, u32 v) {
    seq++;
    useq++;
    put(psm, bp, bw, x, y, v);
}

static int known(u32 psm) { return kh1_gsmem_addr(psm, 0, 1, 0, 0) != ~0u; }
static int bits16(u32 psm) { return psm == KH1_PSMCT16 || psm == KH1_PSMCT16S || psm == KH1_PSMZ16 || psm == KH1_PSMZ16S; }
/* the 8 KB page an address of kh1_gsmem_addr's lies in */
static u32 page_of(u32 psm, u32 a) {
    return (bits16(psm) ? a >> 12 : psm == KH1_PSMT8 ? a >> 13 : psm == KH1_PSMT4 ? a >> 14 : a >> 11) & 511;
}

/* bytes a pixel of an upload takes (0 for 4 bits), the unmodelled formats included so their data
 * is still counted off */
static u32 psm_bytes(u32 psm) {
    switch (psm) {
    case KH1_PSMCT32: case 0x30: return 4;
    case KH1_PSMCT24: case 0x31: return 3;
    case KH1_PSMCT16: case 0x0A: case 0x32: case 0x3A: return 2;
    case KH1_PSMT8: case KH1_PSMT8H: return 1;
    }
    return 0;
}

void (*kh1_gsmem_xfer_hook)(u32 dir, u32 bb_lo, u32 bb_hi, u32 pos_lo, u32 pos_hi, u32 reg_lo, u32 reg_hi);
void (*kh1_gsmem_clut_hook)(u32 lo, u32 hi);

void kh1_gsmem_trxdir(u32 dir, u32 bb_lo, u32 bb_hi, u32 pos_lo, u32 pos_hi, u32 reg_lo, u32 reg_hi) {
    u32 dpsm = bb_hi >> 24 & 63, dbp = bb_hi & 0x3FFF, dbw = bb_hi >> 16 & 63;
    u32 dx = pos_hi & 2047, dy = pos_hi >> 16 & 2047, w = reg_lo & 0xFFF, h = reg_hi & 0xFFF;
    KH1GsUpload *l = nlog < LOG ? &log_[nlog] : 0;
    trx.active = 0;
    trx.log = 0;
    trx.key = -1;
    dir &= 3;
    if (dir == 1) { st.unsupported++; return; }
    if (dir == 3) return;
    seq++;
    useq++;
    if (l) {
        nlog++;
        l->dir = dir; l->bp = dbp; l->bw = dbw; l->psm = dpsm;
        l->x = dx; l->y = dy; l->w = w; l->h = h; l->pixels = 0;
    }
    if (!known(dpsm)) st.unsupported++;
    if (dir == 0) {
        st.uploads++;
        trx.active = w && h;
        trx.psm = dpsm; trx.bp = dbp; trx.bw = dbw;
        trx.x0 = trx.x = dx; trx.y0 = trx.y = dy; trx.w = w; trx.h = h;
        trx.acc = trx.nacc = 0;
        trx.bytes = psm_bytes(dpsm);
        trx.log = l;
        trx.at = trx.active ? trx_addrs(dpsm, dbp, dbw, dx, dy, w, h) : 0;
        trx.ai = 0;
        if (kh1_gsmem_xfer_hook) kh1_gsmem_xfer_hook(dir, bb_lo, bb_hi, pos_lo, pos_hi, reg_lo, reg_hi);
        return;
    }
    /* local->local, in the pixel order TRXPOS.DIR gives (0 from the top left, 1 bottom left, 2 top
     * right, 3 bottom right), as the GS copies an overlap; each pixel's stored bits as they are */
    {
        u32 spsm = bb_lo >> 24 & 63, sbp = bb_lo & 0x3FFF, sbw = bb_lo >> 16 & 63;
        u32 sx = pos_lo & 2047, sy = pos_lo >> 16 & 2047, order = pos_hi >> 27 & 3, i, j;
        st.copies++;
        if (!known(spsm) || !known(dpsm)) {
            if (known(dpsm)) st.unsupported++;
            if (kh1_gsmem_xfer_hook) kh1_gsmem_xfer_hook(dir, bb_lo, bb_hi, pos_lo, pos_hi, reg_lo, reg_hi);
            return;
        }
        for (j = 0; j < h; j++) {
            u32 y = order & 1 ? h - 1 - j : j;
            for (i = 0; i < w; i++) {
                u32 x = order & 2 ? w - 1 - i : i;
                put(dpsm, dbp, dbw, dx + x, dy + y, kh1_gsmem_read_pixel(spsm, sbp, sbw, sx + x, sy + y));
            }
        }
        if (l) l->pixels = w * h;
    }
    if (kh1_gsmem_xfer_hook) kh1_gsmem_xfer_hook(dir, bb_lo, bb_hi, pos_lo, pos_hi, reg_lo, reg_hi);
}

/* Session 141 (the Vita's GPU mode: the Dive streams its characters' textures through ever new
 * rectangles, so most uploads missed the kept addresses and paid the swizzle for every pixel): a
 * rectangle's addresses block by block.  kh1_gsmem_addr is a block's own number (from the block's
 * coordinates alone) times the block's size plus the pixel's place in the block (from its coordinates
 * inside the block alone), so each block's start is computed once and the places come from a table
 * made once per PSM.  0 (the caller computes every pixel) for a rectangle past 2048, where x and y wrap */
static u32 blk_w(u32 psm) { return psm == KH1_PSMT4 ? 32 : bits16(psm) || psm == KH1_PSMT8 ? 16 : 8; }
static u32 blk_h(u32 psm) { return psm == KH1_PSMT8 || psm == KH1_PSMT4 ? 16 : 8; }
static int addr_rect(u32 psm, u32 bp, u32 bw, u32 x0, u32 y0, u32 w, u32 h, u32 *out) {
    static u16 place[64][512];
    static u8 made[64];
    static u32 base[2048 / 8 + 2];
    u32 bwid = blk_w(psm), bhgt = blk_h(psm), x, y, bx0, nb, i;
    if (x0 + w > 2048 || y0 + h > 2048) return 0;
    if (!made[psm]) {
        u32 a0 = kh1_gsmem_addr(psm, 0, 1, 0, 0);
        for (y = 0; y < bhgt; y++)
            for (x = 0; x < bwid; x++) place[psm][y * bwid + x] = (u16)(kh1_gsmem_addr(psm, 0, 1, x, y) - a0);
        made[psm] = 1;
    }
    bx0 = x0 / bwid;
    nb = (x0 + w - 1) / bwid - bx0 + 1;
    for (y = 0; y < h; y++) {
        u32 yy = y0 + y;
        const u16 *pl = place[psm] + (yy % bhgt) * bwid;
        if (y == 0 || yy % bhgt == 0) /* a new row of blocks: their starts */
            for (i = 0; i < nb; i++) base[i] = kh1_gsmem_addr(psm, bp, bw, (bx0 + i) * bwid, yy - yy % bhgt);
        for (x = 0; x < w; x++) {
            u32 xx = x0 + x;
            *out++ = base[xx / bwid - bx0] + pl[xx % bwid];
        }
    }
    return 1;
}

static const u32 *trx_addrs(u32 psm, u32 bp, u32 bw, u32 x0, u32 y0, u32 w, u32 h) {
    u32 i, x, y, *a, lo = ~0u, hi = 0;
    trx.key = -1;
    if (!fast_on || !known(psm) || !w || !h || w * h > AT_POOL) return 0;
    for (i = 0; i < at_n; i++)
        if (at_key[i].psm == psm && at_key[i].bp == bp && at_key[i].bw == bw && at_key[i].x == x0 && at_key[i].y == y0 &&
            at_key[i].w == w && at_key[i].h == h) {
            trx.key = i;
            return at_pool + at_key[i].off;
        }
    if (at_n == AT_KEYS || at_used + w * h > AT_POOL) at_n = at_used = same_used = 0;
    a = at_pool + at_used;
    memset(at_key[at_n].pg, 0, sizeof at_key[at_n].pg);
    if (addr_rect(psm, bp, bw, x0, y0, w, h, a)) {
        for (i = 0; i < w * h; i++) {
            u32 p = page_of(psm, a[i]);
            at_key[at_n].pg[p >> 5] |= 1u << (p & 31);
            if (a[i] < lo) lo = a[i];
            if (a[i] > hi) hi = a[i];
        }
    } else
        for (y = 0; y < h; y++)
            for (x = 0; x < w; x++) {
                *a = kh1_gsmem_addr(psm, bp, bw, x0 + x, y0 + y);
                at_key[at_n].pg[page_of(psm, *a) >> 5] |= 1u << (page_of(psm, *a) & 31);
                if (*a < lo) lo = *a;
                if (*a > hi) hi = *a;
                a++;
            }
    at_key[at_n].psm = psm; at_key[at_n].bp = bp; at_key[at_n].bw = bw; at_key[at_n].x = x0; at_key[at_n].y = y0;
    at_key[at_n].w = w; at_key[at_n].h = h; at_key[at_n].off = at_used;
    at_key[at_n].dlen = 0;
    at_key[at_n].plo = page_of(psm, lo);
    at_key[at_n].phi = page_of(psm, hi);
    at_used += w * h;
    trx.key = at_n;
    return at_pool + at_key[at_n++].off;
}

/* the word bits an upload of psm stores (put_at's, trx_bulk's): a draw's marks it clears */
static u32 psm_bits(u32 psm);

/* Session 137 (the title's menus on the Vita, docs/vita-build.md "Speed"): the menus upload the same
 * ~840,000 pixels every frame, the bytes the memory already holds.  A whole upload of the bytes the
 * same rectangle's last one brought, none of its pages stored to since, stores nothing: put_at would find
 * each pixel the same.  Session 146: a draw's marks on its pages no longer refuse it (the title's two
 * 512 x 192 CT24 backdrops lie in the Z buffer's pages, which the frame's Z target marks every frame: ~200,000
 * pixels a frame through trx_bulk24, most of the Vita title's game thread); the marks are cleared page by
 * page as the pixels' stores would clear them (mark: the upload's bits, the stamp kept).
 * 1 when that is so, the counts and the position then as the pixels would leave them; 0 to send the
 * pixels through kh1_gsmem_image, then kh1_gsmem_image_kept */
int kh1_gsmem_image_same(const void *src, u32 bytes) {
    u32 p, bits;
    if (!trx.active || trx.key < 0 || trx.ai || trx.nacc || flat_raw) return 0;
    if (at_key[trx.key].dlen != bytes || at_key[trx.key].plo > at_key[trx.key].phi) return 0;
    for (p = at_key[trx.key].plo; p <= at_key[trx.key].phi; p++)
        if (wr_pg[p] > at_key[trx.key].stamp) return 0;
    if (!kh1_bytes_same(same_pool + at_key[trx.key].doff, src, bytes)) return 0;
    bits = psm_bits(trx.psm);
    for (p = at_key[trx.key].plo; p <= at_key[trx.key].phi; p++)
        if (at_key[trx.key].pg[p >> 5] >> (p & 31) & 1 && page_drawn[p] & bits) {
            page_drawn[p] &= ~bits;
            marks++;
        }
    st.pixels += trx.w * trx.h;
    if (trx.log) trx.log->pixels += trx.w * trx.h;
    trx.ai = trx.w * trx.h;
    trx.active = 0;
    trx.x = trx.x0;
    trx.y = trx.y0 + trx.h;
    return 1;
}

/* the upload's bytes kept for the next kh1_gsmem_image_same, once all its pixels came */
void kh1_gsmem_image_kept(const void *src, u32 bytes) {
    if (trx.active || trx.key < 0 || !trx.at || trx.ai != trx.w * trx.h || bytes > SAME_POOL) return;
    if (at_key[trx.key].dlen != bytes) {
        u32 i;
        if (same_used + bytes > SAME_POOL) {
            for (i = 0; i < at_n; i++) at_key[i].dlen = 0;
            same_used = 0;
        }
        at_key[trx.key].doff = same_used;
        at_key[trx.key].dlen = bytes;
        same_used += (bytes + 15) & ~15u;
    }
    memcpy(same_pool + at_key[trx.key].doff, src, bytes);
    at_key[trx.key].stamp = seq;
    seq++; /* session 146: a later store's wr_pg is newer than the stamp, whatever op makes it */
    trx.key = -1;
}

static void trx_pixel(u32 v) {
    if (trx.at) put_at(trx.psm, trx.at[trx.ai++], v);
    else if (known(trx.psm)) put(trx.psm, trx.bp, trx.bw, trx.x, trx.y, v);
    st.pixels++;
    if (trx.log) trx.log->pixels++;
    if (++trx.x == trx.x0 + trx.w) {
        trx.x = trx.x0;
        if (++trx.y == trx.y0 + trx.h) trx.active = 0;
    }
}

/* Session 135: a piece of a CT32 / Z32, PSMT8 or PSMT4 upload with its addresses kept, put_at's writes
 * and marks without a call a pixel (the title's ~800,000 a frame); then the count and the position as
 * trx_pixel leaves them.  0 for another PSM */
static int trx_bulk(const u32 *w, u32 n) {
    u32 left = trx.w * trx.h - trx.ai, k, j, a, o, v;
    const u32 *at = trx.at + trx.ai;
    switch (trx.psm) {
    case KH1_PSMCT32: case KH1_PSMZ32:
        k = n < left ? n : left;
        for (j = 0; j < k; j++) {
            a = at[j];
            v = w[j];
            o = ld32(a);
            if (o != v) {
                st32(a, v);
                page_seq[a >> 11] = seq;
            } else if (!page_drawn[a >> 11]) {
                continue;
            }
            page_drawn[a >> 11] = 0;
            marks++;
        }
        break;
    /* session 141 (the Dive's T8 texture streams, a tenth of its frame): mark's work inline, marks moved
     * once a piece (tex_scan's memo only asks whether it moved) */
    case KH1_PSMT8: {
        /* session 143 (the Dive's ~425,000 T8 pixels a frame on the GS worker): a row's run inside one 16-wide
         * block column is one block, so one page; its pixels stored with no test each (an equal byte stored
         * again changes nothing), and the page's stamp and marks once a run, as the test a pixel left them */
        int moved = 0;
        u32 x = trx.ai % trx.w, run, pg, d, i;
#if defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
        const u8 *b = (const u8 *)w;
#define T8_BYTE(i) b[i]
#else
#define T8_BYTE(i) (w[(i) >> 2] >> ((i) & 3) * 8 & 0xFF)
#endif
        k = n * 4 < left ? n * 4 : left;
        for (j = 0; j < k; j += run) {
            run = 16 - (trx.x0 + x) % 16;
            if (run > trx.w - x) run = trx.w - x;
            if (run > k - j) run = k - j;
            pg = at[j] >> 13;
            if (at[j + run - 1] >> 13 != pg) run = 1; /* never for the block layout: a pixel alone */
            d = 0;
            for (i = j; i < j + run; i++) {
                a = at[i];
                v = T8_BYTE(i);
                d |= vm[a] ^ v;
                vm[a] = (u8)v;
            }
            if (d) {
                page_seq[pg] = seq;
                STORED(pg);
                page_drawn[pg] = 0;
                moved = 1;
            } else if (page_drawn[pg]) {
                page_drawn[pg] = 0;
                moved = 1;
            }
            x += run;
            if (x == trx.w) x = 0;
        }
#undef T8_BYTE
        marks += moved;
        break;
    }
    case KH1_PSMT4: {
        int moved = 0;
        k = n * 8 < left ? n * 8 : left;
        for (j = 0; j < k; j++) {
            u32 pg, nv;
            a = at[j];
            v = w[j >> 3] >> (j & 7) * 4 & 15;
            o = vm[a >> 1];
            nv = (o & (0xF0 >> (a & 1) * 4)) | v << (a & 1) * 4;
            pg = a >> 14;
            if (o != nv) {
                vm[a >> 1] = (u8)nv;
                page_seq[pg] = seq;
                STORED(pg);
            } else if (!page_drawn[pg]) {
                continue;
            }
            page_drawn[pg] = 0;
            moved = 1;
        }
        marks += moved;
        break;
    }
    default:
        return 0;
    }
    st.pixels += k;
    if (trx.log) trx.log->pixels += k;
    trx.ai += k;
    if (trx.ai == trx.w * trx.h) {
        trx.active = 0;
        trx.x = trx.x0;
        trx.y = trx.y0 + trx.h;
    } else {
        trx.x = trx.x0 + trx.ai % trx.w;
        trx.y = trx.y0 + trx.ai / trx.w;
    }
    return 1;
}

/* Session 137: a piece of a CT24 / Z24 upload with its addresses kept (the title menus' two 512 x 192
 * backdrops a frame, into memory the frame's Z writes: docs/vita-build.md "Speed"), three bytes a pixel
 * as kh1_gsmem_image assembles them, a pixel's bytes across two pieces too; put_at's stores and marks
 * without a call a pixel */
static void trx_bulk24(const u32 *w, u32 n) {
    u32 total = trx.w * trx.h, ai0 = trx.ai, i = 0, a, o, v, pg;
#define PUT24(px)                                                                    \
    do {                                                                             \
        a = trx.at[trx.ai++];                                                        \
        o = ld32(a);                                                                 \
        v = (o & 0xFF000000u) | (px);                                                \
        pg = a >> 11;                                                                \
        if (o != v) {                                                                \
            st32(a, v);                                                              \
            page_seq[pg] = seq;                                                      \
        } else if (!(page_drawn[pg] & 0x00FFFFFF)) {                                 \
            break;                                                                   \
        }                                                                            \
        page_drawn[pg] &= 0xFF000000u;                                               \
        marks++;                                                                     \
    } while (0)
    /* a pixel begun in the last piece, then whole pixels three bytes at a time */
    for (; i < n * 4 && trx.nacc && trx.ai < total; i++) {
        trx.acc |= (w[i >> 2] >> (i & 3) * 8 & 0xFF) << trx.nacc * 8;
        if (++trx.nacc == 3) {
            PUT24(trx.acc);
            trx.acc = trx.nacc = 0;
        }
    }
#if defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    {
        const u8 *b = (const u8 *)w;
        for (; i + 3 <= n * 4 && trx.ai < total; i += 3) PUT24(b[i] | b[i + 1] << 8 | (u32)b[i + 2] << 16);
    }
#endif
    for (; i < n * 4 && trx.ai < total; i++) {
        trx.acc |= (w[i >> 2] >> (i & 3) * 8 & 0xFF) << trx.nacc * 8;
        if (++trx.nacc == 3) {
            PUT24(trx.acc);
            trx.acc = trx.nacc = 0;
        }
    }
#undef PUT24
    st.pixels += trx.ai - ai0;
    if (trx.log) trx.log->pixels += trx.ai - ai0;
    if (trx.ai == total) {
        trx.active = 0;
        trx.x = trx.x0;
        trx.y = trx.y0 + trx.h;
    } else {
        trx.x = trx.x0 + trx.ai % trx.w;
        trx.y = trx.y0 + trx.ai / trx.w;
    }
}

void kh1_gsmem_image(const u32 *w, u32 n) {
    u32 i, b;
    if (!trx.active) { st.extra += (n + 3) / 4; return; } /* qwords (a HWREG write: one) */
    seq++; /* session 118: each piece of an upload a write of its own (a texture read between two is a miss) */
    if (trx.at && !trx.nacc && !flat_raw && trx_bulk(w, n)) return;
    if (trx.at && trx.bytes == 3 && !flat_raw) {
        trx_bulk24(w, n);
        return;
    }
    if (trx.bytes == 4 && !trx.nacc) { /* session 135: CT32's pixel a whole word */
        for (i = 0; i < n && trx.active; i++) trx_pixel(w[i]);
        return;
    }
    for (i = 0; i < n * 4 && trx.active; i++) {
        b = w[i >> 2] >> (i & 3) * 8 & 0xFF;
        if (!trx.bytes) { /* 4 bits a pixel, the low nibble first */
            trx_pixel(b & 15);
            if (trx.active) trx_pixel(b >> 4);
            continue;
        }
        trx.acc |= b << trx.nacc * 8;
        if (++trx.nacc == trx.bytes) {
            trx_pixel(trx.acc);
            trx.acc = trx.nacc = 0;
        }
    }
}

/* the CLUT formats (CPSM): CT32, CT16 and CT16S */
static int clut_psm(u32 cpsm) { return cpsm == KH1_PSMCT32 || cpsm == KH1_PSMCT16 || cpsm == KH1_PSMCT16S; }
/* session 135: TEX0's CPSM, CT24 (1) read as CT32: the GS manual lists only the three, but dktitle.x's
 * menu lines (func_00f22238's TEX0s, CLD 1) give CPSM 1 with an alpha ramp in the entries (CBP 0x38F5:
 * black, alpha 0 .. 0x80, the glyphs' coverage), which the title shows as its text, so the entry's
 * alpha is the CLUT's own (a CT32 load), not TEXA's */
static u32 cpsm_of(u32 hi) {
    u32 c = hi >> 19 & 15;
    return c == KH1_PSMCT24 ? KH1_PSMCT32 : c;
}
static int bits8(u32 psm) { return psm == KH1_PSMT8 || psm == KH1_PSMT8H; }
static int indexed(u32 psm) { return bits8(psm) || psm == KH1_PSMT4 || psm == KH1_PSMT4HL || psm == KH1_PSMT4HH; }

void (*kh1_gsmem_clut_loaded)(u32 lo, u32 hi);
const u32 *(*kh1_gsmem_palette)(u32 lo, u32 hi, u32 texa_lo, u32 texa_hi);
const u32 *(*kh1_gsmem_texels)(u32 lo, u32 hi);

/* Session 147c (the title's menu on the Vita): its text is ~60 sprites a frame, each with a TEX2 that loads a
 * 16 x 16 CLUT, and each load read its entries through kh1_gsmem_read_rect's tables built anew for each CBP (~80%
 * of the GS worker's menu frame on the host profile, ~11 ms a frame on a Vita).  The entries a load reads are kept
 * by (CPSM, CBP, 8-bit or 4-bit) with the raw words of the blocks they lie in (the rectangle's four corners' blocks:
 * a 16 x 16 CT32 / CT16 CLUT is 2 x 2 / 1 x 2 blocks, a 4-bit one's 8 x 2 one block); a load whose blocks hold the
 * same words takes the kept entries.  Exact: the entries are a function of those words alone. */
#define CLUT_KEPT 64
static struct { u32 key, nb, b[4], raw[4][64], v[256]; } clut_k[CLUT_KEPT];
static int clut_k_at = -1;
static void clut_blocks(u32 cpsm, u32 cbp, int b8, u32 *b, u32 *nb) {
    u32 w = b8 ? 16 : 8, h = b8 ? 16 : 2, i, j, a, blk, shift = cpsm == KH1_PSMCT32 ? 2 : 1;
    *nb = 0;
    for (i = 0; i < 4; i++) {
        a = kh1_gsmem_addr(cpsm, cbp, 1, i & 1 ? w - 1 : 0, i & 2 ? h - 1 : 0);
        blk = (a << shift) >> 8 & 0x3FFF;
        for (j = 0; j < *nb && b[j] != blk; j++) ;
        if (j == *nb) b[(*nb)++] = blk;
    }
}
static u32 clut_hash(u32 key) { return (key * 0x9E3779B1u) >> 26; } /* 64 slots */
/* the kept entries (16x16 for b8, else 8x2, in read order) when the blocks hold the words they held; else 0, and
 * clut_keep then keeps what the caller reads */
static const u32 *clut_kept(u32 cpsm, u32 cbp, int b8) {
    u32 key = cbp | cpsm << 14 | (u32)b8 << 20, i = clut_hash(key), b[4], nb, j;
    clut_k_at = -1;
    if (!fast_on) return 0;
    clut_blocks(cpsm, cbp, b8, b, &nb);
    clut_k_at = (int)i;
    if (clut_k[i].key != key || clut_k[i].nb != nb) {
        clut_k[i].key = key;
        clut_k[i].nb = nb;
        for (j = 0; j < nb; j++) {
            clut_k[i].b[j] = b[j];
            kh1_gsmem_read_block(b[j], clut_k[i].raw[j]);
        }
        return 0;
    }
    for (j = 0; j < nb; j++)
        if (clut_k[i].b[j] != b[j] || !kh1_bytes_same(vm + (b[j] & 0x3FFF) * 256, clut_k[i].raw[j], 256)) break;
    if (j == nb) return clut_k[i].v;
    for (j = 0; j < nb; j++) {
        clut_k[i].b[j] = b[j];
        kh1_gsmem_read_block(b[j], clut_k[i].raw[j]);
    }
    return 0;
}
static const u32 *clut_keep(const u32 *v, u32 n) {
    if (clut_k_at < 0) return v;
    memcpy(clut_k[clut_k_at].v, v, n * 4);
    return clut_k[clut_k_at].v;
}

void kh1_gsmem_tex0(u32 lo, u32 hi) {
    u32 psm = lo >> 20 & 63, cbp = hi >> 5 & 0x3FFF, cpsm = cpsm_of(hi), csm = hi >> 23 & 1;
    u32 csa = hi >> 24 & 31, cld = hi >> 29 & 7, e, p, v, how;
    if (!indexed(psm)) return;
    switch (cld) {
    case 0: case 6: case 7: return;
    case 2: cbp0 = cbp; break;
    case 3: cbp1 = cbp; break;
    case 4: if (cbp == cbp0) return; cbp0 = cbp; break;
    case 5: if (cbp == cbp1) return; cbp1 = cbp; break;
    }
    if (csm || !clut_psm(cpsm) || (bits8(psm) && csa)) {
        st.unsupported++;
        return;
    }
    st.clut_loads++;
    clut_seq++;
    how = cpsm | (u32)bits8(psm) << 8 | csa << 16;
    if (bits8(psm)) {
        static u32 c16[256]; /* session 141: the 16 x 16 at once (kh1_gsmem_read_rect's tables), not 256 swizzles */
        const u32 *c = clut_kept(cpsm, cbp, 1);
        if (c && c == clut_done && how == clut_done_how) goto loaded;
        if (!c) {
            kh1_gsmem_read_rect(cpsm, cbp, 1, 0, 0, 16, 16, c16, 16);
            c = clut_keep(c16, 256);
        }
        clut_done = clut_k_at < 0 ? 0 : c;
        clut_ver++;
        for (e = 0; e < 256; e++) {
            p = (e & 0xE7) | (e & 8) << 1 | (e & 0x10) >> 1; /* entries 8-15 / 16-23 of each 32 swapped */
            v = c[p];
            clut[e] = v;
            if (cpsm == KH1_PSMCT32) clut[e + 256] = v >> 16;
        }
    } else {
        const u32 *c = clut_kept(cpsm, cbp, 0);
        u32 c8[16];
        if (c && c == clut_done && how == clut_done_how) goto loaded;
        if (!c) {
            for (e = 0; e < 16; e++) c8[e] = kh1_gsmem_read_pixel(cpsm, cbp, 1, e & 7, e >> 3);
            c = clut_keep(c8, 16);
        }
        clut_done = clut_k_at < 0 ? 0 : c;
        clut_ver++;
        for (e = 0; e < 16; e++) {
            v = c[e];
            if (cpsm == KH1_PSMCT32) {
                clut[(csa & 15) * 16 + e] = v;
                clut[(csa & 15) * 16 + e + 256] = v >> 16;
            } else {
                clut[csa * 16 + e] = v;
            }
        }
    }
    clut_done_how = how;
loaded:
    if (kh1_gsmem_clut_loaded) kh1_gsmem_clut_loaded(lo, hi);
    if (kh1_gsmem_clut_hook) kh1_gsmem_clut_hook(lo, hi);
}

/* a CT16 colour (or CLUT entry) to RGBA8: 5 bits a channel shifted up 3, A from TEXA (TA1 with the
 * STP bit; else TA0, or 0 for black with AEM) */
static u32 rgba16(u32 v, u32 texa_lo, u32 texa_hi) {
    u32 a = v & 0x8000 ? texa_hi & 0xFF : (texa_lo >> 15 & 1) && !(v & 0x7FFF) ? 0 : texa_lo & 0xFF;
    return (v & 31) << 3 | (v >> 5 & 31) << 11 | (v >> 10 & 31) << 19 | a << 24;
}

/* a texel's stored value v as RGBA8, the CLUT buffer's entry for an indexed PSM (checked by the
 * caller) */
static u32 value_rgba(u32 psm, u32 v, u32 cpsm, u32 csa, u32 texa_lo, u32 texa_hi) {
    u32 e;
    switch (psm) {
    case KH1_PSMCT32: case KH1_PSMZ32: return v;
    case KH1_PSMCT24: case KH1_PSMZ24: return v | ((texa_lo >> 15 & 1) && !v ? 0 : texa_lo & 0xFF) << 24;
    case KH1_PSMCT16: case KH1_PSMCT16S: case KH1_PSMZ16: case KH1_PSMZ16S: return rgba16(v, texa_lo, texa_hi);
    }
    /* indexed: 8 bits from entry 0, 4 bits from CSA's 16 */
    e = bits8(psm) ? v : (cpsm == KH1_PSMCT32 ? csa & 15 : csa) * 16 + v;
    return cpsm == KH1_PSMCT32 ? clut[e] | (u32)clut[e + 256] << 16 : rgba16(clut[e & 511], texa_lo, texa_hi);
}

/* one texel (x, y) of a texture as RGBA8 */
static u32 texel_rgba(u32 psm, u32 tbp, u32 tbw, u32 cpsm, u32 csa, u32 x, u32 y, u32 texa_lo, u32 texa_hi) {
    return value_rgba(psm, kh1_gsmem_read_pixel(psm, tbp, tbw, x, y), cpsm, csa, texa_lo, texa_hi);
}

/* session 116: the palette a TEX0 reads from the CLUT buffer the last load left, as RGBA8 words (the
 * port's palette cache, host/port/palcache.c, takes these): 256 entries for an 8-bit PSM, CSA's 16
 * for a 4-bit one.  Returns the count, or 0 for a PSM that is not indexed or a CLUT the model does not
 * have. */
int kh1_gsmem_clut(u32 lo, u32 hi, u32 texa_lo, u32 texa_hi, u32 *out) {
    /* session 147c: the last answer kept, with the CLUT buffer's version (clut_ver: a load that stored) and how it
     * was asked (CT32 ignores TEXA): the title menu's glyphs ask for the same palette ~60 times a frame */
    static u32 memo[256], memo_how = ~0u, memo_ver, memo_ta, memo_tb;
    u32 psm = lo >> 20 & 63, cpsm = cpsm_of(hi), csa = hi >> 24 & 31, n, e, i, how;
    if (!indexed(psm) || hi >> 23 & 1 || !clut_psm(cpsm) || (bits8(psm) && csa)) return 0;
    n = bits8(psm) ? 256 : 16;
    how = cpsm | n << 8 | csa << 20;
    if (cpsm != KH1_PSMCT32) texa_lo &= 0x80FF, texa_hi &= 0xFF; /* rgba16's TA0, AEM and TA1 */
    else texa_lo = texa_hi = 0;
    if (how == memo_how && memo_ver == clut_ver && memo_ta == texa_lo && memo_tb == texa_hi) {
        memcpy(out, memo, n * 4);
        return (int)n;
    }
    for (i = 0; i < n; i++) {
        e = n == 256 ? i : (cpsm == KH1_PSMCT32 ? csa & 15 : csa) * 16 + i;
        out[i] = cpsm == KH1_PSMCT32 ? clut[e] | (u32)clut[e + 256] << 16 : rgba16(clut[e & 511], texa_lo, texa_hi);
    }
    memcpy(memo, out, n * 4);
    memo_how = how;
    memo_ver = clut_ver;
    memo_ta = texa_lo;
    memo_tb = texa_hi;
    return (int)n;
}

/* the texture TEX0 names can be read (a PSM the model has, an indexed one's CLUT too) */
static int tex_ok(u32 lo, u32 hi) {
    u32 psm = lo >> 20 & 63, cpsm = cpsm_of(hi), csa = hi >> 24 & 31;
    if (!known(psm) || (lo >> 26 & 15) > 10 || ((lo >> 30 | hi << 2) & 15) > 10) return 0;
    return !indexed(psm) || !(hi >> 23 & 1 || !clut_psm(cpsm) || (bits8(psm) && csa));
}

int kh1_gsmem_read_tex(u32 lo, u32 hi, u32 texa_lo, u32 texa_hi, u32 *out) {
    u32 tbp = lo & 0x3FFF, tbw = lo >> 14 & 63, psm = lo >> 20 & 63, tw = lo >> 26 & 15;
    u32 th = (lo >> 30 | hi << 2) & 15, cpsm = cpsm_of(hi), csa = hi >> 24 & 31, w, h, x, y;
    if (!known(psm) || tw > 10 || th > 10) { st.unsupported++; return -1; }
    if (indexed(psm) && (hi >> 23 & 1 || !clut_psm(cpsm) || (bits8(psm) && csa))) {
        st.unsupported++;
        return -1;
    }
    w = 1u << tw;
    h = 1u << th;
    for (y = 0; y < h; y++)
        for (x = 0; x < w; x++) out[y * w + x] = texel_rgba(psm, tbp, tbw, cpsm, csa, x, y, texa_lo, texa_hi);
    return 0;
}

/* the bits of a page's word mark a PSM reads (all of them for the formats that do not share CT32's word) */
static u32 psm_bits(u32 psm) {
    switch (psm) {
    case KH1_PSMCT24: case KH1_PSMZ24: return 0x00FFFFFF;
    case KH1_PSMT8H:  return 0xFF000000u;
    case KH1_PSMT4HL: return 0x0F000000;
    case KH1_PSMT4HH: return 0xF0000000u;
    }
    return ~0u;
}

/* Session 141 (tex_scan was a tenth of a menu frame on the host, one kh1_gsmem_addr a block): a texture
 * that covers whole pages of its layout (a page 64 x 32 pixels at 32 bits, 64 x 64 at 16, 128 x 64 at
 * T8, 128 x 128 at T4) by those pages.  A page's 32 blocks are 32 consecutive block numbers from the
 * one kh1_gsmem_addr gives its first, before the Z formats' XOR (which leaves the page alone) and the
 * wrap at 0x4000, so they lie in that number's page and the next (when bp is not page-aligned).  The
 * newest stamp is the same whatever the order; the first drawn page's target, which the block order
 * decides, too, as long as every drawn page the texture reads names one target: 0 (the caller scans
 * the blocks) when two differ, or for a texture smaller than a page */
static int scan_pages(u32 psm, u32 bp, u32 bw, u32 w, u32 h, u32 bits, u32 *s, u32 *t) {
    u32 pw = bits16(psm) || (psm != KH1_PSMT8 && psm != KH1_PSMT4) ? 64 : 128;
    u32 ph = bits16(psm) || psm == KH1_PSMT8 ? 64 : psm == KH1_PSMT4 ? 128 : 32;
    u32 row = psm == KH1_PSMT8 || psm == KH1_PSMT4 ? bw >> 1 : bw, x, y, k, b, p, seq_max = 0, tg = 0;
    if (w < pw || h < ph) return 0;
    for (y = 0; y < h / ph; y++)
        for (x = 0; x < w / pw; x++) {
            b = bp + y * row * 32 + x * 32;
            for (k = 0; k < 2; k++) {
                p = ((b + k * 31) & 0x3FFF) >> 5;
                if (page_seq[p] > seq_max) seq_max = page_seq[p];
                if (page_drawn[p] & bits) {
                    if (tg && tg != page_tgt[p]) return 0;
                    tg = page_tgt[p];
                }
            }
        }
    *s = seq_max;
    *t = tg;
    return 1;
}

/* the pages a texture's w x h texels lie in: the newest write's sequence number, and with *t the
 * first page whose drawn bits it reads (1 + its target, 0 for none) */
static u32 tex_scan(u32 lo, u32 hi, u32 *t) {
    u32 tbp = lo & 0x3FFF, tbw = lo >> 14 & 63, psm = lo >> 20 & 63, tw = lo >> 26 & 15;
    u32 th = (lo >> 30 | hi << 2) & 15, bwid, bhgt, x, y, a, page, s = 0, bits;
    static u32 m_lo, m_hi, m_marks, m_s, m_t, m_ok;
    *t = 0;
    /* session 135: the frame copy's 16 strips scan the same 512 x 512 texture twice each with no page
     * mark between: the last answer again while no mark moved */
    if (m_ok && fast_on && m_lo == lo && m_hi == hi && m_marks == marks) {
        *t = m_t;
        return m_s;
    }
    m_ok = 0;
    if (!known(psm)) return 0;
    bwid = psm == KH1_PSMT4 ? 32 : bits16(psm) || psm == KH1_PSMT8 ? 16 : 8;
    bhgt = psm == KH1_PSMT8 || psm == KH1_PSMT4 ? 16 : 8;
    bits = psm_bits(psm);
    if (tw > 10 || th > 10) return 0;
    if (fast_on && scan_pages(psm, tbp, tbw, 1u << tw, 1u << th, bits, &s, t)) {
        m_lo = lo; m_hi = hi; m_marks = marks; m_s = s; m_t = *t; m_ok = 1;
        return s;
    }
    /* one address a block: a block never spans two pages */
    for (y = 0; y < 1u << th; y += bhgt)
        for (x = 0; x < 1u << tw; x += bwid) {
            a = kh1_gsmem_addr(psm, tbp, tbw, x, y);
            page = page_of(psm, a);
            if (page_seq[page] > s) s = page_seq[page];
            if (!*t && page_drawn[page] & bits) *t = page_tgt[page];
        }
    m_lo = lo; m_hi = hi; m_marks = marks; m_s = s; m_t = *t; m_ok = 1;
    return s;
}

u32 kh1_gsmem_tex_stamp(u32 lo, u32 hi) {
    u32 t;
    return tex_scan(lo, hi, &t);
}

/* session 142: the raw words of every page TEX0 (lo, hi)'s texels lie in, in page order, at most max words
 * (include/platform/texcache.h's KH1TexRaw): the texels are read from these words only, so the same words
 * give the same texels.  0 for a format the model does not keep or more pages than max holds */
u32 kh1_gsmem_tex_raw(u32 lo, u32 hi, u32 *out, u32 max) {
    u32 tbp = lo & 0x3FFF, tbw = lo >> 14 & 63, psm = lo >> 20 & 63, tw = lo >> 26 & 15;
    u32 th = (lo >> 30 | hi << 2) & 15, bwid, bhgt, x, y, p, n = 0;
    u32 seen[512 / 32];
    if (!known(psm) || tw > 10 || th > 10) return 0;
    bwid = psm == KH1_PSMT4 ? 32 : bits16(psm) || psm == KH1_PSMT8 ? 16 : 8;
    bhgt = psm == KH1_PSMT8 || psm == KH1_PSMT4 ? 16 : 8;
    memset(seen, 0, sizeof seen);
    for (y = 0; y < 1u << th; y += bhgt)
        for (x = 0; x < 1u << tw; x += bwid) {
            p = page_of(psm, kh1_gsmem_addr(psm, tbp, tbw, x, y));
            if (seen[p >> 5] >> (p & 31) & 1) continue;
            seen[p >> 5] |= 1u << (p & 31);
            if (++n * 2048 > max) return 0;
        }
    n = 0;
    for (p = 0; p < 512; p++)
        if (seen[p >> 5] >> (p & 31) & 1) {
            memcpy(out + n, vm + p * 8192, 8192);
            n += 2048;
        }
    return n;
}

/* ---- session 142: GS memory as a frame left it, for the frame's GPU work on its own thread ----
 * kh1_gsmem_snap_take copies the pages stored to since the last one (and every page's stamp); the
 * kh1_gsmem_snap_* readers give what the live readers gave at that moment, from the copy only, and share
 * no state with the model, so another thread may call them while the model goes on (never during a take) */
static u8 *snap_vm;
static u32 snap_seq[512];
/* session 146: the take that last copied each page (its bytes in the copy unchanged since), and the takes */
static u32 snap_ver[512], snap_takes;
u32 kh1_gsmem_snap_pages; /* pages copied so far (the Vita watchdog's) */

int kh1_gsmem_snap_take(void) {
    u32 p, n = 0;
    if (!snap_vm) {
        if (!(snap_vm = (u8 *)malloc(VM_BYTES))) return -1;
        memset(dirty_pg, 1, sizeof dirty_pg);
    }
    in_tables(); /* the copy's read_rect uses them on the GPU thread */
    snap_takes++;
    for (p = 0; p < 512; p++)
        if (dirty_pg[p]) {
            memcpy(snap_vm + p * 8192, vm + p * 8192, 8192);
            dirty_pg[p] = 0;
            snap_ver[p] = snap_takes;
            n++;
        }
    memcpy(snap_seq, page_seq, sizeof snap_seq);
    kh1_gsmem_snap_pages += n;
    return (int)n;
}

/* session 145: 1 when a take now would copy nothing new (no page stored to, no stamp moved since the last) */
int kh1_gsmem_snap_same(void) {
    u32 p;
    if (!snap_vm) return 0;
    for (p = 0; p < 512; p++)
        if (dirty_pg[p]) return 0;
    return memcmp(snap_seq, page_seq, sizeof snap_seq) == 0;
}

void kh1_gsmem_snap_read_block(u32 b, u32 *out) {
    memcpy(out, snap_vm + (b & 0x3FFF) * 256, 256);
}

/* kh1_gsmem_read_rect's answer, from the copy.  Session 146: through read_rect's fast paths (its own split
 * slot and tables: the copy's reader is another thread); pixel by pixel, the title's full-screen CT24 layer
 * (512 x 256) was ~16x the fast path's time on the x86 host, ~25-30 ms a read estimated on the Vita */
int kh1_gsmem_snap_read_rect(u32 psm, u32 bp, u32 bw, u32 x0, u32 y0, u32 w, u32 h, u32 *out, u32 stride) {
    static u32 cx[2048], ry[2048];
    return rect_in(snap_vm, SPLIT_SNAP, cx, ry, psm, bp, bw, x0, y0, w, h, out, stride);
}

/* kh1_gsmem_tex_stamp's answer (the newest stamp of the pages the texels lie in), from the copy */
u32 kh1_gsmem_snap_tex_stamp(u32 lo, u32 hi) {
    u32 tbp = lo & 0x3FFF, tbw = lo >> 14 & 63, psm = lo >> 20 & 63, tw = lo >> 26 & 15;
    u32 th = (lo >> 30 | hi << 2) & 15, bwid, bhgt, x, y, page, s = 0;
    if (!known(psm) || tw > 10 || th > 10) return 0;
    bwid = psm == KH1_PSMT4 ? 32 : bits16(psm) || psm == KH1_PSMT8 ? 16 : 8;
    bhgt = psm == KH1_PSMT8 || psm == KH1_PSMT4 ? 16 : 8;
    for (y = 0; y < 1u << th; y += bhgt)
        for (x = 0; x < 1u << tw; x += bwid) {
            page = page_of(psm, kh1_gsmem_addr(psm, tbp, tbw, x, y));
            if (snap_seq[page] > s) s = snap_seq[page];
        }
    return s;
}

/* session 146: the newest take that copied a page the texels lie in: while it holds, the copy's texels are the
 * same bytes (a page's stamp also moves when a draw marks it, or for bytes stored again unchanged) */
u32 kh1_gsmem_snap_tex_ver(u32 lo, u32 hi) {
    u32 tbp = lo & 0x3FFF, tbw = lo >> 14 & 63, psm = lo >> 20 & 63, tw = lo >> 26 & 15;
    u32 th = (lo >> 30 | hi << 2) & 15, bwid, bhgt, x, y, page, s = 0;
    if (!known(psm) || tw > 10 || th > 10) return 0;
    bwid = psm == KH1_PSMT4 ? 32 : bits16(psm) || psm == KH1_PSMT8 ? 16 : 8;
    bhgt = psm == KH1_PSMT8 || psm == KH1_PSMT4 ? 16 : 8;
    for (y = 0; y < 1u << th; y += bhgt)
        for (x = 0; x < 1u << tw; x += bwid) {
            page = page_of(psm, kh1_gsmem_addr(psm, tbp, tbw, x, y));
            if (snap_ver[page] > s) s = snap_ver[page];
        }
    return s;
}

u32 kh1_gsmem_tex_target(u32 lo, u32 hi) {
    u32 t;
    tex_scan(lo, hi, &t);
    return t;
}

int kh1_gsmem_drawn(u32 psm, u32 bp, u32 bw, u32 x, u32 y) {
    if (!known(psm)) return 0;
    return (page_drawn[page_of(psm, kh1_gsmem_addr(psm, bp, bw, x, y))] & psm_bits(psm)) != 0;
}

int kh1_gsmem_targets(KH1GsTarget *out, int max) {
    int i;
    for (i = 0; i < (int)ntgt && i < max; i++) out[i] = tgt[i];
    return ntgt;
}

/* one surface drawn: its target found or added, its pages marked (again only after an upload, a copy
 * or a pixel write, or when the surface grew) */
static void draw_into(u32 fbp, u32 bw, u32 psm, u32 cols, u32 h, u32 mask) {
    u32 i, r, c, ph = bits16(psm) ? 64 : 32;
    KH1GsTarget *t;
    if (!mask) return;
    for (i = 0; i < ntgt; i++)
        if (tgt[i].bp == fbp * 32 && tgt[i].bw == bw && tgt[i].psm == psm) break;
    if (i == ntgt) {
        if (ntgt == TARGETS) return;
        t = &tgt[ntgt++];
        memset(t, 0, sizeof *t);
        t->bp = fbp * 32;
        t->bw = bw;
        t->psm = psm;
        tgt_useq[i] = useq - 1;
    }
    t = &tgt[i];
    t->draws++;
    t->sent++;
    st.target_draws++;
    if (tgt_useq[i] == useq && h <= t->h && (mask & ~t->mask) == 0) return;
    if (h > t->h) t->h = h;
    t->mask |= mask;
    seq++;
    /* each page by a pixel in it, through the PSM's own layout (a Z format's block XOR stays inside
     * the page, so the extent is the colour twin's) */
    for (r = 0; r < (t->h + ph - 1) / ph; r++)
        for (c = 0; c < cols; c++) {
            u32 p = page_of(psm, kh1_gsmem_addr(psm, fbp * 32, bw, c * 64, r * ph));
            page_drawn[p] |= t->mask;
            page_tgt[p] = i + 1;
            page_seq[p] = seq;
            marks++;
        }
    tgt_useq[i] = useq;
}

void kh1_gsmem_draw(u32 frame_lo, u32 frame_hi, u32 zbuf_lo, u32 zbuf_hi, u32 sc_lo, u32 sc_hi, u32 test_lo) {
    u32 bw = frame_lo >> 16 & 63, psm = frame_lo >> 24 & 63, h = (sc_hi >> 16 & 0x7FF) + 1;
    u32 cols = ((sc_lo >> 16 & 0x7FF) >> 6) + 1, mask;
    if (!bw) return; /* no FRAME yet (FBW 0): nothing a draw could reach */
    if (cols > bw) cols = bw;
    switch (psm) {
    case KH1_PSMCT32: mask = ~frame_hi; break;
    case KH1_PSMCT24: mask = ~frame_hi & 0x00FFFFFF; break;
    default: mask = (~frame_hi & 0x80F8F8F8) ? ~0u : 0; break; /* CT16 / CT16S: FBMSK in RGBA5551's bits */
    }
    draw_into(frame_lo & 0x1FF, bw, psm, cols, h, mask);
    if (test_lo >> 16 & 1 && !(zbuf_hi & 1)) {
        psm = 0x30 | (zbuf_lo >> 24 & 15);
        draw_into(zbuf_lo & 0x1FF, bw, psm, cols, h, psm == 0x31 ? 0x00FFFFFF : ~0u);
    }
}

/* kh1_gsmem_sprite (session 83): a point-sampled textured sprite drawn into the model, as the GS
 * draws it: the pixels from (X0 - OFX + 15) >> 4 up to but not including (X1 - OFX + 15) >> 4 (Y
 * likewise) inside SCISSOR, each texel at U0 + (16 x - X0') (U1 - U0) / (X1 - X0) in 10.4 (no
 * half-pixel offset), Ct x Cv >> 7 (MODULATE) or Ct (DECAL), alpha At x Av >> 7 / At with TCC else
 * Av, then ((A - B) x C >> 7) + D with ABE, clamped to 0-255, the written alpha the source's, the
 * FBMSK bits kept.  The texture animations (renderer-spec 4.13) copy and blend CLUTs this way. */
static int clamp255(s32 v) { return v < 0 ? 0 : v > 255 ? 255 : v; }
static s32 sel(u32 f, s32 cs, s32 cd) { return f == 0 ? cs : f == 1 ? cd : 0; }
static u32 texel(u32 c, u32 n, u32 wm) { return wm ? (c >= n ? n - 1 : c) : c & (n - 1); }
/* a u read back by a wide copy's margin can start left of texel 0 (session 99): the model has none there */
static s32 umax0(s32 u) { return u < 0 ? 0 : u; }
/* session 124: a + n x d / m rounded down (the GS's DDA), not toward zero: a reversed u or v (d < 0) took
 * the next texel up at a boundary (tests/host/vertex_test.c) */
static s32 lerp_floor(s32 a, s32 n, s32 d, s32 m) {
    s32 p = n * d, q = p / m;
    if ((p % m) && ((p < 0) != (m < 0))) q--;
    return a + q;
}

static int atst(u32 m, u32 a, u32 ref);

/* session 135: a sprite's tables (addr_split): the frame's address parts, each column's and row's texel,
 * the texture's address parts */
static u32 sp_cx[2048], sp_ry[2048], sp_tx[2048], sp_ty[2048], sp_tcx[1024], sp_try[1024];
static u32 sp_pm[256];         /* session 135: a palette's entries after the texture function */
static u32 sp_al[256];         /* session 135: a texel's alpha after it, in bits 24-31 */
static s32 qfx[2048], qfy[2048]; /* session 135: a quad's weights (kh1_gsmem_flat_sprite) */

/* a quad's colour at weights fx, fy: the top corners' mix, the bottom's, then between the two */
static void quad_cv(const KH1GsSprite *s, s32 fx, s32 fy, s32 *cv) {
    u32 i;
    for (i = 0; i < 4; i++) {
        s32 top = (s32)(s->rgbav[0] >> i * 8 & 0xFF) * (256 - fx) + (s32)(s->rgbav[1] >> i * 8 & 0xFF) * fx;
        s32 bot = (s32)(s->rgbav[2] >> i * 8 & 0xFF) * (256 - fx) + (s32)(s->rgbav[3] >> i * 8 & 0xFF) * fx;
        cv[i] = (top * (256 - fy) + bot * fy) >> 16;
    }
}

int kh1_gsmem_sprite(const KH1GsSprite *s) {
    static u32 tex[64 * 64];
    u32 p = s->prim, fpsm = s->frame_lo >> 24 & 63, fbp = (s->frame_lo & 0x1FF) * 32, fbw = s->frame_lo >> 16 & 63;
    u32 tw = s->tex0_lo >> 26 & 15, th = (s->tex0_lo >> 30 | s->tex0_hi << 2) & 15, tfx = s->tex0_hi >> 3 & 3;
    u32 tcc = s->tex0_hi >> 2 & 1, ztst = s->test_lo >> 17 & 3, wms = s->clamp_lo & 3, wmt = s->clamp_lo >> 2 & 3;
    u32 w, h, n = 0, x, y, i, t, d, cv[4], ct[4], cd[4], fbmsk = s->frame_hi, v, pmsk;
    u32 zte = s->test_lo >> 16 & 1, zpsm = 0x30 | (s->zbuf_lo >> 24 & 15), zbp = (s->zbuf_lo & 0x1FF) * 32, z = s->z, zw, zb;
    s32 x0, y0, x1, y1, u0, v0, u1, v1, px0, px1, py0, py1, k, c, col[4], as, ad, f;
    const u32 *pal;
    int fsplit = 0;
    if ((p & 7) != 6 || (p & 0x110) != 0x110 || s->tex1_lo & 0x1E0 || tfx > 1 || wms > 1 || wmt > 1) return 0;
    if (p >> 5 & 1 && !(s->tests & 4)) return 0;                             /* FGE */
    if (fpsm != KH1_PSMCT32 && fpsm != KH1_PSMCT24) return 0;
    if (!fbw) return 0;
    if (!(s->tests & 1) && (s->test_lo & 1 || s->test_lo >> 14 & 1)) return 0; /* ATE, DATE */
    if (s->test_lo >> 14 & 1 && fpsm != KH1_PSMCT32) return 0;               /* DATE on a frame with no alpha */
    if (zte && !(ztst == 1 && s->zbuf_hi & 1) && !(s->tests & 2)) return 0;  /* a Z test or write */
    /* session 122 (tests bit 2): a Z buffer in a Z format, the vertex's Z clamped to it as the GS does */
    if (zte && s->tests & 2) {
        if (zpsm != KH1_PSMZ32 && zpsm != KH1_PSMZ24 && zpsm != KH1_PSMZ16 && zpsm != KH1_PSMZ16S) return 0;
        if (zpsm == KH1_PSMZ24 && z > 0xFFFFFF) z = 0xFFFFFF;
        if ((zpsm == KH1_PSMZ16 || zpsm == KH1_PSMZ16S) && z > 0xFFFF) z = 0xFFFF;
    }
    if (tw > 6 || th > 6 || kh1_gsmem_tex_target(s->tex0_lo, s->tex0_hi)) return 0;
    w = 1u << tw;
    h = 1u << th;
    /* session 117: an indexed texture through the present's palette cache, as kh1_gsmem_flat_sprite;
     * session 118: the stored texels from the present's texture cache when it has them */
    pal = 0;
    if (tex_ok(s->tex0_lo, s->tex0_hi) && indexed(s->tex0_lo >> 20 & 63) && kh1_gsmem_palette)
        pal = kh1_gsmem_palette(s->tex0_lo, s->tex0_hi, s->texa_lo, s->texa_hi);
    if (tex_ok(s->tex0_lo, s->tex0_hi) && (pal || kh1_gsmem_texels)) {
        u32 psm = s->tex0_lo >> 20 & 63, cpsm = cpsm_of(s->tex0_hi), csa = s->tex0_hi >> 24 & 31;
        const u32 *tt = kh1_gsmem_texels ? kh1_gsmem_texels(s->tex0_lo, s->tex0_hi) : 0;
        for (y = 0; y < h; y++)
            for (x = 0; x < w; x++) {
                v = tt ? tt[y * w + x] : kh1_gsmem_read_pixel(psm, s->tex0_lo & 0x3FFF, s->tex0_lo >> 14 & 63, x, y);
                tex[y * w + x] = pal ? pal[v] : value_rgba(psm, v, cpsm, csa, s->texa_lo, s->texa_hi);
            }
    } else if (kh1_gsmem_read_tex(s->tex0_lo, s->tex0_hi, s->texa_lo, s->texa_hi, tex))
        return 0;
    x0 = (s32)(s->xy[0] & 0xFFFF) - (s32)(s->xyoffset_lo & 0xFFFF);
    y0 = (s32)(s->xy[0] >> 16) - (s32)(s->xyoffset_hi & 0xFFFF);
    x1 = (s32)(s->xy[1] & 0xFFFF) - (s32)(s->xyoffset_lo & 0xFFFF);
    y1 = (s32)(s->xy[1] >> 16) - (s32)(s->xyoffset_hi & 0xFFFF);
    u0 = (s32)(s->uv[0] & 0x3FFF) + s->uorg; v0 = s->uv[0] >> 16 & 0x3FFF;
    u1 = (s32)(s->uv[1] & 0x3FFF) + s->uorg; v1 = s->uv[1] >> 16 & 0x3FFF;
    if (x1 < x0) { k = x0; x0 = x1; x1 = k; k = u0; u0 = u1; u1 = k; }
    if (y1 < y0) { k = y0; y0 = y1; y1 = k; k = v0; v0 = v1; v1 = k; }
    if (x1 == x0 || y1 == y0) return 1; /* nothing covered */
    px0 = (x0 + 15) >> 4; px1 = (x1 + 15) >> 4;
    py0 = (y0 + 15) >> 4; py1 = (y1 + 15) >> 4;
    if (px0 < (s32)(s->scissor_lo & 0x7FF)) px0 = s->scissor_lo & 0x7FF;
    if (px1 > (s32)(s->scissor_lo >> 16 & 0x7FF) + 1) px1 = (s->scissor_lo >> 16 & 0x7FF) + 1;
    if (py0 < (s32)(s->scissor_hi & 0x7FF)) py0 = s->scissor_hi & 0x7FF;
    if (py1 > (s32)(s->scissor_hi >> 16 & 0x7FF) + 1) py1 = (s->scissor_hi >> 16 & 0x7FF) + 1;
    if (px1 > px0 && py1 > py0 && (px1 - px0) * (py1 - py0) > 4096) return 0;
    for (i = 0; i < 4; i++) cv[i] = s->rgba >> i * 8 & 0xFF;
    seq++;
    useq++;
    /* session 135: the frame's addresses and each column's / row's texel as tables (addr_split) */
    if (px1 > px0 && py1 > py0) {
        fsplit = addr_split(SPLIT_FRAME, fpsm, fbp, fbw, px0, px1, py0, py1, sp_cx, sp_ry);
        for (c = px0; c < px1; c++) sp_tx[c - px0] = texel((u32)umax0(lerp_floor(u0, c * 16 - x0, u1 - u0, x1 - x0)) >> 4, w, wms);
        for (k = py0; k < py1; k++) sp_ty[k - py0] = texel((u32)lerp_floor(v0, k * 16 - y0, v1 - v0, y1 - y0) >> 4, h, wmt);
    }
    for (k = py0; k < py1; k++)
        for (c = px0; c < px1; c++) {
            u32 a = fsplit ? sp_cx[c - px0] + sp_ry[k - py0] : kh1_gsmem_addr(fpsm, fbp, fbw, c, k);
            t = tex[sp_ty[k - py0] * w + sp_tx[c - px0]];
            for (i = 0; i < 4; i++) ct[i] = t >> i * 8 & 0xFF;
            for (i = 0; i < 3; i++) col[i] = tfx ? ct[i] : clamp255(ct[i] * cv[i] >> 7);
            col[3] = tcc ? (tfx ? ct[3] : clamp255(ct[3] * cv[3] >> 7)) : cv[3];
            /* session 122 (tests bit 4): fog after the texture function, the colour only */
            if (p >> 5 & 1)
                for (i = 0; i < 3; i++)
                    col[i] = ((s->f & 0xFF) * (u32)col[i] + (0xFF - (s->f & 0xFF)) * (s->fogcol >> i * 8 & 0xFF)) >> 8;
            /* session 122 (tests bit 2): the Z test against the Z buffer's pixel; a fail writes nothing */
            zw = 0;
            if (zte && s->tests & 2) {
                zb = kh1_gsmem_read_pixel(zpsm, zbp, fbw, c, k);
                if (ztst == 0 || (ztst == 2 && z < zb) || (ztst == 3 && z <= zb)) continue;
                zw = !(s->zbuf_hi & 1);
            }
            d = read_at(fpsm, a);
            pmsk = fbmsk;
            /* session 121 (s->tests): DATE passes where Ad's bit 7 is DATM; a failed alpha test writes
             * by AFAIL: KEEP nothing, FB_ONLY the frame, ZB_ONLY the Z buffer (session 122: written
             * with tests bit 2, else nothing), RGB_ONLY the colour without the alpha */
            if (s->test_lo >> 14 & 1 && (d >> 31) != (s->test_lo >> 15 & 1)) continue;
            if (s->test_lo & 1 && !atst(s->test_lo >> 1 & 7, (u32)col[3], s->test_lo >> 4 & 0xFF)) {
                u32 afail = s->test_lo >> 12 & 3;
                if (afail == 2 && zw) put(zpsm, zbp, fbw, c, k, z);
                if (afail == 0 || afail == 2) continue;
                zw = 0;
                if (afail == 3) pmsk |= 0xFF000000u;
            }
            if (p >> 6 & 1) { /* ABE: ((A - B) x C >> 7) + D */
                for (i = 0; i < 4; i++) cd[i] = d >> i * 8 & 0xFF;
                as = col[3];
                ad = fpsm == KH1_PSMCT24 ? 0x80 : cd[3];
                f = s->alpha_lo >> 4 & 3;
                f = f == 0 ? as : f == 1 ? ad : (s32)(s->alpha_hi & 0xFF);
                for (i = 0; i < 3; i++) {
                    s32 a = sel(s->alpha_lo & 3, col[i], cd[i]), b = sel(s->alpha_lo >> 2 & 3, col[i], cd[i]);
                    s32 m = (a - b) * f;
                    col[i] = clamp255((m >= 0 ? m >> 7 : -((-m + 127) >> 7)) + sel(s->alpha_lo >> 6 & 3, col[i], cd[i]));
                }
            }
            v = col[0] | col[1] << 8 | col[2] << 16 | (u32)col[3] << 24;
            v = (d & pmsk) | (v & ~pmsk);
            put_at(fpsm, a, v);
            if (zw) put(zpsm, zbp, fbw, c, k, z);
            n++;
        }
    st.sprites++;
    st.sprite_pixels += n;
    return 1;
}

/* kh1_gsmem_flat_sprite (session 95, docs/renderer-spec.md 5.4 "Session 95"): an untextured SPRITE
 * (the clears, the display clear, fade, letterbox) filled into the model's pixels, so that
 * KH1_HOST_SHOT's present (host/null/present.c) shows them.  Off unless kh1_gsmem_flat(1): the present
 * turns it on.  The fill changes the pixels only: no page is marked as written (the draw stays a
 * draw, kh1_gsmem_draw marks its target as before, a render target is still one), no counter of the
 * targets / draws / uploads outputs moves (flat_sprites / flat_pixels are its own), so a run's trace
 * is the same with the switch on or off.  The GS rules as in kh1_gsmem_sprite: the pixels (X0 - OFX
 * + 15) >> 4 up to (X1 - OFX + 15) >> 4 inside SCISSOR, the second vertex's RGBA, ALPHA blending
 * with ABE, FBMSK kept; a CT32 / CT24 / CT16 / CT16S FRAME (CT16: RGBA 5551).  Not drawn (0): fog, a
 * Z test other than ALWAYS (the Z buffer is not written either), DATE, an alpha test that is not
 * decided by the flat alpha alone (ATST on the one value: pass draws, fail with AFAIL KEEP skips, any
 * other AFAIL is not modelled).
 *
 * Session 96: also a textured SPRITE kh1_gsmem_sprite refused (gs_sprite's flat pass runs only after
 * it), under the same switch and the same no-mark, no-counter rule: the frame copy D_002A6890 (the 3D
 * target 0x1A00 CT24, 512 x 512 texels, MMAG 1) is the one that matters, so the display shows what
 * the target holds.  Point-sampled whatever TEX1 says (the texel at the pixel's left / top edge, as
 * kh1_gsmem_sprite), the texture read as it is even in a target's pages, MODULATE / DECAL with TCC,
 * then the alpha test per texel (AFAIL KEEP only) and the blend as above.  Not drawn (0): FST 0
 * (STQ), TFX HIGHLIGHT(2), CLAMP's region modes, a PSM or CLUT the model has not.  Counted in
 * tex_sprites / tex_pixels.
 *
 * Session 106: the fill stops at the frame's width (FBW x 64) instead of wrapping (below). */
void kh1_gsmem_flat(int on) { flat_on = on; }

static u32 to16(u32 v) { return (v >> 3 & 0x1F) | (v >> 11 & 0x1F) << 5 | (v >> 19 & 0x1F) << 10 | (v >> 31) << 15; }
static u32 from16(u32 v) {
    return (v & 0x1F) << 3 | (v >> 5 & 0x1F) << 11 | (v >> 10 & 0x1F) << 19 | (v & 0x8000 ? 0x80000000u : 0);
}
static int atst(u32 m, u32 a, u32 ref) {
    switch (m) {
    case 0: return 0;
    case 1: return 1;
    case 2: return a < ref;
    case 3: return a <= ref;
    case 4: return a == ref;
    case 5: return a >= ref;
    case 6: return a > ref;
    }
    return a != ref;
}

int kh1_gsmem_flat_sprite(const KH1GsSprite *s) {
    u32 p = s->prim, fpsm = s->frame_lo >> 24 & 63, fbp = (s->frame_lo & 0x1FF) * 32, fbw = s->frame_lo >> 16 & 63;
    u32 ztst = s->test_lo >> 17 & 3, n = 0, i, d, cd[4], fbmsk = s->frame_hi, v, c16; /* FBMSK: CT32's bits */
    u32 tme = p >> 4 & 1, tfx = s->tex0_hi >> 3 & 3, tcc = s->tex0_hi >> 2 & 1, wms = s->clamp_lo & 3;
    u32 wmt = s->clamp_lo >> 2 & 3, tw = 1u << (s->tex0_lo >> 26 & 15), th = 1u << ((s->tex0_lo >> 30 | s->tex0_hi << 2) & 15);
    u32 tpsm = s->tex0_lo >> 20 & 63, tbp = s->tex0_lo & 0x3FFF, tbw = s->tex0_lo >> 14 & 63;
    u32 cpsm = cpsm_of(s->tex0_hi), csa = s->tex0_hi >> 24 & 31, t, tx, ty;
    s32 x0, y0, x1, y1, px0, px1, py0, py1, k, c, cv[4], cs[4], col[4], ad, f, u0 = 0, v0 = 0, u1 = 0, v1 = 0;
    const u32 *pal = 0, *tt = 0;
    int fsplit = 0, tsplit = 0;
    if (!flat_on) return 0;
    if ((p & 7) != 6 || p >> 5 & 1) return 0;                                /* a SPRITE, FGE 0 */
    /* session 96: a textured one the exact model refused (the frame copy D_002A6890: the 3D target,
     * 512 x 512, bilinear), point-sampled: FST 1, MODULATE / DECAL, CLAMP REPEAT / CLAMP */
    if (tme && (!(p >> 8 & 1) || tfx > 1 || wms > 1 || wmt > 1 || !tex_ok(s->tex0_lo, s->tex0_hi))) return 0;
    c16 = fpsm == KH1_PSMCT16 || fpsm == KH1_PSMCT16S;
    if (fpsm != KH1_PSMCT32 && fpsm != KH1_PSMCT24 && !c16) return 0;
    if (!fbw || s->test_lo >> 14 & 1) return 0;                              /* DATE */
    if (s->test_lo >> 16 & 1 && ztst != 1) return 0;                         /* a Z test */
    if (tme && s->test_lo & 1 && s->test_lo >> 12 & 3) return 0;             /* a per-texel alpha test, AFAIL not KEEP */
    for (i = 0; i < 4; i++) cv[i] = s->rgba >> i * 8 & 0xFF;
    if (!tme && s->test_lo & 1 && !atst(s->test_lo >> 1 & 7, (u32)cv[3], s->test_lo >> 4 & 0xFF)) {
        if (s->test_lo >> 12 & 3) return 0;                                  /* AFAIL not KEEP */
        return 1;                                                            /* nothing written */
    }
    x0 = (s32)(s->xy[0] & 0xFFFF) - (s32)(s->xyoffset_lo & 0xFFFF);
    y0 = (s32)(s->xy[0] >> 16) - (s32)(s->xyoffset_hi & 0xFFFF);
    x1 = (s32)(s->xy[1] & 0xFFFF) - (s32)(s->xyoffset_lo & 0xFFFF);
    y1 = (s32)(s->xy[1] >> 16) - (s32)(s->xyoffset_hi & 0xFFFF);
    if (tme) {
        u0 = (s32)(s->uv[0] & 0x3FFF) + s->uorg; v0 = s->uv[0] >> 16 & 0x3FFF;
        u1 = (s32)(s->uv[1] & 0x3FFF) + s->uorg; v1 = s->uv[1] >> 16 & 0x3FFF;
    }
    if (x1 < x0) { k = x0; x0 = x1; x1 = k; k = u0; u0 = u1; u1 = k; }
    if (y1 < y0) { k = y0; y0 = y1; y1 = k; k = v0; v0 = v1; v1 = k; }
    if (tme && (x1 == x0 || y1 == y0)) return 1;                             /* nothing covered */
    px0 = (x0 + 15) >> 4; px1 = (x1 + 15) >> 4;
    py0 = (y0 + 15) >> 4; py1 = (y1 + 15) >> 4;
    if (px0 < (s32)(s->scissor_lo & 0x7FF)) px0 = s->scissor_lo & 0x7FF;
    if (px1 > (s32)(s->scissor_lo >> 16 & 0x7FF) + 1) px1 = (s->scissor_lo >> 16 & 0x7FF) + 1;
    if (py0 < (s32)(s->scissor_hi & 0x7FF)) py0 = s->scissor_hi & 0x7FF;
    if (py1 > (s32)(s->scissor_hi >> 16 & 0x7FF) + 1) py1 = (s->scissor_hi >> 16 & 0x7FF) + 1;
    /* session 106 (vita-port-plan 5.1at): and inside the frame's width.  The GS would wrap a column
     * past FBW x 64 into the next page row; no 4:3 send reaches there, only a wide view's stretch into
     * a buffer of the PS2's width (the menu capture D_002B6760's KH1_FS_XS row, x 0 .. 338.8 into FBW
     * 4), which a port's own buffer holds whole.  The fill is the present's picture, so it keeps to
     * the buffer instead of writing over the next one (blocks 0x3900 .. 0x393F, the shared texture
     * slot); kh1_gsmem_sprite keeps the GS's wrap */
    if (px1 > (s32)fbw * 64) px1 = fbw * 64;
    /* session 117: an indexed texture's palette from the port's cache (host/null/present.c), the
     * texel's index looked up in it; 0 (no cache, or every slot in use) decodes from the CLUT buffer */
    if (tme && indexed(tpsm) && kh1_gsmem_palette) pal = kh1_gsmem_palette(s->tex0_lo, s->tex0_hi, s->texa_lo, s->texa_hi);
    /* session 118: the stored texels from the present's texture cache; 0 (a render target's texture,
     * the frame copy's 3D target, or not kept) reads GS memory */
    if (tme && kh1_gsmem_texels) tt = kh1_gsmem_texels(s->tex0_lo, s->tex0_hi);
    /* session 135: the frame's addresses and each column's / row's texel as tables (addr_split) */
    if (px1 > px0 && py1 > py0) {
        fsplit = addr_split(SPLIT_FRAME, fpsm, fbp, fbw, px0, px1, py0, py1, sp_cx, sp_ry);
        if (tme) {
            for (c = px0; c < px1; c++) sp_tx[c - px0] = texel((u32)umax0(lerp_floor(u0, c * 16 - x0, u1 - u0, x1 - x0)) >> 4, tw, wms);
            for (k = py0; k < py1; k++) sp_ty[k - py0] = texel((u32)lerp_floor(v0, k * 16 - y0, v1 - v0, y1 - y0) >> 4, th, wmt);
            if (!tt) tsplit = addr_split(SPLIT_TEX, tpsm, tbp, tbw, 0, (s32)tw, 0, (s32)th, sp_tcx, sp_try);
        }
    }
    /* session 135: a quad's weights a column / row: the pixel centre's place between the corners, 0 .. 256 */
    if (s->quad && px1 > px0 && py1 > py0) {
        for (c = px0; c < px1; c++) {
            s32 fx = x1 > x0 ? ((c * 16 + 8 - x0) << 8) / (x1 - x0) : 0;
            qfx[c - px0] = fx < 0 ? 0 : fx > 256 ? 256 : fx;
        }
        for (k = py0; k < py1; k++) {
            s32 fy = y1 > y0 ? ((k * 16 + 8 - y0) << 8) / (y1 - y0) : 0;
            qfy[k - py0] = fy < 0 ? 0 : fy > 256 ? 256 : fy;
        }
    }
    flat_raw = 1;
    /* session 135: the title's every-frame work in three loops of their own, the same pixels as the loop
     * below (tests/host/gsfast_test.c): an untextured fill (the clears) and a textured copy with nothing
     * between texel and pixel (the frame copy: no blend, no FBMSK, no alpha test, DECAL or MODULATE by
     * 0x80, a CT32 / CT24 texture), into a CT32 / CT24 frame whose addresses split; and a cached
     * texture's art with its blend */
    if (fsplit && !c16 && !fbmsk) {
        u32 keep = fpsm == KH1_PSMCT24 ? 0xFF000000u : 0, set;
        if (!tme && !(p >> 6 & 1) && !s->quad) {
            set = (cv[0] | cv[1] << 8 | cv[2] << 16 | (u32)cv[3] << 24) & ~keep;
            for (k = py0; k < py1; k++) {
                u32 fr = sp_ry[k - py0];
                for (c = px0; c < px1; c++) {
                    u32 a = sp_cx[c - px0] + fr;
                    st32(a, (ld32(a) & keep) | set);
                }
            }
            n = (u32)((px1 - px0) * (py1 - py0));
            goto done;
        }
        if (tme && !(p >> 6 & 1) && !s->quad && !pal && !(s->test_lo & 1) && (tt || tsplit) && (tpsm == KH1_PSMCT32 || tpsm == KH1_PSMCT24) &&
            (tfx || (cv[0] == 0x80 && cv[1] == 0x80 && cv[2] == 0x80 && (!tcc || cv[3] == 0x80)))) {
            u32 amask = tcc ? 0xFF000000u : 0, aset = tcc ? 0 : (u32)cv[3] << 24;
            /* value_rgba's CT24 alpha: TA0, or 0 for black with AEM */
            u32 t24 = tpsm == KH1_PSMCT24, ta0 = (s->texa_lo & 0xFF) << 24, aem = s->texa_lo >> 15 & 1;
            for (k = py0; k < py1; k++) {
                u32 fr = sp_ry[k - py0], trow;
                ty = sp_ty[k - py0];
                trow = tt ? ty * tw : sp_try[ty];
                for (c = px0; c < px1; c++) {
                    u32 a = sp_cx[c - px0] + fr;
                    tx = sp_tx[c - px0];
                    t = tt ? tt[trow + tx] : ld32(sp_tcx[tx] + trow);
                    if (t24) {
                        t &= 0xFFFFFF;
                        t |= aem && !t ? 0 : ta0;
                    }
                    st32(a, (ld32(a) & keep) | (((t & (0xFFFFFF | amask)) | aset) & ~keep));
                }
            }
            n = (u32)((px1 - px0) * (py1 - py0));
            goto done;
        }
        /* the art and the fades: a cached texture (the present's texture and palette caches: a copy
         * taken before the draw), a CT32 / CT24 one read in place (a render target's: the art behind
         * the logo) or none, any TFX the flat sprite takes, the alpha test (AFAIL KEEP), any blend,
         * the menu's quads (their colour a pixel from qfx / qfy) */
        if (tt || !tme || (tsplit && (tpsm == KH1_PSMCT32 || tpsm == KH1_PSMCT24))) {
            u32 sa = s->alpha_lo & 3, sb = s->alpha_lo >> 2 & 3, sc = s->alpha_lo >> 4 & 3, sd = s->alpha_lo >> 6 & 3;
            u32 abe = p >> 6 & 1, ate = s->test_lo & 1, am = s->test_lo >> 1 & 7, aref = s->test_lo >> 4 & 0xFF;
            u32 t24 = tpsm == KH1_PSMCT24;
            s32 fix = (s32)(s->alpha_hi & 0xFF), v3[3], mix = sa == 0 && sb == 1 && sd == 1;
            /* a palette's entries as the texture function makes them, once a sprite (not with a quad's
             * colours, which change a pixel) */
            int pm = tme && pal && !s->quad;
            if (pm) {
                u32 ne = bits8(tpsm) ? 256 : 16;
                for (i = 0; i < ne; i++) {
                    t = pal[i];
                    if (tfx) {
                        col[0] = t & 0xFF; col[1] = t >> 8 & 0xFF; col[2] = t >> 16 & 0xFF;
                        col[3] = tcc ? (s32)(t >> 24) : cv[3];
                    } else {
                        col[0] = clamp255((s32)(t & 0xFF) * cv[0] >> 7);
                        col[1] = clamp255((s32)(t >> 8 & 0xFF) * cv[1] >> 7);
                        col[2] = clamp255((s32)(t >> 16 & 0xFF) * cv[2] >> 7);
                        col[3] = tcc ? clamp255((s32)(t >> 24) * cv[3] >> 7) : cv[3];
                    }
                    sp_pm[i] = col[0] | col[1] << 8 | col[2] << 16 | (u32)col[3] << 24;
                }
            }
            /* the art's own case: (Cs - Cd) x As + Cd into CT32 from a palette's entries or CT32 texels
             * that the texture function leaves (DECAL, or MODULATE by 0x80), no alpha test; As 0 keeps
             * Cd and As 0x80 is Cs, exactly */
            if (tme && abe && mix && sc == 0 && !ate && !s->quad && !keep &&
                (pm || (tpsm == KH1_PSMCT32 && (tfx || (cv[0] == 0x80 && cv[1] == 0x80 && cv[2] == 0x80))))) {
                for (i = 0; i < 256; i++) sp_al[i] = (tcc ? (tfx ? i : (u32)clamp255((s32)i * cv[3] >> 7)) : (u32)cv[3]) << 24;
                for (k = py0; k < py1; k++) {
                    u32 fr = sp_ry[k - py0];
                    const u32 *trow = tt ? tt + sp_ty[k - py0] * tw : 0;
                    u32 tr = !tt ? sp_try[sp_ty[k - py0]] : 0;
                    for (c = px0; c < px1; c++) {
                        u32 a = sp_cx[c - px0] + fr, sv;
                        t = tt ? trow[sp_tx[c - px0]] : ld32(sp_tcx[sp_tx[c - px0]] + tr);
                        sv = pm ? sp_pm[t] : (t & 0xFFFFFF) | sp_al[t >> 24];
                        f = (s32)(sv >> 24);
                        d = ld32(a);
                        if (f == 0) {
                            sv = (d & 0xFFFFFF) | (sv & 0xFF000000u);
                        } else if (f != 0x80) {
                            u32 o = sv & 0xFF000000u;
                            for (i = 0; i < 3; i++) {
                                s32 cd1 = (s32)(d >> i * 8 & 0xFF), m = ((s32)(sv >> i * 8 & 0xFF) - cd1) * f;
                                o |= (u32)clamp255((m >= 0 ? m >> 7 : -((-m + 127) >> 7)) + cd1) << i * 8;
                            }
                            sv = o;
                        }
                        st32(a, sv);
                    }
                }
                n = (u32)((px1 - px0) * (py1 - py0));
                goto done;
            }
            for (k = py0; k < py1; k++) {
                u32 fr = sp_ry[k - py0];
                const u32 *trow = tt ? tt + sp_ty[k - py0] * tw : 0;
                u32 tr = tme && !tt ? sp_try[sp_ty[k - py0]] : 0;
                for (c = px0; c < px1; c++) {
                    u32 a = sp_cx[c - px0] + fr, dv;
                    if (s->quad) quad_cv(s, qfx[c - px0], qfy[k - py0], cv);
                    if (!tme) {
                        col[0] = cv[0]; col[1] = cv[1]; col[2] = cv[2]; col[3] = cv[3];
                    } else {
                        if (tt) {
                            t = trow[sp_tx[c - px0]];
                        } else {
                            t = ld32(sp_tcx[sp_tx[c - px0]] + tr);
                            if (t24) t &= 0xFFFFFF;
                        }
                        if (pm) {
                            t = sp_pm[t];
                            col[0] = t & 0xFF; col[1] = t >> 8 & 0xFF; col[2] = t >> 16 & 0xFF; col[3] = (s32)(t >> 24);
                        } else {
                            t = pal ? pal[t] : value_rgba(tpsm, t, cpsm, csa, s->texa_lo, s->texa_hi);
                            if (tfx) {
                                col[0] = t & 0xFF; col[1] = t >> 8 & 0xFF; col[2] = t >> 16 & 0xFF;
                                col[3] = tcc ? (s32)(t >> 24) : cv[3];
                            } else {
                                col[0] = clamp255((s32)(t & 0xFF) * cv[0] >> 7);
                                col[1] = clamp255((s32)(t >> 8 & 0xFF) * cv[1] >> 7);
                                col[2] = clamp255((s32)(t >> 16 & 0xFF) * cv[2] >> 7);
                                col[3] = tcc ? clamp255((s32)(t >> 24) * cv[3] >> 7) : cv[3];
                            }
                        }
                    }
                    if (tme && ate && !atst(am, (u32)col[3], aref)) continue;
                    d = ld32(a);
                    if (abe) { /* ((A - B) x C >> 7) + D, as the loop below */
                        s32 cdv[4], f;
                        cdv[0] = d & 0xFF; cdv[1] = d >> 8 & 0xFF; cdv[2] = d >> 16 & 0xFF; cdv[3] = d >> 24;
                        f = sc == 0 ? col[3] : sc == 1 ? (fpsm == KH1_PSMCT24 ? 0x80 : cdv[3]) : fix;
                        if (mix) /* (Cs - Cd) x C + Cd, the usual one */
                            for (i = 0; i < 3; i++) {
                                s32 m = (col[i] - cdv[i]) * f;
                                v3[i] = clamp255((m >= 0 ? m >> 7 : -((-m + 127) >> 7)) + cdv[i]);
                            }
                        else
                            for (i = 0; i < 3; i++) {
                                s32 cs = col[i], m;
                                m = (sel(sa, cs, cdv[i]) - sel(sb, cs, cdv[i])) * f;
                                v3[i] = clamp255((m >= 0 ? m >> 7 : -((-m + 127) >> 7)) + sel(sd, cs, cdv[i]));
                            }
                        col[0] = v3[0]; col[1] = v3[1]; col[2] = v3[2];
                    }
                    dv = col[0] | col[1] << 8 | col[2] << 16 | (u32)col[3] << 24;
                    st32(a, (d & keep) | (dv & ~keep));
                    n++;
                }
            }
            goto done;
        }
    }
    for (k = py0; k < py1; k++) {
        u32 fr = fsplit ? sp_ry[k - py0] : 0, a;
        ty = tme ? sp_ty[k - py0] : 0;
        for (c = px0; c < px1; c++) {
            if (s->quad) quad_cv(s, qfx[c - px0], qfy[k - py0], cv);
            for (i = 0; i < 4; i++) col[i] = cv[i];
            if (tme) { /* the texel at the pixel's left / top edge, as kh1_gsmem_sprite */
                tx = sp_tx[c - px0];
                t = tt ? tt[ty * tw + tx] : tsplit ? read_at(tpsm, sp_tcx[tx] + sp_try[ty]) : kh1_gsmem_read_pixel(tpsm, tbp, tbw, tx, ty);
                t = pal ? pal[t] : value_rgba(tpsm, t, cpsm, csa, s->texa_lo, s->texa_hi);
                for (i = 0; i < 3; i++) col[i] = tfx ? (s32)(t >> i * 8 & 0xFF) : clamp255((s32)(t >> i * 8 & 0xFF) * cv[i] >> 7);
                col[3] = tcc ? (tfx ? (s32)(t >> 24) : clamp255((s32)(t >> 24) * cv[3] >> 7)) : cv[3];
                if (s->test_lo & 1 && !atst(s->test_lo >> 1 & 7, (u32)col[3], s->test_lo >> 4 & 0xFF)) continue;
            }
            a = fsplit ? sp_cx[c - px0] + fr : kh1_gsmem_addr(fpsm, fbp, fbw, c, k);
            d = read_at(fpsm, a);
            if (c16) d = from16(d);
            if (p >> 6 & 1) { /* ABE: ((A - B) x C >> 7) + D */
                for (i = 0; i < 4; i++) { cd[i] = d >> i * 8 & 0xFF; cs[i] = col[i]; }
                ad = fpsm == KH1_PSMCT24 ? 0x80 : cd[3];
                f = s->alpha_lo >> 4 & 3;
                f = f == 0 ? cs[3] : f == 1 ? ad : (s32)(s->alpha_hi & 0xFF);
                for (i = 0; i < 3; i++) {
                    s32 a = sel(s->alpha_lo & 3, cs[i], cd[i]), b = sel(s->alpha_lo >> 2 & 3, cs[i], cd[i]);
                    s32 m = (a - b) * f;
                    col[i] = clamp255((m >= 0 ? m >> 7 : -((-m + 127) >> 7)) + sel(s->alpha_lo >> 6 & 3, cs[i], cd[i]));
                }
            }
            v = col[0] | col[1] << 8 | col[2] << 16 | (u32)col[3] << 24;
            v = (d & fbmsk) | (v & ~fbmsk);
            put_at(fpsm, a, c16 ? to16(v) : v);
            n++;
        }
    }
done:
    flat_raw = 0;
    if (tme) {
        st.tex_sprites++;
        st.tex_pixels += n;
    } else {
        st.flat_sprites++;
        st.flat_pixels += n;
    }
    return 1;
}

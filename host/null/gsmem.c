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

void *memset(void *, int, __SIZE_TYPE__);

#define VM_BYTES (4u << 20)
#define LOG 256
#define TARGETS 32

static u8 vm[VM_BYTES];
static u16 clut[512];
static u32 cbp0, cbp1;
static u32 seq, page_seq[512], clut_seq;
static KH1GsMemStats st;
static KH1GsUpload log_[LOG];
static u32 nlog;
static KH1GsTarget tgt[TARGETS];
static u32 ntgt, useq, tgt_useq[TARGETS]; /* useq counts uploads, copies and pixel writes; tgt_useq: its
                                            * value when the target's pages were last marked */
static u32 page_drawn[512];          /* the word bits a draw changed and no upload wrote since */
static u8 page_tgt[512];             /* 1 + the target that drew there last */

/* the transfer in progress */
static struct {
    u32 active, psm, bp, bw, x0, y0, w, h, x, y;
    u32 acc, nacc, bytes; /* the pixel being assembled, its bytes so far, bytes a pixel (0: 4 bits) */
    KH1GsUpload *log;
} trx;

void kh1_gsmem_reset(void) {
    memset(vm, 0, sizeof vm);
    memset(clut, 0, sizeof clut);
    memset(page_seq, 0, sizeof page_seq);
    memset(&st, 0, sizeof st);
    memset(&trx, 0, sizeof trx);
    memset(tgt, 0, sizeof tgt);
    memset(page_drawn, 0, sizeof page_drawn);
    memset(page_tgt, 0, sizeof page_tgt);
    cbp0 = cbp1 = seq = clut_seq = nlog = ntgt = useq = 0;
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

static u32 rd32(u32 w) { const u8 *p = vm + w * 4; return p[0] | p[1] << 8 | p[2] << 16 | (u32)p[3] << 24; }
/* bits: the word bits the write stores, no longer a draw's */
static void wr32(u32 w, u32 v, u32 bits) {
    u8 *p = vm + w * 4;
    p[0] = v; p[1] = v >> 8; p[2] = v >> 16; p[3] = v >> 24;
    page_seq[w >> 11] = seq;
    page_drawn[w >> 11] &= ~bits;
}

u32 kh1_gsmem_read_pixel(u32 psm, u32 bp, u32 bw, u32 x, u32 y) {
    u32 a = kh1_gsmem_addr(psm, bp, bw, x, y);
    switch (psm) {
    case KH1_PSMCT32: case KH1_PSMZ32: return rd32(a);
    case KH1_PSMCT24: case KH1_PSMZ24: return rd32(a) & 0xFFFFFF;
    case KH1_PSMT8H:  return rd32(a) >> 24;
    case KH1_PSMT4HL: return rd32(a) >> 24 & 15;
    case KH1_PSMT4HH: return rd32(a) >> 28;
    case KH1_PSMCT16: case KH1_PSMCT16S: case KH1_PSMZ16: case KH1_PSMZ16S: return vm[a * 2] | vm[a * 2 + 1] << 8;
    case KH1_PSMT8:   return vm[a];
    case KH1_PSMT4:   return vm[a >> 1] >> (a & 1) * 4 & 15;
    }
    return 0;
}

static void put(u32 psm, u32 bp, u32 bw, u32 x, u32 y, u32 v) {
    u32 a = kh1_gsmem_addr(psm, bp, bw, x, y);
    switch (psm) {
    case KH1_PSMCT32: case KH1_PSMZ32: wr32(a, v, ~0u); return;
    case KH1_PSMCT24: case KH1_PSMZ24: wr32(a, (rd32(a) & 0xFF000000u) | (v & 0xFFFFFF), 0x00FFFFFF); return;
    case KH1_PSMT8H:  wr32(a, (rd32(a) & 0x00FFFFFF) | v << 24, 0xFF000000u); return;
    case KH1_PSMT4HL: wr32(a, (rd32(a) & 0xF0FFFFFFu) | (v & 15) << 24, 0x0F000000); return;
    case KH1_PSMT4HH: wr32(a, (rd32(a) & 0x0FFFFFFF) | v << 28, 0xF0000000u); return;
    /* the 16-, 8- and 4-bit layouts do not share CT32's word: the page is no longer a draw's */
    case KH1_PSMCT16: case KH1_PSMCT16S: case KH1_PSMZ16: case KH1_PSMZ16S:
        vm[a * 2] = v; vm[a * 2 + 1] = v >> 8; page_seq[a >> 12] = seq; page_drawn[a >> 12] = 0; return;
    case KH1_PSMT8:   vm[a] = v; page_seq[a >> 13] = seq; page_drawn[a >> 13] = 0; return;
    case KH1_PSMT4:
        vm[a >> 1] = (vm[a >> 1] & (0xF0 >> (a & 1) * 4)) | (v & 15) << (a & 1) * 4;
        page_seq[a >> 14] = seq;
        page_drawn[a >> 14] = 0;
        return;
    }
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

void kh1_gsmem_trxdir(u32 dir, u32 bb_lo, u32 bb_hi, u32 pos_lo, u32 pos_hi, u32 reg_lo, u32 reg_hi) {
    u32 dpsm = bb_hi >> 24 & 63, dbp = bb_hi & 0x3FFF, dbw = bb_hi >> 16 & 63;
    u32 dx = pos_hi & 2047, dy = pos_hi >> 16 & 2047, w = reg_lo & 0xFFF, h = reg_hi & 0xFFF;
    KH1GsUpload *l = nlog < LOG ? &log_[nlog] : 0;
    trx.active = 0;
    trx.log = 0;
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
        return;
    }
    /* local->local, in the pixel order TRXPOS.DIR gives (0 from the top left, 1 bottom left, 2 top
     * right, 3 bottom right), as the GS copies an overlap; each pixel's stored bits as they are */
    {
        u32 spsm = bb_lo >> 24 & 63, sbp = bb_lo & 0x3FFF, sbw = bb_lo >> 16 & 63;
        u32 sx = pos_lo & 2047, sy = pos_lo >> 16 & 2047, order = pos_hi >> 27 & 3, i, j;
        st.copies++;
        if (!known(spsm) || !known(dpsm)) { if (known(dpsm)) st.unsupported++; return; }
        for (j = 0; j < h; j++) {
            u32 y = order & 1 ? h - 1 - j : j;
            for (i = 0; i < w; i++) {
                u32 x = order & 2 ? w - 1 - i : i;
                put(dpsm, dbp, dbw, dx + x, dy + y, kh1_gsmem_read_pixel(spsm, sbp, sbw, sx + x, sy + y));
            }
        }
        if (l) l->pixels = w * h;
    }
}

static void trx_pixel(u32 v) {
    if (known(trx.psm)) put(trx.psm, trx.bp, trx.bw, trx.x, trx.y, v);
    st.pixels++;
    if (trx.log) trx.log->pixels++;
    if (++trx.x == trx.x0 + trx.w) {
        trx.x = trx.x0;
        if (++trx.y == trx.y0 + trx.h) trx.active = 0;
    }
}

void kh1_gsmem_image(const u32 *w, u32 n) {
    u32 i, b;
    if (!trx.active) { st.extra++; return; }
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
static int bits8(u32 psm) { return psm == KH1_PSMT8 || psm == KH1_PSMT8H; }
static int indexed(u32 psm) { return bits8(psm) || psm == KH1_PSMT4 || psm == KH1_PSMT4HL || psm == KH1_PSMT4HH; }

void kh1_gsmem_tex0(u32 lo, u32 hi) {
    u32 psm = lo >> 20 & 63, cbp = hi >> 5 & 0x3FFF, cpsm = hi >> 19 & 15, csm = hi >> 23 & 1;
    u32 csa = hi >> 24 & 31, cld = hi >> 29 & 7, e, p, v;
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
    if (bits8(psm)) {
        for (e = 0; e < 256; e++) {
            p = (e & 0xE7) | (e & 8) << 1 | (e & 0x10) >> 1; /* entries 8-15 / 16-23 of each 32 swapped */
            v = kh1_gsmem_read_pixel(cpsm, cbp, 1, p & 15, p >> 4);
            clut[e] = v;
            if (cpsm == KH1_PSMCT32) clut[e + 256] = v >> 16;
        }
        return;
    }
    for (e = 0; e < 16; e++) {
        v = kh1_gsmem_read_pixel(cpsm, cbp, 1, e & 7, e >> 3);
        if (cpsm == KH1_PSMCT32) {
            clut[(csa & 15) * 16 + e] = v;
            clut[(csa & 15) * 16 + e + 256] = v >> 16;
        } else {
            clut[csa * 16 + e] = v;
        }
    }
}

/* a CT16 colour (or CLUT entry) to RGBA8: 5 bits a channel shifted up 3, A from TEXA (TA1 with the
 * STP bit; else TA0, or 0 for black with AEM) */
static u32 rgba16(u32 v, u32 texa_lo, u32 texa_hi) {
    u32 a = v & 0x8000 ? texa_hi & 0xFF : (texa_lo >> 15 & 1) && !(v & 0x7FFF) ? 0 : texa_lo & 0xFF;
    return (v & 31) << 3 | (v >> 5 & 31) << 11 | (v >> 10 & 31) << 19 | a << 24;
}

int kh1_gsmem_read_tex(u32 lo, u32 hi, u32 texa_lo, u32 texa_hi, u32 *out) {
    u32 tbp = lo & 0x3FFF, tbw = lo >> 14 & 63, psm = lo >> 20 & 63, tw = lo >> 26 & 15;
    u32 th = (lo >> 30 | hi << 2) & 15, cpsm = hi >> 19 & 15, csa = hi >> 24 & 31, w, h, x, y, v, e;
    if (!known(psm) || tw > 10 || th > 10) { st.unsupported++; return -1; }
    if (indexed(psm) && (hi >> 23 & 1 || !clut_psm(cpsm) || (bits8(psm) && csa))) {
        st.unsupported++;
        return -1;
    }
    w = 1u << tw;
    h = 1u << th;
    for (y = 0; y < h; y++)
        for (x = 0; x < w; x++) {
            v = kh1_gsmem_read_pixel(psm, tbp, tbw, x, y);
            switch (psm) {
            case KH1_PSMCT32: case KH1_PSMZ32: break;
            case KH1_PSMCT24: case KH1_PSMZ24: v |= ((texa_lo >> 15 & 1) && !v ? 0 : texa_lo & 0xFF) << 24; break;
            case KH1_PSMCT16: case KH1_PSMCT16S: case KH1_PSMZ16: case KH1_PSMZ16S:
                v = rgba16(v, texa_lo, texa_hi);
                break;
            default: /* indexed: 8 bits from entry 0, 4 bits from CSA's 16 */
                e = bits8(psm) ? v : (cpsm == KH1_PSMCT32 ? csa & 15 : csa) * 16 + v;
                v = cpsm == KH1_PSMCT32 ? clut[e] | (u32)clut[e + 256] << 16 : rgba16(clut[e & 511], texa_lo, texa_hi);
                break;
            }
            out[y * w + x] = v;
        }
    return 0;
}

/* the pages a texture's w x h texels lie in: the newest write's sequence number, and with *t the
 * first page whose drawn bits it reads (1 + its target, 0 for none) */
static u32 tex_scan(u32 lo, u32 hi, u32 *t) {
    u32 tbp = lo & 0x3FFF, tbw = lo >> 14 & 63, psm = lo >> 20 & 63, tw = lo >> 26 & 15;
    u32 th = (lo >> 30 | hi << 2) & 15, bwid, bhgt, x, y, a, page, s = 0, bits;
    *t = 0;
    if (!known(psm)) return 0;
    bwid = psm == KH1_PSMT4 ? 32 : bits16(psm) || psm == KH1_PSMT8 ? 16 : 8;
    bhgt = psm == KH1_PSMT8 || psm == KH1_PSMT4 ? 16 : 8;
    switch (psm) {
    case KH1_PSMCT24: case KH1_PSMZ24: bits = 0x00FFFFFF; break;
    case KH1_PSMT8H:  bits = 0xFF000000u; break;
    case KH1_PSMT4HL: bits = 0x0F000000; break;
    case KH1_PSMT4HH: bits = 0xF0000000u; break;
    default: bits = ~0u; break;
    }
    if (tw > 10 || th > 10) return 0;
    /* one address a block: a block never spans two pages */
    for (y = 0; y < 1u << th; y += bhgt)
        for (x = 0; x < 1u << tw; x += bwid) {
            a = kh1_gsmem_addr(psm, tbp, tbw, x, y);
            page = page_of(psm, a);
            if (page_seq[page] > s) s = page_seq[page];
            if (!*t && page_drawn[page] & bits) *t = page_tgt[page];
        }
    return s;
}

u32 kh1_gsmem_tex_stamp(u32 lo, u32 hi) {
    u32 t;
    return tex_scan(lo, hi, &t);
}

u32 kh1_gsmem_tex_target(u32 lo, u32 hi) {
    u32 t;
    tex_scan(lo, hi, &t);
    return t;
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

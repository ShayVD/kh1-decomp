/* KH1_HOST_TRACE=2: walk each chain a send starts, tag by tag, the way the DMAC's source chain
 * mode does (docs/renderer-spec.md 4.4), and print one line per send; a chain that reaches
 * memory the host does not own (where() answers 0), a tag with a bad id, a call past the
 * two-deep stack or a chain that does not end prints each tag.  KH1_HOST_TRACE=3 prints every
 * tag.  Only reads: nothing is transferred.
 *
 * The data the chain sends is then read the way its receiver would (renderer-spec 4.5), the
 * first step of the Vita's GIF parser: on the GIF channel (2) one stream of GIF packets (a
 * GIFtag, then NLOOP x NREG qwords PACKED, half that REGLIST, NLOOP IMAGE) across the chain's
 * data, without the tags (TTE has no effect on the GIF channel, 4.4); on VIF1 (1) one stream
 * of VIF codes and their data, with each tag's upper 64 bits first when TTE is set (VIF0, 0,
 * the same without the codes VIF0 lacks).  A chain
 * that ends inside a GIF packet or a VIF code's data, or a word that is no VIF code, is a
 * problem; each data block that starts inside a packet is counted (an IMAGE's REF data after
 * the cnt that holds its GIFtag does). */
#include "common.h"
#include "dmawalk.h"

int printf(const char *, ...);
int sprintf(char *, const char *, ...);
__SIZE_TYPE__ strlen(const char *);

typedef struct {
    u32 left;    /* qwords (REGLIST: 64-bit words) of the current packet still to come */
    u32 flg, nreg, k;
    u32 regs[16];
    u32 packets, eop, image, blocks, mid;
    u32 set[4];  /* the GS registers written (by address, bit per register: PACKED, REGLIST, A+D) */
} GifStream;

typedef struct {
    u32 need;    /* data words of the current code still to come */
    u32 pad;     /* words to skip before them (DIRECT / MPG data is aligned) */
    u32 pos;     /* word position in the stream, mod 4 */
    u32 cl, wl;  /* STCYCL */
    u32 vif0;    /* VIF0 has no OFFSET, BASE, MSKPATH3 or DIRECT */
    u32 codes, unpacks, direct, blocks, mid, bad, bad_word, bad_addr;
    u32 in_direct, nq, q[4];
    GifStream gif; /* PATH2: every DIRECT's data, one stream of GIF packets */
} VifStream;

static void gif_set(GifStream *g, u32 reg) {
    if (reg < 128) g->set[reg >> 5] |= 1u << (reg & 31);
}

/* one qword of the GIF stream: a GIFtag, or the next qword of the current packet */
static void gif_qword(GifStream *g, const u32 *q) {
    u32 nloop, h;
    if (g->left) {
        if (g->flg == 0) {
            u32 d = g->regs[g->k++ % g->nreg];
            gif_set(g, d == 0xE ? (q[2] & 0x7F) : d);
            g->left--;
        } else if (g->flg == 1) {
            for (h = 0; h < 2 && g->left; h++, g->left--) {
                u32 d = g->regs[g->k++ % g->nreg];
                if (d != 0xE) gif_set(g, d);
            }
        } else {
            g->left--;
        }
        return;
    }
    nloop = q[0] & 0x7FFF;
    g->flg = q[1] >> 26 & 3;
    g->nreg = q[1] >> 28 & 15;
    if (!g->nreg) g->nreg = 16;
    for (h = 0; h < g->nreg; h++) g->regs[h] = q[2 + h / 8] >> (h % 8 * 4) & 15;
    g->k = 0;
    g->packets++;
    if (q[0] & 0x8000) g->eop++;
    if (g->flg == 0 && q[1] >> 14 & 1) gif_set(g, 0); /* PRE: PRIM from the tag */
    if (g->flg == 0) g->left = nloop * g->nreg;
    else if (g->flg == 1) g->left = (nloop * g->nreg + 1) & ~1u;
    else { g->left = nloop; g->image++; }
}

static void gif_block(GifStream *g, const u32 *q, u32 n) {
    u32 i;
    if (!n) return;
    g->blocks++;
    if (g->left) g->mid++;
    for (i = 0; i < n; i++, q += 4) gif_qword(g, q);
}

/* the state registers a stream wrote (not the vertex ones), as names */
static void gif_regs(const GifStream *g, char *out) {
    static const struct { u8 reg; const char *name; } names[] = {
        { 0x00, "PRIM" }, { 0x06, "TEX0_1" }, { 0x07, "TEX0_2" }, { 0x08, "CLAMP_1" }, { 0x09, "CLAMP_2" },
        { 0x14, "TEX1_1" }, { 0x15, "TEX1_2" }, { 0x16, "TEX2_1" }, { 0x17, "TEX2_2" }, { 0x18, "XYOFFSET_1" },
        { 0x19, "XYOFFSET_2" }, { 0x1A, "PRMODECONT" }, { 0x1B, "PRMODE" }, { 0x1C, "TEXCLUT" },
        { 0x22, "SCANMSK" }, { 0x34, "MIPTBP1_1" }, { 0x35, "MIPTBP1_2" }, { 0x36, "MIPTBP2_1" },
        { 0x37, "MIPTBP2_2" }, { 0x3B, "TEXA" }, { 0x3D, "FOGCOL" }, { 0x3F, "TEXFLUSH" }, { 0x40, "SCISSOR_1" },
        { 0x41, "SCISSOR_2" }, { 0x42, "ALPHA_1" }, { 0x43, "ALPHA_2" }, { 0x44, "DIMX" }, { 0x45, "DTHE" },
        { 0x46, "COLCLAMP" }, { 0x47, "TEST_1" }, { 0x48, "TEST_2" }, { 0x49, "PABE" }, { 0x4A, "FBA_1" },
        { 0x4B, "FBA_2" }, { 0x4C, "FRAME_1" }, { 0x4D, "FRAME_2" }, { 0x4E, "ZBUF_1" }, { 0x4F, "ZBUF_2" },
        { 0x50, "BITBLTBUF" }, { 0x51, "TRXPOS" }, { 0x52, "TRXREG" }, { 0x53, "TRXDIR" }, { 0x54, "HWREG" }, { 0x60, "SIGNAL" },
        { 0x61, "FINISH" }, { 0x62, "LABEL" },
    };
    u32 i, r, known[4] = { 0x0000F43E, 0, 0, 0 }; /* the vertex registers 1-5, 0xA, 0xC-0xD, A+D, NOP */
    *out = 0;
    for (i = 0; i < sizeof names / sizeof names[0]; i++) {
        r = names[i].reg;
        known[r >> 5] |= 1u << (r & 31);
        if (g->set[r >> 5] >> (r & 31) & 1) sprintf(out + strlen(out), " %s", names[i].name);
    }
    for (r = 0; r < 128; r++)
        if ((g->set[r >> 5] & ~known[r >> 5]) >> (r & 31) & 1) sprintf(out + strlen(out), " reg%02x", r);
}

/* the words an UNPACK reads: num vectors written, CL of each WL read when WL > CL */
static u32 vif_unpack_words(VifStream *v, u32 cmd, u32 num) {
    u32 vn = cmd >> 2 & 3, vl = cmd & 3, bits, n = num;
    if (vl == 3 && vn != 3) return ~0u;
    bits = vl == 3 ? 16 : (32 >> vl) * (vn + 1);
    if (v->wl > v->cl && v->wl) {
        u32 r = num % v->wl;
        n = num / v->wl * v->cl + (r < v->cl ? r : v->cl);
    }
    return (n * bits + 31) / 32;
}

static void vif_word(VifStream *v, u32 w, u32 addr) {
    u32 cmd = w >> 24 & 0x7F, imm = w & 0xFFFF, num = w >> 16 & 0xFF;
    v->pos = (v->pos + 1) & 3;
    if (v->pad) { v->pad--; return; }
    if (v->need) {
        v->need--;
        if (v->in_direct) {
            v->q[v->nq++] = w;
            if (v->nq == 4) { gif_qword(&v->gif, v->q); v->nq = 0; }
            if (!v->need) v->in_direct = 0;
        }
        return;
    }
    v->codes++;
    if (v->vif0 && (cmd == 0x02 || cmd == 0x03 || cmd == 0x06 || cmd == 0x50 || cmd == 0x51)) cmd = 0x7F;
    switch (cmd) {
    case 0x00: case 0x02: case 0x03: case 0x04: case 0x05: case 0x06: case 0x07:
    case 0x10: case 0x11: case 0x13: case 0x14: case 0x15: case 0x17:
        return;
    case 0x01: /* STCYCL */
        v->cl = imm & 0xFF;
        v->wl = imm >> 8 & 0xFF;
        return;
    case 0x20: v->need = 1; return;              /* STMASK */
    case 0x30: case 0x31: v->need = 4; return;   /* STROW / STCOL */
    case 0x4A:                                   /* MPG: num x 64 bits, 64-bit aligned */
        v->pad = v->pos & 1;
        v->need = (num ? num : 256) * 2;
        return;
    case 0x50: case 0x51:                        /* DIRECT / DIRECTHL: imm qwords, aligned */
        v->direct++;
        v->pad = (4 - v->pos) & 3;
        v->need = (imm ? imm : 0x10000) * 4;
        v->in_direct = 1;
        v->nq = 0;
        return;
    }
    if ((cmd & 0x60) == 0x60) {
        u32 n = vif_unpack_words(v, cmd, num ? num : 256);
        if (n != ~0u) { v->unpacks++; v->need = n; return; }
    }
    if (!v->bad++) { v->bad_word = w; v->bad_addr = addr; }
}

static void vif_block(VifStream *v, const u32 *q, u32 n, u32 addr) {
    u32 i;
    if (!n) return;
    v->blocks++;
    if (v->need || v->pad) v->mid++;
    for (i = 0; i < n * 4; i++) vif_word(v, q[i], addr + i * 4);
}

int kh1_dma_walk(int ch, u32 chcr, u32 tadr, KH1DmaWhere where) {
    static const char *const ids[8] = { "refe", "cnt", "next", "ref", "refs", "call", "ret", "end" };
    static u32 tags[4096][2];
    u32 tag = tadr, asr[2], qwords = 0, ntags = 0, tte_hi = 0;
    int asp = 0, bad = 0, done = 0, i, tte = (chcr & 0x40) != 0;
    const char *last = "?";
    GifStream g = { 0 };
    VifStream v = { 0 };
    char extra[160], regs[400];
    extra[0] = 0;
    while (!done && !bad && ntags < 4096) {
        u32 w0, qwc, id, addr, next = tag + 16;
        if (!where(tag, 16)) { bad = KH1_DMA_TAG_OUTSIDE; break; }
        w0 = ((u32 *)(unsigned long)tag)[0];
        addr = ((u32 *)(unsigned long)tag)[1];
        qwc = w0 & 0xFFFF;
        id = w0 >> 28 & 7;
        tags[ntags][0] = tag;
        tags[ntags++][1] = id;
        last = ids[id];
        qwords += qwc;
        switch (id) {
        case 0: /* refe: the data at ADDR, then end */
            if (qwc && !where(addr, qwc * 16)) bad = KH1_DMA_DATA_OUTSIDE;
            done = 1;
            break;
        case 1: /* cnt: the data after the tag, then the tag after it */
            next = tag + 16 + qwc * 16;
            break;
        case 2: /* next: the data after the tag, then the tag at ADDR */
            next = addr;
            break;
        case 3: case 4: /* ref / refs: the data at ADDR, then the next qword */
            if (qwc && !where(addr, qwc * 16)) bad = KH1_DMA_DATA_OUTSIDE;
            break;
        case 5: /* call: the data after the tag, push its end, go to ADDR */
            if (asp == 2) { bad = KH1_DMA_CALL_DEEP; break; }
            asr[asp++] = tag + 16 + qwc * 16;
            next = addr;
            break;
        case 6: /* ret: the data after the tag, pop (an empty stack ends the chain) */
            if (asp) next = asr[--asp];
            else done = 1;
            break;
        case 7: /* end: the data after the tag, then stop */
            done = 1;
            break;
        }
        if (!bad && (id == 1 || id == 2 || id == 5 || id == 6 || id == 7) && qwc &&
            !where(tag + 16, qwc * 16))
            bad = KH1_DMA_DATA_OUTSIDE;
        tag = next;
    }
    if (!done && !bad) bad = KH1_DMA_NO_END;
    v.vif0 = ch == 0;
    regs[0] = 0;
    if (!bad && ch <= 2) {
        /* the receiver's stream: each tag's data in chain order */
        for (i = 0; i < (int)ntags; i++) {
            u32 *t = (u32 *)(unsigned long)tags[i][0];
            u32 id = tags[i][1], qwc = t[0] & 0xFFFF;
            u32 data = (id == 0 || id == 3 || id == 4) ? t[1] : tags[i][0] + 16;
            if (tte && (t[2] || t[3])) tte_hi++;
            if (ch == 2) {
                gif_block(&g, (u32 *)(unsigned long)data, qwc);
            } else {
                if (tte) {
                    v.pos = 2;
                    vif_word(&v, t[2], tags[i][0] + 8);
                    vif_word(&v, t[3], tags[i][0] + 12);
                }
                v.pos = 0;
                vif_block(&v, (u32 *)(unsigned long)data, qwc, data);
            }
        }
        if (ch == 2) {
            if (g.left) bad |= KH1_DMA_GIF_SHORT;
            sprintf(extra, "; gif %u packets (%u eop, %u image), %u of %u blocks inside one%s", g.packets,
                    g.eop, g.image, g.mid, g.blocks, g.left ? ": ENDS INSIDE A PACKET" : "");
            gif_regs(&g, regs);
        } else {
            if (v.need || v.pad) bad |= KH1_DMA_VIF_SHORT;
            if (v.bad) bad |= KH1_DMA_VIF_BAD;
            if (v.gif.left) bad |= KH1_DMA_PATH2_SHORT;
            sprintf(extra, "; vif%d %u codes (%u unpack, %u direct), %u of %u blocks inside one%s%s", ch, v.codes,
                    v.unpacks, v.direct, v.mid, v.blocks, (v.need || v.pad) ? ": ENDS INSIDE A CODE" : "",
                    v.bad ? ": NOT A VIF CODE" : "");
            if (v.direct)
                sprintf(extra + strlen(extra), "; path2 %u packets%s", v.gif.packets,
                        v.gif.left ? ": ENDS INSIDE A PACKET" : "");
            gif_regs(&v.gif, regs);
        }
        if (tte && tte_hi)
            sprintf(extra + strlen(extra), "; %u tags with upper words (TTE)", tte_hi);
    }
    printf("kh1-host: dma ch %d chcr %08x tadr %08x: %u tags, %u qwords, ends with %s%s%s%s%s\n", ch, chcr,
           tadr, ntags, qwords, last,
           bad & KH1_DMA_TAG_OUTSIDE ? ": TAG OUTSIDE" : bad & KH1_DMA_DATA_OUTSIDE ? ": DATA OUTSIDE"
           : bad & KH1_DMA_CALL_DEEP ? ": CALL TOO DEEP" : bad & KH1_DMA_NO_END ? ": NO END (4096 tags)" : "",
           extra, regs[0] ? "; regs" : "", regs);
    if (bad || kh1_host_trace >= 3)
        for (i = 0; i < (int)ntags; i++) {
            u32 *t = (u32 *)(unsigned long)tags[i][0];
            printf("kh1-host:   %08x %-4s qwc %u addr %08x upper %08x %08x%s\n", tags[i][0], ids[tags[i][1]],
                   t[0] & 0xFFFF, t[1], t[2], t[3], tte ? " (TTE)" : "");
        }
    if (bad & KH1_DMA_TAG_OUTSIDE) printf("kh1-host:   tag at %08x outside\n", tag);
    if (bad & KH1_DMA_VIF_BAD) printf("kh1-host:   %u words no VIF code, the first %08x at %08x\n", v.bad,
                                     v.bad_word, v.bad_addr);
    return bad;
}

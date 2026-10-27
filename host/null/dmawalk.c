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
 * the cnt that holds its GIFtag does).
 *
 * KH1_HOST_TRACE=4 (session 77) prints, after each send's line, every distinct GS state
 * register value the send writes (one "gs REG VALUE" line each, in the order first written;
 * vertex registers left out), without the tags: tools/host/gsstate.py turns a run's lines into
 * the renderer's state list, the run-time twin of tools/host/dmawalk.py --state.
 *
 * Every register write also goes to the GS register file (host/null/gsregs.c, session 79), which
 * keeps the state across sends and counts the vertex kicks per draw state; KH1_HOST_TRACE=5
 * prints each send's draw states after its gs lines.  The IMAGE data goes to the GS memory model
 * (host/null/gsmem.c, session 80), and KH1_HOST_TRACE=5 also prints each send's uploads. */
#include "common.h"
#include "dmawalk.h"
#include "gsregs.h"
#include "gsmem.h"
#include "platform/vu1.h"

int printf(const char *, ...);
int sprintf(char *, const char *, ...);
__SIZE_TYPE__ strlen(const char *);
void *fopen(const char *, const char *);
__SIZE_TYPE__ fwrite(const void *, __SIZE_TYPE__, __SIZE_TYPE__, void *);
int fprintf(void *, const char *, ...);
int fclose(void *);

const char *kh1_host_texdump; /* KH1_HOST_TEXDUMP: a directory for the decoded textures (main.c) */
void (*kh1_dma_after_send)(u32 tadr); /* session 94: KH1_HOST_SHOT's present (host/null/present.c) */
int kh1_dma_quiet; /* session 135: no send line (the Vita, dmawalk.h) */
int kh1_dma_vu1; /* session 137v: VIF1's codes run on host/port/vu1.c, its XGKICKs drawn (dmawalk.h) */
void (*kh1_dma_draw_state)(const KH1GsDraw *d); /* session 123: each send's draw states (KH1_HOST_TRACE=5) */

typedef struct {
    u32 left;    /* qwords (REGLIST: 64-bit words) of the current packet still to come */
    u32 flg, nreg, k;
    u32 regs[16];
    u32 packets, eop, image, blocks, mid;
    u32 set[4];  /* the GS registers written (by address, bit per register: PACKED, REGLIST, A+D) */
} GifStream;

typedef struct {
    u32 need;    /* data words of the current code still to come */
    u32 pad;     /* words to skip before them (none since session 137v: DIRECT / MPG data is not padded) */
    u32 pos;     /* word position in the stream, mod 4 */
    u32 cl, wl;  /* STCYCL */
    u32 vif0;    /* VIF0 has no OFFSET, BASE, MSKPATH3 or DIRECT */
    u32 codes, unpacks, direct, blocks, mid, bad, bad_word, bad_addr;
    u32 in_direct, nq, q[4];
    GifStream gif; /* PATH2: every DIRECT's data, one stream of GIF packets */
} VifStream;

/* the state values the current walk wrote, distinct (KH1_HOST_TRACE=4, kh1_dma_gs_values) */
#define GS_VALUES 512
static struct { u32 reg, lo, hi; } gs_val[GS_VALUES];
static u32 gs_nval;

static void gif_set(GifStream *g, u32 reg) {
    if (reg < 128) g->set[reg >> 5] |= 1u << (reg & 31);
}

/* reg written with the 64-bit value at v (vertex registers are not state) */
static void gif_value(GifStream *g, u32 reg, const u32 *v) {
    u32 i;
    gif_set(g, reg);
    if (reg >= 128 || (reg >= 1 && reg <= 5) || reg == 0xA || reg == 0xC || reg == 0xD || reg == 0xF) return;
    for (i = 0; i < gs_nval; i++)
        if (gs_val[i].reg == reg && gs_val[i].lo == v[0] && gs_val[i].hi == v[1]) return;
    if (gs_nval == GS_VALUES) return;
    gs_val[gs_nval].reg = reg;
    gs_val[gs_nval].lo = v[0];
    gs_val[gs_nval++].hi = v[1];
}

int kh1_dma_gs_values(u32 *reg, u32 *lo, u32 *hi, int max) {
    int i;
    for (i = 0; i < (int)gs_nval && i < max; i++) {
        reg[i] = gs_val[i].reg;
        lo[i] = gs_val[i].lo;
        hi[i] = gs_val[i].hi;
    }
    return gs_nval;
}

/* one qword of the GIF stream: a GIFtag, or the next qword of the current packet */
static void gif_qword(GifStream *g, const u32 *q) {
    u32 nloop, h;
    if (g->left) {
        if (g->flg == 0) {
            u32 d = g->regs[g->k++ % g->nreg];
            if (d == 0xE) gif_value(g, q[2] & 0x7F, q);
            else if (d == 0) { u32 prim[2] = { q[0] & 0x7FF, 0 }; gif_value(g, 0, prim); }
            else gif_value(g, d, q);
            kh1_gs_packed(d, q);
            g->left--;
        } else if (g->flg == 1) {
            for (h = 0; h < 2 && g->left; h++, g->left--) {
                u32 d = g->regs[g->k++ % g->nreg];
                if (d != 0xE) gif_value(g, d, q + 2 * h);
                if (d < 0xE) kh1_gs_write(d, q[2 * h], q[2 * h + 1]);
            }
        } else { /* IMAGE: the upload's pixels (host/null/gsmem.c) */
            kh1_gsmem_image(q, 4);
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
    if (g->flg == 0 && q[1] >> 14 & 1) { /* PRE: PRIM from the tag */
        u32 prim[2] = { q[1] >> 15 & 0x7FF, 0 };
        gif_value(g, 0, prim);
    }
    kh1_gs_giftag(g->flg == 0 && q[1] >> 14 & 1, q[1] >> 15 & 0x7FF);
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

/* session 137v: an XGKICK's GIF packets (host/port/vu1.c), read as PATH1 like the GIF channel's */
static u32 path1_packets;
static void path1_kick(const u32 *q, u32 nqw) {
    GifStream g = { 0 };
    gif_block(&g, q, nqw);
    path1_packets += g.packets;
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
        if (kh1_dma_vu1 && !v->vif0) kh1_vif1_data(w);
        if (v->in_direct) {
            v->q[v->nq++] = w;
            if (v->nq == 4) { gif_qword(&v->gif, v->q); v->nq = 0; }
            if (!v->need) v->in_direct = 0;
        }
        return;
    }
    v->codes++;
    if (kh1_dma_vu1 && !v->vif0) {
        if (!kh1_vu1_kick) kh1_vu1_kick = path1_kick;
        if (cmd == 0x14 || cmd == 0x15 || cmd == 0x17) kh1_gs_path1();
        kh1_vif1_code(w);
    }
    if (v->vif0 && (cmd == 0x02 || cmd == 0x03 || cmd == 0x06 || cmd == 0x50 || cmd == 0x51)) cmd = 0x7F;
    switch (cmd) {
    case 0x14: case 0x15: case 0x17: /* MSCAL / MSCALF / MSCNT: on VIF1 a VU1 program that may XGKICK */
        if (!v->vif0 && !kh1_dma_vu1) kh1_gs_path1();
        return;
    case 0x00: case 0x02: case 0x03: case 0x04: case 0x05: case 0x06: case 0x07:
    case 0x10: case 0x11: case 0x13:
        return;
    case 0x01: /* STCYCL */
        v->cl = imm & 0xFF;
        v->wl = imm >> 8 & 0xFF;
        return;
    case 0x20: v->need = 1; return;              /* STMASK */
    case 0x30: case 0x31: v->need = 4; return;   /* STROW / STCOL */
    case 0x4A:                                   /* MPG: num x 64 bits */
        v->need = (num ? num : 256) * 2;
        return;
    case 0x50: case 0x51:                        /* DIRECT / DIRECTHL: imm qwords */
        /* session 137v: the data follows the code with no padding: the rooms' meshes put DIRECT in any
         * word of a qword (the "aligned" rule is the programmer's, the VIF reads the next words; the game
         * pads with NOPs where it aligns, so the old reading only differed on these) */
        v->direct++;
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

static const char *target_note(u32 t) {
    static char b[32];
    sprintf(b, ", reads target %u", t);
    return b;
}

/* session 91: the vertices' extent in 1/16 pixels from XYOFFSET (gsstate.py --extents) */
static const char *extent_note(const KH1GsDraw *d) {
    static char b[64];
    if (d->x1 < d->x0) return "";
    sprintf(b, ", xy %d %d %d %d", d->x0, d->y0, d->x1, d->y1);
    return b;
}

/* session 93: a SCISSOR the wide view's rule reads as the view's, in canvas sixteenths */
static const char *view_note(const KH1GsDraw *d) {
    static char b[48];
    if (d->vx0 == d->vx1) return "";
    sprintf(b, ", view scissor %d %d", d->vx0, d->vx1);
    return b;
}

/* KH1_HOST_TRACE=5: each draw state the send drew in (host/null/gsregs.c), with the context's
 * FRAME, ZBUF, TEST, ALPHA, TEX0 and CLAMP, and its kicks and primitives */
static void gs_print_draws(void) {
    static KH1GsDraw d[256];
    int n = kh1_gs_draws(d, 256), i;
    if (kh1_dma_draw_state) /* session 123: host/null/pipes.c's count of GPU pipelines */
        for (i = 0; i < n && i < 256; i++) kh1_dma_draw_state(&d[i]);
    for (i = 0; i < n && i < 64; i++)
        printf("kh1-host:   draw prim %03x frame %08x zbuf %08x test %08x alpha %08x%08x tex0 %08x%08x clamp "
               "%08x%08x: %u kicks, %u prims%s%s%s\n", d[i].prim, d[i].ctx.frame.lo, d[i].ctx.zbuf.lo, d[i].ctx.test.lo,
               d[i].ctx.alpha.hi, d[i].ctx.alpha.lo, d[i].ctx.tex0.hi, d[i].ctx.tex0.lo, d[i].ctx.clamp.hi,
               d[i].ctx.clamp.lo, d[i].kicks, d[i].draws, extent_note(&d[i]),
               d[i].target ? target_note(d[i].target) : "", view_note(&d[i]));
    if (n > 64) printf("kh1-host:   draw ... %d states in all\n", n);
}

/* KH1_HOST_TRACE=5 (session 81): the render targets the send drew into (host/null/gsmem.c), with the
 * extent so far and the send's primitives (a VU1 program start counts one, host/null/gsregs.c) */
static void gs_print_targets(void) {
    static KH1GsTarget t[32];
    int n = kh1_gsmem_targets(t, 32), i;
    for (i = 0; i < n && i < 32; i++)
        if (t[i].sent)
            printf("kh1-host:   target %d bp %04x bw %u psm %02x rows %u mask %08x: %u prims\n", i + 1, t[i].bp,
                   t[i].bw, t[i].psm, t[i].h, t[i].mask, t[i].sent);
}

/* KH1_HOST_TRACE=5: each upload / copy into GS memory the send made (host/null/gsmem.c, session 80) */
static void gs_print_uploads(void) {
    static KH1GsUpload u[64];
    int n = kh1_gsmem_log(u, 64), i;
    for (i = 0; i < n && i < 64; i++)
        printf("kh1-host:   upload %s dbp %04x dbw %u dpsm %02x at %u,%u size %ux%u: %u pixels\n",
               u[i].dir ? "copy" : "host", u[i].bp, u[i].bw, u[i].psm, u[i].x, u[i].y, u[i].w, u[i].h, u[i].pixels);
    if (n > 64) printf("kh1-host:   upload ... %d in all\n", n);
}

/* KH1_HOST_TEXDUMP=DIR (session 80): each distinct texture a send drew with, decoded from the GS memory
 * model (host/null/gsmem.c) as it stands after the send, written once per TEX0 + TEXA + contents to
 * DIR/tex_TEX0_N.pam (RGBA, A doubled from the GS's 0-0x80 scale).  Draws do not write the model's
 * pixels: a texture in a render target's drawn bits (the 3D target 0x1A00, the Z area 0x0E00; session
 * 81) is not decoded but named ("texture ... in target N").  From the user's disc: never commit them. */
static void gs_dump_textures(void) {
    static KH1GsDraw d[256];
    static u32 seen[1024][5], nseen, pix[1024 * 1024];
    static unsigned char row[1024 * 4];
    int n = kh1_gs_draws(d, 256), i;
    u32 j, k, w, h, x, y;
    char path[512];
    void *f;
    for (i = 0; i < n && i < 256; i++) {
        u32 key[5];
        if (!(d[i].prim >> 4 & 1)) continue;
        key[0] = d[i].ctx.tex0.lo;
        key[1] = d[i].ctx.tex0.hi & ~0xE0000000u; /* CLD is when, not what */
        key[2] = d[i].texa.lo ^ d[i].texa.hi << 16;
        key[3] = kh1_gsmem_tex_stamp(key[0], key[1]);
        k = key[0] >> 20 & 63; /* the CLUT only for the indexed PSMs */
        key[4] = k == KH1_PSMT8 || k == KH1_PSMT8H || k == KH1_PSMT4 || k == KH1_PSMT4HL || k == KH1_PSMT4HH
                     ? kh1_gsmem_clut_stamp() : 0;
        for (j = 0; j < nseen; j++) {
            for (k = 0; k < 5 && seen[j][k] == key[k]; k++) ;
            if (k == 5) break;
        }
        if (j < nseen || nseen == 1024) continue;
        for (k = 0; k < 5; k++) seen[nseen][k] = key[k];
        if (d[i].target) {
            nseen++;
            printf("kh1-host:   texture %08x%08x in target %u: not decoded\n", key[1], key[0], d[i].target);
            continue;
        }
        if (kh1_gsmem_read_tex(key[0], key[1], d[i].texa.lo, d[i].texa.hi, pix)) continue;
        w = 1u << (key[0] >> 26 & 15);
        h = 1u << ((key[0] >> 30 | key[1] << 2) & 15);
        sprintf(path, "%.400s/tex_%08x%08x_%u.pam", kh1_host_texdump, key[1], key[0], nseen++);
        f = fopen(path, "wb");
        if (!f) continue;
        fprintf(f, "P7\nWIDTH %u\nHEIGHT %u\nDEPTH 4\nMAXVAL 255\nTUPLTYPE RGB_ALPHA\nENDHDR\n", w, h);
        for (y = 0; y < h; y++) {
            for (x = 0; x < w; x++) {
                u32 v = pix[y * w + x], a = (v >> 24) * 2;
                row[x * 4] = v; row[x * 4 + 1] = v >> 8; row[x * 4 + 2] = v >> 16; row[x * 4 + 3] = a > 255 ? 255 : a;
            }
            fwrite(row, 4, w, f);
        }
        fclose(f);
        printf("kh1-host:   texture %s\n", path);
    }
}

/* the HUD's anchors under a wide view (kh1_dma_hud_anchors, session 92) */
static const KH1HudAnchor *hud_tab;
static int hud_n;
static u32 hud_via, hud_via_n;
static s32 hud_margin, hud_env_shift;

void kh1_dma_hud_anchors(const KH1HudAnchor *tab, int n, u32 via, u32 via_n, s32 margin) {
    hud_tab = tab;
    hud_n = n;
    hud_via = via;
    hud_via_n = via_n;
    hud_margin = margin;
    hud_env_shift = 0;
    kh1_gs_xshift(0);
}

/* the static full-screen packets' stretch under a wide view (kh1_dma_fullscreen, session 93) */
static const KH1FullScreen *fs_tab;
static int fs_n;
static s32 fs_x0, fs_w;

void kh1_dma_fullscreen(const KH1FullScreen *tab, int n, s32 x0, s32 w) {
    fs_tab = tab;
    fs_n = n;
    fs_x0 = x0;
    fs_w = w;
    kh1_gs_xstretch(0, 0, 0);
}

/* a send starts at tadr: a listed full-screen packet is stretched (session 93); a staging send keeps
 * the shift of the environment sent before it (as tools/host/gsstate.py keys its extent), any other
 * send is that environment */
static void hud_send(u32 tadr) {
    int i;
    if (fs_n) {
        u32 what = 0;
        for (i = 0; i < fs_n; i++)
            if ((u32)(unsigned long)fs_tab[i].send == tadr) {
                what = fs_tab[i].what;
                break;
            }
        kh1_gs_xstretch(fs_x0, fs_w, what);
    }
    if (!hud_n) return;
    if (tadr - hud_via < hud_via_n) {
        kh1_gs_xshift(hud_env_shift);
        return;
    }
    hud_env_shift = 0;
    for (i = 0; i < hud_n; i++)
        if ((u32)(unsigned long)hud_tab[i].env == tadr) {
            hud_env_shift = hud_tab[i].side * hud_margin;
            break;
        }
    kh1_gs_xshift(hud_env_shift);
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
    gs_nval = 0;
    hud_send(tadr);
    kh1_gs_clear_draws(); /* kh1_gs_draws: this send's; the registers stay */
    kh1_gsmem_clear_log(); /* and the uploads: GS memory stays */
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
    if (!kh1_dma_quiet)
        printf("kh1-host: dma ch %d chcr %08x tadr %08x: %u tags, %u qwords, ends with %s%s%s%s%s\n", ch, chcr,
           tadr, ntags, qwords, last,
           bad & KH1_DMA_TAG_OUTSIDE ? ": TAG OUTSIDE" : bad & KH1_DMA_DATA_OUTSIDE ? ": DATA OUTSIDE"
           : bad & KH1_DMA_CALL_DEEP ? ": CALL TOO DEEP" : bad & KH1_DMA_NO_END ? ": NO END (4096 tags)" : "",
           extra, regs[0] ? "; regs" : "", regs);
    if (kh1_host_trace >= 4)
        for (i = 0; i < (int)gs_nval; i++)
            printf("kh1-host:   gs %02x %08x%08x\n", gs_val[i].reg, gs_val[i].hi, gs_val[i].lo);
    if (kh1_host_trace >= 5) {
        gs_print_draws();
        gs_print_uploads();
        gs_print_targets();
    }
    if (kh1_host_texdump) gs_dump_textures();
    if (bad || kh1_host_trace == 3)
        for (i = 0; i < (int)ntags; i++) {
            u32 *t = (u32 *)(unsigned long)tags[i][0];
            printf("kh1-host:   %08x %-4s qwc %u addr %08x upper %08x %08x%s\n", tags[i][0], ids[tags[i][1]],
                   t[0] & 0xFFFF, t[1], t[2], t[3], tte ? " (TTE)" : "");
        }
    if (bad & KH1_DMA_TAG_OUTSIDE) printf("kh1-host:   tag at %08x outside\n", tag);
    if (bad & KH1_DMA_VIF_BAD) printf("kh1-host:   %u words no VIF code, the first %08x at %08x\n", v.bad,
                                     v.bad_word, v.bad_addr);
    if (kh1_dma_after_send) kh1_dma_after_send(tadr);
    return bad;
}

/* A GIF packet sent without a chain (sceGsPutDrawEnv's normal-mode send: the boot draw environment,
 * renderer-spec 4.11), read like a walk's GIF stream; the line has a send's shape (chcr 0) so
 * tools/host/gsstate.py names it by the packet's host symbol.  Session 80. */
void kh1_dma_gif_direct(const u32 *q, u32 qwc) {
    GifStream g = { 0 };
    char regs[400];
    int i;
    gs_nval = 0;
    hud_send((u32)(unsigned long)q);
    kh1_gs_clear_draws();
    kh1_gsmem_clear_log();
    gif_block(&g, q, qwc);
    gif_regs(&g, regs);
    if (!kh1_dma_quiet)
        printf("kh1-host: dma ch 2 chcr 00000000 tadr %08x: direct (normal mode), %u qwords; gif %u packets%s%s%s\n",
           (u32)(unsigned long)q, qwc, g.packets, g.left ? ": ENDS INSIDE A PACKET" : "", regs[0] ? "; regs" : "",
           regs);
    if (kh1_host_trace >= 4)
        for (i = 0; i < (int)gs_nval; i++)
            printf("kh1-host:   gs %02x %08x%08x\n", gs_val[i].reg, gs_val[i].hi, gs_val[i].lo);
    if (kh1_host_trace >= 5) {
        gs_print_draws();
        gs_print_uploads();
        gs_print_targets();
    }
    if (kh1_dma_after_send) kh1_dma_after_send((u32)(unsigned long)q);
}

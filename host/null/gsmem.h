/* The null platform's model of GS local memory (docs/renderer-spec.md 5.2, host/null/gsmem.c). */
#ifndef KH1_HOST_GSMEM_H
#define KH1_HOST_GSMEM_H

/* the pixel storage modes (TEX0.PSM, BITBLTBUF.SPSM / DPSM) */
#define KH1_PSMCT32  0x00
#define KH1_PSMCT24  0x01
#define KH1_PSMCT16  0x02
#define KH1_PSMT8    0x13
#define KH1_PSMT4    0x14
#define KH1_PSMT8H   0x1B
#define KH1_PSMT4HL  0x24
#define KH1_PSMT4HH  0x2C

typedef struct {
    u32 uploads;     /* host->local transfers started (TRXDIR 0) */
    u32 copies;      /* local->local transfers done (TRXDIR 2) */
    u32 pixels;      /* pixels written by uploads */
    u32 extra;       /* IMAGE qwords with no transfer left to take them */
    u32 unsupported; /* transfers, CLUT loads or reads in a PSM the model does not have (CT16S,
                      * the Z formats), TRXDIR 1, CSM 1 (TEXCLUT) */
    u32 clut_loads;  /* CLUT buffer loads (TEX0 / TEX2 with CLD 1-5 that load) */
} KH1GsMemStats;

/* clears the 4 MB, the CLUT buffer, the transfer and the counters */
void kh1_gsmem_reset(void);
/* TRXDIR written: starts the transfer BITBLTBUF / TRXPOS / TRXREG describe (0 host->local, the
 * IMAGE data then comes through kh1_gsmem_image; 2 local->local, done at once) */
void kh1_gsmem_trxdir(u32 dir, u32 bitbltbuf_lo, u32 bitbltbuf_hi, u32 trxpos_lo, u32 trxpos_hi,
                      u32 trxreg_lo, u32 trxreg_hi);
/* n words of IMAGE data (a GIF FLG 2 / 3 qword, or a HWREG write's two) for the current upload */
void kh1_gsmem_image(const u32 *w, u32 n);
/* a TEX0 (or the TEX0 a TEX2 write leaves) written: loads the CLUT buffer as its CLD says */
void kh1_gsmem_tex0(u32 lo, u32 hi);

/* the address of pixel (x, y) of a buffer at block bp, width bw (64-pixel units) in psm, in units
 * of the PSM's pixel size (CT32 / CT24 / T8H / T4HL / T4HH: words, CT16: halfwords, T8: bytes,
 * T4: nibbles); ~0 for a PSM the model does not have */
u32 kh1_gsmem_addr(u32 psm, u32 bp, u32 bw, u32 x, u32 y);
/* reads / writes one pixel's stored bits (a CT32 word's top byte for T8H, its nibble for T4HL /
 * T4HH; the low 24 bits for CT24, the top byte kept) */
u32 kh1_gsmem_read_pixel(u32 psm, u32 bp, u32 bw, u32 x, u32 y);
void kh1_gsmem_write_pixel(u32 psm, u32 bp, u32 bw, u32 x, u32 y, u32 v);

/* decodes the texture TEX0 names (TBP0, TBW, PSM, TW, TH; CPSM and CSA for the indexed PSMs, from
 * the CLUT buffer the last load left) to w x h RGBA8 words (R in bits 0-7, A in 24-31, as the GS
 * stores CT32; A is the texel's own 0-0x80 scale, TCC is the renderer's), w = 1 << TW and h = 1 <<
 * TH, both at most 1024.  texa: TEXA (TA0, AEM, TA1) for CT24 / CT16 texels and CT16 CLUT entries.
 * Returns 0, or -1 for a PSM or CLUT the model does not have (out untouched). */
int kh1_gsmem_read_tex(u32 tex0_lo, u32 tex0_hi, u32 texa_lo, u32 texa_hi, u32 *out);
/* a texture cache's key check: the newest write sequence number of any 8 KB page the texture's
 * w x h texels lie in (0: never written since the reset), and the CLUT buffer's load count */
u32 kh1_gsmem_tex_stamp(u32 tex0_lo, u32 tex0_hi);
u32 kh1_gsmem_clut_stamp(void);

const KH1GsMemStats *kh1_gsmem_stats(void);

/* an upload or copy since the last kh1_gsmem_clear_log (KH1_HOST_TRACE=5 prints them) */
typedef struct {
    u32 dir;          /* TRXDIR: 0 host->local, 2 local->local */
    u32 bp, bw, psm;  /* the destination (BITBLTBUF's DBP, DBW, DPSM) */
    u32 x, y, w, h;   /* TRXPOS's DSAX / DSAY, TRXREG */
    u32 pixels;       /* pixels written (an upload short of w x h ran out of IMAGE data) */
} KH1GsUpload;
/* fills up to max and returns how many there were (at most 256 kept) */
int kh1_gsmem_log(KH1GsUpload *out, int max);
void kh1_gsmem_clear_log(void);

#endif

/* The null platform's model of GS local memory (docs/renderer-spec.md 5.2, host/null/gsmem.c). */
#ifndef KH1_HOST_GSMEM_H
#define KH1_HOST_GSMEM_H

/* the pixel storage modes (TEX0.PSM, BITBLTBUF.SPSM / DPSM) */
#define KH1_PSMCT32  0x00
#define KH1_PSMCT24  0x01
#define KH1_PSMCT16  0x02
#define KH1_PSMCT16S 0x0A
#define KH1_PSMT8    0x13
#define KH1_PSMT4    0x14
#define KH1_PSMT8H   0x1B
#define KH1_PSMT4HL  0x24
#define KH1_PSMT4HH  0x2C
#define KH1_PSMZ32   0x30
#define KH1_PSMZ24   0x31
#define KH1_PSMZ16   0x32
#define KH1_PSMZ16S  0x3A

typedef struct {
    u32 uploads;     /* host->local transfers started (TRXDIR 0) */
    u32 copies;      /* local->local transfers done (TRXDIR 2) */
    u32 pixels;      /* pixels written by uploads */
    u32 extra;       /* IMAGE qwords with no transfer left to take them */
    u32 unsupported; /* transfers, CLUT loads or reads in a PSM the model does not have, TRXDIR 1,
                      * CSM 1 (TEXCLUT) */
    u32 clut_loads;  /* CLUT buffer loads (TEX0 / TEX2 with CLD 1-5 that load) */
    u32 target_draws; /* primitives drawn into a render target (kh1_gsmem_draw, session 81) */
    u32 sprites;      /* point-sampled sprites drawn into the model's pixels (kh1_gsmem_sprite, session 83) */
    u32 sprite_pixels;
    u32 flat_sprites; /* untextured sprites filled for the present (kh1_gsmem_flat_sprite, session 95) */
    u32 flat_pixels;
    u32 tex_sprites;  /* textured sprites point-sampled for the present (the frame copy, session 96) */
    u32 tex_pixels;
} KH1GsMemStats;

/* clears the 4 MB, the CLUT buffer, the transfer and the counters */
void kh1_gsmem_reset(void);
/* TRXDIR written: starts the transfer BITBLTBUF / TRXPOS / TRXREG describe (0 host->local, the
 * IMAGE data then comes through kh1_gsmem_image; 2 local->local, done at once) */
void kh1_gsmem_trxdir(u32 dir, u32 bitbltbuf_lo, u32 bitbltbuf_hi, u32 trxpos_lo, u32 trxpos_hi,
                      u32 trxreg_lo, u32 trxreg_hi);
/* n words of IMAGE data (a GIF FLG 2 / 3 qword, or a HWREG write's two) for the current upload */
void kh1_gsmem_image(const u32 *w, u32 n);
/* session 137: an upload's whole data at once (src, bytes as the IMAGE words bring them): 1 when it is
 * the data the same rectangle's last upload brought and the memory there was not written or drawn
 * since, the upload then done (nothing stored); else 0, and after the words through kh1_gsmem_image,
 * kh1_gsmem_image_kept keeps them for the next */
int kh1_gsmem_image_same(const void *src, u32 bytes);
void kh1_gsmem_image_kept(const void *src, u32 bytes);
/* session 147d: nonzero around an upload whose bytes the caller names by this generation (gsimage.c's large
 * uploads: the game thread compares them with its own copy, and the same bytes keep the generation):
 * kh1_gsmem_image_same then matches the generation the rectangle's kept bytes came with instead of comparing the
 * bytes, and kh1_gsmem_image_kept keeps it */
extern u32 kh1_gsmem_image_gen;
/* 2026-10-31: kh1_gsmem_image_same's part stores (the same bytes again over a rectangle some of whose pages were
 * stored to since: only those pages stored): the pages stored, and the rectangle's pages left as they were */
extern u32 kh1_gsmem_part_pages, kh1_gsmem_part_skipped;
/* a TEX0 (or the TEX0 a TEX2 write leaves) written: loads the CLUT buffer as its CLD says */
void kh1_gsmem_tex0(u32 lo, u32 hi);

/* the address of pixel (x, y) of a buffer at block bp, width bw (64-pixel units) in psm, in units
 * of the PSM's pixel size (CT32 / CT24 / T8H / T4HL / T4HH / Z32 / Z24: words, CT16 / CT16S / Z16 /
 * Z16S: halfwords, T8: bytes, T4: nibbles); ~0 for a PSM the model does not have.  The Z formats are
 * their colour twin's layout with the block number XORed with 0x18 (session 82) */
u32 kh1_gsmem_addr(u32 psm, u32 bp, u32 bw, u32 x, u32 y);
/* reads / writes one pixel's stored bits (a CT32 word's top byte for T8H, its nibble for T4HL /
 * T4HH; the low 24 bits for CT24 / Z24, the top byte kept) */
u32 kh1_gsmem_read_pixel(u32 psm, u32 bp, u32 bw, u32 x, u32 y);
/* session 135: w x h pixels' stored bits from (x0, y0), row by row into out (stride words a row), as
 * kh1_gsmem_read_pixel gives them; -1 for a PSM the model has not or a rectangle past 2048.  Two
 * address tables instead of the swizzle per pixel (the Vita's present) */
int kh1_gsmem_read_rect(u32 psm, u32 bp, u32 bw, u32 x0, u32 y0, u32 w, u32 h, u32 *out, u32 stride);
/* session 135: 1 (the default) lets the sprites and kh1_gsmem_read_rect take a rectangle's addresses
 * from two tables where the layout allows; 0 computes every pixel's address (the tests compare) */
void kh1_gsmem_fast(int on);
extern int kh1_gsmem_t4band; /* 2026-11-04: 0 stores T4 uploads a pixel at a time (gsmem.c band_t4) */
/* session 141: block b's (0-0x3FFF) 64 words in address order (kh1_gsmem_addr's CT32 units less b x 64): the
 * Vita's target uploads (host/vita/gxm.c) take the words an upload wrote, whatever its PSM */
void kh1_gsmem_read_block(u32 b, u32 *out);
void kh1_gsmem_write_pixel(u32 psm, u32 bp, u32 bw, u32 x, u32 y, u32 v);

/* decodes the texture TEX0 names (TBP0, TBW, PSM, TW, TH; CPSM and CSA for the indexed PSMs, from
 * the CLUT buffer the last load left) to w x h RGBA8 words (R in bits 0-7, A in 24-31, as the GS
 * stores CT32; A is the texel's own 0-0x80 scale, TCC is the renderer's), w = 1 << TW and h = 1 <<
 * TH, both at most 1024.  texa: TEXA (TA0, AEM, TA1) for CT24 / CT16 texels and CT16 CLUT entries.
 * Returns 0, or -1 for a PSM or CLUT the model does not have (out untouched). */
int kh1_gsmem_read_tex(u32 tex0_lo, u32 tex0_hi, u32 texa_lo, u32 texa_hi, u32 *out);
/* session 116: the palette the TEX0 reads from the CLUT buffer (256 entries for T8 / T8H, CSA's 16 for
 * the 4-bit PSMs) as RGBA8 words; returns the count, 0 for one the model does not have */
int kh1_gsmem_clut(u32 tex0_lo, u32 tex0_hi, u32 texa_lo, u32 texa_hi, u32 *out);
/* session 147d: nonzero when the last kh1_gsmem_clut answer is a kept one: the same id, the same entries (ids are
 * never reused) */
u32 kh1_gsmem_clut_id(void);
/* session 117 (the palette cache in the present, renderer-spec 4.13 "Session 117"): called after each
 * CLUT buffer load with the TEX0 that loaded it; and, when set, the textured flat sprite's indexed
 * decode (kh1_gsmem_flat_sprite) asks it for the TEX0's palette (as kh1_gsmem_clut gives: 256 entries,
 * or the 16 at CSA) and reads entry `index` from it, or decodes from the CLUT buffer when it returns 0.
 * host/null/present.c sets both; the palette must equal kh1_gsmem_clut's, so the pixels do not move */
extern void (*kh1_gsmem_clut_loaded)(u32 tex0_lo, u32 tex0_hi);
extern const u32 *(*kh1_gsmem_palette)(u32 tex0_lo, u32 tex0_hi, u32 texa_lo, u32 texa_hi);
/* session 118 (the texture cache in the present, renderer-spec 4.13 "Session 118"): when set, the
 * model's textured sprites (kh1_gsmem_sprite, kh1_gsmem_flat_sprite) ask it for the TEX0's stored
 * texels (1 << TW by 1 << TH, row by row: the index for an indexed PSM, the stored value otherwise,
 * as kh1_gsmem_read_pixel gives) and read GS memory when it returns 0 (a render target's texture).
 * host/null/present.c sets it; the texels must equal GS memory's, so the pixels do not move */
extern const u32 *(*kh1_gsmem_texels)(u32 tex0_lo, u32 tex0_hi);
/* session 127 (the command recorder's transfers, include/platform/cmdbuf.h, host/null/pipes.c): when set,
 * called at each TRXDIR 0 (an upload starts: its IMAGE data follows) or 2 (after the copy) with the
 * transfer's registers, and after each CLUT buffer load with the TEX0 that loaded it (after
 * kh1_gsmem_clut_loaded) */
extern void (*kh1_gsmem_xfer_hook)(u32 dir, u32 bb_lo, u32 bb_hi, u32 pos_lo, u32 pos_hi, u32 reg_lo, u32 reg_hi);
extern void (*kh1_gsmem_clut_hook)(u32 tex0_lo, u32 tex0_hi);
/* a texture cache's key check: the newest write sequence number of any 8 KB page the texture's
 * w x h texels lie in (0: never written since the reset), and the CLUT buffer's load count */
u32 kh1_gsmem_tex_stamp(u32 tex0_lo, u32 tex0_hi);
/* session 142: the raw words of the pages the texture's texels lie in (texcache.h's KH1TexRaw) */
u32 kh1_gsmem_tex_raw(u32 tex0_lo, u32 tex0_hi, u32 *out, u32 max);
/* 2026-11-03: the pages' newest content version (texcache.h's KH1TexVer: moves only when a store reaches them) */
u32 kh1_gsmem_tex_ver(u32 tex0_lo, u32 tex0_hi);
/* 2026-11-03: TEX0's content signature from its blocks' hashes into sig[0..1] (texcache.h's KH1TexSig): 1, or 0 when
 * not known; kh1_gsmem_sig_lazy, the blocks it has hashed itself so far */
int kh1_gsmem_tex_sig(u32 tex0_lo, u32 tex0_hi, u32 *sig);
u32 kh1_gsmem_sig_lazy(void);
/* 2026-11-03: 1 when the pages hold those words (texcache.h's KH1TexRawSame), compared in place */
int kh1_gsmem_tex_raw_same(u32 tex0_lo, u32 tex0_hi, const u32 *raw, u32 n);
/* session 142: GS memory as it is now copied (the pages stored to since the last copy: their count, -1 when
 * the copy's 4 MiB cannot be had), then read from the copy as kh1_gsmem_read_block / _read_rect /
 * _tex_stamp read the live memory, by another thread too (the GPU frame's, gsqueue.h's kh1_gpuq) */
int kh1_gsmem_snap_take(void);
/* session 145: 1 when a take now would change nothing in the copy */
int kh1_gsmem_snap_same(void);
extern u32 kh1_gsmem_snap_pages;
void kh1_gsmem_snap_read_block(u32 b, u32 *out);
int kh1_gsmem_snap_read_rect(u32 psm, u32 bp, u32 bw, u32 x0, u32 y0, u32 w, u32 h, u32 *out, u32 stride);
u32 kh1_gsmem_snap_tex_stamp(u32 tex0_lo, u32 tex0_hi);
/* session 146: the last take that copied any page the texels lie in (the copy's bytes there unchanged while
 * it holds; nonzero once a take has run) */
u32 kh1_gsmem_snap_tex_ver(u32 tex0_lo, u32 tex0_hi);
u32 kh1_gsmem_clut_stamp(void);
/* session 102: nonzero when a draw changed the bits psm reads at pixel (x, y) and no upload, copy or
 * pixel write has written its page since: the model does not hold that pixel (a render's output) */
int kh1_gsmem_drawn(u32 psm, u32 bp, u32 bw, u32 x, u32 y);

const KH1GsMemStats *kh1_gsmem_stats(void);

/* render targets (session 81, renderer-spec 5.1's last paragraph): the model is written by uploads
 * and copies, and also told where each primitive drew, so a texture that lies in drawn pages is known
 * to be a render's output (the 3D target, the Z buffer, a pass at 0x3A00) the model does not hold:
 * reported as "target N", not decoded.  A target is a FRAME or a ZBUF the draws wrote through, its
 * extent FBW pages wide (at most to SCISSOR's SCAX1) and as many page rows as SCISSOR's SCAY1
 * reaches.  Kept per 8 KB page: the bits of the pixel word a draw changed, so a Z24 buffer leaves a
 * PSMT4HL / HH font in its top byte a texture (the message font at 0x1000); an upload or copy clears
 * the bits it writes from each page it touches (page granularity: a partial upload clears the whole
 * page's bits). */
typedef struct {
    u32 bp;    /* the first block: FBP / ZBP x 32 */
    u32 bw;    /* FBW (64-pixel units; a ZBUF takes its context's FRAME's) */
    u32 psm;   /* FRAME.PSM, or 0x30 | ZBUF.PSM */
    u32 h;     /* the rows the draws may reach: the largest SCAY1 + 1 seen */
    u32 mask;  /* the pixel word's bits the draws may change: ~FBMSK, CT24 / Z24's low 24 bits */
    u32 draws; /* primitives drawn into it since the reset */
    u32 sent;  /* ... since the last kh1_gsmem_clear_log (KH1_HOST_TRACE=5 prints a send's) */
} KH1GsTarget;
/* a primitive drew with this context's FRAME, ZBUF, SCISSOR and TEST (Z is written with ZTE 1 and
 * ZMSK 0; FRAME unless FBMSK masks every bit) */
void kh1_gsmem_draw(u32 frame_lo, u32 frame_hi, u32 zbuf_lo, u32 zbuf_hi, u32 scissor_lo, u32 scissor_hi,
                    u32 test_lo);
/* session 151: n of them at once (the same as n calls of kh1_gsmem_draw) */
void kh1_gsmem_draw_n(u32 frame_lo, u32 frame_hi, u32 zbuf_lo, u32 zbuf_hi, u32 scissor_lo, u32 scissor_hi,
                      u32 test_lo, u32 n);
/* 0, or 1 + the target that last drew into a page the texture TEX0 names reads, in bits it reads
 * (the CLUT's own source is not checked) */
u32 kh1_gsmem_tex_target(u32 tex0_lo, u32 tex0_hi);
/* fills up to max and returns how many targets there were (at most 32 kept) */
int kh1_gsmem_targets(KH1GsTarget *out, int max);

/* A textured SPRITE the model can draw into its own pixels (session 83, renderer-spec 4.13): FST 1
 * (UV), point sampling (TEX1 MMAG 0, MMIN 0), TFX MODULATE or DECAL, a texture of at most 64 x 64
 * texels that no render target drew (CLAMP REPEAT or CLAMP), no fog, no alpha or destination alpha
 * test, no Z write (ZTE 0, or ZTST ALWAYS with ZMSK 1), into a CT32 / CT24 FRAME (FBMSK kept), with
 * or without ALPHA blending (COLCLAMP taken as 1), at most 4096 pixels inside SCISSOR.  The texture
 * animations' CLUT passes are such sprites: drawn here, a later CLUT load reads their result.
 * Returns 1 when drawn (the pages written are model pixels, not a target's), 0 for anything else,
 * which the caller marks as a draw (kh1_gsmem_draw). */
typedef struct {
    u32 prim;                                  /* PRIM's attributes in force */
    u32 frame_lo, frame_hi, zbuf_hi, test_lo;  /* the PRIM's context */
    u32 alpha_lo, alpha_hi, tex0_lo, tex0_hi, tex1_lo, clamp_lo;
    u32 xyoffset_lo, xyoffset_hi, scissor_lo, scissor_hi;
    u32 texa_lo, texa_hi;
    u32 xy[2], uv[2];                          /* the two vertices' XYZ2 X / Y (12.4) and UV (10.4) */
    u32 rgba;                                  /* the second vertex's RGBA (a sprite is flat) */
    s32 uorg;                                  /* session 99: added to both u (10.4) as the model reads them:
                                                * a wide copy's read-back by the margin (gsregs.c) */
    u32 tests;                                 /* session 121: 1 lets the sprite take TEST's alpha test (every
                                                * ATST / AFAIL; ZB_ONLY writes nothing, no Z being written) and
                                                * DATE on a CT32 frame (tests/host/atest_test.c); gsregs.c
                                                * passes 0, so a run's model and traces are as before;
                                                * session 122: a bit set, 1 the alpha tests, 2 the Z test
                                                * and write (ZTE / ZTST / ZMSK on ZBUF's Z32 / Z24 / Z16 /
                                                * Z16S, the FRAME's FBW; z clamped to the format), 4 fog
                                                * (FGE: f and fogcol after the texture function) */
    u32 zbuf_lo;                               /* session 122: ZBUF's ZBP and PSM (tests bit 2) */
    u32 z, f, fogcol;                          /* the second vertex's Z and F, FOGCOL's RGB */
    u32 quad;                                  /* session 135: kh1_gsmem_flat_sprite only: 1 for a strip's
                                                * rectangle (gsregs.c gs_quad), each pixel's colour from
                                                * rgbav's four corners (top left, top right, bottom left,
                                                * bottom right) instead of rgba */
    u32 rgbav[4];
} KH1GsSprite;
int kh1_gsmem_sprite(const KH1GsSprite *s);
/* session 95: an untextured SPRITE (clear, fade, letterbox) filled into the model's pixels for the
 * present, without marking the pages or moving the other counters: off unless kh1_gsmem_flat(1)
 * (host/null/present.c turns it on).  Session 96: a textured one kh1_gsmem_sprite refused (the frame
 * copy), point-sampled, the same way.  Returns 1 when handled; the caller still marks the draw. */
void kh1_gsmem_flat(int on);
int kh1_gsmem_flat_sprite(const KH1GsSprite *s);

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

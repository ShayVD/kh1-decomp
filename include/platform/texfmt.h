#ifndef PLATFORM_TEXFMT_H
#define PLATFORM_TEXFMT_H

/* The texture formats a port uploads (docs/renderer-spec.md 4.13 "Session 119", vita-port-plan 5.1bg):
 * port code, not game code.  The texture cache (include/platform/texcache.h) keeps a texture's stored
 * texels, row by row, as kh1_gsmem_read_pixel gives them; this turns them into one GPU texture and
 * says what the shader does when it samples it, so the colour the shader ends with is the GS's
 * (kh1_gsmem_read_tex's RGBA8, the alpha on the GS's 0-0x80 scale):
 *
 *   PSM                  upload                       the shader
 *   CT32, Z32            RGBA8, the word as stored    nothing (A is 0x80 = 1.0: x 255 / 128 where it
 *                        (R in the low byte)          blends; TCC 0 takes the vertex's A instead)
 *   CT24, Z24            RGBA8, A 0                   A from TEXA: TA0, or 0 for black with AEM
 *   CT16, CT16S,         16-bit A1B5G5R5, the         R / G / B back to the GS's 5 bits shifted up 3
 *   Z16, Z16S            halfword as stored           (the GPU widens 31 to 0xFF, the GS to 0xF8);
 *                                                     A from TEXA: TA1 with the bit, else TA0, or 0
 *                                                     for black with AEM
 *   T8, T8H              P8, the index                the palette cache's 256 RGBA8 words
 *   T4, T4HL, T4HH       P4, two indices a byte       the palette cache's 16 (CSA's) words
 *                        (the even texel low)
 *
 * TEXA is a draw's uniform, not part of the texture, so one upload serves every TEXA (the cache's key
 * leaves it out) and a TEXA change costs no upload.  An indexed texture's TEXA is in its palette
 * (a CT16 CLUT's alpha), which the palette cache keys.  Rows are padded to KH1_TEXFMT_ALIGN texels
 * (a guess at the GPU's linear stride rule: check it on the Vita).  Not part of the PS2 build. */
#ifndef KH1_PS2
#define KH1_TEXFMT_ALIGN 8

enum {
    KH1_TEXFMT_NONE,  /* a PSM the cache does not keep */
    KH1_TEXFMT_RGBA8, /* 4 bytes a texel */
    KH1_TEXFMT_A1B5G5R5, /* 2 bytes a texel */
    KH1_TEXFMT_P8,    /* 1 byte a texel, a 256-entry palette */
    KH1_TEXFMT_P4     /* half a byte a texel, a 16-entry palette */
};

/* the GPU format a PSM uploads as */
u32 kh1_texfmt_of(u32 psm);
/* nonzero when the shader takes A from TEXA (CT24 / CT16 and their Z twins) */
int kh1_texfmt_texa(u32 psm);
/* bytes in one row of a w-texel-wide upload (padded to KH1_TEXFMT_ALIGN texels), 0 for NONE */
u32 kh1_texfmt_stride(u32 psm, u32 w);
/* writes the w x h stored texels (the texture cache's) as the GPU texture psm uploads as into out
 * (h rows of kh1_texfmt_stride bytes, the padding 0); returns the bytes written, 0 for NONE */
u32 kh1_texfmt_convert(u32 psm, const u32 *texels, u32 w, u32 h, void *out);
/* the shader's texel (x, y) of an upload, w texels wide: the GPU's sample and the shader's steps above,
 * as RGBA8 on the GS's scale.  pal: the palette cache's words for an indexed PSM; texa: TEXA (TA0, AEM
 * in lo, TA1 in hi).  A model of the shader for the tests, and what the shader must do */
u32 kh1_texfmt_sample(u32 psm, const void *buf, u32 w, u32 x, u32 y, const u32 *pal, u32 texa_lo, u32 texa_hi);
#endif

#endif

/* The texture formats a port uploads from the texture cache's stored texels, and the shader's steps
 * that give back the GS's colour (include/platform/texfmt.h, docs/renderer-spec.md 4.13 "Session
 * 119"), checked by tests/host/texfmt_test.c against host/null/gsmem.c's kh1_gsmem_read_tex.  Not part
 * of the PS2 build (it lives outside src/). */
#include "common.h"
#include "platform/texfmt.h"

void *memset(void *, int, __SIZE_TYPE__);

/* TEX0.PSM (host/null/gsmem.h's KH1_PSM*) */
enum {
    CT32 = 0x00, CT24 = 0x01, CT16 = 0x02, CT16S = 0x0A, T8 = 0x13, T4 = 0x14, T8H = 0x1B, T4HL = 0x24,
    T4HH = 0x2C, Z32 = 0x30, Z24 = 0x31, Z16 = 0x32, Z16S = 0x3A
};

u32 kh1_texfmt_of(u32 psm) {
    switch (psm) {
    case CT32: case Z32: case CT24: case Z24: return KH1_TEXFMT_RGBA8;
    case CT16: case CT16S: case Z16: case Z16S: return KH1_TEXFMT_A1B5G5R5;
    case T8: case T8H: return KH1_TEXFMT_P8;
    case T4: case T4HL: case T4HH: return KH1_TEXFMT_P4;
    }
    return KH1_TEXFMT_NONE;
}

int kh1_texfmt_texa(u32 psm) {
    return psm == CT24 || psm == Z24 || kh1_texfmt_of(psm) == KH1_TEXFMT_A1B5G5R5;
}

u32 kh1_texfmt_stride(u32 psm, u32 w) {
    u32 n = (w + KH1_TEXFMT_ALIGN - 1) & ~(KH1_TEXFMT_ALIGN - 1);
    switch (kh1_texfmt_of(psm)) {
    case KH1_TEXFMT_RGBA8: return n * 4;
    case KH1_TEXFMT_A1B5G5R5: return n * 2;
    case KH1_TEXFMT_P8: return n;
    case KH1_TEXFMT_P4: return n / 2;
    }
    return 0;
}

u32 kh1_texfmt_convert(u32 psm, const u32 *t, u32 w, u32 h, void *out) {
    u32 fmt = kh1_texfmt_of(psm), stride = kh1_texfmt_stride(psm, w), x, y, v;
    u8 *row = out;
    if (fmt == KH1_TEXFMT_NONE) return 0;
    memset(out, 0, stride * h);
    for (y = 0; y < h; y++, row += stride, t += w)
        for (x = 0; x < w; x++) {
            v = t[x];
            switch (fmt) {
            case KH1_TEXFMT_RGBA8: /* CT24's stored top byte is not the texel's: A 0, TEXA's in the shader */
                if (psm == CT24 || psm == Z24) v &= 0xFFFFFF;
                row[x * 4] = v; row[x * 4 + 1] = v >> 8; row[x * 4 + 2] = v >> 16; row[x * 4 + 3] = v >> 24;
                break;
            case KH1_TEXFMT_A1B5G5R5: row[x * 2] = v; row[x * 2 + 1] = v >> 8; break;
            case KH1_TEXFMT_P8: row[x] = v; break;
            case KH1_TEXFMT_P4: row[x / 2] |= (v & 15) << (x & 1) * 4; break;
            }
        }
    return stride * h;
}

/* the GPU widens a 5-bit channel by repeating its top bits; the shader takes the 5 bits back
 * (round(c / 255 x 31)) and shifts them up 3, as the GS does */
static u32 widen5(u32 c) { return c << 3 | c >> 2; }
static u32 back5(u32 c8) { return (c8 * 31 + 127) / 255 << 3; }

u32 kh1_texfmt_sample(u32 psm, const void *buf, u32 w, u32 x, u32 y, const u32 *pal, u32 texa_lo, u32 texa_hi) {
    const u8 *p = (const u8 *)buf + y * kh1_texfmt_stride(psm, w);
    u32 ta0 = texa_lo & 0xFF, aem = texa_lo >> 15 & 1, ta1 = texa_hi & 0xFF, v, r, g, b;
    switch (kh1_texfmt_of(psm)) {
    case KH1_TEXFMT_RGBA8:
        p += x * 4;
        v = p[0] | p[1] << 8 | p[2] << 16;
        if (kh1_texfmt_texa(psm)) return v | (aem && !v ? 0 : ta0) << 24;
        return v | (u32)p[3] << 24;
    case KH1_TEXFMT_A1B5G5R5:
        p += x * 2;
        v = p[0] | p[1] << 8;
        r = back5(widen5(v & 31));
        g = back5(widen5(v >> 5 & 31));
        b = back5(widen5(v >> 10 & 31));
        return r | g << 8 | b << 16 | (v & 0x8000 ? ta1 : aem && !(r | g | b) ? 0 : ta0) << 24;
    case KH1_TEXFMT_P8: return pal[p[x]];
    case KH1_TEXFMT_P4: return pal[p[x / 2] >> (x & 1) * 4 & 15];
    }
    return 0;
}

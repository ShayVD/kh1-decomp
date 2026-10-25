#ifndef PLATFORM_VERTEX_H
#define PLATFORM_VERTEX_H

#include "platform/drawstate.h"
#include "platform/primasm.h"
#include "platform/target.h"

/* The GPU vertex and the vertex shader a port draws the GS's primitives with (docs/renderer-spec.md
 * 4.13 "Session 124", vita-port-plan 5.1bl): port code, not game code.  primasm.h's assembler gives
 * each GPU primitive's vertices as the GIF left them (KH1PaVert); this turns one into the one vertex
 * layout every pipeline reads (32 bytes):
 *
 *   x, y     f32  target pixels: target.h's viewport (((X - OFX) / 16 + ox) x scale) plus half a GS
 *                 pixel (primasm.h: the GS samples a pixel at its corner, a GPU at its centre), so a
 *                 GPU's top-left rule covers the GS's pixels at scale 1 and the same GS area at any
 *                 scale.  The vertex shader maps them to clip space with one per-pass uniform
 *                 (2 / w, 2 / h, -1, -1; a flip for a GPU whose y grows up), w = 1
 *   z        f32  depth.h's kh1_depth_f32 under the pass's Z buffer (Z x 2^-bits, clamped)
 *   s, t, q  f32  the texture coordinate: UV (FST 1) as U / 16 / 2^TW, V / 16 / 2^TH and q 1; ST / Q
 *                 (FST 0) as the GIF sent them (S / Q is already normalised; the shader divides)
 *   rgba     u8x4 RGBAQ's bytes as UNORM8 (x / 255; 0x80 is the GS's 1.0, which texfunc.h's shader
 *                 takes back: the colour is not rescaled here)
 *   f        u8   F as UNORM8 (fog.h's shader takes it back), 3 bytes of padding
 *
 * Every position carries w = 1 (the GS has no w: renderers A / B project on the VU), so every
 * attribute is interpolated linearly in screen space, as the GS does for RGBA, Z, F and S / T / Q,
 * with no noperspective qualifier; ST / Q's perspective is the fragment shader's divide (S / Q,
 * T / Q per pixel, the GS's order).  Nothing is rescaled per draw but UV's 1 / 2^TW, 1 / 2^TH, so a
 * batch's vertices can be written once into one buffer.
 *
 * The vertex shader's variants (KH1VertKey) are what it reads and passes on: the position always;
 * the colour unless the draw is DATE's set-up (which reads only the target); the texture coordinate
 * as UV (2 floats) or ST / Q (3) with a texture; F with fog.  At most 7 (kh1_vertex_variants counts
 * them over a pipeline set).  Not part of the PS2 build. */
#ifndef KH1_PS2
typedef struct {
    f32 x, y, z;
    f32 s, t, q;
    u8 rgba[4];
    u8 f, pad[3];
} KH1GpuVert;

enum { KH1_VTX_NONE, KH1_VTX_UV, KH1_VTX_STQ };
typedef struct {
    u8 setup;  /* 1: position only (DATE's set-up) */
    u8 tex;    /* KH1_VTX_* */
    u8 fog;    /* F passed on */
} KH1VertKey;

/* what a draw's vertices need, from the pass's depth buffer and the texture's size */
typedef struct {
    const KH1RenderPass *pass;
    u32 zpsm;          /* 0x30 | ZBUF.PSM (depth.h's clamp and scale) */
    u32 fst;           /* PRIM FST */
    f32 su, sv;        /* UV's scale: 1 / (16 x 2^TW), 1 / (16 x 2^TH) */
} KH1VertCtx;

/* the context for a pass, ZBUF's low word, PRIM and TEX0's low / high words (TW / TH) */
void kh1_vertex_ctx(KH1VertCtx *c, const KH1RenderPass *pass, u32 zbuf_lo, u32 prim, u32 tex0_lo, u32 tex0_hi);
/* n of primasm.h's vertices to GPU vertices */
void kh1_vertex_of(const KH1VertCtx *c, const KH1PaVert *in, u32 n, KH1GpuVert *out);
/* the vertex shader a pipeline's draws use */
void kh1_vertkey_of(const KH1PipeKey *p, KH1VertKey *out);
/* the variant's number, 0 .. 6 (0 the set-up's), and its name ("pos", "pos col uv fog", ...) */
u32 kh1_vertkey_index(const KH1VertKey *k);
const char *kh1_vertkey_str(u32 index);
/* the distinct vertex shaders a pipeline set's pipelines use: the count, and a bit per index in *mask */
u32 kh1_vertex_variants(const KH1PipeSet *s, u32 *mask);
#endif

#endif

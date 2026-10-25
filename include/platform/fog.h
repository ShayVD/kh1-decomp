#ifndef PLATFORM_FOG_H
#define PLATFORM_FOG_H

/* The fog a port's fragment shader runs for the GS's PRIM FGE, the vertices' F and FOGCOL
 * (docs/renderer-spec.md 4.13 "Session 122", vita-port-plan 5.1bj): port code, not game code.
 *
 * The GS fogs after the texture function (include/platform/texfunc.h) and before the alpha test and
 * the blend, the colour only:
 *
 *   RGB = (F x C + (0xFF - F) x FOGCOL) >> 8          A unchanged
 *
 * F 0xFF is not quite no fog (C x 255 >> 8: 0xFF gives 0xFE), F 0 is FOGCOL x 255 >> 8.  F is a
 * vertex value interpolated across the primitive in screen space (like Gouraud RGBA: noperspective in
 * the shader when the positions carry a w), a sprite's the second vertex's.  Where it comes from:
 * renderers A (P2 / P3 / P7) and B compute F = clamp(A + B / w) per vertex (renderer-spec 2.2), the
 * GIF's XYZF2 or FOG register carries it; FOGCOL is per draw (renderer B's func_0015f488 from the
 * model, func_0015f388 from D_002BC0F0) and the grid's (4.14).
 *
 * The shader gets C, F and FOGCOL as UNORM8 values (x / 255).  The plain float mix(FOGCOL, C, F)
 * rounded to 8 bits is at most 2 from the GS (the GS's floored >> 8 against a rounded / 255 weight);
 * kh1_fog_shader's exact form takes the 8-bit values back (floor(x x 255 + 0.5)) and does the GS's
 * integer step, exact for every C, F and FOGCOL (tests/host/fog_test.c).  Not part of the PS2 build. */
#ifndef KH1_PS2
/* the GS's fogged colour: RGB of c (RGBA8, R in bits 0-7) toward FOGCOL's RGB by f (0 .. 0xFF), A kept */
u32 kh1_fog_gs(u32 c, u32 f, u32 fogcol);
/* a model of the shader on UNORM inputs: exact (the 8-bit values taken back) when exact is nonzero,
 * else mix(FOGCOL, C, F) in floats rounded to 8 bits */
u32 kh1_fog_shader(u32 c, u32 f, u32 fogcol, int exact);
#endif

#endif

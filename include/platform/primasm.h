#ifndef PLATFORM_PRIMASM_H
#define PLATFORM_PRIMASM_H

/* The primitive assembly a port's GIF parser runs: the GS's vertex queue as GPU primitives
 * (docs/renderer-spec.md 4.13 "Session 122", vita-port-plan 5.1bj): port code, not game code.
 *
 * The GS keeps a queue of vertices.  A PRIM write empties it; each XYZ(F)2 / XYZ(F)3 adds one, and
 * an XYZ(F)2 that fills it draws one primitive with the state in force at that kick:
 *
 *   POINT 1, LINE 2, TRIANGLE 3, SPRITE 2   lists: the queue empties after each
 *   LINESTRIP 2, TRISTRIP 3                 strips: the oldest vertex leaves, the last 1 / 2 stay
 *   TRIFAN 3                                the fan: the second vertex leaves, the first and last stay
 *
 * XYZ(F)3 (ADC) adds a vertex without drawing: renderer A's strip restarts, the glyph and face
 * sprites' first corner, a strip restarted inside one tag (func_00208458); a list whose queue an
 * XYZ(F)3 fills empties with nothing drawn.  Any other register write leaves the queue alone, so a
 * write between a strip's kicks (the window bevel's ALPHA_1, renderer-spec 4.9) changes the state of
 * the primitives after it and the strip goes on.  A GPU draws a batch in one state, so the port ends
 * its batch where the draw state changes and keeps this queue: the next batch's first triangle is
 * the strip's last two vertices and the new one (the caller flushes; the queue lives in KH1PrimAsm).
 *
 * The port emits independent lists (GPU POINTS, LINES, TRIANGLES): each primitive's vertices in the
 * GS's order, with
 *   - IIP 0 (flat): every vertex's RGBA the last vertex's, the GS's flat colour (the vertex whose kick
 *     drew).  A GPU's flat interpolation takes a provoking vertex (GL's default the last, Vulkan /
 *     D3D the first), so the colour is copied instead and either convention draws the same.  Q, Z, F,
 *     ST and UV stay per vertex.
 *   - SPRITE: two triangles over the rectangle the two corners span, each corner's X / U / S from
 *     one vertex and Y / V / T from the other; RGBA, Z, F and Q the second vertex's (the GS's sprite,
 *     as PCSX2 draws it; the game's textured sprites are all FST, so Q is unused).
 * The GS draws no back faces away (no culling), nor does the port.  Pixel centres: the GS samples a
 * pixel at its integer corner ((X + 15) >> 4 is the first pixel of an edge at X in 12.4), a GPU at
 * its centre, so the port's positions are the GS's plus half a pixel; then a GPU's top-left fill rule
 * covers the GS's pixels (tests/host/primasm_test.c, the sprites).  RGBA, Z and F are interpolated
 * linearly in screen space on the GS (noperspective when the positions carry a w); ST / Q is the
 * texture's perspective (the shader divides).
 *
 * What the game sends (4.13 "Session 122"): TRISTRIP (Gouraud: renderer A's batches and P8, the text's
 * gradient frames and bars, wintext's icons, fade.c's wipe; flat: the window bevel with its ALPHA_1
 * changes, winmenu / winpart's textured strips, sceneeff func_00102da8, the shadow pass), TRIFAN
 * (renderer A / B's clipped polygons, the HUD's arcs), TRIANGLE (the HUD gauges' textured pairs),
 * SPRITE (the copies, UI, fonts, fades), LINE (the wave's 100 Gouraud lines; prim.c's 3D line has no
 * main-ELF caller).  No LINESTRIP; POINT only as a PRIM write with no vertex (opdma's zero A+D
 * qwords).  Not part of the PS2 build. */
#ifndef KH1_PS2
enum { KH1_PA_NONE, KH1_PA_POINTS, KH1_PA_LINES, KH1_PA_TRIANGLES };

/* a vertex as the GIF left it at the kick (the fields of host/null/gsregs.h's KH1GsVert): XYZ's X | Y
 * << 16 (12.4), Z, F, UV (U | V << 16, 10.4), RGBA, ST's S and T and RGBAQ's Q (floats' bits) */
typedef struct {
    u32 xy, z, f, uv, rgba, s, t, q;
} KH1PaVert;

typedef struct {
    u32 prim;        /* the attributes in force (PRIM's, PRMODE's under PRMODECONT 0) */
    u32 n;           /* vertices queued */
    KH1PaVert q[3];
} KH1PrimAsm;

/* the GPU primitive class a PRIM type draws as (SPRITE: TRIANGLES), KH1_PA_NONE for 7 */
u32 kh1_pa_class(u32 prim);
/* a PRIM write (or the attributes changing under PRMODE): the queue empties */
void kh1_pa_prim(KH1PrimAsm *a, u32 prim);
/* the attributes change with no PRIM write (a PRMODE write under PRMODECONT 0): the queue stays */
void kh1_pa_attr(KH1PrimAsm *a, u32 prim);
/* a vertex kick (draw: XYZ(F)2, else XYZ(F)3).  Writes the GPU vertices of the primitive it draws to
 * out and returns their count: 0, 1 (a point), 2 (a line), 3 (a triangle) or 6 (a sprite's two) */
u32 kh1_pa_vertex(KH1PrimAsm *a, const KH1PaVert *v, int draw, KH1PaVert out[6]);
#endif

#endif

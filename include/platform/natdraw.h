#ifndef PLATFORM_NATDRAW_H
#define PLATFORM_NATDRAW_H

#include "platform/cmdbuf.h"

/* The native renderer (docs/native-renderer.md): port code, not game code.  With it on, a VU1 program the port
 * knows is not run: its run's record stream (the matrices and the untransformed vertices the game's chains
 * unpacked into VU1 memory) is handed to the GS worker and the recorder as one "native run", and the GPU's vertex
 * shader does what the program did per vertex (the matrix, the divide by w, the screen mapping).  So the game
 * thread does no VU1 arithmetic for it, the GS worker no per-vertex GIF decode, and the GPU thread no per-vertex
 * conversion or per-triangle batching: a run is one draw command.
 *
 * Stage 1 is P18 (renderer B's rigid, flat-coloured, back-face-culled program: Sora in Dive to the Heart).  The
 * payload a run hands over (u32 words, whole qwords):
 *
 *   qword 0   KH1_NAT_MAGIC | program, the records, the matrices, the records' length in qwords
 *   qword 1   RGBA (vf01's four bytes), F (vi12 >> 4), 1 when every vertex has ADC (vi12's bit 15: nothing drawn),
 *             1 when a back face is dropped (vi13's bit 15: P18's cull)
 *   records   a qword (the GIF tag's two low words, the vertex count n, the strip's starting parity: P18's
 *             h[3]), then n vertices of 2 qwords: (x, y, z, the matrix's index in this run), (s, t, q, 0)
 *   matrices  4 qwords each: the VU's columns (vf05-08 / vf12-15 / vf19-22 as loaded: c = col0 x + col1 y +
 *             col2 z + col3 w), raw VU floats
 *
 * A record is a TRISTRIP of n vertices.  P18 drops the triangle that ends at vertex j (ADC) when the z of the
 * cross product of its two screen edges, the operands swapped by the parity (h[3] + j) & 1, is negative: in
 * screen space (y down) that keeps the triangle (p[j-2], p[j-1], p[j]) with a signed area >= 0 at odd parity, and
 * its mirror at even.  kh1_nat_tris lists each strip's triangles with the even ones' first two vertices swapped,
 * so every triangle drawn has the same winding rule: kept when cross(p1 - p0, p2 - p0) >= 0 in window
 * coordinates (y down), which the GPU's cull mode does (KH1_NAT_CULL_*).
 *
 * The GPU vertex is vertex.h's KH1GpuVert with x, y, z the position as the game sent it, s, t, q the
 * texture coordinate as sent (P18 multiplies all three by Q; the GPU's perspective-correct interpolation and the
 * fragment shader's S / Q divide give the GS's per-pixel result), rgba and f the run's, and pad[0] the matrix
 * index.  The vertex shader (shadergen.h, the native variants KH1_VERT_NAT + vertex.h's index) reads 4 rows a
 * matrix from the uniform u_m: clip = F x (x, y, z, 1), with F = N x M folded on the CPU per run (kh1_nat_fold),
 * N the screen mapping vertex.h's kh1_vertex_of applies to the GS's XYZ (XYOFFSET, the half pixel, the margin
 * and scale, the pass's 2 / w - 1) as a matrix acting on M's result before the divide, and z's depth.h scale;
 * the shader clamps z to 0 .. w (the GS clamps Z, a GPU would clip).  Not part of the PS2 build. */
#ifndef KH1_PS2
#define KH1_NAT_MAGIC 0x4E415400u /* "NAT" + the program's number */
#define KH1_NAT_MATS 32            /* matrices a native draw command reads (u_m's 128 rows) */
#define KH1_NAT_VERTS 16384        /* GPU vertices a native run lists at most (3 a triangle) */
enum { KH1_NAT_CULL_NONE, KH1_NAT_CULL_CCW, KH1_NAT_CULL_CW };

/* the GPU vertices of a run's records (data: the records as above, nrec of them; mats: the run's matrix count, a
 * record's index past it is dropped as ADC), with the run's rgba / f: the number written (at most max), and the
 * triangles dropped in *lost when out was full */
u32 kh1_nat_tris(const u32 *data, u32 nrec, u32 nmat, u32 rgba, u32 f, KH1GpuVert *out, u32 max, u32 *lost);

/* F = N x M for each of nmat matrices (VU column order, raw floats) into out (4 rows of 4 floats a matrix, the
 * vertex shader's u_m), for a pass and the draw's ZBUF (its PSM picks depth.h's scale) and the GS's X shift in
 * sixteenths (gsregs.c kh1_gs_xshift) */
void kh1_nat_fold(const KH1RenderPass *p, u32 zbuf_lo, s32 xshift16, const u32 *mats, u32 nmat, f32 *out);

/* the reference: P18's screen position of one vertex (GS units, before 12.4: x, y, and z, from M's column-order
 * matrix and the position), for the tests: what the VU computes, in plain float */
void kh1_nat_ref_xyz(const u32 *m, const f32 *pos, f32 out[3]);
#endif

#endif

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
/* 2026-10-31: or'd into kh1_cmd_native's cull: the vertices carry mi's bit 7 (P0's): colour and fog straight across
 * the screen (drawstate.h lin) and z not clamped */
#define KH1_NAT_LIN 0x80u

/* 2026-11-01: GPU skinning (docs/native-renderer.md "P13's two-bone vertices on the GPU", config natskin): a record
 * whose word 3 has KH1_NAT_SKIN (P13's, with natskin on) has 3 qwords a vertex: (x1, y1, z1, mi1 | mi2 << 16),
 * (s, t, q, w1), (x2, y2, z2, w2), the two bones' pre-weighted positions as P13 reads them (w the weight) and their
 * matrices' indices in the run; a one-bone vertex has mi2 = mi1 and the second position 0.  The vertex shader sums
 * u_m[mi1] x p1 + u_m[mi2] x p2, which is P13's sum before its divide.  A record's length in qwords is
 * KH1_NAT_REC_QW (records without the bit: 2 qwords a vertex, as before) */
#define KH1_NAT_SKIN 0x10000u
/* 2026-11-02: a cached record (natvb below): 2 qwords, the record's own first qword (word 3's KH1_NAT_VB set), then the
 * entry's vertices, the record's first index, its index count and the hand-over's sequence number */
#define KH1_NAT_VB 0x20000u
/* 2026-11-02 (natvbjoin): a cached record's index count word (its second qword's word 2) also carries the entry's home:
 * its vertices' matrix indices are the run's own plus home, so the run's matrices go at u_m[home ..], and runs of
 * entries with homes after each other share one draw (cmdbuf.c vb_join) */
#define KH1_NAT_VB_COUNT(w) ((w) & 0xFFFFFFu)
#define KH1_NAT_VB_HOME(w) ((w) >> 24)
#define KH1_NAT_REC_QW(r) ((r)[3] & KH1_NAT_VB ? 2u : 1u + (r)[2] * ((r)[3] & KH1_NAT_SKIN ? 3u : 2u))

/* the GPU vertices of a run's records (data: the records as above, nrec of them; mats: the run's matrix count, a
 * record's index past it is dropped as ADC), with the run's rgba / f: the number written (at most max), and the
 * triangles dropped in *lost when out was full */
u32 kh1_nat_tris(const u32 *data, u32 nrec, u32 nmat, u32 rgba, u32 f, KH1GpuVert *out, u32 max, u32 *lost);

/* 2026-11-01: kh1_nat_tris for KH1_NAT_SKIN records, into the skinned vertex (vertex.h KH1GpuVertSk); lin or'd into
 * every vertex's mi (KH1_NAT_LIN) */
u32 kh1_nat_tris_skin(const u32 *data, u32 nrec, u32 nmat, u32 rgba, u32 f, u32 lin, KH1GpuVertSk *out, u32 max, u32 *lost);
/* 2026-11-04 (pipes.c natinplace): the two above with add put on every vertex's word 3 (its matrix indices) first, as
 * a joined P13 run's records get it when they are copied into the op (pipes.c r_nat_rec), so they can be read where
 * the game thread wrote them */
u32 kh1_nat_tris_at(const u32 *data, u32 nrec, u32 nmat, u32 add, u32 rgba, u32 f, KH1GpuVert *out, u32 max,
                    u32 *lost);
extern int kh1_nat_prefetch; /* 1 (the default): natdraw.c's listing prefetches the records ahead of it */
u32 kh1_nat_tris_skin_at(const u32 *data, u32 nrec, u32 nmat, u32 add, u32 rgba, u32 f, u32 lin, KH1GpuVertSk *out,
                         u32 max, u32 *lost);

/* 2026-10-31: P0's payload (program 0, docs/native-renderer.md stage 3): one record a run (its batch), one matrix (the
 * screen matrix times the clip one, the VU's columns), qword 1's word 0 the F all vertices get (P0's I register);
 * a vertex is (x, y, z, the strip flag word), (s, t, 1.0, RGBA: ST already / 4096 and the colour already scaled as
 * P0 scales it).  kh1_nat_tris0 lists the triangles P0 back-face culls (culled 1, for a draw with the cull mode) or
 * those it does not (culled 0, a draw with none), in the winding kh1_nat_tris uses.  P0's clipper (a triangle
 * across the guard box, split into a fan on the VU) is not reproduced: the GPU clips at its own frustum, with z
 * clamped as for P18, so a triangle across the guard box's near or far plane is drawn whole (z clamped) where the
 * VU drew its inside part */
u32 kh1_nat_tris0(const u32 *data, u32 nrec, u32 f, int culled, KH1GpuVert *out, u32 max, u32 *lost);
/* 2026-11-01: 1 (the default) each record vertex converted once, its triangles copies (config.txt recfast=) */
extern int kh1_nat_once;

/* F = N x M for each of nmat matrices (VU column order, raw floats) into out (4 rows of 4 floats a matrix, the
 * vertex shader's u_m), for a pass and the draw's ZBUF (its PSM picks depth.h's scale) and the GS's X shift in
 * sixteenths (gsregs.c kh1_gs_xshift) */
void kh1_nat_fold(const KH1RenderPass *p, u32 zbuf_lo, s32 xshift16, const u32 *mats, u32 nmat, f32 *out);

/* 2026-11-02 (docs/native-plan.md "Vertex buffers cached by the records' address"; config.txt natvb=, host
 * KH1_HOST_NATVB): renderer B's runs (P18, P11, P10) whose records natchain reads from the chain are cached by the
 * records' EE address and length (the program, the run's colour, F and flags too).  An entry keeps the run's GPU
 * vertices once each (a strip vertex once, not once a triangle) and its triangles as 16-bit indices in kh1_natvb_mem
 * (GPU memory on the Vita), and the stream's shape: where its matrices are (the game rewrites those in place every
 * frame) and which slot registers the run reads.  A run that finds its entry, with the stream's other words hashing as
 * they did, hands over a payload of the run's matrices and one 2-qword KH1_NAT_VB record a strip (no vertices): no
 * parse, a few qwords into the pool, and the GPU thread draws the entry's indices from GPU memory (cmdbuf.h
 * kh1_cmd_native_vb).  kh1_natvb: 0 off, 1 every word but the matrices hashed on each hit, 2 one qword in 8 hashed, 3
 * (host) as 1 and each hit also parsed and its triangles compared */
typedef struct KH1NatVb KH1NatVb;
extern int kh1_natvb;
extern u8 *kh1_natvb_mem;           /* the entries' vertices and indices: GPU-visible memory (the platform's) */
extern u32 kh1_natvb_bytes;
extern volatile u32 kh1_natvb_done; /* every KH1_NAT_VB record with a sequence number up to this one read for good */
extern int kh1_natvb_fenced;        /* the GPU renderer publishes done itself (host/vita/gxm.c, after the GPU's finish) */
extern u32 kh1_natvb_seq;           /* the game thread's last sequence number */
/* the log's counts: hits, runs with no entry, entries made, entries whose words changed, entries dropped for room,
 * entries that found no room, check mode's differences, runs not cacheable (too big) */
extern u32 kh1_natvb_hits, kh1_natvb_miss, kh1_natvb_made, kh1_natvb_stale, kh1_natvb_evict, kh1_natvb_noroom,
    kh1_natvb_bad, kh1_natvb_big;
/* the GPU side: commands of a frame with KH1_NAT_VB records up to seq read by the GPU for good */
void kh1_natvb_publish(u32 seq);
/* the game thread: the entry of a run (src: the held unpack's words, lim qwords) or 0 (a miss, its key remembered) */
KH1NatVb *kh1_natvb_find(const u32 *src, u32 lim, u32 prog, u32 rgba, u32 f, u32 flags);
/* 2026-11-02: 1 (the default) each new entry gets a home after the last one's matrices (wrapping at KH1_NAT_MATS), so
 * the GPU thread can join cached runs into one draw; 0 every home 0 (host KH1_HOST_NATVBHOME, config natvbhome) */
extern int kh1_natvb_home;
/* 1 when the stream's words other than the matrices hash as when the entry was made (else the entry is dropped) */
int kh1_natvb_same(KH1NatVb *e, const u32 *src);
/* a hit's payload into ob: header, the stub records, the matrices (from the stream, or mats_reg[slot] for those the run
 * read from the slot registers); its matrix count in *nmat, the slots' last loads (payload indices, -1 none) in last;
 * returns the payload's qwords */
u32 kh1_natvb_payload(KH1NatVb *e, const u32 *src, const u32 *const *mats_reg, u32 (*ob)[4], u32 (*mats)[4][4], u32 *nmat,
                      s32 *last);
/* after a miss whose run read its records from src: an entry made from its payload (pay, natdraw.h's format: P18's
 * records), msrc[i] the stream qword of payload matrix i's first row (-1 - slot: from the slot's registers), mbody the
 * qwords a matrix record skips after its first (7 P18 / P11, 4 P10), last the slots' last loads, lin or'd into mi */
void kh1_natvb_learn(const u32 *src, u32 lim, u32 prog, u32 flags, const u32 *pay, const s16 *msrc, u32 mbody,
                     const s32 *last, u32 lin);
/* check mode: 1 when the entry's triangles, expanded, are kh1_nat_tris's of the payload pay (lin or'd in) */
int kh1_natvb_check(const KH1NatVb *e, const u32 *pay, u32 lin);
/* the GPU memory the entries hold now, bytes */
u32 kh1_natvb_used(void);
/* forget every entry (the arena's memory gone or the switch changed): only when no record is in flight */
void kh1_natvb_reset(void);

/* the reference: P18's screen position of one vertex (GS units, before 12.4: x, y, and z, from M's column-order
 * matrix and the position), for the tests: what the VU computes, in plain float */
void kh1_nat_ref_xyz(const u32 *m, const f32 *pos, f32 out[3]);
#endif

#endif

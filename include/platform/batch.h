#ifndef PLATFORM_BATCH_H
#define PLATFORM_BATCH_H

#include "platform/drawstate.h"
#include "platform/target.h"

/* Batches: the GS's write stream cut into GPU draw calls (docs/renderer-spec.md 4.13 "Session 124",
 * vita-port-plan 5.1bl): port code, not game code.  The GS draws each primitive at its kick in the state
 * in force; a GPU draws a run of primitives in one call, so a port's GIF parser appends each primitive's
 * vertices (include/platform/vertex.h) to the open batch and ends the batch where what the call binds
 * changes:
 *
 *   the render pass   FRAME's port target (target.h: id, FBP, FBW, PSM) or the depth buffer bound: the
 *                     pass ends (on a tiled GPU like the Vita's SGX543 a new scene: the costly change)
 *   the pipeline      drawstate.h's GPU draws (one or two, AFAIL), DATE's set-up, their pipeline keys
 *   the texture       TEX0's binding (TBP0 / TBW / PSM / TW / TH / TCC / TFX) or the sampler object
 *   the uniforms      KH1DrawUniforms (AREF, FIX, FOGCOL, TEXA, the region bounds, a FETCH blend's)
 *   the scissor       the pass's scissor rectangle (dynamic state: no new pipeline)
 *   a transfer        an upload, a local copy or a CLUT load since the last primitive (kh1_batch_break):
 *                     the batch's draws must not see the new texels, so the next primitive opens a new one
 *
 * XYOFFSET is not among them: the vertices are mapped to target pixels on the CPU (vertex.h), so a moved
 * window draws in the same call.  A state that draws nothing (ZTST NEVER, PRIM 7) neither opens nor ends
 * a batch.  primasm.h's vertex queue is the GIF parser's and is carried across the cut (a strip whose
 * ALPHA_1 changes between kicks goes on in the next batch).  A batch issues drawstate.h's n draws plus
 * DATE's set-up: that is its draw calls.
 *
 * Session 125 (renderer-spec 4.13 "Session 125", vita-port-plan 5.1bm): **column groups**.  The PS2's
 * texture-cache trick (5.4 "Session 93") draws one full-screen copy 16 times, each under a 32-pixel
 * column SCISSOR: the sprites are not inside their columns (the scissor is what cuts them), so dropping a
 * scissor that clips nothing gains nothing there.  Instead a run of primitives under one scissor (the
 * group, at most KH1_BATCH_GROUP) that is repeated, primitive for primitive (the same key but the scissor,
 * the same vertices: the caller's signature `sig`, 0 for unknown), under the horizontally adjacent
 * scissor of the same rows is drawn once with the union of the two: the repeat is absorbed (`merged`)
 * and the group's scissor widened (ux0 .. ux1), and so on column by column.  Exact: each pixel lies in
 * one column, so the order across columns cannot matter, unless a primitive samples the target it draws
 * into (kh1_target_id / kh1_target_alias of its TEX0 against the pass: such a group is never merged) or a
 * transfer falls between columns (a break ends the group).  A repeat that stops part way is replayed as
 * ordinary primitives under its own column.  A port keeps a group's batches unsubmitted until the group
 * ends (a primitive that neither joins nor repeats it), then submits them with the union scissor.
 *
 * Counted per frame (kh1_batch_frame) for a draw-call budget: the batches, draw calls, primitives, GPU
 * vertices (32 bytes each), and what ended each batch.  A draw that samples the target it renders into
 * (a feedback loop) is not detected here: the game's copies go between targets (target.h).  Not part of
 * the PS2 build. */
#ifndef KH1_PS2
typedef struct {
    u8 n, setup;
    KH1PipeKey pipe[2], setup_pipe;
    KH1DrawUniforms u;
    KH1Sampler sampler;
    u32 tex0_lo, tex0_hi;
    u8 rt, psm, depth;
    u16 fbp, fbw;
    s32 sx0, sy0, sx1, sy1;
} KH1BatchKey;

typedef struct {
    u32 batches, draws, prims, verts;
    u32 passes, pipes, textures, uniforms, scissors, breaks; /* what opened each batch (one may have several) */
    u32 merged, columns; /* session 125: primitives absorbed into a column group, columns merged */
} KH1BatchCount;

#define KH1_BATCH_GROUP 32
typedef struct {
    KH1BatchKey k;
    u32 nv, sig;
} KH1BatchPrim;

enum { KH1_GRP_NONE, KH1_GRP_RECORD, KH1_GRP_REPEAT, KH1_GRP_DONE };

typedef struct {
    KH1BatchKey cur;
    int open;           /* a batch is open */
    int broken;         /* a transfer since the last primitive */
    u32 frames;
    KH1BatchCount frame, total, max; /* this frame's, every ended frame's sum, the largest of each */
    /* session 125: the column group */
    KH1BatchPrim grp[KH1_BATCH_GROUP];
    u32 ngrp, rep;      /* the group's primitives; how many of them the column being repeated has matched */
    u8 gstate, gfull;   /* KH1_GRP_*; past KH1_BATCH_GROUP or sampling its own target (never merged) */
    s32 ux0, ux1;       /* the group's scissor columns so far (its rows are grp[0].k's) */
    s32 cx0, cx1;       /* the column being repeated */
} KH1Batcher;

void kh1_batch_reset(KH1Batcher *b);
/* the batch key of a draw state and its render pass */
void kh1_batch_key(const KH1DrawState *d, const KH1RenderPass *p, KH1BatchKey *out);
/* a primitive of nv GPU vertices drawn in d / p; returns 1 when it opened a batch */
int kh1_batch_prim(KH1Batcher *b, const KH1DrawState *d, const KH1RenderPass *p, u32 nv);
/* session 125: the same with the primitive's vertex signature (nonzero, equal for the same vertices) so a
 * column repeat can be absorbed; returns 1 when it opened a batch, 0 when it joined one or was absorbed */
int kh1_batch_prim_sig(KH1Batcher *b, const KH1DrawState *d, const KH1RenderPass *p, u32 nv, u32 sig);
/* a transfer or CLUT load: the next primitive opens a new batch (and the column group ends) */
void kh1_batch_break(KH1Batcher *b);
/* the frame ends: its counts into the totals and maxima; the next frame starts with no batch open */
void kh1_batch_frame(KH1Batcher *b);
#endif

#endif

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
} KH1BatchCount;

typedef struct {
    KH1BatchKey cur;
    int open;           /* a batch is open */
    int broken;         /* a transfer since the last primitive */
    u32 frames;
    KH1BatchCount frame, total, max; /* this frame's, every ended frame's sum, the largest of each */
} KH1Batcher;

void kh1_batch_reset(KH1Batcher *b);
/* the batch key of a draw state and its render pass */
void kh1_batch_key(const KH1DrawState *d, const KH1RenderPass *p, KH1BatchKey *out);
/* a primitive of nv GPU vertices drawn in d / p; returns 1 when it opened a batch */
int kh1_batch_prim(KH1Batcher *b, const KH1DrawState *d, const KH1RenderPass *p, u32 nv);
/* a transfer or CLUT load: the next primitive opens a new batch */
void kh1_batch_break(KH1Batcher *b);
/* the frame ends: its counts into the totals and maxima; the next frame starts with no batch open */
void kh1_batch_frame(KH1Batcher *b);
#endif

#endif

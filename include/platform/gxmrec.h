#ifndef PLATFORM_GXMREC_H
#define PLATFORM_GXMREC_H

#include "platform/cmdbuf.h"

/* The command list as GXM calls (docs/renderer-spec.md 4.13 "Session 128", vita-port-plan 5.1bp): port code,
 * not game code.  A "null GXM": it walks one frame of cmdbuf.h's recorder and writes down the calls a Vita
 * renderer makes for it, in order, without a GPU, so the Vita build (host/vita/, PR #131) has one sequence to
 * turn into sceGxm* calls and the host tests can replay that sequence through a software rasteriser
 * (tests/host/cmdbuf_test.c "gxm"): the same pixels as the commands themselves.
 *
 *   BEGIN_SCENE     sceGxmBeginScene on a pass's colour target (`tgt`: cmdbuf.h's target index; rt / fbp /
 *                   fbw / psm / w / h) and depth buffer, with the pass's colour and depth load (a LOAD is the
 *                   scene's background / depth-stencil surface loaded, DONT_CARE not)
 *   END_SCENE       sceGxmEndScene, with the pass's colour and depth store (DISCARD: no store; OPEN: the last
 *                   frame's pass whose store the next frame decides: a port stores it)
 *   TEX_UPLOAD      the texture cache's entry `slot` written (the CPU's copy into its GXM texture memory; the
 *                   cache never refills an entry a draw of this frame uses, so it may happen inside a scene)
 *   PAL_FILL        the palette cache's slot `slot` written (a 256 x 1 palette texture)
 *   PAL_READBACK    the palette slot `slot` read back from target `src` (the CLUT pass: the scene ended and
 *                   stored before it; a GPU-written palette, then used as a palette texture)
 *   TARGET_UPLOAD   CPU texels into target `dst` at (dx, dy, w, h) (the target's scene ended before, the next
 *                   scene loads it)
 *   BLIT            sceGxmTransferCopy from target `src` (or GS memory: 0) to target `dst` (or 0)
 *   SET_PROGRAMS    sceGxmSetVertexProgram / sceGxmSetFragmentProgram: pipeline `pipe` of the frame's table
 *                   (its fixed-function state: blend, mask, depth, stencil), fragment program `frag` (the
 *                   frame's shader table, shadergen.h's text) and vertex program `vert` (vertex.h's index)
 *   SET_TEXTURE     sceGxmSetFragmentTexture 0: the texture cache's entry `slot` (TEX0 in tex0_lo / hi gives
 *                   its size and format), or target `src`'s own texture, and the palette slot `pslot` (an
 *                   indexed texture's palette texture, -1 none)
 *   SET_REGION      sceGxmSetRegionClip: the command's scissor (sx0, sy0) .. (sx1, sy1) in target pixels
 *   SET_UNIFORMS    the fragment program's 16 floats at `uoff` in the frame's uniform ring slot (and the
 *                   pass's vertex uniform at the scene's uoff)
 *   DRAW            sceGxmDraw: triangles / lines / points (`cls`) of nv vertices from v0 of the frame's vertex
 *                   ring slot (32-byte vertex.h vertices, no index buffer: 0 .. nv - 1)
 *
 * A draw command with DATE first draws its set-up pipeline (stencil written), then each of its one or two GPU
 * draws (atest.h: the pass draw and AFAIL's fail draw) with its own SET_PROGRAMS.  Only state that changes
 * is set again (a scene starts with nothing set).  A transfer that reads or writes a GPU target ends the open
 * scene first (cmdbuf.h starts a new pass after it).  UPLOADs and COPYs in GS memory only are the CPU's and
 * give no call.  Plain C with no libc but memset / memcmp / sprintf / strlen (the Vita build compiles host/port/).
 * Not part of the PS2 build. */
#ifndef KH1_PS2
#define KH1_GXM_CALLS 4096
#define KH1_GXM_PIPES 128
#define KH1_GXM_FRAGS 128

enum {
    KH1_GXM_BEGIN_SCENE, KH1_GXM_END_SCENE, KH1_GXM_TEX_UPLOAD, KH1_GXM_PAL_FILL, KH1_GXM_PAL_READBACK,
    KH1_GXM_TARGET_UPLOAD, KH1_GXM_BLIT, KH1_GXM_SET_PROGRAMS, KH1_GXM_SET_TEXTURE, KH1_GXM_SET_REGION,
    KH1_GXM_SET_UNIFORMS, KH1_GXM_DRAW, KH1_GXM_OPS
};

typedef struct {
    u8 op;
    u8 tgt;           /* BEGIN / END_SCENE: the target index; TARGET_UPLOAD, BLIT: the destination (1 + index, 0 none) */
    u8 src;           /* PAL_READBACK, BLIT, SET_TEXTURE: the source target (1 + index, 0 none) */
    u8 rt, depth;     /* BEGIN_SCENE: target.h's KH1_RT_* and KH1_DS_* */
    u8 load, store, dload, dstore; /* BEGIN_SCENE: loads; END_SCENE: stores (cmdbuf.h's KH1_LOAD_* / KH1_STORE_*) */
    u8 cleared;       /* BEGIN_SCENE: the pass's leading draws cover the target (why its load is DONT_CARE) */
    u8 cls;           /* DRAW: primasm.h's KH1_PA_* */
    u8 stencil;       /* DRAW: 0, 1 tests DATE's stencil, 2 the set-up writes it */
    u8 psm;           /* BEGIN_SCENE: the target's PSM */
    s16 slot, pslot;  /* TEX_UPLOAD / PAL_*: the slot; SET_TEXTURE: the texture entry (-1 none) and palette slot */
    s16 sx0, sy0, sx1, sy1; /* SET_REGION */
    u16 fbp, fbw;     /* BEGIN_SCENE */
    u16 dx, dy, w, h; /* TARGET_UPLOAD, BLIT: the rectangle (BEGIN_SCENE: w, h the target's size) */
    u32 pipe, frag, vert; /* SET_PROGRAMS */
    u32 tex0_lo, tex0_hi; /* SET_TEXTURE: the binding (TEX_UPLOAD: the entry's) */
    u32 v0, nv;       /* DRAW */
    u32 uoff;         /* SET_UNIFORMS, BEGIN_SCENE (the pass's vertex uniform) */
    u32 cmd;          /* the command it comes from */
} KH1GxmCall;

typedef struct {
    u32 frames, calls, scenes, draws, programs, textures, regions, uniforms;
    u32 tex_uploads, pal_fills, pal_readbacks, target_uploads, blits;
    u32 loads, stores;   /* scenes that load colour, store colour */
    u32 lost;            /* calls, pipelines or shaders past the tables */
} KH1GxmCount;

typedef struct {
    KH1GxmCall call[KH1_GXM_CALLS];
    u32 n;
    KH1PipeKey pipe[KH1_GXM_PIPES];   /* the frame's pipelines (deduplicated) */
    u32 npipe;
    KH1ShaderKey frag[KH1_GXM_FRAGS]; /* its fragment programs */
    u32 nfrag;
    KH1GxmCount frame, total;
} KH1GxmRec;

void kh1_gxm_clear(KH1GxmRec *g);
/* the calls for the recorder's frame (between kh1_cmd_frame and kh1_cmd_reset_frame), replacing the last */
void kh1_gxm_frame(KH1GxmRec *g, const KH1CmdRec *r);
/* a call as text: "begin_scene 3D target (1a00) depth main load DONT_CARE ...", "draw tri 6 from 12" */
const char *kh1_gxm_call_str(const KH1GxmCall *c);
#endif

#endif

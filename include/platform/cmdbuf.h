#ifndef PLATFORM_CMDBUF_H
#define PLATFORM_CMDBUF_H

#include "platform/batch.h"
#include "platform/ring.h"
#include "platform/vertex.h"

/* The draw list as GPU commands (docs/renderer-spec.md 4.13 "Session 126", vita-port-plan 5.1bn): port
 * code, not game code.  A frame's GS primitives, cut by batch.h's batcher, recorded as what a GPU is
 * given: render passes, each a run of draw commands, each command one batch with
 *
 *   its key       batch.h's KH1BatchKey: the pipelines, the texture binding and sampler, the uniforms, the
 *                 scissor (a column group's widened to the union), the pass's target and depth buffer
 *   its vertices  a range of ring.h's per-frame vertex ring (32-byte vertex.h vertices, contiguous: only
 *                 the last command grows, and a replayed column is appended as a new command)
 *   its uniforms  a 64-byte slot of the uniform ring (KH1DrawUniforms); each pass takes one more (the
 *                 vertex shader's pixel-to-clip vec4: 2 / w, 2 / h, -1, -1)
 *   its state     the KH1DrawState that opened it (what a GPU binds; a replayed primitive's is its own)
 *
 * Column groups are held: from the batcher's GROUP event (a group that can still merge) until its END,
 * the group's commands are not ready (kh1_cmd_ready): a later column may widen their scissor
 * (WIDEN), or break part way, in which case the batcher replays the column's primitives and the
 * recorder appends them from the vertices it kept at REC.  A port submits the ready commands as it goes
 * or the whole frame at its end (the Vita: one scene per pass, the commands in order).
 *
 * The passes' load / store needs (4.13 "Session 126", for a tiled GPU's scene begin / end): at the frame
 * end kh1_cmd_frame decides for each pass
 *
 *   load    LOAD when the target's earlier contents can show: it was drawn before (this frame, or a
 *           frame before: targets persist) and the pass does not start by covering it (`cleared`: its
 *           leading draws that read nothing of the target, as sprites under their final scissors, cover
 *           every 8 x 8 cell: the GS has no clear, the game clears in strips); else DONT_CARE
 *   store   STORE when a later pass this frame samples the target (TEX0 is that target) or draws it again
 *           with LOAD, or the next frame does either before covering it, or it is the display (scanned
 *           out); else DISCARD.  The last frame's undecided passes are counted `open`
 *   depth   the same for the pass's depth buffer: LOAD when a draw tests Z against Z written earlier
 *           and the pass has not covered it with ALWAYS writes before its first Z test (`zcleared`);
 *           STORE when a later pass (this frame or the next) does that
 *
 * A scene is batch.h's render pass, except that a change of the depth binding alone (a draw with no Z test
 * or write next to one with the depth buffer) does not end it: the scene binds the depth buffer throughout
 * (`depth_joins` counts those).
 *
 * A command that samples the target it draws into (feedback, batch.c never merges those) is counted:
 * on a tiled GPU it ends the scene (store, then sample).  Not part of the PS2 build. */
#ifndef KH1_PS2
#define KH1_CMD_MAX 1024     /* commands a frame */
#define KH1_CMD_PASSES 256   /* passes a frame */
#define KH1_CMD_TARGETS 32   /* distinct colour targets (rt, fbp) tracked across frames */

enum { KH1_LOAD_DONT_CARE, KH1_LOAD_LOAD };
enum { KH1_STORE_DISCARD, KH1_STORE_STORE, KH1_STORE_OPEN };
/* why a pass stores (KH1CmdPass.why bits) */
enum { KH1_WHY_SAMPLED = 1, KH1_WHY_REDRAWN = 2, KH1_WHY_NEXT = 4, KH1_WHY_DISPLAY = 8 };

typedef struct {
    KH1BatchKey k;
    KH1DrawState d;
    u32 pass;          /* its pass */
    u32 v0, nv;        /* first vertex in the frame's vertex slot, count */
    u32 prims;
    u32 uoff;          /* its uniform slot (bytes into the frame's uniform slot) */
    u8 lost;           /* a vertex or uniform allocation did not fit */
    u8 samples;        /* 1 + the KH1CmdRec.tgt index it samples, 0 none */
    u8 hasv;           /* its vertices were given (not a count-only primitive) */
} KH1Cmd;

typedef struct {
    u8 rt, psm, depth;
    u16 fbp, fbw;
    u32 w, h;
    u32 cmd0, ncmd;
    u32 uoff;          /* the pass's uniform slot */
    u8 tgt;            /* its colour target's index in KH1CmdRec.tgt */
    u8 load, store, why;
    u8 dload, dstore;  /* depth (when depth != KH1_DS_NONE) */
    u8 cleared;        /* its first primitive covers the target opaquely */
    u8 zcleared;       /* its first depth use writes Z with ALWAYS over the whole target */
    u8 ztest, zwrite;  /* a command tests / writes Z */
    u8 feedback;       /* a command samples this pass's own target */
    u8 zseen, dwhy;    /* a draw used Z already; a later pass needs the depth written here */
} KH1CmdPass;

typedef struct {
    u32 frames, passes, cmds, prims, verts, held_max;
    u32 loads, dont_care, cleared;
    u32 stores, discards, open, why[4]; /* why: sampled, redrawn, next frame, display */
    u32 dpasses, dloads, dstores, ddiscards, dopen;
    u32 feedback, lost;
    u32 depth_joins;   /* batch.h passes joined into the scene before them: only the depth binding differed */
    u32 max_passes, max_cmds;
} KH1CmdCount;

typedef struct {
    KH1DrawState d;
    KH1RenderPass p;
    KH1GpuVert v[6];
    u32 n;
} KH1CmdGrpPrim;

typedef struct {
    KH1Batcher b;
    KH1Ring vring, uring;
    KH1Cmd cmd[KH1_CMD_MAX];
    KH1CmdPass pass[KH1_CMD_PASSES];
    u32 ncmd, npass, dropped;   /* dropped: commands or passes past the tables this frame */
    int open_pending;           /* a batch opened: the next primitive starts its command */
    u8 assume_drawn;            /* every target counts as drawn before (a static send: what came before is unknown) */
    s32 held;                   /* the first held command, -1 none */
    /* the primitive being added */
    const KH1DrawState *in_d;
    const KH1RenderPass *in_p;
    const KH1GpuVert *in_v;
    u32 in_n;
    KH1CmdGrpPrim grp[KH1_BATCH_GROUP];
    /* colour targets across frames: (rt, fbp, fbw, psm); drawn: in an earlier frame */
    u32 ntgt;
    u32 tgt[KH1_CMD_TARGETS];
    u8 tdrawn[KH1_CMD_TARGETS];
    u8 ddrawn[3];               /* depth buffers written in an earlier frame (KH1_DS_*) */
    /* the previous frame's last pass on each target / depth buffer, its store still open */
    KH1CmdPass prev[KH1_CMD_PASSES];
    u32 nprev;
    KH1CmdCount frame, total;
} KH1CmdRec;

/* a recorder over two rings' memory (KH1_RING_FRAMES x vslot / uslot bytes, 32-byte aligned) */
void kh1_cmd_init(KH1CmdRec *r, void *vmem, u32 vslot, void *umem, u32 uslot);
/* a primitive drawn in d / p: its n GPU vertices (v 0: counted, not written), sig as batch.h's */
void kh1_cmd_prim(KH1CmdRec *r, const KH1DrawState *d, const KH1RenderPass *p, const KH1GpuVert *v, u32 n, u32 sig);
/* a transfer or CLUT load */
void kh1_cmd_break(KH1CmdRec *r);
/* the commands that may be submitted now (those before a held column group, and not the open one) */
u32 kh1_cmd_ready(const KH1CmdRec *r);
/* the frame's vertices of a command */
const KH1GpuVert *kh1_cmd_verts(const KH1CmdRec *r, const KH1Cmd *c);
/* the frame ends: the passes' load / store decided (the previous frame's stores too), counted; then
 * kh1_cmd_reset_frame starts the next (the caller reads ncmd / cmd / npass / pass in between) */
void kh1_cmd_frame(KH1CmdRec *r);
void kh1_cmd_reset_frame(KH1CmdRec *r);
/* the run ends: the last frame's open stores counted */
void kh1_cmd_finish(KH1CmdRec *r);
/* a pass as text: "3D target (1a00) depth main: 4 cmds, load LOAD store STORE (sampled) depth load ..." */
const char *kh1_cmd_pass_str(const KH1CmdPass *p);
#endif

#endif

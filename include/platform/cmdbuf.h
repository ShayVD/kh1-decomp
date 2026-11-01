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
 *   its uniforms  a 64-byte slot of the uniform ring (session 127: shadergen.h's kh1_shader_uniforms, the 16
 *                 floats the generated shaders read); each pass takes one more (the
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
 * on a tiled GPU it ends the scene (store, then sample).
 *
 * Session 127 (4.13 "Session 127", vita-port-plan 5.1bo): **the transfers are commands too**, so a frame's
 * list is complete.  batch.h's breaks (an upload, a local copy, a CLUT load) are recorded where they
 * fall, between the draws, as
 *
 *   UPLOAD   TRXDIR 0 (BITBLTBUF's destination, TRXPOS, TRXREG): the CPU's copy of GS memory written.
 *            Nothing for the GPU, unless the rectangle lies in a render target's pages (`dst`): then the
 *            texels go into the GPU target too (the target stored before it, loaded after)
 *   COPY     TRXDIR 2: a copy between targets (`src` and / or `dst`: a GPU blit; the source stored
 *            first) or in GS memory only (the CPU's)
 *   CLUT     a CLUT buffer load: the palette cache's slot (include/platform/palcache.h) and whether it
 *            was filled now (one palette upload); `src` when CBP lies in a render target (the texture
 *            animations' CLUT pass at 0x3E00: the palette is read back from the GPU target, which is
 *            stored first)
 *   TEXTURE  the texture cache's decode (include/platform/texcache.h): a GPU texture upload into the
 *            cache's entry `slot`, placed before the first draw that binds it
 *
 * and each draw command names what it binds: `tslot` (the texture cache's entry, -1 a render target's
 * own texture or none) and `pslot` (the palette slot of the last CLUT load, for an indexed texture).
 * Neither cache refills an entry a draw of this frame uses, so an upload or a fill never changes what
 * an earlier command of the same scene samples: they do not end the scene.  A transfer that reads or
 * writes a render target does: the next draw starts a new pass (`splits` when it is the same target),
 * the target's last pass is stored (sampled by a read, redrawn by a write) and its next pass loads.
 * A pass's commands are its range (cmd0, ncmd: the transfers between its draws included, ndraw draws).
 *
 * 2026-10-31 (vita-build.md "The GPU's work in the Dive"): an UPLOAD into another target than the open pass's no
 * longer ends the pass.  The Dive's fog and light particles upload their 128 x 128 textures into the slot capture's
 * pages (0x3600) before each draw, which split the 3D target's scene ~14 times a picture (each a colour and depth
 * load and store on a tiled GPU).  The draws read those texels from GS memory (texcache, cpu_pages), and the GPU
 * target's copy (gxm.c's pend) is written from the frame's end state before the target's next scene anyway, so
 * nothing between the two draws needs the scene to end.  A draw of the pass that sampled that target earlier is
 * safe too: gxm.c writes an upload into a target (pend_flush) only between scenes, after the last scene that used
 * the target is done, so the whole scene sees the target as before the upload.  The pass still ends when a later
 * draw of it samples a target written that way (pwrote: it needs the new texels), as before for a copy, a CLUT
 * read-back, or an upload into the pass's own target (its later draws go over the texels).
 * Not part of the PS2 build. */
#ifndef KH1_PS2
#define KH1_CMD_MAX 4096     /* commands a frame (session 141: 1,024 dropped a third of a Destiny Islands frame) */
#define KH1_CMD_PASSES 256   /* passes a frame */
#define KH1_CMD_TARGETS 32   /* distinct colour targets (rt, fbp) tracked across frames */

enum { KH1_LOAD_DONT_CARE, KH1_LOAD_LOAD };
/* a command's kind (KH1Cmd.kind) */
enum { KH1_CMD_DRAW, KH1_CMD_UPLOAD, KH1_CMD_COPY, KH1_CMD_CLUT, KH1_CMD_TEXTURE };
enum { KH1_STORE_DISCARD, KH1_STORE_STORE, KH1_STORE_OPEN };
/* why a pass stores (KH1CmdPass.why bits) */
enum { KH1_WHY_SAMPLED = 1, KH1_WHY_REDRAWN = 2, KH1_WHY_NEXT = 4, KH1_WHY_DISPLAY = 8 };

/* session 127: a transfer command's fields */
typedef struct {
    u32 bb_lo, bb_hi;  /* UPLOAD / COPY: BITBLTBUF (the source in lo, the destination in hi) */
    u16 sx, sy, dx, dy, w, h; /* TRXPOS's source / destination corners, TRXREG */
    u32 tex0_lo, tex0_hi; /* CLUT: the TEX0 that loaded; TEXTURE: the binding */
    s16 slot;          /* CLUT: the palette cache's slot; TEXTURE: the texture cache's entry; -1 uncached */
    u8 fill;           /* CLUT: the slot filled now (a palette upload); TEXTURE: always 1 (a texture upload) */
    u8 src, dst;       /* 1 + the KH1CmdRec.tgt index the transfer reads (COPY, CLUT) / writes (UPLOAD, COPY) */
    u32 texels;        /* TEXTURE: texels uploaded */
} KH1CmdXfer;

typedef struct {
    KH1BatchKey k;
    KH1DrawState d;
    u32 pass;          /* its pass */
    u32 v0, nv;        /* first vertex in the frame's vertex slot, count */
    u32 prims;
    u32 uoff;          /* its uniform slot (bytes into the frame's uniform slot) */
    u8 lost;           /* a vertex or uniform allocation did not fit */
    u8 samples;        /* 1 + the KH1CmdRec.tgt index it samples, 0 none */
    u8 wtex;           /* wide screen: the target it samples has the view's margin, so it is sampled its whole width
                        * (its s taken over that width, KH1CmdRec.tsw) */
    u8 hasv;           /* its vertices were given (not a count-only primitive) */
    u8 kind;           /* session 127: KH1_CMD_* (the fields above are a draw's) */
    s16 tslot, pslot;  /* a draw's texture cache entry and palette slot (-1 none) */
    KH1CmdXfer x;      /* a transfer's */
    u8 nmat;           /* the native renderer (natdraw.h): the draw's matrices (0 an ordinary draw), at moff in the
                        * frame's uniform slot (4 rows of 4 floats each, the native vertex shader's u_m) */
    u8 cull;           /* and its cull mode (natdraw.h's KH1_NAT_CULL_*) */
    u8 skin;           /* 2026-11-01: its vertices are KH1GpuVertSk (KH1_VTX_SKIN_STRIDE), from v0 x 32 bytes */
    u32 moff;
} KH1Cmd;

typedef struct {
    u8 rt, psm, depth;
    u16 fbp, fbw;
    u32 w, h;
    u32 cmd0, ncmd;    /* its commands' range (session 127: the transfers between its draws included) */
    u32 ndraw;         /* its draw commands */
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
    /* session 127: the transfers */
    u32 uploads, copies, cluts, textures;  /* commands of each kind */
    u32 pal_fills, texels;                 /* CLUT loads that filled a palette slot; texels the decodes upload */
    u32 tgt_reads, tgt_writes;             /* transfers reading / writing a render target (GPU work) */
    u32 splits;                            /* scenes split by a transfer touching their own target */
    u32 xfer_joins;                        /* uploads into another target that no longer end the scene (below) */
    u32 hoists;                            /* 2026-10-31: passes moved ahead of a scene they interrupted (cmdbuf.c hoist) */
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
    u32 in_skin;       /* 2026-11-01: in_v is KH1GpuVertSk's (kh1_cmd_native_skin) */
    KH1CmdGrpPrim grp[KH1_BATCH_GROUP];
    /* colour targets across frames: (rt, fbp, fbw, psm); drawn: in an earlier frame */
    u32 ntgt;
    u32 tgt[KH1_CMD_TARGETS];
    u8 tdrawn[KH1_CMD_TARGETS];
    u8 ddrawn[3];               /* depth buffers written in an earlier frame (KH1_DS_*) */
    u32 tpages[KH1_CMD_TARGETS]; /* session 127: the pages each target spans (FBW x its rows' page rows) */
    u32 cpu_pages[16];           /* session 137v: GS pages (8 KiB, 512) an upload wrote after the last draw to their target */
    s32 cur;                    /* session 127: the open draw command, -1 none */
    s16 tslot, pslot;           /* the texture entry / palette slot the next draw binds */
    u8 split;                   /* a transfer touched a target: the next draw starts a pass */
    u32 pwrote;                 /* the targets (bit = index) an upload wrote since the open pass began (a later draw
                                 * of it sampling one starts a pass) */
    /* the previous frame's last pass on each target / depth buffer, its store still open */
    KH1CmdPass prev[KH1_CMD_PASSES];
    u32 nprev;
    KH1CmdCount frame, total;
    f32 tsw[KH1_CMD_TARGETS];   /* wide screen: each target's last pass's width (unscaled) when it had the view's margin
                                 * (target.h's ox), else 0 */
} KH1CmdRec;

/* a recorder over two rings' memory (KH1_RING_FRAMES x vslot / uslot bytes, 32-byte aligned) */
/* 2026-10-31: 1 (the default): passes that split a scene on one target are drawn ahead of it when they do not touch
 * it, and its two parts joined (cmdbuf.c hoist); config.txt hoist=0 / KH1_HOST_HOIST=0 keeps the game's order */
extern int kh1_cmd_hoist;
void kh1_cmd_init(KH1CmdRec *r, void *vmem, u32 vslot, void *umem, u32 uslot);
/* a primitive drawn in d / p: its n GPU vertices (v 0: counted, not written), sig as batch.h's */
void kh1_cmd_prim(KH1CmdRec *r, const KH1DrawState *d, const KH1RenderPass *p, const KH1GpuVert *v, u32 n, u32 sig);
/* the native renderer (natdraw.h): a run's n GPU vertices (triangles; position, the matrix index in pad[0]) and its
 * nmat matrices (4 x 4 floats each, already folded with the screen mapping) as one draw command of its own (nothing
 * batched with it), culled by `cull` (KH1_NAT_CULL_*, with natdraw.h's KH1_NAT_LIN for P0's: the shader's lin) */
void kh1_cmd_native(KH1CmdRec *r, const KH1DrawState *d, const KH1RenderPass *p, const KH1GpuVert *v, u32 n, const f32 *mats,
                    u32 nmat, u32 cull);
/* 2026-11-01: the same with the skinned vertex (vertex.h KH1GpuVertSk, natdraw.h KH1_NAT_SKIN): the command's skin set,
 * so gxmrec.h picks the KH1_VERT_SKIN variants */
void kh1_cmd_native_skin(KH1CmdRec *r, const KH1DrawState *d, const KH1RenderPass *p, const KH1GpuVertSk *v, u32 n,
                         const f32 *mats, u32 nmat, u32 cull);
/* a transfer or CLUT load, not recorded (batch.h's break only) */
void kh1_cmd_break(KH1CmdRec *r);
/* session 127: TRXDIR dir (0 an upload, 2 a copy) with BITBLTBUF, TRXPOS and TRXREG: an UPLOAD or COPY command
 * (and the break) */
void kh1_cmd_upload(KH1CmdRec *r, u32 dir, u32 bb_lo, u32 bb_hi, u32 pos_lo, u32 pos_hi, u32 reg_lo, u32 reg_hi);
/* a CLUT load by TEX0 (lo, hi) into the palette cache's slot (-1 uncached), filled now or not: a CLUT command
 * (and the break); the next indexed draws bind the slot */
void kh1_cmd_clut(KH1CmdRec *r, u32 tex0_lo, u32 tex0_hi, s32 slot, int fill);
/* session 136: a draw's palette without a load (CLD 0 with another CSA, or a new frame's first indexed draw): the
 * CLUT buffer's entries for TEX0 (lo, hi) in the slot; a CLUT command as kh1_cmd_clut's, never read back */
void kh1_cmd_palette(KH1CmdRec *r, u32 tex0_lo, u32 tex0_hi, s32 slot, int fill);
/* the texture cache's answer for the next draw's TEX0: its entry (-1 not kept: a render target's texture, or
 * full), decoded now (a TEXTURE command of `texels` texels, before the draw) or not */
void kh1_cmd_texture(KH1CmdRec *r, u32 tex0_lo, u32 tex0_hi, s32 slot, int decoded, u32 texels);
/* a command as text: "draw ...", "upload 2000 bw 1 psm 00 16 x 16 at (0, 0)", "clut 3e00 slot 2 fill (from CLUT
 * pass)", ... */
const char *kh1_cmd_str(const KH1CmdRec *r, const KH1Cmd *c);
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

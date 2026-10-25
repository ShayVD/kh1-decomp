/* The null platform's GS register file (docs/renderer-spec.md 5.1, host/null/gsregs.c). */
#ifndef KH1_HOST_GSREGS_H
#define KH1_HOST_GSREGS_H

typedef struct {
    u32 lo, hi;
} KH1GsReg;

/* one context's registers (FRAME_n, ZBUF_n, TEST_n, ALPHA_n, TEX0_n, TEX1_n, CLAMP_n, XYOFFSET_n,
 * SCISSOR_n) */
typedef struct {
    KH1GsReg frame, zbuf, test, alpha, tex0, tex1, clamp, xyoffset, scissor;
} KH1GsContext;

/* what renderer-spec 5.1 keeps; the dropped registers are counted, not kept */
typedef struct {
    KH1GsReg prim;               /* the last PRIM written (11 bits) */
    KH1GsReg prmodecont, prmode; /* kept so a PRMODECONT 0 can be noticed (never seen) */
    KH1GsContext ctx[2];
    KH1GsReg fogcol, texa;
    KH1GsReg bitbltbuf, trxpos, trxreg, trxdir;
    /* the vertex being built */
    KH1GsReg rgbaq, st, uv, fog;
    u32 nvert;                   /* vertices queued since the last PRIM or drawing kick */
    u32 dropped;                 /* writes to a register 5.1 drops (DTHE, COLCLAMP, TEXFLUSH, ...) */
    u32 unknown;                 /* writes to an address that is no GS register */
    u32 lost;                    /* vertex kicks in draw states past the 256 kh1_gs_draws keeps */
    u32 path1;                   /* VU1 program starts on VIF1 (kh1_gs_path1) */
} KH1GsState;

/* a distinct draw state and how often it was drawn: the PRIM attributes in force (type, IIP,
 * TME, FGE, ABE, AA1, FST, CTXT, FIX) and the chosen context's registers, FOGCOL and TEXA, with
 * what the draw does not read left 0 (TEX0 / TEX1 / CLAMP / TEXA without TME, ALPHA without ABE,
 * FOGCOL without FGE) */
typedef struct {
    u32 prim;
    KH1GsContext ctx;
    KH1GsReg fogcol, texa;
    u32 kicks; /* vertex kicks (XYZ2 / XYZF2 / XYZ3 / XYZF3) in this state */
    u32 draws; /* drawing kicks: primitives drawn */
    u32 target; /* with TME: 1 + the render target the texture lies in when a kick in this state
                 * first found it there (kh1_gsmem_tex_target, session 81), else 0 */
    s32 x0, y0, x1, y1; /* session 91: the kicked vertices' extent in 1/16 pixels of the context's
                         * XYOFFSET (min, max; x1 < x0 when nothing was kicked) */
} KH1GsDraw;

/* back to the state before any write (all registers 0 but PRMODECONT 1) and no draws counted */
void kh1_gs_reset(void);
/* reg (a GS register address) written with a 64-bit value, as A+D or REGLIST write it */
void kh1_gs_write(u32 reg, u32 lo, u32 hi);
/* one PACKED qword for register descriptor desc (0-0xF; 0xE is A+D) */
void kh1_gs_packed(u32 desc, const u32 *q);
/* a GIF tag starts: the PACKED Q goes back to 1.0, and with PRE, PRIM is written from the tag */
void kh1_gs_giftag(int pre, u32 prim);
const KH1GsState *kh1_gs_state(void);
/* the distinct draw states since the last kh1_gs_reset / kh1_gs_clear_draws, in the order first
 * drawn (at most 256 kept; the kicks of a state past them go to KH1GsState.lost).  Fills up to
 * max and returns the count. */
int kh1_gs_draws(KH1GsDraw *out, int max);
void kh1_gs_clear_draws(void);
/* a VU1 program started on VIF1 (MSCAL / MSCALF / MSCNT): its XGKICK output (PATH1) is not
 * modelled, but renderer A's meshes draw through context 2 (renderer-spec 4.11), so its FRAME_2 /
 * ZBUF_2 are told to host/null/gsmem.c as drawn (an inference: the program's own GIF tags choose the
 * context; session 81) */
void kh1_gs_path1(void);
/* the vertices a primitive type (PRIM bits 0-2) needs for its first drawing kick, 0 for 7 */
u32 kh1_gs_prim_verts(u32 type);

#endif

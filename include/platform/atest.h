#ifndef PLATFORM_ATEST_H
#define PLATFORM_ATEST_H

/* The alpha test and the destination alpha test a port's GPU runs for the GS's TEST (docs/renderer-spec.md
 * 4.13 "Session 121", vita-port-plan 5.1bi): port code, not game code.
 *
 * Alpha test (ATE, ATST, AREF, AFAIL): the GS compares the fragment's alpha (after the texture function,
 * before blending, an 8-bit value on the 0x80 scale) with AREF.  A fragment that passes writes as usual;
 * one that fails writes by AFAIL: KEEP nothing, FB_ONLY the frame (colour and alpha, blended), ZB_ONLY
 * the Z buffer only, RGB_ONLY the colour without the alpha (no Z).  A GPU's write masks are per draw, so
 * the port draws up to twice: the pass draw discards where the test fails and writes everything, the fail
 * draw discards where it passes and writes AFAIL's set.  A draw that would write nothing is left out,
 * and the two are one draw with no discard when they write the same (FB_ONLY with no Z write).  The
 * shader compares the 8-bit alpha it takes back from the texture function (texfunc.h's exact form,
 * floor(x x 255 + 0.5)), so the test is exact.
 *
 * Destination alpha test (DATE, DATM): the GS draws only where the frame's alpha bit 7 is DATM.  With
 * blend.h's 0x80-scale target alpha, bit 7 is "the stored alpha is 1.0" (8-bit 255; 0x7F stores 253),
 * exact.  A GPU cannot test the destination's alpha, so the port marks a stencil bit first: a set-up
 * draw over the primitive's rectangle samples the target, discards where (A == 1.0) != DATM, writes
 * stencil 1 and no colour; the draws then test stencil == 1.  The GS tests each pixel when it writes it:
 * a batch whose primitives overlap and change the alpha they test needs the set-up per primitive (the
 * game's one DATE draw, brightfade's D_002A6AA0, is one sprite).  Only a CT32 frame has the bit.
 *
 * What the game sets (4.13 "Session 121"): ATST GREATER AREF 0 (the cutouts, 49 + 7 + 6 static senders
 * and TEST_2), GREATER 16 / 127 (field.c, roommdl), GEQUAL 120 (texspot), NOTEQUAL 0 (brightfade),
 * ALWAYS, NEVER with FB_ONLY (masks: sceneeff func_00103058, field.c func_001008e8) and NEVER with
 * ZB_ONLY (opdma func_001aaf00's Z-only writes), renderer B's GEQUAL / LESS min(k, 120) pair; DATE with
 * DATM 1 once (brightfade func_00106460).  No RGB_ONLY.  Each is one draw: KEEP discards where the
 * test fails, NEVER draws AFAIL's set with no discard, ALWAYS neither; none needs the two draws (a
 * failing fragment that writes something while a passing one writes more: FB_ONLY, ZB_ONLY or RGB_ONLY
 * with a test that can pass).  Not part of the PS2 build. */
#ifndef KH1_PS2
enum { KH1_ATST_NEVER, KH1_ATST_ALWAYS, KH1_ATST_LESS, KH1_ATST_LEQUAL, KH1_ATST_EQUAL, KH1_ATST_GEQUAL,
       KH1_ATST_GREATER, KH1_ATST_NOTEQUAL };
enum { KH1_AFAIL_KEEP, KH1_AFAIL_FB_ONLY, KH1_AFAIL_ZB_ONLY, KH1_AFAIL_RGB_ONLY };
enum { KH1_DISCARD_NONE, KH1_DISCARD_FAIL /* where the test fails */, KH1_DISCARD_PASS /* where it passes */ };

typedef struct {
    u8 discard;  /* KH1_DISCARD_* */
    u8 mask;     /* the colour write mask: bit 0 R, 1 G, 2 B, 3 A */
    u8 zwrite;   /* depth write */
} KH1AtestDraw;

typedef struct {
    u8 n;                 /* draws: 0 (nothing is written), 1 or 2 */
    KH1AtestDraw draw[2];
    u8 atst, aref;        /* the shader's compare (when a draw discards) */
    u8 date, datm;        /* the stencil set-up: the draws test stencil == 1 */
    u8 ztest;             /* the depth function: 0 ALWAYS (also ZTE 0), 1 GEQUAL, 2 GREATER; NEVER is n 0 */
} KH1AtestState;

/* the GS's compare: 1 when alpha a passes ATST against AREF */
int kh1_atest(u32 atst, u32 a, u32 aref);
/* the draws for TEST (test_lo), the frame's write mask (blend.h's mask) and ZBUF's ZMSK */
void kh1_atest_state(u32 test_lo, u32 mask, u32 zmsk, KH1AtestState *out);
/* the set-up's stencil for a pixel whose target holds the 8-bit alpha a8 (0x80 scale) */
int kh1_atest_date_mark(const KH1AtestState *st, u32 a8);
/* what the GPU writes for one fragment of alpha a (the GS's 8-bit value) over a pixel marked (or not)
 * by the set-up: the colour write mask in bits 0-3, bit 4 the depth write */
u32 kh1_atest_gpu(const KH1AtestState *st, u32 a, int marked);
/* the same by the GS's rules, for frame alpha ad (bit 7 is what DATE reads) */
u32 kh1_atest_gs(u32 test_lo, u32 mask, u32 zmsk, u32 a, u32 ad);
#endif

#endif

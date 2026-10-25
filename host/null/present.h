/* The host "present" (KH1_HOST_SHOT, host/null/present.c, session 94). */
#ifndef KH1_HOST_PRESENT_H
#define KH1_HOST_PRESENT_H

/* the GS memory model's buffer (bp, bw, psm: CT32 / CT24 / CT16 / CT16S) of `lines` rows (448 for the
 * display, 384 for the target) as w x h RGB bytes through the canvas map, black outside it; 0, or -1
 * for a PSM it cannot show */
int kh1_present_rgb(u8 *rgb, s32 w, s32 h, u32 psm, u32 bp, u32 bw, u32 lines);
/* after each send of `send` (the frame copy) write DIR/shot_N.pam, w x h, of the display (the copy's
 * FRAME) or with target set of the 3D target (its TEX0); 0, or -1 for a bad size */
int kh1_present_init(s32 w, s32 h, int target, const char *dir, const void *send);

/* session 97: KH1_HOST_WIDE's margin (kh1_view_side16; 0 = 4:3): the shot line notes the black sides,
 * and the display shot is read back by the stretched copy's shift */
void kh1_present_wide(s32 side16);

#endif

/* The Vita platform's own calls between its files (host/vita/).  Not part of the PS2 build. */
#ifndef KH1_VITA_H
#define KH1_VITA_H

/* display.c */
int kh1_vita_display_init(const void *frame_copy_send);
void kh1_vita_present_on(void);
void kh1_vita_status(unsigned long frames, unsigned reads);
void kh1_vita_fill(unsigned int abgr);
/* session 136: the picture drawn by the GPU (gxm.c) instead of the GS model's buffer */
void kh1_vita_present_gpu(void);
void kh1_vita_draw(void);
int kh1_vita_frame_copied(void); /* display.c: a frame copy was sent since the last call */
void kh1_vita_gxm_latch(void);   /* gxm.c: the display target, whole, kept for the present */

/* gxm.c (session 136): the GPU renderer.  init: 0 when it can run; frame: one frame of the command recorder
 * (host/null/pipes.c's kh1_pipes_frame_hook); present: the display target into vita2d's open scene */
extern int kh1_vita_shacc_ext; /* gxm.c: try SceShaccCgExt's extensions (shark_init) first */
extern int kh1_vita_shacc_restart; /* gxm.c: config.txt's shacc_restart=1 */
extern int kh1_vita_shadertest; /* gxm.c: config.txt's shadertest=1 */
int kh1_vita_gxm_init(void);
int kh1_vita_gxm_ready(void);
int kh1_vita_gxm_present(float x, float y, float w, float h);
void kh1_vita_gxm_stats(unsigned int *frames, unsigned int *draws, unsigned int *skipped, unsigned int *scenes);

/* pad.c: the buttons as sceCtrl read them this frame (for main.c's own screens) */
unsigned int kh1_vita_buttons(void);

/* main.c: the data directory, "ux0:data/kh1" */
extern const char kh1_vita_dir[];
/* main.c: a line into kh1.log (session 136: gxm.c's) */
void kh1_vita_log(const char *fmt, ...);

#endif

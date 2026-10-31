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
void kh1_vita_display_mode(int mode, int strip_always); /* config.txt wide= / strip= (display.c) */
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
/* pad.c: config.txt's rcam= (1 the right stick a free camera, -1 with x the other way, 2 its x as L2 / R2, 0 the
 * stick as it is) and rcaminv= (the free camera's up / down the other way) */
extern int kh1_vita_rcam, kh1_vita_rcam_inv;

/* menu.c: the mod menu (a tap in the middle of the front touch screen; docs/vita-build.md "The mod menu") */
void kh1_vita_menu_init(int *wide, int *late_wait, int *native, int *strip, int gpu_on);
int kh1_vita_menu_config(const char *key, const char *value); /* config.txt's fps= swapox= reartouch= volume= */
int kh1_vita_menu_poll(void);                     /* each vblank: 1 when the menu was asked for */
void kh1_vita_menu_run(void (*redraw)(void));     /* the menu, the game paused, until it is closed */
void kh1_vita_menu_draw(void);                    /* display.c's draw: the FPS counter and the menu */
int kh1_vita_menu_overlay(void);                  /* something is drawn over the picture */
int kh1_vita_menu_swallow(unsigned int held);     /* pad.c: the game sees no buttons while 1 */
extern int kh1_vita_swap_ox, kh1_vita_rear_touch;  /* config.txt's swapox= / reartouch= (pad.c) */
extern int kh1_vita_volume;                       /* config.txt's volume= (audio.c) */
extern volatile u32 kh1_vita_pictures;            /* whole pictures made (the FPS counter's) */

/* main.c: the data directory, "ux0:data/kh1" */
extern const char kh1_vita_dir[];
/* main.c: a line into kh1.log (session 136: gxm.c's) */
void kh1_vita_log(const char *fmt, ...);

#endif

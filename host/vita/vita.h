/* The Vita platform's own calls between its files (host/vita/).  Not part of the PS2 build. */
#ifndef KH1_VITA_H
#define KH1_VITA_H

/* display.c */
int kh1_vita_display_init(const void *frame_copy_send);
void kh1_vita_present_on(void);
void kh1_vita_status(unsigned long frames, unsigned reads);
void kh1_vita_fill(unsigned int abgr);

/* pad.c: the buttons as sceCtrl read them this frame (for main.c's own screens) */
unsigned int kh1_vita_buttons(void);

/* main.c: the data directory, "ux0:data/kh1" */
extern const char kh1_vita_dir[];

#endif

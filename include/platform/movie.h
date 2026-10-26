/* Platform wrapper: the movie player. See docs/portability.md and docs/native-overlays.md.
 *
 * dkmovie.x (the movie overlay) is two parts: a front end (its entry func_00f20000, the open
 * func_00f20258, the per-frame callback func_00f20140, the display set-up func_00f20320 and
 * clean-up func_00f200f8) that the game drives through entry(cmd, arg), and a player (the other
 * ~116 functions: the KINGDOM.IMG stream reader, the IPU MPEG-2 decoder tasks, the MMI colour
 * conversion, the SPU audio over SIF DMA) that the front end reaches only through the function
 * table D_00F28478.  On the PS2 the table holds the overlay's own player (no code here).  A port
 * links the front end's C and points the table at these functions instead
 * (ovl/dkmovie/platform.tsv, tools/host/ovlnative.py).
 *
 * The table, as the front end and the game read it (offsets in D_00F28478):
 *   +0x00 open(n)   +0x04 start   +0x08 close   +0x0C status   +0x10 frame (once a frame)
 *   +0x14 s32 current frame   +0x18 s16 picture width (512 / 640)   +0x1C s32 per movie
 *   (the front end's: 0x28 / 0x58 / 0x30 / 0x10 by n)   +0x20 pause(on)   +0x24 stopped
 *   +0x28 s32 frame count
 * status: 0 nothing open, 2 ready to start, 3 playing, 1 at the last frame, 4 ended,
 * 5 abort (the front end then runs func_001111b0's clean-up); stopped: 1 once a skip has
 * stopped the stream. */
#ifndef KH1_PLATFORM_MOVIE_H
#define KH1_PLATFORM_MOVIE_H

#include "common.h"

#ifndef KH1_PS2
s32 PlatMovieOpen(s32 n); /* n indexes movies.c's names (func_0024b9a8): 0 opn.dat ... 5 ffx2.dat */
s32 PlatMovieStart(void);
s32 PlatMovieClose(void);
s32 PlatMovieStatus(void);
s32 PlatMovieFrame(void);
void PlatMoviePause(s32 on);
s32 PlatMovieStopped(void);
#endif

#endif /* KH1_PLATFORM_MOVIE_H */

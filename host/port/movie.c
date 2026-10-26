/* The movie player for every port (include/platform/movie.h): dkmovie.x's front end calls
 * these through its table D_00F28478 (ovl/dkmovie/platform.tsv).  No decoder yet
 * (vita-port-plan 5.1ad: sceAvPlayer on a re-encoded copy, or MPEG-2 in software): each movie
 * opens, is ready at once and ends on the first frame after its start, as a movie of no frames
 * would, with the PS2 player's ending: its decoder task (func_00f23ae8) sets the ended flag
 * (status 4) and from its next step the done flag (status 5), on which the front end runs the
 * clean-up func_001111b0 and drops its per-frame callback.  The game then goes on as after a
 * play to the end (the title's states 13 / 18, the event script's wait 490).  Not part of the
 * PS2 build. */
#include <stdio.h>
#include "common.h"
#include "platform/movie.h"

char *func_0024b9a8(s32 n); /* movies.c: the movie's file name */

static s32 status; /* the table's +0x0C answer: 2 ready, 3 playing, 4 ended, 5 done */

s32 PlatMovieOpen(s32 n) {
    printf("kh1-movie: open %d (%s): no movie decoder in this port, reported as ended\n", (int)n,
           n >= 0 && n < 6 ? func_0024b9a8(n) : "?");
    status = 2;
    return 0;
}

s32 PlatMovieStart(void) {
    if (status == 2) status = 3;
    return 0;
}

s32 PlatMovieClose(void) {
    status = 0;
    return 0;
}

s32 PlatMovieStatus(void) { return status; }

/* once a frame, from the front end's callback (the PS2 player's decoder step) */
s32 PlatMovieFrame(void) {
    if (status == 4)
        status = 5;
    else if (status == 3)
        status = 4;
    return 0;
}

void PlatMoviePause(s32 on) { (void)on; }

s32 PlatMovieStopped(void) { return 1; }

/* VIF1 and VU1 off the PS2 (docs/vita-build.md "The 3D path"): the PATH1 half of the GS feed.
 *
 * The game's 3D (renderer A's maps and props, renderer B's characters, the lens grid; renderer-spec
 * section 2) reaches the GS only through VU1: channel 1 chains carry VIF codes (UNPACK, STCYCL, STROW,
 * STMASK, MPG, BASE / OFFSET, MSCAL ...) that fill VU1's data memory and start its microprograms, which
 * transform, light, cull and clip the vertices and XGKICK GIF packets to the GS.  The port runs that
 * same machine: host/port/vu1.c keeps VIF1's registers and VU1's state across sends, as the hardware
 * does, and interprets the microprograms the chains upload (so the programs are always the user's own
 * bytes, never this repository's).  Each XGKICK hands its GIF packets to kh1_vu1_kick, which the null
 * platform's walk (host/null/dmawalk.c) points at the same GIF reader PATH2 and PATH3 use, so the GPU
 * recorder (host/null/pipes.c) sees the meshes like any other draw.
 *
 * The walk calls kh1_vif1_code for each VIF code of a channel 1 stream and kh1_vif1_data for each of
 * its data words (without the alignment padding).  Not part of the PS2 build. */
#ifndef KH1_PLATFORM_VU1_H
#define KH1_PLATFORM_VU1_H

#include "common.h"

/* VIF1 and VU1 back to their reset state (VU1 memory zeroed, no program) */
void kh1_vif1_reset(void);
void kh1_vif1_code(u32 w);
void kh1_vif1_data(u32 w);

/* XGKICK: nqw qwords of whole GIF packets (the last one with EOP) copied out of VU1 memory */
extern void (*kh1_vu1_kick)(const u32 *q, u32 nqw);
/* 1: a line per program run */
extern int kh1_vu1_verbose;
/* with kh1_vu1_verbose: the program run (from 1) whose start state is written to vu1_snap.bin */
extern u32 kh1_vu1_snap_run;

typedef struct {
    u32 runs;        /* programs started (MSCAL / MSCALF / MSCNT) */
    u32 insns;       /* instruction pairs executed */
    u32 cycles;      /* the model's cycles (pairs plus stalls) */
    u32 kicks;       /* XGKICKs */
    u32 kick_qw;     /* their qwords */
    u32 unpacks;     /* UNPACKs */
    u32 mpg;         /* MPG uploads that changed micro memory */
    u32 runaway;     /* programs stopped by the instruction limit (no [E] reached) */
    u32 unknown;     /* instructions the interpreter does not know (run as nops) */
    u32 fill;        /* UNPACK vectors written by a filling write (WL > CL) */
    u32 tr_runs;     /* runs of a translated program (out/gen/vu1_tr.c) */
    u32 tr_checked;  /* with kh1_vu1_tr 2: runs both ways */
    u32 tr_differ;   /* and of those, the ones whose results differ */
} KH1Vu1Stats;

/* 1 (the default): a program out/gen/vu1_tr.c has runs as its C; 0: the interpreter only; 2: both, compared */
extern int kh1_vu1_tr;

/* the counts since the last call (zeroed by it) */
void kh1_vu1_stats(KH1Vu1Stats *out);

/* the first unknown instruction seen (upper, lower words), 0 / 0 when none */
void kh1_vu1_first_unknown(u32 *hi, u32 *lo, u32 *pc);

#endif

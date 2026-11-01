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
void kh1_vif1_data_n(const u32 *w, u32 n); /* n data words at once */

/* XGKICK: nqw qwords of whole GIF packets (the last one with EOP) copied out of VU1 memory */
extern void (*kh1_vu1_kick)(const u32 *q, u32 nqw);
/* the native renderer (include/platform/natdraw.h, docs/native-renderer.md): when set, a run of a program the port
 * draws itself (P18) is not run but handed here as natdraw.h's payload (nqw qwords, valid during the call);
 * kh1_vu1_drawn counts them */
extern void (*kh1_vu1_draw)(const u32 *q, u32 nqw);
extern u32 kh1_vu1_drawn;
/* 2026-10-31: P0 and P4 (the map's strips) drawn that way too (1, the default; config.txt natp0=0 / KH1_HOST_NATP0=0 keeps
 * them on the VU1 programs with the rest native) */
extern int kh1_vu1_draw_p0;
/* 2026-10-31: P11 (renderer B's unlit models with the near-plane cull) too (1, the default; natp11=0 / KH1_HOST_NATP11=0) */
extern int kh1_vu1_draw_p11;
/* 2026-10-31: P10 (the shadow pass's untextured strips) too (1, the default; natp10=0 / KH1_HOST_NATP10=0) */
extern int kh1_vu1_draw_p10;
/* 2026-10-31: P13 (renderer B's skinned models) too (1, the default; natp13=0 / KH1_HOST_NATP13=0); the vertices it
 * hands over and those of them with more than one bone (summed on the CPU) */
extern int kh1_vu1_draw_p13;
extern u32 kh1_vu1_nd13_verts, kh1_vu1_nd13_multi;
/* 2026-11-01: P13's two-bone vertices summed by the GPU's vertex shader (natskin=1 / KH1_HOST_NATSKIN=1; 0, the default,
 * sums them on the CPU as before; natdraw.h KH1_NAT_SKIN), and how many were handed over so */
extern int kh1_vu1_nat_skin;
extern u32 kh1_vu1_nd13_gpu2;
/* microseconds (kh1_vu1_clock's) the game thread spent handing native payloads to the GS worker's queue (the copy and
 * a full ring's wait), all programs' and P13's (vu1_draw.h nd_hand) */
extern u32 kh1_vu1_nd_hand_us, kh1_vu1_nd13_hand_us;
/* P13's runs the native renderer handed back to the program (its time: the parse that gave up, then the program) */
extern u32 kh1_vu1_nd13_fail, kh1_vu1_nd13_fail_us;
extern int kh1_vu1_natcheck; /* host: KH1_HOST_NATCHECK=1, P0 run and checked against its payload (vu1_draw.h) */
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

/* a microsecond clock (the Vita's): then kh1_vu1_us counts the time in programs (MSCAL to the end), and
 * kh1_vu1_kick_us the part of it spent in kh1_vu1_kick (the GIF path past the VU) */
extern u32 (*kh1_vu1_clock)(void);
extern u32 kh1_vu1_us, kh1_vu1_kick_us;
/* session 147: with that clock, each translated program's time, runs and pairs (instruction pairs) so far:
 * nonzero for i a translated program (0..KH1_VU1_PROGS-1), *num its number in tools/vu/find_vu1.py's list */
#define KH1_VU1_PROGS 32
int kh1_vu1_prog_stats(int i, int *num, u32 *us, u32 *runs, u32 *pairs);

/* 1 (the default): a program out/gen/vu1_tr.c has runs as its C; 0: the interpreter only; 2: both, compared */
extern int kh1_vu1_tr;
extern int kh1_vu1_native; /* session 150: 1 (the default) the programs written as C where there is one (vu1_nat.h); 2 each one checked against the translation */

/* every kh1_vu1_dump_every-th run's start state to kh1_vu1_dump_dir/vuNNNNN.bin (offline replays; scratch) */
extern const char *kh1_vu1_dump_dir;
extern u32 kh1_vu1_dump_every;

/* the counts since the last call (zeroed by it) */
void kh1_vu1_stats(KH1Vu1Stats *out);

/* the first unknown instruction seen (upper, lower words), 0 / 0 when none */
void kh1_vu1_first_unknown(u32 *hi, u32 *lo, u32 *pc);

#endif

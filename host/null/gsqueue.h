/* The GS side on a worker thread (session 141, host/null/gsqueue.c, docs/vita-build.md "On a real Vita:
 * speed"): the game thread hands the GS model's work (the GIF streams' decode in host/null/dmawalk.c, the
 * register file host/null/gsregs.c, GS memory host/null/gsmem.c and the GPU command recorder
 * host/null/pipes.c) to one worker thread through an ordered queue, so it runs alongside the game's own
 * code and the VIF1 / VU1 programs.  Each op is a function, up to 7 argument words and a copy of its data
 * qwords; the worker runs the ops in the order they were put.  Anything on the game thread that reads GS
 * state first calls kh1_gsq_sync.  Off (kh1_gsq_on 0) every op runs at once on the caller's thread, as
 * before.  Not part of the PS2 build. */
#ifndef KH1_HOST_GSQUEUE_H
#define KH1_HOST_GSQUEUE_H

typedef void (*KH1GsqFn)(const u32 *args, const u32 *data, u32 nqw);

/* 1 once kh1_gsq_start has made the worker */
extern int kh1_gsq_on;
/* makes the queue (bytes of ring, a power of two) and its worker; 0 when it runs */
int kh1_gsq_start(u32 bytes);
/* fn(args, data, nqw) on the worker after every op put before it; data (nqw qwords) is copied, so the
 * caller may change it at once.  An op put right after one of the same fn and args, still unpublished,
 * joins it (fn then sees both ops' data as one).  Runs fn at once when the queue is off. */
void kh1_gsq_put(KH1GsqFn fn, const u32 *args, u32 nargs, const u32 *data, u32 nqw);
/* the same with data of any length (copied, then padded with zeros to whole qwords; never joined): fn
 * reads the length from its arguments */
void kh1_gsq_put_bytes(KH1GsqFn fn, const u32 *args, u32 nargs, const void *data, u32 bytes);
/* the queue's position after the ops put so far, and a wait until the worker has run every op before a
 * position (kh1_gsq_wait(kh1_gsq_pos()) is kh1_gsq_sync): the Vita's vblank keeps one frame in flight */
u32 kh1_gsq_pos(void);
void kh1_gsq_wait(u32 pos);
/* the ops put so far handed to the worker (put publishes on its own every few KiB) */
void kh1_gsq_flush(void);
/* returns once every op put so far has run: the GS model is then the game thread's to read or change
 * until the next put */
void kh1_gsq_sync(void);

/* the watchdog's counts (host/vita/main.c): microseconds the worker spent running ops, microseconds the
 * game thread waited for it (syncs and a full ring), the syncs that had to wait; kh1_vu1_clock's */
extern volatile u32 kh1_gsq_us_busy, kh1_gsq_us_wait, kh1_gsq_waits;
/* session 147b: the worker's time by op function since the last take (up to KH1_GSQ_OPS functions, the last
 * slot also taking any beyond): fn the op's function address (out/vita/kh1.elf's symbols name it), us, n;
 * the count returned, each slot's time and count zeroed */
#define KH1_GSQ_OPS 12
int kh1_gsq_ops_take(u32 *fn, u32 *us, u32 *n);
int kh1_recq_ops_take(u32 *fn, u32 *us, u32 *n); /* 2026-11-03: the same for the GPU thread's recording ops */
/* 2026-11-03: set while the GPU thread runs a recording op that is timed (1 in 8): its parts' own clocks (pipes.c
 * kh1_pipes_nat_us) time only those, x8, so the untimed ones pay no clock reads */
extern u32 kh1_recq_timed;

/* Session 142 (docs/vita-build.md "The GPU frame on the third core"): one more thread, for the frame's GPU
 * work.  kh1_gpuq_put runs fn(args, 0, 0) on it after the jobs before (session 145: up to two posted and not
 * yet ended; a third put waits for the first), kh1_gpuq_wait returns once every job posted has ended.  Off (kh1_gpuq_on 0) fn
 * runs at once on the caller's thread.  The Vita's runs on the third core (the GS worker on the second) */
#define KH1_GPUQ_ARGS 4
extern int kh1_gpuq_on;
int kh1_gpuq_start(void);
void kh1_gpuq_put(KH1GsqFn fn, const u32 *args, u32 nargs);
void kh1_gpuq_wait(void);
/* microseconds the thread ran jobs, microseconds its callers waited for it, the waits that had to wait */
extern volatile u32 kh1_gpuq_us_busy, kh1_gpuq_us_wait, kh1_gpuq_waits;

/* Session 146 (docs/vita-build.md "The recording on the third core"): a second ordered queue of ops, the
 * gsq's kind (an op put right after one of the same fn and args joins it), whose ops run on the GPU frame's
 * thread between its jobs (a posted job first).  The GS worker puts the command recorder's work there
 * (host/null/pipes.c), so the recording runs beside the worker's GIF decode and GS memory.  kh1_recq_start
 * needs kh1_gpuq_on; off (kh1_recq_on 0) every op runs at once on the caller's thread.  kh1_recq_sync returns
 * once every op put so far has run */
extern int kh1_recq_on;
int kh1_recq_start(u32 bytes);
void kh1_recq_put(KH1GsqFn fn, const u32 *args, u32 nargs, const u32 *data, u32 nqw);
void kh1_recq_sync(void);
/* 2026-10-31 (pipes.c's frame op as a recording op): the queue's position after the ops put so far, a wait until
 * the thread has run every op before a position, and the ops put so far handed to the thread (an op put after a
 * flush never joins one before it) */
u32 kh1_recq_pos(void);
void kh1_recq_wait(u32 pos);
void kh1_recq_flush(void);
/* session 149: the three queues' positions, waits and sleeps as a line (the Vita's watchdog, at a stall) */
void kh1_gsq_state(char *b, int n);
/* microseconds the thread ran the queue's ops, microseconds the producer waited for it (room, syncs), the
 * waits that had to wait */
extern volatile u32 kh1_recq_us_busy, kh1_recq_us_wait, kh1_recq_waits;

/* 2026-11-01 (docs/native-plan.md "Native payloads by reference", config.txt natref=): a ring of qwords the game thread
 * writes data into that the GS worker hands on to the GPU thread by reference, so neither queue copies it.  One
 * writer (the game thread: kh1_pool_get), one freer (whoever ran the data's last reader: kh1_pool_free, in order).
 * kh1_pool_get returns room for nqw contiguous qwords (0 when nqw is more than a quarter of the pool) and sets *end
 * to the position after it; kh1_pool_free(end) frees everything before end.  A get that finds no room publishes the
 * GS queue and waits (counted in kh1_pool_us_wait / kh1_pool_waits).  While the pool is on (kh1_pool_on, set by
 * kh1_pool_start) the GS worker publishes the recording queue before it sleeps, so a free put there is never held
 * back while the game thread waits for it */
extern int kh1_pool_on;
/* run on the GS worker before it sleeps while the pool is on (pipes.c: a pool free held back) */
extern void (*kh1_gsq_idle_hook)(void);
int kh1_pool_start(u32 bytes);
u32 *kh1_pool_get(u32 nqw, u32 *end);
void kh1_pool_free(u32 end);
/* 2026-11-01 (natchain): kh1_pool_room waits as kh1_pool_get would for maxqw and returns where they would go without
 * taking them; kh1_pool_take(nqw) takes the first nqw of that room (nqw <= maxqw, no other get or room between) and
 * returns the position after them, kh1_pool_get's *end */
u32 *kh1_pool_room(u32 maxqw);
u32 kh1_pool_take(u32 nqw);
extern volatile u32 kh1_pool_us_wait, kh1_pool_waits;

#endif

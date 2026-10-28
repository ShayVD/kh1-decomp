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

#endif

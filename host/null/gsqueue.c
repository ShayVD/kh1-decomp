/* The GS side's ordered queue and its worker thread (session 141, host/null/gsqueue.h).
 *
 * One ring of words, one producer (the game thread) and one consumer (the worker).  An op is a 4-word
 * head (fn, data qwords, argument words, unused), its arguments padded to 4 words, then its data; an op
 * never wraps (a head with fn 0 sends the worker back to the ring's start).  The producer writes at wpos
 * and publishes head (release) every PUBLISH words or at kh1_gsq_flush / kh1_gsq_sync; the worker runs
 * the ops up to head and moves tail (release) after each.  Either side that finds nothing to do spins a
 * little, then sleeps on a semaphore the other side posts when it sees the sleeper's flag (both flags and
 * positions go through sequentially consistent atomics, so a post is never missed; a spare post only
 * costs a spurious wake, and every wait rechecks).  The Vita's worker is a kernel thread on the second
 * core; the host runner's (and qemu's ARM Linux build's) a POSIX thread.  Not part of the PS2 build. */
#include "common.h"
#include "gsqueue.h"
#include "platform/vu1.h"

void *malloc(__SIZE_TYPE__);
void *memcpy(void *, const void *, __SIZE_TYPE__);

int kh1_gsq_on;
volatile u32 kh1_gsq_us_busy, kh1_gsq_us_wait, kh1_gsq_waits;

#define PUBLISH 4096 /* words (16 KiB) put before the worker is told */
#define SPINS 4000   /* polls before a side sleeps */

static u32 *ring, mask;
static u32 wpos;            /* the producer's own end */
static u32 last_op = ~0u;   /* the head of the last op put, while it is unpublished */
static volatile u32 head, tail;
static volatile int worker_sleeps, producer_sleeps;

#define LOAD(p) __atomic_load_n(&(p), __ATOMIC_SEQ_CST)
#define STORE(p, v) __atomic_store_n(&(p), (v), __ATOMIC_SEQ_CST)

/* ---- the thread and its two semaphores (0: work for the worker, 1: room or done for the producer) ---- */
static void worker(void);
#ifdef KH1_VITA
#include <psp2/kernel/cpu.h>
#include <psp2/kernel/threadmgr.h>
static SceUID sem[2];
static void sem_wait(int i) { sceKernelWaitSema(sem[i], 1, 0); }
static void sem_post(int i) { sceKernelSignalSema(sem[i], 1); }
static int worker_entry(SceSize n, void *p) {
    (void)n;
    (void)p;
    worker();
    return 0;
}
static int thread_start(void) {
    SceUID t;
    int i;
    for (i = 0; i < 2; i++)
        if ((sem[i] = sceKernelCreateSema(i ? "kh1_gsq_done" : "kh1_gsq_work", 0, 0, 0x7FFFFFFF, 0)) < 0) return -1;
    /* the second core (the game thread stays on the first, host/vita/main.c); 2 MiB of stack: the frame's
     * commands run here too, and gxm.c compiles a new shader with SceShaccCg in them */
    t = sceKernelCreateThread("kh1_gs", worker_entry, 0x10000100, 0x200000, 0, SCE_KERNEL_CPU_MASK_USER_1, 0);
    if (t < 0) return -1;
    return sceKernelStartThread(t, 0, 0) < 0 ? -1 : 0;
}
#else
#include <pthread.h>
#include <semaphore.h>
static sem_t sem[2];
static void sem_wait_(int i) {
    while (sem_wait(&sem[i])) ; /* EINTR */
}
static void sem_post_(int i) { sem_post(&sem[i]); }
#define sem_wait sem_wait_
#define sem_post sem_post_
static void *worker_entry(void *p) {
    (void)p;
    worker();
    return 0;
}
static int thread_start(void) {
    pthread_t t;
    if (sem_init(&sem[0], 0, 0) || sem_init(&sem[1], 0, 0)) return -1;
    return pthread_create(&t, 0, worker_entry, 0) ? -1 : 0;
}
#endif

static u32 clock_us(void) { return kh1_vu1_clock ? kh1_vu1_clock() : 0; }

/* ---- the worker ---- */
static void wake_producer(void) {
    if (LOAD(producer_sleeps)) {
        STORE(producer_sleeps, 0);
        sem_post(1);
    }
}

static void worker(void) {
    u32 t = LOAD(tail);
    for (;;) {
        u32 h = LOAD(head), spin, t0;
        if (t == h) {
            for (spin = 0; spin < SPINS && (h = LOAD(head)) == t; spin++) ;
            if (h == t) {
                STORE(worker_sleeps, 1);
                if (LOAD(head) == t) sem_wait(0);
                STORE(worker_sleeps, 0);
                continue;
            }
        }
        t0 = clock_us();
        while (t != h) {
            const u32 *op = ring + (t & mask);
            if (!op[0]) { /* the rest of the ring is unused: the next op is at its start */
                t += mask + 1 - (t & mask);
            } else {
                u32 nqw = op[1], na = op[2], pa = (na + 3) & ~3u;
                ((KH1GsqFn)(unsigned long)op[0])(op + 4, op + 4 + pa, nqw);
                t += 4 + pa + nqw * 4;
            }
            STORE(tail, t);
            wake_producer();
        }
        kh1_gsq_us_busy += clock_us() - t0;
    }
}

/* ---- the producer ---- */
static void publish(void) {
    if (LOAD(head) == wpos) return;
    STORE(head, wpos);
    last_op = ~0u;
    if (LOAD(worker_sleeps)) {
        STORE(worker_sleeps, 0);
        sem_post(0);
    }
}

/* waits until the worker's tail reaches at least want (words past it free, or everything done); the ops
 * put so far are published first, so the worker can get there */
static void wait_tail(u32 want) {
    u32 spin, t0;
    if ((s32)(LOAD(tail) - want) >= 0) return;
    publish();
    t0 = clock_us();
    kh1_gsq_waits++;
    for (;;) {
        for (spin = 0; spin < SPINS && (s32)(LOAD(tail) - want) < 0; spin++) ;
        if ((s32)(LOAD(tail) - want) >= 0) break;
        STORE(producer_sleeps, 1);
        if ((s32)(LOAD(tail) - want) < 0) sem_wait(1);
        STORE(producer_sleeps, 0);
    }
    kh1_gsq_us_wait += clock_us() - t0;
}

void kh1_gsq_flush(void) {
    if (kh1_gsq_on) publish();
}

void kh1_gsq_sync(void) {
    if (kh1_gsq_on) wait_tail(wpos);
}

u32 kh1_gsq_pos(void) { return wpos; }

void kh1_gsq_wait(u32 pos) {
    if (kh1_gsq_on) wait_tail(pos);
}

/* room for n contiguous words at wpos (a wrap marker and the wait for the worker as needed) */
static void room(u32 n) {
    u32 size = mask + 1, end = size - (wpos & mask);
    if (end < n) {
        wait_tail(wpos + end - size); /* the marker's word must be free too */
        ring[wpos & mask] = 0;
        wpos += end;
        last_op = ~0u;
    }
    if (wpos + n - LOAD(tail) > size) wait_tail(wpos + n - size);
}

/* bytes of data (the op's qwords padded with zeros), joining the last op when join is set */
static void put(KH1GsqFn fn, const u32 *args, u32 nargs, const void *data, u32 bytes, int join) {
    u32 nqw = (bytes + 15) / 16, pa = (nargs + 3) & ~3u, n = 4 + pa + nqw * 4, i, *op;
    if (!kh1_gsq_on) {
        fn(args, (const u32 *)data, nqw);
        return;
    }
    /* the last op again with more data: its data grows in place when it is the ring's last words */
    if (join && last_op != ~0u && nqw) {
        op = ring + (last_op & mask);
        if (op[0] == (u32)(unsigned long)fn && op[2] == nargs && (last_op & mask) + 4 + pa + (op[1] + nqw) * 4 <= mask + 1 &&
            wpos + nqw * 4 - LOAD(tail) <= mask + 1) {
            for (i = 0; i < nargs && op[4 + i] == args[i]; i++) ;
            if (i == nargs) {
                memcpy(ring + (wpos & mask), data, nqw * 16);
                op[1] += nqw;
                wpos += nqw * 4;
                if (wpos - LOAD(head) >= PUBLISH) publish();
                return;
            }
        }
    }
    if (n > (mask + 1) / 2) { /* larger than the ring can take: run it here, the worker idle */
        kh1_gsq_sync();
        fn(args, (const u32 *)data, nqw);
        return;
    }
    room(n);
    op = ring + (wpos & mask);
    op[0] = (u32)(unsigned long)fn;
    op[1] = nqw;
    op[2] = nargs;
    op[3] = 0;
    for (i = 0; i < nargs; i++) op[4 + i] = args[i];
    if (nqw) {
        op[4 + pa + nqw * 4 - 1] = op[4 + pa + nqw * 4 - 2] = op[4 + pa + nqw * 4 - 3] = op[4 + pa + nqw * 4 - 4] = 0;
        memcpy(op + 4 + pa, data, bytes);
    }
    last_op = join ? wpos : ~0u;
    wpos += n;
    if (wpos - LOAD(head) >= PUBLISH) publish();
}

void kh1_gsq_put(KH1GsqFn fn, const u32 *args, u32 nargs, const u32 *data, u32 nqw) {
    put(fn, args, nargs, data, nqw * 16, 1);
}

void kh1_gsq_put_bytes(KH1GsqFn fn, const u32 *args, u32 nargs, const void *data, u32 bytes) {
    put(fn, args, nargs, data, bytes, 0);
}

int kh1_gsq_start(u32 bytes) {
    if (kh1_gsq_on) return 0;
    if (sizeof(void *) != 4 || bytes & (bytes - 1)) return -1; /* fn is kept in a word */
    ring = (u32 *)malloc(bytes);
    if (!ring) return -1;
    mask = bytes / 4 - 1;
    if (thread_start()) return -1;
    kh1_gsq_on = 1;
    return 0;
}

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
 * core; the host runner's (and qemu's ARM Linux build's) a POSIX thread.  Session 146: the recording queue
 * (kh1_recq) is a second ring of the same kind, the GS worker its producer and the GPU frame's thread its consumer.
 * Not part of the PS2 build. */
#include "common.h"
#include "gsqueue.h"
#include "platform/vu1.h"

void *malloc(__SIZE_TYPE__);
void *memcpy(void *, const void *, __SIZE_TYPE__);

int kh1_gsq_on;
volatile u32 kh1_gsq_us_busy, kh1_gsq_us_wait, kh1_gsq_waits;

#define PUBLISH 4096 /* words (16 KiB) put before the worker is told */
#define SPINS 4000   /* polls before a side sleeps */

/* session 146: the ring and its two sides as a struct, so the recording queue (gsqueue.h's kh1_recq) is a second
 * one: its consumer is the GPU frame's thread, which sleeps on its own semaphore for either work */
typedef struct {
    u32 *ring, mask;
    u32 wpos;                  /* the producer's own end */
    u32 last_op;               /* the head of the last op put, while it is unpublished */
    volatile u32 head, tail;
    volatile int *csleeps;     /* the consumer's sleep flag */
    volatile int psleeps;      /* the producer's */
    void (*cwake)(void);       /* posts the consumer's semaphore */
    void (*pwait)(void), (*pwake)(void);
    volatile u32 *us_wait, *waits;
} KH1Q;

static KH1Q gsq = { 0, 0, 0, ~0u };
static volatile int worker_sleeps;

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
static SceUID gq_sem[3];
static void gq_sem_wait(int i) { sceKernelWaitSema(gq_sem[i], 1, 0); }
static void gq_sem_post(int i) { sceKernelSignalSema(gq_sem[i], 1); }
static void gq_worker(void);
static int gq_entry(SceSize n, void *p) {
    (void)n;
    (void)p;
    gq_worker();
    return 0;
}
/* session 142: the GPU frame's thread on the third core (with the watchdog, which sleeps); 2 MiB of stack for
 * SceShaccCg, as the GS worker's.  Session 146: semaphore 2 is the recording queue's producer's */
static int gq_thread_start(void) {
    static const char *names[3] = { "kh1_gpu_work", "kh1_gpu_done", "kh1_rec_room" };
    SceUID t;
    int i;
    for (i = 0; i < 3; i++)
        if ((gq_sem[i] = sceKernelCreateSema(names[i], 0, 0, 0x7FFFFFFF, 0)) < 0) return -1;
    t = sceKernelCreateThread("kh1_gpu", gq_entry, 0x10000100, 0x200000, 0, SCE_KERNEL_CPU_MASK_USER_2, 0);
    if (t < 0) return -1;
    return sceKernelStartThread(t, 0, 0) < 0 ? -1 : 0;
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
static sem_t gq_sem[3];
static void gq_sem_wait(int i) {
    while (sem_wait(&gq_sem[i])) ; /* EINTR */
}
static void gq_sem_post(int i) { sem_post(&gq_sem[i]); }
static void gq_worker(void);
static void *gq_entry(void *p) {
    (void)p;
    gq_worker();
    return 0;
}
static int gq_thread_start(void) {
    pthread_t t;
    if (sem_init(&gq_sem[0], 0, 0) || sem_init(&gq_sem[1], 0, 0) || sem_init(&gq_sem[2], 0, 0)) return -1;
    return pthread_create(&t, 0, gq_entry, 0) ? -1 : 0;
}
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


/* ---- either queue's two sides ---- */
static void q_wake_producer(KH1Q *q) {
    if (LOAD(q->psleeps)) {
        STORE(q->psleeps, 0);
        q->pwake();
    }
}

/* the consumer: runs the ops from *t up to h, moving tail after each */
static void q_run(KH1Q *q, u32 *t, u32 h) {
    while (*t != h) {
        const u32 *op = q->ring + (*t & q->mask);
        if (!op[0]) { /* the rest of the ring is unused: the next op is at its start */
            *t += q->mask + 1 - (*t & q->mask);
        } else {
            u32 nqw = op[1], na = op[2], pa = (na + 3) & ~3u;
            ((KH1GsqFn)(unsigned long)op[0])(op + 4, op + 4 + pa, nqw);
            *t += 4 + pa + nqw * 4;
        }
        STORE(q->tail, *t);
        q_wake_producer(q);
    }
}

static void q_publish(KH1Q *q) {
    if (LOAD(q->head) == q->wpos) return;
    STORE(q->head, q->wpos);
    q->last_op = ~0u;
    if (LOAD(*q->csleeps)) {
        STORE(*q->csleeps, 0);
        q->cwake();
    }
}

/* waits until the consumer's tail reaches at least want (words past it free, or everything done); the ops
 * put so far are published first, so the consumer can get there */
static void q_wait_tail(KH1Q *q, u32 want) {
    u32 spin, t0;
    if ((s32)(LOAD(q->tail) - want) >= 0) return;
    q_publish(q);
    t0 = clock_us();
    (*q->waits)++;
    for (;;) {
        for (spin = 0; spin < SPINS && (s32)(LOAD(q->tail) - want) < 0; spin++) ;
        if ((s32)(LOAD(q->tail) - want) >= 0) break;
        STORE(q->psleeps, 1);
        if ((s32)(LOAD(q->tail) - want) < 0) q->pwait();
        STORE(q->psleeps, 0);
    }
    *q->us_wait += clock_us() - t0;
}

/* room for n contiguous words at wpos (a wrap marker and the wait for the consumer as needed) */
static void q_room(KH1Q *q, u32 n) {
    u32 size = q->mask + 1, end = size - (q->wpos & q->mask);
    if (end < n) {
        q_wait_tail(q, q->wpos + end - size); /* the marker's word must be free too */
        q->ring[q->wpos & q->mask] = 0;
        q->wpos += end;
        q->last_op = ~0u;
    }
    if (q->wpos + n - LOAD(q->tail) > size) q_wait_tail(q, q->wpos + n - size);
}

/* bytes of data (the op's qwords padded with zeros), joining the last op when join is set */
static void q_put(KH1Q *q, KH1GsqFn fn, const u32 *args, u32 nargs, const void *data, u32 bytes, int join) {
    u32 nqw = (bytes + 15) / 16, pa = (nargs + 3) & ~3u, n = 4 + pa + nqw * 4, i, *op;
    /* the last op again with more data: its data grows in place when it is the ring's last words */
    if (join && q->last_op != ~0u && nqw) {
        op = q->ring + (q->last_op & q->mask);
        if (op[0] == (u32)(unsigned long)fn && op[2] == nargs && (q->last_op & q->mask) + 4 + pa + (op[1] + nqw) * 4 <= q->mask + 1 &&
            q->wpos + nqw * 4 - LOAD(q->tail) <= q->mask + 1) {
            for (i = 0; i < nargs && op[4 + i] == args[i]; i++) ;
            if (i == nargs) {
                memcpy(q->ring + (q->wpos & q->mask), data, nqw * 16);
                op[1] += nqw;
                q->wpos += nqw * 4;
                if (q->wpos - LOAD(q->head) >= PUBLISH) q_publish(q);
                return;
            }
        }
    }
    if (n > (q->mask + 1) / 2) { /* larger than the ring can take: run it here, the consumer idle */
        q_wait_tail(q, q->wpos);
        fn(args, (const u32 *)data, nqw);
        return;
    }
    q_room(q, n);
    op = q->ring + (q->wpos & q->mask);
    op[0] = (u32)(unsigned long)fn;
    op[1] = nqw;
    op[2] = nargs;
    op[3] = 0;
    for (i = 0; i < nargs; i++) op[4 + i] = args[i];
    if (nqw) {
        op[4 + pa + nqw * 4 - 1] = op[4 + pa + nqw * 4 - 2] = op[4 + pa + nqw * 4 - 3] = op[4 + pa + nqw * 4 - 4] = 0;
        memcpy(op + 4 + pa, data, bytes);
    }
    q->last_op = join ? q->wpos : ~0u;
    q->wpos += n;
    if (q->wpos - LOAD(q->head) >= PUBLISH) q_publish(q);
}

static int q_init(KH1Q *q, u32 bytes) {
    if (sizeof(void *) != 4 || bytes & (bytes - 1)) return -1; /* fn is kept in a word */
    q->ring = (u32 *)malloc(bytes);
    if (!q->ring) return -1;
    q->mask = bytes / 4 - 1;
    q->last_op = ~0u;
    return 0;
}

/* ---- the GS worker ---- */
static void worker(void) {
    u32 t = LOAD(gsq.tail);
    for (;;) {
        u32 h = LOAD(gsq.head), spin, t0;
        if (t == h) {
            for (spin = 0; spin < SPINS && (h = LOAD(gsq.head)) == t; spin++) ;
            if (h == t) {
                STORE(worker_sleeps, 1);
                if (LOAD(gsq.head) == t) sem_wait(0);
                STORE(worker_sleeps, 0);
                continue;
            }
        }
        t0 = clock_us();
        q_run(&gsq, &t, h);
        kh1_gsq_us_busy += clock_us() - t0;
    }
}

static void gsq_cwake(void) { sem_post(0); }
static void gsq_pwait(void) { sem_wait(1); }
static void gsq_pwake(void) { sem_post(1); }

void kh1_gsq_flush(void) {
    if (kh1_gsq_on) q_publish(&gsq);
}

void kh1_gsq_sync(void) {
    if (kh1_gsq_on) q_wait_tail(&gsq, gsq.wpos);
}

u32 kh1_gsq_pos(void) { return gsq.wpos; }

void kh1_gsq_wait(u32 pos) {
    if (kh1_gsq_on) q_wait_tail(&gsq, pos);
}

void kh1_gsq_put(KH1GsqFn fn, const u32 *args, u32 nargs, const u32 *data, u32 nqw) {
    if (!kh1_gsq_on) fn(args, data, nqw);
    else q_put(&gsq, fn, args, nargs, data, nqw * 16, 1);
}

void kh1_gsq_put_bytes(KH1GsqFn fn, const u32 *args, u32 nargs, const void *data, u32 bytes) {
    if (!kh1_gsq_on) fn(args, (const u32 *)data, (bytes + 15) / 16);
    else q_put(&gsq, fn, args, nargs, data, bytes, 0);
}

int kh1_gsq_start(u32 bytes) {
    if (kh1_gsq_on) return 0;
    gsq.csleeps = &worker_sleeps;
    gsq.cwake = gsq_cwake;
    gsq.pwait = gsq_pwait;
    gsq.pwake = gsq_pwake;
    gsq.us_wait = &kh1_gsq_us_wait;
    gsq.waits = &kh1_gsq_waits;
    if (q_init(&gsq, bytes)) return -1;
    if (thread_start()) return -1;
    kh1_gsq_on = 1;
    return 0;
}

/* ---- session 142: the GPU frame's thread (gsqueue.h's kh1_gpuq_*); session 145: two jobs may wait; session 146:
 * it runs the recording queue's ops too, a posted job first ---- */
int kh1_gpuq_on;
volatile u32 kh1_gpuq_us_busy, kh1_gpuq_us_wait, kh1_gpuq_waits;
static KH1GsqFn gq_fn[2];
static u32 gq_args[2][KH1_GPUQ_ARGS];
static volatile u32 gq_posted, gq_done;
static volatile int gq_worker_sleeps, gq_waiter_sleeps;

int kh1_recq_on;
volatile u32 kh1_recq_us_busy, kh1_recq_us_wait, kh1_recq_waits;
static KH1Q recq = { 0, 0, 0, ~0u };

static void gq_worker(void) {
    u32 seen = 0, rt = 0;
    for (;;) {
        u32 spin, t0, h;
        for (spin = 0; spin < SPINS && LOAD(gq_posted) == seen && (!LOAD(kh1_recq_on) || LOAD(recq.head) == rt); spin++) ;
        if (LOAD(gq_posted) != seen) {
            t0 = clock_us();
            gq_fn[seen & 1](gq_args[seen & 1], 0, 0);
            kh1_gpuq_us_busy += clock_us() - t0;
            seen++;
            STORE(gq_done, seen);
            if (LOAD(gq_waiter_sleeps)) {
                STORE(gq_waiter_sleeps, 0);
                gq_sem_post(1);
            }
            continue;
        }
        if (LOAD(kh1_recq_on) && (h = LOAD(recq.head)) != rt) {
            t0 = clock_us();
            q_run(&recq, &rt, h);
            kh1_recq_us_busy += clock_us() - t0;
            continue;
        }
        STORE(gq_worker_sleeps, 1);
        if (LOAD(gq_posted) == seen && (!LOAD(kh1_recq_on) || LOAD(recq.head) == rt)) gq_sem_wait(0);
        STORE(gq_worker_sleeps, 0);
    }
}

/* returns once at most `left` jobs are posted and not yet ended */
static void gq_wait_left(u32 left) {
    u32 spin, t0;
    if (LOAD(gq_posted) - LOAD(gq_done) <= left) return;
    t0 = clock_us();
    kh1_gpuq_waits++;
    for (;;) {
        for (spin = 0; spin < SPINS && LOAD(gq_posted) - LOAD(gq_done) > left; spin++) ;
        if (LOAD(gq_posted) - LOAD(gq_done) <= left) break;
        STORE(gq_waiter_sleeps, 1);
        if (LOAD(gq_posted) - LOAD(gq_done) > left) gq_sem_wait(1);
        STORE(gq_waiter_sleeps, 0);
    }
    kh1_gpuq_us_wait += clock_us() - t0;
}

void kh1_gpuq_wait(void) {
    if (kh1_gpuq_on) gq_wait_left(0);
}

void kh1_gpuq_put(KH1GsqFn fn, const u32 *args, u32 nargs) {
    u32 i, p;
    if (!kh1_gpuq_on) {
        fn(args, 0, 0);
        return;
    }
    gq_wait_left(1); /* a slot free: the job before may still run */
    p = LOAD(gq_posted);
    gq_fn[p & 1] = fn;
    for (i = 0; i < nargs && i < KH1_GPUQ_ARGS; i++) gq_args[p & 1][i] = args[i];
    STORE(gq_posted, p + 1);
    if (LOAD(gq_worker_sleeps)) {
        STORE(gq_worker_sleeps, 0);
        gq_sem_post(0);
    }
}

int kh1_gpuq_start(void) {
    if (kh1_gpuq_on) return 0;
    if (gq_thread_start()) return -1;
    kh1_gpuq_on = 1;
    return 0;
}

/* ---- session 146: the recording queue (gsqueue.h's kh1_recq_*) ---- */
static void recq_cwake(void) { gq_sem_post(0); }
static void recq_pwait(void) { gq_sem_wait(2); }
static void recq_pwake(void) { gq_sem_post(2); }

int kh1_recq_start(u32 bytes) {
    if (kh1_recq_on) return 0;
    if (!kh1_gpuq_on) return -1;
    recq.csleeps = &gq_worker_sleeps;
    recq.cwake = recq_cwake;
    recq.pwait = recq_pwait;
    recq.pwake = recq_pwake;
    recq.us_wait = &kh1_recq_us_wait;
    recq.waits = &kh1_recq_waits;
    if (q_init(&recq, bytes)) return -1;
    STORE(kh1_recq_on, 1);
    return 0;
}

void kh1_recq_put(KH1GsqFn fn, const u32 *args, u32 nargs, const u32 *data, u32 nqw) {
    if (!kh1_recq_on) fn(args, data, nqw);
    else q_put(&recq, fn, args, nargs, data, nqw * 16, 1);
}

void kh1_recq_sync(void) {
    if (kh1_recq_on) q_wait_tail(&recq, recq.wpos);
}

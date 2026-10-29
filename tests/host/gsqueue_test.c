/* host/null/gsqueue.c's two ordered queues (session 146): the GS worker's (kh1_gsq) and the recording queue
 * the GPU frame's thread runs between its jobs (kh1_recq).  A producer puts ops of random sizes (joined runs of
 * the same op, ops past half the ring that run at once on the producer, wraps of a small ring) and jobs; the
 * consumer side checks each op's arguments and data and that the ops ran in the order put, and the syncs
 * return only once everything put has run.  Not part of the PS2 build. */
#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "../../host/null/gsqueue.h"

static u32 rnd_s = 12345;
static u32 rnd(void) {
    rnd_s = rnd_s * 1103515245u + 12345u;
    return rnd_s >> 8;
}

static u32 word(u32 seq, u32 i) { return seq * 2654435761u ^ i * 40503u; }

/* each queue's check: the next op number expected, the words seen, the failures */
typedef struct {
    u32 next, words, bad;
} Seen;
static Seen seen[2];
static volatile u32 jobs_run;

/* an op: a[0] its number, a[1] the queue; each data qword word(number, 0..3); a joined run repeats the number */
static void op(const u32 *a, const u32 *d, u32 nqw) {
    Seen *s = &seen[a[1]];
    u32 i;
    if (a[0] != s->next && a[0] + 1 != s->next) s->bad++; /* in order (a join repeats the last number) */
    s->next = a[0] + 1;
    for (i = 0; i < nqw * 4; i++)
        if (d[i] != word(a[0], i % 4)) s->bad++;
    s->words += nqw * 4;
}

static void job(const u32 *a, const u32 *d, u32 nqw) {
    (void)a;
    (void)d;
    (void)nqw;
    jobs_run++;
}

static u32 buf[1 << 16];

static void put_ops(int q, u32 n, u32 *words) {
    u32 k, i, nq, seq = 0, reps, args[2];
    for (k = 0; k < n; k++) {
        nq = rnd() % 8 == 0 ? rnd() % 9000 : rnd() % 40; /* now and then past half the ring */
        reps = rnd() % 4 == 0 ? 1 + rnd() % 5 : 1;      /* a run of the same op: joined */
        for (i = 0; i < nq * 4; i++) buf[i] = word(seq, i % 4);
        args[0] = seq;
        args[1] = (u32)q;
        for (i = 0; i < reps; i++) {
            if (q) kh1_recq_put(op, args, 2, buf, nq);
            else kh1_gsq_put(op, args, 2, buf, nq);
            *words += nq * 4;
        }
        if (q && rnd() % 16 == 0) kh1_gpuq_put(job, args, 1);
        seq++;
    }
}

int main(void) {
    u32 w0 = 0, w1 = 0, fails = 0;
    if (kh1_gsq_start(1u << 16) || kh1_gpuq_start() || kh1_recq_start(1u << 16)) {
        printf("gsqueue_test: no threads\n");
        return 1;
    }
    put_ops(0, 20000, &w0);
    kh1_gsq_sync();
    put_ops(1, 20000, &w1);
    kh1_recq_sync();
    kh1_gpuq_wait();
    if (seen[0].bad || seen[0].words != w0 || seen[0].next != 20000) {
        printf("gsqueue_test: the GS worker's queue: %u bad, %u of %u words, %u ops\n", seen[0].bad, seen[0].words, w0,
               seen[0].next);
        fails++;
    }
    if (seen[1].bad || seen[1].words != w1 || seen[1].next != 20000) {
        printf("gsqueue_test: the recording queue: %u bad, %u of %u words, %u ops\n", seen[1].bad, seen[1].words, w1,
               seen[1].next);
        fails++;
    }
    printf("gsqueue_test: %s (%u + %u words through the two queues, %u jobs between)\n", fails ? "FAILED" : "ok", w0, w1,
           jobs_run);
    return fails != 0;
}

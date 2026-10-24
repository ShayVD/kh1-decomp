/* The null platform's EE threads and semaphores (platform/thread.h), for the host runner: the
 * game's own threads run as coroutines on POSIX ucontext, each on a host stack of its own.
 *
 * The game makes two threads: src/util/thread.c's worker func_0010c0c8 (priority 40, under the
 * main thread's 30), which runs the callbacks func_0010c170 registers (the disc loader's reads,
 * src/io/discfile.c func_001201d0 / func_001202c0: every func_001204a0 file load) once a frame,
 * and src/game/hdd.c's HDD thread. Without them a load never finished (its result stayed -1).
 * The EE runs a lower-priority thread only while the higher ones wait, and so does this: a
 * thread runs from the main thread's PlatWaitSema until it waits itself. A signal only marks the
 * waiter ready. The main thread's wait then lets a frame pass (the vblank handler, which signals
 * the main loop's frame semaphore through func_0010c378), as before.
 *
 * Only the host runner uses this: the Vita build replaces host/null with its own kernel threads.
 * Not part of the PS2 build (it lives outside src/). */
#define _GNU_SOURCE
#include <stdlib.h>
#include <ucontext.h>
#include "common.h"
#include "platform/thread.h"

void kh1_host_vblank(void);

#define NULL_THREADS 8
#define NULL_SEMAS 32
#define NULL_STACK 0x40000

enum { T_FREE, T_MADE, T_READY, T_WAIT, T_DONE };

typedef struct {
    s32 state;
    s32 sema;               /* the semaphore it waits on (T_WAIT) */
    void (*entry)(void *);  /* ThreadParam +0x4 */
    void *arg;
    ucontext_t uc;
    void *stack;
} NullThread;

typedef struct {
    s32 used;
    s32 count;
    s32 max;
} NullSema;

/* thread 0 is the main thread (the game's main, func_00100558) */
static NullThread thr[NULL_THREADS];
static NullSema sem[NULL_SEMAS];
static s32 cur;
static s32 main_wait = -1;  /* the semaphore the main thread waits on during its frame */
static ucontext_t main_uc;

int PlatGetThreadId(void) { return cur; }
int PlatChangeThreadPriority(int id, int prio) { return 0; }

/* the kernel's ThreadParam: status, entry, stack, stackSize, gpReg, initPriority, ... */
int PlatCreateThread(void *param) {
    s32 i;
    for (i = 1; i < NULL_THREADS; i++)
        if (thr[i].state == T_FREE) {
            thr[i].state = T_MADE;
            thr[i].entry = ((void (**)(void *))param)[1];
            return i;
        }
    return -1;
}

static void thread_entry(void) {
    thr[cur].entry(thr[cur].arg);
    /* the entry returned: the thread is done (ExitThread) */
    thr[cur].state = T_DONE;
    setcontext(&main_uc);
}

int PlatStartThread(int id, void *arg) {
    NullThread *t;
    if (id <= 0 || id >= NULL_THREADS || thr[id].state != T_MADE)
        return -1;
    t = &thr[id];
    if (t->stack == 0 && (t->stack = malloc(NULL_STACK)) == 0)
        abort();
    getcontext(&t->uc);
    t->uc.uc_stack.ss_sp = t->stack;
    t->uc.uc_stack.ss_size = NULL_STACK;
    t->uc.uc_link = 0;
    makecontext(&t->uc, thread_entry, 0);
    t->arg = arg;
    t->state = T_READY;  /* it runs at the main thread's next wait */
    return id;
}

/* the kernel's SemaParam: currentCount, maxCount, initCount, numWaitThreads, attr, option */
int PlatCreateSema(void *param) {
    s32 *p = param;
    s32 i;
    for (i = 1; i < NULL_SEMAS; i++)
        if (!sem[i].used) {
            sem[i].used = 1;
            sem[i].count = p[2];
            sem[i].max = p[1] > 0 ? p[1] : 0x7FFFFFFF;
            return i;
        }
    return -1;
}

/* run the ready threads until each waits (or ends) */
static void run_threads(void) {
    s32 i, again;
    do {
        again = 0;
        for (i = 1; i < NULL_THREADS; i++) {
            if (thr[i].state != T_READY)
                continue;
            cur = i;
            swapcontext(&main_uc, &thr[i].uc);
            cur = 0;
            again = 1;
        }
    } while (again && main_wait >= 0);
}

int PlatWaitSema(int id) {
    if (id <= 0 || id >= NULL_SEMAS || !sem[id].used)
        return -1;
    if (sem[id].count > 0) {
        sem[id].count--;
        return id;
    }
    if (cur != 0) {
        /* a game thread waits: back to the main thread until a signal */
        thr[cur].state = T_WAIT;
        thr[cur].sema = id;
        swapcontext(&thr[cur].uc, &main_uc);
        return id;
    }
    /* the main thread waits: the other threads run, then a frame passes (its handler signals
     * the main loop's frame semaphore) unless a thread signalled it first */
    main_wait = id;
    run_threads();
    if (main_wait >= 0)
        kh1_host_vblank();
    main_wait = -1;
    return id;
}

int PlatSignalSema(int id) {
    s32 i;
    if (id <= 0 || id >= NULL_SEMAS || !sem[id].used)
        return -1;
    if (cur != 0 && main_wait == id) {
        main_wait = -1;
        return id;
    }
    for (i = 1; i < NULL_THREADS; i++)
        if (thr[i].state == T_WAIT && thr[i].sema == id) {
            thr[i].state = T_READY;
            return id;
        }
    if (sem[id].count < sem[id].max)
        sem[id].count++;
    return id;
}

/* from the vblank handler (inside the main thread's wait): the main thread is the waiter */
int PlatISignalSema(int id) {
    if (main_wait == id) {
        main_wait = -1;
        return id;
    }
    return PlatSignalSema(id);
}

int PlatIReferSemaStatus(int id, void *param) {
    s32 *p = param;
    s32 i, n = 0;
    if (id <= 0 || id >= NULL_SEMAS || !sem[id].used)
        return -1;
    for (i = 1; i < NULL_THREADS; i++)
        if (thr[i].state == T_WAIT && thr[i].sema == id)
            n++;
    if (main_wait == id)
        n++;
    p[0] = sem[id].count;
    p[1] = sem[id].max;
    p[2] = 0;
    p[3] = n;
    p[4] = 0;
    p[5] = 0;
    return id;
}

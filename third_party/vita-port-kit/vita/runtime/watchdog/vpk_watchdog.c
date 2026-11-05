/* The watchdog thread and the threads line (vpk_watchdog.h).
 * From kh1-decomp host/vita/main.c @ e1575e1a. */
#include <stdio.h>
#include <string.h>
#include "vpk_watchdog.h"

static struct {
    SceUID uid;
    const char *name;
    SceUInt64 run;
    unsigned int pre;
} threads[VPK_THREADS_MAX];
static int nthreads;

void vpk_thread_note(int uid, const char *name) {
    if (uid < 0 || nthreads >= VPK_THREADS_MAX) return;
    threads[nthreads].uid = uid;
    threads[nthreads++].name = name;
}

int vpk_threads_line(char *line, int size, const char *head) {
    int i, len = snprintf(line, size, "%s", head);
    for (i = 0; i < nthreads && len < size - 80; i++) {
        SceKernelThreadInfo ti;
        SceUInt64 run;
        unsigned int pre;
        memset(&ti, 0, sizeof ti);
        ti.size = sizeof ti;
        if (sceKernelGetThreadInfo(threads[i].uid, &ti) < 0) continue;
        run = (SceUInt64)ti.runClocks;
        pre = ti.threadPreemptCount + ti.intrPreemptCount;
        len += snprintf(line + len, size - len, "%s %s %u ms (core %d, mask %x, prio %x, %u preempted)", i ? "," : "",
                        threads[i].name, (unsigned int)((run - threads[i].run) / 1000), (int)ti.lastExecutedCpuId,
                        (unsigned int)ti.currentCpuAffinityMask, (unsigned int)ti.currentPriority, pre - threads[i].pre);
        threads[i].run = run;
        threads[i].pre = pre;
    }
    return len;
}

int vpk_thread_start(const char *name, SceKernelThreadEntry entry, int prio, int stack, int cpu_mask) {
    SceUID t = sceKernelCreateThread(name, entry, prio, stack, 0, cpu_mask, 0);
    if (t >= 0) sceKernelStartThread(t, 0, 0);
    vpk_thread_note(t, name);
    return t;
}

static unsigned int wd_period;
static void (*wd_window)(void *);
static void *wd_user;

static int wd_entry(SceSize args, void *argp) {
    (void)args;
    (void)argp;
    for (;;) {
        sceKernelDelayThread(wd_period);
        wd_window(wd_user);
    }
    return 0;
}

int vpk_watchdog_start(const char *name, unsigned int period_us, void (*window)(void *user), void *user, int prio,
                       int cpu_mask) {
    wd_period = period_us;
    wd_window = window;
    wd_user = user;
    return vpk_thread_start(name, wd_entry, prio, 0x4000, cpu_mask);
}

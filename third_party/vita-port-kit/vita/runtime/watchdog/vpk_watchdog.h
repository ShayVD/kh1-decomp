/* A watchdog thread and a per-thread CPU line for it.  A second thread that logs every couple of seconds of
 * wall time shows where the app is even when the game thread hangs or the screen is black; the threads line
 * gives each noted thread's CPU time over the window (the kernel's run clock, so time another thread took from
 * it is not counted), the core it last ran on, its affinity mask and priority, and how often it was preempted.
 * From kh1-decomp host/vita/main.c (watchdog, threads_line, kh1_vita_thread_note) @ e1575e1a. */
#ifndef VPK_WATCHDOG_H
#define VPK_WATCHDOG_H

#include <psp2/kernel/threadmgr.h>

#define VPK_THREADS_MAX 12

/* remember a thread for vpk_threads_line (uid < 0, or more than VPK_THREADS_MAX: ignored) */
void vpk_thread_note(int uid, const char *name);
/* "HEAD name N ms (core C, mask M, prio P, K preempted), ..." for the noted threads since the last call, into
 * line (size bytes, no newline); its length */
int vpk_threads_line(char *line, int size, const char *head);

/* creates, starts and notes a thread (prio: the kernel's, e.g. 0x10000100 + offset; cpu_mask:
 * SCE_KERNEL_CPU_MASK_USER_n or 0 for any); its uid, or < 0 */
int vpk_thread_start(const char *name, SceKernelThreadEntry entry, int prio, int stack, int cpu_mask);

/* a watchdog that calls window(user) every period_us of wall time, forever, on a thread of its own (the
 * thread is noted as "watchdog"); its uid, or < 0 */
int vpk_watchdog_start(const char *name, unsigned int period_us, void (*window)(void *user), void *user, int prio,
                       int cpu_mask);

#endif /* VPK_WATCHDOG_H */

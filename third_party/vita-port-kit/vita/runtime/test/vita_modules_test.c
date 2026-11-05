/* Host tests for the vitasdk-facing modules (log, clocks, watchdog's threads line, procparam) against fakes of
 * the few SDK calls they make (fake_psp2/ declares them, this file defines them).  test/run_host_tests.sh builds
 * it with -DVPK_LOG_NO_STDIO_REDIRECT (funopen and _GLOBAL_REENT are newlib's). */
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <psp2/io/fcntl.h>
#include <psp2/kernel/processmgr.h>
#include <psp2/kernel/threadmgr.h>
#include <psp2/power.h>
#include "../log/vpk_log.h"
#include "../clocks/vpk_clocks.h"
#include "../watchdog/vpk_watchdog.h"
#include "../procparam/vpk_procparam.h"
#include "../costack/vpk_costack.h"

int printf(const char *, ...); /* vpk_log_stdio.c's: everything below that prints goes to the fake log */
static int fails;
static char report[256];
#define CHECK(c) do { if (!(c)) { snprintf(report + strlen(report), sizeof report - strlen(report), "FAIL line %d: %s\n", __LINE__, #c); fails++; } } while (0)

/* the fakes */
static char logbuf[16384];
static int loglen, removed, opened = 7;
static SceUInt64 now;
SceUID sceIoOpen(const char *file, int flags, int mode) { (void)file; (void)flags; (void)mode; return opened; }
int sceIoRemove(const char *file) { (void)file; removed++; return 0; }
int sceIoWrite(SceUID fd, const void *data, unsigned int size) {
    (void)fd;
    if (loglen + (int)size <= (int)sizeof logbuf) memcpy(logbuf + loglen, data, size), loglen += size;
    return (int)size;
}
SceUInt64 sceKernelGetProcessTimeWide(void) { return now += 5; }
static int clk[4] = {333, 111, 111, 111};
int scePowerGetArmClockFrequency(void) { return clk[0]; }
int scePowerGetBusClockFrequency(void) { return clk[1]; }
int scePowerGetGpuClockFrequency(void) { return clk[2]; }
int scePowerGetGpuXbarClockFrequency(void) { return clk[3]; }
int scePowerSetArmClockFrequency(int f) { clk[0] = f > 444 ? 444 : f; return 0; }
int scePowerSetBusClockFrequency(int f) { clk[1] = f; return 0; }
int scePowerSetGpuClockFrequency(int f) { clk[2] = f; return 0; }
int scePowerSetGpuXbarClockFrequency(int f) { clk[3] = f; return 0; }
static SceUInt64 run[3] = {0, 0, 0};
static unsigned char fake_stack[1 << 20];
static int stack_mode; /* 0: a thread of the threads line; 1: the main thread's stack around the caller */
SceUID sceKernelCreateThread(const char *name, SceKernelThreadEntry entry, int prio, SceSize stack, unsigned int attr,
                             int cpu_mask, const void *option) {
    (void)name; (void)entry; (void)prio; (void)stack; (void)attr; (void)cpu_mask; (void)option;
    return 42;
}
int sceKernelStartThread(SceUID id, SceSize args, void *argp) { (void)id; (void)args; (void)argp; return 0; }
int sceKernelDelayThread(unsigned int us) { (void)us; return 0; }
SceUID sceKernelGetThreadId(void) { return 1; }
int sceKernelGetThreadInfo(SceUID id, SceKernelThreadInfo *ti) {
    volatile unsigned char probe;
    if (stack_mode) { /* a 1 MiB "stack" whose top is just above here */
        ti->stack = (unsigned char *)&probe - (512 << 10);
        ti->stackSize = 1 << 20;
        return 0;
    }
    if (id < 0 || id > 2) return -1;
    ti->runClocks = run[id];
    ti->lastExecutedCpuId = id;
    ti->currentCpuAffinityMask = 0x10000 << id;
    ti->currentPriority = 0x40 + id;
    ti->threadPreemptCount = 3 * (unsigned int)id;
    ti->intrPreemptCount = 1;
    return 0;
}

int main(void) {
    char line[640], big[6000];
    VpkClocks c;
    unsigned int pool;

    /* log: nothing before it is open; the first line; formatted lines; the cut; printf / puts; the counters */
    vpk_log("lost\n");
    CHECK(loglen == 0);
    CHECK(vpk_log_open("ux0:data/x/x.log", "x: log open\n") == 7 && removed == 1);
    CHECK(loglen == 12 && !memcmp(logbuf, "x: log open\n", 12));
    loglen = 0;
    vpk_log("a %d %s\n", 5, "b");
    printf("c%d\n", 7);
    puts("d");
    CHECK(loglen == 11 && !memcmp(logbuf, "a 5 b\nc7\nd\n", 11));
    CHECK(vpk_log_writes == 4 && vpk_log_us == 4 * 5);
    loglen = 0;
    memset(big, 'z', sizeof big - 1);
    big[sizeof big - 1] = 0;
    vpk_log("%s", big);
    CHECK(loglen == 4607);

    /* clocks: set, and what the Vita accepted read back */
    vpk_clocks_set(VPK_CLOCKS_MAX, &c);
    CHECK(c.arm_was == 333 && c.arm == 444 && c.bus == 222 && c.gpu == 222 && c.gpu_xbar == 166);
    vpk_clocks_set(500, 222, 222, 166, &c);
    CHECK(c.arm_was == 444 && c.arm == 444);

    /* the threads line: CPU time and preemptions since the last line; a uid the kernel does not know left out */
    vpk_thread_note(0, "game");
    vpk_thread_note(-1, "failed");
    vpk_thread_note(2, "gpu");
    vpk_thread_note(9, "gone");
    run[0] = 12000; run[2] = 3000;
    vpk_threads_line(line, sizeof line, "x: threads:");
    CHECK(!strcmp(line, "x: threads: game 12 ms (core 0, mask 10000, prio 40, 1 preempted), gpu 3 ms (core 2, mask 40000, "
                        "prio 42, 7 preempted)"));
    run[0] = 20000;
    vpk_threads_line(line, sizeof line, "x: threads:");
    CHECK(!strncmp(line, "x: threads: game 8 ms (core 0, mask 10000, prio 40, 0 preempted), gpu 0 ms", 74));
    CHECK(vpk_thread_start("t", 0, 0x10000100, 0x4000, 0) == 42);

    /* procparam: the main stack below the caller, less the own part, becomes the pool */
    stack_mode = 1;
    pool = vpk_main_stack_to_costack(256 << 10);
    CHECK(pool > 256 << 10 && pool < 280 << 10); /* 512 KiB above the fake probe, less 256, plus the frames between */
    CHECK(vpk_costack_owns((unsigned long)vpk_costack_alloc(4096), 4096));
    (void)fake_stack;

    fputs(report, stderr);
    fprintf(stderr, fails ? "vita_modules_test: %d failed\n" : "vita_modules_test: ok\n", fails);
    return fails != 0;
}

/* The host runner (docs/vita-port-plan.md section 5.1b): main() calls the game's own main,
 * func_00100558 (crt0's call: func_00262c78 (__main), func_00109288, then func_00109770 for
 * ever), on the null platform.  The first PlatCdRead ends the run (exit 0), since the null
 * platform has no disc to answer it; KH1_HOST_CD=go lets it carry on (every read fails and
 * the game retries).  A crash prints a backtrace.  Not part of the PS2 build. */
#define _GNU_SOURCE
#include <execinfo.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void func_00100558(int argc, char **argv);

int kh1_host_stop_at_cdread = 1;

static void on_crash(int sig) {
    void *bt[64];
    int n = backtrace(bt, 64);
    fprintf(stderr, "kh1-host: signal %d (%s)\n", sig, strsignal(sig));
    backtrace_symbols_fd(bt, n, 2);
    _exit(128 + sig);
}

int main(int argc, char **argv) {
    const char *cd = getenv("KH1_HOST_CD");
    setvbuf(stdout, 0, _IONBF, 0);
    signal(SIGSEGV, on_crash);
    signal(SIGBUS, on_crash);
    signal(SIGFPE, on_crash);
    signal(SIGILL, on_crash);
    signal(SIGABRT, on_crash);
    if (cd && strcmp(cd, "go") == 0)
        kh1_host_stop_at_cdread = 0;
    printf("kh1-host: func_00100558 (the game's main)\n");
    func_00100558(argc, argv);
    printf("kh1-host: func_00100558 returned\n");
    return 1;
}

/* The host runner (docs/vita-port-plan.md sections 5.1b and 5.1c): main() calls the game's own
 * main, func_00100558 (crt0's call: func_00262c78 (__main), func_00109288, then func_00109770
 * for ever), on the null platform.
 *
 *   KH1_HOST_ISO=PATH   the user's own disc image (never in the repo): PlatCdSearchFile and
 *                       PlatCdRead answer from it (host/port/cd_image.c).  Without one the first
 *                       PlatCdRead ends the run (exit 0), since there is no disc to answer it;
 *                       KH1_HOST_CD=go lets it carry on (every read fails and the game retries).
 *   KH1_HOST_FRAMES=N   stop after N frames (default 600); a frame is one call of the game's
 *                       vblank handler, which PlatGsSyncV and PlatWaitSema run
 *   KH1_HOST_TRACE=1    print every search and read
 *   KH1_HOST_OVL=stub   a test switch: a call of the overlay entry D_00F20000 returns 0 instead
 *                       of faulting, so the run goes on past it (each call's two arguments are
 *                       printed).  No overlay code runs: what
 *                       the boot does next is the main ELF's own (docs/vita-port-plan.md 5.1h).
 *                       KH1_HOST_OVL=stub:N also asks for game state N at the title's entry call.
 *                       Not under valgrind, which runs the overlay's bytes instead of faulting.
 *
 * A crash prints a backtrace and what the run had read; a fault inside the memory map (a jump
 * into loaded code: the overlay entry D_00F20000 until the overlays build natively) prints the
 * PS2 address and the caller.  Not part of the PS2 build. */
#define _GNU_SOURCE
#include <execinfo.h>
#include <signal.h>
#include <ucontext.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void func_00100558(int argc, char **argv);
int kh1_cd_image_open(const char *path);

int kh1_host_stop_at_cdread = 1;
int kh1_host_trace;
unsigned int kh1_host_cd_reads, kh1_host_cd_sectors;
static unsigned long frames, max_frames = 600;
static int ovl_stub;
static unsigned long ovl_calls;

static void summary(void) {
    fprintf(stderr, "kh1-host: %lu frames, %u disc reads (%u sectors)\n", frames, kh1_host_cd_reads,
            kh1_host_cd_sectors);
    if (ovl_stub)
        fprintf(stderr, "kh1-host: %lu overlay calls answered 0 (KH1_HOST_OVL=stub)\n", ovl_calls);
}

/* sceGsSyncVCallback's handler (host/port/sdk_host.c), an INTC handler: int (*)(int cause) */
extern void *kh1_vsync_cb;
void kh1_null_iop_frame(void);
void kh1_host_vblank(void) {
    static int in_vblank;
    if (in_vblank) return;
    in_vblank = 1;
    frames++;
    kh1_null_iop_frame();
    if (kh1_vsync_cb) ((int (*)(int))kh1_vsync_cb)(2);
    in_vblank = 0;
    if (frames >= max_frames) {
        printf("kh1-host: %lu frames: stop\n", frames);
        summary();
        exit(0);
    }
}

/* host/port/memmap.c: the PS2's 0x6A0000 - 0x1FE0000 */
extern unsigned char kh1_memmap[];
#define KH1_MEM_BASE 0x6A0000u
#define KH1_MEM_END 0x1FE0000u
/* the overlay area (host/port/memmap.c's D_00F20000, up to the slots at D_00FE0000) */
#define KH1_OVL_BASE 0xF20000u
#define KH1_OVL_END 0xFE0000u

#if defined(REG_EIP) && defined(REG_ESP)
/* KH1_HOST_OVL=stub[:N]: the fault is the call's first instruction (EIP is the faulting address),
 * so the stack is the call's: the return address on top, the arguments above it.  EIP moves to
 * ovl_entry, a host function with the entry's convention (int (int cmd, int arg), cdecl), which
 * returns 0 to the caller.  With N, the first call of dktitle.x's entry (0xF20000 (0, 0), from
 * func_00109630) also asks for game state N with func_00109558, the request the main ELF's own
 * state changes use (roomload.c, gameover.c): a guess at the title's choice (2 would be a new
 * game: func_00109770's case 2 runs func_00109588 and func_001095b0). */
static int ovl_state = -1;
int func_00109558(int state);
static int ovl_entry(int cmd, int arg) {
    ovl_calls++;
    printf("kh1-host: frame %lu: overlay entry D_00F20000(%d, %d) answered 0\n", frames, cmd, arg);
    if (ovl_state >= 0 && cmd == 0) {
        printf("kh1-host: KH1_HOST_OVL: func_00109558(%d), the title's choice (a guess)\n", ovl_state);
        func_00109558(ovl_state);
        ovl_state = -1;
    }
    return 0;
}
static int ovl_return(siginfo_t *si, void *uc) {
    greg_t *r = ((ucontext_t *)uc)->uc_mcontext.gregs;
    unsigned long a = (unsigned long)si->si_addr - (unsigned long)kh1_memmap + KH1_MEM_BASE;
    if (!ovl_stub || (void *)r[REG_EIP] != si->si_addr || a < KH1_OVL_BASE || a >= KH1_OVL_END)
        return 0;
    /* every call in src/ is to the entry; a fault further in means the bytes ran (valgrind
     * does not keep data from running, so the stub cannot work under it) */
    if (a != KH1_OVL_BASE) {
        fprintf(stderr, "kh1-host: KH1_HOST_OVL=stub: fault at PS2 0x%08lx, past the overlay entry: its bytes ran "
                "(under valgrind?)\n", a);
        return 0;
    }
    r[REG_EIP] = (greg_t)ovl_entry;
    return 1;
}
#else
static int ovl_return(siginfo_t *si, void *uc) {
    (void)si;
    (void)uc;
    return 0;
}
#endif

static void on_crash(int sig, siginfo_t *si, void *uc) {
    void *bt[64];
    int n;
    unsigned long a = (unsigned long)si->si_addr - (unsigned long)kh1_memmap;
    if ((sig == SIGSEGV || sig == SIGILL) && ovl_return(si, uc))
        return;
    fprintf(stderr, "kh1-host: signal %d (%s)\n", sig, strsignal(sig));
    /* executing the memory map: a call into loaded code, an overlay entry such as D_00F20000
     * (docs/vita-port-plan.md 5.2: the overlays need a native build) */
    if ((sig == SIGSEGV || sig == SIGILL) && a < KH1_MEM_END - KH1_MEM_BASE) {
        fprintf(stderr, "kh1-host: fault at PS2 0x%08lx in the memory map (a jump into loaded code?)\n",
                a + KH1_MEM_BASE);
#ifdef REG_ESP
        /* a call's return address is on top of the stack: the caller */
        {
            void *ret = *(void **)((ucontext_t *)uc)->uc_mcontext.gregs[REG_ESP];
            fprintf(stderr, "kh1-host: called from\n");
            backtrace_symbols_fd(&ret, 1, 2);
        }
#endif
    }
    n = backtrace(bt, 64);
    summary();
    backtrace_symbols_fd(bt, n, 2);
    _exit(128 + sig);
}

int main(int argc, char **argv) {
    const char *cd = getenv("KH1_HOST_CD");
    const char *iso = getenv("KH1_HOST_ISO");
    const char *nf = getenv("KH1_HOST_FRAMES");
    setvbuf(stdout, 0, _IONBF, 0);
    {
        static const int sigs[] = { SIGSEGV, SIGBUS, SIGFPE, SIGILL, SIGABRT };
        struct sigaction sa;
        unsigned i;
        memset(&sa, 0, sizeof sa);
        sa.sa_sigaction = on_crash;
        sa.sa_flags = SA_SIGINFO;
        for (i = 0; i < sizeof sigs / sizeof sigs[0]; i++)
            sigaction(sigs[i], &sa, 0);
    }
    if (cd && strcmp(cd, "go") == 0)
        kh1_host_stop_at_cdread = 0;
    if (nf)
        max_frames = strtoul(nf, 0, 0);
    kh1_host_trace = getenv("KH1_HOST_TRACE") != 0;
    {
        const char *ovl = getenv("KH1_HOST_OVL");
        ovl_stub = ovl && strncmp(ovl, "stub", 4) == 0 && (ovl[4] == 0 || ovl[4] == ':');
        if (ovl_stub && ovl[4] == ':')
            ovl_state = strtol(ovl + 5, 0, 0);
    }
    if (iso) {
        if (!kh1_cd_image_open(iso)) {
            fprintf(stderr, "kh1-host: %s: not a disc image (no ISO9660 volume at sector 16)\n", iso);
            return 2;
        }
        printf("kh1-host: disc image %s\n", iso);
    }
    printf("kh1-host: func_00100558 (the game's main)\n");
    func_00100558(argc, argv);
    printf("kh1-host: func_00100558 returned\n");
    summary();
    return 1;
}

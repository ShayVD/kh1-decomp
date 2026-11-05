/* vpk_ucontext on 32-bit ARM: two coroutines ping-pong through swapcontext, callee-saved integer and VFP
 * values live across switches, the entry's stack is 8-aligned, each context keeps its own FPSCR, and an
 * entry's return goes to uc_link.  Runs on ARM Linux under qemu-arm (or any ARMv7 hard-float Linux):
 *   arm-linux-gnueabihf-gcc -std=gnu99 -O2 -mfpu=neon -I../std ../vpk_ucontext.S ucontext_test.c -o ucontext_test
 *   qemu-arm -L /usr/arm-linux-gnueabihf ./ucontext_test */
#include <stdint.h>
#include <stdio.h>
#include <ucontext.h> /* ../std/ucontext.h */

static int fails;
#define CHECK(c) do { if (!(c)) { printf("FAIL %s:%d: %s\n", __FILE__, __LINE__, #c); fails++; } } while (0)

#define FPSCR_FZ (1u << 24)
static unsigned int get_fpscr(void) { unsigned int v; __asm__ volatile("vmrs %0, fpscr" : "=r"(v)); return v; }
static void set_fpscr(unsigned int v) { __asm__ volatile("vmsr fpscr, %0" : : "r"(v)); }

static ucontext_t main_uc, a_uc, b_uc, done_uc;
static unsigned char a_stack[16384] __attribute__((aligned(16)));
static unsigned char b_stack[16384] __attribute__((aligned(16)));
static unsigned char d_stack[16384] __attribute__((aligned(16)));
static volatile int trace[16], ntrace;
static volatile int a_aligned, a_fz_seen, finished;

/* values the compiler keeps in callee-saved registers across the switch calls */
static __attribute__((noinline)) int busy(int seed, ucontext_t *self, ucontext_t *other, int tag) {
    int r0 = seed, r1 = seed * 3, r2 = seed * 5, r3 = seed * 7, r4 = seed * 11, r5 = seed * 13;
    double f0 = seed * 0.5, f1 = seed * 0.25, f2 = seed * 1.5, f3 = seed * 2.5;
    int i;
    for (i = 0; i < 3; i++) {
        trace[ntrace++] = tag + i;
        swapcontext(self, other);
        r0 += 1; r1 += 1; r2 += 1; r3 += 1; r4 += 1; r5 += 1;
        f0 += 1.0; f1 += 1.0; f2 += 1.0; f3 += 1.0;
    }
    return (r0 - seed) + (r1 - seed * 3) + (r2 - seed * 5) + (r3 - seed * 7) + (r4 - seed * 11) + (r5 - seed * 13) +
           (int)((f0 - seed * 0.5) + (f1 - seed * 0.25) + (f2 - seed * 1.5) + (f3 - seed * 2.5));
}

static void entry_a(void) {
    unsigned char probe;
    a_aligned = (((uintptr_t)__builtin_frame_address(0)) & 7) == 0;
    (void)probe;
    set_fpscr(get_fpscr() | FPSCR_FZ); /* this context's own FPSCR */
    CHECK(busy(1000, &a_uc, &b_uc, 10) == 3 * 10);
    a_fz_seen = (get_fpscr() & FPSCR_FZ) != 0;
    swapcontext(&a_uc, &b_uc);
}

static void entry_b(void) {
    CHECK((get_fpscr() & FPSCR_FZ) == 0); /* not a's */
    CHECK(busy(2000, &b_uc, &a_uc, 20) == 3 * 10);
    swapcontext(&b_uc, &main_uc);
}

static void entry_done(void) { finished = 1; } /* returns: uc_link (main_uc) */

int main(void) {
    static const int want[] = {10, 20, 11, 21, 12, 22};
    int i;

    getcontext(&a_uc);
    a_uc.uc_stack.ss_sp = a_stack;
    a_uc.uc_stack.ss_size = sizeof a_stack - 4; /* an unaligned top: makecontext aligns it */
    a_uc.uc_link = 0;
    makecontext(&a_uc, entry_a, 0);
    getcontext(&b_uc);
    b_uc.uc_stack.ss_sp = b_stack;
    b_uc.uc_stack.ss_size = sizeof b_stack;
    b_uc.uc_link = 0;
    makecontext(&b_uc, entry_b, 0);

    set_fpscr(get_fpscr() & ~FPSCR_FZ);
    swapcontext(&main_uc, &a_uc);

    CHECK((get_fpscr() & FPSCR_FZ) == 0); /* main's own FPSCR back */
    CHECK(a_aligned);
    CHECK(a_fz_seen);
    CHECK(ntrace == 6);
    for (i = 0; i < 6 && i < ntrace; i++) CHECK(trace[i] == want[i]);

    /* an entry that returns lands in uc_link */
    getcontext(&done_uc);
    done_uc.uc_stack.ss_sp = d_stack;
    done_uc.uc_stack.ss_size = sizeof d_stack;
    done_uc.uc_link = &main_uc;
    makecontext(&done_uc, entry_done, 0);
    swapcontext(&main_uc, &done_uc);
    CHECK(finished);

    printf(fails ? "ucontext_test: %d failed\n" : "ucontext_test: ok\n", fails);
    return fails != 0;
}

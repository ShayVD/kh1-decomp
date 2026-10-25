/* The four ucontext calls host/null/threads.c and host/port/tasks.c use, for the Vita (newlib has
 * none): a cooperative switch of the callee-saved registers, host/vita/context.S.  Only what those
 * files need: getcontext before makecontext (never as a resume point), makecontext with no
 * arguments, swapcontext and setcontext.  The names are macros for kh1_ ones, so the ARM Linux
 * check (tools/vita/build.py --linux-arm) can link it beside glibc's.  Not part of the PS2 build. */
#ifndef KH1_VITA_UCONTEXT_H
#define KH1_VITA_UCONTEXT_H

#define ucontext_t kh1_ucontext_t
#define getcontext kh1_getcontext
#define setcontext kh1_setcontext
#define swapcontext kh1_swapcontext
#define makecontext kh1_makecontext

typedef struct {
    void *ss_sp;
    unsigned int ss_size;
    int ss_flags;
} kh1_stack_t;

/* the offsets are context.S's */
typedef struct kh1_ucontext {
    struct kh1_ucontext *uc_link; /* +0: where the entry's return goes (0: abort) */
    kh1_stack_t uc_stack;         /* +4 */
    unsigned int regs[10];        /* +16: r4-r11, sp, lr */
    double vfp[8];                /* +56: d8-d15 */
    unsigned int fpscr;           /* +120 */
    unsigned int pad;
} ucontext_t;

int getcontext(ucontext_t *uc);
int setcontext(const ucontext_t *uc);
int swapcontext(ucontext_t *save, const ucontext_t *to);
void makecontext(ucontext_t *uc, void (*fn)(void), int argc, ...);

#endif /* KH1_VITA_UCONTEXT_H */

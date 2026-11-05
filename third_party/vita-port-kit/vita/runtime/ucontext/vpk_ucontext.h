/* A cooperative context switch for 32-bit ARM (the Vita, or ARM Linux for a qemu-arm check): the four
 * ucontext calls a coroutine scheduler needs, which newlib lacks (vpk_ucontext.S).  Only what coroutines
 * need: getcontext before makecontext (never as a resume point), makecontext with no arguments to the
 * entry, swapcontext and setcontext.  When the entry returns, uc_link is loaded (0: abort()).
 * The names are vpk_ ones so a build can link them beside glibc's; std/ucontext.h maps the standard names
 * onto them for code written against POSIX ucontext.
 * From kh1-decomp host/vita/include/ucontext.h @ e1575e1a. */
#ifndef VPK_UCONTEXT_H
#define VPK_UCONTEXT_H

typedef struct {
    void *ss_sp;
    unsigned int ss_size;
    int ss_flags;
} vpk_stack_t;

/* the offsets are vpk_ucontext.S's */
typedef struct vpk_ucontext {
    struct vpk_ucontext *uc_link; /* +0: where the entry's return goes (0: abort) */
    vpk_stack_t uc_stack;         /* +4 */
    unsigned int regs[10];        /* +16: r4-r11, sp, lr */
    double vfp[8];                /* +56: d8-d15 */
    unsigned int fpscr;           /* +120 */
    unsigned int pad;
} vpk_ucontext_t;

int vpk_getcontext(vpk_ucontext_t *uc);
int vpk_setcontext(const vpk_ucontext_t *uc);
int vpk_swapcontext(vpk_ucontext_t *save, const vpk_ucontext_t *to);
void vpk_makecontext(vpk_ucontext_t *uc, void (*fn)(void), int argc, ...);

#endif /* VPK_UCONTEXT_H */

/* The game's two cooperative task systems off the EE (docs/vita-port-plan.md section 5.1b), with
 * the hand-written switchers of src/asm/ rewritten in C on POSIX ucontext.  Every task gets a host
 * stack of its own (the game's are sized for EE code: 0x9b0 bytes for a small task.c slot); the
 * game's context blocks keep the fields its C reads and writes, the host keeps the registers.
 * The Vita has no ucontext: there the same four calls (save / switch / make / jump) become
 * a small ARM switch or kernel threads.  Not part of the PS2 build (it lives outside src/). */
#define _GNU_SOURCE
#include <stdlib.h>
#include <ucontext.h>
#include "common.h"
#include "util/task.h"
#include "data/pieces/D_0037A170.h"

#define TASK_STACK 0x40000

#define W(p, off) (*(s32 *)((u8 *)(p) + (off)))

static void *task_stack(void **slot) {
    if (*slot == 0)
        *slot = malloc(TASK_STACK);
    if (*slot == 0)
        abort();
    return *slot;
}

/* --- src/util/sa_task.c's tasks (src/asm/text_0024e0a4.s) ---
 * D_0046A03C: the current group's contexts, D_0046A048 of them, 0x10320 bytes apart; D_0046A040
 * the group's scheduler block (+720 the running context); D_0046A044 the 16 priority lists and
 * their nodes.  A context: +0 the four words the entry receives, +16 / +32 func_0024e0f0's second
 * and third arguments (+32 the priority, 0 first), +48 the entry, +176 nonzero while the task
 * lives (on the EE its saved ra), +768 set until it first runs, +784 the frames left to wait. */
extern s32 D_0046A03C;
extern s32 D_0046A040;
extern u8 *D_0046A044;
extern s32 D_0046A048;

#define SA_STRIDE 0x10320
#define SA_MAX 256
#define SA_LIVE 1 /* +176 of a context func_0024e0f0 made (the EE stores func_0024e18c) */

typedef struct {
    u8 *ctx;
    ucontext_t uc;
    ucontext_t *back; /* the scheduler that runs it now */
    void *stack;
} SaCo;
static SaCo sa_co[SA_MAX];

static SaCo *sa_find(u8 *ctx) {
    s32 i;
    for (i = 0; i < SA_MAX; i++)
        if (sa_co[i].ctx == ctx)
            return &sa_co[i];
    for (i = 0; i < SA_MAX; i++)
        if (sa_co[i].ctx == 0) {
            sa_co[i].ctx = ctx;
            return &sa_co[i];
        }
    abort();
    return 0;
}

/* func_0024e0a4: every context of the group free */
void func_0024e0a4(void) {
    u8 *c = (u8 *)D_0046A03C;
    s32 n = D_0046A048;
    do {
        *(u128 *)(c + 176) = KH1_Q(0);
        c += SA_STRIDE;
    } while (--n);
}

/* func_0024e0f0 (entry, arg, priority): the first free context of the group.  None free: the EE
 * spins for ever. */
void func_0024e0f0(s32 fn, s32 arg, s32 prio) {
    u8 *c = (u8 *)D_0046A03C;
    s32 n = D_0046A048;
    for (;;) {
        n--;
        if (W(c, 176) == 0)
            break;
        c += SA_STRIDE;
        if (n == 0)
            abort();
    }
    W(c, 176) = SA_LIVE;
    W(c, 48) = fn;
    W(c, 16) = arg;
    W(c, 32) = prio;
    W(c, 768) = 1;
    W(c, 784) = 1;
    W(c, 192) = (s32)(c + 0x102E0); /* its stack top on the EE */
}

/* func_0024e18c: the entry on its own stack; at its end the running context is free again */
static void sa_entry(void) {
    u8 *c = (u8 *)W(D_0046A040, 720);
    SaCo *co = sa_find(c);
    ((void (*)(s32, s32, s32, s32))W(c, 48))(W(c, 0), W(c, 4), W(c, 8), W(c, 12));
    c = (u8 *)W(D_0046A040, 720);
    W(c, 176) = 0;
    co = sa_find(c);
    setcontext(co->back);
}

/* func_0024e468 (frames): the running task waits that many scheduler passes (no caller in the
 * main ELF; the overlays may have one) */
void func_0024e468(s32 frames) {
    u8 *c = (u8 *)W(D_0046A040, 720);
    SaCo *co = sa_find(c);
    W(c, 768) = 0;
    W(c, 784) = frames;
    swapcontext(&co->uc, co->back);
}

/* func_0024e1d0: one pass.  The live contexts go into 16 lists by priority (in context order),
 * then each list in turn: every task counts, and one whose wait reaches 0 runs until it waits
 * again or ends.  Returns the count. */
s32 func_0024e1d0(void) {
    u8 *sched = (u8 *)D_0046A040;
    u8 *lists = D_0046A044;
    u8 *node = lists + 512;
    u8 *c = (u8 *)D_0046A03C;
    s32 n = D_0046A048, run = 0, b;
    __builtin_memset(lists, 0, 512);
    do {
        if (W(c, 176) != 0) {
            u8 *l = lists + W(c, 32) * 32;
            u8 *tail = (u8 *)W(l, 16);
            W(l, 16) = (s32)node;
            if (tail == 0)
                W(l, 0) = (s32)node;
            else
                W(tail, 16) = (s32)node;
            W(node, 0) = (s32)c;
            W(node, 16) = 0;
            node += 32;
        }
        c += SA_STRIDE;
    } while (--n);
    for (b = 0; b < 16; b++) {
        u8 *nd;
        for (nd = (u8 *)W(lists + b * 32, 0); nd; nd = (u8 *)W(nd, 16)) {
            ucontext_t back;
            SaCo *co;
            c = (u8 *)W(nd, 0);
            run++;
            if (--W(c, 784) != 0)
                continue;
            W(sched, 720) = (s32)c;
            co = sa_find(c);
            co->back = &back;
            if (W(c, 768)) {
                getcontext(&co->uc);
                co->uc.uc_stack.ss_sp = task_stack(&co->stack);
                co->uc.uc_stack.ss_size = TASK_STACK;
                co->uc.uc_link = 0;
                makecontext(&co->uc, sa_entry, 0);
                W(c, 768) = 0;
            }
            swapcontext(&back, &co->uc);
            sched = (u8 *)D_0046A040;
        }
    }
    return run;
}

/* --- src/util/task.c's tasks (func_001bfac8 in src/asm/text_001aa1f8.s) ---
 * D_0037A170 the run queue ({context, slot}, slot 0 the main loop, ended by a null context),
 * D_0037A164 the running entry, D_0037A168 its slot.  A task starts at ctx->ra with ctx->a[0..7]
 * (src/util/task.nostrict.c writes them); when it returns, func_001bffa0 ends its slot. */
extern Task *D_0037A16C;
extern RunQ_37a170 *D_0037A170;
extern s32 D_0037A164;
extern s32 D_0037A168;
void func_001c0460(void);

#define TK_SLOTS 400
#define TK_SAVED 1 /* ctx->ra of a slot the host saved (the EE stores the return address) */

static ucontext_t tk_uc[TK_SLOTS];
static void *tk_stack[TK_SLOTS];
static ucontext_t tk_fin_uc;
static void *tk_fin_stack;

/* the next queue entry; at the end func_001c0460 rebuilds the queue and the main loop runs */
static s32 tk_next(void) {
    s32 i = D_0037A164 + 1;
    if (D_0037A170[i].ctx == 0) {
        func_001c0460();
        i = 0;
    }
    D_0037A164 = i;
    D_0037A168 = D_0037A170[i].arg;
    return D_0037A168;
}

static void tk_entry(void);

/* into slot s: a saved one resumes, a new one starts at its entry */
static void tk_enter(s32 s, ucontext_t *save) {
    TaskCtx *c = D_0037A16C[s].ctx;
    if (c->ra.w[0] != TK_SAVED) {
        getcontext(&tk_uc[s]);
        tk_uc[s].uc_stack.ss_sp = task_stack(&tk_stack[s]);
        tk_uc[s].uc_stack.ss_size = TASK_STACK;
        tk_uc[s].uc_link = 0;
        makecontext(&tk_uc[s], tk_entry, 0);
    }
    if (save)
        swapcontext(save, &tk_uc[s]);
    else
        setcontext(&tk_uc[s]);
}

/* after a task returns, off its stack (a new task may take the same slot) */
static void tk_finish(void) {
    func_001bffa0(D_0037A168);
    tk_enter(tk_next(), 0);
}

static void tk_entry(void) {
    s32 s = D_0037A168;
    TaskCtx *c = D_0037A16C[s].ctx;
    ((void (*)(s32, s32, s32, s32, s32, s32, s32, s32))c->ra.w[0])(
        c->a[0].w[0], c->a[1].w[0], c->a[2].w[0], c->a[3].w[0],
        c->a[4].w[0], c->a[5].w[0], c->a[6].w[0], c->a[7].w[0]);
    getcontext(&tk_fin_uc);
    tk_fin_uc.uc_stack.ss_sp = task_stack(&tk_fin_stack);
    tk_fin_uc.uc_stack.ss_size = TASK_STACK;
    tk_fin_uc.uc_link = 0;
    makecontext(&tk_fin_uc, tk_finish, 0);
    setcontext(&tk_fin_uc);
}

/* func_001bfac8: the running task yields to the next in the queue */
void func_001bfac8(void) {
    s32 cur = D_0037A170[D_0037A164].arg;
    s32 s;
    D_0037A16C[cur].ctx->ra.w[0] = TK_SAVED;
    s = tk_next();
    if (s == cur)
        return;
    tk_enter(s, &tk_uc[cur]);
}

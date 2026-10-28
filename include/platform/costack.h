#ifndef PLATFORM_COSTACK_H
#define PLATFORM_COSTACK_H

#include "common.h"

/* The stacks of the game's threads and tasks, which the port runs as coroutines (host/null/threads.c,
 * host/port/tasks.c).  Session 137v: the Vita's kernel refuses a system call made with SP outside the calling
 * thread's own stack (the first disc read, from a coroutine on a malloc'd stack, stopped the app with
 * C2-12828-1 on hardware; Vita3K does not check), so the Vita hands the main thread's unused stack to
 * kh1_costack_pool and the coroutines take their stacks from it.  Elsewhere (and when the pool is used up)
 * a stack is malloc'd.  Never freed: each thread / task slot keeps its stack.  Not part of the PS2 build. */
void kh1_costack_pool(void *base, u32 size);
void *kh1_costack_alloc(u32 size);

#endif

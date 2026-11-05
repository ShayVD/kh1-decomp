#ifndef PLATFORM_COSTACK_H
#define PLATFORM_COSTACK_H

/* The stacks of the game's threads and tasks, which the port runs as coroutines (host/null/threads.c,
 * host/port/tasks.c): vita-port-kit's costack (third_party/vita-port-kit/vita/runtime/costack, vendored:
 * docs/vita-port-kit.md), under the kh1_ names the port code calls.  Session 137v: the Vita's kernel refuses a
 * system call made with SP outside the calling thread's own stack (C2-12828-1 on hardware; Vita3K does not
 * check), so host/vita/main.c hands the main thread's unused stack to kh1_costack_pool.  Not part of the PS2
 * build. */
#include "../../third_party/vita-port-kit/vita/runtime/costack/vpk_costack.h"

#define kh1_costack_pool vpk_costack_pool
#define kh1_costack_alloc vpk_costack_alloc
#define kh1_costack_stack vpk_costack_stack
#define kh1_costack_owns vpk_costack_owns

#endif

/* Stacks for coroutines (game threads or tasks run cooperatively, e.g. on vpk_ucontext).
 *
 * On the Vita the kernel refuses a system call made with SP outside the calling thread's own stack: a
 * coroutine running on a malloc'd stack stops the app at its first file read, with no log (hardware only;
 * Vita3K does not check).  So the platform hands a part of the main thread's stack it does not use to
 * vpk_costack_pool (make the main thread's stack large with sceUserMainThreadStackSize, marked used) and the
 * coroutines take their stacks from it.  Elsewhere, and once the pool is used up (said once on stdout), a
 * stack is malloc'd.  Stacks are never freed: each coroutine slot keeps its own.
 * From kh1-decomp include/platform/costack.h @ e1575e1a. */
#ifndef VPK_COSTACK_H
#define VPK_COSTACK_H

/* the pool the stacks come from (aligned up to 16 here) */
void vpk_costack_pool(void *base, unsigned int size);
/* a stack of size bytes (rounded up to 16), 16-aligned; from the pool while it lasts, then malloc'd */
void *vpk_costack_alloc(unsigned int size);
/* the whole stack the pool is part of (the Vita main thread's, its own part above the pool included) */
void vpk_costack_stack(void *base, unsigned int size);
/* nonzero when a..a+n lies in the pool or that stack (e.g. a memory check that must accept stack
 * addresses) */
int vpk_costack_owns(unsigned long a, unsigned int n);

#endif /* VPK_COSTACK_H */

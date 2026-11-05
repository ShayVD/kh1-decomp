/* The process parameters the SDK reads by name, and the main thread's stack as the coroutines' stack pool.
 *
 * vita-elf-create reads sceUserMainThreadStackSize and newlib's sbrk reads _newlib_heap_size_user; nothing in the
 * app refers to them, so without `used` LTO drops them and the app starts with the default 256 KiB main stack and
 * stops at launch (no log).  VPK_PROCESS_PARAMS defines both, used; a build should check the linked ELF still has
 * both names (vita/cmake, or the game's build script).
 *
 * The kernel refuses a system call made with SP outside the calling thread's own stack, so coroutines need their
 * stacks inside the main thread's (vita/runtime/costack): make the main stack large and hand all of it but the
 * main thread's own part to the pool with vpk_main_stack_to_costack.  A main stack of 52 MiB stopped one app at its
 * start on hardware; 16 MiB is known to work.
 * From kh1-decomp host/vita/main.c @ e1575e1a. */
#ifndef VPK_PROCPARAM_H
#define VPK_PROCPARAM_H

#define VPK_PROCESS_PARAMS(heap_bytes, main_stack_bytes) \
    __attribute__((used)) int _newlib_heap_size_user = (heap_bytes); \
    __attribute__((used)) unsigned int sceUserMainThreadStackSize = (main_stack_bytes)

/* call early on the main thread: the main stack below the caller's frame, less own_bytes for the main thread's
 * own frames, becomes the coroutines' pool (vpk_costack_pool), and the whole stack is vpk_costack_stack's; the
 * pool's size in bytes (0: no pool) */
unsigned int vpk_main_stack_to_costack(unsigned int own_bytes);

#endif /* VPK_PROCPARAM_H */

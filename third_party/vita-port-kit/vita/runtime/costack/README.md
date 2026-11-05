# costack

Stacks for coroutines. On the Vita the kernel refuses a system call made with SP outside the calling thread's own
stack, so a coroutine on a malloc'd stack stops the app at its first file read, with no log. This happens on hardware
only, because Vita3K does not check. The platform hands part of the main thread's stack to `vpk_costack_pool`, and
coroutines take their stacks from it. Make that stack large with `sceUserMainThreadStackSize`, marked
`__attribute__((used))`. When the pool runs out, stacks are malloc'd, with one line on stdout
(`vpk-costack: the coroutines' stack pool is used up ...`). Off the Vita, with no pool, every stack is malloc'd.

- `vpk_costack_pool(base, size)`, `vpk_costack_alloc(size)`: 16-aligned, rounded up to 16, never freed.
- `vpk_costack_stack(base, size)`, `vpk_costack_owns(a, n)`: whether an address range is a coroutine stack, for memory
  checks.

**From:** kh1-decomp `host/port/costack.c` and `include/platform/costack.h` @ `e1575e1a`.

**Test:** `test/costack_test.c` (any host compiler):

```bash
cc -std=c99 -Wall -I. vpk_costack.c test/costack_test.c -o costack_test && ./costack_test
```

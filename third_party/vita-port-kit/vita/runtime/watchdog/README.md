# watchdog

- `vpk_thread_start(name, entry, prio, stack, cpu_mask)` creates, starts and notes a thread.
- `vpk_thread_note(uid, name)` / `vpk_threads_line(line, size, head)`: each noted thread's CPU time since the last
  line (the kernel's run clock: time another thread took is not counted), the core it last ran on, its affinity
  mask and priority, and its preemptions. Up to 12 threads.
- `vpk_watchdog_start(name, period_us, window, user, prio, cpu_mask)`: a thread that calls `window(user)` every
  `period_us` of wall time, so the log keeps moving when the game thread hangs or the screen is black. Give it a
  priority above the busy threads (kh1-decomp: at the same priority as its GPU thread its 2 s windows stretched to
  10-40 s) and a core of its own if there is one.

**From:** kh1-decomp `host/vita/main.c` (`threads_line`, `kh1_vita_thread_note`, the watchdog's thread) @ `e1575e1a`.
kh1-decomp keeps its own watchdog loop (its window is all game counters) and uses the threads line and the thread
start.
**Test:** `../test/vita_modules_test.c` (the threads line; the loop itself is two calls).

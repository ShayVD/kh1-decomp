# ucontext

A cooperative context switch for 32-bit ARM: `getcontext`, `setcontext`, `swapcontext` and `makecontext`
(newlib on the Vita has none). Saves r4-r11, sp, lr, d8-d15 and FPSCR, so every context keeps its own rounding and
flush-to-zero mode.

- `vpk_ucontext.h` / `vpk_ucontext.S`: the `vpk_` names. They link beside glibc's, so the same objects run in a
  32-bit ARM Linux check under qemu-arm.
- `std/ucontext.h`: put `std/` on the include path and POSIX-style code (`ucontext_t`, `swapcontext` ...) uses it
  unchanged.
- Limits: `makecontext` passes no arguments to the entry; `getcontext` is only for setting up `makecontext`, not a
  resume point. An entry that returns loads `uc_link` (null: `abort()`).

**From:** kh1-decomp `host/vita/context.S` and `host/vita/include/ucontext.h` @ `e1575e1a`, in use on the Vita since
session 137v (October 2026). kh1-decomp runs its EE threads and tasks as coroutines on it.

**Test:** `test/ucontext_test.c` checks a ping-pong of two coroutines, callee-saved integer and VFP values across
switches, 8-byte stack alignment, per-context FPSCR and the `uc_link` return. Each check fails if the matching part of
the switch is removed. Run it on ARM Linux or under qemu-arm (CI does this):

```bash
arm-linux-gnueabihf-gcc -std=gnu99 -O2 -mfpu=neon -Istd vpk_ucontext.S test/ucontext_test.c -o ucontext_test
```

```bash
qemu-arm -L /usr/arm-linux-gnueabihf ./ucontext_test
```

# vita-port-kit (vendored)

Since 2026-11-05 the port takes its game-free Vita code from vita-port-kit (github.com/ShayVD/vita-port-kit,
private, MIT): a copy of only the modules used, in `third_party/vita-port-kit/`, with `VENDORED` naming the kit
commit. Do not edit those files here: change the kit, then re-vendor from a kit checkout with
`tools/vendor.sh ../kh1-decomp` (it refreshes the paths `VENDORED` lists).

| Kit module | Replaces | Used by | How it is wired |
|---|---|---|---|
| `vita/runtime/ucontext` | host/vita/context.S, host/vita/include/ucontext.h | host/null/threads.c, host/port/tasks.c on the Vita and in `make vita-armcheck` | tools/vita/build.py: `-I.../ucontext/std` (the `<ucontext.h>` those files include) and the directory in both targets' platform dirs |
| `vita/runtime/costack` | host/port/costack.c | the coroutines' stacks on every port platform (host runner, ARM Linux, Vita) | tools/host/census.py `KIT_COSTACK` in `PLATFORM_DIRS` (a platform dir under third_party/ is built from there); include/platform/costack.h maps the kh1_ names |
| `vita/runtime/procparam` | host/vita/main.c's `_newlib_heap_size_user`, `sceUserMainThreadStackSize`, the main stack handed to costack | main.c (`VPK_PROCESS_PARAMS`, `vpk_main_stack_to_costack(MAIN_OWN)`) | tools/vita/build.py: the kit's runtime dirs in the Vita target (compiled like host/vita, with the SDK's short enums) |
| `vita/runtime/log` | main.c's log_out / log_write / funopen redirect / printf, vprintf, puts | main.c (`vpk_log_open`; `kh1_vita_log` forwards to `vpk_logv`); vpk_log_stdio.c supplies printf / vprintf / puts | as above |
| `vita/runtime/config` | main.c config()'s line reader | main.c (`config_key` keeps every key) | as above |
| `vita/runtime/clocks` | main.c's clock block | main.c | as above |
| `vita/runtime/watchdog` | main.c threads_line, kh1_vita_thread_note's table | main.c (the watchdog loop itself stays: its window is all game counters) | as above |
| `vita/tools` | tools/vita/hw_run.sh, hw_ftp.py (and adds hw_check.sh, hw_mock.py), get_vitasdk.sh | tools/vita/hw_run.sh, hw_check.sh, hw_ftp.py are wrappers with this game's settings in tools/vita/hw.game | the wrappers set HW_GAME |

Visible differences: the line when the stack pool runs out starts `vpk-costack:` (was `kh1-port:`); hardware runs
now take a lock in ~/.cache/vita-port-kit (one run at a time across games and clones), fetch any new crash dump into
the run's folder, and install the whole app with vitacompanion's promote when its sce_sys/ changed.

The PS2 build does not compile `host/` or `third_party/`; it is unaffected. Which kit modules come next and the
checks each swap needs: the kit's docs/roadmap.md ("kh1-decomp consuming the kit").

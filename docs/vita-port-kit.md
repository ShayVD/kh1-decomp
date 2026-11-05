# vita-port-kit (vendored)

Since 2026-11-05 the port takes its game-free Vita code from vita-port-kit (github.com/ShayVD/vita-port-kit,
private, MIT): a copy of only the modules used, in `third_party/vita-port-kit/`, with `VENDORED` naming the kit
commit. Do not edit those files here: change the kit, then re-vendor from a kit checkout with
`tools/vendor.sh ../kh1-decomp` (it refreshes the paths `VENDORED` lists).

| Kit module | Replaces | Used by | How it is wired |
|---|---|---|---|
| `vita/runtime/ucontext` | host/vita/context.S, host/vita/include/ucontext.h | host/null/threads.c, host/port/tasks.c on the Vita and in `make vita-armcheck` | tools/vita/build.py: `-I.../ucontext/std` (the `<ucontext.h>` those files include) and the directory in both targets' platform dirs |
| `vita/runtime/costack` | host/port/costack.c | the coroutines' stacks on every port platform (host runner, ARM Linux, Vita) | tools/host/census.py `KIT_COSTACK` in `PLATFORM_DIRS` (a platform dir under third_party/ is built from there); include/platform/costack.h maps the kh1_ names |

One visible difference: the line when the stack pool runs out now starts `vpk-costack:` (was `kh1-port:`).

The PS2 build does not compile `host/` or `third_party/`; it is unaffected. Which kit modules come next and the
checks each swap needs: the kit's docs/roadmap.md ("kh1-decomp consuming the kit").

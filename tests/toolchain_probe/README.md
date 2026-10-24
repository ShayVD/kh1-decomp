The session 1 compiler probes are part of the normal build (session 56 moved
them from `src/anon/session1_probes.c` into their modules, docs/toolchain.md), so `make verify` re-checks them every time. To test
another compiler, change `toolchain.compiler` in kh1.toml, `make clean verify`.

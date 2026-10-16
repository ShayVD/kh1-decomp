The session 1 compiler probes now live in `src/anon/session1_probes.c` and are
part of the normal build, so `make verify` re-checks them every time. To test
another compiler, change `toolchain.compiler` in kh1.toml, `make clean verify`.

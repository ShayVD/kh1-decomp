# log

The app's log file, one `sceIoWrite` per line, unbuffered and timed (`vpk_log_us`, `vpk_log_writes` for a watchdog
line). `vpk_log_open(path, first_line)` removes the old file first (Vita3K's open kept the last run's tail without
truncating) and points stdout / stderr at the log through a `funopen` FILE. Link `vpk_log_stdio.c` too and
`printf` / `vprintf` / `puts` write straight to the log: newlib's own fopen'd log stayed empty in Vita3K, and
pointing newlib's stdout at a file reached neither its global nor its per-thread stream.

`vpk_log(fmt, ...)` / `vpk_logv` format up to 4,607 bytes a call (room for a shader's text).

**From:** kh1-decomp `host/vita/main.c` (`log_out`, `log_write`, `kh1_vita_log`, its printf / vprintf / puts) @
`e1575e1a`.
**Test:** `../test/vita_modules_test.c` against fake SDK calls (`../test/run_host_tests.sh`); CI also compiles it
with vitasdk.

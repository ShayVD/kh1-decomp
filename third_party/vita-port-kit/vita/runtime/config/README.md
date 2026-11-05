# config

`config.txt` in the app's data folder as `key=value` lines: `vpk_config_read(path, fn, user)` calls `fn(key, value,
user)` for each. `#` lines and lines without `=` are skipped; the value loses trailing newline, CR and spaces; the
key is not trimmed. Pure stdio, so the same code runs on a host build.

**From:** kh1-decomp `host/vita/main.c` `config()` @ `e1575e1a` (its loop; the keys stay the game's).
**Test:** `test/config_test.c` (`../test/run_host_tests.sh`).

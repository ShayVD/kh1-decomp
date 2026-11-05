# clocks

`vpk_clocks_set(VPK_CLOCKS_MAX, &got)` sets ARM 444, bus 222, GPU 222 and GPU crossbar 166 MHz (an app starts at
333) and reads back what the Vita accepted, plus the ARM clock before, for the log. Vita3K takes the calls and runs as
fast either way.

**From:** kh1-decomp `host/vita/main.c` @ `e1575e1a`.
**Test:** `../test/vita_modules_test.c`.

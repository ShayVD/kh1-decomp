# Session 139 near misses

| Function | Words off | Draft | Notes |
|---|---|---|---|
| xl_limit func_00f20ff0 | 2 | xl_limit_func_00f20ff0.c | the limit set-up for case 3 of func_00f20000 (siblings func_00f21d90 / func_00f21428 are matched). The store order and `D_00F23488 = D_00F2348C = 0` came from a store-order search and decomp-permuter; left: `lui` / `lw` of D_00F23208 before func_00148968 use v0 where the original uses v1. Test: `KH1_OVL=xl_limit python3 tools/autodecomp.py try func_00f20ff0 --file <draft copied into ovl/xl_limit/hand/> --out-dir ovl/xl_limit/hand --diff` (needs out/overlays/xl_limit.x from the disc). |

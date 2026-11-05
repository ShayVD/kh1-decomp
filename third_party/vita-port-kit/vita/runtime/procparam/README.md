# procparam

- `VPK_PROCESS_PARAMS(heap_bytes, main_stack_bytes);` defines `_newlib_heap_size_user` and
  `sceUserMainThreadStackSize`, both `used`: the SDK reads them by name and LTO otherwise drops them (the app then
  starts with a 256 KiB main stack and stops at launch with no log). Check the linked ELF still defines both (`vita/tools/vpk_pack.py` and `vita/cmake/VpkApp.cmake` refuse to pack it otherwise).
- `vpk_main_stack_to_costack(own_bytes)`: early on the main thread, hands the main stack below the caller, less
  `own_bytes`, to `vita/runtime/costack` as the coroutines' pool (the kernel refuses system calls from a stack that is
  not the thread's own). kh1-decomp: 16 MiB main stack, 4 MiB own; a 52 MiB main stack stopped the app at start on
  hardware.

**From:** kh1-decomp `host/vita/main.c` @ `e1575e1a`. Needs `costack`.
**Test:** `../test/vita_modules_test.c` (the pool from a fake thread info).

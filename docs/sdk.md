# SCE SDK functions (sdk segment, 0x0024F2E0-0x00272C70)

Session 2. Names come only from evidence in the user's own ELF; nothing is
copied from Sony's SDK. They live in `functions.tsv` with the evidence in the
third column, so game code can call them by name. `tools/sdk_names.py`
regenerates the automatic part; review its output before pasting it in.

## How functions are identified

1. **EE kernel syscall stubs** (`li $v1,N; syscall; jr $ra; nop`, 16 bytes,
   back to back from about `0x00257E00`). The syscall numbers and names follow
   the public ps2sdk kernel documentation. Negative numbers are the
   interrupt-context `i…` variants. When the same number appears twice in the
   stub table the second stub is the `…2` variant (`AddIntcHandler2`,
   `AddDmacHandler2`). Later functions that *start* with a syscall (e.g. at
   `0x0025F600`, number `0x74`) are libkernl setup code using inline
   syscalls, not stubs, and are left unnamed. Numbers not in the table
   (`0x0C`-`0x0F`, `0xFC`, `0xFD`, `0x56`, `0x5A`, `0x5B`, `0x80`, `0x82`) stay
   unnamed until confirmed.
2. **Error-string prefixes.** SCE libraries print messages that begin with
   the function's own name (`"sceGsSyncPath: DMA Ch.1 does not terminate"`).
   A function that references exactly one such prefix, and is the only
   function that does, is named after it. This names most of libgraph and
   libdbc.
3. **Hand entries** (marked `hand` in functions.tsv) from unambiguous strings:
   `__assert`, `sceDbcInit`, `sceCdInit`, `sceCdSearchFile`, `sceCdDiskReady`,
   `sceCdRead`, `sceMcInit`, and the SIF RPC calls `sceSifInitRpc`,
   `sceSifBindRpc`, `sceSifCallRpc` (from their call sites in the libdbc,
   libmc and libcdvd init functions: `(client, 0x800009xx, 0)` is a bind).

The layout scan was missing most stubs (they have no prologue and are only
reached by tail calls); `make layout` now splits them out (92 new entries).

## Library map (approximate, from version banners and strings)

| Range | Library | Notes |
|---|---|---|
| `0x0024F2E0`- | libc | `__assert`; printf family at `0x002516B8`/`0x002524A0` (which is which not confirmed); `0x002541B8` float formatting. |
| `0x00257E00`-`0x002585E0` | libkernl | syscall stub table |
| `0x00258F08` | libkernl/deci2 | TTY over DECI2 (`"TTY: packet size larger than expect"`) |
| `0x0025F228`-`0x00260B00` | libkernl | `rom0:UDNL` reboot, TLB setup, `## internel error in libkernl.a!` |
| `0x00261060`-`0x00262CB0` | libgcc2 | `__muldi3`, 64-bit divide family, `__fixunsdfdi`/`__fixunssfdi` |
| `0x00262CB0`-`0x00263748`, `0x00264C38`-`0x002650E0` | libgcc fp-bit | soft-float double (the EE FPU is single precision only) |
| `0x002636A8`-`0x00264C38` | libgcc frame.c (probably) | ULEB128/SLEB128 readers, sema-locked object list, `malloc`/`free`/`abort`; unnamed |
| `0x00265558`-`0x00266380` | libgraph | `rom0:ROMVER`, `sceGs*` |
| `0x00266AB0`-`0x00266B20` | libdma | `"libdma: sync timeout"` (two sync functions) |
| `0x00268098`-`0x00268988` | libdbc | `sceDbc*` |
| `0x00268AA0`-`0x002692F4` | libpad2 | `scePad2*` |
| `0x002692F8`-`0x00269464` | libvib | `sceVib*` |
| `0x002695F8`-`0x0026AD5C` | libcdvd | `sceCd*` |
| `0x0026AD60`-`0x00270AD4` | libm (newlib, fdlibm) | double and float math; no banner, no strings |
| `0x00270AD8`-`0x00270B5C` | libpc | `scePcStart`/`scePcStop` |
| `0x00270B60` | libmc | `sceMcInit` |

### Session 3 additions (behaviour, not strings)

The libc is **newlib** (SCE's EE build): `D_0046A9C8` is `_impure_ptr`
(`struct _reent *`; `+0x8` is `_stdout`, `+0xA8` `_rand_next`, `+0x148`
`_atexit`). The string/memory functions are the EE-optimised ones (128-bit
`lq`/`sq` and MMI zero-byte tests), so they are `hard` and stay
unmatched. Named by what they do and how they are called:

| Function | Address | Evidence (short) |
|---|---|---|
| `exit`, `abort`, `raise`, `_raise_r` | `0x0024F3E8`, `0x00253F70`, `0x00257810`, `0x002576A0` | atexit walk + `_exit`; `raise(6)` + `_exit(1)`; `_raise_r(_impure_ptr, sig)` |
| `malloc`, `free`, `__malloc_lock`, `__malloc_unlock` | `0x0024F4F0`, `0x0024F548`, `0x00250118`, `0x00250198` | lock (thread id + count + sema) around the allocator / release routine |
| `memcmp`, `memcpy`, `memset` | `0x0024FF10`, `0x0024FFA4`, `0x00250054` | (a, b, n) / (dst, src, n) returns dst / (dst, c, n) with `pcpyld`/`pcpyh` splat |
| `strlen`, `strcpy`, `strcmp`, `strncmp`, `strcat` | `0x002512C4`, `0x002511B0`, `0x0025106C`, `0x00251400`, `0x00250F40` | 0x0101…/0x8080… zero-byte tests; `strcat` = find end + `strcpy` |
| `printf`, `puts`, `_puts_r` | `0x00250248`, `0x00250340`, `0x002502B8` | `vfprintf(stdout, …)`; `_puts_r` writes {s, "\n"} and returns 10 / -1 |
| `sprintf`, `_sprintf_r`, `vsprintf`, `_vsprintf_r`, `vfprintf` | `0x00250EB0`, `0x00250E28`, `0x00253DB0`, `0x00253E08`, `0x00252428` | string FILE (flags `0x208`, size `0x7FFFFFFF`) passed to `vfprintf` |
| `srand`, `rand` | `0x00250D50`, `0x00250D68` | newlib LCG `0x5851F42D4C957F2D`, `(next >> 32) & 0x7FFFFFFF` |
| `__muldi3` | `0x00261060` | libgcc 64-bit multiply |
| `scePrintf` | `0x00259CC0` | libkernl: swaps in the DECI2 TTY writer (`0x002593B8`) around the format engine (`0x00259698`); every SDK error message goes through it. `0x00259C88` is the same without the swap (unnamed). |
| `scePad2Init`, `scePad2End`, `scePad2CreateSocket`, `scePad2DeleteSocket`, `scePad2StateIntToStr` | `0x00268AA0`-`0x002692C0` | libpad2 sits right after libdbc and is built on it: init clears 16 socket slots of 0x330 bytes; create/delete are the only callers of `sceDbcCreateSocket`/`DeleteSocket`; StateIntToStr copies one of 4 strings |
| `sceVibGetProfile`, `sceVibSetActParam` | `0x002692F8`, `0x00269378` | libvib: (socket, profile) receive; 5-argument send via `sceDbcSendData2` |
| `scePcStart`, `scePcStop` | `0x00270AD8`, `0x00270B40` | libpc: `mtps`/`mtpc` under `eret`; clear PCCR.CTE |
| `sceIpuInit`, `sceIpuSync` | `0x002727A0`, `0x002726D0` | libipu: IPU reset, BCLR, SETIQ/SETVQ/SETTH; mode 0 waits on IPU_CTRL.BUSY, mode 1 polls |

### Session 4 additions

**The block `0x0026AD60`-`0x00270AD4` is newlib's libm** (fdlibm code), not
an SCE library: no strings, no RPC binds, no syscalls; just IEEE-754 bit
tests on the high word and fdlibm's well-known constants (pi/4 high word
`0x3FE921FB`, float pi/4 `0x3F490FDA`, `1e30` = `0x7149F2C9`, `0.975` =
`0x3F799999`). The double functions do their arithmetic through libgcc's
soft-float routines; the float ones use the FPU. The float code uses
newlib's no-denormal macros (`y` below `0x00800000` counts as zero in
`fmodf`). Objects are in archive order (`s_*`, `sf_*`, `w_*`, `e_*`, `ef_*`,
`k_*`, `kf_*`, then `s_floor`...): the 20-byte `w_*` wrappers only tail-jump
to `__ieee754_*`, which is how the public names are tied to the internals.
Named: the public functions `atan ceil cos fabs nan sin cosf sinf tanf asin
atan2 sqrt acosf asinf atan2f fmodf powf sqrtf floor scalbn atanf fabsf
floorf scalbnf copysign copysignf`, and the internals `__ieee754_*` (atan2,
rem_pio2, sqrt, acosf, asinf, atan2f, fmodf, powf, rem_pio2f, sqrtf) and
`__kernel_*` (cos, sin, rem_pio2, cosf, sinf, tanf, rem_pio2f). Evidence per
function is in functions.tsv. `__ieee754_asin` (`0x0026BA08`) used to be merged
into the `sqrtf` wrapper; the session 4 layout fix (tail calls end functions)
split it.

**`0x00262F50`-`0x002634E0` (what libm calls) is gcc's soft-float `fp-bit`**
in libgcc. Every routine unpacks its operands with `__unpack_d`
(`0x00264E48`) into a {class, sign, exp, frac} struct and repacks with
`__pack_d` (`0x00264D70`). `__adddf3`/`__subdf3` share the static add-parts
routine at `0x00262CF0`; `__muldf3` uses `__muldi3`; `__cmpdf2` is the only
compare linked and returns `__fpcmp_parts_d` unchecked (game code branches
on it with `bltz`/`blez`). Also named: `__floatsidf`, `__fixdfsi`,
`__fixunsdfsi`, `__extendsfdf2` (112 game callers), `__truncdfsf2` (61),
`__make_dp`, `__make_fp`, `__pack_f`, `__unpack_f`, and from libgcc2
`__floatdidf`, `__fixunsdfdi`, `__fixunssfdi` and the divide family
`__divdi3`/`__moddi3`/`__udivdi3`/`__umoddi3` (signed ones negate their
operands; the `mod` ones keep a remainder slot on the stack). The game code
uses doubles (`(int)ceil((double)(a*b))` at `0x001E03F0`), so these are
real dependencies of decompiled code, not dead weight.

**libpad2** (from the one game caller, the pad loop in `func_0011f668`, and the
16 x 0x330-byte socket table at `0x00670040`):

| Function | Address | Evidence (short) |
|---|---|---|
| `scePad2GetState` | `0x00268EB0` | (socket); returns byte 0 of the newer DMA buffer, or asks the device via `sceDbcReceiveData`; the game continues only when it is 1 (`"STABLE"` in `scePad2StateIntToStr`'s table: NOLINK, STABLE, EXECCMD, ERROR) |
| `scePad2GetButtonProfile` | `0x00268DC0` | (socket, profile); `sceDbcReceiveData` into the caller's 4-byte buffer, then rebuilds the slot's 40-entry button table from the bitmap; called right after GetState |
| `scePad2Read` | `0x00268CE8` | (socket, buf); copies the newer of the two 128-byte buffers (counter at `+124`), returns the length byte; the game reads digital buttons from `buf[0..1]`, active low |

Not named yet: `0x00268FF0` (socket, data, button) reads one button out of
the read data using the 40-entry table (bit or 8-bit analog): probably
`scePad2GetButtonInfo`, but nothing calls it. libpad2's statics:
`0x002690D0` caches `sceDbcGetDepNumber`, `0x00269128` picks the newer
buffer, `0x00269190` detects a buffer change, `0x00269210` parses a
profile bitmap. libgcc `frame.c` (probably, `0x002636A8`-`0x00264C38`),
libipu's DMA helpers (`0x002723C8`-`0x00272580`, `0x00272580` restarts IPU
DMA from a saved env, likely `sceIpuRestartDMA`), the newlib internals
(`_malloc_r` `0x0024F7E8`, `_free_r` `0x002557D8`, `_vfprintf_r`
`0x002524A0`, `_dtoa_r` `0x002541B8`, `__sfvwrite` `0x00255C40`).
`func_00268a78` is called in libdbc's bind retry loop: it only adjusts the
stack and returns (an empty varargs function, probably a disabled debug
print).

### Session 5: matching the SDK

395 of 722 SDK functions match. Where they live:

| Directory | What | Flags (kh1.toml overrides) |
|---|---|---|
| `src/sdk/libm/` | newlib libm, all 44 | `-fno-builtin`, no_fill |
| `src/sdk/libgcc/` | fp-bit (`dp-bit.c`, normal filling) and libgcc2 `_*.c` objects | `_*.c`: no_fill |
| `src/sdk/libkernl/syscall.s` | the 162 syscall stubs, as assembly | |
| `src/sdk/libc/` | newlib libc by hand | `-fno-builtin`, no_fill |
| `src/sdk/auto/`, `src/sdk/gcc991111/` | autodecomp matches (57 with 2.96, 48 more with ee-gcc 2.9-991111a) | per directory |
| `nonmatchings/sdk_*.c` | `__muldf3`, `__divdf3`, `__pack_f`, `d2b` | one word off each |

**Compiler.** The SCE libraries were built with ee-gcc 2.9-991111 (a fact
from the ethteck/kh1 notes; nothing else is taken from that repository,
which has no license): `src/sdk/gcc991111/` matched 48 functions 2.96 could
not. newlib (libc, libm, libgcc) matches with 2.96 plus **no_fill**: its
assembler never filled a branch delay slot with an instruction from before
the branch (`jal x; nop`), which `no_fill()` in tools/kh1tool.py reproduces on the
compiler's output (docs/toolchain.md).

**libgcc2.** Each of `__divdi3`/`__moddi3`/`__udivdi3`/`__umoddi3` is its
own object that inlines `__udivmoddi4` and carries a private `__clz_tab`
copy (`D_00492430`/`530`/`630`/`730`; each file sets `CLZ_TAB`). longlong.h
is the 32-bit one (`__ll_B` is `(USItype) 1 << 16`; a 64-bit shift gives
`dsll32`). `__muldf3`, `__divdf3` and `__pack_f` differ from the original
by one branch-likely choice that no flag or compiler tried reproduces.

**newlib libc details that matter for matching:**
- `abort` is `while (1) { raise(6); _exit(1); }`, not noreturn (`__assert`
  sibcalls it); `rand` reads `_REENT` once into a local.
- This newlib's `CHECK_INIT` sets `fp->_data` (from `_REENT`) before
  testing `__sdidinit`; `__sfvwrite` has no `nldist = 0`.
- dlmalloc: `MALLOC_ALIGNMENT` 16, the extra `next_bin` step for
  `idx < MAX_SMALLBIN`, `long_sub_size_t`, `idx2binblock` as an unsigned
  long shift. `sbrked_mem` must be `current_mallinfo.arena` (a struct
  field; as a plain int gcc reorders its stores). `_sbrk_r` takes an int.
  State: `av_` `D_0046A9D0`, `trim_threshold` `D_0046ADD8`, `top_pad`
  `D_0046ADE0`, `sbrk_base` `D_0046ADE8`, `max_sbrked_mem` `D_0046ADF0`,
  `max_total_mem` `D_0046ADF8`, `current_mallinfo` `D_0046AE00`.
  `_calloc_r` is a separate object (MALLOC_ZERO unrolled).
- The low-level `_read`/`_write` return int; `_read_r`/`_write_r` widen to
  long. errno is `D_00494028`.
- `struct _reent` offsets (src/sdk/libc/reent.h): `_stdout` 8, `_stderr`
  12, `__sdidinit` 0x38, `__cleanup` 0x3C, mprec's `_result` 0x40 /
  `_result_k` 0x44 / `_p5s` 0x48 / `_freelist` 0x4C, `_cvtlen` 0x50,
  `_cvtbuf` 0x54, `_rand_next` 0xA8, `_atexit` 0x148, `_atexit0` 0x14C,
  `_sig_func` 0x1D4, `__sglue` 0x1D8, `__sf[3]` 0x1E4 (88-byte FILEs,
  `_data` at 84).
- EE varargs: `__builtin_va_list` with `__builtin_stdarg_start`
  (src/sdk/libc/stdarg.h); `long` is 64-bit.
- String literals the C references are `D_` externs (`"C"` `D_00491FC8`,
  `"\n"` `D_00491B28`...), declared in the .c file: the build only resolves
  `D_` names it finds in .c files.

The MMI string functions (`memcmp`, `memcpy`, `memset`, `strcat`,
`strcmp`, `strcpy`, `strlen`, `strncmp`, `memchr`, `memmove`) are
assembly in src/sdk/libc/string.s (tools/asm_export.py): six of them start
4 bytes off the 8-byte alignment gcc gives every function, so the
originals were `.s` files. `_dtoa_r` and `quorem` are matched in C.

Left in libc: `_vfprintf_r`, `_vfiprintf_r`, `d2b`.

## Porting note

None of these are ported. The Vita layer replaces each library behind the
`include/platform/` wrappers (docs/portability.md).

## Session 5: libkernl SIF RPC and file I/O (0x2594a0-0x260000)

- Built with ee-gcc 2.9-991111a, -O2 -G0, normal delay-slot fill (src/sdk/gcc991111/).
- 991111 sibcalls only void calls whose result is unused, frameless (`lui; j f; lw`). `return f(x)` uses jal plus a frame.
- 991111 pads loops under 6 instructions with nops. The SDK delay loop `i = 0x100000; do i--; while (i != -1);` is plain C.
- 991111 has no `__builtin_va_list`. Use `typedef char *va_list;` and `va_start(v,l)` as `v = (char *)__builtin_next_arg(l) - 8*(8 - __builtin_args_info(2))`; an int va_arg is `*(int *)ap`.
- Store and load order follows type-based aliasing. sceSifSetDma descriptors must be all-word structs `{u32 src, dest; int size, attr;}`. RPC client and packet fields must be words with an int sema.
- An inlined GetThreadId (`li $3,-47; syscall`) appears in func_0025fd10 and func_0025fe28. It is written as a two-instruction asm statement.
- File I/O request block at D_0066C780: `{sema, int *res, size, args}`, with args from +12. Commands seen:
  - 0 open: send size 1048.
  - 2 read: 32.
  - 4 lseek: 28.
  - 13 chstat: i+81.
  - 14 mount: 3088.
  - 17 two-name: 2060.
  - 20 mount with flag: 3092.
  - 22 64-bit lseek: 32.
  - 23 devctl: 2076.
  - 24 two-name: 2060.
  - 25 name + buffer: 2060.
  - 26 ioctl2-like: 1056.
- File mode bit 0x8000 is nowait: the semaphore goes into the 32-entry table D_0046AE58 and `-sema` is sent. Handler func_0025add8 (cmd 0x80000011) signals it. Bit 0x20000000 skips the read-buffer flush.
- sceSifInitRpc registers handlers 0x80000008/9/a/c. The file I/O init (func_0025b2f0) registers 0x80000011 and 0x80000013, binds 0x80000001 into D_0066DA40 and asks fno 255 for the version.
- Hand-written asm left out: func_00258c30 (mfc0), func_0025b2c0 (sync/ei), DIntr.
- func_0025ac40 and func_0025fb60 end in an infinite loop whose delay-slot nop fills the 4-byte gap after them. Their layout entries now include it.

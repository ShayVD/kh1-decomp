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

## Session 5: libpad2/libvib/libdbc/libmc/libcdvd/libdma/libgraph and libgcc (0x260000-0x272c70)

- Most of this range matches with ee-gcc 2.9-991111a (src/sdk/gcc991111/text_00260000_s2.c, 103 functions).
- The libvu0 view-screen matrix func_00267b08 needs **ee-gcc 2.9-991111-01** (src/sdk/gcc991111_01/), which puts `nop; nop` before div.s. All the 991111a matches tried also match under 991111-01, so it may be the true SDK compiler.
- libgcc frame.c's register_frame_info (0x263db8) and register_frame_info_table (0x263e50) need 2.96 with -fno-strict-aliasing (src/sdk/nostrict/). Also from frame.c: 00263ee8 deregister, 00263fc8 count_fdes, 00264008 add_fdes, 00264098 search_fdes, 002640f0 init_object, 00264400 extract_cie_info, 00264630 execute_cfa_insn, 00264a80 frame_state_for, 00264258 find_fde.
- Other names:
  - 00262b28 __do_global_dtors and 00262bb8 __do_global_ctors.
  - 002650e0 atexit, 002729d8 atoi, 00272c38 strtol.
  - 002715a0 sceMcSync, 00271860 sceMcUdCheckNewCard.
  - Syscall 13 SetVTLBRefillHandler, 14 SetVCommonHandler, 0xFC SetAlarm.
- libmc keeps its RPC numbers in D_0046E090. The file-name buffer D_006736B0 is 1044 bytes with the name at +20. Versions required: mcserv >= 522, mcman >= 526.
- libdbc RPC numbers: 0x900 bind, 0x903 depnumber, 0x918 SRData, 0x91b SendData2. The device table is D_00670000.
- libpad2 passes the command word as a sign-extended s32. libvib passes a 64-bit bitfield struct.
- libcdvd locks:
  - N command: semaphore D_0046C628, RPC 0x80000595.
  - S command: semaphore D_0046C62C, RPC 0x80000593.
  - sceCdDiskReady uses RPC 0x8000059a.
- Hand-written asm left out:
  - scePcStart/scePcStop (COP0).
  - func_002654f0 (VU0 cfc2/ctc2).
  - func_00260738 (a cache loop).
  - func_002607e4 (a lone `jr ra`; the layout now gives it 4 bytes and func_002607e8 the rest).
  - func_00265190 (strncpy using MMI).
- 991111 shapes: declare the byte-copy destination pointer inside the loop body; busy-wait is `i = 0x10000; while (--i != -1);`.

## Session 6

- libgcc frame.c (unwind, 0x263840-0x264258) matches in src/sdk/auto
  (2.96, strict, fill). `__muldf3`/`__divdf3` match once `__pack_d` is not
  defined in the same file: the session-5 branch-likely mismatch was the
  callee-above effect from dp-bit.c. `__pack_f` needs
  `normal_exp >= EXPBIAS + 2`.
- newlib `_vfprintf_r` (0x2524a0) and `_vfiprintf_r` are newlib 1.8-era,
  built with FLOATING_POINT and `_NO_LONGLONG`; they keep the precedence
  bug `_double || flags & ALT == 0`. strtol (0x272a00) is 2.96 with fill.
- ee-gcc 991111: struct store order follows alias sets (declare SIF struct
  fields all u32/int); reorg never puts a volatile load in a delay slot;
  sceGsSyncPath's cfc2 result needs `register u32 r asm("$6")`.
- libkernl tty registers are volatile. libcdvd: scePrintf/sceSifInitRpc
  return void; D_0046C624-D_0046C654 are often volatile.
- Hand-written asm, not C: func_00260738 (cache loop + sync),
  func_002607e4 (lone `jr ra`), func_00265190 (MMI strncpy),
  func_002654f0 (VU0 cfc2/ctc2), func_00260b00 (t9 live across
  calls). DIntr was matched as C in session 10 (below). scePcStart/scePcStop are in src/sdk/libpc.s.

## Session 7

- Hand-written asm exported: src/sdk/libkernl_asm.s (func_00260738 cache loop,
  func_002607e4, func_00265190 MMI strncpy, func_002654f0 VU0 cfc2/ctc2, DIntr,
  func_00260b00) and src/sdk/libkernl_exc.s (func_00260d00, the exception
  trampoline: sq of every GPR through $k0, mfhi1/mflo1/mfsa, cop0, eret).
- libvu0 shadow matrix func_00267c10 matches in sdk/gcc991111_01 once nx, ny, nz
  and d are declared separately in each branch (block-local pseudos).
- sceGsExecStoreImage (0x266380) needs sdk/gcc991111_as296 (991111a's reorg never
  puts a volatile store in a delay slot; 2.96 gas fills it): 12 words off, a
  buf/rest s5/s6 swap (nonmatchings/session7/w6__00266380_12w.c).
- libcdvd 0x2695f8, sceCdRead 0x26a7f0 and 0x2698c8 match byte for byte only with
  an empty `__asm__ volatile("")` between two global stores (not accepted; kept as
  nonmatchings/session7/w4__*_asmbarrier.c). The original probably had a real
  side effect there.
- `int SignalSema(int)` / `void scePrintf` prototypes change v0 use after the call.

## Session 10

- DIntr (0x25f338) is C, not asm: the shape of the DIntr copy inlined into `_sbrk`
  (src/sdk/libkernl/kernl.c): `eie &= 0x10000; if (eie) { do { di; sync.p; mfc0 t; t &= 0x10000; }
  while (t); } return eie != 0;` with no separate result local (src/sdk/gcc991111_as296/
  text_00250000_s10_w1.c). Its .s stand-in was removed from src/sdk/libkernl_asm.s.
- func_0025b2f0 (file I/O init): D_0066DAC0 is the `{ void (*func)(int); int arg; }` Hook that
  func_0025b2c0 takes; with that type the two field stores get different alias sets and the
  prologue save order matches (src/sdk/gcc991111/text_00250000_s10_w6.c).

## Session 44: libmc

libmc's calls are named in functions.tsv from the mcserv RPC number each passes to sceSifCallRpc (the
`li $a1,N` before the call), the last-command number it stores in D_0046E090 for sceMcSync, and its arguments
(src/sdk/gcc991111/text_00260000_s2.c already had their bodies matched):

| address | name | evidence |
|---|---|---|
| 0x00270e40 | sceMcGetSlotMax | RPC 21, waits and returns the answer (port) |
| 0x00270f00 | sceMcOpen | RPC 2 (port, slot, name, mode); the game opens with 1, 2, 0x203 |
| 0x00271038 | sceMcMkdir | sceMcOpen(port, slot, name, 0x40) |
| 0x00271070 | sceMcClose | RPC 3 (fd) |
| 0x00271290 | sceMcRead | RPC 5 (fd, buf, size) |
| 0x002713b0 | sceMcWrite | RPC 6 (fd, buf, size), FlushCache first |
| 0x002715a0 | sceMcSync | no RPC (mode, cmd, result); session 5 named it in this file |
| 0x002716d8 | sceMcGetInfo | RPC 1 (port, slot, type, free, format) |
| 0x002718d0 | sceMcGetDir | RPC 13 (port, slot, name, mode, maxent, table) |
| 0x00271ab0 | sceMcChdir | RPC 12 (port, slot, name, current) |
| 0x00271c00 | sceMcFormat | RPC 16 (port, slot) |
| 0x00271cc8 | sceMcDelete | RPC 15 (port, slot, name) |
| 0x00272080 | sceMcRename | RPC 14 (set file info) with valid 0x10 and last command 19 (port, slot, name, new name) |
| 0x002721e8 | sceMcUnformat | RPC 17 (port, slot) |

func_00270d88 (RPC 20, one argument; most likely sceMcChangeThreadPriority) and func_002722b0 are not
called by the game and keep their placeholder names. include/sce/libmc.h has the public signatures and
include/platform/mc.h the PlatMc wrappers (docs/portability.md).


## Session 45: libvu0

libvu0's functions are named in functions.tsv (39 names; sceVu0MulMatrix, sceVu0CopyMatrix and sceVu0UnitMatrix were
named before) from their code: each is the routine its VU0 macro instructions compute, in the order the public
libvu0 lists them (ApplyMatrix, MulMatrix, OuterProduct ... ClipAll), with the unnamed gaps filled by that order and
checked against the code.  The SDK definitions (src/sdk/libvu0/vu0.s, src/sdk/gcc991111*/) take the names; game
code still calls the func_ names, which the normal build PROVIDEs and the shift link aliases (shift_ld.py), so
callers can switch one file at a time.

| address | name | evidence |
|---|---|---|
| 0x002672f8 | sceVu0ApplyMatrix | v0 = m0 x v1 (lqc2 the matrix, vmula/vmadd) |
| 0x00267370 | sceVu0OuterProduct | vopmula / vopmsub, w cleared |
| 0x00267390 | sceVu0InnerProduct | vmul.xyz, x+y+z returned in f0 |
| 0x002673b8 | sceVu0Normalize | vrsqrt of the sum of squares (c2 0x503bd), xyz scaled |
| 0x002673f8 | sceVu0TransposeMatrix | pextlw / pextuw / pcpyld / pcpyud of four rows |
| 0x00267440 | sceVu0InversMatrix | transpose of the rotation, -translation (rigid inverse) |
| 0x002674b0 | sceVu0DivVector | vdiv Q = 1 / f12, xyzw scaled |
| 0x002674d0 | sceVu0DivVectorXYZ | vdiv Q = 1 / f12, xyz scaled |
| 0x002674f0 | sceVu0InterVector | v1 * t + v2 * (1 - t), xyzw |
| 0x00267518 | sceVu0AddVector | vadd.xyzw |
| 0x00267530 | sceVu0SubVector | vsub.xyzw |
| 0x00267548 | sceVu0MulVector | vmul.xyzw |
| 0x00267560 | sceVu0ScaleVector | vmulx.xyzw by f12 |
| 0x00267578 | sceVu0TransMatrix | copy m1, row 3 += v |
| 0x002675a8 | sceVu0CopyVector | one lq / sq |
| 0x002675e0 | sceVu0FTOI4Vector | vftoi4 |
| 0x002675f0 | sceVu0FTOI0Vector | vftoi0 |
| 0x00267600 | sceVu0ITOF4Vector | vitof4 |
| 0x00267610 | sceVu0ITOF0Vector | vitof0 |
| 0x00267648 | _sceVu0ecossin | the sine / cosine series the rotations call (D_0046C580 coefficients) |
| 0x002676c0 | sceVu0RotMatrixZ | pi/2 - angle into _sceVu0ecossin, rotates the x / y rows |
| 0x00267768 | sceVu0RotMatrixX | the y / z rows |
| 0x00267810 | sceVu0RotMatrixY | the x / z rows |
| 0x002678b8 | sceVu0RotMatrix | RotMatrixZ (rot[2]), RotMatrixY (rot[1]), RotMatrixX (rot[0]) |
| 0x00267908 | sceVu0ClampVector | vmaxx / vminix by f12 / f13 |
| 0x00267930 | sceVu0CameraMatrix | unit, outer products of z and y, normalized, transposed, translated by -p |
| 0x002679e0 | sceVu0NormalLightMatrix | three light directions scaled by -1 and normalized |
| 0x00267aa0 | sceVu0LightColorMatrix | four CopyVector calls (c0, c1, c2, ambient) |
| 0x00267b08 | sceVu0ViewScreenMatrix | the screen distance, aspect and depth range in f12-f19 and a stack float |
| 0x00267c10 | sceVu0DropShadowMatrix | light vector and plane (a, b, c, d), two modes |
| 0x00267da0 | sceVu0RotTransPersN | n vertices: m x v, divide by w, vftoi4 (mode: z / w by vftoi0) |
| 0x00267df8 | sceVu0RotTransPers | the same for one vertex |
| 0x00267e40 | sceVu0CopyVectorXYZ | three lwc1 / swc1 |
| 0x00267e60 | sceVu0InterVectorXYZ | InterVector with v1's w kept |
| 0x00267e90 | sceVu0ScaleVectorXYZ | vmulx.xyz by f12 |
| 0x00267ea8 | sceVu0ClipScreen | one vertex against (0, 0) and (4096, 4096) through the clip flags (vi16 & 0xc0) |
| 0x00267ef0 | sceVu0ClipScreen3 | three vertices, the same flags |
| 0x00267f50 | sceVu0ClipAll | near / far plane clip of a vertex list (min, max, matrix, list, n) |
| 0x00267fe0 | sceVpu0Reset | VIF0 registers (0x10003810 ... 0x10003830), FBRST bit 1, VIF0 FIFO |

func_00268040 after it is not libvu0 (sceSifCallRpc 0x80000963: another library's RPC) and keeps its placeholder.
The game uses them through the menu models' camera (src/menu/mdlcam.c), the draw list and the batch senders
(src/gfx/), and about 300 other call sites; a `Plat` vector maths header (docs/portability.md rule 4) can wrap them
by these names.

## Session 56: libdma, the rest of libgraph, and what the game still calls unwrapped

Named from their code, in the library order (functions.tsv; the SDK definitions in src/sdk take the names,
game files call the include/platform/ wrappers):

| address | name | evidence |
|---|---|---|
| 0x00265350 | sceGsResetGraph | (mode, inter, omode, ffmd) as shorts; dispenv.c / display.c call (1, 1, 2, 0) / (0, 1, 2, 0) |
| 0x002654e0 | sceGsGetGParam | returns the static GParam D_0046C500 |
| 0x002654f0 | sceGsResetPath | VIF1 FBRST, VU1 reset through vi28 (cfc2 / ctc2), GIF reset (asm, libkernl_asm.s) |
| 0x00265980 | sceGsPutDispEnv | PMODE, SMODE2, DISPFB, DISPLAY, BGCOLOR to 0x12000000 |
| 0x00265b28 | sceGsSyncV | the vsync wait; returns the field (CSR bit 13) when interlaced |
| 0x002660c0 | sceGsSetDefStoreImage | the store packet, TRXDIR 1 (between SetDefLoadImage and ExecLoadImage) |
| 0x00266c08 | sceDmaGetChan | D_0046C550[id] for id < 10 |
| 0x00266c30 | sceDmaReset | D_CTRL saved, channel registers cleared, D_STAT reset, a zero env put |
| 0x00266d10 | sceDmaPutEnv | field checks (-1 ... ), D_CTRL / D_PCR / D_SQWC / D_RBOR / D_RBSR |
| 0x00266ee8 | sceDmaGetEnv | the 20-byte copy PutEnv keeps (D_0066FAD8) |
| 0x00266f20 | sceDmaPutStallAddr | swaps D_STADR (0x1000e060) |
| 0x00266f38 | sceDmaSend | TADR = tag, QWC 0, CHCR chain from memory (0x105) |
| 0x00266fa0 | sceDmaSendN | MADR / QWC, CHCR normal (0x101) |
| 0x00267018 | sceDmaSendI | MADR / QWC, CHCR interleave (0x109) |
| 0x00267090 | sceDmaRecv | chain, to memory |
| 0x002670d8 | sceDmaRecvN | normal, to memory |
| 0x00267158 | sceDmaRecvI | interleave, to memory |
| 0x002671d8 | sceDmaSync | mode 1 returns CHCR.STR, else the "sync timeout" wait |
| 0x00267210 | sceDmaWatch | mode 1: MADR < addr, else waits for it |
| 0x00267248 | sceDmaPause | DI, the D_ENABLEW hold bit, STR cleared, old CHCR returned |
| 0x002672e0 | sceDmaRestart | CHCR written back, old STR returned |

Left unnamed in that range: func_00266a10 (installs a DMAC interrupt handler on cause 2), func_00266ab0 /
func_00266b20 (the two timeout waits), func_00266ba8 (scratchpad address to its DMA form), func_00266bd0 (a
byte clear), func_00265558 (reads 256 entries of a file named at D_00492920) and func_002655f8 (syscall 0x80).

**Game calls into the SDK still by func_ address** (session 56 census; the next wrappers; the roles in brackets are guesses from the arguments, not checked): the sifdev file
calls of src/io/discfile.c, src/gfx/opfile.c and src/game/hdd*.c, func_0025b588 (open: (name, mode)),
func_0025b810 (close), func_0025b990 (lseek: (fd, off, whence)), func_0025bbc8 (read: (fd, buf, n)),
func_0025cd70 / func_0025cfa0 / func_0025ce38 (dopen / dread / dclose: hdd.c lists a directory),
func_0025d880 (mount: (dev, path, flag, arg, len)), func_0025daf0 (umount), func_0025dd48 (devctl-like, 6
arguments), func_0025db10 (returns s64: a 64-bit lseek), func_0025c448 (6 arguments), func_0025e990
((name)); libcdvd in src/io/discfile.c / cdqueue.c and src/game/movies.c, dkmovie.c: func_0026aaa0 (no
arguments, 4 files), func_00269fd0 ((s32), a sync), func_00269da8, func_0026a728, func_0026a9d0,
func_002696b8 ((s32, void *, s32)), func_0026ab38, func_0026abf0, func_0026aca8 ((void *)), func_00269960
((void *, s32)); func_0025b550 / func_0025ed28 / func_0025ed48 / func_0025f1f0 / func_0025f228 (discfile.c,
the IOP module loads and reboot); func_00262c78 (field.c, no arguments) and func_00250360 ((void *, s32,
s32, void *): cmdmenu / objreact, a libc sort?).  Name each from its code and the library order (as libdma
above) before wrapping it: the cd / iop wrapper is the next one.

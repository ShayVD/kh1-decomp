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
| `0x00265558`-`0x00266380` | libgraph | `rom0:ROMVER`, `sceGs*` |
| `0x00266AB0`-`0x00266B20` | libdma | `"libdma: sync timeout"` (two sync functions) |
| `0x00268098`-`0x00268988` | libdbc | `sceDbc*` |
| `0x002695F8`-`0x0026AB38` | libcdvd | `sceCd*` |
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

Not named yet: the other libpad2 functions (`0x00268CE8`, `0x00268DC0`,
`0x00268EB0` take (socket, buf), (socket, buf), (socket): probably
`scePad2GetButtonProfile`, `scePad2Read`, `scePad2GetState`, but the order
is not proven), libipu's DMA helpers (`0x002723C8`-`0x00272580`,
`0x00272580` restarts IPU DMA from a saved env, likely
`sceIpuRestartDMA`), the newlib internals (`_malloc_r` `0x0024F7E8`,
`_free_r` `0x002557D8`, `_vfprintf_r` `0x002524A0`, `_dtoa_r`
`0x002541B8`, `__sfvwrite` `0x00255C40`), and the large block
`0x0026AD60`-`0x00270B40` between libcdvd and libmc (no banner; calls into
`0x00262F50`-`0x002634E0`), which still needs identifying.
`func_00268a78` is called in libdbc's bind retry loop (a delay?).

## Porting note

None of these are ported. The Vita layer replaces each library behind the
`include/platform/` wrappers (docs/portability.md).

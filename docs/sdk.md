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

Still to do: libpad2, libvib, libpc, libipu (no name-bearing strings found
yet), and the libc string/memory functions (identify by behaviour).
`func_00259cc0` (libkernl range) prints the libraries' error messages, so it
is probably `scePrintf`; `func_00268a78` is called in libdbc's bind retry
loop (a delay?). Neither is named yet.

## Porting note

None of these are ported. The Vita layer replaces each library behind the
`include/platform/` wrappers (docs/portability.md).

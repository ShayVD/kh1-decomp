## Session 27: reach_check (worker s27reach)

Draft section for docs/shiftable-plan.md. reach_check now pins **1,347** names (was 1,803): 467 released,
11 newly pinned (coverage the more precise analysis found). Each rule has a `--no-*` switch
(SHIFT_REACH_FLAGS); with all seven off the output is byte-identical to session 26's float_reach.txt.

### The 1,803 names by reason (session 26 float_reach.log)

Counted by the reasons of every hit that pins a name (a name with one reason only):

| reason | names | what it was |
| --- | --- | --- |
| arg:noreach | 343 | an address in an argument register the callee never reads (left over), or one it stores or DMAs |
| arg:wide | 252 | the callee walks the argument: printf formats, strcat sources, -1-terminated lists, DMA senders |
| idx | 180 | an unbounded index; many were loop counters whose bound widened away |
| stored | 80 | the address is stored, mostly as a stack argument (func_0023b570 -> func_0023aed0's 9th+ arguments) |
| idx-ub | 40 | a bounded index that ends past the next name |

By callee: func_00106b18 / func_00106bd8 / func_00266f38 (DMA chain senders, ~100), scePrintf (47),
func_0010ef70 (26, a window's text pointer), func_00237018 (21, a GIF packet sender),
func_0024afc0 / func_0024af40 (36, -1-terminated index lists), func_00106cd0 (18, DMA ref tags).

### The rules (names each releases on its own, from the final 1,347: `--no-RULE` re-pins them)

| rule (switch) | releases | what it proves |
| --- | --- | --- |
| dead-arg (`--no-dead-arg`) | 184 | `arg_live()`: per function, the argument registers it may read before writing them on any path, through its calls and tail calls (least fixpoint over the call graph). An address left in a0-t3 at a call is not an argument when the callee never reads that register. Conservative: an unknown callee, jalr, a switch `jr`, a branch out of the function or a fall-through past its end read every register; a syscall reads all unless `li v1,N` names one of the SYSCALL_ARGS (FlushCache, semaphores, Enable/DisableIntc/Dmac ...). After a jal the caller-saved registers are dead (EE ABI). |
| counter-cap (`--no-counter-cap`) | 21 | an up-counter loop `i = i0; do { ...; i += k; } while (i < L)` (countdown_loops' up-counter pattern, now listed even with no walked pointer) caps i at its header at max(i0, L-1) (+k when the test sees i before the step). Before, the counter's bound grew 0, 1, 2 and widened to unknown before the slti could cap it, and every index made from it was unbounded (func_00219870's `D[i]` for i < 12). |
| slot-refine (`--no-slot-refine`) | 32 | a `beq/bne t,$0` edge refines the state before the branch's delay slot, not after: `bne v1,$0,loop; sll v0,s2,2` now scales the capped counter. Also reads more switch tables (`sltiu v0,v1,7; beqz v0; sll v0,v1,2` gives the table index its bound), so a switch goes to its cases instead of every label: this both releases names (D_002C64A0) and pins 10 new ones (libc's stored addresses D_00491B40 ..., D_00491D30 ...; they floated in F26_A). |
| str-arg (`--no-str-arg`) | 77 | STRING_ARGS: printf-family formats (scePrintf, func_00259c88, printf, sprintf arg 1), puts/strlen/strcmp/strncmp/strcpy src/strcat src, func_001ea268's encoded-text source. A literal in .data whose first NUL is inside its own object, followed by at most 15 zero bytes (a buffer has a long zero tail or no text), and that no store the analysis sees writes, is read to its NUL. Formats: every `%` must start a whole conversion (func_00259698 skips the byte after a lone `%`, past a NUL). func_001ea268: no control byte 5-7 or 9-31 before the NUL (they take parameter bytes). The callee's quadword reads past the NUL are discarded, so the `arg1:strcat:32` hits are dropped too. |
| list-arg (`--no-list-arg`) | 49 | LIST_CALLS: func_0024afc0(list, out, hdr) and func_0024af40 read a word list to -1 and write 4 / 0xC0 bytes per element to out; func_0024c8b8 reads halfwords to a negative one. A list literal (terminator then at most 12 zero bytes to the next name, no seen store) gives the count, which bounds the list and out at the same call. |
| dma-count (`--no-dma-count`) | 45 | DMA_COUNT_CALLS (block accesses like memcpy's): func_00237018(buf, n) writes an end tag with qwc n-1 at buf and sends buf in chain mode, so 16*n bytes (D_006480D0 is exactly 0x160 = 16*22); func_00106cd0(addr, qwc) appends a ref tag (0x30000000+qwc, addr) to D_00494A90's chain: 16*qwc bytes at addr. Needs a constant count at the call. |
| dma-chain (`--no-dma-chain`) | 99 | CHAIN_CALLS: func_00106b18(chain), func_00106bd8(chain, ...) (through func_00106b98's callback) and func_00266f38(channel, chain) start a chain-mode DMA at the chain. A chain object passed only to these, never stored, uncached, indexed or written by a seen store, whose tags parse (refe/cnt/ref/end only, at most 256, all inside the object) is read to its end tag; each ref/refe target gets an access of 16*qwc bytes from its address (`dma-ref`), so a target whose transfer runs into the next name pins it (D_002BC9B0, new). |

The seven together: 1,803 -> 1,347. `--explain FILE` writes one line per `&B[i]` passed to a call (base,
reason, caller, callee, argument, bound) for the next round. tests/reach_check_test.py covers each rule.

### The default float build

- **KH1_S27_REACH** (`make shift SHIFT_MODE=m12 SHIFT_FLOAT=1` at this branch): **2,050 floated names** (was
  1,602), `_end` **0x751DE4** (was 0x74B164), pools 0x75C000, block heap 0x8AF000 (0xF1000 left, assert 0xE0000);
  keep_check 38/38, M12-FLOAT OK.
- float_keep.txt gets three names, none for a reach reason:
  - D_00278B50 (0x225F0) and D_002C64A0 (0x1C200): released, but floating both leaves the block heap under
    0xE0000 ("block heap ... would keep less than 0xe0000 bytes"). Every floated byte costs twice until
    SHIFT_FLOAT_COMPACT; take them out of float_keep then.
  - D_00272C70: the first data object (= D_BLOB). Floated, shift_cmp maps D_BLOB through it to the copy
    and reports `_gp ... D_BSS ... WRONG`. Needs shift_cmp to map D_BLOB as the blob start.

### Riskiest releases (for the boot route)

- **dma-chain (99)**: the DMA chains of func_00100988 / func_001008e8 (D_0029B170 ...), func_00102118
  (D_002A4310 ... D_002A4570), func_001032b0's ref tags (D_002A46D0 ... D_002A48D0, dma-count),
  func_00103058 / func_00102a48 / func_00102da8 / func_00103c48 / func_001039f8 (D_002A4B60 ... D_002A6B80),
  func_00106000 / func_0010b6c0 / func_0010f658 (D_002B65E0 ... D_002BD140), and the VU/VIF chains
  func_0015fc00 sends (D_00277E40 when `e->o->x48 & 0x10` with `fl & 8`, D_00278210 otherwise) and
  func_0015f018 (D_00278680 on VIF0 at init). A tag the game patches through a pointer would break the
  static parse: watch the title, fades, the load menu, and any model drawn with that special mode.
- **list-arg / dma-count (94)**: the 0x00237000-0x0024A000 module: func_0023b570 / func_0023cf30 /
  func_0023cfe8 / func_00243a90 build 0xC0-byte records from the lists (D_00449900, D_0044A810,
  D_00454558 ...) into bss (D_0064FD60, D_00651BD8 ...), and func_002372e0 ... func_00249010 send GIF
  packets (D_006480D0, D_00648630 ..., 16*n bytes). Find what it draws (menu/HUD 3D?) and exercise it.
- **str-arg file names**: strcat sources ".img" / ".dat" / "00_" (D_0048CC30, D_0048D000, D_0048D008,
  D_0048D128, D_002BCC88) and sprintf formats "%s_%s" / "%s%s" (D_0048D320, D_0048DCB0, D_0048E410):
  file loading; a wrong byte shows as a failed load. D_003DD238 / D_003DD240 ("\x01", "\x04") feed
  func_001ea268's text.
- dead-arg, counter-cap and slot-refine are general and argued from the code; the 10 names slot-refine
  newly pins floated in F26_A without trouble.

### Left pinned (the largest groups)

- idx (187 names by that reason alone): a long tail, 2-6 names per function. Many are nested loops whose
  inner counter carries over the outer loop (func_00103a70's 4x4 copy: t5 counts 16 across both loops);
  that needs relational bounds.
- stored (94): func_0023b570 passes 9+ arguments to func_0023aed0 on the stack (38 names); stack
  arguments are not followed.
- arg:noreach / arg:wide that are real: func_0010ef70 (a window keeps the text pointer; the renderer's
  control codes are not verified), sceGsExecLoadImage via func_0010c438 (16), func_001e05a8, printf `%s`
  arguments.

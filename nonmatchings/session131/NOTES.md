# Session 131 notes

## Matching: 0010d470 129 -> 101 words (unnatural, no match)

The plan's untried idea: decomp-permuter (PENALTY_REGALLOC 50, as session 130) on s14m's 129-word probe
(nonmatchings/session14/s14m__0010d470_129w_finding.c). Counts are true DP LCS words of the original
unmatched (tools/matching/sc6_s12.py with RO=48cdf0, ROOT copied to the scratchpad as in session 130).

| run | base | iterations | best by our count | what it is |
|---|---|---|---|---|
| a | s14m 129w | ~69,000 (90 min, -j3) | **108** (output-10590-1), size 3920 vs 3968 | an unreachable `new_var = str;` between case 5's `break` and `case 6:`, read by case 14's `c2 = new_var[pos];` |
| b | run a's 108w | ~44,000 (60 min) | **101** (two outputs), size 3928 | b1: `pos = 16;` after case 14's `pos++` and `off = n * 16 + pos; off += pos;` (nonsense: changes behaviour); b2: four small temps (`new_var3 = c` for the copy loop's switch, `new_var2 = n` for case 24's `b->g[new_var2].code`, `k = 128 / ...` in case 14 / 0, case 5's `(f32)` cast dropped) |

- s131__0010d470_108w_deadstore.c is run a's draft (valid C, same behaviour: the dead store never runs;
  gcc keeps it as a register-allocation hint). Run b's 101-word outputs were not kept: b1 changes what the
  function does, b2 is four unrelated nudges to the same allocation knock-on.
- Neither run touched the 40-byte size gap (jump2 cross-jumping of the case 24 / 25 PUT copies, s23m3);
  every output stays 3920-3936 bytes. The words won are all in the copy loop's allocation (0x838-0xee0).
  A permuter on this function finds allocation nudges, not the missing cross-jump.

## Overlays: dktitle.x toolchain check (vita-port-plan 5.2 step 2)

ovl_toolcheck/dktitle_leaves.c: nine small dktitle.x functions written by hand from the disassembly,
compiled with the main ELF's ee-gcc 2.96 `-O2 -G0`, linked at their overlay addresses (`chk.sh`: each
function in its own section, the overlay's data / main-ELF names as `--defsym`) and compared with the
user's file byte for byte (a byte compare of linked code, not objdiff: the overlay has no build target yet).

- **8 of 9 identical** with `-O2 -G0 -fno-strict-aliasing` (the main ELF's "nostrict" mode); 7 of 9 in
  the default (strict) mode. `ovl_00f20a78` (store `*a`, then read the header's size) needs the
  no-strict-aliasing order; two other spellings tried in strict mode do not give it.
- `ovl_00f20860` (8 bytes short): the original reaches `0x9A0000 + 16` as `lui; addiu 0 (%lo); addiu 16`
  and sets its six constant arguments in another order; not pursued.
- So the overlay was built with the main ELF's compiler; the flag mode is per file as in the main ELF
  (some functions need nostrict). Step 3 (an overlay build target) can reuse kh1.toml's modes.

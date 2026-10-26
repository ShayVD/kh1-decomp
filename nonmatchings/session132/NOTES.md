# Session 132: dktitle.x (the title screen overlay)

59 of 71 functions byte-identical (`make ovl OVL=dktitle`, objdiff 100% each in `make ovl-report
OVL=dktitle`): 27 from autodecomp pass 1, the rest by hand (ovl/dktitle/hand/). The 12 left have
near-miss drafts here (dktitle/), listed in ovl/dktitle/drafts.tsv so the port compiles them.

## What the overlay is

- 0xF20000 entry; packet helpers: a 1024-qword pool at D_00F286F0 (count D_00F2C6F0,
  func_00f20038 allocates), a 256-entry DMA tag list at D_00F276F0 (count D_00F2C6F4;
  func_00f20090 ref tag `0x30000000 | qwc`, func_00f20118 end tag `0x70000000` then func_00106b18).
- Sprites: func_00f203a8(tex0, tex1, alpha, x, y, w, h) 7 qwords, func_00f20540 with a fixed TEX0,
  func_00f201c8 a 4-vertex strip; screen x * 16 + 0x7008, y * 16 + 0x7408. func_00f24330 a textured
  sprite packet with 18 arguments, func_00f241c8 an image upload packet.
- Textures: func_00f206c8(img, clut, dbp, w, h, psm, cbp) (PSMT8 16 x 16 CLUT, else PSMT4 8 x 2);
  func_00f20a98 walks the title pack at D_009A0000 (8-byte entries from +16; header `u16 off`,
  `s32 size`, CLUT after the pixels) and uploads 12 textures.
- Fades: `{f32 v; s32 st; s32 t;}` at 16-byte steps D_00F2C738 .. D_00F2C880 (func_00f20db0: up by
  2.1333334 to 128, hold 180, down); func_00f21808 inits them.
- Menu: func_00f228c8 the main loop, a 34-state switch on D_00F2C708 (logo fades, memory card check
  through D_003F8370[2] with dialog states 18-23, press start 27, new game / load 28-33);
  func_00f21928 the cursor (selection D_00F2C700; 3 items, 4 when D_002B6478 (a save exists));
  func_00f22238 draws the items; func_00f23de8 a 10-case draw dispatch on D_00F2C89C.
- HDD install (Final Mix's "install to HDD" screens): func_00f24b60 the thread (prompts, copy thread
  func_00f24b28, bar D_00F2C8D8 = D_00F26E3C * 0x27600 / D_00F26E38), func_00f25c40 copies the
  disc file in 512 KB chunks, func_00f25528 writes the header, func_00f25848 probes and formats
  (`sceFormat`), func_00f26180 / 26378 write the files, progress codes 360-490 to D_0046A614,
  D_0046A688 is hdd.c's HddCfg. A port answers "no HDD" (include/platform/ovlsdk.h).

## Matching lessons (gcc 2.96, all but func_00f25848 in the default flags; that one nostrict)

- A callee's declared return type moves registers: try s32 and void early (func_00f237f8 needed
  `s32 func_001117e0(void)` though the main ELF's is void; func_00f23990 `void func_002014a0`).
- `lui; addiu %lo; addiu 16` instead of a folded %lo: the address went through a `static inline`
  accessor (func_00f20860 / 208a8); constants folded the same way unless through an inline helper.
- One variable per value (no splitting): separate locals per reuse; globals rather than a `Fade *`
  (the original batches the loads); a goto retry loop where a real loop would hoist addresses.
- Float literals: 0x3E3851EA is `0.17999998f`, 0x3DF5C28E `0.11999999f`, 0x3E75C28E `0.23999998f`.
- `x += C; x *= 16;` for addiu-then-sll; OR chains and stores in the original's operand order.
- Bit tests on D_002C5968 as a packed bitfield struct; asserts are a bare `break` (PlatBreak()).

## Left (words differing in hand.py try)

| Function | Words | Blocker |
|---|---|---|
| func_00f21068 | 1 | `bc1fl` where the original has `bc1f` (reorg's annulled-branch choice, as 001fd858 in the main ELF) |
| func_00f241c8 | 2 | `dsra32` / `dsll32` swapped |
| func_00f26710 | 2 | `lui` of D_00F26E30 in v1 not v0 |
| func_00f20a98 | 10 | header pointer in a0 vs v0 |
| func_00f25528 | 24 | register choice in the header block |
| func_00f21808 | 36 | 17 global stores' allocation (nostrict draft) |
| func_00f21ca0 | 94 | gcse's hoisted `lui 0xf3` registers permuted |
| func_00f23aa8 | 104 | the shared 20 divisor, `div` only |
| func_00f24330 | 176 | tag offset set in the branches |
| func_00f25c40 | matched (session 136) | ovl/dktitle/hand/func_00f25c40.c: permuter output plus the retry check before each sceCdSync |
| func_00f24b60 | 598 | first full draft, allocation |
| func_00f228c8 | 746 | case 18 falls into 19-21's bodies, cross-jumped menus |

## Session 135: decomp-permuter (20 minutes each, 2 threads)

The user OK'd the cloned decomp-permuter (2026-10-26). Each draft in ovl/dktitle/drafts.tsv and
dkmovie's two: dkmovie func_00f20258 matched (ovl/dkmovie/hand/; func_0011ef10 declared to return a
value). func_00f25528: permuter score 50 -> 40, 6 -> 4 words by `autodecomp.py try` (not kept: the
draft stays the port's). dkmovie func_00f20140: 29 -> 13 words (register choice for the packet base;
four hand variants with a `MoviePkt *` local did not help). No improvement on 00f26710, 00f241c8,
00f20a98, 00f21068 (reorg's annul choice, as expected). func_00f25c40: 245 -> 7 words, kept in the
draft (`u32 i` declared inside the do-while; the other 7 words and the 4-byte size gap are open).
The rest only moved the permuter's score, not `autodecomp.py try`'s word count: 00f21808 36 -> 39
(nostrict), 00f21ca0 94 -> 91, 00f23aa8 and 00f24330 worse; nothing kept. 00f228c8 and 00f24b60
imported but never ran (the queue ended first).

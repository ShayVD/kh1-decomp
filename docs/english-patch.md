# The English fan patch and the port

Session 137 side thread (2026-10-27). The user owns the Japanese disc and has the community English
patch (crazycatz00's KH1 ISOMaker, "July 2025" import folder) plus an ISO it produced
("Kingdom Hearts Final Mix (English v2026-02-26)"). Nothing from either is in the repo, and nothing
may be: patch files and the patched ISO stay on the user's machine.

The matching target does not change: kh1.toml still pins the retail `SLPS_251.98`
(SHA-256 `1993a4da…`) and `kh1.elf` stays byte-identical to it. English is a port-side option only.

## What the patch changes

The ISOMaker rebuilds KINGDOM.IMG from the user's retail ISO plus an `import/` folder (465 files):

| kind | files | what the port needs |
| --- | --- | --- |
| KINGDOM.IMG data | 229 `.ard` (rooms), 226 `.evm` (events), `kanji.knj`, `sysfont.bin`, menu `.kmb` / `.bin`, worldmap and gummi `*MSG.BIN`, `btltbl.bin`, `allarea.nam`, `uitex.bin`, `atad.irx` | nothing: the port reads files through KINGDOM.IDX on whatever disc it is given |
| overlay | `wm.x` (world map) | an English variant once wm.x is decompiled natively; until then nothing |
| main ELF | `SLPS_251.98`, SHA-256 `53eca29e315f43f6cb63960f32d1737b2ea3f95e3954d6b7027f4054ca64954d`, same size (3,804,356) | see below |

The ELF inside the patched ISO is the same file as the one in the import folder (same SHA-256).
The patched ISO's KINGDOM.IDX is 53,248 bytes (retail 57,344); its directory layout otherwise matches retail.

### The ELF's data (45,744 bytes changed)

All in .data/.rodata, 0x378A48-0x4917F8. Every changed byte but one (0x4917F8) lies inside a
`PIECE` of src/data/data_*.s, i.e. bytes the port already takes from the user's ELF at build time.
No changed word is a new pointer: the 185 changed words that look like image addresses are packed
halfword pairs (glyph tables at 0x46A0E4.., layout records at 0x3E48C4..), not relocations.
So cutting the pieces from the English ELF gives the port the English strings and tables.

### The ELF's code (202 words, all in functions already in src/)

| change | where |
| --- | --- |
| glyph cell 18 -> 24 px (`li rX, 0x12` -> `0x18`), its row stride 0x120 -> 0x180 and a few `sll` counts (8 -> 6) in the same index math | text/text.c, text/wintext.c, text/wintext.nostrict_nogcse.c, text/winrow.c, hud/popup.c, hud/timer.c, screen/fade.c, menu/textfade.c, menu/choice.c |
| func_0010c720 (fldtext.c): the glyph source rectangle arithmetic rewritten (74 bytes); func_0010d470 spacing 12.0f -> 8.0f | text/fldtext.c |
| three draws (func_001f94f0, func_001f9e48, func_001fa8b0) save one more register and call a new helper the patch put in the zero padding at 0x257D10: `width = width * 4 / 3; x -= 2` | text/wintext.nostrict_nogcse.c |
| string-table pointers retargeted (`%lo` / `%hi` changes): shop, list and message-window tables now point at English tables elsewhere in the data blob (e.g. list.c's 0x3E0D20 -> 0x48BAA8) | shop/shop.c, list/list.c, msgwin/msgwin.c, text/text.c, gummi/gumisave.c, text/wintext.nostrict.c |
| a two-glyph width test 0x12 -> 0x4D | text/text.c func_001f0868, wintext func_001f9748 |

None of this is VU or compiler-specific; it is constants and a handful of rewritten lines.

## How the port can run in English

1. Disc: give the port the patched ISO (Vita: `ux0:data/kh1/kh1.iso`; host: `KH1_HOST_ISO`).
   This alone brings English dialogue, menus and the English font, but the code would still lay
   glyphs out on the Japanese 18-px grid and point the shop / list tables at Japanese strings.
2. Data: a port-only build option that cuts the data pieces from the English ELF (its own pinned
   SHA-256 above) instead of the retail one. The PS2 build keeps cutting from the retail ELF.
3. Code: an English variant of the ~65 functions above, chosen at run time on the port
   (`#ifndef KH1_PS2`, the PS2 objects unchanged), switched on when the disc's `SLPS_251.98`
   is the English one.

Not done yet: this note records the survey only.

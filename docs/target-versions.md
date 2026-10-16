# Kingdom Hearts (PS2) executables and target choice

Session 1 notes. Serials and dates are from psxdatacenter.com; everything marked
*unverified* still needs checking against a real dump.

The main executable on each disc is named after its serial, e.g. `SLPS_251.98`
for disc SLPS-25198. Reprints (Ultimate Hits, Greatest Hits) sometimes ship a
rebuilt ELF, so the serial on the disc matters, not just the edition name.

| Edition | Serial(s) | ELF name | Released | Notes |
|---|---|---|---|---|
| Original JP | SLPS-25105 | `SLPS_251.05` | 2002-03-28 | Japanese voices and text. Earliest build. |
| Original JP reprint | SLPM-66122 (Ultimate Hits) | `SLPM_661.22` | later | Possibly rebuilt. *unverified* |
| Asia (original) | SLAJ-25004 | `SLAJ_250.04` | 2002 | Asian NTSC-J release. |
| US | SLUS-20370 (incl. Greatest Hits) | `SLUS_203.70` | 2002-09-17 | English. Added bosses/content over JP original that FM later folded in. |
| PAL | SCES-50967 … SCES-50971 | `SCES_509.67` … | 2002-11-15 | One serial per language set (EN/FR/DE/IT/ES), English voices. 50 Hz and multi-language text handling add code. |
| **Final Mix** | **SLPS-25198** | **`SLPS_251.98`** | 2002-12-26 | JP text, English voices. Superset of US content plus FM extras (new bosses, Heartless, cutscenes, Gummi missions, difficulty levels, event skip, battle report). |
| Final Mix Limited | SLPS-25197 | `SLPS_251.97` | 2002-12-26 | Same game in a limited package. Expected (not verified) to carry an identical ELF apart from the name. |
| Final Mix Ultimate Hits | SLPM-66123 | `SLPM_661.23` | later | Budget reprint; may be a rebuild. *unverified* |
| Final Mix Asia | SCAJ-25004, SCAJ-20149 (UH) | | | Asian releases of FM. |

## Recommendation: Final Mix (SLPS-25198 family)

Final Mix is the right primary target, matching the stated preference:

- **Content superset.** FM is the last and most complete PS2 build: it includes
  the US additions plus FM-only content. Decompiling it gets the whole game.
- **It is the lineage of later ports.** KH HD 1.5 ReMIX (PS3) and the PS4/PC
  1.5+2.5 releases are built from Final Mix, so those versions (and the OpenKH
  community's file-format research, which centres on the HD releases) map most
  directly onto FM code and data. That is the best available source of names
  and behaviour hints.
- **Consistency with the kh2 decomp**, which targets KH2 Final Mix (`SLPM_666.75`).
- **No strong counter-argument.** Every version is equally hard to match. The
  only real downside is Japanese text in menus, which matters for string
  tables but not for code matching, and a later Vita port can swap text data
  from any language's disc since assets are extracted from the user's own copy.

Reasons one might pick another version, recorded for completeness:

- **US SLUS-20370**: English strings make debugging easier and it is the most
  common disc in the West. Choose it only if the FM disc is not available.
- **JP original SLPS-25105**: earliest build, sometimes leftovers of debug code.
  No other advantage.

Which exact FM serial is used (25198 vs 25197 vs 66123) is decided by the
disc the user owns; the SHA-256 of that ELF is what gets pinned.

## Pinned target

*Pending: filled in once the user supplies the SHA-256 of their dump.*

| Field | Value |
|---|---|
| Serial | |
| ELF file name | |
| SHA-256 | |
| Size | |

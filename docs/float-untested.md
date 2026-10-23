# Untested float changes (boot these first)

Every change to which data names float (move) in the default shifted build since the last PCSX2 boot.
A float change is only proved by booting the usual route; until then it is a candidate. Sessions without
the Mac add to this list; the first session with the Mac boots the current default and moves the rows it
proves into docs/shiftable-plan.md (and clears them here).

Last booted default: **KH1_F29_N** (session 29, reach_check with nest-carry). Everything below is newer.

## The route

`make shift SHIFT_MODE=m12 SHIFT_FLOAT=1` (after tools/shift/data_owners.py and staging out/overlays from
Downloads/kh1-test/ovl), copy the ELF to Downloads/kh1-test/sNN and /mnt/project-files/kh1-runtime/sNN,
patch KH1_BIG.iso, then: load menu, save 06 with Donald and Goofy, test T, a desert fight, the in-game
menu (item and status pages), save 05 End of the World, the warp drive to Neverland.

## Bisecting a failure

Each row names the switch that undoes it. Add switches to `SHIFT_REACH_FLAGS` from the newest session
back, boot, and narrow down within the session that fixes it.

| session | switch(es) | what changes | names | risk |
| --- | --- | --- | --- | --- |
| 30 | `--no-path-step` | released (float) | 20: D_002B75A0, D_002BC0F0, D_002BC120, D_00351A00, D_002BCC1C, D_002E27C0, D_002E27C8, D_003F60F0, D_003F7500, D_003F7510, D_003F7598, D_003F75A0, D_003F7628, D_003F7630, D_0046C550, D_0046C580, D_004E4528, D_004E49E8, D_00532B90 (D_003F6770 pinned again in session 31) | D_0046C550 (DMA reset at boot), D_00532B90 (walk, fight), D_004E4528 (area load), D_003F75xx (menus) |
| 30 | `--no-arg-bound` | released (float) | 9: D_0048C6F0, D_0048C770, D_004D92F0, D_004D9320, D_002BD178, D_002BD1A8, D_002BD1E0, D_003F31F0, D_003F3200 | whole-program reasoning: D_0048C6F0 (title, models), D_003F31F0 (menu gradients), D_002BD178 (field ray tests) |
| 30 | `--no-wr-span` | fix, no release on its own | keeps D_00370140 / D_00370170 / D_003701B0 pinned | low |
| 30 | `--no-arg-bound` | newly pinned | D_003728C0, D_00372908 | none (back in place) |
| 31 | `--no-arg-keep --no-join-keep --no-stored-idx` | 54 newly pinned, none released | docs/shiftable-plan.md "Session 31: reach_check arg-join" | layout only: every floated name after them moved |
| 32 | `--no-multi-base` | 4 newly pinned, none released | D_003F4C90, D_003C21A0, D_002BD170, D_00454700 | layout only |
| 32 | `--no-sign-prune --no-shadow-image --no-arg-drop` | log only, same names | (termination and order fixes) | none |
| 33 | `--no-idx-span` | 11 newly pinned, none released | D_003F5C20, D_003F5C24, D_003F5C28, D_003F5C2C, D_004E3A1C, D_003C39B0, D_003C39F0, D_003C3A30 (real), D_003C39AC, D_0054C218, D_00575784 (not reached, safe) | layout only (fixes: the menu's D_003F5C18[i < 6], D_004E39F8[4], the script VM's byte variables) |
| 34 | `--no-likely-slot` | **released (float)** | 14: D_002C1310, D_002C1320, D_00304BE8, D_003F59C0, D_003F59C8, D_003F5E58, D_003F5E60, D_0046BE88, D_0046C210, D_0046C250, D_0054C218, D_00669390, D_006693B0, D_006693D0 (each read one entry too far by the analysis; D_00551600 is kept: neg-keep, float_keep.txt) | D_0054C218 (summon/effect slots), D_00669390 ... D_006693D0 (tables passed to func_002474e8), D_003F59C0 / D_003F5E58 (menus) |
| 34 | `--no-widen-heads` | **released (float)** 2, newly pinned 2 | released D_00531B70, D_00531F70 (the loader's 128-entry id/handle table); pinned D_002BD1F0, D_00454468 (not real, safe) | D_00531B70 (every file load registers in it: area load, save load) |
| 34 | `--no-hix-join` | **released (float)** | 3: D_00493F38, D_00493F48, D_00493F58 (atanf's atanhi / atanlo / aT) | atan everywhere (camera, steering, aiming): any wrong angle |
| 34 | `--no-align-end --no-neg-keep` | order only, same names | (D_0054F444 in random orders; D_00551600 now pinned in every order) | none |
| 34 | none (float_keep.txt) | module move only, same names | D_0062F840 (the shop's third window) kept by float_keep.txt: h20's 0x100-byte view of D_0062F790 used to cover it; src/shop/shop.c types the windows as MsgWin (0xb0). It can float after a `SHIFT_FLOAT_FORCE=D_0062F840` boot that plays a shop | none |
| 35 | none | module move only, same names | none: float_covered.txt, float_reach.txt and the symbols match session 34 after every commit | none |
| 36 | none | module move and type folds only, same names | none: float_covered.txt, float_reach.txt, the loaded bytes and the symbols match session 35 after every commit | none |
| 37 | none | module move and the TextWin type only, same names | none: float_covered.txt, float_reach.txt, the loaded bytes and the symbols match session 36 after every commit | none |
| 38 | none | module move, view folds into TextWin and D_0063F758 typed TextWin[24], same names | none: float_covered.txt, float_reach.txt, the loaded bytes and the symbols match session 37 after every commit | none |
| 39 | none | module move into src/menu/ (D_003F3530 typed PartyMdl[4]; D_00640E40, D_003F31D0, D_006411E0 ... D_00641218, D_003F32C8 and D_003F32E8 defined by their modules), same names | none: float_covered.txt, float_reach.txt, the loaded bytes and the symbols match session 38 after every commit | none |
| 40 | none | module move into src/menu/ (the item page's frame, the equipment, abilities, customize and status pages; D_003F3DE0 and D_00642D10 / D_00642D14 defined by their modules), same names | none: float_covered.txt (as a set: one line moved), float_reach.txt, the loaded bytes and the symbols match session 39 after every commit | none |
| 41 | none | module move into src/menu/ (the settings accessors, the config page, page 5's model, sprite frames and frame; D_003F4A48, D_006430EC, D_00642E90, D_003F59E8, D_003F5A00 and D_003F5C08 defined by their modules; D_00643020 typed JMdl), same names | none: float_covered.txt, float_reach.txt, the loaded bytes and the symbols match session 40 after every commit | none |
| 42 | none | module move into src/menu/ (page 5's six sections journal_s0 ... s5, page 7's party.c, savemenu.c and page7.c; D_006435BC ... D_00643638, D_006436C8 and D_003F5C50 defined by their modules), same names | none: float_covered.txt, float_reach.txt, the loaded bytes and the symbols match session 41 after every commit (one commit lost D_003F5C50's definition and the check caught it; fixed before the commit) | none |
| 43 | none | module move into src/menu/ (the load screen loadmenu.c / loadframe.c, gamesetup.c, textfade.c, choice.c / choice.nofill.c, choice2.c) and src/shop/ (shopbuy, shopsell, shopgummi, shopframe, synth.c / synth.faddr.c); D_00643800, D_006469A8 ... D_0064524C, D_006469D8 ... D_006469F8 defined by their modules, D_003F6568 by journal_s5.c; same names | none: float_covered.txt, float_reach.txt, the loaded bytes and the symbols match session 42 after every commit (one commit lost h72's D_003F6568 and the check caught it; fixed before the commit). The shift build has 9,740 input sections instead of 9,741 from the choice commit on: the three nofill handlers' doubles (0.08) now share one .rodata of 0x18 bytes, contiguous as in the original | none |

Session 30's default (2,100 float), session 31's (2,047), session 32's (2,043), session 33's (2,032) and session 34's
(2,049, unchanged in sessions 35 to 43) were never booted. To go back one session at a time: `SHIFT_REACH_FLAGS="--no-likely-slot --no-widen-heads
--no-hix-join --no-align-end --no-neg-keep"` gives session 33's names (float_reach.txt and .log byte-identical);
`--no-hix-join` alone puts back the three atanf tables, `--no-widen-heads` those and D_00531B70 / D_00531F70 (and
re-floats D_002BD1F0 and D_00454468), `--no-likely-slot` the other 14. Add `--no-idx-span` for session 32's names; add
`--no-multi-base` for session 31's;
add `--no-arg-keep --no-join-keep --no-stored-idx` for session 30's, then `--no-path-step --no-arg-bound
--no-wr-span` for session 29's (the last booted). Boot the current default first and walk back only if it
fails; within a session, drop its switches one at a time. If session 30's default fails and 31's passes,
D_003F6770 is the first suspect. Sessions 31, 32 and 33 released nothing, so a failure that their switches fix
points at layout shift around the newly pinned names, not at a wrong release. **Session 34 released 19 names** (the
first releases since session 30): if its default fails and session 33's passes, try `--no-hix-join` first (atanf),
then `--no-widen-heads`, then `--no-likely-slot`; docs/shiftable-plan.md "Session 34: reach_check" has the verdicts.

## Known hazard to read before booting (sessions 32-33)

Session 32: a bounded index that runs past the next name pinned only that one name, so the names after it could
float while code still read them. **Session 33 fixed it** (idx-span, `--no-idx-span` to undo): every name up to an
access's tight end (a bound from a loop or a compare against a constant, not from a byte/halfword load or a mask)
is pinned. Three real cases floated in the session 30-32 defaults and are pinned now: func_0021cfc8's
`D_003F5C18[i]` for i < 6 (D_003F5C20 ... 2C, the menu), func_0011e1c8's fifth slot of D_004E39F8 (D_004E3A1C) and the
script VM's byte variables (func_001c0f30 reads D_003C39B0 / D_003C39F0 / D_003C3A30 through D_003C2D30[idx]). The
other 21 of session 32's 26 names were read case by case and are not reached (D_0054C218 is pinned anyway;
docs/shiftable-plan.md "Session 33: reach_check" has the table). What idx-span cannot see: an index from a byte or halfword field whose values the game
keeps small (party ids, TIM2 types). The one such read that lands outside its table, func_00209f70's
D_003F3150[0xFF] for an empty party slot, hits D_003F3530, which stays in place (float_keep.txt). If a boot breaks in
script-driven scenes with session 30-32's layouts but not session 33's, the VM variables were the cause.

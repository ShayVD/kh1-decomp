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

Session 30's default (2,100 float) and session 31's (2,047 float) were never booted. Boot the current
default first; if it fails, rebuild with session 31's three switches (= session 30's default), then add
session 30's switches one at a time. If session 30's default fails and 31's passes, D_003F6770 is the
first suspect.

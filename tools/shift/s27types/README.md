# s27types: fold cast views of data pieces into one struct (session 27)

Run each with `python3 -I` from the repo root.  Scratch goes to `/tmp/s27types`
(`$S27_DIR`); `-S` comparisons are against a `git archive HEAD` copy there.

- `s27_survey.py [--files] [D_X..]` / `--summary [--views]`: cast uses of each piece
  (basic / shared / view).
- `s27_fold.py [--apply] [--name S] [--only F..] [--skip F..] D_X`: the fold.  Phase 1
  renames every view field to a tmp name and finds the used ones from compiler
  errors; layouts come from a probe compile; `s27_merge.py` merges the views by
  offset into one struct; phase 2 renames the accesses and strips the casts.
  Modes tried in order: full (declaration becomes the struct), split (struct in
  `D_X_s.h`, piece header keeps a forward typedef) and keep (declaration unchanged,
  folded users cast to the struct).  Every user is `-S` checked; failing users are
  dropped and the fold rerun.  `S27_DEBUG=1` dumps to `/tmp/s27types/dbg/`.
- `s27_batch.py D_X..`: fold several pieces, log to `/tmp/s27types/batch/D_X.log`.
- `s27_reasons.py [--per-piece]`: why users stayed unfolded (from the logs).
- `s27_trim.py [--apply] D_X..`: drop basic-type casts users no longer need.
- `s27_unfold.py`: put a piece back in its session-26 cast form (for a refold).
- `s27_check.py`: `-S` of changed .c files and includers of changed headers vs HEAD.
- `s27_hdrcheck.py [REF]`: changed piece headers compile on their own.
- libs: `s27lib.py` (recipes, compile, asm compare), `s27_ctext.py` (C text),
  `s27_layout.py` (types and layout by probe), `s27_merge.py`.

`make` stays the final check (byte-identical).  Notes: `NOTES.md`.

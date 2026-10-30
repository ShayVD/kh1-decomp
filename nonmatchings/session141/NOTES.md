# Session 141 near misses (overlays)

Drafts kept here are the best versions found; each file's first comment says what is left.
`python3 tools/ovl/hand.py try OVL FUNC FILE` reproduces the score.

| Overlay | Function | Left | What is different |
|---|---|---|---|
| xs_genie | func_00f218f8 | 2 words | `lui s4` (gcse's hoisted %hi of D_00FC1DD0) is scheduled before `move s0,sp`; the original has them the other way round. goto / while / for / if-else forms and init orders tried. |
| xs_genie | func_00f22078 | score 74 | the outer search loop is not strength-reduced in the original (i*416 recomputed each pass); every loop form tried here strength-reduces it. Inner copy loop matches with an inline allocator. |
| xs_mushu | func_00f20550 | 2 words | the original loads `o->eff` before D_00F21380 for the src store. |
| xs_tink | func_00f20818 | score 35 | jump threading past the tail's null check and an unfilled `blez` slot (see the file). |

# Session 131b: overlay hand matching (the 11 overlays other than dktitle)

752 -> 1,465 / 2,051 functions, every overlay byte-identical (`make ovl`). Work done by
the main thread plus four parallel workers (wm below / above 0x00f48000, gb, dkmovie with
the small overlays), three rounds each. How-to and tricks: docs/overlays.md "Hand matching".
The main ELF's 7 holdouts are unchanged (compiler-pass limits, docs/next-session.md).

## Probably not C (or not this compiler's)

- gb func_00f50db0, wm func_00f77ea8: an endless loop calling func_0024e468(1) with no
  frame and no $ra save; gcc 2.96 always saves $ra around the call (noreturn does not help).
- dkmovie func_00f205a4 / func_00f205f4: hand-written sq / daddiu copy loops.
- gb func_00f50be8 / func_00f50c58: fragments of a bigger function (layout question).

## Near misses (words or objdiff score left; drafts were in the session's scratch)

| Function | Left |
|---|---|
| wm f5c1c8 | 1 word: `bltz` vs our `bltzl` in the second loop's range check |
| wm f78838 | 1 word: `addu v0,s4,v0` operand order in the align-up return |
| wm f2b4b8 | 1 word: the original reloads `lb v0,0(a0)` at loop entry |
| dkmovie f21da0 | 1 word: `bnel` vs `bne` at the sceCdDiskReady==2 test (nosib) |
| wm f39ef0, f2d360 | final `jr ra` delay slot left unfilled in ours |
| wm f5acf0 | final `lw` not moved into the `jr ra` slot |
| wm f2c910 | 2 words: `sd ra` / `sll s2` swapped in the prologue |
| wm f7cb60 | 2 words: delay-slot order of two stores in the else branch |
| xs_genie f218f8 | 2 words: `lui s4` / `move s0,sp` order before the fetch loop |
| xl_limit f20ff0 | 2 words: a0/a1 swapped for two %hi in the trailing stores |
| gb f35288, f34ea8 | 3 words: two `base + i*12` adds CSE'd into one in ours |
| wm f3a030 | 3 words: `4(s2)` addressing, ours folds the +4 into the base |
| wm f355a8, f5e178 | v0/v1 swapped on two lui temporaries |
| wm f323b8, f2f020 | FP register swap only ($f1/$f3, $f0/$f1) |
| wm f3bc48 | 5 words: `i++` in the bne slot, one store pair swapped |
| xl_limit f202d8 | wants nofill and nosib together (no such mode) plus a cross-jumped duplicate call |
| gb f25a68, wm f4cb60 | angle-wrap helpers: register allocation / volatile store in a likely slot |
| gb f240f0 / f24160 / f24570 / f24680 / f246e0 | tile/kind family: extra `move` copies, likely an inlined helper |
| wm f4dda0 / f4dca0 / f4d618, gb f26ca8 / f26a78 | GS packet builders: arguments copied to s-registers then shifted |
| wm f69278 = f79700 (twins) | 64-bit packet values split into 32-bit stores |
| dkmovie f22290, f25658, f23750 | register allocation only (s1/s3, s0/s1/s2, spill choice) |
| dkmovie f25288 | &D_00F28460 CSE'd across a join; the original reloads it |

Worker yields fell from about 50-100 per worker in round 1 to 7-19 in round 3: what is
left is mostly register allocation, scheduling and large functions.

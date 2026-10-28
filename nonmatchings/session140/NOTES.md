# Session 140 matching notes

xl_limit.x: 69 -> 74 / 76 matched (`make ovl OVL=xl_limit` byte-identical).

Matched (ovl/xl_limit/hand/):

- **func_00f202d8** (turn a direction toward a target, clamped to 5 degrees a frame): plain C from m2c
  with real types; the only fix was the literal: `0.087266453f` gives 0x3DB2B8C1 (`0.08726645f` is
  one ulp low). It needs no nofill or nosib: session 131b's "cross-jumped duplicate call" is only
  reorg taking `move a0,s1` from the join into the `b` delay slot.
- **func_00f20400.nostrict.c** (homing shot update): nostrict for the reload of `o->eff` after the
  stores through it; the end is `if (timer > 0) {...} else if (res == NULL || (res->state & 3) != 1)
  return 4; return 0;`.
- **func_00f206e8.nostrict.c** (spawns n shots in a ring): nostrict, pi/2 spelled `1.5707962f`
  (0x3FC90FD9), and `o->eff = 0` after the `o->turn = rand...` store.
- **func_00f20ae0.nostrict.c** (state 5 of the limit object): nostrict; the Mot pointer fetched before
  the flag OR; `f32 *sc = fx->scale; sc[2] = sc[1] = sc[0] = s` order (sc[2], sc[1], sc[0]); the sin
  argument split (`s = (t - 10) / 40; s = sinf(s * pi * 0.5f) * 3`); and a `CONTEXT_ONLY` empty
  definition of func_00f208f8 above it (callee defined above: `bc1f` with `lui` in the slot instead
  of `bc1fl`).
- **func_00f21e60** (1,448 bytes, the camera path of the limit cutscene): written from m2c's phase
  chain as `else if ((t -= N) < M)`; what it took: the quotient kept in the variable
  (`k = t / 70; k = ...cosf(k * pi)`), `D_002E2780[3] = D_002E2790[3] = 1.0f`, the two closing
  `[3] = 1.0f` stores E90 first, and the last phase inverted with the failure path inside it
  (`else if (!((t -= 120) < 50)) { end: func_00133708(); return 4; } else {...}`, the top check
  `goto end`).

Near misses (nonmatchings/session140/xl_limit/):

- **func_00f20e10.nostrict.c**, 2 words: `mtc1 zero,$f21` / `li s3,10` swapped in the >= 60 default
  block. It needs a `KH1_REG("s4")` pin on `mot` (without it, s0/s4 swap: 15 words). The flat
  if/else-if chain gets the registers right but gcc cross-jumps the identical `< 40` and default
  blocks; the nested form (`else { kind = 5; if (< 60) ... else ... }`) avoids the cross jump but
  swaps the registers. A 4-minute decomp-permuter run on the flat form found nothing.
- **func_00f225b0.norlo.c**, about 90 words (score 60): `norlo` gives the count-up loop and the
  in-loop float constants. The original also hoists all three `%hi` luis (s5-s7, frame 112 against
  our 96) and keeps a copy (s3) of the res slot pointer. That looks like `-fno-rerun-loop-opt` plus
  `-fmove-all-movables` (checked with ee-gcc -S: that pair hoists D_00F23FA0's lui), and there is
  no such mode in kh1.toml. Also the second loop's `bnezl` (ours `bnez`).

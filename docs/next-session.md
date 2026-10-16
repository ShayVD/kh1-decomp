# Next session prompt

Paste this to start the next session.

---

Continue kh1-decomp (Kingdom Hearts PS2 matching decomp, target Kingdom Hearts
Final Mix, `SLPS_251.98`). Read README.md and everything in docs/ first; they
are the only notes carried between sessions.

Where we stopped (end of session 1):
- Repo skeleton builds; `make toolchain && make test` passes. Build model is
  kh2-style patch-in-place (tools/kh1tool.py) with objdiff units, a progress
  tracker (`make progress-update`), a no-assets guard and CI.
- Compiler identified as **ee-gcc 2.96-ee-001003-1, -O2 -G0**: 8/8 probe
  functions matched at objdiff 100% (tests/toolchain_probe/probe.c). This was
  measured on a fan-translation-patched ELF, because the patcher replaces the
  game's ELF and no retail copy was available yet.
- Not pinned yet: retail SHA-256, layout.tsv, segments, progress baseline.
- GitHub: the user wants a public repo under ShayVD, created after the target
  is pinned. Confirm before creating it.

Do next:
1. Get the unmodified retail `SLPS_251.98` (from the user's own Final Mix
   disc/ISO). `make check`, then pin serial + SHA-256 in kh1.toml and
   docs/target-versions.md.
2. Re-run the probes against it (tests/toolchain_probe/README.md) and mark the
   compiler confirmed in docs/toolchain.md.
3. `make layout`, sanity-check boundaries, define [[segment]]s (game code vs
   SCE 2.5.0 libs vs libgcc), `make progress-update`, commit.
4. Create the public GitHub repo and push.

# Next session prompt

Paste this to start the next session.

---

Continue kh1-decomp (Kingdom Hearts PS2 matching decomp, target Kingdom Hearts
Final Mix). Read README.md and everything in docs/ first; they are the only
notes carried between sessions.

Where we stopped (end of session 1):
- Target: Final Mix recommended and accepted in principle. The exact serial
  (SLPS-25198 / 25197 / SLPM-66123) and the SHA-256 are still unpinned in
  kh1.toml because the dump had not been supplied yet.
- Repo skeleton builds and its self-tests pass (`make toolchain && make test`).
  Build model: kh2-style patch-in-place (tools/kh1tool.py), objdiff units,
  progress tracker (`make progress-update`), no-assets guard, CI.
- Toolchain: decomp.me ee-gcc builds + Ubuntu binutils-mips-linux-gnu +
  objdiff-cli 3.7.0. ee-gcc 2.96 is the default candidate; 3.2 is ruled out
  by date. Fingerprints for telling 2.9-99xxxx / 2.96 / 3.2 apart are in
  docs/toolchain.md.

Do next:
1. With the ELF in the repo root: `make check`, then pin serial + SHA-256 in
   kh1.toml and docs/target-versions.md.
2. Step 3 of session 1: identify the compiler (strings, .comment, SCE library
   banners, codegen fingerprints), then match 3-5 small functions and record
   the result in docs/toolchain.md "Confirmed". Ask before committing the
   project to a compiler.
3. `make layout`, sanity-check function boundaries, define [[segment]]s
   (game code vs SCE libs vs libgcc), `make progress-update`.

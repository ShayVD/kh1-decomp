# Matching helpers (session 5)

Ad-hoc scripts the session 5 workers used. Several still have hard-coded scratch paths (/tmp/claude-0/s/...) and need small edits before reuse. See docs/worker-brief.md for how each is used.

- wqb03_rr.py, c07_rr.py: `try` with rodata placed at its real address. Use them for jump tables and literals.
- cons2_probe.py: tests the callee-defined-above effect with stubs.
- cons2_fperm.py: tries float-argument positions in prototypes.
- c00_hill2.py, c11_hill3.py: hill-climb statement order between `/*P*/` and `/*Q*/` markers. hill3 keeps dependencies intact.
- cons2_blkperm.py: random statement reorder.
- cons2_rtry.py: named variant tests.
- c00_vt2.py, c16_subst.py: run variant templates in parallel.
- c00_sdiff.py, c05b_sd.py: sequence diffs that ignore register names and branch targets.
- c05b_prio.py: global-alloc priority per variable, from -dl/-dg dumps.
- c08_dump.py: gcc RTL dumps.
- cons2_sweep.py: sweeps the prototype-deletion and field-type tricks over many drafts.
- c14_oneoff.py: deletes each callee prototype in turn.
- cons2_autofix.py: merges code into an existing file, resolving typedef and extern conflicts.

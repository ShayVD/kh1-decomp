Compiler identification probes from session 1 (docs/toolchain.md). Not built
by default. To re-run against a target ELF, copy `probe.c` into `src/`, set
`text_start = "0x00100000"` / `text_end = "0x00272c70"` in kh1.toml, run
`make layout && make verify`, then remove it again. Addresses come from the
patched ELF and must be re-checked against the retail one.

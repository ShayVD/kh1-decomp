Decompiled code. Every `.c`/`.cpp`/`.s` file under `src/` is built
automatically. Each function must either be named `func_XXXXXXXX` (original
address) or have an entry in `functions.tsv`. Mirror the original source tree
once it is known; `src/anon/` holds functions whose original file is unknown.

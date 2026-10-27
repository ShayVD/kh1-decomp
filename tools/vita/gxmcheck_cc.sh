#!/usr/bin/env bash
# tools/vita/gxmcheck.sh's compiler for census.py: gcc as given; the runner's link is made a second time as
# out/gxmcheck/kh1-gxmcheck with the GPU renderer and its stand-in added.
set -e
gcc "$@"
for a in "$@"; do
  if [[ "$a" == *out/host/kh1-host ]]; then
    args=()
    for b in "$@"; do [[ "$b" == *out/host/kh1-host ]] && args+=("${b%/host/kh1-host}/gxmcheck/kh1-gxmcheck") || args+=("$b"); done
    gcc "${args[@]}" out/gxmcheck/gxm.o out/gxmcheck/gxm_mock.o 2> out/gxmcheck/link.log
  fi
done

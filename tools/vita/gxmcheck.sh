#!/usr/bin/env bash
# The Vita's GPU renderer (host/vita/gxm.c) run inside the host runner on a software stand-in for sceGxm
# (tests/host/gxm_mock.c), its display target compared with the GS model's picture (docs/vita-build.md "GPU").
# Needs vitasdk's headers ($VITASDK, default /usr/local/vitasdk), a PS2 `make` and `make host-census` first.
#   tools/vita/gxmcheck.sh [ISO] [FRAMES] [EVERY]     # default: out/fd/fake.iso, 1500 frames, every 100th
# Extra environment for the run passes through (KH1_HOST_GXM_POINT=1, KH1_HOST_GXM_PPM=DIR, KH1_HOST_PAD ...).
set -euo pipefail
ROOT="$(cd "$(dirname "$0")/../.." && pwd)"
cd "$ROOT"
VITASDK="${VITASDK:-/usr/local/vitasdk}"
ISO="${1:-out/fd/fake.iso}"
FRAMES="${2:-1500}"
EVERY="${3:-100}"
OUT=out/gxmcheck
mkdir -p "$OUT" "$OUT/shots"
[[ -f out/host/kh1-host ]] || { echo "gxmcheck: make host-census first" >&2; exit 1; }
CF=(-m32 -malign-double -std=gnu99 -O2 -w -DKH1_HOST -Iinclude -Isrc -Ihost/null -Ihost/vita -I"$VITASDK/arm-vita-eabi/include")
gcc "${CF[@]}" -c host/vita/gxm.c -o "$OUT/gxm.o"
gcc "${CF[@]}" -c tests/host/gxm_mock.c -o "$OUT/gxm_mock.o"
# the host runner's own link (census.py), with the two objects added
HOST_CC="$ROOT/tools/vita/gxmcheck_cc.sh" python3 -I tools/host/census.py --exe > "$OUT/census.log"
[[ -x "$OUT/kh1-gxmcheck" ]] || { echo "gxmcheck: the link failed (out/gxmcheck/link.log)" >&2; exit 1; }
KH1_HOST_ISO="$ISO" KH1_HOST_FRAMES="$FRAMES" KH1_HOST_TRACE=5 KH1_HOST_QUIET=1 KH1_HOST_SHOT="${KH1_HOST_SHOT:-8:6::$OUT/shots}" \
  KH1_HOST_GXM="$EVERY" "$OUT/kh1-gxmcheck" > "$OUT/run.log" 2>&1 || true
grep -E '^kh1-gxm' "$OUT/run.log"

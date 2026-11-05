#!/usr/bin/env bash
# Run the Vita build on a real PS Vita over Wi-Fi and fetch its log: vita-port-kit's runner
# (third_party/vita-port-kit/vita/tools/hw_run.sh, docs/vita-port-kit.md) with this game's settings (tools/vita/hw.game).
#   VITA_IP=... PAD=tests/host/pads/dive_en.txt tools/vita/hw_run.sh out/hw/a 1800 frames=11600 renderer=native
#   tools/vita/hw_run.sh --restore      put back what a killed run left
# VPK=FILE runs another build than out/vita/kh1-decomp.vpk; PAD and VPK need absolute paths or paths from here.
root=$(cd "$(dirname "$0")/../.." && pwd)
HW_GAME=$root/tools/vita/hw.game exec "$root/third_party/vita-port-kit/vita/tools/hw_run.sh" "$@"

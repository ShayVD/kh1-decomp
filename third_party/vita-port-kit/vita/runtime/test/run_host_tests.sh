#!/usr/bin/env bash
# The vita/runtime modules' host tests, with CC (default cc), RUN (a runner such as qemu-arm) and extra flags:
#   vita/runtime/test/run_host_tests.sh [-m32]
#   CC=arm-linux-gnueabihf-gcc RUN="qemu-arm -L /usr/arm-linux-gnueabihf" vita/runtime/test/run_host_tests.sh
set -euo pipefail
r=$(cd "$(dirname "$0")/.." && pwd)
cc=${CC:-cc}
run=(${RUN:-})
o=$(mktemp -d "${TMPDIR:-/tmp}/vpk_tests.XXXXXX")
trap 'rm -rf "$o"' EXIT
flags=(-std=gnu99 -O1 -Wall -Wextra -Werror -U_FORTIFY_SOURCE "$@") # fortified printf calls __printf_chk, past vpk_log_stdio.c
$cc "${flags[@]}" -I"$r/costack" "$r/costack/vpk_costack.c" "$r/costack/test/costack_test.c" -o "$o/costack" && ${run[@]+"${run[@]}"} "$o/costack" > /dev/null && echo "costack_test: ok"
$cc "${flags[@]}" -I"$r/audioout" "$r/audioout/vpk_audio_ring.c" "$r/audioout/test/audio_ring_test.c" -lm -o "$o/audio_ring" && ${run[@]+"${run[@]}"} "$o/audio_ring" | tail -n 1
$cc "${flags[@]}" -I"$r/test/fake_psp2" -I"$r/audioout" "$r/audioout/vpk_audio_ring.c" "$r/audioout/vpk_audio_out.c" "$r/audioout/test/audio_out_test.c" -o "$o/audio_out" && ${run[@]+"${run[@]}"} "$o/audio_out"
$cc "${flags[@]}" -I"$r/config" "$r/config/vpk_config.c" "$r/config/test/config_test.c" -o "$o/config" && (cd "$o" && ${run[@]+"${run[@]}"} ./config)
$cc "${flags[@]}" -Wno-unused-parameter -DVPK_LOG_NO_STDIO_REDIRECT -I"$r/test/fake_psp2" \
  "$r/log/vpk_log.c" "$r/log/vpk_log_stdio.c" "$r/clocks/vpk_clocks.c" "$r/watchdog/vpk_watchdog.c" \
  "$r/procparam/vpk_procparam.c" "$r/costack/vpk_costack.c" "$r/test/vita_modules_test.c" -o "$o/vita_modules"
${run[@]+"${run[@]}"} "$o/vita_modules"

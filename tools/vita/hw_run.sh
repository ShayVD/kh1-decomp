#!/usr/bin/env bash
# Run the Vita build on a real PS Vita over Wi-Fi until config.txt's frames= stops it (or a timeout), and
# fetch its log (docs/vita-build.md "Hardware runs over vitacompanion"). Adapted from the spyro-vita
# project's tools/vita/hw_run.sh (its decision D77), cut down to what kh1-decomp needs.
#   tools/vita/hw_run.sh OUT_DIR [TIMEOUT_S] [config line]...
#   PAD=tests/host/pads/dive_en.txt tools/vita/hw_run.sh out/hw/a 1800 frames=11600 renderer=native natvbjoin=0
# The Vita: VITA_IP, or tools/vita/hw.env (gitignored; VITA_IP=192.168.1.23), with vitacompanion running
# (FTP on 1337, commands on 1338; 1.05's "kill" or 1.06+'s "quit"). The app (KHDC00001) must be installed
# once with VitaShell; each run uploads only the VPK's eboot.bin (VPK=FILE, default out/vita/kh1-decomp.vpk).
# The owner's ux0:data/kh1/config.txt and kh1.log are renamed to NAME.hw-backup for the run and put back
# when the script ends, however it ends (--restore puts back what a killed run left). The run's config.txt is
# the owner's lines, then the arguments (later lines win). PAD=FILE uploads a host pad script as
# ux0:data/kh1/hw-pad.txt and adds pad=. The disc image and everything else are never touched.
# Exit status 0 only when the run reached frames=.
set -euo pipefail
root=$(cd "$(dirname "$0")/../.." && pwd)
# shellcheck source=/dev/null
[ -z "${VITA_IP:-}" ] && [ -f "$root/tools/vita/hw.env" ] && . "$root/tools/vita/hw.env"
: "${VITA_IP:?set VITA_IP or write it in tools/vita/hw.env}"
export VITA_IP VITA_FTP_PORT VITA_CMD_PORT
restore_only=0
[ "${1:-}" = --restore ] && { restore_only=1; set -- "${TMPDIR:-/tmp}/kh1-hw-restore"; }
out=${1:?usage: hw_run.sh OUT_DIR [TIMEOUT_S] [config line]...}; shift
timeout=${1:-1800}; [ $# -gt 0 ] && shift
vpk=${VPK:-$root/out/vita/kh1-decomp.vpk}
data=ux0:data/kh1
app=ux0:app/KHDC00001
names=(config.txt kh1.log hw-pad.txt)
mkdir -p "$out"
out=$(cd "$out" && pwd)
tmp=$(mktemp -d "${TMPDIR:-/tmp}/kh1_hw.XXXXXX")
v() { python3 -I "$root/tools/vita/hw_ftp.py" "$@"; }
say() { echo "hw_run: $*" | tee -a "$out/hw-run.txt"; }
listing=
relist() { listing=$(v ls "$data"); }
kind() { awk -v n="$1" '{ name = $0; sub(/^[df] [0-9]+ /, "", name); if (name == n) { print $1; exit } }' <<< "$listing"; }

recover() {
  relist
  local n
  for n in "${names[@]}"; do
    [ -n "$(kind "$n.hw-backup")" ] || continue
    [ -n "$(kind "$n")" ] && v mv "$data/$n" "$data/$n.hw-left-$(date +%Y%m%d-%H%M%S)"
    v mv "$data/$n.hw-backup" "$data/$n"
    say "put back $n from a run that couldn't"
  done
}

quit=quit
stopped=0
stop_app() {
  [ "$stopped" = 1 ] && return 0
  stopped=1
  v cmd "$quit" KHDC00001 > /dev/null 2>&1 || true
  sleep 3
}
moved=()
absent=()
setup_done=0
launched=0
cleanup() {
  local rc=$? n ok=1
  trap '' INT TERM HUP
  if [ "$setup_done" = 1 ]; then
    stop_app
    [ "$launched" = 1 ] && { v get "$data/kh1.log" "$out/kh1.log" 2>/dev/null || true; }
    relist || true
    for n in ${moved[@]+"${moved[@]}"} ${absent[@]+"${absent[@]}"}; do
      case $(kind "$n") in f) v rm "$data/$n" || ok=0 ;; esac
    done
    for n in ${moved[@]+"${moved[@]}"}; do v mv "$data/$n.hw-backup" "$data/$n" || ok=0; done
    [ $ok = 1 ] && say "your files in $data are back as they were" ||
      say "NOT ALL PUT BACK: see $data/*.hw-backup; tools/vita/hw_run.sh --restore"
  fi
  rm -rf "$tmp"
  return $rc
}
trap cleanup EXIT
trap 'exit 130' INT
trap 'exit 143' TERM HUP

: > "$out/hw-run.txt"
help=$(v cmd help) || { say "no reply on $VITA_IP:${VITA_CMD_PORT:-1338}: is the Vita awake, with vitacompanion loaded?"; exit 1; }
has() { awk -v c="$1" '$1 == c { f = 1 } END { exit !f }' <<< "$help"; }
if has quit; then quit=quit; elif has kill; then quit=kill; else say "vitacompanion has neither quit nor kill"; exit 1; fi
v cmd "$quit" KHDC00001 > /dev/null 2>&1 || true
sleep 2
recover
[ $restore_only = 1 ] && exit 0

[ -f "$vpk" ] || { say "no $vpk"; exit 1; }
v size "$app/eboot.bin" > /dev/null || { say "KHDC00001 isn't installed: install a kh1-decomp VPK once with VitaShell"; exit 1; }
mkdir -p "$tmp/vpk"
(cd "$tmp/vpk" && unzip -q "$vpk" eboot.bin)
v put "$tmp/vpk/eboot.bin" "$app/eboot.bin"
say "app: eboot.bin ($(wc -c < "$tmp/vpk/eboot.bin" | tr -d ' ') bytes) from $(basename "$vpk")"

relist
[ "$(kind config.txt)" = f ] && v get "$data/config.txt" "$tmp/owner-config.txt"
for n in "${names[@]}"; do
  if [ -n "$(kind "$n")" ]; then v mv "$data/$n" "$data/$n.hw-backup"; moved+=("$n"); else absent+=("$n"); fi
done
setup_done=1
cfg=$out/config.txt
: > "$cfg"
[ -f "$tmp/owner-config.txt" ] && grep -vE '^[[:space:]]*pad=' "$tmp/owner-config.txt" >> "$cfg" || true
echo >> "$cfg"
for line in "$@"; do echo "$line" >> "$cfg"; done
if [ -n "${PAD:-}" ]; then
  cp "$PAD" "$out/pad.txt"
  v put "$PAD" "$data/hw-pad.txt"
  echo "pad=$data/hw-pad.txt" >> "$cfg"
fi
v put "$cfg" "$data/config.txt"
dumps() { v ls ux0:data | awk '$1 == "f" && $3 ~ /^psp2core-.*\.psp2dmp$/ { print $3 }'; }
before=$(dumps)

v cmd screen on > /dev/null 2>&1 || true
say "launch: $(v cmd launch KHDC00001)"
launched=1
# No FTP while the game runs: polling it every 10 s wedged vitacompanion 1.05's FTP at frame ~900 (2026-11-02;
# it also wedged once with the game closed, after many connections in a few minutes: keep them few). Wait
# HW_QUIET_S (default 360: the Dive's 11,600 frames took ~5 min) without touching the Vita, then look for the
# log's "frames: stop" every 30 s (the app exits itself there).
quiet=${HW_QUIET_S:-360}
say "waiting ${quiet}s without touching the Vita"
sleep "$quiet"
t=$quiet fails=0 how="timeout (${timeout}s)"
while [ "$t" -lt "$timeout" ]; do
  sleep 30; t=$((t + 30))
  if v get "$data/kh1.log" "$out/kh1.log" 2>/dev/null; then
    fails=0
    grep -q 'frames: stop' "$out/kh1.log" && { how="frames= reached"; break; }
  else
    fails=$((fails + 1))
    [ $fails -ge 6 ] && { how="no answer from the Vita for $((fails * 30))s"; break; }
  fi
  if [ $((t % 120)) = 0 ] && [ -n "$(comm -13 <(sort <<< "$before") <(dumps | sort) | sed '/^$/d')" ]; then
    how="crashed (a new crash dump in ux0:data)"; break
  fi
done
say "stopped after ${t}s: $how"
stop_app
v get "$data/kh1.log" "$out/kh1.log" 2>/dev/null || say "no kh1.log"
tail -n 3 "$out/kh1.log" 2>/dev/null || true
[ "$how" = "frames= reached" ]

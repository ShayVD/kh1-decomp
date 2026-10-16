#!/usr/bin/env bash
# Fetch the PS2 EE compilers and objdiff-cli into tools/toolchain/ (gitignored).
# Usage: tools/setup_toolchain.sh [compiler-id ...]   (default: the one in kh1.toml)
# Needs: curl, tar, sha256sum, plus on Debian/Ubuntu:
#   sudo dpkg --add-architecture i386 && sudo apt-get update
#   sudo apt-get install libc6:i386 libstdc++5:i386 binutils-mips-linux-gnu
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
DEST="$ROOT/tools/toolchain"
BASE_URL="https://github.com/decompme/compilers/releases/download/compilers"
OBJDIFF_VERSION="3.7.0"
OBJDIFF_SHA256="68b0f6bbbeefccfc4aaa970bc04dfe04bfd1575514972952cf493f251131a8cf"

if [[ $# -eq 0 ]]; then
  set -- "$(python3 "$ROOT/tools/kh1tool.py" config toolchain.compiler)"
fi

mkdir -p "$DEST"
for id in "$@"; do
  line="$(grep -P "^\Q$id\E\t" "$ROOT/tools/toolchains.tsv" || true)"
  [[ -n "$line" ]] || { echo "error: unknown compiler id $id (see tools/toolchains.tsv)" >&2; exit 1; }
  archive="$(cut -f2 <<<"$line")"; sha="$(cut -f3 <<<"$line")"
  if [[ -x "$DEST/$id/bin/ee-gcc" ]]; then echo "ok: $id already installed"; continue; fi
  tmp="$(mktemp -d)"
  echo "fetching $id"
  curl -fsSL -o "$tmp/$archive" "$BASE_URL/$archive"
  echo "$sha  $tmp/$archive" | sha256sum -c --quiet
  mkdir -p "$DEST/$id"
  tar -xf "$tmp/$archive" -C "$DEST/$id"
  rm -rf "$tmp"
  "$DEST/$id/bin/ee-gcc" -dumpversion >/dev/null 2>&1 \
    || { echo "error: $id does not run; install libc6:i386 (and libstdc++5:i386 for 3.x)" >&2; exit 1; }
  echo "ok: $id"
done

if [[ ! -x "$DEST/objdiff-cli" ]]; then
  echo "fetching objdiff-cli $OBJDIFF_VERSION"
  curl -fsSL -o "$DEST/objdiff-cli" \
    "https://github.com/encounter/objdiff/releases/download/v$OBJDIFF_VERSION/objdiff-cli-linux-x86_64"
  echo "$OBJDIFF_SHA256  $DEST/objdiff-cli" | sha256sum -c --quiet
  chmod +x "$DEST/objdiff-cli"
fi

# m2c (https://github.com/matt-kempster/m2c, GPL-3.0): first-draft C for
# `kh1tool.py m2c`. Optional: the build never needs it.
M2C_COMMIT="708d2d2cb2698f091a92492b328f73b24209f72d"
if [[ ! -f "$DEST/m2c/m2c.py" ]]; then
  echo "fetching m2c ${M2C_COMMIT:0:10}"
  if git clone -q https://github.com/matt-kempster/m2c.git "$DEST/m2c" \
      && git -C "$DEST/m2c" checkout -q "$M2C_COMMIT"; then
    python3 -c "import pycparser" 2>/dev/null || echo "note: m2c needs pycparser (python3 -m pip install pycparser)"
  else
    rm -rf "$DEST/m2c"; echo "warning: could not fetch m2c (optional)" >&2
  fi
fi

for tool in as ld objcopy objdump nm; do
  command -v "mips-linux-gnu-$tool" >/dev/null || { echo "error: missing mips-linux-gnu-$tool (apt install binutils-mips-linux-gnu)" >&2; exit 1; }
done
echo "toolchain ready in $DEST"

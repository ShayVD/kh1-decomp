#!/usr/bin/env bash
# Refuse to commit game data. Fails if any tracked (or staged) file is an ELF
# executable, a disc image, or larger than 512 KiB. Run in CI and as a
# pre-commit hook:  ln -s ../../tools/check_no_assets.sh .git/hooks/pre-commit
set -euo pipefail
cd "$(git rev-parse --show-toplevel)"
fail=0
while IFS= read -r -d '' f; do
  [[ -f "$f" ]] || continue
  size=$(stat -c %s "$f")
  magic=$(head -c 4 "$f" | od -An -tx1 | tr -d ' \n')
  if [[ "$magic" == "7f454c46" ]]; then
    echo "refused: $f is an ELF binary"; fail=1
  elif head -c 40000 "$f" | tail -c +32770 | head -c 5 | grep -q "CD001"; then
    echo "refused: $f looks like a disc image"; fail=1
  elif (( size > 524288 )); then
    echo "refused: $f is $size bytes (game data?)"; fail=1
  fi
done < <(git ls-files -z --cached)
exit $fail

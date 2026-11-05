#!/usr/bin/env bash
# Can tools/vita/hw_run.sh reach the Vita (read only): vita-port-kit's hw_check.sh with this game's settings.
root=$(cd "$(dirname "$0")/../.." && pwd)
HW_GAME=$root/tools/vita/hw.game exec "$root/third_party/vita-port-kit/vita/tools/hw_check.sh" "$@"

#!/usr/bin/env bash
# Read-only local inventory. No downloads, uploads, installs or printer I/O.
set -euo pipefail
printf '%s\n' '=== Installed Canon-related packages (local only) ==='
if command -v pacman >/dev/null 2>&1; then
  pacman -Q 2>/dev/null | grep -Ei '(^|[[:space:]])(cnrdrv|canon|carps|cndr)' || true
elif command -v dpkg-query >/dev/null 2>&1; then
  dpkg-query -W -f='${Package} ${Version}\n' 2>/dev/null | grep -Ei 'canon|carps|cnrdrv' || true
fi
printf '\n%s\n' '=== Candidate archives under Downloads (first 80) ==='
if [[ -d "$HOME/Downloads" ]]; then
  find "$HOME/Downloads" -maxdepth 5 -type f \
    \( -iname '*carps*' -o -iname '*cnrdrv*' -o -iname '*canon*' \) \
    -print 2>/dev/null | head -n 80 || true
fi
printf '\n%s\n' '=== Installed CUPS executables with matching names ==='
for dir in /usr/lib/cups/filter /usr/lib64/cups/filter /usr/lib/cups/backend; do
  [[ -d "$dir" ]] || continue
  find "$dir" -maxdepth 1 -type f \
    \( -iname '*carps*' -o -iname '*sfp*' -o -iname '*canon*' \) \
    -printf '%p (%s bytes)\n' 2>/dev/null || true
done
printf '\n%s\n' '=== Printer devices (may show local device names) ==='
if command -v lpstat >/dev/null 2>&1; then lpstat -v 2>/dev/null || true; fi
printf '\n%s\n' 'No files were changed or uploaded. Review output before sharing it.'

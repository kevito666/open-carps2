#!/usr/bin/env bash
# Explicit local publish. Does not add any files except the manifest below.
set -euo pipefail
ROOT="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$ROOT"
for cmd in git gh make; do
  command -v "$cmd" >/dev/null 2>&1 || { echo "Missing executable: $cmd" >&2; exit 1; }
done
if [[ -e .git && ! -d .git ]]; then
  echo 'Local git metadata exists but is not a directory; aborting.' >&2
  exit 1
fi
if git rev-parse --is-inside-work-tree >/dev/null 2>&1; then
  if git remote get-url origin >/dev/null 2>&1; then
    echo 'origin already configured. Review it manually; aborting.' >&2
    exit 1
  fi
fi
if gh repo view kevito666/open-carps2 >/dev/null 2>&1; then
  echo 'GitHub repository already exists. Aborting rather than overwriting.' >&2
  exit 1
fi
if ! gh auth status >/dev/null 2>&1; then
  echo 'GitHub CLI is not authenticated. Run: gh auth login' >&2
  exit 1
fi
make test >/dev/null
printf 'Create a PUBLIC repository at github.com/kevito666/open-carps2?\n'
printf 'Only documented project code and metadata will be committed.\n'
read -r -p 'Type YES to continue: ' choice
[[ "$choice" == 'YES' ]] || { echo 'Cancelled.'; exit 1; }
if [[ ! -d .git ]]; then git init -b main; fi
# Whitelist: do not use `git add -A`; vendor payloads may be present in working tree.
git add -- .gitignore .gitattributes LICENSE README.md COMPATIBILITY.md \
  CONTRIBUTING.md SECURITY.md Makefile include src tests docs scripts .github
printf '\nFiles staged for public release:\n'
git diff --cached --name-only
if [[ -n "$(git diff --cached --name-only | grep -Ei '\.(so|deb|rpm|zip|tar|bin|ppd|pcap)(\.|$)' || true)" ]]; then
  echo 'Potential binary/vendor content staged. Review and unstage before proceeding.' >&2
  exit 1
fi
if ! git diff --cached --quiet; then
  git commit -m 'Initial project scaffold and CARPS2 target roadmap'
fi
gh repo create kevito666/open-carps2 --public --source=. --remote=origin --push \
  --description 'Independent experimental Linux driver project for Canon CARPS2 laser printers'
# Publish the roadmap as GitHub issues; the README remains authoritative if an API call fails.
gh issue create --repo kevito666/open-carps2 --title 'P0: Identify CARPS2 framing and implement an LBP6040 single-page encoder' --body 'Reference hardware: LBP6040. Audit original driver dependencies and permitted observations; establish self-authored test pages, byte-level notes, deterministic encoder fixtures, and an opt-in hardware test path. Done only after an actual monochrome one-page print test.' || true
gh issue create --repo kevito666/open-carps2 --title 'P1: Validate LBP6030 against the baseline' --body 'Research target only. Verify hardware identity and compatibility empirically; do not infer functional compatibility from shared USB ID or Canon package. Document model/firmware/transport and test results.' || true
gh issue create --repo kevito666/open-carps2 --title 'P2: Add LBP6230 and LBP6240 profiles' --body 'Research target only. Verify format differences, duplex/media settings, and working monochrome output independently on each model.' || true
gh issue create --repo kevito666/open-carps2 --title 'P3: Investigate LBP8100 support' --body 'Research target only. Record the device identity, engine constraints, and compatibility tests before claiming support.' || true
gh issue create --repo kevito666/open-carps2 --title 'P4: Investigate LBP7100C and LBP7110C color output' --body 'Research target only. Determine color plane organization, halftoning, and job framing independently; do not claim color printing until tested.' || true
gh issue create --repo kevito666/open-carps2 --title 'Audit licensing and separate open components from Canon binaries' --body 'Inventory current CUPS filter chain, all license files and dependencies. Do not upload copyrighted vendor components to Git. Record provenance for anything imported.' || true
gh issue create --repo kevito666/open-carps2 --title 'Modern IPP Printer Application design (PAPPL)' --body 'Plan native Printer Application architecture after raster/protocol encoder works. Keep classic CUPS filter compatibility during initial bring-up.' || true
echo 'Published: https://github.com/kevito666/open-carps2' 

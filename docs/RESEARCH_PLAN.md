# Protocol research and clean implementation plan

## Phase 0: collect the evidence

1. Record OS/CUPS/packages, model labels, USB IDs, driver paths and checksum hashes.
2. Audit every vendor-provided component's actual license. A source archive is not
   sufficient permission to copy its contents into an open-source project.
3. Read public documentation and identify independent technical references.
4. Check local legal constraints before analyzing vendor software or protected streams.

## Phase 1: observation and hypothesis

- With independently created, non-sensitive test pages, characterize output behavior:
  blank, solid, bars, text, lines, halftones, A4/Letter, resolutions.
- If permitted, use external USB observation of normal print communication to
  determine job framing and session patterns. Do not bypass access controls or
  cryptographic protections, or republish Canon's implementation.
- Record findings as specifications **in our own words** with confidence and provenance.
- Separate empirically observed bytes from guesses. Never infer model compatibility
  solely from sharing a vendor package.

## Phase 2: implementation

- Build a tiny, deterministic single-page encoder with no USB write function.
- Validate output boundaries, endianness, page dimensions, malformed input and memory.
- Compare permitted test output under controlled conditions; don't ship captured data
  that contains private documents or embedded identifiers.
- Introduce explicit opt-in hardware testing only after file-mode tests pass.

## Phase 3: integration and model expansion

- Preserve the existing vendor queue, create a separate development queue.
- Add one feature at a time; publish test evidence and regression results.
- For each new model, verify USB/network identification, physical output, paper handling,
  cancellation, memory behavior, and fault recovery.

## Provenance ledger

Create an entry for each imported dependency/reference with: name, origin URL, copyright,
license, checksum, test/use scope, and approval status. Keep anything unapproved outside Git.

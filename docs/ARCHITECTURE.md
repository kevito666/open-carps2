# Architecture (planned)

```text
Application/PDF/PS/PNG
       |
       v
CUPS filters / libcupsfilters       (prototype pathway)
       |                            [later PAPPL native Printer Application]
       v
Normalized raster input
       |
       v
open-carps2 raster normalization / media & resolution policy
       |
       v
CARPS2 encoder (TBD) --> page/session framing (TBD)
       |
       v
USB or supported network transport (TBD)
       |
       v
Printer
```

The above is a proposed design, **not implemented**. No claim is made about CARPS2 wire
format, compression, page framing or network transport until independently validated.

## Code boundaries

- `include/open_carps2/`, `src/model.c`: model database and capability flags.
- Future `src/raster/`: byte-validated pixel buffers, grayscale/thresholding, stripes.
- Future `src/protocol/`: independently implemented CARPS2 encoder/decoder (if feasible).
- Future `src/transport/`: USB/network interface; never mingle protocol and I/O.
- Future `src/cups/`: classic CUPS filter for current environments.
- Future `src/ipp/`: native PAPPL Printer Application for CUPS 3.x / driverless clients.

## Engineering rules

- Parse untrusted job content with bounds checks; use explicit integer lengths.
- Keep transport mocks and deterministic fixtures; never require root to unit-test.
- Device I/O only in explicitly named tools, never in import/test routines.
- Never let protocol research code silently operate on the user's working CUPS queue.
- No vendor blobs or downloaded binaries in the tracked source tree.

OpenPrinting guidance: https://openprinting.github.io/cups/drivers.html

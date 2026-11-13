# Test plan

## Current automated tests

`make test` validates model metadata, lookup, and candidate USB identifiers. It does not print.

## Hardware test matrix (future, after encoder exists)

- Connection: local USB, then Wi-Fi/network if actually supported and understood.
- Single-page: empty, 1-dot, vertical/horizontal rules, text, embedded fonts, gradients.
- Page size: A4, Letter, landscape, non-default margins.
- Multi-page: 1/2/10 pages, queues, job cancellation, retry after failure.
- Raster: monochrome, shades/dithering, supported resolutions, clipping and scaling.
- Memory: small/large pages, stream memory ceilings, corrupt/truncated inputs.
- Integration: browser PDF, Evince/Okular, LibreOffice, CLI (`lp`).
- Recovery: USB disconnect/reconnect, out of paper, toner warnings (where observable).
- Model-specific: duplex on capable hardware, color and halftoning after base mono works.

## Passing criteria

Mark a printer `SUPPORTED` only with actual hardware, model, firmware/software version,
transport, test artifact hashes, and known limitations recorded. Passing an encoder unit
fixture alone is never "hardware supported".

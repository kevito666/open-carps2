# open-carps2

**Experimental, independent Linux printing project for selected Canon CARPS2 laser printers.**

The initial reference machine is the Japanese-market Canon LBP6040. The long-term goal is a
free-software printing pipeline, from raster data to a printer-specific stream, without
redistributing Canon's proprietary binaries or copying restricted source code.

> **Not a working printer driver yet.** The initial commit provides a buildable C17 model
> database, documentation, tests, and an environment inventory script. It does not encode
> CARPS2, install a CUPS queue, or send any bytes to a printer.

## Target models

| Phase | Models | Plan | Actual open-carps2 print support |
| --- | --- | --- | --- |
| P0 | LBP6040 | USB baseline, format identification, monochrome encoder | **None; research only** |
| P1 | LBP6030 | Verify whether the baseline implementation can be shared | **None; research only** |
| P2 | LBP6230 / LBP6240 | Compare model capabilities, duplex, format/transport | **None; research only** |
| P3 | LBP8100 | Test engine-specific variations | **None; research only** |
| P4 | LBP7100C / LBP7110C | Investigate color planes, halftoning, registration | **None; research only** |

Canon lists these seven printers under **CARPS2 LBP Printer Driver for Linux v5.10**.
That vendor-driver grouping is *not* proof that all models share a byte-for-byte format.
See [COMPATIBILITY.md](COMPATIBILITY.md) for test criteria and evidence.

Canon's references:
- https://canon.jp/support/software/os/select/lbp/linux-carps2lbp-drv-v510-jptar
- https://faq.canon.jp/app/answers/detail/a_id/78576/

## Building the initial tools (Linux)

```sh
make
make test
./build/open-carps2-info --list
./build/open-carps2-info --model LBP6040
./build/open-carps2-info --match-usb 04a9:2795
```

`--match-usb` lists **candidates** only; multiple printers can share a USB product ID.
There is no print-job submission code here yet.

## Development approach

1. Keep a known-good vendor-driver CUPS queue intact for comparisons. Create a separate
   development queue only after the first format encoder exists.
2. Record installed drivers and licenses using `scripts/find-canon-driver.sh`.
3. Identify public specifications, permissible interoperability observations, and
   independently generated tests. Keep all restricted/vendor artifacts outside Git.
4. Implement parsing/encoding in small C17 modules with repeatable tests and sanitizers.
5. Add conventional CUPS integration for near-term testing and a native IPP Printer
   Application (e.g. PAPPL) as the longer-term supported architecture.
6. Mark hardware print support only after actual tests on that model and transport.

See [docs/ARCHITECTURE.md](docs/ARCHITECTURE.md),
[docs/RESEARCH_PLAN.md](docs/RESEARCH_PLAN.md), and
[docs/TEST_PLAN.md](docs/TEST_PLAN.md).

## Important boundaries

- **No Canon proprietary code, libraries, firmware, PPD files, package archives, or
  copyrighted binaries are bundled in this repository.**
- "Includes source" in a Canon download does *not* automatically mean it is freely
  redistributable or usable as a basis for this project. Audit file-level licenses first.
- Do not upload raw print captures with personal document contents, serial numbers,
  network credentials, or other identifying data.
- CARPS2, Canon, and the model names are Canon-related marks; this project is
  independent and is not affiliated with or endorsed by Canon.

## License

Original code and documentation in this initial repository: [MIT](LICENSE). External
contributions must be independently authored or brought in with a compatible license.

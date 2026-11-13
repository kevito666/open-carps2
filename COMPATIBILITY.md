# Hardware compatibility matrix

**Status of all models on initial import: TARGET / UNTESTED. No native print support yet.**

| Printer | Family | Proposed priority | USB ID recorded? | Verified native printing? | Notes |
| --- | --- | --- | --- | --- | --- |
| LBP6040 | Monochrome | P0 | `04a9:2795` (reported/reference; reconfirm) | No | Primary reference; USB and Wi-Fi variants may differ |
| LBP6030 | Monochrome | P1 | `04a9:2795` (publicly reported; reconfirm) | No | Vendor lists alongside LBP6040 |
| LBP6230 | Monochrome | P2 | `04a9:2796` (public USB-ID report; reconfirm) | No | Compare duplex and transport |
| LBP6240 | Monochrome | P2 | `04a9:2796` (public USB-ID report; reconfirm) | No | Model-specific options unknown |
| LBP8100 | Monochrome | P3 | Unknown | No | Additional engine |
| LBP7100C | Color | P4 | Unknown | No | Color-plane work required |
| LBP7110C | Color | P4 | Unknown | No | Color-plane work required |

Canon's supported-model list: https://canon.jp/support/software/os/select/lbp/linux-carps2lbp-drv-v510-jptar
Canon LBP6040/6030 specification (CARPS2): https://faq.canon.jp/app/answers/detail/a_id/78576/
USB references are identification hints only; don't use an ID alone to claim guaranteed support.

## Support level definitions

- `TARGET`: listed for research; no replacement driver exists yet.
- `DETECTED`: local hardware identity has been checked on actual hardware.
- `ENCODER_TESTED`: deterministic test corpus passes; may not print.
- `HARDWARE_TESTED`: prints the minimal one-page matrix successfully.
- `SUPPORTED`: sustained regression success (graphics, fonts, pages, cancellation,
   error recovery) on named hardware/firmware and connection path.

## Excluded until separately researched

Canon CAPT, UFR II/UFRII LT, LIPS/LIPSLX, and other Canon families are **not**
claimed compatible. Similar product names or vendor packages are not protocol evidence.

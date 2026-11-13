# Security

Printer job files can contain sensitive information. Sanitization comes before sharing.
Do not post raw diagnostic archives, full spool files, firmware, or logs containing
network credentials, serial numbers, personal data, or printed document contents.

The initial software performs **no device I/O**. Hardware experiments must remain opt-in
and must never target an existing production CUPS queue silently.

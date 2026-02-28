# PeriSci Python Layer (v0.2.x)

This package is **non-authoritative**.
It must NOT introduce new semantics (no implicit defaults, no schema bypass).
It only calls the authoritative CLI boundaries:

- `perisci-run` (B-beam): pure execution, no filesystem side effects
- `perisci-export` (C-beam): the only place that writes dataset under `output_dir/dataset`

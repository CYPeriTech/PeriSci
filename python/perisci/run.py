# python/perisci/run.py
from __future__ import annotations

import json
from ._cli import run_cmd


def run_case(config_json: str, *, perisci_run: str = "perisci-run") -> dict:
    """
    Thin wrapper for B-beam.
    - config_json is authoritative JSON text (do not mutate / fill defaults).
    - Calls: perisci-run --config -
    - Returns: bundle dict {config_b64, results{...}}
    """
    out = run_cmd([perisci_run, "--config", "-"], stdin_text=config_json)
    return json.loads(out)

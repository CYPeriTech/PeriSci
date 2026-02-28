# python/perisci/dataset.py
from __future__ import annotations

import json
from typing import Union
from ._cli import run_cmd


def export_dataset(bundle: Union[dict, str], out_dir: str, *, perisci_export: str = "perisci-export") -> dict:
    """
    Thin wrapper for C-beam.
    - bundle: dict (from run_case) or path str to a bundle JSON file
    - Calls: perisci-export --bundle <path or -> --out <out_dir>
    - Returns: report dict {ok, dataset_root, message}
    """
    if isinstance(bundle, dict):
        out = run_cmd([perisci_export, "--bundle", "-", "--out", out_dir], stdin_text=json.dumps(bundle))
        return json.loads(out)

    # assume it's a path
    out = run_cmd([perisci_export, "--bundle", bundle, "--out", out_dir], stdin_text=None)
    return json.loads(out)

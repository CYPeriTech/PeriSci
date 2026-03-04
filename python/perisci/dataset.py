# python/perisci/dataset.py
from __future__ import annotations

import json
from typing import Union
from .cli import run_cmd


def export_dataset(bundle: Union[dict, str], out_dir: str, *, perisci_export: str = "perisci-export") -> dict:
    """
    Thin wrapper for C-beam.
    - bundle: dict (from run_case) or path str to a bundle JSON file
    - Calls: perisci-export --bundle - --out <out_dir>   (stdin only)
    - Returns: report dict {ok, dataset_root, message}
    """
    if isinstance(bundle, dict):
        out = run_cmd([perisci_export, "--bundle", "-", "--out", out_dir], stdin_text=json.dumps(bundle))
        return json.loads(out)

    # assume it's a path to a bundle JSON file
    with open(bundle, "r", encoding="utf-8") as f:
        bundle_text = f.read()

    out = run_cmd([perisci_export, "--bundle", "-", "--out", out_dir], stdin_text=bundle_text)
    return json.loads(out)

# Copyright (c) 2026-present Fei Han
# PeriSci is licensed under Mulan PSL v2.
#
# You can use this software according to the terms and conditions of
# the Mulan PSL v2.
#
# You may obtain a copy of Mulan PSL v2 at:
#
#     http://license.coscl.org.cn/MulanPSL2
#
# THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS,
# WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR IMPLIED,
# INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
# MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
#
# See the Mulan PSL v2 for more details.

# python/perisci/validate.py
from __future__ import annotations

import json
from typing import Union
from pathlib import Path
from .cli import run_cmd, resolve_executable

def validate_case(manifest: Union[str, Path], *, perisci_validate: str = "perisci-validate") -> dict:
    """
    Thin wrapper for validate beam.
    - manifest: path str or Path to manifest.json or dataset directory
    - Calls: perisci-validate <manifest_path>
    - Returns: validation report dict
    """
    manifest_path = Path(manifest)
    if manifest_path.is_dir():
        manifest_path = manifest_path / "manifest.json"
    
    if not manifest_path.exists():
        raise FileNotFoundError(f"Manifest not found: {manifest_path}")
    
    exe = resolve_executable(perisci_validate)
    out = run_cmd([exe, str(manifest_path)])
    return json.loads(out)
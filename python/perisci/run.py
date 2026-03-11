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

# python/perisci/run.py
from __future__ import annotations

import json
from .cli import run_cmd


def run_case(config_json: str, *, perisci_run: str = "perisci-run") -> dict:
    """
    Thin wrapper for B-beam.

    - config_json is authoritative JSON text (do not mutate / fill defaults).
    - Calls: perisci-run --config -
    - Returns: bundle dict
        {
            config_b64: "...",
            results: {...},
            run_report: {...}   # observability data
        }
    """

    out = run_cmd([perisci_run, "--config", "-"], stdin_text=config_json)
    bundle = json.loads(out)

    # Backward compatibility:
    # older perisci-run may not emit run_report
    if "run_report" not in bundle:
        bundle["run_report"] = {}

    return bundle

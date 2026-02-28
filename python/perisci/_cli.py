# python/perisci/_cli.py
from __future__ import annotations

import subprocess
from typing import Optional, List


class PeriSciCliError(RuntimeError):
    pass


def run_cmd(cmd: List[str], stdin_text: Optional[str] = None) -> str:
    try:
        p = subprocess.run(
            cmd,
            input=stdin_text,
            text=True,
            capture_output=True,
            check=False,
        )
    except FileNotFoundError as e:
        raise PeriSciCliError(f"CLI not found: {cmd[0]}") from e

    if p.returncode != 0:
        raise PeriSciCliError(
            f"Command failed ({p.returncode}): {' '.join(cmd)}\n"
            f"stderr:\n{p.stderr}\n"
            f"stdout:\n{p.stdout}\n"
        )
    return p.stdout

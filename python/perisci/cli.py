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

# python/perisci/cli.py
from __future__ import annotations

import argparse
import json
import subprocess
import sys
from typing import List, Optional

import shutil
from pathlib import Path

def resolve_executable(name: str) -> str:
    """
    Try to resolve a PeriSci executable.

    Priority:
    1. PATH
    2. repo_root/build/bin/<name>
    """

    path = shutil.which(name)
    if path:
        return path

    repo_root = Path(__file__).resolve().parents[2]
    candidate = repo_root / "build" / "bin" / name

    if candidate.exists() and candidate.is_file():
        return str(candidate)
    if sys.platform.startswith("win"):
        candidate_exe = candidate.with_suffix(".exe")
        if candidate_exe.exists() and candidate_exe.is_file():
            return str(candidate_exe)

    return name

class PeriSciCliError(RuntimeError):
    pass


def run_cmd(cmd: List[str], stdin_text: Optional[str] = None) -> str:
    """
    Execute a CLI command and return stdout.

    Used internally by Python wrappers to call C-beam executables
    such as:

        perisci-run
        perisci-export
        perisci-validate
    """

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


# ----------------------------------------------------------------------
# CLI command implementations
# ----------------------------------------------------------------------

def cmd_run(args: argparse.Namespace) -> int:
    """
    perisci run

    Reads config JSON and calls:
        perisci-run --config -

    Prints bundle JSON to stdout.
    """

    cfg = args.config
    # only let target override when user did NOT explicitly set --config
    if args.target is not None and args.config == "-":
        t = Path(args.target)
        if t.is_dir():
            cfg = str(t / "input.json")
        elif t.suffix != ".json":
            # treat as case name
            repo_root = Path(__file__).resolve().parents[2]
            cfg = str(repo_root / "cases" / args.target / "input.json")
        else:
            cfg = str(t)

    if cfg == "-":
        config_text = sys.stdin.read()
    else:
        with open(cfg, "r", encoding="utf-8") as f:
            config_text = f.read()

    exe = resolve_executable(args.perisci_run)
    out = run_cmd([exe, "--config", "-"], stdin_text=config_text)

    bundle = json.loads(out)

    sys.stdout.write(json.dumps(bundle, ensure_ascii=False))
    sys.stdout.write("\n")

    return 0


def cmd_export(args: argparse.Namespace) -> int:
    """
    perisci export

    Reads bundle JSON and calls:
        perisci-export --bundle - --out <dir>

    Prints export report JSON.
    """

    if args.bundle == "-":
        bundle_text = sys.stdin.read()
    else:
        # 尝试用UTF-8读取，如果失败则尝试UTF-16
        try:
            with open(args.bundle, "r", encoding="utf-8") as f:
                bundle_text = f.read()
        except UnicodeDecodeError:
            try:
                with open(args.bundle, "r", encoding="utf-16") as f:
                    bundle_text = f.read()
            except UnicodeDecodeError:
                # 如果都失败，尝试使用系统默认编码
                with open(args.bundle, "r") as f:
                    bundle_text = f.read()

    exe = resolve_executable(args.perisci_export)
    out = run_cmd([exe, "--bundle", "-", "--out", args.out], stdin_text=bundle_text)

    report = json.loads(out)

    sys.stdout.write(json.dumps(report, ensure_ascii=False))
    sys.stdout.write("\n")

    return 0


def cmd_validate(args: argparse.Namespace) -> int:
    """
    perisci validate

    Calls:
        perisci-validate <manifest.json>

    Prints validation report JSON.
    """

    m = Path(args.manifest)
    if m.is_dir():
        m = m / "manifest.json"
    manifest_path = str(m)
    if not m.exists():
        raise PeriSciCliError(f"Manifest not found: {manifest_path}")

    exe = resolve_executable(args.perisci_validate)
    out = run_cmd([exe, manifest_path])

    report = json.loads(out)

    sys.stdout.write(json.dumps(report, ensure_ascii=False))
    sys.stdout.write("\n")

    return 0


# ----------------------------------------------------------------------
# Parser
# ----------------------------------------------------------------------

def build_parser() -> argparse.ArgumentParser:
    parser = argparse.ArgumentParser(
        prog="perisci",
        description="PeriSci Python CLI wrapper",
    )

    sub = parser.add_subparsers(dest="command", required=True)

    # run
    p_run = sub.add_parser("run", help="run a case")
    p_run.add_argument("--config", default="-", help="config JSON path or '-' (stdin)")
    p_run.add_argument("target", nargs="?", default=None, help="config.json / case dir / case name (optional)")
    p_run.add_argument(
        "--perisci-run",
        dest="perisci_run",
        default="perisci-run",
        help="perisci-run executable",
    )
    p_run.set_defaults(func=cmd_run)

    # export
    p_export = sub.add_parser("export", help="export dataset")
    p_export.add_argument("--bundle", default="-", help="bundle JSON or '-' (stdin)")
    p_export.add_argument("--out", required=True, help="dataset output directory")
    p_export.add_argument(
        "--perisci-export",
        dest="perisci_export",
        default="perisci-export",
        help="perisci-export executable",
    )
    p_export.set_defaults(func=cmd_export)

    # validate
    p_val = sub.add_parser("validate", help="validate dataset")
    p_val.add_argument("manifest", help="manifest.json path OR dataset directory")
    p_val.add_argument(
        "--perisci-validate",
        dest="perisci_validate",
        default="perisci-validate",
        help="perisci-validate executable",
    )
    p_val.set_defaults(func=cmd_validate)

    return parser


# ----------------------------------------------------------------------
# Main
# ----------------------------------------------------------------------

def main(argv: Optional[List[str]] = None) -> int:
    parser = build_parser()
    args = parser.parse_args(argv)

    try:
        return args.func(args)
    except PeriSciCliError as e:
        sys.stderr.write(str(e) + "\n")
        return 2
    except json.JSONDecodeError as e:
        sys.stderr.write(f"Invalid JSON returned by CLI: {e}\n")
        return 2

#!/usr/bin/env python3
from __future__ import annotations

import argparse
import re
import sys
from pathlib import Path
from typing import Iterable, List, Tuple

ADDRESS_DECL_RE = re.compile(r"^\s*(static\s+)?(const\s+)?Address\s+[A-Za-z_][A-Za-z0-9_]*\s*\(")


def default_roots() -> List[Path]:
    repo_root = Path(__file__).resolve().parent.parent
    library_root = repo_root.parent / "ctr-plugin-framework-for-vapecord" / "Library"
    return [repo_root, library_root]


def gather_source_files(roots: Iterable[Path]) -> List[Path]:
    out: List[Path] = []
    patterns = ("*.cpp", "*.hpp", "*.h")

    for root in roots:
        if not root.exists():
            continue
        for pattern in patterns:
            out.extend(root.rglob(pattern))

    # Deterministic output
    out = sorted(set(out))
    return out


def scan_file(file_path: Path) -> List[Tuple[Path, int, str]]:
    violations: List[Tuple[Path, int, str]] = []

    try:
        lines = file_path.read_text(encoding="utf-8", errors="ignore").splitlines()
    except OSError:
        return violations

    depth = 0
    in_block_comment = False

    for index, line in enumerate(lines, start=1):
        stripped = line.strip()

        if in_block_comment:
            if "*/" in line:
                in_block_comment = False
            depth += line.count("{") - line.count("}")
            if depth < 0:
                depth = 0
            continue

        if re.match(r"^\s*/\*", line):
            if "*/" not in line:
                in_block_comment = True
            depth += line.count("{") - line.count("}")
            if depth < 0:
                depth = 0
            continue

        if ADDRESS_DECL_RE.match(line):
            is_comment = stripped.startswith("//") or stripped.startswith("*")
            # depth 0 = file scope, depth 1 = namespace scope
            if not is_comment and depth <= 1:
                violations.append((file_path, index, stripped))

        depth += line.count("{") - line.count("}")
        if depth < 0:
            depth = 0

    return violations


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Fail if Address declarations exist at file/namespace scope."
    )
    parser.add_argument(
        "roots",
        nargs="*",
        help="Optional root directories to scan. Defaults to plugin repo + Library repo.",
    )
    return parser.parse_args()


def main() -> int:
    args = parse_args()

    roots = [Path(p).resolve() for p in args.roots] if args.roots else default_roots()
    files = gather_source_files(roots)

    violations: List[Tuple[Path, int, str]] = []
    for file_path in files:
        violations.extend(scan_file(file_path))

    if violations:
        print("ERROR: Found global or namespace-scope Address declarations:")
        for path, line, code in sorted(violations, key=lambda x: (str(x[0]), x[1])):
            print(f"{path}:{line}: {code}")
        return 1

    print("OK: No global or namespace-scope Address declarations found.")
    return 0


if __name__ == "__main__":
    sys.exit(main())

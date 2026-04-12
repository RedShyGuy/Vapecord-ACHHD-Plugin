import os
import re
import sys
from pathlib import Path

# CONFIG
SCRIPT_DIR = Path(__file__).resolve().parent
PROJECT_ROOT = SCRIPT_DIR.parents[1]
ADDRESSES_HEADER = PROJECT_ROOT / "include" / "core" / "infrastructure" / "Addresses.hpp"

# regex for Address(...) and Address name(...)
address_pattern = re.compile(
    r"\bAddress(?:\s+\w+)?\s*\(\s*(0x[0-9A-Fa-f]+)\s*\)"
)

address_declaration_pattern = re.compile(
    r"\b(?:static\s+)?(?:inline\s+)?(?:constexpr\s+)?(?:const\s+)?Address\b([^;]*);",
    flags=re.MULTILINE,
)

address_direct_initializer_pattern = re.compile(
    r"(?:^|,)\s*[A-Za-z_]\w*\s*[\(\{]\s*(0x[0-9A-Fa-f]+)\s*[\)\}]"
)

# regex entries for address array
array_pattern = re.compile(
    r"\{\s*(0x[0-9A-Fa-f]+)"
)


def strip_block_comments(text: str) -> str:
    return re.sub(r"/\*.*?\*/", "", text, flags=re.DOTALL)


def strip_all_comments(text: str) -> str:
    text = re.sub(r"/\*.*?\*/", "", text, flags=re.DOTALL)
    text = re.sub(r"//.*", "", text)
    return text

def collect_addresses_from_header():
    found = set()
    if not os.path.exists(ADDRESSES_HEADER):
        print(f"ERROR: {ADDRESSES_HEADER} not found!")
        return found

    with open(ADDRESSES_HEADER, "r", encoding="utf-8", errors="ignore") as f:
        content = strip_block_comments(f.read())

    for match in array_pattern.finditer(content):
        found.add(match.group(1).lower())

    return found


def scan_code_files(allowed_set):
    missing = {}
    found_all = set()
    seen_hits = set()

    def register_match(path: str, content: str, match_start: int, hex_value: str):
        line = content.count("\n", 0, match_start) + 1
        normalized = hex_value.lower()

        hit_key = (path, line, normalized)
        if hit_key in seen_hits:
            return
        seen_hits.add(hit_key)

        if normalized not in allowed_set:
            missing.setdefault(path, []).append((line, normalized))
        found_all.add(normalized)

    def scan_content(path: str, content: str):
        for match in address_pattern.finditer(content):
            register_match(path, content, match.start(1), match.group(1))

        for declaration in address_declaration_pattern.finditer(content):
            declarators = declaration.group(1)
            base_offset = declaration.start(1)
            for init_match in address_direct_initializer_pattern.finditer(declarators):
                register_match(
                    path,
                    content,
                    base_offset + init_match.start(1),
                    init_match.group(1),
                )

    for root, _, files in os.walk(PROJECT_ROOT / "src"):
        for file in files:
            if not file.endswith((".cpp", ".hpp", ".h")):
                continue

            path = os.path.join(root, file)
            with open(path, "r", encoding="utf-8", errors="ignore") as f:
                content = strip_all_comments(f.read())

            scan_content(path, content)

    for root, _, files in os.walk(PROJECT_ROOT / "include"):
        for file in files:
            if not file.endswith((".cpp", ".hpp", ".h")):
                continue

            path = os.path.join(root, file)
            if Path(path).resolve() == ADDRESSES_HEADER.resolve():
                continue

            with open(path, "r", encoding="utf-8", errors="ignore") as f:
                content = strip_all_comments(f.read())

            scan_content(path, content)

    return found_all, missing


def main():
    print("Scanning...")
    allowed = collect_addresses_from_header()
    print(f"Known addresses: {len(allowed)}")

    found, missing = scan_code_files(allowed)

    print(f"Total referenced in code: {len(found)}")

    if missing:
        print("\nMissing addresses:")
        for file, entries in missing.items():
            print(f"\n{file}:")
            for line, val in entries:
                print(f"  Line {line}: {val}")
        exit_code = 1
    else:
        print("\nAll Address-Entries are ported!")
        exit_code = 0

    sys.exit(exit_code)

if __name__ == "__main__":
    main()

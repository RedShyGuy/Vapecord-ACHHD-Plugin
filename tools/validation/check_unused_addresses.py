import os
import re
import sys
from pathlib import Path

SCRIPT_DIR = Path(__file__).resolve().parent
PROJECT_ROOT = SCRIPT_DIR.parents[1]
ADDRESSES_HEADER = PROJECT_ROOT / "include" / "core" / "infrastructure" / "Addresses.hpp"

address_usage_pattern = re.compile(
    r"\bAddress(?:\s+\w+)?\s*\(\s*(0x[0-9A-Fa-f]+)\s*\)"
)

address_declaration_pattern = re.compile(
    r"\b(?:static\s+)?(?:inline\s+)?(?:constexpr\s+)?(?:const\s+)?Address\b([^;]*);",
    flags=re.MULTILINE,
)

address_direct_initializer_pattern = re.compile(
    r"(?:^|,)\s*[A-Za-z_]\w*\s*[\(\{]\s*(0x[0-9A-Fa-f]+)\s*[\)\}]"
)

array_pattern = re.compile(
    r"\{\s*(0x[0-9A-Fa-f]+)\s*,"
)


# --- comment stripping ---

def strip_block_comments(text: str) -> str:
    return re.sub(r"/\*.*?\*/", "", text, flags=re.DOTALL)


def strip_all_comments(text: str) -> str:
    text = re.sub(r"/\*.*?\*/", "", text, flags=re.DOTALL)
    text = re.sub(r"//.*", "", text)
    return text


# --- header scan ---

def collect_addresses_from_header():
    addresses = set()

    if not ADDRESSES_HEADER.exists():
        print(f"ERROR: {ADDRESSES_HEADER} not found!")
        return addresses

    with open(ADDRESSES_HEADER, "r", encoding="utf-8", errors="ignore") as f:
        content = strip_block_comments(f.read())

    for match in array_pattern.finditer(content):
        addresses.add(match.group(1).lower())

    return addresses


# --- code scan ---

def collect_used_addresses():
    used = set()

    def collect_from_content(content: str):
        nonlocal used

        for match in address_usage_pattern.finditer(content):
            used.add(match.group(1).lower())

        for declaration in address_declaration_pattern.finditer(content):
            declarators = declaration.group(1)
            for init_match in address_direct_initializer_pattern.finditer(declarators):
                used.add(init_match.group(1).lower())

    for root, _, files in os.walk(PROJECT_ROOT / "src"):
        for file in files:
            if not file.endswith((".cpp", ".hpp", ".h")):
                continue

            path = Path(root) / file

            if path.resolve() == ADDRESSES_HEADER.resolve():
                continue

            with open(path, "r", encoding="utf-8", errors="ignore") as f:
                content = strip_all_comments(f.read())

            collect_from_content(content)

    for root, _, files in os.walk(PROJECT_ROOT / "include"):
        for file in files:
            if not file.endswith((".cpp", ".hpp", ".h")):
                continue

            path = Path(root) / file

            if path.resolve() == ADDRESSES_HEADER.resolve():
                continue

            with open(path, "r", encoding="utf-8", errors="ignore") as f:
                content = strip_all_comments(f.read())

            collect_from_content(content)

    return used


# --- main ---

def main():
    print("Scanning for unused addresses...")

    header_addresses = collect_addresses_from_header()
    used_addresses = collect_used_addresses()

    unused = sorted(header_addresses - used_addresses)

    print(f"Total in header: {len(header_addresses)}")
    print(f"Used in code: {len(used_addresses)}")
    print(f"Unused: {len(unused)}")

    if unused:
        print("\nUnused addresses:")
        for addr in unused:
            print(f"  {addr}")
        exit_code = 1
    else:
        print("\nNo unused addresses found!")
        exit_code = 0

    sys.exit(exit_code)


if __name__ == "__main__":
    main()


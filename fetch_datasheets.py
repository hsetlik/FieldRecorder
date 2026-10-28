#!/usr/bin/env python3
"""Download any datasheets listed in DATASHEETS.md that are missing from Datasheets/.

Usage:
    python3 fetch_datasheets.py          # download missing files
    python3 fetch_datasheets.py --force  # re-download everything
"""

import argparse
import re
import sys
import urllib.request
from pathlib import Path

ROOT = Path(__file__).resolve().parent
LIST_FILE = ROOT / "DATASHEETS.md"
DEST_DIR = ROOT / "Datasheets"

# Some vendor sites reject the default Python user agent.
USER_AGENT = (
    "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) "
    "AppleWebKit/537.36 (KHTML, like Gecko) Chrome/120.0 Safari/537.36"
)

ROW_RE = re.compile(r"^\|\s*([^|]+?)\s*\|\s*([^|]*?)\s*\|\s*$")


def parse_list(path):
    """Return (filename, url) pairs from the markdown table in path."""
    entries = []
    for line in path.read_text().splitlines():
        m = ROW_RE.match(line.strip())
        if not m:
            continue
        name, url = m.groups()
        # Skip the header and separator rows.
        if name.lower() == "file" or set(name) <= set("-: "):
            continue
        # Allow URLs written as <https://...> or [text](https://...).
        link = re.search(r"\((https?://[^)]+)\)|<(https?://[^>]+)>", url)
        if link:
            url = link.group(1) or link.group(2)
        entries.append((name, url))
    return entries


def download(url, dest):
    req = urllib.request.Request(url, headers={"User-Agent": USER_AGENT})
    tmp = dest.with_suffix(dest.suffix + ".part")
    try:
        with urllib.request.urlopen(req, timeout=60) as resp, open(tmp, "wb") as f:
            while chunk := resp.read(1 << 16):
                f.write(chunk)
        with open(tmp, "rb") as f:
            if f.read(5) != b"%PDF-":
                raise ValueError("response is not a PDF (the URL may point to a web page)")
        tmp.replace(dest)
    finally:
        tmp.unlink(missing_ok=True)


def main():
    parser = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    parser.add_argument("--force", action="store_true", help="re-download files that already exist")
    args = parser.parse_args()

    entries = parse_list(LIST_FILE)
    if not entries:
        print(f"No datasheets found in {LIST_FILE.name}")
        return 1

    DEST_DIR.mkdir(exist_ok=True)
    failed = 0
    for name, url in entries:
        dest = DEST_DIR / name
        if dest.exists() and not args.force:
            print(f"  ok       {name}")
            continue
        if not url:
            print(f"  no URL   {name}")
            failed += 1
            continue
        print(f"  fetching {name} ...", end="", flush=True)
        try:
            download(url, dest)
            print(f" done ({dest.stat().st_size / 1e6:.1f} MB)")
        except Exception as e:
            print(f" FAILED: {e}")
            failed += 1

    return 1 if failed else 0


if __name__ == "__main__":
    sys.exit(main())

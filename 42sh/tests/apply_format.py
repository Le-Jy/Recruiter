import subprocess
import os
from os import listdir
from os.path import isfile, join
from argparse import ArgumentParser
from pathlib import Path

import termcolor

WARN_TAG = f"[{termcolor.colored('WARNING', 'yellow')}]"

def apply_clang_format(directory, dry_run):
    
    sources_files = [os.path.join(root,file)
                    for root, dirs, files in os.walk(directory)
                    for file in files
                    if file.endswith((".c", ".h"))]

    if not sources_files:
        return

    for file in sources_files:
        if (dry_run):
            print(f"Checking: {file}")
            result = subprocess.run(["clang-format", "--dry-run", file], capture_output=True)
            if result.stderr:
                print(f"{WARN_TAG}{file}\n{result.stderr}")
        else:
            print(f"Formatting: {file}")
            result = subprocess.run(["clang-format", "-i", file], capture_output=True)

if __name__ == "__main__":
    parser = ArgumentParser("ClangFormat")
    parser.add_argument("--sources", required=True, type=Path)
    parser.add_argument('--dry-run', action='store_true')
    args = parser.parse_args()
    sources_files = args.sources

    apply_clang_format(sources_files, args.dry_run)

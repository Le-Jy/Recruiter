import subprocess
import os
from argparse import ArgumentParser
from difflib import unified_diff
from os import listdir
from os.path import isfile, join
from pathlib import Path
from dataclasses import dataclass

import termcolor

OK_TAG = f"[{termcolor.colored('OK', 'green')}]"
KO_TAG = f"[{termcolor.colored('KO', 'red')}]"
CATEGORY_TAG = f"[{termcolor.colored('CATEGORY', 'blue')}]"

PASSED_TAG = f"[{termcolor.colored('PASSED', 'green')}]"
FAILED_TAG = f"[{termcolor.colored('FAILED', 'red')}]"
RESUME_TAG = f"[{termcolor.colored('RESUME', 'blue')}]"

def diff(expected: str, actual: str) -> str:
    expected_lines = expected.splitlines(keepends=True)
    actual_lines = actual.splitlines(keepends=True)

    return "".join(
        unified_diff(expected_lines, actual_lines, fromfile="expected", tofile="actual")
    )

def run_shell(*cmd_line) -> subprocess.CompletedProcess:
    return subprocess.run(cmd_line, capture_output=True, text=True, timeout=1)

def perform_checks(
    expected: subprocess.CompletedProcess, actual: subprocess.CompletedProcess
):
    assert (
        not expected.stderr
    ) or actual.stderr != "", "Something was expected on stderr"

    assert (
        expected.returncode == actual.returncode
    ), f"Exited withg {actual.returncode}, expected {expected.returncode}"

    assert (
        expected.stdout == actual.stdout
            ), f"stdout differ\n{diff(expected.stdout, actual.stdout)}"

@dataclass
class Category:
    tests: list[str]
    name: str

config = {"categories": ["builtins/echo",
                         "builtins/exit",
                         "builtins/cd",
                         "builtins/boolean",
                         "builtins/dot",
                         "while",
                         "bad_parse",
                         "if_clauses",
                         "comments",
                         "quotes",
                         "and_or",
                         "pipe",
                         "redirections",
                         "variables",
                         "for",
                         "command_blocks",
                         "command_substitution",
                         "until",
                         "functions",
                         "subshells",
                         "loop_interupts",
                         "aliases",
                         "case_clauses",
                         "ifs",
                         "continue",
                         "break",
                         "unset",
                         "export",
                         "options"
                        ]}

if __name__ == "__main__":
    parser = ArgumentParser("TestSuite")
    parser.add_argument("--binary", required=True, type=Path)
    parser.add_argument("--tests", required=True, type=Path)
    args = parser.parse_args()

    binary_path = args.binary.absolute()
    tests_categories = args.tests

    categories: list[Category]= []
    for category in config["categories"]:
        category = f"{tests_categories}/{category}"
        categories.append(
            Category(
                [
                    join(category, f)
                    for f in listdir(category)
                    if isfile(join(category, f))
                ],
                category,
            )
        )

    failed = 0
    passed = 0
    for category in categories:
        print(f"\n{CATEGORY_TAG}: {category.name}")
        print("=" * 40)
        for file in category.tests:
            try:
                sh_proc = run_shell(binary_path, file)
                sh_ref = run_shell("bash", "--posix", file)
            except subprocess.TimeoutExpired as to:
                print(f"{KO_TAG} {file}\nTimeout expired: {to}")
                failed += 1
                pass
            else:

                try:
                    perform_checks(sh_ref, sh_proc)
                except AssertionError as err:
                    print(f"{KO_TAG} {file}\n{err}")
                    failed += 1
                else:
                    print(f"{OK_TAG} {file}")
                    passed += 1
                    pass

    print(f"\n\n{RESUME_TAG}")
    print("=" * 40)
    print(f"{PASSED_TAG} : {passed}")
    print(f"{FAILED_TAG} : {failed}")
    print()

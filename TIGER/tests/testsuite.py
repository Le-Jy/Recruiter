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

def run_process(*cmd_line) -> subprocess.CompletedProcess:
    return subprocess.run(cmd_line, capture_output=True, text=True, timeout=1)

def perform_checks(
    category: str , proc: subprocess.CompletedProcess
):

    expected = 0
    if category == "syntax/scanner":
        expected = 2
    if category == "syntax/parser":
        expected = 3

    assert (
        expected == proc.returncode
    ), f"Exited withg {proc.returncode}, expected {expected}"

    if expected != 0:
        assert (
            proc.stderr != ""
        ), "Something was expected on stderr"

@dataclass
class Test:
    tests: list[str]
    name: str

config = {"tests": ["bind", "good", "syntax/scanner", "syntax/parser", "type"]}

if __name__ == "__main__":
    parser = ArgumentParser("TestSuite")
    parser.add_argument("--binary", required=True, type=Path)
    parser.add_argument("--tests", required=True, type=Path)
    args = parser.parse_args()

    binary_path = args.binary.absolute()
    tests_arg = args.tests

    tests: list[Test]= []
    for category in config["tests"]:

        category_name = category
        category = f"{tests_arg}/{category}"

        tests.append(
            Test(
                [
                    join(category, f)
                    for f in listdir(category)
                    if isfile(join(category, f))
                ],
                category_name,
            )
        )

    failed = 0
    passed = 0
    for category in tests:
        print(f"\n{CATEGORY_TAG}: {category.name}")
        print("=" * 40)
        for file in category.tests:
            file_name = str(file).replace(str(tests_arg), "")
            file_name = file_name[1:]
            try:
                proc = run_process(binary_path, file)
            except subprocess.TimeoutExpired as to:
                print(f"{KO_TAG} {file_name}\nTimeout expired: {to}")
                failed += 1
                pass
            else:

                try:
                    perform_checks(category.name, proc)
                except AssertionError as err:
                    print(f"{KO_TAG} {file_name}\n{err}")
                    failed += 1
                else:
                    print(f"{OK_TAG} {file_name}")
                    passed += 1
                    pass

    print(f"\n\n{RESUME_TAG}")
    print("=" * 40)
    print(f"{PASSED_TAG} : {passed}")
    print(f"{FAILED_TAG} : {failed}")
    print()

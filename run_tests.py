import os
from colorama import init, Fore
import subprocess as sp

init(autoreset=True)

current = os.getcwd()

TESTS = [
    ("Parser Tests", "tests/test_parser", ["sh", "./run.sh"]),
    ("Interpreter Tests", "tests/interpreter_tests/",
     ["python3", "interpreter_test.py"]),
    ("Example Tests", "tests/examples_test/", ["python3", "run_tests.py"])
]


def do_tests(test_name: str, path: str, runable: str):
    print(test_name.center(os.get_terminal_size()[0], '_'))
    os.chdir(path)
    result = sp.run(runable)
    print(f"{test_name}: ", end='')
    if result.returncode == 0:
        print(f"{Fore.GREEN}PASSED")
    else:
        print(f"{Fore.RED}FAILED")
    os.chdir(current)


if __name__ == "__main__":
    for i in range(len(TESTS)):
        do_tests(*TESTS[i])

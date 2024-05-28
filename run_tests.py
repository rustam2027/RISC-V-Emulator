import os
from colorama import init, Fore
import subprocess as sp
import time

init(autoreset=True)

current = os.getcwd()

TESTS = [
    ("Parser Tests", "tests/test_parser", ["sh", "./run.sh"], 10),
    ("Interpreter Tests", "tests/interpreter_tests/", ["python3", "interpreter_test.py"], 2),
    ("Example Tests", "tests/examples_test/", ["python3", "run_tests.py"], 2),
    ("BreakController", "tests/breakcontroller_tests/", ["python3", "run_tests.py"], 2),
    ("Macro tests", "tests/macro_tests/", ["python3", "run_tests.py"], 2)
]

def do_tests(test_name: str, path: str, runable: str, timeout: int = 2):
    print(test_name.center(os.get_terminal_size()[0], '_'))
    os.chdir(path)
    try:
        result = sp.run(runable, timeout=timeout)
        print(f"{test_name}: ", end='')
        if result.returncode == 0:
            print(f"{Fore.GREEN}PASSED")
        else:
            print(f"{Fore.RED}FAILED")
    except sp.TimeoutExpired:
        print(f"{Fore.RED}TIMEOUT (>{timeout}s)")
    finally:
        os.chdir(current)

if __name__ == "__main__":
    for i in range(len(TESTS)):
        do_tests(*TESTS[i])

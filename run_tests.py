import os
from colorama import init, Fore
import subprocess as sp

init(autoreset=True)

current = os.getcwd()

PARSER_TESTS = "tests/test_parser"
INTERPRETER_TESTS = "tests/interpreter_tests/"
EXAMPLE_TESTS = "tests/examples_test/"


def test_pareser():
    print("Parser Tests".center(os.get_terminal_size()[0], '_'))
    os.chdir(PARSER_TESTS)
    result = sp.run(["./run.sh"], shell=True)
    if result.returncode == 0:
        print(f"{Fore.GREEN}PASSED")
    else:
        print(f"{Fore.RED}FAILED")
    os.chdir(current)


def test_interpreter():
    print("Interpreter Tests".center(os.get_terminal_size()[0], '_'))
    os.chdir(INTERPRETER_TESTS)
    result = sp.run(["python3", "interpreter_test.py"])
    if result.returncode == 0:
        print(f"{Fore.GREEN}PASSED")
    else:
        print(f"{Fore.RED}FAILED")
    os.chdir(current)


def test_examples():
    print("Example Tests".center(os.get_terminal_size()[0], '_'))
    os.chdir(EXAMPLE_TESTS)
    result = sp.run(["python3", "run_tests.py"])
    if result.returncode == 0:
        print(f"{Fore.GREEN}PASSED")
    else:
        print(f"{Fore.RED}FAILED")
    os.chdir(current)


if __name__ == "__main__":
    test_pareser()
    test_interpreter()
    test_examples()

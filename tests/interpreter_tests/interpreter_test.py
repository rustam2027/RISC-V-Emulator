import os
import subprocess
from colorama import init, Fore

init(autoreset=True)


def find_test_folders():
    os.chdir("tests")
    test_folders = [folder for folder in os.listdir() if os.path.isdir(
        folder) and folder.startswith('test_')]
    return sorted(test_folders)


def run_executable(executable_path, input_file, output_file):
    with open(output_file, 'w') as f:
        try:
            subprocess.run([executable_path, input_file],
                           stdout=f, text=True, check=True)
        except subprocess.CalledProcessError as e:
            f.write(str(e))


def compare_output(output_file, expected_output_file):
    with open(output_file, 'r') as f1, open(expected_output_file, 'r') as f2:
        return f1.read().strip() == f2.read().strip()


if __name__ == "__main__":
    executable_path = "/Users/rustamsalimov/Documents/GitHub/RISC-V-Emulator/main"

    test_folders = find_test_folders()
    for folder in test_folders:
        in_file = os.path.join(folder, 'in.txt')
        out_file = os.path.join(folder, 'out.txt')
        temp_output_file = os.path.join(folder, 'temp_output.txt')

        if os.path.exists(in_file) and os.path.exists(out_file):
            run_executable(executable_path, in_file, temp_output_file)

            if compare_output(temp_output_file, out_file):
                print(f"[{folder}]: {Fore.GREEN}PASSED")
                os.remove(temp_output_file)

            else:
                print(f"[{folder}]: {Fore.RED}FAILED")

        else:
            print(
                f"Для теста в папке {folder} отсутствует файл in.txt или out.txt")
    os.remove("_in.parse")

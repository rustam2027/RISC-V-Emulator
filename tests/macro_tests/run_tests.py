#!/usr/bin/env python3

import os
import subprocess as sp
from colorama import init, Fore

init(autoreset=True)


# Путь к папке с тестами

# Путь к исполняемому файлу, который нужно запустить
executable_file = "./../../main"
input_file = "in.txt"
out_file = "out.txt"
return_code = 0

# Проход по папке с файлами тестов
for root, _, files in sorted(os.walk("./tests")):
    for file in sorted(files):
        if file.endswith(".asm"):
            cmd = f"cat {os.path.join(root, input_file)} | {executable_file} {os.path.join(root, file)}"
            res = sp.run(cmd, shell=True, capture_output=True, text=True)


            if res.returncode != 0:
                print(f"{Fore.RED}Problem occured with {file}: \n{res.stderr}")
                print(f"{Fore.RED} {res}")
                continue

            with open(os.path.join(root, out_file), "r") as out_bytes:
                out = out_bytes.read().strip()
                if out != res.stdout.strip():
                    print(f'[{file}]: {Fore.RED}FAILED')
                    print(f'\t     {Fore.RED} actual: {res.stdout.strip()}')
                    print(f'\t     {Fore.RED} expected: {out}')
                    return_code = 1
                else:
                    print(f'[{file}]: {Fore.GREEN}PASSED')


exit(return_code)

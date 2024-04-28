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
for root, _, files in sorted(os.walk("./tests"), key=lambda x: x[2]):
    for file in files:
        if file.endswith(".asm"):
            cmd = f"cat {os.path.join(root, input_file)} | {executable_file} {os.path.join(root, file)} -d"
            res = sp.run(cmd, capture_output=True, shell=True, text=True)

            if os.path.isfile("_in.parse"):
                os.remove("_in.parse")

            if res.returncode != 0:
                print(f"Problem occured with {file}: \n{res.stderr}")
                continue

            with open(os.path.join(root, out_file), "r") as out_bytes:
                expected = out_bytes.read().strip().splitlines()
                result = res.stdout.strip().splitlines()
                passed = True
                if len(result) != len(expected):
                    passed = False
                    print(res.stdout.strip())
                else:
                    for i in range(len(result)):
                        if (result[i].split() != expected[i].split()):
                            print(result[i], " --expected-->", expected[i])
                            return_code = 1
                            passed = False
                            break
                if passed:
                    print(f'[{file}]: {Fore.GREEN}PASSED')
                else:
                    print(f'[{file}]: {Fore.RED}FAILED')

exit(return_code)

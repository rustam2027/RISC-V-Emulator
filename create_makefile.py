import os
from typing import List

FLAGS = "-c -std=c++17"
SANITIZERS = "-fsanitize=address -fsanitize=undefined"
CC = "clang++"
FILES: List[str] = []


def get_cpp_files(path: str) -> List[str]:
    files = []
    for file in os.listdir(path):
        if os.path.isdir(file):
            files += get_cpp_files(path + "/" + file)
        elif os.path.isfile(path + "/" + file) and os.path.splitext(file)[1] == ".cpp":
            files.append(path + "/" + file)
    return files


def get_make_rule(file_path: str) -> List[str]:
    return_list: List[str] = []
    file_name = os.path.splitext(os.path.basename(file_path))[0]

    return_list.append(f"{file_name}.o: {file_path}\n")
    return_list.append(f"\t{CC} {file_path} {FLAGS} {SANITIZERS}\n")

    return return_list


in_file_buff: List[str] = [
    "all: compile\n",
    "\n",
    f"\t{CC} *.o -o main {SANITIZERS}\n"
    "\n"
]
compile_rule = "compile:"

FILES = get_cpp_files(".")
for file in FILES:
    compile_rule += f" {os.path.basename(file)[:-4]}.o"
    in_file_buff += get_make_rule(file)
    in_file_buff.append('\n')

compile_rule += "\n"

in_file_buff.insert(2, compile_rule)

in_file_buff.append("clean:\n")
in_file_buff.append("\trm *.o\n")

with open("makefile", "w") as makefile:
    for line in in_file_buff:
        makefile.write(line)

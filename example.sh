#!/bin/bash

clang++ main.cpp parser/Parser.cpp commands/commands_impl.cpp interpreter/Interpreter.cpp -o main -fsanitize=address -fsanitize=undefined -std=c++17 

./main in.txt

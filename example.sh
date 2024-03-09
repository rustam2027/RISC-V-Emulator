#!/bin/bash

clang++ main.cpp parser/Parser.cpp commands/commands_impl.cpp -o main -fsanitize=address 

./main in.txt
rm -rf main
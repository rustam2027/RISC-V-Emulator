#!/bin/bash

clang++ main.cpp frontend/Parser.cpp frontend/Preprocessor.cpp instructions/instructions_impl.cpp interpreter/Interpreter.cpp tests/simple_instructions_test.cpp -o main -fsanitize=address -fsanitize=undefined -std=c++17 

./main in.txt

# rm main

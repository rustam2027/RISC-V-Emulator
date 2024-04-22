#!/bin/bash

clang++ main.cpp frontend/Parser.cpp frontend/Preprocessor.cpp instructions/instructions_impl.cpp interpreter/Interpreter.cpp tests/simple_instructions_test.cpp break_controller/BreakController.cpp frontend/Lexer.cpp -o main -fsanitize=address -fsanitize=undefined -std=c++17 

./main in.txt

# rm main

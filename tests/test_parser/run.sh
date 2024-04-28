clang++ test_parser.cpp test_is_number.cpp ../../frontend/Lexer.cpp ../../frontend/Parser.cpp test_get_immediate.cpp ../../instructions/instructions_impl.cpp ../../instructions/instructions.hpp -std=c++17 -w
if [ $? -eq 0 ]
then
  ./a.out
fi

clang++ test_check_syntax.cpp test_labels.cpp test_get_offset.cpp test_parser.cpp test_is_number.cpp ../../frontend/Lexer.cpp ../../frontend/Parser.cpp ../../frontend/Preprocessor.cpp test_get_immediate.cpp ../../instructions/instructions_impl.cpp ../../instructions/instructions.hpp -std=c++17 -w
if [ $? -eq 0 ]
then
  ./a.out
fi

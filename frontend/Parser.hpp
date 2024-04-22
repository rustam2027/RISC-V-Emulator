#pragma once
#include <cassert>
#include <cstddef>
#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "../instructions/instructions.hpp"
#include "../exceptions/ParserException.hpp"
#include "../break_controller/BreakController.hpp"

#include "Lexer.hpp"
#include "StringUtils.hpp"


class Parser {
  Lexer lexer;
  static std::map<std::string, Register> registers_names;

  std::map<std::string, function<Instruction* (std::vector<std::string> args)>> func = {
      {"add", [](std::vector<std::string> args) { return new Add(args); }},
      {"li", [](std::vector<std::string> args) { return new Li(args); }},
      {"addi", [](std::vector<std::string> args) { return new Addi(args); }},
      {"and", [](std::vector<std::string> args) { return new And(args); }},
      {"mv", [](std::vector<std::string> args) { return new Mv(args); }},
      {"or", [](std::vector<std::string> args) { return new Or(args); }},
      {"sll", [](std::vector<std::string> args) { return new SLL(args); }},
      {"srl", [](std::vector<std::string> args) { return new SRL(args); }},
      {"sub", [](std::vector<std::string> args) { return new Sub(args); }},
      {"xor", [](std::vector<std::string> args) { return new Xor(args); }},
      {"ecall", [](std::vector<std::string> args) { return new Ecall(args); }},
      {"j", [](std::vector<std::string> args) { return new Jump(args); }},
      {"jal", [](std::vector<std::string> args) { return new JumpAndLink(args); }},
      {"beq", [](std::vector<std::string> args) { return new BranchEqual(args); }},
      {"bne", [](std::vector<std::string> args) { return new BranchNotEqual(args); }},
      {"blt", [](std::vector<std::string> args) { return new BranchLessThen(args); }},
      {"bge", [](std::vector<std::string> args) { return new BranchGreaterEqual(args); }},
      {"ret", [](std::vector<std::string> args) { return new Return(args); }},
      {"ebreak", [](std::vector<std::string> args) { return new EBreak(args); }}
  };

  void delete_instructions(std::vector<Instruction* > instructions);
  Instruction* get_instruction(const std::string& str, std::vector<std::string> args);

  static bool is_binary_number(const std::string& str);
  static bool is_hex_number(const std::string& str);
  static bool is_dec_number(const std::string& str);

  static int is_binary_char(char c);
  static bool is_hex_char(char c);

  friend BreakController;

public:
  Parser()=default;

  // TODO: move it to Lexer + add checking commas 
  
  std::vector<std::string> check_syntax(std::vector<std::string> args_tokens);
  std::vector<Instruction*> get_instructions();
  static Register get_register(const std::string& str);
  static std::vector<std::string> get_offset(const std::vector<std::string>& args);
  static int get_immediate(const std::string& str);
  static bool is_number(const std::string& str);
};

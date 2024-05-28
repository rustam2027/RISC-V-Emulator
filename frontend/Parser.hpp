#pragma once
#include <cassert>
#include <cstddef>
#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#include "../instructions/instructions.hpp"
#include "../exceptions/ParserException.hpp"
#include "../interpreter/Interpreter.hpp"

#include "Lexer.hpp"
#include "StringUtils.hpp"


class Parser {
  Lexer lexer;
  std::map<std::string, int>& labels;
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
      {"call", [](std::vector<std::string> args) { return new Call(args); }},
      {"j", [](std::vector<std::string> args) { return new Jump(args); }},
      {"jal", [](std::vector<std::string> args) { return new JumpAndLink(args); }},
      {"beq", [](std::vector<std::string> args) { return new BranchEqual(args); }},
      {"bgt", [](std::vector<std::string> args) { return new BranchGreaterThen(args); } },
      {"bne", [](std::vector<std::string> args) { return new BranchNotEqual(args); }},
      {"blt", [](std::vector<std::string> args) { return new BranchLessThen(args); }},
      {"bge", [](std::vector<std::string> args) { return new BranchGreaterEqual(args); }},
      {"ret", [](std::vector<std::string> args) { return new Return(args); }},
      {"slli", [](std::vector<std::string> args) { return new SLLI(args); }},
      {"sb", [](std::vector<std::string> args) { return new Sb(args); }},
      {"sh", [](std::vector<std::string> args) { return new Sh(args); }},
      {"sw", [](std::vector<std::string> args) { return new Sw(args); }},
      {"lb", [](std::vector<std::string> args) { return new Lb(args); }},
      {"lh", [](std::vector<std::string> args) { return new Lh(args); }}, 
      {"lw", [](std::vector<std::string> args) { return new Lw(args); }},
      {"beqz", [](std::vector<std::string> args) { return new BranchEqualZero(args); }},
      {"srli", [](std::vector<std::string> args) { return new SRLI(args); }},
      {"ebreak", [](std::vector<std::string> args) { return new EBreak(args); }},
      {"data", [](std::vector<std::string> args) { return new Data(args); }},
      {"la", [](std::vector<std::string> args) { return new La(args); }}
  };

  std::set<std::string> label_instructions = {"j", "jal", "beq", "bgt", "bne", "blt", "beqz", "bge", "la"};

  void delete_instructions(std::vector<Instruction* > instructions);
  Instruction* get_instruction(const std::string& str, std::vector<std::string> args);

  static bool is_binary_number(const std::string& str);
  static bool is_hex_number(const std::string& str);
  static bool is_dec_number(const std::string& str);
  static bool is_char(const std::string& str);

  static bool is_binary_char(char c);
  static bool is_hex_char(char c);

  std::vector<int>& from_inparse_to_in;

  friend Interpreter;

public:
  Parser(Lexer lexer_, std::map<std::string, int>& labels_, std::vector<int>& inparse_to_in_): lexer(lexer_), labels(labels_), from_inparse_to_in(inparse_to_in_)  {}
  

  static std::map<std::string, Register> get_register_names() {
    return registers_names;
  }

  static std::vector<std::string> check_syntax(std::vector<std::string> args_tokens, std::string& instruction_token, int line);

  std::vector<Instruction*> get_instructions();
  static Register get_register(const std::string& str);
  static std::vector<std::string> get_offset(const std::vector<std::string>& args);
  static long get_immediate(const std::string& str);
  static bool is_number(const std::string& str);
};

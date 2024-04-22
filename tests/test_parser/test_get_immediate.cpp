#include "../../frontend/Parser.hpp"
#include <assert.h>
#include <cassert>
#include <type_traits>

void Itest_1() { assert(Parser::get_immediate("12") == 12); }

void Itest_2() { assert(Parser::get_immediate("012") == 12); }

void Itest_3() { assert(Parser::get_immediate("-12") == -12); }

void Itest_4() { assert(Parser::get_immediate("123") == 123); }

void Itest_5() { assert(Parser::get_immediate("0x1") == 1); }

void Itest_6() { assert(Parser::get_immediate("0x67") == 103); }

void Itest_7() { assert(Parser::get_immediate("-0x67") == -103); }

void Itest_8() { assert(Parser::get_immediate("0b1001") == 9); }

void Itest_9() { assert(Parser::get_immediate("-0b1001") == -9); }

void Itest_10() { assert(Parser::get_immediate("-0b01001") == -9); }

void Itest_11() { assert(Parser::get_immediate("'1'") == '1'); }

void Itest_12() { assert(Parser::get_immediate("'\n'") == '\n'); }

void test_get_immediate() {
  Itest_1();
  Itest_2();
  Itest_3();
  Itest_4();
  Itest_5();
  Itest_6();
  Itest_7();
  Itest_8();
  Itest_9();
  Itest_10();
  Itest_11();
  Itest_12();

  std::cout << "Get immediate tests passed" << std::endl;
}

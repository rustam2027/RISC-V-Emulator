#include "../../frontend/Parser.hpp"
#include <algorithm>
#include <assert.h>

void Ntest_1() { assert(Parser::is_number("123")); }

void Ntest_2() { assert(Parser::is_number("-1")); }

void Ntest_3() { assert(Parser::is_number("0x1")); }

void Ntest_4() { assert(Parser::is_number("0x11")); }

void Ntest_5() { assert(Parser::is_number("-0x11")); }

void Ntest_6() { assert(Parser::is_number("-0xa1")); }

void Ntest_7() { assert(Parser::is_number("0b11")); }

void Ntest_8() { assert(Parser::is_number("-0b11")); }

void Ntest_9() { assert(!Parser::is_number("12a")); }

void Ntest_10() { assert(!Parser::is_number("0xz1")); }

void Ntest_11() { assert(!Parser::is_number("0b12")); }

void Ntest_12() { assert(!Parser::is_number("0b")); }

void Ntest_13() { assert(!Parser::is_number("0x")); }

void Ntest_14() { assert(!Parser::is_number("")); }

void Ntest_15() { assert(!Parser::is_number("-")); }

void Ntest_16() { assert(!Parser::is_number("-0x")); }

void Ntest_17() { assert(!Parser::is_number("-0b")); }

void Ntest_18() { assert(Parser::is_number("0x10")); }

void Ntest_19() { assert(Parser::is_number("'9'")); }

void Ntest_20() { assert(Parser::is_number("'\n'")); }

void Ntest_21() { assert(Parser::is_number("'\b'")); }


void test_is_number() {
  Ntest_1();
  Ntest_2();
  Ntest_3();
  Ntest_4();
  Ntest_5();
  Ntest_6();
  Ntest_7();
  Ntest_8();
  Ntest_9();
  Ntest_10();
  Ntest_11();
  Ntest_12();
  Ntest_13();
  Ntest_14();
  Ntest_15();
  Ntest_16();
  Ntest_17();
  Ntest_18();
  Ntest_19();
  Ntest_20();
  Ntest_21();

  std::cout << "Is number tests passed!" << std::endl;
}

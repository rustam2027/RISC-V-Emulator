#include "../../frontend/Parser.hpp"
#include <assert.h>
#include <cassert>

void Otest_1() {
    std::vector<std::string> vec = {"a0", "0", "sp"};
    assert(Parser::get_offset({"a0", "0(sp)"}) == vec);
    cout << "get_offset test_1 passed" << endl;
}

void Otest_2() {
    std::vector<std::string> vec = {"s0", "-12", "a3"};
    assert(Parser::get_offset({"s0", "-12(a3)"}) == vec);
    cout << "get_offset test_2 passed" << endl;
}

void Otest_3() {
    std::vector<std::string> vec = {"a0", "4", "sp"};
    assert(Parser::get_offset({"a0", "4(sp)"}) == vec);
    cout << "get_offset test_3 passed" << endl;
}

void test_get_offset() {
    Otest_1();
    Otest_2();
    Otest_3();
    std::cout << "All get_offset tests passed!" << endl;
}
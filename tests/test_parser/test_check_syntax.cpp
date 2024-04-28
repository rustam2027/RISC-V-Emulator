#include "../../frontend/Parser.hpp"
#include "../../exceptions/ParserException.hpp"
#include <assert.h>

void Stest_0() {
    std::vector<std::string> in = {"a0", ",", "a0", ",", "1"};
    std::vector<std::string> out = {"a0", "a0", "1"};
    assert(Parser::check_syntax(in) == out);
    cout << "check_sytax test 0 passed!" << endl;
   
}
void Stest_1() {
    std::vector<std::string> in = {"a0", ",", ",", "a0", ",", "1"};
    try {
        auto res = Parser::check_syntax(in);
    } catch (ParserException e) {
        cout << "check_sytax test 1 passed!" << endl;
    }
}

void Stest_2() {
    std::vector<std::string> in = {"a0", ",", "a0", ",", "1", ","};
    try {
        auto res = Parser::check_syntax(in);
    } catch (ParserException e) {
        cout << "check_sytax test 2 passed!" << endl;
    }
}

void Stest_3() {
    std::vector<std::string> in = {"a0", ",", "a0", ",", "1", "a0"};
    try {
        auto res = Parser::check_syntax(in);
    } catch (ParserException e) {
        cout << "check_sytax test 3 passed!" << endl;
    }
}
void Stest_4() {
    std::vector<std::string> in = {"a0", "a0", ",", "1", ","};
    try {
        auto res = Parser::check_syntax(in);
    } catch (ParserException e) {
        cout << "check_sytax test 4 passed!" << endl;
    }
}

void test_check_sytax() {
    Stest_0();
    Stest_1();
    Stest_2();
    Stest_3();
    cout << "All get syntax tests passed!";
}
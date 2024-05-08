#include "../../frontend/Parser.hpp"
#include "../../frontend/Preprocessor.hpp"
#include "../../frontend/Lexer.hpp"
#include "assert.h"




void Ltest_1() {
    Preprocessor preprocessor = Preprocessor("labels_input/1-in.txt");
    preprocessor.preprocess();
    Lexer lexer(preprocessor.get_inparse());
    Parser parser(lexer, preprocessor.get_labels());
    vector<Instruction*> instructions;
    try {
        instructions = parser.get_instructions();
    } catch (const ParserException& e) {
        assert(e.get_message() == "Jump to a non-existent label: j label_111");
        cout << "labels test 1 passed!" << endl;
    }
}

void Ltest_2() {
    Preprocessor preprocessor = Preprocessor("labels_input/2-in.txt");
    preprocessor.preprocess();
    Lexer lexer(preprocessor.get_inparse());
    Parser parser(lexer, preprocessor.get_labels());
    vector<Instruction*> instructions;
    try {
        instructions = parser.get_instructions();
    } catch (const ParserException& e) {
        assert(e.get_message() == "Jump to a non-existent label: bgt t1 t2 label_33");
        cout << "labels test 2 passed!" << endl;
    }
}

void Ltest_3() {
    Preprocessor preprocessor = Preprocessor("labels_input/3-in.txt");
    preprocessor.preprocess();
    Lexer lexer(preprocessor.get_inparse());
    Parser parser(lexer, preprocessor.get_labels());
    vector<Instruction*> instructions;
    try {
        instructions = parser.get_instructions();
    } catch (const ParserException& e) {
        assert(e.get_message() == "Jump to a non-existent label: bne a1 a2 my_label");
        cout << "labels test 3 passed!" << endl;
    }
}

void Ltest_4() {
    Preprocessor preprocessor = Preprocessor("labels_input/4-in.txt");
    try {
        preprocessor.preprocess();
    } catch (const PreprocessorException& e) {
        assert(e.get_message() == "Name conflict, need to rename label: my_macro_0_my_main");
        cout << "labels test 4 passed!" << endl;
    }
}



void test_labels() {
    Ltest_1();
    Ltest_2();
    Ltest_3();
    Ltest_4();
    cout << "All labels tests passed!" << endl;
}
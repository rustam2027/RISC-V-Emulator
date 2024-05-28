#include "../../frontend/Parser.hpp"
#include "../../frontend/Preprocessor.hpp"
#include "../../frontend/Lexer.hpp"
#include "assert.h"




void Ltest_1() {
    Preprocessor preprocessor = Preprocessor("labels_input/1-in.txt");
    preprocessor.preprocess();
    Lexer lexer(preprocessor.get_inparse());
    Parser parser(lexer, preprocessor.get_labels(), preprocessor.get_from_inparse_to_in());
    vector<Instruction*> instructions;
    try {
        instructions = parser.get_instructions();
    } catch (const ParserException& e) {
        assert(e.get_message() == "Using non-existent label in line 4: label_111");
        cout << "labels test 1 passed!" << endl;
    }
}

void Ltest_2() {
    Preprocessor preprocessor = Preprocessor("labels_input/2-in.txt");
    preprocessor.preprocess();
    Lexer lexer(preprocessor.get_inparse());
    Parser parser(lexer, preprocessor.get_labels(), preprocessor.get_from_inparse_to_in());
    vector<Instruction*> instructions;
    try {
        instructions = parser.get_instructions();
    } catch (const ParserException& e) {
        assert(e.get_message() == "Using non-existent label in line 4: label_33");
        cout << "labels test 2 passed!" << endl;
    }
}

void Ltest_3() {
    Preprocessor preprocessor = Preprocessor("labels_input/3-in.txt");
    preprocessor.preprocess();
    Lexer lexer(preprocessor.get_inparse());
    Parser parser(lexer, preprocessor.get_labels(), preprocessor.get_from_inparse_to_in());
    vector<Instruction*> instructions;
    try {
        instructions = parser.get_instructions();
    } catch (const ParserException& e) {
        assert(e.get_message() == "Using non-existent label in line 4: my_label");
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

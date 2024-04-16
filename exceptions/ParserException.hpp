#pragma once
#include "EmulatorException.hpp"

class ParserException: public EmulatorException {
    public:
        ParserException(const string& message): EmulatorException(message) {}

        ParserException(const string& instruction, int required, int provided) { 
            message = "invalid amount of args in " + instruction + ": required " +
                      to_string(required) + ", provided " + to_string(provided);
        }
};

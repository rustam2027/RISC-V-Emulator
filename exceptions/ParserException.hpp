#pragma once
#include "EmulatorException.hpp"

class ParserException: public EmulatorException {
    public:
        ParserException(const std::string& message): EmulatorException(message) {}

        ParserException(const std::string& instruction, int required, int provided) { 
            message = "invalid amount of args in " + instruction + ": required " +
                      std::to_string(required) + ", provided " + std::to_string(provided);
        }
};

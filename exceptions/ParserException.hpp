#pragma once
#include "EmulatorException.hpp"

class ParserException: public EmulatorException {
    public:
        ParserException(const std::string& message): EmulatorException(message) {}
};

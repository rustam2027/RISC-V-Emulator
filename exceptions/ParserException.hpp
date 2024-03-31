#pragma once
#include "EmulatorException.hpp"

class ParserException: public EmulatorException {
    public:
        ParserException(const std::string& message): EmulatorException(message) {}
};

class CommandCreationException: public ParserException {
    public:
        CommandCreationException(const std::string& message): ParserException(message) {}
};

#pragma once
#include "EmulatorException.hpp"

class PreprocessorException: public EmulatorException {
    public:
        PreprocessorException(const std::string& message): EmulatorException(message) {}
};
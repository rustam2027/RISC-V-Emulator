#pragma once
#include "EmulatorException.hpp"

class RuntimeException: public EmulatorException {
    public:
        RuntimeException(const std::string& message): EmulatorException(message) {}
};

class EcallException: public RuntimeException {
    public:
        EcallException(const std::string& message): RuntimeException(message) {}
};

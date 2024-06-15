#pragma once
#include <string>

class ArgsParsingExceprion {
   public:
    ArgsParsingExceprion() = default;
    ArgsParsingExceprion(const std::string& message) : message(message) {};
    std::string get_message() const { return message; };

   protected:
    std::string message;
};

#pragma once
#include <string>

class EmulatorException {
public:
  EmulatorException(const std::string& message): message(message){};
  std::string get_message() const {return message;};

private:
  std::string message;
};

#pragma once
#include <string>

class EmulatorException {
public:
  EmulatorException()=default;
  EmulatorException(const std::string& message): message(message){};
  std::string get_message() const {return message;};

protected:
  std::string message;
};

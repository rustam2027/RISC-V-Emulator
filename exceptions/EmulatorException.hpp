#include <string>

class EmulatorException {
public:
  EmulatorException(std::string message): message(message){};
  std::string get_message() const {return message;};

private:
  std::string message;
};
